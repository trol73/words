package trolsoft.words.tools;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.util.List;
import java.util.jar.JarEntry;
import java.util.jar.JarOutputStream;
import java.util.jar.Manifest;

import trolsoft.dict.Dictionary;
import trolsoft.utils.FileJournalMaker;
import trolsoft.utils.Utils;

public class MobileGenerator {
	private static final String FILE_WORDS_DATA = "words.bin";
	private static final String PATH_LIST_FILES = "/res/j2me/words.lst";
	private static final String PATH_JAR_FILES = "/res/j2me/jar/";
	private static final String PATH_JAD_FILE = "/res/j2me/words.jad";	

	private Dictionary dict;
	
//	private String pathRoot;	// корневой каталог, в котором будет строится мидлет, со слешем в конце
	private String pathTemp;	// временный каталог для архивации jar-ки
	private String midletName;
	private int fontSize;		// 0, 1, 2
	private String jarFileName;
	private String jadFileName;
	
	private FileJournalMaker fMaker = new FileJournalMaker();

	
	/**
	 * 
	 */
	public MobileGenerator(String pathRoot, String midletName, int fontSize) {
		this.midletName = midletName;
		pathRoot = pathRoot.trim();
		char pathRootLast = pathRoot.charAt(pathRoot.length()-1); 
		if ( pathRootLast != '\\' && pathRootLast != '/' ) {
			pathRoot += File.separatorChar;
		}
//		this.pathRoot = pathRoot;
		pathTemp = pathRoot + "_temp_";
		fMaker.setBasePath(pathTemp);
		this.fontSize = fontSize;
		
		jarFileName = pathRoot + midletName + ".jar";
		jadFileName = pathRoot + midletName + ".jad";
	}
	

	/**
	 * 
	 * @return
	 */
	public boolean generate() {
		try {
			// extract midlet files from jar
			List<String> jarFilesList = Utils.createTextFileFromJar(PATH_LIST_FILES);

			String[] filesToJar = new String[jarFilesList.size()+1];
			int i = 0;
			for ( String fn : jarFilesList ) {
				fn = fn.trim();
				if ( fn.length() == 0 ) {
					continue;
				}
				if ( fn.indexOf("[%FONT_SIZE%]") >= 0 ) {
					String fss;
					switch ( fontSize ) {
						case 0:
							fss = "128";
							break;
						case 1:
							fss = "176";
							break;
						case 2:
							fss = "240";
							break;
						default:
							fss = "";
					}
					fn = fn.replace("[%FONT_SIZE%]", fss);
				}
				InputStream is = Utils.getResourceFromJar(PATH_JAR_FILES + fn);
				filesToJar[i++] = fn;
				fMaker.mkfile(fn, is);
			}
			
			// create data file
			String dataFileName = pathTemp + File.separatorChar + FILE_WORDS_DATA;
			createDataFile(dataFileName);
			fMaker.getCreatedFilesList().add(dataFileName);
			filesToJar[i++] = FILE_WORDS_DATA;
	
			// pack midlet files into jar
			String manifestFileName = pathTemp + File.separatorChar + filesToJar[0];
			patchManifestFile(manifestFileName, 0);
			InputStream manifesIS = new FileInputStream(manifestFileName);
			Manifest manifest = new Manifest(manifesIS);
			manifesIS.close();
			
			JarOutputStream jarOut = new JarOutputStream(new FileOutputStream(jarFileName), manifest);
			for ( i = 1; i < filesToJar.length; i++ ) {
				String fn = filesToJar[i];
				if ( fn == null ) {
					continue;
				}
				JarEntry jarEntry = new JarEntry(fn);
				jarOut.putNextEntry(jarEntry);
				Utils.writeFileToStream(pathTemp + File.separatorChar + fn, jarOut);
			}
			jarOut.close();
			
			// clear and delete temporary directory
			fMaker.undo();
			
			// create jad-file
			List<String> jadFileLines = Utils.createTextFileFromJar(PATH_JAD_FILE);
			patchManifestFile(jadFileName, jadFileLines, new File(jarFileName).length());
		} catch ( Exception e ) {
			e.printStackTrace();
			return false;
		}
		return true;
	}
	
	
	
	
	/**
	 * 
	 * @param fileName
	 * @throws IOException
	 */
	private void createDataFile(String fileName) throws IOException {
		// calculating offsets of words
		int size = dict.size();
		
		int pos = 2 + size*3 + 2;
		int posEng[] = new int[size];
		int posRus[] = new int[size];
		for ( int i = 0; i < size; i++ ) {
			String eng = dict.getKey(i);
			String rus = dict.getValue(i);
			posEng[i] = pos;
			pos += eng.getBytes("utf-8").length;
			posRus[i] = pos;
			pos += rus.getBytes("utf-8").length;
		}
		if ( pos >= 0xffff ) {
			throw new RuntimeException("Words file is to big!");
		}

		RandomAccessFile f = new RandomAccessFile(fileName, "rw");		
		// header
		//f.writeShort(size);
		f.writeByte(size & 0xff);
		f.writeByte((size >> 8) & 0xff);
		for ( int i = 0; i < size; i++ ) {
			int posEn = posEng[i];
			f.writeByte(posEn & 0xff);
			f.writeByte((posEn >> 8) & 0xff);
			if ( posRus[i] - posEng[i] >= 0xff ) {
				throw new RuntimeException("To large word: " + dict.getKey(i) + "!");
			}
			f.writeByte((posRus[i] - posEng[i]) & 0xff);
		}
		f.writeByte(pos & 0xff);
		f.writeByte((pos >> 8) & 0xff);

		// words
		for ( int i = 0; i < size; i++ ) {
			String eng = dict.getKey(i);
			String rus = dict.getValue(i);
			f.write(eng.getBytes("utf-8"));
			f.write(rus.getBytes("utf-8"));
			//f.writeUTF(eng);
			//f.writeUTF(rus);
		}
		f.close();
	}

	/**
	 * 
	 * @param fileName
	 * @throws IOException 
	 */
	private void patchManifestFile(String fileName, long jarSize) throws IOException {
		List<String> lines = Utils.readTextFile(fileName);
		patchManifestFile(fileName, lines, jarSize);
	}
	
	/**
	 * 
	 * @param fileName
	 * @param lines
	 * @param jarSize
	 * @throws IOException
	 */
	private void patchManifestFile(String fileName, List<String> lines, long jarSize) throws IOException {
		String jarSizeStr = Long.toString(jarSize);
		for ( int i = 0; i < lines.size(); i++ ) {
			String s = lines.get(i);
			s = s.replace("%NAME%", midletName);
			s = s.replace("%SIZE%", jarSizeStr);
			lines.set(i, s);
		}
		Utils.writeTextToFile(fileName, lines);		
	}


	/**
	 * 
	 * @param dict
	 */
	public void setDict(Dictionary dict) {
		System.out.println("setDict " + dict.size());
		this.dict = dict;
	}

}
