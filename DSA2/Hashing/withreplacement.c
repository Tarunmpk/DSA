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
        hashTable[index] = key;
    } else {
        // If the slot is not empty, find the next available slot
        int i = index + 1;
        while (i != index) {
            if (i >= TABLE_SIZE) {
                i = 0; // Wrap around
            }
            if (hashTable[i] == -1) {
                // Found an empty slot, insert the key
                hashTable[i] = key;
                break;
            } else {
                i++;
                (*collisions)++;
            }
        }
        if (i == index) {
            // Couldn't find an empty slot
            printf("Hash table is full, could not insert %d\n", key);
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
            printf("%d", hashTable[i]);
            int current = (i + 1) % TABLE_SIZE;
            while (current != i) {
                if (hashTable[current] != -1) {
                    printf(" -> %d", hashTable[current]);
                }
                current = (current + 1) % TABLE_SIZE;
            }
            printf("\n");
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
    printf("Number of collisions (linear probing with chaining and replacement): %d\n", collisions);

    return 0;
}

