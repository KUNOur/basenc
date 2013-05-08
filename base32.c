#include "base32.h"

/* Encode data to Base32 */
int
base32_encode(const base32_byte *data, int len, char* enc)
{
  int success;

  int i, j;

  if (len > 0 && len >= 5) {
    j = 0;
    /* Encode first part of the data */
    for (i = 0; i < len; i += 5) {
      enc[j] = (data[i] >> 3) & 0x1F;
      enc[j+1] = ((data[i] << 2) & 0x1C) | ((data[i+1] >> 6) & 0x3);
      enc[j+2] = (data[i+i] >> 1) & 0x1F;
      enc[j+3] = ((data[i+1] << 4) & 0x10) | ((data[i+2] >> 4) & 0xF);
      enc[j+4] = ((data[i+2] << 1) & 0x1E) | ((data[i+3] >> 7) & 0x1);
      enc[j+5] = (data[i+3] >> 2) & 0x1F;
      enc[j+6] = ((data[i+3] << 3) & 0x18) | ((data[i+4] >> 5) & 0x7);
      enc[j+7] = data[i+4] & 0x1F;
    }
    /* TODO: Finish encoding the remaining data */
  } else if (len > 0 && len < 5) {
    /* TODO: Encode data of a length less than 5, have to padd data */
  } else {
    success = 0;
  }

  return success;
}
