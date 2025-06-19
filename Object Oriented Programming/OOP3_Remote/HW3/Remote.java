package HW3;

public class Remote {
    Command [] buttons = new Command [5];  // 5�ӫ��s�A��ڤW�����ӳ]�w��Object class�A�o��O�ܽd
    
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
     * �����ҰʩҦ����˸m(�N�Y�A�C�Ӹ˸m�����s�����@�U)
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
