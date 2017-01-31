package trolsoft.utils;

import java.awt.Font;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.URLDecoder;

import trolsoft.utils.Properties;


/**
 * Базовый класс конфигурации. Сохраняет свои публичные параметры, имена которых не начинаются с 
 * символа подчеркивания или заглавных букв в property-файл и загружает их оттуда.
 * 
 * Свойство вида 'groupName' сохраняет как параметр 'group.name'
 * 
 * Если для свойства 'groupName' определен метод вида public String groupNameSaver(),
 * то в файл сохранится значение, возвращенное этой функцией
 * 
 * Если для свойства 'groupName' определен метод вида public void groupNameLoader(String s),
 * то он будет вызван при загрузке и должен инициализировать 
 * 
 * 
 * 
 * @author trol
 *
 */
public abstract class ConfigurationBase {
	
	private static String rootPath;
	
	/**
	 * Возвращает имя конфигурационного файла 
	 * @return
	 */
	public abstract String getFileName();
	
	
	/**
	 * Выполняет инициализацию всех нестроковых значений после создания/загрузки
	 */
	public void afterLoad() {
		
	}
	
	/**
	 * Вызывается перед сохранением конфигурации
	 */
	public void beforeSave() {
		
	}	
		
	
	/**
	 * Загружает конфигурацию из файла
	 * 
	 * @param fileName
	 * @return
	 */
	public boolean load(String fileName) {
		Properties properties = new Properties();
		try {			
		    properties.load(new FileInputStream(fileName));
		} catch (IOException e) {
			return false;
		}
		Class<?> c = this.getClass();
		Field[] fields = c.getDeclaredFields();
		for ( Field f: fields ) {
			if ( !isPropertyField(f.getName()) ) {
				continue;
			}
			String propertyName = getPropertyName(f.getName());
			String propertyValue = properties.getProperty(propertyName);
			if ( propertyValue == null ) {
				continue;
			}
			try {
				// если объявлен специальный метод-загрузчик, используем его
				if ( verifyLoader(f.getName(), propertyValue) ) {
				} else if ( verifyLoaderA(f.getName(), properties.getArrayProperty(propertyName)) ) {
				} else if ( f.getType() == String.class ) {
					f.set(this, propertyValue);
				} else if ( f.getType() == int.class ) {
					f.setInt(this, Integer.parseInt(propertyValue));
				} else if ( f.getType() == long.class ) {
					f.setLong(this, Long.parseLong(propertyValue));
				} else if ( f.getType() == boolean.class ) {
					f.setBoolean(this, Boolean.parseBoolean(propertyValue));
				} else if ( f.getType() == double.class ) {
					f.setDouble(this, Double.parseDouble(propertyValue));					
				} else if ( f.getType() == String[].class ) {
					f.set(this, properties.getArrayProperty(propertyName));
				}
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				e.printStackTrace();
			}
		}
		afterLoad();
		return true;
	}
	
	/**
	 * 
	 * @return
	 */
	public boolean load() {
		return load(getFileName());
	}
	
	
	/**
	 * Сохраняет конфигурацию в файл
	 * 
	 * @param fileName
	 * @return
	 */
	public boolean save(String fileName) {
		beforeSave();
		Properties properties = new Properties();
		Class<?> c = this.getClass();
		Field[] fields = c.getDeclaredFields();
		for ( Field f: fields ) {
			if ( !isPropertyField(f.getName()) ) {
				continue;
			}

			String propertyName = getPropertyName(f.getName());
			try {
				// если существует специальный метод-saver, используем его
				String propertyValue = verifySaver(f.getName());
				String[] propertyValues = verifySaverA(f.getName());
				if ( propertyValue != null )  {
					properties.setProperty(propertyName, propertyValue);
				} else if ( propertyValues != null ) {
					properties.setArrayProperty(propertyName, propertyValues);
				} else if ( f.getType() == String.class ) {
					properties.setProperty(propertyName, (String)f.get(this));
				} else if ( f.getType() == int.class ) {
					properties.setProperty(propertyName, Integer.toString(f.getInt(this)));
				} else if ( f.getType() == long.class ) {
					properties.setProperty(propertyName, Long.toString(f.getLong(this)));
				} else if ( f.getType() == boolean.class ) {
					properties.setProperty(propertyName, Boolean.toString(f.getBoolean(this)));
				} else if ( f.getType() == double.class ) {
					properties.setProperty(propertyName, Double.toString(f.getDouble(this)));					
				} else if ( f.getType() == String[].class ) {
					properties.setArrayProperty(propertyName, (String[])f.get(this));
				}
			} catch (IllegalArgumentException e) {
				e.printStackTrace();
			} catch (IllegalAccessException e) {
				e.printStackTrace();
			}
		}
		try {
		    properties.store(new FileOutputStream(fileName), null);
		} catch (IOException e) {
			return false;
		}
		return true;
	}
	
	
	/**
	 * 
	 * @return
	 */
	public boolean save() {
		return save(getFileName());
	}

	/**
	 * Возвращает имя параметра для имени поля
	 * 
	 * @param fieldName
	 * @return
	 */
	private static String getPropertyName(String fieldName) {
		StringBuffer result = new StringBuffer();
		for ( int i = 0; i < fieldName.length(); i++ ) {
			char ch = fieldName.charAt(i);
			boolean isUpper = Character.getType(ch) == Character.UPPERCASE_LETTER;
			if ( isUpper ) {
				result.append('.');
				result.append(Character.toLowerCase(ch));
			} else {
				result.append(ch);
			}
		}
		return result.toString();
	}
	
