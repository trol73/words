package trolsoft.dict;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.List;

/**
 * Абстрактный базовый класс словаря.
 * Умеет загружать словарь из файла и сохранять его в файл. Поддерживает список свойств
 * 
 * @author trol
 *
 */
public abstract class Dictionary {
	private String loadedFileName;	// имя файла, откуда/куда был последний раз прочитан/сохранен словарь
	private List<String> propertiesList = new ArrayList<String>();

	/**
	 * Загрузка словаря из файла
	 *
	 * @param fileName
	 * @param append - если true, то загруженные слова будут добавлены в словарь
	 * @return
	 */
	public boolean load(String fileName, boolean append) {
		loadedFileName = fileName;
		if ( !append ) {
			clear();
			propertiesList.clear();
		}
		try {
			BufferedReader f = new BufferedReader(new InputStreamReader(new FileInputStream(fileName), "UTF-8"));
			String s;
			int line = 0;
			int wordsCount = size();
			while ( (s = f.readLine()) != null ) {
				line++;
				s = s.trim();
				s = new String(s.getBytes());
			
				if ( s.isEmpty() ) {
					continue;
				}
				
				// property string
				if ( s.startsWith("::") ) {
					propertiesList.add(s.substring(2).trim());
					continue;
				}
				// comment string
				if ( s.charAt(0) == '#' ) {
					continue;
				}
				
				// word pairs
				int pos = s.indexOf('=');
				if ( pos < 0 ) {
					pos = s.indexOf("  ");
				}
				if ( pos < 0 ) {
					pos = s.indexOf("\t");
				}
				if ( pos < 0 ) {
					f.close();
					System.out.println("Error in dictionary file " + fileName + "[" + line + "]: separator not found");
					return false;
				}
				String s1 = s.substring(0, pos).trim();
				String s2 = s.substring(pos+1).trim();
				add(s1, s2);
			} // while
			f.close();
			wordsCount = size() - wordsCount;
			System.out.println(fileName + ": " + wordsCount + " words found");
		} catch (FileNotFoundException e) {
			//e.printStackTrace();
			return false;
		} catch (IOException e) {
			e.printStackTrace();
			return false;

		}
		return true;
	}


	/**
	 *
	 * @param fileName
	 * @return
	 */
	public boolean load(String fileName) {
		return load(fileName, false);
	}
	
	
	/**
	 * Загружает словарь из нескольких файлов
	 * 
	 * @param fileNames
	 * @return true, если был загружен хотя бы один файл
	 */
	public boolean load(String[] fileNames) {
		clear();
		boolean result = false;
		for ( int i = 0; i < fileNames.length; i++ ) {
			if ( load(fileNames[i], true) ) {
				result = true;
			}
		}
		return result;
	}



	/**
	 * Сохранение словаря в файл
	 *
	 * @param fileName
	 * @return
	 */
	public boolean save(String fileName) {
		loadedFileName = fileName;
		try {
			
			//BufferedWriter f = new BufferedWriter(new FileWriter(fileName));
			BufferedWriter f = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(fileName), "UTF-8"));
			for ( int i = 0; i < size(); i++ ) {
				String s = getKey(i) + "\t\t\t\t" + getValue(i) + '\n';
				f.write(s);
/*				
				byte[] bytes = s.getBytes("Cp1251");				
				for ( int j = 0; j < bytes.length; j++ ) {
					f.write((int)0xFF & bytes[j]);					
				}
*/				
			}
			f.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return true;
	}


	/**
	 * Сохранение словаря в тот файл, откуда/куда он был последний раз загружен/сохранен
	 *
	 * @return
	 */
	public boolean save() {
		return save(loadedFileName);
	}
	
	
	/**
	 * Удаляет из словаря все слова, содержищиеся в другом словаре
	 * 
	 * @param dict
	 * @return	количество удаленных слов
	 */
	public int delete(Dictionary dict) {
		int cnt = 0;
		for ( int i = 0; i < dict.size(); i++ ) {
			String key = dict.getKey(i);
			String val = dict.getValue(i);
			if ( remove(key, val) ) {
				cnt++;
			}
		}
		return cnt;
	}
	
	
	/**
	 * Очищает словарь удаляя все слова
	 */
	abstract public void clear();
	
	
	/**
	 * Добавляет пару слов в словарь
	 * 
	 * @param key
	 * @param value
	 */
	abstract public void add(String key, String value);
	

	/**
	 * Удаляет пару слов из словаря
	 * 
	 * @param key
	 * @param value
	 * @return
	 */
	abstract public boolean remove(String key, String value);
	
	
	/**
	 * Возвращает число элементов в словаре
	 * 
	 * @return
	 */
	abstract public int size();
	
	/**
	 * Возвращает слово-ключ по индексу
	 * 
	 * @param index
	 * @return
	 */
	abstract public String getKey(int index);
	
	/**
	 * Возвращает слово-значение по индексу
	 * 
	 * @param index
	 * @return
	 */
	abstract public String getValue(int index);
	

}
