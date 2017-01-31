import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.io.IOException;

import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

public class Svn implements Runnable {
	
	private static final String SVN_COMMENT = "Autocommited by words svn-plugin";
	private static final long TIME_INTERVAL = 10*60;
	
	private static final ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
	
	private String rootPath;
	
	/**
	 * Каждый плагин должен иметь публичный конструктор без параметров
	 */
	public Svn() {
	}
	
	
	/**
	 * Метод вызывается единократно при инициализации плагина
	 * 
	 * @return true, если плагин инициализирован и готов к загрузке
	 */
	public boolean init(String rootPath) {
		this.rootPath = rootPath;
		System.out.print("Init SVN plugin...   ");
		if ( new File(rootPath + File.separatorChar + ".svn").exists() ) {
			System.out.println("SVN found!");
			final Runnable task = new Thread(this);
			final ScheduledFuture<?> beeperHandle = scheduler.scheduleAtFixedRate(task, 60, TIME_INTERVAL, TimeUnit.SECONDS);
		} else {
			System.out.println("SVN not found!");
		}
		return true;
	}

	
	public void run() {
		String cmd[];
		
		cmd = new String[] {
			"svn",
			"update",
			rootPath,
		};
		exec(cmd);
		
		cmd = new String[] {
			"svn",
			"commit",
			rootPath,
			"-m",
			"'" + SVN_COMMENT + "'"
		};

		exec(cmd);
//		System.out.println("beep "+rootPath);
	}
	
	
	private static void exec(String[] command) {
		try {
			//System.out.println("JAVA EXEC: " + command);
			Process process = Runtime.getRuntime().exec(command);
			process.waitFor();
			int exitValue = process.exitValue();
			BufferedReader br = new BufferedReader(new InputStreamReader(process.getInputStream()));
			
			String line;
			while ( (line = br.readLine()) != null ) {
				System.out.println(line);  
			}
			
			br = new BufferedReader(new InputStreamReader(process.getErrorStream()));
			while ( (line = br.readLine()) != null ) {
				System.err.println(line);  
			}  
			
//			System.out.println("EXEC return "+ exitValue);
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}