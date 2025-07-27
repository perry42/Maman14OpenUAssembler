/* Elizur Leiman , Yarden Danieli */

/**************************************************************assembler.h**************************************************************/
/*
    The assembler.h file contains macro definitions and enums that are general in the project and handle all hardware parameter
    and the different properties of the unique assembly language as described in mmn14 - 2023.
*/
/**************************************************************************************************************************************/
#ifndef ASSEMBLER_H

#define ASSEMBLER_H

/**************************************** Default values ****************************************/

#define MEMORY_START_POINT 100       /* The memory occupied by code words starts at 100 (page 32) */
#define EMPTY_WORD 0                 /* A default value for an empty code word */ 
#define EXTERNAL_DEFAULT_ADDRESS 0   
#define NOT_FOUND -1                 /* A general macro for a case that an operand, command etc. is not found*/
#define NO_ERROR 0                   /* Errors handeling default state - no error */
#define ERROR 1                      /* Errors handeling default state - error exists */

/**************************************** Variables limits ***************************************/

#define MAX_LINE_LENGTH 80                          /* The limit for characters in a single line */
#define MINIMUM_LABEL_LENGTH 2                      /* The minimal characters for a label with a colon */
#define MINIMUM_LABEL_LENGTH_WITHOUT_COLON 1        /* The minimal characters for a label without a colon */
#define LABEL_LENGTH 30                             /* The limit for characters in a single lable */
#define MAX_COMMAND_LENGTH 4                        /* The upper limit for characters in a command */
#define MIN_COMMAND_LENGTH 3                        /* The lower limit for characters in a command */
#define REGISTER_LENGTH 3                           /* A register's name composed of 3 characters - @ then r and a number in [0,7] */
#define MAX_EXTENSION_LENGTH 5                      /* The limit for file extention (i.e am,as,extern,entry,object) for proper memory alloc. */
#define BASE64_SEQUENCE_LENGTH 3                    /* A base64 code of a word (number) consists of 2 characters (base-64 digits) (and '\0' ending) */

/**************************************** Additional assembly constants ***************************/

#define DIRECTIVES 4        /* Number of directives in assemble language */
#define COMMANDS 16         /* number of commands in assembly language */

/* Encoding related information */
#define WORD_BITS 12               /* The number of bits in code word */
#define OPCODE_BITS 4              /* The bits dedicated for the opcode */ 
#define ADDRESSING_METHOD_BITS 3   /* The bits dedicated for the addressing method (1-001,3-011,5-101) */
#define ARE_BITS 2                 /* Bits in ARE field */
#define REGISTER_BITS 5            /* Bits in register encoding field */

/* Page 21 constants: addressing methods ("source" and "destination") bits positioning in the *first* code-word of a command and memory*/
#define SRC_METHOD_START_POS 9
#define SRC_METHOD_END_POS 11     /* Source operand addressing is between 9-11 bits */
#define DEST_METHOD_START_POS 2
#define DEST_METHOD_END_POS 4     /* Destination operand addressing is between 2-4 bits */
#define MEMORY_CELLS 1024         /* The total memory (RAM) in the hardware part */ 

/********************************************** Enums **********************************************/

/* Directives types */
enum directives
{
    DATA,
    STRING,
    ENTRY,
    EXTERN,
    UNKNOWN_TYPE
};

/* Enum of commands - enumeration is parallel to their opcode */
enum commands
{
    MOV,
    CMP,
    ADD,
    SUB,
    NOT,
    CLR,
    LEA,
    INC,
    DEC,
    JMP,
    BNE,
    RED,
    PRN,
    JSR,
    RTS,
    STOP,
    UNKNOWN_COMMAND
};

/* Enum of different errors we thought that may occure */
enum errors
{
    SYNTAX_ERR = 1,
    MACRO_ALREADY_EXIST,
    MACRO_CANNOT_BE_COMMAND,
    MACRO_CANNOT_BE_REGISTER,
    MACRO_TO_MANY_OR_MISSING_PARAM,
    LABEL_ALREADY_EXISTS,
    LABEL_TOO_LONG,
    LABEL_INVALID_FIRST_CHAR,
    LABEL_ONLY_ALPHANUMERIC,
    LABEL_CANT_BE_COMMAND,
    LABEL_ONLY,
    LABEL_CANT_BE_REGISTER,
    DIRECTIVE_NO_PARAMS,
    DIRECTIVE_INVALID_NUM_PARAMS,
    DATA_COMMAS_IN_A_ROW,
    DATA_EXPECTED_NUM,
    DATA_EXPECTED_COMMA_AFTER_NUM,
    DATA_UNEXPECTED_COMMA,
    STRING_TOO_MANY_OPERANDS,
    STRING_OPERAND_NOT_VALID,
    EXPECTED_COMMA_BETWEEN_OPERANDS,
    EXTERN_NO_LABEL,
    EXTERN_INVALID_LABEL,
    EXTERN_TOO_MANY_OPERANDS,
    COMMAND_NOT_FOUND,
    COMMAND_UNEXPECTED_CHAR,
    COMMAND_TOO_MANY_OPERANDS,
    COMMAND_INVALID_METHOD,
    COMMAND_INVALID_NUMBER_OF_OPERANDS,
    COMMAND_INVALID_OPERANDS_METHODS,
    ENTRY_LABEL_DOES_NOT_EXIST,
    ENTRY_CANT_BE_EXTERN,
    COMMAND_LABEL_DOES_NOT_EXIST,
    CANNOT_OPEN_FILE
};

/* This enum helps to specify if a label should contain a colon or not */
enum
{
    NO_COLON,
    COLON
};

/* Addressing methods ordered by their code (1-immediate, 3-direct and 5-register) */
enum methods
{
    IMMEDIATE_ADDRESSING = 1,
    DIRECT_ADDRESSING = 3,
    REGISTER_ADDRESSING = 5,
    METHOD_UNKNOWN = 6
};

/* Enum of ARE field - enumeration is parallel to their code (absolute - 0, external - 1, relocatable - 2) */
enum ARE
{
    ABSOLUTE,
    EXTERNAL,
    RELOCATABLE
};

/* Enum that includes the different outpot files that the assembler generates */
enum filetypes
{
    FILE_MACRO,
    FILE_INPUT,
    FILE_OBJECT,
    FILE_ENTRY,
    FILE_EXTERN
};

#endif