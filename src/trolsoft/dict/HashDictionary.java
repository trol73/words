package trolsoft.dict;

import java.util.HashMap;
import java.util.Map;

public class HashDictionary extends Dictionary {
	
	private Map<String, String> words = new HashMap<String, String>();

	@Override
	public void add(String key, String value) {
		words.put(key, value);
	}
	
	@Override
	public boolean remove(String key, String value) {
		if ( value.equals(words.get(key)) ) {
			words.remove(key);
			return true;
		}
		return false;
	}


	@Override
	public void clear() {
		words.clear();
	}

	@Override
	public String getKey(int index) {
		return (String)words.keySet().toArray()[index];		
	}

	@Override
	public String getValue(int index) {
		return (String)words.values().toArray()[index];
	}

	@Override
	public int size() {
		return words.size();
	}
	
	public String get(String key) {
		return words.get(key);
	}


}
