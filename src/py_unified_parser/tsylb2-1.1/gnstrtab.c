/* file gnstrtab.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


 void get_nstr_table(int **tab, int *n, int nmax, char *fname,
   pcodeset *pcode, char *comment_flag, int *perr)
                                                         
                 
/*********************************************************************/
/*  Reads in a table of encoded pcode strings from the file *fname.  */
/* Allocates table space.                                            */
/*  Revised 4/28/94 by WMF to expand any environment variables that  */
/* might be in *fname.                                               */
/*********************************************************************/
 {char *proc = "get_nstr_table";
  FILE *fp;
  int nlines;
  int xint[MAX_SYMBS_IN_STR];
  int dbi;
  char dbsx[LINE_LENGTH], *dbs = &dbsx[0];
  char sxx[LONG_LINE], *sx = &sxx[0];
  char fxx[LONG_LINE], *local_fname = &fxx[0];
/* coding */
  db_enter_msg(proc,0);
if (db_level > 0) printf("%sreading strings from '%s'\n",pdb,fname);
  *n = 0;
  local_fname = strcpy(local_fname,fname);
  local_fname = expenv(local_fname,LONG_LINE);
  fp = fopen(local_fname,"r");
  if (fp == NULL)
    {fprintf(stderr,"*ERR:%s: opening file '%s'\n",proc,local_fname);
     *perr = 1;
    }
  else
    {nlines = 0;
     while (fgets(sx,LONG_LINE,fp) != NULL)
       {nlines += 1;
        sx = del_eol(sx);
if (db_level > 2) printf("%ssx='%s'\n",pdb,sx);
        sx = remove_comments(sx,comment_flag);
        if (textlen(sx) < 1) continue;
          {encode2(sx,pcode,xint,&xint[0],perr);
           if (*perr > 0)
             {fprintf(stdout,"*ERR: %s: Encode2 returns perr=%d\n",
                proc,*perr);
              fprintf(stdout," encoding '%s' (line #%d of file '%s')\n",
                sx,nlines, fname);
              *perr = 13;
              goto RETURN;
	     }

if (db_level > 2)
 {printf("%sxint=",pdb);
  for (dbi = 1; dbi <= xint[0]; dbi++) printf("%4d",xint[dbi]);
  printf(" (");
  decode2(dbs,LINE_LENGTH,pcode,xint,&xint[0],perr);
  printf("%s",dbs);
  printf(")\n");
 }

           if (*n < nmax)
             {*n += 1;
              tab[*n] = nstrdup(xint);
              if (tab[*n] == NULL)
                {fprintf(stdout,
                    "*ERR:%s: mem ovf, line #%d, file '%s'\n",
                    proc,nlines,fname);
                 *perr = 15;
                 fclose(fp);
                 goto RETURN;
    }  }  }  }  }
  fclose(fp);  
RETURN:
if (db_level > 0) printf("%sfinal n=%d\n",pdb,*n);
  db_leave_msg(proc,0);
  return;
 }
