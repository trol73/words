#ifnotdef __MVL_UI_JAVA_TITEM_H__
#define   __MVL_UI_JAVA_TITEM_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                          User interface TItem class unit


                      Copyright (c) O.A. Trifonov, 2007-2008
                                Version 1.0.15

\*----------------------------------------------------------------------------*/
#defineblock end

 class TItem {
  public byte type;           // тип элемента
  public int options;         // битовая маска параметров элемента
  public int x, y;            // координаты элемента
  public int width, height;   // размеры элемента
  public Vector v1;           // вектор для хранения строк
  public Vector v2;           // вектор для хранения рисунков и подэлементов
  public boolean visible;     // флаг того, что элемент видими
  public int[] data;          // специфические даные элементов



  public TItem() {
    visible = true;
  }

// -------------------- общие методы ------------------------------------------
  // изменяет координаты элемента
  public final void setCoord(int aX, int aY) {
    x = aX;
    y = aY;
  }



  // изменяет размеры элемента
  public final void setSize(int aW, int aH) {
    width = aW;
    height = aH;
  }



  public final String getString() {
    if ( v1.size() > 0 )
      return (String)v1.elementAt(0);
    else
      return "";
  }



  public final String getString(int index) {
    if ( v1.size() > index )
      return (String)v1.elementAt(index);
    else
      return null;
  }



  public final void setString(String str) {
    if ( v1.size() > 0 )
      v1.setElementAt(str, 0);
    else
      v1.addElement(str);
    activate();
  }



  public final void setString(int index, String str) {
    if ( v1.size() > index )
      v1.setElementAt(str, index);
  }
  

  public final int getStringsCount() {
    return v1.size();
  }



  public final void appendString(TString str) {
    v1.addElement(str);
  }



  public final boolean isFocusable() {
    switch ( type ) {
      case _MVL_UI_ITEM_TEXT:
      case _MVL_UI_ITEM_EDITOR:
        return (options & KItemTextActive) != 0;

      case _MVL_UI_ITEM_IMAGE:
        return (options & KItemImageActive) != 0;

      case _MVL_UI_ITEM_FORM:
#ifdef ENABLE_POPUP_WINDOW
      case _MVL_UI_ITEM_WINDOW:
#endif // ENABLE_POPUP_WINDOW
        return (options & KItemFormActive) != 0;

      case _MVL_UI_ITEM_CHOICE_GROUP:
      case _MVL_UI_ITEM_BUTTON:
#ifdef ENABLE_LIST
      case _MVL_UI_ITEM_LIST:
#endif // ENABLE_LIST
        return true;
    } // switch

    return false;
  }





  public final void setColor(int color, int background) {
    switch ( type ) {
      case _MVL_UI_ITEM_TEXT:
      case _MVL_UI_ITEM_EDITOR:
        data[_MVL_UI_TEXT_OFFSET_COLOR] = color;
        data[_MVL_UI_TEXT_OFFSET_BACKGROUND] = background;
        data[_MVL_UI_TEXT_OFFSET_F_COLOR] = color;
        data[_MVL_UI_TEXT_OFFSET_F_BACKGROUND] = background;
        break;

      case _MVL_UI_ITEM_FORM:
#ifdef ENABLE_POPUP_WINDOW
      case _MVL_UI_ITEM_WINDOW:
#endif // ENABLE_POPUP_WINDOW
        data[_MVL_UI_FORM_OFFSET_BACKGROUND] = color;
        data[_MVL_UI_FORM_OFFSET_BACKGROUND_F] = background;
        break;
        
      case _MVL_UI_ITEM_LIST:
        data[_MVL_UI_LIST_OFFSET_COLOR] = color;
        data[_MVL_UI_LIST_OFFSET_BACKGROUND] = background;
        data[_MVL_UI_LIST_OFFSET_F_COLOR] = color;
        data[_MVL_UI_LIST_OFFSET_F_BACKGROUND] = background;
        break;
        
      case _MVL_UI_ITEM_SOFT_BUTTON:
        data[_MVL_UI_SOFT_BUTTON_OFFSET_COLOR] = color;
        data[_MVL_UI_SOFT_BUTTON_OFFSET_BACKGROUND] = background;
        break;
        
    }
  }



  public final void setColor(int color, int background, int colorFocus, int backgroundFocus) {
    switch ( type ) {
      case _MVL_UI_ITEM_TEXT:
      case _MVL_UI_ITEM_EDITOR:
        data[_MVL_UI_TEXT_OFFSET_COLOR] = color;
        data[_MVL_UI_TEXT_OFFSET_BACKGROUND] = background;
        data[_MVL_UI_TEXT_OFFSET_F_COLOR] = colorFocus;
        data[_MVL_UI_TEXT_OFFSET_F_BACKGROUND] = backgroundFocus;
        break;
        
      case _MVL_UI_ITEM_LIST:
        data[_MVL_UI_LIST_OFFSET_COLOR] = color;
        data[_MVL_UI_LIST_OFFSET_BACKGROUND] = background;
        data[_MVL_UI_LIST_OFFSET_F_COLOR] = colorFocus;
        data[_MVL_UI_LIST_OFFSET_F_BACKGROUND] = backgroundFocus;
        break;
    }
  }



  public final void setFontIndex(int fontIndex) {
    switch ( type ) {
      case _MVL_UI_ITEM_TEXT:
      case _MVL_UI_ITEM_EDITOR:
        data[_MVL_UI_TEXT_OFFSET_FONT] = fontIndex;
        data[_MVL_UI_TEXT_OFFSET_F_FONT] = fontIndex;
        break;
        
      case _MVL_UI_ITEM_LIST:
        data[_MVL_UI_LIST_OFFSET_FONT] = fontIndex;
        data[_MVL_UI_LIST_OFFSET_F_FONT] = fontIndex;
        break;
        
      case _MVL_UI_ITEM_SOFT_BUTTON:
        data[_MVL_UI_SOFT_BUTTON_OFFSET_FONT] = fontIndex;
        break;

    }
  }



  public final void setFontIndex(int fontIndex, int fontFocusedIndex) {
    switch ( type ) {
      case _MVL_UI_ITEM_TEXT:
      case _MVL_UI_ITEM_EDITOR:
        data[_MVL_UI_TEXT_OFFSET_FONT] = fontIndex;
        data[_MVL_UI_TEXT_OFFSET_F_FONT] = fontFocusedIndex;
        break;
        
      case _MVL_UI_ITEM_LIST:
        data[_MVL_UI_LIST_OFFSET_FONT] = fontIndex;
        data[_MVL_UI_LIST_OFFSET_F_FONT] = fontFocusedIndex;
        break;
    }
  }



  public final void setAlignment(int alignment) {
    switch ( type ) {
      case _MVL_UI_ITEM_TEXT:
      case _MVL_UI_ITEM_EDITOR:
        data[_MVL_UI_TEXT_OFFSET_ALIGN] = alignment;
        break;
      case _MVL_UI_ITEM_IMAGE:
        data[_MVL_UI_IMAGE_OFFSET_ALIGN] = alignment;
        break;

    }
  }



  public final void setInterval(int interval) {
    switch ( type ) {
      case _MVL_UI_ITEM_TEXT:
      case _MVL_UI_ITEM_EDITOR:
        data[_MVL_UI_TEXT_OFFSET_INTERVAL] = interval;
        break;
    }
  }



  public final int getSelectedItem() {
    if  ( type == _MVL_UI_ITEM_CHOICE_GROUP )
      return data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT];
    return -1;
  }



  public final void setSelectedItem(int index) {
    if  ( type == _MVL_UI_ITEM_CHOICE_GROUP )
      data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT] = index;
  }


  public final bool getItemChecked(int index) {
    if  ( type == _MVL_UI_ITEM_CHOICE_GROUP )
      return ((data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT] >> index) & 1) != 0;
    return false;
  }


  public final void setItemChecked(int index, bool val) {
    if  ( type == _MVL_UI_ITEM_CHOICE_GROUP ) {
      bool x = ((data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT] >> index) & 1) != 0;
      if ( val && !x )
        data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT] += (1 << index);
      else if ( !val && x )
        data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT] -= (1 << index);
    }
  }




  // инициализация элемента после создания или изменения параметров
  public final void activate() {
    switch ( type ) {

      case _MVL_UI_ITEM_TEXT: // ItemText
      case _MVL_UI_ITEM_EDITOR: // ItemEditor
//        int status = data[_MVL_UI_TEXT_OFFSET_STATUS];
        // если шириа не задана, она берется равной максимальной ширине строки
        if ( width == 0) {
          int mw = 0;
          for (int i = 0; i < v1.size(); i++) {
            int w = getFontStringWidth(_mvl_ui_fonts[data[_MVL_UI_TEXT_OFFSET_FONT]], (String)v1.elementAt(i));
            if ( w > mw )
              mw = w;
/*
            w = getFontStringWidth(_mvl_ui_fonts[data[_MVL_UI_TEXT_OFFSET_F_FONT]], (String)v1.elementAt(i));
            if ( w > mw )
              mw = w;
*/
            width = mw;
          if ( type == _MVL_UI_ITEM_EDITOR )
            width += 8;
          }
        } // width
//        if ( (status & _MVL_UI_TEXT_STATUS_FORMAT) != 0 )
          formatText();
        if ( height == 0 ) {
            int cnt = v1.size();
            if ( cnt == 0 )
              cnt = 1;
            height = (getFontHeight(_mvl_ui_fonts[data[_MVL_UI_TEXT_OFFSET_FONT]]) + data[_MVL_UI_TEXT_OFFSET_INTERVAL]) * cnt;
          if ( type == _MVL_UI_ITEM_EDITOR )
            height += 4;
          if ( (options & KItemTextChangeOnFocus) != 0 )
            height /= 2;
        }

//        data[_MVL_UI_TEXT_OFFSET_STATUS] = 0;
        break; // ItemText


//      case _MVL_UI_ITEM_IMAGE: // ItemImage
//        break; // ItemImage


      case _MVL_UI_ITEM_FORM: // Form
#ifdef ENABLE_POPUP_WINDOW
      case _MVL_UI_ITEM_WINDOW:
#endif // ENABLE_POPUP_WINDOW

        // вычисляем полные размеры формы
        data[_MVL_UI_FORM_OFFSET_FULL_WIDTH] = 0;
        data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT] = 0;
        for (int i = 0; i < v1.size(); i++) {
          TItem itm = getItem(i);
          itm.activate();
          if ( itm.x + itm.width >= data[_MVL_UI_FORM_OFFSET_FULL_WIDTH] )
            data[_MVL_UI_FORM_OFFSET_FULL_WIDTH] = itm.x + itm.width;
          if ( itm.y + itm.height >= data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT] )
            data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT] = itm.y + itm.height;
        }
        // сортируем элементы формы по положению их левого верхнего угла
        for (int i = 0; i < v1.size(); i++) {
          int minIndex = -1;
          TItem Ai = (TItem)v1.elementAt(i);
          for (int j = i+1; j < v1.size(); j++) {
            TItem Bj = (TItem)v1.elementAt(j);
            if ( (Bj.y < Ai.y) || ((Bj.y == Ai.y) && (Bj.x < Ai.x)) ) {
              minIndex = j;
              Ai = Bj;
            }
          }

          if ( minIndex > 0 ) {
            v1.removeElementAt(minIndex);
            v1.insertElementAt(Ai, i);
          }
        }

        // вычисляем индексы первого и последнего видимых элементов и индекс сфокусированного элемента
        if ( (options & KItemFormScrollV) != 0) {
          // вычисляем высоту формы
          data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT] += 15;
          data[_MVL_UI_FORM_OFFSET_SCROLL_DY] = getScreenHeight()/12;
          formCalcVisibleIndexes();
        } else if ( (options & KItemFormScrollH) != 0) {
          // вычисляем высоту формы
          data[_MVL_UI_FORM_OFFSET_FULL_WIDTH] += 10;
          data[_MVL_UI_FORM_OFFSET_SCROLL_DX] = getScreenWidth()/10;
          formCalcVisibleIndexes();
        } else {
          data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] = 0;
          data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE] = v1.size()-1;
          focusFormItem(-1);
          for (int i = 0; i < v1.size(); i++) {
            TItem itm = getItem(i);
            if ( itm.isFocusable() ) {
              focusFormItem(i);
              break;
            }
          }
        }
        
        // фокусируем первый фокусируемый элемент
        if ( data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] >= 0 )
          for (int i = data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE]; i <= data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE]; i++) {
            TItem itm = getItem(i);
            if ( itm.isFocusable() ) {
              focusFormItem(i);
              break;
            }
          }



