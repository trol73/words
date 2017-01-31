#ifnotdef __MVL_EVENTS_H__
#define   __MVL_EVENTS_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                            Trol Mobile Studio v 1.0
                            Moblie Visual Libraries


                        Keyboard, action and events codes

                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.01


\*----------------------------------------------------------------------------*/



#ifdef J2ME

// J2ME: коды клавиатуры
#define  KEY_NUM0       Canvas.KEY_NUM0
#define  KEY_NUM1       Canvas.KEY_NUM1
#define  KEY_NUM2       Canvas.KEY_NUM2
#define  KEY_NUM3       Canvas.KEY_NUM3
#define  KEY_NUM4       Canvas.KEY_NUM4
#define  KEY_NUM5       Canvas.KEY_NUM5
#define  KEY_NUM6       Canvas.KEY_NUM6
#define  KEY_NUM7       Canvas.KEY_NUM7
#define  KEY_NUM8       Canvas.KEY_NUM8
#define  KEY_NUM9       Canvas.KEY_NUM9
#define  KEY_POUND      Canvas.KEY_POUND
#define  KEY_STAR       Canvas.KEY_STAR

// J2ME коды действий
#define  ACT_UP         Canvas.UP
#define  ACT_DOWN       Canvas.DOWN
#define  ACT_LEFT       Canvas.LEFT
#define  ACT_RIGHT      Canvas.RIGHT
#define  ACT_FIRE       Canvas.FIRE
#define  ACT_SOFT1      21               // левая софк-клавиша
#define  ACT_SOFT2      22               // правая софт-клавиша
#define  ACT_SOFT3      23               // средняя софт-клавиша


#else
#endif

#defineblock end
#ifdef J2ME
/*
bool translateKeyToAction (int keyCode, TTime time) {
  switch ( keyCode ) {
    case KEY_NUM4:
      onAction(ACT_LEFT, time);
      return true;
    case KEY_NUM6:
      onAction(ACT_RIGHT, time);
      return true;
    case KEY_NUM2:
      onAction(ACT_UP, time);
      return true;
    case KEY_NUM8:
      onAction(ACT_DOWN, time);
      return true;
    case KEY_NUM5:
      onAction(ACT_FIRE, time);
      return true;
  }
  return false;
}


bool translateKeyToActionRepeated (int keyCode, TTime time) {
  switch ( keyCode ) {
    case KEY_NUM4:
      onActionRepeated(ACT_LEFT, time);
      return true;
    case KEY_NUM6:
      onActionRepeated(ACT_RIGHT, time);
      return true;
    case KEY_NUM2:
      onActionRepeated(ACT_UP, time);
      return true;
    case KEY_NUM8:
      onActionRepeated(ACT_DOWN, time);
      return true;
    case KEY_NUM5:
      onActionRepeated(ACT_FIRE, time);
      return true;
  }
  return false;
}
*/
#else
#endif

#endif // __MVL_EVENTS_H__

