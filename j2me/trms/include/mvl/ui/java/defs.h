#ifnotdef __MVL_UI_JAVA_DEFS_H__
#define   __MVL_UI_JAVA_DEFS_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                         User interface defines unit


                      Copyright (c) O.A. Trifonov, 2007
                                  Version 1.01

\*----------------------------------------------------------------------------*/


// Item types
#define _MVL_UI_ITEM_TEXT                    1
#define _MVL_UI_ITEM_IMAGE                   2
#define _MVL_UI_ITEM_FORM                    3
#define _MVL_UI_ITEM_EDITOR                  4
#define _MVL_UI_ITEM_CHOICE_GROUP            5
#define _MVL_UI_ITEM_BUTTON                  6
#define _MVL_UI_ITEM_SCROLLBAR               7
#define _MVL_UI_ITEM_LIST                    8
#define _MVL_UI_ITEM_SOFT_BUTTON             9

#define _MVL_UI_ITEM_MENU_WINDOW             10
#define _MVL_UI_ITEM_WINDOW                  11

// Items options
// Text
#define KItemTextActive                      1
#define KItemTextActiveFrame                 2
#define KItemTextSyllableWrap                4
#define KItemTextChangeOnFocus               8
#define KItemTextUnderlined                  16
#define KItemTextUnderlinedOnFocus           32
#define KItemTextNoWrap                      64
#define KItemTextNoSquare                    128
// Image
#define KItemImageActive                     1
#define KItemImageDouble                     2
#define KItemImageActiveFrame                4
#define KItemImageAnimated                   8
// Form
#define KItemFormActive                      1
#define KItemFormScrollV                     2
#define KItemFormScrollH                     4
// Editor
// text type
#define KTextTypeAny                       javax.microedition.lcdui.TextField.ANY            // 0
#define KTextTypeEmail                     javax.microedition.lcdui.TextField.EMAILADDR      // 1
#define KTextTypeNumberic                  javax.microedition.lcdui.TextField.NUMERIC        // 2
#define KTextTypePhone                     javax.microedition.lcdui.TextField.PHONENUMBER    // 3
#define KTextTypeUrl                       javax.microedition.lcdui.TextField.URL            // 4
#define KTextTypeDecimal                   javax.microedition.lcdui.TextField.DECIMAL        // 5
#define KTextTypePassword                  javax.microedition.lcdui.TextField.PASSWORD       // 0x10000
#define KTextTypeNotSaveT9                 javax.microedition.lcdui.TextField.SENSITIVE      // 0x40000
#define KTextTypeNotSearchT9               javax.microedition.lcdui.TextField.NON_PREDICTIVE // 0x80000
#define KTextTypeDate                      10  // DD.MM.YYYY
#define KTextTypeTime                      11  // HH:MM:SS
#define KTextTypeDateTime                  12  // HH:MM:SS DD.MM.YYYY

// ChoiceGroup
#define KChoiceRadioBox                    1
#define KChoiceCheckBox                    2
#define KChoiceComboBox                    4

// Button
#define KItemButtonActiveFrame		         1    // в сфокусированном состоянии обводится рамкой
#define KItemButtonUnderlined		           2    // текст не в фокусе подчеркивается
#define KItemButtonUnderlinedOnFocus	     4    // текст в фокусе подчеркивается

// ScrollBar
#define KScrollBarVertical		             1    // вертикальный скроллбар
#define KScrollBarHorisontal               2    // горизонтальный скроллбар
#define KScrollBarNoGradientBack           4    // поле скроллбара не имеет градиентной заливки
#define KScrollBarFillEmpty                8    // закрашивать фоном контролируемого элемента, если нечего прокручивать

// PopupMenuWindow
#define KMenuWindowRadio                   1    // все добавляемые элементы меню становятся радиокнопками

// List
#define KItemListText		                   1    // только текст
#define KItemListIcon		                   2    // только рисунки
#define KItemListIconText	                 4    // сначала иконка, потом надпись
#define KItemListTextIcon	                 8    // сначала надпись, потом иконка
#define KItemListUnderlined                16   // рисовать текст подчеркнутым
#define KItemListUnderlinedOnFocus         32   // рисовать активный текст
#define KitemListCircular                  64   // при прокрутке до конца переходить в начало, при прокрутке за первый элемент переходить в конец

// Window
#define KItemWindowActive                  1
#define KItemWindowScrollV                 2
#define KItemWindowScrollH                 4
#define KItemWindowNoFrame                 8

// SoftButton
#define KItemSoftButtonLeft                1
#define KItemSoftButtonRight               2
#define KItemSoftButtonCenter              4
#define KItemSoftButtonClear               8



