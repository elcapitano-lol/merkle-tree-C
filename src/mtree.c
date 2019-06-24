#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sha256.h"
#include "utils.h"
#include "mtree.h"


void create_tree (unsigned char ** data, size_t size_data, size_t size_tree, node_t ** root)
{
	int i, j;
	int depth;
	unsigned char ** list_strings;
	node_t * temp_node1, * temp_node2;
	unsigned char * digest, * temp_string, * temp_cat_string;

	/* check if size of the base of the tree is smaller than the data size */
	if (size_tree < size_data) error_handler (ERROR_SIZE);

	/* find depth, assuming that size_tree is a power of 2 */
	if (0 != (size_tree & (size_tree - 1))) error_handler (ERROR_NOTPOW2);
	depth = log(size_tree)/log(2); /* another way of doing log2(n) */

	/* complete data array with 0000s if necessary*/
	list_strings = (unsigned char **) calloc (size_tree, sizeof(unsigned char *));
	if (NULL == list_strings) error_handler (ERROR_CALLOC);

	for (i = 0; i < size_tree; i++) {
		/* allocate memory to the string */
		list_strings[i] = (unsigned char *) calloc (MAX_CHARACTERS, sizeof(unsigned char));
		if (NULL == list_strings[i]) error_handler (ERROR_CALLOC);
		/* either fill with the user input data or with "0000" */
		if (i < size_data) 	strncpy(list_strings[i], data[i], strlen(data[i]));
		else memcpy(list_strings[i], "0000", strlen("0000"));
	}

	/* initialize root of the tree and all children */
	initialize_children(root, depth);

	/* initialize digest string, which needs 32 bytes in the case of SHA256 (+1 for \0)*/
	digest = (unsigned char *) calloc (HASH_SIZE + 1, sizeof(unsigned char));
	if (NULL == digest) error_handler (ERROR_CALLOC);

	/* initialize temporary string, which needs to hold 32 characters in the case of SHA256 (+1 for \0) */
	temp_string = (unsigned char *) calloc (HASH_SIZE + 1, sizeof(unsigned char));
	if (NULL == temp_string) error_handler (ERROR_CALLOC);
	
	/* hash the input data and place the hash in the correspondent bottom node (leaf) */
	for (i = 0; i < size_tree; i++) {
		
		find_node(*root, depth, i, &temp_node1);
		digest_message(list_strings[i], &digest);
		memcpy(temp_node1->data, digest, HASH_SIZE+1);
	}


	/* initialize temporary string, which needs to hold 2 hashes */
	temp_cat_string = (unsigned char *) calloc (HASH_SIZE*2 + 1, sizeof(unsigned char));
	if (NULL == temp_cat_string) error_handler (ERROR_CALLOC);

	/* complete the rest of the tree by calculating the hashes for each pair of nodes */
	for (i=depth; i>0; i--) {

		/* level i has 2^(i-1) pairs of nodes */
		for (j=0; j<pow(2,i-1); j++) {

			/* find source pair of nodes depth i and position (j*2, j*2 + 1) */
			find_node(*root, i, j*2, &temp_node1);
			find_node(*root, i, j*2+1, &temp_node2);

			/* clean temp_cat_string and concatenate the two hashes into it */
			temp_cat_string[0]='\0';
			strncat(temp_cat_string, temp_node1->data, strlen(temp_node1->data));
			strncat(temp_cat_string, temp_node2->data, strlen(temp_node2->data));

			/* hash the concatenated hashes, find the parent node and place the result there */
			digest_message(temp_cat_string, &digest);
			find_node(*root, i-1, j, &temp_node1);
			memcpy(temp_node1->data, digest, HASH_SIZE+1);
		}
	}

	/* free memory */
	for (i = 0; i < size_tree; i++)
		free(list_strings[i]);
	free(list_strings);
	free(digest);
	free(temp_string);
	free(temp_cat_string);
}


void free_tree(node_t ** node)
{
	if ((*node)->left != NULL) free_tree(&((*node)->left));
	if ((*node)->right != NULL) free_tree(&((*node)->right));
	
	free((*node)->data);
	free(*node);
}


void initialize_children(node_t ** node, int depth)
{
	/* allocate memory to the node */
	*node = (node_t *) calloc (1,sizeof(node_t));
	if (NULL == (*node)) error_handler (ERROR_CALLOC);

	/* allocate 32 characters to the string that holds the hash (+1 for termination) */
	(*node)->data = (unsigned char *) calloc (HASH_SIZE + 1, sizeof(unsigned char));
	if (NULL == (*node)->data) error_handler (ERROR_CALLOC);

	/* fill it with string "null" */
	memcpy((*node)->data, "null", strlen("null"));
	(*node)->data[strlen("null")] = '\0';

	/* point the children to NULL */
	(*node)->left = NULL;
	(*node)->right = NULL;

	/* if depth > 0, still need to initialize children*/
	if (depth > 0) {
		initialize_children(&((*node)->left), depth-1);
		initialize_children(&((*node)->right), depth-1);
	}
}

void find_node(node_t *root, int depth, int position, node_t ** temp_node)
{
	int i;
	int dir;

	/* start with current node = root of tree */
	*temp_node = root;

	/* go through the tree: 0 is left move, 1 is right move and keep moving temp_node*/
	for (i=depth; i>0; i--) {	
		dir = (position >> (i-1)) & 1;

		if (dir==0) *temp_node = (*temp_node)->left;
		if (dir==1) *temp_node = (*temp_node)->right;
	}
}

void print_root(node_t *tree)
{
	print_hash(tree->data);
}