#ifdef ENABLE_POPUP_WINDOW
        // вычисление позиции при использовании якоря для окон
        if ( type == _MVL_UI_ITEM_WINDOW ) {
          int anchor = data[_MVL_UI_WINDOW_OFFSET_ANCHOR];
          if ( (anchor & KAnchorRight) != 0 ) {
            x -= width;
          } else if ( (anchor & KAnchorHCenter) != 0 ) {
            x -= width/2;
          }
          if ( (anchor & KAnchorBottom) != 0 ) {
            y -= height;
          } else if ( (anchor & KAnchorVCenter) != 0 ) {
            y -= height/2;
          }
          data[_MVL_UI_WINDOW_OFFSET_ANCHOR] = 0;
        }
#endif // ENABLE_POPUP_WINDOW
        break; // Form


        case _MVL_UI_ITEM_CHOICE_GROUP: // ChoiceGroup
          boolean calcWidth = false;
          if ( width == 0 ) {
            calcWidth = true;
            for (int i = 0; i < v1.size(); i++) {
              int w = getFontStringWidth(_mvl_ui_fonts[data[_MVL_UI_CHOICE_GROUP_OFFSET_FONT]], (String)v1.elementAt(i));
              if ( w > width )
                width = w;
            }
          }
          if ( (options & (KChoiceRadioBox | KChoiceCheckBox)) != 0 ) {
            if ( height == 0 )
              height = (getFontHeight(_mvl_ui_fonts[data[_MVL_UI_CHOICE_GROUP_OFFSET_FONT]]) + 2) * v1.size();
            if ( calcWidth )
              width += 15;
          } else if ( (options & KChoiceComboBox) != 0 ) {
            if ( height == 0 )
              height = (getFontHeight(_mvl_ui_fonts[data[_MVL_UI_CHOICE_GROUP_OFFSET_FONT]]) + 2) + 4;
            if ( calcWidth )
              width += height + 5;
          }
          break;  // ChoiceGroup


        case _MVL_UI_ITEM_BUTTON: // Button
          if ( width == 0 )
            width = getFontStringWidth(_mvl_ui_fonts[data[_MVL_UI_BUTTON_OFFSET_FONT]], (String)v1.elementAt(0)) + 10;
          if ( height == 0 )
            height = getFontHeight(_mvl_ui_fonts[data[_MVL_UI_BUTTON_OFFSET_FONT]]) + 6;
          break; // Button


        case _MVL_UI_ITEM_SOFT_BUTTON: // ItemSoftButton
          width = getFontStringWidth(_mvl_ui_fonts[data[_MVL_UI_SOFT_BUTTON_OFFSET_FONT]], (String)v1.elementAt(0));
          height = getFontHeight(_mvl_ui_fonts[data[_MVL_UI_SOFT_BUTTON_OFFSET_FONT]]);
          if ( ( options & KItemSoftButtonLeft ) != 0 ) {
            x = 2;
          } else if ( ( options & KItemSoftButtonRight ) != 0 ) {
            x = getScreenWidth() - width - 2;
          } else if ( ( options & KItemSoftButtonCenter ) != 0 ) {
            x = ( getScreenWidth() - width ) / 2;
          }
          y = getScreenHeight() - height;
          break;


        case _MVL_UI_ITEM_SCROLLBAR: // ScrollBar
          TItem form = (TItem)v1.elementAt(0);
          // вычисление размеров скроллбара
          if ( width == 0 ) {
            if ( (options & KScrollBarVertical) != 0 )
              width = 6;
            else
              width = form.width;
          }
          if ( height == 0 ) {
            if ( (options & KScrollBarVertical) != 0 )
              height = form.height;
            else
              height = 6;
          }
          // вычисление размеров бегунка
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//          data[_MVL_UI_SCROLLBAR_OFFSET_SIZE] =  100; ///////////////////// !!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
          // вычисление цветов градиента
          int r = data[_MVL_UI_SCROLLBAR_OFFSET_COLOR] & 0xFF;
          int g = (data[_MVL_UI_SCROLLBAR_OFFSET_COLOR] >> 8) & 0xFF;
          int b = (data[_MVL_UI_SCROLLBAR_OFFSET_COLOR] >> 16) & 0xFF;
          r = 16*r/10;
          g = 16*g/10;
          b = 16*b/10;
          if ( r > 0xFF )
            r = 0xFF;
          if ( g > 0xFF )
            g = 0xFF;
          if ( b > 0xFF )
            b = 0xFF;
          data[_MVL_UI_SCROLLBAR_OFFSET_COLOR_1] = r + (g << 8) + (b << 16);
          r = r >> 1;
          g = g >> 1;
          b = b >> 1;
          data[_MVL_UI_SCROLLBAR_OFFSET_COLOR_2] = r + (g << 8) + (b << 16);
          // градиент фона
          r = data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND] & 0xFF;
          g = (data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND] >> 8) & 0xFF;
          b = (data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND] >> 16) & 0xFF;
          for (int i = 0; i < 4; i++) {
            if ( i > 0 ) {
              r = 16*r/10;
              g = 16*g/10;
              b = 16*b/10;
            }
            if ( r > 0xFF )
              r = 0xFF;
            if ( g > 0xFF )
              g = 0xFF;
            if ( b > 0xFF )
              b = 0xFF;
            data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_1+i] = r + (g << 8) + (b << 16);
          }
          // размер бегунка
#ifdef ENABLE_POPUP_WINDOW
          if ( form.type == _MVL_UI_ITEM_FORM || form.type == _MVL_UI_ITEM_WINDOW) {
#else
          if ( form.type == _MVL_UI_ITEM_FORM ) {
#endif // ENABLE_POPUP_WINDOW
            if ( form.height >= form.data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT] )
              data[_MVL_UI_SCROLLBAR_OFFSET_SIZE] = 0;
            else
              data[_MVL_UI_SCROLLBAR_OFFSET_SIZE] = (( (options & KScrollBarVertical ) != 0 ) ? height-2 : width-2)*form.height/form.data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT];
#ifdef ENABLE_LIST
          } else if ( form.type == _MVL_UI_ITEM_LIST ) {

            int interval = getFontHeight(_mvl_ui_fonts[form.data[_MVL_UI_LIST_OFFSET_FONT]] ) + 1;
            if ( form.data[_MVL_UI_LIST_OFFSET_ICON_H]+2 > interval )
              interval = form.data[_MVL_UI_LIST_OFFSET_ICON_H] + 2;
            int cnt = (form.v1.size() > form.v2.size()) ? form.v1.size() : form.v2.size();

            if ( form.height >= cnt*interval )
              data[_MVL_UI_SCROLLBAR_OFFSET_SIZE] = 0;
            else
              data[_MVL_UI_SCROLLBAR_OFFSET_SIZE] = (( (options & KScrollBarVertical ) != 0 ) ? height-2 : width-2)*form.height/(cnt*interval);
#endif // ENABLE_LIST
          }
          break; // ScrollBar


#ifdef ENABLE_POPUP_WINDOW
        case _MVL_UI_ITEM_MENU_WINDOW:  // ItemMenuWindw
          // вычисление размеров окна
          height = 0;
          width = 0;
          boolean checked = false;
          boolean submenu = false;
          for (int i = 0; i < v1.size(); i++) {
            int w = getFontStringWidth(_mvl_ui_fonts[data[_MVL_UI_MENU_WINDOW_OFFSET_FONT]], (String)v1.elementAt(i));
            if ( w > width )
              width = w;
            if ( !((String)v1.elementAt(i)).equals("-") )
              height += getFontHeight(_mvl_ui_fonts[data[_MVL_UI_MENU_WINDOW_OFFSET_FONT]]);
            else
              height += 6;
//            height ++;   // межстрочное расстояние
            if ( v2.elementAt(i*2) != null )
              submenu = true;
            if ( v2.elementAt(i*2+1) != null )
              checked = true;
          } // for
          width += 10;
          height += 6;
          if ( (options & KMenuWindowRadio) != 0 || checked )
            width += 16;
          else if ( submenu )
            width += 12;
          // вычисление позиции при использовании якоря
          int anchor = data[_MVL_UI_MENU_WINDOW_OFFSET_ANCHOR];
          if ( (anchor & KAnchorRight) != 0 ) {
            x -= width;
          } else if ( (anchor & KAnchorHCenter) != 0 ) {
            x -= width/2;
          }
          if ( (anchor & KAnchorBottom) != 0 ) {
            y -= height;
          } else if ( (anchor & KAnchorVCenter) != 0 ) {
            y -= height/2;
          }
          data[_MVL_UI_MENU_WINDOW_OFFSET_ANCHOR] = 0;
          break;
#endif  // ENABLE_POPUP_WINDOW

#ifdef ENABLE_LIST
        case _MVL_UI_ITEM_LIST:
          // вычисление размеров иконок
          data[_MVL_UI_LIST_OFFSET_ICON_W] = 0;
          data[_MVL_UI_LIST_OFFSET_ICON_H] = 0;
          data[_MVL_UI_LIST_OFFSET_TOP_LINE] = 0;
          data[_MVL_UI_LIST_OFFSET_ACTIVE] = 0;
          for (int i = 0; i < v2.size(); i++) {
            Image img = (Image)v2.elementAt(i);
            if ( img != null ) {
              if ( img.getWidth() > data[_MVL_UI_LIST_OFFSET_ICON_W] )
                data[_MVL_UI_LIST_OFFSET_ICON_W] = img.getWidth();
              if ( img.getHeight() > data[_MVL_UI_LIST_OFFSET_ICON_H] )
                data[_MVL_UI_LIST_OFFSET_ICON_H] = img.getHeight();
            }
          }
          // +++++
          int interval = getFontHeight(_mvl_ui_fonts[data[_MVL_UI_LIST_OFFSET_FONT]]) + 1;
          if ( data[_MVL_UI_LIST_OFFSET_ICON_H]+2 > interval )
            interval = data[_MVL_UI_LIST_OFFSET_ICON_H] + 2;
          data[_MVL_UI_LIST_OFFSET_INTERVAL] = interval;
          data[_MVL_UI_LIST_OFFSET_VISIBLE_LINES] = height / interval;
          // +++++
          
          listVerifyAnimate();
          break;
