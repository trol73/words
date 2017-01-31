// нажатие клавиши
public final bool onKeyPressed(int keyCode, TTime time) {
  gc();
  switch ( getScreen() ) {
    case SCREEN_WORDS:
      if ( wordsIndex.length == 0 )
        return false;
      if ( !isWordShowed && keyCode >= KEY_NUM1 && keyCode <= KEY_NUM9 ) {
        isWordShowed = true;
        mvlSetItemColors(frmWordWord2, MVLT_STATICTEXT_COLOR, MVLTC_FORM_BACKGROUND);
        repaint();
        return true;
      } else {
        if ( keyCode == KEY_NUM4 ) {
          setCurrentWordLevel(WL_UNKNOWN);
          createWordForm(getNextWord(), getCurrentWordPair());
          wordsProcessed++;
          unknownProcessed++;
          return true;
        } else if ( keyCode == KEY_NUM5 ) {
          setCurrentWordLevel(WL_BAD);
          createWordForm(getNextWord(), getCurrentWordPair());
          wordsProcessed++;
          badProcessed++;
          return true;
        } else if ( keyCode == KEY_NUM6 ) {
          setCurrentWordLevel(WL_GOOD);
          createWordForm(getNextWord(), getCurrentWordPair());
          wordsProcessed++;
          goodProcessed++;
          return true;
        }
      }
      break;
  }
  return false;
}



// отпускание клавиши
public final void onKeyReleased(int keyCode, TTime time) {
  switch ( getScreen() ) {
  }
}



// удержание клавиши
public final bool onKeyRepeated(int keyCode, TTime time) {
  switch ( getScreen() ) {
  }
  return false;
}



// действия (события от джойстика, колеса и пр)
public final void onAction(int action, TTime time) {
  if ( mvlToolsProcessKeyActionEvent(action) )
    return;
  switch ( getScreen() ) {
  }
}



// повторение действия
public final bool onActionRepeated(int action, TTime time) {
  if ( time >= 100)
    if ( action == ACT_UP || action == ACT_DOWN )
      return mvlSendActionToUi(action, time, true);

  switch ( getScreen() ) {
  }
  return false;
}



// события от элементов интерфейса
public final void onEvent(TForm form, TItem item, TEvent event, TTime time) {
  if ( event == EVENT_PUSH && item == softMenu ) {
    saveStatistic();
    setScreen(SCREEN_MAINMENU);
    repaint();
    return;
  }
  
  switch ( getScreen() ) {
    case SCREEN_WORDS:
      break;
    case SCREEN_OPTIONS:
      if ( event == EVENT_PUSH && item == softOk2 ) {
        options_EngRus = mvlGetItemSelected(cbOptionsRusEngl);         // сохранение настроек
        options_Words = mvlGetItemSelected(cbOptionsWords);
        saveOptions();
        initWordsIndex();
        setScreen(SCREEN_MAINMENU);
        repaint();
      } else if ( event == EVENT_PUSH && item == btnClearStatistic ) {
        wordsLevelEng = new byte[wordCount];
        wordsLevelRus = new byte[wordCount];
        for (int i = 0; i < wordCount; i++) {
          wordsLevelEng[i] = WL_UNKNOWN;
          wordsLevelRus[i] = WL_UNKNOWN;
        }
        saveStatistic();
        messageBox("Статистика была стерта", null, "Ок", MBC_INFO);
      }
      break;
    case SCREEN_HELP:
      break;
    case SCREEN_STATISTIC:
      break;
    case SCREEN_MAINMENU:
      if ( event == EVENT_PUSH ) {
      freeAll();
      switch ( mvlGetItemSelected(lstMainMenu) ) {
          case 0:                                 // Начать
            initWordsIndex();
            createWordForm(getNextWord(), getCurrentWordPair());
            startTime = getSystemTime();
            
           wordsProcessed = 0;
           goodProcessed = 0;
           badProcessed = 0;
           unknownProcessed = 0;

            processWordsCompleted1 = 0;
            processWordsCompleted2 = 0;
            for ( int i = 0; i < wordCount; i++)
              switch ( options_EngRus ) {
                case 0:
                  if ( wordsLevelEng[i] == WL_BAD )
                    processWordsCompleted1++;
                  else if ( wordsLevelEng[i] == WL_GOOD )
                    processWordsCompleted2++;
                  break;
                case 1:
                  if ( wordsLevelRus[i] == WL_BAD )
                    processWordsCompleted1++;
                  else if ( wordsLevelRus[i] == WL_GOOD )
                    processWordsCompleted2++;
                  break;
                case 2:
                  if ( wordsLevelEng[i] == WL_BAD )
                    processWordsCompleted1++;
                  else if ( wordsLevelEng[i] == WL_GOOD )
                    processWordsCompleted2++;
                  if ( wordsLevelRus[i] == WL_BAD )
                    processWordsCompleted1++;
                  else if ( wordsLevelRus[i] == WL_GOOD )
                    processWordsCompleted2++;
                  break;
              } // switch

            processWordsCompleted1_cnt = 0;
            processWordsCompleted2_cnt = 0;
            processWordsTotal = wordCount;
            if ( options_EngRus == 2 )
              processWordsTotal *= 2;
            idleWordIndex = 0;
            break;
          case 1:                                 // Словарь
            setScreen(SCREEN_WAIT);
            repaint();
            createListForm();
            break;
          case 2:                                 // Статистика
            createStatristicForm();
            break;
          case 3:                                 // Настройки
            createOptionsForm();
            break;
          case 4:                                 // Справка
            createHelpForm();
            break;
          case 5:                                 // Выход
            quit();
            break;
        }
      }
      break;
  }
}



// события от мыши и активного экрана
public final void onClick(int x, int y, int type, TTime time) {
  switch ( getScreen() ) {
  }
}
// вызывается когда пользователь сделал выбор в окне сообщений.
// в result передает 1, если нажата левая и 2, если правая софт-кнопка
public final void onMessageBoxEnter(int context, int result) {
  switch ( context ) {
    case MBC_WORD_COMPLETE:
      if ( getScreen() != SCREEN_MAINMENU ) {
        setScreen(SCREEN_MAINMENU);
        repaint();
      }
      break;
  }
}

