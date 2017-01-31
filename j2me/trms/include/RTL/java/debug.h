/******************************************************************************
                            Trol MobileStudio                                 
                                                                              
                     Runtime libraries:  RTL/JAVA/DEBUG.H
                                                                              
                               Макросы отладки
                                                                              
                  Copyright (c) by O.A. Trifonov, 2004-2006
                                                                              
    Created: 08.08.2006
    
    Макросы модуля отладки:
    
      DEBUG      - включает генерацию отладочного кода
      NDEBUG     - отключает генерацию отладочного кода
      
      DEBUG_CONSOLE  - разрешает выдачу отладочной информации в консоль
      DEBUG_DEVICE   - разрешает выдачу отладочной информации в окно устройства
      DEBUG_SOKET    - разрешает выдачу отладочной информации через сокеты
      DEBUG_MSG      - включает функцию msg(...)
      DEBUG_MEMORY   - включает функцию mem() если DEBUG не определен
      
      DEBUG_TRANSLIT_CONSOLE  - включить транслитерацию при выводе на консоль
      DEBUG_TRANSLIT_DEVICE   - включить транслитерацию при выводе в окно устройства
      DEBUG_TRANSLIT_SOCKET   - включить транслитерацию при передаче информации через сокеты
      
      DEBUG_HOST              - адрес хоста, на который будет передаваться отчет
      DEBUG_PORT              - его порт
      
   Определяет макрофункции:
      cmsg(...)               - вывод сообщения на консоль
      dmsg(...)               - вывод сообщения на экран устройства
      smsg(...)               - вывод сообщения через сокет
      msg(...)                - вывод сообщения на все разрешенные приемники
      assert(expr[, msg])     - проверка утверждений
      mem([msg])              - вывод сообщения о свободной памяти на все разрешенные приемники
      ddelay(ms)              - задержка в отладочной версии
                                                                              
                                                                              
******************************************************************************/


//------------------------------------------------------------------------------
//   void assert(bool expr, String msg)
// проверяет указанное выражение на истинность. если оно ложно, выдает указанное
// сообщение об ошибке
#macro assert(expr)
#ifdef DEBUG
if ( !(expr) ) {
 #ifdef DEBUG_CONSOLE
  System.out.println("ASSERTION ERROR >> " + __FILE__ + ":" + __LINE__ + " ("+toquote(expr)+")");
 #endif
}
#endif
#endmacro



#macro assert(expr, msg)
#ifdef DEBUG
if ( !(expr) ) {
 #ifdef DEBUG_CONSOLE
  System.out.println("ASSERTION ERROR >> " + __FILE__ + ":" + __LINE__ + "->" + (msg) + " ("+toquote(expr)+")");
 #endif
}
#endif
#endmacro



//------------------------------------------------------------------------------
//   void msg(text1, [text2...text12])
// выводит сообщение на консоль
#macro msg(text1)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + "\n";
  #endif
#endif
#endmacro


#macro msg(text1, text2)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1)+"  "+(text2));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + (text2) + "\n";
  #endif
#endif
#endmacro


#macro msg(text1, text2, text3)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1)+"  "+(text2)+"  "+(text3));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + (text2) + (text3) + "\n";
  #endif
#endif
#endmacro


#macro msg(text1, text2, text3, text4)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1)+"  "+(text2)+"  "+(text3)+"  "+(text4));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + (text2) + (text3) + (text4) + "\n";
  #endif
#endif
#endmacro


#macro msg(text1, text2, text3, text4, text5)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1)+"  "+(text2)+"  "+(text3)+"  "+(text4)+"  "+(text5));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + (text2) + (text3) + (text4) + (text5) + "\n";
  #endif
#endif
#endmacro


#macro msg(text1, text2, text3, text4, text5, text6)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1)+"  "+(text2)+"  "+(text3)+"  "+(text4)+"  "+(text5)+"  "+(text6));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + (text2) + (text3) + (text4) + (text5) + (text6) + "\n";
  #endif
#endif
#endmacro


#macro msg(text1, text2, text3, text4, text5, text6, text7)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1)+"  "+(text2)+"  "+(text3)+"  "+(text4)+"  "+(text5)+"  "+(text6)+"  "+(text7));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + (text2) + (text3) + (text4) + (text5) + (text6) + (text7) + "\n";
  #endif
#endif
#endmacro


