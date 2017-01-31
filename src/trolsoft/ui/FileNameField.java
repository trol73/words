package trolsoft.ui;

import java.awt.Dimension;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

import trolsoft.utils.I18N;
import trolsoft.utils.Utils;
import trolsoft.words.Resources;


public class FileNameField extends Box {
	
	private static final String _TOOLTIP = I18N.get("dialog.filechooser.tooltip");
	private static final String _SELECT = I18N.get("dialog.filechooser.select");
	private static final String _FILE = I18N.get("dialog.filechooser.file");
	private static final String _DIR = I18N.get("dialog.filechooser.dir");
	private static final String _FILE_OR_DIR = I18N.get("dialog.filechooser.fileOrDir");
	private static final String _OK = I18N.get("ok");

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public static final int OPEN = 0;
	public static final int SAVE = 1;
	
	public static final int FILE = 2;
	public static final int DIR = 4;
	public static final int MULTILINE = 8;
	
	

	private TextField edtFileName;
	private JTextArea edtFilesNames;
	private JButton btnSelect;
	private JFileChooser fileChooser;
	private int mode;
	
	private boolean multiline;

		public FileNameField(int mode) {
		super(BoxLayout.LINE_AXIS);
		this.mode = mode;
		multiline = (mode & MULTILINE) != 0;
		Box box = Box.createHorizontalBox();
		if ( multiline ) {
			edtFilesNames = new JTextArea();
			edtFilesNames.setColumns(40);
			edtFilesNames.setRows(4);			
		} else {
			edtFileName = new TextField(40);
		}
		btnSelect = new JButton(new ImageIcon(Resources.imgFileOpen()));
		btnSelect.setToolTipText(_TOOLTIP);
		
		btnSelect.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				if ( fileChooser == null ) {
					fileChooser = new JFileChooser();
					fileChooser.setApproveButtonText(_OK);
					if ( (FileNameField.this.mode & FILE) != 0 && (FileNameField.this.mode & DIR) != 0  ) {
						fileChooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);						
					} else if ( (FileNameField.this.mode & DIR) != 0 ) {
						fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
						fileChooser.setAcceptAllFileFilterUsed(false);
					}
					fileChooser.setMultiSelectionEnabled(FileNameField.this.multiline);
					String title = _SELECT + " " ;
					if ( (FileNameField.this.mode & DIR) != 0 && (FileNameField.this.mode & FILE) != 0 ) {
						title += _FILE_OR_DIR;
					} else if ( (FileNameField.this.mode & DIR) != 0 ) {
						title += _DIR;
					} else { 
						title += _FILE;
					}
					fileChooser.setDialogTitle(title);
					String fn = getFileName();			
					// FIXME invalid directory calculation
					fileChooser.setCurrentDirectory(new File(fn.length() == 0 ? "." : fn));
				}
			
				int returnVal;
				if ( (FileNameField.this.mode & SAVE) == 0 ) {
					returnVal = fileChooser.showOpenDialog(getParent());
				} else {
					returnVal = fileChooser.showSaveDialog(getParent());
				}
				if ( returnVal == JFileChooser.APPROVE_OPTION ) {
					File[] files = fileChooser.getSelectedFiles();
					for ( File f : files ) {
						setFileName(f.getPath());
//						System.out.println("Opening: " + f.getPath() + ".");
					}
				}
			}

		});
		if ( multiline ) {
			JScrollPane scrollPane = new JScrollPane(edtFilesNames); 
			scrollPane.setMaximumSize(new Dimension(800, Utils.UI_MAX_HEIGHT*edtFilesNames.getRows()));
			box.add(scrollPane);
		} else {
			edtFileName.setMaximumSize(new Dimension(800, Utils.UI_MAX_HEIGHT));
			box.add(edtFileName);
		}
		box.add(btnSelect);
		add(box);
	}

	/**
	 * Возвращает имя файла или каталога. Для режима мультиселекторв вернет первый каталог
	 * 
	 * @return
	 */
	public String getFileName() {
		if ( multiline ) {
			if ( getFileNames().length == 0 ) {
				return "";
			}
			return getFileNames()[0];
		} else {
			return edtFileName.getText(); 
		}
	}


	/**
	 * Возвращает массив всех выбранных файлов
	 * 
	 * @return
	 */
	public String[] getFileNames() {
		String[] result;
		if ( !multiline ) {
			result = new String[1];
			result[0] = edtFileName.getText();			
		} else {
			int linesCount = edtFilesNames.getLineCount(); 
			int count = 0;
			for ( int i = 0; i < linesCount; i++ ) {
				if ( getFileName(i).length() > 0 ) {
					count++;
				}
			}
			result = new String[count];
			int index = 0;
			for ( int i = 0; i < linesCount; i++ ) {
				String s = getFileName(i);
				if ( s.length() > 0 ) {
					result[index++] = s;
				}
			}
		}
		return result;		
	}
	
	
	private String getFileName(int index) {
		try {
			int offset = edtFilesNames.getLineStartOffset(index);
			int len = edtFilesNames.getLineEndOffset(index) - offset;
			return edtFilesNames.getText(offset, len).trim();
		} catch (BadLocationException e) {
			e.printStackTrace();
		}
		return "";
	}


	/**
	 * Устанавливает имя файла в обычном режиме и добавляет его, если он еще не добавлен, 
	 * в режиме мультиселектора
	 * 
	 * @param fileName
	 */
	public void setFileName(String fileName) {
		if ( multiline ) {
			if ( !contains(fileName) ) {
				if ( edtFilesNames.getText().length() > 0 ) {
					edtFilesNames.setText(edtFilesNames.getText() + "\n" + fileName);
				} else {
					edtFilesNames.setText(fileName);
				}
				
			}
		} else {
			edtFileName.setText(fileName);
		}
	}
	
	/**
	 * 
	 * @param fileNames
	 */
	public void setFileNames(String[] fileNames) {
		if ( multiline ) {
			clear();
			for ( String s : fileNames ) {
				setFileName(s);
			}
		} else {
			if ( fileNames.length > 0 ) {
				setFileName(fileNames[0]);
			} else {
				setFileName(fileNames[0]);
			}
		}
	}

	/**
	 * Очищает все введенные имена файлов
	 */
	public void clear() {
		if ( multiline ) {
			edtFilesNames.setText("");
		} else {
			edtFileName.setText("");
		}
	}
	
	
	/**
	 * Проверяет, содержит ли поле указанное имя файла/каталога
	 * 
	 * @param fileName
	 * @return
	 */
	public boolean contains(String fileName) {
		String[] files = getFileNames();
		for ( String s : files ) {
			if ( Utils.isEqualFileNames(s, fileName) ) {
				return true;
			}
		}
		return false;
	}
	
	
	public void setEnabled(boolean enabled) {
		if ( edtFileName != null ) {
			edtFileName.setEnabled(enabled);
		}
		if ( edtFilesNames != null ) {
			edtFilesNames.setEnabled(enabled);
		}
		btnSelect.setEnabled(enabled);
	}
/*
	public void setColumns(int columns) {
		edtFileName.setColumns(columns);
	}


	public int getColumns() {
		return edtFileName.getColumns();
	}
*/
}
