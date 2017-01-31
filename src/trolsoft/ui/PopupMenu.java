package trolsoft.ui;

import javax.swing.JMenuItem;



public class PopupMenu {
	private java.awt.PopupMenu awtMenu;
	private javax.swing.JPopupMenu swingMenu;
	
	/**
	 * 
	 * @param swingMode
	 */
	public PopupMenu(boolean swingMode) {
		if ( swingMode ) {
			swingMenu = new javax.swing.JPopupMenu();
		} else {
			awtMenu = new java.awt.PopupMenu();
		}
	}
	
	
	/**
	 * 
	 * @param name
	 * @param enabled
	 */
    public void setMenuItemEnabled(String name, boolean enabled) {
    	int index = findItem(name);
    	if ( index >= 0 ) {
    		enableItem(index, enabled);
    	}
    }
    
    /**
     * 
     * @return
     */
    public int getItemCount() {
    	return awtMenu != null ? awtMenu.getItemCount() : swingMenu.getComponentCount(); 
    }
    
    
    /**
     * 
     * @param label
     */
    public void add(String label) {
    	if ( awtMenu != null ) {
    		awtMenu.add(label);
    	} else {
    		 swingMenu.add(label);
    	}
    }
    
    
    /**
     * 
     */
    public void addSeparator() {
    	if ( awtMenu != null ) {
    		awtMenu.addSeparator();
    	} else {
    		 swingMenu.addSeparator();
    	}    	
    }
    
    
    /**
     * 
     * @param index
     */
    public void enableItem(int index, boolean enabled) {
    	if ( awtMenu != null ) {
    		awtMenu.getItem(index).setEnabled(enabled);
    	} else {
    		JMenuItem mi = (JMenuItem)swingMenu.getComponent(index);
    		mi.setEnabled(enabled);
    	}
    }
    
    
    /**
     * 
     * @param index
     * @return
     */
    public String getItemName(int index) {
    	if ( awtMenu != null ) {
    		return awtMenu.getItem(index).getLabel();
    	} else {
    		JMenuItem mi = (JMenuItem)swingMenu.getComponent(index);
    		return mi.getText();
    	}
    }
    
    
    /**
     * 
     * @return
     */
    private int findItem(String label) {
    	int cnt = getItemCount();
    	for ( int i = 0; i < cnt; i++ ) {
    		if ( getItemName(i).equals(label) ) {
    			return i;
    		}
    	}
    	return -1;
    }

}
