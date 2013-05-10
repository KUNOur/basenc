#include <stdio.h>
#include <stdlib.h>
#include "base32.h"

/*
 * Given some data, encode it to base32 and output to stdout
 */

#define USAGE_MESSAGE_FMT "Usage: %s [filename]\n"
#define DATA_BLOCK_SIZE 5
#define ENC_BLOCK_SIZE 8

static void
print_encoded_block(const char* block) {
  int i;
  for (i = 0; i < ENC_BLOCK_SIZE; i++) {
    printf("%c", block[i]);
  }
}

int
main(int argc, char* argv[])
{
  FILE* in = NULL;
  char* fname = NULL;
  base32_byte data_block[DATA_BLOCK_SIZE];
  char enc_block[ENC_BLOCK_SIZE]; /* block of base32-encoded data */
  int block_size = 0;
  int ch;

  if (argc < 2) {
    in = stdin;
  } else if (argc == 2){
    fname = argv[1];
  } else {
    printf(USAGE_MESSAGE_FMT, argv[0]);
  }

  if (fname) {
    in = fopen(fname, "rb");
  }

  if (in) {
    ch = fgetc(in);
    while (ch != EOF) {
      block_size++;
      data_block[block_size-1] = ch;
      if (block_size == 5) {
	base32_encode_block(data_block, enc_block);
	print_encoded_block(enc_block);
	block_size = 0;
      }
      ch = fgetc(in);
    }
    /* TODO: Finish up any remaining data */

    /* TODO: Output the Base32-encoded stream */

    if (in != stdin) {
      fclose(in);
    }
  }

  printf("\n"); /* Print an extra newline for cleaner output */
  return 0;
}
