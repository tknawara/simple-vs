/*
 * File: list.c
 * Description: Holder for the implementation of the list structure
 * Created at: 2018-1-21
 */

#include "list.h"

static void initialize_node(struct l_node **node, void *data, int size)
{
  void *copy = malloc(size);
  memcpy(copy, data, size);
  *node = malloc(sizeof(struct l_node));
  (*node)->data = copy;
  (*node)->next = NULL;
  (*node)->prev = NULL;
}

void add(struct l_node **list_ptr, void *data, int size)
{
  if ((*list_ptr) == NULL) {
    initialize_node(list_ptr, data, size);
    return;
  }
  struct l_node *node = NULL;
  initialize_node(&node, data, size);
  node->next = (*list_ptr);
  (*list_ptr)->prev = node;
  *list_ptr = node;
}

void append(struct l_node **list_ptr, void *data, int size)
{
  if ((*list_ptr) == NULL) {
    initialize_node(list_ptr, data, size);
    return;
  }
  struct l_node *node = NULL;
  initialize_node(&node, data, size);
  struct l_node *current = *list_ptr;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = node;
  node->prev = current;
}

void *get(struct l_node *list, int index)
{
  if (index < 0 || index >= size(list)) {
    return NULL;
  }
  struct l_node *current = list;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  return current->data;
}

void pop(struct l_node **list_ptr)
{
  if ((*list_ptr) == NULL) {
    puts("Error pop from empty list");
    return;
  }
  (*list_ptr) = (*list_ptr)->next;
}

int size(struct l_node *list)
{
  int res = 0;
  struct l_node *current = list;
  while (current != NULL) {
    current = current->next;
    ++res;
  }
  return res;
}

void reverse(struct l_node **list_ptr)
{
  if ((*list_ptr) == NULL || (*list_ptr)->next == NULL) return;
  struct l_node *prev = NULL;
  struct l_node *cur = *list_ptr;
  struct l_node *next = cur->next;
  while (next != NULL) {
    cur->next = prev;
    prev = cur;
    cur = next;
    next = next->next;
  }
  cur->next = prev;
  *list_ptr = cur;
}

void destroy_list(struct l_node *list)
{
  if (list == NULL) {
    return;
  }
  struct l_node *current = list;
  struct l_node *prev = NULL;
  while (current != NULL) {
    prev = current;
    current = current->next;
    free(prev);
  }
  free(prev);
}