#endif // ENABLE_LIST


    } // switch
  }




  public final void draw(Graphics g, boolean focused, int areaX, int areaY, int areaWidth, int areaHeight) {
    int x0, y0;
    int align;
    int anchor;
    int cnt;
    int color, background;
    Image img;

    int cx = x;
    int cy = y;
    int cw = width;
    int ch = height;

    if ( cx < areaX ) {
      cx += areaX-x;
      cw -= areaX-x;
    }
    if ( cx + cw > areaX + areaWidth )
      cw = areaX + areaWidth - cx;

    if ( cy < areaY ) {
      cy += areaY-y;
      ch -= areaY-y;
    }
    if ( cy + ch > areaY + areaHeight )
      ch = areaY + areaHeight - cy;

    setClip(cx, cy, cw, ch);

    switch ( type ) {
      case _MVL_UI_ITEM_EDITOR: // ItemEditor
      case _MVL_UI_ITEM_TEXT:   // ItemText
        TFont fnt;
        int interval;
        // тест сфокусирован
        if ( focused ) {
          color = data[_MVL_UI_TEXT_OFFSET_F_COLOR];
          background = data[_MVL_UI_TEXT_OFFSET_F_BACKGROUND];
          fnt = _mvl_ui_fonts[data[_MVL_UI_TEXT_OFFSET_F_FONT]];
          setFontUnderlined(fnt, (options & KItemTextUnderlinedOnFocus) != 0);
        } else {
          color = data[_MVL_UI_TEXT_OFFSET_COLOR];
          background = data[_MVL_UI_TEXT_OFFSET_BACKGROUND];
          fnt = _mvl_ui_fonts[data[_MVL_UI_TEXT_OFFSET_FONT]];
          setFontUnderlined(fnt, (options & KItemTextUnderlined) != 0);
        }

        if ( background != 0xFFFFFFFF ) {
          setFillColor(background);
          if ( type == _MVL_UI_ITEM_TEXT && (options & KItemTextNoSquare) != 0 ) {
            int fh = getFontHeight(fnt);
            if ( v1.size() == 1 ) {
              fillRect(x+data[_MVL_UI_TEXT_DELTA_FIRST], y, width-data[_MVL_UI_TEXT_DELTA_FIRST]-data[_MVL_UI_TEXT_DELTA_LAST], fh);
            } else if ( v1.size() == 2 ) {
              fillRect(x+data[_MVL_UI_TEXT_DELTA_FIRST], y, width-data[_MVL_UI_TEXT_DELTA_FIRST], fh);
              fillRect(x, y+height-fh, width-data[_MVL_UI_TEXT_DELTA_LAST], fh);
            } else {
              fillRect(x+data[_MVL_UI_TEXT_DELTA_FIRST], y, width-data[_MVL_UI_TEXT_DELTA_FIRST], fh);
              fillRect(x, y+fh, width, height-2*fh);
              fillRect(x, y+height-fh, width-data[_MVL_UI_TEXT_DELTA_LAST], fh);
            }
          } else {
            fillRect(x, y, width, height);
          }
        }
        setFont(fnt);
        if ( type == _MVL_UI_ITEM_EDITOR ) {
          x += 4;
          width -= 3;
          y += 2;
          height --;
        }
        setTextColor(color);
        // несфокусирован
        interval = getFontHeight(fnt) + data[_MVL_UI_TEXT_OFFSET_INTERVAL];
        align = data[_MVL_UI_TEXT_OFFSET_ALIGN];
        if ( (align & KAlignRight) != 0) {
          anchor = KAnchorRight | KAnchorTop;
          x0 = x+width;
        } else if ( (align & KAlignHCenter) != 0) {
          anchor = KAnchorHCenter | KAnchorTop;
          x0 = x+width/2;
        } else {
          x0 = x;
          anchor = KAnchorLeft | KAnchorTop;
        }
        int len = ( (options & KItemTextChangeOnFocus) == 0 ) ? v1.size() : 1;
        if ( (align & KAlignBottom) != 0 )
          y0 = y + height - interval*len;
        else if ( (align & KAlignVCenter) != 0)
          y0 = y + (height - interval*len)/2;
        else
          y0 = y;
          
        boolean floating = type == _MVL_UI_ITEM_TEXT && (options & KItemTextNoSquare) != 0;
        if ( (options & KItemTextChangeOnFocus) == 0 ) {
          if ( type == _MVL_UI_ITEM_EDITOR && ((data[_MVL_UI_EDITOR_OFFSET_TEXT_TYPE] & KTextTypePassword) != 0)) {
            TString asterixStr = "";
            int asterixLen = ((String)v1.elementAt(0)).length();
            for (int ai = 0; ai < asterixLen; ai++)
              asterixStr += '*';
            drawString(asterixStr, x0, y0, anchor);
          } else
            for ( int i = 0; i < v1.size(); i++ )
              drawString((String)v1.elementAt(i), (floating && i == 0) ? x0+data[_MVL_UI_TEXT_DELTA_FIRST] :x0, y0 + i*interval, anchor);
        } else
          drawString((String)v1.elementAt(focused ? 1 : 0), floating ? x0+data[_MVL_UI_TEXT_DELTA_FIRST] : x0, y0, anchor);
        if ( type == _MVL_UI_ITEM_EDITOR ) {
          x -= 4;
          width += 3;
          y -= 2;
          height ++;

          setLineColor(_mvl_ui_items_frame_color_1);
          drawRect(x, y, width-1, height-1);
          setLineColor(_mvl_ui_items_frame_color_2);
          drawHLine(x+1, y+1, x+width-2);
          drawVLine(x+1, y+1, y+height-2);
        }

        if ( (options & KItemTextActiveFrame) != 0 && focused )
          _mvl_gui_drawSelectorFrameArea(g, x, y, width, height, areaX, areaY, areaWidth, areaHeight);

        break; // ItemText


      case _MVL_UI_ITEM_IMAGE: // ItemImage
        img = (Image)v2.elementAt(0);
        if ( (options & KItemImageDouble) != 0 ) {
          if ( !focused )
            drawImageRegion(img, 0, 0, width, height, x, y);
           else
            drawImageRegion(img, (data[_MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_W]-1)*width, (data[_MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_H]-1)*height, width, height, x, y);
        } else if ( (options & KItemImageAnimated) != 0 ) {
          x0 = (data[_MVL_UI_IMAGE_OFFSET_ANIMATE_FRAME] % data[_MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_W]) * width;
          y0 = (data[_MVL_UI_IMAGE_OFFSET_ANIMATE_FRAME] / data[_MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_W]) * height;
          drawImageRegion(img, x0, y0, width, height, x, y);
        } else {
          drawImage(img, x, y);
        }

        if ( (options & KItemImageActiveFrame) != 0 && focused )
          _mvl_gui_drawSelectorFrameArea(g, x, y, width, height, areaX, areaY, areaWidth, areaHeight);
//          _mvl_gui_drawSelectorFrame(g, x, y, width, height);
        break; // ItemImage


      case _MVL_UI_ITEM_FORM: // Form
#ifdef ENABLE_POPUP_WINDOW
      case _MVL_UI_ITEM_WINDOW:
#endif // ENABLE_POPUP_WINDOW
        // если форма имеет непрозрачный фон, рисуем его
        setClip(x, y, width, height);
        if ( focused ) {
          if ( data[_MVL_UI_FORM_OFFSET_BACKGROUND_F] != 0xFFFFFFFF ) {
            setFillColor(data[_MVL_UI_FORM_OFFSET_BACKGROUND_F]);
            fillRect(x, y, width, height);
          }
        } else {
          if ( data[_MVL_UI_FORM_OFFSET_BACKGROUND] != 0xFFFFFFFF ) {
            setFillColor(data[_MVL_UI_FORM_OFFSET_BACKGROUND]);
            fillRect(x, y, width, height);
          }
        }
        translateCoord(x-data[_MVL_UI_FORM_OFFSET_START_POS_X], y-data[_MVL_UI_FORM_OFFSET_START_POS_Y]);
        if ( data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] >= 0 )
          for (int i = data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE]; i <= data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE]; i++) {
            if ( i < v1.size() )
              getItem(i).draw(g, focused && i==data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX], data[_MVL_UI_FORM_OFFSET_START_POS_X], data[_MVL_UI_FORM_OFFSET_START_POS_Y], width, height);
          }
        translateCoord(data[_MVL_UI_FORM_OFFSET_START_POS_X]-x, data[_MVL_UI_FORM_OFFSET_START_POS_Y]-y);
        if ( type == _MVL_UI_ITEM_WINDOW ) {
          if ( (options & KItemWindowNoFrame) == 0 ) {
            setLineColor(0xDDDDDD);
            setClip(x-1, y-1, width+3, height+3);
            drawHLine(x, y, x+width-1);
            drawVLine(x, y, y+height-1);
            setLineColor(0x333333);
            drawHLine(x, y+height, x+width-1);
            drawVLine(x+width, y+1, y+height);
            setLineColor(0x444444);
            drawHLine(x+2, y+height+1, x+width);
            drawVLine(x+width+1, y+2, y+height+1);
          }
        }
        break; // Form



      case _MVL_UI_ITEM_CHOICE_GROUP: // ChoiceGroup
        if ( focused ) {
          color = data[_MVL_UI_CHOICE_GROUP_OFFSET_F_COLOR];
          background = data[_MVL_UI_CHOICE_GROUP_OFFSET_F_BACKGROUND];
          fnt = _mvl_ui_fonts[data[_MVL_UI_CHOICE_GROUP_OFFSET_F_FONT]];
        } else {
          color = data[_MVL_UI_CHOICE_GROUP_OFFSET_COLOR];
          background = data[_MVL_UI_CHOICE_GROUP_OFFSET_BACKGROUND];
          fnt = _mvl_ui_fonts[data[_MVL_UI_CHOICE_GROUP_OFFSET_FONT]];
        }
        setFontUnderlined(fnt, false);
        setLineStyle(KLineStyleSolid);
        if ( background != 0xFFFFFFFF ) {
          setFillColor(background);
          fillRect(x, y, width, height);
        }
        setFont(fnt);


        interval = height/v1.size();

        if ( (options & KChoiceRadioBox) != 0 ) {
          x0 = getFontHeight(fnt)/2-1; // радиус круга
          for (int i = 0; i < v1.size(); i++ ) {
            setLineColor(_mvl_ui_items_frame_color_1);
            drawCircle(x + x0, y + x0 + interval*i, x0);
            setTextColor(data[_MVL_UI_CHOICE_GROUP_OFFSET_COLOR]);
            drawString((String)v1.elementAt(i), x + 2*x0 + 4, y + interval*i);
          }
          setLineColor(color);
          fillCircle(x + x0, y + x0 + interval*data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT], 3);
          if ( focused )
            _mvl_gui_drawSelectorFrameArea(g, x, y + interval*data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED], 2*x0, 2*x0, areaX, areaY, areaWidth, areaHeight);
//            _mvl_gui_drawSelectorFrame(g, x, y + interval*data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED], 2*x0, 2*x0);
          // проверяем, нет ли попытки сфокусировать невидимую строку и выставляем флаг если это так
          if  (data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] >=  0) {
            if ( (y - x0 + interval*data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] < areaY)
              || (y + x0 + interval*data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] + interval > areaY + areaHeight) )
                data[_MVL_UI_CHOICE_GROUP_OFFSET_FLAG] = 1;
            else
              data[_MVL_UI_CHOICE_GROUP_OFFSET_FLAG] = 0;
          }
        } else if ( (options & KChoiceCheckBox) != 0 ) {
          x0 = getFontHeight(fnt)-2; // сторона квадрата
          y0 = x0*2/3;   // сторона квадрата селектора
          if ( ((x0-y0) % 2) == 0 ) // чтобы квадратик селектора был всегда симметричен
            y0--;

          for (int i = 0; i < v1.size(); i++ ) {
            setLineColor(_mvl_ui_items_frame_color_1);
            drawRect(x, y + interval*i, x0, x0);
            setTextColor(data[_MVL_UI_CHOICE_GROUP_OFFSET_COLOR]);
            drawString((String)v1.elementAt(i), x + x0 + 4, y + interval*i);
            setLineColor(_mvl_ui_items_frame_color_1);
            if ( ((data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT] >> i) & 1) != 0 ) {
              setLineColor(color);
              fillRect(x+(x0-y0)/2+1, 1+y+ interval*i+(x0-y0)/2, y0, y0);
            }
          }
          if ( focused )
            _mvl_gui_drawSelectorFrameArea(g, x, y + interval*data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED], x0+1, x0+1, areaX, areaY, areaWidth, areaHeight);
//            _mvl_gui_drawSelectorFrame(g, x, y + interval*data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED], x0+1, x0+1);
          // проверяем, нет ли попытки сфокусировать невидимую строку и выставляем флаг если это так
          if  (data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] >= 0) {
            if ( (y + interval*data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] < areaY)
              || (y + x0 + interval*data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] + interval > areaY + areaHeight) )
                data[_MVL_UI_CHOICE_GROUP_OFFSET_FLAG] = 1;
            else
              data[_MVL_UI_CHOICE_GROUP_OFFSET_FLAG] = 0;
          }

        } else if ( (options & KChoiceComboBox) != 0 ) {
          setLineColor(_mvl_ui_items_frame_color_2);
          drawHLine(x+1, y+1, x+width-height-1);
          drawVLine(x+1, y+1, y+height-2);
          setLineColor(_mvl_ui_items_frame_color_1);
          drawRect(x, y, width-1, height-1);
          drawVLine(x+width-height, y, y+height);
          x0 = x+width-height+1;
          _mvl_gui_drawVolumeField(g, x0, y+1, height-2, height-2);
          y0 = (height-4)/3+1; // высота треугольника
          // ширина = 2*y0-1
          x0 += (height-2-(2*y0-1))/2;
          setFillColor(0x000000);
          for (int i = 0; i < y0; i++)
            drawHLine(x0+i, y+y0+i, x0+2*y0-1-i);
          if ( focused )
            _mvl_gui_drawSelectorFrameArea(g, x, y, width, height, areaX, areaY, areaWidth, areaHeight);
//            _mvl_gui_drawSelectorFrame(g, x, y, width, height);

          setTextColor(data[_MVL_UI_CHOICE_GROUP_OFFSET_COLOR]);
          setClip(x, y, x0-x-5, height-2);
          drawString((String)v1.elementAt(data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT]), x+4, y+2);
        }
        break;  // ChoiceGroup


      case _MVL_UI_ITEM_BUTTON: // ItemButton
        _mvl_gui_drawVolumeField(g, x+1, y+1, width-2, height-2);
        setLineColor(_mvl_ui_items_frame_color_1);
        setLineStyle(KLineStyleSolid);
        drawRect(x, y, width-1, height-1);


        if ( focused ) {
          color = data[_MVL_UI_BUTTON_OFFSET_F_COLOR];
          fnt = _mvl_ui_fonts[data[_MVL_UI_BUTTON_OFFSET_F_FONT]];
          setFontUnderlined(fnt, (options & KItemTextUnderlinedOnFocus) != 0);
        } else {
          color = data[_MVL_UI_BUTTON_OFFSET_COLOR];
          fnt = _mvl_ui_fonts[data[_MVL_UI_BUTTON_OFFSET_FONT]];
          setFontUnderlined(fnt, (options & KItemTextUnderlined) != 0);
        }

        setFont(fnt);
        setTextColor(color);
        drawString((String)v1.elementAt(0), x+width/2+2, y+height/2+1, KAnchorHCenter|KAnchorVCenter);

        if ( (options & KItemButtonActiveFrame) != 0 && focused )
          _mvl_gui_drawSelectorFrameArea(g, x, y, width, height, areaX, areaY, areaWidth, areaHeight);
