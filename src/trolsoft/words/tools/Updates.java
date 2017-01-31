package trolsoft.words.tools;

import java.awt.TrayIcon.MessageType;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.StringTokenizer;

import trolsoft.utils.I18N;
import trolsoft.words.Words;

public class Updates {
	
	private static final String URL = Words.URL + "soft/words/version.php";
	
	private static int responseCode;
//	private static String responseMsg;	
	private static String lastVersion;
	
	/**
	 * Проверяет наличие новой версии на сайте
	 * 
	 * @return true, если доступна новая версия
	 */
	public static final boolean isNewVersionAvailable() {
		try {
			String s = httpRequest(URL);
			if ( s != null && s.length() > 0 ) {
				lastVersion = s;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		String myVersion = Words.getVersion();
		int myVersionVal = versionToValue(myVersion);
		int lastVersionVal = versionToValue(lastVersion);
		return myVersionVal > 0 && lastVersionVal > myVersionVal;
	}
	
	
	/**
	 * Выполняет GET-запрос на сервер
	 * 
	 * @param url
	 * @return 
	 * @throws IOException 
	 */
	private static final String httpRequest(String url) throws IOException {
		URL u = new URL(url + "?appid=" + Words.getConfiguration().wordsUid + "&version="+Words.getVersion());
		HttpURLConnection c = (HttpURLConnection) u.openConnection();
		c.setDoInput(true);
		c.setRequestMethod("GET");
		c.connect();
		responseCode = c.getResponseCode();
//		responseMsg = c.getResponseMessage();
		if ( responseCode != HttpURLConnection.HTTP_OK ) {
			return null;
		}
		InputStream is = c.getInputStream();
		BufferedReader reader = new BufferedReader(new InputStreamReader(is));
		String result = "";
		while ( result.length() == 0 ) {
			result = reader.readLine().trim();
		}
		reader.close();
		return result;
	}
	
	
	/**
	 * Преобразует строку версии в условное число для сравнения
	 * 
	 * @param version
	 * @return значение версии, или 0, если стрка версии имеет неправильный формат 
	 */
	private static int versionToValue(String version) {
		if ( version == null || version.length() < 3 ) {
			return 0;
		}
		StringTokenizer st = new StringTokenizer(version, ".");
		if ( st.countTokens() != 3 && st.countTokens() != 2 ) {
			return 0;
		}
		try {
			String strVer = st.nextToken();
			String strRev = st.nextToken();
			String strBuild = st.hasMoreTokens() ? st.nextToken() : "";
			
			int ver = Integer.parseInt(strVer);
			int rev = Integer.parseInt(strRev);
			int build = strBuild.length() > 0 ? Integer.parseInt(strBuild) : 0;
			
			if ( ver < 0 || rev < 0 || build < 0 ) {
				return 0;
			}
			return ver * 1000000 + rev * 1000 + build; 
		} catch ( Exception ex) {
			ex.printStackTrace();
			return 0;
		}
	}
	
	
	/**
	 * 
	 * @return
	 */
	public static String getVersion() {
		return lastVersion;
	}
	
	
	public static final void checkUpdates() {
		new Thread() {			
			@Override
			public void run() {
				if ( isNewVersionAvailable() ) { 
					Words.message(I18N.get("messages.newVersionAvailable") +" " + Updates.getVersion(), MessageType.INFO);
				}
			}
		}.start();
	}
	
	
/*
	public static void main(String[] args) throws IOException {
		String s = httpRequest(URL);
		System.out.println(s + " -> " + versionToValue(s));
		System.out.println(Words.getVersion() + " -> " + versionToValue(Words.getVersion()));
		System.out.println(isNewVersionAvailable());
	}
*/
}
