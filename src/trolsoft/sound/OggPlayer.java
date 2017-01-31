/*
 * $ProjectName$
 * $ProjectRevision$
 * -----------------------------------------------------------
 * $Id: Player.java,v 1.4 2003/04/10 19:48:40 jarnbjo Exp $
 * -----------------------------------------------------------
 *
 * $Author: jarnbjo $
 *
 * Description:
 *
 * Copyright 2002-2003 Tor-Einar Jarnbjo
 * -----------------------------------------------------------
 *
 * Change History
 * -----------------------------------------------------------
 * $Log: Player.java,v $
 * Revision 1.4  2003/04/10 19:48:40  jarnbjo
 * no message
 *
 * Revision 1.3  2003/04/04 08:32:54  jarnbjo
 * no message
 *
 * Revision 1.2  2003/03/31 00:22:29  jarnbjo
 * no message
 *
 * Revision 1.1  2003/03/16 01:10:45  jarnbjo
 * no message
 *
 */

package trolsoft.sound;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.FloatControl;
import javax.sound.sampled.SourceDataLine;

import de.jarnbjo.ogg.BufferInputStream;
import de.jarnbjo.ogg.EndOfOggStreamException;
import de.jarnbjo.ogg.LogicalOggStream;
import de.jarnbjo.vorbis.VorbisStream;


public class OggPlayer {
	
	private static float volume = 100.0F;	// volume in percent
	
   public static float getVolume() {
		return volume;
	}

   /**
    * 
    * @param volume
    */
	public static void setVolume(float volume) {
		OggPlayer.volume = volume;
	}	

	/**
	 * 
	 * @param fileName
	 */
	public static void playFile(String fileName ) {
		try {
			// Create a stream from the given file.
			// Throws IOException or UnsupportedAudioFileException
		
			int len = (int)new File(fileName).length();
			byte[] buf = new byte[len];
			RandomAccessFile f = new RandomAccessFile(fileName, "rw");
			f.read(buf);
			f.close();
			playData(buf);
			//WavPlayer.playStream(new ByteArrayInputStream(Ogg2Wav.ogg2wav(buf)));
		} catch ( Exception e ) {
			System.out.println( "Problem with ogg audio file " + fileName + ":" );
			e.printStackTrace();
		}
	}
	
	/**
	 * 
	 * @param data
	 */
	public static void playData(byte[] data) {
		try {
			final BufferInputStream os = new BufferInputStream(data);

			// get the first logical Ogg stream
			final LogicalOggStream los=(LogicalOggStream)os.getLogicalStreams().iterator().next();

			if ( los.getFormat() != LogicalOggStream.FORMAT_VORBIS ) {
				System.out.println("Not a plain Ogg/Vorbis-file. Unable to play.");
				return;
			}

			final VorbisStream vs = new VorbisStream(los);

//			System.out.println("Title:  " + vs.getCommentHeader().getTitle());
//			System.out.println("Artist: " + vs.getCommentHeader().getArtist());

			VorbisInputStream vis = new VorbisInputStream(vs);

			AudioFormat audioFormat = new AudioFormat(
					(float)vs.getIdentificationHeader().getSampleRate(),
					16,
					vs.getIdentificationHeader().getChannels(),
					true, true);

			AudioInputStream ais = new AudioInputStream(vis, audioFormat, -1);
			DataLine.Info dataLineInfo = new DataLine.Info(SourceDataLine.class, audioFormat);
			
			if ( !AudioSystem.isLineSupported(dataLineInfo) ) {
				System.out.println("Play.playAudioStream does not handle this type of audio on this system.");
				return;
			}
			

			//SourceDataLine sourceDataLine = (SourceDataLine)AudioSystem.getLine(dataLineInfo);
			SourceDataLine sourceDataLine = (SourceDataLine)AudioMixer.getInstance().getLine(dataLineInfo);

			sourceDataLine.open(audioFormat);
			
			// Adjust the volume on the output line.
			if ( sourceDataLine.isControlSupported(FloatControl.Type.MASTER_GAIN) ) {
				FloatControl volumeControl = (FloatControl) sourceDataLine.getControl(FloatControl.Type.MASTER_GAIN);

				float vol = volumeControl.getMinimum() + volume * (volumeControl.getMaximum() - volumeControl.getMinimum())	/ 100.0F;
				if ( vol < volumeControl.getMinimum() ) {
					vol = volumeControl.getMinimum();
				}
				if ( vol > volumeControl.getMaximum() ) {
					vol = volumeControl.getMaximum();
				}
				volumeControl.setValue(vol);
			}
			// виснет в этом месте при некоторых частотах дискретизации звука, например, 22кГц не работает, а 11 и 44 кГц работают нормально
			sourceDataLine.start();

			byte[] buffer = new byte[8192];
			int cnt = 0;
			int iterationsCnt = 0 ;
			while ( (cnt = ais.read(buffer, 0, buffer.length)) != -1 ) {
				if ( cnt > 0 ) {
					iterationsCnt++;
					sourceDataLine.write(buffer, 0, cnt);
				} //end if
			} //end while
			
			
			// иногда слишком короткие звуки "проглатываются", не воспроизводятся
			// для их гарантированного воспроизведения выведем в линию блок нулей
			if ( iterationsCnt < 30 ) {
				for ( int i = 0; i < buffer.length; i++) {
					buffer[i] = 0;
				}
				sourceDataLine.write(buffer, 0, buffer.length);
			}
			sourceDataLine.drain();
			sourceDataLine.close();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}

	// Plays audio from given file names.
/*	
	   public static void main( String [] args ) {
	      // Check for given sound file names.
	      if (args.length < 1) {
	         System.out.println( "Play usage:" );
	         System.out.println( "\tjava Play <sound file names>*" );
	         System.exit( 0 );
	      }
	 
	      // Process arguments.
	      for (int i = 0; i < args.length; i++ ) 
	         playFile( args[ i ] );
	   
	      // Must exit explicitly since audio creates non-daemon threads.
	      System.exit( 0 );
	   } // main
*/
	
	
	public static class VorbisInputStream extends InputStream {
		private VorbisStream source;
//		private byte[] buffer=new byte[8192];

		
		public VorbisInputStream(VorbisStream source) {
			this.source = source;
		}

		
		public int read() throws IOException {
			return 0;
		}

		
		public int read(byte[] buffer) throws IOException {
			return read(buffer, 0, buffer.length);
		}

		
		public int read(byte[] buffer, int offset, int length) throws IOException {
			try {
				return source.readPcm(buffer, offset, length);
			} catch(EndOfOggStreamException e) {
				return -1;
			}
		}
	}

}