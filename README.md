CS 371 Computer Networking - Programming Project
Cohen Archbold
University of Kentucky

This repository contains an implementation of a server-client file transfer application.
This application uses socket programming to transfer a file between a client and server program.

The client program takes input, specifically the path to the file to upload to the server and the IP address of the server.


To compile this application:

    $ make all

To test file tranfer:

    In one terminal instance:
    
    $ ./server

    In another terminal instance, potentially another machine:

    $ ./client {filename} {IP address}
    
        For example, 
        
        $./client test.txt 127.0.0.1