#ifnotdef __MVL_FONT_H__
#define   __MVL_FONT_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                              Graphical font unit


                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.02

\*----------------------------------------------------------------------------*/



#defineblock end

#ifdef ENABLE_CUSTOM_FONTS

public class TFont {
  private javax.microedition.lcdui.Font iMidpFont;

  private byte iBaseLine;      // расстояние от верхней точки до базовой линии
  private byte iHeight;        // высота символов
  private byte iDelta;         // дополнительное расстояние между символами
  private boolean iUnderlined;
  private Image iFontBaseImage; // оригинальное изображение (черный цвет)
  private Image[] iFontImages;
  private int iCurrentFontIndex; // индекс рисунка шрифта выбранного цвета или -1 для черного шрифта
  private int iNextFontIndex;    // индекс, под которым надо поместить в кэш следующий шрифт
  private int[] iColors;
  private int[] iFontMaskRGB;
  private int iCurrentColor;    // текущий цвет
  
  private char[] iFontArray;
  private byte[] iCharWidth;
  private short[] iCharPosX;
  private short[] iCharPosY;
  private byte iReleasesCount; // если 0, то шрифт не может менять цвет, иначе, количество кэшируемых цветных шрифтов
  private short iCharsCount;
  
  
  
  
  // Load custom font from file
  public TFont(String fileName) {
    TFile f = fileOpen(fileName);
    int size = fileReadWord(f);
    byte[] buf = new byte[size];
    fileRead(f, buf, size);
    fileClose(f);
    createCustomFont(buf);
  }
  
  
  
  // Load custom font from buffer
  public TFont(byte[] buf) {
    createCustomFont(buf);
  }
  


  // Create system font
  public TFont(int type) {
//System.out.println("TP " + (type & 0x60) + "  "+(type & 0x07)+"  "+(type & 0x18));
//System.out.println("DF  = "+Font.getDefaultFont().getFace() +" "+Font.getDefaultFont().getStyle() + "  "+Font.getDefaultFont().getSize());
/*
    if ( type == 0 )
      iMidpFont = Font.getDefaultFont();
    else
*/
      iMidpFont = Font.getFont(type & 0x60, type & 0x07, type & 0x18);
  }
  
  

  private final void createCustomFont(byte[] buf) {
    int pos = 0;
    iCharsCount = (short)bufferReadWord(buf, pos);
    iCharWidth = new byte[iCharsCount];
    iCharPosX = new short[iCharsCount];
    iCharPosY = new short[iCharsCount];
    iHeight = (byte)bufferReadByte(buf, pos);
    iBaseLine = (byte)bufferReadByte(buf, pos);
    iDelta = (byte)bufferReadByte(buf, pos);
    iReleasesCount = (byte)bufferReadByte(buf, pos);
    iFontImages = new Image[iReleasesCount];
    iColors = new int[iReleasesCount];

    for (int i = 0; i < iReleasesCount; i++)
      iColors[i] = 0xFFFFFFFF;

    iFontArray = new char[bufferReadWord(buf, pos)];
    for (int i = 0; i < iFontArray.length; i++)
      iFontArray[i] = (char)bufferReadWord(buf, pos);
    int len = bufferReadWord(buf, pos);
    iFontBaseImage = createImage(buf, pos, len);
    pos += len;
    int imageWidth = iFontBaseImage.getWidth();
    int imageHeight = iFontBaseImage.getHeight();
    
    iFontMaskRGB = new int[imageWidth*imageHeight];
    iFontBaseImage.getRGB(iFontMaskRGB, 0, imageWidth, 0, 0, imageWidth, imageHeight);

    short x = 0;
    short y = 0;
    for (int i = 0; i < iCharsCount; i++) {
      iCharWidth[i] = (byte)bufferReadByte(buf, pos);
      if ( x + iCharWidth[i] > imageWidth ) {
        x = 0;
        y += iHeight;
      }
      iCharPosX[i] = x;
      iCharPosY[i] = y;
      x += iCharWidth[i];
//System.out.println(""+i+"    "+iCharPosX[i]+"     " +iCharWidth[i]+"    "+iCharPosY[i]);
    }
    
    iCurrentFontIndex = -1;
    iNextFontIndex = 0;
    iCurrentColor = 0x000000;
  }
  
  
  
  
  // вычисляет индекс символа (или -1, если символ отсутствует в шрифте)
  private final int getCharIndex(char ch) {
    int pos = 0;     // позиция в массиве chars[]
    int count;       // число символов в блоке
    int offset = 0;  // число уже отсчитанных символов
    char first;      // первый символ блока

    // если символ принадлежит алфавиту, то скорее всего, мы определим
    // его индекс уже в 1-м - 2-м проходе что быстрее любого бинарного поиска
    while (true) {
      count = iFontArray[pos++];
      if (count == 0)
        break;
      first = iFontArray[pos++];
      if ((ch >= first) && (ch < first+count))
        return offset + ch - first;
      offset += count;
    }
    int startPos = pos;
    // если это отдельный символ, которых обычно немного, то перебор
    for (int i = pos; iFontArray[i] != 0; i++) {
      if ( iFontArray[i] == ch )
        return offset + i - startPos;
    }
    return -1;        // ничего не нашли
  }
  
  
  
