/*******************************************************************************
 * Name        : linked_list.h
 * Author      : Maxwell Metzner, Savnick Patel
 * Date        : 2/26/21
 * Description : Linked List insertion implementation.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdio.h>
#include <string.h>
#include "node.h"

typedef struct linked_list {
	node *head;
	node *tail;
	size_t num_nodes;
} linked_list;

linked_list* create_linked_list() {
	return (linked_list *)calloc(1, sizeof(linked_list));
}

/**
 * Inserts a non-NULL node into a non-NULL linked list.
 * The node is inserted so that the data in the linked list is in
 * non-decreasing order.
 * A node with a value already in the list is inserted AFTER the node(s)
 * already in the list.
 */
void insert_in_order(linked_list *list, node *n,
		int (*cmp)(const void*, const void*)) {
	//When list is empty, start list with n
	if(list->num_nodes == 0){
		list->head = n;
		list-> tail = n;
		++list->num_nodes;
	} else {
		node *prv = list->head;
		node *cur = prv->next;
		if(list->num_nodes == 1){
			if(cmp(n,prv) >= 0){
				list->tail = n;
				prv->next = n;
				n->prev = prv;
				++list->num_nodes;
			} else {
				list->head = n;
				n->next = prv;
				prv->prev = n;
				++list->num_nodes;
			}
		} else {
			//loop as long as there is a next node
			while(cur != NULL){
				//if n is greater than the next node
				if(cmp(n,cur) >= 0){
					if(cur == list->tail){
						//provisions if new node is going to be the tail
						list->tail = n;
						cur->next = n;
						n->prev = cur;
						++list->num_nodes;
						break;
					} else {
						if(cmp(n,cur->next) < 0){
							prv->next = n;
							cur-> prev = n;
							n->prev = prv;
							n->next = cur;
							++list->num_nodes;
							break;
						}
					}
				} else {
					//insert n as new head
					if(cur == list->head){
						list->head = n;
						n->next = cur;
						cur->prev = n;
					} else {
						//insert n without incrementing cur
						n->next = cur;
						cur->prev = n;
						n->prev = prv;
						prv->next = n;
					}
					++list->num_nodes;
					break;
				}
				prv = cur;
				cur = cur->next;
			}
		}
	}
}

void print_list(linked_list *list, void (*print_function)(void*)) {
	putchar('[');
	node *cur = list->head;
	if (cur != NULL) {
		print_function(cur->data);
		cur = cur->next;
	}
	for ( ; cur != NULL; cur = cur->next) {
		printf(", ");
		print_function(cur->data);
	}
	printf("]\n{length: %lu, head->data: ", list->num_nodes);
	list->head != NULL ? print_function(list->head->data) :
			(void)printf("NULL");
	printf(", tail->data: ");
	list->tail != NULL ? print_function(list->tail->data) :
			(void)printf("NULL");
	printf("}\n\n");
}

/**
 * Frees a list starting from the tail.
 * This will check if your previous pointers have been set up correctly.
 */
void free_list(linked_list *list, void (*free_data)(void *)) {
	while (list->tail != NULL) {
		node *prev = list->tail->prev;
		free_node(list->tail, free_data);
		list->tail = prev;
	}
}

#endif