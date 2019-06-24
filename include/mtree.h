#ifndef _MTREE_H_
#define _MTREE_H_

#define MAX_CHARACTERS 200

typedef struct node {
	unsigned char * data;
	struct node * left;
	struct node * right;
} node_t;


/*
 * Function that creates a Merkle tree, initializes it from a list of strings and calculates all nodes
 * Arguments:
 * ** data - array of input data strings
 * size_data - size of the array of input data strings
 * size_tree - size of the base of the tree to be created
 * ** root - pointer to a pointer to the root of the tree 
 */

void create_tree (unsigned char ** data, size_t size_data, size_t size_tree, node_t ** root);

/*
 * Function that allocates memory to a node and initializes its members.
 * Arguments:
 * ** node - pointer to a pointer to the node
 * depth - remainant depth of the tree, in order to decide if we create children or not
 */
void initialize_children(node_t ** node, int depth);

/*
 * Function that recursively frees the memory dynamically alocated to the tree.
 * Arguments:
 * ** node 
 */
void free_tree(node_t ** node);


/*
 * Function that finds a node by level and by number (left to right) and gives you the pointer to that node
 * Arguments:
 * *root - pointer to the root node of the tree
 * depth - level in which the desired node is (from top to bottom) 0 to K
 * position - position of the node (from left to right), 0 to L
 * ** temp_node - pointer to a pointer of a temporary node structure which will contain the desired data 
 *
 * Interesting property of binary tree: bottom leaf number M can be accessed by 
 * following 0bN moves, where 0 is going left and 1 is going right.
 * 0bN has depth-1 bits
 * E.g.: depth = 4. Access leaf 7 = 0b110 = right/right/left.
 * 		 depth = 3. Access leaf 2 = 0b01 = left/right
 */
void find_node(node_t *root, int depth, int position, node_t ** temp_node);

/*
 * Function that prints the root of the tree.
 * Arguments:
 * *tree - pointer to the root of a tree
 */
void print_root(node_t *tree);


#endif /* _MTREE_H_ */
