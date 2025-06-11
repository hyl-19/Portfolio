package HW2 ;
public class Work implements Compare {
	String name ;
	
	public Work(String temp) {
		name = temp ;
	}
	
	public int compare(Compare in) {
		Work temp = (Work) in ;
		
		if ( this.name.compareTo(temp.name) < 0 )
			return 1;   // 
		else 
			return -1;  // 
		
	}
}
