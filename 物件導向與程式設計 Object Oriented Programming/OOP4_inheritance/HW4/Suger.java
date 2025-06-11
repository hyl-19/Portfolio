package HW4;

public class Suger extends Beverage {
	
	private static int cost = 5 ;
	private static String name = "¿}" ;
	
	public Suger() {
	}
	
	public Suger(Beverage drink) {
		this.drink = drink ;
	}
	
	public String getIngredient() {
		// TODO Auto-generated method stub
		if (drink != null)
			return name + drink.getIngredient() ;
		else
			return name ;
	}
		

	@Override
	public int getCost() {
		// TODO Auto-generated method stub
		if (drink != null)
			return cost + drink.getCost() ;
		else
			return cost ;
		
	}

}
