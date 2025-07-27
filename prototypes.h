/* Elizur Leiman , Yarden Danieli */

/************************************************************ prototypes.h ************************************************************/
/*
    The prototypes.h file contains function prototypes collection from the different parts of the assembler working mechanism  .
*/
/**************************************************************************************************************************************/
#ifndef PROTOTYPES_H

#define PROTOTYPES_H
#include "structs.h" 

/* These functions are the over all pass over the code in three parts: macro -> first -> second*/
void macro_pass(FILE *inputFile);
void first_pass(FILE *fp);
void second_pass(FILE *fp, char *filename);

/******************* Macro pass functions *******************/
void add_to_macros_list(char *line);
void write_output_am(FILE *fp);
void reset_global_vars();

/******************* First pass functions *******************/
unsigned int encode_first_word(int type, int is_first, int is_second, int first_method, int second_method);
int count_additional_words(int is_first, int is_second, int first_method, int second_method);
boolean command_accept_methods(int type, int first_method, int second_method);
boolean command_accept_num_operands(int type, boolean first, boolean second);
int detect_adress_method(char *operand);
int process_command(int type, char *line);
int process_directive(int type, char *line);
int process_data_directive(char *line);
int process_extern_directive(char *line);
int process_string_directive(char *line);
boolean is_label(char *token, int colon);
void read_line(char *line);
void write_num_to_data(int num);
void write_string_to_data(char *str);

/******************* Second pass functions *******************/
unsigned int encode_register_word(boolean is_dest, char *reg);
void check_operands_exist(int type, boolean *is_src, boolean *is_dest);
int encode_additional_words(char *src, char *dest, boolean is_src, boolean is_dest, int src_method, int dest_method);
void encode_additional_word(boolean is_dest, int method, char *operand);
void encode_label(char *label);
int process_command_second_pass(int type, char *line);
void read_line_second_pass(char *line);
void write_output_entry(FILE *fp);
void write_output_extern(FILE *fp);
int write_output_files(char *original);
void write_output_ob(FILE *fp);

#endif