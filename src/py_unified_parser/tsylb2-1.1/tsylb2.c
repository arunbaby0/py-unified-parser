/* tsylb2.c - tests syllabification code.                                     */
/*                                                                            */
/* Synopsis: tsylb2 {-n | -f} pcodeset_fname (db_level)                       */
/*   -n : use syllabic constraints appropriate for native words only.         */
/*   -f : use syllabic constraints appropriate for native words and foreign   */
/*        loans.                                                              */
/*   pcodeset_fname : file name of phonetic code set definition.              */
/*   (db_level) : optional de-bug level; > 0 to print intermediate results.   */
/*                                                                            */
/* Program reads in the phone code set definition and the contents of files   */
/* that parametrically define possible syllable initial and final consonant   */
/* clusters, then loops accepting unsyllabified phonetic transcriptions from  */
/* the keyboard and displaying the results of syllabification.                */
/*                                                                            */
/*                                                                            */
/* Exercises fcns:                                                            */
/*     make_basic_pron2(&xpron,astr,pcdp,perr);                               */
/*     expand_sylb2(pron,i,nprons,rate,pcdp,perr);                            */
/*     simplify_prons2(pron,&nprons);                                         */
/* and for pretty-printing:                                                   */
/*     fold_tiers2(xint,&xpron,lmark,rmark);                                  */
/*     print_prons2(pron,nprons,pcdp,lmark,rmark);                            */
/*                                                                            */
/* Author: W. M. Fisher/NIST                                                  */
/* Date Created: Summer 1995.                                                 */
/* Modifications:                                                             */
/*  8/96 - WMF - input buffer size increased; catch put in to warn if input   */
/*     looks like it was truncated; changed to add a default stress mark      */
/*     before each input syllabic segment that doesn't have a stress mark;    */
/*     memory arrays dynamically allocate; and a few cosmetic changes.        */
/*                                                                            */
/******************************************************************************/

#define VERSION "1.1"

/* standard compile environment header files: */
/* #include <gp/stdcenvp.h> */
/* NIST local version */ #include "stdcenvp.h" /* export version */

/* special pronlex processing header files: */
/* #include <plex/stdcenvp.h> */
/* NIST local version */ #include "plex_stdcenvp.h" /* export version */


