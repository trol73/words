package trolsoft.words.windows;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.StringTokenizer;

import javax.swing.BorderFactory;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.SwingWorker;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import trolsoft.dict.HashDictionary;
import trolsoft.dict.PairDictionary;
import trolsoft.dict.WordPair;
import trolsoft.sound.WordsPlayer;
import trolsoft.ui.StatusBar;
import trolsoft.ui.ToolBar;
import trolsoft.ui.Window;
import trolsoft.utils.I18N;
import trolsoft.utils.Utils;
import trolsoft.words.Configuration;
import trolsoft.words.Resources;
import trolsoft.words.Words;



public class WindowDict extends Window implements ActionListener {

	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	
	private static final String _TITLE = I18N.get("dialog.dict.title");
	private static final String _ADD_WORD = I18N.get("dialog.dict.addWord");	
	private static final String _DEL_WORD = I18N.get("dialog.dict.delWord");
	private static final String _EDIT_WORD = I18N.get("dialog.dict.editWord");
	private static final String _PLAY_WORD = I18N.get("dialog.dict.playWord");
	private static final String _FIND_TRANSLATE_WORD = I18N.get("dialog.dict.findTranslate");
	private static final String _WORDS_COUNT = I18N.get("dialog.dict.totalWords");
	private static final Object _DELETE_WORD_CONFIRM = I18N.get("dialog.dict.deleteWordConfirm");
	private static final String _DICT = I18N.get("dialog.dict.dict");



	
	private static final Color COLOR_EDITABLE_AREA = new Color(0xccccff);
	

	class WordsTextArea extends JTextArea {
		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		private Color defaultBackground = null;

		public WordsTextArea() {
			super(5, 10);
		}

		@Override
		public void setEditable(boolean editable) {
			if ( defaultBackground == null ) {
				defaultBackground = getBackground();
			}
			super.setEditable(editable);
			if ( defaultBackground != null ) {
				setBackground(editable ? COLOR_EDITABLE_AREA : defaultBackground);
			}
		}
	}
	
	private static final String CMD_ADD = "add";
	private static final String CMD_DEL = "del";
	private static final String CMD_EDIT = "edit";
	private static final String CMD_PLAY = "play";
	private static final String CMD_FIND = "find";


	private JList<String> lstDicts;
	private JList<String> lstWords;
	private JTextField edtWord;
	private JTextArea edtText;
	private PairDictionary dict = new PairDictionary();

	private JButton btnAdd;
	private JButton btnDel;
	private JButton btnEdit;
	private JButton btnPlay;
	private JButton btnFind;

	private DefaultListModel<String> modelDicts = new DefaultListModel<String>();
	private DefaultListModel<String> modelWords = new DefaultListModel<String>();
	private boolean dictLoading = false;
	
	private List<String> dictFileNames = new ArrayList<String>();
	private StatusBar statusBar;



	public WindowDict() {
		super(_TITLE);
		
		//setResizable(false);
		setIconImage(Resources.imgDict());

//		Container cp = getContentPane();

		//GridBagLayout layout = new GridBagLayout();
//		BorderLayout layout = new BorderLayout();

//		cp.setLayout(layout);
		
//		GridBagConstraints c = new GridBagConstraints();

		lstDicts = new JList<String>(modelDicts);
		lstWords = new JList<String>(modelWords);
		edtWord = new JTextField();
		edtText = new WordsTextArea();

		lstDicts.setVisibleRowCount(15);
		lstWords.setVisibleRowCount(15);
		edtText.setFont(edtWord.getFont());

		lstDicts.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		lstWords.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);


		lstDicts.addListSelectionListener(new ListSelectionListener() {
			@Override
			public void valueChanged(ListSelectionEvent e) {
				if ( e.getValueIsAdjusting() ) {
					// покидаем старый словарь
					updateButtonsEnabled();
					updateStatusLine();
				} else {
					// открываем новый словарь
					fillWordsList();
					updateButtonsEnabled();
				}
			}
		});