// Aligment options
#define KAlignLeft                           javax.microedition.lcdui.Graphics.LEFT
#define KAlignRight                          javax.microedition.lcdui.Graphics.RIGHT
#define KAlignTop                            javax.microedition.lcdui.Graphics.TOP
#define KAlignBottom                         javax.microedition.lcdui.Graphics.BOTTOM
#define KAlignHCenter                        javax.microedition.lcdui.Graphics.HCENTER
#define KAlignVCenter                        javax.microedition.lcdui.Graphics.VCENTER
#define KAlignCenter                         (javax.microedition.lcdui.Graphics.HCENTER+javax.microedition.lcdui.Graphics.VCENTER)

// Layout options
#define KLayoutLeft            1
#define KLayoutRight           2
#define KLayoutHCenter         4
#define KLayoutTop             8
#define KLayoutBotom           16
#define KLayoutVCenter         32
#define KLayoutNewLine         64



// Events
#define EVENT_ACTIVATE                       1   // элемент получает фокус
#define EVENT_DEACTIVATE                     2   // элемент теряет фокус
#define EVENT_PUSH                           4   // "нажатие" на элемент
#define EVENT_WINDOW_POPUP                   8   // над сфокусированной формой всплывает окно, "оттеняя" ее
#define EVENT_WINDOW_CLOSE                   16  // над "оттененной" сфокусированной формой закрывается последнее всплывшее окно возвращая ей управление
#define EVENT_BEFORE_EDIT                    32  // перед редактированием текста
#define EVENT_AFTER_EDIT                     64  // после редактированием текста
#define EVENT_CHANGE                         128 // изменение
#define EVENT_SCROLL_UP                      256 // скроллинг формы вверх
#define EVENT_SCROLL_DOWN                    512 // скроллинг формы вниз


/*
// Layout options
#define KLayoutLeft                          1
#define KLayoutRight                         2
#define KLayoutCenter                        4
#define KLayoutGrid                          8
#define KLayoutNext                          16
#define KLayoutBottom                        32
#define KLayoutNewline                       64
*/

// ItemText
#define  _MVL_UI_TEXT_DATA_LENGTH            10

#define  _MVL_UI_TEXT_OFFSET_COLOR           0
#define  _MVL_UI_TEXT_OFFSET_BACKGROUND      1
#define  _MVL_UI_TEXT_OFFSET_FONT            2
#define  _MVL_UI_TEXT_OFFSET_F_COLOR         3
#define  _MVL_UI_TEXT_OFFSET_F_BACKGROUND    4
#define  _MVL_UI_TEXT_OFFSET_F_FONT          5
#define  _MVL_UI_TEXT_OFFSET_ALIGN           6
#define  _MVL_UI_TEXT_OFFSET_INTERVAL        7
//#define  _MVL_UI_TEXT_OFFSET_STATUS          8
// до сих пор совпадает со структурой редактора текста
#define  _MVL_UI_TEXT_DELTA_FIRST            8   // расстояние от левой границы до начала первого символа первой строки
#define  _MVL_UI_TEXT_DELTA_LAST             9   // расстояние от конца последнего символа последней строки до правой границы

//#define  _MVL_UI_TEXT_STATUS_READY           0   // элемент готов к отображению
//#define  _MVL_UI_TEXT_STATUS_FORMAT          1   // необходимо выполнить форматирование текста
//#define  _MVL_UI_TEXT_STATUS_SIZE            2   // необходимо вычислить размеры элемента
//#define  _MVL_UI_TEXT_STATUS_FONT            4   // необходимо задать шрифты

// ItemImage
#define  _MVL_UI_IMAGE_DATA_LENGTH           7

#define  _MVL_UI_IMAGE_OFFSET_ALIGN          0
#define  _MVL_UI_IMAGE_OFFSET_TIME           1
#define  _MVL_UI_IMAGE_OFFSET_ANIMATE_FRAME  2
#define  _MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_W 3
#define  _MVL_UI_IMAGE_OFFSET_FRAMES_COUNT_H 4
#define  _MVL_UI_IMAGE_OFFSET_TIME_HI        5
#define  _MVL_UI_IMAGE_OFFSET_TIME_LO        6


// ItemForm
#define  _MVL_UI_FORM_DATA_LENGTH             12

