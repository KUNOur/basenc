#include "base32.h"

/**
 * \var char base32_encoding
 * \brief The encoding array for Base32
 *
 * The Base32 alphabet maps the numebers 0 to 31 to uppercase Latin characters
 * and numbers between 2 and 7.
 */
char base32_encoding[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
			   'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
			   'U', 'V', 'W', 'X', 'Y', 'Z', '2', '3', '4', '5',
			   '6', '7' };

/* Encode a 5-byte block of data to Base32 */
void
base32_encode_block(const base32_byte *data, char* enc)
{
  int i;
  int enc_index[8];

  enc_index[0] = (data[0] >> 3) & 0x1F;
  enc_index[1] = ((data[0] << 2) & 0x1C) | ((data[1] >> 6) & 0x3);
  enc_index[2] = (data[1] >> 1) & 0x1F;
  enc_index[3] = ((data[1] << 4) & 0x10) | ((data[2] >> 4) & 0xF);
  enc_index[4] = ((data[2] << 1) & 0x1E) | ((data[3] >> 7) & 0x1);
  enc_index[5] = (data[3] >> 2) & 0x1F;
  enc_index[6] = ((data[3] << 3) & 0x18) | ((data[4] >> 5) & 0x7);
  enc_index[7] = data[4] & 0x1F;

  for (i = 0; i < 8; i++) {
    enc[i] = base32_encoding[enc_index[i]];
  }
}

/* Encode small block */
void
base32_encode_small_block(const base32_byte *data, int len, char* enc)
{
  int i;

  enc[0] = base32_encoding[((data[0] >> 3) & 0x1F)];
  if (len == 1) {
    enc[1] = base32_encoding[(data[0] & 0x7)];
    for (i = 2; i < 8; i++) {
      enc[i] = BASE32_PADDING_CHAR;
    }
  } else {
    enc[1] = base32_encoding[((data[0] << 2) & 0x1C) | ((data[1] >> 6) & 0x3)];
    enc[2] = base32_encoding[(data[1] >> 1) & 0x1F];
    if (len == 2) {
      enc[3] = (data[1] << 7) & 0x80;
      for (i = 4; i < 8; i++) {
	enc[i] = BASE32_PADDING_CHAR;
      }
    } else {
      /* TODO */
    }
  }
}

/* Encode data to Base32 */
int
base32_encode(const base32_byte *data, int len, char* enc)
{
  int success;

  int i, j, k;
  int remaining;
  int enc_index[8];
  char final_block[5];

  if (len > 0 && len >= 5) {
    j = 0;
    /* Encode first part of the data */
    for (i = 0; i + 5 <= len; i += 5) {
      base32_encode_block(&data[i], &enc[j]);
      /*
      enc_index[0] = (data[i] >> 3) & 0x1F;
      enc_index[1] = ((data[i] << 2) & 0x1C) | ((data[i+1] >> 6) & 0x3);
      enc_index[2] = (data[i+1] >> 1) & 0x1F;
      enc_index[3] = ((data[i+1] << 4) & 0x10) | ((data[i+2] >> 4) & 0xF);
      enc_index[4] = ((data[i+2] << 1) & 0x1E) | ((data[i+3] >> 7) & 0x1);
      enc_index[5] = (data[i+3] >> 2) & 0x1F;
      enc_index[6] = ((data[i+3] << 3) & 0x18) | ((data[i+4] >> 5) & 0x7);
      enc_index[7] = data[i+4] & 0x1F;
      */ 

      /*
      for (k = 0; k < 8; k++) {
	enc[j+k] = base32_encoding[enc_index[k]];
      }
      */

      j += 8;
    }
    remaining = len - (i+5);
    /*
    printf("[DEBUG] len = %d\n", len);
    printf("[DEBUG] i = %d\n", i);
    printf("[DEBUG] remaining = %d\n", remaining);
    */
    if (remaining > 0) {
      for (k = 0; k < remaining; k++) {
	final_block[k] = data[i+k];
      }
      for (; k < 5; k++) { /* padding */
	/* TODO: FIX THIS - PADDING COMES AT THE END! */
	final_block[k] = BASE32_PADDING_CHAR;
      }
      /* Finish encoding the remaining data */
      base32_encode_block(final_block, &enc[j]);
    }
    enc[j] = '\0';

    success = 1;
  } else if (len > 0 && len < 5) {
    /* TODO: Encode data of a length less than 5, have to padd data */
  } else {
    success = 0;
  }

  return success;
}

/* Reverse Base32 Encoding */
static int
base32_encoding_reverse(int ch)
{
  int index;
  if (ch >= 'A') {
    index = ch - 'A';
  } else if (ch == BASE32_PADDING_CHAR) {
    /* TODO: Deal with padding */
  } else {
    index = 26 + (ch - '2');
  }
  return index;
}

/* Decode a Base32-encoded block of data */
void
base32_decode_block(const char* encoded, base32_byte *raw)
{
  /* NOTE: This is wrong because the decoding should not be based on the actual
   * encoded character, it is based on the index thereof */
  /* TODO: FIX THIS */
  raw[0] = ((encoded[0] << 3) & 0xF8) | ((encoded[1] >> 2) & 0x7);
  raw[1] = ((encoded[1] << 6) & 0xC0) | ((encoded[2] << 1) & 0x1F) 
    | ((encoded[3] >> 4) & 0x1);
  raw[2] = ((encoded[3] << 3) & 0xF0) | ((encoded[4] >> 1) & 0xF);
  raw[3] = ((encoded[4] << 7) & 0x80) | ((encoded[5] << 2) & 0x7C)
    | ((encoded[6] >> 3) & 0x3);
  raw[4] = ((encoded[6] << 5) & 0xE0) | (encoded[7] & 0x1F);
}
