package cs228hw1.stats;

import java.util.ArrayList;

/**
 * A class that calculates the maximum of a set of numbers within an ArrayList
 * @author William Blanchard
 */
public class Maximum<T extends Number> extends StatCalc<T>{
	
	public Maximum() {
		
	}

	public Maximum(ArrayList<T> data) {
		super(data);
	}

	/**
	 * Returns the maximum in a set of numbers inside of an ArrayList
	 * @return the maximum in a given set of numbers as an ArrayList
	 * @throws RuntimeException if the current data ArrayList is null or has zero elements.
	 */
	public ArrayList<Number> GetResult() throws RuntimeException{
		
		//Gets the data ArrayList and determines if it is fit to get a maximum from.
		ArrayList<T> dat = GetData();
		if(dat == null || dat.size() == 0) {
			throw new RuntimeException("There must be data to average in the array.");
		}
		
		//Sorts the ArrayList from smallest to largest
		dat = sortArray(dat);
		
		//Creates an ArrayList that holds the last number of the data set (the maximum).
		ArrayList<Number> result = new ArrayList<Number>();
		result.add(dat.get(dat.size() - 1));
		
		return result;
	}
	
}