//          _mvl_gui_drawSelectorFrame(g, x, y, width, height);
        break; //  ItemButton




        case _MVL_UI_ITEM_SCROLLBAR: // ItemScrollBar
          // если скроллер не требуется, закрашиваем его цветом фона формы
          TItem frm = (TItem)v1.elementAt(0);
          if ( data[_MVL_UI_SCROLLBAR_OFFSET_SIZE] <= 0 ) {
            if ( ( options & KScrollBarFillEmpty ) != 0) {
#ifdef ENABLE_POPUP_WINDOW
              if ( frm.type == _MVL_UI_ITEM_FORM || frm.type == _MVL_UI_ITEM_WINDOW)
#else
              if ( frm.type == _MVL_UI_ITEM_FORM )
#endif // ENABLE_POPUP_WINDOW
                setFillColor(frm.data[_MVL_UI_FORM_OFFSET_BACKGROUND]);
               else if ( frm.type == _MVL_UI_ITEM_LIST)
                setFillColor(frm.data[_MVL_UI_LIST_OFFSET_BACKGROUND]);
              fillRect(x, y, width, height);
            }
            break;
          }
          setLineColor(_mvl_ui_scrollbar_frame_color);
          setLineStyle(KLineStyleSolid);
          drawRect(x, y, width-1, height-1);
          if ( (options & KScrollBarNoGradientBack) != 0) {
            setFillColor(data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND]);
            fillRect(x+1, y+1, width-2, height-3);
          } else {
            // градиент фона
            if ( (options & KScrollBarVertical) != 0) {
              setLineColor(data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_1]);
              drawVLine(x+1, y+1, y+height-2);
              setLineColor(data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_2]);
              drawVLine(x+2, y+1, y+height-2);
              setLineColor(data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_3]);
              drawVLine(x+3, y+1, y+height-2);
              setFillColor(data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_4]);
              fillRect(x+4, y+1, width-5, height-2);
            } else {
              setLineColor(data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_1]);
              drawHLine(x+1, y+1, x+width-2);
              setLineColor(data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_2]);
              drawHLine(x+1, y+2, x+width-2);
              setLineColor(data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_3]);
              drawHLine(x+1, y+3, x+width-2);
              setFillColor(data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_4]);
              fillRect(x+1, y+4, width-2, height-5);
            }
          }
          x0 = 0; y0 = 0;  // !!!!!!! WARNING !!!!!!
          if ( (options & KScrollBarVertical) != 0) {
#ifdef ENABLE_POPUP_WINDOW
            if ( frm.type == _MVL_UI_ITEM_FORM || frm.type == _MVL_UI_ITEM_WINDOW) {
#else
            if ( frm.type == _MVL_UI_ITEM_FORM ) {
#endif // ENABLE_POPUP_WINDOW
              y0 = y + frm.data[_MVL_UI_FORM_OFFSET_START_POS_Y]*(height-2-data[_MVL_UI_SCROLLBAR_OFFSET_SIZE])/(frm.data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT]-frm.height);
              y0++;
              if ( (y0 + data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]) > y+height-2 )
                y0 -= (y0 + data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]) - (y+height -2);
#ifdef ENABLE_LIST
            } else {
              cnt = (frm.v1.size() > frm.v2.size()) ? frm.v1.size() : frm.v2.size();
              y0 = y + frm.data[_MVL_UI_LIST_OFFSET_INTERVAL]*frm.data[_MVL_UI_LIST_OFFSET_ACTIVE]*(height-2-data[_MVL_UI_SCROLLBAR_OFFSET_SIZE])/(cnt*frm.data[_MVL_UI_LIST_OFFSET_INTERVAL]-frm.height);
              y0++;
              if ( (y0 + data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]) > y+height-2 )
                y0 -= (y0 + data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]) - (y+height-2);
#endif // ENABLE_LIST
            }
            // бегунок
            setLineColor(data[_MVL_UI_SCROLLBAR_OFFSET_COLOR_1]);
            drawHLine(x+1, y0, x+width-2);
            drawVLine(x+1, y0, y0+data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]);
            setLineColor(data[_MVL_UI_SCROLLBAR_OFFSET_COLOR_2]);
            drawHLine(x+1, y0+data[_MVL_UI_SCROLLBAR_OFFSET_SIZE], x+width-2);
            drawVLine(x+width-2, y0+1, y0+data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]);
            setFillColor(data[_MVL_UI_SCROLLBAR_OFFSET_COLOR]);
            fillRect(x+2, y0+1, width-4, data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]-1);
          } else { // Horizontal
            // бегунок
#ifdef ENABLE_POPUP_WINDOW
            if ( frm.type == _MVL_UI_ITEM_FORM || frm.type == _MVL_UI_ITEM_WINDOW) {
#else
            if ( frm.type == _MVL_UI_ITEM_FORM ) {
#endif // ENABLE_POPUP_WINDOW
              x0 = x + frm.data[_MVL_UI_FORM_OFFSET_START_POS_Y]*(width-2-data[_MVL_UI_SCROLLBAR_OFFSET_SIZE])/(frm.data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT]-frm.height);
              x0++;
              if ( (x0 + data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]) > x+width-2 )
                x0 -= (x0 + data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]) - (x+width-2);
#ifdef ENABLE_LIST
            } else {
              cnt = (frm.v1.size() > frm.v2.size()) ? frm.v1.size() : frm.v2.size();
              x0 = x + frm.data[_MVL_UI_LIST_OFFSET_INTERVAL]*frm.data[_MVL_UI_LIST_OFFSET_ACTIVE]*(width-2-data[_MVL_UI_SCROLLBAR_OFFSET_SIZE])/(cnt*frm.data[_MVL_UI_LIST_OFFSET_INTERVAL]-frm.height);
              x0++;
              if ( (x0 + data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]) > x+width-2 )
                x0 -= (x0 + data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]) - (x+width-2);
#endif // ENABLE_LIST
            }
            setLineColor(data[_MVL_UI_SCROLLBAR_OFFSET_COLOR_1]);
            drawVLine(x0, y+1, y+height-2);
            drawHLine(x0, y+1, x0+data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]);
            setLineColor(data[_MVL_UI_SCROLLBAR_OFFSET_COLOR_2]);
            drawVLine(x0+data[_MVL_UI_SCROLLBAR_OFFSET_SIZE], y+2, y+height-2);
            drawHLine(x0+1, y+height-2, x0+data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]);
            setFillColor(data[_MVL_UI_SCROLLBAR_OFFSET_COLOR]);
            fillRect(x0+1, y+2, data[_MVL_UI_SCROLLBAR_OFFSET_SIZE]-1, height-4);
          }
          break;  // ItemScrollBar





        case _MVL_UI_ITEM_SOFT_BUTTON: // ItemSoftButton
          color = data[_MVL_UI_SOFT_BUTTON_OFFSET_COLOR];
          background = data[_MVL_UI_SOFT_BUTTON_OFFSET_BACKGROUND];
          fnt = _mvl_ui_fonts[data[_MVL_UI_SOFT_BUTTON_OFFSET_FONT]];
          int tx = g.getTranslateX();
          int ty = g.getTranslateY();
          if ( background != 0xFFFFFFFF ) {
            setFillColor(background);
            if ( ( options & KItemSoftButtonClear ) != 0 ) {
              setClip(-tx, y-ty, getScreenWidth(), height);
              fillRect(-tx, y-ty, getScreenWidth(), height);
            } else
              fillRect(x-tx, y-ty, width, height);
          }
          setFont(fnt);
          setTextColor(color);
          drawString((String)v1.elementAt(0), x-tx, y-ty);
          break;
          

          
#ifdef ENABLE_POPUP_WINDOW
          case _MVL_UI_ITEM_MENU_WINDOW:  // ItemMenuWindw
            setLineStyle(KLineStyleSolid);
            // фон окна
            setFillColor(_mvl_ui_menu_window_background);
            fillRect(x, y, width, height);
            setLineColor(_mvl_ui_menu_window_frame_color2);
            drawHLine(x, y+height-1, x+width);
            drawVLine(x+width-1, y, y+height);
            setLineColor(_mvl_ui_menu_window_frame_color1);
            drawHLine(x, y, x+width);
            drawVLine(x, y, y+height);
            // элементы
            x0 = x + 6;
            y0 = y + 3;

            for (int i = 0; i < v1.size(); i++) {
              if ( i == data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE] ) {
                fnt = _mvl_ui_fonts[data[_MVL_UI_MENU_WINDOW_OFFSET_F_FONT]];
                setFillColor(_mvl_ui_menu_window_selector_color);
                getFontHeight(fnt);
                fillRoundRect(x0-3, y0, width-6, getFontHeight(fnt), 5, 5);
              } else
                fnt = _mvl_ui_fonts[data[_MVL_UI_MENU_WINDOW_OFFSET_FONT]];
              setFontUnderlined(fnt, false);
              setFont(fnt);
              setTextColor(data[_MVL_UI_MENU_WINDOW_OFFSET_COLOR]);
              String str = (String)v1.elementAt(i);
              if ( !str.equals("-") ) {
                drawString(str, x0, y0);
                if ( v2.elementAt(2*i) != null ) {             // submenu
                  setLineColor( data[_MVL_UI_MENU_WINDOW_OFFSET_COLOR] );
                  int p0_x = x + width - 5;
                  int p0_y = y0 + (getFontHeight(fnt) + 1)/2;
                  for (int j = 0; j < getFontHeight(fnt)/2-2; j++)
                    drawVLine(p0_x-j, p0_y-j, p0_y+j);
                } else if ( v2.elementAt(2*i+1) != null ) {    // checkbox
                  setLineColor(data[_MVL_UI_MENU_WINDOW_OFFSET_COLOR]);
                  int d = getFontHeight(fnt) - 4;
                  drawRect(x+width-d-5, y0+1, d, d);
                  if ( ((Boolean)v2.elementAt(2*i+1)).booleanValue() ) {
                    fillRect(x+width-d-5+3, y0+1+3, d-5, d-5);
                  }
                } else if ( (options & KMenuWindowRadio) != 0 ) {
                  if ( data[_MVL_UI_MENU_WINDOW_OFFSET_RESULT] == i )
                    setLineColor(data[_MVL_UI_MENU_WINDOW_OFFSET_COLOR]);
                  else
                    setLineColor(0xBCE8F7);
                  int d = getFontHeight(fnt) - 1;
                  drawLine(x+width-d-2, y0+d/2, x+width-d-2+d/3, y0+d);
                  drawLine(x+width-d-2+d/3, y0+d, x+width-3, y0);
                }
                y0 += getFontHeight(fnt);

              } else {
                setLineColor(_mvl_ui_menu_window_frame_color1);
                drawHLine(x0, y0+2, x+width-5);
                setLineColor(_mvl_ui_menu_window_frame_color2);
                drawHLine(x0, y0+3, x+width-5);
                y0 += 6;
              }

            }
            break;  // ItemMenuWindw
#endif // ENABLE_POPUP_WINDOW

