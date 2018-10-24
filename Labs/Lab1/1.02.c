/*  Exercise 02
    -----------

Write a C program able to:
- Read two integer values N1 and N2.
- Check whether N1<=DIM and N2<=DIM (DIM is a pre-defined constant
                                     value).
- Read from standard input an array v1 of N1 integer values
- Compute an array v2 of N1 integer values, where each v2[i] is equal
to the arithmetic average of
v1[i-N2], v1[i-N2+1], ..., v1[i-1], v1[i], v1[i+1], ..., v1[i+N2]
if they exist.
- Print-out v2.   */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define DIM 100


int main(int argc, char const *argv[]) {

    int N1,N2;
    printf("Input value N1: ");
    fscanf(stdin, "%d",&N1);
    printf("\n");
    printf("Input value N2: ");
    fscanf(stdin, "%d",&N2);
    printf("\n");
    
    int array1[N1];
    float array2[N1];
    for (int i=0; i<N1; i++) {
        fscanf(stdin, "%d", &array1[i]);
    }
    
    // Compute v2
    
    int tmp=0,flag=0,c=0;
    for (int i=0; i<N1; i++) {
        
        for (c=-1*N2,flag=0,tmp=0; c<N2+1; c++) {
            if (i+c>=0&&i+c<N1) {
                tmp=tmp+array1[i+c];
                flag++;
            }
        }
        array2[i]=(float) tmp/flag;
    }
    
    for (int i=0; i<N1; i++) {
        printf("v2[%d] : %f\n",i,array2[i]);
    }
    
    
    
    
    
    
    
    return EXIT_SUCCESS;

}
