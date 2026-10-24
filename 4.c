#include <stdio.h> 


void accept_mat(int MAT[20][20], int r, int c){

    int i, j;
    printf("enter the elements\n");

    for(i=0; i < r;i++){
        for(j=0; j < c;j++){
            scanf("%d", &MAT[i][j]);
            }
        }

}

int display_mat(int MAT[20][20], int r, int c){
    int i,j;

    for(i=0; i < r;i++){
        for(j=0; j < c;j++){
            printf("%d ", MAT[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int add_mat(int mat1[20][20],int mat2[20][20],int result[20][20],int r1,int c1,int r2, int c2){

    int i,j;
    if(r1 == r2 && c1 == c2){
        for(i=0; i < r1;i++){
            for(j=0; j < c1;j++){
                result[i][j] = mat1[i][j] + mat2[i][j];
            }       
        }
        printf("the matrix after addition is : \n");
        display_mat(result,r1,c1);
    }

    else{
        printf("dimensions dont match, hence addition not possible");
        }
    return 0;
}

int sub_mat(int mat1[20][20],int mat2[20][20],int result[20][20],int r1,int c1,int r2, int c2){

    int i,j;
    if(r1 == r2 && c1 == c2){
        for(i=0; i < r1;i++){
            for(j=0; j < c1;j++){
                result[i][j] = mat1[i][j] - mat2[i][j];
            }       
        }
        printf("the matrix after substraction is : \n");
        display_mat(result,r1,c1);
    }

    else{
        printf("dimensions dont match, hence substraction not possible");
        }
    return 0;
}

int transpose(int mat1[20][20],int r1,int c1,int result[20][20]){

    int i,j;
    for(i=0; i < r1;i++){
            for(j=0; j < c1;j++){
                result[j][i] = mat1[i][j];
            }
    }
    printf("the transpose will be: \n");
    display_mat(result,c1,r1);
}


int mult_mat(int mat1[20][20], int mat2[20][20], int result[20][20], int r1, int c1, int r2, int c2){

    int i, j, k;

    if(c1 == r2){
        for(i=0; i < r1; i++){
            for(j=0; j < c2; j++){
                result[i][j] = 0;
                for(k=0; k < c1; k++){
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        printf("the matrix after multiplication is : \n");
        display_mat(result, r1, c2);
    }

    else{
        printf("dimensions dont match, hence multiplication not possible");
    }
    return 0;
}

int main() {

int MAT1[20][20] , MAT2[20][20], result[20][20];
int r1, c1,r2,c2;


printf("enter the no. of columns and rows for mat1\n");
scanf("%d%d", &r1, &c1);
accept_mat(MAT1,r1,c1);


printf("enter the no. of columns and rows for mat2 \n");
scanf("%d%d", &r2, &c2);
accept_mat(MAT2,r2,c2);


printf("matrix 1: \n");
display_mat(MAT1,r1,c1);
printf("matrix 2: \n");
display_mat(MAT2,r2,c2);

int task;
printf("enter the task to be performed: \n 1:additon \n 2:substraction \n 3:multiplication \n 4:transpose \n" );
scanf("%d",&task);

switch (task){
case 1:
    add_mat(MAT1,MAT2,result,r1,c1,r2,c2);
    break;

case 2:
    sub_mat(MAT1,MAT2,result,r1,c1,r2,c2);
    break;

case 3:
    mult_mat(MAT1,MAT2,result,r1,c1,r2,c2);
    break;

case 4:
    transpose(MAT1,r1,c1,result);
    break;

default:
    break;
}

}