/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIOPENGL.h"
#include    "yVIOPENGL_priv.h"



tMY         myVIOPENGL;



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        yVIOPENGL_ver [200] = "";

char*
yVIOPENGL_version       (void)
{
   char        t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yVIOPENGL_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yVIOPENGL_ver;
}

char
yVIOPENGL__wave_one     (char *a_title, char *a_version, char a_mode)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*----(first)-------------------------*/
   rc = yMODE_init           (a_mode);
   DEBUG_GRAF   yLOG_value   ("yMODE"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(TEMP)---------------------------*/
   rc = yFILE_init           ();
   DEBUG_GRAF   yLOG_value   ("yFILE"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yCMD_init            ();
   DEBUG_GRAF   yLOG_value   ("yCMD"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(early)-----------------------*/
   rc = yVIEW_init (YVIEW_OPENGL, a_title, a_version, yviopengl_cleanse, yviopengl_prep, yviopengl_cursor, yviopengl_refresh);
   DEBUG_GRAF   yLOG_value   ("yVIEW"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*----(update sizes)------------------*/
   yVIEW_resize (myVIOPENGL.wide, myVIOPENGL.tall, 0);
   /*----(later)-------------------------*/
   rc = yKEYS_init           ();
   DEBUG_GRAF   yLOG_value   ("yKEYS"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yMAP_init            ();
   DEBUG_GRAF   yLOG_value   ("yMAP"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = ySRC_init            ();
   DEBUG_GRAF   yLOG_value   ("ySRC"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yMACRO_init          ();
   DEBUG_GRAF   yLOG_value   ("yMACRO"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yMARK_init           ();
   DEBUG_GRAF   yLOG_value   ("yMARK"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIOPENGL__wave_two     (void)
{  /*---(note)---------------------------*/
   /*
    * this wave handles the inter-library calls after all are initialized
    * and yVIHUB is fully configured.
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*----(first)-------------------------*/
   rc = yMODE_init_after     ();
   DEBUG_GRAF   yLOG_value   ("yMODE"   , rc);
   rc = yFILE_init_after     ();
   DEBUG_GRAF   yLOG_value   ("yFILE"   , rc);
   rc = yCMD_init_after      ();
   DEBUG_GRAF   yLOG_value   ("yCMD"    , rc);
   rc = yVIEW_init_after     ();
   DEBUG_GRAF   yLOG_value   ("yVIEW"   , rc);
   rc = yKEYS_init_after     ();
   DEBUG_GRAF   yLOG_value   ("yKEYS"   , rc);
   rc = yMAP_init_after      ();
   DEBUG_GRAF   yLOG_value   ("yMAP"    , rc);
   rc = ySRC_init_after      ();
   DEBUG_GRAF   yLOG_value   ("ySRC"    , rc);
   rc = yMACRO_init_after    ();
   DEBUG_GRAF   yLOG_value   ("yMACRO"  , rc);
   rc = yMARK_init_after     ();
   DEBUG_GRAF   yLOG_value   ("yMARK"   , rc);
   /*---(complete)-----------------------*/
   rc = yCMD_add (YVIHUB_M_FORMAT, "winreset"    , ""    , ""      , yX11_reset                 , "change the width of columns"               );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winreset"    , ""    , ""      , yX11_reset                 , "move between window manager desktops"      );
   rc = yCMD_add (YVIHUB_M_FORMAT, "desktop"     , ""    , "c"     , yX11_desk_goto             , "move between window manager desktops"      );
   rc = yCMD_add (YVIHUB_M_FORMAT, "term"        , ""    , "a"     , yX11_yvikeys_term          , "create a terminal session"                 );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winname"     , ""    , "a"     , yX11_yvikeys_name          , "name an existing window"                   );
   rc = yCMD_add (YVIHUB_M_FORMAT, "sendkeys"    , ""    , "a"     , yX11_yvikeys_sendkeys      , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "blitzkeys"   , ""    , "a"     , yX11_yvikeys_blitzkeys     , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winexact"    , ""    , "cciiii", yX11_yvikeys_winexact      , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winplace"    , ""    , "a"     , yX11_yvikeys_winplace      , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winbring"    , ""    , "c"     , yX11_yvikeys_winbring      , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "wingoto"     , ""    , "c"     , yX11_yvikeys_wingoto       , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "winsend"     , ""    , "cc"    , yX11_yvikeys_winsend       , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "wintake"     , ""    , "cc"    , yX11_yvikeys_wintake       , "sendkeys to a specific window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "mydesk"      , ""    , "c"     , yX11_yvikeys_mydesk        , "change position of current window"         );
   rc = yCMD_add (YVIHUB_M_FORMAT, "myhome"      , ""    , "ii"    , yX11_yvikeys_myhome        , "change position of current window"         );
   rc = yCMD_add (YVIHUB_M_FORMAT, "mysize"      , ""    , "ii"    , yX11_yvikeys_mysize        , "change size of current window"             );
   rc = yCMD_add (YVIHUB_M_FORMAT, "mysizer"     , ""    , "iiii"  , yX11_yvikeys_mysizer       , "reset all desktops, windows, and shortcuts");
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIOPENGL_init          (char *a_title, char *a_version, char a_mode, short a_wide, short a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_GRAF   yLOG_point   ("a_title"   , a_title);
   --rce;  if (a_title == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_info    ("a_title"   , a_title);
   DEBUG_GRAF   yLOG_point   ("a_version" , a_version);
   --rce;  if (a_title == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_info    ("a_version" , a_version);
   /*---(save keys)----------------------*/
   myVIOPENGL.wide = a_wide;
   myVIOPENGL.tall = a_tall;
   strlcpy (myVIOPENGL.title, a_title, LEN_HUND);
   /*----(update sizes)------------------*/
   /*> yVIEW_debug_list ();                                                           <*/
   /*---(color options)------------------*/
   rc = yCOLOR_init     ();
   yCMD_add (YVIHUB_M_VIEW   , "palette"     , ""    , "isss" , yCOLOR_palette             , "" );
   yCMD_add (YVIHUB_M_VIEW   , "wheel"       , ""    , "s"    , yCOLOR_wheel               , "" );
   yCMD_add (YVIHUB_M_VIEW   , "degree"      , "deg" , "i"    , yCOLOR_deg                 , "" );
   yCMD_add (YVIHUB_M_VIEW   , "harmony"     , "har" , "s"    , yCOLOR_harm                , "" );
   yCMD_add (YVIHUB_M_VIEW   , "value"       , "val" , "s"    , yCOLOR_val                 , "" );
   yCMD_add (YVIHUB_M_VIEW   , "saturation"  , "sat" , "s"    , yCOLOR_sat                 , "" );
   yCOLOR_diff_scheme (YCOLOR_WHITE);
   yviopengl_color_init ();
   /*---(library inits)------------------*/
   rc = yVIOPENGL__wave_one (a_title, a_version, a_mode);
   DEBUG_GRAF   yLOG_value   ("wave one", rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(library inits)------------------*/
   rc = yVIOPENGL__wave_two ();
   DEBUG_GRAF   yLOG_value   ("wave two", rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yMODE_results ();
   /*---(library inits)------------------*/
   /*> rc = yVIHUB_init (YVIEW_OPENGL, a_title, a_version, a_mode, yviopengl_cleanse, yviopengl_prep, yviopengl_cursor, yviopengl_refresh);   <* 
    *> DEBUG_GRAF   yLOG_value   ("library"   , rc);                                                                                          <* 
    *> --rce;  if (rc < 0) {                                                                                                                  <* 
    *>    DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);                                                                                      <* 
    *>    return rce;                                                                                                                         <* 
    *> }                                                                                                                                      <*/
   /*---(opengl drawing)-----------------*/
   yVIEW_simple (YVIEW_TITLE  , -1, 0, yviopengl_title);
   yVIEW_simple (YVIEW_VERSION, -1, 0, yviopengl_version);
   yVIEW_simple (YVIEW_MODES  , -1, 0, yviopengl_modes);
   yVIEW_simple (YVIEW_STATUS , -1, 0, yviopengl_status);
   yVIEW_simple (YVIEW_COMMAND, -1, 0, yviopengl_command);
   yVIEW_simple (YVIEW_FORMULA, -1, 0, yviopengl_formula);
   yVIEW_simple (YVIEW_FLOAT  , -1, 0, yviopengl_float);
   yVIEW_simple (YVIEW_KEYS   , -1, 0, yviopengl_keys);
   yVIEW_simple (YVIEW_BUFFER , -1, 0, yviopengl_univs);
   yVIEW_simple (YVIEW_NOTES  , -1, 0, yviopengl_notes);
   yVIEW_menus  (yviopengl_menus);
   myVIOPENGL.p_formula = 's';
   yVIEW_switch_add (YVIEW_FORMULA, "min"  , "", yviopengl_formula_min  , "minimal formula display");
   yVIEW_switch_add (YVIEW_FORMULA, "small", "", yviopengl_formula_small, "formula display with length");
   yVIEW_switch_add (YVIEW_FORMULA, "label", "", yviopengl_formula_label, "formula display with label and length");
   yVIEW_switch_add (YVIEW_FORMULA, "max"  , "", yviopengl_formula_max  , "detailed formula display");
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIOPENGL_dawn                 (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(start window)-------------------*/
   rc = yX11_start (myVIOPENGL.title, myVIOPENGL.wide, myVIOPENGL.tall, YX_FOCUSABLE, YX_FIXED, '-');
   DEBUG_GRAF   yLOG_value   ("yX11"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(color)--------------------------*/
   DEBUG_GRAF   yLOG_note    ("clearing");
   yVIEW_color_clear (YVIEW_MAIN);
   /*---(textures)-----------------------*/
   DEBUG_GRAF   yLOG_note    ("textures");
   glEnable        (GL_TEXTURE_2D);    /* NEW */
   /*---(blending)-----------------------*/
   DEBUG_GRAF   yLOG_note    ("blending");
   glShadeModel    (GL_SMOOTH);
   glEnable        (GL_DEPTH_TEST);
   glEnable        (GL_ALPHA_TEST);
   glAlphaFunc     (GL_GEQUAL, 0.0125);
   glEnable        (GL_BLEND);
   glBlendFunc     (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glDepthFunc     (GL_LEQUAL);
   /*---(anti-aliasing)------------------*/
   DEBUG_GRAF   yLOG_note    ("anti-aliasing");
   glHint          (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   /*---(special polygon antialiasing)----------*/
   DEBUG_GRAF   yLOG_note    ("polygon");
   glEnable        (GL_POLYGON_SMOOTH);
   glPolygonMode   (GL_FRONT_AND_BACK, GL_FILL);
   glHint          (GL_POLYGON_SMOOTH_HINT, GL_NICEST);
   /*---(simple defaulting)--------------*/
   DEBUG_GRAF   yLOG_note    ("sizes");
   glLineWidth     (0.50f);
   /*---(process immediately)------------*/
   DEBUG_GRAF   yLOG_note    ("flush");
   glFlush         ();
   /*---(load fonts)---------------------*/
   rc = yviopengl_font_load  ();
   DEBUG_GRAF   yLOG_value   ("font"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIOPENGL_resize        (char *a_title, short a_wide, short a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_GRAF   yLOG_point   ("a_title"   , a_title);
   --rce;  if (a_title == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_info    ("a_title"   , a_title);
   /*---(save keys)----------------------*/
   myVIOPENGL.wide = a_wide;
   myVIOPENGL.tall = a_tall;
   strlcpy (myVIOPENGL.title, a_title, LEN_HUND);
   /*----(update sizes)------------------*/
   yVIEW_resize (a_wide, a_tall, 0);
   yVIEW_debug_list ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIOPENGL_dusk          (void)
{
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(shutdown nopengl)------------*/
   yviopengl_font_close ();
   yX11_end  ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIOPENGL_wrap                 (void)
{
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(free)---------------------------*/
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIOPENGL_main          (char *a_delay, char *a_update, void *a_altinput)
{
   return yKEYS_main (a_delay, a_update, 0, YVIEW_OPENGL, yVIEW_draw, yviopengl_getch, a_altinput);
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNIT_TEST_______o () { return; }

char          unit_answer [LEN_FULL];

char       /*----: set up program urgents/debugging --------------------------*/
yviopengl__unit_quiet   (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yVIOPENGL_unit" };
   yMODE_init (MODE_MAP);
   yMODE_unit_handlers ();
   yVIOPENGL_init ("yVIOPENGL itself ;)", P_VERNUM, MODE_MAP, 300, 500);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yviopengl__unit_loud    (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yVIOPENGL_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_by_name  ("kitchen"      , YURG_ON);
   yURG_by_name  ("ystr"         , YURG_ON);
   yMODE_init (MODE_MAP);
   yMODE_unit_handlers ();
   DEBUG_PROG   yLOG_info     ("yVIOPENGL"  , yVIOPENGL_version   ());
   yVIOPENGL_init ("yVIOPENGL itself ;)", P_VERNUM, MODE_MAP, 300, 500);
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
yviopengl__unit_end     (void)
{
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   yVIOPENGL_wrap ();
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}

char*        /*-> tbd --------------------------------[ leaf   [gs.520.202.40]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yVIOPENGL__unit         (char *a_question, char a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =    0;
   char        x_list      [LEN_RECD];
   char        t           [LEN_RECD];
   int         c           =    0;
   int         x_len       =    0;
   int         i           =    0;
   /*---(preprare)-----------------------*/
   strcpy  (unit_answer, "VIOPENGL         : question not understood");
   /*---(simple questions)---------------*/
   if      (strcmp (a_question, "rec"            )   == 0) {
      /*> if (g_rcurr < 0) snprintf (unit_answer, LEN_RECD, "MACRO rec    (%c) : macro pointer grounded", g_rname);       <* 
       *> else {                                                                                                          <* 
       *>    sprintf (t, "[%-.33s]", g_rkeys);                                                                            <* 
       *>    if (g_rlen > 33)  t [34] = '>';                                                                              <* 
       *>    snprintf (unit_answer, LEN_RECD, "MACRO rec    (%c) : %c %2d %2d%s", g_rname, g_rmode, g_rpos, g_rlen, t);   <* 
       *> }                                                                                                               <* 
       *> return unit_answer;                                                                                             <*/
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



