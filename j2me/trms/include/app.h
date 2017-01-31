#ifnotdef __APP_H__
#define   __APP_H__

#defineblock begin
/*----------------------------------------------------------------------------*\

                            Trol Mobile Studio v 1.0
                          Runtime libraries:  APP.H

                      Copyright (c) O.A. Trifonov, 2006
                                 Version 1.0
                                 
                                 
   Определяет скелеты различных типов приложений.
   
   Поддерживаемые типы приложений:
       J2ME (midlet)
       J2SE (applet, application)
       BLACKBERRY (cod, jar)
       WIN32
       
   Определяет макрофункции:
       _APP_HEADER_(appname, mainclass)
       _APP_BODY_(appname, mainclass)
       
   Требует и использует макрофункции-обработчики:
       onCreate()
       onStart()
       onDestroy()
       onPause()
       onKeyPressed(keyCode)
       onKeyReleased(keyCode)
       onCommand(command, display)
       onPaint(graphic)
       onRun()
       
    опциональные обработчики:
      bool onTrackweelRoll(mount)
      bool onTrackweelClick()
      bool onTrackweelUnclick()

   



\*----------------------------------------------------------------------------*/

  #include "stddef.h"

  #ifdef BLACKBERRY
    #include "blackberry\app.h"
  #elseif J2ME
    #include "j2me\app.h"
  #elseif J2SE
    #ifdef APPLET
      #include "j2se\applet.h"
    #else
      #include "j2se\app.h"
    #endif
  #elseif WIN32
    #include "win32\app.h"
  #else
    #error "unknown target platform"
  #endif
  
#defineblock end
#endif

