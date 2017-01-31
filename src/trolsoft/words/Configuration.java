package trolsoft.words;

import java.awt.Font;
import java.io.File;

import trolsoft.dict.MixedDictionary;
import trolsoft.utils.ConfigurationBase;
import trolsoft.utils.Utils;
import trolsoft.words.general.Lang;



public class Configuration extends ConfigurationBase {

	// ui
	public int uiColorEngl = 0x00ff00;
	public int uiColorEnglAlt = 0x00ff00;
	public int uiColorRus = 0x00dd00;
	public int uiColorRusAlt = 0x00dd00;
	public int uiColorTranscription = 0xffffff;
	public int uiPosY = -80;
	public int uiLayoutX = 1;	// 0 - по левому краю, 1 - по центру, 2 - по правому краю
	public boolean uiBackgroundDraw = true;
	public int uiBackgroundColor = 0x0000ff;
	public int uiTransparency = 0;		// прозрачность

	public Font uiFontEngl = new Font("Serif", Font.BOLD, 20);
	public Font uiFontRus = new Font("Serif", Font.BOLD, 20);
	public Font uiFontTranscription = new Font("Serif", Font.BOLD, 20);
	
	public Lang langMy = Lang.Russian;;
	public Lang langLearn = Lang.English;

	// dictionaries
	public String[] dictsLearn = {"." + File.separatorChar + "words.dic"};
	public String[] dictsDeleted = {"." + File.separatorChar + "deleted.dic"};
	public String[] dictsAll = {};
	public String[] dictsTranscriptions = {"." + File.separatorChar + "transcription.dic"};
	
	// learn
	public int learnTime = 4000; 			// период смены слов в режиме контроля (мс)
	public MixedDictionary.Mode learnMode = MixedDictionary.Mode.LearnToMy;
	public boolean learnTranscriptionShow = false;
	public boolean learnTranscriptionDelete = false;
	public boolean learnViewmode = false;	// если true, то режим запоминания
	public int learnViewTime = 10000;		// период произношения слов в режиме запоминания (мс)
	public boolean learnWordsMix = true;	// перемешивать слова перевода разделенные ;
	public int learnGroupwordslimit = 0;	// учить словарь группами с ограниченным числом слов (0-учить весь словарь без разбивки на группы)
	
	// sound
	public String[] soundEnglish = {"." + File.separatorChar + "voice-en.pak", "." + File.separatorChar + "voice-en", "." + File.separatorChar + "voice-load-en"};
	public String[] soundRussian = {"." + File.separatorChar + "voice-ru.pak", "." + File.separatorChar + "voice-ru", "." + File.separatorChar + "voice-load-ru"};
	
	public boolean soundControlPlayEnglish = true;	// произносить слова в режиме проверки
	public boolean soundControlPlayRussian = true;
	public boolean soundViewPlayEnglish = true;		// произносить слова в режиме заучивания
	public boolean soundViewPlayRussian = true;	
	
	public int soundPlayVolume = 100;	// громкость воспроизведения
	
	public String wordsUid = "";		// UID экземпляра приложения

	// audio generator
	public double generatorAudioIntervalWords = 1.0;
	public double generatorAudioIntervalPairs = 2.0;
	public int generatorAudioRepeatWords = 1;
	public int generatorAudioRepeatAll = 1;
	public MixedDictionary.Mode generatorAudioDirection = MixedDictionary.Mode.LearnToMy;
	public int generatorAudioWavSamplerate = 44100;
	public int generatorAudioWordsinfile = 100;
	public String generatorAudioOutpath = "";
	

	private static final String CONFIG_FILENAME = "words.conf";
	

	public Configuration() {
//		afterLoad();
	}
	
	
	@Override
	public String getFileName() {
		return getRootPath() + File.separatorChar + CONFIG_FILENAME;
	}

	
	/**
	 * 
	 * @return
	 */
	private static String generateUid() {
		String result = "";
		for ( int i = 0; i < 16; i++ ) {
			int v = Utils.random(0xff);
			String s = Integer.toHexString(v);
			if ( s.length() == 1 ) {
				s = '0' + s;
			}
			result += s;
		}
		return result;
	}
	
