static int idleWordIndex;
static int processWordsCompleted1_cnt;
static int processWordsCompleted2_cnt;

// вызывается во время бездействия системы
public final TTime onIdle() {
  switch ( getScreen() ) {
    case SCREEN_WAIT:
      repaint();
      return 300;
      
    case SCREEN_WORDS:
      // подсчитываем в фоне количество угаданных слов. за проход обрабатываем не более 10 слов
      for ( int i = 0; i < 25; i++) {
        switch ( options_EngRus ) {
          case 0:
            if ( wordsLevelEng[idleWordIndex] == WL_BAD )
              processWordsCompleted1_cnt++;
            else if ( wordsLevelEng[idleWordIndex] == WL_GOOD )
              processWordsCompleted2_cnt++;
            break;
          case 1:
            if ( wordsLevelRus[idleWordIndex] == WL_BAD )
              processWordsCompleted1_cnt++;
            else if ( wordsLevelRus[idleWordIndex] == WL_GOOD )
              processWordsCompleted2_cnt++;
            break;
          case 2:
            if ( wordsLevelEng[idleWordIndex] == WL_BAD )
              processWordsCompleted1_cnt++;
            else if ( wordsLevelEng[idleWordIndex] == WL_GOOD )
              processWordsCompleted2_cnt++;
            if ( wordsLevelRus[idleWordIndex] == WL_BAD )
              processWordsCompleted1_cnt++;
            else if ( wordsLevelRus[idleWordIndex] == WL_GOOD )
              processWordsCompleted2_cnt++;
            break;
        } // switch
        idleWordIndex++;
        if ( idleWordIndex >= wordsLevelEng.length ) {
          processWordsCompleted1 = processWordsCompleted1_cnt;
          processWordsCompleted2 = processWordsCompleted2_cnt;
          processWordsCompleted1_cnt = 0;
          processWordsCompleted2_cnt = 0;
          idleWordIndex = 0;
          break;
        }
      }
      
      repaint();
      return 300;
  }
  return 100;
}

