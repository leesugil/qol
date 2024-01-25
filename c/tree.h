/* Binary tree template */

#ifndef TREE_H
#define TREE_H

#include <string.h>

typedef struct Node Node;

struct Node {
	char *name;
	int count;
	Node *left;
	Node *right;
}

static Node *nodeAlloc(void)
{
	return (Node *) malloc(sizeof(Node));
}

Node *addNode(Node *p, char *name)
{
	int cond;

	if (p == NULL) {
		p = nodeAlloc();
		p->name = strdup(name);
		p->count = 1;
		p->left = NULL;
		p->right = NULL;
	} else if ((cond = strcmp(name, p->name)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addNode(p->left, name);
	else
		p->right = addNode(p->right, name);

	return p;
}

/* listNode: in-order print of tree p */
void listNode(Node *p)
{
	static unsigned int tab = 0;
	unsigned int tab_size = 4;
	int i;

	if (p != NULL) {
		for (i = 0; i < tab; i++)
			printf(" ");
		printf("%s\n", p->name);
		tab += tab_size;
		listNode(p->left);
		listNode(p->right);
		tab -= tab_size;
	}
}

/* getNode: returns a pointer to the Node found */
Node *getNode(Node *p, char *name)
{
	int cond;

	if (p == NULL)
		return NULL;
	else if ((cond = strcmp(name, p->name)) == 0)
		return p;
	else if (cond < 0) {
		fprintf(stderr, "getNode: taking left from p->name: %s\n", p->name);
		return getNode(p->left, name);
	} else {
		fprintf(stderr, "getNode: taking right from p->name: %s\n", p->name);
		return getNode(p->right, name);
	}
}

/* removeNode: frees a node and its branch below */
void removeNode(Node *p)
{
	if (p != NULL) {
		removeNode(p->left);
		removeNode(p->right);
		/* free all dynamically allocated members */
		free(p->name);
		free(p);
	}
}

/* removeNodeBranch: frees child nodes in the branch */
void removeNodeBranch(Node *p)
{
	removeNode(p->left);
	removeNode(p->right);
	p->left = NULL;
	p->right = NULL;
}


#endif	/* TREE_H */
