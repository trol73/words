package trolsoft.sound;

import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Mixer;

public class AudioMixer {
	
	private static Mixer mixer;
	
	public static Mixer getInstance() {
		if ( mixer != null ) {
			return mixer;
		}
		try {
			mixer = AudioSystem.getMixer(null);
			if ( mixer != null ) {
				return mixer;
			}
		} catch (Exception e) {
		}
		Mixer.Info[] mixerInfo = AudioSystem.getMixerInfo();
		for ( Mixer.Info info : mixerInfo ) {
			try {
				mixer = AudioSystem.getMixer(info);
				if ( mixer != null ) {
					return mixer;
				}
			} catch (Exception e) {
			}
		}
		
		return mixer;
	}

}
