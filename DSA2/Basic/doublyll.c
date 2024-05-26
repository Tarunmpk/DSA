#include <stdio.h>
#include <stdlib.h>

// Node structure for doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to insert a new node at the beginning of the doubly linked list
struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = head;

    if (head != NULL) {
        head->prev = newNode;
    }

    return newNode;
}

// Function to insert a new node at the end of the doubly linked list
struct Node* insertAtEnd(struct Node* head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        return newNode;
    }

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Function to delete a node from the doubly linked list by key
struct Node* deleteNode(struct Node* head, int key) {
    struct Node* temp = head;

    // Find the node to be deleted
    while (temp != NULL && temp->data != key) {
        temp = temp->next;
    }

    // If the key is not found, return head
    if (temp == NULL) {
        return head;
    }

    // If the node to be deleted is the head node
    if (temp == head) {
        head = temp->next;
    }

    // Change next only if node to be deleted is NOT the last node
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    // Change prev only if node to be deleted is NOT the first node
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }

    // Free the memory occupied by the node
    free(temp);
    return head;
}

// Function to display the doubly linked list
void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int choice, data, key;

    do {
        printf("\n1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at beginning: ");
                scanf("%d", &data);
                head = insertAtBeginning(head, data);
                break;
            case 2:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                head = insertAtEnd(head, data);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                head = deleteNode(head, key);
                break;
            case 4:
                printf("Doubly linked list: ");
                display(head);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}

