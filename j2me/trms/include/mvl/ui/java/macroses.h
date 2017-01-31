#ifnotdef __MVL_UI_JAVA_MACROSES_H__
#define   __MVL_UI_JAVA_MACROSES_H__
#defineblock begin
/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                          User interface macroses unit


                      Copyright (c) O.A. Trifonov, 2007
                                  Version 1.01

\*----------------------------------------------------------------------------*/


#macro mvlSetItemPos(itm, x, y)
_mvl_void_macro(itm).setCoord(x, y)
#endmacro



#macro mvlSetUiItemSize(itm, w, h)
_mvl_void_macro(itm).setSize(w, h)
#endmacro


#macro mvlSetItemColors(itm, color, background)
_mvl_void_macro(itm).setColor(color, background)
#endmacro


#macro mvlSetItemColors(itm, color, background, colorFocused, backgroundFocused)
_mvl_void_macro(itm).setColor(color, background, colorFocused, backgroundFocused)
#endmacro


#macro mvlSetItemFont(itm, fontIndex)
_mvl_void_macro(itm).setFontIndex(fontIndex)
#endmacro


#macro mvlSetItemFont(itm, fontIndex, fontFocusedIndex)
_mvl_void_macro(itm).setFontIndex(fontIndex, fontFocusedIndex)
#endmacro


#macro mvlSetItemAlignment(itm, align)
_mvl_void_macro(itm).setAlignment(align)
#endmacro


#macro mvlSetItemInterval(itm, interval)
_mvl_void_macro(itm).setInterval(interval)
#endmacro


#macro mvlIsItemFocusable(itm)
_mvl_void_macro(itm).isFocusable()
#endmacro


#macro mvlAppendItem(frm, itm)
_mvl_void_macro(frm).appendItem(itm)
#endmacro


#macro mvlDeleteItem(frm, itm)
_mvl_void_macro(frm).deleteItem(itm)
#endmacro


#macro mvlGetItemString(itm)
_mvl_void_macro(itm).getString()
#endmacro


#macro mvlGetItemString(itm, index)
_mvl_void_macro(itm).getString(index)
#endmacro


#macro mvlSetItemString(itm, str)
_mvl_void_macro(itm).setString(str)
#endmacro



#macro mvlSetItemString(itm, str, index)
_mvl_void_macro(itm).setString(str, index)
#endmacro


#macro mvlGetItemStringsCount(itm)
_mvl_void_macro(itm).getStringsCount()
#endmacro


#macro mvlAppendItemString(itm, str)
_mvl_void_macro(itm).appendString(str)
#endmacro


#macro mvlSetItemTime(itm, t)
_mvl_void_macro(itm).setTime(t)
#endmacro


#macro mvlSetItemImageFrame(itm, index)
_mvl_void_macro(itm).setImageFrame(index)
#endmacro


#macro mvlAssignScrollBarToForm(scroll, form)
_mvl_void_macro(scroll).assignScrollBarToForm(form)
#endmacro



#macro mvlActivateItem(item)
_mvl_void_macro(item).activate()
#endmacro






#defineblock end
#endif  // __MVL_UI_JAVA_MACROSES_H__
