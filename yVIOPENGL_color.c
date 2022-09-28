/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIOPENGL.h"
#include    "yVIOPENGL_priv.h"

/*
 * metis § mc4·· § properly tune colors for opengl                                        § M25J6T §  · §
 *
 *
 */


tBASIC  g_primary [MAX_PRIMARY] = {
   /*---(none)---------------------------*/
   {  '·' , "trn" , "transparent"     , "------", -1.00, -1.00, -1.00  },
   /*---(black)--------------------------*/
   {  '-' , "blk" , "black"           , "abcdef",  0.00,  0.00,  0.00  },
   /*---(darker)-------------------------*/
   {  'o' , "brw" , "d.brown"         , "abcdef",  0.60,  0.30,  0.10  },
   {  'h' , "cho" , "d.chocolate"     , "abcdef",  0.60,  0.20,  0.20  },
   {  'i' , "cin" , "d.cinnamon"      , "abcdef",  0.60,  0.10,  0.30  },
   {  'w' , "aub" , "d.auburn"        , "abcdef",  0.60,  0.00,  0.20  },
   {  'r' , "red" , "d.red"           , "abcdef",  0.60,  0.00,  0.00  },
   {  'k' , "sca" , "d.scarlet"       , "abcdef",  0.60,  0.20,  0.20  },
   {  'n' , "org" , "d.orange"        , "abcdef",  0.60,  0.33,  0.00  },
   {  'l' , "gld" , "d.gold"          , "abcdef",  0.60,  0.45,  0.00  },
   {  'y' , "yel" , "d.yellow"        , "abcdef",  0.60,  0.60,  0.00  },
   {  's' , "spr" , "d.spring"        , "abcdef",  0.30,  0.60,  0.00  },
   {  'g' , "grn" , "d.green"         , "abcdef",  0.00,  0.60,  0.00  },
   {  'a' , "cyn" , "d.cyan"          , "abcdef",  0.00,  0.60,  0.60  },
   {  'b' , "blu" , "d.blue"          , "abcdef",  0.00,  0.00,  0.60  },
   {  'd' , "ind" , "d.indigo"        , "abcdef",  0.30,  0.00,  0.60  },
   {  'p' , "pur" , "d.purple"        , "abcdef",  0.60,  0.00,  0.60  },
   {  'm' , "mag" , "d.magenta"       , "abcdef",  0.60,  0.00,  0.40  },
   {  'c' , "cri" , "d.crimson"       , "abcdef",  0.60,  0.00,  0.20  },
   {  'u' , "egg" , "d.eggplant"      , "abcdef",  0.00,  0.00,  0.00  },
   {  'v' , "vel" , "d.velvet"        , "abcdef",  0.00,  0.00,  0.00  },
   {  't' , "ste" , "d.steel"         , "abcdef",  0.00,  0.00,  0.00  },
   {  'e' , "gry" , "d.grey"          , "abcdef",  0.00,  0.00,  0.00  },
   /*---(lighter)------------------------*/
   {  'O' , "BRW" , "l.brown"         , "abcdef",  1.00,  0.60,  0.30  },
   {  'H' , "CHO" , "l.chocolate"     , "abcdef",  1.00,  0.45,  0.20  },
   {  'I' , "CIN" , "l.cinnamon"      , "abcdef",  1.00,  0.30,  0.15  },
   {  'W' , "AUB" , "l.auburn"        , "abcdef",  1.00,  0.15,  0.10  },
   {  'R' , "RED" , "l.red"           , "abcdef",  1.00,  0.00,  0.00  },
   {  'K' , "SCA" , "l.scarlet"       , "abcdef",  1.00,  0.25,  0.00  },
   {  'N' , "ORG" , "l.orange"        , "abcdef",  1.00,  0.50,  0.00  },
   {  'L' , "GLD" , "l.gold"          , "abcdef",  1.00,  0.70,  0.00  },
   {  'Y' , "YEL" , "l.yellow"        , "abcdef",  1.00,  1.00,  0.00  },
   {  'S' , "SPR" , "l.spring"        , "abcdef",  0.75,  0.75,  0.00  },
   {  'G' , "GRN" , "l.green"         , "abcdef",  0.00,  1.00,  0.00  },
   {  'A' , "CYN" , "l.cyan"          , "abcdef",  0.00,  0.75,  0.75  },
   {  'B' , "BLU" , "l.blue"          , "abcdef",  0.25,  0.25,  1.00  },
   {  'D' , "IND" , "l.indigo"        , "abcdef",  0.75,  0.00,  0.75  },
   {  'P' , "PUR" , "l.purple"        , "abcdef",  1.00,  0.00,  1.00  },
   {  'M' , "MAG" , "l.magenta"       , "abcdef",  1.00,  0.00,  0.66  },
   {  'C' , "CRI" , "l.crimson"       , "abcdef",  1.00,  0.00,  0.33  },
   {  'U' , "EGG" , "l.eggplant"      , "abcdef",  0.00,  0.00,  0.00  },
   {  'V' , "VEL" , "l.velvet"        , "abcdef",  0.00,  0.00,  0.00  },
   {  'T' , "STE" , "l.steel"         , "abcdef",  0.00,  0.00,  0.00  },
   {  'E' , "GRY" , "l.grey"          , "abcdef",  0.00,  0.00,  0.00  },
   /*---(white)--------------------------*/
   {  '!' , "WHI" , "white"           , "abcdef",  1.00,  1.00,  1.00  },
   /*---(end of colors)------------------*/
   {  0   , "---" , "end-of-colors"   , "------", -1.00, -1.00, -1.00  },
   /*---(done)---------------------------*/
};


