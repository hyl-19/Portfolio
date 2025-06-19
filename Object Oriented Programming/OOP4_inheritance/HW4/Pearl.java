package HW4;

public class Pearl extends Beverage {
	
	private static int cost = 10 ;
	private static String name = "�ï]" ;
	
	public Pearl() {
	}
	
	public Pearl(Beverage drink) {
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
