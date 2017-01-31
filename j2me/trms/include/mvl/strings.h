#ifnotdef __MVL_STRINGS_H__
#define   __MVL_STRINGS_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                               String functions


                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.01

\*----------------------------------------------------------------------------*/


#defineblock end
  #ifdef JAVA
  #defineblock begin
  

  #macro strlen(s)
  _mvl_void_macro(s).length()
  #endmacro



  #macro strGetChar(s, index)
  _mvl_void_macro(s).charAt(index)
  #endmacro
  

  
  #macro strFirstIndexOf(s)
  _mvl_void_macro(s).indexOf(s)
  #endmacro



  #macro strFirstIndexOf(s, index)
  _mvl_void_macro(s).indexOf(s, index)
  #endmacro
  
  
  
  #macro strLastIndexOf(s)
  _mvl_void_macro(s).lastIndexOf(s)
  #endmacro



  #macro strLastIndexOf(s, index)
  _mvl_void_macro(s).lastIndexOf(s, index)
  #endmacro



  #macro strTrim(s)
  _mvl_void_macro(s).trim()
  #endmacro



  #defineblock end
  
  public static final String substring(String s, int index, int count) {
    if ( count == 0 )
      return "";
    else
      return s.substring(index, index+count-1);
  }


  public static final char char1251ToUnicode(int bt) {
    char ch;
    if ((bt >= 0xC0) && (bt <= 0xDF)) {
      ch = (char)((int)'А' + bt - 0xC0);
    } else if (bt >=0xE0 && bt <= 0xFF) {
      ch = (char)((int)'а' + bt - 0xE0);
    } else if (bt == 0xA8) {
      ch = 'Ё';
    } else if (bt == 0xB8) {
      ch = 'ё';
    } else if (bt == 0xB9) {
      ch = '№';
    } else {
      ch = (char) bt;
    }
    return ch;
  }



  public static final int charUnicodeTo1251(char bt) {
    int ch;
    if ((bt >= 'А') && (bt <= 'Я')) {
      ch = (0xC0 + bt - 'А');
    } else if (bt >= 'а' && bt <= 'я') {
      ch = (0xE0 + bt - 'а');
    } else if (bt == 'Ё') {
      ch = 0xA8;
    } else if (bt == 'ё') {
      ch = 0xB8;
    } else if (bt == '№') {
      ch = 0xB9;
    } else {
      ch = (int) bt;
    }
    return ch;
  }



  public static final char charUpper(char ch) {
    if ( ( ch >= 0x430 ) && ( ch <= 0x44F) )
      return (char)((int)ch - 0x20);
    else if ( ch == 0x451 )
      return 0x401;
    return Character.toUpperCase(ch);
  }



  public static final char charLower(char ch) {
    if ( ( ch >= 0x410 ) && ( ch <= 0x42F) )
      return (char)((int)ch + 0x20);
    else if ( ch == 0x401 )
      return 0x451;
    return Character.toLowerCase(ch);
  }



  public static final String strUpper(TString s) {
    StringBuffer sb = new StringBuffer(s.length());
    for (int i = 0; i < s.length(); i++)
      sb.append(charUpper(s.charAt(i)));
    return sb.toString();
  }



  public static final String strLower(TString s) {
    StringBuffer sb = new StringBuffer(s.length());
    for (int i = 0; i < s.length(); i++)
      sb.append(charLower(s.charAt(i)));
    return sb.toString();
  }



  public static final long str2date(String str) {
    int i1 = str.indexOf('-');
    int i2 = str.lastIndexOf('-');

    if ( i1 < 0 || i2 < 0 )
      return 0;
    try {
      String sD = str.substring(0, i1);
      String sM = str.substring(i1+1, i2);
      String sY = str.substring(i2+1);
      Calendar c = Calendar.getInstance();
      c.setTime(new Date(0));
      c.set(Calendar.YEAR, Integer.parseInt(sY));
      c.set(Calendar.MONTH, Integer.parseInt(sM)-1);
      c.set(Calendar.DAY_OF_MONTH, Integer.parseInt(sD));
      return c.getTime().getTime();
    } catch ( Exception ex ) {
      return 0;
    }
  }



  public static final long str2time(String str) {
    int i1 = str.indexOf(':');
    int i2 = str.lastIndexOf(':');
    if ( i1 < 0 || i2 < 0 )
      return 0;
    try {
      String sH = str.substring(0, i1);
      String sM = str.substring(i1+1, i2);
      String sS = str.substring(i2+1);
      Calendar c = Calendar.getInstance();
      c.setTime(new Date(0));
      c.set(Calendar.HOUR, Integer.parseInt(sH));
      c.set(Calendar.MINUTE, Integer.parseInt(sM));
      c.set(Calendar.SECOND, Integer.parseInt(sS));
      return c.getTime().getTime();
    } catch ( Exception ex ) {
      return 0;
    }
  }



  public static final String date2str(long date) {
    Calendar c = Calendar.getInstance();
    c.setTime(new Date(date));
    String result = ""+c.get(Calendar.DAY_OF_MONTH)+'-';
    if ( c.get(Calendar.MONTH) < 9 )
      result += '0';
    return result + (c.get(Calendar.MONTH)+1) + '-' + c.get(Calendar.YEAR);
  }



  public static final String time2str(long time) {
    Calendar c = Calendar.getInstance();
    c.setTime(new Date(time));
    String result = ""+c.get(Calendar.HOUR)+':';
    if ( c.get(Calendar.MINUTE) < 10 )
      result += '0';
    result += c.get(Calendar.MINUTE) + ":";
    if ( c.get(Calendar.SECOND) < 10 )
      result += '0';
    return result + c.get(Calendar.SECOND);
  }
  
  
  
  public static final TString int2hex(int value) {
     return Integer.toHexString(value);
  }



  #endif // JAVA
#endif // __MVL_STRINGS_H__

