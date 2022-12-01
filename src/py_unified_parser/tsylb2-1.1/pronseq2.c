/* file pronseq2.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


boolean eq_ex_rate2(struct PRON2 *pron1, struct PRON2 *pron2)
                            
/*****************************************************/
/* Decides if 2 prons are equal, except for "rate".  */
/*****************************************************/
 {boolean match;
  int i;
  match = T;
  if ((!nstreq(pron1->seg,pron2->seg)) ||
      (pron1->nsylbs != pron2->nsylbs) ||
      (pron1->nwords != pron2->nwords) )
     match = F;
  else
    {for (i=1; (match && (i <= pron1->nsylbs)); i++)
       {if ((pron1->sylb[i].nucleus != pron2->sylb[i].nucleus) ||
            (pron1->sylb[i].segs.l1 != pron2->sylb[i].segs.l1) ||
            (pron1->sylb[i].segs.l2 != pron2->sylb[i].segs.l2) ||
            (pron1->sylb[i].stress != pron2->sylb[i].stress) ||
            (pron1->sylb[i].iword != pron2->sylb[i].iword) )
           match = F;
       }
     for (i=1; (match && (i <= pron1->nwords)); i++)
       {if ((pron1->word[i].segs.l1 != pron2->word[i].segs.l1) ||
            (pron1->word[i].segs.l2 != pron2->word[i].segs.l2) )
          match = F;
       }
    }
  return match;
 }
