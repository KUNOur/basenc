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
