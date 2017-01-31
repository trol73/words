/*----------------------------------------------------------------------------*\

                            Trol Mobile Studio v 1.0
                            
                          J2SE platform - application
                            
                          Runtime libraries:  APP.H

                      Copyright (c) O.A. Trifonov, 2006
                                 Version 1.0


\*----------------------------------------------------------------------------*/
#macro  _APP_HEADER_(_appname_, _mainclass_)
package _appname_;


import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.util.*;

__user_imoprt__()

// ****************************************************************************
// ********************  ГЛАВНЫЙ КЛАСС ПРИЛОЖЕНИЯ  ****************************
// ****************************************************************************
public class _mainclass_ extends JFrame implements Runnable {
// Системные объекты
  public static _mainclass_ instance;             // ссылка на себя
  public static int screen;                       // текущий экран
  public static int keyboardEnabled = 0;          // счетчик блокировок клавиатуры
  public static boolean running;                  // флаг того, что поток класса запущен
  public static int JFrame_windowFrameHeight;     // высота рамки окна
  public static int screenWidth;                  // ширина экрана
  public static int screenHeight;                 // высота экрана

  
#endmacro







#macro _APP_BODY_(_appname_, _mainclass_)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Методы приложения
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Конструктор
  public _mainclass_() {
    super ("");
    instance = this;
    onCreate();
    show();
    JFrame_windowFrameHeight = getHeight();
    hide();
    #ifdef DEVICE_SCREEN_WIDTH
      #ifdef DEVICE_SCREEN_HEIGHT
        #define __WINDOW__SIZE__
      #endif
    #endif
    #ifdef __WINDOW__SIZE__
    setSize(DEVICE_SCREEN_WIDTH+7, DEVICE_SCREEN_HEIGHT+JFrame_windowFrameHeight-1);
      #undefine __WINDOW__SIZE__
    #else
// DEVICE_SCREEN_WIDTH
    setSize(640+7, 480+JFrame_windowFrameHeight-1);
    #endif
    screenWidth = getWidth() - 7;
    screenHeight = getHeight() + 1 - JFrame_windowFrameHeight;

    setResizable(false);
    
    running = true;
    Thread t = new Thread(this);
    t.start();

    show();
  }
//------------------------------------------------------------------------------
// Запуск приложения
  public static void main(String args[]) {
    _mainclass_ app = new _mainclass_();
    onStart();
    
    app.addWindowListener(
      new WindowAdapter() {
        public void windowClosing( WindowEvent e ) {
          onDestroy();
          System.exit(0);
        }
      }
    );
  }
//------------------------------------------------------------------------------
// Прорисовка экрана
  public void paint(Graphics g) {
    g.translate(3, JFrame_windowFrameHeight-5);
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

  
}   // end of Application
#endmacro


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




