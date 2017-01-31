/*----------------------------------------------------------------------------*\

                            Trol Mobile Studio v 1.0
                               BlackBerry platform
                           Runtime libraries:  APP.H

                      Copyright (c) O.A. Trifonov, 2006
                                 Version 1.0


\*----------------------------------------------------------------------------*/
#macro  _APP_HEADER_(_appname_, _mainclass_)
package _appname_;


import java.lang.*;
import java.util.*;
import java.io.*;
import javax.microedition.io.* ;
import javax.microedition.rms.*;
import javax.microedition.media.*;
import javax.microedition.media.control.*;

import net.rim.device.api.system.*;
import net.rim.device.api.util.*;
import net.rim.device.api.ui.*;
import net.rim.device.api.ui.container.*;

__user_imoprt__()





// ****************************************************************************
// ********************  ГЛАВНЫЙ КЛАСС ПРИЛОЖЕНИЯ  ****************************
// ****************************************************************************
public class _mainclass_ extends UiApplication {
// Системные объекты
  public static _mainclass_ instance;             // ссылка на себя
  public static MainFrame mainFrame;              // основная канва
  public static int screen;                       // текущий экран
  public static int keyboardEnabled = 0;          // счетчик блокировок клавиатуры
  public static Runnable mainThread = null;       // главный поток
  public static int screenWidth;                  // ширина экрана
  public static int screenHeight;                 // высота экрана
  
#endmacro







#macro _APP_BODY_(_appname_, _mainclass_)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Методы приложения
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
  public static void main(String[] args)
  {
    instance = new _mainclass_();
    instance.enterEventDispatcher();              // запуск обработчика событий

  }
// ----------------------------------------------------------------------------
// Конструктор
  public _mainclass_() {
    enableKeyUpEvents(true);
    mainFrame = new MainFrame();

#defineblock begin
    #ifdef DEBUG
    _debugInitSocketMessage();
    String appName = toquote(_appname_);
    String debugPath = toquote(PATH_PROJECT_ROOT) + "debug";
    sleep(100);
    smsg("app=" + appName);
    sleep(300);
    smsg("dir=" + debugPath);
    sleep(300);
    #endif
#defineblock end

    onCreate();
    
    onStart();
    
    pushScreen(mainFrame);                      // устанавливаем активный экран
    screenWidth = mainFrame.getWidth();
    screenHeight = mainFrame.getHeight();

    repaint();
  }
//*****************************************************************************
//*************************  КЛАСС ГЛАВНОЙ КАНВЫ  *****************************
//*****************************************************************************
  public final class MainFrame extends MainScreen {
// ----------------------------------------------------------------------------
// Конструктор класса экрана
    public MainFrame() {
      super (DEFAULT_MENU | DEFAULT_CLOSE);
      mainThread = new Runnable() {
        public void run() {
          onRun();
          invokeLater(mainThread);
        }
      };
      invokeLater(mainThread);
    }
// ----------------------------------------------------------------------------
// Прорисовка экрана
    public void paint(Graphics g) {
      onPaint(g);
    }
// ----------------------------------------------------------------------------
    public final boolean onClose() {
   	return keyDown(0, 0);
    }
// ----------------------------------------------------------------------------
// Обработчик нажатия клавиши
    public boolean keyDown(int keyCode, int time) {
      if (keyboardEnabled < 0)
        return false;
      onKeyPressed(keyCode)
      return true;
    }
//-----------------------------------------------------------------------------
// Обработчик отпускания клавиши
    public boolean keyUp(int keyCode, int time) {
      if (keyboardEnabled < 0)
        return false;
      onKeyReleased(keyCode)
      return true;
    }
//-----------------------------------------------------------------------------
// Обработчик прокрутки колеса
  public boolean trackwheelRoll(int aAmount, int aStatus, int aTime) {
    onTrackweelRoll(aAmount)
  }
//-----------------------------------------------------------------------------
// Обработчик нажатия колеса
  public boolean trackwheelClick(int status, int time) {
    onTrackweelClick()
  }
//-----------------------------------------------------------------------------
// Обработчик отпускания колеса
  public boolean trackwheelUnclick(int status, int time) {
    onTrackweelUnclick()
  }
//-----------------------------------------------------------------------------
  } // end of MainFrame
#undefine _GAME_FRAME_DEFINED_
}   // end of Midlet
#endmacro

