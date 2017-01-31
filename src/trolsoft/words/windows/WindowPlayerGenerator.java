package trolsoft.words.windows;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.SwingWorker;

import trolsoft.dict.Dictionary;
import trolsoft.dict.HashDictionary;
import trolsoft.dict.MixedDictionary;
import trolsoft.ui.CheckBoxList;
import trolsoft.ui.DoubleSpinner;
import trolsoft.ui.FileNameField;
import trolsoft.ui.Window;
import trolsoft.utils.I18N;
import trolsoft.utils.Utils;
import trolsoft.words.Configuration;
import trolsoft.words.Resources;
import trolsoft.words.Words;
import trolsoft.words.tools.AudioPlayerGenerator;

public class WindowPlayerGenerator  extends Window implements ActionListener {

	private static final long serialVersionUID = 1L;
	
	private static final String _TITLE = I18N.get("dialog.playergenerator.title");
	private static final String _ADDED_WORDS_DICTS = I18N.get("dialog.playergenerator.addedWordsDicts");
	private static final String _DELETED_WORDS_DICTS = I18N.get("dialog.playergenerator.deletedWordsDicts");
	private static final String _OUTPUT_PATH = I18N.get("dialog.playergenerator.outputPath");
		
	private static final String _INTERVAL_BTW_WORDS = I18N.get("dialog.playergenerator.intervalBtwWords");
	private static final String _AND_PAIRS = I18N.get("dialog.playergenerator.andPairs");
	private static final String _REPEATS_OF_WORDS = I18N.get("dialog.playergenerator.repeatsOfWords");
	private static final String _AND_DICTS = I18N.get("dialog.playergenerator.andDicts");
	private static final String _DIRECTION = I18N.get("dialog.playergenerator.direction");
	private static final String _MAXIMUM_PAIRS_PER_FILE = I18N.get("dialog.playergenerator.maximumWordsPerFile");
	private static final String _SAMPLE_RATE = I18N.get("dialog.playergenerator.sampleRate");
	
	private static final String _CREATE = I18N.get("create");
	private static final String _CANCEL = I18N.get("cancel");
	
	private static final String _ENG_TO_RUS_OR_RUS_TO_ENG = I18N.get("dialog.settings.engToRusOrRusToEng");
	private static final String _ENG_TO_RUS_AND_RUS_TO_ENG = I18N.get("dialog.settings.engToRusAndRusToEng");
	private static final String _RUS_TO_ENG = I18N.get("dialog.settings.rusToEng");
	private static final String _ENG_TO_RUS = I18N.get("dialog.settings.engToRus");
	
	
	private CheckBoxList lstDictsLearn;
	private CheckBoxList lstDictsDelete;
	private FileNameField edtOutPath;
	private JButton btnCreate;
	private JButton btnCancel;
	
	private DoubleSpinner edtIntervalWords;
	private DoubleSpinner edtIntervalPairs;
	private DoubleSpinner edtRepeatWords;
	private DoubleSpinner edtRepeatAll;
	private JComboBox cbWordsDirection;
	private JComboBox cbSampleRate;
	private JFormattedTextField edtWordsPerFile;
	
	private JProgressBar progressBar;
	
	private List<String> dictLearnFiles = new ArrayList<String>();
	private List<String> dictDeleteFiles = new ArrayList<String>();
	
	
	
	
	
