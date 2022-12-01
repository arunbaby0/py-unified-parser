/* file sylrule5.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif

void apply_sylb_rule_V(struct PRON2 *pron, int *hit, pcodeset *pcdp)
                                                 
/******************************************************/
/* Applies syllable-structure-building rule V from    */
/* Kahn's thesis to *pron.                            */
/* NOT Inhibited from applying across word boundary.  */
/* Returns *hit == T iff rule is applied.             */
/******************************************************/
 {char *proc = "apply_sylb_rule_V";
  int jsylb,iseg,ph_code;
/* coding */
  db_enter_msg(proc,1);
  *hit = F;
  for (jsylb=1; jsylb < pron->nsylbs; jsylb++)
    {/* Does this syllable end in a C? */
     iseg = pron->sylb[jsylb].segs.l2;
     ph_code = pron->seg[iseg];
     if (!consonantal(ph_code,pcdp)) continue;
     /* Does the next syllable start with a V? */
     iseg = pron->sylb[jsylb+1].segs.l1;
     ph_code = pron->seg[iseg];
     if (consonantal(ph_code,pcdp)) continue; /* not a V */
     /* link last C of this sylb to next sylb */
     pron->sylb[jsylb+1].segs.l1 = pron->sylb[jsylb].segs.l2;
     *hit = T;
    }
  db_leave_msg(proc,1);
  return;
 }
