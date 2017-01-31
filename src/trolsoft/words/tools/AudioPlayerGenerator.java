package trolsoft.words.tools;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.util.StringTokenizer;

import trolsoft.dict.Dictionary;
import trolsoft.dict.MixedDictionary;
import trolsoft.dict.WordPair;
import trolsoft.sound.WordsPlayer;
import trolsoft.wav.WavFile;
import trolsoft.wav.WavFileException;
import trolsoft.wav.WaveTools;
import trolsoft.words.Configuration;
import trolsoft.words.Words;
import trolsoft.words.general.Lang;
import de.jarnbjo.ogg.BufferInputStream;
import de.jarnbjo.ogg.EndOfOggStreamException;
import de.jarnbjo.ogg.LogicalOggStream;
import de.jarnbjo.ogg.OggFormatException;
import de.jarnbjo.ogg.PhysicalOggStream;
import de.jarnbjo.vorbis.VorbisStream;

public class AudioPlayerGenerator {
	private static final int BUFFER_SIZE = 1024*16;
	
	
	private Dictionary dict;
	
	private WavFile wav;
	
	/**
	 * Номер текущего генеримого wav-файла (если включена разбивка по файлам)
	 */
	private int wavFileNumber;
	
	/**
	 * 
	 */
	private String wavFileName;
	
	/**
	 * 
	 */
	private int pairsInCurrentFile;
	
	
	
	public void setDict(Dictionary dict) {
		this.dict = dict;
	}
	
	
	/**
	 * 
	 * @param words
	 * @param lang
	 * @throws IOException
	 * @throws WavFileException
	 */
	private void addWords(String[][] words, Lang lang) throws IOException, WavFileException {
		for ( int pi = 0; pi < words.length; pi++ ) {
			for ( int wi = 0; wi < words[pi].length; wi ++ ) {
				String word = words[pi][wi];
				if ( word == null ) {
					//System.out.println("!!!");
					continue;
				}
				//System.out.println(word);
				byte[] data = getWordWaveData(word, lang);
				//System.out.println(word + "  " + data.length);
				WaveTools.appendWav(wav, new ByteArrayInputStream(data));
			}
		}
	}


	/**
	 * @throws WavFileException 
	 * @throws IOException 
	 * 
	 */
	private void addPauseWords() throws IOException, WavFileException {
		WaveTools.appendPause(wav, Words.getConfiguration().generatorAudioIntervalWords);
	}
	
	/**
	 * @return 
	 * @throws WavFileException 
	 * @throws IOException 
	 * 
	 */
	private void addPausePairs() throws IOException, WavFileException {
		WaveTools.appendPause(wav, Words.getConfiguration().generatorAudioIntervalPairs);
	}
	
	
	/**
	 * 
	 * @throws IOException
	 * @throws WavFileException
	 */
	private void createWav() throws IOException, WavFileException {
		String filePath = Words.getConfiguration().generatorAudioOutpath;
		new File(filePath).mkdirs();
		filePath +=  File.separatorChar;
		String fileName = "words";
		int maxWordsPerFile = Words.getConfiguration().generatorAudioWordsinfile;
		if ( maxWordsPerFile > 0 ) {
			fileName += wavFileNumber;
		}
		wavFileNumber++;
		pairsInCurrentFile = 0;
		wavFileName = filePath + fileName + ".wav";
		int sampleRate = Words.getConfiguration().generatorAudioWavSamplerate;
		wav = WaveTools.createWav(wavFileName, 1, 8, sampleRate);
	}
	
	
	
