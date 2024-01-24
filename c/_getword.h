/* this is an improved version of getword shown in the book that only utilizes the standard C libraries */

#ifndef _GETWORD_H
#define _GETWORD_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

#endif	/* _GETWORD_H */