#define  _MVL_UI_FORM_OFFSET_BACKGROUND       0  // цвет формы
#define  _MVL_UI_FORM_OFFSET_BACKGROUND_F     1  // цвет формы в активном состоянии
#define  _MVL_UI_FORM_OFFSET_FOCUS_INDEX      2  // индекс сфокусированного элемента
#define  _MVL_UI_FORM_OFFSET_START_POS_X      3  // координата x левого угла для скроллируемых форм
#define  _MVL_UI_FORM_OFFSET_START_POS_Y      4  // координата y верхнего угла для скроллируемых форм
#define  _MVL_UI_FORM_OFFSET_FIRST_VISIBLE    5  // индекс первого видимого элемента формы
#define  _MVL_UI_FORM_OFFSET_LAST_VISIBLE     6  // индекс последнего видимого элемента формы
#define  _MVL_UI_FORM_OFFSET_SCROLLER_SIZE    7  // ширина/высота скроллера для скроллируемых форм
#define  _MVL_UI_FORM_OFFSET_FULL_WIDTH       8  // полная ширина скроллируемой формы
#define  _MVL_UI_FORM_OFFSET_FULL_HEIGHT      9  // полная высота скроллируемой формы
#define  _MVL_UI_FORM_OFFSET_SCROLL_DX        10 // шаг скролла по горизонтали
#define  _MVL_UI_FORM_OFFSET_SCROLL_DY        11 // шаг скролла по вертикали

// ItemEditor
#define  _MVL_UI_EDITOR_DATA_LENGTH            10

#define  _MVL_UI_EDITOR_OFFSET_COLOR           0
#define  _MVL_UI_EDITOR_OFFSET_BACKGROUND      1
#define  _MVL_UI_EDITOR_OFFSET_FONT            2
#define  _MVL_UI_EDITOR_OFFSET_F_COLOR         3
#define  _MVL_UI_EDITOR_OFFSET_F_BACKGROUND    4
#define  _MVL_UI_EDITOR_OFFSET_F_FONT          5
#define  _MVL_UI_EDITOR_OFFSET_ALIGN           6
#define  _MVL_UI_EDITOR_OFFSET_INTERVAL        7
//#define  _MVL_UI_EDITOR_OFFSET_TEXT_STATUS     8
// первые записи до сих пор должны соответствовать тексту
#define  _MVL_UI_EDITOR_OFFSET_TEXT_TYPE       8    // тип текста
#define  _MVL_UI_EDITOR_OFFSET_MAX_SIZE        9   // максимальный размер редактируемого текста


// ItemChoiceGroup
#define  _MVL_UI_CHOICE_GROUP_DATA_LENGTH            10

#define  _MVL_UI_CHOICE_GROUP_OFFSET_COLOR           0
#define  _MVL_UI_CHOICE_GROUP_OFFSET_BACKGROUND      1
#define  _MVL_UI_CHOICE_GROUP_OFFSET_FONT            2
#define  _MVL_UI_CHOICE_GROUP_OFFSET_F_COLOR         3
#define  _MVL_UI_CHOICE_GROUP_OFFSET_F_BACKGROUND    4
#define  _MVL_UI_CHOICE_GROUP_OFFSET_F_FONT          5
#define  _MVL_UI_CHOICE_GROUP_OFFSET_ALIGN           6
#define  _MVL_UI_CHOICE_GROUP_OFFSET_RESULT          7
#define  _MVL_UI_CHOICE_GROUP_OFFSET_FOCUSED         8   // индекс сфокусированной строки
#define  _MVL_UI_CHOICE_GROUP_OFFSET_FLAG            9   // флаг, который используется для отслеживания событий фокусирования невидимого элемента


// ItemButton
#define  _MVL_UI_BUTTON_DATA_LENGTH            4

#define  _MVL_UI_BUTTON_OFFSET_COLOR           0
#define  _MVL_UI_BUTTON_OFFSET_FONT            1
#define  _MVL_UI_BUTTON_OFFSET_F_COLOR         2
#define  _MVL_UI_BUTTON_OFFSET_F_FONT          3


// ItemScrollBar
#define  _MVL_UI_SCROLLBAR_DATA_LENGTH         9

#define  _MVL_UI_SCROLLBAR_OFFSET_COLOR        0     // цвет бегунка
#define  _MVL_UI_SCROLLBAR_OFFSET_BACKGROUND   1     // цвет поля
#define  _MVL_UI_SCROLLBAR_OFFSET_COLOR_1      2     // верне-левый угол бегунка
#define  _MVL_UI_SCROLLBAR_OFFSET_COLOR_2      3     // нижне-правый угол бегунка
#define  _MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_1 4     //   цвета градиента фона
#define  _MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_2 5     //     слева-направо
#define  _MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_3 6     //
#define  _MVL_UI_SCROLLBAR_OFFSET_BACKGROUND_4 7     //
#define  _MVL_UI_SCROLLBAR_OFFSET_SIZE         8     // размер бегунка



// ItemMenuWindow
#define  _MVL_UI_MENU_WINDOW_DATA_LENGTH             8

