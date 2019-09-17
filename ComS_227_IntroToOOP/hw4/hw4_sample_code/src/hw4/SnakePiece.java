package hw4;

import api.Cell;
import api.Icon;
import api.Position;

/**
 * Creates a Snake Piece for the game BlockAddiction
 * 
 * @author William Blanchard
 */
public class SnakePiece extends AbstractPiece {
	
	/**
	 * The sequence of positions that each icon of the piece will eventually pass through
	 * if the player cycles through the transformation button.
	 */
	private static final Position[] sequence =
		{
				new Position(0, 0),
				new Position(0, 1),
				new Position(0, 2),
				new Position(1, 2),
				new Position(1, 1),
				new Position(1, 0),
				new Position(2, 0),
				new Position(2, 1),
				new Position(2, 2),
				new Position(1, 2),
				new Position(1, 1),
				new Position(1, 0)
		};
	
	/**
	 * Keeps track of what phase the piece is currently in
	 */
	private int counter;
	
	public SnakePiece(Position position, Icon[] icons) {
		super(position, 4);
		
		//Starts at 9 to indicate the position of the "tail" icon of the piece.
		counter = 9;
		
		Cell[] cells = new Cell[4];
		cells[0] = new Cell(icons[0], sequence[0]);
		cells[1] = new Cell(icons[1], sequence[11]);
		cells[2] = new Cell(icons[2], sequence[10]);
		cells[3] = new Cell(icons[3], sequence[9]);
		setCells(cells);
	}

	@Override
	public void transform() {
		
		Cell[] cells = getCells();
		
		//Iterates through each phase of the sequence for each of the icons
		counter = (counter + 1) % 12;
		
		for(int i = 0; i < 4; i++) {
			cells[i].setPosition(sequence[(counter + 3 - i) % 12]);
		}
		
		setCells(cells);
	}

}
