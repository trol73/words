package trolsoft.sound;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;

import trolsoft.utils.Utils;
import trolsoft.words.TimerTask;
import trolsoft.words.Words;
import trolsoft.words.general.Lang;


public class WordsPlayer {
	
	private static WordsPlayer instance;
	
	
	private String[] pathEngl;
	private String[] pathRuss;
	
	
	private static final int DELAY_WORDS = 5;
	private static final int DELAY_PHRASES = 100;
	
	private Map<String, SoundPackFile> packEnglish = new HashMap<String, SoundPackFile>();
	private Map<String, SoundPackFile> packRussian = new HashMap<String, SoundPackFile>();
	
	private int volume;
	boolean playing = false;
	
	
	/**
	 * 
	 * @param paths
	 * @param packsMap
	 */
	private void setPath(String[] paths, Map<String, SoundPackFile> packsMap) {
		// добавляем все нужные pak-файлы
		for ( String path : paths ) {
			File f = new File(path);
			if ( !f.isDirectory() && f.exists() && !packsMap.containsKey(path) ) {
				SoundPackFile packFile = new SoundPackFile(path);
				packsMap.put(path, packFile);
				if ( !packFile.load() ) {
					System.out.println("can't load sound pack file: " + path);
					packsMap = null;
				}		

			}
		}

		// удяляем все ненужные файлы
		List<String> listToDelete = new ArrayList<String>();
		for ( String path : packsMap.keySet() ) {
			boolean found = false;
			for ( String s : paths ) {
				if ( s.equals(path) ) {
					found = true;
					break;
				}				
			}
			if ( !found ) {
				listToDelete.add(path);
			}
		}

		for ( String path : listToDelete ) {
			packsMap.remove(path);
		}		
	}
	
	/**
	 * 
	 * @param paths
	 */
	public void setPathEngl(String paths[]) {
		pathEngl = paths;
		removeLastSlash(pathEngl);
		setPath(paths, packEnglish);
		
	}
	
	/**
	 * 
	 * @param paths
	 */
	public void setPathRuss(String paths[]) {
		pathRuss = paths;
		removeLastSlash(pathRuss);
		setPath(paths, packRussian);
	}
	
