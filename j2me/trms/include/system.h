#ifnotdef __SYSTEM_H__
#define   __SYSTEM_H__
#defineblock begin
//----------------------------------------------------------------------------//
//                       Tr Java Mobile Builder v 1.5                         //
//                        Runtime libraries:  SYSTEM.H                        //
//                  Copyright (c) O.A. Trifonov, 2004 - 2006                  //
//                                Version 1.15                                //
//                                                                            //
//  Defines:                                                                  //
//  Macroses:                                                                 //
//                                                                            //
//                                                                            //
//                                                                            //
//  Supported devices (total 12 types):                                       //
//                                                                            //
//    Motorola      V300/V400/V500, T720, C650                                //
//                                                                            //
//    SonyEricsson  T610, K700                                                //
//                                                                            //
//    Nokia         Series 40, Series 60                                      //
//                                                                            //
//    Samsung       E700, X600                                                //
//                                                                            //
//    Siemens       55                                                        //
//                                                                            //
//    Siemens       65                                                        //
//                                                                            //
//    Abstract MIDP 1.0 device                                                //
//                                                                            //
//    Abstract MIDP 2.0 device                                                //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//                 библиотека использует следующие идентификаторы
//----------------------------------------------------------------------------//
// УСТРОЙСТВА

  DEVICE_MIDP_1        // стандартный телефон MIDP 1.0
  DEVICE_MIDP_2        // стандартный телефон MIDP 2.0

  MOTOROLA_V300        // - телефоны Motorola V300/V400/V500
  MOTOROLA_T720        // - телефон Motorola  T720
  SONYERICSSON_T610    // - телефон SonyEricsson T610
  SONYERICSSON_K700    // - телефон SonyEricsson K700
  NOKIA_SERIES_40      // - стандартные телефоны Nokia series 40
  NOKIA_SERIES_60      // - стандартные телефоны Nokia series 60
  SAMSUNG_E700         // - Samsung E700
  SAMSUNG_X600         // - Samsung X600
  SIEMENS_55           // - Siemens S(C, M)55
  SIEMENS_65           // - 65-е Siemens
  

// ОБЩИЕ ОПРЕДЕЛЕНИЯ
  MIDP_1               // - версия MIDP 1.0
  MIDP_2               // - версия MIDP 2.0
  MIDP_BOTH            // - серия устройств, в которой есть телефоны обоих версий MIDP

  NOKIA                // - компановка проекта для телефонов, поддерживающих Nokia API
  SIEMENS              // - компановка проекта для телефонов, поддерживающих Siemens API
  
  SCREEN_BUFFERING     // - прорисовка экрана осуществляется с помощью буффера

  SCREEN_CUSTOM_REPAINT  // если этот макрос определен, то при вызове процедуры прорисовки
                         // будет вручную с полной достоверностью контролироваться факт
                         // выполнения прорисовки
  

  DEBUG                // - отладочная версия

// ПЕРЕМЕННЫЕ И КЛАССЫ
  mainFrame            // экземпляр главного класса прорисовки и потока
  display              // ссылка на класс дисплея
  instance             // ссылка на экземпляр главного класса мидлета

//----------------------------------------------------------------------------//
//                   макроопределения системных типов                         //
//----------------------------------------------------------------------------//
#define     bool                  boolean
#define     stdcall               public static final
//----------------------------------------------------------------------------//
//                           макрофункции языка                               //
//----------------------------------------------------------------------------//
// Эта макрофункция возвращает полученный аргумент
// Ее можно использовать в других макрофункциях для обращению к полю или методу
// объекту-аргументу
// #macro strlen(aStr)
//   __void__macro__(aStr).length()
// #endmacro
#macro __void__macro__(param)
param
#endmacro
//------------------------------------------------------------------------------
//                      определяем версию MIDP                                //
//------------------------------------------------------------------------------
#ifdef    MOTOROLA_V300
  #define   MIDP_2
#elseif   MOTOROLA_T720
  #define   MIDP_1
#elseif   SONYERICSSON_T610
  #define   MIDP_1
#elseif   SONYERICSSON_K700
  #define   MIDP_2
#elseif   NOKIA_SERIES_40
  #define   MIDP_BOTH
  #define   NOKIA
  #define   JSR_120
#elseif   NOKIA_SERIES_60
  #define   MIDP_BOTH
  #define   NOKIA
#elseif   SAMSUNG_E700
  #define   MIDP_1
  #define   SAMSUNG
#elseif   SAMSUNG_X600
  #define   MIDP_1
  #define   SAMSUNG
#elseif   SIEMENS_55
  #define   MIDP_1
  #define SIEMENS
#elseif SIEMENS_65
  #define   MIDP_2
  #define   JSR_120
  #define   SIEMENS
#elseif    MOTOROLA_C650
  #define   MIDP_2
  #define   JSR_120
#elseif  ABSTRACT_MIDP1
  #define   MIDP_1
#elseif  ABSTRACT_MIDP2
  #define   MIDP_2
