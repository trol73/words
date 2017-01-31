package trolsoft.words;


// bugs
// FIXME dictionary - виснет иногда???
// FIXME не всегда прячет первое слово в режиме паузы
// FIXME фокусировать окно словаря, если оно уже открыто (при вызове из меню)
// FIXME после перезагрузки словаря на ходу проблемы
// FIXME указываю несколько словарей, один из которых с местоимениями. комментирую # все остальные. в результате отображаются все равно все слова
// FIXME запускаюсь с закомментированными в настойках словарями. иду в настройки и раскомментирую словари. иду в словарь, словари не загружены

// tasks
// TODO create some base class for all windows
// TODO icons on settings tabs
// TODO кешировать словари в окне редактора
// TODO resizable dictionary window
// TODO JPopupMenu
// TODO настраиваемый индикатор статистики на экране
// TODO предупреждать в словаре, что слово не было сохранено
// TODO custom statistic hint window
// TODO stereo sound for player and generator
// TODO error handler for mobile and audio gnerator
// TODO statistic output for audio generator
// TODO hotkey from words pair marking
// TODO pack editor
// TODO ускорить загрузку использую многопоточность
// TODO альтернативные цвета для слов, чтобы выделять варианты (когда слова разделены ';')
// TODO возможность загрузить полностью озвучку для всего словаря с немодальным окошком в фоновом режиме
// TODO в about добавить кнопки перепостав в соцсетях
// TODO смотреть сюда - http://www.learnwords.ru сделать режим с табличкой и режим выбора вариантов
// TODO перегружать словари в случае изменения настроек только тогда, когда это реально необходимо


// bigtasks
// TODO поддержка плагинов добавляющих окна в главное меню
// TODO  - запоминалка алфавита
// TODO  - запоминалка знаков транскрипции
// TODO  - запоминалка чисел
// TODO  - запоминалка времен и дат
// TODO  - неправильные глаголы

// TODO подсчет степени употребимости слов
// TODO  закачка в интернете разных статей, разбивка на слова, поиск слов с этим корнем

// server
// TODO регистрация пользователей
// TODO логгинг в БД с отключением админа и вычислением статистики
// TODO для слова выдавать детальную информацию сворованную с гугла и закешированную
// TODO словари. поддержка словарий с возможностью загрузки по сети. стырить эти http://www.learnwords.ru/database.html


import java.awt.AWTException;
import java.awt.Dialog;
import java.awt.SystemTray;
import java.awt.TrayIcon;
import java.awt.TrayIcon.MessageType;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;

import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UIManager.LookAndFeelInfo;

import trolsoft.dict.HashDictionary;
import trolsoft.dict.MixedDictionary;
import trolsoft.dict.PairDictionary;
import trolsoft.dict.WordPair;
import trolsoft.plugins.Plugins;
import trolsoft.sound.WordsPlayer;
import trolsoft.utils.I18N;
import trolsoft.utils.Utils;
import trolsoft.words.tools.Updates;
import trolsoft.words.windows.MainWindow;
import trolsoft.words.windows.WindowAbout;
import trolsoft.words.windows.WindowDict;
import trolsoft.words.windows.WindowMobileGenerator;
import trolsoft.words.windows.WindowPlayerGenerator;
import trolsoft.words.windows.WindowSettings;

public class Words {

	public static final String NAME = I18N.get("words.title");
	
	public static final String VERSION = "0.7";
	public static final String URL = "http://trolsoft.ru/";
	protected static final String URL_PAGE = URL + "soft/words/";

	private static final String _COMPLETED = I18N.get("message.completed");
	private static final String _WORDS = I18N.get("message.words");
	private static final String _WORD = I18N.get("message.word");
	private static final String _ONE_WORD = I18N.get("message.oneWord");
	private static final String _FROM = I18N.get("message.from");	
	
