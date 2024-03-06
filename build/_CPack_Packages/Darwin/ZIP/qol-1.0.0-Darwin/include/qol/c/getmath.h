#ifndef GETMATH_H
#define GETMATH_H

#include "qol/c/getword.h"

/* parseFuncArg: given a valid function form f(x, y), parses the argument part x, y. pre and suf are the block options { "(", "[", "{", NULL }
 * the current versions of
 * parseFuncArg, parseFuncName, parseSymbName
 * do not fully support all possible block options and
 * only support { "(", NULL } */
void parseFuncArg(char arg[], char *name);

void parseFuncName(char w[], char *name);

void parseSymbName(char w[], char *name);

/* unaryop: "f(", "x", ")" ==> f(x) */
/* "-", "x", "" ==> -x */
void unaryop(char line[], char *pre, char *arg, char *suf);

/* binaryop: "a", " * ", "b" ==> a * b */
void binaryop(char line[], char *left, char *op, char *right);

/* permutate: "a * b * c", " * " ==> "a * b * c
 * 									  a * c * b
 * 									  b * a * c
 * 									  b * c * a
 * 									  c * a * b
 * 									  c * b * a" */
/* line length should be long enough to conider all n! permutations */
void permutate(char line[], char *s, char *delim);

void testpermutate(void);

#endif		// GETMATH_H
