package HW4;

public class BlackTea extends Beverage {
	private static int cost = 20 ;
	private static String name = "����";
	
	public BlackTea() {
	}
	
	public BlackTea(Beverage tea) {
		this.drink = tea ;
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
