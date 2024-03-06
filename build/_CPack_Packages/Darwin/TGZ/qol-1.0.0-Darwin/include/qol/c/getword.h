/* this is an improved version of getword shown in the book that only utilizes the standard C libraries */

#ifndef GETWORD_H
#define GETWORD_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "qol/c/tree.h"

#define MAXCHAR 1024

/* getword: get next word or character from input */
int getword(char *word, int lim);
void testgetword(void);
	
/* sgetword: getword from string while moving pointer next to the word */
int sgetword(char **s, char *word, int lim);
void testsgetword(char *s);

/* getalnum: get next word or character or number from input */
int getalnum(char *word, int lim);
void testgetalnum(void);

/* sgetalnum: getalnum from string while moving pointer next to the word */
int sgetalnum(char **s, char *word, int lim);
void testsgetalnum(char *s);

/* ismathword: in addition to alnum, '.' and '-' should be understood as part of a "word" as a mathematical quantity */
int ismathword(char c);

/* ismathterm: a wrapper for ismathword */
int ismathterm(char c);

/* getwordg: getword generalized, accapting more criteria like crit=ismathword */
int getwordg(char *word, int lim, int (*crit)(char ));
void testgetwordg(int (*crit)(char ));

/* sgetwordg: getwordg from string while moving pointer next to the word */
int sgetwordg(char **s, char *word, int lim, int (*crit)(char ));
void testsgetwordg(char *s, int (*crit)(char ));

/* fcutnstr: cuts off the first n characters */
void fcutnstr(char s[], int n);
void testfcutnstr(int n);

/* fcutstr: fcutnstr( , 1) */
void fcutstr(char s[]);

/* bcutnstr: cuts of n characters from the back */
void bcutnstr(char s[], int n);
void testbcutnstr(int n);

/* bcutstr: bcutnstr( , 1) */
void bcutstr(char s[]);

/* shrknstr: removes the first and last n characters of a string */
void shrknstr(char s[], int n);
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
char *strstrblk(char *line, char **words, int *index);
void teststrstrblk(void);

/* countstrstr: counts number of times the search word occuring inside str */
int countstrstr(char *line, char *word);

/* is_blocked_properly: check if any blocks (such as "(" & ")", "[" & "]", or "{" & "}") are placed propely. returns TRUE if no blocks are detected as well. */
int is_blocked_properly(char line[], char *pre, char *suf);
void testis_blocked_properly(void);

/* is_blocked_properly_blk */
int is_blocked_properly_blk(char *line, char **pre, char **suf, int *index);
void testis_blocked_properly_blk(void);

/* is_outer_blocked: returns 1 if the redundant outer-most block is detected */
int is_outer_blocked(char *line, char *pre, char *suf);
void testis_outer_blocked(void);

/* is_outer_blocked_blk */
int is_outer_blocked_blk(char *line, char **pre, char **suf, int *index);
void testis_outer_blocked_blk(void);

/* remove_outer_block_blk */
void remove_outer_block_blk(char line[], char **pre, char **suf);
void testremove_outer_block_blk(void);

/* remove_outer_block */
void remove_outer_block(char line[], char *pre, char *suf);
void testremove_outer_block(void);

/* remove_outer_blockS: apply remove_outer_block indefinite times until outer blocks are completely removed */
void remove_outer_blocks(char line[], char *pre, char *suf);

/* remove_outer_blocks_blk */
void remove_outer_blocks_blk(char line[], char **pre, char **suf);

/* pastblock: ([a{bc}(d)e]fg) -> fg */
char *pastblock(char line[], char **pre, char **suf);
void testpastblock(void);

/* strstrmaskblk: strstr, but masking blocks specified by bulk (multiple) block indicators such as pre={ "(", "{", "[", NULL } & suf={ ")", "}", "]", NULL } */
char *strstrmaskblk(char line[], char *word, int *index, char **pre, char **suf);
void teststrstrmaskblk(void);

/* strstrmask: strstr with masking part of the string */
char *strstrmask(char line[], char *word, char *pre, char *suf);
void teststrstrmask(void);

/* strstrblkmaskblk: strstr with bulk search words, with respect to bulk masking words */
/* index return is for bulk_words */
char *strstrblkmaskblk(char line[], char **bulk_words, int *index, char **pre, char **suf);
void teststrstrblkmaskblk(void);

/* printn: print a string n times */
void printn(char *s, int n);

/* convertNegSign: "-x" --> "-1 * x" */
void convertNegSign(char s[]);

/* strtod2: strtod but keeps searching for numbers in a mixed string, until stop appears */
double strtod2(char *s, char *stop, char **endp);
void teststrtod2(void);

/* is_pure_number:
 * check if a string is one of the following three:
 * 1) pure number
 * 2) number first, followed by characters
 * 3) pure characters
 * returns 1 if pure number, 0 if pure characters, 2 for case 2), -1 for error */
int is_pure_number(char *s, char **endp);
void testis_pure_number(void);

/* strrstrblk: strstrblk reversed */
char *strrstrblk(char *line, char **words, int *index);
void teststrrstrblk(void);

/* strrstrmaskblk: strstrmaskblk reverse */
char *strrstrmaskblk(char line[], char *word, int *index, char **pre, char **suf);
void teststrrstrmaskblk(void);

/* strrstrmask: strstrmask reversed */
char *strrstrmask(char line[], char *word, char *pre, char *suf);
void teststrrstrmask(void);

/* countnonnum: counts non-number characters in a string */
// -1.2e34
int countnonnum(char *s);
void testcountnonnum(void);

/* replacestr: replaces string s with string r in a mutable string w */
int replacestr(char w[], char *s, char *r);
void testreplacestr(void);

/* parseSeperatedValue: like parsing values one at a time in CSV except the comma is generalized to any string. returns "" when all parsed */
char *parseSV(char w[], char *line, char *delimiter);

/* parseSVmask: parseSV with masking */
char *parseSVmask(char w[], char *line, char *delimiter, char *pre, char *suf);

/* parseSVmaskblk: parseSVmask with multiple masking variables */
char *parseSVmaskblk(char w[], char *line, char *delimiter, char **pre, char **suf);

/* genSV: generate a seperated-value-type string from a Node tree of strings seperated by delimiter */
void genSV(char w[], Node *node, char *delimiter);

#endif	/* GETWORD_H */
