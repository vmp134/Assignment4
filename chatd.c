#include "chatd.h"

int main(int argc, char **argv) {
    
    //Setup
    /*
     * We initialize variables after checking args
     * The program should only have one arg: the port no.
     * We also setup fd for the server
     * We also setup sockaddr_in struct for ipv4
     * We 
     */
    if (argc != 2) {
        fprintf(stderr, "Error: Incorrect # of Arguments\n");
        return EXIT_FAILURE;
    }
    int port = atoi(argv[1]);
    int server_fd;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    Client client[SOMAXCONN];
    int current_client = 0;

    struct pollfd fds[SOMAXCONN + 1]; 
    int nfds = 0;   //Number of fds, as poll() takes nfds as 2nd arg

    //Server Setup
    /*
     * We setup the socket, bind, then listen 
     */
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        return EXIT_FAILURE;
    }
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind");
        return EXIT_FAILURE;
    }
    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("Listen");
        return EXIT_FAILURE;
    }

    //Accept Loop
    /*
     * 
     * 
     * 
     */
    while(1) {
        poll(fds, nfds, -1);

        if ((client[current_client].client_fd = accept(server_fd, (struct sockaddr*)&address, sizeof(address))) < 0) {
            perror("Accept");
            return EXIT_FAILURE;
        }

        current_client++;
    }


    return EXIT_SUCCESS;
}