	/**
	 * 
	 * @return
	 * @throws WavFileException 
	 * @throws IOException 
	 */
	private boolean process() throws IOException, WavFileException {
		Configuration cfg = Words.getConfiguration();
		
		wavFileNumber = 1;
		
		createWav();
//		System.out.println(">>> " + dict.size());
		
		
		MixedDictionary mdict = new MixedDictionary();
		mdict.addDict(dict);
		mdict.setMode(cfg.generatorAudioDirection);
		
		int totalPairs = cfg.generatorAudioRepeatAll * mdict.size() * cfg.generatorAudioRepeatWords;
		if ( mdict.getMode() == MixedDictionary.Mode.LearnToMy_and_MyToLearn ) {
			totalPairs *= 2;
		}
		int currentPair = 0;
		
		for ( int dictRepeatIndex = 0; dictRepeatIndex < cfg.generatorAudioRepeatAll; dictRepeatIndex++ ) {
			for ( int wordPairIndex = 0; wordPairIndex < mdict.size(); wordPairIndex++ ) {
				WordPair p = mdict.getRandomPair();
				//WordPair p = mdict.getPair(i);
	
				Lang lang1 = p.getWordLang(WordPair.WordNumber.First);
				String sph1[][] = getWordsFiles(p.wordInMyLang, lang1);
				Lang lang2 = p.getWordLang(WordPair.WordNumber.Second);
				String sph2[][] = getWordsFiles(p.wordInLearnLang, lang2);
				
				if ( pairsInCurrentFile > cfg.generatorAudioWordsinfile && cfg.generatorAudioWordsinfile > 0 )  {
					wav.close();
					WavFile.rewriteFileHeader(wavFileName, wav);
					createWav();
				}
	
				for ( int pairRepeatIndex = 0; pairRepeatIndex < cfg.generatorAudioRepeatWords; pairRepeatIndex++ ) { 
					addWords(sph1, lang1);
					
					addPauseWords();
		
					addWords(sph2, lang2);
					
					addPausePairs();
					
					 
					onUpdate(100*currentPair/totalPairs);
					currentPair++;
				}
				
				pairsInCurrentFile++;
			} // пары в словаре
		} // повтор словарей
		wav.close();
		WavFile.rewriteFileHeader(wavFileName, wav);

		return true;
	}
	
	
	/**
	 * 
	 */
	public boolean generate() {
		try {
			return process();
		} catch ( Exception e) {
			e.printStackTrace();
			return false;
		}
	}
	
