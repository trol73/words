#ifnotdef __GRAPH_H__
#define   __GRAPH_H__
#defineblock begin
//----------------------------------------------------------------------------//
//                       Tr Java Mobile Builder v 1.11.                       //
//                        Runtime libraries:  GRAPH.H                         //
//                      Copyright (c) O.A. Trifonov, 2005                     //
//                                Version 1.0                                 //
//                                                                            //
//  Defines:                                                                  //
//  Macroses:                                                                 //
//                                                                            //
//                                                                            //
//                                                                            //
//  Supported devices (total 10 types):                                       //
//                                                                            //
//    Motorola      V300/V400/V500, T720, C650                                //
//                                                                            //
//    SonyEricsson  T610, K700                                                //
//                                                                            //
//    Nokia         Series 40, Series 60                                      //
//                                                                            //
//    Samsung       E700, X600                                                //
//                                                                            //
//    Siemens       55                                                        //
//                                                                            //
//    Siemens       65                                                        //
//                                                                            //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//                       константы размеров экранов                           //
//----------------------------------------------------------------------------//
#ifdef    MOTOROLA_V300

  #define     SCREEN_WIDTH           176
  #define     SCREEN_HEIGHT          185
  #define     SCREEN_FULL_HEIGHT     205
  #define     FULL_SCREEN
  
#elseif   MOTOROLA_T720

  #define     SCREEN_WIDTH           120
  #define     SCREEN_HEIGHT          146
  #define     SCREEN_FULL_HEIGHT     160
  #define     FULL_SCREEN
  
#elseif   SONYERICSSON_T610

  #define     SCREEN_WIDTH           127
  #define     SCREEN_HEIGHT          128
  #define     SCREEN_FULL_HEIGHT     128
  
#elseif   SONYERICSSON_K700

  #define     SCREEN_WIDTH           176
  #define     SCREEN_HEIGHT          176
  #define     SCREEN_FULL_HEIGHT     220
  #define     FULL_SCREEN
  
#elseif   NOKIA_SERIES_40

  #define     SCREEN_WIDTH           128
  #define     SCREEN_HEIGHT          128
  #define     SCREEN_FULL_HEIGHT     128
  #define     FULL_SCREEN

#elseif   NOKIA_SERIES_60

  #define     SCREEN_WIDTH           176
  #define     SCREEN_HEIGHT          208
  #define     SCREEN_FULL_HEIGHT     208
  #define     FULL_SCREEN

#elseif   SAMSUNG_E700

  #define     SCREEN_WIDTH           128
  #define     SCREEN_HEIGHT          140
  #define     SCREEN_FULL_HEIGHT     160
  #define     FULL_SCREEN
  
#elseif   SAMSUNG_X600

  #define     SCREEN_WIDTH           128
  #define     SCREEN_HEIGHT          110
  #define     SCREEN_FULL_HEIGHT     128
  #define     FULL_SCREEN
  
#elseif   SIEMENS_55

  #define     SCREEN_WIDTH           101
  #define     SCREEN_HEIGHT          80
  #define     SCREEN_FULL_HEIGHT     80
  #define     FULL_SCREEN

#elseif   SIEMENS_65

  #define     SCREEN_WIDTH           132
  #define     SCREEN_HEIGHT          176
  #define     SCREEN_FULL_HEIGHT     176
  #define     FULL_SCREEN

#elseif   MOTOROLA_C650

  #define     SCREEN_WIDTH           128
  #define     SCREEN_HEIGHT          99
  #define     SCREEN_FULL_HEIGHT     116
  #define     FULL_SCREEN
  

#elseif  ABSTRACT_MIDP1

  #define     SCREEN_WIDTH           128
  #define     SCREEN_HEIGHT          99
  #define     SCREEN_FULL_HEIGHT     116


#elseif  ABSTRACT_MIDP2

  #define     SCREEN_WIDTH           128
  #define     SCREEN_HEIGHT          99
  #define     SCREEN_FULL_HEIGHT     116
  #define     FULL_SCREEN

#endif

//----------------------------------------------------------------------------//
//                       константы рисования                                  //
//----------------------------------------------------------------------------//
// стили линий
#define       SOLID                         Graphics.SOLID
#define       DOTTED                        Graphics.DOTTED
// положение при рисовании
#define       AL_TOP                        Graphics.TOP
#define       AL_BOTTOM                     Graphics.BOTTOM
#define       AL_LEFT                       Graphics.LEFT
#define       AL_RIGHT                      Graphics.RIGHT
#define       AL_BASELINE                   Graphics.BASELINE
#define       AL_HCENTER                    Graphics.HCENTER
#define       AL_VCENTER                    Graphics.VCENTER
// константы шрифтов
#define       FACE_MONOSPACE                Font.FACE_MONOSPACE
#define       FACE_PROPORTIONAL             Font.FACE_PROPORTIONAL
#define       FACE_SYSTEM                   Font.FACE_SYSTEM
#define       FONT_INPUT_TEXT               Font.FONT_INPUT_TEXT
#define       FONT_STATIC_TEXT              Font.FONT_STATIC_TEXT
#define       SIZE_LARGE                    Font.SIZE_LARGE
#define       SIZE_MEDIUM                   Font.SIZE_MEDIUM
#define       SIZE_SMALL                    Font.SIZE_SMALL
#define       STYLE_BOLD                    Font.STYLE_BOLD
#define       STYLE_ITALIC                  Font.STYLE_ITALIC
#define       STYLE_PLAIN                   Font.STYLE_PLAIN
#define       STYLE_UNDERLINED              Font.STYLE_UNDERLINED
//------------------------------------------------------------------------------
  #ifdef MIDP_2

#macro translateHorisontal(source, x, y, width, height)
Image.createImage(source, x, y, width, height, Sprite.TRANS_MIRROR_ROT180)
#endmacro
  
#macro translateVertical(source, x, y, width, height)
Image.createImage(source, x, y, width, height, Sprite.TRANS_MIRROR)
#endmacro
  
#macro createSprite(source, x, y, width, height)
Image.createImage(source, x, y, width, height, Sprite.TRANS_NONE)
#endmacro

  #endif // MIDP_2
#defineblock end
#endif
