package trolsoft.ui;

import java.awt.Component;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class Window extends JFrame implements WindowListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	

	
	public Window(String title) {
		super(title);
		setDefaultCloseOperation(HIDE_ON_CLOSE);
		addWindowListener(this);
	}
	

	@Override
	public void setVisible(final boolean visible) {
		if ( visible && isVisible() ) {
			super.setVisible(false);
		}
		super.setVisible(visible);
	}
	
	@Override
	public void pack() {
		super.pack();
		setMinimumSize(getSize());
	}

/*	
	private void resporeAlwaysOnTop() {
		
			java.awt.EventQueue.invokeLater(new Runnable() {
			    @Override
			    public void run() {
			    	try {
						Thread.sleep(500);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
			    	setAlwaysOnTop(false);
			    	toFront();
			    	unsetAlwaysOnTop = false;
			    }
			});
	}
*/

	@Override
	public void windowOpened(WindowEvent e) {
	}


	@Override
	public void windowClosing(WindowEvent e) {
	}


	@Override
	public void windowClosed(WindowEvent e) {
	}


	@Override
	public void windowIconified(WindowEvent e) {
	}


	@Override
	public void windowDeiconified(WindowEvent e) {
	}


	@Override
	public void windowActivated(WindowEvent e) {
	}


	@Override
	public void windowDeactivated(WindowEvent e) {
	}
	
	
	protected static Box createVerticalBox(Component... components) {
		Box box = Box.createVerticalBox();
		for ( Component c : components ) {
			if (c instanceof JComponent) {
				((JComponent)c).setAlignmentX(0);
			}
			box.add(c);
		}
		box.setBorder(BorderFactory.createEmptyBorder(7, 10, 7, 10));
		box.setAlignmentX(Component.LEFT_ALIGNMENT);
		return box;
	}
	
	protected static Box createHorisontalBox(String[] labels, Component[] components) {
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
		return vbox;
	}

	
	protected static Box createHorisontalBox(String label, Component component) {
		return createHorisontalBox(new String[]{label}, new Component[]{component});
	}
}
