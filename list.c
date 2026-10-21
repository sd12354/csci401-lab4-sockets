// list.c
// linked list implementation (from lab 1)
// Sameer Dhanda

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *list_alloc() {
  list_t* mylist = (list_t *) malloc(sizeof(list_t));
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  node_t *current = l->head;
  while (current != NULL) {
    node_t *next = current->next;   // save next before freeing
    free(current);
    current = next;
  }
  l->head = NULL;
  free(l);
}

void list_print(list_t *l) {
  char *text = listToString(l);
  printf("%s\n", text);
  free(text);
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  char tbuf[20];
  buf[0] = '\0';   // strcat needs an empty string to start
  node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) {
  int length = 0;
  node_t *current = l->head;
  while (current != NULL) {
    length++;
    current = current->next;
  }
  return length;
}

void list_add_to_back(list_t *l, elem value) {
  node_t *cur_node = getNode(value);
  // empty list, new node is the head
  if (l->head == NULL) {
    l->head = cur_node;
    return;
  }
  node_t *current = l->head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = cur_node;
}

void list_add_to_front(list_t *l, elem value) {
  node_t *cur_node = (node_t *) getNode(value);
  /* Insert to front */
  node_t *head = l->head;  // get head of list
  cur_node->next = head;
  l->head = cur_node;
}

node_t * getNode(elem value) {
  node_t *mynode;
  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;
  return mynode;
}

// index starts at 1, index length+1 adds to the back
void list_add_at_index(list_t *l, elem value, int index) {
  if (index < 1 || index > list_length(l) + 1) {
    return;
  }
  if (index == 1) {
    list_add_to_front(l, value);
    return;
  }
  // stop one before so we have the previous node
  node_t *previous = l->head;
  for (int position = 1; position < index - 1; position++) {
    previous = previous->next;
  }
  node_t *cur_node = getNode(value);
  cur_node->next = previous->next;
  previous->next = cur_node;
}

elem list_remove_from_back(list_t *l) {
  if (l->head == NULL) {
    return -1;
  }
  // only one node, same as removing from front
  if (l->head->next == NULL) {
    return list_remove_from_front(l);
  }
  node_t *previous = l->head;
  while (previous->next->next != NULL) {
    previous = previous->next;
  }
  node_t *removed = previous->next;
  elem value = removed->value;
  previous->next = NULL;
  free(removed);
  return value;
}

elem list_remove_from_front(list_t *l) {
  if (l->head == NULL) {
    return -1;
  }
  node_t *removed = l->head;
  elem value = removed->value;
  l->head = removed->next;
  free(removed);
  return value;
}

// index starts at 1, returns -1 if out of range
elem list_remove_at_index(list_t *l, int index) {
  if (index < 1 || index > list_length(l)) {
    return -1;
  }
  if (index == 1) {
    return list_remove_from_front(l);
  }
  node_t *previous = l->head;
  for (int position = 1; position < index - 1; position++) {
    previous = previous->next;
  }
  node_t *removed = previous->next;
  elem value = removed->value;
  previous->next = removed->next;
  free(removed);
  return value;
}

bool list_is_in(list_t *l, elem value) {
  return list_get_index_of(l, value) != -1;
}

// index starts at 1, returns -1 if not there
elem list_get_elem_at(list_t *l, int index) {
  if (index < 1) {
    return -1;
  }
  int position = 1;
  node_t *current = l->head;
  while (current != NULL) {
    if (position == index) {
      return current->value;
    }
    position++;
    current = current->next;
  }
  return -1;
}

// 1 based index of first match, -1 if not found
int list_get_index_of(list_t *l, elem value) {
  int index = 1;
  node_t *current = l->head;
  while (current != NULL) {
    if (current->value == value) {
      return index;
    }
    index++;
    current = current->next;
  }
  return -1;
}
