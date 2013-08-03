
#ifndef __INCLUDED_SUDOKUSOLVER_CELL__
#define __INCLUDED_SUDOKUSOLVER_CELL__

class Cell {
	
public:
	/**
	 * @brief default constructor
	 * */
	Cell();
	
	/**
	 * @brief copy constructor
	 * */
	Cell(const Cell & other);
	
	/**
	 * @brief assignment operator
	 * */
	void assign(const Cell & other);
	
	// inspectors

	/**
	 * @brief return true if a given value is a valid possibility for this cell
	 * */
	inline int possibility(const int value) { return cell_possibility[value]; }
		
	/**
	 * @brief return true of the current value for this cell is a valid possibility
	 * */
	// FIXME the bool valid() should be replaced with a state() enum to indicate
	// the difference between Input Error and Invalid Values
	inline bool valid() const { return cell_valid; }
	
	/**
	 * @brief return the current value for this cell
	 * */
	inline int value() const { return cell_value; }

	// mutators
	
	/**
	 * @brief set wether or not the given value is a valid possibility for a this cell
	 * */
	void set_possibility(int value, bool possible = true);
	
	/**
	 * @brief set wether or not this cell is valid
	 * */
	void set_valid(bool valid);
	
	/**
	 * @brief set the value for this cell
	 * */
	void set_value(int value);
		
private:
	bool cell_possibility[9];
	bool cell_valid;
	int cell_value;
};

#endif // __INCLUDED_SUDOKUSOLVER_CELL__
