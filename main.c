/* printf() */
#include <stdio.h>
/* calloc(), realloc() */
#include <stdlib.h>
/* memset() */
#include <string.h>
/* access() */
#include <unistd.h>

struct loop {
  int open;
  int close;
};

/* description: print out the programs usage instructions */
void usage();
/* description: increase the size of our array
 * example:
 * increase array by 10
 * increase_array(array, &array_size, array_size + 10);
 */
void increase_array(int **arr, int *array_size, int new_size);
void increase_loops(struct loop **lps, int *loop_size, int new_size);

void find_loops(int depth);
int find_loop_open(int close);
int find_loop_close(int open);

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

struct loop *loops;
int loop_size = 0;

FILE *fp;

int main(int argc, char **argv) {
  int c;
  int offset;
  char *filename;

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

  loops = calloc(loop_size, sizeof *loops);

  fp = fopen(filename, "r");

  find_loops(0);
  for (int j = 0; j < loop_size; j++)
    printf("loop %d: %d %d\n", j, loops[j].open, loops[j].close);

  /*fseek(fp, 0, SEEK_SET);*/
  rewind(fp);

  while ((c = fgetc(fp)) != EOF) {
    break;
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
      if (array[dat_ptr] == 0) {
        printf("jumping forward in loop\n");
        offset = find_loop_close(ftell(fp));
        /*fseek(fp, offset, SEEK_SET);*/
      }
      break;
    case ']':
      if (array[dat_ptr] != 0) {
        offset = find_loop_open(ftell(fp));
        printf("Jumping back in loop: offset %d\n", offset);
        /*fseek(fp, offset, SEEK_SET);*/
      }
      break;
    }
  }

  /* Just for testing purposes */
  /*printf("\n");*/
  /*for (int i = 0; i < array_size; i++) {*/
    /*printf("%d\n", array[i]);*/
  /*}*/

  /* cleanup */
  fclose(fp);
  free(loops);
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
  printf("%c", array[dat_ptr]);
  //printf("%d", array[dat_ptr]);
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

void increase_loops(struct loop **lps, int *loops_size_ptr, int new_size) {
  *lps = realloc(*lps, new_size * sizeof(*loops));
  memset(*lps + *loops_size_ptr, 0,
      (new_size - *loops_size_ptr) * sizeof(*lps));
  *loops_size_ptr = new_size;
}

/*
 * every time you find an open bracket you create a new struct of that type and add it to they array and call the function again. And every time you find a closing bracket you go up one level. If the current index of that iteration (depth) is zero means that the next index iteration (on the array) will be the size of the array, otherwise it'll be the current index(on the array) + 1.
 */

void find_loops(int depth) {
  int index = 0;
  int c;
  while ((c = fgetc(fp)) != EOF) {
    switch (c) {
    case '[':
      if (index + 1 >= loop_size)
        increase_loops(&loops, &loop_size, loop_size + 1);


      loops[index].open = ftell(fp);

      index++;

      break;
    case ']':
      loops[index-1].close = ftell(fp);
      break;
    }
  }
}

//void find_loops() {
//  int c;
//  int i = 0;
//  int open_loops = 0;
//
//  fseek(fp, 0, SEEK_SET);
//  while ((c = fgetc(fp)) != EOF) {
//    switch (c) {
//    case '[':
//      /*
//       */
//      break;
//      if (i + 1 == loop_size)
//        increase_loops(&loops, &loop_size, loop_size + 1);
//
//      loops[i++].open = ftell(fp);
//
//      open_loops++;
//
//      break;
//    case ']':
//      /* i - 1 ? */
//      loops[i - 1].close = ftell(fp);
//      if (--open_loops)
//        i--;
//      break;
//    }
//  }
//  
//  for (int j = 0; j < loop_size; j++)
//    printf("loop %d: %d %d\n", j, loops[j].open, loops[j].close);
//}

int find_loop_open(int close) {
  for (int i = 0; i < loop_size; i++)
    if (loops[i].close == close)
      return loops[i].open;
  return -1;
}

int find_loop_close(int open) {
  for (int i = 0; i < loop_size; i++)
    if (loops[i].open == open)
      return loops[i].close;
  return -1;
}

void usage() {
  printf("Usage: bh [FILE]\n");
}

