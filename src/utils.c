#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"
#include "utils.h"

void error_handler(unsigned int err) {

  switch(err) {

	case ERROR_CALLOC :
      	printf("\nError during dynamic memory allocation. Exiting...\n");
      	break;
	
  case ERROR_SHA256 :
      	printf("\nError during use of OpenSSL EVP functions. Exiting...\n");
      	break;
	
  case ERROR_NOTPOW2 :
      	printf("\nSize of tree is not power of 2. Exiting...\n");
      	break;

  case ERROR_SIZE : 
    printf("\nSize of data is larger than the size of tree. Exiting...\n"); 
    break;
  
  default : 
  	break;
  }

  exit(EXIT_FAILURE);
}


void print_hash(unsigned char * string){
	int i;
	for (i=0; i < HASH_SIZE; i++) printf("%02x", string[i]);
	printf("\n");
}