package cs228hw1;

import cs228hw1.stats.*;
import cs228hw1.stats.Statistics.DATA;
import java.util.ArrayList;
import java.lang.reflect.Method;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Gets the monthly maximum and minimum temperatures, the daily average and median temperatures,
 * and a histogram with 15 bins 
 * 
 * @author William Blanchard
 *
 */
public class Weather {
	public static void main(String [] args) {
		Method m;
		
		try {
			File f = new File(args[0]);
			
			m = Double.class.getMethod("parseDouble", String.class);
			
			System.out.println("Monthly Max Temps:");
			System.out.println(getMonthlyMax(f, m));
			System.out.println("Monthly Min Temps:");
			System.out.println(getMonthlyMin(f, m));
			System.out.println("Daily Average Temps:");
			System.out.println(getDailyAve(f, m));
			System.out.println("Daily Median Temps:");
			System.out.println(getDailyMed(f, m));
			System.out.println("Histogram of Daily Max Temps:");
			System.out.println(getDailyMaxHist(f, m));
			
		} catch (NoSuchMethodException e) {
			e.printStackTrace();
		} catch (SecurityException e) {
			e.printStackTrace();
		}

	}
	
	private static ArrayList<ArrayList<Number>> getMonthlyMax(File f, Method m){
		ArrayList<ArrayList<Number>> result = null;
		
		try {
			StatisticsShell<Double> shell = new StatisticsShell<Double>(m);
			shell.ReadFile(f.getName(), DATA.TEMP);
			
			ArrayList<Double> temp = new ArrayList<Double>();
			
			Scanner s = new Scanner(f);
			
			String line = s.nextLine();
			line = s.nextLine();
			
			Scanner d = new Scanner(line);
			String date = d.next();
			date = d.next();
			date = d.next();
			
			long start = Long.parseLong(date)/ 1000000;
			int si = 0;
			long end = start;
			int ei = 0;
			d.close();
			
			while(s.hasNextLine()) {
				while(end == start && s.hasNextLine()) {
					line = s.nextLine();
					d = new Scanner(line);
					date = d.next();
					date = d.next();
					date = d.next();
					end = Long.parseLong(date) / 1000000;
					
					ei++;
					d.close();
				}
				
				shell.AddStatObject(new Maximum<Double>(temp), si, ei - 1);
				
				start = end;
				si = ei;
			}
			
			s.close();

			
			result = shell.MapCar();
			
			
			
			return result;
			
			
			
		} catch(FileNotFoundException e) {
			System.out.print("Please input a valid file name");
			e.printStackTrace();
		}
		
		return result;
	}
	
	private static ArrayList<ArrayList<Number>> getMonthlyMin(File f, Method m){
		ArrayList<ArrayList<Number>> result = null;
		
		try {
			StatisticsShell<Double> shell = new StatisticsShell<Double>(m);
			shell.ReadFile(f.getName(), DATA.TEMP);
			
			ArrayList<Double> temp = new ArrayList<Double>();
			
			Scanner s = new Scanner(f);
			
			String line = s.nextLine();
			line = s.nextLine();
			
			Scanner d = new Scanner(line);
			String date = d.next();
			date = d.next();
			date = d.next();
			
			long start = Long.parseLong(date)/ 1000000;
			int si = 0;
			long end = start;
			int ei = 0;
			d.close();
			
			while(s.hasNextLine()) {
				while(end == start && s.hasNextLine()) {
					line = s.nextLine();
					d = new Scanner(line);
					date = d.next();
					date = d.next();
					date = d.next();
					end = Long.parseLong(date) / 1000000;
					
					ei++;
					d.close();
				}
				
				shell.AddStatObject(new Minimum<Double>(temp), si, ei - 1);
				
				start = end;
				si = ei;
			}
			
			s.close();

			
			result = shell.MapCar();
			
			
			
			return result;
			
			
			
		} catch(FileNotFoundException e) {
			System.out.print("Please input a valid file name");
			e.printStackTrace();
		}
		
		return result;
	}
	
