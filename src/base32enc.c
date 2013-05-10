#include <stdio.h>
#include <stdlib.h>
#include "base32.h"

/*
 * Given some data, encode it to base32 and output to stdout
 */

#define USAGE_MESSAGE_FMT "Usage: %s [filename]\n"

int
main(int argc, char* argv[])
{
  FILE* in = NULL;
  char* fname = NULL;

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
    /* TODO: Encode the stream to Base32 */
    /* TODO: Output the Base32-encoded stream */

    if (in != stdin) {
      fclose(in);
    }
  }

  return 0;
}
