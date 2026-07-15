//
// Created by radar77 on 7/15/26.
//

#include "output.h"
#include "server.h"

#include <stdlib.h>
#include <wlroots-0.20/wlr/render/pass.h>
#include <wlroots-0.20/wlr/types/wlr_output.h>
#include <wlroots-0.20/wlr/util/box.h>
#include <wayland-server-core.h>

void output_frame_notify(struct wl_listener *listener, void *data) {
    struct kwc_output *output = wl_container_of(listener, output, frame);
    struct wlr_output *wlr_output = data;

    struct wlr_output_state state;
    wlr_output_state_init(&state);

    struct wlr_render_pass *render_pass = wlr_output_begin_render_pass(wlr_output, &state, NULL);

    if (render_pass == NULL) {
        wlr_output_state_finish(&state);
        return;
    }
    // Set a clear color, RGBA. Allow this to be configured later
    struct wlr_render_color clear_color = {
        .r = 0.1f,
        .g = 0.1f,
        .b = 0.1f,
        .a = 1.0f
    };

    wlr_render_pass_add_rect(render_pass, &(struct wlr_render_rect_options){
        .box = {
            .x = 0,
            .y = 0,
            .width = output->width,
            .height = output->height,
        },
        .color = clear_color,
        .blend_mode = WLR_RENDER_BLEND_MODE_NONE,
    });

    if (!wlr_render_pass_submit(render_pass)) {
        wlr_output_state_finish(&state);
        return;
    }

    if (!wlr_output_commit_state(wlr_output, &state)) {
        // handle commit failure here
    }

}

void output_destroy_notify(struct wl_listener *listener, void *data) {
    struct kwc_output *output = wl_container_of(listener, output, destroy);
    wl_list_remove(&output->link);
    wl_list_remove(&output->destroy.link);
    wl_list_remove(&output->frame.link);
    free(output);
}

void new_output_notify(struct wl_listener *listener, void *data) {
    struct kwc_server *server = wl_container_of(listener, server, new_output);
    struct wlr_output *wlr_output = data;

    // initialize renderer
    wlr_output_init_render(wlr_output, server->allocator, server->renderer);

    // initialize state
    struct wlr_output_state state;
    wlr_output_state_init(&state);
    wlr_output_state_set_enabled(&state, true);


    if (!wl_list_empty(&wlr_output->modes)) {
        // Grab preferred mode, set it
        struct wlr_output_mode *mode = wlr_output_preferred_mode(wlr_output);
        wlr_output_state_set_mode(&state, mode);
    }

    // Commit changes, free state
    wlr_output_commit_state(wlr_output, &state);
    wlr_output_state_finish(&state);

    struct kwc_output *output = calloc(1, sizeof(struct kwc_output));
    if (!output) {
        return;
    }
    clock_gettime(CLOCK_MONOTONIC, &output->last_frame);
    output->server = server;
    output->wlr_output = wlr_output;
    wl_list_insert(&server->outputs, &output->link);

    wlr_output_transformed_resolution(wlr_output, &output->width, &output->height);

    output->destroy.notify = output_destroy_notify;
    wl_signal_add(&wlr_output->events.destroy, &output->destroy);
    output->frame.notify = output_frame_notify;
    wl_signal_add(&wlr_output->events.frame, &output->frame);
}
