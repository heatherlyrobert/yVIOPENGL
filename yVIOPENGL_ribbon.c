/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIOPENGL.h"
#include    "yVIOPENGL_priv.h"


#define   ICON_SET     "/usr/local/share/fonts/outline_icons.png"
#define   MAX_RIBBON   256

struct {
   int         r_icon;
   short       r_rot;
   char       (*r_func) (void);
} static zVIOPENGL_ribbon [MAX_RIBBON];

static int  zVIOPENGL_icons  = -1;
static char zVIOPENGL_color  = -1;
static char zVIOPENGL_hover  = -1;
static char zVIOPENGL_touch  = -1;
static char zVIOPENGL_margin = -1;

static char (*zVIOPENGL_status)  (char *r_valid, short *r_x, short *r_y, char *r_touch) = NULL;


char
yVIOPENGL_ribbon_purge  (void)
{
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   for (i = 0; i < MAX_RIBBON; ++i) {
      zVIOPENGL_ribbon [i].r_icon = -1;
      zVIOPENGL_ribbon [i].r_rot  =  0;
      zVIOPENGL_ribbon [i].r_func = NULL;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIOPENGL_ribbon_config (char *e_status, char a_color, char a_hover, char a_touch, char a_margin)
{
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("a_args"    , "%p, %d, %d, %d, %d", e_status, a_color, a_hover, a_touch, a_margin);
   /*---(load icons)---------------------*/
   zVIOPENGL_icons  = yFONT_iconload ();
   DEBUG_GRAF   yLOG_value   ("icons"     , zVIOPENGL_icons);
   --rce;  if (zVIOPENGL_icons < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set globals)--------------------*/
   zVIOPENGL_color  = a_color;
   zVIOPENGL_hover  = a_hover;
   zVIOPENGL_touch  = a_touch;
   zVIOPENGL_margin = a_margin;
   zVIOPENGL_status = e_status;
   DEBUG_GRAF   yLOG_complex ("saved"     , "%p, %d, %d, %d, %d", zVIOPENGL_status, zVIOPENGL_color, zVIOPENGL_hover, zVIOPENGL_touch, zVIOPENGL_margin);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIOPENGL_ribbon_add    (uchar a_grid, short a_rot, char a_cat [LEN_LABEL], char a_sub [LEN_LABEL], char *e_func)
{
   char        rce         =  -10;
   int         n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("a_args"    , "%02x, %4d, %p, %p, %p", a_grid, a_rot, a_cat, a_sub, e_func);
   /*---(defense)------------------------*/
   --rce;  if (a_cat == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_info    ("a_cat"     , a_cat);
   --rce;  if (a_sub == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_info    ("a_sub"     , a_sub);
   /*---(find icon)----------------------*/
   n = yFONT_icon (a_cat, a_sub, -1, 0);
   DEBUG_GRAF   yLOG_value   ("n"         , n);
   --rce;  if (n < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save data)----------------------*/
   zVIOPENGL_ribbon [a_grid].r_icon = n;
   zVIOPENGL_ribbon [a_grid].r_rot  = a_rot;
   zVIOPENGL_ribbon [a_grid].r_func = e_func;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
YVIOPENGL_ribbon__color (char a_valid, char a_touch, int a_mx, int a_my, int a_grid, char *c)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x           = a_grid / 16;
   int         y           = a_grid % 16;
   int         x_min       = x * 40;
   int         x_max       = x_min + 40;
   int         y_max       = (-y * 40) - 10;
   int         y_min       = y_max - 40;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   *c =  zVIOPENGL_color;
   /*---(quick out)----------------------*/
   if (a_valid != 'y') {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (strchr ("Rr", a_touch) == NULL) {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(test location)------------------*/
   if (a_mx <  x_min || a_mx >= x_max) {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (a_my <  y_min || a_my >= y_max) {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(return color)-------------------*/
   switch (a_touch) {
   case 'r' : *c = zVIOPENGL_hover;  break;
   case 'R' : *c = zVIOPENGL_touch;  break;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yVIOPENGL_ribbon_draw   (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_name      [LEN_LABEL] = "";
   char        x_on        =  '-';
   short       x_left, x_righ, x_wide, x_bott, x_topp, x_tall;
   char        c           =  YF_BRN_TINT;
   short       x_cur, y_cur;
   char        x_valid, x_touch;
   int         x, y;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(get ribbon data)----------------*/
   yVIEW_curses (YVIEW_RIBBON, x_name, &x_on, NULL, NULL, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   x_topp = 0;
   x_righ = x_left + x_wide;
   DEBUG_GRAF   yLOG_complex (x_name      ,"%c  %4dl  %4dr  %4dx    %4db  %4dt  %4dy", x_on, x_left, x_righ, x_wide, x_bott, x_topp, x_tall);
   /*---(quick-out)----------------------*/
   if (x_on != 'y') {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(draw background)----------------*/
   glColor4f   (0.00, 0.00, 0.00, 1.00);
   glBegin     (GL_POLYGON); {
      glVertex3f ( 0     , 0.0    , -500);
      glVertex3f ( x_wide, 0.0    , -500);
      glVertex3f ( x_wide, -x_tall, -500);
      glVertex3f ( 0     , -x_tall, -500);
   } glEnd     ();
   /*---(get current data)---------------*/
   rc = zVIOPENGL_status (&x_valid, &x_cur, &y_cur, &x_touch);
   DEBUG_GRAF   yLOG_complex ("current"   ,"%c  %4dx  %4dy  %c", x_valid, x_cur, y_cur, x_touch);
   /*---(place icons)--------------------*/
   for (i = 0; i < MAX_RIBBON; ++i) {
      if (zVIOPENGL_ribbon [i].r_icon == -1) continue;
      x  = i / 16;
      y  = i % 16;
      DEBUG_GRAF   yLOG_complex ("found"     ,"%3dg  %2dx  %2dy  %4di  %4dr", i, x, y, zVIOPENGL_ribbon [i].r_icon, zVIOPENGL_ribbon [i].r_rot);
      glPushMatrix(); {
         glTranslatef  ((x * 40) + 20, -((y * 40) + zVIOPENGL_margin + 20),  0.0);
         if (zVIOPENGL_ribbon [i].r_rot != 0)  glRotatef  (zVIOPENGL_ribbon [i].r_rot, 0.0f, 0.0f, 1.0f);
         YVIOPENGL_ribbon__color (x_valid, x_touch, x_cur - x_left, y_cur, i, &c);
         yFONT_iconno    (zVIOPENGL_ribbon [i].r_icon, 38.0, c);
      } glPopMatrix();
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIOPENGL_ribbon_act    (char a_valid, char a_touch, int a_wx, int a_wy)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_name      [LEN_LABEL] = "";
   char        x_on        =  '-';
   short       x_left, x_righ, x_wide, x_bott, x_topp, x_tall;
   short       x, y;
   int         x_grid      =    0;
   static char x_touch     =  '·';
   static char x_button    =  '·';
   int         x_min       = x * 40;
   int         x_max       = x_min + 40;
   int         y_max       = (-y * 40) - 10;
   int         y_min       = y_max - 40;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("a_args"    ,"%c  %c  %4dx  %4dy", a_valid, a_touch, a_wx, a_wy);
   /*---(quick out)----------------------*/
   if (a_valid != 'y') {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (strchr ("Rr", a_touch) == NULL) {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(get ribbon data)----------------*/
   yVIEW_curses (YVIEW_RIBBON, x_name, &x_on, NULL, NULL, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   x_topp = 0;
   x_righ = x_left + x_wide;
   DEBUG_GRAF   yLOG_complex (x_name      ,"%c  %4dl  %4dr  %4dx    %4db  %4dt  %4dy", x_on, x_left, x_righ, x_wide, x_bott, x_topp, x_tall);
   /*---(quick-out)----------------------*/
   if (x_on != 'y') {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(out-of-range)-------------------*/
   if (a_wx < x_left && a_wx > x_righ) {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*> if (a_wy < x_topp && a_wy > x_bott) {                                          <* 
    *>    DEBUG_GRAF   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   /*---(get grid)-----------------------*/
   x       = ((a_wx - x_left) / 40) * 16;
   y       = (-a_wy - zVIOPENGL_margin) / 40;
   x_grid  = x + y;
   DEBUG_DATA   yLOG_complex ("button"    , "%02x %02x %02x", x, y, x_grid);
   DEBUG_DATA   yLOG_complex ("touching"  , "%c %c %02x", x_touch, a_touch, x_button);
   if (x_touch != 'R' || a_touch != 'r') {
      DEBUG_GRAF   yLOG_note    ("not just released");
      x_touch  = a_touch;
      x_button = x_grid;
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(quick-out)----------------------*/
   if (x_grid < 0 || x_grid >= MAX_RIBBON) {
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(place icons)--------------------*/
   DEBUG_DATA   yLOG_note    ("touch released");
   DEBUG_DATA   yLOG_point   ("r_func"    , zVIOPENGL_ribbon [x_grid].r_func);
   if (zVIOPENGL_ribbon [x_grid].r_func != NULL) {
      rc = zVIOPENGL_ribbon [x_grid].r_func ();
   }
   /*---(save local)---------------------*/
   x_touch  = a_touch;
   x_button = x_grid;
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 1;
}


