#ifndef __EVENT_H
#define __EVENT_H

#include <stdint.h>
#include <stdbool.h>
#include "queue.h"

enum ev_event_type {
  EVT_NOTHING,
  EVT_COMMAND,
  EVT_SERIAL1
} event_type_t;

struct ev_event_s {
  enum ev_event_type type;
  void* data;
  struct ev_event_s *prev;
  struct ev_event_s *next;
};

struct ev_loop_s {
  queue_t queue;
  uint64_t time;
};

typedef struct ev_event_s ev_event_t;
typedef struct ev_loop_s ev_loop_t;

ev_loop_t* ev_default_loop();
int ev_loop_init(ev_loop_t *loop);
int ev_loop_close(ev_loop_t *loop);
int ev_run(ev_loop_t* loop);

#endif /* __EVENT_H */
