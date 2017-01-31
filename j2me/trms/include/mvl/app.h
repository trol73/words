#ifnotdef __MVL_APP_H__
#define   __MVL_APP_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries
                            
                           Application skeleton unit
                            

                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.01
                                 
\*----------------------------------------------------------------------------*/


  #ifdef BLACKBERRY
//    #include "mvl/blackberry/app.h"
  #elseif J2ME
    #include "mvl/j2me/app.h"
  #elseif J2SE
    #ifdef APPLET
//      #include "mvl/j2se/applet.h"
    #else
//      #include "mvl/j2se/app.h"
    #endif
  #elseif WIN32
//    #include "mvl/win32/app.h"
  #elseif LINUX
//    #include "mvl/linux/app.h"
  #else
    #error "unknown target platform"
  #endif
  
  
#defineblock end
#endif

