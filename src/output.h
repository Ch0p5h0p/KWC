//
// Created by radar77 on 7/15/26.
//

#ifndef KWC_OUTPUT_H
#define KWC_OUTPUT_H
#include <time.h>
#include <wayland-server-core.h>

struct kwc_output {
    int width, height;

    struct wlr_output *wlr_output;
    struct kwc_server *server;
    struct timespec last_frame;

    struct wl_listener destroy;
    struct wl_listener frame;

    struct wl_list link;
};

void output_frame_notify(struct wl_listener *listener, void *data);

void output_destroy_notify(struct wl_listener *listener, void *data);

void new_output_notify(struct wl_listener *listener, void *data);

#endif //KWC_OUTPUT_H
