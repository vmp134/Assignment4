#include "chatd.h"

int main(int argc, char **argv) {
    
    //Setup
    if (argc != 2) {
        fprintf(stderr, "Error: Incorrect # of Arguments\n");
        return EXIT_FAILURE;
    }
    int port = atoi(argv[1]);
    int server_fd;

    if (server_fd = socket(AF_INET, SOCK_STREAM, 0) < 0) {
        perror("Socket");
        return EXIT_FAILURE;
    }
    

    return EXIT_SUCCESS;
}