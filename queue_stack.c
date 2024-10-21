#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX_SIZE 5
#define STACK_MAX_SIZE 5

struct queue_list {
	int *list;
	int w, r;
};

struct stack_list {
	int *list;
	int top;
};

static struct queue_list *queue_init(void)
{
	struct queue_list *queue;

	queue = malloc(sizeof(struct queue_list));
	if (!queue) {
		printf("memory not enough\n");
		goto err;
	}

	queue->list = malloc(sizeof(int) * QUEUE_MAX_SIZE);
	queue->w = queue->r = 0;

	return queue;
err:
	return NULL;
}

static void queue_en(struct queue_list *queue, int data)
{
	if (((queue->w + 1) % QUEUE_MAX_SIZE) == queue->r) {
		printf("queue full\n");
		return;
	}

	queue->list[queue->w] = data;
	queue->w = (queue->w + 1) % QUEUE_MAX_SIZE;
}

static void queue_de(struct queue_list *queue, int *data)
{
	if (queue->w == queue->r) {
		printf("queue empty\n");
		return;
	}

	*data = queue->list[queue->r];
	queue->r = (queue->r + 1) % QUEUE_MAX_SIZE;
}

static void queue_destroy(struct queue_list *queue)
{
	if (queue) {
		if (queue->list)
			free(queue->list);
		free(queue);
	}
}

static void queue_print(struct queue_list *queue)
{
	struct queue_list *q;
	int index;

	if (!queue)
		return;

	q = queue;
	index = q->r;
	while (index != q->w) {
		printf("%d ", q->list[index]);
		index = (index + 1) % QUEUE_MAX_SIZE;
	}

	printf("\n");

	return;
}

static struct stack_list *stack_init(void)
{
	struct stack_list *stack;

	stack = malloc(sizeof(struct stack_list));
	if (!stack) {
		goto err;
	}

	stack->list = malloc(sizeof(int) * STACK_MAX_SIZE);
	if (!stack->list) {
		goto err;
	}

	stack->top = 0;

	return stack;
err:
	return NULL;
}

static void stack_en(struct stack_list *stack, int data)
{
	if (stack->top >= STACK_MAX_SIZE) {
		printf("stack full\n");
		goto err;
	}

	stack->list[stack->top] = data;
	stack->top ++;

err:
	return;
}

static void stack_de(struct stack_list *stack, int *data)
{
	if (stack->top - 1 < 0) {
		printf("stack empty\n");
		goto err;
	}

	stack->top --;
	*data = stack->list[stack->top];

err:
	return;
}

static void stack_print(struct stack_list *stack)
{
	int index;

	for(index = stack->top - 1; index >= 0; index --) {
		printf("%d ", stack->list[index]);
	}

	printf("\n");
}

static void stack_destroy(struct stack_list *stack)
{
	if (stack) {
		if (stack->list)
			free(stack->list);
		free(stack);
	}
}

static void stack_func(void)
{
	struct stack_list *stack;
	int data;

	stack = stack_init();
	stack_en(stack, 66);
	stack_en(stack, 67);
	stack_en(stack, 56);
	stack_en(stack, 68);

	stack_print(stack);

	stack_de(stack, &data);
	stack_de(stack, &data);

	stack_print(stack);

	stack_destroy(stack);

	return;
}

static void queue_func(void)
{
	struct queue_list *queue;
	int data;

	queue = queue_init();

	queue_en(queue, 66);
	queue_en(queue, 57);
	queue_en(queue, 68);

	queue_en(queue, 89);

	queue_print(queue);

	queue_de(queue, &data);
	printf("%d\n", data);
	queue_de(queue, &data);
	printf("%d\n", data);
	queue_en(queue, 90);
	queue_en(queue, 88);

	queue_print(queue);

	queue_destroy(queue);

	return;
}

static void s2q_en(struct stack_list *s1, int data)
{
	stack_en(s1, data);
	return;
}

static void s2q_de(struct stack_list *s1, struct stack_list *s2, int *data)
{
	if (s2->top - 1 < 0) {
		while (s1->top - 1 >= 0) {
			int tmp;
			stack_de(s1, &tmp);
			stack_en(s2, tmp);
		}
	}

	stack_de(s2, data);
}

static void stack2queue(void)
{
	struct stack_list *s1;
	struct stack_list *s2;
	int data;

	s1 = stack_init();
	s2 = stack_init();

	s2q_en(s1, 56);
	s2q_en(s1, 66);
	s2q_en(s1, 76);
	s2q_en(s1, 36);

	s2q_de(s1, s2, &data);
	printf("%d\n", data);
	s2q_de(s1, s2, &data);
	printf("%d\n", data);

	return;
}

static void q2s_en(struct queue_list *q1, struct queue_list *q2, int data)
{
	if ((q1->w == q1->r) && (q2->w == q2->r)) {
		queue_en(q1, data);
	} else if (q1->w != q1->r) {
		queue_en(q1, data);
	} else {
		queue_en(q2, data);
	}
	return;
}

static void q2s_de(struct queue_list *q1, struct queue_list *q2, int *data)
{
	int tmp_data;

	while (q1->r != q1->w) {
		if (((q1->r + 1) % QUEUE_MAX_SIZE) == q1->w) {
			*data = q1->list[q1->r];
			q1->r = (q1->r + 1) % QUEUE_MAX_SIZE;
			goto ret;
		} else {
			tmp_data = q1->list[q1->r];
			q1->r = (q1->r + 1) % QUEUE_MAX_SIZE;
			queue_en(q2, tmp_data);
		}
	}

	while (q2->r != q2->w) {
		if (((q2->r + 1) % QUEUE_MAX_SIZE) == q2->w) {
			*data = q2->list[q2->r];
			q2->r = (q2->r + 1) % QUEUE_MAX_SIZE;
			goto ret;
		} else {
			tmp_data = q2->list[q2->r];
			q2->r = (q2->r + 1) % QUEUE_MAX_SIZE;
			queue_en(q1, tmp_data);
		}
	}
ret:
	return;
}

static void queue2stack(void)
{
	struct queue_list *q1;
	struct queue_list *q2;
	int data;

	q1 = queue_init();
	q2 = queue_init();

	q2s_en(q1, q2, 68);
	q2s_en(q1, q2, 80);
	q2s_en(q1, q2, 58);
	q2s_en(q1, q2, 90);

	q2s_de(q1, q2, &data);
	printf("%d\n", data);
	q2s_de(q1, q2, &data);
	printf("%d\n", data);

	return ;
}

int main(int argc, char *argv[])
{
	printf("queue\n");
	queue_func();

	printf("stack\n");
	stack_func();

	printf("stack to queue\n");
	stack2queue();

	printf("queue to stack\n");
	queue2stack();
	return 0;
}
