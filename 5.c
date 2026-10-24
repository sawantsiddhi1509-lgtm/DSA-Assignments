#include <stdio.h>

#define maxsize 5
#define titlelen 50

int jobId[maxsize];
char jobTitle[maxsize][titlelen];
int front = -1;
int rear = -1;

int QIsEmpty(){
    return front == -1 || front > rear;
}

int QIsFull(){
    return rear == maxsize - 1;
}

void enqueue(int id, char title[]){
    int i;

    if(QIsFull()){
        printf("Queue Overflow! Print queue is full.\n");
        return;
    }

    if(front == -1)
        front = 0;

    rear++;
    jobId[rear] = id;

    for(i = 0; title[i] != '\0' && i < titlelen - 1; i++)
        jobTitle[rear][i] = title[i];
    jobTitle[rear][i] = '\0';

    printf("Print job added successfully\n");
}

void dequeue(){
    if(QIsEmpty()){
        printf("Queue Underflow! No print jobs available.\n");
        return;
    }

    printf("Processing Print Job:\n");
    printf("Job ID: %d\n", jobId[front]);
    printf("Document Title: %s\n", jobTitle[front]);

    front++;   /* just move front ahead, never reset it */
}

void display(){
    int i;

    if(QIsEmpty()){
        printf("No Pending Print Jobs\n");
        return;
    }

    printf("Print Jobs in Queue:\n");
    for(i = front; i <= rear; i++){
        printf("Job ID: %d, Document Title: %s\n", jobId[i], jobTitle[i]);
    }
}

int main(){
    int choice = 0;
    int id;
    char title[titlelen];

    printf("Queue initialized successfully.\n");

    do{
        printf("\n----- PRINT QUEUE (LINEAR) -----\n");
        printf("1. Enqueue Print Job\n");
        printf("2. Dequeue Print Job\n");
        printf("3. Display Print Jobs\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1){
            printf("Enter Job ID: ");
            scanf("%d", &id);
            printf("Enter Document Title: ");
            scanf("%49s", title);

            enqueue(id, title);
        }
        else if(choice == 2){
            dequeue();
        }
        else if(choice == 3){
            display();
        }
        else if(choice == 4){
            printf("Exiting...\n");
        }
        else{
            printf("Invalid choice\n");
        }
    }while(choice != 4);

    return 0;
}