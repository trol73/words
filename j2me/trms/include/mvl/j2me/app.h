/*----------------------------------------------------------------------------*\

                            Trol Mobile Studio v 1.0
                            Moblie Visual Libraries
                            
                                  J2ME platform
                           Application skeleton unit

                      Copyright (c) O.A. Trifonov, 2007-2008
                                 Version 1.05


\*----------------------------------------------------------------------------*/
#macro  _MVL_APP_HEADER_(_appname_, _mainclass_)
#define _MVL_MAINCLASS_ _mainclass_
package _appname_;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.game.*;
import javax.microedition.rms.*;
import javax.microedition.io.*;
import java.io.*;
import java.util.*;


#ifdef NOKIA
import com.nokia.mid.ui.FullCanvas;
#endif

#ifdef IMPORT_JSR_135
import javax.microedition.media.*;
import javax.microedition.media.control.*;
import javax.microedition.media.protocol.*;
#endif

#ifdef IMPORT_JSR_75
import javax.microedition.io.file.*;
#endif


#include "mvl/j2me/fonts.h"

// ****************************************************************************
// ********************  ГЛАВНЫЙ КЛАСС ПРИЛОЖЕНИЯ  ****************************
// ****************************************************************************
public class _mainclass_ extends MIDlet {
// Системные объекты
  public static _mainclass_  _mvl_instance;                  // ссылка на себя
  public static MainFrame    _mvl_mainFrame;                 // основная канва
  public static Display      _mvl_display;                   // класс экрана
  public static int          _mvl_screen;                    // текущий экран
  public static boolean      _mvl_keyboardDisabled = false;  // флаг блокировки клавиатуры
#ifdef ENABLE_CUSTOM_KEY_REPEATED
  public static boolean      _mvl_customKeyRepeated = false; // флаг того, что событие удержания клавиши будет генерироваться вручную
  public static int          _mvl_keyPressedCodes[];         // коды клавиш, которые в данный момент нажаты
  public static long         _mvl_keyPressedTimes[];         // времена последнего вызыва обработчика
  public static int          _mvl_keyPressedCount;           // число событий о нажатых клавишах
  public static final int    _mvl_keyPressedMax = 10;        // максимальный размер массивов
#endif // ENABLE_CUSTOM_KEY_REPEATED
#ifdef ENABLE_CUSTOM_FONTS
  public static TFont        _mvl_currentFont;               // текущий шрифт для рисования текста
#endif
#ifdef ENABLE_BACKBUFFER
  public static Image        _mvl_screenBackBufferImage;     // заэкранный буффер
  public static Graphics     _mvl_screenBackBufferGraphics;
  public static boolean      _mvl_drawToBackBuffer = false;  // флаг того, что рисование производить в заэкранный буффер
  public static boolean      _mvl_drawFromBackBuffer = false;// флаг того, что рисование производить из заэкранного буффер
#endif
#ifdef ENABLE_POPUP_WINDOW
  public static Vector       _mvl_windows = new Vector();    // стек, в который помещаются созданные окна
#endif
#ifdef ENABLE_SOFTKEYCODES_JAD
  public static int _mvl_keyCode_soft1_;                  // коды софт-клавиш, задаваемые явно в jad-манифесте
  public static int _mvl_keyCode_soft2_;
  public static int _mvl_keyCode_soft3_;
#endif


#endmacro







#macro _MVL_APP_BODY_(_appname_, _mainclass_)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Методы мидлета
// ----------------------------------------------------------------------------

#include "mvl/j2me/images.h"


// Конструктор
  public _mainclass_() {
    _mvl_instance = this;
    _mvl_display = Display.getDisplay(this);
    _mvl_mainFrame = new MainFrame();
#ifnotdef NOKIA
    _mvl_mainFrame.setFullScreenMode(true);
#endif
#ifdef ENABLE_CUSTOM_KEY_REPEATED
    if ( !_mvl_mainFrame.hasRepeatEvents() )
      enableCustomKeyRepeatedEvents();
    _mvl_keyPressedCodes = new int[_mvl_keyPressedMax];
    _mvl_keyPressedTimes = new long[_mvl_keyPressedMax];
#endif // ENABLE_CUSTOM_KEY_REPEATED
#ifdef ENABLE_BACKBUFFER
  _mvl_screenBackBufferImage = Image.createImage(_mvl_mainFrame.getWidth(), _mvl_mainFrame.getHeight());
  _mvl_screenBackBufferGraphics = _mvl_screenBackBufferImage.getGraphics();
#endif // ENABLE_BACKBUFFER
#ifdef ENABLE_SOFTKEYCODES_JAD
  _mvl_keyCode_soft1_ = _mvl_getAppPropertyInt("key1");
  _mvl_keyCode_soft2_ = _mvl_getAppPropertyInt("key2");
  _mvl_keyCode_soft3_ = _mvl_getAppPropertyInt("key3");
#endif
    onCreate();
  }

#ifdef ENABLE_SOFTKEYCODES_JAD
  public final int _mvl_getAppPropertyInt(String key) {
    try {
      String s = getAppProperty(key);
      if ( s == null || s == "" )
        return 0;
      return Integer.parseInt(s);
    } catch ( Exception ex ) {
      return 0;
    }
  }
#endif




// Запуск мидлета
  public void startApp() {
#ifnotdef NOKIA
    _mvl_mainFrame.setFullScreenMode(true);
#endif
    _mvl_mainFrame.start();
    _mvl_display.setCurrent(_mvl_mainFrame);
    try {
      Thread.sleep(50);
    } catch (Exception ex) { };
    onInit();
  }



// Пауза мидлета
  public void pauseApp() {
    onPause();
  }



// Уничтожение мидлета
  public void destroyApp(boolean unconditional) {
    _mvl_mainFrame._mvl_running = false;
    onDestroy();
  }
  
  

