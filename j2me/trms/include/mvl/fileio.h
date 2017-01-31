#ifnotdef __MVL_FILEIO_H__
#define   __MVL_FILEIO_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                                File IO functions


                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.0

\*----------------------------------------------------------------------------*/


#defineblock end
  #ifdef J2ME
  
  
  
  public static final TFile fileOpen(String filename) {
    return _mvl_instance.getClass().getResourceAsStream('/'+filename);
  }
  
  
  
  public static final boolean fileClose(TFile is) {
    try {
      is.close();
      is = null;
      return true;
    } catch ( Exception ex ) {
      return false;
    }
  }
  
  
  
  public static final boolean fileSkip(TFile is, int count) {
    try {
      is.skip(count);
      return true;
    } catch ( Exception ex ) {
      return false;
    }
  }
  
  
  public static final int fileReadByte(TFile is) {
    try {
      return (int)(is.read() & 0xFF);
    } catch (IOException e) {
      return -1;
    }
  }
  
  
  
  public static int fileReadWord(TFile is) {
    try {
      return (int)(is.read() & 0xFF) + ( (int)(is.read() & 0xFF) << 8);
    } catch (IOException e) {
      return -1;
    }
  }



  public static final int fileRead3Byte(TFile is) {
    try {
      return (int)(is.read() & 0xFF) + ( (int)(is.read() & 0xFF) << 8) + ( (int)(is.read() & 0xFF) << 16);
    } catch (IOException e) {
      return -1;
    }
  }
  
  
  
  public static final int fileReadDword(TFile is) {
    try {
      return (int)(is.read() & 0xFF) + ( (int)(is.read() & 0xFF) << 8) + ( (int)(is.read() & 0xFF) << 16 ) + ( (int)(is.read() & 0xFF) << 24);
    } catch (IOException e) {
      return -1;
    }
  }
  
  
  
  public static final int fileReadInt(TFile is, int length) {
    if ( length == 1 )
      return fileReadByte(is);
    else if ( length == 2 )
      return fileReadWord(is);
    else if ( length == 3 )
      return fileRead3Byte(is);
    else if ( length == 4 ) {
      try {
        return (is.read() & 0xFF) + ( (is.read() & 0xFF) << 8) + ( (is.read() & 0xFF) << 16 ) + ( (is.read() & 0xFF) << 24);
      } catch (IOException e) {
        return -1;
      }
    } else
      return 0;
  }
  
  
  
  public static final String fileReadString(TFile is, int length) {
    int len = fileReadByte(is);
    if (length == 2)
      len += (fileReadByte(is) << 8);
    StringBuffer sb = new StringBuffer(len);
    for (int i = 0; i < len; i++) {
      int bt = fileReadByte(is);
      sb.append((char)(bt));
    }
    return sb.toString();
  }
  
  
  
  public static final String fileReadStringWin1251(TFile is, int length) {
    int len = fileReadByte(is);
    if (length == 2)
      len += (fileReadByte(is) << 8);
    StringBuffer sb = new StringBuffer(len);
    for (int i = 0; i < len; i++) {
      int bt = fileReadByte(is);
      sb.append(char1251ToUnicode(bt));
    }
    return sb.toString();
  }
  
  
  
  public static final int fileRead(TFile is, byte[] b, int offset, int length) {
    try {
      return is.read(b, offset, length);
    } catch ( Exception ex ) {
      return -1;
    }
  }
  
  
  
  public static final int fileRead(TFile is, byte[] b, int length) {
    try {
      return is.read(b, 0, length);
    } catch ( Exception ex ) {
      return -1;
    }
  }
  
  

  public static final byte[] fileReadRecord(String fileName, int index) {
    TFile f = fileOpen(fileName);
    if ( f == null )
      return null;
    fileSkip(f, 2);
    int offsetSize = fileReadByte(f);
    fileSkip(f, index*offsetSize);
    int offset = fileReadInt(f, offsetSize);
    int offsetNext = fileReadInt(f, offsetSize);
    fileSkip(f, offset - (3+(index+2)*offsetSize));
    byte result[] = new byte[offsetNext-offset];
    fileRead(f, result, offsetNext-offset);
    fileClose(f);
    return result;
  }




  #endif // JAVA
#endif // __MVL_FILEIO_H__

