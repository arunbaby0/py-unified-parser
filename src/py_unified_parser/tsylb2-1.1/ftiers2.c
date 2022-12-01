/* file ftiers2.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


void fold_tiers2(WCHAR_T *sint, struct PRON2 *pron, int *lmark, int *rmark, int *wbound)
                                  
                            
/*****************************************************************/
/* Takes pronunciation structure in PRON2 *pron and folds its    */
/* tiers into the int string *s.                                 */
/* "lmark", "rmark", and "wbound" are int strings representing   */
/* the left and right syllable boundary marks and word boundary  */
/* mark, respectively.                                           */
/*****************************************************************/
 {char *proc = "fold_tiers2";
  int iph, nph,iword,ksylb,nsylbs;
  int dbi;
/* coding */
  db_enter_msg(proc,1);

if (db_level > 2)
 {printf("%son entry, lmark =",pdb);
  for (dbi=1; dbi <= lmark[0]; dbi++) printf("%4d",lmark[dbi]);
  printf(", rmark =");
  for (dbi=1; dbi <= rmark[0]; dbi++) printf("%4d",rmark[dbi]);
  printf(", wbound =");
  for (dbi=1; dbi <= wbound[0]; dbi++) printf("%4d",wbound[dbi]);
  printf("\n");
  dump_pron2(pron);
 }
  nph = 0;
  nsylbs = pron->nsylbs;
  iword = 1;
  ksylb = 1;
  sint[0] = 0;
  nph = pron->seg[0];
  for (iph=1; iph <= nph; iph++)
    {/* if iph is first seg of a word, push wbound */
     for (iword=1; iword <= pron->nwords; iword++)
       {if (pron->word[iword].segs.l1 == iph) nstrcat(sint,wbound);
       }  /* (the slow but sure way) */
     /* if iph is first seg of this sylb or the next if any, push "[" */
     if (((ksylb <= nsylbs)&&(iph == pron->sylb[ksylb].segs.l1)) || 
         ((ksylb <  nsylbs)&&(iph == pron->sylb[ksylb+1].segs.l1)))
       nstrcat(sint,lmark);
     /* if seg is nucleus of a sylb with non-zero stress, push it */
     if (iph == pron->sylb[ksylb].nucleus)
        sint[++sint[0]] = pron->sylb[ksylb].stress;
     /* push segment itself */
     sint[++sint[0]] = pron->seg[iph];
     /* if iph is last seg of this sylb, push "]" and bump sylb index */
     if (iph == pron->sylb[ksylb].segs.l2)
       {nstrcat(sint,rmark);
        if (ksylb < nsylbs) ksylb += 1;
       }

if (db_level > 2)
 {printf("%sat bottom of loop, sint=",pdb);
  for (dbi=1; dbi <= sint[0]; dbi++) printf("%4d",sint[dbi]);
  printf("\n");
}
    }
/* add a word boundary at the very end */
  nstrcat(sint,wbound);

if (db_level > 2)
 {printf("%sat exit, sint=",pdb);
  for (dbi=1; dbi <= sint[0]; dbi++) printf("%4d",sint[dbi]);
  printf("\n");
}
  db_leave_msg(proc,1);
  return;
 } /* ftiers2() */