tCOLOR       g_colors [MAX_COLOR];
int          g_ncolor  = 0;
char         g_print       [LEN_RECD]  = "";



/*====================------------------------------------====================*/
/*===----                        finding colors                        ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH__________________o (void) {;}

char
yviopengl__by_abbr      (char a_abbr)
{
   char        rce         =  -10;
   int         i           =    0;
   DEBUG_GRAF  yLOG_senter  (__FUNCTION__);
   DEBUG_GRAF  yLOG_schar   (a_abbr);
   for (i = 0; i < MAX_PRIMARY; ++i) { 
      if (g_primary [i].abbr == 0)                break;
      if (g_primary [i].abbr != a_abbr)           continue;
      DEBUG_GRAF  yLOG_snote   ("found");
      DEBUG_GRAF  yLOG_sint    (i);
      DEBUG_GRAF  yLOG_sinfo   ("name"      , g_primary [i].terse);
      DEBUG_GRAF  yLOG_sexit   (__FUNCTION__);
      return i;
   }
   DEBUG_GRAF  yLOG_snote   ("FAIL, not found");
   DEBUG_GRAF  yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

char*
yVIOPENGL_primary       (char a_abbr)
{
   int         i           =    0;
   DEBUG_GRAF  yLOG_enter   (__FUNCTION__);
   /*> strcpy (g_print, "n/a");                                                       <*/
   i = yviopengl__by_abbr (a_abbr);
   DEBUG_GRAF  yLOG_value   ("i"         , i);
   if (i < 0)  return "n/a";
   sprintf (g_print, "%c  %-5.5s  %4.2f %4.2f %4.2f  %s", a_abbr,
         g_primary [i].terse, g_primary [i].red, g_primary [i].grn, g_primary [i].blu, g_primary [i].desc);
   DEBUG_GRAF  yLOG_exit    (__FUNCTION__);
   return g_print;
}

