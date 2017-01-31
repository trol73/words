#ifnotdef __JMD__MAIN_H__
#define   __JMD__MAIN_H__
#defineblock begin
//----------------------------------------------------------------------------//
//                       Tr Java Mobile Builder v 1.5.                        //
//                         Mobile document libraries:  MAIN.H                 //
//                    Copyright (c) O.A. Trifonov, 2005                       //
//                                Version 1.0                                 //
//                                                                            //
//                                                                            //
//                                                                            //
//                                                                            //
//----------------------------------------------------------------------------//

//------------------------------------------------------------------------------
//                            РЕСУРСЫ
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// объявляет список изображений list_images
#macro defineImages()
  #foreach list_images(index, i_name, i_file)
#image i_name
  file = i_file
#endimage
  #endforeach
#endmacro
//------------------------------------------------------------------------------
// объявляет список текстов list_texts
#macro defineTexts()
  #foreach list_texts(index, t_name, t_str)
  #text t_name
    t_str
  #endtext
  #endforeach
#endmacro
//------------------------------------------------------------------------------
//                            ЭЛЕМЕНТЫ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// insText(pos_x, pos_y, text_id, [action_id = action_none],
//         [text_color = DEFAULT_COLOR], [text_background = DEFAULT_BACKGROUND])
// вставляет текстовый элемент

#macro insText(pos_x, pos_y, text_id, action_id, text_color, text_background)
  #item_text
    x = pos_x
    y = pos_y
    text = text_id
    action = action_id
    color = text_color
    background = text_background
  #enditem
#endmacro

#macro insText(pos_x, pos_y, text_id, action_id, text_color)
  #item_text
    x = pos_x
    y = pos_y
    text = text_id
    action = action_id
    color = text_color
    background = DEFAULT_BACKGROUND
  #enditem
#endmacro

#macro insText(pos_x, pos_y, text_id, action_id)
  #item_text
    x = pos_x
    y = pos_y
    text = text_id
    action = action_id
    color = DEFAULT_COLOR
    background = DEFAULT_BACKGROUND
  #enditem
#endmacro

#macro insText(pos_x, pos_y, text_id)
  #item_text
    x = pos_x
    y = pos_y
    text = text_id
    action = action_none
    color = DEFAULT_COLOR
    background = DEFAULT_BACKGROUND
  #enditem
#endmacro
//------------------------------------------------------------------------------
// insImage(pos_x, pos_y, image_id, [action_id = action_none])
// вставляет рисунок

#macro insImage(pos_x, pos_y, image_id, action_id)
  #item_image
    x = pos_x
    y = pos_y
    image = image_id
    action = action_id
  #enditem
#endmacro

#macro insImage(pos_x, pos_y, image_id)
  #item_image
    x = pos_x
    y = pos_y
    image = image_id
    action = action_none
  #enditem
#endmacro
//------------------------------------------------------------------------------
// insButton(pos_x, pos_y, image_id, [action_id = action_none])
// вставляет кнопку (рисунок, изменяющийся при фокусировке)
#macro insButton(pos_x, pos_y, image_id, action_id)
  #item_image
    x = pos_x
    y = pos_y
    image_active = image_id 
    action = action_id
  #enditem
#endmacro

#macro insButton(pos_x, pos_y, image_id)
  #item_image
    x = pos_x
    y = pos_y
    image_active = image_id 
    action = action_none
  #enditem
#endmacro
//------------------------------------------------------------------------------
// insAnimator(pos_x, pos_y, image_id, [action_id = act_none])
// вставляет анимированный рисунок
#macro insAnimator(pos_x, pos_y, image_id, action_id)
  #item_image
    x = pos_x
    y = pos_y
    image_animate = image_id
    action = action_id
  #enditem
#endmacro

#macro insAnimator(pos_x, pos_y, image_id)
  #item_image
    x = pos_x
    y = pos_y
    image_animate = image_id
    action = action_none
  #enditem
#endmacro
//------------------------------------------------------------------------------


#defineblock end
#endif
