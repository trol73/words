package trolsoft.ui;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;

import trolsoft.dialogs.FontChooserDialog;
import trolsoft.utils.I18N;
import trolsoft.utils.Utils;
import trolsoft.words.Resources;


public class FontField extends Box {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private static final String _TOOLTIP = I18N.get("dialog.fontchooser.fontSelectionDialog");
	private static final String _BOLD = I18N.get("dialog.fontchooser.bold").toLowerCase();
	private static final String _ITALIC = I18N.get("dialog.fontchooser.italic").toLowerCase();
	
	private TextField edtFontName;
	private JButton btnSelect;
	private Font font;
	private FontChooserDialog dialog;


	public FontField() {
		super(BoxLayout.LINE_AXIS);
		Box box = Box.createHorizontalBox();
		edtFontName = new TextField(30);
		btnSelect = new JButton(new ImageIcon(Resources.imgFont()));
		btnSelect.setToolTipText(_TOOLTIP);

		btnSelect.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if ( dialog == null ) {
					Frame parentFrame = null;
					Container parent = FontField.this.getParent();
					while ( parent != null ) {
						parent = parent.getParent();
						if ( parent instanceof Frame ) {
							parentFrame = (Frame)parent;
							break;
						}
					}
					dialog = new FontChooserDialog(parentFrame);
					dialog.setIconImage(Resources.imgFont());
				}
				dialog.setSelectedFont(getFont());
				dialog.setVisible(true);
				if ( dialog.getSelectedFont() != null ) {
					setFont(dialog.getSelectedFont());
				}
			}
		});
		edtFontName.setMaximumSize(new Dimension(500, Utils.UI_MAX_HEIGHT));
		edtFontName.setEditable(false);
		box.add(edtFontName);
		box.add(btnSelect);
		add(box);
	}




	public Font getFont() {
		return font;
	}


	public void setFont(Font font) {
		this.font = font;
		if ( font != null ) {
			String fontName = font.getFamily() + ", " + font.getSize();
			String fontStyle = "";
			if ( (font.getStyle() & Font.BOLD) != 0 ) {
				fontStyle += _BOLD;
			}
			if ( (font.getStyle() & Font.ITALIC) != 0 ) {
				if ( fontStyle.length() > 0 ) {
					fontStyle += ", ";
				}
				fontStyle += _ITALIC;
			}
			if ( fontStyle.length() > 0 ) {
				fontName += " (" + fontStyle + ')';
			}
			edtFontName.setText(fontName);
		} else {
			edtFontName.setText("");
		}
	}



}
