package trolsoft.dict;

import java.util.StringTokenizer;

import trolsoft.words.Words;
import trolsoft.words.general.Lang;

/**
 * 
 * @author trol
 *
 */
public class WordPair {
	
	/**
	 * Направление перевода
	 * 
	 * @author trol
	 *
	 */
	public enum Direction {
		LearnToMy,
		MyToLearn;
		
		public static Direction opposite(Direction direction) {
			return direction == LearnToMy ? MyToLearn : LearnToMy;
		}
	}
	
	public enum WordNumber {
		First,
		Second;
	}
	
	public enum LangType {
		Learn,
		My
	}
	
	public String wordInLearnLang, wordInMyLang;
	public Direction direction;
	

	/*
	 *
	 */
	public WordPair(String word1, String word2) {
		this(word1, word2, Direction.LearnToMy);
	}
	
	public WordPair(String word1, String word2, Direction direction) {
		this.wordInLearnLang = word1;
		this.wordInMyLang = word2;
		this.direction = direction;
	}
	
	public WordPair(WordPair pair) {
		this.wordInLearnLang = pair.wordInLearnLang;
		this.wordInMyLang = pair.wordInMyLang;		
		this.direction = pair.direction;
	}


	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if ( obj == null ) {
			return false;
		}
		if ( obj instanceof WordPair ){
			WordPair pair = (WordPair)obj;
			boolean eq1 = (wordInLearnLang == null) ? pair.wordInLearnLang == null : wordInLearnLang.equals(pair.wordInLearnLang);
			if ( !eq1 ) {
				return false;
			}
			boolean eq2 = (wordInMyLang == null) ? pair.wordInMyLang == null : wordInMyLang.equals(pair.wordInMyLang);
			return eq2;
		}
		return super.equals(obj);
	}


	@Override
	public String toString() {
		return wordInLearnLang + " <-> " + wordInMyLang;
	}


	/**
	 * Возвращает пару, обратную текущей, где слова переставлены местами
	 *
	 * @return
	 */
	public WordPair inverted() {
		return new WordPair(wordInMyLang, wordInLearnLang, Direction.opposite(direction));
	}
	
	/**
	 * Для номера слова возвращает его язык
	 * 
	 * @param wordNum 1/2
	 * @return 
	 */
	public Lang getWordLang(WordNumber wordNum) {
		return getLangType(wordNum) == LangType.Learn ? Words.getConfiguration().langLearn : Words.getConfiguration().langMy;
	}
	
	/**
	 * 
	 * @param wordNumber
	 * @return word1/word2
	 */
	public String getWord(WordNumber wordNumber) {
		return wordNumber == WordNumber.First ? wordInLearnLang : wordInMyLang;
	}
	
	/**
	 * 
	 * @param wordNumber
	 * @return
	 */
	public LangType getLangType(WordNumber wordNumber) {
		return (direction == Direction.LearnToMy && wordNumber == WordNumber.First) || (direction == Direction.MyToLearn && wordNumber == WordNumber.Second) ? LangType.Learn : LangType.My; 
	}
	
	/**
	 * 
	 * @param wordNumber
	 * @return
	 */
	public String[] getWords(WordNumber wordNumber) {
		return splitWords(getWord(wordNumber));
	}
	
	/**
	 * Делит список слов на слова
	 * 
	 * @param words строка со списком строк, разделенных ;
	 * @return массив слов
	 */
	static String[] splitWords(String words) {
		StringTokenizer st = new StringTokenizer(words, ";");
		int cnt = st.countTokens();
		String[] result = new String[cnt];
		int i = 0;
		while ( st.hasMoreTokens() ) {
			result[i++] = st.nextToken().trim(); 
		}
		return result;
	}

	/**
	 * 
	 * @param wordNum
	 * @param string
	 */
	public void setWord(WordNumber wordNum, String word) {
 		if ( wordNum == WordNumber.First ) {
 			wordInLearnLang = word;
 		} else {
 			wordInMyLang = word;
 		}
	}
	
}