	public WindowPlayerGenerator() {
		super(_TITLE);
		setDefaultCloseOperation(HIDE_ON_CLOSE);
		setResizable(false);
		setIconImage(Resources.imgMobile());
		
		Container cp = getContentPane();
		//cp.setLayout(new BoxLayout(cp, BoxLayout.PAGE_AXIS));
		cp.setLayout(new BorderLayout());
		JPanel panel = new JPanel();
		panel.setAlignmentX(0.0F);
	
		BoxLayout boxLayout = new BoxLayout(panel, BoxLayout.LINE_AXIS);
		panel.setLayout(boxLayout);
		panel.setAlignmentX(Component.LEFT_ALIGNMENT);
		cp.add(panel, BorderLayout.PAGE_START);
		Box box = Box.createVerticalBox();
		box.setAlignmentX(Component.LEFT_ALIGNMENT);
		panel.add(box);
		
		
		lstDictsLearn = new CheckBoxList();
		lstDictsDelete = new CheckBoxList();
		
		addComponentV(box, "<html><b>" + _ADDED_WORDS_DICTS, lstDictsLearn);
		addComponentV(box, "<html><b>" + _DELETED_WORDS_DICTS, lstDictsDelete);
		
		lstDictsLearn.setMaximumSize(new Dimension(800, Utils.UI_MAX_HEIGHT*10));
		lstDictsLearn.setMinimumSize(new Dimension(600, Utils.UI_MAX_HEIGHT*3));
		lstDictsDelete.setMaximumSize(new Dimension(800, Utils.UI_MAX_HEIGHT*10));
		lstDictsDelete.setMinimumSize(new Dimension(600, Utils.UI_MAX_HEIGHT*3));
		
		
		Configuration cfg = Words.getConfiguration();
		edtIntervalWords = new DoubleSpinner(cfg.generatorAudioIntervalWords, 0.1).setRange(0.0, 60.0).setPrecesion(1);
		edtIntervalWords.setMinimumSize(new Dimension(50, Utils.UI_MAX_HEIGHT));
		edtIntervalWords.setMaximumSize(new Dimension(70, Utils.UI_MAX_HEIGHT));

		edtIntervalPairs = new DoubleSpinner(cfg.generatorAudioIntervalPairs, 0.1).setRange(0.0, 60.0).setPrecesion(1);
		edtIntervalPairs.setMinimumSize(new Dimension(50, Utils.UI_MAX_HEIGHT));
		edtIntervalPairs.setMaximumSize(new Dimension(70, Utils.UI_MAX_HEIGHT));
		
		addComponentsH(box, new String[] {_INTERVAL_BTW_WORDS+"  ", _AND_PAIRS + "  "}, new Component[] {edtIntervalWords, edtIntervalPairs});
		
		
		edtRepeatWords = new DoubleSpinner(cfg.generatorAudioRepeatWords, 1).setRange(1, 50).setPrecesion(0);
		edtRepeatWords.setMinimumSize(new Dimension(50, Utils.UI_MAX_HEIGHT));
		edtRepeatWords.setMaximumSize(new Dimension(70, Utils.UI_MAX_HEIGHT));
		
		edtRepeatAll = new DoubleSpinner(cfg.generatorAudioRepeatAll, 1).setRange(1, 50).setPrecesion(0);
		edtRepeatAll.setMinimumSize(new Dimension(50, Utils.UI_MAX_HEIGHT));
		edtRepeatAll.setMaximumSize(new Dimension(70, Utils.UI_MAX_HEIGHT));
		
		addComponentsH(box, new String[] {_REPEATS_OF_WORDS + "  ", _AND_DICTS + "  "}, new Component[] {edtRepeatWords, edtRepeatAll});
		
		
		cbWordsDirection = new JComboBox();
		cbWordsDirection.setMinimumSize(new Dimension(200, Utils.UI_MAX_HEIGHT));
		cbWordsDirection.setMaximumSize(new Dimension(250, Utils.UI_MAX_HEIGHT));
		cbWordsDirection.addItem(_ENG_TO_RUS);
		cbWordsDirection.addItem(_RUS_TO_ENG);
		cbWordsDirection.addItem(_ENG_TO_RUS_AND_RUS_TO_ENG);
		cbWordsDirection.addItem(_ENG_TO_RUS_OR_RUS_TO_ENG);
		cbWordsDirection.setSelectedIndex(cfg.generatorAudioDirection.ordinal());
		addComponentH(box, _DIRECTION + "  ", cbWordsDirection);

		
		cbSampleRate = new JComboBox();
		cbSampleRate.setMinimumSize(new Dimension(100, Utils.UI_MAX_HEIGHT));
		cbSampleRate.setMaximumSize(new Dimension(150, Utils.UI_MAX_HEIGHT));
		cbSampleRate.addItem("22050");
		cbSampleRate.addItem("32000");
		cbSampleRate.addItem("44100");
		cbSampleRate.addItem("48000");
		cbSampleRate.addItem("96000");
		cbSampleRate.addItem("192000");		
		addComponentH(box, _SAMPLE_RATE + "  ", cbSampleRate);
		
		int index = -1;
		try {
			for ( int i = 0; i < cbSampleRate.getItemCount(); i++ ) {
				String s = (String)cbSampleRate.getItemAt(i);
				int val = Integer.parseInt(s); 
				if ( val == cfg.generatorAudioWavSamplerate ) {
					index = i;
					break;
				}
			}
		} catch ( Exception e ) {
		}
		if ( index < 0 ) {
			index = 1;
		}
		cbSampleRate.setSelectedIndex(index);
		
		edtWordsPerFile = new JFormattedTextField(NumberFormat.getIntegerInstance());
		edtWordsPerFile.setMinimumSize(new Dimension(50, Utils.UI_MAX_HEIGHT));
		edtWordsPerFile.setMaximumSize(new Dimension(70, Utils.UI_MAX_HEIGHT));
		edtWordsPerFile.setText(""+cfg.generatorAudioWordsinfile);
		addComponentH(box, _MAXIMUM_PAIRS_PER_FILE + "  ", edtWordsPerFile);

		
		// каталог для сохранения файлов
		edtOutPath = new FileNameField(FileNameField.DIR | FileNameField.OPEN);
		addComponentV(box, "<html><b>" + _OUTPUT_PATH, edtOutPath);
		String path = cfg.generatorAudioOutpath;
		if ( path == null || path.trim().length() == 0 ) {
			path = Configuration.getRootPath() + File.separatorChar + "audio";
		}
		edtOutPath.setFileName(path);
		
		progressBar = new JProgressBar();
		progressBar.setValue(0);
		box.add(progressBar);
		
		// Кнопки
		JPanel pnlButtons = new JPanel();
		pnlButtons.setLayout(new BoxLayout(pnlButtons, BoxLayout.LINE_AXIS));
		pnlButtons.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		pnlButtons.add(Box.createHorizontalGlue());
		btnCreate = new JButton(_CREATE);
		btnCreate.addActionListener(this);
		btnCreate.setActionCommand("create");
		pnlButtons.add(btnCreate);
		pnlButtons.add(Box.createRigidArea(new Dimension(10, 0)));
		btnCancel = new JButton(_CANCEL);
		btnCancel.addActionListener(this);
		btnCancel.setActionCommand("cancel");
		pnlButtons.add(btnCancel);
		pnlButtons.add(Box.createHorizontalGlue());
		cp.add(pnlButtons, BorderLayout.PAGE_END);
		
		init();
		pack();
		setSize(600, getHeight());
	}
	
