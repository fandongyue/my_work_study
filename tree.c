#include <stdio.h>
#include <stdlib.h>

enum tree_option_enum {
	TREE_OPTION_PRINT = 0,
	TREE_OPTION_FREE,
};

struct tree_node {
	int data;
	int height;
	struct tree_node *l, *r;
};

static struct tree_node *tree_create_node(int data)
{
	struct tree_node *node;

	node = malloc(sizeof(struct tree_node));
	if (node) {
		node->data = data;
		node->height = 1;
		node->l = NULL;
		node->r = NULL;
	}

	return node;
}

/*BST(Binary Search Tree)*/
static struct tree_node *tree_insert_node(struct tree_node *root_node, int data)
{
	if (!root_node) {
		root_node = tree_create_node(data);
	} else if (data < root_node->data) {
		root_node->l = tree_insert_node(root_node->l, data);
	} else if (data > root_node->data) {
		root_node->r = tree_insert_node(root_node->r, data);
	} else {
		/*item has exist, update data.*/
		root_node->data = data;
	}

	return root_node;
}

static void tree_pre_print(struct tree_node *root)
{
	if (root) {
		printf("[%d %d]", root->data, root->height);
		tree_pre_print(root->l);
		tree_pre_print(root->r);
	}
}

static void tree_in_print(struct tree_node *root)
{
	if (root) {
		tree_in_print(root->l);
		printf("[%d %d]", root->data, root->height);
		tree_in_print(root->r);
	}
}

static void tree_post_print(struct tree_node *root)
{
	if (root) {
		tree_post_print(root->l);
		tree_post_print(root->r);
		printf("[%d %d]", root->data, root->height);
	}
}

static void tree_pre_print_non_recursive(struct tree_node *root)
{
	struct tree_node **tree_stack = NULL;
	int top = -1;

	tree_stack = malloc(sizeof(struct tree_node *) * 20);
	if (!tree_stack) {
		printf("no memory\n");
		goto err;
	}

	tree_stack[++ top] = root;
	while (top >= 0) {
		struct tree_node *node;

		node = tree_stack[top --];
		printf("%d ", node->data);

		if (node->r) {
			tree_stack[++ top] = node->r;
		}

		if (node->l) {
			tree_stack[++ top] = node->l;
		}
	}

	printf("\n");

err:
	if (tree_stack)
		free(tree_stack);
	return;
}

static void tree_in_print_non_recursive(struct tree_node *root)
{
	struct tree_node **tree_stack = NULL;
	int top = -1;
	struct tree_node *cur = NULL;

	tree_stack = malloc(sizeof(struct tree_node *) * 20);
	if (!tree_stack) {
		printf("no memory\n");
		goto err;
	}

	cur = root;
	while (top != -1 || cur) {
		while (cur) {
			tree_stack[++ top] = cur;
			cur = cur->l;
		}

		cur = tree_stack[top --];
		printf("%d ", cur->data);

		cur = cur->r;
	}

	printf("\n");

err:
	if (tree_stack)
		free(tree_stack);
	return;
}

static void tree_post_traversal_no_recursive(struct tree_node *root, int option)
{
	struct tree_node **tree_stack_in = NULL;
	struct tree_node **tree_stack_out = NULL;
	int top_in = -1;
	int top_out = -1;

	tree_stack_in = malloc(sizeof(struct tree_node *) * 20);
	if (!tree_stack_in) {
		printf("no memory\n");
		goto err;
	}

	tree_stack_out = malloc(sizeof(struct tree_node *) * 20);
	if (!tree_stack_out) {
		printf("no memory\n");
		goto err;
	}

	tree_stack_in[++ top_in] = root;
	while (top_in >= 0) {
		struct tree_node *node;
		node = tree_stack_in[top_in --];
		tree_stack_out[++ top_out] = node;

		if (node->l) {
			tree_stack_in[++ top_in] = node->l;
		}

		if (node->r) {
			tree_stack_in[++ top_in] = node->r;
		}
	}

	while (top_out >= 0) {
		struct tree_node *node;
		node = tree_stack_out[top_out --];
		switch (option) {
		case TREE_OPTION_FREE:
			free(node);
			break;
		case TREE_OPTION_PRINT:
		default:
			printf("%d ", node->data);
			break;
		}
	}

	printf("\n");
err:
	if (tree_stack_in)
		free(tree_stack_in);
	if (tree_stack_out)
		free(tree_stack_out);
	return;
}

static void tree_post_print_non_recursive(struct tree_node *root)
{
	tree_post_traversal_no_recursive(root, TREE_OPTION_PRINT);
	return;
}

#ifdef RECURSIVE
static void tree_free_recursive(struct tree_node *root)
{
	if (root) {
		tree_free_recursive(root->l);
		tree_free_recursive(root->r);
		free(root);
	}

	return;
}
#endif

static void tree_free_no_recursive(struct tree_node *root)
{
	tree_post_traversal_no_recursive(root, TREE_OPTION_FREE);
	return;
}

static struct tree_node *tree_create_BST_tree(void)
{
	struct tree_node *root = NULL;

