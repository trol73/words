static int wordCount;          // число слов

// смещения слов
static int[] wordEnglPos;
static int[] wordEnglSize;

static TStrings wordEnglish;   // английские слова
static TStrings wordRussian;   // русские слова
static byte[] wordsLevelEng;       // оценка знания слова WL_xxx
static byte[] wordsLevelRus;

static int options_EngRus = 0;
static int options_Words = 0;

// массив индексов слов. делает выборку всех слов, удовлетворяющих критериям
static int[] wordsIndex;

static int wordIndexPos = 0;

static Random random = new Random();

static int mixTypeLang; // для режима вперемешку равен 0 для английского или 1 для русского


// читает заголовок файла слов
static final bool readWordsHeader() {
  TFile f = fileOpen(WORDS_FILE);
  wordCount = fileReadWord(f);
  wordEnglPos = new int[wordCount+1];
  wordEnglSize = new int[wordCount];
  wordEnglish = new TString[wordCount];
  wordRussian = new TString[wordCount];
  wordsLevelEng = new byte[wordCount];
  wordsLevelRus = new byte[wordCount];
  for (int i = 0; i < wordCount; i++) {
    wordEnglPos[i] = fileReadWord(f);
    wordEnglSize[i] = fileReadByte(f);
    wordsLevelEng[i] = WL_UNKNOWN;
    wordsLevelRus[i] = WL_UNKNOWN;
  }
  wordEnglPos[wordCount] = fileReadWord(f);
  fileClose(f);
  return true;
}




// читает пару слов
static final bool readWordsPair(int index) {
  TFile f = fileOpen(WORDS_FILE);
  int pos = wordEnglPos[index];
  int len1 = wordEnglSize[index];
  int len2 = wordEnglPos[index+1]-wordEnglPos[index] - len1;
  fileSkip(f, pos);

  try {
    byte[] data;
    data = new byte[len1];
    fileRead(f, data, len1);
    wordEnglish[index] = new String(data, "utf8");

    data = new byte[len2];
    fileRead(f, data, len2);
    wordRussian[index] = new String(data, "utf8");
  } catch ( UnsupportedEncodingException e) {
    e.printStackTrace();
  }
/*
  StringBuffer sb = new StringBuffer();
  for (int i = 0; i < len1; i++) {
    sb.append(char1251ToUnicode(fileReadByte(f)));
  }
  wordEnglish[index] = sb.toString();

  sb = new StringBuffer();
  for (int i = 0; i < len2; i++) {
    sb.append(char1251ToUnicode(fileReadByte(f)));
  }
  wordRussian[index] = sb.toString();
*/
 
  fileClose(f);
  return true;
}


static final TString getEngWord(int index) {
  if ( wordEnglish[index] == null )
    readWordsPair(index);
  return wordEnglish[index];
}


static final TString getRusWord(int index) {
  if ( wordRussian[index] == null )
    readWordsPair(index);
  return wordRussian[index];
}


static final TBuffer loadRMS(TString name, int index) {
  RecordStore rs = null;
  byte buf[] = null;
  try {
    rs = RecordStore.openRecordStore(name, false);
    buf = rs.getRecord(index);
  } catch ( RecordStoreException rse ) { buf = null; }
   if ( rs != null )
     try {
        rs.closeRecordStore();
  } catch ( RecordStoreException rse ) { buf = null; }
  return buf;
}


static final void saveRMS(TString name, int index, TBuffer buf) {
  RecordStore rs = null;
  try {
    rs = RecordStore.openRecordStore(name, true);
    if ( rs.getNumRecords() == 0 )
       rs.addRecord(buf, 0, buf.length);
      else
       rs.setRecord(index, buf, 0, buf.length);
  } catch ( RecordStoreException rse ) {  }
  if ( rs != null )
    try { rs.closeRecordStore(); } catch ( RecordStoreException rse ) {  }
}



static final bool loadOptions() {
  TBuffer buf = loadRMS("options", 1);
  if ( buf == null )
    return false;
  options_EngRus = (int)buf[0];
  options_Words = (int)buf[1];
  return true;
}


static final bool saveOptions() {
  TBuffer buf = new byte[2];
  buf[0] = (byte)options_EngRus;
  buf[1] = (byte)options_Words;
  saveRMS("options", 1, buf);
  return true;
}


