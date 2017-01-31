/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                            Graphical functions unit
                                  J2ME midlet


                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.0

\*----------------------------------------------------------------------------*/


//----------------------------------------------------------------------------//
//                             константы рисования                            //
//----------------------------------------------------------------------------//

// Константы стиля линий
#define KLineStyleSolid    javax.microedition.lcdui.Graphics.SOLID    // сплошная линия
#define KLineStyleDotted   javax.microedition.lcdui.Graphics.DOTTED   // точечный пунктир

// Константы якорей
#define KAnchorLeft        javax.microedition.lcdui.Graphics.LEFT    // разместить левый край у координаты Х
#define KAnchorRight       javax.microedition.lcdui.Graphics.RIGHT   // разместить правый край у координаты Х
#define KAnchorTop         javax.microedition.lcdui.Graphics.TOP     // разместить верх у координаты Y
#define KAnchorBottom      javax.microedition.lcdui.Graphics.BOTTOM  // разместить низ у координаты Y
#define KAnchorHCenter     javax.microedition.lcdui.Graphics.HCENTER // размещает горизонтальный центр у координаты Х
#define KAnchorVCenter     javax.microedition.lcdui.Graphics.VCENTER // размещает вертикальный центр у координаты Y

// Константы трансформирования
#define KTransformNone         javax.microedition.lcdui.game.Sprite.TRANS_NONE          // без трансформации
#define KTransformMirror       javax.microedition.lcdui.game.Sprite.TRANS_MIRROR        // отражение от вертикального центра
#define KTransformMirrorRot90  javax.microedition.lcdui.game.Sprite.TRANS_MIRROR_ROT90  // отражение от вертикального центра и поворот на 90 градусов по часовой стрелке
#define KTransformMirrorRot180 javax.microedition.lcdui.game.Sprite.TRANS_MIRROR_ROT180 // отражение от вертикального центра и поворот на 180 градусов по часовой стрелке
#define KTransformMirrorRot270 javax.microedition.lcdui.game.Sprite.TRANS_MIRROR_ROT270 // отражение от вертикального центра и поворот на 270 градусов по часовой стрелке
#define KTransformRot90        javax.microedition.lcdui.game.Sprite.TRANS_ROT90         // поворот на 90 градусов по часовой стрелке
#define KTransformRot180       javax.microedition.lcdui.game.Sprite.TRANS_ROT180        // поворот на 180 градусов по часовой стрелке
#define KTransformRot270       javax.microedition.lcdui.game.Sprite.TRANS_ROT270        // поворот на 270 градусов по часовой стрелке


//----------------------------------------------------------------------------//
//                        установка параметров рисования                      //
//----------------------------------------------------------------------------//


//   void setLineColor(TColor color)
// задает текущий цвет рисования
#macro setLineColor(color)
g.setColor(color)
#endmacro

//   void setLineColor(int r, int g, int b)
// задает текущий цвет рисования по компонентам (r, g, b)
#macro setLineColor(r, g, b)
g.setColor(r, g, b)
#endmacro

//   void setLineColor(int r, int g, int b, int alpha)
// задает текущий цвет рисования и заливки по компонентам (r, g, b) и прозрачность в alpha
#macro setLineColor(r, g, b, alpha)
g.setColor(r, g, b)
#endmacro



// задает стиль рисования линий
#macro setLineStyle(style)
g.setStrokeStyle(style)
#endmacro



//   void setFillColor(TColor color)
// задает текущий цвет заливки
#macro setFillColor(color)
g.setColor(color)
#endmacro

//   void setFillColor(int r, int g, int b)
// задает текущий цвет заливки по компонентам (r, g, b)
#macro setFillColor(r, g, b)
g.setColor(r, g, b)
#endmacro

//   void setFillColor(int r, int g, int b, int alpha)
// задает текущий цвет заливки по компонентам (r, g, b) и прозрачность в alpha
#macro setFillColor(r, g, b, alpha)
g.setColor(r, g, b)
#endmacro


#ifdef ENABLE_CUSTOM_FONTS

//   void setTextColor(TColor color)
// задает текущий цвет текста
#macro setTextColor(color)
_mvl_currentFont.setColor(g, color)
#endmacro

//   void setTextColor(int r, int g, int b)
// задает текущий цвет текста по компонентам (r, g, b)
#macro setTextColor(r, g, b)
_mvl_currentFont.setColor(g, r + ((g & 0xFF) << 8) + ((b & 0xFF) << 16))
#endmacro

