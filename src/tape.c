#include "tape.h"

int tape_push(tape_ut *tape, char *str, size_t match_idx )
{

	int compres;

	if( tape->match_len == tape->curr_match_len )
	{
		if( tape->newc == 0 )
			tape->newc = tape->getchr(tape->par);
		if( str[tape->match_len] == 0 )
		{
			tape->match = str;
			tape->match_idx = match_idx;
		}
		if( tape->newc == str[tape->curr_match_len] )
		{
			tape->match = str;
			tape->newc = 0;
			tape->match_len++;
			tape->curr_match_len++;
			tape->match_idx = match_idx;
			return 0;
		}
		else
			return (int)str[tape->curr_match_len]-(int)tape->newc;
	}
	else //it should be always curr_match_len < match_len
	{
		if( str[tape->curr_match_len] == tape->match[tape->curr_match_len] )
		{
			tape->curr_match_len++;
			return 0;
		}
		else
			return (int)str[tape->curr_match_len]-(int)tape->match[tape->curr_match_len];
	}

	return compres;

}

void reset_tape(tape_ut *tape, int reset_flag ) 
{
	if( reset_flag )
	{
		tape->match_len = 0;
		tape->match = NULL;
	}
	tape->curr_match_len = 0;
}

void init_tape(tape_ut *tape, int (*getchr)(void *), void *par )
{
	tape->match = NULL;
	tape->match_len = 0;
	tape->curr_match_len = 0;
	tape->newc = 0;
	tape->getchr = getchr;
	tape->par = par;
}

