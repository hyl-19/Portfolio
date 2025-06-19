package HW3;

public class ControlSoundbox implements Command {
	private Soundbox soundbox = new Soundbox();
	public ControlSoundbox() {
		
	}
	
	public ControlSoundbox(Soundbox soundbox) {
		this.soundbox = soundbox ;
	}
	
	public void execute() {
		if(soundbox.getLevel() ==0) {
			soundbox.low();
		}
		else if (soundbox.getLevel() ==1) {
			soundbox.medium();
		}
		else if (soundbox.getLevel() ==2) {
			soundbox.high();
		}
		else if (soundbox.getLevel()==3) {
			soundbox.off();
		}
		
	}

}
