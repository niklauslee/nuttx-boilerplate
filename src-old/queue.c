
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

/**
 * Initialize a queue
 */
int queue_init(queue_t *queue) {
  queue->head = NULL;
  queue->tail = NULL;
}

/**
 * Test whether queue is empty or not
 */
bool queue_is_empty(queue_t *queue) {
  return (queue->head == NULL && queue->tail == NULL);
}

/**
 * Push an item to the queue (at the tail)
 */
int queue_push(queue_t *queue, void *data) {
  queue_entry_t *entry = malloc(sizeof(queue_entry_t));
  entry->data = data;
  entry->next = NULL;
  if (queue_is_empty(queue)) {
    queue->tail = entry;
    queue->head = entry;
  } else {
    queue->tail->next = entry;
    queue->tail = entry;
  }
}

/**
 * Pop an item from the queue (at the head)
 */
void* queue_pop(queue_t *queue) {
  if (queue_is_empty(queue)) {
    return NULL; // can't pop from empty queue
  } else {
    queue_entry_t *entry = queue->head;
    void *data = entry->data;
    queue->head = queue->head->next;
    free(entry);
    return data;
  }
}
