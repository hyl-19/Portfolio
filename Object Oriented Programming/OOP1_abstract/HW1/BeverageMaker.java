package HW1 ;
public abstract class BeverageMaker {
	  final void prepare() {
		  boilWater();     
		  brew();          
		  pourInCup();    
		  addIce() ;
		  addCondiments(); 
	  }
	  abstract void brew() ;
	  abstract void addCondiments() ;
	  
	  public void addIce() {} ;
	  
	  public void boilWater() {
	    System.out.println("�N��");
	  }
	  
	  public void pourInCup() {
	    System.out.println("�˶i�M�l");
	  }

}
