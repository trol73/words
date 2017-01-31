#ifnotdef __MVL_BASE_H__
#define   __MVL_BASE_H__
#defineblock begin

/*----------------------------------------------------------------------------*\

                             Trol Mobile Studio v 1.0
                            Moblie Visual Libraries

                                Base functions


                      Copyright (c) O.A. Trifonov, 2007
                                 Version 1.0

\*----------------------------------------------------------------------------*/

#macro getScreen()
_mvl_screen
#endmacro


#macro setScreen(screen)
_mvl_screen = screen
#endmacro



#macro repaint()
{_mvl_mainFrame.repaint();_mvl_mainFrame.serviceRepaints();}
#endmacro


#macro repaint(x, y, w, h)
{_mvl_mainFrame.repaint(x, y, w, h);_mvl_mainFrame.serviceRepaints();}
#endmacro


#defineblock end
#endif

