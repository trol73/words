package trolsoft.words.windows;

import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.NumberFormat;
import java.text.ParseException;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTabbedPane;

import trolsoft.dict.MixedDictionary;
import trolsoft.ui.ColorField;
import trolsoft.ui.FileNameField;
import trolsoft.ui.FontField;
import trolsoft.ui.LangSelector;
import trolsoft.ui.Window;
import trolsoft.utils.I18N;
import trolsoft.utils.Utils;
import trolsoft.words.Configuration;
import trolsoft.words.Resources;
import trolsoft.words.Words;

public class WindowSettings extends Window implements ActionListener {
	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	private static final String TITLE = I18N.get("dialog.settings.title");
	private static final String TAB_DICTS = I18N.get("dialog.settings.dicts");
	private static final String TAB_UI = I18N.get("dialog.settings.ui");
	private static final String TAB_LEARN = I18N.get("dialog.settings.learn");
	private static final String TAB_SOUND = I18N.get("dialog.settings.sound");

	private static final String _CANCEL = I18N.get("cancel");
	private static final String _OK = I18N.get("ok");
	private static final String _APPLY = I18N.get("apply");
	private static final String _VOLUME = I18N.get("volume");
	
	private static final String _PLAY_RUSSIAN_IN_LEARN_MODE = I18N.get("dialog.settings.playRussianInLearnMode");
	private static final String _PLAY_ENGLISH_IN_LEARN_MODE = I18N.get("dialog.settings.playEnglishInLearnMode");
	private static final String _PLAY_RUSSIAN_IN_CONTROL_MODE = I18N.get("dialog.settings.playRussianInControlMode");
	private static final String _PLAY_ENGLISH_IN_CONTROL_MODE = I18N.get("dialog.settings.playEnglishInControlMode");
	private static final String _RUSSIAN_WORDS_FILES_AND_DIRS = I18N.get("dialog.settings.soundsPathForRussianWords");
	private static final String _ENGLISH_WORDS_FILES_AND_DIRS = I18N.get("dialog.settings.soundsPathForEnglishWords");
	private static final String _MIX_TRANSLATION_WORDS = I18N.get("dialog.settings.mixTranslationWords");
	private static final String _REMOVE_TRANSCRIPTION = I18N.get("dialog.settings.removeTranscription");
	private static final String _SHOW_TRANSCRIPTION = I18N.get("dialog.settings.showTranscription");
	private static final String _LEARN_GROUP_WORDS = I18N.get("dialog.settings.learnGroupWords");
	private static final String _LEARN_TRANSLATION = I18N.get("dialog.settings.learnTranslation");
	private static final String _ENG_TO_RUS_OR_RUS_TO_ENG = I18N.get("dialog.settings.engToRusOrRusToEng");
	private static final String _ENG_TO_RUS_AND_RUS_TO_ENG = I18N.get("dialog.settings.engToRusAndRusToEng");
	private static final String _RUS_TO_ENG = I18N.get("dialog.settings.rusToEng");
	private static final String _ENG_TO_RUS = I18N.get("dialog.settings.engToRus");
	private static final String _TIME_INTERVAL_IN_LEARN_MODE = I18N.get("dialog.settings.timeIntervalInLearnMode");
	private static final String _TIME_INTERVAL_IN_CONTROL_MODE = I18N.get("dialog.settings.timeIntervalInControlMode");
	private static final String _ALIGNMENT = I18N.get("dialog.settings.alignment");
	private static final String _ON_RIGHT_EDGE = I18N.get("dialog.settings.onRightEdge");
	private static final String _ON_CENTER = I18N.get("dialog.settings.onCenter");
	private static final String _ON_LEFT_EDGE = I18N.get("dialog.settings.onLeftEdge");
	private static final String _POSITION_ON_SCREEN = I18N.get("dialog.settings.screenPosition");
	private static final String _TRANSPARENCY = I18N.get("dialog.settings.transparency");	
	private static final String _WORDS_BACKGROUND_COLOR = I18N.get("dialog.settings.wordsBackgroundColor");	
	private static final String _DISABLE_TRANSPARENCY = I18N.get("dialog.settings.disableTransparency");
	private static final String _FILL_BACKGROUND = I18N.get("dialog.settings.fillBackground");
	private static final String _TRANSCRIPTION_COLOR = I18N.get("dialog.settings.transcriptionColor");
	private static final String _TRANSCRIPTION_FONT = I18N.get("dialog.settings.transcriptionFont");
	private static final String _TRANSLATED_WORDS_COLOR = I18N.get("dialog.settings.translationColor");
	private static final String _TRANSLATED_WORDS_FONT = I18N.get("dialog.settings.translationFont");
	private static final String _LEARNED_WORDS_COLOR = I18N.get("dialog.settings.learnedWordsColor");
	private static final String _LEARNED_WORDS_FONT = I18N.get("dialog.settings.learnedWordsFont");
	private static final String _TRANSCRIPTION_FILES = I18N.get("dialog.settings.transcriptionFiles");
	private static final String _DICT_FILES = I18N.get("dialog.settings.dictionaryFiles");
	private static final String _COMPLETED_WORD_FILES = I18N.get("dialog.settings.completedWordFiles");
	private static final String _LEARNED_WORD_FILES = I18N.get("dialog.settings.learnedWordsFiles");
	private static final String _ALTERNATIVE = I18N.get("dialog.settings.alternative");

