
/*  Exercise 03
    -----------
 
 Write a C program able to:
 - Read a matrix m1 of R rows and C columns of integer values
 - Compute a matrix m2 of R rows and C columns such that
 - m2[i][j] is equal to zero
 if m1[i][j] is equal to zero.
 - m2[i][j] is the factorial number of -m1[i][j]
 if m1[i][j] is a negative number.
 - m2[i][j] is the smallest power of 10 larger than m1[r][j]
 if m1[i][j] is a positive number.
   */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define R 5
#define C 5

unsigned factorial(int n);
int findclosepower(int n);

int main(int argc, char const *argv[]) {
    
    int m1[R][C],m2[R][C];
    
    for (int i=0; i<R; i++) {
        for (int j=0; j<C; j++) {
            fscanf(stdin, "%d",&m1[i][j]);
            if (m1[i][j]== 0) {
                m2[i][j]=0;
            }
            if (m1[i][j]<0) {
                m2[i][j]= factorial(m1[i][j]);
            }
            if (m1[i][j]>0) {
                m2[i][j]= findclosepower(m1[i][j]);
            }
        }
        
    
    }
    return EXIT_SUCCESS;

}

unsigned factorial(int n)
{
    n=abs(n);
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}
int findclosepower(int n){
    int power=1;
    while (power<n) {
        power=power*10;
    }
    return (power);
}
