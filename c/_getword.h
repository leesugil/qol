/* this is to provide useful shortcuts and wrapper functions for handling strings using the standard C library and POSIX functions.
 *
 * if possible, functions are written to prefer avoiding dynamically allocating memories.
 *
 * Sugil Steve Lee
 * */

#ifndef _GETWORD_H
#define _GETWORD_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXCHAR 1024

/* getword: get next word or character from input */
int getword(char *word, unsigned int lim)
{
	int c = 0;
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
void testgetword(void)
{
	char word[MAXCHAR] = "";
	while (getword(word, MAXCHAR) != EOF)
		fprintf(stderr, "\"%s\"\n", word);
}

/* sgetword: get next word from string while reducing it */
int sgetword(char **s, char *word, unsigned int lim)
{
	int c = 0;
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
	printf("s=\"%s\"\n", s);
	char word[MAXCHAR] = "";
	while (sgetword(&s, word, MAXCHAR) != '\0')
		printf("\"%s\"\n", word);
}

/* getalnum: get next word or character or number from input */
int getalnum(char *word, unsigned int lim)
{
	int c = 0;
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
void testgetalnum(void)
{
	char word[MAXCHAR] = "";
	while (getalnum(word, MAXCHAR) != EOF)
		fprintf(stderr, "\"%s\"\n", word);
}

/* sgetalnum: getalnum from string while reducing it */
int sgetalnum(char **s, char *word, unsigned int lim)
{
	int c = 0;
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
	printf("s=\"%s\"\n", s);
	char word[MAXCHAR] = "";
	while (sgetalnum(&s, word, MAXCHAR) != '\0')
		fprintf(stderr, "\"%s\"\n", word);
}

/* ismathword: in addition to alnum, '.' and '-' should be understood as part of a "word" as a mathematical quantity */
int ismathword(char c)
{
	return isalnum(c) || (c == '.') || (c == '-');
}

/* getwordg: getword generalized */
int getwordg(char *word, unsigned int lim, int (*crit)(char ))
{
	int c = 0;
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
	char word[MAXCHAR] = "";
	while (getwordg(word, MAXCHAR, crit) != EOF)
		fprintf(stderr, "\"%s\"\n", word);
}

/* sgetwordg: getwordg from string while reducing it */
int sgetwordg(char **s, char *word, unsigned int lim, int (*crit)(char ))
{
	int c = 0;
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
	char word[MAXCHAR] = "";
	while (sgetwordg(&s, word, MAXCHAR, crit) != '\0')
		fprintf(stderr, "\"%s\"\n", word);
}

/* fcutnstr: cuts off the first n characters */
void fcutnstr(char s[], unsigned int n)
{
	if (s != NULL && n < strlen(s)) {
		/*s += n;*/
		int i;

		for (i = 0; i < strlen(s) - n; i++)
			s[i] = s[i+n];
		s[i] = '\0';
	}
}
void testfcutnstr(int n)
{
	char line[MAXCHAR] = "foo bar";
	
	printf("line: \"%s\"\n", line);
	printf("n: %d\n", n);
	fcutnstr(line, n);
	printf("testfcutnstr: \"%s\"\n", line);
}

void fcutstr(char s[])
{
	fcutnstr(s, 1);
}

/* bcutnstr: cuts of n characters from the back */
void bcutnstr(char s[], unsigned int n)
{
	char *prog = "bcutnstr";
	unsigned int m = strlen(s);

	if (s == NULL || m <= n)
		;
	else
		s[m - n] = '\0';
}
void testbcutnstr(int n)
{
	char line[MAXCHAR] = "foo bar";

	printf("line: \"%s\"\n", line);
	printf("n: %d\n", n);
	bcutnstr(line, n);
	printf("testbcutnstr: \"%s\"\n", line);
}

void bcutstr(char s[])
{
	bcutnstr(s, 1);
}

/* shrknstr: removes the first and last n characters of a string */
void shrknstr(char s[], unsigned int n)
{
	fcutnstr(s, n);
	bcutnstr(s, n);
}
void testshrknstr(int n)
{
	char s[MAXCHAR] = "123456789";
	printf("input: \"%s\", n = %d\n", s, n);
	shrknstr(s, n);
	printf("testshrknstr: \"%s\"\n", s);
}

/* shrkstr: abcde -> bcd */
void shrkstr(char s[])
{
	shrknstr(s, 1);
}
void testshrkstr(void)
{
	char s[MAXCHAR] = "123456789";
	printf("input: \"%s\"\n", s);
	shrkstr(s);
	printf("testshrkstr: \"%s\"\n", s);
}

/* wrapstr: abc -> (p)abc(s) */
void wrapstr(char s[], char *pre, char *suf)
{
	char *prog = "wrapstr";

	sprintf(s, "%s%s%s", pre, s, suf);
}
void testwrapstr(void)
{
	char s[MAXCHAR] = "test word";
	char *pre = "foo";
	char *suf = "bar";

	printf("input: \"%s\"\n", s);
	wrapstr(s, pre, suf);
	printf("testwrapstr: \"%s\"\n", s);
}

/* parenthstr: abc -> (abc) */
void parenthstr(char s[])
{
	wrapstr(s, "(", ")");
}
void testparenthstr(void)
{
	char s[MAXCHAR] = "test word";
	printf("input: \"%s\"\n", s);
	parenthstr(s);
	printf("testparenthstr: \"%s\"\n", s);
}

/* brackstr: abc -> [abc] */
void brackstr(char s[])
{
	wrapstr(s, "[", "]");
}
void testbrackstr(void)
{
	char s[MAXCHAR] = "test word";
	printf("input: \"%s\"\n", s);
	brackstr(s);
	printf("testbrackstr: \"%s\"\n", s);
}

/* bracestr: abc -> {abc} */
void bracestr(char s[])
{
	wrapstr(s, "{", "}");
}
void testbracestr(void)
{
	char s[MAXCHAR] = "test word";
	printf("input: \"%s\"\n", s);
	bracestr(s);
	printf("testbracestr: \"%s\"\n", s);
}

/* reverse: reverses a mutable string. */
void reverse(char s[])
{
	int c, i, j;

	for (i=0, j=strlen(s)-1; i<j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}

/* strrstr: strstr reversed */
char *strrstr(char *line, char *word)
{
	char dum_line[MAXCHAR] = "";
	strcpy(dum_line, line);					/* 0123456789 */
	reverse(dum_line);						/* 9876543210 */

	char dum_word[MAXCHAR] = "";
	strcpy(dum_word, word);					/* ......67.. */
	reverse(word);							/* ..76...... */

	char *p = strstr(dum_line, dum_word);	/* ..76543210 */
											/*   34     0 */
	if (p != NULL) {
		int n = (p - dum_line) + strlen(dum_word);
		n = strlen(dum_line) - n;
		return (0 < n && n < strlen(line) && strstr(line + n, word) != NULL) ? line + n : NULL;
	}

	return NULL;
}
void teststrrstr(void)
{
	char *line = "01234567890123456789";
	char *word = "678";
	printf("line: \"%s\"\n", line);
	printf("word: \"%s\"\n", word);
	printf("strrstr: \"%s\"\n", strrstr(line, word));
}

/* strstrblk: strstr against bulk search words such as { "search", "word1", "word2", NULL } and returning the first occurence of any of them */
char *strstrblk(char *line, char **words, unsigned int *index)
{
	char *p, *q = line + strlen(line);

	for (int i = 0; words[i] != NULL; i++)
		if ((p = strstr(line, words[i])) != NULL)
			if (p < q) {
				fprintf(stderr, "strstrblk: word \"%s\" detected.\n", words[i]);
				q = p;
				*index = i;
			}
	fprintf(stderr, "strstrblk: words[%d] =  \"%s\", detected at \"%s\".\n", *index, words[*index], q);
	return q;
}
void teststrstrblk(void)
{
	char *line = "abc 123 def 456 ghi 789";
	char *words[] = { "def", "456", NULL };
	unsigned int i = 0;

	printf("input: \"%s\"\n", line);
	printf("words: {");
	for (int j = 0; words[j] != NULL; j++)
		printf("\"%s\" ", words[j]);
	printf("}\n");
	printf("index=%d\n", i);
	printf("teststrstrblk: \"%s\", index=%u\n", strstrblk(line, words, &i), i);
}

/* pastblock: ([a{bc}(d)e]fg) -> fg */
char *pastblock(char line[], char **pre, char **suf)
{
	char *prog = "pastblock";
	char *p, *q, *r;
	unsigned int i = 0;
	int c = 0;

	/* get the first occurence of **pre */
	p = strstrblk(line, pre, &i);	/* returns NULL if not found */
	fprintf(stderr, "%s: pre[%d] =  \"%s\", detected at \"%s\".\n", prog, i, pre[i], p);

	/* check if parentheses are properly placed? - future project.
	 * part of it is implemented in the loop below. */

	/* count occurence of pre[i] and suf[i] */
	if (p != NULL) {
		/* pre[i] exists in line (c++), so the same number of suf[i] must exist as well */
		/* p = p + strlen(pre[i])
		 * from p, look for pre and suf. - (1)
		 * if pre appears, c++, p = current location + strlen(pre[i]).
		 * if suf appears, c--, p = current location + strlen(suf[i]).
		 * if c == 0, the first pre[i] is now closed, return.
		 * go back to (1) */
		c = 1;
		p += strlen(pre[i]);
		while (c > 0) {
			q = strstr(p, pre[i]);
			r = strstr(p, suf[i]);
			/* q == NULL && r == NULL normal if c == 0 */
			/* q == NULL && r != NULL normal like y + z) */
			/* q != NULL && r == NULL error */
			/* q != NULL && r != NULL normal, keep updating c */
			if (q == NULL) {
				if (r == NULL) {
					/* q == NULL && r == NULL  implies c == 0 */
					/* so reaching here means error */
					fprintf(stderr, "%s: error, c=%d, but no more \"%s\" and \"%s\". check if blocks are made properly.\n", prog, c, pre[i], suf[i]);
					return NULL;
				} else {
					/* q == NULL && r != NULL normal like y + z) */
					/* when ((ab)c) is provided, the code will convert it into (ab)c first. */
					fprintf(stderr, "%s: error, there were more %s. there's a chance that the entire line is blocked. checking if it's the case...\n", prog, suf[i]);
					/* check if the case is true. otherwise return NULL */
					if (line == strstr(line, pre[i]) &&
							line + strlen(line) - strlen(suf[i]) == strstr(line, suf[i])) {
						fprintf(stderr, "%s: the case is true, removing the block indicators\n", prog);
						fcutnstr(line, strlen(pre[i]));
						bcutnstr(line, strlen(suf[i]));
						return pastblock(line, pre, suf);
					} else
						return NULL;
				}
			} else {
				if (r == NULL) {
					/* q != NULL && r == NULL error */
					/* more pre[i] than suf[i] for sure */
					fprintf(stderr, "%s: error, there are more \"%s\" than \"%s\" for sure, please revise the input.\n", prog, pre[i], suf[i]);
					return NULL;
				} else {
					/* q != NULL && r != NULL normal, keep updating c */
					if (q < r) {
						/* pre[i] detected first */
						c++;
						p = q + strlen(pre[i]);
						fprintf(stderr, "%s: c=%d, p=\"%s\"\n", prog, c, p);
					} else {
						/* suf[i] detected first */
						c--;
						p = r + strlen(suf[i]);
						fprintf(stderr, "%s: c=%d, p=\"%s\"\n", prog, c, p);
					}
				}
			}
		}
		if (c == 0) {
			/* code ran properly */
			fprintf(stderr, "%s: result found:\n%s", p, line);
			for (int i = 0; i < p - line; i++)
				fprintf(stderr, " ");
			fprintf(stderr, "%s\n", p);
			return p;
		} else {
			/* c < 0? impossible */
			fprintf(stderr, "%s: c=%d<0, impossible outcome. contact sugilmath at gmail dot com\n", prog, c);
			return NULL;
		}
	} else {
		/* pre doesn't exist in line, no block to skip */
		return line;
	}
}
void testpastblock(void)
{
	char line[MAXCHAR] = "(((x + y) + y) * (y + z))";
	char *word = "y";
	char *pre[] = { "(", "[", "{", NULL };
	char *suf[] = { ")", "]", "}", NULL };

	printf("line: \"%s\"\n", line);
	printf("testpastblock: \"%s\"\n", pastblock(line, pre, suf));
}

/* strstrmaskblk: strstr, but masking blocks specified by bulk (multiple) block indicators such as pre={ "(", "{", "[", NULL } & suf={ ")", "}", "]", NULL } */
char *strstrmaskblk(char line[], char *word, char **pre, char **suf)
{
	/* mission: make this function yield a pointer inside line (so that we can to pointer arithmetic with the outcome), and also, if possible, leave no dynamically allocated memories un-freed. */
	/* mission accomplished. */
	/* ((x + y) + (y + z)) */
	char *prog = "strstrmaskblk";

	if (line == NULL || word == NULL)
		return NULL;

	fprintf(stderr, "%s: checking if \"%s\" exists in \"%s\"\n", prog, word, line);
	char *r = strstr(line, word);

	if (r == NULL) {
		fprintf(stderr, "%s: nothing found.\n", prog);
		return NULL;
	}

	fprintf(stderr, "%s: potential keyword found, checking if there are blocks to be masked...\n", prog);
	unsigned int index = 0;
	char *q = strstrblk(line, pre, &index);
	if (q != NULL)
		if (q < r) {
			/* block entry found ahead of the first primary operator */
			fprintf(stderr, "%s: block found before the search word, masking the block\n", prog);
			char *p = pastblock(line, pre, suf);
			fprintf(stderr, "%s: searching \"%s\" after the block as in \"%s\"\n", prog, word, p);
			return strstr(p, word);
		}

	fprintf(stderr, "%s: \"%s\" masking was not needed\n", prog, word);
	return r;
}
void teststrstrmaskblk(void)
{
	char line[MAXCHAR] = "((x + y) + y)^(y + z)";
	char *word = " + ";
	char *pre[] = { "(", "[", "{", NULL };
	char *suf[] = { ")", "]", "}", NULL };
	int i;

	printf("line: \"%s\"\n", line);
	printf("word: \"%s\"\n", word);
	printf("strstr: \"%s\"\n", strstr(line, word));
	printf("teststrstrmaskblk: \"%s\"\n", strstrmaskblk(line, word, pre, suf));
}

/* strstrmask: strstr with masking part of the string */
char *strstrmask(char line[], char *word, char *pre, char *suf)
{
	char *pre2[] = { pre, NULL };
	char *suf2[] = { suf, NULL };
	return strstrmaskblk(line, word, pre2, suf2);
}
void teststrstrmask(void)
{
	char line[MAXCHAR] = "((x + y) * (y + z))";
	char *word = "y";
	char *pre = "(";
	char *suf = ")";

	printf("line: \"%s\"\n", line);
	printf("word: \"%s\"\n", word);
	printf("strstr: \"%s\"\n", strstr(line, word));
	printf("pre: \"%s\", suf: \"%s\"\n", pre, suf);
	printf("teststrstrmask: \"%s\"\n", strstrmask(line, word, pre, suf));
}

#endif	/* _GETWORD_H */
