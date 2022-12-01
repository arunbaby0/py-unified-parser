/* file prpron2.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


void print_pron2(struct PRON2 *pron, pcodeset *pcdp)
                                   
/*****************************************************/
/*  Uses global lmark, rmark, wbound!!               */
/*****************************************************/
 {int i,xint[MAX_SYMBS_IN_STR], err;
  char sxx[LONG_LINE], *sx = &sxx[0];
  fold_tiers2(xint,pron,lmark,rmark,wbound);
  decode2(sx,LONG_LINE,pcdp,xint,&xint[0],&err);
  fprintf(stdout," /%-32s/  %c%1d     ",
    sx,pron->rate_relation,pron->rate_value);
  for (i=1; i <= pron->lect[0]; i++)
     fprintf(stdout,"%2d",pron->lect[i]);
  fprintf(stdout,"\n");
  return;
 }
