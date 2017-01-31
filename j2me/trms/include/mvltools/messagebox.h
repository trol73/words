/******************************************************************************
                                 Trol MobileStudio
                                                                              
                          Runtime libraries:  messagebox.h
                                                                              
                            																	 

    Created: 17.02.2008  11:46:39                                                   
    Autor: Trifonov O.A.
    
    Export:
    
      void messageBox(TString text, TString soft1, TString soft2, int context)
        Создает всплывающее окно с сообщением text. На левую и правую софт-кнопки
        вешает подписи soft1 и soft2 соответственно. Если какая-то из софт-клавиш
        не нужна, передается null. В аргументе context передается целочисленный
        положительный дескриптор контекста, который будет получен обработчиком
        событий от окна сообщений.
                                                                              
******************************************************************************/


static int _mvl_tools__messageBox_context_ = -1;     // контекст вызванного окна сообщений
static byte _mvl_tools_messageBox_buttons_ = 0;      // битовая маска доступных кнопок в окне сообщения

// выводит окно ошибки с текстом
public final void messageBox(TString text, TString soft1, TString soft2, int context) {
  TWindow wndMessageBox;
  TForm frmMessageBox;
  TItem scrMessageBox;

  _mvl_tools__messageBox_context_ = context;
  int h = getFontHeight(fontBold) + 4;

  wndMessageBox = mvlCreateWindow(0, getScreenHeight()/2, getScreenWidth(), getScreenHeight()/2, KItemWindowActive, KAnchorLeft|KAnchorTop);
  mvlSetItemColors(wndMessageBox, MVLT_MESSAGEBOX_BACKGROUND, MVLT_MESSAGEBOX_BACKGROUND);
  frmMessageBox = mvlCreateForm(4, 4, getScreenWidth()-16, getScreenHeight()/2-h-5, KItemFormActive|KItemFormScrollV);
  mvlSetItemColors(frmMessageBox, MVLT_MESSAGEBOX_BACKGROUND, MVLT_MESSAGEBOX_BACKGROUND);

  TItem itm;
  _mvl_tools_messageBox_buttons_ = 0;
  if ( soft1 != null ) {
    _mvl_tools_messageBox_buttons_ |= 1;
    itm = mvlCreateText(3, getScreenHeight()/2-h+2, 0, 0, soft1, 0);
    mvlSetItemFont(itm, fntBold);
    mvlAppendItem(wndMessageBox, itm);
  }
  if ( soft2 != null ) {
    _mvl_tools_messageBox_buttons_ |= 2;
    itm = mvlCreateText(0, getScreenHeight()/2-h+2, getScreenWidth()-3, h, soft2, 0);
    mvlSetItemAlignment(itm, KAlignRight);
    mvlSetItemFont(itm, fntBold);
    mvlAppendItem(wndMessageBox, itm);
  }


  itm = mvlCreateText(0, 0, getScreenWidth()-20, 0, text, KItemTextSyllableWrap);
  mvlAppendItem(frmMessageBox, itm);

  mvlAppendItem(wndMessageBox, frmMessageBox);

  scrMessageBox = mvlCreateScrollBar(getScreenWidth()-8, 4, 5, getScreenHeight()/2-h-5, KScrollBarVertical|KScrollBarFillEmpty);
  mvlAssignScrollBarToControl(scrMessageBox, frmMessageBox);
  mvlAppendItem(wndMessageBox, scrMessageBox);

  mvlPushWindow(wndMessageBox);
}