//   void setTextColor(int r, int g, int b, int alpha)
// задает текущий цвет текста по компонентам (r, g, b) и прозрачность в alpha
#macro setTextColor(r, g, b, alpha)
_mvl_currentFont.setColor(g, r + ((g & 0xFF) << 8) + ((b & 0xFF) << 16))
#endmacro


#else // ENABLE_CUSTOM_FONTS

//   void setTextColor(TColor color)
// задает текущий цвет текста
#macro setTextColor(color)
g.setColor(color)
#endmacro

//   void setTextColor(int r, int g, int b)
// задает текущий цвет текста по компонентам (r, g, b)
#macro setTextColor(r, g, b)
g.setColor(r, g, b)
#endmacro

//   void setTextColor(int r, int g, int b, int alpha)
// задает текущий цвет текста по компонентам (r, g, b) и прозрачность в alpha
#macro setTextColor(r, g, b, alpha)
g.setColor(r, g, b)
#endmacro


#endif // ENABLE_CUSTOM_FONTS

//   void setGlobalAlpha(int alpha)
// задает уровень прозрачности
#macro setGlobalAlpha(alpha)
#endmacro


//----------------------------------------------------------------------------//
//                              работа со шрифтами                            //
//----------------------------------------------------------------------------//



#ifdef ENABLE_CUSTOM_FONTS

// void setFont(TFont font)
#macro setFont(font)
_mvl_currentFont = font;
#endmacro



// TFont getFont()
#macro getFont()
_mvl_currentFont
#endmacro



// int getFontBaseline(TFont fnt)
#macro getFontBaseline(fnt)
_mvl_void_macro(fnt).getBaseLinePosition()
#endmacro



// int getFontCharWidth(TFont fnt, TChar ch)
#macro getFontCharWidth(fnt, ch)
_mvl_void_macro(fnt).charWidth(ch)
#endmacro



// int getFontStringWidth(TFont fnt, TString str)
#macro getFontStringWidth(fnt, str)
_mvl_void_macro(fnt).getStringWidth(str)
#endmacro


#else  // ENABLE_CUSTOM_FONTS

// void setFont(TFont font)
#macro setFont(font)
g.setFont(font)
#endmacro


// TFont getFont()
#macro getFont()
g.getFont()
#endmacro




// int getFontBaseline(TFont fnt)
#macro getFontBaseline(font)
_mvl_void_macro(font).getBaseLinePosition()
#endmacro



// int getFontCharWidth(TFont fnt, TChar ch)
#macro getFontCharWidth(font, ch)
_mvl_void_macro(font).charWidth(ch)
#endmacro



// int getFontStringWidth(TFont fnt, TString str)
#macro getFontStringWidth(font, str)
_mvl_void_macro(font).stringWidth(str)
#endmacro


#endif




//   void setClip(int x, int y, int w, int h)
// устанавливает размеры доступной для рисования области
#macro setClip(x, y, w, h)
g.setClip(x, y, w, h)
#endmacro



//   void resetClip()
// делает весь экран доступным для рисования
#macro resetClip()
g.setClip(0, 0, getScreenWidth(), getScreenHeight());
#endmacro



//   void translateCoord(int x, int y)
// переносит начало координат в точку (x, y)
#macro translateCoord(x, y)
g.translate(x, y)
#endmacro



//----------------------------------------------------------------------------//
//                           рисование примитивов                             //
//----------------------------------------------------------------------------//

//   void drawLine(int x1, int y1, int x2, int y2)
// рисует линию из точки (x1, y1) в точку (x2, y2)
#macro drawLine(x1, y1, x2, y2)
g.drawLine(x1, y1, x2, y2)
#endmacro



//   void drawHLine(int x1, int y, int x2)
// рисует горизонтальную линию из точки (x1, y) в точку (x2, y)
#macro drawHLine(x1, y, x2)
g.drawLine(x1, y, x2, y)
#endmacro



//   void drawVLine(int x, int y1, int y2)
// рисует вертикальную линию из точки (x, y1) в точку (x, y2)
#macro drawVLine(x, y1, y2)
g.drawLine(x, y1, x, y2)
#endmacro



//   void drawRect(int x, int y, int w, int h)
// рисует прямоугольник
#macro drawRect(x, y, w, h)
g.drawRect(x, y, w, h)
#endmacro