int main(int argc, char ** argv) {
    char * proc = "TSYLB2";
    char * usage = " Usage: tsylb2 {-n | -f} <pcodeset_fname> (db_level)\n"
    " where:\n"
    "       -n means use constraints from native words only,\n"
    "       -f means use constraints from native words and foreign loans,\n"
    "       <pcodeset_fname> = name of file holding phonetic pcodeset,\n"
    "       db_level = optional level of de-bug print-outs of\n"
    "         intermediate results -- 0 for none.\n"
    " Then (repeatedly):\n"
    "   type in a phonetic string in the alphabet defined by\n"
    "     the pcodeset in <pcodeset_fname> (null to quit)\n"
    "   see syllabification produced by program.\n";
    char * fname_CC_inits = "CC_inits.txt";
    char * fname_CC_bad_inits = "CC_bad_inits.txt";
    char * fname_CC_final = "CC_final.txt";
    char rxf[LINE_LENGTH], * fname_pcodeset = & rxf[0];
    // char pax[LONG_LINE], * astr = & pax[0];
    char pax[LONG_LINE], * astr = & pax[0];

    char sxx[LONG_LINE], * sx = & sxx[0];
    char fnx[LONG_LINE], * fname = & fnx[0];
    char ddx[LINE_LENGTH], * data_dir = & ddx[0];
    int i_default_stress, rate, nprons, old_nprons, err;
    int * perr = & err;
    int dbi;
    int xint[MAX_SYMBS_IN_STR + 1];
    boolean done, no_print_wbound = T;
    /* *xpron is a single pron, pron[i] is an array of prons */
    /* (memory allocated dynamically */
    struct PRON2 * pron, * xpron;
    pcodeset pcd_data, * pcdp = & pcd_data;
    /*   code   */
    strcpy(astr,"");
    strcpy(data_dir, "");
    pdb = strcpy(pdb, "*DB: ");
    /*  fprintf(stdout,"\n Program %s version %s.\n",proc,VERSION);*/
    // /* NIST local */
    // fprintf(stdout, "\n Program %s export version %s.\n", proc, VERSION);  export 
    // fprintf(stdout, " Tests Syllabification.\n");
    // fprintf(stdout, "\n");
    if (argc < 3) {
        (void) fprintf(stderr, usage, proc);
        exit(-1);
    }
    /* for NIST_local version: */
    /*  if (streq(argv[1],"-n")) strcpy(data_dir,"$LEXDATA/native/");  */
    /*  if (streq(argv[1],"-f")) strcpy(data_dir,"$LEXDATA/nat+for/"); */
    /* for export version: */
    strcpy(data_dir, argv[5]);
    if (streq(argv[1], "-n")) strcat(data_dir, "/lexdata/native/");
    if (streq(argv[1], "-f")) strcat(data_dir, "/lexdata/nat+for/");
    // if (streq(argv[1], "-n")) strcpy(data_dir, "lexdata/native/");
    // if (streq(argv[1], "-f")) strcpy(data_dir, "lexdata/nat+for/");
    fname_pcodeset = argv[2];
    // printf("ARgc:%d %s", argc, argv[4]);
    if (argc > 3) db_level = atoi(argv[3]);
    else db_level = 0;

    strcpy(astr, argv[4]);
    // fprintf(stdout, " Input parameter values are:\n");
    // fprintf(stdout, "   native/native+foreign switch  = %s\n", argv[1]);
    // fprintf(stdout, "   pcodeset file  name = '%s'\n", fname_pcodeset);
    // fprintf(stdout, "   db_level = %d\n", db_level);
    /* allocate memory for data structures: */
    xpron = malloc_safe(sizeof(struct PRON2), proc);
    pron = malloc_safe(sizeof(struct PRON2) * MAX_PRONS, proc);
    /* get pcodeset */
    get_pcode3(pcdp, "", fname_pcodeset, perr);
    if ( * perr > 0) {
        // fprintf(stdout, " Get_pcode3 returned err code =%d\n", * perr);
    }
    if ( * perr > 10) return 0;
    // printf(" Name of pcodeset is: '%s'\n", pcdp -> name);
    /* find left and right syllable boundary marks in int string form */
    lmark[0] = 1;
    lmark[1] = pcindex2("[", pcdp);
    rmark[0] = 1;
    rmark[1] = pcindex2("]", pcdp);
    /* and word boundary mark */
    wbound[0] = 1;
    wbound[1] = pcindex2("#", pcdp);
    if (db_level > 0) printf("%slmark=%d,rmark=%d,wbound=%d\n",
        pdb, lmark[1], rmark[1], wbound[1]);

    /* get integers representing some particular suprasegmental phones */
    iwordbound = pcindex2("#", pcdp);
    i_default_stress = pcindex2("'0", pcdp);
    if (db_level > 0) printf("%siwordbound=%d\n", pdb, iwordbound);

    /* read in global list of allowable initial consonant clusters */
    fname = strcat(strcpy(fname, data_dir), fname_CC_inits);
    get_nstr_table(CC_init, & n_CC_inits, MAX_CC, fname, pcdp, ";", perr);
    if ( * perr > 0) {
        fprintf(stdout, "*ERR: read of '%s' fails, err=%d\n",
            fname_CC_inits, * perr);
        return -1;
    }

    /* read in global list of universally disallowed initial  */
    /* consonant clusters, for use in rule IV */
    fname = strcat(strcpy(fname, data_dir), fname_CC_bad_inits);
    get_nstr_table(CC_bad_init, & n_CC_bad_inits, MAX_CC, fname, pcdp, ";", perr);
    if ( * perr > 0) {
        fprintf(stdout, "*ERR: read of '%s' fails, err=%d\n",
            fname_CC_inits, * perr);
        return -1;
    }

    /* read in global list of allowable final consonant clusters */
    fname = strcat(strcpy(fname, data_dir), fname_CC_final);
    get_nstr_table(CC_final, & n_CC_final, MAX_CC, fname, pcdp, ";", perr);
    if ( * perr > 0) {
        fprintf(stdout, "*ERR: read of '%s' fails, err=%d\n",
            fname_CC_final, * perr);
        return -1;
    }

    // printf("THis is 0\n");

    /* exercise the function */
    done = F;
    while (!done) {
        // fprintf(stdout, "\n Enter ASCII arun phone string: ");
        // astr = fgets(astr, LONG_LINE, stdin);
        // printf("input: %s", argv[4]);
        
        // * (astr + strlen(astr) - 1) = '\n';
        // // astr = fgets(astr, LONG_LINE, argv[4]);
        // if ((astr == NULL) || (textlen(astr) < 1)) {
        //     fprintf(stdout, "\n Quitting now.  Bye.\n");
        //     done = T;
        //     continue;
        // }
        // if ( * (astr + strlen(astr) - 1) != '\n') {
        //     fprintf(stderr, "*WARNING:%s: line w/o newline char,", proc);
        //     fprintf(stderr, " probably truncated.\n  Line is:'%s'\n", astr);
        //     fprintf(stderr, " Increase size of array *astr and re-compile.\n");
        //     done = T;
        //     continue;
        // }

        // printf("Arun0: %s\n",astr);
        astr = del_eol(astr);
        // printf("Arun1: %s\n",astr);
        /* original phone string in external form is in *astr */

        // if (db_level > 0) printf("%s astr='%s'\n", pdb, astr);

        /* do initial encoding into int string xint[] */
        encode2(astr, pcdp, xint, & xint[0], perr);
        if ( * perr > 0) {
            // fprintf(stdout, "*ERR: %s: Encode2 returns perr=%d\n", proc, * perr);
            // fprintf(stdout, " encoding '%s'\n", sx);
            continue;
        }

        // if (db_level > 0) {
        //     printf("%safter initial encoding, xint=", pdb);
        //     for (dbi = 1; dbi <= xint[0]; dbi++) printf("%4d", xint[dbi]);
        //     printf("\n");
        // }

        /* add default stress marks to syllabics unmarked for stress */
        add_default_stress(xint, pcdp, i_default_stress);

        // if (db_level > 0) {
        //     decode2(sx, LONG_LINE, pcdp, xint, & xint[0], perr);
        //     printf("%s after add_default_stress, string='%s'\n", pdb, sx);
        // }

        /* make basic pronunciation */
        make_basic_pron3(xpron, xint, pcdp, perr);
        if ( * perr > 0) {
            printf("*ERR: make_basic_pron err #%d\n", * perr);
            continue;
        }
        /* basic pron is now in *xpron */
        /* print it out */
        fold_tiers2(xint, xpron, lmark, rmark, wbound);
        decode2(sx, LONG_LINE, pcdp, xint, & xint[0], perr);
        fprintf(stdout, "%s\n", sx);
        /* assume basic pron is o.k. for slower rates */
        // nprons = 1;
        // pron[1] = * xpron;
        // pron[1].rate_relation = '<';
        // pron[1].rate_value = 3;
        // /* expand syllabification */
        // for (rate = 5; rate > 0; rate--) {
        //     old_nprons = nprons;
        //     expand_sylb2(pron, 1, & nprons, rate, pcdp, perr);
        //     /* if variable rules haven't add a pron for this rate, use basic */
        //     if (nprons == old_nprons) {
        //         xpron -> rate_relation = '=';
        //         xpron -> rate_value = rate;
        //         if (nprons < MAX_PRONS) pron[++nprons] = * xpron;
        //         else fprintf(stderr, "*ERR:%s: MAX_PRONS exceeded.\n", proc);
        //     }
        // }
        // printf("\n");

        // if (db_level > 0) {
        //     printf("%sBEFORE SIMPLIFY_PRONS,\n", pdb);
        //     print_prons2(pron, nprons, pcdp, lmark, rmark, wbound, no_print_wbound);
        // }
        // do {
        //     old_nprons = nprons;
        //     simplify_prons2(pron, & nprons);
        // }
        // while (nprons != old_nprons);
        // print_prons2(pron, nprons, pcdp, lmark, rmark, wbound, !no_print_wbound);
        done = T;
    }
    free_pcode(pcdp);
    return 0;
} /* end main */

