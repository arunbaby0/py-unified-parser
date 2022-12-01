/* file csrates1.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif

 NUM_REL collapse_rates(NUM_REL *rate1, NUM_REL *rate2)
                        

/**************************************************************************/
/* Tries to collapse rate2 and rate1; returns the result.                 */
/* If it can't be done, returns rate.relation == 'x'.                     */
/**************************************************************************/
 {char *proc = "collapse_rates";
  NUM_REL xrate_data, *xrate = &xrate_data;
/* code */
 db_enter_msg(proc,0); /* debug only */
if (db_level > 0) printf("%s rate1: %c %d\n",pdb,rate1->relation,rate1->value);
if (db_level > 0) printf("%s rate2: %c %d\n",pdb,rate2->relation,rate2->value);
/* initialize */
  xrate->relation = 'x';
  xrate->value = 0;
 /* check for duplicates */
  if ((rate2->relation == rate1->relation) &&
      (rate2->value    == rate1->value))
    *xrate = *rate1;
  else
    {
if (db_level > 0) printf("%s not duplicates\n",pdb);
  /* check for high-end collapse */
     if ((rate1->relation == '=')&&
         (rate2->relation == '>'))
       {if (rate1->value >= rate2->value)
          {xrate->relation = '>';
           if (rate1->value > rate2->value)
                xrate->value = rate2->value;
           else xrate->value = rate2->value - 1;
       }  }
     if (rate1->relation == '>')
       {if (rate2->relation == '=')
          {if (rate2->value >= rate1->value)
             {xrate->relation = '>';
              if (rate2->value > rate1->value)
                   xrate->value = rate1->value;
              else xrate->value = rate1->value - 1;
          }  }
        if (rate2->relation == '>')
          {xrate->relation = '>';
           xrate->value = min(rate1->value,rate2->value);
          }
        if (rate2->relation == '<')
          {/* whole range must be specified: */
           if (rate1->value <= rate2->value)
             {xrate->relation = '>';
              xrate->value = MIN_RATE - 1;
       }  }  }
   /* check for low-end collapse */
     if ((rate1->relation == '=')&&
         (rate2->relation == '<'))
       {if (rate1->value <= rate2->value)
          {xrate->relation = '<';
           if (rate1->value < rate2->value)
                xrate->value = rate2->value;
           else xrate->value = rate2->value + 1;
       }  }
     if (rate1->relation == '<')
       {if (rate2->relation == '=')
          {if (rate2->value <= rate1->value)
             {xrate->relation = '<';
              if (rate2->value < rate1->value)
                   xrate->value = rate1->value;
              else xrate->value = rate1->value + 1;
          }  }
        if (rate2->relation == '<')
          {xrate->relation = '<';
           xrate->value = max(rate1->value,rate2->value);
          }
        if (rate2->relation == '>')
          {/* whole range must be specified: */
           if (rate1->value >= rate2->value)
             {xrate->relation = '>';
              xrate->value = MIN_RATE - 1;
    }  }  }  }

if (db_level > 0) printf("%s xrate: %c %d\n",pdb,xrate->relation,xrate->value);

 db_leave_msg(proc,0); /* debug only */
  return xrate_data;
 }