	private static Configuration config;
	private static TrayIcon trayIcon;
	private static TrayPopupMenu popupMenu;
	private static MainWindow wnd;
	private static MixedDictionary dictLearn;
	private static PairDictionary dictDeleted;
	private static HashDictionary dictTranscription;
	private static TimerTask timer;
	private static WindowSettings wndSettings;
	private static WindowAbout wndAbout;
	private static WindowDict wndDict;
	private static Plugins plugins;


	private static boolean started;

	public static WordsPlayer player = WordsPlayer.getInstance();


    public static final void message(String msg, MessageType mt) {
        trayIcon.displayMessage(NAME + ' ' + VERSION, msg, mt);
    }



    

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String lookAndFeelName = UIManager.getSystemLookAndFeelClassName();
		if ( "javax.swing.plaf.metal.MetalLookAndFeel".equals(lookAndFeelName) ) {
			for (LookAndFeelInfo lfi : UIManager.getInstalledLookAndFeels() ) {
				if ( "com.sun.java.swing.plaf.gtk.GTKLookAndFeel".equals(lfi.getClassName()) ) {
					lookAndFeelName = lfi.getClassName();
				}
	        	System.out.println(lfi);
	        }	
		}
        try {
            UIManager.setLookAndFeel(lookAndFeelName);
        } catch(Exception e) {
            e.printStackTrace();
        }

        config = new Configuration();
        if ( !config.load() ) {        	
        	config.save();
        	config.load();		// загружаем конфигурацию, чтобы относительные пути к файлам преобразовались в абсолютные
        	about();
        }

		wnd = new MainWindow();

		wnd.setWordClickListener(new WordClickListener() {
			@Override
			public void onClick(int word, WordPair pair) {
				if ( Words.getConfiguration().learnViewmode ) {
					wnd.extractNewPair();
					wnd.setTextVisible(true, true);
				} else {
					if ( dictLearn.markComplete(timer.getCurrentPair()) ) {
						System.out.println("delete: " + timer.getCurrentPair().wordInMyLang);
					}
					dictLearn.getCompletedWords().save();
				}
			}
		});

		dictLearn = new MixedDictionary();
		dictDeleted = new PairDictionary();
		dictTranscription = new HashDictionary();

		popupMenu = new TrayPopupMenu(NAME);
		boolean trayIconCreated = false;
		// операция создания иконки в трее иногда не срабатывает с первого раза. поэтому пытаемся несколько раз
		for ( int i = 0; i < 10; i++) {
			if ( createTrayIcon() ) {
				trayIconCreated = true;
				break;
			}
			Utils.sleep(100);
		}
		if (!trayIconCreated) {
			System.exit(-10);
		}
		Updates.checkUpdates();
		
		plugins = new Plugins();
		plugins.loadPlugins(Configuration.getRootPath() + File.separatorChar + "plugins", Configuration.getRootPath());
		
		init();		
		updateTrayIcon(true);
		
