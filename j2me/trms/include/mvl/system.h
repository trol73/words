#ifnotdef __MVL_SYSTEM_H__
#define   __MVL_SYSTEM_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                             Base system functions


                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.0

\*----------------------------------------------------------------------------*/


#defineblock end
  #ifdef JAVA
  public static final void sleep(TTime t) {
    if (t > 0) {
      try {
        Thread.sleep(t);
      } catch ( Exception ex ) { }
    }
  }

  
  
  public static final long getSystemTime() {
    return System.currentTimeMillis();
  }
  

  
  public static final long getSystemTime(long t) {
    return System.currentTimeMillis() - t;
  }



  public static final void quit() {
    _mvl_instance.destroyApp(true);
    _mvl_instance.notifyDestroyed();
    _mvl_instance = null;
  }
  
  

  #ifdef J2ME
    #ifdef ENABLE_BACKBUFFER
  public static final void repaintToBB() {
    _mvl_drawToBackBuffer = true;
    _mvl_mainFrame.repaint();
    _mvl_mainFrame.serviceRepaints();
  }
  
  
  
  public static final void repaintFromBB() {
    _mvl_drawFromBackBuffer = true;
    _mvl_mainFrame.repaint();
    _mvl_mainFrame.serviceRepaints();
  }
  
  
  public static final Image getBackBufferImage() {
    return _mvl_screenBackBufferImage;
  }
    #endif // ENABLE_BACKBUFFER
  #endif // J2ME
  
  #endif // JAVA
#endif // __MVL_SYSTEM_H__