		lstWords.addListSelectionListener(new ListSelectionListener() {
			@Override
			public void valueChanged(ListSelectionEvent e) {
				if ( !lstWords.isSelectionEmpty() ) {
					fillWordText();
					edtWord.setText((String)lstWords.getSelectedValue());
				}
				updateButtonsEnabled();
			}
		});


		edtWord.getDocument().addDocumentListener(new DocumentListener() {
			@Override
			public void changedUpdate(DocumentEvent e) {
				onWord1Changed();
			}

			@Override
			public void insertUpdate(DocumentEvent e) {
				onWord1Changed();
			}

			@Override
			public void removeUpdate(DocumentEvent e) {
				onWord1Changed();
			}
		});

		JScrollPane spDicts = new JScrollPane(lstDicts);
		JScrollPane spWords = new JScrollPane(lstWords);
		JScrollPane spText = new JScrollPane(edtText);

		spDicts.setPreferredSize(new Dimension(220, 150));
		spWords.setPreferredSize(new Dimension(200, 200));
		spText.setPreferredSize(new Dimension(240, 150));

		ToolBar toolbar = new ToolBar();
		toolbar.setActionListener(this);
		btnAdd = toolbar.addButton(CMD_ADD, Resources.imgAdd(), _ADD_WORD);
		btnDel = toolbar.addButton(CMD_DEL, Resources.imgDel(), _DEL_WORD);
		btnEdit = toolbar.addButton(CMD_EDIT, Resources.imgEdit(), _EDIT_WORD);
		btnPlay = toolbar.addButton(CMD_PLAY, Resources.imgSound(), _PLAY_WORD);
		btnFind = toolbar.addButton(CMD_FIND, Resources.imgSearch(), _FIND_TRANSLATE_WORD);
		
		
		statusBar = new StatusBar();
		
	
		add(toolbar, BorderLayout.PAGE_START);
		add(statusBar, BorderLayout.PAGE_END);
		
//		Box boxDicts = Box.createVerticalBox();
//		boxDicts.setAlignmentX(Component.LEFT_ALIGNMENT);
//		boxDicts.add(lblDicts);
//		boxDicts.add(spDicts);
		add(createHorisontalBox(_TITLE, spDicts), BorderLayout.LINE_START);
		
		
		add(createVerticalBox(edtWord, spWords), BorderLayout.CENTER);
		add(spText, BorderLayout.LINE_END);
		spText.setBorder(BorderFactory.createEmptyBorder(7, 10, 7, 10));
		

		fillDictsList();
		lstDicts.setSelectedIndex(0);

