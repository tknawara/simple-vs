/*
 * File: list.h
 * Description: Holder for the definition of the list structure
 * Created at: 2018-1-21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct l_node {
  void *data;
  struct l_node *next;
  struct l_node *prev;
};

/* Prepend the given data to the list. */
void add(struct l_node **list_ptr, void *data, int size);

/* Append the given data to the end of the list. */
void append(struct l_node **list_ptr, void *data, int size);

/* Get the element at the given index. 
   Will return NULL if the list is empty
   or index is greater than the length
   of the list. */
void *get(struct l_node *list, int index);

/* Remove the given node from the list. */
void pop(struct l_node **list_ptr);

/* Get the size of the list */
int size(struct l_node *list);

/* Reverse the given list */
void reverse(struct l_node **list_ptr);

/* Free the memory allocated to the list. */
void destroy_list(struct l_node *list);
