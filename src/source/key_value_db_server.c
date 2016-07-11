#include "key_value_db_server.h"

#include <stdio.h>

#include "request_parser.h"
#include "tcp_server.h"

const char* execute_request(const char* request, hash_table_t* t) {
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

    // handle parser erros
    switch (command) {
	case ERR_INVALID_COMMAND:
		return invcom_err_resp;
		break;
	case ERR_NUM_PARAMS:
		return numparams_err_resp;
		break;
    }

	if (command < 0)
		return unknown_err_resp;

    // execute command
    switch (command) {
    case 0:
		if (hash_table_insert_elem(&t, params[0], params[1]))
		    return elem_inserted_resp;
		else
			return elem_not_inserted_resp;
		
		break;
    case 1:
		{
			char* elem = hash_table_find_elem(t, params[0]);
			if (elem)
				return elem;
			else
				return elem_not_found_resp;
				
			break;
		}
    case 2:
		if (hash_table_update_elem(t, params[0], params[1]))
			return elem_updated_resp;
		else
			return elem_not_found_resp;
			
		break;
    case 3:
		hash_table_delete_elem(t, params[0]);
	    return done_resp;
		
		break;
	default:
		fprintf(stderr, "Action not found for command");
    }

    // free params
    for (size_t i = 0; i < command_list[command].params; i++)
		free(params[i]);
    
    return 0;
}

hash_table_t* t;
const char* server_callback(const char* request) {
	return execute_request(request, t);
}

void run_server_blocking(uint16_t port) {
    t = hash_table_constructor();
	start_server(port);
	while (1) {
		wait_connection(server_callback);
	}
}
