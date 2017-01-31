/*----------------------------------------------------------------------------*\

                            Trol Mobile Studio v 1.0
                            
                            J2SE platform - applet
                            
                          Runtime libraries:  APPLET.H

                      Copyright (c) O.A. Trifonov, 2006
                                 Version 1.0


\*----------------------------------------------------------------------------*/
#macro  _APP_HEADER_(_appname_, _mainclass_)
package _appname_;

import java.applet.*;
import java.awt.*;
import java.io.*;
import java.util.*;

__user_imoprt__()

// ****************************************************************************
// ********************  ГЛАВНЫЙ КЛАСС ПРИЛОЖЕНИЯ  ****************************
// ****************************************************************************
public class _mainclass_ extends Applet implements Runnable {
// Системные объекты
  public static _mainclass_ instance;             // ссылка на себя
  public static int screen;                       // текущий экран
  public static int keyboardEnabled = 0;          // счетчик блокировок клавиатуры
  public static boolean running;                   // флаг того, что поток класса запущен
  public static int screenWidth;                  // ширина экрана
  public static int screenHeight;                 // высота экрана

  
#endmacro







#macro _APP_BODY_(_appname_, _mainclass_)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Методы апплета
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Иннициализация
  public void init() {
    instance = this;
    onCreate();
    running = true;
    Thread t = new Thread(this);
    t.start();
    screenWidth = getWidth();
    screenHeight = getHeight();
  }
//------------------------------------------------------------------------------
// Запуск апплета
  public void start() {
    onStart();
  }
//------------------------------------------------------------------------------
// Уничтожение апплета
  public void destroy() {
    onDestroy();
  }
//------------------------------------------------------------------------------
// Прорисовка экрана
public void paint(Graphics g) {
#define _MAIN_FRAME_DEFINED_
  onPaint(g);
#undefine _MAIN_FRAME_DEFINED_
}
//------------------------------------------------------------------------------
// Поток программы
public final void run() {
  while (running) {
    onRun()
  }
}


//------------------------------------------------------------------------------
/*
//-----------------------------------------------------------------------------
// Обработчик нажатия клавиши
    public void keyPressed(int keyCode) {
      if (keyboardEnabled < 0)
        return;
      pressedKeyCode = keyCode;
      pressedKeyCodeAction = getGameAction(keyCode);
      onKeyPressed(keyCode)
    }
//-----------------------------------------------------------------------------
// Обработчик отпускания клавиши
    public void keyReleased(int keyCode) {
      pressedKeyCode = 0;
      onKeyReleased(keyCode);
    }
//-----------------------------------------------------------------------------
// Прорисовка экрана
// ----------------------------------------------------------------------------
//  Поток экрана
    public void run() {
      while (runing) {
        onRun()
      }
    }
// ----------------------------------------------------------------------------
// Обработчик событий экрана
    public void commandAction(Command aCommand, Displayable aDisplay) {
      if (keyboardEnabled < 0)
        return;
      onCommand(aCommand, aDisplay);
    }
*/

}   // end of Applet
#endmacro

