#include <stdio.h>
#include <stdlib.h>

// Node structure for doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of a doubly linked list
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
    newNode->prev = temp;
}

// Function to merge two sorted doubly linked lists
struct Node* mergeSortedLists(struct Node* list1, struct Node* list2) {
    struct Node* result = NULL;
    struct Node* temp1 = list1;
    struct Node* temp2 = list2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data < temp2->data) {
            insertAtEnd(&result, createNode(temp1->data));
            temp1 = temp1->next;
        } else {
            insertAtEnd(&result, createNode(temp2->data));
            temp2 = temp2->next;
        }
    }

    // Append remaining nodes of list1, if any
    while (temp1 != NULL) {
        insertAtEnd(&result, createNode(temp1->data));
        temp1 = temp1->next;
    }

    // Append remaining nodes of list2, if any
    while (temp2 != NULL) {
        insertAtEnd(&result, createNode(temp2->data));
        temp2 = temp2->next;
    }

    return result;
}

// Function to display a doubly linked list
void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to free memory allocated for a doubly linked list
void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    int n, data;

    // Taking input for list1
    printf("Enter the number of elements in the first list: ");
    scanf("%d", &n);
    printf("Enter %d elements in sorted order for the first list: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertAtEnd(&list1, createNode(data));
    }

    // Taking input for list2
    printf("Enter the number of elements in the second list: ");
    scanf("%d", &n);
    printf("Enter %d elements in sorted order for the second list: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insertAtEnd(&list2, createNode(data));
    }

    // Merging and displaying the sorted lists
    struct Node* mergedList = mergeSortedLists(list1, list2);
    printf("Merged sorted list: ");
    display(mergedList);

    // Freeing memory allocated for the lists
    freeList(mergedList);

    return 0;
}

