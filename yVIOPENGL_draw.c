/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIOPENGL.h"
#include    "yVIOPENGL_priv.h"


/*
 * metis � wv4�� � get editing window to show cursor, length, etc                         � M25J0t �  � �
 * metis � mg2�� � make sure menu shows error color when yKEYS locks it                   � M25JAU �  � �
 * metis � wc2�� � status bar must recolor for errors and warnings                        � M25JBH �  � �
 *
 *
 */

char        face_pretty [LEN_LABEL] = "sansation";
/*> char   face_fixed  [30] = "comfortaa";                                            <*/
/*> char   face_fixed [30] = "courier";                                               <*/
/*> char        face_fixed  [LEN_LABEL] = "hack";                                     <*/
char        face_fixed  [LEN_LABEL] = "shrike";



/*====================------------------------------------====================*/
/*===----                             fonts                            ----===*/
/*====================------------------------------------====================*/
static void      o___FONTS___________________o (void) {;}

char
yviopengl_font_load     (void)
{
   char        rce         =  -10;
   DEBUG_GRAF   yLOG_senter   (__FUNCTION__);
   myVIOPENGL.fixed  = yFONT_load(face_fixed);
   DEBUG_GRAF   yLOG_sint     (myVIOPENGL.fixed);
   --rce;  if (myVIOPENGL.fixed <  0) {
      /*> fprintf(stderr, "Problem loading %s\n", face_fixed);                        <*/
      /*> exit(1);                                                                    <*/
      DEBUG_GRAF   yLOG_sexitr   (__FUNCTION__, rce);
      return rce;
   }
   myVIOPENGL.pretty  = yFONT_load(face_pretty);
   DEBUG_GRAF   yLOG_sint     (myVIOPENGL.pretty);
   --rce;  if (myVIOPENGL.pretty <  0) {
      /*> fprintf(stderr, "Problem loading %s\n", face_pretty);                       <*/
      /*> exit(1);                                                                    <*/
      DEBUG_GRAF   yLOG_sexitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_sexit    (__FUNCTION__);
   return 0;
}

char
yviopengl_font_close    (void)
{
   DEBUG_GRAF   yLOG_senter   (__FUNCTION__);
   yFONT_free (myVIOPENGL.fixed);
   myVIOPENGL.fixed  = -1;
   DEBUG_GRAF   yLOG_sint     (myVIOPENGL.fixed);
   yFONT_free (myVIOPENGL.pretty);
   myVIOPENGL.pretty = -1;
   DEBUG_GRAF   yLOG_sint     (myVIOPENGL.pretty);
   DEBUG_GRAF   yLOG_sexit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      text-only drawing                       ----===*/
/*====================------------------------------------====================*/
static void  o___TEXTONLY________o () { return; }

char
yviopengl__text         (char a_part)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_on        =  '-';
   char        x_type      =  '-';
   char        x_orient    =  '-';
   char        x_anchor    =  '-';
   short       x_min, x_max, x_len;
   short       y_min, y_max, y_len;
   short       x_left, x_wide, x_bott, x_tall;
   char        x_name      [LEN_LABEL] = "";
   char        x_text      [LEN_RECD]  = "";
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(get size)-----------------------*/
   yVIEW_curses (a_part, x_name, &x_on, NULL, x_text, &x_orient, &x_left, &x_wide, &x_bott, &x_tall);
   yVIEW_bounds (a_part, NULL, &x_anchor, NULL, &x_min, &x_max, &x_len, &y_min, &y_max, &y_len);
   DEBUG_GRAF   yLOG_complex (x_name, "%c on %c, x_min %4d, x_max %4d, y_min %4d, y_max %4d", a_part, x_on, x_min, x_max, y_min, y_max);
   if (x_on != 'y') {
      DEBUG_GRAF   yLOG_note    ("hidden, not marked for display");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(setup view)---------------------*/
   /*> DEBUG_GRAF   yLOG_note    ("set up the view");                                 <*/
   /*> glViewport      (x_left, x_bott, x_wide, x_tall);                              <* 
    *> glMatrixMode    (GL_PROJECTION);                                               <* 
    *> glLoadIdentity  ();                                                            <* 
    *> glOrtho         (x_min, x_max, y_min, y_max, -500, 500);                       <* 
    *> glMatrixMode    (GL_MODELVIEW);                                                <*/
   /*---(background)---------------------*/
   DEBUG_GRAF   yLOG_note    ("draw a background for ortho/flat");
   /*---(test for editing)---------------*/
   glPushMatrix    (); {
      glColor4f (0.0, 0.0, 0.0, 1.0);
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_min    , y_max    ,  100);
         glVertex3f  (x_max    , y_max    ,  100);
         glVertex3f  (x_max    , y_min    ,  100);
         glVertex3f  (x_min    , y_min    ,  100);
      } glEnd   ();
      switch (a_part) {
      case YVIEW_TITLE    :  yVIOPENGL_by_name ("w_titl", '-', 1.00);  break;
      case YVIEW_VERSION  :  yVIOPENGL_by_name ("w_vers", '-', 1.00);  break;
      case YVIEW_STATUS   :  yVIOPENGL_by_name ("w_sbar", '-', 1.00);  break;
      case YVIEW_KEYS     :  yVIOPENGL_by_name ("w_keys", '-', 1.00);  break;
      case YVIEW_MODES    :  yVIOPENGL_by_name ("w_keys", '-', 1.00);  break;
      }
      if (a_part == YVIEW_KEYS) {
         if      (yKEYS_is_locked () == 1) yVIOPENGL_by_name ("!_errs", '-', 1.00);
         else if (yKEYS_is_error  () == 1) yVIOPENGL_by_name ("!_warn", '-', 1.00);
      }
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_min + 2, y_max - 2,  110);
         glVertex3f  (x_max - 2, y_max - 2,  110);
         glVertex3f  (x_max - 2, y_min + 2,  110);
         glVertex3f  (x_min + 2, y_min + 2,  110);
      } glEnd   ();
      /*> glColor4f (0.00, 0.00, 0.00, 1.00);                                         <* 
       *> glTranslatef (x_min + 2.0, y_min + 2.0, 120.0f);                            <* 
       *> yFONT_print  (myVIOPENGL.fixed, 8, YF_BOTLEF, t);                           <*/
   } glPopMatrix   ();
   /*> glPushMatrix    (); {                                                                      <* 
    *>    /+> DEBUG_GRAF   yLOG_value   ("color"     , s_parts [n].color);             <+/        <* 
    *>    /+> yVIKEYS_view_color (s_parts [n].color, 1.0);                                  <*    <* 
    *>     *> if (s_parts [n].color < 0)                                                    <*    <* 
    *>     *>    glColor4f    (1.00f, 0.50f, 0.50f, 1.0f);                                  <*    <* 
    *>     *> if (s_parts [n].abbr == YVIKEYS_VERSION && yURG_debugmode () == 'y')          <*    <* 
    *>     *>    glColor4f    (1.00f, 0.00f, 0.00f, 1.0f);                                  <*    <* 
    *>     *> if (s_parts [n].abbr == YVIKEYS_STATUS  && yVIKEYS_error  ())                 <*    <* 
    *>     *>    glColor4f    (1.00f, 0.00f, 0.00f, 1.0f);                                  <*    <* 
    *>     *> if (s_parts [n].abbr == YVIKEYS_MODES   && yMACRO_exe_mode () == MACRO_RUN)   <*    <* 
    *>     *>    glColor4f    (1.00f, 0.00f, 0.00f, 1.0f);                                  <+/   <* 
    *>    /+> yCOLOR_diff_color (a_part, 0.5);                                         <+/        <* 
    *>    /+> glColor4f (0.00, 0.00, 0.00, 1.00);                                         <*      <* 
    *>     *> glBegin         (GL_POLYGON); {                                             <*      <* 
    *>     *>    glVertex3f  (x_min, y_max,  -80);                                        <*      <* 
    *>     *>    glVertex3f  (x_max, y_max,  -80);                                        <*      <* 
    *>     *>    glVertex3f  (x_max, y_min,  -80);                                        <*      <* 
    *>     *>    glVertex3f  (x_min, y_min,  -80);                                        <*      <* 
    *>     *> } glEnd   ();                                                               <+/     <* 
    *>    glColor4f (0.0, 0.0, 0.0, 1.0);                                                         <* 
    *>    glBegin         (GL_POLYGON); {                                                         <* 
    *>       glVertex3f  (x_min    , y_max    ,  100);                                            <* 
    *>       glVertex3f  (x_max    , y_max    ,  100);                                            <* 
    *>       glVertex3f  (x_max    , y_min    ,  100);                                            <* 
    *>       glVertex3f  (x_min    , y_min    ,  100);                                            <* 
    *>    } glEnd   ();                                                                           <* 
    *>    glColor4f (0.75, 0.75, 0.00, 1.00);                                                     <* 
    *>    glBegin         (GL_POLYGON); {                                                         <* 
    *>       glVertex3f  (x_min + 2, y_max - 2,  -60);                                            <* 
    *>       glVertex3f  (x_max - 0, y_max - 2,  -60);                                            <* 
    *>       glVertex3f  (x_max - 0, y_min + 2,  -60);                                            <* 
    *>       glVertex3f  (x_min + 2, y_min + 2,  -60);                                            <* 
    *>    } glEnd   ();                                                                           <* 
    *> } glPopMatrix   ();                                                                        <*/
   /*---(display text)-------------------*/
   DEBUG_GRAF   yLOG_info    ("x_text"    , x_text);
   if (strlen (x_text) > 0) {
      glPushMatrix    (); {
         if (x_orient == 'r') {
            glTranslatef (-2.0f, 5.0f, 120.0f);
            glRotatef    ( 90.0, 0.0f, 0.0f, 1.0f);
         } else {
            glTranslatef ( 3.0f, 2.0f, 120.0f);
         }
         /*> yVIKEYS_view_color_adj (s_parts [n].color, YCOLOR_MIN, 0.8);             <*/
         glColor4f (0.00, 0.00, 0.00, 1.00);
         /*> yFONT_print  (myVIKEYS.font, myVIKEYS.point, YF_BOTLEF, x_text);         <*/
         yFONT_print  (myVIOPENGL.fixed, 8, YF_BOTLEF, x_text);
      } glPopMatrix   ();
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char  yviopengl_title         (void)  { return yviopengl__text (YVIEW_TITLE); }
char  yviopengl_version       (void)  { return yviopengl__text (YVIEW_VERSION); }
char  yviopengl_modes         (void)  { return yviopengl__text (YVIEW_MODES); }
char  yviopengl_status        (void)  { return yviopengl__text (YVIEW_STATUS); }
char  yviopengl_keys          (void)  { return yviopengl__text (YVIEW_KEYS); }



/*====================------------------------------------====================*/
/*===----                     fancy text drawing                       ----===*/
/*====================------------------------------------====================*/
static void  o___FANCY___________o () { return; }

char
yviopengl_univs         (void)
{
   char        rc          =    0;
   char        t           [LEN_LABEL] = "";
   char        x_on        =  '-';
   short       x_left, x_wide, x_bott, x_tall;
   char        x_name      [LEN_LABEL] = "";
   char        x_pre       [LEN_LABEL] = "";
   char        x_main      [LEN_RECD]  = "";
   int         i           =    0;
   int         x_last      =   -1;
   char       *x_disp      = " 0 1 2 3 4 5 6 7 8 9 � A B C D E F G H I J K L M N O P Q R S T U V W X Y Z � � � � �";
   ushort      x_pos       =    0;
   short       x_ref       =    0;
   uchar       x_used      =    0;
   int         x_off       =    2;
   ushort      c           =    0;
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   yVIEW_curses (YVIEW_BUFFER, x_name, &x_on, NULL, NULL, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   DEBUG_GRAF   yLOG_complex  (x_name, "%c on %c, %3dl, %3dw, %3db, %3dt", YVIEW_BUFFER, x_on, x_left, x_wide, x_bott, x_tall);
   /*> sprintf (x_main, "%s%s%s", BACK_YEL, BOLD_BLK, x_univ);                        <*/
   yVIOPENGL_by_name ("u_back", '-', 1.00);
   mvprintw (x_bott, x_left, "%-*.*s", x_wide, x_wide, x_disp);
   rc = yMAP_by_cursor (YMAP_UNIV, YDLST_HEAD, &x_pos, &x_ref, NULL, &x_used);
   yMAP_axis_grid (YMAP_UNIV , NULL, &c, NULL, NULL);
   while (rc >= 0) {
      DEBUG_GRAF   yLOG_complex  ("review", "%3d, %3d, %3d/%c", x_pos, x_ref, x_used, x_used);
      if      (x_pos < 10)  x_off = 1;
      else if (x_pos < 36)  x_off = 3;
      else                  x_off = 5;
      if (c == x_pos)  x_used = YMAP_CURR;
      switch (x_used) {
      case YMAP_CURR   :
         yVIOPENGL_by_name ("u_curr", '-', 1.00);
         mvprintw (x_bott, x_left +  x_off + (x_pos * 2), "%c", YSTR_UNIV [x_pos]);  break;
         break;
      case YMAP_USED  :
         yVIOPENGL_by_name ("u_used", '-', 1.00);
         mvprintw (x_bott, x_left +  x_off + (x_pos * 2), "%c", YSTR_UNIV [x_pos]);  break;
         break;
      case YMAP_PLACE :
         yVIOPENGL_by_name ("u_place", '-', 1.00);
         mvprintw (x_bott, x_left +  x_off + (x_pos * 2), "%c", YSTR_UNIV [x_pos]);  break;
         break;
      }
      rc = yMAP_by_cursor (YMAP_UNIV, YDLST_NEXT, &x_pos, &x_ref, NULL, &x_used);
   }
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       drawing functions                      ----===*/
/*====================------------------------------------====================*/
static void  o___DRAWING_________o () { return; }

char
yviopengl__color        (char a_part)
{
   /*---(locals)-----------+------+----+-*/
   char        x_edit      =   '-';
   char        x_code      =   '-';
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_char    ("a_part"     , a_part);
   DEBUG_GRAF   yLOG_char    ("curr"       , yMODE_curr ());
   DEBUG_GRAF   yLOG_char    ("prev"       , yMODE_prev ());
   /*---(fast-track formula)-------------*/
   if (a_part == YVIEW_FORMULA) {
      if (yMODE_curr () != MODE_SOURCE && yMODE_prev () != MODE_SOURCE)  {
         DEBUG_GRAF   yLOG_note    ("formula fast track");
         x_code = 'm';
      }
   }
   /*---(fast-track command)-------------*/
   if (a_part == YVIEW_COMMAND) {
      if (strchr (":/;", yMODE_curr ()) == NULL && strchr (":/;", yMODE_prev ()) == NULL) {
         DEBUG_GRAF   yLOG_note    ("command fast track");
         x_code = 'c';
      }
   }
   /*---(check focused)------------------*/
   if (x_code == '-' && strchr (MODES_ONELINE, yMODE_curr ()) != NULL)  {
      DEBUG_GRAF   yLOG_note    ("current source mode");
      x_edit = 'y';
      x_code = 's';
   }
   /*---(check editing)------------------*/
   else if (x_code == '-' && strchr (MODES_ONELINE, yMODE_prev ()) != NULL)  {
      DEBUG_GRAF   yLOG_note    ("sub-mode editing");
      x_edit = 'y';
      switch (yMODE_curr ()) {
      case SMOD_SREG       : x_code = 't';  break;
      case UMOD_REPLACE    : x_code = 'r';  break;
      case UMOD_INPUT      : x_code = 'i';  break;
      case UMOD_WANDER     : x_code = 'w';  break;
      default              : x_code = '-';  break;
      }
   }
   /*---(just a safety)------------------*/
   else if (x_code == '-') {
      DEBUG_GRAF   yLOG_note    ("catch for mistakes");
      x_code = 'e';
   }
   /*---(set curses color)---------------*/
   DEBUG_GRAF   yLOG_note    ("assign a opengl color");
   DEBUG_GRAF   yLOG_char    ("x_code"    , x_code);
   switch (x_code) {
   case  'm' :  yVIOPENGL_by_name ("i_maps", '-', 1.00);  break;
   case  's' :  yVIOPENGL_by_name ("i_srcs", '-', 1.00);  break;
   case  'c' :  yVIOPENGL_by_name ("w_cmds", '-', 1.00);  break;
   case  't' :  yVIOPENGL_by_name ("i_treg", '-', 1.00);  break;
   case  'r' :  yVIOPENGL_by_name ("i_repl", '-', 1.00);  break;
   case  'i' :  yVIOPENGL_by_name ("i_inpt", '-', 1.00);  break;
   case  'w' :  yVIOPENGL_by_name ("i_wand", '-', 1.00);  break;
   case  'e' :  yVIOPENGL_by_name ("!_errs", '-', 1.00);  break;
   default   :  yVIOPENGL_by_name ("i_maps", '-', 1.00);  break;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_char    ("x_edit"    , x_edit);
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return x_edit;
}

char
yviopengl__display         (char a_part, char a_loc, char a_style)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_edit      =  '-';
   char        x_on        =  '-';
   char        x_type      =  '-';
   char        x_anchor    =  '-';
   short       x_min, x_max, x_len;
   short       y_min, y_max, y_len;
   short       x_left, x_wide, x_bott, x_tall;
   char        x_name      [LEN_LABEL] = "";
   char        m           =  '-';
   char        l           [LEN_LABEL] = "";
   short       n, a, b, c, e;
   char        f           [LEN_LABEL] = "";
   char        t           [LEN_RECD]  = "";
   char        x_mark      =  ' ';
   short       x_beg       =    0;
   short       x_end       =    0;
   int         x_off       =    0;
   char        nn          [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("args"      , "%c part, %c loc, %c style", a_part, a_loc, a_style);
   /*---(get size)-----------------------*/
   yVIEW_curses (a_loc, x_name, &x_on, NULL, NULL, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   yVIEW_bounds (a_loc, &x_type, &x_anchor, NULL, &x_min, &x_max, &x_len, &y_min, &y_max, &y_len);
   DEBUG_GRAF   yLOG_complex (x_name, "%c on %c, x_min %4d, x_max %4d, y_min %4d, y_max %4d", a_part, x_on, x_min, x_max, y_min, y_max);
   if (x_on != 'y') {
      DEBUG_GRAF   yLOG_note    ("hidden, not marked for display");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(get contents)-------------------*/
   ySRC_contents (a_part, &m, l, &n, &a, &b, &c, &e, f, t);
   DEBUG_GRAF   yLOG_complex  ("pos"       , "%3dn, %3da, %3db, %3dc, %3de", n, a, b, c, e);
   if (strlen (t) == 0)  strcpy (t, "�����");
   DEBUG_GRAF   yLOG_complex  ("content"   , "%c �%s�", m, t);
   /*> strlcpy (l, "JESUS", LEN_LABEL);                                               <*/
   DEBUG_GRAF   yLOG_info     ("label"     , l);
   DEBUG_GRAF   yLOG_info     ("format"    , f);
   /*---(test for editing)---------------*/
   glPushMatrix    (); {
      glColor4f (0.0, 0.0, 0.0, 1.0);
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_min    , y_max    ,  100);
         glVertex3f  (x_max    , y_max    ,  100);
         glVertex3f  (x_max    , y_min    ,  100);
         glVertex3f  (x_min    , y_min    ,  100);
      } glEnd   ();
      x_edit = yviopengl__color (a_part);
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_min + 2, y_max - 2,  110);
         glVertex3f  (x_max - 2, y_max - 2,  110);
         glVertex3f  (x_max - 2, y_min + 2,  110);
         glVertex3f  (x_min + 2, y_min + 2,  110);
      } glEnd   ();
      glColor4f (0.00, 0.00, 0.00, 1.00);
      glTranslatef (x_min + 2.0, y_min + 2.0, 120.0f);
      yFONT_print  (myVIOPENGL.fixed, 8, YF_BOTLEF, t);
   } glPopMatrix   ();
   DEBUG_GRAF   yLOG_char    ("x_edit"    , x_edit);
   /*---(draw)---------------------------*/
   /*> if (a_part == YVIEW_COMMAND && x_edit != 'y') {                                                           <* 
    *>    DEBUG_GRAF   yLOG_note     ("display message in command space");                                       <* 
    *>    x_len = strlen (yMODE_message ());                                                                     <* 
    *>    if (x_len < x_wide)  mvprintw (x_bott, x_left, "%-*.*s" , x_wide - 1, x_wide - 1, yMODE_message ());   <* 
    *>    else                 mvprintw (x_bott, x_left, "%-*.*s�", x_wide - 1, x_wide - 1, yMODE_message ());   <* 
    *>    DEBUG_GRAF   yLOG_exit    (__FUNCTION__);                                                              <* 
    *>    return 0;                                                                                              <* 
    *> }                                                                                                         <*/
   /*---(content)------------------------*/
   /*> if (a_part == YVIEW_COMMAND) {                                                                                            <* 
    *>    x_off = 4;                                                                                                             <* 
    *>    strlpadn (n, nn, '.', '>', 4);                                                                                         <* 
    *>    mvprintw (x_bott, x_left, "%s %-*.*s ", nn, a, a, t + b);                                                              <* 
    *> } else {                                                                                                                  <* 
    *>    switch (a_style) {                                                                                                     <* 
    *>    case '-' :                                                                                                             <* 
    *>       x_off = 0;                                                                                                          <* 
    *>       if (n == 0) {                                                                                                       <* 
    *>          mvprintw (x_bott, x_left, " %c%-*.*s ", G_CHAR_NULL, a - 1, a - 1, YSTR_EMPTY);                                  <* 
    *>       } else {                                                                                                            <* 
    *>          mvprintw (x_bott, x_left, " %-*.*s ", a, a, t + b);                                                              <* 
    *>       }                                                                                                                   <* 
    *>       break;                                                                                                              <* 
    *>    case 's' :                                                                                                             <* 
    *>       x_off = 4;                                                                                                          <* 
    *>       if (n == 0) {                                                                                                       <* 
    *>          mvprintw (x_bott, x_left, "%-4.4s %c%-*.*s ", "����", G_CHAR_NULL, a - 1, a - 1, YSTR_EMPTY);                    <* 
    *>       } else {                                                                                                            <* 
    *>          strlpadn (n, nn, '.', '>', 4);                                                                                   <* 
    *>          mvprintw (x_bott, x_left, "%s %-*.*s ", nn, a, a, t + b);                                                        <* 
    *>       }                                                                                                                   <* 
    *>       break;                                                                                                              <* 
    *>    case 'l' :                                                                                                             <* 
    *>       x_off = 12;                                                                                                         <* 
    *>       if (n == 0) {                                                                                                       <* 
    *>          mvprintw (x_bott, x_left, " %-6.6s %-4.4s %c%-*.*s ", l, "����", G_CHAR_NULL, a - 1, a - 1, YSTR_EMPTY);         <* 
    *>       } else {                                                                                                            <* 
    *>          strlpadn (n, nn, '.', '>', 4);                                                                                   <* 
    *>          mvprintw (x_bott, x_left, " %-6.6s %s %-*.*s ", l, nn, a, a, t + b);                                             <* 
    *>       }                                                                                                                   <* 
    *>       break;                                                                                                              <* 
    *>    case 'x' :                                                                                                             <* 
    *>       x_off = 13 + strlen (f);                                                                                            <* 
    *>       if (n == 0) {                                                                                                       <* 
    *>          mvprintw (x_bott, x_left, " %-6.6s %s %-4.4s %c%-*.*s ", l, f, "����", G_CHAR_NULL, a - 1, a - 1, YSTR_EMPTY);   <* 
    *>       } else {                                                                                                            <* 
    *>          strlpadn (n, nn, '.', '>', 4);                                                                                   <* 
    *>          mvprintw (x_bott, x_left, " %-6.6s %s %s %-*.*s ", l, f, nn, a, a, t + b);                                       <* 
    *>       }                                                                                                                   <* 
    *>       break;                                                                                                              <* 
    *>    }                                                                                                                      <* 
    *> }                                                                                                                         <*/
   /*---(beg marker)---------------------*/
   /*> if (n != 0) {                                                                  <* 
    *>    if (b >  0)   x_mark = '<';                                                 <* 
    *>    else          x_mark = '�';                                                 <* 
    *>    mvprintw (x_bott, x_left + x_off, "%c", x_mark);                            <* 
    *> }                                                                              <*/
   /*---(update offset)------------------*/
   ++x_off;
   /*---(end marker)---------------------*/
   /*> if (n != 0) {                                                                  <* 
    *>    x_len = e - b + 1;                                                          <* 
    *>    if (e != n - 1) x_mark = '>';                                               <* 
    *>    else            x_mark = '�';                                               <* 
    *>    mvprintw (x_bott, x_left + x_off + x_len, "%c", x_mark);                    <* 
    *> }                                                                              <*/
   /*---(selection)----------------------*/
   /*> if (x_edit == 'y' && ySRC_select_islive () && n > 0) {                                 <* 
    *>    ysrc_select_curr (&x_beg, &x_end, NULL);                                            <* 
    *>    if (x_beg < b)  x_beg = b;                                                          <* 
    *>    if (x_end > e)  x_end = e;                                                          <* 
    *>    x_len = x_end - x_beg + 1;                                                          <* 
    *>    yVIOPENGL_by_name ("i_sele", '-', 1.00);                                                       <* 
    *>    mvprintw (x_bott, x_left + x_off + x_beg - b, "%-*.*s", x_len, x_len, t + x_beg);   <* 
    *> }                                                                                      <*/
   /*---(current)------------------------*/
   /*> if (x_edit == 'y' && n > 0) {                                                  <* 
    *>    yVIOPENGL_by_name ("i_maps", '-', 1.00);                                               <* 
    *>    mvprintw (x_bott, x_left + x_off + c - b, "%c", t [c]);                     <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yviopengl_formula       (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   yviopengl__display (YVIEW_FORMULA, YVIEW_FORMULA, myVIOPENGL.p_formula);
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yviopengl_formula_min   (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   myVIOPENGL.p_formula = '-';
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yviopengl_formula_small (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   myVIOPENGL.p_formula = 's';
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yviopengl_formula_label (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   myVIOPENGL.p_formula = 'l';
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yviopengl_formula_max   (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   myVIOPENGL.p_formula = 'x';
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yviopengl_command       (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   yviopengl__display (YVIEW_COMMAND, YVIEW_COMMAND, '-');
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yviopengl_float         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_mode      =  '-';
   char        x_on        =  '-';
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(check modes)-----------------*/
   DEBUG_GRAF   yLOG_char    ("mode_curr" , yMODE_curr ());
   DEBUG_GRAF   yLOG_char    ("mode_prev" , yMODE_prev ());
   if      (strchr (MODES_ONELINE, yMODE_curr ()) != NULL )      x_mode = yMODE_curr ();
   else if (strchr (MODES_ONELINE, yMODE_prev ()) != NULL )      x_mode = yMODE_prev ();
   DEBUG_GRAF   yLOG_char    ("x_mode"    , x_mode);
   if (x_mode == '-')  {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check modes)-----------------*/
   --rce;  switch (x_mode) {
   case MODE_SOURCE  :
      DEBUG_GRAF   yLOG_note    ("mode source");
      if (!yVIEW_showing (YVIEW_FORMULA))  yviopengl__display (YVIEW_FORMULA, YVIEW_FLOAT, '-');
      break;
   case MODE_COMMAND :
   case MODE_SEARCH  :
   case SMOD_HINT    :
      DEBUG_GRAF   yLOG_note    ("mode command/search");
      if (!yVIEW_showing (YVIEW_COMMAND))  yviopengl__display (YVIEW_COMMAND, YVIEW_FLOAT, '-');
      break;
   default :
      DEBUG_GRAF   yLOG_note    ("default");
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)--------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      menu focused                            ----===*/
/*====================------------------------------------====================*/
static void  o___MENU____________o () { return; }



