#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 4096
#define RESPONSE "Hello from server!"

int create_server_socket(int port){
	int sockfd;
	struct sockaddr_in addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))<0){
		perror("bind");
		exit(1);
	}
	if(listen(sockfd, 1) < 0){
		perror("listen");
		exit(1);
	}
	return sockfd;
}
int accept_client(int server_sock){
	int client_sock;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
	if (client_sock < 0) {
        	perror("accept");
        	exit(1);
    	}

	printf("Client connected!\n");
	return client_sock;
}
int receive_data(int client_sock, char *buffer, int size) {
    int bytes;

    bytes = recv(client_sock, buffer, size - 1, 0);
    if (bytes < 0) {
        perror("recv");
        exit(1);
    }

    buffer[bytes] = '\0';
    printf("Received %d bytes\n", bytes);
    printf("Message: %s\n", buffer);

    return bytes;
}
int send_response(int client_sock, char *response) {
    int bytes;

    bytes = send(client_sock, response, strlen(response), 0);
    if (bytes < 0) {
        perror("send");
        exit(1);
    }

    printf("Sent response: %s\n", response);

    return bytes;
} void cleanup(int sock){
	close(sock);
}
int main(int argc, char *argv[]) {
    int port, server_sock, client_sock;
    char buffer[BUFFER_SIZE];

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);

    server_sock = create_server_socket(port);
    client_sock = accept_client(server_sock);
    receive_data(client_sock, buffer, BUFFER_SIZE);
    send_response(client_sock, RESPONSE);

    cleanup(client_sock);
    cleanup(server_sock);

    return 0;
}