#define  _MVL_UI_MENU_WINDOW_OFFSET_COLOR            0     // цвет текста
#define  _MVL_UI_MENU_WINDOW_OFFSET_ANCHOR           1     // якорь окна
#define  _MVL_UI_MENU_WINDOW_OFFSET_ACTIVE           2     // индекс текущего элемента
#define  _MVL_UI_MENU_WINDOW_OFFSET_FONT             3     // индекс шрифта
#define  _MVL_UI_MENU_WINDOW_OFFSET_F_FONT           4     // индекс шрифта в фокусе
#define  _MVL_UI_MENU_WINDOW_OFFSET_RESULT           5     // индекс выбранной радиокнопки

// ItemList
#define  _MVL_UI_LIST_DATA_LENGTH                    18

#define  _MVL_UI_LIST_OFFSET_COLOR                   0     // цвет текста
#define  _MVL_UI_LIST_OFFSET_BACKGROUND              1     // цвет фона
#define  _MVL_UI_LIST_OFFSET_F_COLOR                 2     // цвет текста текущего элемента
#define  _MVL_UI_LIST_OFFSET_F_BACKGROUND            3     // цвет фона текущего элемента
#define  _MVL_UI_LIST_OFFSET_ALIGN_TEXT              4     // выравнивание текста
#define  _MVL_UI_LIST_OFFSET_ACTIVE                  5     // индекс текущего элемента
#define  _MVL_UI_LIST_OFFSET_FONT                    6     // индекс шрифта
#define  _MVL_UI_LIST_OFFSET_F_FONT                  7     // индекс шрифта в фокусе
#define  _MVL_UI_LIST_OFFSET_VISIBLE_LINES           8     // количество строк, умещающихся в списке
#define  _MVL_UI_LIST_OFFSET_TOP_LINE                9     // абсолютный номер первой видимой строки
#define  _MVL_UI_LIST_OFFSET_INTERVAL                10    // межстрочный интервал (абсолютный)
#define  _MVL_UI_LIST_OFFSET_ICON_W                  11    // максимальная ширина иконки
#define  _MVL_UI_LIST_OFFSET_ICON_H                  12    // максимальная высота иконки
#define  _MVL_UI_LIST_OFFSET_FLAG                    13    // флаг, который используется для отслеживания событий фокусирования невидимого элемента
#define  _MVL_UI_LIST_OFFSET_ANIMATE_STR_LEN         14    // длина сфокусированной строки, если она не умещается по ширине. иначе - 0
#define  _MVL_UI_LIST_OFFSET_ANIMATE_STR_X           15    // координата Х бегущей строки
#define  _MVL_UI_LIST_OFFSET_ANIMATE_TIME_HI         16    //   время, в которое был выполнен последний шаг
#define  _MVL_UI_LIST_OFFSET_ANIMATE_TIME_LO         17    //   анимации


#define  _MVL_UI_WINDOW_DATA_LENGTH             13

#define  _MVL_UI_WINDOW_OFFSET_BACKGROUND       0  // цвет формы
#define  _MVL_UI_WINDOW_OFFSET_BACKGROUND_F     1  // цвет формы в активном состоянии
#define  _MVL_UI_WINDOW_OFFSET_FOCUS_INDEX      2  // индекс сфокусированного элемента
#define  _MVL_UI_WINDOW_OFFSET_START_POS_X      3  // координата x левого угла для скроллируемых форм
#define  _MVL_UI_WINDOW_OFFSET_START_POS_Y      4  // координата y верхнего угла для скроллируемых форм
#define  _MVL_UI_WINDOW_OFFSET_FIRST_VISIBLE    5  // индекс первого видимого элемента формы
#define  _MVL_UI_WINDOW_OFFSET_LAST_VISIBLE     6  // индекс последнего видимого элемента формы
#define  _MVL_UI_WINDOW_OFFSET_SCROLLER_SIZE    7  // ширина/высота скроллера для скроллируемых форм
#define  _MVL_UI_WINDOW_OFFSET_FULL_WIDTH       8  // полная ширина скроллируемой формы
#define  _MVL_UI_WINDOW_OFFSET_FULL_HEIGHT      9  // полная высота скроллируемой формы
#define  _MVL_UI_WINDOW_OFFSET_SCROLL_DX        10 // шаг скролла по горизонтали
#define  _MVL_UI_WINDOW_OFFSET_SCROLL_DY        11 // шаг скролла по вертикали
// до сих пор должно совпадать с полями формы
#define _MVL_UI_WINDOW_OFFSET_ANCHOR            12 // якорь выравнивания





#define  _MVL_UI_SOFT_BUTTON_DATA_LENGTH        3

#define  _MVL_UI_SOFT_BUTTON_OFFSET_COLOR       0
#define  _MVL_UI_SOFT_BUTTON_OFFSET_BACKGROUND  1
#define  _MVL_UI_SOFT_BUTTON_OFFSET_FONT        2



#defineblock end
#endif // __MVL_UI_JAVA_DEFS_H__

