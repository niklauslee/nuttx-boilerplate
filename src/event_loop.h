#include <stdint.h>

typedef enum {
  EVT_NOTHING,
  EVT_COMMAND,
  EVT_SERIAL1
} io_event_type_t;

// io event type
typedef struct {
  io_event_type_t type;
} io_event_t;

// io event functions
void event_loop_init();
void event_loop_close();
void push_event(io_event_t* event);
io_event_t* pop_event();
uint8_t has_event();
