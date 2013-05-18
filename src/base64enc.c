/*
 * Copyright 2013 David Jackson
 *
 * This file is part of Basenc
 *
 * Basenc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Basenc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Basenc.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Encode Data to Base64 */

#include <stdio.h>
#include <stdlib.h>
#include "base64.h"

#define USAGE_MESSAGE_FMT "Usage: %s [filename]"

int
main(int argc, char* argv[])
{
  char* fname = NULL;
  FILE* fp;
  base64_byte block[3];
  char encoded[5];
  int ch;
  int i;

  if (argc < 1 || argc > 2) {
    printf(USAGE_MESSAGE_FMT, argv[0]);
  } else {
    if (argc == 2) {
      fname = argv[1];
      fp = fopen(fname, "rb");
    } else {
      fp = stdin;
    }
    if (fp) {
      i = 0;
      while ((ch = fgetc(fp)) != EOF) {
	block[i] = ch;
	i++;
	if (i >= 3) {
	  base64_encode_block(block, encoded);
	  encoded[4] = '\0';
	  printf("%s", encoded);
	  i = 0;
	}
      }
      if (fp != stdin)
	fclose(fp);
    } else {
      printf("Error opening file: %s\n", fname);
    }
  }

  return 0;
}
