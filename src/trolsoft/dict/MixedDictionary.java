package trolsoft.dict;

import trolsoft.utils.Utils;



/**
 * Словарь, выдающий пары вперемешку и в случайном порядке
 *
 * @author Oleg Trifonov
 *
 */
public class MixedDictionary extends PairDictionary {
	
	public enum Mode {
		LearnToMy,
		MyToLearn,
		LearnToMy_and_MyToLearn,
		LearnToMy_or_MyToLearn;
	}

	private Mode mode;
	/**
	 * Here will be store all completed words
	 */
	private PairDictionary completedWords = new PairDictionary();

	private int indexes[];			// массив индексов для случайного извлечения пар
	private int indexesProcessed;	// текущая позиция в этом массиве

	private int wordsInGroup;		// число слов в группе. если <= 0, то разбивки на группы нет и учится весь словарь сразу
	
	/**
	 * For group learn mode - number of uncompleted english words
	 */
	private int englishWordsRemainsForGroupMode;
	
	/**
	 * For group learn mode - number of uncompleted russian words
	 */
	private int russianWordsRemainsForGroupMode;


	public MixedDictionary() {
		mode = Mode.LearnToMy;
	}


	public Mode getMode() {
		return mode;
	}


	public void setMode(Mode mode) {
		englishWordsRemainsForGroupMode = 0;
		russianWordsRemainsForGroupMode = 0;
		this.mode = mode;
	}
	
	public int getWordsInGroup() {
		return wordsInGroup;
	}
	
	public void setWordsInGroup(int wordsInGroup) {
		this.wordsInGroup = wordsInGroup;
	}


	/**
	 * Построить индекс для случайной выборки слов, если в этом есть необходимость
	 */
	private void buildIndexes() {
		if ( indexes != null && indexesProcessed < indexes.length ) {
			return;
		}


		// размер создаваемого индекса
		int indexSize = size();
		if ( mode == Mode.LearnToMy_and_MyToLearn ) {
			indexSize *= 2;
		}
		// далее этот размер будет уменьшен, надо удалить слова, оставшиеся в completedWords

		// build index
		int tempIndex[] = new int[indexSize];
		int tempIndexOffset = 0;

		int mixedDictSize = wordsInGroup <= 0 ? words.size() : wordsInGroup;
		int foundPairs = 0;
		
		// if we are learning not all words and using mixing, need to build mixed index
		int[] mixedIndex = new int[words.size()];
		for ( int i = 0; i < words.size(); i++ ) {
			mixedIndex[i] = i;
		}
		for ( int i = 0; i < mixedIndex.length; i++ ) {
			int rnd = Utils.random(mixedIndex.length);
			int tmp = mixedIndex[i];
			mixedIndex[i] = mixedIndex[rnd];
			mixedIndex[rnd] = tmp;
		}
		
		englishWordsRemainsForGroupMode = 0;
		russianWordsRemainsForGroupMode = 0;
		
		// build index
		for ( int i = 0; i < words.size(); i++ ) {
			int pairIndex = wordsInGroup > 0 ? mixedIndex[i] : i;
			WordPair pair = words.get(pairIndex);
			boolean groupCopleted = wordsInGroup > 0 && foundPairs >= mixedDictSize; 

			switch ( mode ) {
				case LearnToMy:
					if ( !completedWords.contains(pair) ) {
						if ( !groupCopleted ) {
							tempIndex[tempIndexOffset++] = pairIndex;
							foundPairs++;
						} else {
							englishWordsRemainsForGroupMode++;	
						}
					}
					break;
				case MyToLearn:
					if ( !completedWords.contains(pair.inverted()) ) {
						if ( !groupCopleted ) {
							tempIndex[tempIndexOffset++] = size() + pairIndex;
							foundPairs++;
						} else {
							russianWordsRemainsForGroupMode++;
						}
					}
					break;
				case LearnToMy_or_MyToLearn:
					boolean found = false;
					int rnd2 = Utils.random(2); 
					if ( !completedWords.contains(pair) ) {
						if ( !groupCopleted ) {
							if ( rnd2 == 0 ) {
								tempIndex[tempIndexOffset++] = pairIndex;
								found = true;
							}
						} else {
							englishWordsRemainsForGroupMode++;
						}
					} else if ( !completedWords.contains(pair.inverted()) ) {
						if ( !groupCopleted ) {
							if ( rnd2 != 0 ) { 
								tempIndex[tempIndexOffset++] = size() + pairIndex;
								found = true;
							}
						} else {
							russianWordsRemainsForGroupMode++;
						}
					}
					if ( found ) {
						foundPairs++;
					}
					break;
				case LearnToMy_and_MyToLearn:
					found = false;
					if ( !completedWords.contains(pair) ) {
						if ( !groupCopleted ) {
							tempIndex[tempIndexOffset++] = pairIndex;
							found = true;
						} else {
							englishWordsRemainsForGroupMode++;
						}
					} 
					if ( !completedWords.contains(pair.inverted()) ) {
						if ( !groupCopleted ) {
							tempIndex[tempIndexOffset++] = size() + pairIndex;
							found = true;
						} else {
							russianWordsRemainsForGroupMode++;
						}
					}
					if ( found ) {
						foundPairs++;
					}
					break;
			}
		} // for

		// перестраиваем массив, если надо
		if ( tempIndexOffset == indexSize ) {
			indexes = tempIndex;
		} else {
			indexes = new int[tempIndexOffset];
			for ( int i = 0; i < tempIndexOffset; i++ ) {
				indexes[i] = tempIndex[i];
			}
		}
		indexesProcessed = 0;

		// перемешивание
		for ( int i = 0; i < indexes.length; i++ ) {
			int rnd = Utils.random(indexes.length);
			int tmp = indexes[i];
			indexes[i] = indexes[rnd];
			indexes[rnd] = tmp;
		}
	}


