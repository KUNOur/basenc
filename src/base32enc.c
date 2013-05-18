/*
 * Copyright 2013 David Jackson
 *
 * This file is part of Basenc
 *
 * Basenc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Basenc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Basenc.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include "base32.h"

/*
 * Given some data, encode it to base32 and output to stdout
 */

#define USAGE_MESSAGE_FMT "Usage: %s [filename]\n"
#define DATA_BLOCK_SIZE 5
#define ENC_BLOCK_SIZE 8

/*
 * Print an 8-character block of Base32-encoded data
 */
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
    if (block_size > 0) {
      int i;
      for (i = block_size; i < DATA_BLOCK_SIZE; i++) {
	data_block[i] = BASE32_PADDING_CHAR;
      }
      base32_encode_block(data_block, enc_block);
      print_encoded_block(enc_block);
    }

    if (in != stdin) {
      fclose(in);
    }
  }

  printf("\n"); /* Print an extra newline for cleaner output */
  return 0;
}