  public static final int getScreenWidth() {
    return _mvl_mainFrame.getWidth();
  }
  
  
  
  public static final int getScreenHeight() {
    return _mvl_mainFrame.getHeight();
  }
  
  
  
	public static final void enableCustomKeyRepeatedEvents() {
#ifdef ENABLE_CUSTOM_KEY_REPEATED
	  if ( _mvl_customKeyRepeated )
      return;
    _mvl_customKeyRepeated = true;
#endif // ENABLE_CUSTOM_KEY_REPEATED
	}
//*****************************************************************************
//******************************  КЛАСС ЭКРАНА ********************************
//*****************************************************************************
  #ifdef NOKIA
  public class MainFrame extends FullCanvas implements Runnable, CommandListener {
  #else
  public class MainFrame extends Canvas implements Runnable, CommandListener {
  #endif

    public boolean _mvl_running;           // флаг того, что поток класса запущен
    #ifdef SCREEN_CUSTOM_REPAINT
    public boolean _mvl_painted = true;     // флаг того, что запрос на отрисовку экрана был выполнен
    #endif


//-----------------------------------------------------------------------------

    // Конструктор класса экрана
    public MainFrame() {
      _mvl_running = false;
     }



    // Запускает главный поток приложения
    public final void start() {
      _mvl_running = true;
      Thread t = new Thread(this);
      t.start();
    }



    public final int _mvl_getKeyActionCode(int keyCode) {
#ifdef ENABLE_SOFTKEYCODES_JAD
      if ( _mvl_keyCode_soft1_ != 0 && keyCode == _mvl_keyCode_soft1_ )
        return ACT_SOFT1;
      if ( _mvl_keyCode_soft2_ != 0 && keyCode == _mvl_keyCode_soft2_ )
        return ACT_SOFT2;
      if ( _mvl_keyCode_soft3_ != 0 && keyCode == _mvl_keyCode_soft3_ )
        return ACT_SOFT3;
#endif
      switch ( keyCode ) {
#ifdef TRANSLATE_STAR_AND_POUND_TO_SOFT
        case KEY_STAR:
          return ACT_SOFT1;
        case KEY_POUND:
          return ACT_SOFT2;
#endif
#ifdef TRANSLATE_NUM_TO_ARROW
        case KEY_NUM4:
          return ACT_LEFT;
        case KEY_NUM6:
          return ACT_RIGHT;
        case KEY_NUM2:
          return ACT_UP;
        case KEY_NUM8:
          return ACT_DOWN;
        case KEY_NUM5:
          return ACT_FIRE;
#endif
      // если для устройства указаны коды, сначала пробуем их
#ifdef DEVICE_LEFT_SOFT_KEY
        case DEVICE_LEFT_SOFT_KEY:
          return ACT_SOFT1;
#endif
#ifdef DEVICE_RIGHT_SOFT_KEY
        case DEVICE_RIGHT_SOFT_KEY:
          return ACT_SOFT2;
#endif
#ifdef DEVICE_MIDLE_SOFT_KEY
        case DEVICE_MIDLE_SOFT_KEY:
          return ACT_SOFT3;
#endif
      }
      // иначе, пробуем стандартные действия
      int action = getGameAction(keyCode);
      if ( action != 0 && (action < 9 || action > 12 ))
        return action;
      switch ( keyCode ) {
        case 21:
          return ACT_SOFT1;
        case 22:
          return ACT_SOFT2;
        case 23:
          return ACT_SOFT3;
        case -6:
          return ACT_SOFT1;
        case -7:
          return ACT_SOFT2;
        case -12:
          return ACT_SOFT3;
        case -20:
          return ACT_SOFT1;
        case -21:
          return ACT_SOFT2;
        case -22:
          return ACT_SOFT3;
        case -1:
          return ACT_SOFT1;
        case -4:
          return ACT_SOFT2;
      }
      return 0;
    }
    
    

