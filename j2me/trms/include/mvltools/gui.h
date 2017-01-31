/******************************************************************************
                                Trol MobileStudio
                                                                              
                            Runtime libraries:  gui.h
                                                                              
                            																	 


    Created: 17.02.2008  11:46:20                                                   
    Autor: Trifonov O.A.
    Version: 1.0.05
    
    Export:
      bool mvlToolsProcessKeyActionEvent(int action)


      TForm mvltCreateForm(int screen, TString caption)
        создает стандартную форму с заголовком и скроллом
        
      TItem mvltCreateList(int screen, TString caption)
        создает стандартный экран списка с заголовком и скроллом
        
      void mvltCreateScreenDone(bool setAndPaint)
        завершает создание формы или списка. если setAndPaint установлен, то устанавливает экран и выполняет прорисовку
        
      void mvltAppendListItem(TString name, TImage icon);
        добавляем элемент к списку формы
        
      void mvltAppendToScreen(TItem item)
        добавляет элемент (сфот-книпку) к форме или списку

      TItem mvltAppendLabel(TString str)
        добавляет метку элемента к форме
        
      void mvltAppendListItems(TStrings names, TImages icons)
        добавляет массив элементов к списку формы
        
      TItem mvltAppendEditor(TString text, int maxLength, int textType, TString caption)
        добавляет поле ввода к форме

      TItem mvltAppendStaticText(TString str)
        добавляет простую строку текста
        
      TItem mvltAppendButton(TString caption, TString context)
        добавляет кнопку к форме
        
      TItem mvltAppendCheckbox(TString caption, bool checked)
        добавляет чекбокс к форме

      TItem mvltAppendCombobox(TStrings items)
        добавляет комбобокс к форме

                                                                              
******************************************************************************/

// обработчик событий клавиатуры
// возвращает true, если событие было поглощено
//   - работа с messageBox
public final bool mvlToolsProcessKeyActionEvent(int action) {
  // проверка выбора в messageBox-е
  if ( _mvl_tools__messageBox_context_ > 0 && mvlGetPushedWindowsCount() > 0) {
    int keyRes;
    if ( action == ACT_SOFT1 && (_mvl_tools_messageBox_buttons_ & 1) != 0 )
      keyRes = 1;
    else if ( action == ACT_SOFT2 && (_mvl_tools_messageBox_buttons_ & 2) != 0 )
      keyRes = 2;
    else
      keyRes = 0;
    if ( keyRes != 0 ) {
      mvlPopWindow();
      int context = _mvl_tools__messageBox_context_;
      _mvl_tools__messageBox_context_  = -1;
      onMessageBoxEnter(context, keyRes);
      return true;
    }
  } // messageBox
  
  return false;
}


//-------------------------------------------------------------------------------------------------
// процедуры быстрой разработки gui


// переменные
static int _mvl_tools_gui_screen_;
static TForm _mvl_tools_gui_form_;
static TItem _mvl_tools_gui_list_;
static TItem _mvl_tools_gui_caption_;
static TItem _mvl_tools_gui_scroll_;
static bool _mvl_tools_gui_mainItemInserted;


// создает стандартную форму с заголовком и скроллом
final TForm mvltCreateForm(int screen, TString caption) {
  return mvltCreateForm(screen, caption, 0, 0, getScreenWidth(), getScreenHeight());
}


final TForm mvltCreateForm(int screen, TString caption, int x, int y, int width, int height) {
  _mvl_tools_gui_screen_ = screen;
  _mvl_tools_gui_mainItemInserted = false;
  if ( screen >= 0 )
    mvlRemoveAllScreenItems(_mvl_tools_gui_screen_);
  int h = getFontHeight(fontBold) + 4;

  _mvl_tools_gui_form_ = mvlCreateForm(x, y+h, width, height-2*h+4, KItemFormActive|KItemFormScrollV);
  mvlSetItemColors(_mvl_tools_gui_form_, MVLTC_FORM_BACKGROUND, MVLTC_FORM_BACKGROUND);

  _mvl_tools_gui_caption_ = mvlCreateText(x, y, width, h, caption, KItemTextNoWrap);
  mvlSetItemFont(_mvl_tools_gui_caption_, fntBold);
  mvlSetItemColors(_mvl_tools_gui_caption_, MVLTC_CAPTION_COLOR, MVLTC_CAPTION_BACKGROUND);

  _mvl_tools_gui_scroll_ = mvlCreateScrollBar(x+width-5, y+h, 5, height-2*h+4, KScrollBarVertical|KScrollBarFillEmpty);
  mvlAssignScrollBarToControl(_mvl_tools_gui_scroll_, _mvl_tools_gui_form_);


  return _mvl_tools_gui_form_;
}



