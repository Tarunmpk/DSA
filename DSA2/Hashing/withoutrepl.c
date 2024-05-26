#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

struct Node {
    int key;
    struct Node* next;
};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

void insert(int hashTable[], int key, int* collisions) {
    int index = key % TABLE_SIZE;
    if (hashTable[index] == -1) {
        // If the slot is empty, insert the key
        struct Node* newNode = createNode(key);
        hashTable[index] = (int)newNode;
    } else {
        // If the slot is not empty, check if the key already exists
        struct Node* temp = (struct Node*)hashTable[index];
        struct Node* prev = NULL;
        while (temp != NULL && temp->key != key) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != NULL) {
            // Key already exists, replace it
            temp->key = key;
        } else {
            // Key doesn't exist, add it to the end of the linked list
            struct Node* newNode = createNode(key);
            prev->next = newNode;
            (*collisions)++;
        }
    }
}

void display(int hashTable[]) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        if (hashTable[i] == -1) {
            printf("Empty\n");
        } else {
            struct Node* temp = (struct Node*)hashTable[i];
            while (temp != NULL) {
                printf("%d -> ", temp->key);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

int main() {
    int hashTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }

    int n, key, collisions = 0;
    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);
    printf("Enter %d elements to insert:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(hashTable, key, &collisions);
    }

    display(hashTable);
    printf("Number of collisions (chaining): %d\n", collisions);

    return 0;
}

