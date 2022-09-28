/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIOPENGL.h"
#include    "yVIOPENGL_priv.h"

char
yviopengl_menu__back     (char a_lvl, short x_min, short x_cen, short x_max, short y_min, short y_mid, short y_max)
{
   int         i           =    0;
   DEBUG_GRAF   yLOG_complex ("x args", "x_min %4d, x_max %4d, x_cen %4d", x_min, x_max, x_cen);
   DEBUG_GRAF   yLOG_complex ("y args", "y_min %4d, y_max %4d, y_cen %4d", y_min, y_max, y_mid);
   glPushMatrix    (); {
      glTranslatef (0.0  , 0.0  , 850.0);
      glColor4f (0.00, 0.00, 0.00, 1.00);
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_min    , y_max    ,  100);
         glVertex3f  (x_max    , y_max    ,  100);
         glVertex3f  (x_max    , y_min    ,  100);
         glVertex3f  (x_min    , y_min    ,  100);
      } glEnd   ();
      glTranslatef (0.0  , 0.0  ,  10.0);
      if (yKEYS_is_locked ())  glColor4f (0.50, 0.00, 0.00, 1.00);
      else                     glColor4f (0.70, 0.35, 0.15, 1.00);
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_min + 2, y_max - 2,  105);
         glVertex3f  (x_max - 2, y_max - 2,  105);
         glVertex3f  (x_max - 2, y_min + 2,  105);
         glVertex3f  (x_min + 2, y_min + 2,  105);
      } glEnd   ();
      if (yKEYS_is_locked ())  glColor4f (0.70, 0.00, 0.00, 1.00);
      else                     yVIOPENGL_by_name ("m_back", '-', 1.00);
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_min + 2, y_max - 15,  110);
         glVertex3f  (x_max - 2, y_max - 15,  110);
         glVertex3f  (x_max - 2, y_min + 15,  110);
         glVertex3f  (x_min + 2, y_min + 15,  110);
      } glEnd   ();
      glColor4f (0.00, 0.00, 0.00, 1.00);
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_cen - 6, y_max    ,  120);
         glVertex3f  (x_cen    , y_max - 6,  120);
         glVertex3f  (x_cen + 6, y_max    ,  120);
      } glEnd   ();
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_min    , y_mid + 6,  120);
         glVertex3f  (x_min + 7, y_mid    ,  120);
         glVertex3f  (x_min    , y_mid - 6,  120);
      } glEnd   ();
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_max    , y_mid + 6,  120);
         glVertex3f  (x_max - 6, y_mid    ,  120);
         glVertex3f  (x_max    , y_mid - 6,  120);
      } glEnd   ();
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_min + 20, y_min    ,  120);
         glVertex3f  (x_min + 26, y_min + 6,  120);
         glVertex3f  (x_min + 32, y_min    ,  120);
      } glEnd   ();
      glBegin         (GL_POLYGON); {
         glVertex3f  (x_max - 20, y_min    ,  120);
         glVertex3f  (x_max - 26, y_min + 6,  120);
         glVertex3f  (x_max - 32, y_min    ,  120);
      } glEnd   ();
      glTranslatef (0.0  , 0.0  ,  10.0);
      if (yKEYS_is_locked ())  glColor4f (0.75, 0.75, 0.75, 1.00);
      else                     glColor4f (0.70, 0.35, 0.15, 1.00);
      for (i = 0; i < 360; i += (360.0 / 18.0)) {
         glPushMatrix    (); {
            glTranslatef (x_cen, y_mid, 0.0);
            glRotatef    ( i, 0.0f, 0.0f, 1.0f);
            glTranslatef ( 0.0 , +25.0 + 15.0 * a_lvl, 0.0);
            glBegin         (GL_POLYGON); {
               glVertex3f  (-4.0,  0.0,  120);
               glVertex3f  ( 0.0, 10.0,  120);
               glVertex3f  ( 4.0,  0.0,  120);
            } glEnd   ();
         } glPopMatrix   ();
      }
   } glPopMatrix   ();
   return 0;
}