    // Обработчик нажатия клавиши
    public final void keyPressed(int keyCode) {
      long time = System.currentTimeMillis();
#ifdef ENABLE_CUSTOM_KEY_REPEATED
      for (int i = 0; i < _mvl_keyPressedMax; i++)
        if ( _mvl_keyPressedCodes[i] == 0 ) {
          _mvl_keyPressedCodes[i] = keyCode;
          _mvl_keyPressedTimes[i] = time;
          _mvl_keyPressedCount++;
          break;
        }
#endif // ENABLE_CUSTOM_KEY_REPEATED

      if ( _mvl_keyboardDisabled )
        return;
      if ( onKeyPressed(keyCode, time) )
        return;
//#ifdef ENABLE_GUI
//      if ( mvlSendKeyCodeToUi(keyCode, time, false) )
//        return;
//#endif
      int action = _mvl_getKeyActionCode(keyCode);
      if ( action != 0 ) {
#ifdef ENABLE_GUI
        if ( !mvlSendActionToUi(action, time, false) )
#endif
        onAction(action, time);
      }
    }



    // Обработчик отпускания клавиши
    public final void keyReleased(int keyCode) {
      long time = System.currentTimeMillis();
#ifdef ENABLE_CUSTOM_KEY_REPEATED
      for (int i = 0; i < _mvl_keyPressedMax; i++)
        if ( _mvl_keyPressedCodes[i] == keyCode ) {
          _mvl_keyPressedCodes[i] = 0;
          _mvl_keyPressedCount--;
        #ifdef DEBUG
          if ( _mvl_keyPressedCount < 0 )
            System.out.println("SYSTEM::MIDLET::keyReleased() failed !!!");
        #endif
          break;
        }
#endif  // ENABLE_CUSTOM_KEY_REPEATED

      if ( _mvl_keyboardDisabled )
        return;
      onKeyReleased(keyCode, time);
    }

#ifdef ENABLE_CUSTOM_KEY_REPEATED
    // Обработчик удержания клавиши
    public final void keyRepeated(int keyCode) {
      boolean found = false;
      if ( !_mvl_customKeyRepeated ) {
        long time = System.currentTimeMillis();
        for (int i = 0; i < _mvl_keyPressedMax; i++ )
          if ( _mvl_keyPressedCodes[i] == keyCode ) {
            found = true;
            if ( onKeyRepeated(_mvl_keyPressedCodes[i], time-_mvl_keyPressedTimes[i]) )
              _mvl_keyPressedTimes[i] = time;
            else {
              int action = _mvl_getKeyActionCode(_mvl_keyPressedCodes[i]);
              if ( action != 0 ) {
                if ( onActionRepeated(action, time-_mvl_keyPressedTimes[i]) )
                  _mvl_keyPressedTimes[i] = time;
              }
            } // else
          } // if ( _mvl_keyPressedCodes[i] != 0 )
      }
      if ( !found ) {
    #ifdef DEBUG
        System.out.println("SYSTEM::MIDLET::keyRepeated() key in buffer is not found !!!");
    #endif
     //   onKeyRepeated(keyCode, 0);
      }
    }
#endif // ENABLE_CUSTOM_KEY_REPEATED

    
    
