#include <stdio.h>
#include <stdlib.h>

// Structure for a BST node
struct Node {
    int key;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a key into BST
struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// Function to find the minimum value node in a BST
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a key from BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Function to find a key in BST
struct Node* find(struct Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (root->key < key) {
        return find(root->right, key);
    }

    return find(root->left, key);
}

// Function to print nodes at a given level
void printLevel(struct Node* root, int level) {
    if (root == NULL) {
        return;
    }

    if (level == 1) {
        printf("%d ", root->key);
    } else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Function to get the height of a BST
int height(struct Node* node) {
    if (node == NULL) {
        return 0;
    } else {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
}

// Function to print level order traversal of BST
void levelOrder(struct Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printLevel(root, i);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, key;

    do {
        printf("\nBinary Search Tree Operations\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Find\n");
        printf("4. Level Wise Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 3:
                printf("Enter key to find: ");
                scanf("%d", &key);
                if (find(root, key) != NULL) {
                    printf("Key %d found in the BST.\n", key);
                } else {
                    printf("Key %d not found in the BST.\n", key);
                }
                break;
            case 4:
                printf("Level wise display of BST:\n");
                levelOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid choice.\n");
        }
    } while (choice != 5);

    return 0;
}

