    #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define namelen 50


struct Student{
    int regNo;
    char name[namelen];
    struct Student *next;
};

struct Student *head = NULL;

int ListIsEmpty(){
    return head == NULL;
}

void addStudent(int regNo, char name[]){
    struct Student *newNode, *temp;

    newNode = (struct Student*)malloc(sizeof(struct Student));
    if(newNode == NULL){
        printf("Memory allocation failed\n");
        return;
    }

    newNode->regNo = regNo;
    strcpy(newNode->name, name);
    newNode->next = NULL;

    if(ListIsEmpty()){
        head = newNode;
    }
    else{
        temp = head;
        while(temp->next != NULL)   /* walk to the last node */
            temp = temp->next;
        temp->next = newNode;
    }

    printf("Student is added successfully.\n");
}

void removeStudent(int regNo){
    struct Student *curr, *prev;

    if(ListIsEmpty()){
        printf("No students registered.\n");
        return;
    }

    prev = NULL;
    curr = head;
    while(curr != NULL && curr->regNo != regNo){
        prev = curr;
        curr = curr->next;
    }

    if(curr == NULL){
        printf("Student not found.\n");
        return;
    }

    if(prev == NULL)            
        head = curr->next;
    else
        prev->next = curr->next;

    free(curr);
    printf("Student record is deleted successfully.\n");
}

void displayList(){
    struct Student *temp;

    if(ListIsEmpty()){
        printf("No students registered.\n");
        return;
    }

    printf("Registered Students:\n");
    for(temp = head; temp != NULL; temp = temp->next){
        printf("RegNo: %d, Name: %s\n", temp->regNo, temp->name);
    }
}

int countStudents(){
    struct Student *temp;
    int count = 0;

    for(temp = head; temp != NULL; temp = temp->next)
        count++;

    return count;
}

void sortList(){
    struct Student *i, *j;
    int tempReg;
    char tempName[namelen];

    if(ListIsEmpty()){
        printf("No students registered.\n");
        return;
    }

    
    for(i = head; i->next != NULL; i = i->next){
        for(j = i->next; j != NULL; j = j->next){
            if(i->regNo > j->regNo){
                tempReg = i->regNo;
                strcpy(tempName, i->name);

                i->regNo = j->regNo;
                strcpy(i->name, j->name);

                j->regNo = tempReg;
                strcpy(j->name, tempName);
            }
        }
    }

    printf("List sorted by Registration Number.\n");
}

void reverseList(){
    struct Student *prev, *curr, *nextNode;

    if(ListIsEmpty()){
        printf("No students registered.\n");
        return;
    }

    prev = NULL;
    curr = head;
    while(curr != NULL){
        nextNode = curr->next;   /* save the next node first */
        curr->next = prev;       /* flip the link */
        prev = curr;
        curr = nextNode;
    }
    head = prev;

    printf("List reversed.\n");
}

void freeList(){
    struct Student *temp;

    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(){
    int choice = 0;
    int regNo;
    char name[namelen];

    do{
        printf("\n=== Workshop Enrollment System ===\n");
        printf("1. Add a Student\n");
        printf("2. Remove a Student\n");
        printf("3. Display the List\n");
        printf("4. Count Total Participants\n");
        printf("5. Sort the List\n");
        printf("6. Reverse the List\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1){
            printf("Enter Registration Number: ");
            scanf("%d", &regNo);
            printf("Enter Name: ");
            scanf("%49s", name);

            addStudent(regNo, name);
        }
        else if(choice == 2){
            printf("Enter Registration Number to remove: ");
            scanf("%d", &regNo);

            removeStudent(regNo);
        }
        else if(choice == 3){
            displayList();
        }
        else if(choice == 4){
            printf("Total Participants: %d\n", countStudents());
        }
        else if(choice == 5){
            sortList();
        }
        else if(choice == 6){
            reverseList();
        }
        else if(choice == 7){
            freeList();
            printf("Exiting...\n");
        }
        else{
            printf("Invalid choice\n");
        }
    }while(choice != 7);

    return 0;
}