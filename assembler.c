/* Elizur Leiman , Yarden Danieli */

/************************************************************** MAIN function **************************************************************/
/*
    This is the *main* function of an imaginary assembly language that was invented for the final 
    project - MMN14 in 20465 course at the open university.

    This program, over its all .c and .h files (that are described independently), is getting a raw
    text written as an assembly code (syntax and structure is described in MMN14 2023 B) in a .as file.
    After processing the file it will do the following:

    If file is Valid - 4 new file will be created:
    1) .am file - the same assembly program after macros expansion.
    2) .ext file - lines of text that show any external symbol and any memory adress that is related to that symbol, in the code.
    3) .ent file - lines of text showing an entry symbol and the memory address where it was defined.  
    4. .ob file - a so called object file with the full memory image of the code - all code words encoded to base 64, line by line.

    If file is not valid:
    1) .am file will be created as default after macro expansion.
    2) All errors that were detected will be written as standard output to the terminal in the following pattern:
                             " Error (line #):' Text explaining to error origin'." 
*/

/* We define global variables here because they are defined as extern,
   and therefore must be initialized in a specific C file. */

/* Some global variables are essential for the program to run fluently */
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "prototypes.h"
#include "externals.h"
#include "tools.h"
#include "assembler.h"

unsigned int data[MEMORY_CELLS];
unsigned int instructions[MEMORY_CELLS];
int ic;                                     /* The instructions counter*/
int dc;                                     /* The data counter*/
int err;                                    /* A variable to hold errors*/
labelPtr symbols_table;                     
extPtr externals_list;
boolean entry_exists, extern_exists, was_error;
/*macros_list *macros_list_head;*/

/* The array of the 'digits' of base 64 numbers */
const char base64[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

/* The array of the different commands in the particular assembly language */
const char *commands[] = {
    "mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne",
    "red", "prn", "jsr", "rts", "stop"};

/* An array of the different registers in the computer hardware */
/*const char *registers[] = {
    "@r0",
    "@r1",
    "@r2",
    "@r3",
    "@r4",
    "@r5",
    "@r6",
    "@r7",
};*/

/* A array for the different directives that may be used in an assembly program */
const char *directives[] = {
    ".data", ".string", ".entry", ".extern"};

/* This function handles all activities in the program, it receives command line arguments for .as filenames and will 
   export the relevant files */

macros_list *macros_list_head;
  void reset_global_vars()
{
    macros_list *temp;

    while (macros_list_head != NULL)
    {
        temp = macros_list_head;
        macros_list_head = macros_list_head->next;
        free(temp);
    }
    symbols_table = NULL;
    externals_list = NULL;

    entry_exists = FALSE;
    extern_exists = FALSE;
    was_error = FALSE;
} 

int main(int argc, char *argv[])
{
    int i;
    char *input_filename, *input_filename_after_mac;
    FILE *fp, *tp;

    for (i = 1; i < argc; i++)   /* Start running over command line arguments that represent a .as file*/
    {
        input_filename = create_file_name(argv[i], FILE_INPUT); /* Appending .as to filename */
        tp = fopen(input_filename, "r");

        if (tp != NULL)
        { /* If file exists */
            input_filename_after_mac = create_file_name(argv[i], FILE_MACRO);


            if (tp != NULL)
            {
                printf("\n*-------------------------------------------- Started assembling %s --------------------------------------------*\n\n", input_filename);
                reset_global_vars();

                macro_pass(tp);
                if (!was_error)
                {
	            fp = fopen(input_filename_after_mac, "w+");
                    write_output_am(fp);
                    rewind(fp);

                    first_pass(fp);
                }

                if (!was_error)
                { /* procceed to second pass */
                    rewind(fp);
                    second_pass(fp, argv[i]);
                }

                printf("\n\n*-------------------------------------------- Finished assembling %s --------------------------------------------*\n\n", input_filename);
            }
            else
            {
                err = CANNOT_OPEN_FILE;
                write_error(NOT_FOUND);
            }
        }
        else
        {
            printf("\n\n*-------------------------------------------- Assembling %s has failed --------------------------------------------*\n\n", input_filename);
            err = CANNOT_OPEN_FILE;
            write_error(NOT_FOUND);
            continue;
        }
    free(input_filename);
    free(input_filename_after_mac);
    }

    return 0;
}


