#include "Data.h"

ostream& operator<<(ostream &lhs, Data &rhs) {
	lhs << rhs.getName();
	return lhs;
}