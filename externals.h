/* Elizur Leiman , Yarden Danieli */

/************************************************************** structs.h **************************************************************/
/*
    The externals.h file contains differen external variables that should be valid and accesible all over assembler files.
*/
/**************************************************************************************************************************************/

#include "structs.h"
#include "assembler.h"

extern int ic, dc;                           /* Data and instruction counters */
extern int err;                              /* The error that was detected*/
extern boolean was_error;                    /* Is there a detected error? T or F*/
extern labelPtr symbols_table;               /* The symbol table that catches the lables*/
extern extPtr externals_list;                /* The list of external variables  */
extern const char base64[64];                /* The array that holds the base 64 digits*/
extern const char *commands[];               /* Array for the 16 command list*/
extern const char *directives[];             /* Array for the 4 different directives*/
extern boolean entry_exists, extern_exists;  /* Is thare an entry or an extern lable? T or F*/
extern macros_list *macros_list_head;