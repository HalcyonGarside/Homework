package hw4;

import api.Cell;
import api.Icon;
import api.Position;

/**
 * Creates a Corner Piece for the game BlockAddiction
 * 
 * @author William Blanchard
 */
public class CornerPiece extends AbstractPiece {
	
	/**
	 * The sequence of positions that each icon of the piece will eventually pass through
	 * if the player cycles through the transformation button.
	 */
	private final Position[] sequence =
		{
				new Position(0, 0),
				new Position(0, 1),
				new Position(1, 1),
				new Position(1, 0)
		};
	
	/**
	 * Keeps track of what phase the piece is currently in
	 */
	private int counter;
	
	public CornerPiece(Position position, Icon[] icons) {
		super(position, 3);
		
		//Starts at 2 to indicate the position of the "tail" icon of the piece.
		counter = 2;
		
		Cell[] cells = new Cell[3];
		cells[0] = new Cell(icons[0], new Position(0, 0));
		cells[1] = new Cell(icons[1], new Position(1, 0));
		cells[2] = new Cell(icons[2], new Position(1, 1));
		setCells(cells);
	}

	@Override
	public void transform() {
		
		Cell[] cells = getCells();
		
		//Iterates through each phase of the sequence for each of the icons
		counter = (counter + 1) % 4;
		
		for(int i = 0; i < 3; i++) {
			cells[i].setPosition(sequence[(counter + 2 - i) % 4]);
		}
		
		setCells(cells);
	}

}
