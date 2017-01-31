#ifnotdef __KEYBOARD_H__
#define   __KEYBOARD_H__

#defineblock begin
/*----------------------------------------------------------------------------*\

                            Trol Mobile Studio v 1.0
                        Runtime libraries:  KEYBOARD.H

                      Copyright (c) O.A. Trifonov, 2004-2006
                                  Version 1.0
                                 
                                 
  Supported devices:
    Motorola      V300/V400/V500, T720, C650
    SonyEricsson  T610, K700
    Nokia         Series 40, Series 60
    Samsung       E700, X600
    Siemens       55, 65
    Abstract MIDP 1.0 device
    Abstract MIDP 2.0 device
    
/*----------------------------------------------------------------------------*/



//----------------------------------------------------------------------------//
//                            общие коды клавиш                               //
//----------------------------------------------------------------------------//
// цифровые клавиши, их коды одинаковы для всех телефонов
#define     KEY_NUM0         48
#define     KEY_NUM1         49
#define     KEY_NUM2         50
#define     KEY_NUM3         51
#define     KEY_NUM4         52
#define     KEY_NUM5         53
#define     KEY_NUM6         54
#define     KEY_NUM7         55
#define     KEY_NUM8         56
#define     KEY_NUM9         57
// * и #, их коды тоже стандартны
#define     KEY_STAR         42
#define     KEY_POUND        35
//----------------------------------------------------------------------------//
//              коды клавиш джойстика и функциональных клавиш                 //
//----------------------------------------------------------------------------//
#ifdef    DEVICE_MOTOROLA_V300

  #define   KEY_UP          1
  #define   KEY_DOWN        6
  #define   KEY_LEFT        2
  #define   KEY_RIGHT       5
  #define   KEY_SELECT      20
  #define   KEY_F1          21
  #define   KEY_F2          22
  #define   KEY_F3          23
  #define   KEY_CALL        -10
  
#elseif   DEVICE_MOTOROLA_T720

  #define   KEY_UP          -10
  #define   KEY_DOWN        -11
  #define   KEY_LEFT        -13
  #define   KEY_RIGHT       -12
  #define   KEY_F1          -20
  #define   KEY_F2          -21
  #define   KEY_F3          -22
  #define   KEY_CALL        -14

#elseif   DEVICE_SONYERICSSON_T610

  #define   KEY_UP          -1
  #define   KEY_DOWN        -2
  #define   KEY_LEFT        -3
  #define   KEY_RIGHT       -4
  #define   KEY_SELECT      -5
  #define   KEY_F1          -6
  #define   KEY_F2          -7

#elseif   DEVICE_NOKIA_SERIES_40

  #define   KEY_UP          -1
  #define   KEY_DOWN        -2
  #define   KEY_LEFT        -3
  #define   KEY_RIGHT       -4
  #define   KEY_SELECT      -5
  #define   KEY_F1          -6
  #define   KEY_F2          -7
  #define   KEY_CALL        -10

#elseif   DEVICE_NOKIA_SERIES_60

  #define   KEY_UP          -1
  #define   KEY_DOWN        -2
  #define   KEY_LEFT        -3
  #define   KEY_RIGHT       -4
  #define   KEY_SELECT      -5
  #define   KEY_F1          -6
  #define   KEY_F2          -7
  #define   KEY_F3          -12
  #define   KEY_C           -8
  #define   KEY_ABC         -50
  #define   KEY_CALL        -10

#elseif   DEVICE_SAMSUNG_E700

  #define   KEY_UP          -1
  #define   KEY_DOWN        -2
  #define   KEY_LEFT        -3
  #define   KEY_RIGHT       -4
  #define   KEY_SELECT      -5
  #define   KEY_CALL        -10
  #define   KEY_EXIT        -11
  #define   KEY_C           -8

#elseif   DEVICE_SAMSUNG_X600

  #define   KEY_UP          -1
  #define   KEY_DOWN        -2
  #define   KEY_LEFT        -3
  #define   KEY_RIGHT       -4
  #define   KEY_SELECT      -5
  #define   KEY_CALL        -10
  #define   KEY_EXIT        -11
  #define   KEY_C           -8

#elseif   DEVICE_SIEMENS_55

  #define   KEY_UP          -59
  #define   KEY_DOWN        -60
  #define   KEY_LEFT        -61
  #define   KEY_RIGHT       -62
  #define   KEY_F1          -1
  #define   KEY_F2          -4
  
#elseif   DEVICE_SIEMENS_65

  #define   KEY_UP          -59
  #define   KEY_DOWN        -60
  #define   KEY_LEFT        -61
  #define   KEY_RIGHT       -62
  #define   KEY_F1          -1
  #define   KEY_F2          -4
  #define   KEY_SELECT      -26

#elseif    DEVICE_MOTOROLA_C650

  #define   KEY_UP          1
  #define   KEY_DOWN        6
  #define   KEY_LEFT        2
  #define   KEY_RIGHT       5
  #define   KEY_SELECT      20
  #define   KEY_CALL        -10
  
