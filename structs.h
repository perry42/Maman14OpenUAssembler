/* Elizur Leiman , Yarden Danieli */

/************************************************************** structs.h **************************************************************/
/*
    The structs.h file contains structs definitions that are general in the project and handle different structures that manage the 
    code flow and the way data is saved in it  .
*/
/**************************************************************************************************************************************/
#ifndef STRUCTS_H

#define STRUCTS_H

#include "assembler.h" 

extern unsigned int data[];           /* An array to save data words */
extern unsigned int instructions[];   /* An array to save instruction words */

typedef enum /* Defining a boolean variable type (we don't have it in ANSI C) */
{
    FALSE,
    TRUE
} boolean; 

/* A linked list of the lales and a separate pointer to that list */
typedef struct structLabels *labelPtr;
typedef struct structLabels
{
    char name[LABEL_LENGTH];   /* Lable's name */
    unsigned int address;      /* It's address */
    boolean external;          /* Is it an extern lable? - T or F */
    boolean inActionStatement; /* Is it an action? - T or F */
    boolean entry;             /* Is it an entry lable? T or F */
    labelPtr next;             /* a pointer to the next label in the list */
} Labels;

/* A macro struct that saves the macro's name and content */
typedef struct
{
    char name[MAX_LINE_LENGTH];    /* The name of the macro */
    char content[MEMORY_CELLS];    /* The content of the macro */
} Macro;

/*A macro linked list */
typedef struct Node
{
    char line[MAX_LINE_LENGTH]; /* Represents a single line of text */
    struct Node *next;          /* Pointer to the next node in the linked list */
} macros_list;

/* Defining a circular double-linked list to store each time the program uses an extern label, and a pointer to that list */
typedef struct ext *extPtr;
typedef struct ext
{
    char name[LABEL_LENGTH]; /* Extern lable's name */
    unsigned int address;    /* Memory address */
    extPtr next;             /* A pointer to the next extern in the list */
    extPtr prev;             /* A pointer to the previous extern in the list */
} ext;

#endif