#defineblock begin

// параметры mvl
#define ENABLE_CUSTOM_FONTS
#define ENABLE_CUSTOM_KEY_REPEATED
#define ENABLE_GUI
#define ENABLE_BACKBUFFER
#define ENABLE_POPUP_WINDOW
#define ENABLE_LIST
#define TRANSLATE_NUM_TO_ARROW
#define TRANSLATE_STAR_AND_POUND_TO_SOFT



#define WORDS_FILE            "words.bin"



#define DEVICE_240
//#define DEVICE_176
//#define DEVICE_DEFAULT

// файлы шрифтов
//#ifdef SCREEN_NONE_FUCKING_TRMS
//#else



#ifdef DEVICE_240
//  #make resourcespath "240"
  #make outputfile "words240"
  #make res + "f240.bin"
  #make res + "fb240.bin"

  #define FONT_DEFAULT_FILE     "f240.bin"
  #define FONT_BOLD_FILE        "fb240.bin"

#elseif DEVICE_176
//  #make resourcespath "176"
  #make outputfile "words176"
  #make res + "f176.bin"
  #make res + "fb176.bin"

  #define FONT_DEFAULT_FILE     "f176.bin"
  #define FONT_BOLD_FILE        "fb176.bin"
  
#elseif DEVICE_DEFAULT
//  #make resourcespath "128"
  #make outputfile "words"
  #make res + "f.bin"
  #make res + "fb.bin"
  
  #define FONT_DEFAULT_FILE     "f.bin"
  #define FONT_BOLD_FILE        "fb.bin"

#endif

#define FONT_DEFAULT_FILE     "f.bin"
#define FONT_BOLD_FILE        "fb.bin"



//#define DEBUG
#define OBFUSCATE


// константы экранов
#define SCREEN_WAIT                       0     // экран ожидания выполнения операции
#define SCREEN_WORDS                      1
#define SCREEN_OPTIONS                    2
#define SCREEN_HELP                       3
#define SCREEN_STATISTIC                  4
#define SCREEN_MAINMENU                   5
#define SCREEN_LIST                       6

#define MAX_SCREENS_COUNT          7            // общее количество экранов

#define WL_UNKNOWN                 0            // невыученное слово
#define WL_BAD                     1            // плоховыученное слово
#define WL_GOOD                    2            // выученное слово


// контексты messageBox()
#define MBC_WORD_COMPLETE          1            // закончились актуальные слова
#define MBC_INFO                   2            // просто информационное сообщение

#defineblock end