#ifdef ENABLE_LIST
          case _MVL_UI_ITEM_LIST:
            setFillColor(data[_MVL_UI_LIST_OFFSET_BACKGROUND]);
            fillRect(x, y, width, height);
            cnt = ( v1.size() > v2.size() ) ? v1.size() : v2.size();
            x0 = x + 2;
            if ( (options & KItemListIconText) != 0 )
              x0 += data[_MVL_UI_LIST_OFFSET_ICON_W] + 4;

            // если элемент не в фокусе, то отключаем всю анимацию
            if ( !focused )
              data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] = -1;
            else if ( data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] < 0 )
              listVerifyAnimate();
            interval = getFontHeight(_mvl_ui_fonts[data[_MVL_UI_LIST_OFFSET_FONT]]) + 1;
            data[_MVL_UI_LIST_OFFSET_VISIBLE_LINES] = cnt;

            if ( data[_MVL_UI_LIST_OFFSET_ICON_H]+2 > interval )
              interval = data[_MVL_UI_LIST_OFFSET_ICON_H] + 2;
              
            data[_MVL_UI_LIST_OFFSET_INTERVAL] = interval;

            boolean imageLeft = false;     // рисовать рисунок слева
            boolean imageRight = false;    // рисовать рисунок справа
            if ( (options & (KItemListIcon+KItemListIconText)) != 0 )
              imageLeft = true;
            else if ( (options & KItemListTextIcon) != 0 )
              imageRight = true;

            for (int i = data[_MVL_UI_LIST_OFFSET_TOP_LINE]; i < cnt; i++) {
              y0 = y + interval*(i-data[_MVL_UI_LIST_OFFSET_TOP_LINE]);
              if ( y0 > y+height-interval+2 ) {
                data[_MVL_UI_LIST_OFFSET_VISIBLE_LINES] = i - data[_MVL_UI_LIST_OFFSET_TOP_LINE];
                break;
              }

/*
              if ( y0+interval > y+height+2 )  // y+
{
                data[_MVL_UI_LIST_OFFSET_VISIBLE_LINES] = i - data[_MVL_UI_LIST_OFFSET_TOP_LINE];
System.out.println("!!!!!!");
}
else
System.out.println("=>"+(y0+interval) + " <-> " +(y+height+2));
*/

              if ( i != data[_MVL_UI_LIST_OFFSET_ACTIVE] ) {
                color = data[_MVL_UI_LIST_OFFSET_COLOR];
                fnt = _mvl_ui_fonts[data[_MVL_UI_LIST_OFFSET_FONT]];
                setFontUnderlined(fnt, (options & KItemListUnderlined) != 0);
              } else {
                color = data[_MVL_UI_LIST_OFFSET_F_COLOR];
                fnt = _mvl_ui_fonts[data[_MVL_UI_LIST_OFFSET_F_FONT]];
                setFontUnderlined(fnt, (options & KItemListUnderlinedOnFocus) != 0);
                setFillColor(data[_MVL_UI_LIST_OFFSET_F_BACKGROUND]);
                if ( focused )
                  fillRoundRect(x, y0, width, interval, 5, 5);
                else {
                  setLineStyle(KLineStyleDotted);
                  drawRoundRect(x+1, y0+1, width-2, interval-3, 5, 5);
                }
                data[_MVL_UI_LIST_OFFSET_FLAG] = ( (y0  < areaY) || (y0 + interval > areaY + areaHeight) ) ? 1 : 0;
              }
              
              if ( i >= 0 ) {
                setFont(fnt);
                String str = (String)v1.elementAt(i);
                if ( str != null ) {
                  setTextColor(color);
                  if ( i != data[_MVL_UI_LIST_OFFSET_ACTIVE] || data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] <= 0 )
                    drawString(str, x0, y0);
                  else {
                    if ( imageLeft )
                      setClip(x0, y0, width + x - x0, height);
                    else if ( imageRight )
                      setClip(x0, y0, width - data[_MVL_UI_LIST_OFFSET_ICON_W], height);
                    drawString(str, x0-data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_X], y0);
                    setClip(cx, cy, cw, ch);
                  }
                }
                img = (Image)v2.elementAt(i);
                if ( img != null ) {
                  if ( imageLeft )
                    drawImage(img, x+2, y0);
                  else if ( imageRight )
                    drawImage(img, x+width-2, y0, KAnchorTop|KAnchorRight);
                }
              
              } // if ( i >= 0 )
            } // for

            if ( focused )
              _mvl_gui_drawSelectorFrameArea(g, x, y, width, height, areaX, areaY, areaWidth, areaHeight);
//              _mvl_gui_drawSelectorFrame(g, x, y, width, height);

            break;
#endif // ENABLE_LIST


    } // switch
  }



  // вызывается во время бездействия системы. возвращает количество миллисекунд, через которое
  // элементу хотелось бы получить процессорное время в следующий раз или -1, если таковое не требуется
  public final int idle() {
    long t, t0;

    switch ( type ) {


      case _MVL_UI_ITEM_IMAGE: // ItemImage
        if ( (options & KItemImageAnimated) != 0 ) {
          t0 = (long)data[_MVL_UI_IMAGE_OFFSET_TIME_HI]*Integer.MAX_VALUE + data[_MVL_UI_IMAGE_OFFSET_TIME_LO];
          if ( t0 == 0 ) {
            t0 = getSystemTime();
            data[_MVL_UI_IMAGE_OFFSET_TIME_HI] = (int)(t0 / Integer.MAX_VALUE);
            data[_MVL_UI_IMAGE_OFFSET_TIME_LO] = (int)(t0 % Integer.MAX_VALUE);
            return data[_MVL_UI_IMAGE_OFFSET_TIME];
          }
          t = getSystemTime(t0);
          if ( t >= data[_MVL_UI_IMAGE_OFFSET_TIME] && data[_MVL_UI_IMAGE_OFFSET_TIME] >= 0 ) {
/////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            data[_MVL_UI_IMAGE_OFFSET_ANIMATE_FRAME]++;
/////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if ( data[_MVL_UI_IMAGE_OFFSET_ANIMATE_FRAME] >= data[_MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_W]*data[_MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_H])
              data[_MVL_UI_IMAGE_OFFSET_ANIMATE_FRAME] = 0;
            _mvl_ui_repaint_request = true;
            t0 = getSystemTime();
            data[_MVL_UI_IMAGE_OFFSET_TIME_HI] = (int)(t0 / Integer.MAX_VALUE);
            data[_MVL_UI_IMAGE_OFFSET_TIME_LO] = (int)(t0 % Integer.MAX_VALUE);
            return data[_MVL_UI_IMAGE_OFFSET_TIME];
          } else
            return ((int)(data[_MVL_UI_IMAGE_OFFSET_TIME]-t));
        }
        break; // ItemImage



        case _MVL_UI_ITEM_FORM: // Form
#ifdef ENABLE_POPUP_WINDOW
      case _MVL_UI_ITEM_WINDOW:
#endif // ENABLE_POPUP_WINDOW
          int min = -1;
          int val;
          // проходимся только по видимым элементам
          for (int i = data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE]; i <= data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE]; i++) {
            if ( i < 0 )
              break;
            val = getItem(i).idle();
            if ( (val >= 0) && ( (min < 0) || (val < min) ) )
              min = val;
          }
          return min; // Form

#ifdef ENABLE_LIST
        case _MVL_UI_ITEM_LIST:
          if ( data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] > 0 ) {
#define _MDL_STEP 200
            t0 = (long)data[_MVL_UI_LIST_OFFSET_ANIMATE_TIME_HI]*Integer.MAX_VALUE + data[_MVL_UI_LIST_OFFSET_ANIMATE_TIME_LO];
            if ( t0 == 0 ) {
              t0 = getSystemTime();
            data[_MVL_UI_LIST_OFFSET_ANIMATE_TIME_HI] = (int)(t0 / Integer.MAX_VALUE);
            data[_MVL_UI_LIST_OFFSET_ANIMATE_TIME_LO] = (int)(t0 % Integer.MAX_VALUE);
              return _MDL_STEP;
            }
            t = getSystemTime(t0);
            if ( t >= _MDL_STEP ) {
              data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_X] += 5;//data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_X_DELTA];
              if ( data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_X] >= data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] - width/2 )
                data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_X] = -10;
//              if ( data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_X] >= data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] || data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_X] < 0 )
//                data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_X_DELTA] = -data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_X_DELTA];

              _mvl_ui_repaint_request = true;
              t0 = getSystemTime();
              data[_MVL_UI_LIST_OFFSET_ANIMATE_TIME_HI] = (int)(t0 / Integer.MAX_VALUE);
              data[_MVL_UI_LIST_OFFSET_ANIMATE_TIME_LO] = (int)(t0 % Integer.MAX_VALUE);
              return _MDL_STEP;
            } else
              return ((int)(_MDL_STEP-t));
          }
#undefine _MDL_STEP
#endif // ENABLE_LIST

    } // switch
    return -1;
  }



  // получает код действия, время получения события и объект контейнера (или null, если
  // элемент принадлежит экрану). возвращает true, если элемент поглотил событие
  // если событие связано с удержанием клавиши, в repeated передается true.
  public final boolean actionHandler(int action, long time, TItem owner, boolean repeated) {
    String str;
    String caption;

    switch ( type ) {

      case _MVL_UI_ITEM_TEXT:
      case _MVL_UI_ITEM_IMAGE:
      case _MVL_UI_ITEM_BUTTON:
        if ( action == ACT_FIRE )
          onEvent(owner, this, EVENT_PUSH, time);
        break;

      case _MVL_UI_ITEM_EDITOR:
        if ( action == ACT_FIRE ) {
          _mvl_ui_command_item = this;
          _mvl_ui_command_item_owner = owner;
          str = "";
          for (int i = 0; i < v1.size(); i++) {
            str += (String)v1.elementAt(i);
            if ( i != v1.size()-1 )
              str += '\n';
          }
          int textType = data[_MVL_UI_EDITOR_OFFSET_TEXT_TYPE];
          caption = (String)v2.elementAt(0);
          _mvl_ui_command_item = this;
          _mvl_ui_command_item_owner = owner;
          onEvent(owner, this, EVENT_BEFORE_EDIT, getSystemTime());
          if ( textType != KTextTypeDate && textType != KTextTypeTime && textType != KTextTypeDateTime ) {
            _mvl_ui_text_editor = new TextBox(caption, str, data[_MVL_UI_EDITOR_OFFSET_MAX_SIZE], textType);
            _mvl_ui_text_editor.addCommand(_mvl_ui_cmd_ok);
            _mvl_ui_text_editor.addCommand(_mvl_ui_cmd_cancel);
            _mvl_ui_text_editor.setCommandListener(_mvl_mainFrame);
            _mvl_display.setCurrent(_mvl_ui_text_editor);
          } else {
            _mvl_ui_date_form = new Form(caption);
            if ( textType == KTextTypeDate )
              textType = DateField.DATE;
            else if ( textType == KTextTypeTime )
              textType = DateField.TIME;
            else if ( textType == KTextTypeDateTime )
              textType = DateField.DATE_TIME;
            DateField df = new DateField(caption, textType);
            str = ( v1.size() > 0 ) ? (String)v1.elementAt(0) : "";
            Date date = new Date();
            long d;
            if ( str != null && str != "" ) {
              if ( textType == DateField.DATE ) {
                d = str2date(str);
                if ( d != 0 )
                  date.setTime(d);
                df.setDate(date);
              } else if ( textType == DateField.TIME ) {
                d = str2time(str);
                if ( d != 0 )
                  date.setTime(d);
                df.setDate(date);
              } else if ( textType == DateField.DATE_TIME ) {

                int i = str.indexOf(' ');
                if ( i >= 0 ) {
                  try {
                    String s1 = str.substring(0, i).trim();
                    String s2 = str.substring(i).trim();
                    d = str2date(s1);
                    long d1 = str2time(s2);
                    if ( d == 0 || d1 == 0 )
                      d = 0;
                    else
                      d += d1;
                  } catch (Exception ex) {
                    d = 0;
                  }
                  date.setTime(d);
                  df.setDate(date);
                }
              }
            }
            _mvl_ui_date_form.append(df);
            _mvl_ui_date_form.addCommand(_mvl_ui_cmd_ok);
            _mvl_ui_date_form.addCommand(_mvl_ui_cmd_cancel);
            _mvl_ui_date_form.setCommandListener(_mvl_mainFrame);
            _mvl_display.setCurrent(_mvl_ui_date_form);
          }
        }
        break;


      case _MVL_UI_ITEM_FORM:
#ifdef ENABLE_POPUP_WINDOW
      case _MVL_UI_ITEM_WINDOW:
#endif // ENABLE_POPUP_WINDOW
        // сначала пытаемся передать событие текущему элементу формы
        if ( data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] >= 0 )
          if ( (getItem(data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX])).actionHandler(action, time, this, true) )
            return true;
        switch (action) {
          case ACT_UP:
            if ( tabUp(/*!repeated || (time - _mvl_last_action_time > 500)*/ true) ) {
              repaint();
              return true;
            }
            if ( data[_MVL_UI_FORM_OFFSET_START_POS_Y] > 0 ) {
              data[_MVL_UI_FORM_OFFSET_START_POS_Y] -= data[_MVL_UI_FORM_OFFSET_SCROLL_DY];
              if ( data[_MVL_UI_FORM_OFFSET_START_POS_Y] < 0 )
                data[_MVL_UI_FORM_OFFSET_START_POS_Y] = 0;
              formCalcVisibleIndexes();
              onEvent(this, null, EVENT_SCROLL_UP, getSystemTime());
              repaint();
              return true;
            }
            
            break;
          case ACT_DOWN:
            if ( tabDown(/*!repeated || (time - _mvl_last_action_time > 500)*/ true) ) {
              repaint();
              return true;
            }
            if ( data[_MVL_UI_FORM_OFFSET_START_POS_Y] + height < data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT] ) {
              data[_MVL_UI_FORM_OFFSET_START_POS_Y] += data[_MVL_UI_FORM_OFFSET_SCROLL_DY];
              if ( data[_MVL_UI_FORM_OFFSET_START_POS_Y] + height > data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT] )
                data[_MVL_UI_FORM_OFFSET_START_POS_Y] = data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT] - height;
              formCalcVisibleIndexes();
              onEvent(this, null, EVENT_SCROLL_DOWN, getSystemTime());
              repaint();
              return true;
            }
            break;
          case ACT_LEFT:
            if ( tabFormPrev() )
              repaint();
            return true;
          case ACT_RIGHT:
            if ( tabFormNext() )
              repaint();
            return true;
          case ACT_FIRE:
            break;
        }
        break; // Form

        case _MVL_UI_ITEM_CHOICE_GROUP: // ChoiceGroup
          if ( (options & (KChoiceRadioBox+KChoiceCheckBox) ) != 0 ) {  // Radio- Checkbox
//            if ( repeated && (time - _mvl_last_action_time < 500) )
//              return true;
            if ( action == ACT_UP ) {
              if ( data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] == 0 ) {
//                data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] = 0;
                return false;
              } else {
                data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED]--;
                onEvent(owner, this, EVENT_CHANGE, getSystemTime());
                repaint();
                // если отрисовка сказала, что фокусируемая позиция не видна, то передаем событие форме
                if ( data[_MVL_UI_CHOICE_GROUP_OFFSET_FLAG] != 0 ) {
                  data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED]++;
                  return false;
                }
                return true;
              }
            } else if ( action == ACT_DOWN ) {
              if ( data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] >= v1.size()-1 ) {
                data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] = v1.size()-1;
                return false;
              } else {
                data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED]++;
                onEvent(owner, this, EVENT_CHANGE, getSystemTime());
                repaint();
                // если отрисовка сказала, что фокусируемая позиция не видна, то передаем событие форме
                if ( data[_MVL_UI_CHOICE_GROUP_OFFSET_FLAG] != 0 ) {
                  data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED]--;
                  return false;
                }
                return true;
              }
            } else if ( action == ACT_FIRE ) {
              if ( (options & KChoiceRadioBox) != 0 )               // ComboBox
                data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT] = data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED];
              else
                setItemChecked(data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED], !getItemChecked(data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED]));
              repaint();
              return true;
            } else if ( action == ACT_LEFT ) {
              // теряем фокус
              data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] = 0;
            } else if ( action == ACT_RIGHT ) {
              // теряем фокус
              data[_MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED] = v1.size()-1;
            }

