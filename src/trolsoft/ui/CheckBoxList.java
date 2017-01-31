package trolsoft.ui;

import java.awt.Component;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JCheckBox;
import javax.swing.JList;
import javax.swing.ListCellRenderer;
import javax.swing.ListModel;
import javax.swing.ListSelectionModel;
import javax.swing.UIManager;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;

public class CheckBoxList extends JList {
	
	private static final long serialVersionUID = 1L;
	protected static Border noFocusBorder = new EmptyBorder(1, 1, 1, 1);

	
	public CheckBoxList() {
		setCellRenderer(new CellRenderer());

		addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				int index = locationToIndex(e.getPoint());
				if ( index < 0 ) {
					return;
				}
				JCheckBox checkbox = getCheckBox(index);
				checkbox.setSelected(!checkbox.isSelected());
				repaint();
			}
		});
		
		addKeyListener(new KeyListener() {
			@Override
			public void keyTyped(KeyEvent e) {
				if ( e.getKeyChar() != ' ' ) {
					return;
				}
				int index = getSelectedIndex();
				if ( index < 0 ) {
					return;
				}
				JCheckBox checkbox = getCheckBox(index);
				checkbox.setSelected(!checkbox.isSelected());
				repaint();
			}
			
			@Override
			public void keyReleased(KeyEvent e) {
			}
			
			@Override
			public void keyPressed(KeyEvent e) {
			}
		});

		setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
	}
	
	/**
	 * 
	 * @param checkBox
	 */
	public void addCheckbox(JCheckBox checkBox) {
		ListModel currentList = this.getModel();
		JCheckBox[] newList = new JCheckBox[currentList.getSize() + 1];
		for (int i = 0; i < currentList.getSize(); i++) {
			newList[i] = (JCheckBox) currentList.getElementAt(i);
		}
		newList[newList.length - 1] = checkBox;
		setListData(newList);
	}
	
	/**
	 * 
	 * @param name
	 * @param checked
	 */
	public void addCheckBox(String name, boolean checked) {
		JCheckBox cb = new JCheckBox(name, checked);
		addCheckbox(cb);
	}
	
	/**
	 * 
	 * @param index
	 * @return
	 */
	public JCheckBox getCheckBox(int index) {
		return (JCheckBox) getModel().getElementAt(index);
	}

	/**
	 * 
	 * @author trol
	 * 
	 */
	protected class CellRenderer implements ListCellRenderer {
		
		public Component getListCellRendererComponent(JList list, Object value,	int index, boolean isSelected, boolean cellHasFocus) {
			JCheckBox checkbox = (JCheckBox) value;
			checkbox.setBackground(isSelected ? getSelectionBackground() : getBackground());
			checkbox.setForeground(isSelected ? getSelectionForeground() : getForeground());
			checkbox.setEnabled(isEnabled());
			checkbox.setFont(getFont());
			checkbox.setFocusPainted(false);
			checkbox.setBorderPainted(true);
			checkbox.setBorder(isSelected ? UIManager.getBorder("List.focusCellHighlightBorder") : noFocusBorder);
			return checkbox;
		}
	}
}
