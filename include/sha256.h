#ifndef _SHA256_H_
#define _SHA256_H_

/* SHA256 produces a 32 byte hash */
#define HASH_SIZE 32

#include <openssl/evp.h>
#include <openssl/crypto.h>

/*
 * Function that hashes a message with the SHA256 algorithm using openSSL EVP library.
 * Arguments:
 * * message - string for the message
 * ** digest - pointer to a string for the digest
 */ 

void digest_message (unsigned char * message, unsigned char ** digest);

#endif /* _SHA256_H_ */
