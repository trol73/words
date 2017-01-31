#ifnotdef __MVL_GRAPH_H__
#define   __MVL_GRAPH_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                            Graphical functions unit


                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.0

\*----------------------------------------------------------------------------*/


  #ifdef BLACKBERRY
//    #include "mvl/blackberry/graph.h"
  #elseif J2ME
    #include "mvl/j2me/graph.h"
  #elseif J2SE
//      #include "mvl/j2se/graph.h"
  #elseif WIN32
//    #include "mvl/win32/graph.h"
  #elseif LINUX
//    #include "mvl/linux/graph.h"
  #else
    #error "unknown target platform"
  #endif

 #defineblock end
  #ifdef BLACKBERRY
  #elseif J2ME
    #include "mvl/j2me/images.h"
    
  #ifnotdef ENABLE_CUSTOM_FONTS
  public static final void _mvl_DrawString(Graphics g, String str, int x, int y, int anchor) {
    if ( (anchor & KAnchorVCenter) != 0 ) {
      anchor -= KAnchorVCenter - KAnchorTop;
      y -= g.getFont().getHeight()/2;
    }
    g.drawString(str, x, y, anchor);
  }
  #endif  // ENABLE_CUSTOM_FONTS
#ifdef ENABLE_BACKBUFFER
  public static final void shadowBackBufferImage(int shadowLevel) {
    int w = _mvl_screenBackBufferImage.getWidth();
    int h = _mvl_screenBackBufferImage.getHeight();
    int rgb[] = new int[w*h];
    getImageRGB(_mvl_screenBackBufferImage, rgb, 0, w, 0, 0, w, h);

    for (int x = 0; x < w; x++)
      for (int y = 0; y < h; y++) {
        int c = rgb[x+w*y];
        int r = c >> 16 & 0xFF;
        int g = c >> 8 & 0xFF;
        int b = c & 0xFF;
        r = shadowLevel*r/100;
        g = shadowLevel*g/100;
        b = shadowLevel*b/100;
        rgb[x+w*y] = (r << 16) + (g << 8) + b;
      }
    _mvl_screenBackBufferGraphics.setClip(0, 0, w, h);
    _mvl_screenBackBufferGraphics.drawRGB(rgb, 0, w, 0, 0, w, h, false);
  }
#endif  // ENABLE_BACKBUFFER


  #elseif J2SE
  #elseif WIN32
  #elseif LINUX
  #else
    #error "unknown target platform"
  #endif

/*
 #ifdef J2SE
#func
public final Image createImageFromJar(String name) {
// создает изображение из jar-файла приложения
  java.net.URL imgURL = getClass().getResource("/"+name);
  java.awt.Toolkit tk = java.awt.Toolkit.getDefaultToolkit();
  Image img = null;
  try {
    java.awt.MediaTracker m = new java.awt.MediaTracker(this);
    img = tk.getImage(imgURL);
    m.addImage(img, 0);
    m.waitForAll();
  } catch (Exception e) {
 #ifdef DEBUG
    System.out.println(">> FATAL ERROR! >> createImage() -> file not found.\n" + e.toString());
 #endif
  }
  return img;
}
#end
#func
public static final Font createFontWithFace(int face, int style, int size) {
// возвращает созданный шрифт
//   face - вид шрифта  (один из FONT_FACE_SYSTEM, FONT_FACE_MONOSPACE, or FONT_FACE_PROPORTIONAL)
//   style - стиль шрифта (FONT_STYLE_PLAIN, или комбинация FONT_STYLE_BOLD, FONT_STYLE_ITALIC, FONT_STYLE_UNDERLINED
//   size - размер шрифта (оди нз FONT_SIZE_SMALL, FONT_SIZE_MEDIUM, или FONT_SIZE_LARGE)
  switch ( face ) {
    case FONT_FACE_SYSTEM:
      return new Font("Dialog", style, size);
    case FONT_FACE_MONOSPACE:
      return new Font("Monospaced", style, size);
    case FONT_FACE_PROPORTIONAL:
      return new Font("Serif", style, size);
  }
  return new Font("Serif", style, size);
}
#end
#func
public static final void drawStringAnchor(Graphics g, String str, int x, int y, int anchor) {
// рисование строки с поддержкой якорей
  java.awt.FontMetrics fontMetrics = g.getFontMetrics();

  if ( (anchor & DRAW_ANCHOR_RIGHT) == DRAW_ANCHOR_RIGHT )
    x -= fontMetrics.stringWidth(str);
  else if ( (anchor & DRAW_ANCHOR_HCENTER) == DRAW_ANCHOR_HCENTER )
    x -= fontMetrics.stringWidth(str)/2;

  if ( (anchor & DRAW_ANCHOR_BOTTOM) == DRAW_ANCHOR_BOTTOM )
    y -= fontMetrics.getHeight();
  else if ( (anchor & DRAW_ANCHOR_VCENTER) == DRAW_ANCHOR_VCENTER )
    y -= fontMetrics.getHeight()/2;
  else if ( (anchor & DRAW_ANCHOR_BASELINE) == DRAW_ANCHOR_BASELINE )
    y -= fontMetrics.getAscent() + fontMetrics.getLeading();

  g.drawString(str, x, y);
}
#end
 #endif
*/



#endif

