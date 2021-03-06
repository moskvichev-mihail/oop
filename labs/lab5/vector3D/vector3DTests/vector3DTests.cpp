// vector3DTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../vector3D/CVector.h"


bool IsEqualDouble(double d1, double d2)
{
	const double E = 0.001;
	return abs(d1 - d2) < E;
}

TEST_CASE("vector3D tests")
{
	SECTION("initialize var")
	{
		cout << "initialize var" << endl;
		CVector3D v3;
		CHECK((IsEqualDouble(v3.x, 0) && IsEqualDouble(v3.y, 0) && IsEqualDouble(v3.z, 0)) == true);
		CVector3D vector3(1, 1, 2);
		CHECK((IsEqualDouble(vector3.x, 1) && IsEqualDouble(vector3.y, 1) && IsEqualDouble(vector3.z, 2)) == true);
	}
	SECTION("check equal vectors")
	{
		cout << "check equal vectors" << endl;
		CVector3D v1(1, 2, 3);
		CVector3D v2(1, 2, 3);
		CVector3D v3(2, 2, 3);
		CHECK((v1 == v2 && v2 == v1) == true);
		CHECK((v1 != v3 && v3 != v1) == true);
	}
	SECTION("check on binary operations")
	{
		cout << "check on binary operations" << endl;
		CVector3D v1(1, 2, 3);
		CVector3D v2(4, 4, 4);
		CHECK((v1 + v2) == CVector3D(5, 6, 7));
		CHECK((v1 - v2) == CVector3D(-3, -2, -1));
		CHECK(((v1 * 2) == CVector3D(2, 4, 6) && (2 * v1) == CVector3D(2, 4, 6)) == true);
		CHECK((v1 / 2) == CVector3D(0.5, 1, 1.5));
	}

	SECTION("check on short binary operations")
	{
		cout << "check on short binary operations" << endl;
		CVector3D v1(1, 2, 3);
		CVector3D v2(4, 4, 4);
		v1 += v2;
		CHECK(v1 == CVector3D(5, 6, 7));
		v1 -= v2;
		CHECK(v1 == CVector3D(1, 2, 3));
		v1 *= 2;
		CHECK(v1 == CVector3D(2, 4, 6));
		v1 /= 2;
		CHECK(v1 == CVector3D(1, 2, 3));
	}

	SECTION("unary + and -")
	{
		cout << "unary + and -" << endl;
		CVector3D v2(4, 4, 4);
		v2 = -v2;
		CHECK(v2 == CVector3D(-4, -4, -4));
		v2 = +v2;
		CHECK(v2 == CVector3D(-4, -4, -4));
	}
	SECTION("operations << and >>")
	{
		cout << "operations << and >>" << endl;
		string str = "1 2 3";
		istringstream iStream(str);
		CVector3D v1;
		iStream >> v1;
		CHECK(v1 == CVector3D(1, 2, 3));

		ostringstream oStream;
		oStream << v1;
		CHECK(oStream.str() == "1, 2, 3");

		str = "4 4";
		istringstream wrongIStream(str);
		wrongIStream >> v1;
		CHECK(v1 == CVector3D(1, 2, 3));
	}

	SECTION("check on integrated methods on class")
	{
		cout << "check on integrated methods on class" << endl;
		CVector3D v2(4, 4, 4);
		double expectedLength = 6.928;

		CHECK(IsEqualDouble(v2.GetLength(), expectedLength));

		v2.Normalize();
		CHECK(v2.GetLength() == 1);

		CVector3D v1(1, 2, 3);
		CVector3D v3(2, 2, 2);
		CHECK(CVector3D::DotProduct(v1, v3) == 12);
		CHECK(CVector3D::CrossProduct(v1, v3) == CVector3D(-2, 4, -2));
	}

	SECTION("check on division by zero")
	{
		cout << "check on division by zero" << endl;
		CVector3D v1(1, 2, 3);
		try
		{
			v1 = v1 / 0;
		}
		catch (invalid_argument ex)
		{
			CHECK(static_cast<const string&>("Division by zero \n") == ex.what());
		}

		try
		{
			v1 /= 0;
		}
		catch (invalid_argument ex)
		{
			CHECK(static_cast<const string&>("Division by zero \n") == ex.what());
		}
	}
}