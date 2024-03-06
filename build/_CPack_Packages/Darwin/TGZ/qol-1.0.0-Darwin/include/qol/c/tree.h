/* Binary tree template */

#ifndef TREE_H
#define TREE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
	char *name;
	int count;
	Node *left;
	Node *right;
};

static Node *nodeAlloc(void);

Node *addNode(Node *p, char *name);

/* listNode: in-order print of tree p */
void listNode(Node *p);

/* getNode: returns a pointer to the Node found */
Node *getNode(Node *p, char *name);

/* removeNode: frees a node and its branch below */
void removeNode(Node *p);

/* removeNodeBranch: frees child nodes in the branch */
void removeNodeBranch(Node *p);

int nodelen(Node *p, int n);

#endif	/* TREE_H */
