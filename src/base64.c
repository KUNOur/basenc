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