// создает стандартный экран списка с заголовком и скроллом
TItem mvltCreateList(int screen, TString caption, int options) {
  _mvl_tools_gui_screen_ = screen;
  _mvl_tools_gui_mainItemInserted = false;
  
  if ( screen > 0 )
    mvlRemoveAllScreenItems(_mvl_tools_gui_screen_);

  int h = getFontHeight(fontBold) + 4;

  _mvl_tools_gui_form_ = mvlCreateForm(0, 0, getScreenWidth(), getScreenHeight(), KItemFormActive);
  _mvl_tools_gui_caption_ = mvlCreateText(0, 0, getScreenWidth(), h, caption, KItemTextNoWrap);
  mvlSetItemFont(_mvl_tools_gui_caption_, fntBold);
  mvlSetItemColors(_mvl_tools_gui_caption_, MVLTC_CAPTION_COLOR, MVLTC_CAPTION_BACKGROUND);

  _mvl_tools_gui_list_ = mvlCreateList(0, h, getScreenWidth(), getScreenHeight()-2*h+4, options);
  _mvl_tools_gui_scroll_ = mvlCreateScrollBar(getScreenWidth()-5, h, 5, getScreenHeight()-2*h+4, KScrollBarVertical);//|KScrollBarFillEmpty);

  mvlAssignScrollBarToControl(_mvl_tools_gui_scroll_, _mvl_tools_gui_list_);
  mvlAppendItem(_mvl_tools_gui_form_, _mvl_tools_gui_list_);
  mvlAppendItem(_mvl_tools_gui_form_, _mvl_tools_gui_caption_);
  mvlAppendItem(_mvl_tools_gui_form_, _mvl_tools_gui_scroll_);
  if ( _mvl_tools_gui_screen_ > 0 )
    mvlAppendScreenForm(_mvl_tools_gui_screen_, _mvl_tools_gui_form_);

  return _mvl_tools_gui_list_;
}


TItem mvltCreateList(int screen, TString caption) {
  return mvltCreateList(screen, caption, KItemListText|KitemListCircular);
}


// добавляет элемент (сфот-книпку) к форме или списку
void mvltAppendToScreen(TItem item) {
  if ( _mvl_tools_gui_list_ == null ) {
    if ( !_mvl_tools_gui_mainItemInserted ) {
      mvlAppendScreenForm(_mvl_tools_gui_screen_, _mvl_tools_gui_form_);
      _mvl_tools_gui_mainItemInserted = true;
    } else if ( !_mvl_tools_gui_mainItemInserted ) {
      mvlAppendScreenForm(_mvl_tools_gui_screen_, _mvl_tools_gui_list_);
      _mvl_tools_gui_mainItemInserted = true;
    }
  }
  mvlAppendScreenForm(_mvl_tools_gui_screen_, item);
}


// добавляет элемент к списку формы
void mvltAppendListItem(TString name, TImage icon) {
  mvlAppendItemString(_mvl_tools_gui_list_, name);
  mvlAppendItemImage(_mvl_tools_gui_list_, icon);
}


// добавляет массив элементов к списку формы
void mvltAppendListItems(TStrings names, TImages icons) {
  int len = names == null ? icons.length : names.length;
  for ( int i = 0; i < len; i++ ) {
    mvlAppendItemString(_mvl_tools_gui_list_, names != null ? names[i] : "");
    mvlAppendItemImage(_mvl_tools_gui_list_, icons != null ? icons[i] : null);
  }
}



// завершает создание формы или списка. если setAndPaint установлен, то устанавливает экран и выполняет прорисовку
void mvltCreateScreenDone(bool setAndPaint) {
  if ( _mvl_tools_gui_list_ == null ) {
    if ( !_mvl_tools_gui_mainItemInserted )
      mvlAppendScreenForm(_mvl_tools_gui_screen_, _mvl_tools_gui_form_);
    mvlAppendScreenForm(_mvl_tools_gui_screen_, _mvl_tools_gui_caption_);
    mvlAppendScreenForm(_mvl_tools_gui_screen_, _mvl_tools_gui_scroll_);
  } else {
    mvlActivateItem(_mvl_tools_gui_list_);
    mvlActivateItem(_mvl_tools_gui_scroll_);
  }
  _mvl_tools_gui_form_ = null;
  _mvl_tools_gui_list_ = null;
  _mvl_tools_gui_caption_ = null;
  _mvl_tools_gui_scroll_ = null;
  if ( setAndPaint ) {
    setScreen(_mvl_tools_gui_screen_);
    repaint();
  }
}


