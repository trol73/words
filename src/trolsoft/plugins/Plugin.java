package trolsoft.plugins;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class Plugin {
	
	private Class<?> cls;
	private Object obj;
	private Method mInit;
	private Method mOnSoundNotFound;
	
	
	/**
	 * 
	 * @param cls
	 */
	public Plugin(Class<?> cls) {
		this.cls = cls;
	}
	
	
	/**
	 * 
	 * @return
	 */
	public boolean initialize() {
		Constructor<?> constructor;
		try {
			constructor = cls.getConstructor();
			obj = constructor.newInstance();
			
			for ( Method method : cls.getMethods() ) {
				if ( checkMethod(method, boolean.class, "init", String.class) ) {
					mInit = method;
				} else if ( checkMethod(method, void.class, "onSoundNotFound", String.class, String.class) ) {
					mOnSoundNotFound = method;
				}
			}			
			return true;
		} catch (SecurityException e) {
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		return false;
	}
	
	
	/**
	 * Проверяет, является ли метод соответствующим декларации
	 * 
	 * @param method проверяемый метод
	 * @param out возвращаемое значение
	 * @param name имя метода
	 * @param args аргументы метода
	 * @return
	 */
	private static boolean checkMethod(Method method, Class<?> out, String name, Class<?>... args) {
		Class<?> margs[] = method.getParameterTypes();
		if ( !(method.getName().equals(name) && method.getReturnType().equals(out) && margs.length == args.length) ) {
			return false;
		}
		for ( int i = 0; i < args.length; i++ ) {
			if ( !margs[i].equals(args[i]) ) {
				return false;
			}
		}
		return true;
	}
	

	
	/**
	 * Метод вызывается единократно при инициализации плагина
	 * 
	 * @return true, если плагин инициализирован и готов к загрузке
	 */
	public boolean init(String rootPath) {
		if ( mInit == null ) {
			return true;
		}
		try {
			return ((Boolean)mInit.invoke(obj, rootPath)).booleanValue();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return false;
	}
	
	
	/**
	 * Вызывается при проигрывании звука когда звуковой файл не найден
	 * 
	 * @param word отсутствующее слово
	 * @param lang код языка 
	 */
	public void onSoundNotFound(String word, String lang) {
		if ( mOnSoundNotFound == null ) {
			return;
		}
		try {
			mOnSoundNotFound.invoke(obj, word, lang);
		} catch ( Exception e ) {
			e.printStackTrace();
		}
	}
	
	
}
