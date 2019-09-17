package hw4;

import api.*;

/**
 * Creates a I Piece for the game BlockAddiction
 * 
 * @author William Blanchard
 */
public class IPiece extends AbstractPiece {
	
	public IPiece(Position position, Icon[] icons) {
		super(position, 3);
		
		Icon[] ic = icons;
		Cell[] cells = new Cell[3];
		cells[0] = new Cell(ic[0], new Position(0, 1));
		cells[1] = new Cell(ic[1], new Position(1, 1));
		cells[2] = new Cell(ic[2], new Position(2, 1));
		
		setCells(cells);
	}

	@Override
	public void transform() {
		// Does nothing
	}

}
