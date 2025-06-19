package HW2 ;
public class MyUtility {

	public void mySort(Object arr[]) {
		int arraylen = arr.length ;
		
		for ( int i = 0 ; i < arraylen ; i++ ) {
			if (!(arr[i] instanceof Compare)) 
				return ;
		}
		
		Compare list[] = (Compare[]) arr ;
	  
		for ( int i = 0; i < arraylen; i++ ) {
			for ( int j = 0; j < arraylen ; j++ ) { 
				if ( list[i].compare(list[j]) == 1 ) {
					Compare tmp = list[j];
					list[j] = list[i];
					list[i] = tmp;
				}
			}
		}
	
	}
	
}
