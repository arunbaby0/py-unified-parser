/* file badicc1.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif

boolean bad_init_cluster(WCHAR_T *aint, struct INTERVAL1 cluster, pcodeset *pcdp)
/******************************************************************/
/* Returns T iff the cluster of segments in aint is a universally */
/* bad syllable-initial consonant cluster, based on the contents  */
/* of global list CC_init_bad[]                                   */
/******************************************************************/
 {char *proc = "bad_init_cluster";
  int i,j,size;
  WCHAR_T xint[MAX_SYMBS_IN_STR];
  boolean ans;
/* coding */
  db_enter_msg(proc,1);
  ans = F;
/* invalid cluster specs yield "bad" */
  size = cluster.l2 - cluster.l1 + 1;
  if ((cluster.l1 < 1) || (cluster.l2 < 1) || (size < 0))
    {ans = T;
     goto RETURN;
   }
/* null cluster yields "not bad" */
  if (size < 1) goto RETURN;
/* all 1-segment consonants are o.k. */ 
  if (size == 1) goto RETURN;
/* otherwise cast cluster into integer string form */
  j = 0;
  for (i=cluster.l1; i <= cluster.l2; i++) xint[++j] = aint[i];
  xint[0] = j;
/* and search list */
  for (i=1; (!ans)&&(i <= n_CC_bad_inits); i++)
    {if (nstreq(xint,CC_bad_init[i])) ans = T;
    }
 RETURN:
  db_leave_msg(proc,1);
  return ans;
 }
