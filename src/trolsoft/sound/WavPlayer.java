package trolsoft.sound;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.FloatControl;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.SourceDataLine;

public class WavPlayer {

	private static float volume = 100.0F; // volume in percent

	public static float getVolume() {
		return volume;
	}

	public static void setVolume(float volume) {
		WavPlayer.volume = volume;
	}

	// Plays audio from given file names.
/*	
	public static void main(String[] args) {
		// Check for given sound file names.
		if ( args.length < 1 ) {
			System.out.println("Play usage:");
			System.out.println("\tjava Play <sound file names>*");
			System.exit(0);
		}

		// Process arguments.
		for (int i = 0; i < args.length; i++)
			playFile(args[i]);

		// Must exit explicitly since audio creates non-daemon threads.
		System.exit(0);
	} // main
*/
	
	/**
	 * 
	 */
	public static void playFile(String fileName) {
		File soundFile = new File(fileName);

		try {
			// Create a stream from the given file.
			// Throws IOException or UnsupportedAudioFileException
			AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(soundFile);
			playAudioStream(audioInputStream);
		} catch (Exception e) {
			System.out.println("Problem with wav-audio file " + fileName + ":");
			e.printStackTrace();
		}
	}
	
	/**
	 * 
	 * @param data
	 */
	public static void playData(byte[] data) {
		final ByteArrayInputStream is = new ByteArrayInputStream(data);
		playStream(is);
	}

	/**
	 * 
	 * @param is
	 */
	public static void playStream(InputStream is) {
		try {
			// Create a stream from the given file.
			// Throws IOException or UnsupportedAudioFileException
			AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(is);
			playAudioStream(audioInputStream);
		} catch (Exception e) {
			System.out.println("Problem with audio :");
			e.printStackTrace();
		}
	}

	/**
	 * Plays audio from the given audio input stream
	 * 
	 * @param audioInputStream
	 */
	public static void playAudioStream(AudioInputStream audioInputStream) {
		// Audio format provides information like sample rate, size, channels.
		AudioFormat audioFormat = audioInputStream.getFormat();
		// System.out.println( "Play input audio format=" + audioFormat );

		// Open a data line to play our type of sampled audio.
		// Use SourceDataLine for play and TargetDataLine for record.
		DataLine.Info info = new DataLine.Info(SourceDataLine.class, audioFormat);
		if ( !AudioSystem.isLineSupported(info) ) {
			System.out.println("Play.playAudioStream does not handle this type of audio on this system.");
			return;
		}
		
		try {
			// Create a SourceDataLine for play back (throws
			// LineUnavailableException).
			SourceDataLine dataLine = (SourceDataLine) AudioSystem.getLine(info);
			//SourceDataLine sourceDataLine = (SourceDataLine)AudioMixer.getInstance().getLine(dataLineInfo);
			// System.out.println( "SourceDataLine class=" + dataLine.getClass() );

			// The line acquires system resources (throws LineAvailableException).
			dataLine.open(audioFormat);

			// Adjust the volume on the output line.
			if ( dataLine.isControlSupported(FloatControl.Type.MASTER_GAIN) ) {
				FloatControl volumeControl = (FloatControl) dataLine.getControl(FloatControl.Type.MASTER_GAIN);

				float vol = volumeControl.getMinimum() + volume	* (volumeControl.getMaximum() - volumeControl.getMinimum())	/ 100.0F;
				if ( vol < volumeControl.getMinimum() ) {
					vol = volumeControl.getMinimum();
				}
				if ( vol > volumeControl.getMaximum() ) {
					vol = volumeControl.getMaximum();
				}
				volumeControl.setValue(vol);
			}

			// Allows the line to move data in and out to a port.
			dataLine.start();

			// Create a buffer for moving data from the audio stream to the line.
			int bufferSize = (int) audioFormat.getSampleRate()
					* audioFormat.getFrameSize();
			byte[] buffer = new byte[bufferSize];

			// Move the data until done or there is an error.
			try {
				int bytesRead = 0;
				while ( bytesRead >= 0 ) {
					bytesRead = audioInputStream.read(buffer, 0, buffer.length);
					if ( bytesRead >= 0 ) {
						// System.out.println( "Play.playAudioStream bytes read=" +
						// bytesRead +
						// ", frame size=" + audioFormat.getFrameSize() +
						// ", frames read=" + bytesRead / audioFormat.getFrameSize()
						// );
						// Odd sized sounds throw an exception if we don't write the
						// same amount.
						// int framesWritten =
						dataLine.write(buffer, 0, bytesRead);
					}
				} // while
			} catch (IOException e) {
				e.printStackTrace();
			}

			// System.out.println( "Play.playAudioStream draining line." );
			// Continues data line I/O until its buffer is drained.
			dataLine.drain();

			// System.out.println( "Play.playAudioStream closing line." );
			// Closes the data line, freeing any resources such as the audio
			// device.
			dataLine.close();
		} catch (LineUnavailableException e) {
			e.printStackTrace();
		}
	} // playAudioStream
} // Play