	/**
	 * 
	 */
	private void init() {
		Configuration cfg = Words.getConfiguration();
		
		for ( String dict : cfg.dictsLearn ) {
			if ( dict.length() > 0 && dict.charAt(0) != ';' && dict.charAt(0) != '#' ) {
				dictLearnFiles.add(dict);
				lstDictsLearn.addCheckBox(dict, true);
			}
		}
		for ( String dict : cfg.dictsDeleted ) {
			if ( dict.length() > 0 && dict.charAt(0) != ';' && dict.charAt(0) != '#' ) {
				dictDeleteFiles.add(dict);
				lstDictsDelete.addCheckBox(dict, true);
			}
		}		
	}
	
	
	/**
	 * 
	 * @param enabled
	 */
	private void enableControls(boolean enabled) {
		lstDictsLearn.setEnabled(enabled);
		lstDictsDelete.setEnabled(enabled);
		edtOutPath.setEnabled(enabled);		
		edtIntervalWords.setEnabled(enabled);
		edtIntervalPairs.setEnabled(enabled);
		edtRepeatWords.setEnabled(enabled);
		edtRepeatAll.setEnabled(enabled);
		cbWordsDirection.setEnabled(enabled);
		cbSampleRate.setEnabled(enabled);
		edtWordsPerFile.setEnabled(enabled);
		btnCreate.setEnabled(enabled);
		btnCancel.setEnabled(enabled);
	}
	

