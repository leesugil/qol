#ifndef CLOCK_H
#define CLOCK_H

/* run at the beginning of the code */
void clock_start(void);
void sclock_start(char *);

/* run tat the end of the code before returning */
void clock_end(void);
void sclock_end(char *);

#endif	/* CLOCK_H */