	@Override
	public void afterLoad() {
		if ( wordsUid == null || wordsUid.trim().length() < 10 ) {
			wordsUid = generateUid();
			save();
		}
	}

	@Override
	public void beforeSave() {
	}
	
	

	public String uiColorEnglSaver() {
		return color2str(uiColorEngl);
	}
	
	public void uiColorEnglLoader(String val) {
		uiColorEngl = str2color(val);
	}
	
	public String uiColorRusSaver() {
		return color2str(uiColorRus);
	}
	
	public void uiColorRusLoader(String val) {
		uiColorRus = str2color(val);
	}
	
	public String uiColorTranscriptionSaver() {
		return color2str(uiColorTranscription);
	}
	
	public void uiColorTranscriptionLoader(String val) {
		uiColorTranscription = str2color(val);
	}
	
	public String uiBackgroundColorSaver() {
		return color2str(uiBackgroundColor);
	}
	
	public void uiBackgroundColorLoader(String val) {
		uiBackgroundColor = str2color(val);
	}
	

	public String[] dictsLearnSaver() {
		return packLocalPath(dictsLearn);
	}
	
	public void dictsLearnLoader(String[] val) {
		dictsLearn = unpackLocalPath(val);
	}
	
	public String[] dictsDeletedSaver() {
		return packLocalPath(dictsDeleted);
	}
	
	public void dictsDeletedLoader(String[] val) {
		dictsDeleted = unpackLocalPath(val);
	}

	public String[] soundEnglishSaver() {
		return packLocalPath(soundEnglish);
	}
	
	public void soundEnglishLoader(String[] val) {
		soundEnglish = unpackLocalPath(val);
	}
	
	public String[] soundRussianSaver() {
		return packLocalPath(soundRussian);
	}
	
	public void soundRussianLoader(String[] val) {
		soundRussian = unpackLocalPath(val);
	}
	
	public String uiFontEnglSaver() {
		return font2str(uiFontEngl);
	}
	
	public void uiFontEnglLoader(String val) {
		uiFontEngl = str2font(val);
	}
	
	public String uiFontRusSaver() {
		return font2str(uiFontRus);
	}
	
	public void uiFontRusLoader(String val) {
		try {
			uiFontRus = str2font(val);
		} catch (Exception e) {	}
	}
	
	public String uiFontTranscriptionSaver() {
		return font2str(uiFontTranscription);
	}
	
	public void uiFontTranscriptionLoader(String val) {
		try {
			uiFontTranscription = str2font(val);
		} catch (Exception e) {	}
	}
	
	public String[] dictsAllSaver() {
		return packLocalPath(dictsAll);
	}
	
	public void dictsAllLoader(String[] val) {
		dictsAll = unpackLocalPath(val);
	}
	
	public String[] dictsTranscriptionsSaver() {
		return packLocalPath(dictsTranscriptions);
	}
	
	public void dictsTranscriptionsLoader(String[] val) {
		dictsTranscriptions = unpackLocalPath(val);
	}

	public String langMySaver() {
		return langMy.name();
	}

	public void langMyLoader(String val) {
		langMy = Lang.valueOf(val);
	}
	
	public String langLearnSaver() {
		return langLearn.name();
	}

	public void langLearnLoader(String val) {
		langLearn = Lang.valueOf(val);
	}
	
	public String generatorAudioDirectionSaver() {
		return generatorAudioDirection.name();
	}
	
	public void generatorAudioDirectionLoader(String val) {
		generatorAudioDirection = MixedDictionary.Mode.valueOf(val);
	}

	public String learnModeSaver() {
		return learnMode.name();
	}
	
	public void learnModeLoader(String val) {
		learnMode = MixedDictionary.Mode.valueOf(val);
	}
	
}