	@Override
	public void actionPerformed(ActionEvent e) {
		if ( e.getActionCommand().equals("create") ) {
			final AudioPlayerGenerator gen = new AudioPlayerGenerator() {
				@Override
				public void onUpdate(int progress) {
					progressBar.setValue(progress);
				}
			};
			
			Configuration cfg = Words.getConfiguration();
			cfg.generatorAudioDirection = MixedDictionary.Mode.values()[cbWordsDirection.getSelectedIndex()];
			cfg.generatorAudioIntervalPairs = edtIntervalPairs.getValueAsDouble();
			cfg.generatorAudioIntervalWords = edtIntervalWords.getValueAsDouble();
			cfg.generatorAudioRepeatAll = edtRepeatAll.getValueAsInt();
			cfg.generatorAudioRepeatWords = edtRepeatWords.getValueAsInt();
			cfg.generatorAudioWavSamplerate = Integer.parseInt(((String)cbSampleRate.getSelectedItem()));
			cfg.generatorAudioWordsinfile = Integer.parseInt(edtWordsPerFile.getText());
			cfg.generatorAudioOutpath = edtOutPath.getFileName();
			gen.setDict(buildDict());
			
			enableControls(false);
			setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
			
			new SwingWorker<Void, Void>() {
				@Override
				protected Void doInBackground() throws Exception {
					if ( gen.generate() ) {
						setVisible(false);
					}
					return null;
				}
				
				@Override
				protected void done() {
					enableControls(true);
					setDefaultCloseOperation(HIDE_ON_CLOSE);
					progressBar.setValue(100);
				}
			}.execute();

		} else if ( e.getActionCommand().equals("cancel") ) {
			setVisible(false);
		}
	}
	
	/**
	 * Строит словарь слов, которые будут сохранены
	 * @return
	 */
	private Dictionary buildDict() {
		Dictionary dict = new HashDictionary();
		Dictionary dictDeleted = new HashDictionary();
		
		int i = 0;
		for ( String fn : dictLearnFiles ) {
			if ( lstDictsLearn.getCheckBox(i++).isSelected() ) { 
				dict.load(fn, true);
			}
		}
		i = 0;
		for ( String fn : dictDeleteFiles ) {
			if ( lstDictsDelete.getCheckBox(i++).isSelected() ) {
				dictDeleted.load(fn, true);
			}
		}
		dict.delete(dictDeleted);
		return dict;
	}
	

	/**
	 * 
	 * @param panel
	 * @param label
	 * @param component
	 */
	private void addComponentV(Box panel, String label, Component component) {
		addComponentsV(panel, new String[]{label}, new Component[]{component});
	}
	
	/**
	 * 
	 * @param panel
	 * @param labels
	 * @param components
	 */
	private void addComponentsV(Box panel, String[] labels, Component[] components) {
		Box vbox = Box.createHorizontalBox();
		vbox.setAlignmentX(Component.LEFT_ALIGNMENT);
		vbox.setAlignmentY(Component.TOP_ALIGNMENT);
		
		for ( int i = 0; i < labels.length; i++ ) {
			Box box = Box.createVerticalBox();
			JLabel lbl = new JLabel(labels[i]);
			lbl.setAlignmentX(0);
			Component component = components[i];
			if (component instanceof JComponent) {
				((JComponent)component).setAlignmentX(0);
			}
//			box.add(Box.createHorizontalGlue());
//			box.add(Box.createHorizontalStrut(20));
			box.add(lbl);
			box.add(component);
			box.setBorder(BorderFactory.createEmptyBorder(7, 10, 7, 10));
			box.setAlignmentX(Component.LEFT_ALIGNMENT);
			vbox.add(box);
		}
		panel.add(vbox);
	}
	
	
	/**
	 * 
	 * @param panel
	 * @param label
	 * @param component
	 */
	private void addComponentH(Box panel, String label, Component component) {
		addComponentsH(panel, new String[]{label}, new Component[]{component});
	}
	
	/**
	 * 
	 * @param panel
	 * @param labels
	 * @param components
	 */
	private void addComponentsH(Box panel, String[] labels, Component[] components) {
		Box hbox = Box.createHorizontalBox();
		hbox.setAlignmentX(Component.LEFT_ALIGNMENT);
		hbox.setAlignmentY(Component.TOP_ALIGNMENT);
		
		for ( int i = 0; i < labels.length; i++ ) {
			Box box = Box.createHorizontalBox();
			JLabel lbl = new JLabel(labels[i]);
			lbl.setAlignmentX(0);
			Component component = components[i];
/*
			if (component instanceof JComponent) {
				((JComponent)component).setAlignmentX(0);
			}
*/
			box.add(lbl);
			//box.add(Box.createHorizontalGlue());
			box.add(component);
			box.setBorder(BorderFactory.createEmptyBorder(0, 10, 0, 10));
			box.setAlignmentX(Component.LEFT_ALIGNMENT);
			hbox.add(box);
		}
		panel.add(hbox);
	}


}