	root = tree_insert_node(root, 10);
	tree_insert_node(root, 80);
	tree_insert_node(root, 65);
	tree_insert_node(root, 75);
	tree_insert_node(root, 15);
	tree_insert_node(root, 60);

	return root;
}

static struct tree_node *tree_search_node(struct tree_node *root, int data)
{
	struct tree_node *node = NULL;

	node = root;
	while (node) {
		if (node->data > data)
			node = node->l;
		else if (node->data < data)
			node = node->r;
		else
			break;
	}

	if (node) {
		printf("search ok, node:[%p], value:[%d]\n", node, data);
	} else {
		printf("not search node, value:[%d]\n", data);
	}

	return node;
}

static struct tree_node *tree_get_leftmost_node(struct tree_node *root)
{
	struct tree_node *node;

	node = root;
	while (node && node->l) {
		node = node->l;
	}

	return node;
}

static struct tree_node *tree_delete_node(struct tree_node *root, int data)
{
	if (!root) {
		return NULL;
	}

	if (data < root->data) {
		root->l = tree_delete_node(root->l, data);
	} else if (data > root->data) {
		root->r = tree_delete_node(root->r, data);
	} else {
		struct tree_node *node;
		if (!root->l) {
			node = root->r;
			free(root);
			root = NULL;
			return node;
		}

		if (!root->r) {
			node = root->l;
			free(root);
			root = NULL;
			return node;
		}

		/*get min node of right subtree.*/
		node = tree_get_leftmost_node(root->r);
		root->data = node->data;
		root->r = tree_delete_node(root->r, node->data);
	}

	return root;
}

static void tree_post_print_no_rec(struct tree_node *root)
{
	struct tree_node **queue, **stack, *q;
	int w = 0, r = 0;
	int top = 0;

	queue = malloc(sizeof(struct tree_node *) * 20);
	if (!queue) {
		goto err;
	}

	stack = malloc(sizeof(struct tree_node *) * 20);
	if (!stack) {
		goto err;
	}

	queue[w] = root;
	w = (w + 1) % 20;

	while (w != r) {
		q = queue[r];
		r = (r + 1) % 20;

		stack[top ++] = q;

		if (q->l) {
			queue[w] = q->l;
			w = (w + 1) % 20;
		}

		if (q->r) {
			queue[w] = q->r;
			w = (w + 1) % 20;
		}
	}

	while (top > 0) {
		printf("%d ", stack[-- top]->data);
	}

	printf("\n");
err:
	if (queue) {
		free(queue);
	}
	if (stack) {
		free(stack);
	}
	return;
}

static void tree_level_print(struct tree_node *root)
{
	struct tree_node **queue, *q;
	int w = 0, r = 0;

	queue = malloc(sizeof(struct tree_node *) * 20);
	if (!queue) {
		printf("malloc error\n");
		goto err;
	}

	queue[w] = root;
	w = (w + 1) % 20;
	while (w != r) {
		q = queue[r];
		printf("%d ", queue[r]->data);
		r = (r + 1) % 20;

		if (q->l) {
			queue[w] = q->l;
			w = (w + 1) % 20;
		}

		if (q->r) {
			queue[w] = q->r;
			w = (w + 1) % 20;
		}
	}

	printf("\n");
err:
	if (queue) {
		free(queue);
	}
	return;
}

static void tree_mirror_switch(struct tree_node *root)
{
	struct tree_node **stack, *p;
	int top = 0;

	stack = malloc(sizeof(struct tree_node *) * 20);
	if (!stack) {
		goto err;
	}

	stack[top ++] = root;
	while (top > 0) {
		struct tree_node *node;

		node = stack[-- top];
		p = node->l;
		node->l = node->r;
		node->r = p;

		if (node->l) {
			stack[top ++] = node->l;
		}

		if (node->r) {
			stack[top ++] = node->r;
		}
	}

	printf("mirror tree, print\n");
	tree_pre_print_non_recursive(root);
	tree_in_print_non_recursive(root);
err:
	if (stack) {
		free(stack);
	}
	return;
}

static void tree_BST_operation(void)
{
	struct tree_node *root;

	printf("create BST tree\n");
	root = tree_create_BST_tree();

	printf("recursive\n");
	tree_pre_print(root);
	printf("\n");
	tree_in_print(root);
	printf("\n");
	tree_post_print(root);
	printf("\n");

	printf("no recursive\n");
	tree_pre_print_non_recursive(root);
	tree_in_print_non_recursive(root);
	tree_post_print_non_recursive(root);
	printf("use queue, post:\n");
	tree_post_print_no_rec(root);

	printf("level\n");
	tree_level_print(root);

	printf("mirror\n");
	tree_mirror_switch(root);

	printf("search node\n");
	tree_search_node(root, 65);
	tree_search_node(root, 66);

	printf("delete node\n");
	root = tree_delete_node(root, 65);
	tree_pre_print_non_recursive(root);

	printf("free BST tree all, node\n");
#ifdef RECURSIVE
	tree_free_recursive(root);
#else
	tree_free_no_recursive(root);
#endif
}

static int get_node_height(struct tree_node *node)
{
	if (!node)
		return 0;

	return node->height;
}

