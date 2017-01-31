#ifnotdef __MVL_UI_JAVA_GLOBAL_H__
#define   __MVL_UI_JAVA_GLOBAL_H__
#defineblock begin
/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                 User interface globals variables and metods unit


                      Copyright (c) O.A. Trifonov, 2007
                                  Version 1.10

\*----------------------------------------------------------------------------*/


#defineblock end
  public static Vector[] _mvl_ui_screens;              // вектора форм для всех экранов
  public static int[] _mvl_ui_screen_active;           // номера активных форм экранов

  public static TFont[] _mvl_ui_fonts;                 // массив зарегистрированных шрифтов
  public static int _mvl_ui_fonts_count;               // число записей в массиве

  // ЦВЕТА
  public static int _mvl_ui_frame_color_1 = 0x122064;       // цвет рамки фокуса
  public static int _mvl_ui_frame_color_2 = 0x2455BF;       // внешний цвет для рамки двойной толщины
  public static int _mvl_ui_items_frame_color_1 = 0x525255; // цвет внешней рамки элементов
  public static int _mvl_ui_items_frame_color_2 = 0xC9CFC9; // цвет внутренней рамки элементов
  public static int _mvl_ui_items_3d_color_1 = 0xFFFFFF;    // цвет верхнего левого угла объемных элементов
  public static int _mvl_ui_items_3d_color_2 = 0xC9CFC9;    // цвет нижнего правого угла объемных элементов
  public static int _mvl_ui_items_3d_color = 0xDBDFDB;      // цвет фона объемных элементов
  public static int _mvl_ui_scrollbar_frame_color = 0x000000;// цвет рамки скролеров
#ifdef ENABLE_POPUP_WINDOW
  public static int _mvl_ui_menu_window_background = 0x33CCFF; // фон окон меню
  public static int _mvl_ui_menu_window_frame_color1 = 0xD1EFF9; // верхняя левая часть рамки
  public static int _mvl_ui_menu_window_frame_color2 = 0x64AAC2; // нижняя правая часть рамки
  public static int _mvl_ui_menu_window_selector_color = 0x0099FF; // фон подсвеченного текста
