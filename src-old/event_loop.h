#ifndef __EVENT_LOOP_H
#define __EVENT_LOOP_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
  EVT_NOTHING,
  EVT_COMMAND,
  EVT_SERIAL1
} io_event_type_t;

// io event type
typedef struct {
  io_event_type_t type;
  void* data;
} io_event_t;

// io event functions
void event_loop_init();
void event_loop_close();
void event_loop_process();

unsigned int get_queue_size();
bool is_queue_empty();
bool is_queue_full();
unsigned int push_event(io_event_t *event);
io_event_t* pop_event();

#endif /* __EVENT_LOOP_H */
