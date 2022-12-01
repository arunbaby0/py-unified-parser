/* file ttp1s.c                                              */
/* function ttp1s(stx,sp,perr) for converting text to phones */
/* and its sub-functions.                                    */
/* Uses character functions defined in letfcns1.c            */
/* Marks stress on only a few vowels.                        */
/* Output phones are from standard phone set "phon1ax.pcd"   */

#if !defined(COMPILE_ENVIRONMENT)
#include "stdcenvf.h" /* std compile environment for functions */
#endif

/* local function prototypes: */
static boolean in_unpronounceable_token(char *p, char *st);
static char *char_name(char letter, char *sx);


  /*********************************************/
  /*  char *ttp1s(stx,sp,perr)                 */
  /*  Converts text to phones                  */
  /*  Input: *stx is a text string;            */
  /*  Output: *sp is a phone string;           */
  /*  Process: elementary.                     */
  /*  Returns *perr > 0 iff error.             */
  /*********************************************/
  char *ttp1s(char *stx, char *sp, int *perr)
   {char *proc = "ttp1s";
    char *p,*q;
    char st_data[MAX_REC_LENGTH], *st = &st_data[0];
    char sxx[LINE_LENGTH], *sx = &sxx[0];
/* code */
 db_enter_msg(proc,1); /* debug only */
if (db_level > 2) printf("%sinput='%s'\n",pdb,stx);
    *perr = 0;
    *sp = '\0'; /* empty output string */
/* pre-process */
    q = st;
    if (*stx != ' ') *q++ = ' ';
    for (p = stx; *p != '\0'; p++)
      {if (p > stx)
         {if (isalpha(*(p-1)) && isalpha(*(p+1)) && (*p == '+'))
            {*q++ = '\'';  /* "kiska+s" --> kiska's */
             continue;
	 }  }
       if ( (!ispunct(*p)) ||
             (*p == '\'')  ||
             (*p == '&')) *q++ = tolower(*p);
       else 
         {if (ispunct(*p)) *q++ = ' ';
      }  }
    if (*(p-1) != ' ')  *q++ = ' ';
    *q = '\0';
if (db_level > 1) printf("*DB: st=[%s]\n",st);
/* convert letter to phone */
    for (p = st; *p != '\0'; p++)
      {if (in_unpronounceable_token(p,st))
         {sp = strcat(sp,char_name(*p,sx));
          continue;
	 }
/* geminate consonants */
       if (iscons1(*p)&&(*p == *(p+1))) continue;  /* geminate cons */
/* "'" */
       if (*p == '\'') /* apostrophe */
         {if (bound(*(p+1))) continue; /* warriors' */
          if (bound(*(p-1))) continue; /* 'taters   */
          if (*(p+1) == 's')
            {if ((fric1(p-1))||((*(p-1) == 'e')&& fric1(p-2)))
               {sp=strcat(sp," '0 ax z"); p++; continue;} /* boss's, face's, rage's" */
              if (voiced(p-1))
               {sp=strcat(sp," z"); p++; continue;} /* Joe's,bag's */
              else
               {sp=strcat(sp," s"); p++; continue;} /* bat's */
            }
          if ((*(p+1) == 'l')&&(*(p+2) == 'l')&&bound(*(p+3)))
	    {sp = strcat(sp," el"); p++; p++; continue;} /* john'll, they'll */                   
          continue;
         }
/* "a" */
       if (*p == 'a')
         {if (bound(*(p+1))) {sp = strcat(sp," '0 ax");      continue;}/* final a */
          if (*(p+1) == 'i') {sp = strcat(sp," ey"); p++; continue;}
          if (*(p+1) == 'y') {sp = strcat(sp," ey"); p++; continue;}
          if (*(p+1) == 'u') {sp = strcat(sp," ao"); p++; continue;}/*haul*/
          if (*(p+1) == 'w') {sp = strcat(sp," ao"); p++; continue;}/*bawl*/
          if ((*(p+1) == 'l')&&(*(p+2) == 'l'))
            {sp = strcat(sp," ao"); /* all, ball, call, fall */
             continue;
            }
          if (strncmp(p+1,"ste ",4) == 0)  /* paste (long env?) */
            {sp = strcat(sp," ey"); continue;}
          if ((*(p+1) == 'h') && bound(*(p+2)))
            {sp = strcat(sp," '0 ax");
             p++;
             continue;
            }
          if (short_env(p)) sp = strcat(sp," ae");
          else              sp = strcat(sp," ey");
         }
/* "b" */
       if (*p == 'b') sp = strcat(sp," b");
/* "c" */
       if (*p == 'c')
         {if (*(p+1) == 'h') {sp = strcat(sp," ch"); p++; continue;}
          if (is_front_vowel(*(p+1))) sp = strcat(sp," s");
          else                        sp = strcat(sp," k");
          if (*(p+1) == 'k') {p++; continue;}
         }
/* "d" */
       if (*p == 'd') sp = strcat(sp," d");
/* "e" */
       if (*p == 'e')
         {if  (*(p+1) == 'w') {sp = strcat(sp," y uw"); p++; continue;}/*few*/
          if ((*(p+1) == 'l') && (*(p+2) == ' ')) /* final "el" */
	      {sp = strcat(sp," el"); p++; continue;} /* nickel */
          if ((*(p+1) == 'y')&&(iscons1(*(p-1)))&&(bound(*(p-2))))
            {sp = strcat(sp," ey"); p++; continue;} /* hey */
          if ((*(p+1) == 'y')&&(iscons1(*(p-1)))&&(iscons1(*(p-2)))&&(bound(*(p-3))))
            {sp = strcat(sp," ey"); p++; continue;} /* they */
          if ((*(p+1) == 'y')&&(*(p+2) == ' ')) /* final "ey" */
            {sp = strcat(sp," iy"); p++; continue;
            }
          if (bound(*(p+1))) /* final "e" */
            {if (iscons1(*(p-1)))
               {if (bound(*(p-2))) {sp = strcat(sp," '1 iy"); continue;}
                if ((iscons1(*(p-2))) &&(bound(*(p-3))) )
                    {sp=strcat(sp," '1 iy"); continue;}  /* me, the */
               } 
             if (bound(*(p-1))) {sp = strcat(sp," '1 iy"); continue;}
             continue;
            }

          if ((*(p+1) == 'd')&&(bound(*(p+2)))) /* final "ed" */
            {if ((*(p-1) == 't')||(*(p-1) == 'd'))
               {sp=strcat(sp," '0 ax d"); p++; continue;} /* batted */
             if ((*(p-1) == 'r')&&(*(p-2) == 'd'))
               {sp=strcat(sp," '0 ax d"); p++; continue;} /* hundred */
             if (voiced(p-1)) sp=strcat(sp," d");       /* bagged */
             else             sp=strcat(sp," t");       /* backed */
             p++;
             continue;
	   }
          if ((*(p+1) == 's')&&(*(p+2) == ' ')) /* final "es" */
            {if ((*(p-2) == 's')&&(*(p-1) == 't')) /* estes */
               {sp = strcat(sp," '0 ax s"); p++; continue;}
             if (fric1(p-1))
               {sp=strcat(sp," '0 ax z"); p++; continue;} /* bosses */
              if (voiced(p-1)) sp=strcat(sp," z");      /* aides */
              else             sp=strcat(sp," s");      /* crates */
              p++; continue;
            }

          if ((*(p+1) == 'r'))
            {if (*(p+2) == 'r')
               {sp = strcat(sp," eh"); /* terror */
                continue;
	       }
             if (!isvowel1(*(p+2)))
               {sp = strcat(sp," ax r"); /* herd */
                p++;
                continue;
	       }
             else
               {if (bound(*(p+3))) sp = strcat(sp," iy"); /* here */
                else               sp = strcat(sp," eh"); /* heretic */
                continue;
	    }  }
          if (*(p+1) == 'a')
            {if (*(p+2) == 'u') /* cocteau */
               {sp = strcat(sp," ow");
                p++; p++; continue;
 	       }
             if (*(p+2) == 'd') sp = strcat(sp," eh"); /* head, instead */
             else               sp = strcat(sp," iy");
             p++; continue;
            }
          if (*(p+1) == 'e') {sp = strcat(sp," iy"); p++; continue;}
          if (*(p+1) == 'i') {sp = strcat(sp," ey"); p++; continue;}
          if (short_env(p)) sp = strcat(sp," eh");
          else              sp = strcat(sp," iy");
         }
/* "f" */
       if (*p == 'f') sp = strcat(sp," f");
/* "g" */
       if (*p == 'g')
         {if (*(p+1) == 'h')
            {if (*(p-1) == ' ')
               {sp = strcat(sp," g"); p++; continue;} /* ghost */
             else
               {p++; continue;} /* might flight higher */
            }
          if ((*(p+1) == 'n')&&(!isvowel1(*(p+2)))) continue; /* align */
          if ((*(p-1) == 'n')&&(*(p+1) == ' ')) continue; /* -ing */
          if (*(p-1) == 'g') {sp=strcat(sp," g"); continue;} /* bagged */
          if (is_front_vowel(*(p+1))) sp = strcat(sp," jh");
          else                        sp = strcat(sp," g");
         }
/* "h" */
       if (*p == 'h')
         {if (!bound(*(p+1))) sp = strcat(sp," hh"); /* not "Noah" */
	 }
/* "i" */
       if (*p == 'i')
         {if ((*(p+1) == 'g')&&(*(p+2) == 'h'))  /* igh... */
            {sp = strcat(sp," ay"); continue;}
          if (*(p+1) == 'e') {sp = strcat(sp," iy"); p++; continue;}
          if ((*(p+1) == 'o')&&(*(p+2) == 'n')) /* -ion */
            {if (bound(*(p-2))) /* #Cion */
               {sp = strcat(sp," '1 ay '0 ax"); p++; continue;} /* lion */
             else
               {if (*(p-1) == 'l')
                  {sp = strcat(sp," y '0 ax"); p++; continue;}/* million */
                else
                  {sp = strcat(sp," '0 ax"); p++; continue;} /* diction */
	    }  }
          if (short_env(p)) sp = strcat(sp," ih");
          else              sp = strcat(sp," ay");
         }
/* "j" */
       if (*p == 'j') sp = strcat(sp," jh");
/* "k" */
       if (*p == 'k')
         {if ((*(p-1) == ' ')&&(*(p+1) == 'n')) continue;/* knee */
          sp = strcat(sp," k");
         }
/* "l" */
       if (*p == 'l')
         {if ( (*(p+1) == 'e') && (iscons1(*(p-1))) )
            {if  (bound(*(p+2)) || (*(p+2) == 's') || (*(p+2) == 'd'))
	       {sp = strcat(sp," '0 el"); /* rifle, rifles, rifled */
                p++; continue;
            }  }
          sp = strcat(sp," l");
 	 }
/* "m" */
       if (*p == 'm')
         {if ((*(p-1) == ' ')&&(*(p+1) == 'c')) /* mcvey,mcintosh */
            {sp = strcat(sp," m ae k"); p++;}
         else sp = strcat(sp," m");
         }
/* "n" */
       if (*p == 'n')
         {if (velar(*(p+1))) sp = strcat(sp," nx");
          else sp = strcat(sp," n");
         }
/* "o" */
       if (*p == 'o')
         {if (*(p+1) == 'a') {sp = strcat(sp," ow"); p++; continue;}
          if (*(p+1) == 'u') {sp = strcat(sp," aw"); p++; continue;}
          if (*(p+1) == 'i') {sp = strcat(sp," oy"); p++; continue;}
          if (*(p+1) == 'y') {sp = strcat(sp," oy"); p++; continue;}
          if (*(p+1) == 'o') {sp = strcat(sp," uw"); p++; continue;}
          if (*(p+1) == 'r') {sp = strcat(sp," ow");      continue;}/* for */
          if ((*(p+1) == 'w') && (bound(*(p+2)))) /* sorrow, arrow, bow */
	    {sp = strcat(sp," ow"); p++; continue;}
          if (bound(*(p+1))) {sp = strcat(sp," ow");      continue;}
          if ((*(p+1) == 's')&&(*(p+2) == ' '))
             {sp = strcat(sp," ow"); continue;} /* tomatos */
          if (short_env(p)) sp = strcat(sp," aa");
          else              sp = strcat(sp," ow");
         }
/* "p" */
       if (*p == 'p')
         {if (*(p+1) == 'h') {sp = strcat(sp," f"); p++; continue;}
          if ((*(p+1) == 'n')&&(*(p-1) == ' ')) continue;
          if ((*(p+1) == 's')&&(*(p-1) == ' ')) continue;
          sp = strcat(sp," p");
         }
/* "q" */
       if (*p == 'q')
         {sp = strcat(sp," k w"); if (*(p+1) == 'u') p++; continue;}
/* "r" */
       if (*p == 'r')
         {if (*(p-1) == 'r')
            {sp=strcat(sp," r"); continue;} /* bizarre, pierre */
          if ((iscons1(*(p-1)))&&(*(p+1) == 'e')&&bound(*(p+2)))
            {sp=strcat(sp," '0 ax r"); p++; continue;} /* acre,centre,sabre */
          sp = strcat(sp," r");
          if ((*(p-1) == ' ')&&(*(p+1) == 'h')) p++; /* Rhode */
          continue;
         }
/* "s" */
       if (*p == 's')
         {if (*(p+1) == 'h') {sp = strcat(sp," sh"); p++; continue;}
          if ((*(p+1) == 'i')&&(*(p+2) == 'o')) /* -sio */
            {if (*(p-1) == 's') sp = strcat(sp," sh");
             else               sp = strcat(sp," zh");
             continue;
            }
          if ((*(p+1) == ' ')&& voiced(p-1))  /* bags */
            {sp=strcat(sp," z"); continue;}
          if ((*(p+1) == 'c')&&(*(p+2) == 'h')) /* sch = /sh/ */
            {sp=strcat(sp," sh"); p++; p++; continue;}
          sp = strcat(sp," s");
         }
/* "t" */
       if (*p == 't')
         {if (*(p+1) == 'h') {sp = strcat(sp," th"); p++; continue;}
          if ((*(p+1) == 'i')&&(*(p+2) == 'o'))
            {sp = strcat(sp," sh"); continue;}
          if ((*(p+1) == 'c')&&(*(p+2) == 'h')) continue; /* batch */
          sp = strcat(sp," t");
         }
/* "u" */
       if (*p == 'u')
         {if (*(p+1) == 'y')
            {sp = strcat(sp," ay"); p++; continue;} /* buy, guy */
          if (short_env(p)) sp = strcat(sp," ax");
          else
            {if ((*(p-1) == 'r'))
               {sp = strcat(sp," uw"); continue;} /* rune */
    /* American rule, not British or stage English: */
             if (coronal(*(p-1)))
               {sp = strcat(sp," uw"); continue;} /* tune */
             sp = strcat(sp," y uw");
         }  }
/* "v" */
       if (*p == 'v') sp = strcat(sp," v");
/* "w" */
       if (*p == 'w')
         {if (*(p+1) == 'h') {sp = strcat(sp," wh"); p++; continue;}
          if (*(p+1) == 'r') continue; /* wrist */
          sp = strcat(sp," w");
         }
/* "x" */
       if (*p == 'x') sp = strcat(sp," k s");
/* "y" */
       if (*p == 'y')
         {if (isvowel1(*(p+1))) sp = strcat(sp," y"); /* yes */
          else
            {if (bound(*(p+1)))  /* final y */
               {if ((iscons1(*(p-1)))&&(bound(*(p-2))))
                  {sp = strcat(sp," '1 ay"); continue;} /*  my */
                if ((iscons1(*(p-1)))&&(iscons1(*(p-2)))&&(bound(*(p-3))))
                  {sp = strcat(sp," '1 ay"); continue;} /* fly */
                sp = strcat(sp," iy");               /* envy */
               }
             else                 sp = strcat(sp," ih");
         }  }
/* "z" */
       if (*p == 'z') sp = strcat(sp," z");
/*       if (*p == ' ') sp = strcat(sp," #"); */
      }
if (db_level > 2) printf("%soutput='%s'\n",pdb,sp);
 db_leave_msg(proc,1); /* debug only */
    return sp;
   }
