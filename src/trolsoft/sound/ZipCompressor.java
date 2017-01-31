package trolsoft.sound;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.zip.DataFormatException;
import java.util.zip.Deflater;
import java.util.zip.Inflater;

public class ZipCompressor {
	
	private static void about() {
		System.out.println("Usage: java ZipCompressor pack|unpack <infile> <outfile>");
		System.exit(0);
	}
	
	public static void main(String[] args) {
		if ( args.length != 3 ) {
			about();
		}
		String inFile = args[1];
		String outFile = args[2];
		if ( args[0].equalsIgnoreCase("pack") ) {
			pack(inFile, outFile);
			File fin = new File(inFile);
			File fout = new File(outFile);
			long sizeIn = fin.length();
			long sizeOut = fout.length();
			if ( sizeOut == 0 )
				sizeOut++;				
			System.out.println("compressed ["+inFile + "] rate = " + 100*sizeIn/sizeOut + "%");
		} else if ( args[0].equalsIgnoreCase("unpack") ) {
			unpack(inFile, outFile);
			File fin = new File(inFile);
			File fout = new File(outFile);
			long sizeIn = fin.length();
			long sizeOut = fout.length();
			if ( sizeIn == 0 )
				sizeIn++;				
			System.out.println("uncompressed ["+outFile + "] rate = " + 100*sizeOut/sizeIn + "%");
			
		} else {
			about();
		}
	}
	
	
	public static byte[] pack(byte[] data) {
		Deflater compressor = new Deflater();
		compressor.setLevel(Deflater.BEST_COMPRESSION);
		
		// Create an expandable byte array to hold the compressed data.
	    // It is not necessary that the compressed data will be smaller than
	    // the uncompressed data.
	    ByteArrayOutputStream bos = new ByteArrayOutputStream(data.length);
	    
		compressor.setInput(data);
		compressor.finish();
	    
	    // Compress the data
	    byte[] buf = new byte[1024];
	    while ( !compressor.finished() ) {
	        int count = compressor.deflate(buf);
	        bos.write(buf, 0, count);
	    }
	    try {
	        bos.close();
	    } catch (IOException e) {
	    	e.printStackTrace();
	    	return null;
	    }
	    
	    // Get the compressed data
	    return bos.toByteArray();
	}
	
	
	public static byte[] unpack(byte[] data) {
		// Create the decompressor and give it the data to compress
		Inflater decompressor = new Inflater();
		decompressor.setInput(data);
	    
		// Create an expandable byte array to hold the decompressed data
		ByteArrayOutputStream bos = new ByteArrayOutputStream(data.length);
	    
		// Decompress the data
		byte[] buf = new byte[1024];
		while ( !decompressor.finished() ) {
			try {
				int count = decompressor.inflate(buf);
				bos.write(buf, 0, count);
			} catch ( DataFormatException e ) {
				e.printStackTrace();
				return null;
			}
		}
		try {
			bos.close();
		} catch (IOException e) {
		}
	    
		// Get the decompressed data
		return bos.toByteArray();
	}

	
	public static void pack(String fileNameFrom, String fileNameTo) {
		try {
			byte[] data = readFile(fileNameFrom);
			byte[] packet = pack(data);
			writeFile(fileNameTo, packet);			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void unpack(String fileNameFrom, String fileNameTo) {
		try {
			byte[] data = readFile(fileNameFrom);
			byte[] unpacket = unpack(data);
			writeFile(fileNameTo, unpacket);			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private static byte[] readFile(String fileName) throws IOException {
		RandomAccessFile f = new RandomAccessFile(fileName, "rw");
		byte[] buf = new byte[(int)f.length()];
		f.read(buf);
		f.close();
		return buf;
	}
	
	
	private static void writeFile(String fileName, byte[] buf) throws IOException {
		RandomAccessFile f = new RandomAccessFile(fileName, "rw");
		f.write(buf);
		f.close();
	}

}
