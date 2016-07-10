#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <stdint.h>

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

//const uint32_t MAX_CMD_SIZE = 256;
const uint32_t MAX_PARAMS = 256;

typedef enum {
    ERR_INVALID_COMMAND = 1,
    ERR_NUM_PARAMS
} request_error_t;


typedef struct {
    const char* name;
    uint32_t params;
} command_t;

int parse_request(const char* request);

#endif
