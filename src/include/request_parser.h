#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <stdint.h>
#include <limits.h>

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

//const uint32_t MAX_CMD_SIZE = 256;
const uint32_t MAX_PARAMS = 16;

typedef enum {
    ERR_INVALID_COMMAND = INT_MIN,
    ERR_NUM_PARAMS
} request_error_t;

/* typedef enum { */
/* 	CREATE_ACTION, */
/* 	KEY_VALUE_ACTION, */
/* 	KEY_ONLY_ACTION */
/* } action_t; */

typedef struct {
    const char* name;
    uint32_t params;
	//	void (*const action)(void);
	//	action_t action_type;
} command_t;

int execute_request(const char* request, hash_table_t* t);

#endif
