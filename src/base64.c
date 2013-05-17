#include "base64.h"

/*
 * Base64 Encoding Table
 */
char base64_encoding[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
			   'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
			   'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
			   'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
			   's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
			   '3', '4', '5', '6', '7', '8', '9', '+', '/' };

/* Encode a 3-byte block of data to Base64 */
void
base64_encode_block(const base64_byte *data, char* enc)
{
  int i;
  int enc_index[BASE64_ENCODED_BLOCK_SIZE];

  enc_index[0] = (data[0] >> 2) & 0x3F;
  enc_index[1] = ((data[0] << 4) & 0x3C) | ((data[1] >> 4) & 0xF);
  enc_index[2] = ((data[1] << 2) & 0x3C) | ((data[2] >> 6) & 0x3);
  enc_index[3] = (data[2] & 0x3F);

  /* Encode the data block to Base64 */
  for(i = 0; i < BASE64_ENCODED_BLOCK_SIZE; i++) {
    enc[i] = base64_encoding[enc_index[i]];
  }
}

/* Encode Data to Base64 */
void
base64_encode(base64_byte *data, int len, char* encoded)
{
  int i, j;
  int remaining;
  j = 0;
  for (i = 0; i + 3 <= len; i += 3) {
    base64_encode_block(&data[i], &encoded[j]);
    j += 4;
  }

  remaining = len - i;
  if (remaining == 1) {
    encoded[j] = base64_encoding[(data[i] >> 2) & 0x3F];
    encoded[j+1] = base64_encoding[(data[i] << 4) & 0x30];
    encoded[j+2] = BASE64_PADDING_CHAR;
    encoded[j+3] = BASE64_PADDING_CHAR;
  } else if (remaining == 2) {
    encoded[j] = base64_encoding[(data[i] >> 2) & 0x3F];
    encoded[j+1] = base64_encoding[((data[i] << 4) & 0x30)
				   | ((data[i+1] >> 4) & 0xF)];
    encoded[j+2] = base64_encoding[(data[i+1] << 2) & 0x3C];
    encoded[j+3] = BASE64_PADDING_CHAR;
  }
}

/* Get index of Base64 Character */
static int
base64_get_index(char ch)
{
  int index;

  if (ch >= 'A' && ch <= 'Z') {
    index = ch - 'A';
  } else if (ch >= 'a' && ch <= 'z') {
    index = 26 + (ch - 'a');
  } else if (ch >= '0' && ch <= '9') {
    index = 26 + 26 + (ch - '0');
  } else if (ch == '+') {
    index = 26 + 26 + 10;
  } else if (ch == '/') {
    index = 26 + 26 + 11;
  } else if (ch == '=') {
    index = 0; /* Padding */
  } else {
    printf("Incorrect input, illegal character '%c'\n", ch);
    assert(0); /* Fail on incorrect input */
  }

  return index;
}

/* Decode Base64-encoded data */
void
base64_decode(char* encoded, base64_byte *raw)
{
  int encoded_len = strlen(encoded);
  int i, j, k;
  base64_byte indices[4];

  k = 0;
  for (i = 0; i + 4 <= encoded_len; i += 4) {
    for (j = 0; j < 4; j++) {
      indices[j] = base64_get_index(encoded[i+j]);
    }
    raw[k] = ((indices[i] << 6) & 0xFC) | ((indices[i+1] >> 4) & 0x3);
    raw[k+1] = ((indices[i+1] << 4) & 0xF0) | ((indices[i+2] >> 2) & 0xF);
    raw[k+2] = ((indices[i+2] << 6) & 0xC0) | (indices[i+3] & 0x3F);
    k += 3;
  }
}
