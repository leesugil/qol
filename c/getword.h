/* this is an improved version of getword shown in the book that only utilizes the standard C libraries */

#ifndef GETWORD_H
#define GETWORD_H

#include "_getword.h"

/* getword: get next word or character from input */
int getword(char *word, int lim);
void testgetword();

/* sgetword: get next word from string while reducing it */
int sgetword(char **s, char *word, int lim);
void testsgetword(char *s);

/* getalnum: get next word or character or number from input */
int getalnum(char *word, int lim);
void testgetalnum();

/* sgetalnum: getalnum from string while reducing it */
int sgetalnum(char **s, char *word, int lim);
void testsgetalnum(char *s);

/* getwordg: getword generalized, accepting an arbitrary criteria of acceptable characters in word */
int getwordg(char *word, int lim, int (*crit)(char ));
void testgetwordg(int (*crit)(char ));

/* sgetwordg: getwordg from string while reducing it */
int sgetwordg(char **s, char *word, int lim, int (*crit)(char ));
void testsgetwordg(char *s, int (*crit)(char ));

/* ismathexpr: isalsnum + '.' + '-' */
int ismathexpr(char c);

/* shrkstr: removes the first and last character of a string */
char *shrkstr(char *);
void testshrkstr(void);

/* shrknstr: removes the first and last n characters of a string. */
char *shrknstr(char *s, unsigned int n);
void testshrknstr(unsigned int n);

#endif	/* GETWORD_H */
