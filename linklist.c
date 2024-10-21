#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __maybe_unused
#define __maybe_unused			__attribute__((unused))
#endif

struct linklist_node {
	int data;
	struct linklist_node *next;
};

struct link_node {
	int data;
	struct link_node *pre, *next;
};

static struct linklist_node *create_linklist_node(int data)
{
	struct linklist_node *node;

	node = malloc(sizeof(struct linklist_node));
	if (!node)
		goto err;

	node->data = data;
	node->next = NULL;
err:
	return node;
}

static void linklist_insert_pre(struct linklist_node *head, int data)
{
	struct linklist_node *node;

	node = create_linklist_node(data);
	if (!node) {
		goto err;
	}
	node->next = head->next;
	head->next = node;

err:
	return;
}

static void linklist_insert_post(struct linklist_node * head,int data)
{
	struct linklist_node *node;
	struct linklist_node *p;

	node = create_linklist_node(data);
	if (!node) {
		goto err;
	}

	p = head;
	while (p->next) {
		p = p->next;
	}

	p->next = node;

err:
	return;
}

static void linklist_print(struct linklist_node *head)
{
	struct linklist_node *p;

	p = head->next;
	while (p) {
		printf("%d ", p->data);
		p = p->next;
	}

	printf("\n");
	return;
}

static void linklist_free(struct linklist_node *head)
{
	struct linklist_node *p;
	struct linklist_node *q;

	if (!head)
		goto err;

	p = head;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}

err:
	return;
}


static void linklist_reverse(struct linklist_node *head)
{
	struct linklist_node *p, *q;

	if (!head)
		goto err;

	p = head->next;
	head->next = NULL;

	while (p) {
		q = p->next;
		p->next = head->next;
		head->next = p;
		p = q;
	}

err:
	return;
}

static struct linklist_node *linklist_get_node(struct linklist_node *head, int data)
{
	struct linklist_node *p;

	p = head->next;
	while (p) {
		if (p->data == data)
			break;
		p = p->next;
	}

	if (p) {
		printf("get item, addr:[%p], data:[%d]\n", p, p->data);
	} else {
		printf("not get item\n");
	}

	return p;
}

static void linklist_delete_node(struct linklist_node *head, int data)
{
	struct linklist_node *p;
	struct linklist_node *q;

	p = head;
	while (p) {
		q = p->next;
		if (q && q->data == data)
			break;
		p = q;
	}

	if (q) {
		p->next = q->next;
		free(q);
	}
	return;
}

__maybe_unused static void singly_linklist_operation(void)
{
	
	struct linklist_node *head, *p;

	printf("linklist pre:\n");
	head = create_linklist_node(0);
	linklist_insert_pre(head, 10);
	linklist_insert_pre(head, 70);
	linklist_insert_pre(head, 66);
	linklist_insert_pre(head, 56);
	linklist_insert_pre(head, 80);
	linklist_insert_pre(head, 36);
	linklist_print(head);
	printf("reverse\n");
	linklist_reverse(head);
	linklist_print(head);
	printf("get node\n");
	p = linklist_get_node(head, 56);
	printf("%p\n", p);
	linklist_free(head);

	printf("linklist post:\n");
	head = create_linklist_node(0);
	linklist_insert_post(head, 10);
	linklist_insert_post(head, 70);
	linklist_insert_post(head, 66);
	linklist_insert_post(head, 56);
	linklist_insert_post(head, 80);
	linklist_insert_post(head, 36);
	linklist_print(head);
	printf("reverse\n");
	linklist_reverse(head);
	linklist_print(head);
	printf("get node\n");
	p = linklist_get_node(head, 56);
	printf("%p\n", p);
	printf("delete node\n");
	linklist_delete_node(head, 10);
	linklist_print(head);
	linklist_free(head);

	return;
}

static struct link_node *create_link_node(int data)
{
	struct link_node *node;

	node = malloc(sizeof(struct link_node));
	if (!node) {
		goto err;
	}

	node->data = data;
	node->pre = NULL;
	node->next = NULL;
err:
	return node;
}

static void link_insert_pre(struct link_node *head, int data)
{
	struct link_node *node;

	node = create_link_node(data);
	if (!node) {
		goto err;
	}

	node->next = head->next;
	node->pre = head;
	if (head->next)
		head->next->pre = node;
	head->next = node;

err:
	return;
}

static void link_insert_post(struct link_node *head, int data)
{
	struct link_node *node, *p;

	node = create_link_node(data);
	if (!node) {
		goto err;
	}

	p = head;
	while (p->next) {
		p = p->next;
	}

	node->next = p->next;
	p->next = node;
	node->pre = p;

err:
	return;		
}

static void link_print(struct link_node *head)
{
	struct link_node *p;

	p = head->next;
	while (p) {
		printf("%d ", p->data);
		p = p->next;
	}

	printf("\n");

	p = head;
	while (p->next) {
		p = p->next;
	}
	while (p->pre) {
		printf("%d ", p->data);
		p = p->pre;
	}
	printf("\n");
	return;
}

static void link_free(struct link_node *head)
{
	struct link_node *p;
	struct link_node *q;

	p = head;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}

	return;
}

