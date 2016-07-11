#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

const uint32_t MAX_PARAMS = 16;

typedef enum {
    ERR_INVALID_COMMAND = INT_MIN,
    ERR_NUM_PARAMS
} request_error_t;


/*
 * Struct containing command name
 * and number of parameters
 */
typedef struct {
    const char* name;
    uint32_t params;
} command_t;


/*
 * Parse request finding command and parameters
 * *** IMPORTANT ***
 * ALLOCATES LIST OF params THAT SHOULD BE
 * DEALLOCATED BY THE USER.
 *     RETURNS index of command in command_list
 * if successful or request_error_t otherwise
 */
int parse_request(const char* request, const command_t* command_list, size_t comm_list_size, char** params);

#endif