#endif

  public static int _mvl_ui_frame_line_style = KLineStyleSolid; // стиль рисования линий

  public static boolean _mvl_ui_repaint_request = false; // если какому-то компоненту требуется выполнить прорисовку
  // в потоке idle(), он выставляет этот флаг.
  public static long _mvl_last_action_time;              // время, в которое последний раз было получено действие

  public static TextBox _mvl_ui_text_editor;             // редактор текста
  public static TItem   _mvl_ui_command_item;            // тут сохраняется элемент перед вызывом телефонных стандартных экранов интерфейса
  public static TItem   _mvl_ui_command_item_owner;      // а тут его владелец (для обработчика событий)
  public static Command _mvl_ui_cmd_ok;
  public static Command _mvl_ui_cmd_cancel;
  public static Form    _mvl_ui_date_form;
  public static List    _mvl_ui_list;                    // список для "комбо"бокса


  // вызывается при инициализации приложения для выделения памяти под экраны
  public static final void setScreensCount(int count) {
    _mvl_ui_screens = new Vector[count];
    _mvl_ui_screen_active = new int[count];
    for (int i = 0; i < count; i++) {
      _mvl_ui_screen_active[i] = -1;
      _mvl_ui_screens[i] = new Vector();
    }
    _mvl_ui_cmd_ok = new Command("Ok", Command.OK, 1);
    _mvl_ui_cmd_cancel = new Command("Отмена", Command.CANCEL, 1);
  }



  // добавляет форму на жкран
  public final void mvlAppendScreenForm(int screen, TItem form) {
    form.activate();
    _mvl_ui_screens[screen].addElement(form);
    if ( _mvl_ui_screen_active[screen] < 0 )
      mvlSetActiveForm(screen, form);
    if ( screen == _mvl_screen )
      repaint();
  }
  
  
  // удаляет все элементы с экрана
  public final void mvlRemoveAllScreenItems(int screen) {
    _mvl_ui_screens[screen].removeAllElements();
    if ( screen == _mvl_screen )
      repaint();
  }
  

  
  // удаляет форму с экрана
  public final void mvlRemoveScreenForm(int screen, TItem form) {
    _mvl_ui_screens[screen].removeElement(form);
    if ( screen == _mvl_screen )
      repaint();
  }




  public final void mvlSetActiveForm(int screen, TItem form) {
    for (int i = 0; i < _mvl_ui_screens[screen].size(); i++)
      if ( form.equals((TItem)_mvl_ui_screens[screen].elementAt(i)) ) {
        if ( _mvl_ui_screen_active[screen] >= 0 )
          onEvent((TItem)_mvl_ui_screens[screen].elementAt(_mvl_ui_screen_active[screen]), null, EVENT_DEACTIVATE, getSystemTime());
        _mvl_ui_screen_active[screen] = i;
        onEvent(form, null, EVENT_ACTIVATE, getSystemTime());
        repaint();
        return;
      }
  }



  public final void mvlSetActiveForm(TItem form) {
    mvlSetActiveForm(_mvl_screen, form);
  }



  public static final int mvlRegisterFont(TFont font) {
    if ( _mvl_ui_fonts == null ) {
      _mvl_ui_fonts = new TFont[5];
      _mvl_ui_fonts_count = 0;
    }
    if ( _mvl_ui_fonts.length <= _mvl_ui_fonts_count ) {
      TFont[] tmp = new TFont[_mvl_ui_fonts.length];
      System.arraycopy(tmp, 0, _mvl_ui_fonts, 0, _mvl_ui_fonts.length);
      _mvl_ui_fonts = new TFont[_mvl_ui_fonts.length+5];
      System.arraycopy(_mvl_ui_fonts, 0, tmp, 0, tmp.length);
    }
    _mvl_ui_fonts[_mvl_ui_fonts_count++] = font;
    return _mvl_ui_fonts_count-1;
  }
  
  
  
  public static final TFont mvlGetFont(int index) {
    return _mvl_ui_fonts[index];
  }



  // задает внешний вид выделяющей рамки
  // color1 - внутренний цвет, color2- внешний цвет или 0xFFFFFFFF для рамки одинарной толщины
  // lineStyle - стиль линии рамки
  public static final void setUiFocusFrameColor(int color1, int color2, int lineStyle) {
    _mvl_ui_frame_color_1 = color1;
    _mvl_ui_frame_color_2 = color2;
    _mvl_ui_frame_line_style = lineStyle;
  }



  public static final boolean mvlSendActionToUi(int action, long time, boolean repeated) {
#ifdef ENABLE_POPUP_WINDOW
    if ( _mvl_windows.size() > 0 ) {
      return ( ((TItem)_mvl_windows.elementAt(_mvl_windows.size()-1)).actionHandler(action, time, null, repeated) );
    }
#endif
    for (int i = 0; i < _mvl_ui_screens[_mvl_screen].size(); i++)
      if ( ((TItem)_mvl_ui_screens[_mvl_screen].elementAt(i)).actionHandler(action, time, null, repeated) ) {
        _mvl_last_action_time = time;
        return true;
      }
     _mvl_last_action_time = time;
    return false;
  }
  

