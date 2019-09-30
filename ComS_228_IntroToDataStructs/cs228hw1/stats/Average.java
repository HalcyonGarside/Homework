package cs228hw1.stats;

import java.util.ArrayList;

/**
 * A class that calculates the average of a set of Ts within an ArrayList
 * @author William Blanchard
 */
public class Average<T extends Number> extends StatCalc<T>{
	
	public Average() {
		
	}
	
	public Average(ArrayList<T> data) {
		super(data);
	}
	
	/**
	 * Returns the average in a set of Ts inside of an ArrayList
	 * @return the average in a given set of Ts as an ArrayList
	 * @throws RuntimeException if the current data ArrayList is null or has zero elements.
	 */
	public ArrayList<Number> GetResult() throws RuntimeException{
		
		//Gets the data ArrayList and determines if it is fit to get an average from.
		ArrayList<T> dat = GetData();
		if(dat == null || dat.size() == 0) {
			throw new RuntimeException("There must be data to average in the array.");
		}
		
		dat = sortArray(dat);
		
		//Adds all elements of the data together and counts how many points there are.
		int i;
		double total = 0;
		for(i = 0; i < dat.size(); i++) {
			total += dat.get(i).doubleValue();
		}
		
		//Creates an ArrayList that holds the resulting average of the data set.
		ArrayList<Number> result = new ArrayList<Number>();
		result.add(total / i);
		
		return result;
	}
	
}
