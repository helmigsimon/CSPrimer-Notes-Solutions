#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_CAPACITY 8

/*
* NOTES
* - Array of 3 integers
*   - Each integer will be 4 bytes long (32 bits each)
*   - To access the index 2 it needs to compute
*     - arr_address + 2 * size(byte)
*       - In many architectures this is a single instruction
*     - Allows constant time indexing
*       - As long as you have fixed size
*
*
*/

typedef struct DA {
  // TODO define our struct
  int size;
  int capacity;
  void **values;
} DA;


DA* DA_new (void) {
  // TODO allocate and return a new dynamic array
  DA* da = (DA*)malloc(sizeof(DA));
  if (!da){
    perror("Failed to allocate memory");
    exit(1);
  }
  da -> size = 0;
  da -> capacity = STARTING_CAPACITY;
  da -> values = malloc(sizeof(void*) * STARTING_CAPACITY);
  if (!da->values){
    perror("Failed to allocate memory");
    exit(1);
  }
  return da;
}

int DA_size(DA *da) {
  // TODO return the number of items in the dynamic array
  return da->size;
}

void DA_push (DA* da, void* x) {
  // TODO push to the end
  void* new_val = x;
  if (da -> size >= da -> capacity){
    int new_capacity = da->capacity+1;
    void **temp = realloc(da -> values, sizeof(void*) * new_capacity);
    if (!temp){
      perror("Failed to allocate memory");
      free(da -> values);
      exit(1);
    }
    da -> values = temp;
    da -> capacity = new_capacity;
  }
  for (int i=0; i<da->capacity; i++){
    void* old_val = da -> values[i];
    da -> values[i] = new_val;
    new_val = old_val;
  }
  (da->size)++;
}

void *DA_pop(DA *da) {
  // TODO pop from the end
  int array_size = da -> capacity;
  void* return_val = (da -> values)[0];
  for (int i=0;i<array_size;i++){
    (da -> values)[i] = (da -> values[i+1]);
  }
  da -> size--;
  return return_val;
}

void DA_set(DA *da, void *x, int i) {
  // TODO set at a given index, if possible
  int array_size = da -> capacity;
  if (i+1 >= array_size) return;
  void* value = da -> values[i];
  da -> values[i] = x;
  if (value != NULL) {(da -> size)++;};
}

void *DA_get(DA *da, int i) {
  // TODO get from a given index, if possible
  int array_size = da -> capacity;
  if (i+1 >= array_size) return NULL;
  return da -> values[i];
}


void DA_free(DA *da) {
  // TODO deallocate anything on the heap
}

int main() {
    DA* da = DA_new();

    int size = DA_size(da);
    assert(DA_size(da) == 0);

    // basic push and pop test
    int x = 5;
    float y = 12.4;
    printf("first val: %p\n", &x);

    DA_push(da, &x);
    DA_push(da, &y);
    printf("size: %d", DA_size(da));
    assert(DA_size(da) == 2);

    assert(DA_pop(da) == &y);
    assert(DA_size(da) == 1);

    assert(DA_pop(da) == &x);
    assert(DA_size(da) == 0);
    assert(DA_pop(da) == NULL);

    // basic set/get test
    DA_push(da, &x);
    DA_set(da, &y, 0);
    assert(DA_get(da, 0) == &y);
    DA_pop(da);
    assert(DA_size(da) == 0);

    // expansion test
    DA *da2 = DA_new(); // use another DA to show it doesn't get overriden
    DA_push(da2, &x);
    int i, n = 100 * STARTING_CAPACITY, arr[n];
    for (i = 0; i < n; i++) {
      arr[i] = i;
      DA_push(da, &arr[i]);
    }
    assert(DA_size(da) == n);
    for (i = 0; i < n; i++) {
      assert(DA_get(da, i) == &arr[i]);
    }
    for (; n; n--)
      DA_pop(da);
    assert(DA_size(da) == 0);
    assert(DA_pop(da2) == &x); // this will fail if da doesn't expand

    DA_free(da);
    DA_free(da2);
    printf("OK\n");
}
