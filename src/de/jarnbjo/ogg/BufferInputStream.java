/*
 */

package de.jarnbjo.ogg;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;


/**
 * Implementation of the <code>PhysicalOggStream</code> interface for accessing
 * normal disk files.
 */

public class BufferInputStream implements PhysicalOggStream {

	private boolean closed = false;
	private long[] pageOffsets;
//	private long numberOfSamples = -1;
	
	private SeekedByteArrayInputStream source;

	private HashMap<Integer, LogicalOggStreamImpl> logicalStreams = new HashMap<Integer, LogicalOggStreamImpl>();

	/**
	 * Creates access to the specified file through the
	 * <code>PhysicalOggStream</code> interface. The specified source file must
	 * have been opened for reading.
	 * 
	 * @param source
	 *           the file to read from
	 * 
	 * @throws OggFormatException
	 *            if the stream format is incorrect
	 * @throws IOException
	 *            if some other IO error occurs when reading the file
	 */

	public BufferInputStream(byte[] data) throws OggFormatException, IOException {		
		source = new SeekedByteArrayInputStream(data);
		
		ArrayList<Long> po = new ArrayList<Long>();
		int pageNumber = 0;
		try {
			while ( true ) {
				po.add(new Long(source.getPos()));

				// skip data if pageNumber>0
				OggPage op = getNextPage(pageNumber > 0);
				if ( op == null ) {
					break;
				}

				LogicalOggStreamImpl los = (LogicalOggStreamImpl) getLogicalStream(op.getStreamSerialNumber());
				if ( los == null ) {
					los = new LogicalOggStreamImpl(this, op.getStreamSerialNumber());
					logicalStreams.put(new Integer(op.getStreamSerialNumber()), los);
				}

				if ( pageNumber == 0 ) {
					los.checkFormat(op);
				}

				los.addPageNumberMapping(pageNumber);
				los.addGranulePosition(op.getAbsoluteGranulePosition());

				if ( pageNumber > 0 ) {
					source.seek(source.getPos() + op.getTotalLength());
				}

				pageNumber++;
			}
		} catch (EndOfOggStreamException e) {
			// ok
		} catch (IOException e) {
			throw e;
		}
		// System.out.println("pageNumber: "+pageNumber);
		source.seek(0L);
		pageOffsets = new long[po.size()];
		int i = 0;
		Iterator<Long> iter = po.iterator();
		while ( iter.hasNext() ) {
			pageOffsets[i++] = iter.next().longValue();
		}
	}

	public Collection<LogicalOggStreamImpl> getLogicalStreams() {
		return logicalStreams.values();
	}

	public boolean isOpen() {
		return !closed;
	}

	public void close() throws IOException {
		closed = true;
		source.close();
	}

//	private OggPage getNextPage() throws EndOfOggStreamException, IOException, OggFormatException {
//		return getNextPage(false);
//	}

	private OggPage getNextPage(boolean skipData)	throws EndOfOggStreamException, IOException, OggFormatException {
		return OggPage.create(source, skipData);
	}

	public OggPage getOggPage(int index) throws IOException {
		source.seek(pageOffsets[index]);
		return OggPage.create(source);
	}

	private LogicalOggStream getLogicalStream(int serialNumber) {
		return (LogicalOggStream) logicalStreams.get(new Integer(serialNumber));
	}

	public void setTime(long granulePosition) throws IOException {
		for (Iterator<LogicalOggStreamImpl> iter = logicalStreams.values().iterator(); iter.hasNext();) {
			LogicalOggStream los = iter.next();
			los.setTime(granulePosition);
		}
	}

	/**
	 * @return always <code>true</code>
	 */

	public boolean isSeekable() {
		return true;
	}
	
	private class SeekedByteArrayInputStream extends ByteArrayInputStream {

		public SeekedByteArrayInputStream(byte[] data) throws IOException {
			super(data);
		}
		
		public void seek(long p) {
			pos = (int)p;
		}
		
		public long getPos() {
			return pos;
		}

	}

}