//          } else if ( (options & KChoiceCheckBox) != 0 ) {
          } else if ( (options & KChoiceComboBox) != 0 ) {
            if ( action == ACT_FIRE ) {
              onEvent(owner, this, EVENT_BEFORE_EDIT, getSystemTime());
              _mvl_ui_list = new List("Выберите", List.IMPLICIT);  //////////////////// !!!!!!!!!!!!!!!!!!
              _mvl_ui_command_item = this;
              _mvl_ui_command_item_owner = owner;
              for ( int i = 0; i < v1.size(); i++)
                _mvl_ui_list.append((String)v1.elementAt(i), ((v2.size() >= v1.size()) ? (Image)v2.elementAt(i) : null));
              _mvl_ui_list.addCommand(_mvl_ui_cmd_ok);
              _mvl_ui_list.setSelectCommand(_mvl_ui_cmd_ok);
              _mvl_ui_list.addCommand(_mvl_ui_cmd_cancel);
              _mvl_ui_list.setCommandListener(_mvl_mainFrame);
              _mvl_display.setCurrent(_mvl_ui_list);
              return true;
            }
          }
          break; // ChoiceGroup



      case _MVL_UI_ITEM_SOFT_BUTTON:  // SoftButton
        if ( ( action == ACT_SOFT1 && (options & KItemSoftButtonLeft) != 0 ) ||
          ( action == ACT_SOFT2 && (options & KItemSoftButtonRight) != 0 ) ||
          ( action == ACT_SOFT3 && (options & KItemSoftButtonCenter) != 0 ) ) {
            onEvent(owner, this, EVENT_PUSH, time);
            return true;
          }
        break; // SoftButton

          
#ifdef ENABLE_POPUP_WINDOW
        case _MVL_UI_ITEM_MENU_WINDOW:
          if ( action == ACT_UP ) {
            if ( data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE] == 0 )
              data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE] = v1.size()-1;
            else
              data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE]--;
            if ( getString(data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE]).equals("-") )
              return actionHandler(action, time, owner, repeated);
            repaint();
            return true;
          } else if ( action == ACT_DOWN ) {
            if ( data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE] == v1.size()-1 )
              data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE] = 0;
            else
              data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE]++;
            if ( getString(data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE]).equals("-") )
              return actionHandler(action, time, owner, repeated);
            repaint();
            return true;
          } else if ( action == ACT_LEFT ) {
            mvlPopWindow();
            repaint();
            return true;
          } else if ( action == ACT_RIGHT ) {
            TItem submenu = (TItem)v2.elementAt(2*data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE]);
            if ( submenu != null ) {
               submenu.activate();
              // если окно умещается рядом справа, ставим рядом
              if ( x+width + 2 + submenu.width  < getScreenWidth() )
                submenu.x = x+width + 2;
              // иначе, равняем по правой границе экрана
              else
                submenu.x = getScreenWidth() - 2 - submenu.width;
              submenu.y = y+height*data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE]/v1.size() - submenu.height/2;
              if ( submenu.y < 0 )
                submenu.y = 0;
              if ( submenu.y +submenu.height > getScreenHeight() )
                submenu.y = getScreenHeight() - submenu.height - 2;
              mvlPushWindow(submenu);
              return true;
            }
          } else if ( action == ACT_FIRE ) {
            if ( v2.elementAt(data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE]*2) != null ) {           // submenu
              return actionHandler(ACT_RIGHT, time, owner, repeated);
            } else if ( v2.elementAt(data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE]*2+1) != null ) {  // checked
              Boolean b = (Boolean)v2.elementAt(data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE]*2+1);
              v2.setElementAt(new Boolean( !b.booleanValue()), data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE]*2+1);
              repaint();
              return true;
            } else if ( (options & KMenuWindowRadio) != 0 ) {
              data[_MVL_UI_MENU_WINDOW_OFFSET_RESULT] = data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE];
              repaint();
              return true;
            } else {
              onEvent(this, this, EVENT_PUSH, time);
              return true;
            }
          }
          break;
#endif

#ifdef ENABLE_LIST
        case _MVL_UI_ITEM_LIST:
          int lastIndex = ( ( v1.size() > v2.size() ) ? v1.size() : v2.size() ) - 1;
          if ( action == ACT_FIRE ) {
            onEvent(owner, this, EVENT_PUSH, time);
          } else if ( action == ACT_UP ) {
            if ( data[_MVL_UI_LIST_OFFSET_ACTIVE] == 0 ){
              if ( (options & KitemListCircular) == 0)
                return false;
              else
                mvlSetItemSelected(this, lastIndex);
            } else
              data[_MVL_UI_LIST_OFFSET_ACTIVE]--;
            if ( data[_MVL_UI_LIST_OFFSET_TOP_LINE] > data[_MVL_UI_LIST_OFFSET_ACTIVE] )
              data[_MVL_UI_LIST_OFFSET_TOP_LINE]--;
            onEvent(owner, this, EVENT_CHANGE, getSystemTime());

            listVerifyAnimate();
            
            repaint();
            // если отрисовка сказала, что фокусируемая позиция не видна, то передаем событие форме
            if ( data[_MVL_UI_LIST_OFFSET_FLAG] != 0 ) {
              data[_MVL_UI_LIST_OFFSET_ACTIVE]++;
              listVerifyAnimate();
              return false;
            }
            return true;
          } else if ( action == ACT_DOWN ) {
            if ( data[_MVL_UI_LIST_OFFSET_ACTIVE] >= lastIndex ) {
              if ( (options & KitemListCircular) == 0)
                return false;
              else
                mvlSetItemSelected(this, 0);
            } else
              data[_MVL_UI_LIST_OFFSET_ACTIVE]++;
            if ( data[_MVL_UI_LIST_OFFSET_TOP_LINE]+data[_MVL_UI_LIST_OFFSET_VISIBLE_LINES]-1 < data[_MVL_UI_LIST_OFFSET_ACTIVE] ) {
              if ( data[_MVL_UI_LIST_OFFSET_VISIBLE_LINES] + data[_MVL_UI_LIST_OFFSET_TOP_LINE] <= lastIndex ) {
                data[_MVL_UI_LIST_OFFSET_TOP_LINE]++;
              } else
                return false;
            }

            onEvent(owner, this, EVENT_CHANGE, getSystemTime());
            
            listVerifyAnimate();

            repaint();
            // если отрисовка сказала, что фокусируемая позиция не видна, то передаем событие форме
            if ( data[_MVL_UI_LIST_OFFSET_FLAG] != 0 ) {
              data[_MVL_UI_LIST_OFFSET_ACTIVE]--;
              listVerifyAnimate();
              return false;
            }
            return true;
          }
          break;
#endif // ENABLE_LIST

    }
    return false;
  }


/*
  // получает код нажатой клавиши, время получения события и объект контейнера (или null, если
  // элемент принадлежит экрану). возвращает true, если элемент поглотил событие
  // если событие связано с удержанием клавиши, в repeated передается true.
  public final boolean actionKeyHandler(int keyCode, long time, TItem owner, boolean repeated) {
    switch ( type ) {

      case _MVL_UI_ITEM_SOFT_BUTTON:
        if ( keyCode ==  )
        break;
    }
    return false;
  }
*/



  public final void commandHandler(Command cmd, Displayable d) {
    switch ( type ) {
      case _MVL_UI_ITEM_EDITOR:  // ItemEditor
        if ( d.equals(_mvl_ui_text_editor) ) {
          if ( cmd != _mvl_ui_cmd_cancel ) {
            v1.removeAllElements();
            v1.addElement(_mvl_ui_text_editor.getString());
            formatText();
            onEvent(_mvl_ui_command_item_owner, this, EVENT_AFTER_EDIT, getSystemTime());
          }
          _mvl_display.setCurrent(_mvl_mainFrame);
          repaint();
        } else if ( d.equals(_mvl_ui_date_form) ) {
          if ( cmd != _mvl_ui_cmd_cancel ) {
            onEvent(_mvl_ui_command_item_owner, this, EVENT_AFTER_EDIT, getSystemTime());
            v1.removeAllElements();
            DateField df = (DateField)_mvl_ui_date_form.get(0);
            long t = df.getDate().getTime();
            if ( df.getInputMode() == DateField.DATE )
              v1.addElement(date2str(t));
            else if ( df.getInputMode() == DateField.TIME )
              v1.addElement(time2str(t));
            else {
              Calendar c = Calendar.getInstance();
              c.setTime(new Date(t));
              String res = "" + c.get(Calendar.DAY_OF_MONTH)+"."+c.get(Calendar.MONTH)+"."+c.get(Calendar.YEAR);
              long t2 = t - str2date(res);
              long t1 = t - t2;
              v1.addElement(date2str(t1)+" "+time2str(t2));
            }
          }
          _mvl_display.setCurrent(_mvl_mainFrame);
          repaint();
        }
        break; // ItemEditor



        case _MVL_UI_ITEM_CHOICE_GROUP: // ItemChoiceGroup
          if ( (options & KChoiceComboBox) != 0 ) {
            if ( cmd.equals(_mvl_ui_cmd_ok)  ) {
              data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT] = _mvl_ui_list.getSelectedIndex();
              onEvent(_mvl_ui_command_item_owner, this, EVENT_AFTER_EDIT, getSystemTime());
              _mvl_display.setCurrent(_mvl_mainFrame);
              repaint();
            }
            if ( cmd.equals(_mvl_ui_cmd_cancel) ) {
              _mvl_display.setCurrent(_mvl_mainFrame);
              repaint();
            }
          }
          break; // ItemChoiceGroup
    }
  }
