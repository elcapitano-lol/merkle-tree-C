#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"
#include "utils.h"

void digest_message (unsigned char *message, unsigned char **digest)
{
	int i;
	unsigned int status = 1;
	EVP_MD_CTX *mdctx;
	unsigned char md_value[EVP_MAX_MD_SIZE];
	int md_len;
	size_t message_len = strlen(message);

	/* create a Message Digest context */
	mdctx = EVP_MD_CTX_create();
	if (NULL == mdctx) error_handler(ERROR_SHA256);

	/* initialize the context and specify algorithm */
	status = EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
	if (1 != status) error_handler(ERROR_SHA256);

	/* provide the message, calculate hash, place it in *digest */
	status = EVP_DigestUpdate(mdctx, message, message_len);
	if (1 != status) error_handler(ERROR_SHA256);

	status = EVP_DigestFinal_ex(mdctx, *digest, &md_len);
	if (1 != status) error_handler(ERROR_SHA256);

	(*digest)[md_len]='\0';
	
	/* free up resources */
	EVP_MD_CTX_destroy(mdctx);
}
