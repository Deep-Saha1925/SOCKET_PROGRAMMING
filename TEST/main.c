#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(){

    int socketFD = socket(AP_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in address;
    

    connect(socketFD, &address, sizeof address);

    return 0;
}