package HW3;

public class ControlTV implements Command {
	private Television tv = new Television() ;
	public ControlTV () {
		
	}
	
	public ControlTV(Television tv) {
		this.tv = tv ;
	}
	
	public void execute() {
		
		if ( tv.getStatus() == true ) {
			tv.off() ;
		}
		else if ( tv.getStatus() == false ) {
			tv.on() ;
		}
	}
	
	
}
