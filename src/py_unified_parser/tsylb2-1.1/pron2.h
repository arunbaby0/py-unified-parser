/* file pron2.h */

#include "lexpars.h"

#if !defined(PRON2_HEADER)
#define PRON2_HEADER

  struct WORD1
    {struct INTERVAL1 segs; /* first and last segments */
     int stress;
    }; /* Note words are composed of segs, not sylbs. */
  struct SYLB1
    {int nucleus;
     struct INTERVAL1 segs; /* first and last segments */
     int iword; /* index of word that it belongs to originally */
     int stress;
    };

  struct PRON2
    {WCHAR_T seg[MAX_SEGS+1]; /* codes for segments */
     struct WORD1 word[MAX_WORDS_IN_UTT+1]; /* one-based */
     struct SYLB1 sylb[MAX_SYLBS+1]; /* one-based */
     int nwords,nsylbs;
     char rate_relation; /* <, =, > */
     int rate_value; /* 1 = slowest, 5 = fastest */
     int lect[MAX_LECTS+1]; /* int str of (dia)lects, 0=all */
    };

#endif
