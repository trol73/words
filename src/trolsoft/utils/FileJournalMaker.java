package trolsoft.utils;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.List;

public class FileJournalMaker {
	private List<String> filesList = new ArrayList<String>();	// пути всех созданных файлов и каталогов сохраняются сюда для последующего удаления
	
	private String basePath;
	
	
	public FileJournalMaker() {
		
	}
	
	
	/**
	 * Задает базовый путь. Если он не null, то будет служить корнем для создаваемых объектов
	 * @param basePath
	 */
	public void setBasePath(String basePath) {
		if ( basePath != null ) {
			basePath = basePath.trim();
			if ( basePath.length() == 0 ) {
				basePath = File.separator;
			} else {
				char lastChar = basePath.charAt(basePath.length()-1); 
				if ( lastChar != '\\' && lastChar != '/' ) {
					basePath += File.separatorChar;
				}
			}
		}
		this.basePath = basePath;
	}
	
	
	/**
	 * Создает каталог
	 * 
	 * @param path
	 * @return true, если каталог был создан
	 */
	public boolean mkdir(String path) {
		return _mkdir(addBasePath(path));
	}
	
	
	/**
	 * 
	 * @param path
	 * @return
	 */
	public boolean _mkdir(String path) {
		File f = new File(path);
		if ( f.exists() ) {
			return false;
		}
		if ( f.mkdir() ) {
			filesList.add(path);
			return true;
		}
		return false;
	}
	
	
	/**
	 * Создает каталог в все промежуточные каталоги, если надо
	 * 
	 * @param path
	 * @return true, если каталог был создан
	 */
	public boolean mkdirs(String path) {
		return _mkdirs(addBasePath(path));
	}
	
	
	/**
	 * 
	 * @param path
	 * @return
	 */
	public boolean _mkdirs(String path) {
		File f = new File(path);
		
		if ( f.exists() ) {
			return false;
		}
		if ( f.mkdir() ) {
			filesList.add(path);
			return true;
		}
		File canonFile = null;
		try {
			canonFile = f.getCanonicalFile();
		} catch (IOException e) {
			e.printStackTrace();
			return false;
		}

		File parent = canonFile.getParentFile();
		String parentName = canonFile.getParent();
		return (parentName != null && (_mkdirs(parentName) || parent.exists()) && _mkdir(path));
	}
	
	
	/**
	 * 
	 * @param fileName
	 * @param is
	 * @return
	 */
	public RandomAccessFile mkfile(String fileName) {
		return _mkfile(addBasePath(fileName));
	}
	
	/**
	 * 
	 * @param fileName
	 * @return
	 * @throws FileNotFoundException 
	 */
	public OutputStream mkfileStream(String fileName) throws FileNotFoundException {
		fileName = addBasePath(fileName);
		createDirsForFile(fileName);
		FileOutputStream os = new FileOutputStream(fileName);
		filesList.add(fileName);
		return os;
	}
	
	
	/**
	 * 
	 * @param fileName
	 * @param is
	 * @throws IOException 
	 */
	public void mkfile(String fileName, InputStream is) throws IOException {
		RandomAccessFile of = _mkfile(addBasePath(fileName));
		byte[] bytes = new byte[10240];
		
		int bytesRead = -1;
		do {
			bytesRead = is.read(bytes);
			if ( bytesRead > 0 ) {
				of.write(bytes, 0, bytesRead);	
			}
		} while ( bytesRead > 0 );
		
		is.close();
		of.close();
	}
	
	
	/**
	 * 
	 * @param fileName
	 */
	private void createDirsForFile(String fileName) {
		try {
			File f = new File(fileName);
			File canonFile = f.getCanonicalFile();
			File parent = canonFile.getParentFile();
			if ( !parent.exists() ) {
				_mkdirs(parent.getAbsolutePath());
			}
		} catch (IOException e) {
		}
	}
	
	
	/**
	 * 
	 * @param fileName
	 * @return
	 */
	private RandomAccessFile _mkfile(String fileName) {
		createDirsForFile(fileName);
		try {
			RandomAccessFile f = new RandomAccessFile(fileName, "rw");
			filesList.add(fileName);
			return f;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			return null;
		}
	}
	
	/**
	 * 
	 */
	public void undo() {
		for ( int i = filesList.size()-1; i >= 0; i-- ) {
			String path = filesList.get(i);
			File f = new File(path);
			if ( f.exists() ) {
				if ( f.delete() ) {
					filesList.remove(i);
				}
			}
		}
	}
	
	
	/**
	 * 
	 * @return
	 */
	public List<String> getCreatedFilesList() {
		return filesList;
	}
	
	
	/**
	 * 
	 * @param path
	 * @return
	 */
	private String addBasePath(String path) {
		if ( basePath == null ) {
			return path;
		}
		if ( path.length() == 0 ) {
			return basePath;
		}
		char firstChar = path.charAt(0);
		if ( firstChar != '\\' && firstChar != '/' ) {
			return basePath + path;
		}
		return basePath + path.substring(1); 
	}
	
/*
	public static void main(String args[]) {
		FileJournalMaker fjm = new FileJournalMaker();
		fjm.setBasePath("/home/trol/-base");
		fjm.mkdirs("1/2/3/4");
		fjm.mkdirs("1a/2/3");
		fjm.undo();
	}
*/

}
