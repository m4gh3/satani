#include "tape.h"

struct value_ut;
typedef struct value_ut value_ut;
struct context_ut;

typedef struct
{
	char *str;
	value_ut *(*action)(size_t action_id, value_ut *pvalue, value_ut *svalue );
	size_t action_id;
	int fwd;
	size_t prec_level;
	size_t new_prec;
	struct context_ut *next_context, *rec_context;
} token_ut;

typedef struct context_ut
{
	token_ut *tokens;
	size_t size;
} context_ut;

value_ut *parse(context_ut *context, tape_ut *tape, value_ut *pvalue, size_t prec_level );

#define mkcontext(name) context_ut name##_context = { .tokens = name##_tokens, .size = sizeof(name##_tokens)/sizeof(token_ut) };
