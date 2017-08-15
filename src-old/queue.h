#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdbool.h>

struct queue_entry_s {
  void *data;
  struct queue_entry_s *next;
};

struct queue_s {
  struct queue_entry_s *head;
  struct queue_entry_s *tail;
};

typedef struct queue_s queue_t;
typedef struct queue_entry_s queue_entry_t;

int queue_init(queue_t *queue);
bool queue_is_empty(queue_t *queue);
int queue_push(queue_t *queue, void *data);
void* queue_pop(queue_t *queue);

#endif /* __QUEUE_H */