	private LangSelector edtLangMy;
	private LangSelector edtLangLearn;


	private FileNameField edtDictFile;
	private FileNameField edtDictDeletedFile;
	private FileNameField edtDictAddedFile;
	private FileNameField edtDictTranscriptionsFile;
	private JFormattedTextField edtPosY;
	private JFormattedTextField edtTimeControl;
	private JFormattedTextField edtTimeView;
	private JFormattedTextField edtMaxWordsLimit;

	private JComboBox cbLearn;
	private JComboBox cbLayoutX;

	private NumberFormat fmtNumber;

	private FontField edtFontEngl;
	private FontField edtFontRus;
	private FontField edtFontTranscription;
	private ColorField edtColorEngl;
	private ColorField edtColorEnglAlt;
	private ColorField edtColorRus;
	private ColorField edtColorRusAlt;
	private ColorField edtColorTranscription;
	private ColorField edtColorBackground;
	private JCheckBox cbDrawBackground;
	private JCheckBox cbShowTranscription;
	private JCheckBox cbDeleteTranscription;
	private JCheckBox cbMixWords;
	
	private FileNameField edtSoundEngl;
	private FileNameField edtSoundRuss;

	private JCheckBox cbControlPlayEnglish;
	private JCheckBox cbControlPlayRussian;
	private JCheckBox cbViewPlayEnglish;
	private JCheckBox cbViewPlayRussian;
	private JSlider sdSoundVolume;
	private JComboBox cbTransparency;

	private JButton btnApply, btnOk, btnCancel;

