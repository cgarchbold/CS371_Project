#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 1024

// write a function that takes a socket, 
void transfer(FILE *fp, int sockfd){

    char data_buf[SIZE] = {0};

    //For each line in the file, send 
    while ( fgets(data_buf, SIZE, fp) != NULL ) {
        //send the data, report if there is error
        if (send(sockfd, data_buf, sizeof(data_buf), 0) == -1) {
            perror("*** Error in file transfer, exiting... ***");
            exit(1);
        } 
        //clear data buffer
        bzero(data_buf, SIZE);
    }
}

int main(){

    //Define some parameters

    char *ip = "127.0.0.1";
    int port =  8080;

    char *filename = "test.txt";

    // Attempt to open the file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("*** Error in reading file, exiting... ***");
        exit(1);
    }

    //Create socket
    int sockfd;
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //Check if socket was created without error
    if(sockfd < 0) {
        perror("*** Error in socket, exiting... ***");
        exit(1);
    }
    printf("- Socket created successfully. \n");

    //add server struct information
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //Attempt to connect to server
    if( connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        perror("*** Error creating connection, exiting... ***");
        exit(1);
    }
    printf("- Connected to server. \n");

    //Transfer the file
    transfer(fp, sockfd);
    printf("- File Sent Successfully. \n");

    close(sockfd);
    printf("- Connection closed. \n");

    return 0;
}