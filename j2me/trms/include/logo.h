#ifnotdef __LOGO_H__
#define   __LOGO_H__
#defineblock begin
//----------------------------------------------------------------------------//
//                       Tr Java Mobile Builder v 1.0.                        //
//                        Runtime libraries:  LOGO.H                          //
//                      Copyright (c) O.A. Trifonov, 2005                     //
//                                Version 1.0                                 //
//                                                                            //
//  Defines:                                                                  //
//  Macroses:                                                                 //
//  Functions:                                                                //
//  Variables:                                                                //
//                                                                            //
//                                                                            //
//  Supported devices (total 8 types):                                        //
//                                                                            //
//    Motorola      V300/V400/V500, T720                                      //
//                                                                            //
//    SonyEricsson  T610                                                      //
//                                                                            //
//    Nokia         Series 40, Series 60                                      //
//                                                                            //
//    Samsung       E700, X600                                                //
//                                                                            //
//    Siemens       S55                                                       //
//                                                                            //
//----------------------------------------------------------------------------//

//------------------------------------------------------------------------------
// Модуль предназначен для вывода анимированного логотипа, собирающегося на
// экране из 4-х частей.
//
// Для включения логотипа необходимо определить макрос USE_LOGO
// если этот макрос не определен, весь код этого модуля будет проигнорирован
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//   void logoInit(String filename; int delta)
// Загружает фрагменты логотипа из заданного файла
//   delta - смещение фрагмента логотипа за итерацию
#macro logoInit(filename, delta)
#ifdef USE_LOGO
  #ifdef DEBUG
try { imgAnimateLogo = Image.createImage(filename); } catch (Exception e) { System.out.println(">> FATAL ERROR! >> createImage(logo) -> file not found. " + e.toString()); } // логотип
  #else
try { imgAnimateLogo = Image.createImage(filename); } catch (Exception e) {} // логотип
  #endif
#endif
#endmacro
//------------------------------------------------------------------------------
//   void logoStart()
// Запускает анимацию логотипа
#macro logoStart()
#ifdef USE_LOGO
final int start_logo_a = __ANIMATE_LOGO_WIDTH/2;
final int start_logo_b = __ANIMATE_LOGO_HEIGHT/2;
final int start_logo_y0 = (SCREEN_HEIGHT/2 - start_logo_b);
pos_x = (SCREEN_WIDTH/2 - start_logo_a);
pos_y = start_logo_y0 - __ANIMATE_LOGO_DELTA*((start_logo_y0+start_logo_b)/__ANIMATE_LOGO_DELTA + 1);
animate_step = 0;
screen = SCR__LOGO;
repaint();
#endif
#endmacro
//------------------------------------------------------------------------------
//   void logoDrawHandler()
// Обработчик события прорисовки логотипа
#macro logoDrawHandler()
#ifdef USE_LOGO
  #define LOGO_A    __ANIMATE_LOGO_WIDTH/2
  #define LOGO_B    __ANIMATE_LOGO_HEIGHT/2
// рисование анимированного логотипа
switch (animate_step) {
  case 0:           // предварительная очистка экрана
    setColor(0x000000);
    fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    animate_step++;
    break;
  case 1:           // 1-й фрагмент логотипа.         вниз
    fillRect(pos_x, pos_y-__ANIMATE_LOGO_DELTA, LOGO_A, __ANIMATE_LOGO_DELTA);
    drawSprite(imgAnimateLogo, pos_x, pos_y, 0, 0, LOGO_A, LOGO_B);
    break;
  case 2:           // 2-й фрагмент логотипа.         влево
    fillRect(pos_x+LOGO_A, pos_y, __ANIMATE_LOGO_DELTA, LOGO_B);
    drawSprite(imgAnimateLogo, pos_x, pos_y, LOGO_A, 0, LOGO_A, LOGO_B);
    break;
  case 3:           // 3-й фрагмент логотипа.         вверх
    fillRect(pos_x, pos_y+LOGO_B, LOGO_A, __ANIMATE_LOGO_DELTA);
    drawSprite(imgAnimateLogo, pos_x, pos_y, LOGO_A, LOGO_B, LOGO_A, LOGO_B);
    break;
  case 4:           // 4-й фрагмент логотипа.         вправо
    fillRect(pos_x-__ANIMATE_LOGO_DELTA, pos_y, __ANIMATE_LOGO_DELTA, LOGO_B);
    drawSprite(imgAnimateLogo, pos_x, pos_y, 0, LOGO_B, LOGO_A, LOGO_B);
    break;
}
  #undefine LOGO_B
  #undefine LOGO_A