	public WindowSettings() {
		super(TITLE);
		setDefaultCloseOperation(HIDE_ON_CLOSE);
		setResizable(false);
		setIconImage(Resources.imgSettings());

		Container cp = getContentPane();
		cp.setLayout(new BoxLayout(cp, BoxLayout.PAGE_AXIS));
		JTabbedPane tabs = new JTabbedPane();

		// Словари
		Box pnlDicts = Box.createVerticalBox();
		pnlDicts.setAlignmentX(Component.LEFT_ALIGNMENT);
		tabs.add(TAB_DICTS, pnlDicts);
		
		edtLangMy = new LangSelector();
		edtLangLearn = new LangSelector();
		addComponentsV(pnlDicts, new String[]{"Мой язык", "Изучаемый язык"}, new Component[]{edtLangMy, edtLangLearn});

		
		edtDictFile = new FileNameField(FileNameField.OPEN | FileNameField.MULTILINE);
		addComponentV(pnlDicts, _LEARNED_WORD_FILES, edtDictFile);
		edtDictDeletedFile = new FileNameField(FileNameField.OPEN | FileNameField.MULTILINE);
		addComponentV(pnlDicts, _COMPLETED_WORD_FILES, edtDictDeletedFile);
		edtDictAddedFile = new FileNameField(FileNameField.OPEN | FileNameField.MULTILINE);
		addComponentV(pnlDicts, _DICT_FILES, edtDictAddedFile);
		edtDictTranscriptionsFile = new FileNameField(FileNameField.OPEN | FileNameField.MULTILINE);
		addComponentV(pnlDicts, _TRANSCRIPTION_FILES, edtDictTranscriptionsFile);
		
		pnlDicts.add(Box.createVerticalGlue());

		// Интерфейс
		Box pnlUI = Box.createVerticalBox();
		pnlUI.setAlignmentX(Component.LEFT_ALIGNMENT);
		tabs.add(TAB_UI, pnlUI);

		edtFontEngl = new FontField();
		edtFontRus = new FontField();
		edtFontTranscription = new FontField();
		edtColorEngl = new ColorField();
		edtColorEnglAlt = new ColorField();
		edtColorRus = new ColorField();
		edtColorRusAlt = new ColorField();
		edtColorTranscription = new ColorField();
		
		addComponentsV(pnlUI, new String[]{_LEARNED_WORDS_FONT, _LEARNED_WORDS_COLOR}, new Component[]{edtFontEngl, edtColorEngl});
		addComponentsV(pnlUI, new String[]{_TRANSLATED_WORDS_FONT, _TRANSLATED_WORDS_COLOR}, new Component[]{edtFontRus, edtColorRus});
//		addComponentsV(pnlUI, new String[]{_LEARNED_WORDS_FONT, _LEARNED_WORDS_COLOR, _ALTERNATIVE}, new Component[]{edtFontEngl, edtColorEngl, edtColorEnglAlt});
//		addComponentsV(pnlUI, new String[]{_TRANSLATED_WORDS_FONT, _TRANSLATED_WORDS_COLOR, _ALTERNATIVE}, new Component[]{edtFontRus, edtColorRus, edtColorRusAlt});
		addComponentsV(pnlUI, new String[]{_TRANSCRIPTION_FONT, _TRANSCRIPTION_COLOR}, new Component[]{edtFontTranscription, edtColorTranscription});

		cbDrawBackground = new JCheckBox(_FILL_BACKGROUND);
		addComponentV(pnlUI, "", cbDrawBackground);

		edtColorBackground = new ColorField();
		
		cbTransparency = new JComboBox();
		cbTransparency.addItem(_DISABLE_TRANSPARENCY);
		for ( int i = 5; i <= 100; i += 5 ) {
			cbTransparency.addItem(Integer.toString(i) + '%');
		}
		cbTransparency.setMaximumSize(new Dimension(200, Utils.UI_MAX_HEIGHT));
		addComponentsV(pnlUI, new String[]{_WORDS_BACKGROUND_COLOR, _TRANSPARENCY}, new Component[]{edtColorBackground, cbTransparency});

		fmtNumber = NumberFormat.getIntegerInstance();
		fmtNumber.setGroupingUsed(false);
		edtPosY = new JFormattedTextField(fmtNumber);
		edtPosY.setColumns(10);
		edtPosY.setMaximumSize(new Dimension(200, 100));
		addComponentV(pnlUI, _POSITION_ON_SCREEN, edtPosY);
		
		cbLayoutX = new JComboBox();
		cbLayoutX.setMaximumSize(new Dimension(300, Utils.UI_MAX_HEIGHT));
		cbLayoutX.addItem(_ON_LEFT_EDGE);
		cbLayoutX.addItem(_ON_CENTER);
		cbLayoutX.addItem(_ON_RIGHT_EDGE);
		addComponentV(pnlUI, _ALIGNMENT, cbLayoutX);
		
		
		pnlUI.add(Box.createVerticalGlue());
		
		// Заучивание
		Box pnlLearn = Box.createVerticalBox();
		pnlLearn.setAlignmentX(Component.LEFT_ALIGNMENT);
		tabs.add(TAB_LEARN, pnlLearn);

		edtTimeControl = new JFormattedTextField(fmtNumber);
		edtTimeControl.setColumns(10);
		edtTimeControl.setMaximumSize(new Dimension(200, Utils.UI_MAX_HEIGHT));
		addComponentV(pnlLearn, _TIME_INTERVAL_IN_CONTROL_MODE, edtTimeControl);
		
		edtTimeView = new JFormattedTextField(fmtNumber);
		edtTimeView.setColumns(10);
		edtTimeView.setMaximumSize(new Dimension(200, Utils.UI_MAX_HEIGHT));
		addComponentV(pnlLearn, _TIME_INTERVAL_IN_LEARN_MODE, edtTimeView);

		cbLearn = new JComboBox();
		cbLearn.setMaximumSize(new Dimension(300, Utils.UI_MAX_HEIGHT));
		cbLearn.addItem(_ENG_TO_RUS);
		cbLearn.addItem(_RUS_TO_ENG);
		cbLearn.addItem(_ENG_TO_RUS_AND_RUS_TO_ENG);
		cbLearn.addItem(_ENG_TO_RUS_OR_RUS_TO_ENG);
		addComponentV(pnlLearn, _LEARN_TRANSLATION, cbLearn);
		
		edtMaxWordsLimit = new JFormattedTextField(fmtNumber);
		edtMaxWordsLimit.setColumns(10);
		edtMaxWordsLimit.setMaximumSize(new Dimension(200, Utils.UI_MAX_HEIGHT));
		addComponentV(pnlLearn, _LEARN_GROUP_WORDS, edtMaxWordsLimit);
		
		cbShowTranscription = new JCheckBox(_SHOW_TRANSCRIPTION);
		addComponentV(pnlLearn, "", cbShowTranscription);
		
		cbDeleteTranscription = new JCheckBox(_REMOVE_TRANSCRIPTION);
		addComponentV(pnlLearn, "", cbDeleteTranscription);
		
		cbMixWords = new JCheckBox(_MIX_TRANSLATION_WORDS);
		addComponentV(pnlLearn, "", cbMixWords);
		
		// Озвучивание
		Box pnlSound = Box.createVerticalBox();
		pnlSound.setAlignmentX(Component.LEFT_ALIGNMENT);
		tabs.add(TAB_SOUND, pnlSound);
		
		edtSoundEngl = new FileNameField(FileNameField.OPEN | FileNameField.FILE | FileNameField.DIR | FileNameField.MULTILINE);
		addComponentV(pnlSound, _ENGLISH_WORDS_FILES_AND_DIRS, edtSoundEngl);
		
		edtSoundRuss = new FileNameField(FileNameField.OPEN | FileNameField.FILE | FileNameField.DIR | FileNameField.MULTILINE);
		addComponentV(pnlSound, _RUSSIAN_WORDS_FILES_AND_DIRS, edtSoundRuss);

		cbControlPlayEnglish = new JCheckBox(_PLAY_ENGLISH_IN_CONTROL_MODE);
		addComponentV(pnlSound, "", cbControlPlayEnglish);
		
		cbControlPlayRussian = new JCheckBox(_PLAY_RUSSIAN_IN_CONTROL_MODE);
		addComponentV(pnlSound, "", cbControlPlayRussian);
		
		cbViewPlayEnglish = new JCheckBox(_PLAY_ENGLISH_IN_LEARN_MODE);
		addComponentV(pnlSound, "", cbViewPlayEnglish);
		
		cbViewPlayRussian = new JCheckBox(_PLAY_RUSSIAN_IN_LEARN_MODE);
		addComponentV(pnlSound, "", cbViewPlayRussian);
		
		
		sdSoundVolume = new JSlider();
		sdSoundVolume.setMajorTickSpacing(20);
		sdSoundVolume.setMinorTickSpacing(5);
		sdSoundVolume.setPaintTicks(true);
		sdSoundVolume.setPaintLabels(true);
		addComponentV(pnlSound, _VOLUME, sdSoundVolume);

		
		

		cp.add(tabs);

		// Кнопки
		JPanel pnlButtons = new JPanel();
		pnlButtons.setLayout(new BoxLayout(pnlButtons, BoxLayout.LINE_AXIS));
		pnlButtons.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		pnlButtons.add(Box.createHorizontalGlue());
		btnApply = new JButton(_APPLY);
		btnApply.addActionListener(this);
		btnApply.setActionCommand("apply");
		pnlButtons.add(btnApply);
		pnlButtons.add(Box.createRigidArea(new Dimension(10, 0)));
		btnOk = new JButton(_OK);
		btnOk.addActionListener(this);
		btnOk.setActionCommand("ok");
		pnlButtons.add(btnOk);
		pnlButtons.add(Box.createRigidArea(new Dimension(10, 0)));
		btnCancel = new JButton(_CANCEL);
		btnCancel.addActionListener(this);
		btnCancel.setActionCommand("cancel");
		pnlButtons.add(btnCancel);
		//pnlButtons.setLayout(new BoxLayout(pnlButtons, BoxLayout.LINE_AXIS));
		cp.add(pnlButtons);

		initConfiguration();

		pack();
	}

