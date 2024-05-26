#include <stdio.h>
#include <stdlib.h>

// Node structure for singly linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of a singly linked list
void insertAtEnd(struct Node** head, struct Node* newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

// Function to display a singly linked list
void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to reverse a singly linked list iteratively
void Reverse(struct Node** head) {
    struct Node* prev = NULL;
    struct Node* current = *head;
    struct Node* next = NULL;

    while (current != NULL) {
        // Store next node
        next = current->next;
        // Reverse current node's pointer
        current->next = prev;
        // Move pointers one position ahead
        prev = current;
        current = next;
    }

    // Update head pointer
    *head = prev;
}

int main() {
    struct Node* head = NULL;
    int n, data;

    // Taking input for the singly linked list
    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);
    printf("Enter %d elements for the list: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertAtEnd(&head, createNode(data));
    }

    // Displaying the original list
    printf("Original list: ");
    display(head);

    // Reversing the list
    Reverse(&head);

    // Displaying the reversed list
    printf("Reversed list: ");
    display(head);

    return 0;
}