/*
  public static final boolean mvlSendKeyCodeToUi(int keyCode, long time, boolean repeated) {
#ifdef ENABLE_POPUP_WINDOW
    if ( _mvl_windows.size() > 0 )
      return ( ((TItem)_mvl_windows.elementAt(_mvl_windows.size()-1)).actionKeyHandler(keyCode, time, null, repeated) );
#endif
    for (int i = 0; i < _mvl_ui_screens[_mvl_screen].size(); i++)
      if ( ((TItem)_mvl_ui_screens[_mvl_screen].elementAt(i)).actionKeyHandler(keyCode, time, null, repeated) ) {
//        _mvl_last_action_time = time;
        return true;
      }
//     _mvl_last_action_time = time;
    return false;
  }
*/



  // рисует рамку выбора элемента
  // параметры определяют внутренний размер рамки
  public static final void _mvl_gui_drawSelectorFrame(Graphics g, int x, int y, int w, int h) {
    x--; y--;  w++; h++;
    setLineStyle(_mvl_ui_frame_line_style);
    setLineColor(_mvl_ui_frame_color_1);
    // одинарная рамка
    if ( _mvl_ui_frame_color_2 == 0xFFFFFFFF ) {
      setClip(x, y, w+1, h+1);
      drawRect(x, y, w, h);
    } else {
      setClip(x-1, y-1, w+3, h+3);
      drawRect(x-1, y-1, w+1, h+1);
      setLineColor(_mvl_ui_frame_color_2);
      drawRect(x, y, w+1, h+1);
    }
  }



  public static final void _mvl_gui_drawSelectorFrameArea(Graphics g, int x, int y, int w, int h, int ax, int ay, int aw, int ah) {
    int clipX = g.getClipX();
    int clipY = g.getClipY();
    int clipWidth = g.getClipWidth();
    int clipHeight = g.getClipHeight();

    x--; y--;  w++; h++;
    setLineStyle(_mvl_ui_frame_line_style);
    setLineColor(_mvl_ui_frame_color_1);
    // одинарная рамка
    if ( _mvl_ui_frame_color_2 == 0xFFFFFFFF ) {
      setClip(x, y, w+1, h+1);
      g.clipRect(ax, ay, aw, ah);
      drawRect(x, y, w, h);
    } else {
      setClip(x-1, y-1, w+3, h+3);
      g.clipRect(ax, ay, aw, ah);
      drawRect(x-1, y-1, w+1, h+1);
      setLineColor(_mvl_ui_frame_color_2);
      drawRect(x, y, w+1, h+1);
    }
    setClip(clipX, clipY, clipWidth, clipHeight);
  }



  // рисует псевдообъемное прямоугольное поле
  public static final void _mvl_gui_drawVolumeField(Graphics g, int x, int y, int w, int h) {
    setLineColor(_mvl_ui_items_3d_color_1);
    drawVLine(x, y, y+h-2);
    drawHLine(x, y, x+w-2);
    setLineColor(_mvl_ui_items_3d_color_2);
    drawVLine(x+w-1, y, y+h-1);
    drawHLine(x, y+h-1, x+w-1);
    setLineColor(_mvl_ui_items_3d_color);
    fillRect(x+1, y+1, w-2, h-2);
  }


  public static final void _mvl_fillGradientRect(Graphics g, int aX, int aY, int aWidth, int aHeight, int aColor1, int aColor2) {
    // разделяем цвета на компоненты
    int r1 = aColor1 >> 16;
    int g1 = aColor1 >> 8 & 0xFF;
    int b1 = aColor1 & 0xFF;
    int r2 = aColor2 >> 16;
    int g2 = aColor2 >> 8 & 0xFF;
    int b2 = aColor2 & 0xFF;
    // вычисляем шаг градиента, предварительно умножая цвета на 255
    // для уменьшения ошибки округления
    r1 <<= 8;
    g1 <<= 8;
    b1 <<= 8;
    r2 <<= 8;
    g2 <<= 8;
    b2 <<= 8;
    int dR = (r2 - r1) / aHeight;
    int dG = (g2 - g1) / aHeight;
    int dB = (b2 - b1) / aHeight;
    // рисуем градиентынй прямоугольник горизонтальными линиями
    int lineEndX = (aX + aWidth) - 1;
    for (int rectEndY = (aY + aHeight) - 1; aY < rectEndY; aY++) {
        g.setColor(r1 >> 8, g1 >> 8, b1 >> 8);
        g.drawLine(aX, aY, lineEndX, aY);
        r1 += dR;
        g1 += dG;
        b1 += dB;
    }
  }
  
  
  
  
  public final TItem mvlCreateForm(int x, int y, int w, int h, int options) {
    TItem res = new TItem();
    res.createItemForm(x, y, w, h, options);
    return res;
  }
  
  
  public final TItem mvlCreateText(int x, int y, int w, int h, String str, int options) {
    TItem res = new TItem();
    res.createItemText(x, y, w, h, str, options);
    return res;
  }

  
  public final TItem mvlCreateText(int x, int y, String str, int options) {
    TItem res = new TItem();
    res.createItemText(x, y, str, options);
    return res;
  }
  
  
  public final TItem mvlCreateImage(int x, int y, Image img, int options) {
    TItem res = new TItem();
    res.createItemImage(x, y, img, options);
    return res;
  }
  

  public final TItem mvlCreateImage(int x, int y, int w, int h, TImage img, int options) {
    TItem res = new TItem();
    res.createItemImage(x, y, w, h, img, options);
    return res;
  }
  
  public final TItem mvlCreateEditor(int x, int y, int w, int h, String str, int options, int textType, int maxSize, String title) {
    TItem res = new TItem();
    res.createItemEditor(x, y, w, h, str, options, textType, maxSize, title);
    return res;
  }

  
  public final Image mvlGetItemImage(TItem item, int index) {
    return (Image)item.v2.elementAt(index);
  }
  
  
  
  public final Image mvlGetItemImage(TItem item) {
    return (Image)item.v2.elementAt(0);
  }
  


  public final void mvlSetItemImage(TItem item, TImage img, int index) {
    if ( item.v2.size() > 0 )
      item.v1.setElementAt(img, index);
  }
  
  
  
  public final void mvlSetItemImage(TItem item, TImage img) {
    if ( item.v2.size() > 0 )
      item.v1.setElementAt(img, 0);
  }



  public final int mvlGetItemImagesCount(TItem item) {
    return item.v2.size();
  }



  public final void mvlAppendItemImage(TItem item, TImage img) {
    item.v2.addElement(img);
  }
  
  
  
  public final TItem mvlCreateChoiceGroup(int x, int y, int w, int h, int options) {
    TItem res = new TItem();
    res.createItemChoiceGroup(x, y, w, h, options);
    return res;
  }
  
  
  public final TItem mvlCreateButton(int x, int y, int w, int h, TString str, int options) {
    TItem res = new TItem();
    res.createItemButton(x, y, w, h, str, options);
    return res;
  }







  public final TItem mvlCreateScrollBar(int x, int y, int w, int h, int options) {
    TItem res = new TItem();
    res.createItemScrollBar(x, y, w, h, options);
    return res;
  }
  
  
  public final void mvlAssignScrollBarToControl(TItem scrollbar, TItem form) {
    scrollbar.assignScrollBarToControl(form);
  }



  public final TItem mvlCreateSoftButton(String str, int options) {
    TItem res = new TItem();
    res.createItemSoftButton(str, options);
    return res;
  }
  
  
  
