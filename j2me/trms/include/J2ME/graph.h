/******************************************************************************
                              Trol MobileStudio

                                J2ME platform

                       Runtime libraries:  J2ME\GRAPH.H

                        Модуль подпрограм рисования

                   Copyright (c) by O.A. Trifonov, 2004-2006

    Created: 07.08.2006


******************************************************************************/

//----------------------------------------------------------------------------//
//                              макроопределения                              //
//----------------------------------------------------------------------------//
// типы
#define Font                       javax.microedition.lcdui.Font
#define Image                      javax.microedition.lcdui.Image

// шрифты
#define FONT_FACE_SYSTEM           javax.microedition.lcdui.Font.FACE_SYSTEM
#define FONT_FACE_MONOSPACE        javax.microedition.lcdui.Font.FACE_MONOSPACE
#define FONT_FACE_PROPORTIONAL     javax.microedition.lcdui.Font.FACE_PROPORTIONAL

#define FONT_STYLE_PLAIN           javax.microedition.lcdui.Font.STYLE_PLAIN
#define FONT_STYLE_BOLD            javax.microedition.lcdui.Font.STYLE_BOLD
#define FONT_STYLE_ITALIC          javax.microedition.lcdui.Font.STYLE_ITALIC
#define FONT_STYLE_UNDERLINED      javax.microedition.lcdui.Font.STYLE_UNDERLINED

#define FONT_SIZE_SMALL            javax.microedition.lcdui.Font.SIZE_SMALL
#define FONT_SIZE_MEDIUM           javax.microedition.lcdui.Font.SIZE_MEDIUM
#define FONT_SIZE_LARGE            javax.microedition.lcdui.Font.SIZE_LARGE

// якоря рисования
#define DRAW_ANCHOR_BASELINE       javax.microedition.lcdui.Graphics.BASELINE
#define DRAW_ANCHOR_BOTTOM         javax.microedition.lcdui.Graphics.BOTTOM
#define DRAW_ANCHOR_HCENTER        javax.microedition.lcdui.Graphics.HCENTER
#define DRAW_ANCHOR_LEFT           javax.microedition.lcdui.Graphics.LEFT
#define DRAW_ANCHOR_RIGHT          javax.microedition.lcdui.Graphics.RIGHT
#define DRAW_ANCHOR_TOP            javax.microedition.lcdui.Graphics.TOP
#define DRAW_ANCHOR_VCENTER        javax.microedition.lcdui.Graphics.VCENTER
// x:   LEFT     RIGHT     HCENTER
// y:   TOP      BOTTOM    BASELINE    VCENTER



//----------------------------------------------------------------------------//
//                        установка параметров рисования                      //
//----------------------------------------------------------------------------//


//----------------------------------------------------------------------------//
//   void setColor(int color)
// задает текущий цвет рисования и заливки
#macro setColor(color)
g.setColor(color)
#endmacro

//------------------------------------------------------------------------------
//   void setColor(int r, int g, int b)
// задает текущий цвет рисования и заливки по компонентам (r, g, b)
#macro setColor(r, g, b)
g.setColor(r, g, b)
#endmacro

//------------------------------------------------------------------------------
//   void setGlobalAlpha(int alpha)
// задает уровень прозрачности
#macro setGlobalAlpha(alpha)
#endmacro

//------------------------------------------------------------------------------
//   void setColor(int r, int g, int b, int alpha)
// задает текущий цвет рисования и заливки по компонентам (r, g, b) и прозрачность в alpha
#macro setColor(r, g, b, alpha)
g.setColor(r, g, b)
#endmacro

//------------------------------------------------------------------------------
//   void setClip(int x, int y, int w, int h)
// устанавливает размеры доступной для рисования области
#macro setClip(x, y, w, h)
g.setClip(x, y, w, h)
#endmacro

//------------------------------------------------------------------------------
//   void setClip()
// делает весь экран доступным для рисования
#macro setClip()
g.setClip(0, 0, getWidth(), getHeight());
#endmacro

//------------------------------------------------------------------------------
//   void translate(int x, int y)
// переносит начало координат в точку (x, y)
#macro translate(x, y)
g.translate(x, y)
#endmacro


//----------------------------------------------------------------------------//
//                            работа со шрифтами                              //
//----------------------------------------------------------------------------//

//------------------------------------------------------------------------------
//   Font createFont(int face, int style, int size)
// возвращает созданный шрифт
//   face - вид шрифта  (один из FONT_FACE_SYSTEM, FONT_FACE_MONOSPACE, or FONT_FACE_PROPORTIONAL)
//   style - стиль шрифта (FONT_STYLE_PLAIN, или комбинация FONT_STYLE_BOLD, FONT_STYLE_ITALIC, FONT_STYLE_UNDERLINED
//   size - размер шрифта (оди нз FONT_SIZE_SMALL, FONT_SIZE_MEDIUM, или FONT_SIZE_LARGE)
#macro createFont(face, style, size)
Font.getFont(face, style, size)
#endmacro

