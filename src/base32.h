/** 
 * \file base32.h
 * \brief A header for encoding and decoding data to/from Base32
 */

#ifndef BASE32_H
#define BASE32_H

#define BASE32_PADDING_CHAR '='

/**
 * \var typedef unsigned char base32_byte
 * \brief A type definition for a generic byte
 *
 * The base32_byte type is an unsigned character because it has to be one byte
 * long and the sign bit is always irrelevant.
 */
typedef unsigned char base32_byte;

/**
 * Base32 Encode Block
 *
 * Given a bytestring with a length of exactly 5 bytes, return a character
 * string with a length of 8 bytes that is the Base32-encoded version of that
 * initial bytestring of data. It is the programmer's responsibility to ensure
 * that the "encoded" string has enough space for 8 characters and a trailing
 * null character.
 *
 * \param data The initial data bytestring
 * \param enc A pointer to the encoded string
 */
extern void
base32_encode_block(const base32_byte *data, char* enc);

/**
 * Base32 Encode
 *
 * Given a bytestring of data, find the Base32 encoding of that bytestring. It
 * is the programmer's responsibility to ensure that enough memory is allocated
 * to store the encoded data.
 *
 * \param data The original data to encode
 * \param len The length of the data in bytes
 * \param enc A pointer to the string into which to store the encoded version.
 * \return An intger: 1 on pass, 0 on failure
 */
extern int
base32_encode(const base32_byte *data, int len, char* enc);

#endif /* BASE32_H */
