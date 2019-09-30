package cs228hw1.stats;

import java.io.File;
import java.io.FileNotFoundException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Scanner;

public class StatisticsShell<T extends Number> implements Statistics<T>{
	
	ArrayList<StatObject<T>> objects;
	ArrayList<T> data;
	Method m;

	public StatisticsShell(Method mth) {
		objects = new ArrayList<StatObject<T>>();
		data = new ArrayList<T>();
		m = mth;
	}
	
	/**
	 * Reads the weather data of the indicated data type into the data ArrayList
	 */
	public boolean ReadFile(String path, DATA d) {
		try {
			File f = new File(path);
			Scanner s = new Scanner(f);
			String dat = s.next();
			DATA[] types = DATA.values();
			int i = 0;
			
			while(!(d == types[i])) {
				i++;
			}
			
			String line = s.nextLine();
			
			while(s.hasNextLine()) {
				line = s.nextLine();
				Scanner l = new Scanner(line);
				
				for(int j = 0; j <= i; j++) {
					dat = l.next();
				}
				
				if(!dat.contains("*")){
					T dpoint = parse(dat, m);
					data.add(dpoint);
				}
				else {
					data.add(null);
				}
				
				l.close();
			}
			
			s.close();
			
		}catch(FileNotFoundException e) {
			return false;
		}
		
		return true;
	}
	
	/**
	 * Adds a statistics object into the objects ArrayList
	 */
	public void AddStatObject(StatObject<T> so) {
		objects.add(so);
	}
	
	/**
	 * Adds a statistics object into the objects ArrayList based off of the specific part of the array
	 * indicated by the user.
	 */
	public void AddStatObject(StatObject<T> so, int first, int last) {
		ArrayList<T> added = new ArrayList<T>();
		
		for(int i = first; i <= last; i++) {
			added.add(data.get(i));
		}
		
		so.SetData(added);
		objects.add(so);
	}
	
	/**
	 * Gets the specific statistics object at its specific position in the object array.
	 */
	public StatObject<T> GetStatObject(int i){
		return objects.get(i);
	}
	
	/**
	 * Removes the statistics object at the given index in the objects ArrayList.
	 */
	public StatObject<T> RemoveStatObject(int i){
		StatObject<T> ob = objects.get(i);
		objects.remove(i);
		
		return ob;
	}
	
	/**
	 * Returns the amount of elements in the objects ArrayList.
	 */
	public int Count() {
		return objects.size();
	}
	
	/**
	 * Returns a copy of the data set in this StatisticsShell
	 */
	public ArrayList<T> GetDataSet(){
		ArrayList<T> cpy = new ArrayList<T>();
		cpy.addAll(data);
		return cpy;
	}
	
	/**
	 * Runs all of the calculations in the objects ArrayList and returns the resulting ArrayList.
	 */
	public ArrayList<ArrayList<Number>> MapCar(){
		ArrayList<ArrayList<Number>> res = new ArrayList<ArrayList<Number>>();
		
		for(StatObject<T> i : objects) {
			res.add(i.GetResult());
		}
		
		return res;
	}
	
	/**
	 * Uses the method given in the constructor and a given string to parse an object out of that string.
	 * 
	 * @param str - the string to be parsed
	 * @param m - the method that will parse the string
	 * @return the object parsed from the string
	 */
	public T parse(String str, Method m) {
		try {
			return (T)m.invoke(null, str);
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
		return null;
	}
}
