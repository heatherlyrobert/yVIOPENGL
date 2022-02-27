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
yVIOPENGL_init          (char *a_title, char *a_version, char a_mode, int a_wide, int a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(start window)-------------------*/
   rc = yX11_start (a_title, a_wide, a_tall, YX_FOCUSABLE, YX_FIXED, '-');
   DEBUG_GRAF   yLOG_value   ("yX11"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(color)--------------------------*/
   DEBUG_GRAF   yLOG_note    ("clearing");
   /*> glClearColor    (1.0f, 1.0f, 1.0f, 1.0f);                                      <*/
   glClearColor    (0.3f, 0.3f, 0.3f, 1.0f);
   glClearDepth    (1.0f);
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
   /*---(color options)------------------*/
   rc = yCOLOR_init     (YCOLOR_WHEEL );
   /*> yVIKEYS_cmds_addX (YVIKEYS_M_VIEW  , "palette"     , ""    , "isss" , yCOLOR_palette             , "" );   <* 
    *> yVIKEYS_cmds_addX (YVIKEYS_M_VIEW  , "wheel"       , ""    , "s"    , yCOLOR_wheel               , "" );   <* 
    *> yVIKEYS_cmds_addX (YVIKEYS_M_VIEW  , "degree"      , "deg" , "i"    , yCOLOR_deg                 , "" );   <* 
    *> yVIKEYS_cmds_addX (YVIKEYS_M_VIEW  , "harmony"     , "har" , "s"    , yCOLOR_harm                , "" );   <* 
    *> yVIKEYS_cmds_addX (YVIKEYS_M_VIEW  , "value"       , "val" , "s"    , yCOLOR_val                 , "" );   <* 
    *> yVIKEYS_cmds_addX (YVIKEYS_M_VIEW  , "saturation"  , "sat" , "s"    , yCOLOR_sat                 , "" );   <*/
   yCOLOR_diff_scheme (YCOLOR_WHITE);
   yviopengl_color_init ();
   /*----(first)-------------------------*/
   rc = yMODE_init           (a_mode);
   DEBUG_GRAF   yLOG_value   ("yMODE"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(TEMP)------------------------*/
   rc = yFILE_init           ();
   DEBUG_GRAF   yLOG_value   ("yFILE"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yMODE_debug_status ();
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
   yviopengl_resize ();
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
   rc = yviopengl_font_load  ();
   DEBUG_GRAF   yLOG_value   ("font"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(curses drawing)-----------------*/
   yVIEW_simple (YVIEW_TITLE  , 0, yviopengl_title);
   yVIEW_simple (YVIEW_VERSION, 0, yviopengl_version);
   yVIEW_simple (YVIEW_MODES  , 0, yviopengl_modes);
   yVIEW_simple (YVIEW_STATUS , 0, yviopengl_status);
   yVIEW_simple (YVIEW_COMMAND, 0, yviopengl_command);
   yVIEW_simple (YVIEW_FORMULA, 0, yviopengl_formula);
   yVIEW_simple (YVIEW_FLOAT  , 0, yviopengl_float);
   yVIEW_simple (YVIEW_KEYS   , 0, yviopengl_keys);
   yVIEW_simple (YVIEW_BUFFER , 0, yviopengl_univs);
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
yVIOPENGL_wrap                 (void)
{
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(shutdown ncurses)------------*/
   yviopengl_font_close ();
   yX11_end  ();
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
   yMODE_handler_setup ();
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
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("ystr"         , YURG_ON);
   yMODE_init (MODE_MAP);
   yMODE_handler_setup ();
   DEBUG_SCRP   yLOG_info     ("yVIOPENGL"  , yVIOPENGL_version   ());
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


