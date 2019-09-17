package hw4;

import api.Cell;
import api.Position;
import api.Icon;

/**
 * Creates a L Piece for the game BlockAddiction
 * 
 * @author William Blanchard
 */
public class LPiece extends AbstractPiece {
	
	public LPiece(Position position, Icon[] icons) {
		super(position, 4);
		
		Icon[] ic = icons;
		Cell[] cells = new Cell[4];
		cells[0] = new Cell(ic[0], new Position(0, 0));
		cells[1] = new Cell(ic[1], new Position(0, 1));
		cells[2] = new Cell(ic[2], new Position(1, 1));
		cells[3] = new Cell(ic[3], new Position(2, 1));
		setCells(cells);
	}
	
	@Override
	public void transform() {
		Cell[] cells = getCells();
		
		if(cells[0].getCol() == 0) {
			cells[0].setCol(2);
			
			setCells(cells);
		}
		else {
			cells[0].setCol(0);
			
			setCells(cells);
		}
	}
}
