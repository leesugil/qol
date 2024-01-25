/* this is an improved version of getword shown in the book that only utilizes the standard C libraries */

#ifndef _GETWORD_H
#define _GETWORD_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while (isspace(c = getchar()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getchar())) {
			ungetc(*w, stdin);
			break;
		}
	*w = '\0';
	return word[0];
}

void testgetword()
{
	int maxchar = 100;
	char word[maxchar];
	while (getword(word, maxchar) != EOF)
		fprintf(stderr, "\"%s\"\n", word);
}

/* sgetword: get next word from string while reducing it */
int sgetword(char **s, char *word, int lim)
{
	int c;
	char *w = word;

	while (isspace(c = *(*s)++))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = *(*s)++)) {
			(*s)--;
			break;
		}
	*w = '\0';
	return word[0];
}

void testsgetword(char *s)
{
	int maxchar = 100;
	char word[maxchar];
	while (sgetword(&s, word, maxchar) != '\0')
		fprintf(stderr, "\"%s\"\n", word);
}

/* getalnum: get next word or character or number from input */
int getalnum(char *word, int lim)
{
	int c;
	char *w = word;

	while (isspace(c = getchar()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalnum(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getchar())) {
			ungetc(*w, stdin);
			break;
		}
	*w = '\0';
	return word[0];
}

void testgetalnum()
{
	int maxchar = 100;
	char word[maxchar];
	while (getalnum(word, maxchar) != EOF)
		fprintf(stderr, "\"%s\"\n", word);
}

/* sgetalnum: getalnum from string while reducing it */
int sgetalnum(char **s, char *word, int lim)
{
	int c;
	char *w = word;

	while (isspace(c = *(*s)++))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalnum(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = *(*s)++)) {
			(*s)--;
			break;
		}
	*w = '\0';
	return word[0];
}

void testsgetalnum(char *s)
{
	int maxchar = 100;
	char word[maxchar];
	while (sgetalnum(&s, word, maxchar) != '\0')
		fprintf(stderr, "\"%s\"\n", word);
}

int ismathexpr(char c)
{
	return isalnum(c) || (c == '.') || (c == '-');
}

