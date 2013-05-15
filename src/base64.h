/**
 * \file base64.h
 * \brief Header to deal with encoding/decoding Base64 data
 */

#ifndef BASE64_H
#define BASE64_H

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BASE64_DATA_BLOCK_SIZE 3
#define BASE64_ENCODED_BLOCK_SIZE 4
#define BASE64_PADDING_CHAR '='

/**
 * \var typedef unsigned char base64_byte
 * \brief A type definition for a generic byte
 *
 * The base64_byte type is an unsigned character because it has to be one byte
 * long and the sign bit is always irrelevant.
 */
typedef unsigned char base64_byte;

/**
 * Base64 Encode Block
 *
 * Given a block of arbitrary data, encode that block to Base64. The size of the
 * data block is 3 bytes, the output will be 4 bytes (characters). It is the
 * programmer's responsibility to ensure that the encoded data array is large
 * enough to contain the encoded data.
 *
 * \param data The input data array
 * \param enc The array into which to put the encoded data
 */
void
base64_encode_block(const base64_byte *data, char* enc);

/**
 * Base64 Encode
 *
 * Given an array of binary data, find the Base64 representation of that data. It
 * is left up to the programmer to ensure that the array to hold the encoded data
 * is large enough to do so.
 *
 * \param data The array of binary data
 * \param len The length of the data array in bytes
 * \parma encoded The Base64-encoded data array
 */
void
base64_encode(base64_byte *data, int len, char* encoded);

/**
 * Base64 Decode
 *
 * Given an array of Base64-encoded data, find the raw binary data which it
 * represents. It is up to the programmer to ensure that the array which holds the
 * binary data is large enough to do so.
 *
 * \param encoded The Base64-encoded data
 * \param raw The data to store the raw binary data
 */
void
base64_decode(char* encoded, base64_byte *raw);

#endif /* BASE64_H */

