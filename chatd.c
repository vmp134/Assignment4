#include "chatd.h"

int main(int argc, char **argv) {
    
    //Initial Setup
    /*
     * We initialize variables after checking args
     * The program should only have one arg: the port no.
     * We also setup sockaddr_in struct for ipv4
     * We also setup our array of poll fds for people connected to the server
     * We set fd to server_fd, and setup our linkedlist of clients
     * This makes for easy add/removal of clients, and unbounded amount
     * Better compared to declared array or dynamic array, due to sorting/shifting overhead
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

    struct pollfd fds[SOMAXCONN + 1]; 
    int nfds = 1;   //Number of fds, as poll() takes nfds as 2nd arg
    fds[0].events = POLLIN;
    fds[0].fd = server_fd;
    int ready = 0;  //Number of ready fds

    struct Node* head = NULL;

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

    //Accept Loop
    /*
     * We set while(1) so the server runs indefinitely
     * We check to see if there are any "ready" fds after polling
     * If people have joined (POLLIN), and we have open spots, we add them to fds
     */
    while(1) {
        if ((ready = poll(fds, nfds, -1)) < 0) {
            perror("Poll");
            return EXIT_FAILURE;
        }
        if (fds[0].revents & POLLIN) {
            if (nfds < SOMAXCONN + 1) {            
                int new_fd = accept(server_fd, (struct sockaddr*)&address, &address_length);
                if (new_fd >= 0) {                
                    fds[nfds].fd = new_fd;
                    fds[nfds].events = POLLIN;

                    addNode(new_fd, &head);
                    
                    nfds++;
                }
            }
        }
    }


    return EXIT_SUCCESS;
}