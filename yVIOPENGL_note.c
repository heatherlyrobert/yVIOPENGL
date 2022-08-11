/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIOPENGL.h"
#include    "yVIOPENGL_priv.h"



char
yviopengl_notes_shadow  (short x, short y, uchar w, uchar h, uchar *t)
{
   int         x_align     =    0;
   int         x_full, x_len;
   int         x_beg, x_next, x_cr;
   int         i, j;
   char       *p           = NULL;
   int         z           = -152;
   float       xx, yy, ww, hh;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex  ("opengl"    , "%4dx, %4dy, %4dw, %4dh", x, y, w, h);
   /*---(background)---------------------*/
   /*> xx = x / 4.5;                                                                  <* 
    *> yy = y / 4.5;                                                                  <* 
    *> ww = w / 4.5;                                                                  <* 
    *> hh = h / 4.5;                                                                  <*/
   glColor4f (0.0f, 0.0f, 0.0f, 1.0f);
   glBegin(GL_POLYGON); {
      glVertex3f (x    , y    , z);
      glVertex3f (x + w, y    , z);
      glVertex3f (x + w, y - h, z);
      glVertex3f (x    , y - h, z);
   } glEnd();
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yviopengl_notes_draw    (cchar s, short x, short y, uchar w, uchar h, uchar *t)
{
   int         x_align     =    0;
   int         x_full, x_len;
   int         x_beg, x_next, x_cr;
   int         i, j;
   char       *p           = NULL;
   int         z           = -150;
   float       xx, yy, ww, hh;
   /*---(locals)-----------+-----+-----+-*/
   float       x_edge, y_edge;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex  ("opengl"    , "%4dx, %4dy, %4dw, %4dh", x, y, w, h);
   /*---(background)---------------------*/
   /*> xx = x / 4.5;                                                                  <* 
    *> yy = y / 4.5;                                                                  <* 
    *> ww = w / 4.5;                                                                  <* 
    *> hh = h / 4.5;                                                                  <* 
    *> x_edge = 0.70;                                                                 <* 
    *> y_edge = 0.70;                                                                 <*/
   x_edge = 3;
   y_edge = 3;
   glBegin(GL_POLYGON); {
      glVertex3f (x     + x_edge, y     - y_edge, z);
      glVertex3f (x + w - x_edge, y     - y_edge, z);
      glVertex3f (x + w - x_edge, y - h + y_edge, z);
      glVertex3f (x     + x_edge, y - h + y_edge, z);
   } glEnd();
   /*---(text)---------------------------*/
   DEBUG_GRAF   yLOG_info     ("t"         , t);
   z +=  2.0;
   x_edge =  6.0;
   glPushMatrix(); {
      glTranslatef (x + w * 0.5, y - (y_edge * 4.5), z);
      switch (s) {
      case ')' :  case '!' :  glColor4f (1.0, 1.0, 1.0, 1.0);  break;
      default  :              glColor4f (0.0, 0.0, 0.0, 1.0);  break;
      }
      if (s == '.')  yFONT_printw (myVIOPENGL.fixed, 8, YF_TOPCEN, t, w               , h - y_edge * 2.0, 1.2);
      else           yFONT_printw (myVIOPENGL.fixed, 8, YF_TOPCEN, t, w - x_edge * 5.0, h - y_edge * 2.0, 1.2);
   } glPopMatrix();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yviopengl_notes_line    (char c, short xb, short yb, short xe, short ye)
{
   int         i           =    0;
   char        x_side      =    3;
   int         z           = -148;
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*> mvprintw (10, 10, "ˆ");                                                        <*/
   DEBUG_GRAF   yLOG_complex ("args"       , "%c  %4dx %4dy  %4dx %4dy", c, xb, yb, xe, ye);
   /*---(origin)-------------------------*/
   glColor4f (0.0, 0.0, 0.0, 1.0);
   glBegin(GL_POLYGON); {
      glVertex3f (xb + x_side, yb - x_side, z);
      glVertex3f (xb - x_side, yb - x_side, z);
      glVertex3f (xb - x_side, yb + x_side, z);
      glVertex3f (xb + x_side, yb + x_side, z);
   } glEnd();
   /*> mvprintw (yb, xb, "³");                                                        <*/
   /*---(first leg)----------------------*/
   switch (c) {
   case 'Ô' : case '1' : case '8' :
   case 'Õ' : case '4' : case '5' :
      DEBUG_GRAF   yLOG_note    ("vertical first (8,1,4,5)");
      glBegin(GL_LINES); {
         glVertex3f (xb         , yb         , z);
         glVertex3f (xb         , ye         , z);
      } glEnd();
      break;
   case '×' : case '6' : case '7' :
   case 'Ö' : case '2' : case '3' :
      DEBUG_GRAF   yLOG_note    ("horizontal first (2,3,6,7)");
      glBegin(GL_LINES); {
         glVertex3f (xb         , yb         , z);
         glVertex3f (xe         , yb         , z);
      } glEnd();
      break;
   default  :
      break;
   }
   /*---(second leg)---------------------*/
   switch (c) {
   case '1' : case '4' :
   case '5' : case '8' :
      DEBUG_GRAF   yLOG_note    ("horizontal second (8,1,4,5)");
      glBegin(GL_LINES); {
         glVertex3f (xb         , ye         , z);
         glVertex3f (xe         , ye         , z);
      } glEnd();
      break;
   case '2' : case '7' :
   case '3' : case '6' :
      DEBUG_GRAF   yLOG_note    ("vertical second (2,3,6,7)");
      glBegin(GL_LINES); {
         glVertex3f (xe         , yb         , z);
         glVertex3f (xe         , ye         , z);
      } glEnd();
      break;
   }
   /*---(final point)--------------------*/
   /*> mvprintw (ye, xe    , "Ï");                                                    <*/
   glColor4f (0.0, 0.0, 0.0, 1.0);
   glBegin(GL_POLYGON); {
      glVertex3f (xe + x_side, ye - x_side, z);
      glVertex3f (xe - x_side, ye - x_side, z);
      glVertex3f (xe - x_side, ye + x_side, z);
      glVertex3f (xe + x_side, ye + x_side, z);
   } glEnd();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



char
yviopengl_notes         (void)
{
   char        rc          =    0;
   int         i           =    0;
   short       x, y;
   uchar       m, s, w, h;
   uchar       t           [LEN_HUND]  = "";
   uchar       c;
   short       xb, yb, xe, ye;
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   if (yVIEW_note_showing () == 0) {
      DEBUG_GRAF   yLOG_note    ("note showing mode is OFF");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_GRAF   yLOG_note    ("note showing mode is ON");
   for (i = 0; i < 20; ++i) {
      rc = yVIEW_note_data (i, &m, &s, &x, &y, &w, &h, t, &c, &xb, &yb, &xe, &ye);
      if (rc < 0)  break;
      DEBUG_GRAF   yLOG_complex  ("note"      , "%2di, %2dm, %4dx, %4dw, %4dy, %4dh, %c, %s", i, m, x, w, y, h, s, t);
      yviopengl_notes_shadow (x, y, w, h, t);
      if (s == ')') {
         DEBUG_GRAF   yLOG_note    ("title type");
         yVIOPENGL_by_name ("n_main", '-', 1.0);
      } else if (s == '!') {
         DEBUG_GRAF   yLOG_note    ("warning type");
         yVIOPENGL_by_name ("n_warn", '-', 1.0);
      } else if (i == m) {
         DEBUG_GRAF   yLOG_note    ("current type");
         yVIOPENGL_by_name ("n_curr", '-', 1.0);
      } else {
         DEBUG_GRAF   yLOG_note    ("previous type");
         yVIOPENGL_by_name ("n_prev", '-', 1.0);
      }
      yviopengl_notes_draw (s, x, y, w, h, t);
      yVIOPENGL_by_name ("n_line", '-', 1.0);
      yviopengl_notes_line (c, xb, yb, xe, ye);
   }
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}
