/* file dpcode3.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

/*****************************************************************/
/*                                                               */
/*  dump_pcode3(p1)                                              */
/*  dumps a pcodeset to stdout, including lower code int codes.  */
/*                                                               */
/*****************************************************************/
void dump_pcode3(pcodeset *p1)
 {
  int i,j,*jn;  char *xac, *xlc;
  fprintf(stdout,"\n");
  fprintf(stdout," PCODESET DUMP\n\n");
  fprintf(stdout," name = '%s'\n",p1->name);
  fprintf(stdout," file_name = '%s'\n",p1->file_name);
  fprintf(stdout," directory = '%s'\n",p1->directory);
  fprintf(stdout," desc = '%s'\n",p1->desc);
  fprintf(stdout," format = '%s'\n",p1->format);
  fprintf(stdout," hashed = '%s'\n",bool_print(p1->hashed));
  if (p1->hashed) dump_hash_pars(p1->hash_pars);
  fprintf(stdout," order = '%s'\n",p1->order);
  fprintf(stdout," type_case = '%s'\n",p1->type_case);
  fprintf(stdout," comment_flag = '%s'\n",p1->comment_flag);
  fprintf(stdout," separated = '%s'\n",bool_print(p1->separated));
  fprintf(stdout," sep codes are '%s'\n",p1->sep_codes);
  fprintf(stdout," compositional = '%s'\n",bool_print(p1->compositional));
  fprintf(stdout," element_type = '%s'\n",p1->element_type);
  fprintf(stdout," lower_code_fname = '%s'\n",p1->lower_code_fname);
  if (p1->lower_code != NULL)
    fprintf(stdout," *lower_code is defined.\n");
  else
    fprintf(stdout," *lower_code is NOT defined.\n");
  fprintf(stdout," ppf_fname = '%s'\n",p1->ppf_fname);
  if (p1->ppf != NULL)
    fprintf(stdout," *ppf is defined.\n");
  else
    fprintf(stdout," *ppf is NOT defined.\n");
  fprintf(stdout," from_stn_rules_fname = '%s'\n",p1->from_stn_rules_fname);
  if (p1->from_stn_rules != NULL)
    fprintf(stdout," *from_stn_rules is defined, ->name='%s'.\n",
      p1->from_stn_rules->name);
  else
    fprintf(stdout," *from_stn_rules is NOT defined.\n");
  fprintf(stdout," to_stn_rules_fname = '%s'\n",p1->to_stn_rules_fname);
  if (p1->to_stn_rules != NULL)
    fprintf(stdout," *to_stn_rules is defined, ->name='%s'.\n",
      p1->to_stn_rules->name);
  else
    fprintf(stdout," *to_stn_rules is NOT defined.\n");
  fprintf(stdout," highest code value=%d\n",p1->highest_code_value);
  fprintf(stdout," max_ncodes = %d\n",p1->max_ncodes);
  fprintf(stdout," ncodes = %d\n",p1->ncodes);
  fprintf(stdout," pc table length = %d\n",p1->pctab_length);
  if (p1->ncodes > 0 )
    {fprintf(stdout,"\n");
     fprintf(stdout,"            code      composition\n");
     fprintf(stdout,"   i       pc[i].ac   pc[i].lc_ext (int)\n");
     for (i = 0; ((i < p1->pctab_length)&&(i <= p1->highest_code_value)); i++)
       {if (strlen(p1->pc[i].ac) > 0)
          {xac=p1->pc[i].ac;
           xlc=p1->pc[i].lc_ext;
           fprintf(stdout," %3d  %9s       %s (",i,xac,xlc);
           jn = p1->pc[i].lc_int;
           if (jn != NULL)
             {for (j = 1; j <= p1->pc[i].lc_int[0]; j++)
                {jn += 1; fprintf(stdout,"%3d",*jn);
             }  }
           fprintf(stdout,")\n");
    }  }  }
  return;
 } /* end dump_pcode3 */