static final bool loadStatistic() {
  TBuffer buf = loadRMS("statistic", 1);
  if ( buf == null )
    return false;
  if ( buf.length != wordCount )
    return false;
  int pos = 0;
  for (int i = 0; i < wordCount; i++) {
    int val = (int)buf[pos++] & 0xFF;
    wordsLevelEng[i] = (byte)((val >> 3) & 7);
    wordsLevelRus[i] = (byte)(val & 7);
  }
  return true;
}



static final void saveStatistic() {
  TBuffer buf = new byte[wordCount];
  for (int i = 0; i < wordCount; i++)
    buf[i] = (byte)((wordsLevelEng[i] << 3) + wordsLevelRus[i]);
  saveRMS("statistic", 1, buf);
}



static final bool isActualWord(int index) {
  // если режим вперемешку
  if ( options_EngRus == 2 ) {
    options_EngRus = 0;
    bool ac1 = isActualWord(index);
    options_EngRus = 1;
    bool ac2 = isActualWord(index);
    options_EngRus = 2;
    return ac1 || ac2;
  }
  int wordLevel = options_EngRus == 0 ? wordsLevelEng[index] : wordsLevelRus[index];
  switch ( options_Words ) {
    case 0:              // Все
      return true;
    case 1:              // Выученные
      return wordLevel == WL_GOOD;
    case 2:              // Плоховыученные
      return wordLevel == WL_BAD;
    case 3:              // Невыученные
      return wordLevel == WL_UNKNOWN;
    case 4:              // Плохо+невыученны
      return wordLevel == WL_UNKNOWN || wordLevel == WL_BAD;
  }
  return false;
}



// иннициализируем инднкс актуальных слов
final void initWordsIndex() {
  int cnt = 0;
  for (int i = 0; i < wordCount; i++)
    if ( isActualWord(i) )
      cnt++;
  if ( cnt == 0 ) {
    messageBox("Слова закончились", null, "Ок", MBC_WORD_COMPLETE);
    return;
  }

  
  wordsIndex = new int[cnt];
  cnt = 0;
  for (int i = 0; i < wordCount; i++)
    if ( isActualWord(i) )
      wordsIndex[cnt++] = i;
  mixIndex();
}


// перемешывает индекс случайным образом
final void mixIndex() {
  for ( int i = 0 ; i < 2*wordsIndex.length/3; i++ ) {
    int p1 = random.nextInt() % wordsIndex.length;
    int p2 = random.nextInt() % wordsIndex.length;
    if ( p1 < 0 )
      p1 = -p1;
    if ( p2 < 0 )
      p2 = -p2;
    int t = wordsIndex[p1];
    wordsIndex[p1] = wordsIndex[p2];
    wordsIndex[p2] = t;
  }
}



  
final TString getNextWord() {
  if ( wordIndexPos >= wordsIndex.length ) {
    wordIndexPos = 0;
    initWordsIndex();
    if ( wordsIndex.length == 0 )
      return "";
  }
  int index = wordsIndex[wordIndexPos++];

  // если режим вперемешку
  if ( options_EngRus == 2 ) {
    options_EngRus = 0;
    bool ac1 = isActualWord(index);
    options_EngRus = 1;
    bool ac2 = isActualWord(index);
    options_EngRus = 2;
    if ( ac1 && !ac2 )
      mixTypeLang = 0;
    else if ( ac2 && !ac1 )
      mixTypeLang = 1;
    else
      mixTypeLang = Math.abs(random.nextInt() % 2);
    return mixTypeLang == 0 ? getEngWord(index) : getRusWord(index);
  }
  return options_EngRus == 0 ? getEngWord(index) : getRusWord(index);
}


static final TString getCurrentWordPair() {
  if ( wordsIndex.length == 0 )
    return "";
  int index = wordsIndex[wordIndexPos-1];
  if ( options_EngRus == 2 )
    return mixTypeLang == 1 ? getEngWord(index) : getRusWord(index);
  return options_EngRus == 1 ? getEngWord(index) : getRusWord(index);
}


static final void setCurrentWordLevel(int level) {
  int index = wordsIndex[wordIndexPos-1];
  if ( options_EngRus == 0 ) {
    wordsLevelEng[index] = (byte)level;
  } else if ( options_EngRus == 1 ) {
    wordsLevelRus[index] = (byte)level;
  } else if ( options_EngRus == 2 ) {
    if ( mixTypeLang == 0 )
      wordsLevelEng[index] = (byte)level;
    else
      wordsLevelRus[index] = (byte)level;
  }
}



