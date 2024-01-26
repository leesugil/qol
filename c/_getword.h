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

	for (i = n-m; i >= 0; i--) {
		p = line+i;
		if ((strstr(p, word)) != NULL)
			return p;
	}

	return NULL;
}
void teststrrstr(void)
{
	char *line = "((x + y) * (y + z))";
	char *word = ")";
	printf("line: \"%s\"\n", line);
	printf("word: \"%s\"\n", word);
	printf("strrstr: \"%s\"\n", strrstr(line, word));
}

/* strstrmaskblk: bulk strstrmask applied to l delimeter sets */
	/* not for math formula. this one detects the first and the last
	 * occurence of block parameters, fails to mask terms properly in
	 * some cases such as
	 * (x + y) * (y + z)
	 * which the middle operator '*' shouldn't be masked in the math sense */
char *strstrmaskblk(char *line, char *word, char **pre, char **suf, unsigned int l)
{
	char *p, *q, *r;
	int i, j = 0, c = 0;

	q = line + strlen(line);

	/* get the first occurence of **pre */
	for (i = 0; i < l; i++)
		if ((p = strstr(line, pre[i])) != NULL) {
			if (p < q) {
				fprintf(stderr, "strstrmaskblk: pre \"%s\" detected.\n", pre[i]);
				q = p;
				j = i;
			}
			if (c == 0)
				c++;
		}
	fprintf(stderr, "strstrmaskblk: pre[%d] =  \"%s\", detected at \"%s\".\n", j, pre[j], q);

	/* check if parentheses are properly placed? - future project. */

	/* count occurence of pre[j] and suf[j] */
	if ((p = strstr(line, pre[j]) + strlen(pre[j])) != NULL) {
		/* c = 1 already */
		while (c > 0) {
			q = strstr(p, pre[j]);
			r = strstr(p, suf[j]);
			/* q != NULL && r != NULL normal like  * (y + z) */
			/* q == NULL && r != NULL normal like y + z) */
			/* q != NULL && r == NULL error */
			/* q == NULL && r == NULL normal if c == 0 */
			if (r != NULL) {
				if (q != NULL) {
					if (q < r) {
						c++;
						p = q + strlen(pre[j]);
						fprintf(stderr, "strstrmaskblk: c=%d, p=\"%s\"\n", c, p);
					} else {
						c--;
						p = r + strlen(suf[j]);
						fprintf(stderr, "strstrmaskblk: c=%d, p=\"%s\"\n", c, p);
					}
				} else {
					/* like y + z) */
					/* shouldn't occur unless there were more pre[j] by a mistake? */
					fprintf(stderr, "strstrmaskblk: error, there were more %s. no masking applied.\n", pre[j]);
					return strstr(line, word);
				}
			} else {
				fprintf(stderr, "strstrmaskblk: error, at least %d more %s than %s. no masking applied.\n", c, pre[j], suf[j]);
				return strstr(line, word);
			}
		}
		/* p should be pointing right after the first block ended, i.e., where the op parsing should start */
		fprintf(stderr, "strstrmaskblk: line after block: \"%s\"\n", p);
		p = strstr(p, word);
		fprintf(stderr, "strstrmaskblk: returning \"%s\"\n", p);
		return p;
	} else {
		/* pre[j] never occurred */
		fprintf(stderr, "strstrmaskblk: no masking applied.\n");
		return strstr(line, word);
	}
}
void teststrstrmaskblk(void)
{
	char *line = "((x + y) + y) * (y + z)";
	char *word = "y";
	char *pre[] = { "(", "[", "{" };
	char *suf[] = { ")", "]", "}" };
	int i, l = sizeof(pre) / sizeof(pre[0]);

	printf("line: \"%s\"\n", line);
	printf("word: \"%s\"\n", word);
	printf("strstr: \"%s\"\n", strstr(line, word));
	for (i = 0; i < l; i++)
		printf("pre: \"%s\", suf: \"%s\"\n", pre[i], suf[i]);
	printf("teststrstrmaskblk: \"%s\"\n", strstrmaskblk(line, word, pre, suf, l));
}

/* strstrmask: mask part of the string with delimiters */
char *strstrmask(char *line, char *word, char *pre, char *suf)
{
	return strstrmaskblk(line, word, &pre, &suf, 1);
}
void teststrstrmask(void)
{
	char *line = "((x + y) * (y + z))";
	char *word = "y";
	char *pre = "(";
	char *suf = ")";

	printf("line: \"%s\"\n", line);
	printf("word: \"%s\"\n", word);
	printf("strstr: \"%s\"\n", strstr(line, word));
	printf("pre: \"%s\", suf: \"%s\"\n", pre, suf);
	printf("strstrmask: \"%s\"\n", strstrmask(line, word, pre, suf));
}

#endif	/* _GETWORD_H */
