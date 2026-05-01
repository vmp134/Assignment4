#include "chatd.h"
#include <assert.h>

void test_create() {
    struct Node* head = create(1);
    
    assert(head->next == NULL);
    assert(head->client.client_fd == 1);
    assert(head->client.state == 0);
    assert(head->client.name[0] == '\0');
    assert(head->client.status[0] == '\0');    

    destroy(head);
    printf("create tests passed.\n");
}

void test_addNode() {
    struct Node* head = create(1);
    addNode(2, &head);

    assert(head->client.client_fd == 2);
    assert(head->next->next == NULL);
    assert(head->next->client.client_fd == 1);

    destroyList(&head);
    printf("addNode tests passed.\n");
}

void test_destroyFD() {
    struct Node* head = create(1);
    for (int i = 2; i < 6; i++) {
        addNode(i, &head);
    }
    destroyFD(2, &head);
    destroyFD(5, &head);

    assert(head->client.client_fd == 4);
    assert(head->next->client.client_fd == 3);
    assert(head->next->next->client.client_fd == 1);
    assert(head->next->next->next == NULL); 

    destroyList(&head);
    printf("destroyFD tests passed.\n");
}

void test_findName() {
    struct Node* head = create(1);
    addNode(2, &head);
    strcpy(head->client.name, "Alice");       
    strcpy(head->next->client.name, "Bob");   

    struct Node* found = findName("Alice", &head);
    assert(found != NULL);
    assert(found->client.client_fd == 2);

    found = findName("Bob", &head);
    assert(found != NULL);
    assert(found->client.client_fd == 1);

    found = findName("Charlie", &head);
    assert(found == NULL);

    destroyList(&head);
    printf("findName tests passed.\n");
}

void test_destroyList() {
    struct Node* head = create(1);
    for (int i = 2; i < 6; i++) {
        addNode(i, &head);
    }
    destroyList(&head);

    assert(head == NULL);

    printf("destroyList tests passed.\n");
}



int main() {
    test_create();
    test_addNode();
    test_destroyFD();
    test_findName();
    test_destroyList();

    return EXIT_SUCCESS;
}