		pack();
		edtWord.setMaximumSize(new Dimension(800, edtWord.getHeight()));
		updateButtonsEnabled();
	}

	/**
	 * 
	 * @return
	 */
	private String getDictFileName() {
		int index = lstDicts.getSelectedIndex();
		if ( index < 0 ) {
			return null;
		}
		return dictFileNames.get(index);
	}


	/**
	 * 
	 * @return
	 */
	private PairDictionary getDict() {
		String fileName = getDictFileName();
		if ( fileName == null ) {
			return null;
		}
		PairDictionary dict = new PairDictionary();
		if ( !dict.load(fileName) ) {
//			return null;
		}
		dict.sort();
		return dict;
	}
	
	/**
	 * Добавляет словарь в список
	 * 
	 * @param title
	 * @param fileName
	 */
	private void addDictToList(String title, String fileName) {
		modelDicts.addElement(title);
		dictFileNames.add(fileName);
	}


	/**
	 * Заполнение списка словарей
	 */
	private void fillDictsList() {
		modelDicts.clear();
		dictFileNames.clear();
		Configuration cfg = Words.getConfiguration();
		
		// добавляем словари изучаемых слов
		for ( int i = 0; i < cfg.dictsLearn.length; i++ ) {
			String fn = cfg.dictsLearn[i];
			addDictToList("<html><b>" + new File(fn).getName(), fn);
		}
		
		// добавляем общие словари
		for ( int i = 0; i < cfg.dictsAll.length; i++ ) {
			String fn = cfg.dictsAll[i];
			addDictToList("[" + new File(fn).getName() + "]", fn);
		}		
		
		// добавляем словари транскрипций
		for ( int i = 0; i < cfg.dictsTranscriptions.length; i++ ) {
			String fn = cfg.dictsTranscriptions[i];
			addDictToList("*" + new File(fn).getName() + "*", fn);
		}		
		
		// добавляем все остальные словари из директории программы
		File[] files = new File(Configuration.getRootPath()).listFiles();

		for ( int i = 0; i < files.length; i++ ) {
			String fn = files[i].getAbsolutePath();
			String name = fn.toLowerCase();
			if ( files[i].isFile() && name.length() > 4 && name.indexOf(".dic") == name.length()-4 ) {
				if ( !isLearnDict(fn) && !isAllDict(fn) && !isTranscriptionDict(fn) ) {
					addDictToList("<html><i>" + files[i].getName(), fn);
				}
			}
		}
	}
	
	
	/**
	 * Проверяет, является ли файл словарем для изучения
	 * 
	 * @param fileName
	 * @return
	 */
	private boolean isLearnDict(String fileName) {
		Configuration cfg = Words.getConfiguration();
		for ( String fn : cfg.dictsLearn ) {
			if ( Utils.isEqualFileNames(fn, fileName) ) {
				return true;
			}
		}
		return false;
	}
	
	
	/**
	 * Проверяет, является файл файлом из общих словарев
	 * 
	 * @param fileName
	 * @return
	 */
	private boolean isAllDict(String fileName) {
		Configuration cfg = Words.getConfiguration();
		for ( String fn : cfg.dictsAll ) {
			if ( Utils.isEqualFileNames(fn, fileName) ) {
				return true;
			}
		}
		return false;
	}

	/**
	 * Проверяет, является файл файлом транскрипции
	 * 
	 * @param fileName
	 * @return
	 */
	private boolean isTranscriptionDict(String fileName) {
		Configuration cfg = Words.getConfiguration();
		for ( String fn : cfg.dictsTranscriptions ) {
			if ( Utils.isEqualFileNames(fn, fileName) ) {
				return true;
			}
		}
		return false;
	}
	
	
	/**
	 * Обновляет статусную строку
	 */
	private void updateStatusLine() {
		if ( lstDicts.getSelectedIndex() < 0 || dict == null ) {
			statusBar.setText("");
		} else {
			statusBar.setText(_WORDS_COUNT + ": " + dict.size());
		}
	}

	
	/**
	 * 
	 */
	private void fillWordsList() {
		/*
		 * Бага в swing-е - если при заполнении большого списка выбран
		 * первый элемент, то будут страшные тормоза
		 */		
		
		final boolean firstItemWasSelected = lstWords.getSelectedIndex() == 0;
		final String oldWord = edtWord.getText();
		
		if ( firstItemWasSelected ) {
			new SwingWorker<Void, Void>() {
				@Override
				protected Void doInBackground() throws Exception {
					lstWords.setSelectedIndex(1);
					return null;
				}
			}.execute();
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		

		new SwingWorker<PairDictionary, Void>() {
			@Override
			protected PairDictionary doInBackground() throws Exception {
				dictLoading = true;
				edtText.setText("");
//				edtWord.setText("");
				enableAllItems(false);
				dict = getDict();
				updateStatusLine();
				return dict;
			}

			@Override
			protected void done() {
				if ( dict == null ) {
					modelWords.clear();
					dictLoading = false;
					enableAllItems(true);
					return;
				}
				lstWords.clearSelection();
				modelWords.clear();

				Iterator<WordPair> it = dict.iterator();
				modelWords.ensureCapacity(dict.size());
				while ( it.hasNext() ) {
					WordPair pair = it.next();
					modelWords.addElement(pair.wordInLearnLang);
				}
				if ( firstItemWasSelected ) {
					edtWord.setText(oldWord);
				}
				if ( edtWord.getText().length() > 0 ) {
					findAndFocusWordInList();
				} else {				
					lstWords.ensureIndexIsVisible(0);
					edtText.setText("");
				}
				enableAllItems(true);
				updateButtonsEnabled();
				dictLoading = false;
			}

		}.execute();
	}

	
	/**
	 * 
	 * @return
	 */
	private WordPair getCurrentPair() {
		int wordIndex = lstWords.getSelectedIndex();
		return wordIndex < 0 ? null : dict.getPair(wordIndex);
	}


	/**
	 * 
	 */
	private void fillWordText() {
		edtText.setEditable(false);
		WordPair pair = getCurrentPair();

		if ( pair == null ) {
			edtText.setText("");
			return;
		}
		String word2 = pair.wordInMyLang;
		StringTokenizer st = new StringTokenizer(word2, ";");
		StringBuffer text = new StringBuffer();
		while ( st.hasMoreTokens() ) {
			text.append(st.nextToken().trim()).append("\n");
		}
		edtText.setText(text.toString());
	}

	
	/**
	 * Ищет введенное слово в списке и фокусируется на нем
	 */
	private void findAndFocusWordInList() {
		edtText.setEditable(false);
		String word = edtWord.getText().toLowerCase();
		if ( word.equalsIgnoreCase((String)lstWords.getSelectedValue()) ) {
			return;
		}

		for ( int i = 0; i < modelWords.size(); i++ ) {
			String s = (String)modelWords.getElementAt(i);
			if ( s != null && s.indexOf(word) == 0 ) {
//			if ( s != null && s.startsWith(word) ) {
//[!!!] startsWith
				if ( s.equalsIgnoreCase(word) ) {
					lstWords.setSelectedValue(s, true);
					lstWords.setSelectedIndex(i);
				} else {
					lstWords.clearSelection();
					lstWords.ensureIndexIsVisible(i+lstWords.getVisibleRowCount());
					lstWords.ensureIndexIsVisible(i);
				}

				return;
			}
		}
	}

	/**
	 * 
	 */
	private void onWord1Changed() {
		updateButtonsEnabled();
		new SwingWorker<Void, Void>() {

			@Override
			protected Void doInBackground() throws Exception {
				return null;
			}

			@Override
			protected void done() {
				findAndFocusWordInList();
			}
		}.execute();
	}


	/**
	 * 
	 * @param enabled
	 */
	private void enableAllItems(boolean enabled) {
		lstDicts.setEnabled(enabled);
		lstWords.setEnabled(enabled);
		btnAdd.setEnabled(enabled);
		btnDel.setEnabled(enabled);
		btnEdit.setEnabled(enabled);
		btnPlay.setEnabled(enabled);
		btnFind.setEnabled(enabled && edtText.isEditable());		
		edtWord.setEnabled(enabled);
		edtText.setEditable(false);
	}


	/**
	 * 
	 */
	private void updateButtonsEnabled() {
		new SwingWorker<Void, Void>() {
			@Override
			protected void done() {
				String word = edtWord.getText();
				
				btnAdd.setEnabled(!dictLoading && dict != null && word.length() > 0);
				btnDel.setEnabled(lstWords.getSelectedIndex() >= 0);
				btnEdit.setEnabled(lstWords.getSelectedIndex() >= 0);
				
				btnPlay.setEnabled(WordsPlayer.getInstance().isWordExist(word, Words.getConfiguration().langLearn));
				btnFind.setEnabled(edtText.isEditable() && edtText.isEnabled());
			}

			@Override
			protected Void doInBackground() throws Exception {
				return null;
			}
		}.execute();
	}


	@Override
	public void setVisible(boolean b) {
		if ( modelDicts.size() == 0 ) {
			fillDictsList();
		}
		super.setVisible(b);
	}


	@Override
	public void actionPerformed(ActionEvent e) {
		if ( e.getActionCommand().equals(CMD_ADD) ) {
			WordPair pair = dict.createPair(edtWord.getText(), "");
			if ( !dict.addPair(pair, true) ) {
				return;
			}
			dict.sort();
			dict.save();
			int index = dict.indexOf(pair);
			modelWords.add(index, pair.wordInLearnLang);
			lstWords.setSelectedIndex(index);
			lstWords.ensureIndexIsVisible(index);
			updateStatusLine();
		} else if ( e.getActionCommand().equals(CMD_DEL) ) {
			int index = lstWords.getSelectedIndex();
			if ( index >= 0 && JOptionPane.showConfirmDialog(this, _DELETE_WORD_CONFIRM, _DICT, JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION ) {
				dict.delete(index);
				dict.save();
				modelWords.remove(index);
				edtWord.setText("");
				edtText.setText("");
				btnFind.setEnabled(false);
				updateStatusLine();
			}
		} else if ( e.getActionCommand().equals(CMD_EDIT) ) {
			if ( !edtText.isEditable() ) {
				edtText.setEditable(true);
				btnFind.setEnabled(true);
				edtText.requestFocus();
			} else {
				edtText.setEditable(false);
				btnFind.setEnabled(false);
				String s = edtText.getText();
				StringTokenizer st = new StringTokenizer(s, "\n");
				StringBuffer text = new StringBuffer();
				while ( st.hasMoreTokens() ) {
					text.append(st.nextToken().trim());
					if ( st.hasMoreTokens() ) {
						text.append("; ");
					}
				}
				WordPair pair = getCurrentPair();
				pair.wordInMyLang = text.toString();
				dict.setPair(lstWords.getSelectedIndex(), pair);
				dict.save();
			}
		} else if ( e.getActionCommand().equals(CMD_PLAY) ) {
			WordsPlayer.getInstance().play(edtWord.getText(), Words.getConfiguration().langLearn);
		} else if ( e.getActionCommand().equals(CMD_FIND) ) {
			onFindWord();
		}
	}
	
	/**
	 * Ищет все возможные переводы слова по всем словарям
	 * 
	 * @param word
	 * @return
	 */
	private static String findWordTranslations(String word) {
		Configuration cfg = Words.getConfiguration();
		String s = "";
		for ( String fn : cfg.dictsAll ) {
			s += getWordTranslation(word, fn) + ';';
		}
		return removeDuplicatedWords(s);
	}
	
	/**
	 * Ищет перевод слова в словаре
	 * 
	 * @param word  переводимое слово
	 * @param fileName  имя файла словаря
	 * @return	перевод, или пустая строка
	 */
	private static String getWordTranslation(String word, String fileName) {
		HashDictionary dict = new HashDictionary();
		if ( !dict.load(fileName) ) {
			return "";
		}
		String translation = dict.get(word);
		return translation != null ? translation : "";
	}
	
	
	/**
	 * Удаляет дублирующиеся переводы в строке
	 * 
	 * @param s строка со списком слов, разделенных ;
	 * @return строка с удаленными дубликатами и разделенный символом перевода строки
	 */
	private static String removeDuplicatedWords(String s) {
		Set<String> set = new HashSet<String>();
		StringTokenizer st = new StringTokenizer(s, ";");
		while ( st.hasMoreTokens() ) {
			set.add(st.nextToken().trim());
		}
		StringBuffer result = new StringBuffer();
		for ( String word : set ) {
			result.append(word);
			result.append('\n');
		}
		return result.toString();
	}
	
	

	
	private void onFindWord() {
		updateButtonsEnabled();
		new SwingWorker<Void, Void>() {

			@Override
			protected Void doInBackground() throws Exception {
				enableAllItems(false);
				edtText.setEnabled(false);
				return null;
			}

			@Override
			protected void done() {
				String s = findWordTranslations(edtWord.getText());				
				edtText.setEnabled(true);
				edtText.setEditable(true);
				edtText.setText(s);
				enableAllItems(true);
				edtText.setEditable(true);
				edtText.setCaretPosition(0);
				WindowDict.this.requestFocus();
				edtText.requestFocus();
				if ( s.length() > 0 ) {
					edtText.moveCaretPosition(s.length()-1);
				}
			}
		}.execute();
	}

	

}
