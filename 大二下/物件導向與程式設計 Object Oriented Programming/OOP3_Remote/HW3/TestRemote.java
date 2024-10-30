package HW3;

public class TestRemote {

	public static void main(String[] args) {
		ControlTV tv = new ControlTV() ;
		Controllight light = new Controllight() ;
		ControlSoundbox soundbox = new ControlSoundbox() ;
		Remote r = new Remote(tv, light, soundbox, null, null) ;
		r.buttonClicked(0);
		r.buttonClicked(0);
		r.buttonClicked(1);
		r.buttonClicked(1);
		r.buttonClicked(1);
		r.buttonClicked(2);
		r.buttonClicked(2);
		r.buttonClicked(2);
		r.buttonClicked(2);
		
		r.pressAllButtons();
	}

}
