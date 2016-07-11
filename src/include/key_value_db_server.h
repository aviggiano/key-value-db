#ifndef KEY_VALUE_SERVER_DB_H
#define KEY_VALUE_SERVER_DB_H

#include <stdint.h>

#include "hash_table.h"

/*
 * Protocol responses
 */
static const char elem_inserted_resp[] = "<element inserted>";
static const char elem_not_inserted_resp[] = "<element NOT inserted>";
static const char elem_not_found_resp[] = "<element not found>";
static const char elem_updated_resp[] = "<element updated>";
static const char done_resp[] = "<done>";

static const char invcom_err_resp[] = "<invalid command>";
static const char numparams_err_resp[] = "<wrong number of parameters>";
static const char unknown_err_resp[] = "<unknown error>";


/*
 * Executes request on key-value db t
 *     RETURNS string depending on request command
 */
const char* execute_request(const char* request, hash_table_t* t);

/*
 * Creates a key-value db and opens a server
 * that handles CRUD operations
 */
void run_server_blocking(uint16_t port);

#endif
