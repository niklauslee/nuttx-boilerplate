
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "hardware.h"
#include "event.h"
#include "queue.h"
#include "console.h"
#include "jerryscript.h"

static ev_loop_t default_loop_struct;
static ev_loop_t* default_loop;

/**
 * Return the default loop
 */
ev_loop_t* ev_default_loop(void) {
  if (default_loop != NULL) {
    return default_loop;
  }
  ev_loop_init(&default_loop_struct);
  default_loop = &default_loop_struct;
}

/**
 * Initialize a loop
 */
int ev_loop_init(ev_loop_t *loop) {
  queue_init(&loop->queue);
}

/**
 * Close a loop
 */
int ev_loop_close(ev_loop_t *loop) {
  // Free all items in loop's queue
  while (!queue_is_empty(&loop->queue)) {
    void *data = queue_pop(&loop->queue);
    free(data);
  }
}

/**
 * Run an event-loop
 */
int ev_run(ev_loop_t* loop) {
  while (1) {
    // ev_update_time(loop);
    // ev_run_timers(loop);
    // ev_run_idle(loop);
  }
}


/*
int ev_event_init();
int ev_uart_init();
int ev_uart_start();
int ev_run_uarts();
int ev_uart_send();
int ev_uart_receive();
*/

/*
void print_value (const jerry_value_t value) {

  if (jerry_value_has_error_flag(value)) {
    console_error("Error.");
  } else {
    jerry_value_t str_value = jerry_value_to_string(value);


    jerry_size_t req_sz = jerry_get_string_size (str_value);
    jerry_char_t str_buf_p[req_sz + 1];

    jerry_string_to_char_buffer (str_value, str_buf_p, req_sz);
    str_buf_p[req_sz] = '\0';
    if (jerry_value_is_string(value)) {
      char str[req_sz + 3];
      strcpy(str, "\"");
      strcat(str, (char *) str_buf_p);
      strcat(str, "\"");
      console_log(str);
    } else if (jerry_value_is_array(value)) {
      char str[req_sz + 3];
      strcpy(str, "[");
      strcat(str, (char *) str_buf_p);
      strcat(str, "]");
      console_log(str);
    } else {
      console_log((char *) str_buf_p);
    }
  }
}

void handle_command_event(io_event_t *event) {
  jerry_value_t parsed_code = jerry_parse(event->data, strlen(event->data), false);
  if (jerry_value_has_error_flag (parsed_code)) {
    console_error("Syntax error while parsing code.");
  } else {
    jerry_value_t ret_value = jerry_run(parsed_code);
    print_value(ret_value);
    jerry_release_value(ret_value);
  }
  jerry_release_value(parsed_code);
  free(event->data);
}

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

unsigned int get_queue_size() {
  unsigned int size = 0;
  if (head_index < tail_index) {
    size = (tail_index - head_index);
  } else if (head_index > tail_index) {
    size = ((MAX_EVENT_QUEUE_SIZE) - head_index) + tail_index;
  }
  return size;
}

bool is_queue_empty() {
  return (get_queue_size() == 0);
}

bool is_queue_full() {
  return (get_queue_size() == ((MAX_EVENT_QUEUE_SIZE) - 1));
}

unsigned int next_index(unsigned int index) {
  if (index == ((MAX_EVENT_QUEUE_SIZE) - 1)) {
    return 0;
  } else {
    return index + 1;
  }
}

unsigned int push_event(io_event_t *event) {
  if (is_queue_full()) {
    return -1;
  } else {
    event_queue[tail_index] = event;
    tail_index = next_index(tail_index);
    return tail_index;
  }
}

io_event_t* pop_event() {
  if (is_queue_empty()) {
    return 0; // null
  } else {
    io_event_t *event = event_queue[head_index];
    head_index = next_index(head_index);
    return event;
  }
}
*/