char
yviopengl__by_name      (char *a_terse)
{
   char        rce         =  -10;
   int         i           =    0;
   DEBUG_GRAF  yLOG_senter  (__FUNCTION__);
   DEBUG_GRAF  yLOG_spoint  (a_terse);
   --rce;  if (a_terse == NULL) {
      DEBUG_GRAF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   for (i = 0; i < g_ncolor; ++i) {
      if (g_colors [i].terse [0] != a_terse [0])       continue;
      if (strcmp (g_colors [i].terse, a_terse) != 0)   continue;
      DEBUG_GRAF  yLOG_snote   ("found");
      DEBUG_GRAF  yLOG_sint    (i);
      DEBUG_GRAF  yLOG_sexit   (__FUNCTION__);
      return i;
   }
   DEBUG_GRAF  yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

/*> char*                                                                                   <* 
 *> yviopengl__by_pair      (int a_pair)                                                    <* 
 *> {                                                                                       <* 
 *>    char        rce         =  -10;                                                      <* 
 *>    int         i           =    0;                                                      <* 
 *>    for (i = 0; i < g_ncolor; ++i) {                                                     <* 
 *>       if (g_colors [i].value != a_pair)                continue;                        <* 
 *>       sprintf (g_print, "%-8.8s f=%c b=%c  %s",                                         <* 
 *>             g_colors [i].terse, g_colors [i].fg, g_colors [i].bg, g_colors [i].desc);   <* 
 *>       return g_print;                                                                   <* 
 *>    }                                                                                    <* 
 *>    return "n/a";                                                                        <* 
 *> }                                                                                       <*/



/*====================------------------------------------====================*/
/*===----                        creating colors                       ----===*/
/*====================------------------------------------====================*/
static void      o___CREATE__________________o (void) {;}

char
yVIOPENGL_color         (char *a_terse, char *a_desc, char a_fg, char a_bg)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   int         x_fg        =    0;
   int         x_bg        =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_GRAF  yLOG_point   ("a_terse"   , a_terse);
   --rce;  if (a_terse == NULL) {
      DEBUG_GRAF  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF  yLOG_info    ("a_terse"   , a_terse);
   /*---(identify)-----------------------*/
   n = yviopengl__by_name (a_terse);
   if (n <  0) {
      n = g_ncolor;
      DEBUG_GRAF  yLOG_value   ("new"       , n);
   } else {
      DEBUG_GRAF  yLOG_value   ("existing"  , n);
   }
   DEBUG_GRAF  yLOG_info    ("terse"     , a_terse);
   /*---(retrieve primaries)-------------*/
   x_fg = yviopengl__by_abbr (a_fg);
   if (x_fg < -1)   x_fg  = yviopengl__by_abbr  ('!');
   x_bg = yviopengl__by_abbr  (a_bg);
   if (x_bg < -1)   x_bg  = yviopengl__by_abbr  ('-');
   /*---(save)---------------------------*/
   strlcpy (g_colors [n].terse, a_terse, LEN_LABEL);
   if (a_desc != NULL)  strlcpy (g_colors [n].desc, a_desc, LEN_DESC);
   g_colors [n].fg    = a_fg;
   g_colors [n].bg    = a_bg;
   DEBUG_GRAF  yLOG_value   ("fg"        , g_colors [n].fg);
   DEBUG_GRAF  yLOG_value   ("bg"        , g_colors [n].bg);
   /*---(update)-------------------------*/
   if (n == g_ncolor)  ++g_ncolor;
   DEBUG_GRAF  yLOG_value   ("g_ncolor"  , g_ncolor);
   /*---(complete)-----------------------*/
   DEBUG_GRAF  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          using colors                        ----===*/
/*====================------------------------------------====================*/
static void      o___USING___________________o (void) {;}

char
yVIOPENGL_by_name       (char *a_terse, char a_fg, char a_alpha)
{
   int         n           =    0;
   int         p           =    0;
   char        rce         =  -10;
   n = yviopengl__by_name (a_terse);
   --rce;  if (n < 0)  return rce;
   if (a_fg == 'y')    p = yviopengl__by_abbr (g_colors [n].fg);
   else                p = yviopengl__by_abbr (g_colors [n].bg);
   --rce;  if (g_primary [p].red < -0.01)  return rce;
   glColor4f (g_primary [p].red, g_primary [p].grn, g_primary [p].blu, a_alpha);
   return 0;
}

char*
yVIOPENGL_at_loc        (short x, short y)
{
   /*> long  x_loc  = mvwinch (stdscr, y, x);                                         <* 
    *> uchar x_ch   = x_loc & A_CHARTEXT;                                             <* 
    *> int   x_attr = x_loc & A_ATTRIBUTES;                                           <* 
    *> int   x_col  = x_loc & A_COLOR;                                                <* 
    *> int   x_left = x_attr - x_col;                                                 <* 
    *> char  b, B, u;                                                                 <* 
    *> char  t [LEN_HUND] = "";                                                       <* 
    *> switch (x_left) {                                                              <* 
    *> case  A_NORMAL               :  b = '-';  u = '-';  B = '-';     break;        <* 
    *> case  A_BOLD                 :  b = 'y';  u = '-';  B = '-';     break;        <* 
    *> case  A_UNDERLINE            :  b = '-';  u = 'y';  B = '-';     break;        <* 
    *> case  A_BLINK                :  b = '-';  u = '-';  B = 'y';     break;        <* 
    *> case  A_BOLD  | A_UNDERLINE  :  b = 'y';  u = 'y';  B = '-';     break;        <* 
    *> case  A_BLINK | A_UNDERLINE  :  b = '-';  u = 'y';  B = 'y';     break;        <* 
    *> case  A_BLINK | A_BOLD       :  b = 'y';  u = '-';  B = 'y';     break;        <* 
    *> }                                                                              <* 
    *> strlcpy (t, yviopengl__by_pair (x_col), LEN_HUND);                             <* 
    *> sprintf (g_print, "%3dx %3dy   %8d   %c %3d   %8d %c %c %c   %8d %s",          <* 
    *>       x, y, x_loc, chrvisible (x_ch), x_ch,                                    <* 
    *>       x_attr, b, B, u, x_col, t);                                              <*/
   return g_print;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char         /*-> tbd --------------------------------[ ------ [gc.842.031.62]*/ /*-[02.0000.014.!]-*/ /*-[--.---.---.--]-*/
yviopengl_color_init    (void)
{
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(globals)------------------------*//*-------------------------------------------------fg----bg--*/
   g_ncolor = 0;
   /*---(window parts)-------------------*/
   yVIOPENGL_color  ("w_titl"    , "window, normal title"                               , 'k' , 'O' );
   yVIOPENGL_color  ("w_vers"    , "window, version number"                             , 'k' , 'o' );
   yVIOPENGL_color  ("w_sbar"    , "window, normal status"                              , 'k' , 'o' );
   yVIOPENGL_color  ("w_cmds"    , "window, command message"                            , 'k' , 'o' );
   yVIOPENGL_color  ("w_keys"    , "window, keystoke display"                           , 'k' , 'O' );
   /*---(universes)----------------------*/
   yVIOPENGL_color  ("u_back"    , "window, universe/buffers"                           , 'K' , '-' );
   yVIOPENGL_color  ("u_curr"    , "window, universe/buffers"                           , 'A' , '-' );
   yVIOPENGL_color  ("u_used"    , "window, universe/buffers"                           , 'G' , '-' );
   yVIOPENGL_color  ("u_place"   , "window, universe/buffers"                           , 'R' , '-' );
   /*---(trouble)------------------------*/
   yVIOPENGL_color  ("!_warn"    , "trouble, warning"                                   , 'O' , 'R' );
   yVIOPENGL_color  ("!_errs"    , "trouble, error"                                     , '!' , 'r' );
   /*---(formula modes)------------------*/
   yVIOPENGL_color  ("i_maps"    , "map mode (2d review of sheet/cell collection"       , '-' , 'O' );
   yVIOPENGL_color  ("i_srcs"    , "source mode (single cell review)"                   , '-' , 'G' );
   yVIOPENGL_color  ("i_treg"    , "text register sub-mode"                             , '-' , 'A' );
   yVIOPENGL_color  ("i_inpt"    , "input sub-mode"                                     , '-' , 'B' );
   yVIOPENGL_color  ("i_repl"    , "replace sub-mode"                                   , '-' , 'M' );
   yVIOPENGL_color  ("i_wand"    , "wander sub-mode"                                    , '-' , 'R' );
   yVIOPENGL_color  ("i_sele"    , "source mode text selection"                         , '-' , '!' );
   /*---(visual)---------*/
   yVIOPENGL_color  ("v_curr"    , "current cell"                                       , '-' , 'Y' );
   yVIOPENGL_color  ("v_root"    , "root of visual selection"                           , 'Y' , '-' );
   yVIOPENGL_color  ("v_fill"    , "selected, not root/curr"                            , 'Y' , 'y' );
   /*---(marking)--------*/
   yVIOPENGL_color  ("m_hint"    , "marks for extended hinting"                         , 'A' , 'a' );
   yVIOPENGL_color  ("m_temp"    , "marks for temporary locations"                      , 'Y' , 'y' );
   yVIOPENGL_color  ("m_srch"    , "marks for search results"                           , 'R' , 'r' );
   /*---(menus)----------*/
   yVIOPENGL_color  ("m_back"    , "menu, background"                                   , '-' , 'o' );
   yVIOPENGL_color  ("m_cent"    , "menu, center webbing"                               , 'a' , '-' );
   yVIOPENGL_color  ("m_bull"    , "menu, bullet"                                       , 'A' , '-' );
   yVIOPENGL_color  ("m_menu"    , "menu, normal item"                                  , 'G' , '-' );
   yVIOPENGL_color  ("m_cant"    , "menu, item not available"                           , 'O' , 'y' );
   yVIOPENGL_color  ("m_errs"    , "menu, item in error"                                , 'R' , 'y' );
   /*---(menus)----------*/
   yVIOPENGL_color  ("m_main"    , "note, main title/subject"                           , '-' , 'R' );
   yVIOPENGL_color  ("m_warn"    , "note, displaying a warning"                         , '!' , 'R' );
   yVIOPENGL_color  ("m_curr"    , "note, current note item"                            , '-' , 'Y' );
   yVIOPENGL_color  ("m_prev"    , "note, old note item"                                , 'Y' , 'y' );
   /*---(overlays)-------*/
   yVIOPENGL_color  ("n_main"    , "note, main title/subject"                           , 'c' , 'C' );
   yVIOPENGL_color  ("n_warn"    , "note, displaying a warning"                         , 'R' , 'r' );
   yVIOPENGL_color  ("n_curr"    , "note, current note item"                            , 'y' , 'Y' );
   yVIOPENGL_color  ("n_prev"    , "note, old note item"                                , 'Y' , 'y' );
   yVIOPENGL_color  ("n_line"    , "note, connector line"                               , 'Y' , '-' );
   yVIOPENGL_color  ("n_dark"    , "note, connector line darkened"                      , 'y' , '-' );
   /*---(headers)--------*/
   yVIOPENGL_color  ("h_curr"    , "header (row/col) current"                           , 'A' , '-' );
   yVIOPENGL_color  ("h_lock"    , "header (row/col) locked in place"                   , 'K' , 'r' );
   yVIOPENGL_color  ("h_used"    , "header (row/col) with used cells"                   , 'A' , '·' );
   yVIOPENGL_color  ("h_norm"    , "header (row/col) normal"                            , 'K' , '·' );
   /*---(dependencies)---*/
   yVIOPENGL_color  ("d_reqs"    , "depends, current cell uses this value"              , 'M' , 'm' );
   yVIOPENGL_color  ("d_pros"    , "depends, provides a value to current cell"          , 'G' , 'g' );
   yVIOPENGL_color  ("d_like"    , "depends, adapts formula from current cell"          , 'B' , 'b' );
   /*---(cell types)-----*/
   yVIOPENGL_color  ("9_norm"   , "numeric, literal"                                    , 'B' , '·' );
   yVIOPENGL_color  ("9_form"   , "numeric, formula"                                    , 'G' , '·' );
   yVIOPENGL_color  ("9_dang"   , "numeric, complex/dangerous formula"                  , 'R' , '·' );
   yVIOPENGL_color  ("9_like"   , "numeric, formula adapted from elsewhere"             , '!' , '·' );
   yVIOPENGL_color  ("#_norm"   , "string, literal"                                     , 'Y' , '·' );
   yVIOPENGL_color  ("#_form"   , "string, formula"                                     , 'M' , '·' );
   yVIOPENGL_color  ("#_dang"   , "string, complex/dangerous formula"                   , 'R' , '·' );
   yVIOPENGL_color  ("#_like"   , "string, formula adapted from elsewhere"              , '!' , '·' );
   yVIOPENGL_color  ("p_rang"   , "range pointer"                                       , 'A' , '·' );
   yVIOPENGL_color  ("p_addr"   , "address pointer"                                     , 'A' , '·' );
   /*---(other)----------*/
   yVIOPENGL_color  (">_null"   , "blank cell"                                          , 'b' , '·' );
   yVIOPENGL_color  (">_unkn"   , "default for unidentified cells"                      , 'Y' , '·' );
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yviopengl_color_purge   (void)
{
   int         i           =    0;
   DEBUG_GRAF  yLOG_senter  (__FUNCTION__);
   DEBUG_GRAF  yLOG_sint    (g_ncolor);
   for (i = 0; i < MAX_COLOR; ++i) { 
      g_colors [i].terse [0] = '\0';
      g_colors [i].desc [0]  = '\0';
      g_colors [i].fg        = -1;
      g_colors [i].bg        = -1;
   }
   g_ncolor = 0;
   DEBUG_GRAF  yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gc.842.031.62]*/ /*-[02.0000.014.!]-*/ /*-[--.---.---.--]-*/
yviopengl_color_wrap    (void)
{
   return 0;
}


