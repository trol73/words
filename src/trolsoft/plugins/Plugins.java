package trolsoft.plugins;

import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.ArrayList;
import java.util.List;

import trolsoft.words.general.Lang;

/**
 * Класс загружает все плагины из директоии проектов.
 * Плагины располагаются в поддиректории 'plugins' в отдельных каталогах
 * Допускаются плагины трех типов:
 * 		1) .class-файл
 * 		2) .zip-архив, содержащий главный класс - с таким же именем, как имя файла архива
 * 		3) .jar-архив, содержащий главный класс - с таким же именем, как имя файла архива
 * 
 * Также выполняет рассылку получаемых событий всем загруженным плагинам
 * 
 * @author trol
 *
 */
public class Plugins {
	
	private Plugin[] plugins = new Plugin[0];
	
	/**
	 * Загружает все плагины, лежащие в каталоге
	 * 
	 * @param pluginsPath имя каталога (без конечного слеша)
	 * @param rootPath 	корневой каталог программы
	 */
	public void loadPlugins(String pluginsPath, String rootPath) {
		List<Plugin> pluginsArray = new ArrayList<Plugin>();
		
		// проходимяся по подкаталогам
		File dir = new File(pluginsPath);
		String[] pluginsDirs = dir.list();
		if ( pluginsDirs == null ) {
			return;
		}
		for ( String fileName : pluginsDirs ) {
			String pluginDir = pluginsPath + File.separatorChar + fileName;
			File f = new File(pluginDir);
			if ( !f.isDirectory() ) {
				continue;
			}
			String pluginFileName = isFileExist(pluginDir, fileName + ".class");
			if ( pluginFileName != null ) {
				System.out.println(">> Plugin[C] " + pluginFileName);
				Class<?> cls = loadClassFromFile(pluginDir, pluginFileName);
				Plugin plugin = new Plugin(cls);
				if ( plugin.initialize() && plugin.init(rootPath) ) {
					pluginsArray.add(plugin);
				}
				continue;
			}
			pluginFileName = isFileExist(pluginDir, fileName + ".jar");
			if ( pluginFileName != null ) {
				System.out.println(">> Plugin[J] " + pluginFileName);
				continue;
			}
			pluginFileName = isFileExist(pluginDir, fileName + ".zip");
			if ( pluginFileName != null ) {
				System.out.println(">> Plugin[Z] " + pluginFileName);
				continue;
			}			
		} // for
		plugins = new Plugin[pluginsArray.size()];
		for ( int i = 0; i < plugins.length; i++ ) {
			plugins[i] = pluginsArray.get(i);
		}
	}
	
	
	
