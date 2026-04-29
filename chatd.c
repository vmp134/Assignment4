#include "chatd.h"

int main(int argc, char **argv) {
    
    //Setup
    /*
     * We initialize variables after checking args
     * The program should only have one arg: the port no.
     * We also setup sockaddr_in struct for ipv4
     * We also setup our array of poll fds for people connected to the server
     * We also setup our clients array
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
    socklen_t address_length = sizeof(address);

    Client client[SOMAXCONN];
    struct pollfd fds[SOMAXCONN + 1]; 
    int nfds = 1;   //Number of fds, as poll() takes nfds as 2nd arg
    fds[0].events = POLLIN;
    int ready = 0;  //Number of ready fds

    //Server Setup
    /*
     * We setup the socket, bind, then listen 
     */
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        return EXIT_FAILURE;
    }
    if (bind(server_fd, (struct sockaddr*)&address, address_length) < 0) {
        perror("Bind");
        return EXIT_FAILURE;
    }
    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("Listen");
        return EXIT_FAILURE;
    }

    fds[0].fd = server_fd;
    

    //Accept Loop
    /*
     * We set while(1) so the server runs indefinitely
     * We check to see if there are any "ready" fds after polling
     * 
     */
    while(1) {
        if ((ready = poll(fds, nfds, -1)) < 0) {
            perror("Poll");
            return EXIT_FAILURE;
        }
        if (fds[0].revents & POLLIN) {
            int new_fd = accept(server_fd, (struct sockaddr*)&address, address_length);
            fds[nfds].fd = new_fd;
            fds[nfds].events = POLLIN;
            client[nfds-1].client_fd = new_fd;

            nfds++;

        }
    }


    return EXIT_SUCCESS;
}