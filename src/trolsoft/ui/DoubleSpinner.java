package trolsoft.ui;

import java.text.NumberFormat;

import javax.swing.JSpinner;
import javax.swing.SpinnerModel;
import javax.swing.event.ChangeListener;

public class DoubleSpinner extends JSpinner {
	private static final long serialVersionUID = 1L;
	
	private double value;
	private double increment;
	private Double min;
	private Double max;
	
	private NumberFormat formatter = NumberFormat.getInstance();
	

	/**
	 * 
	 */
	private SpinnerModel model = new SpinnerModel() {
		@Override
		public Object getValue() {
			return value;
		}

		@Override
		public void setValue(Object val) {
			value = (Double)val;
			value = validateValue(value);
			((JSpinner.DefaultEditor)DoubleSpinner.this.getEditor()).getTextField().setText(getValueAsString());
		}

		@Override
		public Object getNextValue() {
			return validateValue(value + increment);
		}

		@Override
		public Object getPreviousValue() {
			return validateValue(value - increment);
		}

		@Override
		public void addChangeListener(ChangeListener l) {
			// TODO Auto-generated method stub
		}

		@Override
		public void removeChangeListener(ChangeListener l) {
			// TODO Auto-generated method stub
		}
		
	};
	
	/**
	 * 
	 * @param value
	 * @param increment
	 */
	public DoubleSpinner(double value, double increment) {
		super();
		this.value = value;
		this.increment = increment;
		setValue(new Double(value));
		setModel(model);
		formatter.setMaximumFractionDigits(1);
	}
	
	
	/**
	 * 
	 * @param min
	 * @param max
	 */
	public DoubleSpinner setRange(Double min, Double max) {
		this.min = min;
		this.max = max;
		value = validateValue(value);
		return this;
	}
	
	
	/**
	 * 
	 * @param min
	 * @param max
	 */
	public DoubleSpinner setRange(Integer min, Integer max) {
		this.min = min != null ? new Double(min) : null;
		this.max = max != null ? new Double(max) : null;
		return this;
	}
	
	
	/**
	 * 
	 * @param fractionDigits
	 * @return
	 */
	public DoubleSpinner setPrecesion(int fractionDigits) {
		formatter.setMaximumFractionDigits(fractionDigits);
		return this;
	}
	
	
	@Override
	public Object getValue() {
		return value;
	}
	
	/**
	 * 
	 */
	private double validateValue(double value) {
		if ( min != null && value < min ) {
			value = min;
		}
		if ( max != null && value > max ) {
			value = max;
		}
		return value;
	}
	
	/**
	 * 
	 * @return
	 */
	public String getValueAsString() {
		return formatter.format(value);
	}
	
	/**
	 * 
	 * @return
	 */
	public int getValueAsInt() {
		return (int)value;
	}
	
	
	/**
	 * 
	 * @return
	 */
	public double getValueAsDouble() {
		return value;
	}

}
