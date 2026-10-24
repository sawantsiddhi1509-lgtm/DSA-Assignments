#include <stdio.h>
#include <ctype.h>

#define maxsize 50


int valStack[maxsize];
int valTop = -1;


int ValIsEmpty(){
    return valTop == -1;
}

int ValIsFull(){
    return valTop == maxsize - 1;
}

void ValPush(int val){
    if(ValIsFull()){
        printf("Operand stack is full\n");
        return;
    }
    valTop++;
    valStack[valTop] = val;
}

int ValPop(){
    int val;
    if(ValIsEmpty()) return 0;
    val = valStack[valTop];   
    valTop--;                 
    return val;
}

int applyOperator(char op){
    int a, b, result, i;

    if(valTop < 1){
        printf("Invalid expression\n");
        return 0;
    }

    b = ValPop();  
    a = ValPop();   

    if(op == '+') result = a + b;
    else if(op == '-') result = a - b;
    else if(op == '*') result = a * b;
    else if(op == '/' || op == '%'){
        if(b == 0){
            printf("Division by zero\n");
            return 0;
        }
        if(op == '/')
            result = a / b;
        else
            result = a % b;
    }
    else{   /* '^' */
        if(b < 0){
            printf("Negative exponent not supported\n");
            return 0;
        }
        result = 1;
        for(i = 0; i < b; i++)
            result *= a;
    }

    ValPush(result);
    return 1;
}

void evaluate(char postfix[]){
    int i;
    char ch;

    valTop = -1;

    for(i = 0; postfix[i] != '\0'; i++){
        ch = postfix[i];

        if(isdigit(ch)){
            ValPush(ch - '0');
        }
        else{
            if(!applyOperator(ch))
                return;
        }
    }

    printf("Result: %d\n", ValPop());
}

int main(){
    char postfix[maxsize];
    int choice = 0;

    do{
        printf("\n=== Postfix Expression Evaluation ===\n");
        printf("1. Evaluate Postfix Expression\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1){
            printf("Enter postfix expression: ");
            scanf("%s", postfix);

            evaluate(postfix);
        }
        else if(choice != 2){
            printf("Invalid choice\n");
        }
    }while(choice != 2);

    return 0;
}