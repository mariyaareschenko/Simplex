#pragma once
#include <iostream>
#include <memory>
#include <algorithm>
#include<array>
#include"SimplexOps.h"
namespace OptLib
{
	template<size_t dim>//объявляет шаблонный класс с безнаковым целым числом в 8 байт
	using Point = std::array<double, dim>; //контейнер (Point) с числами с плавающей запятой и кол-ом этих чисел - dim
	template<size_t dim>
	Point<dim> operator+ (const Point<dim>& arr1, const Point<dim> arr2) 
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::plus<>{});
		return result;
	}

	template<size_t dim>
	Point<dim> operator+ (const Point<dim>& arr1, double consta)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(), result.begin(), SimplexOps::UnaryOps::plus<double>{consta });
		return result;
	}

	template<size_t dim>
	Point<dim> operator- (const Point<dim>& arr1, const Point<dim> arr2)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::minus<>{});
		return result;
	}

	template<size_t dim>
	Point<dim> operator- (const Point<dim>& arr1, double consta)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(), result.begin(), SimplexOps::UnaryOps::minus<double>{consta });
		return result;
	}

	template<size_t dim>
	double operator* (const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result;
		double res = 0;
		std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::multiplies<>{});
		for (auto& el : result)
			res += el;
		return res;
	}

	template<size_t dim>
	Point<dim> operator* (const Point<dim>& arr1, double consta)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(), result.begin(), SimplexOps::UnaryOps::multiplies<double>{consta });
		return result;
	}

	template<size_t dim>
	Point<dim> operator/ (const Point<dim>& arr1, double consta)
	{
		Point<dim> result;
		std::transform(arr1.begin(), arr1.end(), result.begin(), SimplexOps::UnaryOps::division<double>{consta});
		return result;
	}

	template<size_t dim>
	Point<dim> Abs(const Point<dim>& arr)
	{
		Point<dim> result;
		std::transform(arr.begin(), arr.end(), result.begin(), SimplexOps::UnaryOps::Abs<>{});
		return result;
	}

	template<size_t dim>
	Point<dim> Sqrt(const Point<dim>& arr)
	{
		Point<dim> result;
		std::transform(arr.begin(), arr.end(), result.begin(), SimplexOps::UnaryOps::Sqrt<>{});
		return result;
	}

	template<size_t dim>
	struct RawPoint
	{
		RawPoint() = default;
		Point<dim> P;
		RawPoint(const Point<dim>& p) : P{ p } {}; //не конструктор копирования 
		RawPoint(Point <dim>&& p): P{std::move(p)} {};
		double operator[](size_t i) const { return P[i]; }
		operator Point<dim>() { return P; }
	};
	template<size_t dim>
	struct PointVal :
		public RawPoint<dim>
	{
		double val;
		PointVal() = default;
		PointVal(Point<dim>&& p, double val) : RawPoint<dim>{ std::move(p) }, val{ val }{};
		PointVal(const Point<dim>& p, double val) : RawPoint<dim>{p}, val{ val }{};
		bool operator<(const Point<dim>& rhs)
		{
			return this->val < rhs.val;
		}
	};
	template<size_t dim>
	PointVal<dim> operator+(const PointVal<dim>& p1, const PointVal<dim>& p2)
	{
		return PointVal<dim>{p1.P + p2.P, p1.val + p2.val};
	}
	template<size_t dim>
	Point<dim> operator+ (const PointVal<dim>& p1, double consta)
	{
		return PointVal<dim>{p1.P + consta, p1.val};
	}
	template<size_t dim>
	PointVal<dim> operator-(const PointVal<dim>& p1, const PointVal<dim>& p2)
	{
		return PointVal<dim>{p1.P - p2.P, p1.val - p2.val};
	}
	template<size_t dim>
	Point<dim> operator- (const PointVal<dim>& p1, double consta)
	{
		return PointVal<dim>{p1.P - consta, p1.val};
	}
	template<size_t dim>
	Point<dim> operator* (const PointVal<dim>& p1, const PointVal<dim>& p2)
	{
		return PointVal<dim>{p1.P * p2.P, p1.val * p2.val};
	}
	template<size_t dim>
	Point<dim> operator* (const PointVal<dim>& p1, double consta)
	{
		return PointVal<dim>{p1.P * consta, p1.val};
	}
	template<size_t dim>
	Point<dim> operator/ (const PointVal<dim>& p1, const PointVal<dim>& p2)
	{
		return PointVal<dim>{p1.P / p2.P, p1.val / p2.val};
	}
	template<size_t dim>
	Point<dim> operator/ (const PointVal<dim>& p1, double consta)
	{
		return PointVal<dim>{p1.P / consta, p1.val};
	}
	template<size_t dim>
	Point<dim> operatorabs(const PointVal<dim>& p)
	{
		return PointVal<dim>{abs(p.P), abs(p.val)};
	}
	template<size_t dim>
	Point<dim> operatorsqrt(const PointVal<dim>& p)
	{
		return PointVal<dim>{sqrt(p.P), sqrt(p.val)};
	}

	template<size_t count, typename point>
	using SetOfPoints = std::array<point, count>;
	template<size_t count, typename point>
	Point<count> operator*(const SetOfPoints<count, point>& matrix, const point& vector_dim1)
	{
		Point<count> res;
		for (size_t i = 0;i <count;i++)
		{
			res[i] = matrix[i] * vector_dim1;
		}
		return res;
	}
	template<size_t count, typename point>
	SetOfPoints<count, point> operator*(const SetOfPoints<count, point>& mat1, const SetOfPoints<count, point>& mat2)
	{
		SetOfPoints <count, point> res;
		for (size_t i = 0;i < count;i++)
		{
			res[i] = mat1 * mat2[i];
		}
		return res;
	}
}