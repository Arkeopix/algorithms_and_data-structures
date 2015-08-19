#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void	print(sl_node *node) {
	printf("%s\n", (char*)node->data);
}

int		singly_linked_list_pop(sl_node **head) {
	sl_node *tmp = NULL;

	if (*head == NULL) {
		return -1;
	}
	tmp = (*head)->next;
	free(*head);
	*head = tmp;
	return 0;
}

int		singly_linked_list_remove_last(sl_node *head) {
	sl_node *tmp = head;
	
	if (head->next == NULL) {
		free(head);
		return 0;
	}
	while (tmp->next->next != NULL) {
		tmp = tmp->next;
	}
	free(tmp->next);
	tmp->next = NULL;
	return 0;
}

void	singly_linked_list_do(sl_node *head, void (func)(sl_node *)) {
	sl_node *tmp = head;

	while (tmp != NULL) {
		func(tmp);
		tmp = tmp->next;
	}
}

void	singly_linked_list_push_front(sl_node **head, void *data) {
	sl_node *new = NULL;

	new = malloc(sizeof *new);
	if (new) {
		new->data = data;
		new->next = *head;
		*head = new;
	}
}

void 	singly_linked_list_push_end(sl_node *head, void *data) {
	sl_node *tmp = head;

	if (tmp->data == NULL) {
		tmp->data = data;
		tmp->next = NULL;
	} else {
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = malloc(sizeof *tmp);
		tmp->next->data = data;
		tmp->next->next = NULL;
	}
}

sl_node	 *singly_linked_list_init() {
	sl_node *node = NULL;

	node = malloc(sizeof *node);
	if (node) {
		node->data = NULL;
		node->next = NULL;
	}
	return node;
}

int main(void) {
	sl_node *head = singly_linked_list_init();

	singly_linked_list_push_end(head, "coucou");
	singly_linked_list_push_end(head, "lol");
	singly_linked_list_push_end(head, "poil");
	singly_linked_list_push_front(&head, "enculer");
	singly_linked_list_push_front(&head, "salaud");
	singly_linked_list_push_front(&head, "mougaga");
	singly_linked_list_do(head, &print);
	singly_linked_list_pop(&head);
	printf("pop happend\n");
	singly_linked_list_do(head, &print);
	printf("removelast\n");
	singly_linked_list_remove_last(head);
	singly_linked_list_do(head, &print);
	free_singly_linked_list(head);
	return 0;
}
