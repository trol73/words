// обработчик прорисовки
public final void onPaint(TGraphics g) {
  switch ( getScreen() ) {
    case SCREEN_WAIT:
      setFillColor(0);
      fillRect(0, 0, getScreenWidth(), getScreenHeight());
      break;
  }
}



// вызывается после отрисовки интерфейса
public final void onPostPaint(TGraphics g) {
  switch ( getScreen() ) {
    case SCREEN_WORDS:
      setClip(0, 0, getScreenWidth(), getScreenHeight());
      TTime time = getSystemTime(startTime);
      int t = (int)(time/1000);

      int min = (t / 60) % 60;
      int sec = t % 60;
      int hour = t / 3600;
      TString hourS = ( hour == 0 ) ? "" : Integer.toString(hour)+':';
      TString minS = Integer.toString(min);
      if ( min < 10 && hour != 0 )
        minS = '0'+minS;
      minS += ':';
      TString secS = Integer.toString(sec);
      if ( sec < 10  )
        secS = '0'+secS;

      setFont(fontBold);
      setTextColor(0xFFFFFF);
      drawString(hourS+minS+secS, getScreenWidth()-5, 2, KAnchorRight|KAnchorTop);

      setLineColor(0x6666FF);
      drawRect(3, 3, getScreenWidth()-60, 10);
      if ( processWordsTotal != 0 ) {
        setFillColor(0x9999FF);
        fillRect(4, 4, (getScreenWidth()-61)*(processWordsCompleted1+processWordsCompleted2)/processWordsTotal, 9);
        setFillColor(0x7777FF);
        fillRect(4, 4, (getScreenWidth()-61)*processWordsCompleted2/processWordsTotal, 9);
      }


      if ( isWordShowed ) {
#ifdef DEVICE_240
        drawImage(imgBtns, getScreenWidth()/2, getScreenHeight()-80, KAnchorHCenter|KAnchorTop);
#else
        drawImage(imgBtns, getScreenWidth()/2, getScreenHeight()-50, KAnchorHCenter|KAnchorTop);
#endif
      }

      break;
  }
}

