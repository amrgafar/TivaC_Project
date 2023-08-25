/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   dynamic_memory.h                                             *
 *                                                                             *
 * [AUTHOR]:      Amr Gafar                                                    *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        21/08/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: header file for dynamic memory allocation driver             *
 *                                                                             *
 *******************************************************************************/

#ifndef DYNAMIC_MEMORY_H_
#define DYNAMIC_MEMORY_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
/* Create a node */
struct Node {
  int data;
  struct Node* next;
};

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Insert at the beginning */
void insertAtBeginning(struct Node** head_ref, int new_data);

/* Insert a node after a node */
void insertAfter(struct Node* prev_node, int new_data);

/* Insert the the end */
void insertAtEnd(struct Node** head_ref, int new_data);

/* Delete a node */
void deleteNode(struct Node** head_ref, int key);

/* Search a node */
int searchNode(struct Node** head_ref, int key);

/* Sort the linked list */
void sortLinkedList(struct Node** head_ref);

/* Print the linked list */
void printList(struct Node* node);



#endif /* DYNAMIC_MEMORY_H_ */
