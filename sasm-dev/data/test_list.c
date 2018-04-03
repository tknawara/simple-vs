/*
 * File: test_list.c
 * Description: Testing the list functionality
 * Created at: 2018-1-21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int main(void)
{
  struct l_node *list = NULL;
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    add(&list, &x, sizeof(int));
  }
  printf("%d\n", size(list));
  for (int i = 0; i < size(list); ++i) {
    if (i > 0) printf(" ");
    printf("%d", *((int *) get(list, i)));
  }
  puts("");
  reverse(&list);
  for (int i = 0; i < size(list); ++i) {
    if (i > 0) printf(" ");
    printf("%d", *(int *) get(list, i));
  }
  puts("");
  destroy_list(list);
  return 0;
}
