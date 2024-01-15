/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIOPENGL.h"
#include    "yVIOPENGL_priv.h"



/*====================------------------------------------====================*/
/*===----                        resize the parts                      ----===*/
/*====================------------------------------------====================*/
static void      o___RESIZE__________________o (void) {;}

char
yviopengl_resize        (void)
{
   char        rc         =    0;
   short       x_wide     =    0;
   short       x_tall     =    0;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   yVIEW_size (YVIEW_WINDOW, NULL, NULL, &x_wide, NULL, &x_tall);
   DEBUG_LOOP   yLOG_value   ("x_wide"    , x_wide);
   DEBUG_LOOP   yLOG_value   ("x_tall"    , x_tall);
   if (myVIOPENGL.wide != x_wide || myVIOPENGL.tall != x_tall) {
      rc = yX11_resize (x_wide, x_tall);
      DEBUG_LOOP   yLOG_value   ("yX11"      , rc);
      myVIOPENGL.wide = x_wide;
      myVIOPENGL.tall = x_tall;
      yVIEW_debug_list ();
   }
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        gather input                          ----===*/
/*====================------------------------------------====================*/
static void      o___INPUT___________________o (void) {;}

char
yviopengl_getch         (char a_block, char *a_ch)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_ch        =    0;
   char        x_key       =    0;
   XKeyEvent  *key_event;
   int         the_bytes;
   char        the_keys    [5];
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_LOOP   yLOG_schar   (a_block);
   --rce;  if (a_block == 0 || strchr ("y-", a_block) == NULL) {
      DEBUG_LOOP   yLOG_snote   ("illegal blocking type");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_LOOP   yLOG_spoint  (a_ch);
   --rce;  if (a_ch == NULL) {
      DEBUG_LOOP   yLOG_snote   ("NULL RETURN VAR");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   DEBUG_LOOP   yLOG_snote   ("default");
   *a_ch = 0;
   /*---(set delay)----------------------*/
   if (a_block == 'y') {
      DEBUG_LOOP   yLOG_snote   ("blocked, wait");
      XNextEvent(YX_DISP, &YX_EVNT);
   }
   else {
      if (XPending(YX_DISP))   XNextEvent(YX_DISP, &YX_EVNT);
      else {
         DEBUG_LOOP   yLOG_snote   ("no event pending");
         DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
   }
   /*---(handle input)-------------------*/
   switch(YX_EVNT.type) {
   case KeyPress:
      key_event  = (XKeyEvent *) &YX_EVNT;
      the_bytes = XLookupString((XKeyEvent *) &YX_EVNT, the_keys, 5, NULL, NULL);
      if (the_bytes < 1) break;
      /*---(handle)----------------*/
      x_ch  = the_keys [0];
      break;
   }
   /*---(special operations)-------------*/
   /*> if (x_ch == KEY_RESIZE || x_ch == -102) {                                      <* 
    *>    DEBUG_LOOP   yLOG_snote   ("resize request");                               <* 
    *>    yviopengl_resize ();                                                        <* 
    *>    DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);                                   <* 
    *>    return 1;                                                                   <* 
    *> }                                                                              <*/
   /*---(save back)----------------------*/
   if (x_ch >= 0 && x_ch <= 255)  x_key = x_ch;
   else                           x_key = 0;
   DEBUG_LOOP   yLOG_sint    (x_key);
   *a_ch = x_key;
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       drawing support                        ----===*/
/*====================------------------------------------====================*/
static void      o___DRAW____________________o (void) {;}

char
yviopengl_cleanse       (void)
{
   /*> if (myVIKEYS.redraw == 'y')  clear  ();                                        <*/
   yviopengl_resize ();
   /*> if (myVIKEYS.font_scale <= 0.20) {                                             <* 
    *>    myVIKEYS.font_scale = yFONT_width (myVIKEYS.font, myVIKEYS.point);          <* 
    *>    DEBUG_GRAF   yLOG_double  ("font_scale", myVIKEYS.font_scale);              <* 
    *> }                                                                              <*/
   /*> yVIEW_color_set  (YVIEW_MAIN, 1.0);                                            <*/
   /*> yCOLOR_set_clear (YCOLOR_BAS + YCOLOR_ACC);                                    <*/
   /*> glClearColor    (1.0f, 1.0f, 1.0f, 1.0f);                                   <*/
   yVIEW_color_clear (YVIEW_MAIN);
   /*> glClearColor    (0.0f, 0.0f, 0.0f, 1.0f);                                      <*/
   glClear     (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   return 0;
}

char
yviopengl_prep          (char a_part)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_on        =  '-';
   char        x_type      =  '-';
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
   /*> yVIEW_opengl (a_part, x_name, &x_on, NULL, x_text, &x_type, &x_anchor, NULL, &x_min, &x_max, &x_len, &y_min, &y_max, &y_len);   <*/
   DEBUG_GRAF   yLOG_char    ("a_part"    , a_part);
   if (strchr ("MFH", a_part) != NULL) {
      DEBUG_GRAF   yLOG_note    ("floating type (menu, float, history)");
      yVIEW_curses (YVIEW_WINDOW, x_name, NULL, NULL, NULL, NULL, &x_left, &x_wide, &x_bott, &x_tall);
      /*> yVIEW_curses (a_part, x_name, &x_on, NULL, x_text, NULL, &x_min, &x_len, &y_min, &y_len);   <*/
      /*> y_max = y_min + y_len;                                                      <*/
      x_min = x_left;
      x_max = x_min + x_wide;
      y_min = x_bott;
      y_max = y_min + x_tall;
      yVIEW_bounds (a_part, &x_type, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
      x_anchor = YVIEW_BOTLEF;
   } else {
      DEBUG_GRAF   yLOG_note    ("normal type");
      yVIEW_curses (a_part, x_name, &x_on, NULL, x_text, NULL, &x_left, &x_wide, &x_bott, &x_tall);
      yVIEW_bounds (a_part, &x_type, &x_anchor, &x_min, &x_max, &x_len, &y_min, &y_max, &y_len);
   }
   DEBUG_GRAF   yLOG_complex (x_name, "left %4d, wide %4d, bott %4d, tall %4d", x_left, x_wide, x_bott, x_tall);
   DEBUG_GRAF   yLOG_complex (x_name, "%c on %c, %c x_min %4d, x_max %4d, y_min %4d, y_max %4d", a_part, x_on, x_anchor, x_min, x_max, y_min, y_max);
   if (strchr ("MFH", a_part) == NULL && x_on != 'y') {
      DEBUG_GRAF   yLOG_note    ("hidden, not marked for display");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(clear)--------------------------*/
   /*> yVIEW_color_clear (YVIEW_MAIN);                                                <*/
   /*---(setup view)---------------------*/
   DEBUG_GRAF   yLOG_note    ("set up the view");
   glViewport      (x_left, x_bott, x_wide, x_tall);
   glMatrixMode    (GL_PROJECTION);
   DEBUG_GRAF   yLOG_char    ("x_type"    , x_type);
   glLoadIdentity  ();
   if      (x_type  == YVIEW_FLAT)     glOrtho         (x_min, x_max, y_min, y_max, -1000, 1000);
   else if (x_type  == YVIEW_FLATISH)  glOrtho         (x_min, x_max, y_min, y_max, -1000, 1000);
   else                                gluPerspective  (45.0f, (GLfloat) x_len / (GLfloat) y_len, 0.01f, 4000.0f);
   glMatrixMode    (GL_MODELVIEW);
   /*---(background)---------------------*/
   if (x_type  == YVIEW_FLAT) {
      DEBUG_GRAF   yLOG_note    ("draw a background for ortho/flat");
      glPushMatrix    (); {
         /*> glColor4f (1.00, 0.00, 0.00, 1.00);                                      <*/
         yVIEW_color_back (a_part);
         /*> yCOLOR_opengl (YCOLOR_BAS, YCOLOR_ACC, 1.0);                             <*/
         glBegin         (GL_POLYGON); {
            glVertex3f  (x_min, y_max, -1000);
            glVertex3f  (x_max, y_max, -1000);
            glVertex3f  (x_max, y_min, -1000);
            glVertex3f  (x_min, y_min, -1000);
         } glEnd   ();
      } glPopMatrix   ();
   } else {
      DEBUG_GRAF   yLOG_note    ("curses or overlay, no background");
   }
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yviopengl_cursor        (void)
{
   return 0;
}

char
yviopengl_refresh       (void)
{
   /*> mvprintw (0,0,"%3dw,%3dt", myVIOPENGL.wide, myVIOPENGL.tall);                                    <*/
   /*> mvprintw (myVIOPENGL.y_cur, myVIOPENGL.x_cur, "");                             <*/
   /*> refresh ();                                                                    <*/
   glXSwapBuffers (YX_DISP, YX_BASE);
   glFlush();
   return 0;
}

