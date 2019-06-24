#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha256.h"
#include "utils.h"
#include "mtree.h"

int main() 
{
	
	int i;
	node_t * tree;

	unsigned char *data[] = {"Pedro", "Lisa", "Tom", "Hannah"};
	size_t size_data = sizeof(data)/sizeof(unsigned char *);
	size_t size_tree = 4;
	
	/* create tree */
	create_tree(data, size_data, size_tree, &tree);

	/* print root tree */
	print_root(tree);

	/* free the entire tree */
	free_tree(&tree);

	exit(EXIT_SUCCESS);
} 
