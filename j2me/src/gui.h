static TItem lstMainMenu;

static TItem cbOptionsRusEngl;
static TItem cbOptionsWords;

static TForm frmWord;
static TItem frmWordWord2;

static TItem btnClearStatistic;

static TItem softMenu, softOk, softOk2;

static final TStrings mainMenu_items = { "Начать", "Словарь", "Статистика", "Настройки", "Справка", "Выход" };
static final TStrings optionsRusEngl = { "англ->рус", "рус->англ", "вперемешку" };
static final TStrings optionsWords = { "все", "хорошо", "плохо", "никак", "плохо+никак" };

static bool isWordShowed;

// создает все необходимые элементы интерфейса
void createGUI() {
  // загружаем шрифты
  try {
    fontDefault = createFont("f128.bin");
    fontBold = createFont("fb128.bin");
  } catch ( Exception e) {
  }
  if ( fontDefault == null ) {
    try {
      fontDefault = createFont("f176.bin");
      fontBold = createFont("fb176.bin");
    } catch ( Exception e) {
    }
  }
  if ( fontDefault == null ) {
    try {
      fontDefault = createFont("f240.bin");
      fontBold = createFont("fb240.bin");
    } catch ( Exception e) {
    }
  }
  
  fntDefault = mvlRegisterFont(fontDefault);
  fntBold = mvlRegisterFont(fontBold);
  
  softMenu = mvlCreateSoftButton("Меню" , KItemSoftButtonLeft|KItemSoftButtonClear);
  mvlSetItemColors(softMenu, 0x000000, 0x9999BB);
  mvlSetItemFont(softMenu, fntBold);

  softOk = mvlCreateSoftButton("Ок", KItemSoftButtonRight|KItemSoftButtonClear);
  mvlSetItemColors(softOk, 0x000000, 0x9999BB);
  mvlSetItemFont(softOk, fntBold);

  softOk2 = mvlCreateSoftButton("Ок", KItemSoftButtonRight);
  mvlSetItemColors(softOk2, 0x000000, 0x9999BB);
  mvlSetItemFont(softOk2, fntBold);

}


void createMainMenu() {
  lstMainMenu = mvltCreateList(SCREEN_MAINMENU, "Словозубр", KItemListIconText|KitemListCircular);
  mvltAppendListItems(mainMenu_items, mvltLoadImages("pics.png"));
  mvltAppendToScreen(softOk);
  mvltCreateScreenDone(true);
}


void createOptionsForm() {
  mvltCreateForm(SCREEN_OPTIONS, "Настройки");

  mvltAppendStaticText("Перевод с");

  cbOptionsRusEngl = mvltAppendCombobox(optionsRusEngl);
  mvlSetItemSelected(cbOptionsRusEngl, options_EngRus);

  mvltAppendStaticText("Выбирать слова, которые я помню");
  cbOptionsWords = mvltAppendCombobox(optionsWords);
  mvlSetItemSelected(cbOptionsWords, options_Words);

  mvltAppendStaticText("");
  mvltAppendStaticText("Очистить статистику и начать контроль запоминания заново");
  btnClearStatistic = mvltAppendButton("Очистить", "clear");


  mvltAppendToScreen(softMenu);
  mvltAppendToScreen(softOk2);
  mvltCreateScreenDone(true);
}



void createWordForm(TString s1, TString s2) {
  setScreen(SCREEN_WAIT);
  isWordShowed = false;
  frmWord = mvltCreateForm(SCREEN_WORDS, "");
  TItem txt = mvltAppendStaticText(s1);
  mvltAppendStaticText("");
  frmWordWord2 = mvltAppendStaticText(s2);
  mvlSetItemColors(frmWordWord2, MVLTC_FORM_BACKGROUND, MVLTC_FORM_BACKGROUND);
  mvltAppendToScreen(softMenu);
  mvltCreateScreenDone(false);
  mvlSetItemAlignment(txt, KAlignHCenter);
  mvlSetItemAlignment(frmWordWord2, KAlignHCenter);
  setScreen(SCREEN_WORDS);
  repaint();
}


