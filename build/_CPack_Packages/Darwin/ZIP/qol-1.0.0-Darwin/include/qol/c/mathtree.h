/* Binary tree template */

#ifndef MATHTREE_H
#define MATHTREE_H

#include <string.h>
#include "qol/c/getword.h"

typedef struct MathNode MathNode;

struct MathNode {
	char *name;
	int count;
	MathNode *left;
	MathNode *right;
};

static MathNode *mathnodeAlloc(void);

int mathstrcmp(char *s, char *t, char *pre, char *suf);

MathNode *addMathNode(MathNode *p, char *name, char *pre, char *suf);

/* listMathNode: in-order print of tree p */
void listMathNode(MathNode *p);

/* getMathNode: returns a pointer to the MathNode found */
MathNode *getMathNode(MathNode *p, char *name);

/* removeMathNode: frees a mathnode and its branch below */
void removeMathNode(MathNode *p);

/* removeMathNodeBranch: frees child mathnodes in the branch */
void removeMathNodeBranch(MathNode *p);

int mathnodelen(MathNode *p, int n);

/* mathstrcmp: similar to strcmp, except it recognizes the "base" of a mathematical symbol with aid of *pre and *surf, making them out and compare.
 * it's tricky to explain in words, so here's an example.
 *
 * consider the following three elements:
 * a, b, -b
 * usual lexicon order sorting would sort it as
 * -b, a, b
 * as the negative sign has smaller integer value.
 * mathstrcmp accepts "-" and "" as pre and suf, mask them, and yield
 * a, b, -b
 *
 * another example:
 * a, (dx)^3, (dx)^-4
 * will turn into
 * a, (dx)^-4, (dx)^3
 * with "(" and ")^" as pre ans suf
 * instead of
 * (dx)^-4, (dx)^3, a
 * which is the usual comparison made with ASCII values.
 * */
int mathstrcmp(char *s, char *t, char *pre, char *suf);

#endif	/* MATHTREE_H */
