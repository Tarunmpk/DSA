#include <stdio.h>
#include <stdlib.h>

// Structure for a node of the binary search tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Structure for a stack used in traversal
struct Stack {
    struct Node** array;
    int top;
    int capacity;
};

// Function to create a new node with the given data
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to create a new stack
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(stack->capacity * sizeof(struct Node*));
    return stack;
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push a node onto the stack
void push(struct Stack* stack, struct Node* node) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = node;
}

// Function to pop a node from the stack
struct Node* pop(struct Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

// Function to get the top node of the stack
struct Node* top(struct Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top];
}

// Function to insert a key into the BST
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    return root;
}

// Function for non-recursive preorder traversal
void preorderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    struct Stack* stack = createStack(100);
    push(stack, root);
    while (!isEmpty(stack)) {
        struct Node* node = pop(stack);
        printf("%d ", node->data);
        if (node->right)
            push(stack, node->right);
        if (node->left)
            push(stack, node->left);
    }
}

// Function for non-recursive inorder traversal
void inorderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    struct Stack* stack = createStack(100);
    struct Node* current = root;
    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        printf("%d ", current->data);
        current = current->right;
    }
}

// Function for non-recursive postorder traversal
void postorderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    struct Stack* stack1 = createStack(100);
    struct Stack* stack2 = createStack(100);
    push(stack1, root);
    while (!isEmpty(stack1)) {
        struct Node* node = pop(stack1);
        push(stack2, node);
        if (node->left)
            push(stack1, node->left);
        if (node->right)
            push(stack1, node->right);
    }
    while (!isEmpty(stack2)) {
        struct Node* node = pop(stack2);
        printf("%d ", node->data);
    }
}

// Function to count the number of leaf nodes
int countLeafNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    struct Stack* stack = createStack(100);
    push(stack, root);
    int count = 0;
    while (!isEmpty(stack)) {
        struct Node* node = pop(stack);
        if (node->left == NULL && node->right == NULL)
            count++;
        if (node->right)
            push(stack, node->right);
        if (node->left)
            push(stack, node->left);
    }
    return count;
}

// Function to count the total number of nodes
int countTotalNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    struct Stack* stack = createStack(100);
    push(stack, root);
    int count = 0;
    while (!isEmpty(stack)) {
        struct Node* node = pop(stack);
        count++;
        if (node->right)
            push(stack, node->right);
        if (node->left)
            push(stack, node->left);
    }
    return count;
}

// Function to display the height of the tree
int height(struct Node* root) {
    if (root == NULL)
        return 0;
    struct Stack* stack = createStack(100);
    push(stack, root);
    int height = 0;
    while (1) {
        int nodeCount = stack->top + 1;
        if (nodeCount == 0)
            return height;
        height++;
        while (nodeCount > 0) {
            struct Node* node = pop(stack);
            if (node->left)
                push(stack, node->left);
            if (node->right)
                push(stack, node->right);
            nodeCount--;
        }
    }
}

// Function for level wise display
void levelWiseDisplay(struct Node* root) {
    if (root == NULL)
        return;
    struct Stack* stack = createStack(100);
    push(stack, root);
    while (!isEmpty(stack)) {
        int nodeCount = stack->top + 1;
        while (nodeCount > 0) {
            struct Node* node = pop(stack);
            printf("%d ", node->data);
            if (node->left)
                push(stack, node->left);
            if (node->right)
                push(stack, node->right);
            nodeCount--;
        }
        printf("\n");
    }
}

// Function to create the mirror image of the tree
void mirror(struct Node* root) {
    if (root == NULL)
        return;
    struct Stack* stack = createStack(100);
    push(stack, root);
    while (!isEmpty(stack)) {
        struct Node* current = pop(stack);
        struct Node* temp = current->left;
        current->left = current->right;
        current->right = temp;
        if (current->left != NULL)
            push(stack, current->left);
        if (current->right != NULL)
            push(stack, current->right);
    }
}

// Function to display leaf nodes
void displayLeafNodes(struct Node* root) {
    if (root == NULL)
        return;
    struct Stack* stack = createStack(100);
    push(stack, root);
    while (!isEmpty(stack)) {
        struct Node* current = pop(stack);
        if (current->left == NULL && current->right == NULL)
            printf("%d ", current->data);
        if (current->right != NULL)
            push(stack, current->right);
        if (current->left != NULL)
            push(stack, current->left);
    }
}

// Function to display total nodes
void displayTotalNodes(struct Node* root) {
    if (root == NULL)
        return;
    struct Stack* stack = createStack(100);
    push(stack, root);
    int count = 0;
    while (!isEmpty(stack)) {
        struct Node* current = pop(stack);
        count++;
        if (current->right != NULL)
            push(stack, current->right);
        if (current->left != NULL)
            push(stack, current->left);
    }
    printf("%d", count);
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert Node\n2. Preorder Traversal\n3. Inorder Traversal\n4. Postorder Traversal\n5. Count Leaf Nodes\n6. Count Total Nodes\n7. Display Height\n8. Level Wise Display\n9. Mirror Image\n10. Display Leaf Nodes\n11. Display Total Nodes\n12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            case 6:
                printf("Total Number of Nodes: %d\n", countTotalNodes(root));
                break;
            case 7:
                printf("Height of the Tree: %d\n", height(root));
                break;
            case 8:
                printf("Level Wise Display:\n");
                levelWiseDisplay(root);
                break;
            case 9:
                printf("Creating mirror image...\n");
                mirror(root);
                printf("Mirror image created.\n");
                break;
            case 10:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 11:
                printf("Total Nodes: ");
                displayTotalNodes(root);
                printf("\n");
                break;
            case 12:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

