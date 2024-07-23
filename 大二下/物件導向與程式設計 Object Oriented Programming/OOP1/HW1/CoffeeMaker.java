package HW1 ;
public class CoffeeMaker extends BeverageMaker {
	
	public void addIce( ) {
		System.out.println("加冰");
	}
	
	public void brew() { //brewCoffee
		System.out.println("把熱水倒進磨好的咖啡粉");
	}
	
	 public void addCondiments() { // addSugarAndMilk
		 System.out.println("添加糖或牛奶等額外添加物");
	 }	 
}
