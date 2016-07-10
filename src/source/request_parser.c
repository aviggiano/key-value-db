#include "request_parser.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "hash_table.h"

#define UNKNOWN_COMMAND -1

inline int is_whitespace(const char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

inline void skip_whitespaces(const char* str, size_t* index) {
    while (is_whitespace(str[*index]))
	(*index)++;
}

int parse_command(const char* request, size_t* index, const command_t* command_list, size_t comm_list_size) {
    size_t initial_i = *index;
    // find end of command
    while (!is_whitespace(request[*index]) &&
	     request[*index] != '\0') {
	(*index)++;
    }

    // check command list
    for (size_t i = 0; i < comm_list_size; i++) {
	if (strncmp(command_list[i].name, &request[initial_i], *index - initial_i) == 0)
	    return i;
    }
    
    return UNKNOWN_COMMAND;
}

char* parse_param(const char* request, size_t* index) {
    size_t initial_i = *index;
    int ignore_whitespaces = 0;

    while (request[*index] != '\0') { //TODO: check no parmas
	// param contains spaces
	if (request[*index] == '\"')
	    ignore_whitespaces = !ignore_whitespaces;

	// end of param
        if (!ignore_whitespaces && is_whitespace(request[*index]))
	    break;

	(*index)++;
    }

    size_t param_len = *index - initial_i;
    if (param_len == 0)
	return NULL;
    
    return strndup(&request[initial_i], param_len);
}

int parse_request(const char* request, const command_t* command_list, size_t comm_list_size, char** params) {
    size_t index = 0;

    skip_whitespaces(request, &index);

    // parse command
    int command = parse_command(request, &index, command_list, comm_list_size);
    if (command == UNKNOWN_COMMAND)
	return ERR_INVALID_COMMAND;
    //printf("command %i index %lu\n", command, index);
    
    skip_whitespaces(request, &index);

    // parse params
    uint32_t params_num = command_list[command].params;
    for (size_t i = 0; i < params_num; i++) {
	params[i] = parse_param(request, &index);

	// not enough params
        if (params[i] == NULL) {
	    for (size_t j = 0; j < i; j++)
		free(params[j]);

	    return ERR_NUM_PARAMS;
	}
	
	printf("param %s\n", params[i]);
	skip_whitespaces(request, &index);
    }

    // too much params
    if (request[index] != '\0') {
	for (size_t i = 0; i < params_num; i++)
	    free(params[i]);
	 
	return ERR_NUM_PARAMS;
    }
    
    return command;
}

int execute_request(const char* request, hash_table_t* t) {
    char* params[MAX_PARAMS];
    
    const command_t command_list[] = {
	{ "CREATE", 2 },
	{ "READ",   1 },
	{ "UPDATE", 2 },
	{ "DELETE", 1 }
    };

    int command = parse_request(request,
				command_list, NELEMS(command_list),
				params);

    // error
    if (command < 0)
	return command;

    // execute command
    switch (command) {
    case 0:
	hash_table_insert_elem(&t, params[0], params[1]);
	break;
    case 1:
	hash_table_find_elem(t, params[0]);
	break;
    case 2:
	hash_table_update_elem(t, params[0], params[1]);
	break;
    case 3:
	hash_table_delete_elem(t, params[0]);
	break;
    }

    // free params
    for (size_t i = 0; i < command_list[command].params; i++)
	free(params[i]);
    
    return 0;
}