		started = true;
		updateCurrentMode(started, true);
	}
	
	/**
	 * 
	 */
	private static final boolean createTrayIcon() {
        SystemTray tray = SystemTray.getSystemTray();
        try {
            trayIcon = new TrayIcon(Resources.imgWait(), NAME + " v" + VERSION, popupMenu);
            trayIcon.addMouseListener(new MouseAdapter() {
            	public void mouseClicked(MouseEvent e) {
            		if ( e.getButton() != MouseEvent.BUTTON1 ) {
            			return;
            		}
					if ( started ) {
						updateCurrentMode(false, false);
					} else {
						updateCurrentMode(true, false);
					}
				}
            });
            trayIcon.setImageAutoSize(true);
            tray.add(trayIcon);
            return true;
        } catch (AWTException ex) {
            ex.printStackTrace();
            return false;
        }
	}

	/**
	 * 
	 */
	public static void about() {
		if ( wndAbout == null ) {
			wndAbout = new WindowAbout();
			wndAbout.setLocation(Utils.getPointForCentering(wndAbout));
		}
		showWindow(wndAbout);
	}
	
	/**
	 * 
	 */
	public static final void showSettinsWindow() {
		if ( wndSettings == null ) {
			wndSettings = new WindowSettings();
			wndSettings.setLocation(Utils.getPointForCentering(wndSettings));
		}
		showWindow(wndSettings);
	}
	
	/**
	 * 
	 */
	public static final void showDictionaryWindow() {
		if ( wndDict == null ) {
			wndDict = new WindowDict();
			wndDict.setLocation(Utils.getPointForCentering(wndDict));
		}
		showWindow(wndDict);
	}
	
	/**
	 * 
	 */
	public static final void showMobileGenerator() {
		WindowMobileGenerator wndMobileGenerator = new WindowMobileGenerator();
		wndMobileGenerator.setLocation(Utils.getPointForCentering(wndMobileGenerator));
		wndMobileGenerator.setModalExclusionType(Dialog.ModalExclusionType.APPLICATION_EXCLUDE);
		wndMobileGenerator.setVisible(true);
	}
	

	/**
	 * 
	 */
	public static final void showPlayerGenerator() {
		WindowPlayerGenerator wndPlayerGenerator = new WindowPlayerGenerator();
		wndPlayerGenerator.setLocation(Utils.getPointForCentering(wndPlayerGenerator));
		wndPlayerGenerator.setModalExclusionType(Dialog.ModalExclusionType.APPLICATION_EXCLUDE);
		wndPlayerGenerator.setVisible(true);
	}
	
	
	/**
	 * 
	 * @param wnd
	 */
	private static final void showWindow(final JFrame wnd) {
		// TODO nedd to restore window, if that was collapsed
		wnd.setVisible(true);
/*		
		if ( !wnd.isVisible() ) {
			wnd.setVisible(true);
		} else {
			wnd.toBack();
			wnd.toFront();
		}
*/
	}

	/**
	 * 
	 */
	public static void init() {
		updateTrayIcon(true);
		wnd.init();
		dictLearn.setMode(config.learnMode);
		dictLearn.setWordsInGroup(config.learnGroupwordslimit);
		dictLearn.load(config.dictsLearn);
		
		// TODO
		dictDeleted.clear();
		for ( String fn : config.dictsDeleted ) {
			dictLearn.getCompletedWords().load(fn, true);
			dictDeleted.load(fn, true);
		}
		dictLearn.getCompletedWords().clear();
		dictLearn.completeDict(dictDeleted);
		
		dictTranscription.load(config.dictsTranscriptions);
		
		updateCurrentMode(started, true);
		System.gc();
	}
	
	/**
	 * 
	 */
	public static void createTimer() {
		if ( timer != null ) {
			timer.stop();
		}
		timer = new TimerTask(TimerTask.getConfigInterval(), wnd);
		initPlayerSettings();
		if ( started ) {
			timer.start();
		}
	}


	
	/**
	 * Выводит сообщение о количестве выученных слов
	 */
	public static void showInfoHint() {
		int total = dictLearn.size();
		// TODO дважды пробегается весь список слов
		int completedEnglToRus = dictLearn.getLearnedWords(WordPair.Direction.LearnToMy);
		int completedRusToEngl = dictLearn.getLearnedWords(WordPair.Direction.MyToLearn);
		int percentEnglToRus = total != 0 ? 100*completedEnglToRus/total : 0;
		int percentRusToEngl = total != 0 ? 100*completedRusToEngl/total : 0;
		String strTotal = Integer.toString(total);
		String strCompleted, strPercent;
		switch ( config.learnMode ) {
			case LearnToMy:
				strCompleted = Integer.toString(completedEnglToRus);
				strPercent = Integer.toString(percentEnglToRus) + '%';
				break;
			case MyToLearn:
				strCompleted = Integer.toString(completedRusToEngl);
				strPercent = Integer.toString(percentRusToEngl) + '%';
				break;
			case LearnToMy_or_MyToLearn:
			case LearnToMy_and_MyToLearn:
				strCompleted = Integer.toString(completedEnglToRus) + '/' + Integer.toString(completedRusToEngl);
				strPercent = Integer.toString(percentEnglToRus)  + '%' + '/' + Integer.toString(percentRusToEngl)  + '%';
				break;
			default:				
				strCompleted = null;
				strPercent = null;
				break;
		}
		String strCompletedWords;
		switch ( strCompleted.charAt(strCompleted.length()-1) ) {
			case '1':
				strCompletedWords = _ONE_WORD;
				break;
			case '2':
			case '3':
			case '4':
				strCompletedWords = _WORD;
				break;
			default:
				strCompletedWords = _WORDS;
		}
		String hint = _COMPLETED + " " + strCompleted + ' ' + strCompletedWords + " "+_FROM+" " + strTotal + " (" + strPercent +")";
		message(hint, MessageType.INFO);
	}





    public static Configuration getConfiguration() {
    	return config;
    }


    public static MainWindow getWindow() {
    	return wnd;
    }
    
    
    public static TimerTask getTimerTask() {
    	return timer;
    }
    
    public static MixedDictionary getDictLearn() {
    	return dictLearn;
    }
    
    public static HashDictionary getDictTranscription() {
    	return dictTranscription;
    }
    
    
    
    /**
     * Стартует или останавливает текущий режим (запоминание/контроль)
     * 
     * @param start - остановить/запустить
     * @param init - если true, будет выполненна переинициализация таймера и перезагрузка слова
     */
    public static void updateCurrentMode(boolean start, boolean init) {
    	if ( timer != null ) {
    		timer.stop();
    	}

    	if ( config.learnViewmode ) {
    		wnd.setTextVisible(start, start);
       	}
    	if ( init && start ) {
    		createTimer();
    		if ( config.learnViewmode ) {
    			wnd.extractNewPair();
    			wnd.setTextVisible(true, true);
    		}
    	}
    	if ( start && timer != null ) {
    		timer.start();
    	} else if ( timer != null ) {
    		timer.stop();
    	}
    	started = start;
    	popupMenu.setMenuItemEnabled(TrayPopupMenu.MENU_START, !started);
    	popupMenu.setMenuItemEnabled(TrayPopupMenu.MENU_STOP, started);
    	updateTrayIcon(false);
    }
    
    /**
     * 
     */
    private static void updateTrayIcon(boolean wait) {
    	if ( wait ) {
    		trayIcon.setImage(Resources.imgWait());
    	} else {
    		trayIcon.setImage(started ? Resources.imgStart() : Resources.imgPause());
    	}
	}
    

    /**
     * 
     * @return
     */
    public static final boolean isStarted() {
    	return started;
    }

    /**
     * Переинициализирует аудиоплеер
     */
	public static void initPlayerSettings() {
		updateTrayIcon(true);
		Configuration cfg = Words.getConfiguration();
		Words.player.setPathEngl(cfg.soundEnglish);
		Words.player.setPathRuss(cfg.soundRussian);
		Words.player.setVolume(cfg.soundPlayVolume);
		updateTrayIcon(false);
		System.gc();
	}
	
	
	/**
	 * Перерагружает все файлы словарей 
	 */
	public static final void resetDicts() {
		updateTrayIcon(true);
		dictLearn.getCompletedWords().clear();
		dictLearn.getCompletedWords().save();
		init();
		updateTrayIcon(false);
	}
	
	
	/**
	 * 
	 * @return
	 */
	public static String getVersion() {
		String version = Words.class.getPackage().getImplementationVersion();
		if ( version == null ) {
			version = Words.VERSION;
		}
		return version;
	}
	
	
	/**
	 * 
	 * @return
	 */
	public static final Plugins getPlugins() {
		return plugins;
	}


}
