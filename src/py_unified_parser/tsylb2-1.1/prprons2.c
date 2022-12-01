/* file prprons2.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


void print_prons2(struct PRON2 *pron, int nprons, pcodeset *pcdp,
 int *lmark, int *rmark, int *wbound, int no_wbound)
 {int i, j, err;
  int xint[MAX_SYMBS_IN_STR];
  char sxx[LONG_LINE], *sx = &sxx[0];
  char wxx[LONG_LINE], *wbound_chars = &wxx[0];
  strcpy(wbound_chars,pcdp->pc[wbound[1]].ac);
  printf("\n");
  printf(" No. of prons = %d\n",nprons);
  if (nprons > 0)
    {printf(" They are:");
     if (no_wbound) printf(" (erasing word boundaries)");
     printf("\n");
     printf(" #  Pronunciation ................         Rate  Lects\n");
     for (i=1; i <= nprons; i++)
       {fold_tiers2(xint,&pron[i],lmark,rmark,wbound);
        decode2(sx,LONG_LINE,pcdp,xint,&xint[0],&err);
        if (no_wbound) del_chars(sx,wbound_chars);
/* deletes all occurrances of characters in *char from *sx. */
        fprintf(stdout,"%2d /%-36s/  %c%1d     ",
           i,sx,pron[i].rate_relation,pron[i].rate_value);
        for (j=1; j <= pron[i].lect[0]; j++)
           fprintf(stdout,"%2d",pron[i].lect[j]);
        fprintf(stdout,"\n");
    }  }
  return;
 }
