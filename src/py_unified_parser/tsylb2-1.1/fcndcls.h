/* file fcndcls.h              */
/* local function declarations */
/* export version - stripped of all functions not relevant to syllabification */

#ifndef FCNDCLS_HEADER
#define FCNDCLS_HEADER

extern int            add_pcode_element(pcodeset *p1, pcode_element *px, int *perr);
extern char          *adjust_type_case(char *s, pcodeset *pcode);
extern char          *apply_rules1(char *pb, char *pa, RULESET1 *rset, int *perr);
extern boolean        atobool(char *s);
extern char          *bool_print(boolean x);
boolean               bound(char c);
extern void          *calloc_safe(size_t nobj, size_t size, char *calling_proc);
extern boolean        coronal(char c);
extern void           db_enter_msg(char *proc, int level);
extern void           db_leave_msg(char *proc, int level);
extern void           decode2(char *psex, int lpsex, pcodeset *pc1, int *psinin, int *plinin, int *perr);
extern char          *del_eol(char *ps);
extern void           dump_hash_pars(HASH_PARAMETERS *hpars);
extern void           dump_pcode3(pcodeset *p1);
extern void           encode_lcs(pcodeset *p1, int *perr);
extern void           encode2(char *psex_in, pcodeset *pcstr, int *psinin, int *plinin, int *perr);
extern char          *expenv(char *s, int slength);
extern void           fatal_error(char *reporting_procedure, char *msg, int error_level);
extern void           free_pcode(pcodeset *p);
extern void           free_rules1(RULESET1 *rset);
extern void           free_str(char *s);
boolean               fric1(char *p);
extern void           get_comment_flag(char *s, char *comment_flag);
extern void           get_pcode3(pcodeset *p1, char *path, char *fname, int *perr);
extern void           get_pcode_element(char *pline, int compositional, pcode_element *px, int *perr);
extern void           get_ppfcn2(ppfcn *ppf, char *fname, pcodeset *pcode, int *perr);
extern void           get_rules1(RULESET1 *rset, char *path, char *fname, int *perr);
extern int            hash(char *key, HASH_PARAMETERS *hpars, int table_length);
extern void           hash_init(HASH_PARAMETERS *hpars);
extern void           init_pc_table(pcodeset *p1);
extern boolean        isvowel1(char c);
extern boolean        isvowel2(char c);
extern boolean        iscons1(char c);
extern boolean        iscons2(char c);
extern boolean        is_front_vowel(char c);
extern pcode_element *make_element(pcode_element *px, char *symb, pcodeset *pc1);
extern char          *make_full_fname(char *sx, char *path, char *fname);
extern char          *make_lower(char *s);
extern char          *make_upper(char *s);
extern void           make_pc_table(pcodeset *p1);
extern void          *malloc_safe(size_t size, char *calling_proc);
extern int           *nstrcpy(int *pn_to, int *pn_from);
extern int           *nstrcpyn(int *pn_to, int *pn_from, int nmax);
extern int           *nstrcat(int *pn_to, int *pn_from);
extern int           *nstrdup(int *pn);
extern int           *nstrdup_safe(int *pn, char *calling_proc);
extern boolean        nstreq(int *pn1, int *pn2);
extern int            nstrcmp(int *pn1, int *pn2);
extern int            pc_htab_store(pcodeset *pc1, pcode_element *element, int *duplicate_key, int *table_full);
extern int            pcindex_htab_lookup(char *symb, pcodeset *pc1, int *found);
extern int            pcodeset_misorders(pcodeset *pc1);
extern PCIND_T        pcindex2(char *phone, pcodeset *pc1);
extern PCIND_T        pcindex_bsearch(char *astr, pcodeset *pc1);
extern void           pcsort1(pcodeset *p1);
extern char          *pltrim(char *s);
extern char          *pltrimf(char *s);
extern char          *prtrim(char *s);
extern char          *prtrim2(char *s);
extern void           process_pcode_aux_line(pcodeset *p1, char *pline, int *perr);
extern void           process_pcode_data_line(pcodeset *p1, char *pline, int *perr);
extern void           process_ppf_aux_line(ppfcn *ppf, char *pline, int *plno, int *perr);
extern void           process_ppf_data_line(ppfcn *ppf, char *pline, int *plno, int *perr);
extern char          *remove_comments(char *s, char *comment_flag);
extern void           report_lex_add2(int i, pcodeset *pc1, int *perr);
boolean               short_env(char *p);
extern void           sort_pcodeset_a(pcodeset *p1);
extern SUBSTRING      sstok(SUBSTRING *ssx, char *delimiters);
extern SUBSTRING      sstok2(char *sx, char *delimiters);
extern char          *strdup_safe(char *ps, char *calling_proc);
extern int            substr_length(SUBSTRING *substr);
extern char          *substr_to_str(SUBSTRING *substr, char *str, int lmax);
extern boolean        string_equal(char *cs, char *ct, int ignore_case);
extern int            strcmpi(char *ps1, char *ps2);  /* BCD 4.2; not TURBO C */
extern char          *strcutr(char *ps, int n);
extern int            textlen(char *s);
extern char          *ttp1(char *stx, char *sp, int *perr);
extern char          *ttp1s(char *stx, char *sp, int *perr);
extern char          *ttpj1(char *stx, char *sp, int *perr);
extern char          *ttpspan2(char *stx, char *sp, char *path, int *perr);
extern boolean        valid_data_line(char *s, char *comment_flag);
boolean               velar(char c);
boolean               voiced(char *p);
extern void           warn_if_add_file(char *fname, char *time);
extern char          *wbtrim(char *s);

#endif
/* end file fcndcls.h        */
