//
// Created by radar77 on 7/13/26.
//

//#include "output.h"

#include "server.h"

#include "output.h"

#include <stdio.h>
#include <assert.h>

#include <wayland-server-core.h>
#include <wlroots-0.20/wlr/backend.h>
#include <wlroots-0.20/wlr/backend/session.h>
#include <wlroots-0.20/wlr/types/wlr_output.h>
#include <wlroots-0.20/wlr/render/pass.h>
#include <wlroots-0.20/wlr/render/allocator.h>
#include <wlroots-0.20/wlr/render/wlr_renderer.h>
#include <wlroots-0.20/wlr/util/box.h>

int main(int argc, char *argv[]) {
    struct kwc_server server;

    server.wl_display = wl_display_create();
    assert(server.wl_display);
    server.wl_event_loop = wl_display_get_event_loop(server.wl_display);
    assert(server.wl_event_loop);

    server.session = wlr_session_create(server.wl_event_loop);
    assert(server.session);
    server.backend = wlr_backend_autocreate(server.wl_event_loop, &server.session);
    assert(server.backend);

    server.renderer = wlr_renderer_autocreate(server.backend);
    assert(server.renderer);
    server.allocator = wlr_allocator_autocreate(server.backend, server.renderer);
    assert(server.allocator);

    wl_list_init(&server.outputs);

    server.new_output.notify = new_output_notify;
    wl_signal_add(&server.backend->events.new_output, &server.new_output);

    if (!wlr_backend_start(server.backend)) {
        fprintf(stderr, "Failed to start server backend\n");
        wl_display_destroy(server.wl_display);
        return 1;
    }

    wl_display_run(server.wl_display);
    wl_display_destroy(server.wl_display);

    return 0;
}
