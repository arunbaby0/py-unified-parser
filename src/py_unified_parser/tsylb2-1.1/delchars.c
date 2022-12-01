/* file delchars.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif

void del_chars(char *sx, char *chars)                  
/************************************************************/
/* deletes all occurrances of characters in *char from *sx. */
/************************************************************/
 {char *p, offset;
  offset = 0;
  for (p=sx; *p != '\0'; p++)
    {if (strchr(chars,*p) != NULL) offset += 1;
     else *(p-offset) = *p;
    }
  *(p-offset) = '\0';
  return;
 }
