//
// Created by radar77 on 7/15/26.
//

#ifndef KWC_SERVER_H
#define KWC_SERVER_H

#include <wayland-server.h>

struct kwc_server {
    struct wl_display *wl_display;
    struct wl_event_loop *wl_event_loop;

    struct wlr_session *session;
    struct wlr_backend *backend;

    struct wl_listener new_output;
    struct wl_list outputs;

    struct wlr_allocator *allocator;
    struct wlr_renderer *renderer;
};

#endif //KWC_SERVER_H
