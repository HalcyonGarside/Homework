package cs228hw1.stats;

import java.util.ArrayList;

/**
 * A class that calculates the histogram of a set of numbers within an ArrayList to the user's preference
 * @author William Blanchard
 */
public class Histogram<T extends Number> extends StatCalc<T>{
	
	private int numBins;
	private Number minRange;
	private Number maxRange;
	
	public Histogram() {
		numBins = 10;
		minRange = Double.NEGATIVE_INFINITY;
		maxRange = Double.POSITIVE_INFINITY;
	}

	public Histogram(ArrayList<T> data) {
		super(data);
		numBins = 10;
		minRange = Double.NEGATIVE_INFINITY;
		maxRange = Double.POSITIVE_INFINITY;
	}

	/**
	 * Returns the histogram of numbers inside of an ArrayList within a given range.
	 * @return the histogram of a given set of numbers within a given range as an ArrayList.
	 * @throws RuntimeException if the current data ArrayList is null or the minimum range is higher than the maximum range.
	 */
	public ArrayList<Number> GetResult() throws RuntimeException{
		
		//Determines if this histogram has the proper parameters to run the calculations.
		if(minRange.doubleValue() > maxRange.doubleValue()) {
			throw new RuntimeException("The max range of the histogram must be higher than the min range.");
		}
		
		//Gets the data ArrayList and determines if it is fit to get a histogram from.
		ArrayList<T> dat = GetData();
		if(dat == null) {
			throw new RuntimeException("There must be data to create a histogram with in the array.");
		}
		
		//Calculates how big the interval of each bin is.
		double interval = ((maxRange.doubleValue() - minRange.doubleValue()))/ (double)numBins;
		
		dat = sortArray(dat);
		
		//Initializes the first bin's start and end values.
		double st = minRange.doubleValue();
		double en = st + interval;
		
		//Creates the variable to indicate how many numbers are within a certain bin in the histogram.
		int iter;
		
		//Creates an ArrayList that holds the integers that are the bins of the histogram.
		ArrayList<Number> result = new ArrayList<Number>();
		for(int i = 0; i < numBins; i++) {
			result.add(0);
		}
		
		int i = 0;
		
		//Initializes i to an index of the data that is within the range of the histogram.
		while(dat.get(i).doubleValue() < minRange.doubleValue()) {
			i++;
		}
		
		
		
		/*
		 * For each bin in the result array, the for loop counts how many numbers fit within the individual
		 * bin (between the values of st and en).  After it counts that, it sets that number to its
		 * respective bin in the result array, resets the values of st and en for the next bin, and sets iter
		 * back to zero.  If the data array's size is reached, the loop breaks.
		 */
		for(int j = 0; j < numBins; j++) {
			iter = 0;
			
			
			while(dat.size() > i && dat.get(i).doubleValue() < en) {
				
				if(dat.get(i).doubleValue() == en) break;
				if(dat.get(i) == null || dat.get(i).doubleValue() == maxRange.doubleValue()) {
					i++;

				}
				else if((dat.get(i).doubleValue() < en && dat.get(i).doubleValue() >= st) || dat.get(i).doubleValue() == minRange.doubleValue()){
					iter++;
					i++;

				}


			}
			
			result.set(j, iter);
			
			st = en;
			en += interval;
			if(dat.size() == i) break;
		}
		
		System.out.println(result);
		return result;
		
		
	}
	
		
	
	/**
	 * Assigns the number of bins in this Histogram
	 * @param num - the number of bins in this Histogram
	 */
	public void SetNumberBins(int num) {
		numBins = num;
	}
	
	/**
	 * Returns the number of bins in this Histogram
	 * @return the number of bins in this Histogram
	 */
	public int GetNumberBins() {
		return numBins;
	}
	
	/**
	 * Assigns the lowest number to be included in this Histogram
	 * @param num - the lowest number to be included in this Histogram
	 */
	public void SetMinRange(Number num) {
		minRange = num;
	}
	
	/**
	 * Returns the lowest number to be included in this Histogram
	 * @return the lowest number to be included in this Histogram
	 */
	public Number GetMinRange() {
		return minRange;
	}
	
	/**
	 * Assigns the highest number to be included in this Histogram
	 * @param num - the highest number to be included in this Histogram
	 */
	public void SetMaxRange(Number num) {
		maxRange = num;
	}
	
	/**
	 * Returns the highest number to be included in this Histogram
	 * @return the highest number to be included in this Histogram
	 */
	public Number GetMaxRange() {
		return maxRange;
	}
	
}