//------------------------------------------------------------------------------
//   void setFont(Font font)
// задает шрифт для вывода строк
#macro setFont(font)
g.setFont(font)
#endmacro

//------------------------------------------------------------------------------
//   void setFont(int face, int style, int size)
// задает шрифт для вывода строк
#macro setFont(face, style, size)
g.setFont(Font.createFont(face, style, size));
#endmacro

//----------------------------------------------------------------------------//
//                           рисование примитивов                             //
//----------------------------------------------------------------------------//

//------------------------------------------------------------------------------
//   void drawLine(int x1, int y1, int x2, int y2)
// рисует линию из точки (x1, y1) в точку (x2, y2)
#macro drawLine(x1, y1, x2, y2)
g.drawLine(x1, y1, x2, y2)
#endmacro

//------------------------------------------------------------------------------
//   void drawHLine(int x1, int y, int x2)
// рисует горизонтальную линию из точки (x1, y) в точку (x2, y)
#macro drawHLine(x1, y, x2)
g.drawLine(x1, y, x2, y)
#endmacro

//------------------------------------------------------------------------------
//   void drawVLine(int x, int y1, int y2)
// рисует вертикальную линию из точки (x, y1) в точку (x, y2)
#macro drawVLine(x, y1, y2)
g.drawLine(x, y1, x, y2)
#endmacro

//------------------------------------------------------------------------------
//   void drawRect(int x, int y, int w, int h)
// рисует прямоугольник
#macro drawRect(x, y, w, h)
g.drawRect(x, y, w, h)
#endmacro

//------------------------------------------------------------------------------
//   void drawRoundRect(int x, int y, int w, int h, int arcWidth, int arcHeight)
// рисует прямоугольник (x, y, w, h) с закругленными углами
//  arcWidth - горизонтальный диаметр дуги
//  arcHeight - вертикальный диаметр дуги
#macro drawRoundRect(x, y, w, h, arcWidth, arcHeight)
g.drawRoundRect(x, y, w, h, arcWidth, arcHeight)
#endmacro

//------------------------------------------------------------------------------
//   void drawArc(int x, int y, int w, int h, int startAngle, int arcAngle)
// рисует дугу круга или эллипса, вписанного в прямоугольник (x, y, w, h)
//  startAngle - угол, от которого начинает рисоваться дуга
//  arcAngle - угловая длина дуги
// дуга рисуется ПРОТИВ часовой стрелки в следующих координатах
//                o
//            | 90
//     o      |       o
//  180  ----------- 0
//           o|
//        270 |
//------------------------------------------------------------------------------
#macro drawArc(x, y, w, h, startAngle, arcAngle)
g.drawArc(x, y, w-1, h-1, startAngle, arcAngle)
#endmacro

//------------------------------------------------------------------------------
//   void drawCircle(int x, int y, int r)
// рисует окружность радиуса r с центром в точке (x, y)
#macro drawCircle(x, y, r)
g.drawArc(x, y, r-1, r-1, 0, 360)
#endmacro


//----------------------------------------------------------------------------//
//                           закраска примитивов                              //
//----------------------------------------------------------------------------//

//------------------------------------------------------------------------------
//   void fillRect(int x, int y, int w, int h)
// закрашивает прямоугольник
#macro fillRect(x, y, w, h)
g.fillRect(x, y, w, h)
#endmacro

//------------------------------------------------------------------------------
//   void fillRect()
// закрашивает весь экран
#macro fillRect()
g.fillRect(0, 0, getWidth(), getHeight());
#endmacro

//------------------------------------------------------------------------------
//   void fillRect(int color)
// закрашивает весь экран
#macro fillRect(color)
g.setColor(color);
g.fillRect(0, 0, getWidth(), getHeight());
#endmacro

//------------------------------------------------------------------------------
//   void fillArc(int x, int y, int w, int h, int startAngle, int arcAngle)
// закрашивает круговой или эллиптический сегмент
#macro fillArc(x, y, w, h, startAngle, arcAngle)
g.fillArc(x, y, w, h, startAngle, arcAngle)
#endmacro

//------------------------------------------------------------------------------
//   void fillCircle(x, y, r)
// закрашивает окружность радиуса r с центром в точке (x, y)
#macro fillCircle(x, y, r)
g.fillArc(x, y, r, r, 0, 360)
#endmacro

//------------------------------------------------------------------------------
//   void fillRoundRect(int x, int y, int w, int h, int arcWidth, int arcHeight)
// закрашивает прямоугольник (x, y, w, h) с закругленными углами
//  arcWidth - горизонтальный диаметр дуги
//  arcHeight - вертикальный диаметр дуги
#macro fillRoundRect(x, y, w, h, arcWidth, arcHeight)
g.fillRoundRect(x, y, w, h, arcWidth, arcHeight)
#endmacro