char
yviopengl_menus         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   int         x_len       =    0;
   int         x_cen, y_mid;
   char        t           [LEN_HUND]  = "";
   char        s           [LEN_HUND]  = "";
   short       x, y, xo, yo;
   char        l, a, v, x_lvl;
   char        b           [LEN_TERSE] = "";

   char        x_on        =  '-';
   char        x_type      =  '-';
   char        x_anchor    =  '-';
   short       x_min       =    0;
   short       x_max       =    0;
   short       x_dif       =    0;
   short       y_min       =    0;
   short       y_max       =    0;
   short       y_dif       =    0;
   char        x_name      [LEN_LABEL] = "";
   char        x_lock      =    0;
   static char x_lasts     [LEN_LABEL] = "";
   static char x_lastb     [LEN_TERSE] = "";
   static char x_lastl     =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_GRAF   yLOG_char    ("mode"      , yMODE_curr ());
   if (yMODE_not (SMOD_MENUS)) {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(get size)-----------------------*/
   yVIEW_curses (YVIEW_MENUS, x_name, &x_on, NULL, NULL, NULL, &x_min, &x_dif, &y_min, &y_dif);
   x_max  = x_min + x_dif;
   y_max  = y_min + y_dif;
   x_cen  = x_min + (x_dif * 0.50);
   y_mid  = y_min + (y_dif * 0.50);
   DEBUG_GRAF   yLOG_complex (x_name, "x_min %4d, x_max %4d, x_dif %4d, x_cen %4d", x_min, x_max, x_dif, x_cen);
   DEBUG_GRAF   yLOG_complex (x_name, "y_min %4d, y_max %4d, y_dif %4d, y_cen %4d", y_min, y_max, y_dif, y_mid);
   /*---(background)---------------------*/
   rc = yCMD_menu_overall (&x_lvl, b, s);
   yviopengl_menu__back (x_lvl, x_min, x_cen, x_max, y_min, y_mid, y_max);
   DEBUG_GRAF   yLOG_complex ("before"   , "%d, %s, %s", x_lvl, b, s);
   /*> DEBUG_GRAF   yLOG_complex ("last"     , "%d, %s, %s", x_lastl, x_lastb, x_lasts);   <*/
   /*> if (x_lvl == 0)           { strcpy (x_lasts, ""); strcpy (x_lastb, ""); }      <*/
   /*> if (strcmp (b, "") == 0)  { strlcpy (b, x_lastb, LEN_TERSE); x_lvl = x_lastl; }   <* 
    *> else                      { strlcpy (x_lastb, b, LEN_TERSE); x_lastl = x_lvl; }   <* 
    *> if (strcmp (s, "") == 0)  strlcpy (s, x_lasts, LEN_LABEL);                        <* 
    *> else                      strlcpy (x_lasts, s, LEN_LABEL);                        <*/
   /*> DEBUG_GRAF   yLOG_complex ("after"    , "%d, %s, %s", x_lvl, b, s);            <*/
   /*> DEBUG_GRAF   yLOG_complex ("last"     , "%d, %s, %s", x_lastl, x_lastb, x_lasts);   <*/
   /*---(check status)-------------------*/
   x_lock = yKEYS_is_locked ();
   DEBUG_GRAF   yLOG_value   ("x_lock"    , x_lock);
   /*---(header/footer)------------------*/
   glPushMatrix    (); {
      if (x_lock == 1)  glColor4f (1.00, 1.00, 1.00, 1.00);
      else              glColor4f (0.00, 0.00, 0.00, 1.00);
      /*> glTranslatef (x_cen, y_mid, 880.0);                                         <*/
      switch (x_lvl) {
      case  0 : strlcpy (t, " main menu ", LEN_HUND); break;
      case  1 : sprintf (t, " %s sub-menu ", s);      break;
      case  2 : sprintf (t, " %s options " , s);      break;
      }
      glPushMatrix    (); {
         glTranslatef (x_cen, y_max - 15, 1000.0);
         yFONT_print  (myVIOPENGL.fixed, 8, YF_BOTCEN, t);
         glTranslatef ( 0.00, 18 - y_dif, 0.0);
         if (x_lock == 1) yFONT_print  (myVIOPENGL.fixed, 8, YF_BOTCEN, "bad key, locked, ее to exit");
         else             yFONT_print  (myVIOPENGL.fixed, 8, YF_BOTCEN, "wider, flatter, and universal");
      } glPopMatrix   ();
      if (x_lvl > 0) {
         sprintf (t, "╡%s", b);
      }
      sprintf (t, "\\%s", b);
      glPushMatrix    (); {
         glTranslatef (x_min + 5, y_max - 15, 1000.0);
         yFONT_print  (myVIOPENGL.fixed, 8, YF_BOTLEF, t);
         glTranslatef (x_dif - 10, 0         , 0.0);
         yFONT_print  (myVIOPENGL.fixed, 8, YF_BOTRIG, P_VERNUM);
      } glPopMatrix   ();
   } glPopMatrix   ();
   /*---(items)--------------------------*/
   glPushMatrix    (); {
      yVIOPENGL_by_name ("m_back", '-', 1.00);
      for (i = 0; i < 400; ++i) {
         rc = yCMD_menu_data          (i, &x, &y, b, &xo, &yo, &l, t, &a, &v);
         if (rc < 0)  break;
         DEBUG_GRAF   yLOG_complex (t, "%2d, %3dx, %3dy, %s, %3dxo, %3dyo, %2dl, %c %c", i, x, y, b, xo, yo, l, a, v);
         if (strcmp (t, "м") == 0)  continue;
         /*> yVIOPENGL_by_name ("m_bull", '-', 1.00);                                    <*/
         glColor4f (0.00, 0.00, 0.00, 1.00);
         glPushMatrix    (); {
            glTranslatef (x, y, 1000);
            if      (xo > 0) { sprintf (s, "%s)", b);  a = YF_BOTLEF; }
            else if (xo < 0) { sprintf (s, "(%s", b);  a = YF_BOTRIG; }
            else             { sprintf (s, "%s" , b);  a = YF_BOTCEN; }
            yFONT_print  (myVIOPENGL.fixed, 8, a, s);
            /*> if      (xo == 0)  xo -= l / 2;                                          <* 
             *> else if (xo <  0)  xo -= l - 1;                                          <*/
            /*> switch (v) {                                                             <* 
             *> case 'y' : yVIOPENGL_by_name ("m_menu", '-', 1.00);   break;             <* 
             *> default  : yVIOPENGL_by_name ("m_back", '-', 1.00);   break;             <* 
             *> }                                                                        <*/
            glTranslatef (xo, yo, 0);
            yFONT_print  (myVIOPENGL.fixed, 8, a, t);
         } glPopMatrix   ();
      }
   } glPopMatrix   ();
   /*---(if locked)----------------------*/
   /*> if (x_lock == 1) {                                                                     <* 
    *>    glPushMatrix    (); {                                                               <* 
    *>       glColor4f (0.30, 0.00, 0.00, 1.00);                                              <* 
    *>       glBegin         (GL_POLYGON); {                                                  <* 
    *>          glVertex3f  (x_min + 10, y_mid + 20,  990);                                   <* 
    *>          glVertex3f  (x_max - 10, y_mid + 20,  990);                                   <* 
    *>          glVertex3f  (x_max - 10, y_mid - 20,  990);                                   <* 
    *>          glVertex3f  (x_min + 10, y_mid - 20,  990);                                   <* 
    *>       } glEnd   ();                                                                    <* 
    *>       glColor4f (0.80, 0.80, 0.80, 1.00);                                              <* 
    *>       glTranslatef (x_cen, y_mid, 1000.0);                                             <* 
    *>       yFONT_print  (myVIOPENGL.fixed, 10, YF_MIDCEN, "bad key, locked, ее to exit");   <* 
    *>    } glPopMatrix   ();                                                                 <* 
    *> }                                                                                      <*/
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}
