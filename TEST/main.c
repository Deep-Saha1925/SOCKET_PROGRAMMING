#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main(){

    int socketFD = socket(AP_INET, SOCK_STREAM, 0);
    
    char* ip = "172.217.24.14";
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(80);
    inet_pton(AF_INET, ip, &address.sin_addr.s_addr);

    int result = connect(socketFD, &address, sizeof address);

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