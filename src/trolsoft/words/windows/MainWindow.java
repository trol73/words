package trolsoft.words.windows;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Shape;
import java.awt.Toolkit;
import java.awt.TrayIcon.MessageType;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.font.FontRenderContext;
import java.awt.font.TextLayout;
import java.awt.geom.AffineTransform;
import java.awt.geom.Area;
import java.awt.geom.Rectangle2D;
import java.awt.geom.RoundRectangle2D;

import javax.swing.Box;
import javax.swing.JFrame;
import javax.swing.JWindow;


import trolsoft.dict.WordPair;
import trolsoft.dict.WordPair.LangType;
import trolsoft.dict.WordPair.WordNumber;
import trolsoft.utils.I18N;
import trolsoft.utils.Utils;
import trolsoft.words.Configuration;
import trolsoft.words.WordClickListener;
import trolsoft.words.Words;


public class MainWindow extends JWindow implements WindowListener {
	
	private static final long serialVersionUID = 1L;
	
	private WordPair pair;
	private WordPair mixedPair;
	private int windowY;

	private Font fontEngl;		// TODO
	private Font fontRus;		// TODO
	private Font fontTrans;		// TODO dupplication from configuratio !n
	private Color colorEngl;	// TODO
	private Color colorRus;		// TODO
	private Color colorEnglAlt;	// TODO
	private Color colorRusAlt;	// TODO
	private Color colorTrans;	// TODO
	
	private boolean textVisible1, textVisible2;
	
	private boolean drawBackground;
	private Color backgroundColor;
	
	
	private Point posWord1, posWord2;
	
	private Box pnlCenter;

	private WordClickListener wordClickListener;
	
	private final int END = 0;
	private final int WORD = 1;
	private final int TRANCSCRIPTION = 2;
	
	private MouseListener labelMouseListener = new MouseListener() {

		@Override
		public void mouseClicked(MouseEvent e) {
			if ( wordClickListener != null ) {
				int word = -1;
				if ( e.getY() >= getHeight()/2 ) {
					word = 1;
				} else {
					word = 0;
				}
				wordClickListener.onClick(word, pair);
			}
		}

		@Override
		public void mouseEntered(MouseEvent e) {
		}

		@Override
		public void mouseExited(MouseEvent e) {
		}

		@Override
		public void mousePressed(MouseEvent e) {
		}

		@Override
		public void mouseReleased(MouseEvent e) {
		}

	};

	static {
		JFrame.setDefaultLookAndFeelDecorated(true);
	}



	public MainWindow() {
		super();
		
		textVisible1 = false;
		textVisible2 = false;

		addMouseListener(labelMouseListener);

		pnlCenter = Box.createVerticalBox();
	
		add(pnlCenter, BorderLayout.CENTER);

		addWindowListener(this);
		setAlwaysOnTop(true);
	}
	
	private void setBackground() {
		getContentPane().setBackground(drawBackground ? backgroundColor : colorEngl);
	}
	
	private Shape getTextShape(String str, Font font, AffineTransform t) {
		Graphics2D g2d = (Graphics2D)this.getGraphics();
		FontRenderContext frc = g2d.getFontRenderContext();
		if ( str == null || str.length() == 0 ) {
			str = " ";
		}
		TextLayout tl = new TextLayout(str, font, frc); 
		return tl.getOutline(t); 
	}
	
	
	private void updateSize(int y) {
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		int width = screenSize.width;
		int heightEn = getFontHeight(fontEngl);
		int heightRu = getFontHeight(fontRus);
		int heightTr = getFontHeight(fontTrans);
		int height = heightEn > heightRu ? heightEn : heightRu;
		if ( heightTr > height ) {
			height = heightTr;
		}
		height = height*2 + 10;
		int locX = 0;
		int locY = y;
		if ( locY < 0 ) {
			locY = screenSize.height + locY;
		}
		setLocation(locX, locY);
		setSize(width, height);
	}
	