#elseif DEVICE_SONYERICSSON_K700

  #define   KEY_UP          -1
  #define   KEY_DOWN        -2
  #define   KEY_LEFT        -3
  #define   KEY_RIGHT       -4
  #define   KEY_SELECT      -5
  #define   KEY_F1          -6
  #define   KEY_F2          -7

#elseif    DEVICE_ABSTRACT_MIDP1

  #define   KEY_F1          21
  #define   KEY_F2          22

#elseif    DEVICE_ABSTRACT_MIDP2

  #define   KEY_F1          21
  #define   KEY_F2          22

#endif
//----------------------------------------------------------------------------//
//              макрофункции включения и выключения клавиатуры                //
//----------------------------------------------------------------------------//
//   void enableKeyboard()
// уменьшает счетчик блокировки клавиатуры
#macro enableKeyboard()
keyboardEnabled = true;
#endmacro
//------------------------------------------------------------------------------
//   void disableKeyboard()
// увеличивает счетчик блокировки клавиатуры
#macro disableKeyboard()
keyboardEnabled = false;
#endmacro

//----------------------------------------------------------------------------//
//       макрофункции проверки нажатия стандартных комбинаций клавиш          //
//----------------------------------------------------------------------------//



//------------------------------------------------------------------------------
//   boolean action_up(code = keyCode)
// возвращает true, если была нажата одна из клавиш перемещения вверх
#macro action_up(keyCode)
((pressedKeyCodeAction == UP) || (keyCode == KEY_NUM2))
#endmacro

#macro action_up()
((pressedKeyCodeAction == UP) || (keyCode == KEY_NUM2))
#endmacro
//------------------------------------------------------------------------------
//   boolean action_down(code = keyCode)
// возвращает true, если была нажата одна из клавиш перемещения вниз
#macro action_down(keyCode)
((getGameAction(keyCode) == DOWN) || (keyCode == KEY_NUM8))
#endmacro

#macro action_down()
((getGameAction(keyCode) == DOWN) || (keyCode == KEY_NUM8))
#endmacro
//------------------------------------------------------------------------------
//   boolean action_left(code = keyCode)
// возвращает true, если была нажата одна из клавиш перемещения влево
#macro action_left(keyCode)
((pressedKeyCodeAction == LEFT) || (keyCode == KEY_NUM4))
#endmacro

#macro action_left()
((pressedKeyCodeAction == LEFT) || (keyCode == KEY_NUM4))
#endmacro
//------------------------------------------------------------------------------
//   boolean action_right(code = keyCode)
// возвращает true, если была нажата одна из клавиш перемещения вправо
#macro action_right(keyCode)
((pressedKeyCodeAction == RIGHT) || (keyCode == KEY_NUM6))
#endmacro

#macro action_right()
((pressedKeyCodeAction == RIGHT) || (keyCode == KEY_NUM6))
#endmacro
//------------------------------------------------------------------------------
//   boolean action_select(code = keyCode)
// возвращает true, если была нажата клавиша выбора
#macro action_select(keyCode)
((pressedKeyCodeAction == FIRE) || (keyCode == KEY_NUM5))
#endmacro

#macro action_select()
((pressedKeyCodeAction == FIRE) || (keyCode == KEY_NUM5))
#endmacro
//------------------------------------------------------------------------------
//   boolean action_F1(code = keyCode)
// возвращает true, если была нажата левая функциональная клавиша
#ifdef KEY_F1
  #macro action_F1(keyCode)
(keyCode == KEY_F1)
  #endmacro
#else
  #macro action_F1(keyCode)
(keyCode == KEY_STAR)
  #endmacro
#endif


#ifdef KEY_F1
  #macro action_F1()
(keyCode == KEY_F1)
  #endmacro
#else
  #macro action_F1()
(keyCode == KEY_STAR)
  #endmacro
#endif
//------------------------------------------------------------------------------
//   boolean action_F2(code = keyCode)
// возвращает true, если была нажата правая функциональная клавиша
#ifdef KEY_F2
  #macro action_F2(keyCode)
(keyCode == KEY_F2)
  #endmacro
#else
  #macro action_F2(keyCode)
(keyCode == KEY_POUND)
  #endmacro
#endif

#ifdef KEY_F2
  #macro action_F2()
(keyCode == KEY_F2)
  #endmacro
#else
  #macro action_F2()
(keyCode == KEY_POUND)
  #endmacro
#endif




// ДЖОЙСТИК
#macro joystic_up(keyCode)
(getGameAction(keyCode) == UP)
#endmacro

#macro joystic_down(keyCode)
(getGameAction(keyCode) == DOWN)
#endmacro

#macro joystic_left(keyCode)
(getGameAction(keyCode) == LEFT)
#endmacro

#macro joystic_right(keyCode)
(getGameAction(keyCode) == RIGHT)
#endmacro


#macro joystic_up()
(getGameAction(keyCode) == UP)
#endmacro

#macro joystic_down()
(getGameAction(keyCode) == DOWN)
#endmacro

#macro joystic_left()
(getGameAction(keyCode) == LEFT)
#endmacro

#macro joystic_right()
(getGameAction(keyCode) == RIGHT)
#endmacro





#defineblock end
#endif
