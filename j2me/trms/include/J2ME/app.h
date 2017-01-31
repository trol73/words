/*----------------------------------------------------------------------------*\

                            Trol Mobile Studio v 1.0
                                  J2ME platform
                           Runtime libraries:  APP.H

                      Copyright (c) O.A. Trifonov, 2006
                                 Version 1.0


\*----------------------------------------------------------------------------*/
#macro  _APP_HEADER_(_appname_, _mainclass_)
package _appname_;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.rms.*;
import javax.microedition.io.*;
import java.io.*;
import java.util.*;

#ifdef MIDP_2
import javax.microedition.lcdui.game.*;
#endif
#ifdef NOKIA
import com.nokia.mid.ui.FullCanvas;
#endif

__user_imoprt__()

// ****************************************************************************
// ********************  ГЛАВНЫЙ КЛАСС ПРИЛОЖЕНИЯ  ****************************
// ****************************************************************************
public class _mainclass_ extends MIDlet {
// Системные объекты
  public static _mainclass_ instance;             // ссылка на себя
  public static MainFrame mainFrame;              // основная канва
  public static Display display;                  // класс экрана
  public static int screen;                       // текущий экран
  public static int keyboardEnabled = 0;          // счетчик блокировок клавиатуры
  public static int screenWidth;                  // ширина экрана
  public static int screenHeight;                 // высота экрана

#endmacro







#macro _APP_BODY_(_appname_, _mainclass_)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Методы мидлета
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Конструктор
  public _mainclass_() {
    instance = this;
    display = Display.getDisplay(this);

    mainFrame = new MainFrame();
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



    
    onCreate();
  }
//------------------------------------------------------------------------------
// Запуск мидлета
  public void startApp() {
    mainFrame.start();
    display.setCurrent(mainFrame);
//    setFullScreen();
    sleep(50);
    onStart();
    
    screenWidth = mainFrame.getWidth();
    screenHeight = mainFrame.getHeight();
  }
//------------------------------------------------------------------------------
// Пауза мидлета
  public void pauseApp() {
    onPause()
  }
//------------------------------------------------------------------------------
// Уничтожение мидлета
  public void destroyApp(boolean unconditional) {
    mainFrame.stop();
    onDestroy();
    _debugDoneSocketMessage();
  }
//*****************************************************************************
//*************************  КЛАСС ГЛАВНОЙ КАНВЫ  *****************************
//*****************************************************************************
  #ifdef NOKIA
  public class MainFrame extends FullCanvas implements Runnable, CommandListener {
  #else
  public class MainFrame extends Canvas implements Runnable, CommandListener {
  #endif
  
  #define _MAIN_FRAME_DEFINED_
    public boolean running;           // флаг того, что поток класса запущен
    public int pressedKeyCode;        // код удерживаемой клавиши, или 0
    public int pressedKeyCodeAction;  // её Action
    #ifdef CUSTOM_SCREEN_BUFFERING
    public Image imgBuf;               // буферная картинка
    public Graphics g;                 // ее Graphics
    #endif
    #ifdef SCREEN_CUSTOM_REPAINT
    public boolean painted = true;     // флаг того, что хапрос на отрисовку экрана был выполнен
    #endif


// ----------------------------------------------------------------------------
// Конструктор класса экрана
    public MainFrame() {
      running = false;
    #ifnotdef NOKIA
      setCommandListener(this);
    #endif

    #ifdef CUSTOM_SCREEN_BUFFERING
      // создаем буфферный экран
      try {
      #ifdef SCREEN_WIDTH
        #ifdef SCREEN_FULL_HEIGHT
        imgBuf = Image.createImage(SCREEN_WIDTH, SCREEN_FULL_HEIGHT);
        #elseifdef SCREEN_HEIGHT
        imgBuf = Image.createImage(SCREEN_WIDTH, SCREEN_HEIGHT);
        #endif
      #else
        imgBuf = Image.createImage(getWidth(), getHeight());
      #endif // SCREEN_WIDTH
        g = imgBuf.getGraphics();
      #ifdef DEBUG
      } catch(Exception e) { System.out.println(">> FATAL ERROR! >> create buffer image -> " + e.toString()); }
      #else
      } catch(Exception e) { }
      #endif // DEBUG
    #endif // CUSTOM_SCREEN_BUFFERING
    }
//-----------------------------------------------------------------------------
// Запускает главный поток приложения
    public final void start() {
      running = true;
      Thread t = new Thread(this);
      t.start();
    }
//-----------------------------------------------------------------------------
// Останавливает главный поток приложения
    public final void stop() {
      running = false;
    }
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
    #ifdef CUSTOM_SCREEN_BUFFERING
    public void paint(Graphics g0) {
      #ifdef SCREEN_WIDTH
        #ifdef SCREEN_FULL_HEIGHT
        g.setClip(0, 0, SCREEN_WIDTH, SCREEN_FULL_HEIGHT);
        #elseifdef SCREEN_HEIGHT
        g.setClip(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        #endif
      #else // SCREEN_WIDTH
        g.setClip(0, 0, getWidth(), getHeight());
      #endif // SCREEN_WIDTH
    #else // CUSTOM_SCREEN_BUFFERING
    public void paint(Graphics g) {
    #endif // CUSTOM_SCREEN_BUFFERING
      onPaint(g);
    #ifdef CUSTOM_SCREEN_BUFFERING
      g0.drawImage(imgBuf, 0, 0, 0);
    #endif // CUSTOM_SCREEN_BUFFERING
    #ifdef SCREEN_CUSTOM_REPAINT
      painted = true;
    #endif // SCREEN_CUSTOM_REPAINT
    }
// ----------------------------------------------------------------------------
//  Поток экрана
    public void run() {
      while (running) {
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
  } // end of MainFrame
#undefine _MAIN_FRAME_DEFINED_
}   // end of Midlet
#endmacro

