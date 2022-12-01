/* file sylrule4.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif

void apply_sylb_rule_IV(struct PRON2 *pron, int *hit, pcodeset *pcdp)
                                                 
/******************************************************/
/* Applies syllable-structure-building rule IV from   */
/* Kahn's thesis to *pron.                            */
/* Inhibited from applying across word boundary.      */
/* Returns *hit == T iff rule is applied.             */
/******************************************************/
 {char *proc = "apply_sylb_rule_IV";
  int jsylb,iseg,ph_code;
  struct INTERVAL1 cluster;
/* coding */
  db_enter_msg(proc,1);
  *hit = F;
  for (jsylb=1; jsylb < pron->nsylbs; jsylb++)
    {/* is the next sylb in the same word? */
/** NOTE: at this point, we can act like words are composed of    **/
/** syllables because no rules have acted to re-syllabify across  **/
/** word boundaries.                                              **/
     if (pron->sylb[jsylb+1].iword != pron->sylb[jsylb].iword) continue;
     /* Does this syllable end in a C? */
     iseg = pron->sylb[jsylb].segs.l2;
     ph_code = pron->seg[iseg];
     if (!consonantal(ph_code,pcdp)) continue;
     /* is the next syllable unstressed? */
     if (!unstressed(&(pron->sylb[jsylb+1]),pcdp)) continue;
     /* would the result be a TRULY impossible initial cluster? */
     cluster.l1 = iseg;
     cluster.l2 = pron->sylb[jsylb+1].nucleus - 1;
     if (bad_init_cluster(pron->seg,cluster,pcdp)) continue;
     /* link last C of this sylb to next sylb */
     pron->sylb[jsylb+1].segs.l1 = pron->sylb[jsylb].segs.l2;
     *hit = T;
    }
  db_leave_msg(proc,1);
  return;
 }
