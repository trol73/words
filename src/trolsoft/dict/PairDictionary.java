package trolsoft.dict;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;


public class PairDictionary extends Dictionary {

	protected List<WordPair> words = new ArrayList<WordPair>();

	/**
	 *
	 * @return
	 */
	public Iterator<WordPair> iterator() {
		return words.iterator();
	}

	/**
	 * Проверяет, содержит ли словарь указанную пару слов
	 * @param pair
	 *
	 * @return true, если содержит
	 */
/*
	public boolean contains(Pair pair) {
		return words.contains(pair);
	}
*/
	public boolean contains(WordPair pair) {
		return indexOf(pair) >= 0;
	}



	/**
	 *
	 */
	public void clear() {
		words.clear();
	}


	/**
	 *
	 * @param pair
	 * @return
	 */
	public boolean delete(WordPair pair) {
		return words.remove(pair);
	}


	public void delete(int index) {
		words.remove(index);
	}




	/**
	 * 
	 * @param dict
	 */
	public void addDict(Dictionary dict) {
		for ( int di = 0; di < dict.size(); di++ ) {
			addPair(dict.getKey(di), dict.getValue(di));
		}
	}

	/**
	 * Удалить из словаря все слова, входящие в словарь dict
	 *
	 * @param dict
	 * @return
	 */
	public int deleteDict(PairDictionary dict) {
		int result = 0;
		for ( int di = 0; di < dict.words.size(); di++ ) {
			if ( delete(dict.words.get(di)) ) {
				result++;
			}
		}
		System.out.println("deleteDict: " + result +  " words has been deleted");
		return result;
	}


	/**
	 * Добавить пару слов
	 *
	 * @param word1
	 * @param word2
	 * @return
	 */
	public boolean addPair(String word1, String word2) {
		return addPair(new WordPair(word1, word2));

	}


	/**
	 * Добавить пару слов
	 *
	 * @param pair
	 * @param compareOnlyKeyWord - если true, пары будут сравниваться только по первому слову, иначе - по обоим словам
	 * @return true, если пара уже была добавлена, false - если такая пара уже существовала
	 */
	public boolean addPair(WordPair pair, boolean compareOnlyKeyWord) {
		// если пара с таким ключом уже есть, выходим
		if ( compareOnlyKeyWord ) {
			for ( WordPair p : words ) {
				if ( p.wordInMyLang.equals(pair.wordInMyLang) ) {
					return false;
				}
			}	
		} else {
			for ( WordPair p : words ) {
				if ( p.equals(pair) ) {
					return false;
				}	
			}
		}

		words.add(pair);
		return true;
	}
	
	/**
	 * 
	 * @param pair
	 * @return
	 */
	public boolean addPair(WordPair pair) {
		return addPair(pair, false);
	}



	/**
	 * Возвращает число слов в словаре
	 *
	 * @return
	 */
	@Override
	public int size() {
		return words.size();
	}
	
	/**
	 * Возвращает число слов в словаре с заданным направлением перевода
	 * 
	 * @param direction
	 * @return
	 */
	public int size(WordPair.Direction direction) {
		int result = 0;
		for ( WordPair p : words ) {
			if ( p.direction == direction ) {
				result++;
			}
		}
		return result;
	}


	public int search(WordPair pair) {
		for ( int i = 0; i < size(); i++ ) {
			if ( words.get(i).equals(pair) ) {
				return i;
			}
		}
		return -1;
	}


	public WordPair getPair(int index) {
		return words.get(index);
	}


	public void setPair(int index, WordPair pair) {
		words.set(index, pair);
	}


	/**
	 * Ищет пару слов
	 *
	 * @param pair
	 * @return индекс найденной пары или -1, если не найдена
	 */
	public int indexOf(WordPair pair) {
		return words.indexOf(pair);
	}


	/**
	 * Сортирует словарь по ключевым словам
	 */
	public void sort() {
		Comparator<WordPair> comparator = new Comparator<WordPair>() {
			@Override
			public int compare(WordPair p1, WordPair p2) {
				return p1.wordInMyLang.compareToIgnoreCase(p2.wordInMyLang);
			}
		};
		Collections.sort(words, comparator);
	}


	public WordPair createPair(String word1, String word2) {
		return new WordPair(word1, word2);
	}

	

	@Override
	public void add(String key, String value) {
		words.add(new WordPair(key, value));		
	}

	
	@Override
	public boolean remove(String key, String value) {
		WordPair pair1 = new WordPair(key, value);
//		WordPair pair2 = new WordPair(value, key);
		if ( words.contains(pair1) ) {
			words.remove(pair1);
			return true;
		}
/*		
		if ( words.contains(pair2) ) {
			words.remove(pair2);
			return true;
		}
*/
		return false;
	}

	
	@Override
	public String getKey(int index) {
		return words.get(index).wordInMyLang;
	}

	@Override
	public String getValue(int index) {
		return words.get(index).wordInLearnLang;
	}



}
