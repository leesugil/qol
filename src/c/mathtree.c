/* Binary tree template */

#include "qol/c/mathtree.h"

static MathNode *mathnodeAlloc(void)
{
	return (MathNode *) malloc(sizeof(MathNode));
}

int mathstrcmp(char *s, char *t, char *pre, char *suf);
MathNode *addMathNode(MathNode *p, char *name, char *pre, char *suf)
{
	int cond;

	if (p == NULL) {
		p = mathnodeAlloc();
		p->name = strdup(name);
		p->count = 1;
		p->left = NULL;
		p->right = NULL;
	} else if ((cond = mathstrcmp(name, p->name, pre, suf)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addMathNode(p->left, name, pre, suf);
	else
		p->right = addMathNode(p->right, name, pre, suf);

	return p;
}

/* listMathNode: in-order print of tree p */
void listMathNode(MathNode *p)
{
	if (p != NULL) {
		listMathNode(p->left);
		printf("%s\n", p->name);
		listMathNode(p->right);
	}
}

/* getMathNode: returns a pointer to the MathNode found */
MathNode *getMathNode(MathNode *p, char *name)
{
	int cond;

	if (p == NULL)
		return NULL;
	else if ((cond = mathstrcmp(name, p->name, NULL, NULL)) == 0)
		return p;
	else if (cond < 0) {
		fprintf(stderr, "getMathNode: taking left from p->name: %s\n", p->name);
		return getMathNode(p->left, name);
	} else {
		fprintf(stderr, "getMathNode: taking right from p->name: %s\n", p->name);
		return getMathNode(p->right, name);
	}
}

/* removeMathNode: frees a mathnode and its branch below */
void removeMathNode(MathNode *p)
{
	if (p != NULL) {
		removeMathNode(p->left);
		removeMathNode(p->right);
		p->left = NULL;
		p->right = NULL;
		/* free all dynamically allocated members */
		free(p->name);
		free(p);
	}
}

/* removeMathNodeBranch: frees child mathnodes in the branch */
void removeMathNodeBranch(MathNode *p)
{
	removeMathNode(p->left);
	removeMathNode(p->right);
	p->left = NULL;
	p->right = NULL;
}

int mathnodelen(MathNode *p, int n)
{
	if (p == NULL)
		return n;

	n = mathnodelen(p->left, n);
	n = mathnodelen(p->right, n);

	return n + 1;
}

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
int mathstrcmp(char *s, char *t, char *pre, char *suf)
{
	/* return back to here */

	return 0;
}
