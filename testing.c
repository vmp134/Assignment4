#include "chatd.h"
#include <assert.h>

void test_create() {
    struct Node* head = create(3);
    
    assert(head->next == NULL);
    assert(head->client.client_fd == 3);
    assert(head->client.state == 0);
    assert(head->client.name[0] == '\0');
    assert(head->client.status[0] == '\0');    

    destroy(&head);
    printf("create tests passed.\n");
}

void test_addNode() {
    struct Node* head = create(3);
    addNode(4, &head);

    assert(head->client.client_fd == 4);
    assert(head->next->next == NULL);
    assert(head->next->client.client_fd == 3);

    destroyList(&head);
    printf("addNode tests passed.\n");
}

void test_destroy() {
    struct Node* head = create(3);
    destroy(&head);

    assert(head == NULL);

    printf("destroy tests passed.\n");
}

void test_destroyFD() {
    struct Node* head = create(3);
    for (int i = 4; i < 9; i++) {
        addNode(i, &head);
    }
    destroyFD(4, &head);
    destroyFD(7, &head);

    assert(head->client.client_fd == 8);
    assert(head->next->client.client_fd == 6);
    assert(head->next->next->client.client_fd == 5);
    assert(head->next->next->next->next == NULL); 

    destroyList(&head);
    printf("destroyFD tests passed.\n");
}

void test_findName() {
    struct Node* head = create(3);
    addNode(4, &head);
    strcpy(head->client.name, "Alice");       
    strcpy(head->next->client.name, "Bob");   

    struct Node* found = findName("Alice", &head);
    assert(found != NULL);
    assert(found->client.client_fd == 4);

    found = findName("Bob", &head);
    assert(found != NULL);
    assert(found->client.client_fd == 3);

    found = findName("Charlie", &head);
    assert(found == NULL);

    destroyList(&head);
    printf("findName tests passed.\n");
}

void test_destroyList() {
    struct Node* head = create(3);
    for (int i = 4; i < 9; i++) {
        addNode(i, &head);
    }
    destroyList(&head);

    assert(head == NULL);

    printf("destroyList tests passed.\n");
}



int main() {
    test_create();
    test_addNode();
    test_destroy();
    test_destroyFD();
    test_findName();
    test_destroyList();

    return EXIT_SUCCESS;
}