/* https://github.com/jakub-m/sudoku-solver/blob/master/sudoku.c */

#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "assert.h"

#define NROWS (9)
#define NCOLS NROWS
#define NFIELDS (NCOLS * NROWS)
#define EMPTY (0)
#define true (1)
#define false (0)
#define NDIGITS (10)

//#define debugf(...) do {printf("%s %d:\t", __func__, __LINE__); printf(__VA_ARGS__);} while(0);
#define debugf(...)

typedef unsigned char bool;

typedef unsigned char field_t;

typedef struct {
  field_t fields[NROWS][NCOLS];
  int n_filled;
} board_t;

typedef struct {
  field_t digits[NDIGITS];
} digits_t;

struct stats {
  long unsigned int solve;
} stats;

struct stats stats;

bool is_complete(const board_t* board);
bool is_dead_end(const board_t* board);
void count_digits(const board_t* board, size_t i_row, size_t i_col,
		  digits_t* digits);
int count_possibilities(const digits_t* digits);
void find_next_continuation(const board_t* board, size_t* i_row, size_t* i_col,
			    digits_t* digits);

board_t* new_board()
{
  board_t* p = malloc(sizeof(board_t));
  bzero(p, sizeof(board_t));
  return p;
}

board_t* copy_board(const board_t* board)
{
  board_t* copied = (board_t*) malloc(sizeof(board_t));
  memcpy(copied, board, sizeof(board_t));
  return copied;
}

field_t get_digit(const board_t* board, size_t i_row, size_t i_col)
{
  return board->fields[i_row][i_col];
}

void set_digit(board_t* board, size_t i_row, size_t i_col, field_t value)
{
  assert(value > 0);
  assert(value < 10);
  assert(i_row < NROWS);
  assert(i_col < NCOLS);
  assert(EMPTY == board->fields[i_row][i_col]);
  assert(board->n_filled > 0);
  board->fields[i_row][i_col] = value;
  board->n_filled++;
}

bool load_board(board_t* board)
{
  size_t i;
  int n_filled = 0;
  bool is_good = true;
  field_t* p;
  for (i = 0; i < NROWS; ++i) {
    p = *(board->fields + sizeof(field_t) * i);
    scanf("%c%c%c%c%c%c%c%c%c\n",
	  p + 0, p + 1, p + 2,
	  p + 3, p + 4, p + 5,
	  p + 6, p + 7, p + 8);
  }
  p = *(board->fields);
  for (i = 0; i < (NROWS*NCOLS); ++i) {
    field_t v = (p[i] == '.') ? 0 : (p[i] - '0');
    p[i] = v;
    n_filled += (EMPTY == v) ? 0 : 1;
    is_good &= (v <= 9) ? true : false;
  }
  board->n_filled = n_filled;
  return is_good;
}

void print_board(const board_t* p)
{
  size_t i, j;
  for (i = 0; i < NROWS; ++i) {
    for (j = 0; j < NCOLS; ++j) {
      field_t x = p->fields[i][j];
      if (EMPTY == x) {
	printf(". ");
      } else {
	printf("%d ", (int)x);
      }
      if (2 == (j % 3)) {
	printf(" ");
      }
    }
    printf("\n");
    if ((i < (NROWS - 1)) && (2 == (i % 3))) {
      printf("\n");
    }
  }
}

void init_stats(struct stats* stats)
{
  bzero(stats, sizeof(struct stats));
}

void print_stats(struct stats stats)
{
  printf("# solve iterations: %lu\n", stats.solve);
}