#endif
//------------------------------------------------------------------------------
//                     системные макрофункции                                 //
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
//   void quit()
// завершает выполнение мидлета
#macro quit()
instance.destroyApp(true);
instance.notifyDestroyed();
instance = null
#endmacro
//------------------------------------------------------------------------------
//   void setFullScreen(bool full)
// переводит устройство в полноэкранный режим, если этот режим доступен и
// full = true
#macro setFullScreen(full)
#ifdef NOKIA
#elseif MIDP_2
mainFrame.setFullScreenMode(full);
#endif
#endmacro
// переводит устройство в полноэкранный режим, если этот режим доступен
#macro setFullScreen()
#ifdef NOKIA
#elseif MIDP_2
mainFrame.setFullScreenMode(true);
#endif
#ifdef SAMSUNG_E700
  #define SCREEN_BUFFERING
#elseif SAMSUNG_X600
  #define SCREEN_BUFFERING
#endif
#define SCREEN_HEIGHT SCREEN_FULL_HEIGHT
#endmacro
//------------------------------------------------------------------------------
//   void repaint(int x, int y, int w, int h)
// выполнить прорисовку экрана в заданной области
#macro repaint(x, y, w, h)
#ifdef DEBUG
if (x < 0) System.out.println("repaint() ->  x < 0");
if (y < 0) System.out.println("repaint() ->  y < 0");
if (x+w > SCREEN_WIDTH) System.out.println("repaint() ->  x+w > SCREEN_WIDTH");
if (y+h > SCREEN_HEIGHT) System.out.println("repaint() ->  y+h > SCREEN_HEIGHT");
#endif
#ifnotdef SCREEN_CUSTOM_REPAINT
  #ifdef GAME_FRAME_DEFINED
this.repaint(x, y, w, h);
serviceRepaints();
  #else
mainFrame.repaint(x, y, w, h);
mainFrame.serviceRepaints();
  #endif // GAME_FRAME_DEFINED
#else // SCREEN_CUSTOM_REPAINT
  #ifdef GAME_FRAME_DEFINED
painted = false;
while (!painted) {
  this.repaint(x, y, w, h);
  serviceRepaints();
}
  #else // GAME_FRAME_DEFINED
painted = false;
while (!painted) {
  mainFrame.repaint(x, y, w, h);
  mainFrame.serviceRepaints();
}
  #endif // GAME_FRAME_DEFINED
  
#endif // SCREEN_CUSTOM_REPAINT

#endmacro




//   void repaint()
// выполнить прорисовку всего экрана
#ifnotdef MOTOROLA_T720
// для не-T720
#macro repaint()
#ifnotdef SCREEN_CUSTOM_REPAINT
  #ifdef GAME_FRAME_DEFINED
this.repaint();
this.serviceRepaints();
  #else // GAME_FRAME_DEFINED
mainFrame.repaint();
mainFrame.serviceRepaints();
  #endif // GAME_FRAME_DEFINED
#else // SCREEN_CUSTOM_REPAINT
  #ifdef GAME_FRAME_DEFINED
painted = false;
while (!painted) {
  this.repaint();
  serviceRepaints();
}
  #else // GAME_FRAME_DEFINED
painted = false;
while (!painted) {
  mainFrame.repaint();
  mainFrame.serviceRepaints();
}
  #endif // GAME_FRAME_DEFINED
  
#endif // SCREEN_CUSTOM_REPAINT

#endmacro


#else
// T720
#macro repaint()
#ifnotdef SCREEN_CUSTOM_REPAINT
  #ifdef GAME_FRAME_DEFINED
this.repaint(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
serviceRepaints();
  #else
mainFrame.repaint(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
mainFrame.serviceRepaints();
  #endif
#else
  #ifdef GAME_FRAME_DEFINED
painted = false;
while (!painted) {
  this.repaint(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  serviceRepaints();
}
  #else
painted = false;
while (!painted) {
  mainFrame.repaint(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  mainFrame.serviceRepaints();
}

  #endif
  
#endif

#endmacro

#endif

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
#ifnotdef DEBUG
(System.getProperty("microedition.platform"))
#elseifnot NOKIA_SERIES_60  // на эмуляторах Nokia Series 60 функция возвращает null (!)
(System.getProperty("microedition.platform"))
#else                       // для отладки телефонов Nokia Series 60 выдадим типовую строку
(String("Nokia6600/03.14"))
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
//   int strToInt(String str)
// преобразует строку в целое число
#macro strToInt(str)
Integer.valueOf(str).intValue()
#endmacro
//------------------------------------------------------------------------------
//  bool call(String phone)
//  bool browseWap(String url)
//  bool browseWap(String url, String params)
#ifnotdef MIDP_2

  #macro call(phone)
    false
  #endmacro

  #macro browseWap(url)
    false
  #endmacro
  
#else

  #macro browseWap(url, params)
    browseWap(url+'?'+params)
  #endmacro
  
#endif






#defineblock end
#endif
