/*Exercise 01 (A and B)
 ---------------------
 
 A file has the following format:
 - the first row contains an integer number n
 - the following n rows store a string (each string is terminated
 by a '\n' character).
 The longest string included in the file is 100 character long but
 the average string length is much smaller (e.g., 10 characters).
 
 A C program receives two file names on the command line (input and
 output file names).
 The first file has the format previously specified.
 The program:
 1) reads the content of the first (input) file and stores all strings
 into a dynamic data structure
 2) orders the strings in alphabetic order
 3) stores the strings in the second (output) file.
 The output file has the same format of the input one.
 
 Write two versions of the program:
 
 - Version B
 It stores the words in a dynamic matrix:
 
 char **mat;
 
 In this second version, to reorder the strings will be necessary to
 swap strings or sufficient to swap pointers to strings?
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX_FILE_LEN 30
#define MAX_STR_LEN 100




char **read_file(char *filename, int *num);
void print_data(char **index,int t, char *filename);
void sort_data(char **index, int num);

int main(void)
{
    char file1[MAX_FILE_LEN],file2[MAX_FILE_LEN];
    char **index;
    int num;
    
    
    fprintf(stdout,"First file: ");
    fscanf(stdin,"%s",file1);
    fprintf(stdout,"Second file: ");
    fscanf(stdin,"%s",file2);
    
    index = read_file(file1,&num);
    sort_data(index, num);
    print_data(index,num, file2);
    
    
    for (int i = 0; i < num; ++i)
    {
        free(index[i]);
    }
    free(index);
    return (EXIT_SUCCESS);
}

/*
 Reads a file and outputs the information in a pointer of type strig
 */
char **read_file(char *filename, int *num){
    
    char tmp[MAX_STR_LEN+1];
    
    FILE *fp;
    fp=fopen(filename,"r");
    if (fp==NULL)
    {
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp,"%d",num);
    
    char **index= (char **) malloc(*num * sizeof(char *));
    if (index==NULL) {
        fprintf(stderr, "memory allocation failure\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < *num; ++i){
        
        fscanf(fp,"%s",tmp);
        index[i]=strdup(tmp);
        if (index[i]==NULL) {
            fprintf(stderr, "memory allocation failure\n");
            exit(EXIT_FAILURE);
        }
        
    }
    fclose(fp);
    return(index);
}

/*
 Outputs data on a file
 */
void print_data(char **index,int t,char *filename){
    
    FILE *fp;
    fp=fopen(filename, "w");
    if (fp==NULL) {
        fprintf(stderr, "Cannot access file");
        exit(EXIT_FAILURE);
    }
    
    fprintf(fp, "%d\n",t);
    for (int i = 0; i < t; ++i){
        fprintf(fp, "%s\n", index[i]);
    }
    
    fclose(fp);
}

/*
 sorts a string in alphabetical order
 */
void sort_data(char **index, int num){
    
    int i,j;
    char *tmp;
    
    for ( i = 0; i < num; ++i)
    {
        for ( j = i+1; j < num; ++j)
        {
            if (strcasecmp(index[i],index[j])>0)
            {
                tmp=index[i];
                index[i]=index[j];
                index[j]=tmp;
            }
        }
    }
    
}
