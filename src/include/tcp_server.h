/***********************
 TCP Server inspired by
 http://www.binarytides.com/server-client-example-c-sockets-linux/
 ***********************/
#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <stdint.h>

typedef enum {
	SOCKET_ERR,
	BIND_ERR,
	ACCEPT_ERR,
	WRITE_ERR
} socket_error_t;

/*
 * Start TCP Server
 * RETURNS 0 if successful, socket_error_t otherwise
 */
int start_server(uint16_t port);

/*
 * Accepts incomming connection
 * RETURNS 0 if successful, socket_error_t otherwise
 */
int wait_connection();

#endif
