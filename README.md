# Simple Merkle tree implementation
==============


## 1. Introduction
--------------

This is a library to implement a simplified version of a Merkle tree. It also contains a test application that makes use of the library.


## 2. Dependencies
--------------

User needs to install OpenSSL development libraries before trying to build the library.
- In Ubuntu:
	apt-get install libssl-dev
- In Fedora:
	yum install openssl-libdevel


## 3. Build
--------------

To build, run make with the following targets: 
- all - builds the library and the test application 
- clean - cleans the build artifacts 


## 4. Usage
--------------

The test application already contains a simple test case but you can execute more by changing the array of strings data[] and the variable size_tree, which is the amount of bottom nodes or leaves (for example size_tree=8 means there are 8 strings in total). The strings that are not specified in the data[] array will be filled with "0000".

	create_tree()
This function will create the tree, initialize the leaves with the SHA256 hash of the provided input strings and fill all parent nodes up to the root with the SHA256 hash of the respective children

	print_root()
This function will print out the root hash.

	free_tree()
This function releases all memory used up by the tree.


## 5. Notes
--------------

During the development I used gdb for debugging.

	gdb ./test_app

Additionally, I ran valgrind to detect any memory issues. There were no errors or leaks and all allocated heap space was freed.

	valgrind ./test_app


Thank you for your time! 
Pedro
