// создание приложения
public final void onCreate() {
  setScreensCount(MAX_SCREENS_COUNT);
}



// иннициализация приложения
public final void onInit() {

  imgBtns = createImage("btns.png");
  createGUI();
  createMainMenu();
  readWordsHeader();
  loadOptions();
  loadStatistic();
  initWordsIndex();
}



// уничтожение приложения
public final void onDestroy() {
}



// пауза приложения
public final void onPause() {
}



// пауза приложения
public final void onShow() {
}



// пауза приложения
public final void onHide() {
}

