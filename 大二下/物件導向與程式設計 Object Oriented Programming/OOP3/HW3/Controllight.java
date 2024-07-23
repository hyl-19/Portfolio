package HW3;

public class Controllight implements Command {
	private Light light = new Light() ;
	
	public Controllight () {
		
	}
	
	public Controllight(Light light) {
		this.light = light ;
	}
	
	public void execute() {
		
		if(light.getBrightness() ==0) {
			light.dim();
		}
		else if (light.getBrightness() ==1) {
			light.bright();
		}
		else if (light.getBrightness() ==2) {
			light.off();
		}
	}
	
}
