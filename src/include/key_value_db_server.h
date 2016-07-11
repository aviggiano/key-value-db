#ifndef KEY_VALUE_SERVER_DB_H
#define KEY_VALUE_SERVER_DB_H

#include <stdint.h>

#include "hash_table.h"

#define RESP_TOO_LONG_ERR -1

// 0 se ok, neg se erro
int execute_request(const char* request, char* response, size_t resp_len, hash_table_t* t);


void run_server_blocking(uint16_t port);

#endif