// --------------------------- ItemText ---------------------------------------
  // создание текстового элемента известных размеров со строкой
  public final void createItemText(int aX, int aY, int aW, int aH, String aStr, int aOptions) {
    type = _MVL_UI_ITEM_TEXT;
    data = new int[_MVL_UI_TEXT_DATA_LENGTH];
    options = aOptions;
    v1 = new Vector();
    v1.addElement(aStr);
    x = aX;
    y = aY;
    width = aW;
    height = aH;
//    data[_MVL_UI_TEXT_OFFSET_STATUS] = _MVL_UI_TEXT_STATUS_FORMAT;
    data[_MVL_UI_TEXT_OFFSET_BACKGROUND] = 0xFFFFFFFF;
    data[_MVL_UI_TEXT_OFFSET_F_BACKGROUND] = 0xFFFFFFFF;
  }



  // создание текстового элемента из строки и установка его размеров в минимальные
  public final void createItemText(int aX, int aY, String aStr, int aOptions) {
    type = _MVL_UI_ITEM_TEXT;
    data = new int[_MVL_UI_TEXT_DATA_LENGTH];
    options = aOptions;
    v1 = new Vector();
    v1.addElement(aStr);
    x = aX;
    y = aY;
    width = 0;
    height = 0;
//    data[_MVL_UI_TEXT_OFFSET_STATUS] = _MVL_UI_TEXT_STATUS_FORMAT;
  }



  public final void formatText() {
    if ( (options & KItemTextNoWrap) != 0 )
      return;
    if ( type == _MVL_UI_ITEM_EDITOR )
      width -= 7;
    Vector tmp = new Vector();
    String delims = "| ";
    String deleteIt = "|";
    TFont fnt = _mvl_ui_fonts[data[_MVL_UI_TEXT_OFFSET_FONT]];
    boolean floating = type == _MVL_UI_ITEM_TEXT && (options & KItemTextNoSquare) != 0;
    for (int i = 0; i < v1.size(); i++) {
      String str = (String)v1.elementAt(i);
      if ( (options & KItemTextSyllableWrap) != 0 )
        str = stringSyllableAnalyse(str, '|');
      if ( floating && (i == 0) )
        formatString(str, tmp, width, width-data[_MVL_UI_TEXT_DELTA_FIRST], delims, fnt);
      else
        formatString(str, tmp, width, 0, delims, fnt);
    }
    if ( type == _MVL_UI_ITEM_EDITOR )
      width += 7;
    v1 = tmp;
    for (int i = 0; i < v1.size(); i++)
      v1.setElementAt(deleteCharFromString((String)v1.elementAt(i), deleteIt), i);
    if ( floating ) {
      if ( v1.size() > 1 )
        data[_MVL_UI_TEXT_DELTA_LAST] = width-getFontStringWidth(fnt, (String)v1.elementAt(v1.size()-1));
      else
        data[_MVL_UI_TEXT_DELTA_LAST] = width-getFontStringWidth(fnt, (String)v1.elementAt(v1.size()-1))-data[_MVL_UI_TEXT_DELTA_FIRST];
      if ( data[_MVL_UI_TEXT_DELTA_LAST] < 0 )
        data[_MVL_UI_TEXT_DELTA_LAST] = 0;
    }
  }
// --------------------------- ItemImage --------------------------------------
  public final void createItemImage(int aX, int aY, TImage aImg, int aOptions) {
    type = _MVL_UI_ITEM_IMAGE;
    data = new int[_MVL_UI_IMAGE_DATA_LENGTH];
    options = aOptions;
    v2 = new Vector();
    v2.addElement(aImg);
    x = aX;
    y = aY;
    data[_MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_W] = 1;
    data[_MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_H] = 1;

    if ( (options & KItemImageDouble) != 0 ) {
      width = aImg.getWidth();
      height = aImg.getHeight()/2;
      data[_MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_H] = 2;
    } else {
      width = aImg.getWidth();
      height = aImg.getHeight();
    }
  }



  public final void createItemImage(int aX, int aY, int aWidth, int aHeight, TImage aImg, int aOptions) {
    type = _MVL_UI_ITEM_IMAGE;
    data = new int[_MVL_UI_IMAGE_DATA_LENGTH];
    options = aOptions;
    v2 = new Vector();
    v2.addElement(aImg);
    x = aX;
    y = aY;
    width = aWidth;
    height = aHeight;
    data[_MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_W] = aImg.getWidth()/width;
    data[_MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_H] = aImg.getHeight()/height;
  }


  public final void setTime(int time) {
    switch ( type ) {
      case _MVL_UI_ITEM_IMAGE: // ItemImage
        data[_MVL_UI_IMAGE_OFFSET_TIME] = time;
        break;  // ItemImage
    }

  }
  
  
  public final void setImageFrame(int index) {
    switch ( type ) {
      case _MVL_UI_ITEM_IMAGE: // ItemImage
        data[_MVL_UI_IMAGE_OFFSET_ANIMATE_FRAME] = index;
        break;  // ItemImage
    }

  }

// --------------------------- ItemForm ---------------------------------------
  public final void createItemForm(int aX, int aY, int aWidth, int aHeight, int aOptions) {
    type = _MVL_UI_ITEM_FORM;
    x = aX;
    y = aY;
    width = aWidth;
    height = aHeight;
    options = aOptions;
    v1 = new Vector();
    data = new int[_MVL_UI_FORM_DATA_LENGTH];
    data[_MVL_UI_FORM_OFFSET_BACKGROUND] = 0xFFFFFFFF;
    data[_MVL_UI_FORM_OFFSET_BACKGROUND_F] = 0xFFFFFFFF;
  }



  public final void appendItem(TItem item) {
    v1.addElement(item);
  }
  
  
  
  public final void deleteItem(TItem item) {
    v1.removeElement(item);
  }



  // пытается выполнить табуляцию на следующий элемент, находящийся в пределах экрана
  // возвращает true, если попытка удалась (т.е. в видимой части экрана имеется хотя бы один
  // активный элемент)
  public final boolean tabFormNext() {
    // если на экране ничего не видно, то выходим
    if ( data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] < 0 )
      return false;
    // получаем текущий активный элемент
    int i = data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX];
    // проходимся по всем элементам, которые видно на экране и ищем активный
    while ( ++i <= data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE] )
      if ( getItem(i).isFocusable() )
        break;
    // если таковой найден, то ...
    if ( (i <= data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE]) && getItem(i).isFocusable() ) {
      // .. устанавливаем его в активный
      focusFormItem(i);
      // иначе, если текущий активный элемент страницы находится после первого видимого элемента
      // (это условие нужно для предотвращения рекурсивного зацикливания)
    } else if ( data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] > data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] ){
      // делаем активным элемент, предшевствующий первому и свершаем рекурсию
      focusFormItem(data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] - 1);
      return tabFormNext();
    }
    // если полученный элемент не находится на экране, то снимаем с него активность
      if ( data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] < data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] ) {
        focusFormItem(-1);
        return false;
      }
      return true;
  }



  // пытается выполнить табуляцию на предыдущий элемент, находящийся в пределах экрана
  // возвращает true, если попытка удалась (т.е. в видимой части экрана имеется хотя бы один
  // активный элемент)
  public final boolean tabFormPrev() {
    // если на экране ничего не видно, то выходим
    if ( data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] < 0 )
      return false;
    // получаем текущий активный элемент
    int i = data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX];
    // проходимся по всем элементам, которые видно на экране и ищем активный
    while ( --i >= data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] )
      if ( getItem(i).isFocusable() )
        break;

    // если таковой найден, то ...
    if ( (i >= data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE]) && getItem(i).isFocusable() ) {
      // .. устанавливаем его в активный
      focusFormItem(i);
      // иначе, если текущий активный элемент страницы находится после первого видимого элемента
      // (это условие нужно для предотвращения рекурсивного зацикливания)
    } else if ( data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] < data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE] ) {
      // делаем активным элемент, предшевствующий первому и свершаем рекурсию
      focusFormItem(data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE] + 1);
      return tabFormPrev();
    }
    // если полученный элемент не находится на экране, то снимаем с него активность
      if ( data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] > data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE] ) {
        focusFormItem(-1);
        return false;
      }
      return true;
  }







  // Перемещает курсор на элемент, лежащий под текущим. Если табуляция удалась, возвращает true
  // если tabulate = true, то выполняет табуляцию, иначе, просто возвращает результат
  public final boolean tabDown(boolean tabulate) {
    // если на экране ничего не видно, то выходим
    if ( data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] < 0 )
      return false;
    // получаем текущий активный элемент
    int activeIndex = data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX];
    // если в фокусе ничего нет, то и табулировать некуда
