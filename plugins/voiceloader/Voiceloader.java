import java.io.DataInputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.ConnectException;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;
import java.net.URLDecoder;
import java.util.Properties;
import java.util.Locale;




public class Voiceloader extends Thread {
	
	private String rootPath;
	private static final String VOICE_DIR = "voice-load-";
	private static final String HOST = "http://trolsoft.ru/services/voiceloader.php";
	//private static final String HOST = "http://trol.dyndns.tv:8080/wordsldr/services/get";
	
	private Properties properties;
	private String appId;

	
	/**
	 * Каждый плагин должен иметь публичный конструктор без параметров
	 */
	public Voiceloader() {
		
	}
	
	/**
	 * 
	 */
	private void loadProperties() {
		properties = new Properties();
		try {
			properties.load(new FileReader(new File(rootPath + File.separator + "words.conf")));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * 
	 * @return
	 */
	private String getAppId() {
		if ( appId != null ) {
			return appId;
		}
		loadProperties();
		appId = properties.getProperty("words.uid");
		return appId;
	}
	
	/**
	 * Метод вызывается единократно при инициализации плагина
	 * 
	 * @return true, если плагин инициализирован и готов к загрузке
	 */
	public boolean init(String rootPath) {
		this.rootPath = rootPath;
		System.out.println("Init Voiceloader plugin");
		System.out.println("    output path: " + rootPath + File.separatorChar + VOICE_DIR + "[lang]");
		return true;
	}
	
	/**
	 * Вызывается при проигрывании звука когда звуковой файл не найден
	 * 
	 * @param word отсутствующее слово
	 * @param lang код языка
	 */
	public void onSoundNotFound(String word, String lang) {
		System.out.println("SoundNotFound [" + lang + "]: " + word);
		String dir = rootPath + File.separatorChar + VOICE_DIR + lang;
		String cmd[] = new String[] {
			word,
			lang,
			dir
		};
		load(cmd);
	}
	
	
	/**
	 * 
	 * @param contentDisposition
	 * @return
	 */
	private static String getWordFileName(String word, String contentDisposition) {
		try {
			final String beginMarker = "filename*=UTF-8''";
			int pos = contentDisposition.indexOf(beginMarker);
			if ( pos > 0 ) {
				String fileName = contentDisposition.substring(pos + beginMarker.length());
				return URLDecoder.decode(fileName, "utf-8");
			}			
		} catch ( Exception e) {
			e.printStackTrace();
		}	
		return word.replace(' ', '_') + ".ogg";
	}
	
	/**
	 * 
	 */
	public void run() {
		if ( command.length != 3 ) {
			return;
		}
		String word = command[0];
		String lang = command[1];
		String dir = command[2];
		String appid = getAppId();

		try {
			//URL url = new URL(HOST + "?lang="+lang+"&phrase="+URLEncoder.encode(word, "utf-8")+"&appid="+appid);
			URL url = new URL(HOST + "?lang="+lang+"&phrase="+encodeURLComponent(word)+"&appid="+appid);
			
			URLConnection connection = url.openConnection();
			DataInputStream in = new DataInputStream(connection.getInputStream());
			if ( connection.getContentLength() <= 0 ) {
				return;
			}

			String fileName = getWordFileName(word, connection.getHeaderField("Content-Disposition"));

			System.out.println("VoiceLoader: saving word " + word + " to file " + dir + File.separator + fileName);
			File fDir = new File(dir);
			if ( !fDir.exists() ) {
				fDir.mkdirs();
			}
			File f = new File(dir + File.separator + fileName);
			FileOutputStream os = new FileOutputStream(f);
			final int BUFSIZE = 1024*64;
			byte[] bbuf = new byte[BUFSIZE];


			int length;
			while ( in != null && (length = in.read(bbuf)) != -1 ) {
				os.write(bbuf, 0, length);
			}

			in.close();
			os.flush();
			os.close();
		} catch ( ConnectException ce ) {
			System.out.println("VoiceLoader: can't connect to server");
		} catch ( Exception e ) {
			e.printStackTrace();
		}
	}
	

	private String[] command = new String[0];
	
	/**
	 * 
	 * @param cmd
	 */
	private void load(final String[] cmd) {
		synchronized ( command ) {
			command = cmd;
			new Thread(this).start();
		}
	}
	
	
	
public static String encodeURLComponent(final String s)
{
  if (s == null)
  {
    return "";
  }

  final StringBuilder sb = new StringBuilder();

  try
  {
    for (int i = 0; i < s.length(); i++)
    {
      final char c = s.charAt(i);

      if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')) ||
          ((c >= '0') && (c <= '9')) ||
          (c == '-') ||  (c == '.')  || (c == '_') || (c == '~'))
      {
        sb.append(c);
      }
      else
      {
        final byte[] bytes = ("" + c).getBytes("UTF-8");

        for (byte b : bytes)
        {
          sb.append('%');

          int upper = (((int) b) >> 4) & 0xf;
          sb.append(Integer.toHexString(upper).toUpperCase(Locale.US));

          int lower = ((int) b) & 0xf;
          sb.append(Integer.toHexString(lower).toUpperCase(Locale.US));
        }
      }
    }

    return sb.toString();
  }
  catch (UnsupportedEncodingException uee)
  {
    throw new RuntimeException("UTF-8 unsupported!?", uee);
  }
}

/*
	public static void main(String[] args) {
		String cmd[] = new String[] {
			"слово",
			"ru",
			"/home/trol/bin"
		};
		Voiceloader vl = new Voiceloader(); 
		vl.appId = "1234567890123456789";
		vl.load(cmd);
	}
*/
}
