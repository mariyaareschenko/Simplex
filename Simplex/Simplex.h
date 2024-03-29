#pragma once
#include <iostream>
#include <memory>
#include <algorithm>
#include<array>
#include <cassert>
#include <cmath>
#include"SimplexOps.h"
namespace OptLib
{
	template<size_t dim>//��������� ��������� ����� � ���������� ����� ������ � 8 ����
	using Point = std::array<double, dim>; //��������� (Point) � ������� � ��������� ������� � ���-�� ���� ����� - dim
	//static constexpr size_t Dim = dim;
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
		RawPoint(const Point<dim>& p) : P{ p } {}; //�� ����������� ����������� 
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
	template<size_t dim>
	SetOfPoints<dim, Point<1>> operator*(const SetOfPoints<dim, Point<1>> x, const SetOfPoints<dim, Point<dim>> A)
	{
		SetOfPoints<dim, Point<1>>res;
		for (size_t i = 0; i < dim;i++)
		{
			Point<1> p1{ 0.0 };
			for (size_t j = 0; j < dim;j++)
			{
				p1 = p1 + x[j][0] * A[i][j];
			}
			res[i] = p1;
		}
		return res;
	}
	template<size_t count, typename point>
	class RawSetOfPoints
	{
	protected:
		SetOfPoints<count, point> ItsSetOfPoints;
	public:
		RawSetOfPoints() = default;
		RawSetOfPoints(SetOfPoints<count, point>&& s):ItsSetOfPoints{ std::move(s) }{};
		RawSetOfPoints(const SetOfPoints<count, point>& sop) :ItsSetOfPoints{ sop } {};
		const point& operator[](size_t idx)
		{
			assert(idx < count);
			return ItsSetOfPoints[idx];
		}
		point Mean() const
		{
			point p = ItsSetOfPoints[0];
			if constexpr (count > 1) 
			{
				for (size_t i = 1; i < count; i++)
				{
					p = p + ItsSetOfPoints[i];
				}	

			}
			return p / count;
		}
		/*std::pair<point, point> Dispersion() const
		{
			point avg{ Mean() };
			point result = (Point()[0] - avg) * (Points([0] - avg);
			for (size_t i = 1; i < count; i++)
				result = result + (Points()[i] - avg) * (Points()[i] - avg);
			return { avg,result / (count + 0.0) };
		}*/
	};
	template <size_t count, typename point, typename pointval>
	class SetOfPointsVal :RawSetOfPoints < count, pointval>
	{	

	public:
		SetOfPointsVal(SetOfPoints<count, pointval>&& s) :RawSetOfPoints<count, pointval>{ std::move(s) } {}
		SetOfPointsVal(SetOfPoints<count, point>&& s, std::array<double, count>&& Pval) : 
		SetOfPointsVal<count, point, pointval>{ std::move(make_field(std::move(s),std::move(Pval))) } {}
	protected:
		static SetOfPoints<count, pointval> make_field(SetOfPoints<count, point>&& s, std::array<double, count>&& vals)
		{
			SetOfPoints<count, pointval> P;
			for (size_t i = 0;i < count;i++)
			{
				P[i] = pointval{ s[i], vals[i] };
			}
			return P;                                                                                                                                        
		}
	};
	template<size_t count, typename point, typename pointval>
	class SetOfPointsValSort : public SetOfPointsVal<count, point, pointval>
	{
	private:
		void Sort(SetOfPointsVal<count, point,pointval> ItsSetOfPoints)
		{
			
			std::sort(ItsSetOfPoints.begin(), ItsSetOfPoints.end());
		}
	public:
		SetOfPointsValSort() = default;
		SetOfPointsValSort(SetOfPoints<count, pointval>&& s) :SetOfPointsVal<count, point, pointval>{ std::move(s) } {this->Sort();}
		SetOfPointsValSort(SetOfPoints<count,point>&& s,std::array<double,count>&&vals):
			SetOfPointsVal<count, point, pointval>{ std::move(s),std::move(vals) } {this->Sort();}
	};
}