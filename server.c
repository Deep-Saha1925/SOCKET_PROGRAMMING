#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int server_fd, client_socket;
    struct sockaddr_in server_addr;

    server_fd = socket(AF_INET, SOCL_STREAM, 0);
}