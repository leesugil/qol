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
void testgetalnum(void);

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

/* wrapstr: places characters around a string */
char *wrapstr(char *word, char *pre, char *suf);
void testwrapstr(char *pre, char *suf);

/* parenthstr: abc -> (abc) */
char *parenthstr(char *word);
void testparenthstr(void);

/* brackstr: abd -> [abc] */
char *brackstr(char *word);
void testbrackstr(void);

/* bracestr: abd -> {abc} */
char *bracestr(char *word);
void testbracestr(void);

/* reverse: reverses a mutable string. for immutables, use with strdup. */
void reverse(char s[]);

/* strrstr: strstr reversed */
char *strrstr(char *line, char *word);
void teststrrstr(void);

/* strstrblk: get the first occurence among words */
char *strstrblk(char *line, char **words, unsigned int l, int *j);

/* pastblock: a((bc)de)fg -> fg */
char *pastblock(char *line, char **pre, char **suf, unsigned int l);
void testpastblock(void);

/* strstrmaskblk: bulk strstrmask applied to l delimeter sets */
char *strstrmaskblk(char *line, char *word, char **pre, char **suf, unsigned int l);
void teststrstrmaskblk(void);

/* strstrmask: mask part of the string with delimiters */
char *strstrmask(char *line, char *word, char *pre, char *suf);
void teststrstrmask(void);

#endif	/* GETWORD_H */
