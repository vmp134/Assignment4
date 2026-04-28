#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

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