/* file sylb_glob_dataf.h */
/* special global data DECLARATIONS for syllabification rules */

/* lists of integer strings representing allowable initial */
/* consonant clusters, universally-bad initial consonant   */
/* clusters, and allowable final consonant clusters:       */

#if !defined(MAX_CC)
#define MAX_CC 500
#endif

#ifndef SYLB_GLOB_DATAF_HEADER
#define SYLB_GLOB_DATAF_HEADER

 extern int n_CC_inits, n_CC_bad_inits,n_CC_final;
 extern int *CC_init[MAX_CC], *CC_bad_init[MAX_CC], *CC_final[MAX_CC];

/* integer strings representing left & right sylb boundaries: */
 extern int lmark[2], rmark[2];
/* integer string representing word boundary: */
 extern int wbound[2];
/* integers representing primary, secondary, and zero stress: */
 extern int istr_1, istr_2, istr_0;
/* integer representing word boundary: */
 extern int iwordbound;

#endif
