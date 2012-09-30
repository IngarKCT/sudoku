
#include "cell.h"

Cell::Cell()
{
	cell_value = 0;
	cell_valid = true;
}

Cell::Cell(const Cell & other)
{
	assign(other);
}
	
void Cell::assign(const Cell & other)
{
	cell_valid = other.cell_valid;
	cell_value = other.cell_value;
	cell_valid = other.cell_valid;
	
	for (int i = 0; i < 9; i++) {
		cell_possibility[i] = other.cell_possibility[i];
	}
}
	
void Cell::set_value(int value)
{
	cell_value = value;
}

void Cell::set_possibility(int value, bool possible)
{
	cell_possibility[value] = possible;
}

void Cell::set_valid(bool valid)
{
	cell_valid = valid;
}
