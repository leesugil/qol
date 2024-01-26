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

/* wrapstr: places characters around a string */
char *wrapstr(char *word, char *pre, char *suf)
{
	unsigned int l = strlen(pre) + strlen(word) + strlen(suf) + 1;
	char output[l];
	int i, j = 0;

	sprintf(output, "%s%s%s", pre, word, suf);

	fprintf(stderr, "wrapword: *** strdup used in the return, free it after use ***\n");
	return strdup(output);
}
void testwrapstr(char *pre, char *suf)
{
	char *word = "test word";
	printf("input: \"%s\"\n", word);
	printf("output: \"%s\"\n", wrapstr(word, pre, suf));
}

/* parenthstr: abc -> (abc) */
char *parenthstr(char *word)
{
	return wrapstr(word, "(", ")");
}
void testparenthstr(void)
{
	char *word = "test word";
	printf("input: \"%s\"\n", word);
	printf("output: \"%s\"\n", parenthstr(word));
}

/* brackstr: abd -> [abc] */
char *brackstr(char *word)
{
	return wrapstr(word, "[", "]");
}
void testbrackstr(void)
{
	char *word = "test word";
	printf("input: \"%s\"\n", word);
	printf("output: \"%s\"\n", brackstr(word));
}

/* bracestr: abd -> {abc} */
char *bracestr(char *word)
{
	return wrapstr(word, "{", "}");
}
void testbracestr(void)
{
	char *word = "test word";
	printf("input: \"%s\"\n", word);
	printf("output: \"%s\"\n", bracestr(word));
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

/* strstrblk: get the first occurence among words */
char *strstrblk(char *line, char **words, unsigned int l, int *j)
{
	char *p, *q;
	int i;

	q = line + strlen(line);
	
	for (i = 0; i < l; i++)
		if ((p = strstr(line, words[i])) != NULL)
			if (p < q) {
				fprintf(stderr, "strstrblk: word \"%s\" detected.\n", words[i]);
				q = p;
				*j = i;
			}
	fprintf(stderr, "strstrblk: words[%d] =  \"%s\", detected at \"%s\".\n", *j, words[*j], q);
	return q;
}

/* pastblock: a((bc)de)fg -> fg */
char *pastblock(char *line, char **pre, char **suf, unsigned int l)
{
	char *p, *q, *r;
	int i, j = 0, c = 0;

	/* get the first occurence of **pre */
	q = strstrblk(line, pre, l, &j);
	fprintf(stderr, "strstrmaskblk: pre[%d] =  \"%s\", detected at \"%s\".\n", j, pre[j], q);

	/* check if parentheses are properly placed? - future project. */

	/* count occurence of pre[j] and suf[j] */
	if ((p = strstr(line, pre[j]) + strlen(pre[j])) != NULL) {
		c = 1;
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
					return line;
				}
			} else {
				fprintf(stderr, "strstrmaskblk: error, at least %d more %s than %s. no masking applied.\n", c, pre[j], suf[j]);
				return line;
			}
		}
		/* p should be pointing right after the first block ended, i.e., where the op parsing should start */
		fprintf(stderr, "strstrmaskblk: line after block: \"%s\"\n", p);
		return p;
	} else {
		/* pre[j] never occurred */
		fprintf(stderr, "strstrmaskblk: no masking applied.\n");
		return line;
	}
}
void testpastblock(void)
{
	char *line = "((x + y) + y) * (y + z)";
	char *word = "y";
	char *pre[] = { "(", "[", "{" };
	char *suf[] = { ")", "]", "}" };
	int i, l = sizeof(pre) / sizeof(pre[0]);

	printf("line: \"%s\"\n", line);
	for (i = 0; i < l; i++)
		printf("pre: \"%s\", suf: \"%s\"\n", pre[i], suf[i]);
	printf("testpastblock: \"%s\"\n", pastblock(line, pre, suf, l));
}

/* strstrmaskblk: bulk strstrmask applied to l delimeter sets */
char *strstrmaskblk(char *line, char *word, char **pre, char **suf, unsigned int l)
{
	/* the current code doesn't exactly does the job.
	 * if word appears ahead of the masked block,
	 * the current code doesn't catch that. */
	int j;
	char *p = pastblock(line, pre, suf, l);
	char *q = strstrblk(line, pre, l, &j);
	char *r = strstr(line, word);

	if (q < r) {
		/* strstr(line, word) could be wrong, need to apply strstr to p */
		return strstr(p, word);
	}
	return r;
}
void teststrstrmaskblk(void)
{
	char *line = "y * ((x + y) + y) * (y + z)";
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