  // Gets character width
  public final int charWidth(char ch) {
    if ( iMidpFont != null )
      return iMidpFont.charWidth(ch);
    int index = getCharIndex(ch);
    if ( index >= 0 )
      return iCharWidth[index] + iDelta;
    else
      return iDelta;
  }
  
  
  
  // Gets the distance in pixels from the top of the text to the text's baseline.
  public final int getBaseLinePosition() {
    if ( iMidpFont != null )
      return iMidpFont.getBaselinePosition();
    return iBaseLine;
  }
  
  
  
  // Gets the height of a line of text in this font
  public final int getHeight() {
    if ( iMidpFont != null )
      return iMidpFont.getHeight();
    return iHeight;
  }


  
  // Gets the total string width
  public final int getStringWidth(String str) {
    if ( iMidpFont != null )
      return iMidpFont.stringWidth(str);
    int w = iDelta * str.length();
    for (int i = 0; i < str.length(); i++) {
      int index = getCharIndex(str.charAt(i));

      if ( index >= 0 )
        w += iCharWidth[index];
    }
    return w;
  }
  
  
  // рисует графическим шрифтом символ в заданную точку и возвращает его ширину
  private final int drawCustomChar(Graphics g, int x, int y, char ch) {
		int index = getCharIndex(ch);
		if ( index < 0 )
      return iDelta;
    // если цвет черный
    if ( iCurrentFontIndex < 0)
      g.drawRegion(iFontBaseImage, iCharPosX[index], iCharPosY[index], iCharWidth[index], iHeight, 0, x, y, 0);
    else
      g.drawRegion(iFontImages[iCurrentFontIndex], iCharPosX[index], iCharPosY[index], iCharWidth[index], iHeight, 0, x, y, 0);

    return iCharWidth[index] + iDelta;
  }
  

  public final void DrawChar(Graphics g, char ch, int x, int y) {
    if ( iMidpFont != null ) {
      g.setFont(iMidpFont);
      g.drawChar(ch, x, y, Graphics.LEFT | Graphics.TOP);
    } else {
      int w = drawCustomChar(g, x, y, ch);
      if ( iUnderlined ) {
        g.setStrokeStyle(Graphics.SOLID);
        g.setColor(iCurrentColor);
        g.drawLine(x, y+iBaseLine, x+w, y+iBaseLine);
      }
    }
  }
  


  public final void DrawChar(Graphics g, char ch, int x, int y, int anchor) {
    if ( (anchor & KAnchorVCenter) != 0 ) {
      y -= getHeight()/2;
      anchor -= KAnchorVCenter;
    }
    if ( iMidpFont != null ) {
      g.setFont(iMidpFont);
      g.drawChar(ch, x, y, anchor);
      return;
    }
    if ( (anchor & KAnchorRight) != 0 )
      x -= charWidth(ch);
    if ( (anchor & KAnchorBottom) != 0 )
      y -= iHeight;
    if ( (anchor & KAnchorHCenter) != 0 )
      x -= charWidth(ch);
    int w = drawCustomChar(g, x, y, ch);
    if ( iUnderlined ) {
      g.setStrokeStyle(Graphics.SOLID);
      g.setColor(iCurrentColor);
      g.drawLine(x, y+iBaseLine, x+w, y+iBaseLine);
    }
  }
  


  public final void DrawString(Graphics g, String str, int x, int y) {
    int x0 = x;
    if ( iMidpFont != null ) {
      g.setFont(iMidpFont);
      g.drawString(str, x, y, Graphics.LEFT | Graphics.TOP);
      return;
    }
    for (int i = 0; i < str.length(); i++)
      x += drawCustomChar(g, x, y, str.charAt(i));
    if ( iUnderlined ) {
      g.setColor(iCurrentColor);
      g.setStrokeStyle(Graphics.SOLID);
      g.drawLine(x0, y+iBaseLine, x, y+iBaseLine);
    }
  }