#ifdef ENABLE_POPUP_WINDOW
  public final TItem mvlCreateMenu(int x, int y, int options, int anchor) {
    TItem res = new TItem();
    res.createMenuWindow(x, y, options, anchor);
    return res;
  }
  
  
  
  public final void mvlPushWindow(TItem menu) {
    repaintToBB();
    if ( _mvl_windows.size() == 0 ) {
      if ( _mvl_ui_screen_active[_mvl_screen] >= 0 && _mvl_ui_screen_active[_mvl_screen] < _mvl_ui_screens[_mvl_screen].size() )
        onEvent((TItem)_mvl_ui_screens[_mvl_screen].elementAt(_mvl_ui_screen_active[_mvl_screen]), null, EVENT_WINDOW_POPUP, getSystemTime());
      shadowBackBufferImage(40);
    }
    menu.activate();
    _mvl_windows.addElement(menu);
    repaint();
  }
  

  
  public static final int mvlGetPushedWindowsCount() {
#ifdef ENABLE_POPUP_WINDOW
    return _mvl_windows.size();
#else
    return 0;
#endif
  }



  public final void mvlPopWindow() {
    TItem last = (TItem)_mvl_windows.lastElement();
    _mvl_windows.removeElement(last);
    if ( _mvl_windows.size() == 0 ) {
      if ( _mvl_ui_screen_active[_mvl_screen] >= 0 )
        onEvent((TItem)_mvl_ui_screens[_mvl_screen].elementAt(_mvl_ui_screen_active[_mvl_screen]), last, EVENT_WINDOW_CLOSE, getSystemTime());
      else
        onEvent(null, last, EVENT_WINDOW_CLOSE, getSystemTime());
    }
    repaint();
  }
  
  
  public final int mvlAppendCommand(TItem menu, TString name) {
    menu.v1.addElement(name);
    menu.v2.addElement(null);  // submenu
    menu.v2.addElement(null);  // checked
    return menu.v1.size()-1;
  }
  
  
  
  public final int mvlAppendCheckItem(TItem menu, TString name, boolean checked) {
    menu.v1.addElement(name);
    menu.v2.addElement(null);  // submenu
    menu.v2.addElement(new Boolean(checked));  // checked
    return menu.v1.size()-1;
  }

  
  
  public final int mvlAppendSubMenu(TItem menu, TString name, TMenu subMenu) {
    menu.v1.addElement(name);
    menu.v2.addElement(subMenu); // submenu
    menu.v2.addElement(null);    // checked
    return menu.v1.size()-1;
  }
  
  
  
  public final boolean mvlGetMenuChecked(TItem menu, int itemIndex) {
    return ((Boolean)menu.v2.elementAt(2*itemIndex + 1)).booleanValue();
  }



  public final void mvlSetMenuChecked(TItem menu, int itemIndex, boolean status) {
    menu.v2.setElementAt(new Boolean(status), itemIndex);
  }



  public final int mvlGetMenuRadioItemIndex(TItem item) {
    return item.data[_MVL_UI_MENU_WINDOW_OFFSET_RESULT];
  }



  public final void mvlSetMenuRadioItemIndex(TItem item, int value) {
    item.data[_MVL_UI_MENU_WINDOW_OFFSET_RESULT] = value;
  }
  
  
  
  public final void mvlClearItemStrings(TItem item) {
    item.v1.removeAllElements();
  }
  

  
  public final void mvlClearItemImages(TItem item) {
    item.v2.removeAllElements();
  }

  
  
  public final int mvlGetItemSelected(TItem item) {
    switch ( item.type ) {
      case _MVL_UI_ITEM_CHOICE_GROUP:
        return item.data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT];

      case _MVL_UI_ITEM_LIST:
        return item.data[_MVL_UI_LIST_OFFSET_ACTIVE];
        
        
      case _MVL_UI_ITEM_MENU_WINDOW:
        return item.data[_MVL_UI_MENU_WINDOW_OFFSET_ACTIVE];
    }
    return -1;
  }
  
  
  
  public final void mvlSetItemSelected(TItem item, int index) {
    switch ( item.type ) {
      case _MVL_UI_ITEM_CHOICE_GROUP:
        item.data[_MVL_UI_CHOICE_GROUP_OFFSET_RESULT] = index;
        break;

      case _MVL_UI_ITEM_LIST:
        // проверяем валидность границ
        if ( index < 0 )
          index = 0;
        else if ( index >= item.v1.size() )
          index = item.v1.size()-1;
        // а надо ли вообще переходить?
        if ( item.data[_MVL_UI_LIST_OFFSET_ACTIVE] == index )
          return;
        // переход к более начальному элементу
        item.data[_MVL_UI_LIST_OFFSET_ACTIVE] = index;
        if ( index < item.data[_MVL_UI_LIST_OFFSET_TOP_LINE] )
          item.data[_MVL_UI_LIST_OFFSET_TOP_LINE] = index;
        // к более конечному элементу
        else if ( index >= item.data[_MVL_UI_LIST_OFFSET_TOP_LINE] + item.data[_MVL_UI_LIST_OFFSET_VISIBLE_LINES]  )
          item.data[_MVL_UI_LIST_OFFSET_TOP_LINE] = index - item.data[_MVL_UI_LIST_OFFSET_VISIBLE_LINES] + 1;
        break;
    }
  }
  
  
  
  public final bool mvlGetItemChecked(TItem item, int index) {
    return item.getItemChecked(index);
  }



  public final void mvlSetItemChecked(TItem item, int index, bool status) {
    item.setItemChecked(index, status);
  }


  
  public final TItem mvlCreateWindow(int x, int y, int w, int h, int options, int anchor) {
    TItem res = new TItem();
    res.createWindow(x, y, w, h, options, anchor);
    return res;
  }


