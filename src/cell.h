
#ifndef __INCLUDED_SUDOKUSOLVER_CELL__
#define __INCLUDED_SUDOKUSOLVER_CELL__

class Cell {
	
public:
	Cell();
	
	// inspector
	inline int value() const { return cell_value; }
	
	// mutator
	void set_value(int value);
	
private:
	int cell_value;
};

#endif // __INCLUDED_SUDOKUSOLVER_CELL__
