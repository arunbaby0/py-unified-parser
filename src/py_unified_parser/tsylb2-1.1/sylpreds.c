/* file sylpreds.c */
/* A package of predicates over segments, useful for syllabification */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif

 boolean suprasegmental(int i, pcodeset *pcdp)
  {if (strstr(pcdp->pc[i].lc_ext,"nonseg") != NULL) return T;
   else return F;
  } 
 boolean stress_mark(int i, pcodeset *pcdp)
  {if (*(pcdp->pc[i].ac) == '\'') return T;
   else return F;
  }
 boolean boundary_mark(int i, pcodeset *pcdp)
  {if (strstr(pcdp->pc[i].lc_ext,"bound") != NULL) return T;
   else return F;
  }
 boolean consonantal(int i, pcodeset *pcdp)
  {if (strstr(pcdp->pc[i].lc_ext,"cons") != NULL) return T;
   else return F;
  }
 boolean syllabic(int i, pcodeset *pcdp)
  {if (strstr(pcdp->pc[i].lc_ext,"syl") != NULL) return T;
   else return F;
  }
 boolean unstressed(struct SYLB1 *sylb, pcodeset *pcdp)
  {if (streq(pcdp->pc[sylb->stress].ac,"'0")) return T;
   else return F;
  }
