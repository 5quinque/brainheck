/* printf() */
#include <stdio.h>
/* calloc(), realloc(), abort() */
#include <stdlib.h>
/* memset() */
#include <string.h>
/* getopt() */
#include <unistd.h>

void increase_array(int *array, int cs, int ns);

int main(int argc, char **argv) {
  int c;
  int array_size = 20;
  int *array = calloc(array_size, sizeof(int));

  while ((c = getopt(argc, argv, "i:o:")) != -1) {
    switch(c) {
    case 'i':
      printf("input: %s\n", optarg);
      break;
    case 'o':
      printf("output: %s\n", optarg);
      break;
    default:
      abort();
    }
  }

  int index = 0;
  //int *ptr = array;

  //for (; ptr != array + array_size; ptr++) {
  //  *ptr = *(ptr - 1) + 1;
  //}

  array_size = 30;
  increase_array(array, 20, 30);

  //ptr = array;
  //for (; ptr != &array[array_size]; ptr++) {
  //}
  //
  for (int i = 0; i < array_size; i++) {
    array[i] = i;
    printf("%d\n", array[i]);
  }

  free(array);
  return 0;
}

void increase_array(int *array, int current_size, int new_size) {
  array = realloc(array, new_size * sizeof(int));
  memset(array + current_size, 0, (new_size - current_size) * sizeof(int));
}
