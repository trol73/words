package trolsoft.words;

import java.awt.CheckboxMenuItem;
import java.awt.Menu;
import java.awt.PopupMenu;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.net.URI;

import trolsoft.utils.I18N;

public class TrayPopupMenu extends PopupMenu {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 7588928386884416054L;
/*
	public static String MENU_START = "Start";
	public static String MENU_STOP = "Stop";
	public static String MENU_SETTINGS = "Settings";
	public static String MENU_RESET = "Reset";
	public static String MENU_RELOAD = "Reload";
	public static String MENU_MODE = "Mode";
	public static String MENU_DICTS = "Dictionaries";
	public static String MENU_INFO = "Info";
	public static String MENU_ABOUT = "About";
	public static String MENU_HELP = "Help";
	public static String MENU_EXIT = "Exit";
	
	public static String MENU_MODE_LEARN = "Learn";
	public static String MENU_MODE_CONTROL = "Control";
	
	public static String MENU_OTHER = "Other";
*/
	
	public static String MENU_START = I18N.get("mainmenu.start");
	public static String MENU_STOP = I18N.get("mainmenu.stop");
	public static String MENU_SETTINGS = I18N.get("mainmenu.settings");
//	public static String MENU_RESET = "Сброс";
	public static String MENU_RELOAD = I18N.get("mainmenu.reload");
	public static String MENU_MODE = I18N.get("mainmenu.mode");
	public static String MENU_DICTS = I18N.get("mainmenu.dicts");
	public static String MENU_INFO = I18N.get("mainmenu.info");
	public static String MENU_ABOUT = I18N.get("mainmenu.about");
	public static String MENU_HELP = I18N.get("mainmenu.help");
	public static String MENU_EXIT = I18N.get("mainmenu.quit");
	
	public static String MENU_MODE_LEARN = I18N.get("mainmenu.mode.learn");
	public static String MENU_MODE_CONTROL = I18N.get("mainmenu.mode.control");
	
//	public static String MENU_OTHER = "Прочее";	
	private static CheckboxMenuItem miModeLearn;
	private static CheckboxMenuItem miModeControl;
	
	public static String MENU_TOOLS = I18N.get("mainmenu.tools");
	public static String MENU_TOOLS_MOBILE = I18N.get("mainmenu.tools.mobile");
	public static String MENU_TOOLS_PLAYER = I18N.get("mainmenu.tools.player");
	
	
	// TODO disable right click in menu

	private static ItemListener modeItemListener = new ItemListener() {
		@Override
		public void itemStateChanged(ItemEvent e) {
			String ps = e.paramString();
			Configuration cfg = Words.getConfiguration();
			if ( ps.indexOf(MENU_MODE_CONTROL) >= 0 ) {
				miModeControl.setState(true);
				miModeLearn.setState(false);
				cfg.learnViewmode = false;
				cfg.save();
				Words.updateCurrentMode(Words.isStarted(), false);
			} else if ( ps.indexOf(MENU_MODE_LEARN) >= 0 ) {				
				miModeControl.setState(false);
				miModeLearn.setState(true);				
				cfg.learnViewmode = true;
				cfg.save();
				Words.updateCurrentMode(Words.isStarted(), false);
			}
		}
	};
	

    private static ActionListener menuListener = new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
			String ps = e.paramString(); 
			if ( ps.indexOf(MENU_START) >= 0 ) {
				Words.updateCurrentMode(true, false);
			} else if ( ps.indexOf(MENU_STOP) >= 0 ) {
				Words.updateCurrentMode(false, false);
			} else if ( ps.indexOf(MENU_SETTINGS) >= 0 ) {
				Words.showSettinsWindow();
//			} else if ( ps.indexOf(MENU_RESET) >= 0 ) {
//				Words.resetDicts();
			} else if ( ps.indexOf(MENU_RELOAD) >= 0 ) {
				Words.init();
				Words.showInfoHint();
			} else if ( ps.indexOf(MENU_INFO) >= 0 ) {
				Words.showInfoHint();
			} else if ( ps.indexOf(MENU_ABOUT) >= 0 ) {
				Words.about();
			} else if ( ps.indexOf(MENU_HELP) >= 0 ) {
				try {
					java.awt.Desktop.getDesktop().browse(new URI(Words.URL_PAGE));
				} catch (Exception e1) {
				}				
			} else if ( ps.indexOf(MENU_DICTS) >= 0 ) {
				Words.showDictionaryWindow();
			} else if ( ps.indexOf(MENU_EXIT) >= 0 ) {
				System.exit(0);
			} else if ( ps.indexOf(MENU_TOOLS_MOBILE) >= 0 ) {
				Words.showMobileGenerator();
			} else if ( ps.indexOf(MENU_TOOLS_PLAYER) >= 0 ) {
				Words.showPlayerGenerator();
			}
		}
    };
    
    
	public TrayPopupMenu(String name) {
		super(name);
//		Menu mnuOthers = new Menu(MENU_OTHER);
		Menu mnuMode = new Menu(MENU_MODE);
		Menu mnuHelp = new Menu(MENU_HELP);
		Menu mnuTools = new Menu(MENU_TOOLS);
		
		add(MENU_START);
		add(MENU_STOP);
		add(MENU_INFO);
		addSeparator();
		add(mnuMode);
//		add(mnuOthers);
		add(MENU_RELOAD);
		add(MENU_DICTS);
		add(MENU_SETTINGS);
		add(mnuTools);
		addSeparator();
		add(mnuHelp);
		addSeparator();
		add(MENU_EXIT);

//		mnuOthers.add(MENU_RESET);
//		mnuOthers.add(MENU_RELOAD);
		//mnuOthers.add(MENU_DICTS);
		
		mnuHelp.add(MENU_ABOUT);
		mnuHelp.add(MENU_HELP);
		
		mnuTools.add(MENU_TOOLS_MOBILE);
		mnuTools.add(MENU_TOOLS_PLAYER);

		Configuration cfg = Words.getConfiguration();
		miModeLearn = new CheckboxMenuItem(MENU_MODE_LEARN, cfg.learnViewmode);
		miModeLearn.addItemListener(modeItemListener);
		miModeControl = new CheckboxMenuItem(MENU_MODE_CONTROL, !cfg.learnViewmode);
		miModeControl.addItemListener(modeItemListener);
		mnuMode.add(miModeLearn);
		mnuMode.add(miModeControl);


		addActionListener(menuListener);
//		mnuOthers.addActionListener(menuListener);
		mnuHelp.addActionListener(menuListener);
		mnuTools.addActionListener(menuListener);
		
		setMenuItemEnabled(MENU_START, false);

	}
	
    public void setMenuItemEnabled(String name, boolean enabled) {
    	for ( int i = 0; i < getItemCount(); i++ ) {
    		if ( name.equals(getItem(i).getLabel()) ) {
    			getItem(i).setEnabled(enabled);
    			return;
    		}
    	}
    }
	
    
	
	

}