// добавляет метку элемента к форме
TItem mvltAppendLabel(TString str) {
  TItem itm = mvlCreateText(0, 0, getScreenWidth()-16, 0, str, KItemTextSyllableWrap);
  mvlSetItemColors(itm, MVLT_LABEL_COLOR, MVLT_LABEL_BACKGROUND);
  mvlSetItemFont(itm, fntBold);
  mvlAppendItemFlow(_mvl_tools_gui_form_, itm, MVLT_LABEL_DELTA_X, MVLT_LABEL_DELTA_Y, KLayoutLeft|KLayoutBotom|KLayoutNewLine);
  return itm;
}


// добавляет поле ввода к форме
TItem mvltAppendEditor(TString text, int maxLength, int textType, TString caption) {
  TItem itm = mvlCreateEditor(0, 0, getScreenWidth()-20, 0, text, KItemTextActive|KItemTextActiveFrame|KItemTextNoWrap, textType, maxLength, caption);
  mvlSetItemColors(itm, MVLT_LABEL_COLOR, MVLT_LABEL_BACKGROUND);
  mvlAppendItemFlow(_mvl_tools_gui_form_, itm, MVLT_EDITOR_DELTA_X, MVLT_EDITOR_DELTA_Y, KLayoutLeft|KLayoutBotom|KLayoutNewLine);
  return itm;
}


// добавляет простую строку текста
TItem mvltAppendStaticText(TString str) {
  TItem itm = mvlCreateText(0, 0, getScreenWidth()-16, 0, str, KItemTextSyllableWrap);
  mvlSetItemColors(itm, MVLT_STATICTEXT_COLOR, MVLT_STATICTEXT_BACKGROUND);
  mvlAppendItemFlow(_mvl_tools_gui_form_, itm, MVLT_STATICTEXT_DELTA_X, MVLT_STATICTEXT_DELTA_Y, KLayoutLeft|KLayoutBotom|KLayoutNewLine);
  return itm;
}


// добавляет кнопку к форме
TItem mvltAppendButton(TString caption, TString context) {
  TItem itm = mvlCreateButton(0, 0, 0, 0, caption, KItemButtonActiveFrame);
  mvlSetItemFont(itm, fntBold);
  mvlSetItemContextString(itm, context);
  mvlAppendItemFlow(_mvl_tools_gui_form_, itm, MVLT_BUTTON_DELTA_X, MVLT_BUTTON_DELTA_Y, KLayoutLeft|KLayoutBotom|KLayoutNewLine);
  return itm;
}


// добавляет чекбокс к форме
TItem mvltAppendCheckbox(TString caption, bool checked) {
  TItem itm = mvlCreateChoiceGroup(0, 0, 0, 0, KChoiceCheckBox);
  mvlSetItemString(itm, caption);
  mvlSetItemColors(itm, MVLT_CHECKBOX_COLOR, MVLT_CHECKBOX_BACKGROUND);
  mvlSetItemFont(itm, fntBold);
  mvlAppendItemFlow(_mvl_tools_gui_form_, itm, MVLT_CHECKBOX_DELTA_X, MVLT_CHECKBOX_DELTA_Y, KLayoutLeft|KLayoutBotom|KLayoutNewLine);
  mvlSetItemChecked(itm, 0, checked);
  return itm;
}


// добавляет комбобокс к форме
TItem mvltAppendCombobox(TStrings items) {
  TItem itm = mvlCreateChoiceGroup(0, 0, 0, 0, KChoiceComboBox);
  for ( int i = 0; i < items.length; i++ )
    mvlAppendItemString(itm, items[i]);
  mvlSetItemColors(itm, MVLT_COMBOBOX_COLOR, MVLT_COMBOBOX_BACKGROUND);
  mvlSetItemFont(itm, fntBold);
  mvlAppendItemFlow(_mvl_tools_gui_form_, itm, MVLT_COMBOBOX_DELTA_X, MVLT_COMBOBOX_DELTA_Y, KLayoutLeft|KLayoutBotom|KLayoutNewLine);
  return itm;
}


// возвращает массив пиктограмм, у которых ширина равна высоте, из файла. пиктограмки должны распологаться в файле
// в одну строку
TImages mvltLoadImages(TString fileName) {
  TImage img = createImage(fileName);
  int w = getImageWidth(img);
  int h = getImageHeight(img);
  int c = w/h;
  TImages result = imagesLibCreate(c);
  int x = 0;
  for ( int i = 0; i < c; i++) {
    result[i] = createImage(img, x, 0, h, h, KTransformNone);
    x += h;
  }
  return result;
}
