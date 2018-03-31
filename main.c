/* printf() */
#include <stdio.h>
/* calloc(), realloc(), abort() */
#include <stdlib.h>
/* memset() */
#include <string.h>
/* getopt(), access() */
#include <unistd.h>


void usage();
/* example:
 * increase array by 10
 * increase_array(array, &array_size, array_size + 10);
 */
void increase_array(int *arr, int *array_size, int ns);

/* Commands */
/* > */
void inc_dat_ptr();
/* < */
void dec_dat_ptr();
/* + */
void inc_data();
/* - */
void dec_data();
/* . */
void print_byte();
/* , */
void read_byte();
/* [ */
void start_loop();
/* ] */
void end_loop();

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

int *array;
int dat_ptr = 0;

int main(int argc, char **argv) {
  int c;
  int array_size = 1000;
  char *filename;
  FILE *fp;

  array = calloc(array_size, sizeof(int));

  while ((c = getopt(argc, argv, "i:")) != -1) {
    switch(c) {
    case 'i':
      filename = optarg;
      if (access(filename, R_OK) == -1) {
        printf("%s: No such file or directory\n", filename);
        return 1;
      }
      break;
    default:
      abort();
    }
  }
  if (filename == NULL) {
    usage();
    return 1;
  }


  fp = fopen(filename,"r");
  while ((c = fgetc(fp)) != EOF) {
    //printf("%c", c);
    switch (c) {
    case '>':
      dec_dat_ptr();
      break;
    case '<':
      inc_dat_ptr();
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
    }
  }
  fclose(fp);

  /* cleanup */
  free(array);
  printf("\n");
  return 0;
}

void inc_dat_ptr() {
  ++dat_ptr;
}

void dec_dat_ptr() {
  --dat_ptr;
}

void inc_data() {
  ++array[dat_ptr];
}

void dec_data() {
  --array[dat_ptr];
}

void print_byte() {
  printf("%c", array[dat_ptr]);
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

void increase_array(int *arr, int *array_size_ptr, int new_size) {
  arr = realloc(arr, new_size * sizeof(int));
  memset(arr + *array_size_ptr, 0, (new_size - *array_size_ptr) * sizeof(int));
  *array_size_ptr = new_size;
}

void usage() {
  printf("Usage: bh -i input");
}
