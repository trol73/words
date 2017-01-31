package trolsoft.sound;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.util.HashMap;
import java.util.Map;


public class SoundPackFile {
	int version;
	int uid;
	
	private class SoundRecord {
		public int offset;
		public int size;
	}
	
	private String fileName;
	private Map<String, SoundRecord> records = new HashMap<String, SoundRecord>();
	
	
	
	public SoundPackFile(String fileName) {
		this.fileName = fileName;
	}
	
	public boolean load() {
		File f = new File(fileName);
		if ( !f.exists() ) {
			return false;
		}
		try {
			readHeader();
			return true;
		} catch (IOException e) {			
			e.printStackTrace();
			return false;
		}
	}
	
	
	public boolean isWordExists(String word) {
		return records.get(word) != null;
	}
	
	public byte[] getData(String word) {
		SoundRecord rec = records.get(word);
		if ( rec == null ) {
			return null;
		}
		byte[] buf = new byte[rec.size];
		try {
			RandomAccessFile f = new RandomAccessFile(fileName, "rw");
			f.seek(rec.offset);
			f.read(buf);
			f.close();
			return buf;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			return null;
		} catch (IOException e) {			
			e.printStackTrace();
			return null;
		}
		
	}
	
	public InputStream getStream(String word) {
		byte buf[] = getData(word);
		if ( buf == null ) {
			return null;
		}
		return new ByteArrayInputStream(buf);		
	}
	
	private int readByte(RandomAccessFile f) throws IOException {
		return f.readByte() & 0xff;
	}
	
	private int readWord(RandomAccessFile f) throws IOException {
		int result = readByte(f);
		result += readByte(f) << 8;
		return result;
	}

	private int readDword(RandomAccessFile f) throws IOException {
		int result = readWord(f);
		result += readWord(f) << 16;
		return result;
	}
	
	private String readString(RandomAccessFile f) throws IOException {
		int size = readWord(f);
		StringBuffer sb = new StringBuffer();
		for ( int i = 0; i < size; i++ ) {
			char c = f.readChar();
			sb.append(c);
		}
		return sb.toString();
	}

	
	
	
	private void readHeader() throws IOException {
		System.out.println("Locading "+fileName + "...");
//		BufferedReader f = new BufferedReader(new FileReader(fileName));
		RandomAccessFile f = new RandomAccessFile(fileName, "rw");

		version = readDword(f);
		uid = readDword(f);
		int count = readDword(f);
		SoundRecord prev = null;
		
		for ( int w = 0; w < count; w++ ) {
			String word = readString(f);
			int offset = readDword(f);
			if ( prev != null ) {
				prev.size = offset - prev.offset;
			}
			SoundRecord rec = new SoundRecord();
			rec.offset = offset;
			records.put(word, rec);
			//System.out.println(word+ "   " + offset);
			prev = rec;
		}
		if ( prev != null ) {
			File file = new File(fileName);
			prev.size = (int)file.length() - prev.offset;
		}		
		f.close();
		
		System.out.println("Found " + count+ " sounds");
	}
	
	
	public String getFileName() {
		return fileName;
	}
	
	 
}
