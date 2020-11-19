#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define SIZE 1024

void receive_file(int sockfd){
    FILE *fp;
    char *filename = "rec.txt";
    char data_buf[SIZE];

    //open file for writing
    fp = fopen(filename, "w");

    //continuous loop
    while (1) {
        //receive data from socket
        if (recv(sockfd, data_buf, SIZE, 0) <= 0){
            break;
            return;
        }
    //write data to file
    fprintf(fp, "%s", data_buf);

    //zero out buffer
    bzero(data_buf, SIZE);
    }
    return;
}



int main(){
    char *ip = "127.0.0.1";
    int port = 8080;

    //create passive socket, connected socket
    int pass_sockfd, con_sockfd;
    struct sockaddr_in pass_server_addr, con_server_addr;
    pass_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(pass_sockfd < 0) {
        perror("*** Error in socket, exiting... ***");
        exit(1);
    }
    printf("- Socket created successfully. \n");

    //add server struct information
    pass_server_addr.sin_family = AF_INET;
    pass_server_addr.sin_port = port;
    pass_server_addr.sin_addr.s_addr = inet_addr(ip);

    if( bind(pass_sockfd, (struct sockaddr*)&pass_server_addr, sizeof(pass_server_addr)) < 0){
        perror("*** Error binding, exiting... ***");
        exit(1);
    }
    printf("- Binding successful. \n");

    if(listen(pass_sockfd, 10) == 0){
        printf("- Listening....\n");
    }else{
        perror("*** Error listening, exiting... ***");
        exit(1);
    }

    //accept connection, and wait for transfer
    socklen_t size = sizeof(con_server_addr);
    con_sockfd = accept(pass_sockfd, (struct sockaddr*)&con_server_addr, &size );

    //receive and write file
    receive_file(con_sockfd);
    printf("- Transfer Received.\n");

    return 0;
}