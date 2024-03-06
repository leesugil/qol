#ifndef GETMATH_H
#define GETMATH_H

#include "getword.h"
#include "tree.h"

/* parseFuncArg: given a valid function form f(x, y), parses the argument part x, y. pre and suf are the block options { "(", "[", "{", NULL }
 * the current versions of
 * parseFuncArg, parseFuncName, parseSymbName
 * do not fully support all possible block options and
 * only support { "(", NULL } */
void parseFuncArg(char arg[], char *name)
{
	char *prog = "parseFuncArg";

	arg[0] = '\0';
	if (name == NULL || strlen(name) == 0)
		return ;
	if (name[strlen(name) - 1] != ')')
		return ;
	char line[MAXCHAR] = "";
	strcpy(line, name);
	char *pre[] = { "(", NULL };
	char *suf[] = { ")", NULL };
	while (is_outer_blocked_blk(line, pre, suf, NULL))
		remove_outer_block_blk(line, pre, suf);
	if (!is_blocked_properly_blk(line, pre, suf, NULL))
		return;
	char *s = strstr(line, "(");
	if (s == NULL)
		return ;
	strcpy(arg, line);
	fcutnstr(arg, s - line + 1);
	fprintf(stderr, "%s: bcutstr: \"%s\"\t(before)\n", prog, arg);
	bcutstr(arg);
	fprintf(stderr, "%s: bcutstr: \"%s\"\t(after)\n", prog, arg);
	if (!is_blocked_properly_blk(arg, pre, suf, NULL))
		arg[0] = '\0';
}
void parseFuncName(char w[], char *name)
{
	if (w == NULL)
		return;
	w[0] = '\0';
	if (name == NULL)
		return;
	/* case f(x, y) * z */
	if (strlen(name) == 0 || name[strlen(name) - 1] != ')')
		return;

	/* case f((x)) */
	/* case f(x + dx) - f(x) */
	char *s = strstr(name, "(");
	if (s != NULL) {					// f(
		char arg[MAXCHAR] = "";
		parseFuncArg(arg, name);
		if (strlen(arg) == 0)
			return;
		strncpy(w, name, s - name + 1);
		w[s - name + 1] = '\0';
	} else
		w[0] = '\0';
}
void parseSymbName(char w[], char *name)
{
	char *prog = "parseSymbName";

	if (w == NULL)
		return;
	w[0] = '\0';
	if (name == NULL)
		return;
	/* case f(x, y) * z */
	/* case f(x + dx) - f(x) */

	char *s = strstr(name, "(");
	if (s != NULL) {
		parseFuncName(w, name);
		if (strlen(w) > 0) {
			fprintf(stderr, "%s: bcutstr: \"%s\"\t(before)\n", prog, w);
			bcutstr(w);
			fprintf(stderr, "%s: bcutstr: \"%s\"\t(after)\n", prog, w);
		}
	} else
		strcpy(w, name);
}

/* unaryop: "f(", "x", ")" ==> f(x) */
/* "-", "x", "" ==> -x */
void unaryop(char line[], char *pre, char *arg, char *suf)
{
	sprintf(line, "%s%s%s", pre, arg, suf);
}

/* binaryop: "a", " * ", "b" ==> a * b */
void binaryop(char line[], char *left, char *op, char *right)
{
	sprintf(line, "%s%s%s", left, op, right);
}

/* permutate: "a * b * c", " * " ==> "a * b * c
 * 									  a * c * b
 * 									  b * a * c
 * 									  b * c * a
 * 									  c * a * b
 * 									  c * b * a" */
/* line length should be long enough to conider all n! permutations */
void permutate(char line[], char *s, char *delim)
{
	line[0] = '\0';

	if (s == NULL || delim == NULL)
		return ;

	Node *root = NULL;
	char *p = s;
	while (strlen(p) > 0) {
		p = parseSV(line, p, delim);
		root = addNode(root, line);
	}
	int n = nodelen(root, 0);
	printf("node length: %d\n", n);
	genSV(line, root, delim);
	removeNode(root);
	root = NULL;
}
void testpermutate(void)
{
	char line[MAXCHAR] = "";
	permutate(line, "b * c * x * a * godzilla * kaizu", " * ");
	printf("%s\n", line);
}

#endif		// GETMATH_H
