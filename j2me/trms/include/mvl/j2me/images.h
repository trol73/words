#ifnotdef __MVL_IMAGES_H__
#define   __MVL_IMAGES_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                            Graphical functions unit


                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.0

\*----------------------------------------------------------------------------*/



//  int getImageWidth(TImage image)
#macro getImageWidth(image)
_mvl_void_macro(image).getWidth()
#endmacro



//  int getImageHeight(TImage image)
#macro getImageHeight(image)
_mvl_void_macro(image).getHeight()
#endmacro



//  void getImageRGB(TImage image, TRGBArray rgb, int offset, int scanlength, int x, int y, int width, int height)
#macro getImageRGB(image, rgb, offset, scanlength, x, y, width, height)
_mvl_void_macro(image).getRGB(rgb, offset, scanlength, x, y, width, height)
#endmacro



//  void freeImage(TImage image)
#macro freeImage(image)
image = null
#endmacro


#defineblock end

public static final Image createImage(String filename) {
  try {
    return Image.createImage('/'+filename);
  } catch (Exception ex) {
    return null;
  }
}



public static final Image createImage(String filename, int index) {
  try {
    byte buf[] = fileReadRecord(filename, index);
    if ( buf == null )
      return null;
    if ( buf.length <= 0)
      return null;
    return createImage(buf, 0, buf.length);
  } catch (Exception ex) {
    return null;
  }
}



public static final Image createImage(byte[] buf, int offset, int length) {
  try {
    return Image.createImage(buf, offset, length);
  } catch (Exception ex) {
    return null;
  }
}



public static final Image createImage(Image source) {
  try {
    return Image.createImage(source);
  } catch (Exception ex) {
    return null;
  }
}



public static final Image createImage(Image source, int x, int y, int width, int height, int transform) {
  try {
    return Image.createImage(source, x, y, width, height, transform);
  } catch (Exception ex) {
    return null;
  }
}



public static final Image createRGBImage(int[] rgb, int width, int height, boolean processAlpha) {
  try {
    return Image.createRGBImage(rgb, width, height, processAlpha);
  } catch (Exception ex) {
    return null;
  }
}



public static final Image[] imagesLibCreate(String filename) {
  TFile f = fileOpen(filename);
  if ( f == null )
    return null;
  int count = fileReadWord(f);
  Image lib[] = new Image[count];
  int offsetSize = fileReadByte(f);
  int[] header = new int[count];
  for (int i = 0; i < count; i++)
    header[i] = fileReadInt(f, offsetSize);

  int spritesCnt = fileReadWord(f);
  int[] sprites_images = new int[spritesCnt];
  int[] sprites_w = new int[spritesCnt];
  int[] sprites_h = new int[spritesCnt];
  int[] sprites_x = new int[spritesCnt];
  int[] sprites_y = new int[spritesCnt];
  for (int i = 0; i < spritesCnt; i++) {
    sprites_images[i] = fileReadWord(f);
    sprites_w[i] = fileReadWord(f);
    sprites_h[i] = fileReadWord(f);
    sprites_x[i] = fileReadWord(f);
    sprites_y[i] = fileReadWord(f);
  }
  Image[] imgs = new Image[count];
  byte[] ibuf = null;
  for ( int i = 0; i < count; i++ ) {
    int l = header[i+1]-header[i];
    ibuf = new byte[l];
    fileRead(f, ibuf, 0, l);
    imgs[i] = createImage(ibuf, 0, l);
  }
  
  fileClose(f);
  
  lib = new Image[spritesCnt];
  for ( int i = 0; i < spritesCnt; i++ )
    lib[i] = createImage(imgs[sprites_images[i]], sprites_x[i], sprites_y[i], sprites_w[i], sprites_h[i], javax.microedition.lcdui.game.Sprite.TRANS_NONE);

  return lib;
}



public static final void imagesLibFree(Image[] lib) {
  lib = null;
}


public static final Image[] imagesLibCreate(int count) {
  return new Image[count];
}



#endif // __MVL_IMAGES_H__