/** end main function **/

/** local auxiliary functions **/

static boolean in_unpronounceable_token(char *p, char *st)
/* NOTE: this is only a sloppy first approximation! */
{boolean pronounceable = T, decided = F, vowel_letter = F;
 char *p1, *p2;
 char *stops = "bpdtgk";
/* unpronounceable if initial consonant cluster is verboten */
 for (p1 = p; ((p1 >= st)&&(!isspace((int)*p1))); p1 -= 1);
 p1 += 1;
 p2 = p1+1;
 if (iscons1(*p1) && iscons1(*p2))
   {if ((strchr(stops,*p1)!=NULL)&&(strchr(stops,*(p2))!=NULL))
       pronounceable = F;
    if ((*p1 == 'f')&&(*(p2) == 'b')) pronounceable = F;
    if ((*p1 == 'p')&&(*(p2) == 'j')) pronounceable = F;
    if (*p1 == 'c')
      {if ((*(p2) == 'b') ||
           (*(p2) == 'c') ||
           (*(p2) == 'd') ||
           (*(p2) == 'f') ||
           (*(p2) == 'g') ||
           (*(p2) == 'k') ||
           (*(p2) == 'm') ||
           (*(p2) == 'p') ||
           (*(p2) == 'q') ||
           (*(p2) == 't') ||
           (*(p2) == 'v') ||
           (*(p2) == 'x')   ) pronounceable = F;
      }
    if (!pronounceable) decided = T;
   }
 /* unpronounceable if one of the characters is a digit or funny character */
 for (p2 = p1; ((!decided)&&(*p2 != '\0')&&(!isspace((int)*p2))); p2++)
   {if (isdigit(*p2))  {pronounceable = F; decided = T;}
    if (*p2 == '&')    {pronounceable = F; decided = T;}
   }

 /* unpronounceable if no vowel letters    */
 for (p2 = p1; ((!decided)&&(*p2 != '\0')&&(!isspace((int)*p2))); p2++)
   {if (isvowel1(*p2)) {vowel_letter = T; decided = T;}
   }
 if (!vowel_letter) pronounceable = F;

 return (!pronounceable);
}

