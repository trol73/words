package trolsoft.words.windows;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import trolsoft.ui.Window;
import trolsoft.utils.I18N;
import trolsoft.words.Resources;
import trolsoft.words.Words;

public class WindowAbout extends Window implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;



	public WindowAbout() {
		super(I18N.get("dialog.about.title"));
		setDefaultCloseOperation(HIDE_ON_CLOSE);
		setResizable(false);
		setIconImage(Resources.imgInfo());
		
		Container cp = getContentPane();
		cp.setLayout(new BoxLayout(cp, BoxLayout.PAGE_AXIS));

		addText(Words.NAME, Font.BOLD, 30);
		
		addText(I18N.get("dialog.about.version") + " " + Words.getVersion(), Font.BOLD, 20);

		cp.add(Box.createVerticalStrut(40));
		addText(I18N.get("dialog.about.name"));
		addText(I18N.get("dialog.about.copyright"));
		addText("<html>" + I18N.get("dialog.about.homepage") + ": <a href= \"" + Words.URL + "\">" + Words.URL + "</a>");

		JPanel pnlButtons = new JPanel();
        pnlButtons.setLayout(new BoxLayout(pnlButtons, BoxLayout.LINE_AXIS));
        pnlButtons.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
           pnlButtons.add(Box.createHorizontalGlue());
           pnlButtons.add(Box.createRigidArea(new Dimension(10, 0)));
           JButton btnOk = new JButton(I18N.get("ok"));
           btnOk.addActionListener(this);
           btnOk.setActionCommand("ok");
           pnlButtons.add(btnOk);
           pnlButtons.setLayout(new BoxLayout(pnlButtons, BoxLayout.LINE_AXIS));
           JButton btnHompePage = new JButton(I18N.get("dialog.about.button.homepage"));
           btnHompePage.addActionListener(this);
           btnHompePage.setActionCommand("homepage");
           pnlButtons.add(btnHompePage);
           pnlButtons.setLayout(new BoxLayout(pnlButtons, BoxLayout.LINE_AXIS));
       cp.add(pnlButtons);


		pack();
	}


	private void addText(String s, int fontStyle, int fontSize) {
		JLabel lbl = new JLabel(s);
		lbl.setFont(new Font("Serif", fontStyle, fontSize));
		Box box = Box.createHorizontalBox();
		box.add(Box.createHorizontalStrut(30));
		box.add(lbl);
		box.add(Box.createHorizontalStrut(30));
		getContentPane().add(box);
	}

	private void addText(String s) {
		JLabel lbl = new JLabel(s);
		Box box = Box.createHorizontalBox();
		box.add(Box.createHorizontalStrut(30));
		box.add(lbl);
		box.add(Box.createHorizontalStrut(30));
		getContentPane().add(box);
	}



	@Override
	public void actionPerformed(ActionEvent e) {
		if ( e.getActionCommand().equals("ok") ) {
			setVisible(false);
		} else if ( e.getActionCommand().equals("homepage") ) {
			try {
				java.awt.Desktop.getDesktop().browse(new URI(Words.URL));
			} catch (IOException e1) {
			} catch (URISyntaxException e1) {
			}
		}
	}

}
