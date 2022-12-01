/* file okfcc1.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


boolean ok_final_cluster(WCHAR_T *aint, struct INTERVAL1 cluster, pcodeset *pcdp)
/************************************************************/
/* Returns T iff the cluster of segments in aint is a valid */
/* syllable-final consonant cluster.                        */
/* Uses global list of allowable final consonant clusters.  */
/************************************************************/
 {char *proc = "ok_final_cluster";
  int C1,i,j,size;
  WCHAR_T xint[MAX_SYMBS_IN_STR];
  boolean ans;
/* coding */
  db_enter_msg(proc,1);
  ans = F;
  if ((cluster.l1 > aint[0]) || (cluster.l2 > aint[0])) goto RETURN;
  size = cluster.l2 - cluster.l1 + 1;
  if (size < 1) goto RETURN;
/* all 1-segment consonants are o.k. */ 
  if (size == 1)
    {C1 = aint[cluster.l1];
     if (strstr(pcdp->pc[C1].lc_ext,"syl") == NULL) ans = T;
     goto RETURN;
    }
/* cast cluster into integer string form */
  j = 0;
  for (i=cluster.l1; i <= cluster.l2; i++) xint[++j] = aint[i];
  xint[0] = j;
/* search list */
  for (i=1; (!ans)&&(i <= n_CC_final); i++)
    {if (nstreq(xint,CC_final[i])) ans = T;
    }
 RETURN:
  db_leave_msg(proc,1);
  return ans;
 } /* ok_final_cluster() */