/* getwordg: getword generalized */
int getwordg(char *word, int lim, int (*crit)(char ))
{
	int c;
	char *w = word;

	while (isspace(c = getchar()))
		;
	if (c != EOF)
		*w++ = c;
	if (!crit(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!crit(*w = getchar())) {
			ungetc(*w, stdin);
			break;
		}
	*w = '\0';
	return word[0];
}

void testgetwordg(int (*crit)(char ))
{
	int maxchar = 100;
	char word[maxchar];
	while (getwordg(word, maxchar, crit) != EOF)
		fprintf(stderr, "\"%s\"\n", word);
}

/* sgetwordg: getwordg from string while reducing it */
int sgetwordg(char **s, char *word, int lim, int (*crit)(char ))
{
	int c;
	char *w = word;

	while (isspace(c = *(*s)++))
		;
	if (c != EOF)
		*w++ = c;
	if (!crit(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!crit(*w = *(*s)++)) {
			(*s)--;
			break;
		}
	*w = '\0';
	return word[0];
}

void testsgetwordg(char *s, int (*crit)(char ))
{
	int maxchar = 100;
	char word[maxchar];
	while (sgetwordg(&s, word, maxchar, crit) != '\0')
		fprintf(stderr, "\"%s\"\n", word);
}

/* shrknstr: removes the first and last n characters of a string */
char *shrknstr(char *s, unsigned int n)
{
	int l = strlen(s) - 2 * n + 1;
	char output[l];
	int i;

	if (l > 0) {
		for (i = n; i < strlen(s) - n; i++)
			output[i-n] = s[i];
		output[i-n] = '\0';
		fprintf(stderr, "shrknstr: *** strdup used in the return, free it after use ***\n");
		return strdup(output);
	} else {
		fprintf(stderr, "shrknstr: error, n too large\n");
		return NULL;
	}
}
void testshrknstr(unsigned n)
{
	char *s = "123456789";
	printf("input: \"%s\", n = %u\n", s, n);
	printf("output: \"%s\"\n", shrknstr(s, n));
}

/* shrkstr: removes the first and last character of a string */
char *shrkstr(char *s)
{
	return shrknstr(s, 1);
}
void testshrkstr(void)
{
	testshrknstr(1);
}

/* wrapword: places characters around a string */
char *wrapword(char *word, char *pre, char *suf)
{
	unsigned int l = strlen(pre) + strlen(word) + strlen(suf) + 1;
	char output[l];
	int i, j = 0;

	sprintf(output, "%s%s%s", pre, word, suf);

	fprintf(stderr, "wrapword: *** strdup used in the return, free it after use ***\n");
	return strdup(output);
}
void testwrapword(char *pre, char *suf)
{
	char *word = "test word";
	printf("input: \"%s\"\n", word);
	printf("output: \"%s\"\n", wrapword(word, pre, suf));
}

/* parenthword: parenthesize a word */
char *parenthword(char *word)
{
	return wrapword(word, "(", ")");
}
void testparenthword(void)
{
	char *word = "test word";
	printf("input: \"%s\"\n", word);
	printf("output: \"%s\"\n", parenthword(word));
}

/* brackword: bracket a word */
char *brackword(char *word)
{
	return wrapword(word, "[", "]");
}
void testbrackword(void)
{
	char *word = "test word";
	printf("input: \"%s\"\n", word);
	printf("output: \"%s\"\n", brackword(word));
}

/* braceword: parenthesize a word */
char *braceword(char *word)
{
	return wrapword(word, "{", "}");
}
void testbraceword(void)
{
	char *word = "test word";
	printf("input: \"%s\"\n", word);
	printf("output: \"%s\"\n", braceword(word));
}

/* reverse: reverses a mutable string. for immutables, use with strdup. */
void reverse(char s[])
{
	int c, i, j;

	for (i=0, j=strlen(s)-1; i<j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}

/* strrstr: strstr reversed */
char *strrstr(char *line, char *word)
{
	int m = strlen(word), n = strlen(line);
	int i;
	char *p;

	for (i = n-m; i >= 0; i--, p = line+i)
		if ((strstr(p, word)) != NULL)
			return p;

	return NULL;
}
void teststrrstr(void)
{
	char *line = "Hello, World, Hello!";
	char *word = "Hello";
	printf("line: \"%s\"\n", line);
	printf("word: \"%s\"\n", word);
	printf("strrstr: \"%s\"\n", strrstr(line, word));
}

/* strstrmask: mask part of the string with delimiters */
char *strstrmask(char *line, char *word, char *pre, char *suf)
{
	char *pre_loc, *suf_loc;

	/* get the first occurence of *pre */
	if ((pre_loc = strstr(line, pre)) == NULL) {
		fprintf(stderr, "strstrmask: \"%s\" not detected.\n", pre);
		return strstr(line, word);
	}

	/* get the last occuruence of *suf */
	if ((suf_loc = strrstr(line, suf)) == NULL) {
		fprintf(stderr, "strstrmask: \"%s\" not detected.\n", suf);
		return strstr(line, word);
	}

	/* mask the block */
	if (pre_loc < suf_loc) {
		/* main code */
		return strstr(suf_loc, word);
	} else {
		fprintf(stderr, "strstrmask: suf(%s) appeearing ahead of pre(%s) in line(%s)\n", suf, pre, line);
		return strstr(line, word);
	}
}
void teststrstrmask(void)
{
	char *line = "Hello, (World), Hello!";
	char *word = "World";
	char *pre = "(";
	char *suf = ")";

	printf("line: \"%s\"\n", line);
	printf("word: \"%s\"\n", word);
	printf("strstr: \"%s\"\n", strstr(line, word));
	printf("pre: \"%s\", suf: \"%s\"\n", pre, suf);
	printf("strstrmask: \"%s\"\n", strstrmask(line, word, pre, suf));
}

#endif	/* _GETWORD_H */