#endif // ENABLE_POPUP_WINDOW


#ifdef ENABLE_LIST
  public final TItem mvlCreateList(int x, int y, int w, int h, int options) {
    TItem res = new TItem();
    res.createList(x, y, w, h, options);
    return res;
  }
#endif  // ENABLE_LIST



  // удаляет все элементы с формы
  public final void mvlDeleteAllItems(TItem form) {
    form.v1.removeAllElements();
    if ( form.type == _MVL_UI_ITEM_FORM ) {
      form.data[_MVL_UI_FORM_OFFSET_FOCUS_INDEX] = 0;
      form.data[_MVL_UI_FORM_OFFSET_FIRST_VISIBLE] = 0;
      form.data[_MVL_UI_FORM_OFFSET_LAST_VISIBLE] = 0;
    }
  }
  
  
  public final TItem mvlGetItem(TItem form, int index) {
    return (TItem)form.v1.elementAt(index);
  }
  
  
  public final int mvlGetItemsCount(TItem form) {
    return form.v1.size();
  }

  
  
  public final void mvlSetItemContextString(TItem item, String str) {
    switch ( item.type ) {
      case _MVL_UI_ITEM_TEXT:
        if ( item.v2 == null )
          item.v2 = new Vector();
        item.v2.removeAllElements();
        item.v2.addElement(str);
        break;
      case _MVL_UI_ITEM_BUTTON:
        if ( item.v2 == null )
          item.v2 = new Vector();
        item.v2.removeAllElements();
        item.v2.addElement(str);
        break;

    }
  }



  public final String mvlGetItemContextString(TItem item) {
    if ( item == null )
      return "";
    switch ( item.type ) {
      case _MVL_UI_ITEM_TEXT:
        return ( item.v2 == null || item.v2.size() == 0 ) ? "" : (String)item.v2.elementAt(0);
      case _MVL_UI_ITEM_BUTTON:
        return ( item.v2 == null || item.v2.size() == 0 ) ? "" : (String)item.v2.elementAt(0);
    }
    return "";
  }



  public final void mvlAppendItemFlow(TForm form, TItem item, int dx, int dy, int layout, int deltaItem) {
    item.activate();
    if ( item.type == _MVL_UI_ITEM_TEXT && item.width == 0 )
      item.width = form.width - item.x  - 3;
    if ( form.v1.size() == 0 ) {
      item.x = dx;
      item.y = dy;
      // это для решения проблемы неверного отступа первого элемента
      if ( (layout & KLayoutLeft) != 0 && (layout & KLayoutNewLine) != 0 )
        item.x += dx;
      form.appendItem(item);
      return;
    }
    TItem baseItem = (TItem)form.v1.elementAt(form.v1.size() - deltaItem);

    baseItem.activate();
    if ( (layout & KLayoutLeft) != 0 )
      item.x = baseItem.x;
    else if ( (layout & KLayoutHCenter) != 0 )
      item.x = baseItem.x + baseItem.width/2;
    else
      item.x = baseItem.x + baseItem.width;
    if ( (layout & KLayoutTop) != 0 )
      item.y = baseItem.y;
    else if ( (layout & KLayoutVCenter) != 0 )
      item.y = baseItem.y + baseItem.height;
    else
      item.y = baseItem.y + baseItem.height;
    if ( (layout & KLayoutNewLine) != 0 ) {
      item.x = dx;
      // вычисляем высоту элементов формы
      int maxY = 0;
      for (int i = 0; i < form.v1.size(); i++) {
        TItem fi = (TItem)form.v1.elementAt(i);
        if ( fi.y + fi.height > maxY )
          maxY = fi.y + fi.height;
        item.y = maxY;
      }
    }
    // если базовый элемент непрямоугольный
    if ( baseItem.type == _MVL_UI_ITEM_TEXT && (baseItem.options & KItemTextNoSquare) != 0 ) {
      if ( (layout & KLayoutRight) != 0 ) {
        TFont fnt = _mvl_ui_fonts[baseItem.data[_MVL_UI_TEXT_OFFSET_FONT]];
        item.y -= getFontHeight(fnt);
        item.x = baseItem.x;
        int freeWidth = baseItem.data[_MVL_UI_TEXT_DELTA_LAST];  // сколько пикселов свободно на последней строке
        int needWidth = item.width; // сколько пикселов требуется элементу для размещения на строке
        boolean itemNoSquaredText = item.type == _MVL_UI_ITEM_TEXT && (item.options & KItemTextNoSquare) != 0;
        if ( itemNoSquaredText ) {
           item.data[_MVL_UI_TEXT_DELTA_FIRST] = baseItem.width - baseItem.data[_MVL_UI_TEXT_DELTA_LAST];
//          item.activate();
          fnt = _mvl_ui_fonts[item.data[_MVL_UI_TEXT_OFFSET_FONT]];
          needWidth = getFontStringWidth(fnt, (String)item.v1.elementAt(0));
        }



        if ( needWidth > freeWidth ) {
          if ( itemNoSquaredText ) {
            fnt = _mvl_ui_fonts[item.data[_MVL_UI_TEXT_OFFSET_FONT]];
            item.data[_MVL_UI_TEXT_DELTA_FIRST] = 0;
            if ( item.v1.size() > 1 )
              item.data[_MVL_UI_TEXT_DELTA_LAST] = item.width-getFontStringWidth(fnt, (String)item.v1.elementAt(item.v1.size()-1));
            else
              item.data[_MVL_UI_TEXT_DELTA_LAST] = item.width-getFontStringWidth(fnt, (String)item.v1.elementAt(item.v1.size()-1))-item.data[_MVL_UI_TEXT_DELTA_FIRST];
            if ( item.data[_MVL_UI_TEXT_DELTA_LAST] < 0 )
              item.data[_MVL_UI_TEXT_DELTA_LAST] = 0;
          }
          fnt = _mvl_ui_fonts[baseItem.data[_MVL_UI_TEXT_OFFSET_FONT]];
          item.y += getFontHeight(fnt);
        }

      }
    }
    item.x += dx;
    item.y += dy;
    form.appendItem(item);
  }
  
  
  
  public final void mvlAppendItemFlow(TForm form, TItem item, int dx, int dy, int layout) {
    mvlAppendItemFlow(form, item, dx, dy, layout, 1);
  }
  
  
  
  public final void mvlScrollTo(TForm form, int x, int y) {
    form.data[_MVL_UI_FORM_OFFSET_START_POS_X] = x;
    form.data[_MVL_UI_FORM_OFFSET_START_POS_Y] = y;
  }

  


#endif  // __MVL_UI_JAVA_GLOBAL_H__

