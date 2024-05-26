#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val;
    int lbit;
    int rbit;
    struct node *left, *right;
};

struct node *insertTBT(struct node *head, int data)
{
    struct node *temp, *p;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->lbit = temp->rbit = 0;
    temp->val = data;
    if (head->lbit == 0)
    {
        head->left = temp;
        temp->left = temp->right = head;
        head->lbit = 1;
        return head;
    }
    p = head->left;

    while (1)
    {
        if (data < p->val && p->lbit == 1)
        {
            p = p->left;
        }
        else if (data > p->val && p->rbit == 1)
        {
            p = p->right;
        }
        else
        {
            break;
        }
    }

    if (data < p->val)
    {
        temp->right = p;
        temp->left = p->left;
        p->left = temp;
        p->lbit = 1;
    }

    if (data > p->val)
    {
        temp->left = p;
        temp->right = p->right;
        p->right = temp;
        p->rbit = 1;
    }
    return head;
}

void inorderTBT(struct node *root)
{
    struct node *temp = root->left;

    while (temp->lbit == 1)
    {
        temp = temp->left;
    }

    while (temp != root)
    {
        printf("%d - ", temp->val);
        if (temp->rbit == 1)
        {
            temp = temp->right;
            while (temp->lbit == 1)
            {
                temp = temp->left;
            }
        }
        else
        {
            temp = temp->right;
        }
    }
}

int main()
{
    int n, data;
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head->lbit = 0;
    head->rbit = 1;
    head->left = head->right = head;

    int h;
    int x;
    printf("Enter the how many nodes :");
    scanf("%d", &x);
    printf("\nEnter the data : ");
    for (int i = 0; i < x; i++)
    {
        scanf("%d", &h);
        head = insertTBT(head, h);
    }

    printf("\nInorder Traversal: ");
    inorderTBT(head);

    return 0;
}