  public final void DrawString(Graphics g, String str, int x, int y, int anchor) {
    if ( (anchor & KAnchorVCenter) != 0 ) {
      y -= getHeight()/2;
      anchor -= KAnchorVCenter-KAnchorTop;
    }
    if ( (anchor & KAnchorHCenter) != 0 ) {
      x -= getStringWidth(str)/2;
      anchor -= KAnchorHCenter-KAnchorLeft;
    }

    if ( iMidpFont != null ) {
      g.setFont(iMidpFont);
      g.drawString(str, x, y, anchor);
      return;
    }
    if ( (anchor & KAnchorRight) != 0 )
      x -= getStringWidth(str);
    if ( (anchor & KAnchorBottom) != 0 )
      y -= iHeight;
    int x0 = x;
    for (int i = 0; i < str.length(); i++)
      x += drawCustomChar(g, x, y, str.charAt(i));
    if ( iUnderlined ) {
      g.setColor(iCurrentColor);
      g.setStrokeStyle(Graphics.SOLID);
      g.drawLine(x0, y+iBaseLine, x, y+iBaseLine);
    }
  }



  public final void DrawSubstring(Graphics g, String str, int offset, int len, int x, int y) {
    DrawString(g, str.substring(offset, offset+len), x, y);
  }

  

  public final void DrawSubstring(Graphics g, String str, int offset, int len, int x, int y, int anchor) {
    DrawString(g, str.substring(offset, offset+len), x, y, anchor);
  }
  
  
  public final void setColor(Graphics g, int color) {
    iCurrentColor = color;
    if ( iMidpFont != null ) {
      g.setColor(color);
      return;
    }

    // шрифт не поддерживает перекрашивание
    if ( iReleasesCount == 0 )
      return;

    // шрифт оригинального цвета
    if ( color == 0x000000 ) {
      iCurrentFontIndex = -1;
      return;
    }

    // ищем в буффере готовый цвет
    for (int i = 0; i < iReleasesCount; i++ )
      if ( iColors[i] == color ) {
        iCurrentFontIndex = i;
        return;
      }

    iCurrentFontIndex = iNextFontIndex;
    iNextFontIndex = ( iNextFontIndex + 1 ) % iReleasesCount;
    iColors[iCurrentFontIndex] = color;
    // перекрашиваем маску
    int imageArea = iFontBaseImage.getWidth()*iFontBaseImage.getHeight();
    int backColor = iFontMaskRGB[imageArea-1];
    int symColor = 0;
    for (int i = 0; i < imageArea; i++)
      if ( iFontMaskRGB[i] != backColor ) {
        symColor = iFontMaskRGB[i];
        break;
      }
    
    color = color | 0xFF000000;
    for ( int i = 0; i < imageArea; i++ )
      if ( iFontMaskRGB[i] != symColor )
        iFontMaskRGB[i] = iFontMaskRGB[i] & 0x00ffffff;
      else
        iFontMaskRGB[i] = color;


    // создаем рисунок и сохраняем его в кэше
    iFontImages[iCurrentFontIndex] = createRGBImage(iFontMaskRGB, iFontBaseImage.getWidth(), iFontBaseImage.getHeight(), true);
  }
  
  
  
  public final boolean isUnderlined() {
     return ( iMidpFont == null ) ? iUnderlined : iMidpFont.isUnderlined();
  }
  
  
  
  public final void setUnderlined(boolean val) {
    if ( (iMidpFont != null) && (iMidpFont.isUnderlined() != val) ) {
      iMidpFont = (val) ? Font.getFont(iMidpFont.getFace(), iMidpFont.getStyle()+Font.STYLE_UNDERLINED, iMidpFont.getSize())
        : Font.getFont(iMidpFont.getFace(), iMidpFont.getStyle()-Font.STYLE_UNDERLINED, iMidpFont.getSize());
    } else
      iUnderlined = val;
  }

  
} // TFont

#endif //  ENABLE_CUSTOM_FONTS




#ifdef ENABLE_CUSTOM_FONTS

public final TFont createFont(String filename) {
  return new TFont(filename);
}



public final TFont createFont(byte[] buf) {
  return new TFont(buf);
}



public final TFont createFont(int type) {
  return new TFont(type);
}


#else // ENABLE_CUSTOM_FONTS


public static final Font createFont(String filename) {
  return Font.getDefaultFont();
}



public static final Font createFont(byte[] buf) {
  return Font.getDefaultFont();
}



public static final Font createFont(int type) {
  return Font.getFont(type & 0x60, type & 0x07, type & 0x18);
}


public static final Font _mvl_setFontUnderlined(Font aFnt, boolean aValue) {
  return (aValue) ? Font.getFont(aFnt.getFace(), aFnt.getStyle() | Font.STYLE_UNDERLINED, aFnt.getSize())
    : Font.getFont(aFnt.getFace(), aFnt.getStyle() & 0xFB, aFnt.getSize());
}


#endif  // ENABLE_CUSTOM_FONTS

  public static final int getFontHeight(TFont font) {
    return font.getHeight();
  }

#endif // __MVL_FONT_H__

