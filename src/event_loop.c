
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "event_loop.h"
#include "kameleon_config.h"

#include "hardware.h"
#include "jerryscript.h"

/**
 * An circular structure queue.
 * Actual maximum number of queue entries is (MAX_EVENT_QUEUE_SIZE - 1)
 */
io_event_t *event_queue[MAX_EVENT_QUEUE_SIZE];

/**
 * head index points the first entry.
 */
unsigned int head_index = 0;

/**
 * tail index points the entry where the next pushed item will be placed.
 */
unsigned int tail_index = 0;

/**
 * Initialize event queue
 */
void event_loop_init() {
  head_index = 0;
  tail_index = 0;
}

/**
 * Finalize event queue
 */
void event_loop_close() {
}

void print_to_uart(char *data, unsigned int size) {
  uart_transmit(data, size);
}

void print_value (const jerry_value_t value)
{
  if (jerry_value_is_undefined (value))
  {
    print_to_uart("undefined", 9);
  }
  else if (jerry_value_is_null (value))
  {
    print_to_uart("null", 4);
  }
  else if (jerry_value_is_boolean (value))
  {
    if (jerry_get_boolean_value (value))
    {
      print_to_uart("true", 4);
    }
    else
    {
      print_to_uart("false", 5);
    }
  }
  /* Float value */
  else if (jerry_value_is_number (value))
  {
    print_to_uart("number", 6);
  }
  /* String value */
  else if (jerry_value_is_string (value))
  {
    /* Determining required buffer size */
    jerry_size_t req_sz = jerry_get_string_size (value);
    jerry_char_t str_buf_p[req_sz];

    jerry_string_to_char_buffer (value, str_buf_p, req_sz);
    str_buf_p[req_sz] = '\0';
    print_to_uart((char *) str_buf_p, req_sz);
    // printf ("%s", (const char *) str_buf_p);
  }
  /* Object reference */
  else if (jerry_value_is_object (value))
  {
    print_to_uart("[object]", 8);
  }

  print_to_uart("\r\n", 2);
}

void handle_command_event(io_event_t *event) {
  jerry_value_t parsed_code = jerry_parse(event->data, strlen(event->data), false);
  if (!jerry_value_has_error_flag (parsed_code)) {
    jerry_value_t ret_value = jerry_run(parsed_code);
    print_value(ret_value);
    jerry_release_value(ret_value);
  }
  jerry_release_value(parsed_code);
  free(event->data);
}

/**
 * Process an event at head index in the queue.
 */
void event_loop_process() {
  if (!is_queue_empty()) {
    io_event_t *event = pop_event();
    switch (event->type) {
      case EVT_COMMAND:
        handle_command_event(event);
        break;
      default:
        // do nothing
        break;
    }
    free(event);
  }
}

/**
 * Return size of the queue.
 */
unsigned int get_queue_size() {
  unsigned int size = 0;
  if (head_index < tail_index) {
    size = (tail_index - head_index);
  } else if (head_index > tail_index) {
    size = ((MAX_EVENT_QUEUE_SIZE) - head_index) + tail_index;
  }
  return size;
}

/**
 * Check whether the queue is empty.
 */
bool is_queue_empty() {
  return (get_queue_size() == 0);
}

/**
 * Check whether the queue is full.
 */
bool is_queue_full() {
  return (get_queue_size() == ((MAX_EVENT_QUEUE_SIZE) - 1));
}

/**
 * Return a next index of a given index pointing a queue entry.
 */
unsigned int next_index(unsigned int index) {
  if (index == ((MAX_EVENT_QUEUE_SIZE) - 1)) {
    return 0;
  } else {
    return index + 1;
  }
}

/**
 * Return an index of a queue entry where event is pushed.
 */
unsigned int push_event(io_event_t *event) {
  if (is_queue_full()) {
    return -1;
  } else {
    event_queue[tail_index] = event;
    tail_index = next_index(tail_index);
    return tail_index;
  }
}

/**
 * Return 0 if queue is empty
 */
io_event_t* pop_event() {
  if (is_queue_empty()) {
    return 0; // null
  } else {
    io_event_t *event = event_queue[head_index];
    head_index = next_index(head_index);
    return event;
  }
}
