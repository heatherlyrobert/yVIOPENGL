/*============================----beg-of-source---============================*/
#ifndef yVIOPENGL_priv
#define yVIOPENGL_priv yes



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "opengl specific logic"
#define     P_PURPOSE   "remove opengl-specific dependency from vikeys libraries"

#define     P_NAMESAKE  "kalleis-daimona (beauty)"
#define     P_HERITAGE  "wife of hephaestus and youngest of the graces"
#define     P_IMAGERY   ""
#define     P_REASON    "opengl is a colorful, aesthetic, and powerful solution"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "yVIOPENGL"
#define     P_FULLPATH  "/usr/local/lib64/libyVIOPENGL"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2022-12-11"

#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.0-, break out yVIKEYS into curses and opengl"
#define     P_VERNUM    "2.0f"
#define     P_VERTXT    "added note and line masking to the library ;)"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/

/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
#include    <math.h>              /* clibc  standard math library             */
/*---(custom core)-----------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
/*---(custom vikeys)---------------------*/
#include    <yKEYS.h>             /* heatherly vikeys key handling           */
#include    <yMODE.h>             /* heatherly vikeys mode tracking          */
#include    <yMACRO.h>            /* heatherly vikeys macro processing       */
#include    <ySRC.h>              /* heatherly vikeys source editing         */
#include    <yCMD.h>              /* heatherly vikeys command processing     */
#include    <yVIEW.h>             /* heatherly vikeys view management        */
#include    <yFILE.h>             /* heatherly vikeys content file handling  */
#include    <yMARK.h>             /* heatherly vikeys search and marking      */
#include    <yMAP.h>              /* heatherly vikeys location management    */
/*---(custom other)----------------------*/
#include    <yX11.h>              /* heatherly xlib/glx setup/teardown        */
#include    <yFONT.h>             /* heatherly texture mapped fonts           */
#include    <yCOLOR.h>            /* heatherly opengl color handling          */
#include    <yDLST_solo.h>        /* heatherly double-double-list             */
/*---(posix standard)--------------------*/
#include    <GL/gl.h>             /* opengl standard primary header           */
#include    <GL/glx.h>            /* opengl standard X11 integration          */
#include    <X11/extensions/shape.h>   /* xwindows shape extension            */


#define     MAX_PRIMARY    50
typedef  struct cBASIC  tBASIC;
struct cBASIC {
   char        abbr;
   char        terse       [LEN_SHORT];
   char        desc        [LEN_LABEL];
   char        hex         [LEN_TERSE];
   float       red;
   float       grn;
   float       blu;
};
extern tBASIC  g_primary [MAX_PRIMARY];


#define     MAX_COLOR   100
typedef  struct cCOLOR  tCOLOR;
struct cCOLOR {
   char        terse       [LEN_LABEL];     /* short description              */
   char        desc        [LEN_DESC ];     /* description/reason             */
   char        fg;
   char        bg;
};
extern tCOLOR  g_colors [MAX_COLOR];
extern int     g_ncolor;


typedef    struct    cMY    tMY;
struct cMY {
   char        title    [LEN_HUND];
   int         wide;              /* maximum x-coordinate                    */
   int         tall;              /* maximum y-coordinate                    */
   int         x_cur;
   int         y_cur;
   char        p_formula;         /* formula configuration                   */
   int         fixed;                       /* fixed font                     */
   int         pretty;                      /* pretty font                    */
};
extern tMY         myVIOPENGL;



extern char g_print       [LEN_RECD];



/*===[[ yVIOPENGL_base.c ]]===================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        yVIOPENGL_init          (char *a_title, char *a_version, char a_mode, short a_wide, short a_tall);
char        yVIOPENGL_wrap          (void);
char        yVIOPENGL_main          (char *a_delay, char *a_update, void *a_altinput);
/*---(unittest)-------------*/
char        yviopengl__unit_quiet   (void);
char        yviopengl__unit_loud    (void);
char        yviopengl__unit_end     (void);
/*---(done)-----------------*/
char*       yVIOPENGL__unit         (char *a_question, char a_index);



/*===[[ yVIOPENGL_base.c ]]===================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(resize)---------------*/
char        yviopengl_resize        (void);
/*---(input)----------------*/
char        yviopengl_getch         (char a_block, char *a_ch);
/*---(draw)-----------------*/
char        yviopengl_cleanse       (void);
char        yviopengl_prep          (char a_abbr);
char        yviopengl_cursor        (void);
char        yviopengl_refresh       (void);
/*---(done)-----------------*/



/*===[[ yVIOPENGL_base.c ]]===================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(search)---------------*/
char        yviopengl__by_abbr      (char a_abbr);
char        yviopengl__primary      (char a_abbr);
char        yviopengl__by_name      (char *a_terse);
/*---(create)---------------*/
char        yVIOPENGL_color         (char *a_terse, char *a_desc, char a_fg, char a_bg);
/*---(using)----------------*/
char        yVIOPENGL_by_name       (char *a_terse, char a_fg, char a_alpha);
/*> char*       yviopengl__by_pair      (int a_pair);                                 <*/
/*---(program)--------------*/
char        yviopengl_color_init    (void);
char        yviopengl_color_wrap    (void);
/*---(done)-----------------*/



/*===[[ yVIOPENGL_draw.c ]]===================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(text)-----------------*/
char        yviopengl_title         (void);
char        yviopengl_version       (void);
char        yviopengl_modes         (void);
char        yviopengl_status        (void);
char        yviopengl_command       (void);
char        yviopengl_keys          (void);
/*---(fancy)----------------*/
char        yviopengl_univs         (void);
char        yviopengl_menus         (void);
/*---(source)---------------*/
char        yviopengl__display      (char a_part, char a_loc, char a_style);
char        yviopengl_formula       (void);
char        yviopengl_formula_min   (void);
char        yviopengl_formula_small (void);
char        yviopengl_formula_label (void);
char        yviopengl_formula_max   (void);
char        yviopengl_float         (void);
/*---(done)-----------------*/

char        yviopengl_font_load     (void);
char        yviopengl_font_close    (void);


char        yviopengl_notes         (void);

#endif

