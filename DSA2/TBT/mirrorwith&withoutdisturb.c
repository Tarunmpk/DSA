#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Stack {
    struct Node** array;
    int top;
    int capacity;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(stack->capacity * sizeof(struct Node*));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, struct Node* node) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = node;
}

struct Node* pop(struct Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

struct Node* insert(struct Node* node, int data) {
    if (node == NULL)
        return newNode(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    return node;
}

struct Node* createMirrorImage(struct Node* root) {
    if (root == NULL)
        return NULL;
    struct Node* mirror = newNode(root->data);
    struct Stack* stack = createStack(100);
    push(stack, root);
    struct Stack* mirrorStack = createStack(100);
    push(mirrorStack, mirror);

    while (!isEmpty(stack)) {
        struct Node* current = pop(stack);
        struct Node* mirrorCurrent = pop(mirrorStack);

        if (current->right != NULL) {
            mirrorCurrent->left = newNode(current->right->data);
            push(stack, current->right);
            push(mirrorStack, mirrorCurrent->left);
        }

        if (current->left != NULL) {
            mirrorCurrent->right = newNode(current->left->data);
            push(stack, current->left);
            push(mirrorStack, mirrorCurrent->right);
        }
    }
    return mirror;
}

int calculateHeight(struct Node* root) {
    if (root == NULL)
        return 0;
    struct Stack* stack = createStack(100);
    push(stack, root);
    int height = 0;
    while (!isEmpty(stack)) {
        int size = stack->top + 1;
        while (size > 0) {
            struct Node* current = pop(stack);
            if (current->left != NULL)
                push(stack, current->left);
            if (current->right != NULL)
                push(stack, current->right);
            size--;
        }
        height++;
    }
    return height;
}

void inorderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

int main() {
    struct Node* root = NULL;
    int data, n;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the elements to insert into the BST:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("Inorder traversal of original tree:\n");
    inorderTraversal(root);
    printf("\n");

    struct Node* mirror = createMirrorImage(root);
    printf("Inorder traversal of mirror image tree (without disturbing original tree):\n");
    inorderTraversal(mirror);
    printf("\n");

    int height = calculateHeight(root);
    printf("Height of the original tree: %d\n", height);

    return 0;
}