static void link_delete_node(struct link_node *head, int data)
{
	struct link_node *p;
	struct link_node *q;

	p = head;
	while (p) {
		q = p->next;
		if (q && q->data == data)
			break;
		p = q;
	}

	if (q) {
		p->next = q->next;
		if (q->next)
			q->next->pre = p;
		free(q);
	}

	return;
}

__maybe_unused static void doubly_linklist_operation(void)
{
	struct link_node *head;

	printf("create pre doubly linklist\n");
	head = create_link_node(0);
	link_insert_pre(head, 10);
	link_insert_pre(head, 70);
	link_insert_pre(head, 66);
	link_insert_pre(head, 56);
	link_insert_pre(head, 80);
	link_insert_pre(head, 36);

	printf("print pre doubly linklist\n");
	link_print(head);

	printf("delete pre node\n");
	link_delete_node(head, 36);
	link_print(head);

	printf("free pre link\n");
	link_free(head);

	printf("create post doubly linklist\n");
	head = create_link_node(0);
	link_insert_post(head, 10);
	link_insert_post(head, 70);
	link_insert_post(head, 66);
	link_insert_post(head, 56);
	link_insert_post(head, 80);
	link_insert_post(head, 36);

	printf("print pre doubly linklist\n");
	link_print(head);

	printf("delete pre node\n");
	link_delete_node(head, 36);
	link_print(head);

	printf("free post link\n");
	link_free(head);
}

static void circular_head_init(struct link_node **head, int data)
{
	*head = malloc(sizeof(struct link_node));
	if (!*head) {
		goto err;
	}

	memset(*head, 0, sizeof(struct link_node));
	(*head)->data = data;
	(*head)->next = (*head)->pre = *head;
err:
	return;
}

static void circular_insert_node(struct link_node *head, int data)
{
	struct link_node *node;

	circular_head_init(&node, data);
	if (!node)
		goto err;

	node->next = head->next;
	node->pre = head;
	head->next->pre = node;
	head->next = node;

err:
	return;
}

static void circular_print(struct link_node *head)
{
	struct link_node *p = NULL;

	p = head->next;
	while (p && p != head) {
		printf("%d ", p->data);
		p = p->next;
	}

	printf("\n");

	p = head->pre;
	while (p && p != head) {
		printf("%d ", p->data);
		p = p->pre;
	}

	printf("\n");
	return;
}

static void circular_get_node(struct link_node *head, int data)
{
	struct link_node *p;

	p = head->next;
	while (p && p != head) {
		if (p->data == data)
			break;
		p = p->next;
	}
	if (p != head) {
		printf("search node ok\n");
	} else {
		printf("no search node\n");
	}
	return;
}

static void circular_free(struct link_node *head)
{
	struct link_node *p;
	struct link_node *q;

	p = head;
	head->pre->next = NULL;
	while (p) {
		q = p->next;
#if 0
		printf("free node:[%d]\n", p->data);
#endif
		free(p);
		p = q;
	}

	return;
}

static void circular_delete_node(struct link_node *head, int data)
{
	struct link_node *p;

	p = head->next;
	while (p && p != head) {
		if (p->data == data)
			break;
		p = p->next;
	}

	if (p != head) {
		p->pre->next = p->next;
		p->next->pre = p->pre;
		free(p);
	}

	return;
}

static void circular_insert_node_tail(struct link_node *head, int data)
{
	struct link_node *node;

	circular_head_init(&node, data);
	if (!node) {
		goto err;
	}

	head->pre->next = node;
	node->next = head;
	node->pre = head->pre;
	head->pre = node;
err:
	return;
}

static void circular_doubly_linklist_operation(void)
{
	struct link_node *head;

	printf("create pre circular link\n");
	circular_head_init(&head, 0);
	printf("[%p %p %p]\n", head, head->next, head->pre);

	circular_insert_node(head, 10);
	circular_insert_node(head, 70);
	circular_insert_node(head, 66);
	circular_insert_node(head, 56);
	circular_insert_node(head, 80);
	circular_insert_node(head, 36);

	printf("print circular link\n");
	circular_print(head);

	printf("search circular link node\n");
	circular_get_node(head, 56);

	printf("delete circular link node\n");
	circular_delete_node(head, 10);
	printf("print circular link\n");
	circular_print(head);

	printf("free circular link\n");
	circular_free(head);

	printf("create post circular link\n");
	circular_head_init(&head, 0);
	printf("[%p %p %p]\n", head, head->next, head->pre);

	circular_insert_node_tail(head, 10);
	circular_insert_node_tail(head, 70);
	circular_insert_node_tail(head, 66);
	circular_insert_node_tail(head, 56);
	circular_insert_node_tail(head, 80);
	circular_insert_node_tail(head, 36);

	printf("print circular link\n");
	circular_print(head);

	printf("free circular link\n");
	circular_free(head);
}

int main(int argc, char *argv[])
{
#if 0
	singly_linklist_operation();
	doubly_linklist_operation();
#endif
	circular_doubly_linklist_operation();
	return 0;
}
