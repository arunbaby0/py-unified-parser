/* file simprns2.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


void simplify_prons2(struct PRON2 *pron, int *nprons)
                                          
/**************************************************************/
/* Collapses some prons over rate expressions.                */
/**************************************************************/
 {char *proc = "simplify_prons2";
  int i,j,offset;
  boolean del[MAX_PRONS], collapse;
  char rate_relation;
  int rate_value;
/* coding */
  db_enter_msg(proc,0);
  if (*nprons > 0)
    {for (i=1; i <= *nprons; i++) del[i] = F;
   /* find 2 prons equal except for rate */
     for (i = 1; i <= *nprons; i++)
       {/* change end-points to ranges on pron i */
        if (pron[i].rate_relation == '=')
          {if (pron[i].rate_value == MAX_RATE)
             {pron[i].rate_relation = '>';
              pron[i].rate_value -= 1;
             }
           if (pron[i].rate_value == MIN_RATE)
             {pron[i].rate_relation = '<';
              pron[i].rate_value += 1;
          }  }
        for (j = i+1; j <= *nprons; j++)
          {if (db_level > 0) printf("%schecking i=%d,j=%d\n",pdb,i,j);
           if (del[j]) continue;
           if (eq_ex_rate2(&pron[i],&pron[j]))
             {/* can the rate expressions be collapsed? */

     if (db_level > 0) printf("%sequal except for rate\n",pdb);

              collapse = F;

            /* check for duplicates */
              if ((pron[i].rate_relation == '=')&&
                  (pron[j].rate_relation == '='))
                {if (pron[i].rate_value == pron[j].rate_value)
                   {collapse = T;
                    rate_relation = '=';
                    rate_value = pron[i].rate_value;
		}  }
            /* check for high-end collapse */
              if ((pron[i].rate_relation == '=')&&
                  (pron[j].rate_relation == '>'))
                {if (pron[i].rate_value >= pron[j].rate_value)
                   {collapse = T;
                    rate_relation = '>';
                    if (pron[i].rate_value > pron[j].rate_value)
                         rate_value = pron[j].rate_value;
                    else rate_value = pron[j].rate_value - 1;
	        }  }
              if (pron[i].rate_relation == '>')
                {if (pron[j].rate_relation == '=')
                   {if (pron[j].rate_value >= pron[i].rate_value)
                      {collapse = T;
                       rate_relation = '>';
                       if (pron[j].rate_value > pron[i].rate_value)
                            rate_value = pron[i].rate_value;
                       else rate_value = pron[i].rate_value - 1;
	           }  }
                 if (pron[j].rate_relation == '<')
                   {/* whole range must be specified: */
                    if (pron[i].rate_value <= pron[j].rate_value)
                      {collapse = T;
                       rate_relation = '>';
                       rate_value = MIN_RATE - 1;
	        }  }  }
            /* check for low-end collapse */
              if ((pron[i].rate_relation == '=')&&
                  (pron[j].rate_relation == '<'))
                {if (pron[i].rate_value <= pron[j].rate_value)
                   {collapse = T;
                    rate_relation = '<';
                    if (pron[i].rate_value < pron[j].rate_value)
                         rate_value = pron[j].rate_value;
                    else rate_value = pron[j].rate_value + 1;
	        }  }
              if (pron[i].rate_relation == '<')
                {if (pron[j].rate_relation == '=')
                   {if (pron[j].rate_value <= pron[i].rate_value)
                      {collapse = T;
                       rate_relation = '<';
                       if (pron[j].rate_value < pron[i].rate_value)
                            rate_value = pron[i].rate_value;
                       else rate_value = pron[i].rate_value + 1;
	           }  }
                 if (pron[j].rate_relation == '>')
                   {/* whole range must be specified: */
                    if (pron[i].rate_value >= pron[j].rate_value)
                      {collapse = T;
                       rate_relation = '>';
                       rate_value = MIN_RATE - 1;
	        }  }  }

          /* if two collapsable prons are found ... */
              if (collapse)
                {/* change one and mark the other for deletion */

if (db_level > 0) printf("%scollapsing i and j, del[j]=T\n",pdb);

                 pron[i].rate_relation = rate_relation;
                 pron[i].rate_value = rate_value;
                 del[j] = T;
       }  }  }  }
   /* go thru and delete deletables */
     offset = 0;
     for (j = 1; j <= *nprons; j++)
       {if (del[j])
          {offset += 1;
          }
        else
          {if (offset > 0) pron[j-offset] = pron[j];
          }
       }
     *nprons -= offset;
    }
  db_leave_msg(proc,0);
  return;
 }
