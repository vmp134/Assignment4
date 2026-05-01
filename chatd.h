#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <netinet/in.h>

#define NAME_MAX 32
#define STATUS_MAX 64
#define MESSAGE_MAX 80

typedef enum {
    NAM,    
    SET,
    MSG,
    WHO,
    ERR
} MessageType;

//Notes on the following two:
/*
 * +1 is added to account for \0
 * state is meant to be from
 *  - 0, waiting for name
 *  - 1, logged in
 */
typedef struct {
    int client_fd;
    char name[NAME_MAX + 1];
    char status[STATUS_MAX + 1];
    int state; 
} Client;

typedef struct {
    char sender[NAME_MAX + 1];
    char receiver[NAME_MAX + 1];
    char content[MESSAGE_MAX + 1];
    int length;
    MessageType type;
} Message;

struct Node {
    Client client;
    struct Node *next;
};

//clientList.c
struct Node* create(int fd);
void addNode(int fd, struct Node** head);
void destroy(struct Node *node);
void destroyFD(int fd, struct Node** head);
struct Node* findName(char *name, struct Node** head);
void destroyList(struct Node** head);
