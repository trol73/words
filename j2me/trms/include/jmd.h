#ifnotdef __JMD_H__
#define   __JMD_H__
#defineblock begin
//----------------------------------------------------------------------------//
//                       Tr Java Mobile Builder v 1.5.                        //
//                         Mobile document libraries:  JMD.H                  //
//                    Copyright (c) O.A. Trifonov, 2005                       //
//                                Version 1.0                                 //
//                                                                            //
//                                                                            //
//                                                                            //
//                                                                            //
//----------------------------------------------------------------------------//
#include "jmd\main.h"
#include "jmd\colors.h"

//------------------------------------------------------------------------------
//                     СТАНДАРТНЫЕ МАКРООПРЕДЕЛЕНИЯ
//------------------------------------------------------------------------------
// макросы выравнивания
#define ALIGN_Y_NEXT         0  // элемент располагаятся с новой строки сразу за предыдущим
#define ALIGN_Y_PREV         1  // элемент располагается на одном уровне с предыдущим

//------------------------------------------------------------------------------
//                        СТАНДАРТНЫЕ ДАННЫЕ
//------------------------------------------------------------------------------
// цвет и фон текста по умолчанию
#define  DEFAULT_COLOR         CLR_BLACK
#define  DEFAULT_BACKGROUND    CLR_WHITE
//------------------------------------------------------------------------------
// самое первое описываемое действие должно быть пустым
#action action_none
  type = none
#endaction
//------------------------------------------------------------------------------
#defineblock end
#endif