package trolsoft.words.windows;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import trolsoft.dict.Dictionary;
import trolsoft.dict.HashDictionary;
import trolsoft.ui.CheckBoxList;
import trolsoft.ui.FileNameField;
import trolsoft.ui.Window;
import trolsoft.utils.I18N;
import trolsoft.utils.Utils;
import trolsoft.words.Configuration;
import trolsoft.words.Resources;
import trolsoft.words.Words;
import trolsoft.words.tools.MobileGenerator;

public class WindowMobileGenerator extends Window implements ActionListener {

	private static final long serialVersionUID = 1L;
	
	private static final String _TITLE = I18N.get("dialog.mobilegenerator.title");
	private static final String _ADDED_WORDS_DICTS = I18N.get("dialog.mobilegenerator.addedWordsDicts");
	private static final String _DELETED_WORDS_DICTS = I18N.get("dialog.mobilegenerator.deletedWordsDicts");
	private static final String _FONT_SIZE = I18N.get("dialog.mobilegenerator.fontSize");
	private static final String _MIDLET_NAME = I18N.get("dialog.mobilegenerator.midletName");
	private static final String _OUTPUT_PATH = I18N.get("dialog.mobilegenerator.outputPath");
	private static final String _SMALL = I18N.get("dialog.mobilegenerator.small");
	private static final String _MEDIUM = I18N.get("dialog.mobilegenerator.medium");
	private static final String _BIG = I18N.get("dialog.mobilegenerator.big");
	
	private static final String _CREATE = I18N.get("create");
	private static final String _CANCEL = I18N.get("cancel");
	private static final String _DEFAULT_MIDLET_NAME = I18N.get("dialog.mobilegenerator.defaultMidletName");
	
	
	private CheckBoxList lstDictsLearn;
	private CheckBoxList lstDictsDelete;
	private JTextField edtMidletName;
	private FileNameField edtOutPath;
	private JComboBox cbFontSize;
	private JButton btnCreate;
	private JButton btnCancel;
	
	private List<String> dictLearnFiles = new ArrayList<String>();
	private List<String> dictDeleteFiles = new ArrayList<String>();
	
	
	public WindowMobileGenerator() {
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
		lstDictsLearn.setMinimumSize(new Dimension(400, Utils.UI_MAX_HEIGHT*3));
		lstDictsDelete.setMaximumSize(new Dimension(800, Utils.UI_MAX_HEIGHT*10));
		lstDictsDelete.setMinimumSize(new Dimension(400, Utils.UI_MAX_HEIGHT*3));
		
		// размер шрифта
		cbFontSize = new JComboBox(new String[]{_SMALL, _MEDIUM, _BIG }) ;
		addComponentV(box, "<html><b>" + _FONT_SIZE, cbFontSize);
		
		// Имя мидлета
		edtMidletName = new JTextField();
		edtMidletName.setColumns(20);
		addComponentV(box, "<html><b>" + _MIDLET_NAME, edtMidletName);
		edtMidletName.setText(_DEFAULT_MIDLET_NAME);
		
		// каталог для генерации мидлета
		edtOutPath = new FileNameField(FileNameField.DIR | FileNameField.OPEN);
		addComponentV(box, "<html><b>" + _OUTPUT_PATH, edtOutPath);
		edtOutPath.setFileName(Configuration.getRootPath() + File.separatorChar + "mobile");
		
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


	
	@Override
	public void actionPerformed(ActionEvent e) {
		if ( e.getActionCommand().equals("create") ) {
			MobileGenerator gen = new MobileGenerator(edtOutPath.getFileName(), edtMidletName.getText(), cbFontSize.getSelectedIndex());
			gen.setDict(buildDict());
			if ( gen.generate() ) {
				setVisible(false);
			}
		} else if ( e.getActionCommand().equals("cancel") ) {
			setVisible(false);
		}
	}
	
	/**
	 * Строит словарь слов, которые будут помещены в мидлет
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
	
	
	private void addComponentV(Box panel, String label, Component component) {
		addComponentsV(panel, new String[]{label}, new Component[]{component});
	}
	
	
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
			box.add(Box.createHorizontalGlue());
			box.add(lbl);
			box.add(component);
			box.setBorder(BorderFactory.createEmptyBorder(7, 10, 7, 10));
			box.setAlignmentX(Component.LEFT_ALIGNMENT);
			vbox.add(box);
		}
		panel.add(vbox);
	}
	

}
