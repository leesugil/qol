/* this is an improved version of getword shown in the book that only utilizes the standard C libraries */

#ifndef GETWORD_H
#define GETWORD_H

#include "_getword.h"

/* getword: get next word or character from input */
int getword(char *word, unsigned int lim);
void testgetword(void);
	
/* sgetword: getword from string while moving pointer next to the word */
int sgetword(char **s, char *word, unsigned int lim);
void testsgetword(char *s);

/* getalnum: get next word or character or number from input */
int getalnum(char *word, unsigned int lim);
void testgetalnum(void);

/* sgetalnum: getalnum from string while moving pointer next to the word */
int sgetalnum(char **s, char *word, unsigned int lim);
void testsgetalnum(char *s);

/* ismathword: in addition to alnum, '.' and '-' should be understood as part of a "word" as a mathematical quantity */
int ismathword(char c);

/* getwordg: getword generalized, accapting more criteria like crit=ismathword */
int getwordg(char *word, unsigned int lim, int (*crit)(char ));
void testgetwordg(int (*crit)(char ));

/* sgetwordg: getwordg from string while moving pointer next to the word */
int sgetwordg(char **s, char *word, unsigned int lim, int (*crit)(char ));
void testsgetwordg(char *s, int (*crit)(char ));

/* fcutnstr: cuts off the first n characters */
void fcutnstr(char s[], unsigned int n);
void testfcutnstr(int n);

/* fcutstr: fcutnstr( , 1) */
void fcutstr(char s[]);

/* bcutnstr: cuts of n characters from the back */
void bcutnstr(char s[], unsigned int n);
void testbcutnstr(int n);

/* bcutstr: bcutnstr( , 1) */
void bcutstr(char s[]);

/* shrknstr: removes the first and last n characters of a string */
void shrknstr(char s[], unsigned int n);
void testshrknstr(int n);

/* shrkstr: shrknstr( , 1) */
void shrkstr(char s[]);
void testshrkstr(void);

/* wrapstr: abc -> (p)abc(s) */
void wrapstr(char s[], char *pre, char *suf);
void testwrapstr(void);

/* parenthstr: abc -> (abc) */
void parenthstr(char s[]);
void testparenthstr(void);

/* brackstr: abc -> [abc] */
void brackstr(char s[]);
void testbrackstr(void);

/* bracestr: abc -> {abc} */
void bracestr(char s[]);
void testbracestr(void);

/* reverse: reverses a mutable string. */
void reverse(char s[]);

/* strrstr: strstr reversed, searching the last occurence of the keyword */
char *strrstr(char *line, char *word);
void teststrrstr(void);

/* strstrblk: strstr against bulk search words such as { "search", "word1", "word2", NULL } and returning the first occurence of any of them */
char *strstrblk(char *line, char **words, unsigned int *index);
void teststrstrblk(void);

/* pastblock: ([a{bc}(d)e]fg) -> fg */
char *pastblock(char line[], char **pre, char **suf);
void testpastblock(void);

/* strstrmaskblk: strstr, but masking blocks specified by bulk (multiple) block indicators such as pre={ "(", "{", "[", NULL } & suf={ ")", "}", "]", NULL } */
char *strstrmaskblk(char line[], char *word, char **pre, char **suf);
void teststrstrmaskblk(void);

/* strstrmask: strstr with masking part of the string */
char *strstrmask(char line[], char *word, char *pre, char *suf);
void teststrstrmask(void);

#endif	/* GETWORD_H */
