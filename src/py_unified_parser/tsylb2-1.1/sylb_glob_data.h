/* file sylb_glob_data.h */
/* special global data for syllabification rules */

/* lists of integer strings representing allowable initial */
/* consonant clusters, universally-bad initial consonant   */
/* clusters, and allowable final consonant clusters:       */

#if !defined(MAX_CC)
#define MAX_CC 500
#endif

#ifndef SYLB_GLOB_DATA_HEADER
#define SYLB_GLOB_DATA_HEADER

 int n_CC_inits, n_CC_bad_inits,n_CC_final;
 int *CC_init[MAX_CC], *CC_bad_init[MAX_CC], *CC_final[MAX_CC];

/* integer strings representing left & right sylb boundaries: */
  int lmark[2], rmark[2];
/* integer string representing word boundary: */
  int wbound[2];
/* integer representing word boundary: */
  int iwordbound;

#endif
