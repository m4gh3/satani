#include "parse.h"

value_ut *parse(context_ut *context, tape_ut *tape, value_ut *pvalue, size_t prec_level )
{

	value_ut *svalue = NULL;
	size_t match_idx;

	while(1)
	{

		int i = 0;
		int j = context->size-1;
		int m;
		while( i <= j )
		{
			m = ( ( j-i ) >> 1 ) + i;
			int compres = tape_push(tape, context->tokens[m].str, m );
			if( compres < 0 )
			{
				reset_tape(tape, 0 );
				i = m+1;
			}
			else if( compres > 0 )
			{
				reset_tape(tape, 0 );
				j = m-1;
			}
		}

		match_idx = tape->match_idx;

		if( tape->match == NULL || prec_level > context->tokens[match_idx].prec_level || tape->match[tape->match_len] )
		{
			//printf("error\n");
			return pvalue;
			//exit(EXIT_FAILURE);
		}
	
		reset_tape(tape, 1 );
		tape->match_idx = match_idx;

		if( context->tokens[match_idx].rec_context != NULL )
		{
			if( context->tokens[match_idx].fwd && context->tokens[match_idx].action != NULL )
			{
				pvalue = context->tokens[match_idx].action(context->tokens[match_idx].action_id, pvalue, NULL );
				pvalue = parse(context->tokens[match_idx].rec_context, tape, pvalue, /*context->tokens[match_idx].prec_level +*/ context->tokens[match_idx].new_prec );
			}
			else
				svalue = parse(context->tokens[match_idx].rec_context, tape, NULL, /*context->tokens[match_idx].prec_level +*/ context->tokens[match_idx].new_prec );
		}

		if( !context->tokens[match_idx].fwd && context->tokens[match_idx].action != NULL )
			pvalue = context->tokens[match_idx].action(context->tokens[match_idx].action_id, pvalue, svalue );

		if( context->tokens[match_idx].next_context == NULL )
			return pvalue;
		else
			context = context->tokens[match_idx].next_context;

	}

	return pvalue;

}
