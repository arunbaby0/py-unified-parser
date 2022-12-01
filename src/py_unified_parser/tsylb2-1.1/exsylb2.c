/* file exsylb2.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


void expand_sylb2(struct PRON2 *pron, int i, int *nprons, int rate, pcodeset *pcdp, int *perr)
                                                          
               
/*****************************************************************/
/* Expands PRON2 pron[i], adding to pron[] list, applying        */
/* variable rules of syllabification only, assuming that the     */
/* basic syllabification has already been done.                  */
/* Rate is the rate of speech, from 1 (slowest) to 5 (fastest).  */
/* Note that "rate" is a conventional misnomer for "formality".  */
/* The pcodeset *pcdp contains auxiliary info.                   */
/* On return *perr > 0 signals an error.                         */
/*****************************************************************/
 {char *proc = "expand_sylb2";
  struct PRON2 xpron;
  boolean hit;
/* coding */
  db_enter_msg(proc,0);
  *perr = 0;
  xpron = pron[i];
  xpron.rate_relation = '=';
  xpron.rate_value = rate;

if (db_level > 0)
 {printf("%sexpanding syllabifications for rate=%d\n",pdb,rate);
  printf("%sbefore variable rules, xpron is:\n",pdb);
  print_pron2(&xpron,pcdp);
 }

/* current decisions:                                              */
/*   Rule III is applicable for rates 3,4,5                        */
/*   Rule IV is inapplicable for rates 1,2,3, optional for 4 and 5 */
/*   Rule V is applicable for rate 5                               */
  switch (rate)
    {case 1: break;
     case 2: break;
     case 3:
       {hit = F;
        apply_sylb_rule_III(&xpron,&hit,pcdp);
        if (hit)
          {if (*nprons < MAX_PRONS) pron[++*nprons] = xpron;
           else fprintf(stderr,"*ERR:%s: MAX_PRONS exceeded.\n",proc);

if (db_level > 0)
 {printf("%sRule III applies to make xpron:\n",pdb);
  print_pron2(&xpron,pcdp);
 }
          }
        break;
       }
     case 4:
       {hit = F;
        apply_sylb_rule_III(&xpron,&hit,pcdp);
    /* at higher rates, rule IV is optional (?) - Kahn p. 48 */
        if (hit)
          {if (*nprons < MAX_PRONS) pron[++*nprons] = xpron;
           else fprintf(stderr,"*ERR:%s: MAX_PRONS exceeded.\n",proc);

if (db_level > 0)
 {printf("%sRule III applies to make xpron:\n",pdb);
  print_pron2(&xpron,pcdp);
 }
          }
        hit = F;
        apply_sylb_rule_IV(&xpron,&hit,pcdp);
        if (hit)
          {if (*nprons < MAX_PRONS) pron[++*nprons] = xpron;
           else fprintf(stderr,"*ERR:%s: MAX_PRONS exceeded.\n",proc);

if (db_level > 0)
 {printf("%sRule IV applies to make xpron:\n",pdb);
  print_pron2(&xpron,pcdp);
 }


          }
        break;
       }
     case 5:
       {hit = F;
        apply_sylb_rule_III(&xpron,&hit,pcdp);
    /* at higher rates, rule IV is optional (?) - Kahn p. 48 */
        if (hit)
          {if (*nprons < MAX_PRONS) pron[++*nprons] = xpron;
           else fprintf(stderr,"*ERR:%s: MAX_PRONS exceeded.\n",proc);

if (db_level > 0)
 {printf("%sRule III applies to make xpron:\n",pdb);
  print_pron2(&xpron,pcdp);
 }
          }
        hit = F;
        apply_sylb_rule_IV(&xpron,&hit,pcdp);
        if (hit)
          {if (*nprons < MAX_PRONS) pron[++*nprons] = xpron;
           else fprintf(stderr,"*ERR:%s: MAX_PRONS exceeded.\n",proc);

if (db_level > 0)
 {printf("%sRule IV applies to make xpron:\n",pdb);
  print_pron2(&xpron,pcdp);
 }

	  }
        hit = F;
        apply_sylb_rule_V(&xpron,&hit,pcdp);
        if (hit)
          {if (*nprons < MAX_PRONS) pron[++*nprons] = xpron;
           else fprintf(stderr,"*ERR:%s: MAX_PRONS exceeded.\n",proc);

if (db_level > 0)
 {printf("%sRule V applies to make xpron:\n",pdb);
  print_pron2(&xpron,pcdp);
 }

          }
        break;
       }
    }


  db_leave_msg(proc,0);
  return;
 } /* end expand_sylb2() */
