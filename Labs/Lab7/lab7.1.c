/*
Exercise 01
-----------

A "producer" file includes a line for each car manufacturer with the
following format:
manufactuiredName id
where manufacturerName and id are strings of 20 characters at most.
The following is a correct example:

FIAT it001
ALFA_ROMEO it002
BMW ge001
MERCEDES ge002
TOYOTA ja001
...

The size of the file, and the order of the lines within the file, are
unknown.

A "product" file stores the product names and relative prices for each
product of each manufacturer, with the format:
id productName price
The following one is a correct example:

it001 500 15131
it001 Panda 12001
it001 Punto 17891
ge002 AClass 22411
ge002 CClass 75641
...

The size (and order) of the file is unknown.

Write a C program that:
* receives two file names on the command line
* stores the content of the two files (the first one of type "producer",
  the second one of type "product") in a proper data structure
* goes through an iteration in which it reads the name of a
  manufacturer (e.g, FIAT) and it prints-out all products (and
  relative prices) produced by it on standard output.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//DEBUG
#define F1 "file1.txt"
#define F2 "file2.txt"

typedef struct s_car s_car;
struct s_car{
    //char id[5];
    char car[20];
    int price;
    s_car *nextptr;

};
typedef struct s_brand s_brand;
struct s_brand{
    char name[21];
    char id[6];
    s_brand *nextptr;
    s_car *carptr;

};

s_brand *brand_newptr(void);
s_car *car_newptr(void);
s_brand *read_file_brand(char *filename,int *numbrand);
s_brand *read_file_car(char *filename, s_brand *head, int numbrand);
void add_car_list(s_brand *p,s_car t);
void print_data(s_brand *head,int numbrand);
void freeList(s_brand* head);


int main(int argc, char const *argv[]) {

    int numbrand;
    s_brand *head;


    head=read_file_brand(F1,&numbrand);
    head=read_file_car(F2, head,numbrand);
    print_data(head,numbrand);


    return 0;
}

s_brand *brand_newptr(void){

    s_brand *newptr=malloc(sizeof(s_brand));
    newptr->carptr=NULL;
    newptr->nextptr=NULL;
    if (newptr==NULL) {
        fprintf(stdout, "Error allocating memory");
        exit(EXIT_FAILURE);
    }

    return (newptr);
}

s_car *car_newptr(void){

    s_car *newptr=malloc(sizeof(s_car));
    newptr->nextptr=NULL;
    if (newptr==NULL) {
        fprintf(stdout, "Error allocating memory");
        exit(EXIT_FAILURE);
    }

    return (newptr);
}

s_brand *read_file_brand(char *filename, int *numbrand){

    s_brand *head,*p;
    head=brand_newptr();
    p=head;

    FILE *fp;
    fp=fopen(filename,"r");
    if (fp==NULL){
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    *numbrand=0;
    while (fscanf(fp,"%s %s",p->name,p->id)==2) {
        *numbrand=*numbrand+1;
        p->nextptr=brand_newptr();
        p=p->nextptr;
    }
    return (head);
}

s_brand *read_file_car(char *filename, s_brand *head,int numbrand){

    FILE *fp;
    fp=fopen(filename,"r");
    if (fp==NULL){
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    s_brand *p;
    p=head;
    s_car t;
    char tmpid[6];

    while (fscanf(fp,"%s %s %d",tmpid,t.car,&t.price)==3) {
        for (int i = 0; i < numbrand; ++i){

            if (strcmp(tmpid,p->id)==0){
                add_car_list(p,t);
                break;
            }
            p=p->nextptr;

        }
    }
    return(head);
}

void add_car_list(s_brand *p,s_car t) {
    s_car *g;
    g=p->carptr;
    if (g==NULL) {
        p->carptr=car_newptr();
        strcpy(p->carptr->car, t.car);
        p->carptr->price=t.price;
        return;
    }
    while (g->nextptr!=NULL) {
        g=g->nextptr;
    }
    g->nextptr=car_newptr();
    g=g->nextptr;
    strcpy(g->car, t.car);
    g->price=t.price;
}

void print_data(s_brand *head, int numbrand) {

    s_car *c;
    s_brand *p;
    p=head;
    for (int i = 0; i < numbrand; ++i){
        c=p->carptr;
        fprintf(stdout, "\nBRAND: %s\n", p->name);
        while (c!=NULL) {
            fprintf(stdout, " - %s €%d\n", c->car,c->price);
            c=c->nextptr;
        }
        p=p->nextptr;
    }


}
