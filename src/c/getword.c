/* this is to provide useful shortcuts and wrapper functions for handling strings using the standard C library and POSIX functions.
 *
 * if possible, functions are written to prefer avoiding dynamically allocating memories.
 *
 * Sugil Steve Lee
 * */

#include "qol/c/getword.h"

/* getword: get next word or character from input */
int getword(char *word, int lim)
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
int sgetword(char **s, char *word, int lim)
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
int getalnum(char *word, int lim)
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
int sgetalnum(char **s, char *word, int lim)
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

int ismathterm(char c)
{
	return ismathword(c);
}

/* getwordg: getword generalized */
int getwordg(char *word, int lim, int (*crit)(char ))
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
int sgetwordg(char **s, char *word, int lim, int (*crit)(char ))
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
void fcutnstr(char s[], int n)
{
	if (s != NULL && n <= strlen(s)) {
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

/* fcutstr: fcutstr( , 1) */
void fcutstr(char s[])
{
	fcutnstr(s, 1);
}

/* bcutnstr: cuts of n characters from the back */
void bcutnstr(char s[], int n)
{
	char *prog = "bcutnstr";
	int m = strlen(s);

	if (s == NULL || m < n)
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

void firstnstr(char s[], int n)
{
	bcutnstr(s, strlen(s) - n);
}
void lastnstr(char s[], int n)
{
	fcutnstr(s, strlen(s) - n);
}

/* shrknstr: removes the first and last n characters of a string */
void shrknstr(char s[], int n)
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
	char tmp[MAXCHAR] = "";

	strcpy(tmp, s);
	sprintf(s, "%s%s%s", pre, tmp, suf);
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
	char *prog = "strrstr";
	char dum_line[MAXCHAR] = "";
	strcpy(dum_line, line);					/* 0123456789 */
	reverse(dum_line);						/* 9876543210 */

	char dum_word[MAXCHAR] = "";
	strcpy(dum_word, word);					/* ......67.. */
	reverse(dum_word);							/* ..76...... */

	char *p = strstr(dum_line, dum_word);	/* ..76543210 */
											/*   34     0 */
	if (p != NULL) {
		int n = (p - dum_line) + strlen(dum_word);
		n = strlen(dum_line) - n;
		return (0 <= n && n <= strlen(line) && strstr(line + n, word) != NULL) ? line + n : NULL;
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
char *strstrblk(char *line, char **words, int *index)
{
	char *prog = "strstrblk";
	char *p, *q = line + strlen(line);

	if (line == NULL || words == NULL) {
		fprintf(stderr, "%s: NULL condition(s)\n", prog);
		return NULL;
	}

	for (int i = 0; words[i] != NULL; i++)
		if ((p = strstr(line, words[i])) != NULL)
			if (p < q) {
				fprintf(stderr, "strstrblk: word \"%s\" detected.\n", words[i]);
				q = p;
				if (index != NULL)
					*index = i;
			}
	if (strcmp(q, "") != 0) {
		if (index != NULL)
			fprintf(stderr, "%s: words[%d]=\"%s\", detected at \"%s\".\n", prog, *index, words[*index], q);
		return q;
	} else {
		if (index != NULL) {
			*index = -1;
			fprintf(stderr, "%s: words[%d]=\"%s\" not detected, returning NULL\n", prog, *index, words[*index]);
		}
		return NULL;
	}
}
void teststrstrblk(void)
{
	char *line = "abc 123 def 456 ghi 789";
	char *words[] = { "456", "ghi", "def", NULL };
	int i = 0;

	printf("input: \"%s\"\n", line);
	printf("words: { ");
	for (int j = 0; words[j] != NULL; j++)
		printf("\"%s\", ", words[j]);
	printf("\b\b }\n");
	printf("index=%d\n", i);
	printf("teststrstrblk: \"%s\", index=%u\n", strstrblk(line, words, &i), i);
}

/* countstrstr: counts number of times the search word occuring inside str */
int countstrstr(char *line, char *word)
{
	char *prog = "countstrstr";
	int n = 0;
	char *p = line;
	
	fprintf(stderr, "%s: n:%d, word=%s, p=%s\n", prog, n, word, p);
	while ((p = strstr(p, word)) != NULL) {
		fprintf(stderr, "%s: n:%d, word=%s, p=%s\n", prog, n, word, p);
		p += strlen(word);
		n++;
		fprintf(stderr, "%s: => n:%d, word=%s, p=%s\n", prog, n, word, p);
	}

	return n;
}
void testcountstrstr(void)
{
	char *line = "((x + y) * z)";
	char *word = "(";

	printf("input:%s\n", line);
	printf("word:%s\n", word);
	printf("testcountstrstr:%d\n", countstrstr(line, word));
}

/* is_blocked_properly: check if any blocks (such as "(" & ")", "[" & "]", or "{" & "}") are placed propely. */
// returns TRUE if no blocks are detected as well
int is_blocked_properly(char line[], char *pre, char *suf)
{
	char *prog = "is_blocked_properly";

	fprintf(stderr, "%s: (start) \"%s\" \"%s\" \"%s\"\n", prog, pre, suf, line);

	char *p = strstr(line, pre);

	if (p != NULL) {
		int c = 0;
		char *q = NULL, *r = NULL;

		while (p != NULL && c >= 0) {
			q = strstr(p, pre);
			r = strstr(p, suf);
			fprintf(stderr, "%s: p=\"%s\"\n", prog, p);
			if (q != NULL && r != NULL) {
				if (q < r) {
					/* pre appears first */
					p = q + strlen(pre);
					c++;
				} else {
					/* suf appears first */
					p = r + strlen(suf);
					c--;
				}
			} else if (q == NULL && r != NULL) {
				/* pre depleted */
				p = r + strlen(suf);
				c--;
			} else if (q != NULL && r == NULL) {
				/* suf depleted only, shouldn't happen */
				p = q + strlen(pre);
				c++;
			} else
				p = NULL;
		}

		if (c == 0) {
			fprintf(stderr, "%s: pass\n", prog);
			return 1;
		}
	} else if (strstr(line, suf) == NULL) {
		// no blocks detected, clean.
		fprintf(stderr, "%s: pass\n", prog);
		return 1;
	}

	fprintf(stderr, "%s: fail\n", prog);
	return 0;
}
void testis_blocked_properly(void)
{
	char line1[MAXCHAR] = "([(foo)-(]bar))";
	// the function would not detect such false case yet - future project
	char line2[MAXCHAR] = "(((foo)-(bar))";
	char *pre = "(";
	char *suf = ")";

	printf("input: %s\n", line1);
	printf("testis_blocked_properly: %d\n", is_blocked_properly(line1, pre, suf));

	printf("input: %s\n", line2);
	printf("testis_blocked_properly: %d\n", is_blocked_properly(line2, pre, suf));

	char line3[MAXCHAR] = ")foo-bar(";
	printf("input: %s\n", line3);
	printf("testis_blocked_properly: %d\n", is_blocked_properly(line2, pre, suf));
}

/* is_blocked_properly_blk */
int is_blocked_properly_blk(char *line, char **pre, char **suf, int *index)
{
	char *prog = "is_blocked_properly_blk";

	if (line == NULL || pre == NULL || suf == NULL)
		return 0;

	if (index != NULL)
		*index = -1;
	
	char *p = NULL;
	int i, output = 1;

	// the test condition should be "for all"
	for (i = 0; pre[i] != NULL || suf[i] != NULL; i++) {
		output *= is_blocked_properly(line, pre[i], suf[i]);
		if (output == 0) {
			// failed
			if (index != NULL) {
				fprintf(stderr, "%s: \"%s\" \"%s\" \"%s\" failed\n", prog, pre[i], suf[i], line);
				*index = i;
			}
			return 0;
		}
	}

	return 1;
}
void testis_blocked_properly_blk(void)
{
	char *line = "is (this line [properly blocked)?]";
	// this will not be captured in the current version of the function yet
	line = "(is this line properly blocked?)";
	char *pre[] = {
		"(",
		"[",
		"{",
		NULL
	};
	char *suf[] = {
		")",
		"]",
		"}",
		NULL
	};
	int index = 0;

	printf("input:\"%s\"\n", line);
	printf("testis_blocked_properly_blk:%d\n", is_blocked_properly_blk(line, pre, suf, &index));

	line = "is (this line [properly blocked]?";
	printf("input:\"%s\"\n", line);
	printf("testis_blocked_properly_blk:%d\n", is_blocked_properly_blk(line, pre, suf, &index));
}

/* is_outer_blocked: 1 if the redundant outer-most block is detected */
int is_outer_blocked(char *line, char *pre, char *suf)
{
	char *prog = "is_outer_blocked";

	fprintf(stderr, "%s: (start) \"%s\" \"%s\" \"%s\"\n", prog, pre, suf, line);

	if (line != NULL && pre != NULL && suf != NULL) {
		fprintf(stderr, "%s: checking if blocked properly\n", prog);
		if (is_blocked_properly(line, pre, suf)) {
			fprintf(stderr, "%s: (pass) checking if blocked properly\n", prog);
			// "[" "]" "2 * ((5 + 6) * z)"
			char *p = strstr(line, pre);
			char *q = strrstr(line, suf);
			char *r = NULL;
			if (p == NULL || q == NULL)
				return 0;
			if (strcmp(line, p) == 0 && strcmp("", q + strlen(suf)) == 0) {
				/* line starting and ending with pre, suf, respectively */
				/* (x + (x + y) * z) */
				/* (x + y) * (y + z) */
				/* c = 0 at some point
				 * ==> no outer block */
				/* boundaries, c > 0, and, at some point, countstrstr(p, pre) == 0 and countstrstr(p, suf) == 1
				 * ==> outer block */
				int c = 0, entry = 1;
				while (c > 0 || entry == 1) {
					entry = 0;
					fprintf(stderr, "%s: p=\"%s\"\n", prog, p);
					q = strstr(p, pre);
					r = strstr(p, suf);
					if (q != NULL && r != NULL) {
						if (q < r) {
							p = q + strlen(pre);
							c++;
						} else {
							p = r + strlen(suf);
							c--;
						}
					}
					if (q != NULL && r == NULL) {
						/* impossible */
						p = q + strlen(pre);
						c++;
					}
					if (q == NULL && r != NULL) {
						/* shouldn't this be the end? */
						//p = r + strlen(suf);
						//c--;
						fprintf(stderr, "%s: pass\n", prog);
						return 1;
					}
					if (q == NULL && r == NULL) {
						fprintf(stderr, "%s: fail\n", prog);
						return 0;
					}
				}
			}
		} else
			fprintf(stderr, "%s: (fail) checking if blocked properly\n", prog);
	}

	fprintf(stderr, "%s: fail\n", prog);
	return 0;
}
void testis_outer_blocked(void)
{
	char *line = "(x + y) * (y + z)";
	char *pre = "(";
	char *suf = ")";

	printf("input: %s\n", line);
	printf("pre: %s\n", pre);
	printf("suf: %s\n", suf);
	printf("testis_outer_blocked: %d\n", is_outer_blocked(line, pre, suf));

	line = "(x * (x + y) * z)";
	printf("\ninput: %s\n", line);
	printf("pre: %s\n", pre);
	printf("suf: %s\n", suf);
	printf("testis_outer_blocked: %d\n", is_outer_blocked(line, pre, suf));

	line = "((x + y) * z)";
	printf("\ninput: %s\n", line);
	printf("pre: %s\n", pre);
	printf("suf: %s\n", suf);
	printf("testis_outer_blocked: %d\n", is_outer_blocked(line, pre, suf));

	line = "(x * (x + y))";
	printf("\ninput: %s\n", line);
	printf("pre: %s\n", pre);
	printf("suf: %s\n", suf);
	printf("testis_outer_blocked: %d\n", is_outer_blocked(line, pre, suf));
}

/* is_outer_blocked_blk */
int is_outer_blocked_blk(char *line, char **pre, char **suf, int *index)
{
	if (line == NULL || pre == NULL || suf == NULL)
		return 0;

	if (index != NULL)
		*index = -1;
	
	char *p = NULL;
	int i, output = 0;

	// test "there exists"
	for (i = 0; pre[i] != NULL || suf[i] != NULL; i++) {
		output += is_outer_blocked(line, pre[i], suf[i]);
		if (output == 1) {
			if (index != NULL)
				*index = i;
			return 1;
		}
	}

	return 0;
}
void testis_outer_blocked_blk(void)
{
	char *line = "[is this line outer-blocked?]";
	char *pre[] = {
		"(",
		"[",
		"{",
		NULL
	};
	char *suf[] = {
		")",
		"]",
		"}",
		NULL
	};
	int index = 0;

	printf("input:\"%s\"\n", line);
	printf("testis_outer_blocked_blk:%d\n", is_outer_blocked_blk(line, pre, suf, &index));
}

/* remove_outer_block_blk */
void remove_outer_block_blk(char line[], char **pre, char **suf)
{
	char *prog = "remove_outer_block_blk";

	fprintf(stderr, "%s: (start) \"%s\"\n", prog, line);
	
	if (line != NULL && pre != NULL && suf != NULL) {
		/* obtain the left-most block opening */
		char *p = NULL;
		int index = 0;

		p = strstrblk(line, pre, &index);

		fprintf(stderr, "%s: check if blocked properly\n", prog);
		/* test is_blocked_properly */
		if (is_blocked_properly(line, pre[index], suf[index])) {
			fprintf(stderr, "%s: (pass) check if blocked properly\n", prog);
			/* test if outer block exists */
			fprintf(stderr, "%s: check if outer-blocked\n", prog);
			if (is_outer_blocked(line, pre[index], suf[index])) {
				/* fcutnstr, bcutnstr */
				fprintf(stderr, "%s: (pass) check if outer-blocked\n", prog);
				fprintf(stderr, "%s: removing the outer block \"%s\" \"%s\"\n", prog, pre[index], suf[index]);
				fcutnstr(line, strlen(pre[index]));
				bcutnstr(line, strlen(suf[index]));
				fprintf(stderr, "%s: removed the outer block\n", prog);
			} else
				fprintf(stderr, "%s: (fail) check if outer-blocked\n", prog);
		} else
			fprintf(stderr, "%s: (fail) check if blocked properly\n", prog);
	}
	fprintf(stderr, "%s: (end) \"%s\"\n", prog, line);
}
void testremove_outer_block_blk(void)
{
	char line[MAXCHAR] = "<!--get rid of this comment!-->";
	char *pre[] = {
		"<!--",
		NULL
	};
	char *suf[] = {
		"-->",
		NULL
	};

	printf("input: \"%s\"\n", line);
	remove_outer_block_blk(line, pre, suf);
	printf("testremove_outer_block_blk: \"%s\"\n", line);
}

/* remove_outer_block */
void remove_outer_block(char line[], char *pre, char *suf)
{
	char *pre2[] = {
		pre,
		NULL
	};
	char *suf2[] = {
		suf,
		NULL
	};
	remove_outer_block_blk(line, pre2, suf2);
}
void testremove_outer_block(void)
{
	char line[MAXCHAR] = "<!--get rid of this comment!-->";
	char *pre = "<!--";
	char *suf = "-->";

	printf("input: \"%s\"\n", line);
	remove_outer_block(line, pre, suf);
	printf("testremove_outer_block: \"%s\"\n", line);
}

/* remove_outer_blockS: apply remove_outer_block indefinite times until outer blocks are completely removed */
void remove_outer_blocks(char line[], char *pre, char *suf)
{
	while (is_outer_blocked(line, pre, suf))
		remove_outer_block(line, pre, suf);
}

/* remove_outer_blocks_blk */
void remove_outer_blocks_blk(char line[], char **pre, char **suf)
{
	while (is_outer_blocked_blk(line, pre, suf, NULL))
		remove_outer_block_blk(line, pre, suf);
}


/* pastblock: ([a{bc}(d)e]fg) -> fg */
char *pastblock(char line[], char **pre, char **suf)
{
	char *prog = "pastblock";

	fprintf(stderr, "%s: (start) \"%s\"\n", prog, line);

	char *p = NULL;

	// (1) check if properly blocked, return NULL if fails
	// (2) check if outer blocks are removed, return NULL if fails
	// (3) detect the earliest occuring b_start
	// (4) c = 1, p = strstr(line, pre[i]) + strlen(pre[i])
	// (5) because of (1) & (2), c == 0 at the end. return it.
	
	// (1) check if properly blocked (bulk), return NULL if fails
	int index = 0;
	if (is_blocked_properly_blk(line, pre, suf, &index)) {
		index = 0;
	// (2) check if outer blocks are removed, return NULL if fails
		while (is_outer_blocked_blk(line, pre, suf, &index))
			remove_outer_block_blk(line, pre, suf);
	}

	// (3) detect the earliest occuring b_start
	index = 0;
	p = strstrblk(line, pre, &index);
	if (p == NULL)
		return NULL;

	// (4) c = 1, p = strstr(line, pre[i]) + strlen(pre[i])
	int c = 0;
	char *q, *r;
	fprintf(stderr, "%s: (target) c=%d, \"%s\" \"%s\" %s\n", prog, c, pre[index], suf[index], p);
	while (c >= 0) {
		q = strstr(p, pre[index]);
		r = strstr(p, suf[index]);
		if (q != NULL && r != NULL) {
			if (q < r) {
				p = q + strlen(pre[index]);
				c++;
			} else {
				p = r + strlen(suf[index]);
				c--;
				if (c == 0)
					c = -1;
			}
		}
		if (q != NULL && r == NULL) {
			return NULL;
		}
		if (q == NULL && r != NULL) {
			p = r + strlen(suf[index]);
			c--;
			if (c == 0)
				c = -1;
		}
		if (q == NULL && r == NULL) {
	// (5) because of (1) & (2), c == 0 at the end. return it.
			if (c == 0)
				c = -1;
			else
				return NULL;
		}
		fprintf(stderr, "%s: c=%d, \"%s\" \"%s\" %s\n", prog, c, pre[index], suf[index], p);
	}

	return p;
}
void testpastblock(void)
{
	//char line[MAXCHAR] = "[[[x + y] + y] * [y + z]]";
	//char line[MAXCHAR] = "(a * (b - c) / d) / y";
	char line[MAXCHAR] = "(b / d) - (c / d)";
	char *pre[] = { "(", "[", "{", NULL };
	char *suf[] = { ")", "]", "}", NULL };

	printf("line: \"%s\"\n", line);
	printf("testpastblock: \"%s\"\n", pastblock(line, pre, suf));
}

/* strstrmaskblk: strstr, but masking blocks specified by bulk (multiple) block indicators such as pre={ "(", "{", "[", NULL } & suf={ ")", "}", "]", NULL } */
char *strstrmaskblk(char line[], char *word, int *index, char **pre, char **suf)
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

	char *q = strstrblk(line, pre, index);
	if (q != NULL)
		if (q < r) {
			/* block entry found ahead of the first primary operator */
			fprintf(stderr, "%s: block found before the search word, masking the block\n", prog);
			char *p = pastblock(line, pre, suf);
			if (p != NULL) {
				fprintf(stderr, "%s: searching \"%s\" after the block as in \"%s\"\n", prog, word, p);
				return strstrmaskblk(p, word, index, pre, suf);
			} else {
				fprintf(stderr, "%s: error, please revise the input string format.\n", prog);
				return NULL;
			}
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
	int i = 0;

	printf("line: \"%s\"\n", line);
	printf("word: \"%s\"\n", word);
	printf("strstr: \"%s\"\n", strstr(line, word));
	printf("teststrstrmaskblk: \"%s\"\n", strstrmaskblk(line, word, &i, pre, suf));
}

/* strstrmask: strstr with masking part of the string */
char *strstrmask(char line[], char *word, char *pre, char *suf)
{
	char *pre2[] = { pre, NULL };
	char *suf2[] = { suf, NULL };
	int index = 0;

	return strstrmaskblk(line, word, &index, pre2, suf2);
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

/* strstrblkmaskblk: strstr with bulk search words, with respect to bulk masking words */
/* index return is for bulk_words */
char *strstrblkmaskblk(char line[], char **bulk_words, int *index, char **pre, char **suf)
{
	char *prog = "strstrblkmaskblk";
	char *p, *q = NULL;
	int dummy_index = 0;

	for (int i = 0; bulk_words[i] != NULL; i++) {
		p = strstrmaskblk(line, bulk_words[i], &dummy_index, pre, suf);
		if (q == NULL || (p != NULL && p < q)) {
			q = p;
			if (index != NULL)
				*index = i;
			fprintf(stderr, "%s: updating q=\"%s\"\n", prog, q);
		}
	}

	return q;
}
void teststrstrblkmaskblk(void)
{
	char *prog = "teststrstrblkmaskblk";
	//char line[MAXCHAR] = "([(x + y) + z] * {x + (y + z)})";
	/*char *words[] = {
		" + ",
		" - ",
		" * ",
		" / ",
		" % ",
		"^",
		NULL
	};*/
	char line[MAXCHAR] = " = ";
	char *words[] = {
		" = ",
		NULL
	};
	char *pre[] = {
		"(",
		"[",
		"{",
		NULL
	};
	char *suf[] = {
		")",
		"]",
		"}",
		NULL
	};
	int index = 0;

	printf("input: %s\n", line);
	//printf("%s: %s\n", prog, strstrblkmaskblk(line, words, &index, pre, suf));
	printf("%s: %s\n", prog, strstrblkmaskblk(line, words, &index, NULL, NULL));
}

/* printn: print a string n times */
void printn(char *s, int n)
{
	for (int i = 0; i < n; i++)
		printf("%s", s);
}

/* convertNegSign: "-x" --> "-1 * x" */
void convertNegSign(char s[])
{
	if (strcmp(s, "") == 0)
		return;
	if (strlen(s) < 2)
		return;
	if (s[0] == '-') {
		char t[MAXCHAR] = "";
		strncpy(t, s, 2);
		t[2] = '\0';
		if (strtod(t, NULL) == 0) {
			strcpy(t, "-1 * ");
			strcat(t, s+1);
			strcpy(s, t);
		}
	}
}

/* strtod2: strtod but keeps searching for numbers in a mixed string, until stop appears */
double strtod2(char *s, char *stop, char **endp)
{
	double output = strtod(s, endp);

	if (strcmp(s, *endp) != 0)
		return output;
	// scan next
	if (strcmp(stop, "") == 0)
		stop = NULL;
	while (strcmp(s, *endp) == 0 &&
			strlen(s) > 0) {
		if (stop != NULL &&
				strcmp(s, strstr(s, stop)) == 0)
			break;
		s++;
		output = strtod(s, endp);
	}
	return output;
}
void teststrtod2(void)
{
	//char *line = "1.1 -2 -4e-2 -3^2";
	//char *line = "1.1 -2 -4e-2";
	//char *line = "-2 * 3 * a * 7 * -1";
	char *line = "(-1 * (a + b)) * -1 / 2 * c";
	char *p = line;
	double num = 0;
	char *stop = "";

	printf("line:%s\n", line);

	printf("stop:\"%s\"\n", stop);
	int c = 1;
	while (c > 0) {
		p = line;
		num = strtod2(line, stop, &line);
		printf("line:%s (before)\n", p);
		printf("line:%s (after)\n", line);
		c = line - p;
		printf("%g\n", num);
	}

	stop = " / ";
	printf("change of stop to \"%s\"\n", stop);
	line = "(-1 * (a + b)) * -1 / 2 * c";
	p = line;
	num = 0;
	c = 1;
	while (c > 0) {
		p = line;
		num = strtod2(line, stop, &line);
		printf("line:%s (before)\n", p);
		printf("line:%s (after)\n", line);
		c = line - p;
		printf("%g\n", num);
	}
}

/* is_pure_number:
 * check if a string is one of the following three:
 * 1) pure number
 * 2) number first, followed by characters
 * 3) pure characters
 * returns 1 if pure number, 0 if pure characters, 2 for case 2), -1 for error */
int is_pure_number(char *s, char **endp)
{
	char *prog = "is_pure_number";

	fprintf(stderr, "%s: (start) \"%s\"\n", prog, s);

	if (s == NULL)
		return -1;

	char *p = s;
	double value = 0;

	value = strtod(s, &p);
	if (endp != NULL)
		*endp = p;
	if (strlen(p) == 0) {
		fprintf(stderr, "%s: (end) \"%s\" is a pure number\n", prog, s);
		return 1;
	}
	if (strcmp(s, p) == 0) {
		fprintf(stderr, "%s: (end) \"%s\" is made of pure characters\n", prog, s);
		return 0;
	}

	fprintf(stderr, "%s: (end) \"%s\" is a number-character composite\n", prog, s);
	return 2;
}
void testis_pure_number(void)
{
	char *s = "4";
	char *p = NULL;

	printf("s:%s\n", s);
	printf("n:%d\n", is_pure_number(s, &p));
	printf("p:%s\n", p);
}

/* strrstrblk: strstrblk reversed */
char *strrstrblk(char *line, char **words, int *index)
{
	char *prog = "strrstrblk";
	char *p, *q = line;

	if (line == NULL || words == NULL) {
		return NULL;
	}

	for (int i = 0; words[i] != NULL; i++)
		if ((p = strstr(line, words[i])) != NULL)
			if (q < p) {
				q = p;
				if (index != NULL)
					*index = i;
			}
	if (strcmp(q, line) != 0) {
		return q;
	} else {
		if (index != NULL)
			*index = -1;
		return NULL;
	}
}
void teststrrstrblk(void)
{
	char *line = "abc 123 def 456 ghi 789";
	char *words[] = { "456", "ghi", "def", NULL };
	int i = 0;

	printf("input: \"%s\"\n", line);
	printf("words: { ");
	for (int j = 0; words[j] != NULL; j++)
		printf("\"%s\", ", words[j]);
	printf("\b\b }\n");
	printf("index=%d\n", i);
	printf("teststrrstrblk: \"%s\", index=%u\n", strrstrblk(line, words, &i), i);
}

/* strrstrmaskblk: strstrmaskblk reverse */
char *strrstrmaskblk(char line[], char *word, int *index, char **pre, char **suf)
{
	char *prog = "strrstrmaskblk";

	if (line == NULL || word == NULL)
		return NULL;

	// reverse line
	char liner[MAXCHAR] = "";
	strcpy(liner, line);
	reverse(liner);

	// reverse word
	char wordr[MAXCHAR] = "";
	strcpy(wordr, word);
	reverse(wordr);

	// reverse pre
	int i;
	for (i = 0; pre[i] != NULL; i++)
		;
	char *prer[i+1];
	for (int j = 0; j < i; j++) {
		prer[j] = strdup(pre[j]);
		reverse(prer[j]);
	}
	prer[i] = NULL;

	// reverse suf
	for (i = 0; suf[i] != NULL; i++)
		;
	char *sufr[i+1];
	for (int j = 0; j < i; j++) {
		sufr[j] = strdup(suf[j]);
		strcpy(sufr[j], suf[j]);
		reverse(sufr[j]);
	}
	sufr[i] = NULL;

	// strstrmaskblk with reversed text
	char *p = strstrmaskblk(liner, wordr, index, sufr, prer);
	// line:  abXY(-cdXY-)
	// word:  XY
	// pre: { "(-", "{-", "[-", NULL }
	// suf: { "-)", "-}", "-]", NULL }
	//
	// liner: )-YXdc-(YXba
	// wordr: YX
	// prer: { "-(", "-{", "-[", NULL }
	// sufr: { ")-", "}-", "]-", NULL }
	//
	// p:     ********YXba
	// p + strlen(wordr):
	//        **********ba
	// n = strlen(p + strlen(wordr));
	// q = line + n:
	//        **XY(-cdXY-)
	if (p == NULL)
		return NULL;
	int n = strlen(p + strlen(wordr));

	for (i = 0; pre[i] != NULL; i++)
		;
	for (int j = 0; j < i; j++) {
		free(prer[j]);
	}
	free(prer[i]);
	for (i = 0; suf[i] != NULL; i++)
		;
	for (int j = 0; j < i; j++) {
		free(sufr[j]);
	}
	free(sufr[i]);


	return line + n;
}
void teststrrstrmaskblk(void)
{
	char line[MAXCHAR] = "((x + y) + y)^(y + z)";
	char *word = " + ";
	char *pre[] = { "(", "[", "{", NULL };
	char *suf[] = { ")", "]", "}", NULL };
	int i = 0;

	printf("line: \"%s\"\n", line);
	printf("word: \"%s\"\n", word);
	printf("strstr: \"%s\"\n", strstr(line, word));
	printf("teststrrstrmaskblk: \"%s\"\n", strrstrmaskblk(line, word, &i, pre, suf));
}

/* strrstrmask: strstrmask reversed */
char *strrstrmask(char line[], char *word, char *pre, char *suf)
{
	char *pre2[] = { pre, NULL };
	char *suf2[] = { suf, NULL };

	return strrstrmaskblk(line, word, NULL, pre2, suf2);
}
void teststrrstrmask(void)
{
	char line[MAXCHAR] = "((x + y) * (y + z))";
	char *word = "y";
	char *pre = "(";
	char *suf = ")";

	printf("line: \"%s\"\n", line);
	printf("word: \"%s\"\n", word);
	printf("strrstr: \"%s\"\n", strrstr(line, word));
	printf("pre: \"%s\", suf: \"%s\"\n", pre, suf);
	printf("teststrrstrmask: \"%s\"\n", strrstrmask(line, word, pre, suf));
}

/* countnonnum: counts non-number characters in a string */
// -1.2e34
int countnonnum(char *s)
{
	int n = 0;
	double dum;
	char *p;

	while (*s != '\0') {
		dum = strtod(s, &p);
		if (strcmp(s, p) == 0) {
			s++;
			n++;
		} else
			s = p;
	}

	return n;
}
void testcountnonnum(void)
{
	char *line = "x * (3 * y) * 2";

	printf("%s\n", line);
	printf("%d\n", countnonnum(line));
}

int replacestr(char w[], char *s, char *r)
{
	char *p = w, *pp = p;
	char line[MAXCHAR] = "", output[MAXCHAR] = "";
	int n = 0;

	while (p != NULL) {
		pp = p;					// previous p
		strcpy(line, pp);
		p = strstr(p, s);		// n = p - pp
		if (p != NULL) {
			n++;
			firstnstr(line, p - pp);
			strcat(output, line);
			strcat(output, r);
			p += strlen(s);
		}
	}

	strcat(output, pp);
	strcpy(w, output);

	return n;
}
void testreplacestr(void)
{
	char w[MAXCHAR] = "";
	strcpy(w, "foo, bar!");
	printf("%s\n", w);
	replacestr(w, "oo", "^@@^");
	printf("%s\n", w);
}

/* parseSeperatedValue: like parsing values one at a time in CSV except the comma is generalized to any string. returns "" when all parsed */
char *parseSV(char w[], char *line, char *delimiter)
{
	w[0] = '\0';
	if (line == NULL || delimiter == NULL || strlen(delimiter) == 0)
		return line;
	strcpy(w, line);
	char *p = strstr(line, delimiter);
	if (p == NULL)
		return line + strlen(line);
	bcutnstr(w, strlen(p));
	return p + strlen(delimiter);
}

/* parseSVmask: parseSV with masking */
char *parseSVmask(char w[], char *line, char *delimiter, char *pre, char *suf)
{
	w[0] = '\0';
	if (line == NULL || delimiter == NULL || strlen(delimiter) == 0)
		return line;
	strcpy(w, line);
	char *p = strstrmask(line, delimiter, pre, suf);
	if (p == NULL)
		return line + strlen(line);
	bcutnstr(w, strlen(p));
	return p + strlen(delimiter);
}

/* parseSVmaskblk: parseSVmask with multiple masking variables */
char *parseSVmaskblk(char w[], char *line, char *delimiter, char **pre, char **suf)
{
	char *prog = "parseSVmaskblk";

	w[0] = '\0';
	if (line == NULL || delimiter == NULL || strlen(delimiter) == 0)
		return line;
	strcpy(w, line);
	while (is_outer_blocked_blk(w, pre, suf, NULL))
		remove_outer_block_blk(w, pre, suf);
	fprintf(stderr, "%s: input \"%s\"\n", prog, w);
	char *p = strstrmaskblk(line, delimiter, NULL, pre, suf);
	if (p == NULL)
		return line + strlen(line);
	bcutnstr(w, strlen(p));
	fprintf(stderr, "%s: parsed \"%s\"\n", prog, w);
	return p + strlen(delimiter);
}

void _genSV(char w[], Node *node, char *delimiter);
void genSV(char w[], Node *node, char *delimiter)
{
	char *prog = "genSV";

	w[0] = '\0';
	if (delimiter == NULL)
		delimiter = "";
	_genSV(w, node, delimiter);
	if (strlen(w) > strlen(delimiter)) {
		fprintf(stderr, "%s: bcutnstr: \"%s\"\t(before)\n", prog, w);
		bcutnstr(w, strlen(delimiter));
		fprintf(stderr, "%s: bcutnstr: \"%s\"\t(after)\n", prog, w);
	}
}
void _genSV(char w[], Node *node, char *delimiter)
{
	if (node == NULL)
		return ;
	_genSV(w, node->left, delimiter);
	while (node->count-- > 0) {
		strcat(w, node->name);
		strcat(w, delimiter);
	}
	_genSV(w, node->right, delimiter);
}
