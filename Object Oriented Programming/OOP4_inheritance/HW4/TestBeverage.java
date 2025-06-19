package HW4;

public class TestBeverage {

	public static void main(String[] args) {
		Beverage drink = new Pearl() ;
		drink = new GreenTea(drink);
		drink = new Suger(drink);
		System.out.print(drink.getIngredient());
		System.out.println(drink.getCost());
		//¿}ºñ¯ù¬Ã¯]35
		drink = new BlackTea();
		drink = new Pearl(drink);
		drink = new Milk(drink);
		System.out.print(drink.getIngredient());
		System.out.println(drink.getCost());
		//¤û¥¤¬Ã¯]¬õ¯ù50
	}

}