	/**
	 * Возвращает объект области для фразы, состоящей из слов и транскрипций
	 * 
	 * @param wordNum
	 * @return
	 */
	private Shape getWordShape(WordNumber wordNum) {
		return getWordShape(wordNum, 0, 0);
	}
	
	
private static boolean debug = false;	
	/**
	 * Возвращает объект области для фразы, состоящей из слов и транскрипций, с переносом ее в указанные координаты
	 *  
	 * @param wordNum
	 * @param x
	 * @param y
	 * @return
	 */
	private Shape getWordShape(WordNumber wordNum, int x, int y) {
		if ( pair == null ) {
			return new Rectangle2D.Double(-1, -1, 1, 1);
		}
		String word = pair.getWord(wordNum);
		if ( word == null || word.length() == 0 ) {
System.out.println("[!!! EMPTY !!!] " + wordNum + " - " + pair.wordInMyLang + "/" + pair.wordInLearnLang );			
			return new Rectangle2D.Double(-1, -1, 1, 1);
		}
		Font fntText = pair.getLangType(wordNum) == LangType.Learn ? fontEngl : fontRus;
		
		Area area = new Area();
		
		int index = 0;
		while ( splitWordArray[wordNum.ordinal()][index] != END ) {
			int type = splitWordArray[wordNum.ordinal()][index++];
			int begin = splitWordArray[wordNum.ordinal()][index++];
			int end = splitWordArray[wordNum.ordinal()][index++];
			
			if ( end > word.length() ) {
				System.out.println("[!!!] 188: " + word + " " + wordNum + " -> " + type + " " + begin + " " + end);
				debug=true;
				splitWords(wordNum);
				index -= 3;
				type = splitWordArray[wordNum.ordinal()][index++];
				begin = splitWordArray[wordNum.ordinal()][index++];
				end = splitWordArray[wordNum.ordinal()][index++];
				System.out.println("[!!!] FATAL 194 => " + word + " " +  begin + "   " + end + "           " + word.length());
				debug=false;
			}
String s;
try {
			//String
			s = word.substring(begin, end);
} catch ( Exception e ) {
	System.out.println("begin, end   len   " + begin + "   " + end + "           " + word.length());
	e.printStackTrace();
	s = "";
}
			Font fnt = type == WORD ? fntText : fontTrans;
			
			AffineTransform transform = new AffineTransform();
			transform.setToTranslation(x, y);
			Shape sh = getTextShape(s, fnt, transform);
			Area a = new Area(sh);
			area.add(a);
			x += a.getBounds().width;
		}
		return area;
	}
	
	
	/**
	 * Создает область для отображения слова с учетом режима отображения и добавляет ее к указанной области
	 * 
	 * @param wordNum
	 * @param area
	 * @param y
	 * @return
	 */
	private Point appendShape(WordNumber wordNum, Area area, int y) {
		if ( pair == null ) {
			return new Point();
		}
		String word = pair.getWord(wordNum);
		boolean visible = wordNum == WordNumber.First ? textVisible1 : textVisible2;
		if ( word == null || word.length() == 0 || !visible ) {
			return new Point();
		}

		Shape shape = getWordShape(wordNum);
		int textX;
		switch ( Words.getConfiguration().uiLayoutX ) {
			case 0:				// Left
				textX = 16;
				break;
			case 1:				// Center
				textX = (getWidth() - shape.getBounds().width)/2;
				break;
			case 2:				// Right
				textX = getWidth() - shape.getBounds().width - 16;				
				break;
			default:
				textX = 0;
		
		}
		int textY = y;
		Point result = new Point(textX, textY - shape.getBounds().y + 4);
		if ( drawBackground ) {
			int dw = word.indexOf('[') >= 0 ? 26 : 16;
			shape = new RoundRectangle2D.Double(textX-8, textY, shape.getBounds().width+dw, shape.getBounds().height+8, 20, 20);
		} else {
			shape = getWordShape(wordNum, textX-shape.getBounds().x, y-shape.getBounds().y);
		}
		area.add(new Area(shape));
		return result;
	}
	



