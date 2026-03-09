#include <stdio.h>
#include <stdlib.h>

static int capacity = 5;
static int size = 0;
static int *items = NULL;

// Function prototypes
void initialize();
int peek();
int poll();
int add(int item);

static int get_left_child_index(int index);
static int get_right_child_index(int index);
static int get_parent_index(int index);

static int has_left_child(int index);
static int has_right_child(int index);
static int has_parent(int index);

static int left_child(int index);
static int right_child(int index);
static int parent(int index);

static void swap(int a, int b);
static void ensure_capacity();
static void heapify_up();
static void heapify_down();
static void print_heap();

void initialize() {
  items = (int *)malloc(capacity * sizeof(int));
}

static int get_left_child_index(int index) {
  return 2 * index + 1;
}

static int get_right_child_index(int index) {
  return 2 * index + 2;
}

static int get_parent_index(int index) {
  return (index - 1) / 2;
}

static int has_left_child(int index) {
  return get_left_child_index(index) < size;
}

static int has_right_child(int index) {
  return get_right_child_index(index) < size;
}

static int has_parent(int index) {
  return get_parent_index(index) >= 0;
}

static int left_child(int index) {
  return items[get_left_child_index(index)];
}

static int right_child(int index) {
  return items[get_right_child_index(index)];
}

static int parent(int index) {
  return items[get_parent_index(index)];
}

static void swap(int a, int b) {
  int temp = items[a];
  items[a] = items[b];
  items[b] = temp;
}

static void ensure_capacity() {
  if (size == capacity) {
    capacity *= 2;
    items = (int *)realloc(items, capacity * sizeof(int));
  }
}

int peek() {
  if (size == 0) {
    return -1; // Heap is empty
  }
  return items[0];
}

int poll() {
  if (size == 0) {
    return -1; // Heap is empty
  }
  int item = items[0];
  items[0] = items[size - 1];
  size--;
  heapify_down();
  return item;
}

int add(int item) {
  ensure_capacity();
  items[size] = item;
  size++;
  print_heap();
  heapify_up();
  print_heap();
  return item;
}

static void heapify_up() {
  int index = size - 1;
  while (has_parent(index) && parent(index) > items[index]) {
    swap(get_parent_index(index), index);
    index = get_parent_index(index);
  }
}

static void heapify_down() {
  int index = 0;
  while (has_left_child(index)) {
    int smaller_child_index = get_left_child_index(index);
    if (has_right_child(index) && right_child(index) < left_child(index)) {
      smaller_child_index = get_right_child_index(index);
    }
    if (items[index] < items[smaller_child_index]) {
      break;
    } else {
      swap(index, smaller_child_index);
    }
    index = smaller_child_index;
  }
}

static void print_heap() {
  printf("Heap: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", items[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  initialize();

  // Gen how many random number from argument or ask user
  int n;
  if (argc > 1) {
    n = atoi(argv[1]);
  } else {
    printf("Enter how many random numbers to generate: ");
    scanf("%d", &n);
  }

  // Gen random numbers and add to heap
  for (int i = 0; i < n; i++) {
    int num = rand() % 1000;
    printf("Adding %d to heap\n", num);
    add(num);
  }

  // Poll all items from heap
  printf("Polling items from heap:\n");
  while (size > 0) {
    int item = poll();
    printf("%d ", item);
  }
  printf("\n");

  // Free allocated memory
  free(items);
  return 0;
}
