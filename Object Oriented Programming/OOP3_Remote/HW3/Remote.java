package HW3;

public class Remote {
    Command [] buttons = new Command [5];  // 5個按鈕，實際上不應該設定成Object class，這邊是示範
    
    public Remote(Command odj1, Command odj2, Command odj3, Command odj4, Command odj5) {
    	buttons[0] = odj1 ;
    	buttons[1] = odj2 ;
    	buttons[2] = odj3 ;
    	buttons[3] = odj4 ;
    	buttons[4] = odj5 ;
    }
    
    void buttonClicked(int buttonId) {
       Command o = buttons[buttonId] ;
       o.execute() ;
    }
    
    /**
     * 直接啟動所有的裝置(意即，每個裝置的按鈕都按一下)
     */
    void pressAllButtons() {
        for ( int i = 0; i < buttons.length; i++ ) {
        	if ( buttons[i]==null ) {
        		continue ;
        	}
            buttonClicked(i);
        }
    }
}
