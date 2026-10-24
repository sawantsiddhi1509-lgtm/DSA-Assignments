#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define maxsize 50
#define exprlen 200


char opStack[maxsize];
int opTop = -1;


char strStack[maxsize][exprlen];
int strTop = -1;


int OpIsEmpty(){
    return opTop == -1;
}

int OpIsFull(){
    return opTop == maxsize - 1;
}

void OpPush(char ch){
    if(OpIsFull()){
        printf("Operator stack is full\n");
        return;
    }
    opTop++;
    opStack[opTop] = ch;
}

char OpPop(){
    char ch;
    if(OpIsEmpty()) return '\0';
    ch = opStack[opTop];   
    opTop--;               
    return ch;
}

char OpPeek(){
    if(OpIsEmpty()) return '\0';
    return opStack[opTop];
}


int StrIsEmpty(){
    return strTop == -1;
}

int StrIsFull(){
    return strTop == maxsize - 1;
}

void StrPush(char s[]){
    if(StrIsFull()){
        printf("Expression stack is full\n");
        return;
    }
    strTop++;
    strcpy(strStack[strTop], s);
}

void StrPop(char out[]){
    out[0] = '\0';
    if(StrIsEmpty()) return;
    strcpy(out, strStack[strTop]);
    strTop--;
}


int isOperator(char ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^';
}

int precedence(char op){
    if(op == '^') return 3;
    if(op == '*' || op == '/' || op == '%') return 2;
    if(op == '+' || op == '-') return 1;
    return 0;  
}


int infixToPostfix(char infix[], char postfix[]){
    int i, k = 0;
    char ch, top;

    opTop = -1;

    for(i = 0; infix[i] != '\0'; i++){
        ch = infix[i];

        if(isalnum(ch)){
            postfix[k++] = ch;
        }
        else if(ch == '('){
            OpPush(ch);
        }
        else if(ch == ')'){
            while(!OpIsEmpty() && OpPeek() != '(')
                postfix[k++] = OpPop();

            if(OpIsEmpty()){
                printf("Mismatched parentheses\n");
                return 0;
            }
            OpPop();   
        }
        else if(isOperator(ch)){
            while(!OpIsEmpty()){
                top = OpPeek();
                if(top == '(') break;

                
                if(precedence(top) > precedence(ch) ||
                   (precedence(top) == precedence(ch) && ch != '^'))
                    postfix[k++] = OpPop();
                else
                    break;
            }
            OpPush(ch);
        }
        else{
            printf("Invalid character '%c'\n", ch);
            return 0;
        }
    }

    while(!OpIsEmpty()){
        top = OpPop();
        if(top == '('){
            printf("Mismatched parentheses\n");
            return 0;
        }
        postfix[k++] = top;
    }

    postfix[k] = '\0';
    return 1;
}

int prefixToInfix(char prefix[], char result[]){
    int i;
    char ch, a[exprlen], b[exprlen], temp[exprlen];

    strTop = -1;

    for(i = strlen(prefix) - 1; i >= 0; i--){  
        ch = prefix[i];

        if(isalnum(ch)){
            temp[0] = ch;
            temp[1] = '\0';
            StrPush(temp);
        }
        else if(isOperator(ch)){
            if(strTop < 1){
                printf("Invalid expression\n");
                return 0;
            }
            StrPop(a);   
            StrPop(b);   
            sprintf(temp, "(%s%c%s)", a, ch, b);
            StrPush(temp);
        }
        else{
            printf("Invalid character '%c'\n", ch);
            return 0;
        }
    }

    if(strTop != 0){
        printf("Invalid expression\n");
        return 0;
    }

    StrPop(result);
    return 1;
}

int prefixToPostfix(char prefix[], char result[]){
    int i;
    char ch, a[exprlen], b[exprlen], temp[exprlen];

    strTop = -1;

    for(i = strlen(prefix) - 1; i >= 0; i--){   
        ch = prefix[i];

        if(isalnum(ch)){
            temp[0] = ch;
            temp[1] = '\0';
            StrPush(temp);
        }
        else if(isOperator(ch)){
            if(strTop < 1){
                printf("Invalid expression\n");
                return 0;
            }
            StrPop(a);   
            StrPop(b);   
            sprintf(temp, "%s%s%c", a, b, ch);
            StrPush(temp);
        }
        else{
            printf("Invalid character '%c'\n", ch);
            return 0;
        }
    }

    if(strTop != 0){
        printf("Invalid expression\n");
        return 0;
    }

    StrPop(result);
    return 1;
}

int postfixToInfix(char postfix[], char result[]){
    int i;
    char ch, a[exprlen], b[exprlen], temp[exprlen];

    strTop = -1;

    for(i = 0; postfix[i] != '\0'; i++){   
        ch = postfix[i];

        if(isalnum(ch)){
            temp[0] = ch;
            temp[1] = '\0';
            StrPush(temp);
        }
        else if(isOperator(ch)){
            if(strTop < 1){
                printf("Invalid expression\n");
                return 0;
            }
            StrPop(b);   
            StrPop(a);   
            sprintf(temp, "(%s%c%s)", a, ch, b);
            StrPush(temp);
        }
        else{
            printf("Invalid character '%c'\n", ch);
            return 0;
        }
    }

    if(strTop != 0){
        printf("Invalid expression\n");
        return 0;
    }

    StrPop(result);
    return 1;
}

int main(){
    char expr[maxsize];
    char result[exprlen];
    int choice = 0;

    do{
        printf("\n=== Expression Conversion Using Stack ===\n");
        printf("1. Infix to Postfix\n");
        printf("2. Prefix to Infix\n");
        printf("3. Prefix to Postfix\n");
        printf("4. Postfix to Infix\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice >= 1 && choice <= 4){
            printf("Enter expression (no spaces): ");
            scanf("%49s", expr);

            if(choice == 1){
                if(infixToPostfix(expr, result))
                    printf("Postfix: %s\n", result);
            }
            else if(choice == 2){
                if(prefixToInfix(expr, result))
                    printf("Infix: %s\n", result);
            }
            else if(choice == 3){
                if(prefixToPostfix(expr, result))
                    printf("Postfix: %s\n", result);
            }
            else{
                if(postfixToInfix(expr, result))
                    printf("Infix: %s\n", result);
            }
        }
        else if(choice == 5){
            printf("Exiting...\n");
        }
        else{
            printf("Invalid choice\n");
        }
    }while(choice != 5);

    return 0;
}