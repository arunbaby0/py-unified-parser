/* file include/plex/fcndcls.h                           */
/* export version - stripped of all functions not relevant to syllabification */
/* local function declarations                           */
/* last modified 10/31/94, converted to ANSI style       */

#ifndef LEX_FCNDCLS_HEADER
#define LEX_FCNDCLS_HEADER

extern void         add_default_stress(int *istr,pcodeset *pcdp,int i_default_stress);
extern void         apply_sylb_rule_III(struct PRON2 *pron, int *hit, pcodeset *pcdp);
extern void         apply_sylb_rule_IV(struct PRON2 *pron, int *hit, pcodeset *pcdp);
extern void         apply_sylb_rule_V(struct PRON2 *pron, int *hit, pcodeset *pcdp);
extern boolean      bad_init_cluster(WCHAR_T *aint, struct INTERVAL1 cluster, pcodeset *pcdp);
extern boolean      boundary_mark(int i, pcodeset *pcdp);
extern NUM_REL      collapse_rates(NUM_REL *rate1, NUM_REL *rate2);
extern boolean      consonantal(int i, pcodeset *pcdp);
extern void         del_chars(char *sx, char *chars);
extern void         dump_pron2(struct PRON2 *pron);
extern void         dump_sylbs(struct SYLB1 *sylb, int nsylbs);
extern void         dump_words(struct WORD1 *word, int nwords);
extern boolean      eq_ex_rate2(struct PRON2 *pron1, struct PRON2 *pron2);
extern void         expand_sylb2(struct PRON2 *pron, int i, int *nprons, int rate, pcodeset *pcdp, int *perr);
extern void         fatal_error(char *reporting_procedure, char *msg, int error_level);
extern void         fold_tiers2(WCHAR_T *sint, struct PRON2 *pron, int *lmark, int *rmark, int *wbound);
extern void         get_nstr_table(int **tab, int *n, int nmax, char *fname, pcodeset *pcode, char *comment_flag, int *perr);
extern void         make_basic_pron3(struct PRON2 *pron, int *xint, pcodeset *pcdp, int *perr);
extern boolean      no_word_boundl(WCHAR_T *bnd_int, struct INTERVAL1 cluster, int iwordbound);
extern boolean      ok_final_cluster(WCHAR_T *aint, struct INTERVAL1 cluster, pcodeset *pcdp);
extern boolean      ok_init_cluster(WCHAR_T *aint, struct INTERVAL1 cluster, pcodeset *pcdp);
extern boolean      prons_eq3(struct PRON_SPEC *pron1, struct PRON_SPEC *pron2);
extern void         print_pron2(struct PRON2 *pron, pcodeset *pcdp);
extern void         print_prons2(struct PRON2 *pron, int nprons, pcodeset *pcdp, int *lmark, int *rmark, int *wbound, int no_wbound);
extern void         simplify_prons2(struct PRON2 *pron, int *nprons);
extern boolean      suprasegmental(int i, pcodeset *pcdp);
extern boolean      stress_mark(int i, pcodeset *pcdp);
extern boolean      unstressed(struct SYLB1 *sylb, pcodeset *pcdp);

#endif
/* end file include/plex/fcndcls.h        */