	/**
	 * Получить случайную пару слов
	 *
	 * @return
	 */
	public WordPair getRandomPair() {
		int index;
		do {
			buildIndexes();
			if ( indexes.length == 0 ) {
				return null;
			}
			index = indexes[indexesProcessed++];
		} while ( index < 0 );
		boolean inverted = index >= size();
		if ( inverted ) {
			index -= size();
		}
		return inverted ? words.get(index).inverted() : words.get(index);
	}







	public PairDictionary getCompletedWords() {
		return completedWords;
	}


	public boolean markComplete(WordPair pair) {
		if ( completedWords.contains(pair) ) {
			return false;
		}
		int ind = indexOf(pair);
		if ( ind < 0 ) {
			ind = indexOf(pair.inverted());
			if ( ind < 0 ) {
//System.out.println("markComplete:: pair not found: "+pair);
				return false;
			}
			ind += size();
		}

		completedWords.addPair(pair);
		// удаляем этот номер в индексах
		if ( indexes != null ) {
			for ( int i = 0; i < indexes.length; i++ ) {
				if ( indexes[i] == ind ) {
					indexes[i] = -1;
					break;
				}
			}
		}
		return true;
	}

	public int completeDict(PairDictionary dict) {
		int result = 0;
		for ( int di = 0; di < dict.size(); di++ ) {
			if ( markComplete(dict.words.get(di)) ) {
				result++;
			}
		}
		System.out.println("completeDict: " + result +  " words has been learned");
		return result;
	}


	/**
	 * Возвращает количество слов для изучения
	 * @return
	 */
	public int getTotalWords() {
		switch ( mode ) {
			case LearnToMy:				
			case MyToLearn:
			case LearnToMy_or_MyToLearn:				
				return size();
			case LearnToMy_and_MyToLearn:
				return size() * 2;
		}
		return size();
	}
	
	/**
	 * Возвращает количество слов для изучения
	 * 
	 * @return
	 */
	public int getTotalWords(WordPair.Direction direction) {
		return size(direction);
	}

	/**
	 * Возвращает количество слов, которые были выучены
	 * @return
	 */
	public int getLearnedWords() {
		buildIndexes();

		// проходимся по индексу и считаем количество неотрицательных элементов - это будут невыученные слова
		// после вычитания их из полного количества слов, получим количество выученных
		int notLearned = 0;
		for ( int i = 0; i < indexes.length; i++ ) {
			if ( indexes[i] >= 0 ) {
				notLearned++;
			}
		}
		return getTotalWords() - notLearned;
	}
	
	
	/**
	 * Возвращает количество слов с заданным направлением перевода, которые были выучены
	 * 
	 * @param direction
	 * @return
	 */
	public int getLearnedWords(WordPair.Direction direction) {
		buildIndexes();		
		// проходимся по индексу и считаем количество неотрицательных элементов - это будут невыученные слова
		// после вычитания их из полного количества слов, получим количество выученных
		int notLearnedEngl = 0;
		int notLearnedRus = 0;
		for ( int i = 0; i < indexes.length; i++ ) {
			if ( indexes[i] >= 0 ) {
				if ( indexes[i] < size() ) {
					notLearnedEngl++;
				} else {
					notLearnedRus++;
				}
			}
		}
		int notLearned = direction == WordPair.Direction.LearnToMy ? notLearnedEngl + englishWordsRemainsForGroupMode : notLearnedRus + russianWordsRemainsForGroupMode;
		return size() - notLearned;
	}


	@Override
	public boolean addPair(WordPair pair) {
		indexes = null;
		return super.addPair(pair);
	}

	@Override
	public int deleteDict(PairDictionary dict) {
		indexes = null;
		return super.deleteDict(dict);
	}

	@Override
	public boolean delete(WordPair pair) {
		indexes = null;
		return super.delete(pair);
	}

	@Override
	public boolean load(String fileName, boolean append) {
		indexes = null;
		return super.load(fileName, append);
	}


}
