package HW1 ;
public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		TeaMaker Tworker = new TeaMaker() ;
		Tworker.prepare();
		System.out.println( "-------------------" );
		CoffeeMaker Cworker = new CoffeeMaker() ;
		Cworker.prepare();
	}

}