	/**
	 * Проверяет, существует ли в указанном каталоге файл с заданным именем. Первая буква имени файла
	 * может иметь другой регистр. 
	 * 
	 * @param path
	 * @param fileName
	 * @return имя существующего файла, или null, если файла не существует
	 */
	private static final String isFileExist(String path, String fileName) {
		char firstChar = fileName.charAt(0);
		
		String s = Character.toUpperCase(firstChar) + fileName.substring(1);
		if ( new File(path + File.separatorChar +  s).isFile() ) {
			return s;
		}
		s = Character.toLowerCase(firstChar) + fileName.substring(1);
		if ( new File(path + File.separatorChar + s).isFile() ) {
			return s;
		}
		return null;
	}
	
	
	/**
	 * Загружает класс из файла
	 * 
	 * @param path
	 * @param classFileName
	 * @return
	 */
	private static Class<?> loadClassFromFile(String path, String classFileName) {
		String className = classFileName.substring(0, classFileName.length()-6);
		try {
			URL url = new URL("file://" + path + File.separatorChar);
			URL[] urls = new URL[] { url };

			// Create a new class loader with the directory
			ClassLoader cl = new URLClassLoader(urls);
		
			Class<?> cls = cl.loadClass(className);
			return cls;
		} catch (MalformedURLException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	

	
	/**
	 * Вызывается при проигрывании звука когда звуковой файл не найден
	 * 
	 * @param word отсутствующее слово
	 * @param lang код языка 
	 */
	public void onSoundNotFound(String word, String lang) {
		for ( Plugin plugin: plugins ) {
			plugin.onSoundNotFound(word, lang);
		}
	}
	
	public void onSoundNotFound(String word, Lang lang) {
		onSoundNotFound(word, lang.getShortName());
	}

	
/*
	public class JarFileLoader extends URLClassLoader {
		public JarFileLoader(URL[] urls) {
			super(urls);
		}

		public void addFile(String path) throws MalformedURLException {
			String urlPath = "jar:file://" + path + "!/";
			addURL(new URL(urlPath));
		}

		public void main(String args[]) {
			try {
				System.out.println("First attempt...");
				Class.forName("org.gjt.mm.mysql.Driver");
			} catch (Exception ex) {
				System.out.println("Failed.");
			}

			try {
				URL urls[] = {};

				JarFileLoader cl = new JarFileLoader(urls);
				cl.addFile("/opt/mysql-connector-java-5.0.4/mysql-connector-java-5.0.4-bin.jar");
				System.out.println("Second attempt...");
				cl.loadClass("org.gjt.mm.mysql.Driver");
				System.out.println("Success!");
			} catch (Exception ex) {
				System.out.println("Failed.");
				ex.printStackTrace();
			}
		}
	}

	
	
	// Note that it is not necessary to cache classes here, because the ClassLoader caches loaded classes automatically. Also you can override the following methods to search resources in the archive:
	public final class ZipClassLoader extends ClassLoader {
	    private final ZipFile file;

	    public ZipClassLoader(String filename) throws IOException {
	        this.file = new ZipFile(filename);
	    }

	    @Override
	    protected Class<?> findClass(String name) throws ClassNotFoundException {
	        ZipEntry entry = this.file.getEntry(name.replace('.', '/') + ".class");
	        if (entry == null) {
	            throw new ClassNotFoundException(name);
	        }
	        try {
	            byte[] array = new byte[1024];
	            InputStream in = this.file.getInputStream(entry);
	            ByteArrayOutputStream out = new ByteArrayOutputStream(array.length);
	            int length = in.read(array);
	            while (length > 0) {
	                out.write(array, 0, length);
	                length = in.read(array);
	            }
	            return defineClass(name, out.toByteArray(), 0, out.size());
	        }
	        catch (IOException exception) {
	            throw new ClassNotFoundException(name, exception);
	        }
	    }
	    
	    @Override
	    protected URL findResource(String name) {
	        ZipEntry entry = this.file.getEntry(name);
	        if (entry == null) {
	            return null;
	        }
	        try {
	            return new URL("jar:file:" + this.file.getName() + "!/" + entry.getName());
	        }
	        catch (MalformedURLException exception) {
	            return null;
	        }
	    }

	    @Override
	    protected Enumeration<URL> findResources(final String name) {
	        return new Enumeration<URL>() {
	            private URL element = findResource(name);

	            public boolean hasMoreElements() {
	                return this.element != null;
	            }

	            public URL nextElement() {
	                if (this.element != null) {
	                    URL element = this.element;
	                    this.element = null;
	                    return element;
	                }
	                throw new NoSuchElementException();
	            }
	        };
	    }
	    
	}

	
	
	
	void loadClassFromFile() {
		// Create a File object on the root of the directory containing the
		// class file
		File file = new File("c:\\myclasses\\");
		try {
			// Convert File to a URL
			URL url = file.toURL(); // file:/c:/myclasses/
			URL[] urls = new URL[] { url };
			// Create a new class loader with the directory
			ClassLoader cl = new URLClassLoader(urls);
			// Load in the class; MyClass.class should be located in // the
			// directory file:/c:/myclasses/com/mycompany
			Class<?> cls = cl.loadClass("com.mycompany.MyClass");
		} catch (MalformedURLException e) {
		} catch (ClassNotFoundException e) {
		}
	}
	
	// Perhaps someone may need it because it slightly faster. But I recommend to use the URLClassLoader which is able to work with remote archives and supports security:
	// URL[] urls = { new URL("jar:file:" + path + "!/") };
	// return URLClassLoader.newInstance(urls);

*/
}
