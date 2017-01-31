package trolsoft.words;

import trolsoft.dict.WordPair;

public interface WordClickListener {

	/**
	 *
	 * @param word - 0 or 1
	 */
	void onClick(int word, WordPair pair);
}
