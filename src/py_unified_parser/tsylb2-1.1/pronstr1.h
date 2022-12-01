/* file pronstr1.h */
/* pronunciation specification structure #1, */
/* as used, for example, in LEX_ITEM3.       */

#if !defined(PRON_SPEC_STRUCT)
#define PRON_SPEC_STRUCT

 struct PRON_SPEC
   {char *cats;
    char *tags;
    char *phon;
    int *iphon;
    char *status;
   };

#endif
