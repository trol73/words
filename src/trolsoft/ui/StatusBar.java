package trolsoft.ui;

import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.BevelBorder;

public class StatusBar extends JPanel {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	protected JLabel statusLabel = new JLabel();

	public StatusBar() {
		super();
		setBorder(new BevelBorder(BevelBorder.LOWERED));
		setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
		statusLabel.setHorizontalAlignment(SwingConstants.LEFT);
		add(statusLabel);
	}
	
	public void setText(String text) {
		statusLabel.setText(text);
	}
	
	public String getText() {
		return statusLabel.getText();
	}

}