void createStatristicForm() {
  mvltCreateForm(SCREEN_STATISTIC, "Статистика");
  mvltAppendLabel("Всего слов: ");
  mvltAppendStaticText(""+wordCount);

  int good1 = 0, good2 = 0;
  int bad1 = 0, bad2 = 0;
  int unknown1 = 0, unknown2 = 0;
  for (int i = 0; i < wordCount; i++) {
    if ( wordsLevelEng[i] == WL_GOOD )
      good1++;
    if ( wordsLevelRus[i] == WL_GOOD )
      good2++;
    if ( wordsLevelEng[i] == WL_BAD )
      bad1++;
    if ( wordsLevelRus[i] == WL_BAD )
      bad2++;
    if ( wordsLevelEng[i] == WL_UNKNOWN )
      unknown1++;
    if ( wordsLevelRus[i] == WL_UNKNOWN )
      unknown2++;
  }
	if ( wordCount > 0 ) {
		mvltAppendLabel("Не выучено: ");
		mvltAppendStaticText(""+unknown1+" / "+unknown2+ "  ("+(unknown1*100/wordCount)+"% / "+(unknown2*100/wordCount)+"% )");
		mvltAppendLabel("Выучено плохо: ");
		mvltAppendStaticText(""+bad1+" / "+bad2+ "  ("+(bad1*100/wordCount)+"% / "+(bad2*100/wordCount)+"% )");
		mvltAppendLabel("Выучено: ");
		mvltAppendStaticText(""+good1+" / "+good2+ "  ("+(good1*100/wordCount)+"% / "+(good2*100/wordCount)+"% )");
		mvltAppendToScreen(softMenu);
		mvltCreateScreenDone(true);
	}
}


void createHelpForm() {
  mvltCreateForm(SCREEN_HELP, "Справка");
  mvltAppendStaticText("Версия 1.04");
  
  mvltAppendLabel("Использование");
  mvltAppendStaticText("Программа для запоминания иностранных слов");
  mvltAppendStaticText("В режиме просмотра слов сначала отображается слово, которое надо перевести. Далее, при нажатии на любую клавишу, кроме '0', показывается перевод этого слова. Клавишу '0' можно нажать, если подсветка телефона отключилась после долгого ненажимания клавиш. Если этот перевод запомнен, надо нажать клавишу '6', если слово не знакомо - клавишу '4', если же перевод помнится, но неуверенно - клавишу '5'. После чего будет показано следующее случайно выбранное слово и так до бесконечности. В верхней части экрана показывается время опроса, число спрошенных слов и статистика запоминания сеанса.");
  mvltAppendStaticText("В настройках можно указать направление перевода и то, какие слова стоит показывать. Также, тут можно сбросить статистику (т.е., пометить все слова как незапомненные).");
  mvltAppendStaticText("В режиме словаря можно посмотреть полный список слов.");
  mvltAppendStaticText("");
  mvltAppendLabel("Copyright:");
  mvltAppendStaticText("TrolSoft, 2008-2011");
  mvltAppendStaticText("http://trol.0fees.net");
  mvltAppendStaticText("otrifonow@gmail.com");
  mvltAppendStaticText("");

  mvltAppendToScreen(softMenu);
  mvltCreateScreenDone(true);
}



void createListForm() {
  mvltCreateForm(SCREEN_LIST, "Словарь");
  mvltAppendStaticText("Всего слов: "+wordCount);
  for ( int i = 0; i < wordCount; i++) {
    TString s1 = options_EngRus != 1 ? getEngWord(i) : getRusWord(i);
    TString s2 = options_EngRus != 1 ? getRusWord(i) : getEngWord(i);
    mvltAppendLabel(s1);
    mvltAppendStaticText(s2);
  }
  mvltAppendToScreen(softMenu);
  mvltCreateScreenDone(true);
}


public final void freeAll() {
  cbOptionsRusEngl = null;
  cbOptionsWords = null;
  frmWord = null;
  frmWordWord2 = null;
  btnClearStatistic = null;
  mvlRemoveAllScreenItems(SCREEN_WORDS);
  mvlRemoveAllScreenItems(SCREEN_OPTIONS);
  mvlRemoveAllScreenItems(SCREEN_HELP);
  mvlRemoveAllScreenItems(SCREEN_STATISTIC);
  mvlRemoveAllScreenItems(SCREEN_LIST);
  gc();
}
