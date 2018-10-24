
/*  Exercise 04
    -----------
 
 Write a C program able to compute the product of two matrices
 containing real values.
 The program has to proceed as follows:
 1. It defines two matrix's m1 and m2 of "physical" size equal to
 MAX_DIM rows and MAX_DIM columns, where MAX_DIM is a pre-defined
 constant.
 2. It reads the "logical" (actual) size of the two matrices:
 r1 rows and c1 columns for m1
 and
 r2 rows and c2 columns for m2.
 3. It verifies whether r1, c1, r2, and c2 are smaller than MAX_DIM,
 and whether c1==r2 (i.e., it is possible to compute the product).
 4. It reads m1 and m2 from standard input.
 5. It computes the product
 m3 = m1 x m2
 with m3 having r1 rows and c2 columns.
 6. It prints-out m3 on standard output.
   */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_DIM 5


int smallerthan(int n);
void printmatrix(int t, float m[t][t]);

int main(int argc, char const *argv[]) {
    
    float m1[MAX_DIM][MAX_DIM], m2[MAX_DIM][MAX_DIM];
    int r1,r2,c1,c2;
    
    fprintf(stdout,"First matrix (rxc): ");
    fscanf(stdin, "%d %d",&r1, &c1);
    fprintf(stdout,"\nSecond matrix (rxc): ");
    fscanf(stdin, "%d %d",&r2, &c2);
    
    if (smallerthan(r1)==0&&smallerthan(r2)==0&&smallerthan(c1)==0&&smallerthan(c2)==0&&c1==r2) {
        
        fprintf(stdout, "\nMatrix 1: ");
        for (int i=0; i<r1; i++) {
            for (int j=0; j<c1; j++) {
                fscanf(stdin, "%f",&m1[i][j]);
            }
        }
        fprintf(stdout, "\nMatrix 2: ");
        for (int i=0; i<r2; i++) {
            for (int j=0; j<c2; j++) {
                fscanf(stdin, "%f",&m2[i][j]);
            }
        }
        
        float m3[c1][c1];
        int tmp=0;
        for (int i =0; i<c1; i++) {
            for (int j=0; j<c1; j++) {
                for (int t=0,tmp=0; t<c1; t++) {
                    tmp=tmp + m1[i][t]*m2[t][j];
                }
                m3[i][j]=tmp;
            }
        }
        
        printmatrix(c1,m3);
        return EXIT_SUCCESS;
    }
    
    else{
        return EXIT_FAILURE;
    }

}

int smallerthan(int n){
    if (n<MAX_DIM) {
        return (0);
    }
    else{
        return (1);
    }
}

void printmatrix(int t, float m[t][t]){
    
    for (int i=0; i<t; i++) {
        for (int j=0; j<t; j++) {
            fprintf(stdout, "%f ",m[i][j]);
        }
        fprintf(stdout, "\n");
    }
    
}

