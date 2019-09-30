package cs228hw1.stats;

import java.util.ArrayList;

/**
 * A class that calculates the median of a set of numbers within an ArrayList
 * @author William Blanchard
 */
public class Median<T extends Number> extends StatCalc<T>{

	public Median() {
		
	}
	
	public Median(ArrayList<T> data) {
		super(data);
	}
	
	/**
	 * Returns the median in a set of numbers inside of an ArrayList
	 * @return the median in a given set of numbers as an ArrayList
	 * @throws RuntimeException if the current data ArrayList is null or has zero elements.
	 */
	public ArrayList<Number> GetResult() throws RuntimeException{
		
		//Gets the data ArrayList and determines if it is fit to get a median from.
		ArrayList<T> dat = GetData();
		if(dat == null || dat.size() == 0) {
			throw new RuntimeException("There must be data to average in the array.");
		}
		
		//Sorts the data array to get the numbers in order.
		dat = sortArray(dat);
		
		//Creates a variable to hold the true median of the data set.
		Number median;
		
		//If the number of Numbers in the data is odd, it takes the number in the middle of the array.
		if(dat.size() % 2 == 1) {
			if(dat.size() / 2 > 0) {
				median = dat.get((dat.size() / 2));
			}else {
				median = dat.get(0);
			}
		}
		//Otherwise, it takes the numbers immediately below and above the middle and finds their average.
		else {
			double a = dat.get((dat.size() / 2) - 1).doubleValue();
			double b = dat.get((dat.size() / 2)).doubleValue();
			
			median = (a + b) / 2;
		}
		
		//Creates a resulting ArrayList and makes its only element the previously computed median.
		ArrayList<Number> result = new ArrayList<Number>();
		result.add(median);
		
		return result;
	}
	

	
}
