package HW2 ;
public class Test {

	public static void main(String[] args) {
		Work [] list = new Work[5] ;
		list[0] = new Work("5") ;
		list[1] = new Work("1") ;
		list[2] = new Work("3") ;
		list[3] = new Work("8") ;
		list[4] = new Work("4") ;
		
		MyUtility util = new MyUtility() ;
		
		util.mySort(list);
		for ( int i = 0 ; i < list.length ; i++) {
			System.out.println( list[i].name ) ;
		}
	}

}
