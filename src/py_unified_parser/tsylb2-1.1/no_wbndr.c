/* file no_wbndr.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


boolean no_word_boundr(WCHAR_T *bnd_int, struct INTERVAL1 cluster, int iwordbound)
/*********************************************************/
/* Returns T iff there is no word boundary (iwordbound)  */
/* in the cluster of boundary marks bnd_int[] looking to */
/* the right (include just before the CC).               */
/*********************************************************/
 {int i;
  boolean found;
/* coding */
  found = F;
  for (i=cluster.l1; i <= cluster.l2; i++)
    {if (bnd_int[i] == iwordbound) found = T;
    }
  return !found;
 }
