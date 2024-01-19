/*============================----beg-of-source---============================*/
#ifndef yVIOPENGL
#define yVIOPENGL yes

#include <ySTR_solo.h>


typedef  unsigned char        uchar;



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char*       yVIOPENGL_version       (void);
char        yVIOPENGL_init          (char *a_title, char *a_version, char a_mode, short a_wide, short a_tall);
char        yVIOPENGL_dawn          (void);
char        yVIOPENGL_resize        (char *a_title, short a_wide, short a_tall);
char        yVIOPENGL_dusk          (void);
char        yVIOPENGL_wrap          (void);
char*       yVIOPENGL__unit         (char *a_question, char a_index);


char        yVIOPENGL_main          (char *a_delay, char *a_update, void *a_altinput);

char        yVIOPENGL_color         (char *a_terse, char *a_desc, char a_fg, char a_bg);
char        yVIOPENGL_by_name       (char *a_terse, char a_fg, char a_alpha);
char*       yVIOPENGL_at_loc        (short x, short y);

char        yVIOPENGL_notes_mask    (void *gc, void *bounds);

char        yVIOPENGL_ribbon_purge  (void);
char        yVIOPENGL_ribbon_config (char *e_status, char a_color, char a_hover, char a_touch, char a_margin);
char        yVIOPENGL_ribbon_add    (uchar a_grid, short a_rot, char a_cat [LEN_LABEL], char a_sub [LEN_LABEL], char *e_func);
char        yVIOPENGL_ribbon_draw   (void);
char        yVIOPENGL_ribbon_act    (char a_valid, char a_touch, int a_wx, int a_wy);


#endif
/*============================----end-of-source---============================*/
