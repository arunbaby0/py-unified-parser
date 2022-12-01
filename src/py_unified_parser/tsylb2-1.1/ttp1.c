/* file ttp1.c                                               */
/* function ttp1(stx,sp,perr) for converting text to phones */
/* and its sub-functions.                                   */
/* Uses character functions defined in letfcns1.c           */
/* Marks NO stress.                                         */
/* Output phones are from standard phone set "phon1ax.pcd"  */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif



  /*********************************************/
  /*  char *ttp1(stx,sp,perr)                  */
  /*  Converts text to phones                  */
  /*  Input: *stx is a text string;            */
  /*  Output: *sp is a phone string;           */
  /*  Process: elementary.                     */
  /*  Returns *perr > 0 iff error.             */
  /*********************************************/
  char *ttp1(char *stx, char *sp, int *perr)
   {char *proc = "ttp1";
    char *p,*q;
    boolean in_stress_symb;
/* code */
 db_enter_msg(proc,1); /* debug only */
    *perr = 0;
if (db_level > 2) printf("%sinput='%s'\n",pdb,stx);
  /* get stressed phones */
    p = ttp1s(stx,sp,perr);
  /* delete stress markers */
    q = sp;
    in_stress_symb = F;
    for (p = sp; *p != '\0'; p++)
      {if (in_stress_symb)
         {if (*p == ' ') in_stress_symb = F;
	 }
       else
         {if (*p == '\'') in_stress_symb = T;
          else
            {*(q++) = *p;
      }  }  }
    *q = '\0';
if (db_level > 2) printf("%soutput='%s'\n",pdb,sp);
 db_leave_msg(proc,1); /* debug only */
    return sp;
   }
/* end file ttp1.c */
