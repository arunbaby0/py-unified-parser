/* file mpron3.c */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

#if !defined(LEX_COMPILE_ENVIRONMENT)
#include "plex_stdcenvf.h" /* phonlex compile environment for functions */
#endif


void make_basic_pron3(struct PRON2 *pron, int *xint, pcodeset *pcdp, int *perr)
                                                        
/**************************************************************/
/* Makes initial pronunciation structure for phone string *xint */
/* in PRON2 *pron, using pcodeset *pcdp.                      */
/* This version takes as input an integer string instead of   */
/* a character string.                                        */
/**************************************************************/
 {char *proc = "make_basic_pron3";
  int i,j,iph,ph_code,iword,nwords,jsylb,jseg,jstr,jbnd,nseg,nsylbs;
  int cc_final_style = 2;
  int dbi;
  WCHAR_T seg_int[MAX_SEGS+1];
  WCHAR_T str_int[MAX_SEGS+1];
  WCHAR_T bnd_int[MAX_SEGS+1];
  int isylb[MAX_SEGS+1]; /* syllable no. of seg i, 0 for none */
  struct INTERVAL1 cluster;
/* coding */
  db_enter_msg(proc,0);

if (db_level > 0)
 {printf("%son entry, xint=",pdb);
  for (dbi=1; dbi <= xint[0]; dbi++) printf("%4d",xint[dbi]);
  printf("\n");
 }
if (db_level > 0) printf("%siwordbound=%d\n",pdb,iwordbound);

  *perr = 0;
  pron->rate_relation = '>';
  pron->rate_value = 0;
  pron->lect[0] = 1;
  pron->lect[1] = 0;

/* delete initial & final word boundaries, if any */
  if (xint[1] == iwordbound)
    {for (i=1; i < xint[0]; i++) xint[i] = xint[i+1];
     xint[0] -= 1;
    }
  if (xint[xint[0]] == iwordbound) xint[0] -= 1;

if (db_level > 0)
 {printf("%safter deleting init & final word boundaries, xint=",pdb);
  for (dbi=1; dbi <= xint[0]; dbi++) printf("%4d",xint[dbi]);
  printf("\n");
 }

/* split phones into segments, stresses, and boundaries */
  nseg = 0;
  jstr = 0;
  jbnd = 0;
  for (j=1; j <= xint[0]; j++)
    {jseg = xint[j];
     if (suprasegmental(jseg,pcdp))
       {if (stress_mark(jseg,pcdp))   jstr = jseg;
        if (boundary_mark(jseg,pcdp)) jbnd = jseg;
       }
     else
       {nseg += 1;
        str_int[nseg] = jstr;
        bnd_int[nseg] = jbnd;
        seg_int[nseg] = jseg;
        jstr = 0;
        jbnd = 0;
    }  }
  str_int[0] = nseg;
  bnd_int[0] = nseg;
  seg_int[0] = nseg;

if (db_level > 0)
 {printf("%sstresses & boundaries split out,\n",pdb);
  printf("%sstr_int=",pdb);
  for (dbi=1; dbi <= nseg; dbi++) printf("%4d",str_int[dbi]);
  printf("\n");
  printf("%sbnd_int=",pdb);
  for (dbi=1; dbi <= nseg; dbi++) printf("%4d",bnd_int[dbi]);
  printf("\n");
  printf("%sseg_int=",pdb);
  for (dbi=1; dbi <= nseg; dbi++) printf("%4d",seg_int[dbi]);
  printf("\n");
 }
/* assign initial syllable structure */
/* initialize with no syllables or associations */
  nsylbs = 0;
  for (iph=1; iph <= nseg; iph++) isylb[iph] = 0;
/* Rule 1: make a syllable for each syllable nucleus */
  for (iph=1; iph <= nseg; iph++)
    {ph_code = seg_int[iph];
     if (strstr(pcdp->pc[ph_code].lc_ext,"syl") != NULL)
       {if (nsylbs < MAX_SYLBS)
          {nsylbs += 1;
           pron->sylb[nsylbs].nucleus = iph;
           pron->sylb[nsylbs].stress = str_int[iph];
           pron->sylb[nsylbs].segs.l1 = 0;
           pron->sylb[nsylbs].segs.l2 = 0;
           isylb[iph] = nsylbs;
	  }
        else
          {fprintf(stderr,"*ERR:%s: syllable array overflow.\n",proc);
           fprintf(stderr," (Increase MAX_SYLBS and re-compile.)\n");
           *perr = 11; goto RETURN;
    }  }  }
/* assign initial word structure */
  nwords = 1;
  pron->word[nwords].segs.l1 = 1;
  pron->word[nwords].segs.l2 = 1;
  pron->word[nwords].stress = 0;
  for (iph=1; iph <= nseg; iph++)
    {if (bnd_int[iph] == iwordbound)
       {if (nwords < MAX_WORDS_IN_UTT)
          {nwords += 1;
           pron->word[nwords].segs.l1 = iph;
           pron->word[nwords].segs.l2 = iph;
	  }
        else
          {fprintf(stderr,"*ERR:%s: word array overflow.\n",proc);
           fprintf(stderr," (Increase MAX_WORDS_IN_UTT and re-compile.)\n");
           *perr = 12; goto RETURN;
       }  }
     else
       {pron->word[nwords].segs.l2 = iph;
    }  }

if (db_level > 0) printf("%safter rule 1, nsylbs=%d\n",pdb,nsylbs);
if (db_level > 0) printf("%snwords=%d\n",pdb,nwords);

/* rule 2: (slow speech) */
/* 2a */
/* for each syllabic nucleus, associate maximal initial cluster */
  for (jsylb=1; jsylb <= nsylbs; jsylb++)
    {cluster.l2 = pron->sylb[jsylb].nucleus - 1;
     cluster.l1 = cluster.l2;
/* NOTE: we must still use word boundary marks instead of which */
/* syllables are in which words because sylb segs haven't been set */
     while (no_word_boundl(bnd_int,cluster,iwordbound) &&
            ok_init_cluster(seg_int,cluster,pcdp)) cluster.l1 -= 1;
     cluster.l1 += 1;
     if (cluster.l1 <= cluster.l2) /* good cluster */
       {pron->sylb[jsylb].segs.l1 = cluster.l1;
        for (iph=cluster.l1; iph <= cluster.l2; iph++)
          isylb[iph] = jsylb;
       }
     else
       {pron->sylb[jsylb].segs.l1 = pron->sylb[jsylb].nucleus;
    }  }

if (db_level > 0) printf("%safter rule 2a, nsylbs=%d\n",pdb,nsylbs);
if (db_level > 0) dump_pron2(pron);

/* 2b */
/* for each syllabic nucleus, associate maximal final non-associated cluster */
  for (jsylb=1; jsylb <= nsylbs; jsylb++)
    {cluster.l1 = pron->sylb[jsylb].nucleus + 1;
   /* NB: must work backward from longest to shortest because of */
   /*    [Vdst#, "amidst"] but *[Vds#]                           */
 
     cluster.l2 = cluster.l1;     /* find cluster */
     while (no_word_boundr(bnd_int,cluster,iwordbound)&&
            (isylb[cluster.l2] == 0 )) cluster.l2 += 1;
     cluster.l2 -= 1;
  /* style # 1 - stop here */
  /* style # 2 - back off to o.k. final cluster */
     if (cc_final_style == 2)
       {while ((cluster.l2 >= cluster.l1)&&
               (!ok_final_cluster(seg_int,cluster,pcdp)))
          cluster.l2 -= 1;
       }
     if (cluster.l1 <= cluster.l2) /* good cluster */
       {pron->sylb[jsylb].segs.l2 = cluster.l2;
        for (iph=cluster.l1; iph <= cluster.l2; iph++)
          isylb[iph] = jsylb;
       }
     else
       {pron->sylb[jsylb].segs.l2 = pron->sylb[jsylb].nucleus;
    }  }

if (db_level > 0) printf("%safter rule 2b, nsylbs=%d\n",pdb,nsylbs);

/* mark syllables as to what word they (initially) belong to */
  for (iword=1; iword <= nwords; iword++)
    {for (jsylb = 1; jsylb <= nsylbs; jsylb += 1)
       {if ((pron->sylb[jsylb].segs.l1 >= pron->word[iword].segs.l1)&&
            (pron->sylb[jsylb].segs.l2 <= pron->word[iword].segs.l2) )
          pron->sylb[jsylb].iword = iword;
    }  }

 RETURN:
  pron->nsylbs = nsylbs;
  pron->nwords = nwords;
  nstrcpy(pron->seg,seg_int);

if (db_level > 0) dump_pron2(pron);

  db_leave_msg(proc,0);
  return;
 } /* end make_basic_pron3() */
