package trolsoft.words;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Timer;

import trolsoft.dict.WordPair;
import trolsoft.dict.WordPair.WordNumber;
import trolsoft.words.windows.MainWindow;

public class TimerTask {

	private Timer timer;
	private MainWindow window;
	public WordPair lastPair;
	public boolean firstWordVisible = false;
	private boolean started = false;
	

	private ActionListener listener = new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
			onTick();
		}

	};


	public TimerTask(int delay, MainWindow window) {
		timer = new Timer(delay, listener);
		this.window = window;
	}


	public WordPair getCurrentPair() {
		return lastPair;
	}

	
	private void onTick() {
		if ( !Words.getConfiguration().learnViewmode ) {
			if ( !firstWordVisible ) {
				window.setTextVisible2(false);
				lastPair = window.extractNewPair();
				if ( lastPair != null ) {
					window.setTextVisible1(true);
				}
			} else {
				window.setTextVisible2(true);
			}
		}
		if ( window.getMixedPair() != null ) {
			playWord(window.getMixedPair(), firstWordVisible ? WordNumber.Second : WordNumber.First);
		}
		firstWordVisible = !firstWordVisible;		
		window.setVisible(true);
	}
	
	

	public void start() {
		timer.start();
		started = true;
	}
	
	public void resume() {
		if ( started ) {
			timer.start();
			new Thread() {
				@Override
				public void run() {
					onTick();					
				}
			}.start();
		}
	}


	public void stop() {
		timer.stop();
		started = false;
		firstWordVisible = false;
		window.setTextVisible(false, false);
	}


	public boolean isStarted() {
		return started;
	}
	
	
	private void playWord(WordPair pair, WordNumber wordNum) {
		if ( pair == null ) {
			return;
		}
		String word = pair.getWord(wordNum);
		Configuration cfg = Words.getConfiguration();
		boolean playLearnLang; 
		boolean playMyLang;
		if ( cfg.learnViewmode ) {
			playLearnLang = cfg.soundViewPlayEnglish;
			playMyLang = cfg.soundViewPlayRussian;
		} else {
			playLearnLang = cfg.soundControlPlayEnglish;
			playMyLang = cfg.soundControlPlayRussian;
		}
		
		//if ( (lastPair.getLangType(wordNum) == WordPair.LangType.Learn && playLearnLang) || playMyLang ) {
		if ( playLearnLang || playMyLang ) {
			timer.stop();			
			Words.player.play(word, pair.getWordLang(wordNum));
		}
	}
	
	
	public static int getConfigInterval() {
		Configuration cfg = Words.getConfiguration();
		return cfg.learnViewmode ? cfg.learnViewTime : cfg.learnTime;
	}
	
	
	

}