//   void drawRoundRect(int x, int y, int w, int h, int arcWidth, int arcHeight)
// рисует прямоугольник (x, y, w, h) с закругленными углами
//  arcWidth - горизонтальный диаметр дуги
//  arcHeight - вертикальный диаметр дуги
#macro drawRoundRect(x, y, w, h, arcWidth, arcHeight)
g.drawRoundRect(x, y, w, h, arcWidth, arcHeight)
#endmacro



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
#macro drawArc(x, y, w, h, startAngle, arcAngle)
g.drawArc(x, y, w-1, h-1, startAngle, arcAngle)
#endmacro



//   void drawCircle(int x, int y, int r)
// рисует окружность радиуса r с центром в точке (x, y)
#macro drawCircle(x, y, r)
g.drawArc(x-r, y-r, r*2, r*2, 0, 360)
#endmacro


//----------------------------------------------------------------------------//
//                           закраска примитивов                              //
//----------------------------------------------------------------------------//

//   void fillRect(int x, int y, int w, int h)
// закрашивает прямоугольник
#macro fillRect(x, y, w, h)
g.fillRect(x, y, w, h)
#endmacro



//   void fillScreen()
// закрашивает весь экран
#macro fillScreen()
{g.setClip(0, 0, getScreenWidth(), getScreenHeight()); g.fillRect(0, 0, getScreenWidth(), getScreenHeight());}
#endmacro



//   void fillScreen(TColor color)
// закрашивает весь экран
#macro fillScreen(color)
{g.setClip(0, 0, getScreenWidth(), getScreenHeight());g.setColor(color); g.fillRect(0, 0, getScreenWidth(), getScreenHeight());}
#endmacro



//   void fillArc(int x, int y, int w, int h, int startAngle, int arcAngle)
// закрашивает круговой или эллиптический сегмент
#macro fillArc(x, y, w, h, startAngle, arcAngle)
g.fillArc(x, y, w, h, startAngle, arcAngle)
#endmacro



//   void fillCircle(int x, int y, int r)
// закрашивает окружность радиуса r с центром в точке (x, y)
#macro fillCircle(x, y, r)
g.fillArc(x-r, y-r, r*2, r*2, 0, 360)
#endmacro



//   void fillRoundRect(int x, int y, int w, int h, int arcWidth, int arcHeight)
// закрашивает прямоугольник (x, y, w, h) с закругленными углами
//  arcWidth - горизонтальный диаметр дуги
//  arcHeight - вертикальный диаметр дуги
#macro fillRoundRect(x, y, w, h, arcWidth, arcHeight)
g.fillRoundRect(x, y, w, h, arcWidth, arcHeight)
#endmacro



//  void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
//  заливает треугольную область
#macro fillTriangle(x1, y1, x2, y2, x3, y3)
g.fillTriangle(x1, y1, x2, y2, x3, y3)
#endmacro

//----------------------------------------------------------------------------//
//                           рисование текста                                 //
//----------------------------------------------------------------------------//
#ifdef ENABLE_CUSTOM_FONTS

//   void drawChar(char ch, int x, int y, int anchor)
// рисует символ ch в точку (x, y) с выравниванием anchor
#macro drawChar(ch, x, y, anchor)
_mvl_currentFont.DrawChar(g, ch, x, y, anchor);
#endmacro

//   void drawChar(char ch, int x, int y)
// рисует символ ch в точку (x, y) с выравниванием LEFT | TOP
#macro drawChar(ch, x, y)
_mvl_currentFont.DrawChar(g, ch, x, y);
#endmacro



//   void drawString(String str, int x, int y, int anchor)
// рисует строку str в точку (x, y) с выравниванием anchor
#macro drawString(str, x, y, anchor)
_mvl_currentFont.DrawString(g, str, x, y, anchor)
#endmacro

//   void drawString(String str, int x, int y)
// рисует строку str в точку (x, y) с выравниванием LEFT | TOP
#macro drawString(str, x, y)
_mvl_currentFont.DrawString(g, str, x, y)
#endmacro



//   void drawSubstring(String str, int offset, int len, int x, int y, int anchor)
// рисует len символов подстроки str в начиная с offset в точку (x, y) с
// выравниванием anchor
#macro drawSubstring(str, offset, len, x, y, anchor)
_mvl_currentFont.DrawSubstring(g, str, offset, len, x, y, anchor)
#endmacro