/********************* FUNCTIONS USED: *******************************/
/* (you may uncomment these lines to include the code directly)      */
/* COMMENT OUT INCLUDES OF FUNCTION SOURCE CODE - GET FROM LIBRARY
#include "calloc2.c"
#include "malloc2.c"
#include "frstr1.c"
#include "dbpkg1.c"
#include "strdup2.c"
#include "str_eq.c"
#include "textlen.c"
#include "del_eol.c"
#include "mlower.c"
#include "mupper.c"
#include "atobool.c"
#include "boolpr1.c"
#include "gcomflag.c"
#include "remcomm.c"
#include "valdata.c"
#include "fatalerr.c"
#include "nstrfcns.c"
#include "delchars.c"
#include "enclcs1.c"
#include "expenv.c"
#include "pltrim.c"
#include "pltrimf.c"
#include "prtrim.c"
#include "prtrim2.c"
#include "strcmpi.c"
#include "strcutr.c"
#include "wbtrim.c"
#include "ss_len.c"
#include "ss_to_s.c"
#include "sstok.c"
#include "sstok2.c"
#include "pcsort1.c"
#include "pcindex2.c"
#include "pcindex4.c"
#include "mfname1.c"
#include "grules1.c"
#include "aprules1.c"
#include "decode2.c"
#include "encode2.c"
#include "repladd2.c"
#include "dhpars1.c"
#include "pchmeth1.c"
#include "hashfcn.c"
#include "addpcd.c"
#include "mkele1.c"
#include "letfcns.c"
#include "ttp1.c"
#include "ttp1s.c"
#include "ttpj1.c"
#include "ttpspan2.c"
#include "addfwarn.c"
#include "adjcase.c"
#include "dpcode3.c"
#include "gppf2.c"
#include "gpcaux.c"
#include "gpcode3.c"
#include "frpcode.c"
#include "frules1.c"
#include "gnstrtab.c"
#include "dwords1.c"
#include "dsylbs1.c"
#include "dpron2.c"
#include "addstres.c"
#include "mpron3.c"
#include "simprns2.c"
#include "pronseq2.c"
#include "pronseq3.c"
#include "csrates1.c"
#include "badicc1.c"
#include "okicc1.c"
#include "okfcc1.c"
#include "no_wbndl.c"
#include "no_wbndr.c"
#include "sylpreds.c"
#include "sylrule3.c"
#include "sylrule4.c"
#include "sylrule5.c"
#include "exsylb2.c"
#include "prpron2.c"
#include "prprons2.c"
#include "ftiers2.c"
*/
/* END OF INCLUDES OF FUNCTION SOURCE CODE */