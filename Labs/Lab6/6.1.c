#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_SIZE 1000
#define MAX_FILE 20
#define F1 "file1.txt"



typedef struct s_word s_word;
struct s_word {
    char *key;
    int occurrence;
    s_word *nextptr;
};

s_word *newptr(void);
s_word *readFile(char *filename);
void makeLower(char *word);
void printData(char *filename,s_word *head);
void freeList(s_word* head);


int main(int argc,char *argv[]){
    char file1[MAX_FILE+1];
    char file2[MAX_FILE+1];
    s_word *head;
    
    fprintf(stdout, "Input file 1: ");
    fscanf(stdin, "%s",file1);
    fprintf(stdout, "Input file 2: ");
    fscanf(stdin, "%s",file2);
    
    head= readFile(F1);
    printData(file2, head);
    //LIBERATE MEMORY, MURICA!!!
    freeList(head);
    
    return (0);
   
}

s_word *newptr(void){
    
    s_word *newptr=malloc(sizeof(s_word));
    if (newptr==NULL) {
        fprintf(stdout, "Error allocating memory");
        exit(EXIT_FAILURE);
    }
    
    return (newptr);
}

s_word *readFile(char *filename){
    char buffer[MAX_LINE_SIZE +1];
    s_word *head=newptr();
    s_word *p= newptr();
    int flag,numwords;
    
    FILE *fp;
    fp=fopen(filename,"r");
    if (fp==NULL){
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    
    numwords=-1;
    while (fscanf(fp, "%s",buffer)==1) {
        p=head;
        flag=0;
        makeLower(buffer);
        while (flag==0) {
            if (numwords==-1) {
                head->key=strdup(buffer);
                head->occurrence=1;
                numwords=1;
                head->nextptr=newptr();
                flag=1;
                continue;
            }
        
            if (p->key!=NULL) {
                if (strcmp(buffer, p->key)==0) {
                    p->occurrence++;
                    flag=2;
                    continue;
                }
                
            }
            
            if (p->key==NULL) {
                p->key=strdup(buffer);
                p->occurrence=1;
                p->nextptr=newptr();
                numwords++;
                flag=3;
                continue;
                
            }
            
            p=p->nextptr;
        }
    }
    fclose(fp);
    return (head);
}

void makeLower(char *word){
    int i;
    
    for (i=0; i<strlen(word); i++) {
        word[i]=tolower(word[i]);
    }
}

void printData(char *filename,s_word *head){
    s_word *p;
    p=head;
    
    FILE *fp;
    fp=fopen(filename,"w");
    if (fp==NULL){
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    
    while (p->key!=NULL) {
        fprintf(fp, "%s %d /n",p->key,p->occurrence);
        p=p->nextptr;
    }
    fclose(fp);
}

void freeList(s_word* head){
    s_word* tmp;
    
    while (head != NULL){
        tmp = head;
        head = head->nextptr;
        free(tmp);
    }
    
}
