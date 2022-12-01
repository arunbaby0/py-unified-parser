/* file dwords1.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


void dump_words(struct WORD1 *word, int nwords)
                              /* one-based */
           
/**************************************************/
/* Dumps array of words                           */
/**************************************************/
 {int i;
  printf(" WORDS: (as composed of segments)\n");
  if (nwords < 1) printf("(There are none.)\n");
  else
    {printf(" N  L1  L2  Stress\n");
     for (i=1; i <= nwords; i++) printf("%2d %3d %3d %4d\n",
        i,word[i].segs.l1,word[i].segs.l2,word[i].stress);
    }
  printf("\n");
 }
