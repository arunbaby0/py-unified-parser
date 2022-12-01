/* file dpron2.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


void dump_pron2(struct PRON2 *pron)
 {int i;
  printf(" DUMP OF PRON:\n");
  printf(" segs:");
  for (i=1; i <= pron->seg[0]; i++) printf("%4d",pron->seg[i]);
  printf("\n");
  dump_sylbs(pron->sylb,pron->nsylbs);
  dump_words(pron->word,pron->nwords);
  printf(" rate: %c %d\n",pron->rate_relation,pron->rate_value);
  printf(" (dia)lects:");
  for (i=1; i <= pron->lect[0]; i++) printf("%3d",pron->lect[i]);
  printf("\n");
 }
