package hw4;

import java.awt.Color;
import java.util.List;
import java.util.Random;
import java.util.ArrayList;
import java.util.Collections;

import api.AbstractGame;
import api.Position;
import api.Generator;
import api.Icon;


/**
 * Creates a game deemed as a combination of Tetris and Bejeweled called BlockAddiction
 * 
 * @author William Blanchard
 */
public class BlockAddiction extends AbstractGame {
	
	public BlockAddiction(int height, int width, Generator gen, int preFillRows) {
		super(height, width, gen);
		
		//Sets a checkerboard pattern of rows for the amount specified by preFillRows
		for(int i = height - 1; i > height - preFillRows - 1; i--) {
			int alternate = i % 2;
			
			for(int j = alternate; j < width; j += 2) {
				setBlock(i, j, new Icon(getRandomColor()));
			}
		}
	}
	
	public BlockAddiction(int height, int width, Generator gen) {
		super(height, width, gen);
	}

	@Override
	public List<Position> determinePositionsToCollapse() {
		List<Position> positions = new ArrayList<>();
		
		//An array for each icon that should be included in the set of positions to collapse
		List<Position> validSides = new ArrayList<>();
		Icon check;
		
		for(int row = 0; row < getHeight(); row++) {
			for(int col = 0; col < getWidth(); col++) {
				
				//The icon being checked
				check = getIcon(row, col);
				
				//The positions of each side of the currently checked icon
				Position pa = new Position(row - 1, col);
				Position pb = new Position(row + 1, col);
				Position pc = new Position(row, col - 1);
				Position pd = new Position(row, col + 1);
				
				
				if(check != null) {
					//Check each side of the icon in question, add position if it is part of a set
					//to a separate list.  Also checks if the icon being checked is within the game
					//frame and whether or not an icon exists there.
					if(row - 1 >= 0 && iconAt(pa) != null && check.getColorHint() == getIcon(row - 1, col).getColorHint()) {
						validSides.add(pa);
					}
					if(row + 1 < getHeight() && iconAt(pb) != null && check.getColorHint() == getIcon(row + 1, col).getColorHint()) {
						validSides.add(pb);
					}
					if(col - 1 >= 0 && iconAt(pc) != null && check.getColorHint() == getIcon(row, col - 1).getColorHint()) {
						validSides.add(pc);
					}
					if(col + 1 < getWidth() && iconAt(pd) != null && check.getColorHint() == getIcon(row, col + 1).getColorHint()) {
						validSides.add(pd);
					}
				
				
					//If that list has more than 2 matching sides, then all icons are part of a
					//collapsable set.  Add them to the positions array list.
					if(validSides.size() >= 2) {
						positions.add(new Position(row, col));
						for(int i = 0; i < validSides.size(); i++) {
							if(!positions.contains(validSides.get(i))) {
								positions.add(validSides.get(i));
							}
						}
						Collections.sort(positions);
					}
					
					//Clears the valid sides array from the previously selected icon
					validSides.clear();
				}
			}
		}
		
		return positions;
	}
	
	/**
	 * Gets a random color from the list of colors provided in the Icon class.
	 * @return a random color from a limited selection.
	 */
	private Color getRandomColor() {
		Random r = new Random();
		int i = r.nextInt(7);
		
		return Icon.COLORS[i];
	}
	
	/**
	 * Returns the icon that presides at the given position object.  Returns null if no icon exists there.
	 * @param p - The position where the icon is being picked from
	 * @return The icon that is at the indicated position.  Null if no icon exists at the position.
	 */
	private Icon iconAt(Position p) {
		int row = p.row();
		int col = p.col();
		
		return getIcon(row, col);
	}
}
