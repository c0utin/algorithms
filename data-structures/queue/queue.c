#include <stdio.h>
#include <stdlib.h>

#define MAX 5

struct queue {
    int front;
    int rear;
    int items[MAX];
};

void enqueue(struct queue *q, int data) {
    if (q->rear >= MAX) {
        printf("\nQueue is Full!!\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[q->rear] = data;
    q->rear++;
}

void dequeue(struct queue *q) {
    if (q->front == -1) {
        printf("\nQueue is Empty!!\n");
        return;
    }
    printf("Dequeued: %d\n", q->items[q->front]);
    q->front++;
    if (q->front >= q->rear) {
        q->front = q->rear = -1;
    }
}

void display(struct queue *q) {
    if (q->rear == -1) {
        printf("\nQueue is Empty!!!\n");
    } else {
        printf("\nQueue elements are:\n");
        for (int i = q->front; i < q->rear; i++) {
            printf("%d  ", q->items[i]);
        }
        printf("\n");
    }
}

int main() {
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = 0;

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);
    enqueue(q, 50);

    display(q);

    dequeue(q);
    printf("\nQueue after dequeue:\n");
    display(q);

    free(q);

    return 0;
}

