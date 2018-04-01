/* printf() */
#include <stdio.h>
/* calloc(), realloc() */
#include <stdlib.h>
/* memset() */
#include <string.h>
/* getopt(), access() */
#include <unistd.h>


/* description: print out the programs usage instructions */
void usage();
/* description: increase the size of our array
 * example:
 * increase array by 10
 * increase_array(array, &array_size, array_size + 10);
 */
void increase_array(int **arr, int *array_size, int new_size);

/* Commands */
void inc_dat_ptr(); /* > */
void dec_dat_ptr(); /* < */
void inc_data();    /* + */
void dec_data();    /* - */
void print_byte();  /* . */
void read_byte();   /* , */
void start_loop();  /* [ */
void end_loop();    /* ] */

/*
 * >  increment the data pointer (to point to the next cell to the right).
 *
 * <  decrement the data pointer (to point to the next cell to the left).
 *
 * +  increment (increase by one) the byte at the data pointer.
 *
 * -  decrement (decrease by one) the byte at the data pointer.
 *
 * . output the byte at the data pointer.
 *
 * , accept one byte of input, storing its value in the byte at the data pointer.
 *
 * [ if the byte at the data pointer is zero, then instead of moving the
 *   instruction pointer forward to the next command, jump it forward to
 *   the command after the matching ] command.
 *
 * ] if the byte at the data pointer is nonzero, then instead of moving
 *   the instruction pointer forward to the next command, jump it back to
 *   the command after the matching [ command.
 */

int array_size = 5;
int *array;
int dat_ptr = 0;

int main(int argc, char **argv) {
  int c;
  char *filename;
  FILE *fp;
  int looking_for_exit;

  array = calloc(array_size, sizeof(int));

  if (argc < 2) {
    usage();
    return 1;
  }

  filename = argv[1];
  if (access(filename, R_OK) == -1) {
    printf("%s: No such file or directory\n", filename);
    return 1;
  }

  fp = fopen(filename, "r");
  while ((c = fgetc(fp)) != EOF) {
    if (looking_for_exit && c != ']')
      continue;
    switch (c) {
    case '>':
      inc_dat_ptr();
      break;
    case '<':
      dec_dat_ptr();
      break;
    case '+':
      inc_data();
      break;
    case '-':
      dec_data();
      break;
    case '.':
      print_byte();
      break;
    case '[':
      if (array[dat_ptr] == 0 || looking_for_exit) {
        looking_for_exit++;
      }
      break;
    case ']':
      if (looking_for_exit) {
        looking_for_exit--;
        continue;
      } else if (array[dat_ptr] != 0) {
        // move backwards 
      }
      //if (array[dat_ptr] != 0) {
      //  loop_count++;
      //}
    }
  }
  fclose(fp);

  /* Just for testing purposes */
  /*printf("\n");*/
  /*for (int i = 0; i < array_size; i++) {*/
    /*printf("%d\n", array[i]);*/
  /*}*/

  /* cleanup */
  free(array);
  printf("\n");
  return 0;
}

void inc_dat_ptr() {
  if (++dat_ptr == array_size)
    increase_array(&array, &array_size, array_size + 10);
}

void dec_dat_ptr() {
  if (--dat_ptr < 0)
    printf("Error dat_ptr < 0");
}

void inc_data() {
  ++array[dat_ptr];
}

void dec_data() {
  --array[dat_ptr];
}

void print_byte() {
  //printf("%c", array[dat_ptr]);
  printf("%d", array[dat_ptr]);
}

void read_byte() {
  array[dat_ptr] = getchar();
}

void start_loop() {
  return;
}

void end_loop() {
  return;
}

void increase_array(int **arr, int *array_size_ptr, int new_size) {
  *arr = realloc(*arr, new_size * sizeof(int));
  memset(*arr + *array_size_ptr, 0, (new_size - *array_size_ptr) * sizeof(int));
  *array_size_ptr = new_size;
}

void usage() {
  printf("Usage: bh [FILE]\n");
}
