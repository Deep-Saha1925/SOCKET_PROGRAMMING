#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<malloc.h>

int createTCPIpv4Socket(){
    return socket(AP_INET, SOCK_STREAM, 0);
}

struct sockaddr_in* createTCPIpv4Address(char* ip, int port){
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    return address;
}

int main(){

    int socketFD = createTCPIpv4Socket();
    
    struct sockaddr_in *address = createTCPIpv4Address("172.217.24.14", 80);

    int result = connect(socketFD, address, sizeof(*address));

    if(result == 0){
        printf("CONNECTION SUCCESSFUL\n");
    }

    char* buffer;
    buffer = "GET \\ HTTP /1.1\r\nHost:google.com\r\n\r\n";
    send(socketFD, buffer, strlen(buffer), 0);

    char buffer[1024];
    recv(socketFD, buffer, 1024, 0);

    printf("Response was %s\n", buffer);


    return 0;
}