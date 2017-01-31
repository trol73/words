package trolsoft.utils;

import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.Image;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Window;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.List;

import trolsoft.words.Words;

public class Utils {
	
	private static Words wordsInstance;

	public static final int UI_MAX_HEIGHT = 24;
	
	public static boolean isWindows = System.getProperty("os.name", "").toLowerCase().indexOf("windows") > 0;

	/**
	 * <p/>
	 * Returns the <code>Point</code> at which a window should be placed to
	 * center that window on the given desktop.
	 * </p>
	 * <p/>
	 * Some thought was taken as to whether to implement a method such as this,
	 * or to simply make a method that, given a window, will center it. It was
	 * decided that it is better to not alter an object within a method.
	 * </p>
	 * 
	 * @param window
	 *            The window (JInternalFrame) to calculate the center point for.
	 *            This object can not be null.
	 * 
	 * @return the <code>Point</code> at which the window should be placed to
	 *         center that window on the given desktop
	 */
	public static Point getPointForCentering(Window window) {
		try {
			// assert window != null;
			Point mousePoint = MouseInfo.getPointerInfo().getLocation();
			GraphicsDevice[] devices = GraphicsEnvironment.getLocalGraphicsEnvironment().getScreenDevices();
			for (GraphicsDevice device : devices) {
				Rectangle bounds = device.getDefaultConfiguration().getBounds();
				// check to see if the mouse cursor is within these bounds
				if (mousePoint.x >= bounds.x && mousePoint.y >= bounds.y
						&& mousePoint.x <= (bounds.x + bounds.width)
						&& mousePoint.y <= (bounds.y + bounds.height)) {
					// this is it
					int screenWidth = bounds.width;
					int screenHeight = bounds.height;
					int width = window.getWidth();
					int height = window.getHeight();
					return new Point(((screenWidth - width) / 2) + bounds.x, ((screenHeight - height) / 2) + bounds.y);
				}
			}
		} catch (Exception e) {

		}
		return new Point(0, 0);
	}

	/**
	 * 
	 * @param name
	 * @return
	 */
	public static final Image createImageFromJar(String name) {
		java.net.URL imgURL = getJarClass().getResource("/" + name);

		java.awt.Toolkit tk = java.awt.Toolkit.getDefaultToolkit();
		Image img = null;
		try {
			java.awt.MediaTracker m = new java.awt.MediaTracker(Words.getWindow());
			img = tk.getImage(imgURL);
			m.addImage(img, 0);
			// m.waitForAll();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return img;
	}
	
	
	/**
	 * Прочитать ресурс из jar-файла
	 * 
	 * @param path
	 * @return
	 */
	public static final InputStream getResourceFromJar(String path) {
		return getJarClass().getResourceAsStream(path);
	}
	
	
	/**
	 * Прочитать текстовый файл из jar-файла
	 * 
	 * @param path
	 * @return
	 */
	public static final List<String> createTextFileFromJar(String path) {
		InputStream is = getResourceFromJar(path);
		BufferedReader br = new BufferedReader(new InputStreamReader(is));
		List<String> list = new ArrayList<String>();
		String line;
		try {
			while ( null != (line = br.readLine()) ) {
				list.add(line);
			}
		} catch (IOException e) {
			e.printStackTrace();
			list = null;
		}
		finally {
			try {
				if ( br != null ) {
					br.close();
				}
				if ( is != null ) {
					is.close();
				}
			} catch ( IOException e ) {
				e.printStackTrace();
			}
		}
		return list;
	}
	
	
	/**
	 * 
	 * @return
	 */
	private static Class<?> getJarClass() {
		if ( wordsInstance == null ) {
			wordsInstance = new Words();
		}
		return wordsInstance.getClass();
	}
	
	
	/**
	 * Сравнивает имена файлов с учеом регистрочувствительности ОС
	 * 
	 * @param fn1
	 * @param fn2
	 * @return true, если имена совпадают
	 */
	public static final boolean isEqualFileNames(String fn1, String fn2) {
		fn1 = fn1.replace('\\', '/');
		fn2 = fn2.replace('\\', '/');
		if ( fn1.equals(fn2) ) {
			return true;
		}
		if ( isWindows && fn1.equalsIgnoreCase(fn2) ) {
			return true;
		}
		return false;
	}
	
	
	/**
	 * 
	 * @param max
	 * @return
	 */
	public static int random(int max) {
		int rnd = (int)Math.round(Math.random()*(max)-1);
		if ( rnd < 0 ) {
			rnd = -rnd;
		}
		return rnd;
	}
	
	
	/**
	 * 
	 * @param fileName
	 * @param os
	 * @throws IOException
	 */
	public static void writeFileToStream(String fileName, OutputStream os) throws IOException {
		FileInputStream is = new FileInputStream(fileName);
		final int buffersize = 1024; 
		byte buffer[] = new byte[buffersize]; 
		int readcount = 0; 
		while ( (readcount = is.read(buffer, 0, buffersize)) >= 0 ) { 
			if ( readcount > 0 ) { 
				os.write(buffer, 0, readcount); 
			}
		}
		is.close();
	}
	
	/**
	 * 
	 * @param fileName
	 * @return
	 * @throws IOException 
	 */
	public static List<String> readTextFile(String fileName) throws IOException {
		FileReader fr = new FileReader(fileName);
		BufferedReader in = new BufferedReader(fr);

		List<String> lines = new ArrayList<String>();
		String line;
		while ( true ) {
			line = in.readLine();
			if ( line == null ) {
				break;
			}
			lines.add(line);
		}
		in.close();
		fr.close();
		return lines;
	}
	

	/**
	 * 
	 * @param fileName
	 * @return
	 */
	public static byte[] readBinaryFile(String fileName) {
		File f = new File(fileName);

		if ( !f.exists() ) {
			return null;
		}
		try {
			RandomAccessFile rf = new RandomAccessFile(fileName, "rw");
			int len = (int)f.length();
			byte[] buf = new byte[len];			
			rf.read(buf);
			rf.close();
			return buf;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	
	/**
	 * 
	 * @param fileName
	 * @param lines
	 * @throws IOException 
	 */
	public static void writeTextToFile(String fileName, List<String> lines) throws IOException {
		FileWriter wr = new FileWriter(fileName);
		BufferedWriter out = new BufferedWriter(wr);
		for ( String s : lines ) {
			out.write(s);
			out.write("\n");
		}
		out.close();
		wr.close();
	}

	public static void sleep(long millis) {
		try {
			Thread.sleep(millis);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
