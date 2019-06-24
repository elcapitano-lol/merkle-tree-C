#ifndef _UTILS_H_
#define _UTILS_H_

#define ERROR_CALLOC 0
#define ERROR_SHA256 1
#define ERROR_NOTPOW2 2
#define ERROR_SIZE 3

/*
 * Function that handles error codes
 * Arguments:
 * err - error code
 */ 

void error_handler (unsigned int err);

/*
 * Function that prints a string in hexadecimal form
 * Arguments:
 * * string - string containing the hash
 */
void print_hash(unsigned char * string);

#endif /* _UTILS_H_ */
