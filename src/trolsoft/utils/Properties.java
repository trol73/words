package trolsoft.utils;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class Properties {

	private Map<String, List<String>> properties = new HashMap<String, List<String>>();

	public Properties() {
		
	}
	
	/**
	 * Searches for the property with the specified key in this property list.
	 * 
	 * @param key
	 * @return
	 */
	public String getProperty(String key) {
		List<String> p = properties.get(key);
		if ( p == null || p.size() == 0 ) {
			return null;
		}
		return p.get(0);
	}
	
	
	public String[] getArrayProperty(String key) {
		List<String> lst = properties.get(key);
		if ( lst == null ) {
			return null;
		}
		String[] result = new String[lst.size()];
		for ( int i = 0; i < lst.size(); i++ ) {
			result[i] = lst.get(i);
		}
		return result;

	}

	
     
	
	/**
	 * Searches for the property with the specified key in this property list.
	 * 
	 * @param key
	 * @param defaultValue
	 * @return
	 */
	public String getProperty(String key, String defaultValue) {
		String result = getProperty(key);
		return result != null ? result : defaultValue;
	}
	
	
	public String[] getArrayProperty(String key, String[] defaultValue) {
		if ( properties.get(key) == null ) {
			return defaultValue;
		}
		return getArrayProperty(key);
	}
	

	/**
	 * Calls the Hashtable method put
	 * 
	 * @param key
	 * @param value
	 */
	public void setProperty(String key, String value) {
		List<String> array = new ArrayList<String>();
		array.add(value); 
		properties.put(key, array);
	}
	
	
	public void setArrayProperty(String key, String[] value) {
		List<String> array = new ArrayList<String>();
		for ( String s : value ) {
			array.add(s);
		}
		properties.put(key, array);
	}
	
	
	/**
	 * Reads a property list (key and element pairs) from the input stream.
	 * 
	 * @param inStream
	 * @throws IOException 
	 */
	public void load(InputStream inStream) throws IOException {		
		BufferedReader is = new BufferedReader(new InputStreamReader(inStream));
		properties.clear();
		while ( true ) {
			String s = is.readLine();
			if ( s == null ) {
				break;
			}
			s = s.trim();
			
			// skip comment
			if ( s.length() > 0 && s.charAt(0) == '#' ) {
				continue;
			}
			int pos = s.indexOf('=');
			String key = pos >= 0 ? s.substring(0, pos) : s;
			String val = pos >= 0 ? s.substring(pos+1) : "";
			if ( properties.get(key) == null ) {
				setProperty(key, val);
			} else {
				properties.get(key).add(val);
			}
		}
		is.close();
	}
	
	
	/**
	 * Writes this property list (key and element pairs) in this Properties table to the output stream in a format suitable for 
	 * loading into a Properties table using the load method.
	 * 
	 * @param out
	 * @param comments
	 * @throws IOException 
	 */
	public void store(OutputStream out, String comments) throws IOException {
		List<String> keys = new ArrayList<String>();
		for ( String key : properties.keySet() ) {
			if ( !keys.contains(key) ) {
				keys.add(key);
			}
		}

		Collections.sort(keys);
		BufferedWriter os = new BufferedWriter(new OutputStreamWriter(out));
		String prevSection = null;
		for ( String key : keys ) {
			int sectionPos = key.indexOf('.');
			String section = sectionPos > 0 ? key.substring(0, sectionPos) : "";
			if ( !section.equals(prevSection) ) {
				if ( prevSection != null ) {
					os.write("\n");
				}
				prevSection = section;
			}
			List<String> vals = properties.get(key);
			for ( String val : vals ) {
				os.write(key + '=' + val);			
				os.write("\n");
			}
		}
		os.close();
	}
     
     
	
}