	private void addComponentV(Box panel, String label, Component component) {
		addComponentsV(panel, new String[]{label}, new Component[]{component});
	}
	
	private void addComponentsV(Box panel, String[] labels, Component[] components) {
/*		
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
			box.add(Box.createHorizontalGlue());
			box.add(lbl);
			box.add(component);
			box.setBorder(BorderFactory.createEmptyBorder(7, 10, 7, 10));
			box.setAlignmentX(Component.LEFT_ALIGNMENT);
			vbox.add(box);
		}
		panel.add(vbox);
*/
		panel.add(createHorisontalBox(labels, components));
	}

	private void udpateConfiguration() {
		Configuration cfg = Words.getConfiguration();

		cfg.langMy = edtLangMy.getLang();
		cfg.langLearn = edtLangLearn.getLang();
		cfg.uiColorEngl = edtColorEngl.getColor().getRGB();
		cfg.uiColorEnglAlt = edtColorEnglAlt.getColor().getRGB();
		cfg.uiColorRus = edtColorRus.getColor().getRGB();
		cfg.uiColorRusAlt = edtColorRusAlt.getColor().getRGB();
		cfg.uiColorTranscription = edtColorTranscription.getColor().getRGB();
		cfg.uiBackgroundColor = edtColorBackground.getColor().getRGB();
		cfg.uiBackgroundDraw = cbDrawBackground.isSelected();
		cfg.dictsLearn = edtDictFile.getFileNames();
		cfg.dictsDeleted = edtDictDeletedFile.getFileNames();
		cfg.dictsAll = edtDictAddedFile.getFileNames();
		cfg.dictsTranscriptions = edtDictTranscriptionsFile.getFileNames();
		cfg.uiFontEngl = edtFontEngl.getFont();
		cfg.uiFontRus = edtFontRus.getFont();
		cfg.uiFontTranscription = edtFontTranscription.getFont();
		try {
			cfg.uiPosY = fmtNumber.parse(edtPosY.getText()).intValue();
		} catch (ParseException e) {
			cfg.uiPosY = 0;
		}
		cfg.uiLayoutX = cbLayoutX.getSelectedIndex();
		try {
			cfg.learnTime = fmtNumber.parse(edtTimeControl.getText()).intValue();
		} catch (ParseException e) {
			cfg.learnTime = 0;
		}
		try {
			cfg.learnViewTime = fmtNumber.parse(edtTimeView.getText()).intValue();
		} catch (ParseException e) {
			cfg.learnViewTime = 0;
		}
		try {
			cfg.learnGroupwordslimit = fmtNumber.parse(edtMaxWordsLimit.getText()).intValue();
		} catch (ParseException e) {
			cfg.learnGroupwordslimit = 0;
		}
		
		cfg.learnMode = MixedDictionary.Mode.values()[cbLearn.getSelectedIndex()];
		cfg.learnTranscriptionShow = cbShowTranscription.isSelected();
		cfg.learnTranscriptionDelete = cbDeleteTranscription.isSelected();
		cfg.learnWordsMix = cbMixWords.isSelected();
		
		cfg.soundEnglish = edtSoundEngl.getFileNames();
		cfg.soundRussian = edtSoundRuss.getFileNames();
		cfg.soundControlPlayEnglish = cbControlPlayEnglish.isSelected();
		cfg.soundControlPlayRussian = cbControlPlayRussian.isSelected();
		cfg.soundViewPlayEnglish = cbViewPlayEnglish.isSelected();
		cfg.soundViewPlayRussian = cbViewPlayRussian.isSelected();
		cfg.soundPlayVolume = sdSoundVolume.getValue();
		cfg.uiTransparency = cbTransparency.getSelectedIndex()*5;
	}

	
	private void initConfiguration() {
		Configuration cfg = Words.getConfiguration();

		edtLangMy.setLang(cfg.langMy);
		edtLangLearn.setLang(cfg.langLearn);
		edtColorEngl.setColor(cfg.uiColorEngl);
		edtColorEnglAlt.setColor(cfg.uiColorEnglAlt);
		edtColorRus.setColor(cfg.uiColorRus);
		edtColorRusAlt.setColor(cfg.uiColorRusAlt);
		edtColorTranscription.setColor(cfg.uiColorTranscription);
		edtColorBackground.setColor(cfg.uiBackgroundColor);
		cbDrawBackground.setSelected(cfg.uiBackgroundDraw);
		edtDictFile.setFileNames(cfg.dictsLearn);
		edtDictDeletedFile.setFileNames(cfg.dictsDeleted);
		edtDictAddedFile.setFileNames(cfg.dictsAll);
		edtDictTranscriptionsFile.setFileNames(cfg.dictsTranscriptions); 
		edtFontEngl.setFont(cfg.uiFontEngl);
		edtFontRus.setFont(cfg.uiFontRus);
		edtFontTranscription.setFont(cfg.uiFontTranscription);
		edtPosY.setText(fmtNumber.format(cfg.uiPosY));
		cbLayoutX.setSelectedIndex(cfg.uiLayoutX);
		edtTimeControl.setText(fmtNumber.format(cfg.learnTime));
		edtTimeView.setText(fmtNumber.format(cfg.learnViewTime));
		edtMaxWordsLimit.setText(fmtNumber.format(cfg.learnGroupwordslimit));
		cbLearn.setSelectedIndex(cfg.learnMode.ordinal());
		cbShowTranscription.setSelected(cfg.learnTranscriptionShow);
		cbDeleteTranscription.setSelected(cfg.learnTranscriptionDelete);
		cbMixWords.setSelected(cfg.learnWordsMix);
		
		edtSoundEngl.setFileNames(cfg.soundEnglish);
		edtSoundRuss.setFileNames(cfg.soundRussian);
		cbControlPlayEnglish.setSelected(cfg.soundControlPlayEnglish);
		cbControlPlayRussian.setSelected(cfg.soundControlPlayRussian);
		cbViewPlayEnglish.setSelected(cfg.soundViewPlayEnglish);
		cbViewPlayRussian.setSelected(cfg.soundViewPlayRussian);
		
		sdSoundVolume.setValue(cfg.soundPlayVolume);
		cbTransparency.setSelectedIndex(cfg.uiTransparency/5);
	}

	
	private void saveSettingsAndInit() {
		boolean started = Words.isStarted();
		Words.updateCurrentMode(false, false);
		udpateConfiguration();
		Words.init();
		Words.updateCurrentMode(started, true);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if (e.getActionCommand().equals("apply")) {
			saveSettingsAndInit();
		} else if (e.getActionCommand().equals("ok")) {
			saveSettingsAndInit();
			Words.getConfiguration().save();
			setVisible(false);
		} else if (e.getActionCommand().equals("cancel")) {
			initConfiguration();
			setVisible(false);
		}
	}

}
