package cs228hw1.stats;

import java.util.ArrayList;

/**
 * A class that calculates the minimum of a set of numbers within an ArrayList
 * @author William Blanchard
 */
public class Minimum <T extends Number> extends StatCalc<T>{
	
	public Minimum() {
		
	}
	
	public Minimum(ArrayList<T> data) {
		super(data);
	}

	/**
	 * Returns the minimum in a set of numbers inside of an ArrayList
	 * @return the minimum in a given set of numbers as an ArrayList
	 * @throws RuntimeException if the current data ArrayList is null or has zero elements.
	 */
	public ArrayList<Number> GetResult() throws RuntimeException{
		
		//Gets the data ArrayList and determines if it is fit to get a minimum from.
		ArrayList<T> dat = GetData();
		if(dat == null || dat.size() == 0) {
			throw new RuntimeException("There must be data to average in the array.");
		}
		
		ArrayList<T>res = new ArrayList<T>();
		
		//Sorts the ArrayList from smallest to largest
		res = sortArray(dat);
		
		//Creates an ArrayList that holds the first number of the data set (the minimum).
		ArrayList<Number> result = new ArrayList<Number>();
		result.add(res.get(0));
		
		return result;
	}
	
	
}
