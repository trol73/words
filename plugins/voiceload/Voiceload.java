import java.io.File;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class Voiceload extends Thread {
	
	private String rootPath;
	private static final String VOICE_DIR = "voice-load-";
	
	/**
	 * Каждый плагин должен иметь публичный конструктор без параметров
	 */
	public Voiceload() {
		
	}
	
	/**
	 * Метод вызывается единократно при инициализации плагина
	 * 
	 * @return true, если плагин инициализирован и готов к загрузке
	 */
	public boolean init(String rootPath) {
		this.rootPath = rootPath;
		System.out.println("plugin init: Voiceload " + rootPath);
		return true;
	}
	
	/**
	 * Вызывается при проигрывании звука когда звуковой файл не найден
	 * 
	 * @param word отсутствующее слово
	 * @param lang 1 - английское, 2 - русское 
	 */
	public void onSoundNotFound(String word, int lang) {
		System.out.println("SoundNotFound " + word + " :  " + lang);
		String slang = lang == 1 ? "en" : "ru";
		String path = rootPath + File.separatorChar + "plugins" + File.separatorChar + "voiceload" + File.separatorChar;
		String dir = rootPath + File.separatorChar + VOICE_DIR + slang;
		String cmd[] = new String[] {
			path + "synth.py",
			slang,
			dir,
			'"' + word + '"'
		};
		//System.out.println(cmd);
		exec(cmd);
	}
	
	
	/**
	 * 
	 */
	public void run() {
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
			
			System.out.println("EXEC return "+ exitValue);
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	private String[] command = new String[0];
	
	/**
	 * 
	 * @param cmd
	 */
	private void exec(final String[] cmd) {
		synchronized ( command ) {
			command = cmd;
			new Thread(this).start();
		}
	}
	


}
