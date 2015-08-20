#ifndef 	LINKED_LIST_H_
#define 	LINKED_LIST_H_

typedef struct _singly_linked_list_node {
	void *data;
	struct _singly_linked_list_node *next;
} sl_node;

void	singly_linked_list_do(sl_node *head, void (func)(sl_node*));
void	singly_linked_list_push_front(sl_node **head, void *data);
void 	singly_linked_list_push_end(sl_node *head, void *data);
int		singly_linked_list_pop(sl_node **head);
int		singly_linked_list_remove_last(sl_node *head);
sl_node	*singly_linked_list_init();

#endif		/* !LINKED_LIST_H_ */
