#include <stdio.h>
#include <stdlib.h>

static void search_print(int index, int size)
{
	if (index < size) {
		printf("search ok, index:[%d]\n", index);
	} else {
		printf("not seatch item\n");
	}

	return;
}

static int linear_search(int *array, int size, int key)
{
	int i;

	for (i = 0; i < size; i ++) {
		if (array[i] == key)
			break;
	}

	search_print(i, size);

	return i;
}

static void swap_num(int *array, int i, int j)
{
	int tmp;

	tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;

	return;
}

static void print_array(int *array, int size)
{
	int i = 0;

	for (i = 0; i < size; i ++) {
		printf("%d ", array[i]);
	}

	printf("\n");

	return;
}

static void select_sort_array(int *array, int size)
{
	int i = 0, j = 0;
	int tmp = 0;

	for (i = 0; i < size - 1; i ++) {
		tmp = i;
		for (j = i + 1; j < size; j ++) {
			if (array[j] < array[tmp])
				tmp = j;
		}
		if (tmp != i) {
			swap_num(array, i, tmp);
		}
	}

	print_array(array, size);
	return;
}

static int binary_search(int *array, int size, int key)
{
	int l = 0;
	int r = size - 1;
	int mid;

	while (l <= r) {
		mid = (l + r) / 2;
		if (array[mid] > key)
			r = mid - 1;
		else if (array[mid] < key)
			l = mid + 1;
		else return mid;
	}

	return size;
}

int main(int argc, char *argv[])
{
	int array[8] = {30, 41, 25, 90, 36, 50, 16, 85};
	int size = sizeof(array) / sizeof(int);
	int key;
	int index = 0;

	if (argc != 2) {
		printf("please use: ./search [key]\n");
		goto err;
	}

	key = atoi(argv[1]);

	linear_search(array, size, key);

	select_sort_array(array, size);
	index = binary_search(array, size, key);
	search_print(index, size);

err:
	return 0;
}