static char *char_name(char character, char *sx)
{switch (character)
   {case 'a': strcpy(sx," '1 ey");                     break;
    case 'b': strcpy(sx," b '1 iy");                   break;
    case 'c': strcpy(sx," s '1 iy");                   break;
    case 'd': strcpy(sx," d '1 iy");                   break;
    case 'e': strcpy(sx," '1 iy");                     break;
    case 'f': strcpy(sx," '1 eh f");                   break;
    case 'g': strcpy(sx," jh '1 iy");                  break;
    case 'h': strcpy(sx," '1 ey ch");                  break;
    case 'i': strcpy(sx," '1 ay");                     break;
    case 'j': strcpy(sx," jh '1 ey");                  break;
    case 'k': strcpy(sx," k '1 ey");                   break;
    case 'l': strcpy(sx," '1 eh l");                   break;
    case 'm': strcpy(sx," '1 eh m");                   break;
    case 'n': strcpy(sx," '1 eh n");                   break;
    case 'o': strcpy(sx," '1 ow");                     break;
    case 'p': strcpy(sx," p '1 iy");                   break;
    case 'q': strcpy(sx," k y '1 uw");                 break;
    case 'r': strcpy(sx," '1 aa r");                   break;
    case 's': strcpy(sx," '1 eh s");                   break;
    case 't': strcpy(sx," t '1 iy");                   break;
    case 'u': strcpy(sx," y '1 uw");                   break;
    case 'v': strcpy(sx," v '1 iy");                   break;
    case 'w': strcpy(sx," d '1 ax b '0 ax l y '2 uw"); break;
    case 'x': strcpy(sx," '1 eh k s");                 break;
    case 'y': strcpy(sx," w '1 ay");                   break;
    case 'z': strcpy(sx," z '1 iy");                   break;
    case '0': strcpy(sx," z '1 iy r '0 ow");   break;
    case '1': strcpy(sx," w '1 ax n");         break;
    case '2': strcpy(sx," t '1 uw");           break;
    case '3': strcpy(sx," th r '1 iy");        break;
    case '4': strcpy(sx," f '1 ow r");         break;
    case '5': strcpy(sx," f '1 ay v");         break;
    case '6': strcpy(sx," s '1 ih k s");       break;
    case '7': strcpy(sx," s '1 eh v '0 ax n"); break;
    case '8': strcpy(sx," '1 ey t");           break;
    case '9': strcpy(sx," n '1 ay n");         break;
    case '&': strcpy(sx," '0 ae n d");         break;
    default: strcpy(sx,"");
   }
  return sx;
 }
/* end file ttp1s.c */
