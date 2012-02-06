#define NUM 2
#define ADD_TOKEN_NAME(TOKEN_NAMES, TOKEN) TOKEN_NAMES[TOKEN] = #TOKEN
const char *token_names[100];

struct number {
	unsigned long value;
};
