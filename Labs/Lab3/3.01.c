/* LAB 03 -- Exercise 01
 ------------------------

 A first file stores a text with an undefined number of rows.
 Each row contains at most 100 characters.

 A second file stores a list of words.
 Each word is shorter than 20 characters and the file stores at most
 100 (different) words.

 The program has count the number of times each word stored in the
 second file appears in the text stored in the first file.

 Once the files have been read and manipulated, the program has to
 print out (on standard output) each word found in the first file with
 its absolute frequency, i.e., the number of times it appears in the
 text.

 Capital and small letter have to be considered as equivalent, e.g.,
 "word" and "WORD" and "WoRd" must be considered as equivalent.


 */
//Made by Ed

//Edit 1: removed function removeSpecialChar and included it in optimizeBuffer

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define F1 "file.txt"
#define F2 "words.txt"
#define MAX_WORDS 100

struct word {
    char word[20];
    int occurence;
};typedef struct word word;

int getWords(char *filename,word key[MAX_WORDS]);
void optimizeBuffer(char word[]);
int findWords(char *filemane,word key[MAX_WORDS], int numWords);


int main(void) {
    int numWords, tmp,i;
    word key[MAX_WORDS];

    numWords = getWords(F2, key);
    if (numWords==-1) {
        return EXIT_FAILURE;
    }

    tmp= findWords(F1, key, numWords);
    if (numWords==-1) {
        return EXIT_FAILURE;
    }

    for (i=0; i<numWords; i++) {
        fprintf(stdout, "The word (%s) occurred %d time/s\n",key[i].word,key[i].occurence);
    }


    return EXIT_SUCCESS;

}

/*
 *  Gets word from F2
 */

int getWords(char *filename,word key[MAX_WORDS]){

    FILE *fp;
    fp=fopen(filename, "r");
    if (fp==NULL) {
        fprintf(stderr, "filename does not exist");
        return(-1);
    }
    int i=0;
    while (fscanf(fp, "%s",key[i].word)==1){
        key[i].occurence=0;
        i++;
    }

    fclose(fp);
    return (i);
}

/*
 *  Makes words lowercase & removes special char
 */

void optimizeBuffer(char word[]){

    int i;
    for (i=0; i<strlen(word); i++) {
        if (isalnum(word[i])==0) {
            word[i]='\0';
            break;
        }
        word[i]=tolower(word[i]);
    }
}

/*
 *  Looks in F1 if the key words are present
 */

int findWords(char *filemane,word key[MAX_WORDS], int numWords){

    char buffer[101]; int i;

    FILE *fp;
    fp=fopen(filemane, "r");
    if (fp==NULL) {
        return(-1);
    }

    while (fscanf(fp,"%100s",buffer)==1) {
        optimizeBuffer(buffer);
        for (i=0; i<numWords; i++) {
            if (strcmp(buffer, key[i].word)==0) {
                key[i].occurence++;
            }
        }
    }
    return (EXIT_SUCCESS);
}