#macro msg(text1, text2, text3, text4, text5, text6, text7, text8)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1)+"  "+(text2)+"  "+(text3)+"  "+(text4)+"  "+(text5)+"  "+(text6)+"  "+(text7)+"  "+(text8));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + (text2) + (text3) + (text4) + (text5) + (text6) + (text7) + (text8) + "\n";
  #endif
#endif
#endmacro


#macro msg(text1, text2, text3, text4, text5, text6, text7, text8, text9)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1)+"  "+(text2)+"  "+(text3)+"  "+(text4)+"  "+(text5)+"  "+(text6)+"  "+(text7)+"  "+(text8)+"  "+(text9));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + (text2) + (text3) + (text4) + (text5) + (text6) + (text7) + (text8) + (text9) + "\n";
  #endif
#endif
#endmacro


#macro msg(text1, text2, text3, text4, text5, text6, text7, text8, text9, text10)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1)+"  "+(text2)+"  "+(text3)+"  "+(text4)+"  "+(text5)+"  "+(text6)+"  "+(text7)+"  "+(text8)+"  "+(text9)+"  "+(text10));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + (text2) + (text3) + (text4) + (text5) + (text6) + (text7) + (text8) + (text9) + (text10) + "\n";
  #endif
#endif
#endmacro


#macro msg(text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1)+"  "+(text2)+"  "+(text3)+"  "+(text4)+"  "+(text5)+"  "+(text6)+"  "+(text7)+"  "+(text8)+"  "+(text9)+"  "+(text10)+"  "+(text11));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + (text2) + (text3) + (text4) + (text5) + (text6) + (text7) + (text8) + (text9) + (text10) + (text11) + "\n";
  #endif
#endif
#endmacro


#macro msg(text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11, text12)
#ifdef DEBUG
  #ifdef DEBUG_CONSOLE
System.out.println(""+(text1)+"  "+(text2)+"  "+(text3)+"  "+(text4)+"  "+(text5)+"  "+(text6)+"  "+(text7)+"  "+(text8)+"  "+(text9)+"  "+(text10)+"  "+(text11)+"  "+(text12));
  #endif
  #ifdef DEBUG_DEVICE
_debugOutputLines_ += (text1) + (text2) + (text3) + (text4) + (text5) + (text6) + (text7) + (text8) + (text9) + (text10) + (text11) + (text12) + "\n";
  #endif
#endif
#endmacro


//------------------------------------------------------------------------------
//   void dmsg(text1, [text2...text12])
// выводит сообщение на экран устройства
#macro dmsg(text1)
#ifdef DEBUG
_debugOutputLines_ += (text1)+"\n";
#endif
#endmacro



#macro dmsg(text1, text2)
#ifdef DEBUG
_debugOutputLines_ += (text1)+" "+(text2)+"\n";
#endif
#endmacro



#macro dmsg(text1, text2, text3)
#ifdef DEBUG
_debugOutputLines_ += (text1)+" "+(text2)+" "+(text3)+"\n";
#endif
#endmacro



#macro dmsg(text1, text2, text3, text4)
#ifdef DEBUG
_debugOutputLines_ += (text1)+" "+(text2)+" "+(text3)+" "+(text4)+"\n";
#endif
#endmacro


