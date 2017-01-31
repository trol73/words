package trolsoft.ui;

import java.awt.Component;
import java.awt.Image;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JToolBar;

public class ToolBar extends JToolBar {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private ActionListener actionListener;

	public ToolBar() {
		super(HORIZONTAL);
		setFloatable(false);
	}
	
	public void setActionListener(ActionListener l) {
		for ( Component c : getComponents() ) {
			if ( c instanceof JButton ) {
				JButton btn = (JButton) c;
				if ( actionListener != null ) {
					btn.removeActionListener(actionListener);
				}
				if ( l != null ) {
					btn.addActionListener(l);
				}
			}
		}
		this.actionListener = l;		
	}
	
	public JButton addButton(String cmd, Image img, String toolTip) {
		JButton btn;
		if ( img != null ) {
			btn = new JButton(new ImageIcon(img));
		} else {
			btn = new JButton();
		}
		btn.setActionCommand(cmd);
		if ( actionListener != null ) {
			btn.addActionListener(actionListener);
		}
		if ( toolTip != null ) {
			btn.setToolTipText(toolTip);
		}
		add(btn);
		return btn;
	}


}
