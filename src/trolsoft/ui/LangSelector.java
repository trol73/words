package trolsoft.ui;

import java.awt.Component;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.ListCellRenderer;

import trolsoft.words.Resources;
import trolsoft.words.general.Lang;

public class LangSelector extends Box {
	private static final long serialVersionUID = 1L;

	
	private JComboBox<Lang> comboBox;
	
	class ComboBoxlangRenderer extends JLabel implements ListCellRenderer<Lang> {
		private static final long serialVersionUID = 1L;

		@Override
		public Component getListCellRendererComponent(JList<? extends Lang> list, Lang value, int index,
				boolean isSelected, boolean cellHasFocus) {

	        if (isSelected) {
	            setBackground(list.getSelectionBackground());
	            setForeground(list.getSelectionForeground());
	        } else {
	            setBackground(list.getBackground());
	            setForeground(list.getForeground());
	        }
	        ImageIcon icon = new ImageIcon(Resources.imgFlag(value), value.name());
	        String pet = value.getNativeName();
	        setIcon(icon);
            setText(pet);
            setFont(list.getFont());
            setOpaque(true);

	        return this;
		}

	}

	public LangSelector() {
		super(BoxLayout.LINE_AXIS);
		try {
			comboBox = new JComboBox<Lang>(Lang.values());
			comboBox.setRenderer(new ComboBoxlangRenderer());
			add(comboBox);
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void setLang(Lang lang) {
		comboBox.setSelectedItem(lang);
	}

	public Lang getLang() {
		return (Lang)comboBox.getSelectedItem();
	}


}