	private void setWindowShape() {
		Configuration cfg = Words.getConfiguration();
		Area area;
		if ( Utils.isWindows && !cfg.uiBackgroundDraw ) {
			area = new Area(new Rectangle2D.Double(0, 0, getWidth(), getHeight()));
		} else {
			area = new Area(new Rectangle2D.Double(-1, -1, 1, 1));
			posWord1 = appendShape(WordNumber.First, area, 0);
			posWord2 = appendShape(WordNumber.Second, area, getHeight()/2);
		}
		com.sun.awt.AWTUtilities.setWindowShape(this, area);
	}


	public void setTextVisible1(boolean visible) {
		textVisible1 = visible;
		setWindowShape();
		repaint();
	}

	public void setTextVisible2(boolean visible) {
		textVisible2 = visible;
		setWindowShape();
		repaint();
	}
	
	public void setTextVisible(boolean visible1, boolean visible2) {
		textVisible1 = visible1;
		textVisible2 = visible2;
		setWindowShape();
		repaint();
	}

	/**
	 * Инициализирует значения параметрами конфигурации
	 */
	public void init() {
		Configuration cfg = Words.getConfiguration();				
		fontEngl = cfg.uiFontEngl;
		fontRus = cfg.uiFontRus;
		fontTrans = cfg.uiFontTranscription;
		colorEngl = new Color(cfg.uiColorEngl);
		colorEnglAlt = new Color(cfg.uiColorEnglAlt);
		colorRus = new Color(cfg.uiColorRus);
		colorRusAlt = new Color(cfg.uiColorRusAlt);
		colorTrans = new Color(cfg.uiColorTranscription);
		backgroundColor = new Color(cfg.uiBackgroundColor);
		drawBackground = cfg.uiBackgroundDraw;
		windowY = cfg.uiPosY;
		setBackground();
		updateSize(windowY);
		setWindowShape();
		try {
			float opacity = 1.0f - 1.0f*cfg.uiTransparency/100.0f;
			if ( opacity < 0 ) {
				opacity = 0;
			}
			com.sun.awt.AWTUtilities.setWindowOpacity(this, opacity);
		} catch ( Exception e ) {
		}
		// для Windows можно отключить прозрачность, если фон под словами не закрашивается
		if ( Utils.isWindows ) {  
			try {
				com.sun.awt.AWTUtilities.setWindowOpaque(this, cfg.uiBackgroundDraw);
			} catch ( Exception ex ) {
				ex.printStackTrace();
			}
		}
		setVisible(true);
	}


	@SuppressWarnings("deprecation")
	private int getStringWidth(String s, Font fnt) {
		return Toolkit.getDefaultToolkit().getFontMetrics(fnt).stringWidth(s);
	}
	
