/* Elizur Leiman , Yarden Danieli */

/************************************************************** macro_pass.c **************************************************************/
/*
    The macro_pass.c file are functions in the code that are being used to expand the macros in the assembly program.
    At the end of this pass a .am file is created, and is the platform for th following first and second passes. 
*/
/**************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"
#include "structs.h"
#include "tools.h"
#include "externals.h"
#include "prototypes.h"



/* A void function  reset the global variables to their default values */


/* Function to remove macro declarations from the input file */
void macro_pass(FILE *fp)
{
    char line[LABEL_LENGTH];        /* Buffer to store a line of text */
    char lineCopy[LABEL_LENGTH];    /* Copy of the line for parsing */
    Macro macroTable[LABEL_LENGTH]; /* Array to store macro declarations */
    int macroCount = 0;             /* Number of macro declarations */
    int isInMacroBlock = 0;         /* Flag to indicate if currently inside a macro block */
    int i;                          /* Loop counter */
    int foundMacro;                 /* Flag to indicate if a macro was found */
    Macro newMacro;                 /* Temporary macro declaration */
    Macro *currentMacro;            /* Pointer to the current macro declaration */
    char contentCopy[LABEL_LENGTH]; /* Copy of macro content for parsing */
    char *content;                  /* Pointer to the macro content */
    char *parsedLine;               /* Parsed line from macro content */
    int linecount = 0;
    char param1[LABEL_LENGTH], param2[LABEL_LENGTH], param3[LABEL_LENGTH];/* params for argument*/
	int numParams;

    const char *registers[] = {
    "@r0",
    "@r1",
    "@r2",
    "@r3",
    "@r4",
    "@r5",
    "@r6",
    "@r7",
	"r0",
    "r1",
    "r2",
    "r3",
    "r4",
    "r5",
    "r6",
    "r7"
    };
    while (fgets(line, LABEL_LENGTH, fp) != NULL)
    {
        
        line[strcspn(line, "\n")] = '\0'; /* Remove the trailing newline character */

        strcpy(lineCopy, line);
		numParams = sscanf(lineCopy, "%s%*[\t ]%s%*[\t ]%s", param1, param2, param3);


        if (numParams == 0)
        {
            add_to_macros_list("");
            continue;
        }
        if (strcmp(param1, "mcro") == 0)
        { /* Found a macro declaration */
            isInMacroBlock = 1;

            /* if there is no macro name*/
            if (numParams != 2)           
            {
                was_error = TRUE;
                err = MACRO_TO_MANY_OR_MISSING_PARAM;
                write_error(linecount);
                return;
            }
            strcpy(newMacro.name, param2); /* look its copy even though its not sure the code will continue*/

            if (find_index(param2, registers, 16) != NOT_FOUND)
            {
                was_error = TRUE;
                err = MACRO_CANNOT_BE_REGISTER;
                write_error(linecount);
            }
            for (i = 0; i < macroCount; i++)
            {
                if (strcmp(param2, macroTable[i].name) == 0)
                {
                    was_error = TRUE;
                    err = MACRO_ALREADY_EXIST;
                    write_error(linecount);
                }
            }
            if (find_index(param2, commands, COMMANDS) != NOT_FOUND)
            {
                was_error = TRUE;
                err = MACRO_CANNOT_BE_COMMAND;
                write_error(linecount);
            }

            newMacro.name[LABEL_LENGTH - 1] = '\0'; /* Ensure the name is null-terminated */
            strcpy(newMacro.content, "");
            macroTable[macroCount++] = newMacro;
        }
        else if (strcmp(param1, "endmcro") == 0)
        { /* End of a macro declaration block */
            if (numParams > 1)
            {
                was_error = TRUE;
                err = MACRO_TO_MANY_OR_MISSING_PARAM;
                write_error(linecount);
                return;
            }
            isInMacroBlock = 0;
        }
        else if (!isInMacroBlock)
        { /* Not in a macro block, check for macro usage */
            foundMacro = 0;

            for (i = 0; i < macroCount; i++)
            {
                if (strcmp(param1, macroTable[i].name) == 0)
                { /* Found a matching macro */
                    if (numParams >1)
                    {
                        was_error = TRUE;
                        err = MACRO_TO_MANY_OR_MISSING_PARAM;
                        write_error(linecount);
                        return;
                    }
                    foundMacro = 1;
                    content = macroTable[i].content;
                    strcpy(contentCopy, content);
                    parsedLine = strtok(contentCopy, "\n");
                    while (parsedLine != NULL)
                    {
                        add_to_macros_list(parsedLine);
                        parsedLine = strtok(NULL, "\n");
                    }
                    break;
                }
            }

            if (!foundMacro)
            {
                add_to_macros_list(line); /* Add the line as itis to the linked list */
            }
        }
        else
        {
            currentMacro = &macroTable[macroCount - 1];
            strcat(currentMacro->content, line);
            strcat(currentMacro->content, "\n");

        }
		linecount++;
    }

    fclose(fp);
}
/* Function to add a line to the end of the linked list */
void add_to_macros_list(char *line)
{
    macros_list *newNode = (macros_list *)malloc(sizeof(macros_list));
    macros_list *current;
    strcpy(newNode->line, line);
    newNode->next = NULL;

    if (macros_list_head == NULL)
    {
        macros_list_head = newNode;
    }
    else
    {
        current = macros_list_head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void write_output_am(FILE *fp)
{
    macros_list *current = macros_list_head;
    while (current != NULL)
    {
        fprintf(fp, "%s\n", current->line);
        current = current->next;
    }
}
