#include "base32.h"

/* Encode data to Base32 */
int
base32_encode(const base32_byte *data, int len, char* enc)
{
  int success;

  int i, j, k;
  int remaining;
  int enc_index[8];

  if (len > 0 && len >= 5) {
    j = 0;
    /* Encode first part of the data */
    for (i = 0; i + 5 < len; i += 5) {
      enc_index[0] = (data[i] >> 3) & 0x1F;
      enc_index[1] = ((data[i] << 2) & 0x1C) | ((data[i+1] >> 6) & 0x3);
      enc_index[2] = (data[i+i] >> 1) & 0x1F;
      enc_index[3] = ((data[i+1] << 4) & 0x10) | ((data[i+2] >> 4) & 0xF);
      enc_index[4] = ((data[i+2] << 1) & 0x1E) | ((data[i+3] >> 7) & 0x1);
      enc_index[5] = (data[i+3] >> 2) & 0x1F;
      enc_index[6] = ((data[i+3] << 3) & 0x18) | ((data[i+4] >> 5) & 0x7);
      enc_index[7] = data[i+4] & 0x1F;

      for (k = 0; k < 8; k++) {
	enc[j+k] = base32_encoding[enc_index[k]];
      }

      j += 8;
    }
    /* TODO: Finish encoding the remaining data */
    remaining = len - i;
    for (k = 0; k < remaining; k++) {
    }
  } else if (len > 0 && len < 5) {
    /* TODO: Encode data of a length less than 5, have to padd data */
  } else {
    success = 0;
  }

  return success;
}
