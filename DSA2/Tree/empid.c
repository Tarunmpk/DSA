#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for an employee record
struct Employee {
    int emp_id;
    char name[50];
    int age;
};

// Structure for a node of the binary search tree
struct Node {
    struct Employee emp;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node with the given employee record
struct Node* newNode(struct Employee emp) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->emp = emp;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to insert a new employee record into the BST
struct Node* insert(struct Node* root, struct Employee emp) {
    if (root == NULL)
        return newNode(emp);
    if (emp.emp_id < root->emp.emp_id)
        root->left = insert(root->left, emp);
    else if (emp.emp_id > root->emp.emp_id)
        root->right = insert(root->right, emp);
    return root;
}

// Function to search for an employee record by employee ID
struct Node* search(struct Node* root, int emp_id) {
    if (root == NULL || root->emp.emp_id == emp_id)
        return root;
    if (emp_id > root->emp.emp_id)
        return search(root->right, emp_id);
    return search(root->left, emp_id);
}

// Function to traverse the BST in inorder (ascending order of employee IDs)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Emp ID: %d, Name: %s, Age: %d\n", root->emp.emp_id, root->emp.name, root->emp.age);
        inorderTraversal(root->right);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int n, emp_id, age;
    char name[50];

    printf("Enter number of employees to add: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter emp ID, name, and age for employee %d: ", i + 1);
        scanf("%d", &emp_id);
        scanf("%s", name);
        scanf("%d", &age);

        struct Employee newEmp = {emp_id, "", age};
        strcpy(newEmp.name, name); // Copying string safely
        root = insert(root, newEmp);
    }

    printf("Employee records sorted by emp ID (ascending order):\n");
    inorderTraversal(root);
    printf("\n");

    printf("Enter emp ID to search for: ");
    scanf("%d", &emp_id);
    struct Node* result = search(root, emp_id);
    
    if (result != NULL)
        printf("Employee found - Emp ID: %d, Name: %s, Age: %d\n", result->emp.emp_id, result->emp.name, result->emp.age);
    else
        printf("Employee with emp ID %d not found\n", emp_id);

    return 0;
}