//   void drawSubstring(String str, int offset, int len, int x, int y)
// рисует строку str в точку (x, y) с выравниванием LEFT | TOP
#macro drawSubstring(str, offset, len, x, y)
_mvl_currentFont.DrawSubstring(g, str, offset, len, x, y)
#endmacro





#else // ENABLE_CUSTOM_FONTS

//   void drawChar(char ch, int x, int y, int anchor)
// рисует символ ch в точку (x, y) с выравниванием anchor
#macro drawChar(ch, x, y, anchor)
g.drawChar(ch, x, y, anchor)
#endmacro

//   void drawChar(char ch, int x, int y)
// рисует символ ch в точку (x, y) с выравниванием LEFT | TOP
#macro drawChar(ch, x, y)
g.drawChar(ch, x, y, javax.microedition.lcdui.Graphics.LEFT|javax.microedition.lcdui.Graphics.TOP)
#endmacro



//   void drawString(String str, int x, int y, int anchor)
// рисует строку str в точку (x, y) с выравниванием anchor
#macro drawString(str, x, y, anchor)
_mvl_DrawString(g, str, x, y, anchor)
#endmacro

//   void drawString(String str, int x, int y)
// рисует строку str в точку (x, y) с выравниванием LEFT | TOP
#macro drawString(str, x, y)
g.drawString(str, x, y, javax.microedition.lcdui.Graphics.LEFT|javax.microedition.lcdui.Graphics.TOP)
#endmacro



//   void drawSubstring(String str, int offset, int len, int x, int y, int anchor)
// рисует len символов подстроки str в начиная с offset в точку (x, y) с
// выравниванием anchor
#macro drawSubstring(str, offset, len, x, y, anchor)
_mvl_DrawString(g, str.substring(offset, offset+len), x, y, anchor)
#endmacro

//   void drawSubstring(String str, int offset, int len, int x, int y)
// рисует строку str в точку (x, y) с выравниванием LEFT | TOP
#macro drawSubstring(str, offset, len, x, y)
g.drawSubstring(str, offset, offset+len, x, y, javax.microedition.lcdui.Graphics.LEFT|javax.microedition.lcdui.Graphics.TOP)
#endmacro



#endif



//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


//----------------------------------------------------------------------------//
//                           рисование изображений                            //
//----------------------------------------------------------------------------//

//   void drawImage(TImage img, int x, int y, int anchor)
// рисует изображение img в точку (x, y) с выравниванием anchor
#macro drawImage(img, x, y, anchor)
g.drawImage(img, x, y, anchor)
#endmacro



//   void drawImage(TImage img, int x, int y)
// рисует изображение img в точку (x, y) с выравниванием LEFT | TOP
#macro drawImage(img, x, y)
g.drawImage(img, x, y, javax.microedition.lcdui.Graphics.LEFT|javax.microedition.lcdui.Graphics.TOP)
#endmacro



//  void drawImageRegion(TImage img, int x_src, int y_src, int width, int height, int transform, int x, int y, int anchor)
#macro drawImageRegion(img, x_src, y_src, width, height, transform, x, y, anchor)
g.drawRegion(img, x_src, y_src, width, height, transform, x, y, anchor)
#endmacro



//  void drawImageRegion(TImage img, int x_src, int y_src, int width, int height, int transform, int x, int y)
#macro drawImageRegion(img, x_src, y_src, width, height, transform, x, y)
g.drawRegion(img, x_src, y_src, width, height, transform, x, y, javax.microedition.lcdui.Graphics.LEFT|javax.microedition.lcdui.Graphics.TOP)
#endmacro



//  void drawImageRegion(TImage img, int x_src, int y_src, int width, int height, int x, int y)
#macro drawImageRegion(img, x_src, y_src, width, height, x, y)
g.drawRegion(img, x_src, y_src, width, height, javax.microedition.lcdui.game.Sprite.TRANS_NONE, x, y, javax.microedition.lcdui.Graphics.LEFT|javax.microedition.lcdui.Graphics.TOP)
#endmacro



//  void drawRGB(TRGBArray rgbData, int offset, int scanLength, int x, int y, int width, int height, bool processAlpha)
#macro drawRGB(rgbData, offset, scanLength, x, y, width, height, processAlpha)
g.drawRGB(rgbData, offset, scanlength, x, y, width, height, processAlpha)
#endmacro



