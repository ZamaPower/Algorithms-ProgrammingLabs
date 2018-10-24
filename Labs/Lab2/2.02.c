/* LAB 02 --- Exercise 02
   ----------------------
 
 A file contains a text with an unknown number of rows, but with lines
 of maximum length equal to 100 characters.
 
 Write a C program able to find and count-up the number of:
 - horizontal sequences made up of 5 adjacent 'h' characters
 ('h' like in "horizontal") on the same row
 - vertical sequences made up of 5 adjacent 'v' characters
 ('v' like in "vertical") on the same column.
 
 Notice that, as the length of the file is unknown, it cannot be stored
 entirely at the same time into the main memory (i.e., it can only be
 stored into the main memory a piece at a time).
 Moreover, it is not possible to read the file more than once.
 
 The program:
 - receives on the command line the name of the file
 - prints out (on standard output) the number of times the "hhhhh"
 sequence appears on a row, and the number of times the sequence
 "vvvvv" appears on a column.

 */




#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[]) {
    
    char filename[20];
    fprintf(stdout, "Input file name: ");
    fgets(filename, 20,stdin );
    filename[strcspn(filename, "\n")] = 0; //removes '/n' from 'filename'
    
    FILE *fp;
    fp= fopen(filename, "r");
    if (fp==NULL) {
        fprintf(stdout, "File error!");
        return EXIT_FAILURE;
    }
    
    char line[101];//100 chars + /n
    int i, h_repetition, v_position[100]={0}, line_counter=0, h_counter=0,v_counter=0, other_char=0;
    
    while (fgets(line, 100, fp)!=NULL) {//read one line from file
       
        h_repetition=0;
        line_counter++; //useful only to not repeat 5 useless for statements later
        
        for (i=0; i<strlen(line); i++) {
            
            //check each char for flag letters
            
            if (line[i]=='h') {
                h_repetition++;
            }
            
            if (line[i]=='v'){
                v_position[i]++;
                other_char=0;
            }
            
            if(line[i]!='h'&&line[i]!='v'){
                h_repetition=0;
                v_position[i]=0;
                other_char=0;
            }
            
            //check if there were 5 Hs in a row
            if (h_repetition==5&&other_char==0) {
                other_char=1;
                h_repetition=0;
                h_counter++;
            }
        }
        
        
        //check if there were 5 Vs in a row
        if (line_counter>=5) {
            for (i=0; i<100; i++) {
                if (v_position[i]>=5) {
                    v_counter++;
                }
            }
        }
        
        
    }
    
    fclose(fp);
    
    //print the results
    fprintf(stdout, "Horizontal Sequence: %d\n", h_counter);
    fprintf(stdout, "Vertical Sequence  : %d\n",v_counter);
    
    return EXIT_SUCCESS;
    
}

