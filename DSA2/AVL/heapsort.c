#include <stdio.h>
#include <stdlib.h>

int size;
int swap_no = 0;
struct student {
    char n[50];
    int rn;
    int t;
}s[5];


struct student accept() {
    struct student temp;

    printf("\nEnter name: ");
    scanf("%s",&temp.n);
    printf("Enter roll: ");
    scanf("%d",&temp.rn);
    printf("Enter total marks:");
    scanf("%d",&temp.t);

    return temp;
}

void display(){
    int i;
    for(i=0;i<size;i=i+1) {
        printf("\nName: %s\n",s[i].n);
        printf("Roll: %d\n",s[i].rn);
        printf("Marks: %d\n",s[i].t);
    }
}

void swap(struct student * a, struct student * b)
{
    swap_no = swap_no + 1;
    struct student temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct student st[], int N, int i)
{
    
    int largest = i;

    int left = 2 * i + 1;

    int right = 2 * i + 2;

    if (left < N && st[left].rn > st[largest].rn)

        largest = left;

    if (right < N && st[right].rn > st[largest].rn)

        largest = right;

    if (largest != i) {

        swap(&st[i], &st[largest]);

        heapify(st, N, largest);
    }
}

void heapSort(struct student st[], int N)
{

    // Build max heap
    for (int i = N / 2 - 1; i >= 0; i--)

        heapify(st, N, i);

    // Heap sort
    for (int i = N - 1; i >= 0; i--) {

        swap(&st[0], &st[i]);

        // Heapify root element
        // to get highest element at
        // root again
        heapify(st, i, 0);
    }
}

int main() {
    printf("enter no. of students want to add");
    scanf("%d",&size);
    int i=0;

    for(i=0;i<size;i=i+1) {
        s[i] = accept();
    }
    heapSort(s,size);
    printf("\nNumber of times swapped: %d\n", swap_no);
    display();

}




