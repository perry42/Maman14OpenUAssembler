/* Elizur Leiman , Yarden Danieli */

/************************************************************** tools.h **************************************************************/
/*
    The tools.h file contains all functions prototypes that are used as tools to proces the different lables, detect and characterize
    them, and also process their encoding. As well as error output messages functions.
*/
/**************************************************************************************************************************************/

#include "structs.h"
#include <stdio.h>

/* Useful functions that are used for parsing tokens and splitting the text efficiently */
char *next_token_string(char *dest, char *line);
char *nexternals_list_token(char *dest, char *line);
char *next_token(char *seq);
char *skip_spaces(char *ch);
void copy_token(char *dest, char *line);
int end_of_line(char *line);
int skip(char *line);

/* Helpful functions that are used to determine the type of a certain token */
int find_index(char *token, const char *arr[], int n);
int find_command(char *token);
int find_directive(char *token);
boolean is_string(char *string);
boolean is_number(char *seq);
boolean is_register(char *token);

/* Functions that are used for exporting files and assigning the relevant required extension to the file */
char *create_file_name(char *original, int type);
FILE *open_file(char *filename, int type);
char *convert_to_base_64(unsigned int num);

/* Functions of external labels positions' linked list */
extPtr add_external(extPtr *hptr, char *name, unsigned int reference);
void free_external(extPtr *hptr);
void print_external(extPtr h);

/* Functions of the symbols table (as described in mmn 14) */
labelPtr add_label(labelPtr *hptr, char *name, unsigned int address, boolean external, ...);
int delete_label(labelPtr *hptr, char *name);
void free_labels(labelPtr *hptr);
void offset_addresses(labelPtr label, int num, boolean is_data);
unsigned int get_label_address(labelPtr h, char *name);
labelPtr get_label(labelPtr h, char *name);
boolean is_existing_label(labelPtr h, char *name);
boolean is_external_label(labelPtr h, char *name);
int make_entry(labelPtr h, char *name);
void print_labels(labelPtr h);

/* Functions that handle differen errors may arise during assembler run */
void write_error(int line_num); /* This function is called when an error output is needed */
int is_error();

/* Helper functions for encoding and building code words - the first, and any extra word needed */
unsigned int extract_bits(unsigned int word, int start, int end);
void encode_to_instructions(unsigned int word);
unsigned int put_are(unsigned int info, int are);