//    if ( activeIndex < 0 )
//      return false;
    // если в фокусе ничего нет, то можно сфокусировать последний видимый элемент
    if ( activeIndex < 0 ) {
      for (int i = data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE]; i <= data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE]; i++) {
        TItem itm = getItem(i);
        if ( itm.isFocusable() && isVisibleItem(i) ) {
          focusFormItem(i);
          return true;
        }
      }
      return false;
    }

    int startIndex = data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX];
    // проходимся по всем элементам, которые видно на экране и ищем среди активных
    // максимально близкий по вертикали, но лежащий ниже активного
    // должно быть видно не менее 50% высоты элемента, если он полностью умещается на форме или
    // не менее 50% высоты формы в противном случае
    int minDistanceY = data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT];
    TItem activeItem = getItem(activeIndex);
    for (int i = activeIndex+1; i <= data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE]; i++) {
      TItem itm = getItem(i);
      int dy = itm.y - activeItem.y;
      int minVisible = ( itm.height < height/2 ) ? itm.height/2 : height/2;
      if ( itm.isFocusable() && (dy < minDistanceY) && (itm.y >= activeItem.y+activeItem.height)
        && (data[_MVL_UI_FORM_OFFSET_START_POS_Y]+height-itm.y > minVisible) )
          minDistanceY = dy;
    } // for
    // если это расстояние больше, чем размер экрана + высота текущего элемента, то этот
    // элемент точно нельзя сфокусировать
    if (minDistanceY > height+activeItem.height)
      return false;
    // если нашли, то отбираем самый близкий по вертикальной медиане помещаем его индекс
    int minDistanceX = data[_MVL_UI_FORM_OFFSET_FULL_WIDTH];    // минимальное отклонение по горизонтали от активного элемента
    for (int i = activeIndex+1; i <= data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE]; i++) {
      TItem itm = getItem(i);
      int dx = Math.abs( (itm.x + itm.width/2) - (activeItem.x+activeItem.width/2) );
      int minVisible = ( itm.height < height/2 ) ? itm.height/2 : height/2;
      if ( itm.isFocusable() && (itm.y - activeItem.y == minDistanceY) && (dx < minDistanceX)
        && (data[_MVL_UI_FORM_OFFSET_START_POS_Y]+height-itm.y > minVisible) ) {
          minDistanceX = dx;
          if ( tabulate )
            focusFormItem(i);
      }
    } // for
    return data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] != startIndex;
  }




  // Перемещает курсор на элемент, лежащий над текущим. Если табуляция удалась, возвращает true
  // если tabulate = true, то выполняет табуляцию, иначе, просто возвращает результат
  public final boolean tabUp(boolean tabulate) {
    // если на экране ничего не видно, то выходим
    if ( data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] < 0 )
      return false;
    // получаем текущий активный элемент
    int activeIndex = data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX];
    // если в фокусе ничего нет, то можно сфокусировать последний видимый элемент
    if ( activeIndex < 0 ) {
      for (int i = data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE]; i >= data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE]; i--) {
        TItem itm = getItem(i);
        if ( itm.isFocusable() && isVisibleItem(i) ) {
          focusFormItem(i);
          return true;
        }
      }
      return false;
    }
    int startIndex = data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX];
    // проходимся по всем элементам, которые видно на экране и ищем среди активных
    // максимально близкий по вертикали, но лежащий выше активного
    // должно быть видно не менее 50% высоты элемента, если он полностью умещается на форме или
    // не менее 50% высоты формы в противном случае
    int minDistanceY = data[_MVL_UI_FORM_OFFSET_FULL_HEIGHT]+5;
    TItem activeItem = getItem(activeIndex);
    for (int i = activeIndex-1; i >= data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE]; i--) {
      TItem itm = getItem(i);
      int dy = activeItem.y - itm.y;
      int minVisible = ( itm.height < height/2 ) ? itm.height/2 : height/2;
      if ( itm.isFocusable() && (dy < minDistanceY) && (activeItem.y >= itm.y+itm.height) //&& (dy >= activeItem.height)
        && (data[_MVL_UI_FORM_OFFSET_START_POS_Y]-minVisible < itm.y) )
          minDistanceY = dy;

    } // for
    // если это расстояние больше, чем размер экрана + высота текущего элемента, то этот
    // элемент точно нельзя сфокусировать
    if ( minDistanceY > height+activeItem.height )
      return false;
    // если нашли, то отбираем самый близкий по вертикальной медиане помещаем его индекс
    int minDistanceX = data[_MVL_UI_FORM_OFFSET_FULL_WIDTH];   // минимальное отклонение по горизонтали от активного элемента
    for (int i = activeIndex-1; i >= data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE]; i--) {
      TItem itm = getItem(i);
      int dx = Math.abs( (itm.x + itm.width/2) - (activeItem.x+activeItem.width/2) );
      int minVisible = ( itm.height < height/2 ) ? itm.height/2 : height/2;
      if ( itm.isFocusable() && (activeItem.y - itm.y == minDistanceY) && (dx < minDistanceX)
        && (data[_MVL_UI_FORM_OFFSET_START_POS_Y]-minVisible < itm.y) ) {
          minDistanceX = dx;
          if ( tabulate )
            focusFormItem(i);
      }
    } // for
    return data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] != startIndex;
  }



  // для индекса элемента формы возвращает true, если соответствующий элемент видим
  public final boolean isVisibleItem(int index) {
    TItem itm = getItem(index);
    return ( ( itm.x + itm.width > data[_MVL_UI_FORM_OFFSET_START_POS_X] ) && (itm.x < data[_MVL_UI_FORM_OFFSET_START_POS_X] + width )
       && ( itm.y + itm.height > data[_MVL_UI_FORM_OFFSET_START_POS_Y] ) && (itm.y < data[_MVL_UI_FORM_OFFSET_START_POS_Y] + height ) );
  }



  // иннициализирует значения индексов 1го и последнего видимых элементов
  public final void formCalcVisibleIndexes() {
    data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] = -1;
    data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE] = -1;
    if ( v1.size() == 0 ) {
      data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] = -1;
      return;
    }
    
    // если сфокусированный элемент невидим, расфокусируем его
    if ( data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] >= 0 && (!isVisibleItem(data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX]) ) )
      data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] = -1;

    for (int i = 0; i < v1.size(); i++)
      if ( isVisibleItem(i) ) {
        if ( data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] < 0 )
          data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] = i;
        data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE] = i;
      }
  }



  public final TItem getItem(int index) {
    return (TItem)v1.elementAt(index);
  }



  public final void focusFormItem(int index) {
    if ( data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] == index )
      return;
    if ( data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] >= 0 && data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] < v1.size() )
      onEvent(this, (TItem)v1.elementAt(data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX]), EVENT_DEACTIVATE, getSystemTime());
    data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] = index;
    if ( data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] >= 0 && data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] < v1.size() )
      onEvent(this, (TItem)v1.elementAt(data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX]), EVENT_ACTIVATE, getSystemTime());
  }



// --------------------------- ItemEditor ---------------------------------------
  // создание текстового редактора
  public final void createItemEditor(int aX, int aY, int aW, int aH, String aStr, int aOptions, int aTextType, int aMaxSize, String aTitle) {
    type = _MVL_UI_ITEM_EDITOR;
    data = new int[_MVL_UI_EDITOR_DATA_LENGTH];
    options = aOptions;
    v1 = new Vector();
    v2 = new Vector();
    v1.addElement(aStr);
    v2.addElement(aTitle);
    x = aX;
    y = aY;
    width = aW;
    height = aH;
//    data[_MVL_UI_EDITOR_OFFSET_TEXT_STATUS] = _MVL_UI_TEXT_STATUS_FORMAT;
    data[_MVL_UI_EDITOR_OFFSET_BACKGROUND] = 0xFFFFFFFF;
    data[_MVL_UI_EDITOR_OFFSET_F_BACKGROUND] = 0xEEEEEEEE;
    data[_MVL_UI_EDITOR_OFFSET_TEXT_TYPE] = aTextType;
    data[_MVL_UI_EDITOR_OFFSET_MAX_SIZE] = aMaxSize;
  }




// --------------------------- ItemChoiceGroup ---------------------------------------

  public final void createItemChoiceGroup(int aX, int aY, int aW, int aH, int aOptions) {
    type = _MVL_UI_ITEM_CHOICE_GROUP;
    data = new int[_MVL_UI_CHOICE_GROUP_DATA_LENGTH];
    options = aOptions;
    v1 = new Vector();
    v2 = new Vector();

    x = aX;
    y = aY;
    width = aW;
    height = aH;
    data[_MVL_UI_CHOICE_GROUP_OFFSET_BACKGROUND] = 0xFFFFFFFF;
    data[_MVL_UI_CHOICE_GROUP_OFFSET_F_BACKGROUND] = 0xFFFFFFFF;
  }




// ------------------------------ ItemButton ---------------------------------------
  public final void createItemButton(int aX, int aY, int aW, int aH, TString aStr, int aOptions) {
    type = _MVL_UI_ITEM_BUTTON;
    data = new int[_MVL_UI_BUTTON_DATA_LENGTH];
    options = aOptions;
    v1 = new Vector();
    v1.addElement(aStr);
    v2 = new Vector();
    x = aX;
    y = aY;
    width = aW;
    height = aH;
  }

// ------------------------------ ItemScrollBar ---------------------------------------
  public final void createItemScrollBar(int aX, int aY, int aW, int aH, int aOptions) {
    type = _MVL_UI_ITEM_SCROLLBAR;
    data = new int [_MVL_UI_SCROLLBAR_DATA_LENGTH];
    v1 = new Vector();
    x = aX;
    y = aY;
    width = aW;
    height = aH;
    options = aOptions;
    data[_MVL_UI_SCROLLBAR_OFFSET_COLOR] = 0x3333CC;
    data[_MVL_UI_SCROLLBAR_OFFSET_BACKGROUND] = 0x404045;
  }



  // привязывает скроллер к форме
  void assignScrollBarToControl(TForm form) {
    v1.removeAllElements();
    v1.addElement(form);
  }
// ------------------------------ ItemSoftButton ---------------------------------------
  public final void createItemSoftButton(TString aStr, int aOptions) {
    type = _MVL_UI_ITEM_SOFT_BUTTON;
    data = new int[_MVL_UI_SOFT_BUTTON_DATA_LENGTH];
    options = aOptions;
    v1 = new Vector();
    v1.addElement(aStr);
    v2 = new Vector();
    v2.addElement(null);
    data[_MVL_UI_SOFT_BUTTON_OFFSET_BACKGROUND] = 0xFFFFFFFF;
  }
// ------------------------------ ItemMenuWindow ---------------------------------------
  public final void createMenuWindow(int aX, int aY, int aOptions, int aAnchor) {
    type = _MVL_UI_ITEM_MENU_WINDOW;
    data = new int[_MVL_UI_MENU_WINDOW_DATA_LENGTH];
    data[_MVL_UI_MENU_WINDOW_OFFSET_ANCHOR] = aAnchor;
    x = aX;
    y = aY;
    options = aOptions;
    v1 = new Vector();
    v2 = new Vector();
  }
  
  
// -------------------------------- ItemWindow -----------------------------------------
  public final void createWindow(int aX, int aY, int aW, int aH, int aOptions, int aAnchor) {
    type = _MVL_UI_ITEM_WINDOW;
    data = new int[_MVL_UI_WINDOW_DATA_LENGTH];
    data[_MVL_UI_WINDOW_OFFSET_ANCHOR] = aAnchor;
    x = aX;
    y = aY;
    width = aW;
    height = aH;
    options = aOptions;
    v1 = new Vector();
    v2 = new Vector();
  }



// --------------------------------- ItemList ------------------------------------------
#ifdef ENABLE_LIST
  public final void  createList(int aX, int aY, int aW, int aH, int aOptions) {
    type = _MVL_UI_ITEM_LIST;
    data = new int[_MVL_UI_LIST_DATA_LENGTH];
    x = aX;
    y = aY;
    width = aW;
    height = aH;
    data[_MVL_UI_LIST_OFFSET_BACKGROUND] = 0xDAEBF4;
    data[_MVL_UI_LIST_OFFSET_COLOR] = 0x000000;
    data[_MVL_UI_LIST_OFFSET_F_BACKGROUND] = 0xAEB0FB;
    data[_MVL_UI_LIST_OFFSET_COLOR] = 0x000000;
    data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] = -1;  // если 1й элемент длинный, при отрисовке будет запущен его скролл

    options = aOptions;
    v1 = new Vector();
    v2 = new Vector();
  }
  
  
  
  // проверяет, не ли необходимости запустить бегущую строку элемента списка и рассчитывает параметры. если надо
  public final void listVerifyAnimate() {
    data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_X] = 0;
    if ( data[_MVL_UI_LIST_OFFSET_ACTIVE] >= v1.size() || data[_MVL_UI_LIST_OFFSET_ACTIVE] < 0 ) {
      data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] = 0;
      return;
    }

    String str = (String)v1.elementAt(data[_MVL_UI_LIST_OFFSET_ACTIVE]);
    int wd = width - data[_MVL_UI_LIST_OFFSET_ICON_W] - 4;
    if ( str != null ) {
      data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] = getFontStringWidth(_mvl_ui_fonts[data[_MVL_UI_LIST_OFFSET_F_FONT]], str);
      if ( data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] > wd ) {
        data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] -= data[_MVL_UI_LIST_OFFSET_ICON_W] + 4;
//        data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_X_DELTA] = 5;
      } else
        data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] = 0;
    } else
      data[_MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN] = 0;
  }
#endif  // ENABLE_LIST





  public final void appendItem(TItem item, int layout, int deltaX, int deltaY) {
/*
    if ( deltaX < 0 )
      deltaX =  -deltaX * width/100;
    if ( deltaY < 0 )
      deltaY =  -deltaY * height/100;
    if ( item.width < 0 )
      item.width =  -item.width * width/100;
    if ( item.height < 0 )
      item.height =  -item.height * height/100;

    if ( (layout & KLayoutNewline) != 0 ) {
      formLayoutDoneLine();
    } else if ( (layout & KLayoutBottom) != 0) {
    }

    if        ( (layout & KLayoutLeft) != 0 ) {
      // если предыдущая строке не пуста, завершаем ее
      if ( data[_MVL_UI_FORM_OFFSET_LINE_COUNT] > 0 )
        formLayoutDoneLine();
      // если этот элемент первый в форме
      if ( v1.size() == 0 ) {
        item.x = deltaX;
        item.y = deltaY;
      } else {
        item.x = deltaX;
        item.y = data[_MVL_UI_FORM_OFFSET_LAST_LINE_END_Y] + deltaY;
      }
    } else if ( (layout & KLayoutRight) != 0 ) {
////////////////
    } else if ( (layout & KLayoutCenter) != 0 ) {
    } else if ( (layout & KLayoutGrid) != 0 ) {
    } else if ( (layout & KLayoutNext) != 0 ) {
    }
*/
  }


/*
  // завершает компоновку последней строки, вычисляет все незаданные размеры
  // ее элементов
  public final void formLayoutDoneLine() {
   // проходимся по всем элементам с незаданной шириной и вычисляем ее
    for (int i = v1.size()-data[_MVL_UI_FORM_OFFSET_LINE_COUNT]; i < v1.size(); i++) {
      TItem itm = (TItem)v1.elementAt(i);
      if ( itm.width == 0 )
      ;
    }


    data[_MVL_UI_FORM_OFFSET_LINE_COUNT] = 0;
    data[_MVL_UI_FORM_OFFSET_LAST_LINE_END_Y] += 11111;
  }

*/


}
#endif // __MVL_UI_JAVA_TITEM_H__

