#include "Simplex.h"
#include"SimplexOps.h"
#include"Tests.h"
#include <iostream>

int main()
{
	OptLib::test_plus();
	OptLib::test_plus_scalar();
	OptLib::test_minus_scalar();
	OptLib::test_minus();
	OptLib::test_mult();
	OptLib::test_mult_scalar();
	OptLib::test_div_scalar();
	OptLib::test_abs();
	OptLib::test_sqrt();
	OptLib::test_matrix();
	OptLib::test_mean();
	OptLib::test_sin();
	//OptLib::test_paraboloid();
}

