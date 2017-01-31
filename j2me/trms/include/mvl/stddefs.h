#ifnotdef __MVL_STDDEFS_H__
#define   __MVL_STDDEFS_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                               System base unit


                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.0

\*----------------------------------------------------------------------------*/

#macro _mvl_void_macro(param)
param
#endmacro


#ifdef  J2ME
// J2ME: определение стандартных типов
  #define   bool        boolean
  #define   int32       int
  #define   int16       short
  #define   int8        byte
  #define   TChar       char
  #define   TString     String
  #define   TColor      int
  #define   TTime       long
  #define   TBuffer     byte[]
  #define   TRGBArray   int[]
  #define   TIntArray   int[]
  #define   TStrings    String[]
  #define   TImages     Image[]
  #define   TFile       InputStream
  #define   TImage      Image
  #define   TGraphics   Graphics
#ifnotdef ENABLE_CUSTOM_FONTS
  #define   TFont       Font
#endif
  #define   TScreen     int
  #define   TForm       TItem
  #define   TMenu       TItem
  #define   TWindow     TItem
  #define   TEvent      int
  #define   TSound      Player
  #define   TTimeArray  long[]
  #define   TByteMatrix byte[][]

#elseif J2SE

#elseif SYMBIAN
#elseif WIN32
#elseif LINUX
#endif


#ifdef JAVA
// JAVA: стандартные макросы

// TBuffer bufferCreate(int size)
#macro bufferCreate(size)
new byte[size]
#endmacro



// void bufferFree(TBuffer buf)
#macro bufferFree(buf)
buf = null
#endmacro


// int bufferReadByte(TBuffer buf, int pos)
#macro bufferReadByte(buf, pos)
(buf[pos++] & 0xFF)
#endmacro



// int bufferReadWord(TBuffer buf, int pos)
#macro bufferReadWord(buf, pos)
((buf[pos++] & 0xFF) + ((buf[pos++] & 0xFF) << 8))
#endmacro



// int bufferRead3Byte(TBuffer buf, int pos)
#macro bufferRead3Byte(buf, pos)
((buf[pos++] & 0xFF) << 16) + ((buf[pos++] & 0xFF) << 8) + (buf[pos++] & 0xFF)
#endmacro



// long bufferReadDword(TBuffer buf, int pos)
#macro bufferReadDword(buf, pos)
((buf[pos++] & 0xFF) + ((buf[pos++] & 0xFF) << 8) + ((buf[pos++] & 0xFF) << 16) + ((long)((buf[pos++] & 0xFF)) << 24))
#endmacro



// int bufferReadInt(TBuffer buf, int pos)
#macro bufferReadInt(buf, pos)
((buf[pos++] & 0xFF) + ((buf[pos++] & 0xFF) << 8) + ((buf[pos++] & 0xFF) << 16) + ((buf[pos++] & 0xFF) << 24))
#endmacro


// void gc()
#macro gc()
System.gc()
#endmacro


// TIntArray createIntArray(int size)
#macro createIntArray(size)
new int[size]
#endmacro


// void freeIntArray(TIntArray array)
#macro freeIntArray(array)
array = null
#endmacro



// TStrings createStrings(int size)
#macro createStrings(size)
new String[size]
#endmacro



// void freeStrings(TStrings array)
#macro freeStrings(array)
array = null
#endmacro


// TTimeArray createTimeArray(int size)
#macro createTimeArray(size)
new long[size]
#endmacro


// void freeTimeArray(TTimeArray array)
#macro freeTimeArray(array)
array = null
#endmacro



#elseif CPP
#endif

#defineblock end
#endif // __MVL_STDDEFS_H__
