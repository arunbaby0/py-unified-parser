/* file pronseq3.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif

 boolean prons_eq3(struct PRON_SPEC *pron1, struct PRON_SPEC *pron2)
                                 
/**************************************************************************/
/* Determines if the two prons are equal or not, ignoring tags            */
/**************************************************************************/
 {char *proc = "prons_eq3";
/* code */
  int i;
  boolean same;
 db_enter_msg(proc,1); /* debug only */
  same = T;
/* check cats */
  if (!streq(pron1->cats,pron2->cats))
    {if (streq(pron1->cats,"*") || streq(pron2->cats,"*")) same = T;
     else {same = F; goto RETURN;}
    }
/* check phon */
  if ((pron1->iphon[0] == 0)&&(pron2->iphon[0] == 0))
    {if (!streq(pron1->phon,pron2->phon)) same = F;
    }
  else
    {/* compare integer phone strings */
     if (pron1->iphon[0] != pron2->iphon[0]) same = F;
     else
       {for (i = 1; (same && (i <= pron1->iphon[0])); i++)
          if (pron1->iphon[i] != pron2->iphon[i]) same = F;
    }  }
RETURN:
 db_leave_msg(proc,1); /* debug only */
  return same;
 }