#endif
#endmacro
//------------------------------------------------------------------------------
//   void logoRunHandler(int next_screen)
// Обработчик потока выполнения логотипа
#macro logoRunHandler()
#ifdef USE_LOGO
// Введем обозначения:
//    размеры экрана    (W, H)
//    размеры логотипа  (w, h)         a = w/2    b = h/2
final int logo_a = __ANIMATE_LOGO_WIDTH/2;
final int logo_b = __ANIMATE_LOGO_HEIGHT/2;
//    шаг перемещения   d
final int logo_d = __ANIMATE_LOGO_DELTA;
//    число перемещений фрагментов     nx1, ny1, nx2, ny2
//    начальные позиции фрагментов логотипа   (x0, y0) (x0+a, y0) (x0+1, y0+b) (x0, y0+b)
// Тогда вычисляем:
//   x0 := W/2 - a;   y0 := H/2-b             (постулат)
final int logo_x0 = (SCREEN_WIDTH/2 - logo_a);
final int logo_y0 = (SCREEN_HEIGHT/2 - logo_b);
//   nx1 := (x0+a)/d + 1                      ny1 := (y0+b)/d + 1
final int logo_nx1 = (logo_x0+logo_a)/logo_d + 1;
final int logo_ny1 = (logo_y0+logo_b)/logo_d + 1;
//   x10, x20, y10, y20 - начальные координаты фрагментов
//   x10 = x0 - d*nx1                         y10 = y0 - d*ny1
final int logo_x10 = logo_x0 - logo_d*logo_nx1;
final int logo_y10 = logo_y0 - logo_d*logo_ny1;
//   nx2 := (W-x0-w)/d + 1                    ny2 := (H-y0-h)/d + 1
final int logo_nx2 = (SCREEN_WIDTH-logo_x0-2*logo_a)/logo_d;
final int logo_ny2 = (SCREEN_HEIGHT-logo_y0-2*logo_b)/logo_d;
//   x20 = x0 + a + d*nx2                     y20 = y0 + b + d*ny2
final int logo_x20 = logo_x0 + logo_a + logo_a + logo_d * logo_nx2 + 1;
#ifdef SAMSUNG_E700
final int logo_y20 = logo_y0 + logo_b + logo_b + logo_d * logo_ny2 + 2;
#elseif SAMSUNG_X600
final int logo_y20 = logo_y0 + logo_b + logo_b + logo_d * logo_ny2 + 2;
#elseif NOKIA_SERIES_40
final int logo_y20 = logo_y0 + logo_b + logo_b + logo_d * logo_ny2 + 2;
#elseif MOTOROLA_T720
final int logo_y20 = logo_y0 + logo_b + logo_b + logo_d * logo_ny2 + 2;
#elseif SONYERICSSON_T610
final int logo_y20 = logo_y0 + logo_b + logo_b + logo_d * logo_ny2 + 2;
#elseif SIEMENS_55
final int logo_y20 = logo_y0 + logo_b + logo_b + logo_d * logo_ny2 + 2;
#else
final int logo_y20 = logo_y0 + logo_b + logo_b + logo_d * logo_ny2;
#endif
// теперь блок обработки
delay(10);
if (animate_step == 1) {           // 1-й фрагмент логотипа.         вниз
    if (pos_y < logo_y0)  pos_y += logo_d;
    else {  // -> 2
      animate_step++;
      pos_x = logo_x20;
      pos_y = logo_y0;
      break;
    }
  int logo_y0_step_1 = pos_y-logo_d;
  if (logo_y0_step_1 < 0) logo_y0_step_1 = 0;
  repaint(pos_x, logo_y0_step_1, logo_a, logo_b+logo_d);
  break;
} else if (animate_step == 2) {    // 2-й фрагмент логотипа.         влево
  if (pos_x > logo_x0+logo_a)  pos_x -= logo_d;
  else {    // -> 3
    animate_step++;
    pos_x = logo_x0+logo_a;
    pos_y = logo_y20;
    break;
  }
  int logo_w_step_2 = logo_a+2*logo_d;
  if (pos_x-logo_d+logo_w_step_2 > SCREEN_WIDTH) logo_w_step_2 = SCREEN_WIDTH - (pos_x-logo_d);
  repaint(pos_x-logo_d, pos_y, logo_w_step_2, logo_b);
  break;
} else if (animate_step == 3) {    // 3-й фрагмент логотипа.         вверх
  if (pos_y > logo_y0+logo_b)  pos_y -= logo_d;
  else {    // -> 4
    animate_step++;
    pos_x = logo_x10;
    pos_y = logo_y0+logo_b;
    break;
  }
  int logo_h_step_3 = logo_b+2*logo_d;
  if (pos_y-logo_d+logo_h_step_3 > SCREEN_HEIGHT) logo_h_step_3 = SCREEN_HEIGHT - (pos_y-logo_d);
  repaint(pos_x, pos_y-logo_d, logo_a, logo_h_step_3);
  break;
} else if (animate_step == 4) {    // 4-й фрагмент логотипа.         вправо
  if (pos_x < logo_x0) {
    pos_x += logo_d;
    int logo_x0_step_4 = pos_x-logo_d;
    if (logo_x0_step_4 < 0) logo_x0_step_4 = 0;
    repaint(logo_x0_step_4, pos_y, logo_a+logo_d, logo_b);
    break;
  }
}
//------------------------------------------------------------------------------
#endif
#endmacro
//------------------------------------------------------------------------------
#defineblock end
