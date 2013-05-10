#include <stdio.h>
#include <stdlib.h>
#include "base32.h"

/*
 * Given some data, encode it to base32 and output to stdout
 */

#define USAGE_MESSAGE_FMT "Usage: %s [filename]\n"
#define ENC_BLOCK_SIZE 8

int
main(int argc, char* argv[])
{
  FILE* in = NULL;
  char* fname = NULL;
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
      block_size = (block_size + 1) % ENC_BLOCK_SIZE;
      /* TODO: Encode the stream to Base32 */
      ch = fgetc(in);
    }

    /* TODO: Output the Base32-encoded stream */

    if (in != stdin) {
      fclose(in);
    }
  }

  return 0;
}
