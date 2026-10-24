
#include <stdio.h>

void accept_mat(int MAT[20][20], int r, int c){
    int i, j;
    printf("enter the elements\n");
    for(i=0; i < r; i++){
        for(j=0; j < c; j++){
            scanf("%d", &MAT[i][j]);
        }
    }
}

int display_mat(int MAT[20][20], int r, int c){
    int i,j;
    for(i=0; i < r; i++){
        for(j=0; j < c; j++){
            printf("%d ", MAT[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int compact(int mat[20][20], int r, int c, int result[20][20]){
    int i,j,k;
    result[0][0] = r;
    result[0][1] = c;
    k = 1;

    for(i=0; i < r; i++){
        for(j=0; j < c; j++){
            if(mat[i][j] != 0){
                result[k][0] = i;
                result[k][1] = j;
                result[k][2] = mat[i][j];
                k++;
            }
        }
    }

    result[0][2] = k-1;
    printf("matrix 1 compact form : \n");
    display_mat(result, k, 3);
    return 0;
}

int simple_transpose(int mat[20][20], int result[20][20]) {
    int i, j, k = 1;
    int numCols   = mat[0][1];
    int numTerms  = mat[0][2];

    result[0][0] = mat[0][1];   // new rows = old cols
    result[0][1] = mat[0][0];   // new cols = old rows
    result[0][2] = mat[0][2];   // same number of terms

    for (i = 0; i < numCols; i++) {
        for (j = 1; j <= numTerms; j++) {
            if (mat[j][1] == i) {
                result[k][0] = mat[j][1];
                result[k][1] = mat[j][0];
                result[k][2] = mat[j][2];
                k++;
            }
        }
    }

    printf("matrix 1 transpose form : \n");
    display_mat(result, numTerms + 1, 3);
    return 0;
}

int fast_transpose(int mat[20][20], int result[20][20]){
    
    int i,col;
    int numCols   = mat[0][1];
    int numTerms  = mat[0][2];
    int col_count[20] = {0};   
    int start_pos[20];

    result[0][0] = mat[0][1];   // new rows = old cols
    result[0][1] = mat[0][0];   // new cols = old rows
    result[0][2] = mat[0][2];   // same number of terms

    for(i=0;i<numTerms;i++){
        col = mat[i][1];
        col_count[col] += 1;
    }

    start_pos[0] = 1;
    for(i=1;i<numCols;i++){
        start_pos[i] = start_pos[i-1] + col_count[i-1];
    }
    
    for (i = 1; i <= numTerms; i++) {
        col = mat[i][1];
        int pos = start_pos[col];

        result[pos][0] = mat[i][1];   
        result[pos][1] = mat[i][0];   
        result[pos][2] = mat[i][2];  

        start_pos[col]++;   
    }

    printf("matrix 1 fast transpose form : \n");
    display_mat(result, numTerms + 1, 3);
    return 0;
}

int main(){
    int MAT1[20][20], compactForm[20][20], transposeForm[20][20];
    int r1, c1; 

    printf("enter rows and columns\n");
    scanf("%d%d", &r1, &c1);
    accept_mat(MAT1, r1, c1);

    printf("matrix 1: \n");
    display_mat(MAT1, r1, c1);

    compact(MAT1, r1, c1, compactForm);
    simple_transpose(compactForm, transposeForm);
    fast_transpose(compactForm,transposeForm);

    return 0;
}