/*----------------------------------------------------------------------------*\

                            Trol Mobile Studio v 1.0
                          Runtime libraries:  RTL\JAVA\SYSTEM.H

                     Copyright (c) O.A. Trifonov, 2004-2006
                                 Version 1.0


   Определяет базовые функции Java-приложений.


   Определяет макросы:
     bool
     stdcall

   Определяет макрофункции:
     void_macro(param)
     
   Системные функции:
     void sleep(long ms)
     void wait()
     void quit()
     void setFullScreen(bool full=true)
     void repaint()
     long time()
     long time(long start)
     long freeMem()
     void gc()
\*----------------------------------------------------------------------------*/



//------------------------------------------------------------------------------
//                     системные макрофункции                                 //
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//   void sleep(long ms)
// приостанавливает выполнение текущего потока на ms миллисекунд, передавая
// это процессорное время другим потокам
#macro sleep(ms)
  #ifnotdef DEBUG
try { Thread.sleep(ms); } catch (InterruptedException e) { }
  #else
try { Thread.sleep(ms); } catch (InterruptedException e) { System.out.println(">> FATAL ERROR >> sleep() -> InterruptedException"); }
  #endif
#endmacro

//------------------------------------------------------------------------------
//   void wait()
// приостанавливает выполнение текущего потока, передавая процессорное
// время другим потокам
#macro wait()
  #ifnotdef DEBUG
try { this.wait(); } catch (InterruptedException e) { }
  #else
try { this.wait(); } catch (InterruptedException e) { System.out.println(">> FATAL ERROR >> wait() -> InterruptedException"); }
  #endif
#endmacro

//------------------------------------------------------------------------------
//   void quit()
// завершает выполнение приложения
#macro quit()
  #ifdef J2ME
instance.destroyApp(true);
instance.notifyDestroyed();
instance = null;
  #else
  #endif
#endmacro

//------------------------------------------------------------------------------
//   void setFullScreen(bool full)
// переводит устройство в полноэкранный режим, если этот режим доступен и full = true
#macro setFullScreen(full)
 #ifdef MIDP_2
   #ifnotdef NOKIA
mainFrame.setFullScreenMode(full);
   #endif // NOKIA
 #endif // MIDP_2
#endmacro

// переводит устройство в полноэкранный режим, если этот режим доступен
#macro setFullScreen()
 #ifdef MIDP_2
   #ifnotdef NOKIA
mainFrame.setFullScreenMode(true);
   #endif // NOKIA
 #endif // MIDP_2
#endmacro

//------------------------------------------------------------------------------
//   void repaint()
// выполнить прорисовку всего экрана
#ifdef J2ME
 #ifnotdef BLACKBERRY
#macro repaint()
    #ifdef GAME_FRAME_DEFINED
{this.repaint();  this.serviceRepaints();}
    #else // GAME_FRAME_DEFINED
{mainFrame.repaint();mainFrame.serviceRepaints();}
    #endif // GAME_FRAME_DEFINED
#endmacro
  #endif // BLACKBERRY
#endif // J2ME

//------------------------------------------------------------------------------
//   long time()
// возвращает количество времени в миллисекундах, прошедших с 1 января 1970 года
// до текушего момента
#macro time()
(System.currentTimeMillis())
#endmacro

//   long time(long start)
// возвращает количество времени в миллисекундах, прошедших с момента start
#macro time(start)
(System.currentTimeMillis() - start)
#endmacro

//------------------------------------------------------------------------------
//   long freeMem()
// возвращает количество свободной памяти в байтах
#macro freeMem()
(Runtime.getRuntime().freeMemory())
#endmacro

//------------------------------------------------------------------------------
//   void gc()
// вызывает сборщик мусора
#macro gc()
System.gc()
#endmacro

//------------------------------------------------------------------------------
//   String platform()
// возвращает строку с названием модели устройства
#macro platform()
  #ifdef J2ME
( (System.getProperty("microedition.platform") != null) ? System.getProperty("microedition.platform") : "j2me" )
  #elseif J2SE
    #ifdef APPLET
"j2se applet"
     #else
"j2se"
     #endif // APPLET
  #else
"unknown"
  #endif
#endmacro


