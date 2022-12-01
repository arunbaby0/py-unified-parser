/* file addstres.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


void add_default_stress(int *istr,pcodeset *pcdp,int i_default_stress)
/****************************************************************/
/* Adds the default stress mark <i_default_stress> before those */
/* syllabic segments in *istr that aren't already marked        */
/* for lexical stress, according to phoneset *pcdp.             */
/****************************************************************/
 {char *proc = "add_default_stress";
  int i,jstr[MAX_SYMBS_IN_STR+1];
  boolean stress_mark_precedes;
db_enter_msg(proc,0);
  stress_mark_precedes = F;
  jstr[0] = 0;
  for (i=1; i <= istr[0]; i++)
    {if (syllabic(istr[i],pcdp) && (!stress_mark_precedes))
       {if (jstr[0] < MAX_SYMBS_IN_STR) jstr[++jstr[0]] = i_default_stress;
        else fprintf(stderr,"*WARNING:%s: integer string OVF.\n",proc);
       }
     if (jstr[0] < MAX_SYMBS_IN_STR) jstr[++jstr[0]] = istr[i];
     else fprintf(stderr,"*WARNING:%s: integer string OVF.\n",proc);
     if (stress_mark(istr[i],pcdp)) stress_mark_precedes = T;
     else                           stress_mark_precedes = F;
    }
  nstrcpy(istr,jstr);
db_leave_msg(proc,0);
  return;
 }
