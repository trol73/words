package trolsoft.ui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JColorChooser;

import trolsoft.utils.I18N;
import trolsoft.utils.Utils;
import trolsoft.words.Resources;



public class ColorField extends Box {
	private static final String TOOLTIP = I18N.get("dialog.colorchooser.tooltip");
	private static final String TITLE = I18N.get("dialog.colorchooser.title");
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private TextField edtColor;
	private JButton btnSelect;
	private Font font;
	private Color color;

	public ColorField() {
		super(BoxLayout.LINE_AXIS);
		Box box = Box.createHorizontalBox();
		edtColor = new TextField(7);
		btnSelect = new JButton(new ImageIcon(Resources.imgColor()));
		btnSelect.setToolTipText(TOOLTIP);

		btnSelect.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				Color res = JColorChooser.showDialog(getParent(), TITLE, color);
				if ( res != null ) {
					setColor(res);
				}
			}
		});

		edtColor.setMaximumSize(new Dimension(100, Utils.UI_MAX_HEIGHT));
		edtColor.setEditable(false);
		box.add(edtColor);
		box.add(btnSelect);
		setFont(font);
		add(box);
	}

	public Color getColor() {
		return color;
	}

	public void setColor(Color color) {
		this.color = color;
		edtColor.setBackground(color);
	}

	public void setColor(int color) {
		setColor(new Color(color));
	}
	
	public int getFieldWidth() {
		return edtColor.getMaximumSize().width;
	}
	
	public void setFieldWidth(int width) {
		edtColor.setMaximumSize(new Dimension(width, Utils.UI_MAX_HEIGHT));
	}

}