	/**
	 * Разделяет набор фраз на слова
	 * 
	 * TODO it's copypaste from words player !
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
			StringTokenizer stw = new StringTokenizer(phrase, " \t-,.");
			int totalWords = stw.countTokens();
			words[p] = new String[totalWords];
			for ( int w = 0; w < totalWords; w++ ) {
				words[p][w] = stw.nextToken().trim().toLowerCase();
			}
		}
		return words;
	}

	
	/**
	 * Возвращает массив всех имен файлов проигрываемых слов для всех найденных пар
	 * 
	 * TODO it's modified copypaste from WordsPlayer
	 * 
	 * @param phrases
	 * @param lang
	 * @return
	 */
	private static String[][] getWordsFiles(String phrases, Lang lang) {
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
		
		String result[][] = new String[words.length][];
		
		for ( int p = 0; p < words.length; p++ ) {
			// если это фраза, проверяем, существует ли она
			if ( words[p].length > 1 ) {
				String phrase = "";
				for ( int i = 0; i < words[p].length; i++ ) {
					if ( i > 0 ) {
						phrase += '_';
					}
					phrase += words[p][i];
				}
				
				if ( Words.player.isWordExist(phrase, lang) ) {
					result[p] = new String[1];
					result[p][0] = phrase;
					continue;	// переходим к следующей фразе
				} else {
					Words.getPlugins().onSoundNotFound(phrase.replace('_', ' '), lang);
				}
			}
			
			result[p] = new String[words[p].length];
			for ( int w = 0; w < words[p].length; w++ ) {
				String word = words[p][w];
				if ( Words.player.isWordExist(word, lang) ) {
					result[p][w] = word;
				} else {
					result[p][w] = null;
					Words.getPlugins().onSoundNotFound(word, lang);
				}
			}
		}
		
		return result;
	}
	
	
	/**
	 * 
	 * TODO пуределать это возвращая wav-file и используя его средства формирования заголовка
	 * 
	 * @param ogg
	 * @return
	 */
	public static byte[] ogg2wav(byte[] ogg) {
		try {
			PhysicalOggStream os = new BufferInputStream(ogg);

			// get the first logical Ogg stream from the file
			LogicalOggStream los = (LogicalOggStream) os.getLogicalStreams().iterator().next();

			// exit, if it is not a Vorbis stream
			if ( los.getFormat() != LogicalOggStream.FORMAT_VORBIS ) {
				System.out.println("no ogg vorbis content");
				return null;
			}
			
			// create a Vorbis stream from the logical Ogg stream
			final VorbisStream vs = new VorbisStream(los);
			
			// allocate a buffer for data
			final byte[] buffer = new byte[BUFFER_SIZE];
			ByteArrayOutputStream out = new ByteArrayOutputStream();


			// number of data bytes written to the wav stream
			int len = 0;

			// get basic stream data from the vorbis channel
			int channels = vs.getIdentificationHeader().getChannels();
			int sampleRate = vs.getIdentificationHeader().getSampleRate();

			// write "RIFF" header chunk
			out.write("RIFF".getBytes("ASCII"));
			out.write(toBytes(0)); // will be filled in later
			out.write("WAVE".getBytes("ASCII"));

			// write "fmt " header chunk
			out.write("fmt ".getBytes("ASCII"));
			out.write(toBytes(16));
			out.write(toBytes((short) 1)); // PCM format
			out.write(toBytes((short) channels));
			out.write(toBytes(sampleRate));
			out.write(toBytes(sampleRate * channels * 2));
			out.write(toBytes((short) (2 * channels)));
			out.write(toBytes((short) 16));

			// write "data" header
			out.write("data".getBytes("ASCII"));
			out.write(toBytes(0)); // will be filled in later

			try {
				// read pcm data from the vorbis channel and
				// write the data to the wav file
				while ( true ) {
					int read = vs.readPcm(buffer, 0, buffer.length);
					for (int i = 0; i < read; i += 2) {
						// swap from big endian to little endian
						byte tB = buffer[i];
						buffer[i] = buffer[i + 1];
						buffer[i + 1] = tB;
					}
					out.write(buffer, 0, read);
					len += read;
				}
			} catch (EndOfOggStreamException e) {
				// not really an error, but we've
				// reached the end of the vorbis stream
				// and so exit the loop
			}

			// close the ogg and vorbis streams
			os.close();
			
			byte[] result = out.toByteArray(); 

			// fill the wav header with missing data: write file length at file position 4
			setDword(result, 4, len + 36);

			// write data chunk length at file position 40
			setDword(result, 40, len);

			return result;
		} catch (OggFormatException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	
	private static byte[] toBytes(int val) {
		byte[] res = new byte[4];
		res[3] = (byte) (0xff & (val >> 24));
		res[2] = (byte) (0xff & (val >> 16));
		res[1] = (byte) (0xff & (val >> 8));
		res[0] = (byte) (0xff & (val));
		return res;
	}

	private static byte[] toBytes(short val) {
		byte[] res = new byte[2];
		res[1] = (byte) (0xff & (val >> 8));
		res[0] = (byte) (0xff & (val));
		return res;
	}
	
	private static void setDword(byte[] buf, int offset, int val) {
		buf[offset++] = (byte) (0xff & (val));
		buf[offset++] = (byte) (0xff & (val >> 8));		
		buf[offset++] = (byte) (0xff & (val >> 16));
		buf[offset] = (byte) (0xff & (val >> 24));
	}
	
	/**
	 * 
	 * @param word
	 * @param lang
	 * @return
	 */
	private static byte[] getWordWaveData(String word, Lang lang) {
		byte[] data = WordsPlayer.getInstance().getWordData(word, lang);
		int sign = ((int)data[0] & 0xFF) + (((int)data[1] & 0xFF) << 8);
		final int WAV_SIGNATURE = 0x4952;
		final int OGG_SIGNATURE = 0x674f;
		if ( sign == WAV_SIGNATURE ) {
			return data;
		} else if ( sign == OGG_SIGNATURE ) {
			return ogg2wav(data);
		} else {
			System.out.println("unknown pack item signature: "+Integer.toHexString(sign));
			return null;			
		}
	}

	
	/**
	 * 
	 * @param progress
	 */
	public void onUpdate(int progress) {
		
	}
}