	/**
	 * Проверяет, является ли поле сохраняемым
	 * 
	 * @param fieldName
	 * @return
	 */
	private static boolean isPropertyField(String fieldName) {
		char firstChar = fieldName.charAt(0);
		return Character.getType(firstChar) != Character.UPPERCASE_LETTER;// && firstChar != '_';		
	}

	/**
	 * Возвращает корневой каталог проекта
	 * 
	 * @return
	 */
	public static String getRootPath() {
		if ( rootPath == null ) {
			rootPath = new File(ConfigurationBase.class.getProtectionDomain().getCodeSource().getLocation().getPath()).getAbsolutePath();
			int index = rootPath.lastIndexOf(File.separator);
			if ( index >= 0 ) {
				rootPath = rootPath.substring(0, index);
			}
			try {
				rootPath = URLDecoder.decode(rootPath, "utf-8");
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return rootPath;
	}
	
	/**
	 * Если для свойства 'groupName' определен метод вида public String groupNameSaver(),
	 * то в файл сохранится значение, возвращенное этой функцией
	 * 
	 * @param fieldName
	 * @return сохраняемая строка, или null, если метода-saverа не существует
	 */
	private String verifySaver(String fieldName) {
		Class<?> c = this.getClass();
		try {
			Method m = c.getDeclaredMethod(fieldName+"Saver");
			if ( m.getReturnType() != String.class ) {
				return null;
			}
			return (String)m.invoke(this);
		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();			
		}
		return null;
	}
	
	private String[] verifySaverA(String fieldName) {
		Class<?> c = this.getClass();
		try {
			Method m = c.getDeclaredMethod(fieldName + "Saver");
			if ( m.getReturnType() != String[].class ) {
				return null;
			}
			return (String[])m.invoke(this);
		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();			
		}
		return null;
	}


	
	/**
	 * Если для свойства 'group.name' определен метод вида public void groupNameLoader(String s),
	 * то он будет вызван при загрузке и должен инициализировать значение
	 * 
	 * @param fieldName
	 * @param value
	 * @return
	 */
	private boolean verifyLoader(String fieldName, String value) {
		Class<?> c = this.getClass();
		try {
			Method m = c.getDeclaredMethod(fieldName + "Loader", String.class);
			if ( m.getReturnType() != void.class ) {
				return false;
			}
			m.invoke(this, value);
			return true;
		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
//			e.printStackTrace();
		}
		return false;
	}
	
	
	private boolean verifyLoaderA(String fieldName, String[] value) {
		Class<?> c = this.getClass();
		try {
			Method m = c.getDeclaredMethod(fieldName + "Loader", String[].class);
			if ( m.getReturnType() != void.class ) {
				return false;
			}
			m.invoke(this, (Object)value);
			return true;
		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
//			e.printStackTrace();
		}
		return false;
	}
	
	
	
	/**
	 * Если путь начинается с текущей директории, то удаляет ее, заменяя на точку.
	 * Используется при сохранении конфигурации
	 * 
	 * @param path
	 * @return
	 */
	protected static String packLocalPath(String path) {
		if ( path.indexOf(getRootPath()) == 0 ) {
			return "." + path.substring(getRootPath().length());
		}
		return path;
	}
	
	protected static String[] packLocalPath(String[] paths) {
		String[] result = new String[paths.length];
		for ( int i = 0; i < paths.length; i++ ) {
			result[i] = packLocalPath(paths[i]);
		}
		return result;
	}
	
	/**
	 * Если путь начинается с точки, то заменяет ее на путь к корню.
	 * Используется при загрузке конфигурации
	 * 
	 * @param path 
	 * @return
	 */
	protected static String unpackLocalPath(String path) {
		if ( path.isEmpty() || path.charAt(0) != '.' ) {
			return path;
		}	
		return getRootPath() + path.substring(1);
	}
	
	protected static String[] unpackLocalPath(String[] paths) {
		String[] result = new String[paths.length];
		for ( int i = 0; i < paths.length; i++ ) {
			result[i] = unpackLocalPath(paths[i]);
		}
		return result;
	}
	

	/**
	 * 
	 * @param color
	 * @return
	 */
	protected static String color2str(int color) {
		String result = Integer.toHexString(color & 0xffffff);
		while ( result.length() < 6 ) {
			result = "0" + result;
		}
		return result;
	}
	
	
	/**
	 * 
	 * @param s
	 * @return
	 */
	protected static int str2color(String s) {
		return Integer.parseInt(s, 16);
	}
	
	
	/**
	 * 
	 * @param font
	 * @return
	 */
	protected static String font2str(Font font) {
		return "[" + font.getName() + ", " + font.getStyle() + ", " + font.getSize() + "]"; 
	}
	

	/**
	 * 
	 * @param s
	 * @return
	 */
	protected static Font str2font(String s) {
		int p1 = s.indexOf(',');
		int p2 = s.indexOf(',', p1+1);
		String name = s.substring(1, p1).trim();
		String style = s.substring(p1+2, p2).trim();
		String size = s.substring(p2+1, s.length()-1).trim();
		return new Font(name, Integer.parseInt(style), Integer.parseInt(size));
	}

}
