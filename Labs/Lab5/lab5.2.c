/*Exercise 02
 -----------
 
 A matrix of strings is stored in a file with the following format:
 
 R C
 string_1_1 string_1_2 string_1_3 ... string_1_C
 ...
 string_R_1 string_R_2 string_R_3 ... string_R_C
 
 where R and C are integers, representing the number of rows and
 columns of the matrix, and string_i_j are the strings stored in
 the matrix.
 Each string is at most 20 characters long.
 Notice that strings on each row are already alphabetically ordered.
 
 Write a C program able to "merge" all strings in the matrix in a
 single array of strings, i.e., to store all strings of the matrix
 in a unique array containing all strings alphabetically ordered.
 
 Notice that:
 1. the array has a number of elements equal to RxC, and that
 each of its element contains a string
 2. as the strings on each row of the matrix are already ordered,
 strings do not need to be re-ordered completely to generate the
 final array.
 See the "suggestions" for further details.
 
 The result has to be stored in an output file, which contains
 the total number of strings on the first row, and all string in the
 following lines.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX_STR_LEN 20

#define FILE1 "file1.txt"
#define FILE2 "words.txt"




char ***read_file(char *filename, int *row,int *col);
char **sort_data(char ***index, int ,int);
void print_data(char *filename, char **index,int ,int);
void print_all_data(char ***index, int row,int col);

int main(void)
{
    
    int row,col;
    char ***index,**sortedIndex;
    
    index=read_file(FILE1, &row,&col);
    sortedIndex=sort_data(index, row, col);
    print_data(FILE2, sortedIndex, row, col);
    
    /*
     Liberate the memory!!!! MURICA!!
     */
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            free(index[i][j]);
        }
        free(index[i]);
    }
    free(index);
    free(sortedIndex);
    
    return (EXIT_SUCCESS);
}

/*
 Reads a file and outputs the information in a pointer of type strig
 */
char ***read_file(char *filename, int *row,int *col){
    
    char tmp[MAX_STR_LEN+1];
    char ***index;
    
    FILE *fp;
    fp=fopen(filename,"r");
    if (fp==NULL)
    {
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(fp,"%d %d",row,col);
    
    //FORMAT index[row][column]
    index= (char ***) malloc(*row * sizeof(char **));
    
    for (int i = 0; i < *row; ++i){
        
        index[i]= (char **) malloc(*col * sizeof(char **));
        for (int j=0; j<*col; j++) {
            
            fscanf(fp,"%s",tmp);
            index[i][j]=strdup(tmp);
        }
        
    }
    fclose(fp);
    return(index);
}

/*
 Outputs data on a file
 */
void print_data(char *filename, char **index,int row, int col){
    
    int total= row*col;
    int i;
    
    FILE *fp;
    fp=fopen(filename, "w");
    if (fp==NULL) {
        fprintf(stderr, "Cannot access file");
        exit(EXIT_FAILURE);
    }
    
    
    fprintf(fp, "%d\n",total);
    for (i=0; i<total; i++) {
        fprintf(fp, "%s\n",index[i]);
    }
    
    fclose(fp);
}

/*
 sorts a string in alphabetical order
 */
char **sort_data(char ***index, int row,int col){
    
    int i,posInIndex,smallestCharPos,*tracker;
    char **sortedindex,*buffer;
    sortedindex=(char **) malloc((row*col)*sizeof(char*));
    tracker= (int*) calloc(row, sizeof(int));//calloc is used so all items are initialized to 0
    
    posInIndex=0;
    while (posInIndex<row*col) {
        smallestCharPos=-1;
        for (i=0; i<row; i++) {
            if (tracker[i]<col&&((smallestCharPos==-1)||(strcmp(index[i][tracker[i]], buffer)<0))) {
                smallestCharPos=i;
                buffer=index[i][tracker[i]];
            }
            
        }
        sortedindex[posInIndex]=index[smallestCharPos][tracker[smallestCharPos]];
        posInIndex++;
        tracker[smallestCharPos]++;
    }
    free(tracker);
    return (sortedindex);
    
}
