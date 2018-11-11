/*
Exercise 02
-----------

A file contains data on a set of employees.
For each employee there is a row of the file, including:
* Last and first name (a single C string, maximum 50 characters,
  e.g., Smith_John).
* Personal identification (exactly 16 characters).
* Data of hiring (format dd.mm.yyy, e.g, 30.05.2005).
* Salary (integer value, in euro).
Fields are space-separated.
Employees do not appear in any specific order.

A C program receives 3 parameters on the command line:
* Input file name (the format is the previously defined one).
* A single strings, representing a last and first name pair (e.g.,
  Clinton_Bill).
* A string made of only + and - characters (e.g., +++---+-+).

The program has to:
* Read the file.
* Store its content in a LIFO-logic list, but with two pointers for
  each element one pointing ahead and one pointing behind the element
  itself as:

  pHead  --> ----- --> ----- --> ----- --> ----- -X
             |###|     |###|     |###|     |###|
          X- ----- <-- ----- <-- ----- <-- -----

* Find in the list the element storing the employee whose name is
* passed on the command line as a second parameter.
* Move along the list in the
  - right direction for each '+' character
  - left direction for each '-' character
  in the third string parameter.
  For each visited node of the list (including the first one) the
  program has to print out (on standard output) all data of the
  employee (with the same format this data appears in the original
  input file).
  If the end of the list is reached (in either side) the program has to
  print-out the same element repeatedly.
*/






#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_SIZE 1000
#define ID_LEN 20
#define DATE 10
#define MAX_NAME 50

//DEBUG
#define F1 "file1.txt"
#define F2 "Giallo_Antonio"
#define F3 "---+"



typedef struct s_person s_person;
struct s_person {
    char *name;
    char id[ID_LEN+1];
    char date[DATE+1];
    int salary;
    s_person *prevptr;
    s_person *nextptr;
};

s_person *newptr(void);
s_person *readFile(char *filename);
s_person *findPerson(s_person *head, char name[MAX_NAME+1]);
void movingGame(s_person *start, char *map);
void freeList(s_person* head);



int main(int argc,char *argv[]){
    
    if (argc!= 4) {
        fprintf(stderr, "usage: <filename> <person> <movement>\n");
        exit(EXIT_FAILURE);
    }

    s_person *head,*person;
    
    head=readFile(argv[1]);
    person=findPerson(head, argv[2]);
    movingGame(person,argv[3]);
    freeList(head);
    


    
    
return (0);
   
}

s_person *newptr(void){
    s_person *newptr=malloc(sizeof(s_person));
    if (newptr==NULL) {
        fprintf(stdout, "Error allocating memory");
        exit(EXIT_FAILURE);
    }
    return (newptr);
}

s_person *readFile(char *filename){
   
    s_person *bottom, *p;
    char tmp_name[MAX_NAME+1];
    bottom=newptr();
    p=newptr();
    
    FILE *fp;
    fp=fopen(filename,"r");
    if (fp==NULL){
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    
    p=bottom;
    while (fscanf(fp, "%s %s %s %d",tmp_name,p->id,p->date,&p->salary)==4) {
        p->name=strdup(tmp_name);
        
        p->prevptr=newptr();
        p->prevptr->nextptr=p;
        p=p->prevptr;
        
    }
    
    fclose(fp);
    return (p->nextptr);
}

s_person *findPerson(s_person *head, char name[MAX_NAME+1]){
    s_person *p;
    
    p=head;
    
    while (p->nextptr!=NULL) {
        if (strcmp(p->name, name)==0) {
            return (p);
        }
        else
            p=p->nextptr;
    }
    
    fprintf(stdout, "Person not found on file");
    exit(1);
}

void movingGame(s_person *start, char *map){
    
    s_person *p;
    p=start;
    
    fprintf(stdout, "%s %s %s %d\n",start->name,start->id,start->date,start->salary);
    for (int i=0; i<strlen(map); i++) {
        if (map[i]=='-') {
            if (p->prevptr->name!=NULL) {
                p=p->prevptr;
                fprintf(stdout, "%s %s %s %d\n",p->name,p->id,p->date,p->salary);
            }
            else
                fprintf(stdout, "%s %s %s %d\n",p->name,p->id,p->date,p->salary);
        }
        else{
            if (p->nextptr!=NULL) {
                p=p->nextptr;
                fprintf(stdout, "%s %s %s %d\n",p->name,p->id,p->date,p->salary);
            }
            else
                fprintf(stdout, "%s %s %s %d\n",p->name,p->id,p->date,p->salary);
        }
    }
}

void freeList(s_person* head){
    s_person* tmp;
    
    while (head->nextptr!= NULL){
        tmp = head;
        head = head->nextptr;
//        free(tmp->name);
        free(tmp);
    }
    
}
