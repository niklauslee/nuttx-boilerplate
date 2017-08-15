
#include <stddef.h>
#include "tiny-uv.h"

static uv_loop_t default_loop_struct;
static uv_loop_t* default_loop;

uv_loop_t* uv_default_loop(void) {
  if (default_loop != NULL) {
    return default_loop;
  }
  uv_loop_init(&default_loop_struct);
  default_loop = &default_loop_struct;
}

int uv_loop_init(uv_loop_t* loop) {

}

int uv_loop_close(uv_loop_t* loop) {

}

int uv_run(uv_loop_t* loop) {
  while (1) {
    // uv_update_time(loop);
    // uv_run_timers(loop);
    // uv_run_idle(loop);
  }
}

/*

struct uv_idle_s {
  // UV_HANDLE_FIELDS
  void* data;
  uv_loop_t* loop;
  uv_handle_type type;
  uv_close_cb close_cb;
  void* handle_queue[2];
  union {
    int fd;
    void* reserved[4];
  } u;
  uv_handle_t* next_closing;
  unsigned int flags;

  // UV_IDLE_PRIVATE_FIELDS
  uv_idle_cb idle_cb;
  void* queue[2];
};

int uv_idle_init(uv_loop_t* loop, uv_idle_t* handle) {
  uv__handle_init(loop, (uv_handle_t*)handle, UV_IDLE);
  handle->idle_cb = NULL;
  return 0;
}

int uv_idle_start(uv_idle_t* handle, uv_idle_cb cb) {
  if (uv__is_active(handle)) return 0;
  if (cb == NULL) return -EINVAL;
  QUEUE_INSERT_HEAD(&handle->loop->idle_handles, &handle->queue);
  handle->idle_cb = cb;
  uv__handle_start(handle);
  return 0;
}

int uv_idle_stop(uv_idle_t* handle) {
  if (!uv__is_active(handle)) return 0;
  QUEUE_REMOVE(&handle->queue);
  uv__handle_stop(handle);
  return 0;
}

void uv__run_idle(uv_loop_t* loop) {
  uv_idle_t* h;
  QUEUE queue;
  QUEUE* q;
  QUEUE_MOVE(&loop->idle_handles, &queue);
  while (!QUEUE_EMPTY(&queue)) {
    q = QUEUE_HEAD(&queue);
    h = QUEUE_DATA(q, uv_idle_t, queue);
    QUEUE_REMOVE(q);
    QUEUE_INSERT_TAIL(&loop->idle_handles, q);
    h->idle_cb(h);
  }
}

void uv__idle_close(uv_idle_t* handle) {
  uv_idle_stop(handle);
}
*/
