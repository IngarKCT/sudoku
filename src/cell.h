
#ifndef __INCLUDED_SUDOKUSOLVER_CELL__
#define __INCLUDED_SUDOKUSOLVER_CELL__

class Cell {
	
public:
	Cell();
	Cell(const Cell & other);
	
	void assign(const Cell & other);
	
	// inspector
	inline int value() const { return cell_value; }

	inline int possibility(const int value) { return cell_possibility[value]; }
	
	// mutator
	void set_value(int value);
	
	void set_possibility(int value, bool possible = true);
	
private:
	int cell_value;
	bool cell_possibility[9];
};

#endif // __INCLUDED_SUDOKUSOLVER_CELL__