	@SuppressWarnings("deprecation")
	private int getFontHeight(Font fnt) {
		return Toolkit.getDefaultToolkit().getFontMetrics(fnt).getHeight();
	}



	
	/**
	 * Рисует слово с учетом того, что оно может содержать транскрипции 
	 * @param g
	 * @param wordNum  1 or 2
	 * @param x
	 * @param y
	 */
	private void drawWord(Graphics g, WordNumber wordNum, int x, int y) {
		Font fntText;
		Color clrText;
		Color clrTextAlt;
		if ( pair == null ) {
			return;
		}
		if ( pair.getLangType(wordNum) == LangType.Learn ) {
			fntText = fontEngl;
			clrText = colorEngl;
			clrTextAlt = colorEnglAlt;
		} else {
			fntText = fontRus;
			clrText = colorRus;
			clrTextAlt = colorRusAlt;
		}			
		
		String word = pair.getWord(wordNum);
		int index = 0;
		if ( !word.equals(splitWordWords[wordNum.ordinal()]) ) {	// TODO
			splitWords(wordNum);
		}
		boolean evenWord = true;
		while ( splitWordArray[wordNum.ordinal()][index] != END ) {
			int type = splitWordArray[wordNum.ordinal()][index++];
			int begin = splitWordArray[wordNum.ordinal()][index++];
			int end = splitWordArray[wordNum.ordinal()][index++];
			
			String s;
			try {
				s = word.substring(begin, end);
			} catch ( Exception e ) {
				System.out.println("[!!!] " + word + ": "+ type + " " + begin + " " + end + " " + word.length());
				// sour ['sauə]		2 6 13
				// vote [vəut]: 2 6 13 11
				// sit [sɪt]: 2 5 11 9
				// bore [bɔː]: 2 13 33 10
				// plant [plɑːnt]: 2 7 15 14
				// then [ðen]: 2 5 15 10
				// loan [ləun]: 2 9 19 11
				
				return;
			}
			
			Color clr;
			Font fnt;
			if ( type == WORD ) {
				clr = evenWord ? clrText : clrTextAlt;
				fnt = fntText;
				evenWord = !evenWord;
			} else {
				clr = colorTrans;
				fnt = fontTrans;
			}
			g.setColor(clr);
			g.setFont(fnt);

			g.drawString(s, x, y);
			x += getStringWidth(s, fnt);
		}
	}
	
	
	/**
	 * Закрашивает область слова. Используется в линуксе при отключенной даливки фона
	 * 
	 * @param g
	 * @param wordNum  1 or 2
	 * @param windowY
	 */
	private void fillWord(Graphics g, WordNumber wordNum, int x) {
		Font fntText;
		Color clrText;
		if ( pair.getLangType(wordNum) == LangType.Learn ) {
			fntText = fontEngl;
			clrText = colorEngl;
		} else {
			fntText = fontRus;
			clrText = colorRus;
		}
		int h = getHeight()/2;
		int y = wordNum == WordNumber.First ? 0 : h;
		
		String word = pair.getWord(wordNum);
		if ( !word.equals(splitWordWords[wordNum.ordinal()]) ) {
			splitWords(wordNum);
		}
		
		int index = 0;
		while ( splitWordArray[wordNum.ordinal()][index] != END ) {
			int type = splitWordArray[wordNum.ordinal()][index++];
			int begin = splitWordArray[wordNum.ordinal()][index++];
			int end = splitWordArray[wordNum.ordinal()][index++];

			String s;
			try {
				s = word.substring(begin, end);
			} catch ( Exception e ) {
				System.out.println("[!!!-2] " + word + ": "+ type + " " + begin + " " + end + " " + word.length());
				// sour ['sauə]		2  6  13
				// ear [ɪə]: 		2  8  19  8
				// vote [vəut]: 	2  6  13  11
				// sit [sɪt]: 		2  5  11  9
				// bore [bɔː]: 		2  13 33  10
				// plant [plɑːnt]:  2  7  15  14
				// then [ðen]:      2  5  15  10
				// loan [ləun]:     2  9  19  11				
				return;
			}

			Color clr;
			Font fnt;
			if ( type == WORD ) {
				clr = clrText;
				fnt = fntText;
			} else {
				clr = colorTrans;
				fnt = fontTrans;
			}
			g.setColor(clr);
			int w = getStringWidth(s, fnt);
			g.fillRect(x, y, w, h);
			x += w;
		}	
	}
	
	
	@Override
	public void paint(Graphics g) {
		if ( drawBackground ) {
			g.setColor(backgroundColor);
			g.fillRect(0, 0, getWidth(), getHeight());
			if ( textVisible1 ) {
				drawWord(g, WordNumber.First, posWord1.x, posWord1.y);
			}
			if ( textVisible2 ) {
				drawWord(g, WordNumber.Second, posWord2.x, posWord2.y);
			}
		} else {
			if ( textVisible1 ) {
				fillWord(g, WordNumber.First, posWord1.x);
			}
			if ( textVisible2 ) {
				fillWord(g, WordNumber.Second, posWord2.x);
			}
		}
	}


	@Override
	public void windowActivated(WindowEvent e) {
	}

	@Override
	public void windowClosed(WindowEvent e) {
	}

	@Override
	public void windowClosing(WindowEvent e) {
		System.exit(0);
	}

	@Override
	public void windowDeactivated(WindowEvent e) {
	}

	@Override
	public void windowDeiconified(WindowEvent e) {
	}

	@Override
	public void windowIconified(WindowEvent e) {
	}

	@Override
	public void windowOpened(WindowEvent e) {
	}


