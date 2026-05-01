#include "chatd.h"

struct Node *create(int fd) {
  struct Node *node = malloc(sizeof(struct Node));
  node->client.client_fd = fd;

  // Avoid Garbage Data
  memset(node->client.name, 0, NAME_MAX + 1);
  memset(node->client.status, 0, STATUS_MAX + 1);

  node->client.state = 0;
  return node;
}

void addNode(int fd, struct Node **head) {
  struct Node *temp = create(fd);
  temp->next = *head;
  *head = temp;
}

void destroy(struct Node *node) {
  close(node->client.client_fd);
  free(node);
}

void destroyFD(int fd, struct Node **head) {
  struct Node *prev = NULL;
  struct Node *curr = *head;
  while (curr != NULL) {
    if (curr->client.client_fd == fd) {
      if (prev == NULL) {
        *head = curr->next;
      } else
        prev->next = curr->next;
      destroy(curr);
      return;
    }
    prev = curr;
    curr = curr->next;
  }
}

struct Node *findName(char *name, struct Node **head) {
  struct Node *curr = *head;
  while (curr != NULL) {
    if (strcmp(curr->client.name, name) == 0)
      return curr;
    curr = curr->next;
  }
  return NULL;
}