void solve_board(board_t* board)
{
  stats.solve++;
  if (is_complete(board)) {
    printf("SOLVED!\n");
    print_board(board);
    print_stats(stats);
    assert(0);
  } else if (is_dead_end(board)) {
    debugf("dead end, skip\n");
  } else {
    size_t i_row, i_col;
    digits_t digits;
    find_next_continuation(board, &i_row, &i_col, &digits);
    debugf("best continuation [%lu,%lu]\n", i_row, i_col);
    size_t i;
    for (i = 1; i < NDIGITS; i++) {
      if (0 == digits.digits[i]) {
	debugf("extending [%lu,%lu] <- %lu\n", i_row, i_col, i);
	board_t* new_board = copy_board(board);
	set_digit(new_board, i_row, i_col, i);
	solve_board(new_board);
	free(new_board);
      }
    }
  }
}

#define NO_MOVE_POSSIBLE (100)
void find_next_continuation(const board_t* board, size_t* i_row, size_t* i_col,
			    digits_t* digits) {
  size_t i, j, best_row, best_col;
  digits_t tmp_digits, best_digits;
  int min_possibilities = NO_MOVE_POSSIBLE;
  for (i = 0; i < NROWS; i++) {
    for (j = 0; j < NCOLS; j++) {
      if (EMPTY == get_digit(board, i, j)) {
	count_digits(board, i, j, &tmp_digits);
	int n_possible = count_possibilities(&tmp_digits);
	assert(n_possible > 0);
	assert(n_possible < NDIGITS);
	if (n_possible < min_possibilities) {
	  min_possibilities = n_possible;
	  best_row = i;
	  best_col = j;
	  best_digits = tmp_digits;
	}
      }
    }
  }
  assert(min_possibilities != NO_MOVE_POSSIBLE);
  memcpy(digits, &best_digits, sizeof(digits_t));
  *i_row = best_row;
  *i_col = best_col;
}

bool is_complete(const board_t* board)
{
  return NFIELDS == board->n_filled;
}


bool is_dead_end(const board_t* board)
{
  size_t i, j;
  bool dead_end = false;
  for (i = 0; (i < NROWS) && (!dead_end); i++) {
    for (j = 0; (j < NCOLS) && (!dead_end); j++) {
      field_t value = get_digit(board, i, j);
      debugf("[%u,%u] == %d\n", i, j, value);
      if (EMPTY == value) {
	digits_t digits;
	count_digits(board, i, j, &digits);
	int n_possibilities = count_possibilities(&digits);
	if (0 == n_possibilities) {
	  dead_end = true;
	  debugf("[%lu,%lu] = %d, dead end\n", i, j, value);
	}
      }
    }
  }
  return dead_end;
}

void count_digits(const board_t* board, size_t i_row, size_t i_col,
		  digits_t* digits)
{
  assert(i_row < NROWS);
  assert(i_col < NCOLS);
  debugf("count digits [%lu,%lu]\n", i_row, i_col);
  bzero(digits, sizeof(digits_t));
  size_t i, j;

  const field_t* p = board->fields[i_row];
  for (i = 0; i < NCOLS; i++) {
    field_t x = p[i];
    assert(x <= 9);
    digits->digits[x] += 1;
  }

  p = board->fields[0];
  for (i = 0; i < NROWS; i++) {
    field_t x = *(p + i_col + i * NCOLS);
    assert(x <= 9);
    digits->digits[x] += 1;
  }

  p = board->fields[0] + (3 * (i_col / 3)) + (3 * (i_row / 3)) * NCOLS;
  for (i = 0; i < 3; i++) {
    for(j = 0; j < 3; j++) {
      field_t x = *(p + i + j*NCOLS);
      assert(x <= 9);
      digits->digits[x] += 1;
    }
  }
}

int count_possibilities(const digits_t* digits)
{
  int i, n_possibilities = 0;
  for (i = 1; i < NDIGITS; i++) {
    n_possibilities += (0 == digits->digits[i]) ? 1 : 0;
  }
  return n_possibilities;
}

int main() // int argc, char* argv)
{
  init_stats(&stats);
  board_t* board = new_board();
  if (false == load_board(board)) {
    printf("bad board\n");
  } else {
    printf("loaded board:\n");
    print_board(board);
    solve_board(board);
  }
  //        print_board(board);
  return 0;
}
