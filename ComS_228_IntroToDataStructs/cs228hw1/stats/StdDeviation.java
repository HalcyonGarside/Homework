package cs228hw1.stats;

import java.util.ArrayList;
import java.lang.Math;

/**
 * A class that calculates the standard deviation of a set of numbers within an ArrayList
 * @author William Blanchard
 */
public class StdDeviation<T extends Number> extends StatCalc<T> {
	
	public StdDeviation() {
		
	}

	public StdDeviation(ArrayList<T> data) {
		super(data);
	}

	/**
	 * Returns the standard deviation of a set of numbers inside of an ArrayList
	 * @return the standard deviation in a given set of numbers as an ArrayList
	 * @throws RuntimeException if the current data ArrayList is null or has zero elements.
	 */
	public ArrayList<Number> GetResult() throws RuntimeException{
		
		//Gets the data ArrayList and determines if it is fit to get a standard deviation from.
		ArrayList<T> dat = GetData();
		if(dat == null || dat.size() == 0) {
			throw new RuntimeException("There must be data to average in the array.");
		}
		
		//Gets the average (mean) of the data using the Average class
		Average<T> a = new Average<T>(dat);
		double ave = (double)a.GetResult().get(0);
		
		//Creates the variable being used for the numerator in the standard deviation equation.
		double num = 0.0;
		
		//Computes the numerator of the standard deviation equation
		for(Number i : dat) {
			num += Math.pow((i.doubleValue() - ave), 2);
		}
		
		
		
		//Creates an ArrayList that holds the standard deviation of the data set.
		//This is the square root of the calculated numerator over the number of samples in the set minus 1.
		ArrayList<Number> result = new ArrayList<Number>();
		result.add(Math.sqrt(num / (dat.size() - 1)));
		
		return result;
	}
	
}
