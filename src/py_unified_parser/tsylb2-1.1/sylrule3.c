/* file sylrule3.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif

void apply_sylb_rule_III(struct PRON2 *pron, int *hit, pcodeset *pcdp)
                                                 
/******************************************************/
/* Applies syllable-structure-building rule III from  */
/* Kahn's thesis to *pron.                            */
/* This version is slightly different -- if style==2, */
/* it disconnects the C from the following sylb.      */
/* Inhibited from applying across word boundary.      */
/* Returns *hit == T iff rule is applied.             */
/******************************************************/
 {char *proc = "apply_sylb_rule_III";
  int jsylb,iseg,iseg_next,ph_code;
  boolean style = 2;
/* coding */
  db_enter_msg(proc,1);
  *hit = F;
  for (jsylb=1; jsylb < pron->nsylbs; jsylb++)
    {/* is the next sylb in the same word? */
/** NOTE: at this point, we can act like words are composed of    **/
/** syllables because no rules have acted to re-syllabify across  **/
/** word boundaries.                                              **/
     if (pron->sylb[jsylb+1].iword != pron->sylb[jsylb].iword) continue;
     /* does the next sylb start with a C? */
     iseg_next = pron->sylb[jsylb+1].segs.l1;
     ph_code = pron->seg[iseg_next];
     if (!consonantal(ph_code,pcdp)) continue; /* not a C */
     /* is the next syllable unstressed? */
     if (!unstressed(&(pron->sylb[jsylb+1]),pcdp)) continue;
     /* does this sylb end in a vowel ? */
     iseg = pron->sylb[jsylb].segs.l2;
     ph_code = pron->seg[iseg];
     if (consonantal(ph_code,pcdp)) continue; /* not a V */
     /* link 1st C of next sylb to this sylb */
     pron->sylb[jsylb].segs.l2 = pron->sylb[jsylb+1].segs.l1;
     /* and, if style==2, disconnect it from next sylb */
     if (style == 2)
       {pron->sylb[jsylb+1].segs.l1 += 1;
       }
     *hit = T;
    }
  db_leave_msg(proc,1);
  return;
 }
