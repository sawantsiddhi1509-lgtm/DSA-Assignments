#include <stdio.h>

#define maxsize 6     
#define titlelen 50

int jobId[maxsize];
char jobTitle[maxsize][titlelen];
int front = 0;    
int rear = 0;       


int QIsEmpty(){
    return front == rear;
}

int QIsFull(){
    return (rear + 1) % maxsize == front;
}

void enqueue(int id, char title[]){
    int i;

    if(QIsFull()){
        printf("Queue Overflow! Print queue is full.\n");
        return;
    }

    jobId[rear] = id;

    for(i = 0; title[i] != '\0' && i < titlelen - 1; i++)
        jobTitle[rear][i] = title[i];
    jobTitle[rear][i] = '\0';

    rear = (rear + 1) % maxsize;   
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

    front = (front + 1) % maxsize;   
}

void display(){
    int idx;

    if(QIsEmpty()){
        printf("No Pending Print Jobs\n");
        return;
    }

    printf("Pending Print Jobs:\n");
    for(idx = front; idx != rear; idx = (idx + 1) % maxsize){
        printf("Job ID: %d, Document Title: %s\n", jobId[idx], jobTitle[idx]);
    }
}

int main(){
    int choice = 0;
    int id;
    char title[titlelen];

    printf("Circular Queue is initialized successfully.\n");

    do{
        printf("\n===== PRINTER QUEUE MANAGER (CIRCULAR) =====\n");
        printf("1. Add a Print Job (Enqueue)\n");
        printf("2. Process a Print Job (Dequeue)\n");
        printf("3. Display All Pending Print Jobs\n");
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