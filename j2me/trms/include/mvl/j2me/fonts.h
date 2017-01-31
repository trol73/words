#ifnotdef __MVL_FONTS_H__
#define   __MVL_FONTS_H__

#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                              Fonts functions unit


                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.0

\*----------------------------------------------------------------------------*/

#define KFontSystemDefault             0
#define KFontStylePlain                0
#define KFontStyleBold                 1
#define KFontStyleItalic               2
#define KFontStyleUnderlined           4
#define KFontSizeSmall                 8
#define KFontSizeMedium                0
#define KFontSizeLarge                 16
#define KFontFaceSystem                0
#define KFontFaceMonospace             32
#define KFontFaceProportional          64



// void freeFont(TFont font)
#macro freeFont(font)
font = null
#endmacro


#ifdef ENABLE_CUSTOM_FONTS


#macro setFontUnderlined(font, val)
_mvl_void_macro(font).setUnderlined(val)
#endmacro

#macro isFontUnderlined(fnt)
_mvl_void_macro(font).isUnderlined()
#endmacro



#else // ENABLE_CUSTOM_FONTS


#macro setFontUnderlined(font, val)
font = _mvl_setFontUnderlined(font, val)
#endmacro

#macro isFontUnderlined(fnt)
_mvl_void_macro(font).isUnderlined()
#endmacro



#endif  // ENABLE_CUSTOM_FONTS


#defineblock end
#endif // __MVL_FONTS_H__