	/**
	 * 
	 * TODO move it to utils
	 * 
	 * @param strings
	 */
	private static void removeLastSlash(String[] strings) {
		for ( int i = 0; i < strings.length; i++ ) {
			while ( strings[i].length() > 0 && (strings[i].charAt(strings[i].length()-1) == '/' || strings[i].charAt(strings[i].length()-1) == '\\') ) {
				strings[i] = strings[i].substring(0, strings[i].length()-2); 
			}
		}
	}
	
	
	/**
	 * 
	 * @param words
	 * @param lang
	 */
	public void play(final String words, final Lang lang) {
		final long startTime = System.currentTimeMillis();

		new Thread() {
			@Override
			public void run() {
				synchronized ( WordsPlayer.this ) {				
					playing = true;
					try {
						playWords(words, lang);
					} catch ( Exception e ) {
						e.printStackTrace();
					}
					playing = false;
					long time = System.currentTimeMillis() - startTime;
					long remainsTime = TimerTask.getConfigInterval() - time;
					if ( remainsTime > 0 ) {
						try {
							sleep(remainsTime);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					}
					Words.getTimerTask().resume();

				}
			}
		}.start();
	}
	
	
	
	
	/**
	 * Разделяет набор фраз на слова
	 * 
	 * 
	 * @param phrases строка вида 'слово11 слово12; слово1-слово2-слово3'
	 * @return двумерный массив слов во фразах
	 */
	private static String[][] extractWords(String phrases) {
		StringTokenizer stp = new StringTokenizer(phrases, ";");
		int totalPhrases =  stp.countTokens();
		String words[][] = new String[totalPhrases][];
		for ( int p = 0 ; p < totalPhrases; p++ ) {
			String phrase = stp.nextToken();
			StringTokenizer stw = new StringTokenizer(phrase, " \t-,./\\");
			int totalWords = stw.countTokens();
			words[p] = new String[totalWords];
			for ( int w = 0; w < totalWords; w++ ) {
				words[p][w] = stw.nextToken().trim().toLowerCase();
			}
		}
		return words;
	}
	
	/**
	 * Возвращает true, если слово существует в каталоге слов или в файле
	 * @param word
	 * @return
	 */
	public boolean isWordExist(String word, Lang lang) {
		String[] paths = lang == Lang.English ? pathEngl : pathRuss;
		Map<String, SoundPackFile> packs = lang == Lang.English ? packEnglish : packRussian; 
		
		for ( String path : paths ) {
			SoundPackFile pack = packs.get(path); 
			if ( pack != null ) {
				if ( pack.isWordExists(word) ) {
					return true;
				}
			} else {
				File f = new File(path + File.separatorChar + word + ".ogg");		
				if ( f.exists() ) {
					return true;
				}
				f = new File(path + File.separatorChar + word + ".wav");		
				if ( f.exists() ) {
					return true;
				}
			}
		}
		return false;
	}
	
	
	/**
	 * Проигрывает отдельное слово
	 * 
	 * @param word
	 * @param lang
	 * @return
	 */
	private boolean playWord(String word, Lang lang) {
		byte[] data = getWordData(word, lang);
		if ( data == null ) {
			return false;
		}
		return playData(data);
	}
	
	/**
	 * 
	 * @param data
	 * @return
	 */
	private static boolean playData(byte[] data) {
		int sign = ((int)data[0] & 0xFF) + (((int)data[1] & 0xFF) << 8);
		final int WAV_SIGNATURE = 0x4952;
		final int OGG_SIGNATURE = 0x674f;
		if ( sign == WAV_SIGNATURE ) {
			WavPlayer.playData(data);
		} else if ( sign == OGG_SIGNATURE ) {
			OggPlayer.playData(data);
		} else {
			System.out.println("unknown pack item signature: "+Integer.toHexString(sign));
		}
		return true;
	}
	
	/**
	 * 
	 * @param word
	 * @param lang
	 * @return
	 */
	public byte[] getWordData(String word, Lang lang) {
		String[] paths = lang == Lang.English ? pathEngl : pathRuss;
		Map<String, SoundPackFile> packs = lang == Lang.English ? packEnglish : packRussian;
		byte[] data;
		for ( String path : paths ) {
			SoundPackFile pack = packs.get(path);
			if ( pack != null ) {
				data = pack.getData(word);
				if ( data != null && data.length > 10 ) {
					return data;
				}
			}
			data = readWordFile(path, word, lang, "ogg");
			if ( data != null ) {
				return data;
			}
			data = readWordFile(path, word, lang, "wav");
			if ( data != null ) {
				return data;
			}			
		}
		return null;
	}
	
	/**
	 * 
	 * @param path
	 * @param word
	 * @param lang
	 * @param ext
	 * @return
	 */
	private static byte[] readWordFile(String path, String word, Lang lang, String ext) {
		String filePath = path + File.separatorChar + word + "." + ext;
		return Utils.readBinaryFile(filePath);
	}
	
	
	
	
	/**
	 * Выполняет задержку между словами
	 */
	private void delayWords() {
		try {
			Thread.sleep(DELAY_WORDS);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	
	/**
	 * Выполняет задержку между фразами
	 */	
	private void delayPhrases() {
		try {
			Thread.sleep(DELAY_PHRASES);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}		
	}
	
	/**
	 * Выполняет задержку между русской и английской фразами
	 */
	/*
	private void delayLangs() {
		try {
			Thread.sleep(DELAY_LANG);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}		
	}*/

	/**
	 * Проигрывает фразу 
	 * 
	 * @param phrases
	 * @param lang
	 * @return
	 */
	private boolean playWords(String phrases, Lang lang) {
		// удаляем из фразы все слова в скобках
		while ( true ) {
			int p1 = phrases.indexOf('(');
			if ( p1 < 0 ) {
				break;
			}
			int p2 = phrases.indexOf(')');
			if ( p2 < 0 || p2 < p1 ) {
				break;
			}
			phrases = phrases.substring(0, p1) + " " + phrases.substring(p2+1);
		}
		// выделяем слова
		String[][] words = extractWords(phrases);
		boolean result = true;
		for ( int p = 0; p < words.length; p++ ) {
			if ( p != 0 ) {
				delayPhrases();
			}
			
			// если это фраза, проверяем, существует ли она
			if ( words[p].length > 1 ) {
				String phrase = "";
				for ( int i = 0; i < words[p].length; i++ ) {
					if ( i > 0 ) {
						phrase += '_';
					}
					phrase += words[p][i];
				}
				if ( isWordExist(phrase, lang) ) {
					if ( !playWord(phrase, lang) ) {
						result = false;
					}
					continue;
				} else {
					Words.getPlugins().onSoundNotFound(phrase.replace('_', ' '), lang);
				}
			}
			
			
			// выясняем, существуют ли все слова фразы
			boolean allWordsExist = true;
			for ( String word : words[p] ) {
				if ( !isWordExist(word, lang) ) {
					allWordsExist = false;
					result = false;
					Words.getPlugins().onSoundNotFound(word, lang);
					//break;
				}
			}
			
			// если существуют, проигрываем ее
			if ( allWordsExist ) {
				for ( int w = 0; w < words[p].length; w++ ) {
					if ( !playWord(words[p][w], lang) ) {
						result = false;
					} else {
						if ( w != words[p].length - 1 ) {
							delayWords();
						}
					}
				}
			}
		}
		
		return result;
	}

	/**
	 * 
	 * @return
	 */
	public static WordsPlayer getInstance() {
		if ( instance == null ) {
			instance = new WordsPlayer();
		}
		return instance;
	}
	
	/**
	 * 
	 * @param volume
	 */
	public void setVolume(int volume) {
		this.volume = volume;
		WavPlayer.setVolume(volume);
		OggPlayer.setVolume(volume);
	}
	
	/**
	 * 
	 * @return
	 */
	public int getVolume() {
		return volume;
	}

	/**
	 * 
	 * @return
	 */
	public boolean isPlaying() {
		synchronized ( this ) {
			return playing;
		}
	}
}
