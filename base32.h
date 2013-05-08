/** 
 * \file base32.h
 * \brief A header for encoding and decoding data to/from Base32
 */

#ifndef BASE32_H
#define BASE32_H

/**
 * \var typedef unsigned char base32_byte
 * \brief A type definition for a generic byte
 *
 * The base32_byte type is an unsigned character because it has to be one byte
 * long and the sign bit is always irrelevant.
 */
typedef unsigned char base32_byte;

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
int
base32_encode(const base32_byte *data, int len, char* enc);

#endif /* BASE32_H */
