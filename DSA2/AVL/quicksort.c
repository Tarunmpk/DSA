//employee quick sort
#include<stdio.h>
#include<stdlib.h>

int size ;

struct emp {

    char na[50];
    int no;
    int sal;
}e[10];


void swap(struct emp *a, struct emp *b){
    struct emp temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct emp emps[], int lower, int upper){
    int pivot = upper;
    int i = lower;
    int j = upper - 1;

    while(i<j){
        while(i < upper && emps[i].no<emps[pivot].no){
            i+=1;
        }

        while(j > lower && emps[j].no>=emps[pivot].no){
            j-=1;
        }

        if(i<j)
            swap(&emps[i],&emps[j]);

    }

    if(emps[i].no>=emps[pivot].no)
        swap(&emps[i],&emps[pivot]);

    return i;
}


void quicksort(struct emp emps[], int lower, int upper){
    if(lower<upper){
        int partition_pos = partition(emps,lower,upper);
        quicksort(emps,lower,partition_pos-1);
        quicksort(emps,partition_pos+1,upper);
    }
}

void accept(){
    for(int i=0;i<size;i++){
        printf("\nEnter name: ");
        scanf("%s",e[i].na);
        printf("\nEnter emp no: ");
        scanf("%d",&e[i].no);
        printf("\nEnter salaray: ");
        scanf("%d",&e[i].sal);
    }
}

void display(){
    for(int i=0;i<size;i++){
        printf("\nName: %s",e[i].na);
        printf("\nEmp no: %d",e[i].no);
        printf("\nSalary: %d",e[i].sal);
    }
}

void main(){

    printf("enter the no of employess want to add");
    scanf("%d", &size);
    accept();
    quicksort(e,0,size-1);
    display();
}


