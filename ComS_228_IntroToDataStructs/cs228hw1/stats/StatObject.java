package cs228hw1.stats;

import java.util.ArrayList;

/**
 * An abstraction of a statistical calculation.
 * @param <T> The type of data to be used in the calculation. Must be a number of some variety.
 * @author Don Nye
 */
public interface StatObject<T extends Number>
{
	/**
	 * @param d is the description to set for this statistics object.
	 */
	void SetDescription(String d);
	
	/**
	 * @return the currently set description.
	 */
	String GetDescription();
	
	/**
	 * Returns the result of this statistical function in an ArrayList.
	 * If the result is a single value, it should be the sole element of the array.
	 * If the result consists of multiple values, order is important.
	 * @throws RuntimeException Thrown if the data in this StatObject is null or empty.
	 */
	ArrayList<Number> GetResult() throws RuntimeException;
	
	/**
	 * Changes the data to be used in the calculations for this StatObject.
	 * A deep copy of all the data will be made.
	 * @param data The new data.
	 */
	void SetData(ArrayList<T> data);
	
	/**
	 * Returns a deep copy of the data used in the calculations for this StatObject.
	 */
	ArrayList<T> GetData();
}