#include <stdio.h>
#include <stddef.h>

typedef struct
{
	char *match;
	size_t match_idx;
	size_t match_len;
	size_t curr_match_len;
	char newc;
	int (*getchr)(void *);
	void *par;
} tape_ut;

int tape_push(tape_ut *tape, char *str, size_t match_idx );
void reset_tape(tape_ut *tape, int reset_flag );
void init_tape(tape_ut *tape, int (*getchr)(void *), void *par );
