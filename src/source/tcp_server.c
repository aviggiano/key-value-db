#include "tcp_server.h"

#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

const size_t BUFF_SIZE = 10;
const char stop_char = ';';

int socket_desc = 0;

int start_server(uint16_t port) {
    // create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
		perror("Could not create socket.");
		return SOCKET_ERR;
	}
    puts("Socket created.");
     
    // prepare the sockaddr_in structure
	struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
     
    // bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("Bind failed.");
		return BIND_ERR;
	}
    puts("Bind done.");
     
    // listen
    listen(socket_desc , 3);
     
	return 0;
}

int wait_connection() {	
    puts("Waiting for incoming connections...");
     
    // accept connection from an incoming client
	struct sockaddr_in client;
	int addr_len = sizeof(struct sockaddr_in);
    int client_sock = accept(socket_desc,
						 (struct sockaddr*)&client,
						 (socklen_t*)&addr_len);

	if (client_sock == -1) {
		perror("Accept failed");
		return ACCEPT_ERR;
	}
    puts("Connection accepted.");
     
    // receive a message from client
	int read_size;
	char msg_buff[BUFF_SIZE];
	while ((read_size = recv(client_sock, msg_buff, BUFF_SIZE, 0)) > 0 ) {
		// set end of request
		char* stop_ptr = strchr(msg_buff, stop_char);
		if (stop_ptr) {
			msg_buff[stop_ptr - msg_buff] = '\0';
		
			// answer client
			char ans[] = "OK\n";
			int write_size = write(client_sock, ans, strlen(ans));
			if (write_size == -1) {
				perror("Write failed");
				return WRITE_ERR;
			}
		}
	}
	
    if (read_size == 0) {
		puts("Client disconnected.");
		fflush(stdout);
	}
    else if (read_size == -1) {
		perror("RECV failed");
	}
     
    return 0;
}