	private static ArrayList<ArrayList<Number>> getDailyAve(File f, Method m){
		ArrayList<ArrayList<Number>> result = null;
		
		try {
			StatisticsShell<Double> shell = new StatisticsShell<Double>(m);
			shell.ReadFile(f.getName(), DATA.TEMP);
			
			ArrayList<Double> temp = new ArrayList<Double>();
			
			Scanner s = new Scanner(f);
			
			String line = s.nextLine();
			line = s.nextLine();
			
			Scanner d = new Scanner(line);
			String date = d.next();
			date = d.next();
			date = d.next();
			
			long start = Long.parseLong(date)/ 10000;
			int si = 0;
			long end = start;
			int ei = 0;
			d.close();
			
			while(s.hasNextLine()) {
				while(end == start && s.hasNextLine()) {
					line = s.nextLine();
					d = new Scanner(line);
					date = d.next();
					date = d.next();
					date = d.next();
					end = Long.parseLong(date) / 10000;
					
					ei++;
					d.close();
				}
				
				shell.AddStatObject(new Average<Double>(temp), si, ei - 1);
				
				start = end;
				si = ei;
			}
			
			s.close();

			
			result = shell.MapCar();
			
			
			
			return result;
			
			
			
		} catch(FileNotFoundException e) {
			System.out.print("Please input a valid file name");
			e.printStackTrace();
		}
		
		return result;
	}
	
	private static ArrayList<ArrayList<Number>> getDailyMed(File f, Method m){
		ArrayList<ArrayList<Number>> result = null;
		
		try {
			StatisticsShell<Double> shell = new StatisticsShell<Double>(m);
			shell.ReadFile(f.getName(), DATA.TEMP);
			
			ArrayList<Double> temp = new ArrayList<Double>();
			
			Scanner s = new Scanner(f);
			
			String line = s.nextLine();
			line = s.nextLine();
			
			Scanner d = new Scanner(line);
			String date = d.next();
			date = d.next();
			date = d.next();
			
			long start = Long.parseLong(date)/ 10000;
			int si = 0;
			long end = start;
			int ei = 0;
			d.close();
			
			while(s.hasNextLine()) {
				while(end == start && s.hasNextLine()) {
					line = s.nextLine();
					d = new Scanner(line);
					date = d.next();
					date = d.next();
					date = d.next();
					end = Long.parseLong(date) / 10000;
					
					ei++;
					d.close();
				}
				
				shell.AddStatObject(new Median<Double>(temp), si, ei - 1);
				
				start = end;
				si = ei;
			}
			
			s.close();

			
			result = shell.MapCar();
			
			
			
			return result;
			
			
			
		} catch(FileNotFoundException e) {
			System.out.print("Please input a valid file name");
			e.printStackTrace();
		}
		
		return result;
	}
	
	private static ArrayList<ArrayList<Number>> getDailyMaxHist(File f, Method m){
		ArrayList<ArrayList<Number>> result = null;
		
		try {
			StatisticsShell<Double> shell = new StatisticsShell<Double>(m);
			shell.ReadFile(f.getName(), DATA.TEMP);
			
			ArrayList<Double> temp = new ArrayList<Double>();
			
			Scanner s = new Scanner(f);
			
			String line = s.nextLine();
			line = s.nextLine();
			
			Scanner d = new Scanner(line);
			String date = d.next();
			date = d.next();
			date = d.next();
			
			long start = Long.parseLong(date)/ 10000;
			int si = 0;
			long end = start;
			int ei = 0;
			d.close();
			
			while(s.hasNextLine()) {
				while(end == start && s.hasNextLine()) {
					line = s.nextLine();
					d = new Scanner(line);
					date = d.next();
					date = d.next();
					date = d.next();
					end = Long.parseLong(date) / 10000;
					
					ei++;
					d.close();
				}
				
				shell.AddStatObject(new Maximum<Double>(temp), si, ei - 1);
				
				start = end;
				si = ei;
			}
			
			s.close();

			
			result = shell.MapCar();
			ArrayList<Double> histVals = new ArrayList<Double>();
			
			for(int i = 0; i < result.size(); i++) {
				histVals.add(result.get(i).get(0).doubleValue());
			}
			
			StatisticsShell<Double> hist = new StatisticsShell<Double>(m);
			Histogram<Double> h = new Histogram<Double>(histVals);
			
			h.SetNumberBins(15);
			h.SetMaxRange(110);
			h.SetMinRange(-40);
			
			hist.AddStatObject(h);
			
			result = hist.MapCar();
			
			return result;
			
			
			
		} catch(FileNotFoundException e) {
			System.out.print("Please input a valid file name");
			e.printStackTrace();
		}
		
		return result;
	}
	
	
	
}
