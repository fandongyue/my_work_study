#include <stdio.h>
#include <stdlib.h>

#if 0
static int *create_node()
{
	int *n;
	n = malloc(sizeof(int));
	return n;
}

static void test_return(void)
{
	int *p = NULL;

	printf("%p\n", p);
	p = create_node();
	printf("%p\n", p);
}
#else
static void create_node(int *p)
{
	p = malloc(sizeof(int));
}

static void test_return(void)
{
	int *p = NULL;

	printf("%p\n", p);
	create_node(p);
	printf("%p\n", p);
}
#endif

int main(int argc, char *argv[])
{
	test_return();
	return 0;
}
