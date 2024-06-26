#include <stdlib.h>
#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head;

void Insert(int data, int n) {

    struct Node* temp1 = (struct Node*)malloc(sizeof(struct Node*));

    temp1 -> data = data;
    temp1 -> next = NULL;

    if(n == 1) {
        temp1 -> next = head;
        head = temp1;
        return;
    }

    struct Node* temp2 = head;
    for(int i = 0; i < n-2; i++){
        temp2 = temp2 -> next;
    };

    temp1 -> next = temp2 -> next;
    temp2 -> next = temp1;
};

void Print() {

    struct Node* temp = head;
    while(temp != NULL){
        printf("%d", temp -> data);
        temp = temp -> next;
    };

    printf("\n");
};

void Delete (int n){

    struct Node* tempDelete = head;

    if(n == 1) {
        head = tempDelete -> next;
        free(tempDelete);
        return;
    }

    for(int i = 0; i < n-2; i++){
        tempDelete = tempDelete -> next;
    }

    struct Node* tempDelete2 = tempDelete -> next;
    tempDelete -> next = tempDelete2 -> next;
    free(tempDelete2);
};

int main() {

    head = NULL;

    Insert(6, 1);
    Insert(6, 2);
    Insert(3, 1);
    Insert(9, 3);
    Insert(9, 2);
    Print();

    int n;
    printf("Enter a position\n");
    scanf("%d", &n);
    Delete(n);
    Print();
}