//----------------------------------------------------------------------------//
//                           рисование текста                                 //
//----------------------------------------------------------------------------//

//------------------------------------------------------------------------------
//   void drawChar(char ch, int x, int y, int anchor)
// рисует символ ch в точку (x, y) с выравниванием anchor
#macro drawChar(ch, x, y, anchor)
g.drawChar(ch, x, y, anchor)
#endmacro

//------------------------------------------------------------------------------
//   void drawChar(char ch, int x, int y)
// рисует символ ch в точку (x, y) с выравниванием LEFT | TOP
#macro drawChar(ch, x, y)
g.drawChar(ch, x, y, Graphics.LEFT|Graphics.TOP)
#endmacro

//------------------------------------------------------------------------------
//   void drawChars(char[] data, int offset, int length, int x, int y, int anchor)
// рисует length символов массива data начиная с offset-го в точку (x, y)
// с выравниванием anchor
#macro drawChars(data, offset, length, x, y, anchor)
g.drawChars(data, offset, length, x, y, anchor)
#endmacro

//------------------------------------------------------------------------------
//   void drawChars(char[] data, int offset, int length, int x, int y)
// рисует length символов массива data начиная с offset-го в точку (x, y)
// с выравниванием LEFT | TOP
#macro drawChars(data, offset, length, x, y)
g.drawChars(data, offset, length, x, y, javax.microedition.lcdui.Graphics.LEFT|javax.microedition.lcdui.Graphics.TOP)
#endmacro

//------------------------------------------------------------------------------
//   void drawString(String str, int x, int y, int anchor)
// рисует строку str в точку (x, y) с выравниванием anchor
#macro drawString(str, x, y, anchor)
g.drawString(str, x, y, anchor)
#endmacro

//------------------------------------------------------------------------------
//   void drawString(String str, int x, int y)
// рисует строку str в точку (x, y) с выравниванием LEFT | TOP
#macro drawString(str, x, y)
g.drawString(str, x, y, javax.microedition.lcdui.Graphics.LEFT|javax.microedition.lcdui.Graphics.TOP)
#endmacro

//------------------------------------------------------------------------------
//   void drawSubstring(String str, int offset, int len, int x, int y, int anchor)
// рисует len символов подстроки str в начиная с offset в точку (x, y) с
// выравниванием anchor
#macro drawSubstring(str, offset, len, x, y, anchor)
g.drawSubstring(str, offset, len, x, y, anchor)
#endmacro

//------------------------------------------------------------------------------
//   void drawSubstring(String str, int offset, int len, int x, int y, int anchor)
// рисует строку str в точку (x, y) с выравниванием LEFT | TOP
#macro drawSubstring(str, offset, len, x, y)
g.drawSubstring(str, offset, len, x, y, javax.microedition.lcdui.Graphics.LEFT|javax.microedition.lcdui.Graphics.TOP)
#endmacro
//------------------------------------------------------------------------------


//----------------------------------------------------------------------------//
//                           рисование изображений                            //
//----------------------------------------------------------------------------//

//------------------------------------------------------------------------------
//   Image createImage(Image img, String name)
// загруженное изображение img из файла с именем name
#macro createImage(img, name)
#ifdef DEBUG
try { img = javax.microedition.lcdui.Image.createImage("/"+name); } catch (Exception e) { System.out.println(">> FATAL ERROR! >> createImage() -> file not found.\n" + e.toString()); }
#else
try { img = javax.microedition.lcdui.Image.createImage("/"+name); } catch (Exception e) {}
#endif

#endmacro

//------------------------------------------------------------------------------
//   void drawImage(Image img, int x, int y, int anchor)
// рисует изображение img в точку (x, y) с выравниванием anchor
#macro drawImage(img, x, y, anchor)
g.drawImage(img, x, y, anchor)
#endmacro

//------------------------------------------------------------------------------
//   void drawImage(Image img, int x, int y)
// рисует изображение img в точку (x, y) с выравниванием LEFT | TOP
#macro drawImage(img, x, y)
g.drawImage(img, x, y, javax.microedition.lcdui.Graphics.LEFT|javax.microedition.lcdui.Graphics.TOP)
#endmacro

//------------------------------------------------------------------------------
//   void drawSprite(Image img, int x, int y, int x0, int y0, int w, int h)
// рисует часть изображения img (x0, y0, w, h) в точку (x, y)
#macro drawSprite(img, x, y, x0, y0, w, h)
g.setClip(x, y, w, h);
g.drawImage(img, x - x0, y - y0, javax.microedition.lcdui.Graphics.LEFT|javax.microedition.lcdui.Graphics.TOP)
#endmacro