static int get_max(int n, int m)
{
	if (n > m)
		return n;
	else
		return m;
}

static void tree_update_node_height(struct tree_node *node)
{
	node->height = 1 + get_max(get_node_height(node->l), get_node_height(node->r));
}

static int tree_get_balance(struct tree_node *node)
{
	if (!node)
		return 0;

	return get_node_height(node->l) - get_node_height(node->r);
}

static struct tree_node *tree_right_rotate(struct tree_node *node)
{
	struct tree_node *l = node->l;
	struct tree_node *t = l->r;

	l->r = node;
	node->l = t;

	tree_update_node_height(node);
	tree_update_node_height(l);

	return l;
}

static struct tree_node *tree_left_rotate(struct tree_node *node)
{
	struct tree_node *r = node->r;
	struct tree_node *t = r->l;

	r->l = node;
	node->r = t;

	tree_update_node_height(node);
	tree_update_node_height(r);

	return r;
}

static struct tree_node *tree_insert_AVL_node(struct tree_node *node, int data)
{
	int balance = 0;

	if (!node) {
		node = tree_create_node(data);
		return node;
	} else if (data < node->data) {
		node->l = tree_insert_AVL_node(node->l, data);
	} else if (data > node->data) {
		node->r = tree_insert_AVL_node(node->r, data);
	} else {
		/*only update data*/
		node->data = data;
		return node;
	}

	/*update node height*/
	tree_update_node_height(node);

	/*get balance.*/
	balance = tree_get_balance(node);

	if (balance > 1 && data < node->l->data)
		return tree_right_rotate(node);

	if (balance < -1 && data > node->r->data)
		return tree_left_rotate(node);

	if (balance > 1 && data > node->l->data) {
		node->l = tree_left_rotate(node->l);
		return tree_right_rotate(node);
	}

	if (balance < -1 && data < node->r->data) {
		node->r = tree_right_rotate(node->r);
		return tree_left_rotate(node);
	}

	return node;
}

static struct tree_node *tree_create_AVL_tree(void)
{
	struct tree_node *root = NULL;

	root = tree_insert_AVL_node(root, 10);
	root = tree_insert_AVL_node(root, 80);
	root = tree_insert_AVL_node(root, 65);
	root = tree_insert_AVL_node(root, 75);
	root = tree_insert_AVL_node(root, 15);
	root = tree_insert_AVL_node(root, 60);

	return root;
}

static struct tree_node *tree_delete_AVL_node(struct tree_node *root, int data)
{
	int balance = 0;

	if (!root) {
		return NULL;
	}

	if (data < root->data) {
		root->l = tree_delete_AVL_node(root->l, data);
	} else if (data > root->data) {
		root->r = tree_delete_AVL_node(root->r, data);
	} else {
		struct tree_node *node;
		if (!root->l) {
			node = root->r;
			free(root);
			root = NULL;
			return node;
		}

		if (!root->r) {
			node = root->l;
			free(root);
			root = NULL;
			return node;
		}

		/*get min node of right subtree.*/
		node = tree_get_leftmost_node(root->r);
		root->data = node->data;
		root->r = tree_delete_AVL_node(root->r, node->data);
	}

	if (!root)
		return NULL;

	/*update node height.*/
	tree_update_node_height(root);

	/*get balance.*/
	balance = tree_get_balance(root);

	if (balance > 1 && tree_get_balance(root->l) >= 0)
		return tree_right_rotate(root);

	if (balance < -1 && tree_get_balance(root->r) >= 0)
		return tree_left_rotate(root);

	if (balance > 1 && tree_get_balance(root->l) < 0) {
		root->l = tree_left_rotate(root->l);
		return tree_right_rotate(root);
	}

	if (balance < -1 && tree_get_balance(root->r) < 0) {
		root->r = tree_right_rotate(root->r);
		return tree_left_rotate(root);
	}

	return root;
}

static void tree_AVL_operation(void)
{
	struct tree_node *root;

	printf("create AVL tree\n");
	root = tree_create_AVL_tree();

	printf("recursive\n");
	printf("pre order:\n");
	tree_pre_print(root);
	printf("\n");
	printf("in order:\n");
	tree_in_print(root);
	printf("\n");
	printf("post order:\n");
	tree_post_print(root);
	printf("\n");

	printf("no recursive\n");
	printf("pre order:\n");
	tree_pre_print_non_recursive(root);
	printf("in order:\n");
	tree_in_print_non_recursive(root);
	printf("post order:\n");
	tree_post_print_non_recursive(root);

	printf("level\n");
	tree_level_print(root);

	printf("search node\n");
	tree_search_node(root, 65);
	tree_search_node(root, 66);

	printf("delete AVL node\n");
	tree_delete_AVL_node(root, 65);
	printf("printf pre AVL node\n");
	tree_pre_print_non_recursive(root);

	printf("free BST tree all, node\n");
#ifdef RECURSIVE
	tree_free_recursive(root);
#else
	tree_free_no_recursive(root);
#endif

}

int main(int argc, char *argv[])
{
	tree_BST_operation();
	tree_AVL_operation();
	return 0;
}
