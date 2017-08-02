#ifndef __TINY_UV_H
#define __TINY_UV_H

#include <stdint.h>

struct uv_loop_s {
  void *data;
  uint64_t time;
  void *watcher_handles;
};

struct uv_watcher_s {
  void *data;
  struct uv_loop_s *loop;
};

/* Handles */
typedef struct uv_loop_s uv_loop_t;

/* Loops */
uv_loop_t* uv_default_loop(void);
int uv_loop_init(uv_loop_t* loop);
int uv_loop_close(uv_loop_t* loop);
int uv_run(uv_loop_t* loop);

#endif /* __TINY_UV_H */
