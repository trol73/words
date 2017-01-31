package trolsoft.words;

import java.awt.Image;

import trolsoft.utils.Utils;
import trolsoft.words.general.Lang;

public class Resources {
	private static Image imgStart;
	private static Image imgPause;
	private static Image imgAdd;
	private static Image imgDel;
	private static Image imgEdit;
	private static Image imgSound;
	private static Image imgSearch;
	private static Image imgWait;
	private static Image imgDict;
	private static Image imgSettings;
	private static Image imgFont;
	private static Image imgInfo;
	private static Image imgFile;
	private static Image imgFileOpen;
	private static Image imgColor;
	private static Image imgMobile;
	
	private static Image[] imgFlags;
	
	
	private static final Image createImage(String fileName) {
		return Utils.createImageFromJar("res/" + fileName);
	}
	
	public static final Image imgStart() {
		if ( imgStart == null ) {
			imgStart = createImage("play.png");
		}
		return imgStart;
	}
	
	
	public static final Image imgPause() {
		if ( imgPause == null ) {
			imgPause = createImage("pause.png");
		}
		return imgPause;
	}
	
	
	public static final Image imgAdd() {
		if ( imgAdd == null ) {
			imgAdd = createImage("add.png");
		}
		return imgAdd;
	}
	
	
	public static final Image imgDel() {
		if ( imgDel == null ) {
			imgDel = createImage("del.png");
		}
		return imgDel;
	}
	
	
	public static final Image imgEdit() {
		if ( imgEdit == null ) {
			imgEdit = createImage("edit.png");
		}
		return imgEdit;
	}
	
	
	public static final Image imgSound() {
		if ( imgSound == null ) {
			imgSound = createImage("sound.png");
		}
		return imgSound;
	}
	
	
	public static final Image imgSearch() {
		if ( imgSearch == null ) {
			imgSearch = createImage("search.png");
		}
		return imgSearch;
	}
	
	public static final Image imgWait() {
		if ( imgWait == null ) {
			imgWait = createImage("wait.png");
		}
		return imgWait;
	}
	
	public static final Image imgDict() {
		if ( imgDict == null ) {
			imgDict = createImage("dict.png");
		}
		return imgDict;
	}
	
	public static final Image imgSettings() {
		if ( imgSettings == null ) {
			imgSettings = createImage("settings.png");
		}
		return imgSettings;
	}
	
	public static final Image imgFont() {
		if ( imgFont == null ) {
			imgFont = createImage("font.png");
		}
		return imgFont;
	}
	
	public static final Image imgInfo() {
		if ( imgInfo == null ) {
			imgInfo = createImage("info.png");
		}
		return imgInfo;
	}
	
	public static final Image imgFile() {
		if ( imgFile == null ) {
			imgFile = createImage("file.png");
		}
		return imgFile;
	}	
	
	public static final Image imgFileOpen() {
		if ( imgFileOpen == null ) {
			imgFileOpen = createImage("fileopen.png");
		}
		return imgFileOpen;
	}
	
	public static final Image imgColor() {
		if ( imgColor == null ) {
			imgColor = createImage("color.png");
		}
		return imgColor;
	}
	
	public static final Image imgMobile() {
		if ( imgMobile == null ) {
			imgMobile = createImage("mobile.png");
		}
		return imgMobile;
	}	

	public static final Image imgFlag(Lang lang) {
		if (imgFlags == null) {
			imgFlags = new Image[Lang.values().length];
			for ( Lang l : Lang.values() ) {
				imgFlags[l.ordinal()] = createImage("flags/" + l.getShortName() + ".png");
			}
		}
		return imgFlags[lang.ordinal()];
	}
	
}
