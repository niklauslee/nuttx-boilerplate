#ifndef __QUEUE_H
#define __QUEUE_H

struct queue_s {
  void *prev;
  void *next;
};

typedef struct queue_s queue_t;

void queue_init(queue_t *queue);
void queue_insert_tail(queue_t *queue, queue_t *entry);
void queue_insert_head(queue_t *queue, queue_t *entry);

#endif /* __QUEUE_H */
