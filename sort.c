#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum sort_type_enum {
	SORT_TYPE_BUBBLE = 0,
	SORT_TYPE_SELECT,
	SORT_TYPE_INSERT,
	SORT_TYPE_QUICK,
	SORT_TYPE_MERGE,
	SORT_TYPE_HEAP,

	SORT_TYPE_MAX,
};

struct sort_type_info {
	int id;
	char *name;
};

struct sort_type_info type_list[SORT_TYPE_MAX] = {
	[SORT_TYPE_BUBBLE] = {
		.id = SORT_TYPE_BUBBLE,
		.name = "bubble",
	},

	[SORT_TYPE_SELECT] = {
		.id = SORT_TYPE_SELECT,
		.name = "select",
	},

	[SORT_TYPE_INSERT] = {
		.id = SORT_TYPE_INSERT,
		.name = "insert",
	},

	[SORT_TYPE_QUICK] = {
		.id = SORT_TYPE_QUICK,
		.name = "quick",
	},

	[SORT_TYPE_MERGE] = {
		.id = SORT_TYPE_MERGE,
		.name = "merge",
	},

	[SORT_TYPE_HEAP] = {
		.id = SORT_TYPE_HEAP,
		.name = "heap",
	},
};

static enum sort_type_enum get_sort_type(char *name)
{
	int i = 0;
	int size = sizeof(type_list) / sizeof(type_list[0]);

	for (i = 0; i < size; i ++) {
		if (strcmp(name, type_list[i].name) == 0)
			return type_list[i].id;
	}

	return SORT_TYPE_MAX;
}

static void array_print(int *array, int len)
{
	int i = 0;

	for (i = 0; i < len; i ++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	return;
}

static void swap_num(int *array, int i, int j)
{
	int tmp;

	tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;

	return;
}

static void bubble_sort(int *array, int len)
{
	int i = 0, j = 0;

	for (i = 0; i < len - 1; i ++) {
		for (j = 1; j < len; j ++) {
			if (array[j - 1] > array[j]) {
				swap_num(array, j, j - 1);
			}
		}
	}

	return;
}

static void select_sort(int *array, int len)
{
	int i = 0, j = 0;
	int index = 0;

	for (i = 0; i < len - 1; i ++) {
		index = i;
		for (j = i + 1; j < len; j ++) {
			if (array[j] < array[index])
				index = j;
		}

		if (index != i) {
			swap_num(array, index, i);
		}
	}
	return;
}

static void insert_sort(int *array, int len)
{
	int i = 0, j = 0;
	int tmp = 0;

	for (i = 1; i < len; i ++) {
		tmp = array[i];
		for (j = i - 1; j >= 0 && tmp < array[j]; j --) {
			array[j + 1] = array[j];
		}
		array[j + 1] = tmp;
	}
	return;
}

static int partition(int *array, int low, int high)
{
	int i = low - 1;
	int j = 0;

	for (j = low; j < high; j ++) {
		if (array[j] < array[high]) {
			i ++;
			swap_num(array, j, i);
		}
	}

	swap_num(array, i + 1, high);

	return i + 1;
}

static void quick_sort_list(int *array, int low, int high)
{
	int part = 0;

	if (low >= high)
		return;

	part = partition(array, low, high);
	quick_sort_list(array, low, part - 1);
	quick_sort_list(array, part + 1, high);

	return;
}

static void quick_sort(int *array, int len)
{
	quick_sort_list(array, 0, len - 1);
	return;
}

static void merge(int *array, int l, int m, int r)
{
	int i = 0, j = 0, k = 0;
	int l_len = m - l + 1;
	int r_len = r - m;
	int l_list[l_len];
	int r_list[r_len];

	for (i = 0; i < l_len; i ++) {
		l_list[i] = array[l + i];
	}

	for (j = 0; j < r_len; j++) {
		r_list[j] = array[m + 1 + j];
	}

	i = j = 0;
	k = l;
	while (i < l_len && j < r_len) {
		if (l_list[i] < r_list[j]) {
			array[k] = l_list[i];
			i ++;
		} else {
			array[k] = r_list[j];
			j ++;
		}

		k ++;
	}

	while (i < l_len) {
		array[k] = l_list[i];
		i ++;
		k ++;
	}

	while (j < r_len) {
		array[k] = r_list[j];
		j ++;
		k ++;
	}

	return;
}

static void merge_sort_list(int *array, int l, int r)
{
	int m = 0;

	if (l >= r) {
		return;
	}

	m = l + (r - l) / 2;
	merge_sort_list(array, l, m);
	merge_sort_list(array, m + 1, r);

	merge(array, l, m, r);
}

static void merge_sort(int *array, int len)
{
	merge_sort_list(array, 0, len - 1);
	return;
}

static void heap_adjust(int *array, int len, int index)
{
	int largest = index;
	int l = 2 * index + 1;
	int r = 2 * index + 2;

	if (l < len && array[largest] < array[l])
		largest = l;

	if (r < len && array[largest] < array[r])
		largest = r;

	if (largest != index) {
		swap_num(array, index, largest);
		heap_adjust(array, len, largest);
	}
}

static void heap_sort(int *array, int len)
{
	int i = 0;

	for (i = len / 2 - 1; i >= 0; i --) {
		heap_adjust(array, len, i);
	}

	for (i = len - 1; i >= 0; i --) {
		swap_num(array, i, 0);
		heap_adjust(array, i, 0);
	}
	return;
}

int main(int argc, char *argv[])
{
	int ret = 0;
	enum sort_type_enum type;
	int array[8] = {81, 105, 91, 71, 93, 88, 68, 79};
	int size = sizeof(array) / sizeof(int);

	if (argc != 2) {
		printf("please use: ./sort [sort_type]\n");
		goto err;
	}

	type = get_sort_type(argv[1]);
	switch (type) {
	case SORT_TYPE_BUBBLE:
		bubble_sort(array, size);
		break;
	case SORT_TYPE_SELECT:
		select_sort(array, size);
		break;
	case SORT_TYPE_INSERT:
		insert_sort(array, size);
		break;
	case SORT_TYPE_QUICK:
		quick_sort(array, size);
		break;
	case SORT_TYPE_MERGE:
		merge_sort(array, size);
		break;
	case SORT_TYPE_HEAP:
		heap_sort(array, size);
		break;
	default:
		break;
	}

	array_print(array, size);

err:
	return ret;
}
