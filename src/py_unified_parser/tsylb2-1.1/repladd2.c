/* file repladd2.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

  /*************************************************************************/
  /*  void report_lex_add2(i,pc1,perr)                                     */
  /*  Reports the addition of lexeme i to pcodeset *pc1 (into a file).     */
  /*  On exit, *perr == 0 means a.o.k.                                     */
  /*                    11 means ADD file couldn't be opened.              */
  /* Changed on 7/16/96 by WMF to set very lax permissions on file when    */
  /* it is created.                                                        */
  /*************************************************************************/
  void report_lex_add2(int i, pcodeset *pc1, int *perr)
   {char *proc = "report_lex_add2";
    static FILE *fp = NULL;
    static char fnx[LONG_LINE], *fname = &fnx[0];
    struct stat stbuf;
    boolean file_wasnt_there;
    mode_t permissions;
    int err_ret;
    time_t t_sec;
/* code */
 db_enter_msg(proc,1);
    *perr = 0;
    if (fp == NULL) /* if file not open, try to open it */
      {fname = make_full_fname(fname,pc1->directory,pc1->file_name);
       fname = strcat(fname,".ADD");
       fname = expenv(fname,LONG_LINE);
    /* if file does not already exist, create it with general r/w permissions */       
       if (stat(fname,&stbuf)  == -1) file_wasnt_there = T;
       else                           file_wasnt_there = F;
       fp = fopen(fname,"a");
       if (fp == NULL) /* open fails, crap out */
         {fprintf(stderr,"*ERR:'%s' cannot open file '%s'\n",proc,fname);
          *perr = 11;
	 }
       else            /* open succeeds, add time stamp */
         {if (file_wasnt_there)
            {err_ret = chmod(fname,permissions=0666);
             if (err_ret == -1)
               {fprintf(stderr,"*ERR:'%s' cannot set permissions on file '%s'\n",
                 proc,fname);
                *perr = 3;
	       }
if (db_level > 2) printf("%s permissions on file '%s' set to %o\n",pdb,fname,permissions);
	    }
          t_sec = time(&t_sec);
          fprintf(fp,"%s items added  %s:\n",
            pc1->comment_flag,del_eol(ctime(&t_sec)));
      }  }
   /* add item only to an open file */
    if (fp != NULL) fprintf(fp,"%s  %s\n",pc1->pc[i].ac,pc1->pc[i].lc_ext);
db_leave_msg(proc,1);
   return;
  }
/* end include repladd2.c */
