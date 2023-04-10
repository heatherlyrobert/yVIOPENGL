/*============================----beg-of-source---============================*/
#ifndef yVIOPENGL
#define yVIOPENGL yes



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



#endif
/*============================----end-of-source---============================*/
