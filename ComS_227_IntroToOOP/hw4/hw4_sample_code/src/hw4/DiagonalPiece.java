package hw4;

import api.Cell;
import api.Icon;
import api.Position;

/**
 * Creates a Diagonal Piece for the game BlockAddiction
 * 
 * @author William Blanchard
 */
public class DiagonalPiece extends AbstractPiece {
	
	public DiagonalPiece(Position position, Icon[] icons) {
		super(position, 2);
		
		Cell[] cells = new Cell[2];
		cells[0] = new Cell(icons[0], new Position(0, 0));
		cells[1] = new Cell(icons[1], new Position(1, 1));
		setCells(cells);
	}

	@Override
	public void transform() {
		Cell[] cells = getCells();
		
		//If the first cell is in the first column, flip the two cells.
		if(cells[0].getCol() == 0) {
			cells[0].setCol(1);
			cells[1].setCol(0);
			
			setCells(cells);
		}
		//Otherwise, unflip the cells.
		else {
			cells[0].setCol(0);
			cells[1].setCol(1);
			
			setCells(cells);
		}
	}

}