#macro dmsg(text1, text2, text3, text4, text5)
#ifdef DEBUG
_debugOutputLines_ += (text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+"\n";
#endif
#endmacro


#macro dmsg(text1, text2, text3, text4, text5, text6)
#ifdef DEBUG
_debugOutputLines_ += (text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+"\n";
#endif
#endmacro


#macro dmsg(text1, text2, text3, text4, text5, text6, text7)
#ifdef DEBUG
_debugOutputLines_ += (text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7)+"\n";
#endif
#endmacro


#macro dmsg(text1, text2, text3, text4, text5, text6, text7, text8)
#ifdef DEBUG
_debugOutputLines_ += (text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7)+" "+(text8)+"\n";
#endif
#endmacro


#macro dmsg(text1, text2, text3, text4, text5, text6, text7, text8, text9)
#ifdef DEBUG
_debugOutputLines_ += (text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7)+" "+(text8)+" "+(text9)+"\n";
#endif
#endmacro


#macro dmsg(text1, text2, text3, text4, text5, text6, text7, text8, text9, text10)
#ifdef DEBUG
_debugOutputLines_ += (text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7)+" "+(text8)+" "+(text9)+" "+(text10)+"\n";
#endif
#endmacro


#macro dmsg(text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11)
#ifdef DEBUG
_debugOutputLines_ += (text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7)+" "+(text8)+" "+(text9)+" "+(text10)+" "+(text11)+"\n";
#endif
#endmacro


#macro dmsg(text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11, text12)
#ifdef DEBUG
_debugOutputLines_ += (text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7)+" "+(text8)+" "+(text9)+" "+(text10)+" "+(text11)+" "+(text12)+"\n";
#endif
#endmacro




//------------------------------------------------------------------------------
//   void smsg(text1, [text2...text12])
// выводит сообщение через сокет
#macro smsg(text1)
#ifdef DEBUG
_debugSocketMessage(""+text1);
#endif
#endmacro



#macro smsg(text1, text2)
#ifdef DEBUG
_debugSocketMessage(""+(text1)+" "+(text2));
#endif
#endmacro



#macro smsg(text1, text2, text3)
#ifdef DEBUG
_debugSocketMessage(""+(text1)+" "+(text2)+" "+(text3));
#endif
#endmacro



#macro smsg(text1, text2, text3, text4)
#ifdef DEBUG
_debugSocketMessage(""+(text1)+" "+(text2)+" "+(text3)+" "+(text4));
#endif
#endmacro


#macro smsg(text1, text2, text3, text4, text5)
#ifdef DEBUG
_debugSocketMessage(""+(text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5));
#endif
#endmacro


#macro smsg(text1, text2, text3, text4, text5, text6)
#ifdef DEBUG
_debugSocketMessage(""+(text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6));
#endif
#endmacro


#macro smsg(text1, text2, text3, text4, text5, text6, text7)
#ifdef DEBUG
_debugSocketMessage(""+(text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7));
#endif
#endmacro


#macro smsg(text1, text2, text3, text4, text5, text6, text7, text8)
#ifdef DEBUG
_debugSocketMessage(""+(text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7)+" "+(text8));
#endif
#endmacro


#macro smsg(text1, text2, text3, text4, text5, text6, text7, text8, text9)
#ifdef DEBUG
_debugSocketMessage(""+(text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7)+" "+(text8)+" "+(text9));
#endif
#endmacro


#macro smsg(text1, text2, text3, text4, text5, text6, text7, text8, text9, text10)
#ifdef DEBUG
_debugSocketMessage(""+(text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7)+" "+(text8)+" "+(text9)+" "+(text10));
#endif
#endmacro


#macro smsg(text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11)
#ifdef DEBUG
_debugSocketMessage(""+(text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7)+" "+(text8)+" "+(text9)+" "+(text10)+" "+(text11));
#endif
#endmacro


#macro smsg(text1, text2, text3, text4, text5, text6, text7, text8, text9, text10, text11, text12)
#ifdef DEBUG
_debugSocketMessage(""+(text1)+" "+(text2)+" "+(text3)+" "+(text4)+" "+(text5)+" "+(text6)+" "+(text7)+" "+(text8)+" "+(text9)+" "+(text10)+" "+(text11)+" "+(text12));
#endif
#endmacro

//------------------------------------------------------------------------------
//   void mem()
// Выводит количество свобожных байт после сборки мусора
#macro mem()
#ifdef DEBUG
  System.gc();
  #ifdef DEBUG_CONSOLE
  System.out.println("Free memory = " + (Runtime.getRuntime().freeMemory()));
  #endif
#elseif DEBUG_MEMORY
  System.gc();
  #ifdef DEBUG_CONSOLE
  System.out.println("Free memory = " + (Runtime.getRuntime().freeMemory()));
  #endif
#endif
#endmacro


//   void mem(String text)
// Выводит количество свобожных байт после сборки мусора и текстовое сообщение
#macro mem(text)
#ifdef DEBUG
  System.gc();
  #ifdef DEBUG_CONSOLE
  System.out.println(text + "  " + (Runtime.getRuntime().freeMemory()));
  #endif
#elseif DEBUG_MEMORY
  System.gc();
  #ifdef DEBUG_CONSOLE
  System.out.println(text + "  " + (Runtime.getRuntime().freeMemory()));
  #endif
#endif
#endmacro



//------------------------------------------------------------------------------
//   void delay(long ms)
// отладочная задержка приложения
#macro ddelay(ms)
#ifdef DEBUG
try { Thread.sleep(ms); } catch (InterruptedException e) { }
#endif
#endmacro

