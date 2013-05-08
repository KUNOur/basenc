/** \file */

#ifndef BASE32_H
#define BASE32_H

typedef unsigned char base32_byte;

/**
 * Base32 Encode
 *
 * Given a bytestring of data, find the Base32 encoding of that bytestring.
 *
 * \param data The original data to encode
 * \param enc A pointer to the string into which to store the encoded version.
 * \return An intger: 1 on pass, 0 on failure
 */
int
base32_encode(const base32_byte *data, char* enc);

#endif /* BASE32_H */