	public WordClickListener getWordClickListener() {
		return wordClickListener;
	}


	public void setWordClickListener(WordClickListener wordClickListener) {
		this.wordClickListener = wordClickListener;
	}

	
	private int[][] splitWordArray = new int[2][100];	// TODO !!!
	private String[] splitWordWords = new String[2];
	
	/**
	 * Парсит строку вида "word1 [transcription1]; word2 [transcription2]", выделяя в ней слова и их типы 
	 * (WORD|TRANSCRIPTION). в конце массива пишет END
	 * заполняет массив тройками цифр [тип; смещение начала; смещение конца]
	 * 
	 * @param word
	 */	
	private void splitWords(WordPair.WordNumber wordNum) {
		String word = pair.getWord(wordNum);
if (debug) System.out.println("  : " + word + "   " + wordNum);
		splitWordWords[wordNum.ordinal()] = word;
		int len = word.length();
		int arrayPos = 0;		
		if ( word == null || len == 0 ) {
			splitWordArray[wordNum.ordinal()][0] = END;
//if (debug) System.out.println("  : -> 1");
			return;
		}
		int pos = 0;
		splitWordArray[wordNum.ordinal()][arrayPos++] = word.charAt(0) == '[' ? TRANCSCRIPTION : WORD; 
		splitWordArray[wordNum.ordinal()][arrayPos++] = 0;
		pos++;

		while ( pos < word.length() ) {
			int posB = word.indexOf('[', pos);
			int posE = word.indexOf(']', pos);
//if (debug) System.out.println("  : ? " + posB + "   " + posE);			
			if ( posB > 0 && posB < posE) {	// начало транскрипции
				splitWordArray[wordNum.ordinal()][arrayPos++] = posB;	// "закрываем" предыдущее слово
				splitWordArray[wordNum.ordinal()][arrayPos++] = TRANCSCRIPTION;
				splitWordArray[wordNum.ordinal()][arrayPos++] = posB;
				pos = posB+1;
			} else if ( posE > 0 ) {		// конец транскрипции
				pos = posE < len ? posE+1 : len;
				splitWordArray[wordNum.ordinal()][arrayPos++] = pos;	// "закрываем" предыдущее слово
				if ( pos == len ) {
					splitWordArray[wordNum.ordinal()][arrayPos++] = END;
//if (debug) System.out.println("  : -> 2 "+ (arrayPos-2)  + "   " + len + "  " + END);
//if (debug) for (int i = 0; i < arrayPos; i++) System.out.println(" "+ i + "-" + splitWordArray[wordNum][i]);
					return;
				}
				splitWordArray[wordNum.ordinal()][arrayPos++] = WORD;
				splitWordArray[wordNum.ordinal()][arrayPos++] = pos;
			} else {						// конец фразы
				splitWordArray[wordNum.ordinal()][arrayPos++] = len;	// "закрываем" последнее слово
				splitWordArray[wordNum.ordinal()][arrayPos++] = END;
//if (debug) System.out.println("  : -> 3 !!! " + (arrayPos-2)  + "   " + len + "  " + END);
//if (debug) for (int i = 0; i < arrayPos; i++) System.out.println(" "+ i + "-" + splitWordArray[wordNum][i]);
				return;
			}
		}
		if ( pos == 1 ) {
			splitWordArray[wordNum.ordinal()][arrayPos++] = word.length(); 
			splitWordArray[wordNum.ordinal()][arrayPos] = END;
		}
//if (debug) System.out.println("  : !!!!!!!!!!!!!!!!! " + arrayPos);
if (debug) for (int i = 0; i < arrayPos; i++) System.out.println(" "+ i + "-" + splitWordArray[wordNum.ordinal()][i]);
	}
	
	
	/**
	 * Возвращает слово, из которого удалены все транскрипции заключенные в []
	 * @param word
	 * @return
	 */
	private static String deleteTranscription(String word) {
		while ( true ) {
			int posB = word.indexOf('[');
			int posE = word.indexOf(']');
			if ( posB < 0 || posE < 0 || posB > posE ) {
				break;
			}
			String s1 = posB > 0 ? word.substring(0, posB) : "";
			String s2 = posE < word.length()-1 ? word.substring(posE+1) : "";
			word = s1 + s2;
		}
		return word;
	}
	
	
	/**
	 * Перемешивает строки в массиве
	 * 
	 * @param words
	 * @return
	 */
	private static String[] mixWords(String[] words) {
		int len = words.length;
		if ( len < 2 ) {
			return words;
		}
		for ( int i = 0; i < len; i++ ) {
			int i1 = Utils.random(len);
			int i2 = Utils.random(len);
			if ( i1 != i2 ) {
				String t = words[i1];
				words[i1] = words[i2];
				words[i2] = t;
			}
		}
		return words;
	}
	
	
	/**
	 * Форматирует слово перед выводом, добавляя к нему транскрипцию, если это необходимо
	 * 
	 * @param pair
	 * @param wordNum
	 * @return
	 */
	private String getOutputText(WordPair pair, WordNumber wordNum) {
		if ( pair == null ) {
			return "";
		}
		Configuration cfg = Words.getConfiguration();
		StringBuffer sb = new StringBuffer();
		boolean eng = pair.getLangType(wordNum) == LangType.Learn;
		
		String[] wordsList = pair.getWords(wordNum);
		if ( wordNum == WordNumber.First ) {
			mixedPair = new WordPair(pair);
		}
		if ( cfg.learnWordsMix && wordsList.length > 1 ) {
			wordsList = mixWords(wordsList);
			StringBuffer mixed = new StringBuffer();
			for ( String w : wordsList ) {
				mixed.append(w);
				mixed.append(';');
			}
			mixedPair.setWord(wordNum, mixed.toString());
		}
		if ( eng ) {
			// удаляем транскрипции, если надо
			if ( cfg.learnTranscriptionDelete ) {
				for ( int i = 0; i < wordsList.length; i++ ) {
					wordsList[i] = deleteTranscription(wordsList[i]);
				}
			}
			// добавляем транскрипцию из словаря, если надо
			if ( cfg.learnTranscriptionShow ) {
				// TODO move into separated method
				for ( int i = 0; i < wordsList.length; i++ ) {
					String word = wordsList[i];
					String transcription = Words.getDictTranscription().get(word);
					sb.append(word);
					if ( transcription != null && transcription.length() > 0 ) {						
						sb.append(' ');
						if ( transcription.charAt(0) != '[' ) {
							sb.append('[');
						}
						sb.append(transcription);
						if ( transcription.charAt(transcription.length()-1) != ']' ) {
							sb.append("]");
						}
					}
					if ( i < wordsList.length-1 ) {
						sb.append(';');
						sb.append(' ');
					}
				} // for
				return sb.toString();
			} // cfg.learnTranscriptionShow
		} // if eng
		for ( int i = 0; i < wordsList.length; i++ ) {
			String word = wordsList[i];
			sb.append(word);
			if ( i < wordsList.length-1 ) {
				sb.append(';');
				sb.append(' ');
			}
		}
		return sb.toString();
	}
	
	
	/**
	 * Извлекает очередную пару слов из словаря и делает ее текущей
	 *  
	 * @return
	 */
	public WordPair extractNewPair() {
		WordPair p = Words.getDictLearn().getRandomPair();
		if ( p == null ) {
			Words.message(I18N.get("message.wordsIsOver"), MessageType.INFO);	// TODO i18n
			Words.updateCurrentMode(false, false);
			setTextVisible1(false);
			setTextVisible2(false);
		} else {			
			pair = new WordPair(getOutputText(p, WordNumber.First), getOutputText(p, WordNumber.Second), p.direction);
			splitWords(WordNumber.First);
			splitWords(WordNumber.Second);
			setWindowShape();
			repaint();
		}
		Words.getTimerTask().lastPair = p;
		return p;
	}


	/**
	 * Возвращает пару слов на экране после возможно выполненного перемешивания 
	 * @return
	 */
	public WordPair getMixedPair() {
		return mixedPair;
	}

}
