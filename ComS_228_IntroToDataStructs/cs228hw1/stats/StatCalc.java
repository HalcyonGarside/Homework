package cs228hw1.stats;

import java.util.ArrayList;

/**
 * An abstract class assigned to each StatObject to get rid of repetitive code
 * @author William Blanchard
 */

public abstract class StatCalc<T extends Number> implements StatObject<T>{
	
	/**
	 * The description of this StatCalc
	 */
	private String desc;
	
	/**
	 * The data contained within this StatCalc
	 */
	private ArrayList<T> dat;
	
	protected StatCalc() {
		dat = new ArrayList<T>();
		desc = "";
	}
	
	protected StatCalc(ArrayList<T> d) {
		desc = "";
		dat = new ArrayList<T>();
		dat.addAll(d);
	}
	
	/**
	 * Sets this StatCalc's description
	 */
	public void SetDescription(String d) {
		desc = d;
	}
	
	/**
	 * Gets this StatCalc's description
	 * @return this StatCalc's description
	 */
	public String GetDescription() {
		return desc;
	}
	
	public abstract ArrayList<Number> GetResult() throws RuntimeException;
	
	/**
	 * Sets this StatCalc's data
	 */
	public void SetData(ArrayList<T> data) {
		dat.clear();
		for(int i = 0; i < data.size(); i++) {
			dat.add(data.get(i));
		}
	}
	
	/**
	 * Gets this StatCalc's data
	 * @return this StatCalc's data
	 */
	public ArrayList<T> GetData(){
		ArrayList<T> ret = new ArrayList<T>();
		ret.addAll(dat);
		return ret;
	}
	
	/**
	 * Sorts an array from smallest T to largest T
	 * @param a - an ArrayList<T> to be sorted.
	 */
	protected ArrayList<T> sortArray(ArrayList<T> a) {
		
		if(a == null || a.size() <= 1) return a;
		
		ArrayList<T> al1 = sortArray(subarray(a, 0, (a.size()/2)-1));
		ArrayList<T> al2 = sortArray(subarray(a, (a.size()/2), a.size()-1));
		
		ArrayList<T> result = new ArrayList<T>();
		
		
		int i = 0;
		int	j = 0;
		
		while(i < al1.size() && j < al2.size()) {
			
			if(al1.get(i) == null) i++;
			else if(al2.get(j) == null) j++;
			
			else if(al1.get(i).doubleValue() >= al2.get(j).doubleValue()) {
				result.add(al2.get(j));
				j++;
			}
			else if(al2.get(j).doubleValue() >= al1.get(i).doubleValue()) {
				result.add(al1.get(i));
				i++;
			}
		}
		
		if(i == al1.size()) {
			while(j < al2.size()) {
				result.add(al2.get(j));
				j++;
			}
		}
		if(j == al2.size()) {
			while(i < al1.size()) {
				result.add(al1.get(i++));
			}
		}
		
		removeNulls(result);
		
		return result;
		
	}
	
	/**
	 * Returns a sub-ArrayList of a given ArrayList of type T
	 * @param a - The ArrayList with which to find the subarray
	 * @param s - The starting index of the subarray
	 * @param e - The ending index of the subarray
	 * @return the indicated subarray in the given ArrayList between elements s and e
	 */
	private ArrayList<T> subarray(ArrayList<T> a, int s, int e){
		
		if((s > e) || (a.size() - 1 < e) || (s < 0)) {
			return null;
		}
		
		ArrayList<T> res = new ArrayList<T>();
		
		for(int i = s; i <= e; i++) {
			res.add(a.get(i));
		}
		
		return res;
	}
	
	private ArrayList<T> removeNulls(ArrayList<T> al){
		ArrayList<T> ret = new ArrayList<T>();
		for(int i = 0; i < al.size(); i++) {
			if(!(al.get(i) == null)) {
				ret.add(al.get(i));
			}
		}
		
		return ret;
	}
}
