#include "../src/parse.h"
#include <stdlib.h>

enum type_id_ut
{
	lvalue,
	rvalue
};

struct value_ut
{
	enum type_id_ut type_id;
	union
	{
		int s_int;
	} val;
};

int lvalues[4] = { 1, 2, 3, 4 };

context_ut num_context;
context_ut prefix_context;
context_ut op_context;
context_ut close_context;

value_ut *read_num(size_t action_id, value_ut *pvalue, value_ut *svalue )
{

	if( pvalue == NULL )
	{
		pvalue = malloc(sizeof(value_ut));
		pvalue->val.s_int = 0;
		pvalue->type_id = rvalue;
	}

	if( 0 <= action_id && action_id <= 9 )
		pvalue->val.s_int = pvalue->val.s_int * 10 + action_id;
	
	return pvalue;

}

value_ut *minus_num(size_t action_id, value_ut *pvalue, value_ut *svalue )
{
	svalue->val.s_int*=-1;
	return svalue;
}

value_ut *op_num(size_t action_id, value_ut *pvalue, value_ut *svalue )
{
	if( svalue == NULL )
	{
		printf("Syntax error\n");
		exit(EXIT_FAILURE);
	}
	if(pvalue->type_id == lvalue)
	{
		pvalue->val.s_int = lvalues[pvalue->val.s_int];
		pvalue->type_id = rvalue;
	}
	if(svalue->type_id == lvalue)
	{
		svalue->val.s_int = lvalues[svalue->val.s_int];
		svalue->type_id = rvalue;
	}
	switch( action_id )
	{
		case 0:
			pvalue->val.s_int += svalue->val.s_int;
			break;
		case 1:
			pvalue->val.s_int -= svalue->val.s_int;
			break;
		case 2:
			pvalue->val.s_int *= svalue->val.s_int;
			break;
		case 3:
			pvalue->val.s_int /= svalue->val.s_int;
			break;
		case 4:
			pvalue->val.s_int %= svalue->val.s_int;
			break;
	}
	free(svalue);
	return pvalue;
}

value_ut *sval_forw(size_t action_id, value_ut *pvalue, value_ut *svalue )
{ return svalue; }

value_ut *read_var(size_t action_id, value_ut *pvalue, value_ut *svalue )
{
	pvalue = malloc(sizeof(value_ut));
	pvalue->val.s_int = action_id;
	pvalue->type_id = lvalue;
	return pvalue;
}

value_ut *assign(size_t action_id, value_ut *pvalue, value_ut *svalue )
{
	if( pvalue == NULL || svalue == NULL || pvalue->type_id != lvalue )
	{
		printf("Syntax error\n");
		exit(EXIT_FAILURE);
	}
	if(svalue->type_id == lvalue)
		svalue->val.s_int = lvalues[svalue->val.s_int];
	lvalues[pvalue->val.s_int] = svalue->val.s_int;
	free(svalue);
	return pvalue;
}

value_ut *print_value(size_t action_id, value_ut *pvalue, value_ut *svalue )
{
	if(pvalue != NULL)
	{
		if(pvalue->type_id == lvalue)
		{
			pvalue->val.s_int = lvalues[pvalue->val.s_int];
			pvalue->type_id = rvalue;
		}
		printf("%d\n", pvalue->val.s_int );
		free(pvalue);
	}
	return NULL;
}
// .str, .action, .action_id, .fwd, .prec_level, .prec_inc, .next_context, .rec_context

token_ut prefix_tokens[] =
{
	(token_ut){ "\n", NULL,	0, 0, 4, 0, &prefix_context, NULL },
	(token_ut){ " " , NULL,	0, 0, 4, 0, &prefix_context, NULL },
	(token_ut){ "(", sval_forw, 0, 0, 4, 0, &close_context, &prefix_context },
	(token_ut){ "-", minus_num, 0, 0, 4, 4, &op_context, &num_context },
	(token_ut){ "0", read_num, 0, 1, 4, 4, &op_context, &num_context },
	(token_ut){ "1", read_num, 1, 1, 4, 4, &op_context, &num_context },
	(token_ut){ "2", read_num, 2, 1, 4, 4, &op_context, &num_context },
	(token_ut){ "3", read_num, 3, 1, 4, 4, &op_context, &num_context },
	(token_ut){ "4", read_num, 4, 1, 4, 4, &op_context, &num_context },
	(token_ut){ "5", read_num, 5, 1, 4, 4, &op_context, &num_context },
	(token_ut){ "6", read_num, 6, 1, 4, 4, &op_context, &num_context },
	(token_ut){ "7", read_num, 7, 1, 4, 4, &op_context, &num_context },
	(token_ut){ "8", read_num, 8, 1, 4, 4, &op_context, &num_context },
	(token_ut){ "9", read_num, 9, 1, 4, 4, &op_context, &num_context },
	(token_ut){ ";", NULL, 0, 0, 0, 0, NULL, NULL },
	(token_ut){ "a", read_var, 0, 0, 4, 4, &op_context, NULL },
	(token_ut){ "b", read_var, 1, 0, 4, 4, &op_context, NULL },
	(token_ut){ "c", read_var, 2, 0, 4, 4, &op_context, NULL },	
	(token_ut){ "d", read_var, 3, 0, 4, 4, &op_context, NULL },	

};

token_ut num_tokens[] =
{
	(token_ut){ "0", read_num, 0, 0, 4, 4, &num_context, NULL },
	(token_ut){ "1", read_num, 1, 0, 4, 4, &num_context, NULL },
	(token_ut){ "2", read_num, 2, 0, 4, 4, &num_context, NULL },
	(token_ut){ "3", read_num, 3, 0, 4, 4, &num_context, NULL },
	(token_ut){ "4", read_num, 4, 0, 4, 4, &num_context, NULL },
	(token_ut){ "5", read_num, 5, 0, 4, 4, &num_context, NULL },
	(token_ut){ "6", read_num, 6, 0, 4, 4, &num_context, NULL },
	(token_ut){ "7", read_num, 7, 0, 4, 4, &num_context, NULL },
	(token_ut){ "8", read_num, 8, 0, 4, 4, &num_context, NULL },
	(token_ut){ "9", read_num, 9, 0, 4, 4, &num_context, NULL }
};

token_ut op_tokens[] =
{
	(token_ut){ "\n", NULL, 0, 0, 4, 0, &op_context, NULL },
	(token_ut){ " " , NULL,	0, 0, 4, 0, &op_context, NULL },
	(token_ut){ "%", op_num, 4, 0, 3, 4, &op_context, &prefix_context },
	(token_ut){ "*", op_num, 2, 0, 3, 4, &op_context, &prefix_context },
	(token_ut){ "+", op_num, 0, 0, 2, 3, &op_context, &prefix_context },
	(token_ut){ "-", op_num, 1, 0, 2, 3, &op_context, &prefix_context },
	(token_ut){ "/", op_num, 3, 0, 3, 4, &op_context, &prefix_context },
	(token_ut){ ";", print_value, 0, 0, 0, 0, &prefix_context, NULL },
	(token_ut){ "=", assign, 0, 0, 1, 1, &op_context, &prefix_context }
};

token_ut close_tokens[] =
{ (token_ut){ ")", NULL, 0, 0, 3, 3, &op_context, NULL } };

mkcontext(prefix)
mkcontext(num)
mkcontext(op)
mkcontext(close)

int main()
{

	tape_ut tape;
	init_tape(&tape, fgetc, stdin );
	value_ut *val = parse(&prefix_context, &tape, NULL, 0 );	
	return 0;

}