    // Прорисовка экрана
    public final void paint(Graphics g) {
#ifdef ENABLE_POPUP_WINDOW
      if ( _mvl_windows.size() > 0 ) {
        drawImage(_mvl_screenBackBufferImage, 0, 0);
        for (int i = 0; i < _mvl_windows.size(); i++)
          ((TItem)_mvl_windows.elementAt(i)).draw(g, i==_mvl_windows.size()-1, 0, 0, getScreenWidth(), getScreenHeight());
        return;
      }
#endif // ENABLE_POPUP_WINDOW
#ifdef ENABLE_BACKBUFFER
      if ( _mvl_drawFromBackBuffer ) {
        drawImage(_mvl_screenBackBufferImage, 0, 0);
        _mvl_drawFromBackBuffer = false;
        return;
      }

      if ( _mvl_drawToBackBuffer ) {
        onPaint(_mvl_screenBackBufferGraphics);
      } else
        onPaint(g);
#else // ENABLE_BACKBUFFER
      onPaint(g);
#endif // ENABLE_BACKBUFFER

#ifdef ENABLE_GUI
  #ifdef ENABLE_BACKBUFFER
      if ( _mvl_drawToBackBuffer ) {
        for (int i = 0; i < _mvl_ui_screens[_mvl_screen].size(); i++)
          ((TItem)_mvl_ui_screens[_mvl_screen].elementAt(i)).draw(_mvl_screenBackBufferGraphics, _mvl_ui_screen_active[_mvl_screen]==i, 0, 0, getScreenWidth(), getScreenHeight());
      } else {
        for (int i = 0; i < _mvl_ui_screens[_mvl_screen].size(); i++)
          ((TItem)_mvl_ui_screens[_mvl_screen].elementAt(i)).draw(g, _mvl_ui_screen_active[_mvl_screen]==i, 0, 0, getScreenWidth(), getScreenHeight());
      }
  #else
       for (int i = 0; i < _mvl_ui_screens[_mvl_screen].size(); i++)
         ((TItem)_mvl_ui_screens[_mvl_screen].elementAt(i)).draw(g, _mvl_ui_screen_active[_mvl_screen]==i, 0, 0, getScreenWidth(), getScreenHeight());
  #endif
#endif  // ENABLE_GUI

#ifdef ENABLE_BACKBUFFER
      if ( _mvl_drawToBackBuffer ) {
        onPostPaint(_mvl_screenBackBufferGraphics);
        _mvl_drawToBackBuffer = false;
      } else
        onPostPaint(g);
#else // ENABLE_BACKBUFFER
      onPostPaint(g);
#endif // ENABLE_BACKBUFFER


    #ifdef SCREEN_CUSTOM_REPAINT
      _mvl_painted = true;
    #endif
    }



    //  Поток экрана
    public final void run() {
      while ( _mvl_running ) {
#ifdef ENABLE_CUSTOM_KEY_REPEATED
        long time1 = System.currentTimeMillis();
        if ( _mvl_customKeyRepeated ) {
          for (int i = 0; i < _mvl_keyPressedMax; i++ ) {
            int keyCode = _mvl_keyPressedCodes[i];
            if ( keyCode != 0 ) {
              if ( onKeyRepeated(keyCode, time1-_mvl_keyPressedTimes[i]) )
                _mvl_keyPressedTimes[i] = time1;
              else {
                int action = _mvl_getKeyActionCode(keyCode);
                if ( action != 0 ) {
                  if ( onActionRepeated(action, time1-_mvl_keyPressedTimes[i]) )
                    _mvl_keyPressedTimes[i] = time1;
                }
              } // else
            } // if ( _mvl_keyPressedCodes[i] != 0 )
          } // for
        } // custom key repeated
        long timeKey = System.currentTimeMillis()-time1;
  #ifdef ENABLE_GUI
        long timeBeforeGui = System.currentTimeMillis();
        int min = -1;
    #ifdef ENABLE_POPUP_WINDOW
        if ( _mvl_windows.size() > 0 ) {
          for (int i = 0; i < _mvl_windows.size(); i++) {
           int val = ((TItem)_mvl_windows.elementAt(i)).idle();
            if ( (val >= 0) && ( (min < 0) || (val < min) ) )
               min = val;
          } // for
        } else
    #endif // ENABLE_POPUP_WINDOW
        for (int i = 0; i < _mvl_ui_screens[_mvl_screen].size(); i++) {
          int val = ((TItem)_mvl_ui_screens[_mvl_screen].elementAt(i)).idle();
          if ( (val >= 0) && ( (min < 0) || (val < min) ) )
             min = val;
        } // for
        if ( _mvl_ui_repaint_request ) {
          repaint();
          _mvl_ui_repaint_request = false;
        }
        long timeGui = System.currentTimeMillis() - timeBeforeGui;
        if ( min < 0 )
          sleep(onIdle()-timeKey-timeGui);
        else {
          long idleTime = onIdle();
          if ( idleTime < min )
            sleep(idleTime-timeKey-timeGui);
          else
            sleep(idleTime-timeKey-timeGui);
        }
  #else  // ENABLE_GUI
        sleep(onIdle()-timeKey);
  #endif  // ENABLE_GUI
#else // ENABLE_CUSTOM_KEY_REPEATED
        sleep(onIdle());
#endif // ENABLE_CUSTOM_KEY_REPEATED
      } // while
    } // run
    
    
    
    public final void showNotify() {
      onShow();
    }
    
    
    
    public final void hideNotify() {
      onHide();
    }
    
    
    public final void commandAction(Command c, Displayable d) {
#ifdef ENABLE_GUI
      _mvl_ui_command_item.commandHandler(c, d);
#endif
    }
    
  } // end of MainFrame


#include "mvl/j2me/font.h"



}   // end of Midlet
#endmacro

