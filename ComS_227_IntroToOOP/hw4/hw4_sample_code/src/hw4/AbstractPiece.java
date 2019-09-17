package hw4;

import java.awt.Color;
import java.util.Random;

import api.Cell;
import api.Icon;
import api.Piece;
import api.Position;

/**
 * The general implementation for a standard piece in the game BlockAddiction
 * 
 * @author William Blanchard
 */
public abstract class AbstractPiece implements Piece {
	/**
	 * The general position of this piece
	 */
	private Position position;
	
	/**
	 * The array of cells belonging to this piece
	 */
	private Cell[] cells;
	
	protected AbstractPiece(Position givenPosition, int cellSize) {
		position = givenPosition;
		cells = new Cell[cellSize];
	}
	
	@Override
	public Position getPosition() {
		return position;
	}

	@Override
	public Cell[] getCells() {
		return cells;
	}

	@Override
	public Cell[] getCellsAbsolute() {
		Cell[] ret = new Cell[cells.length];
		
		int row;
		int col;
	    Icon b;
		
	    for(int i = 0; i < cells.length; i++) {
	    	row = cells[i].getRow() + position.row();
		    col = cells[i].getCol() + position.col();
		    b = cells[i].getIcon();
		    ret[i] = new Cell(b, new Position(row, col));
	    }

	    return ret;
	}

	@Override
	public void setCells(Cell[] givenCells) {
		for(int i = 0; i < cells.length; i++) {
			cells[i] = givenCells[i];
		}
	}

	@Override
	public void shiftDown() {
		position = new Position(position.row() + 1, position.col());
	}

	@Override
	public void shiftLeft() {
		Position pos = new Position(position.row(), position.col() - 1);
		position = pos;
	}

	@Override
	public void shiftRight() {
		Position pos = new Position(position.row(), position.col() + 1);
		position = pos;
	}
	
	public abstract void transform();

	@Override
	public void cycle() {
		Icon il = cells[cells.length - 1].getIcon();
		
		for(int i = cells.length - 1; i > 0; i--) {
			cells[i].setIcon(cells[i - 1].getIcon());
		}
		
		cells[0].setIcon(il);
	}

	@Override
	public Piece clone()
	  {
	    try
	    {
	      // call the Object clone() method to create a shallow copy
	      AbstractPiece s = (AbstractPiece) super.clone();

	      // then make it into a deep copy (note there is no need to copy the position,
	      // since Position is immutable, but we have to deep-copy the cell array
	      // by making new Cell objects      
	      s.cells = new Cell[cells.length];
	      for (int i = 0; i < cells.length; i++)
	      {
	        s.cells[i] = new Cell(cells[i]);
	      }
	      return s;
	    }
	    catch (CloneNotSupportedException e)
	    {
	      // can't happen, since we know the superclass is cloneable
	      return null;
	    }    
	  }
	
	protected void setCellSize(int size) {
		cells = new Cell[size];
	}
}