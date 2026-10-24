#include <stdio.h>
#include <stdlib.h>


struct Term{
    int coeff;
    int exp;
    struct Term *next;
};


struct Term *makeTerm(int c, int e){
    struct Term *node;

    node = (struct Term*)malloc(sizeof(struct Term));
    if(node == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    node->coeff = c;
    node->exp = e;
    node->next = node;   
    return node;
}


struct Term *removeTerm(struct Term *head, struct Term *target){
    struct Term *prev;

    if(target->next == target){
        free(target);
        return NULL;
    }

    prev = head;
    while(prev->next != target)  
        prev = prev->next;

    if(target == head)
        head = head->next;

    prev->next = target->next;
    free(target);
    return head;
}

void freePoly(struct Term *head){
    struct Term *temp, *nextNode;

    if(head == NULL) return;

    temp = head->next;
    while(temp != head){
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
    free(head);
}


struct Term *insertTerm(struct Term *head, int c, int e){
    struct Term *newNode, *curr, *last;

    if(c == 0) return head;   

    if(head == NULL){
        return makeTerm(c, e);
    }

    
    curr = head;
    do{
        if(curr->exp == e){
            curr->coeff += c;
            if(curr->coeff == 0)
                head = removeTerm(head, curr);
            return head;
        }
        curr = curr->next;
    }while(curr != head);

    newNode = makeTerm(c, e);

    if(e > head->exp){   
        last = head;
        while(last->next != head)
            last = last->next;
        newNode->next = head;
        last->next = newNode;
        return newNode;
    }

    
    curr = head;
    while(curr->next != head && curr->next->exp > e)
        curr = curr->next;

    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}

struct Term *createPoly(){
    struct Term *head = NULL;
    int n, i, c, e;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++){
        printf("Enter coefficient and exponent of term %d: ", i + 1);
        scanf("%d %d", &c, &e);

        if(e < 0){
            printf("Exponent must be non-negative, term skipped\n");
            continue;
        }
        head = insertTerm(head, c, e);
    }

    return head;
}

void displayPoly(struct Term *head){
    struct Term *temp;
    int first = 1;
    int c;

    if(head == NULL){
        printf("0\n");
        return;
    }

    temp = head;
    do{
        c = temp->coeff;

        if(first){
            if(c < 0) printf("-");
        }
        else{
            if(c < 0) printf(" - ");
            else printf(" + ");
        }

        if(c < 0) c = -c;

        if(c != 1 || temp->exp == 0)   
            printf("%d", c);

        if(temp->exp == 1)
            printf("x");
        else if(temp->exp > 1)
            printf("x^%d", temp->exp);

        first = 0;
        temp = temp->next;
    }while(temp != head);

    printf("\n");
}

struct Term *addPoly(struct Term *p1, struct Term *p2){
    struct Term *a, *b, *result, *tail, *node;
    int c, e, aDone, bDone;

    result = NULL;
    tail = NULL;
    a = p1;
    b = p2;
    aDone = (p1 == NULL);   
    bDone = (p2 == NULL);

    while(!aDone || !bDone){
        if(bDone || (!aDone && a->exp > b->exp)){
            c = a->coeff;
            e = a->exp;
            a = a->next;
            if(a == p1) aDone = 1;
        }
        else if(aDone || b->exp > a->exp){
            c = b->coeff;
            e = b->exp;
            b = b->next;
            if(b == p2) bDone = 1;
        }
        else{   
            c = a->coeff + b->coeff;
            e = a->exp;
            a = a->next;
            b = b->next;
            if(a == p1) aDone = 1;
            if(b == p2) bDone = 1;
        }

        if(c != 0){
            node = makeTerm(c, e);
            if(result == NULL){
                result = node;
            }
            else{
                tail->next = node;
            }
            tail = node;
        }
    }

    if(result != NULL)
        tail->next = result;   

    return result;
}

int main(){
    struct Term *p1 = NULL, *p2 = NULL, *sum;
    int choice = 0;

    do{
        printf("\n=== Polynomial Operations (Circular Linked List) ===\n");
        printf("1. Create Polynomial 1\n");
        printf("2. Create Polynomial 2\n");
        printf("3. Display Polynomials\n");
        printf("4. Add Polynomials\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1){
            freePoly(p1);
            p1 = createPoly();
        }
        else if(choice == 2){
            freePoly(p2);
            p2 = createPoly();
        }
        else if(choice == 3){
            printf("P1(x) = ");
            displayPoly(p1);
            printf("P2(x) = ");
            displayPoly(p2);
        }
        else if(choice == 4){
            sum = addPoly(p1, p2);
            printf("P1(x) = ");
            displayPoly(p1);
            printf("P2(x) = ");
            displayPoly(p2);
            printf("Sum   = ");
            displayPoly(sum);
            freePoly(sum);
        }
        else if(choice == 5){
            freePoly(p1);
            freePoly(p2);
            printf("Exiting...\n");
        }
        else{
            printf("Invalid choice\n");
        }
    }while(choice != 5);

    return 0;
}