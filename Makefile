#================================[[ beg-code ]]================================#



#===(manditory)============================================#
# basename of executable, header, and all code files
NAME_BASE  = yVIOPENGL
# additional standard and outside libraries
LIB_STD    = -lX11 -lGL -lGLU -lm -lXext
# all heatherly libraries used, debug versions whenever available
LIB_MINE   = -lyKEYS_debug -lyMODE_debug -lyMACRO_debug -lySRC_debug -lyCMD_debug -lyVIEW_debug -lyFILE_debug -lyMAP_debug -lySTR_debug -lyFONT_debug -lyCOLOR_debug -lyX11_debug -lyMARK_debug
# directory for production code, no trailing slash
INST_DIR   = 



#===(optional)=============================================#
# extra include directories required
INC_MINE   = 
# utilities generated, separate from main program
NAME_UTIL  = 
# libraries only for the utilities
LIB_UTIL   = 



#===(post-processing)======================================#
# create a rule for...
#install_prep       :
#remove_prep        :



#===(master template)======================================#
include /usr/local/sbin/make_program



#===(post-processing)======================================#
# create a rule for...
#install_post       :
#remove_post        :



#================================[[ end-code ]]================================#
