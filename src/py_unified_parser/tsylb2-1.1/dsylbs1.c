/* file dsylb1.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif

void dump_sylbs(struct SYLB1 *sylb, int nsylbs)
                              /* one-based */
           
/**************************************************/
/* Dumps array of syllables                       */
/**************************************************/
 {int i;
  printf(" SYLLABLES:\n");
  if (nsylbs < 1) printf("(There are none.)\n");
  else
    {printf(" N  IWORD  L1  Nuc  L2  Stress\n");
     for (i=1; i <= nsylbs; i++) printf("%2d  %3d   %3d %3d %4d %4d\n",
        i,sylb[i].iword,sylb[i].segs.l1,sylb[i].nucleus,
        sylb[i].segs.l2, sylb[i].stress);
    }
  printf("\n");
 }
