#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>

void error(const char *msg){
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){

    if(argc < 2){
        fprintf(stderr, "Port no. not provided. Program terminated\n");
        exit(1);
    }

    if(argc < 3){
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    int sockfd, newsockfd, portno, n;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clien;
    struct hostent *server;

    char buffer[256];

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Error opening socket");
    }

    server = gethostbyname(argv[1]);
    if(server == NULL){
        fprintf(stderr, "ERROR: NO SUCH HOST\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("Binding faled!!");

    listen(sockfd, 5);
    clien = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clien);
    if(newsockfd < 0){
        error("ERROR on acception");
    }

    

    close(newsockfd);
    close(sockfd);
    return 0;
}