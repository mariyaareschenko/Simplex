#pragma once
#include<array>
#include<cmath>
#include"Simplex.h"

namespace FuncInterface
{

	template<size_t dim>
	class IFunc
	{
	public:	
		virtual double operator()(const OptLib::Point<dim>& p) const = 0;
		template<size_t count>
		OptLib::Point<count> operator()(const OptLib::SetOfPoints<count, OptLib::Point<dim>>& arr) const
		{
			OptLib::Point<count> out;
			for (int i = 0;i < count;i++)
				out = this->operator()(arr[i]);
			return out;
		}
	};
	template<size_t dim>
	class IGrad
	{
	public:
		virtual OptLib::Point<dim> grad(const OptLib::Point<dim>& p) const = 0;
		template<size_t count>
		OptLib::SetOfPoints<count, OptLib::Point<dim>> grad(const OptLib::SetOfPoints<count, OptLib::Point<dim>>& arr) const
		{
			OptLib::SetOfPoints<count, OptLib::Point<dim>> out;
			for (int i = 0; i < count;i++)
				out = this->grad(arr[i]);
			return out;
		}		
	};
	template<size_t dim>
	class IHess
	{
	public:
		virtual OptLib::Point<dim> hess(const OptLib::Point<dim>& p) const = 0;
	};
	template<size_t dim>
	class IFuncWhithGrad : public IFunc<dim>,public IGrad<dim>
	{};
	template <size_t dim>
	class IFuncWithHess : public IFuncWhithGrad<dim>, public IHess<dim>
	{};
}
namespace OptLib {

	namespace ConcretFunc
	{
		class Sin1 : public FuncInterface::IFuncWithHess<1>
		{
		public:
			double operator()(const OptLib::Point<1>& p)const override
			{
				return { sin(p[0]) };
			}
			OptLib::Point<1> grad(const OptLib::Point<1>& p) const override
			{
				return OptLib::Point<1>{cos(p[0])};
			}
			OptLib::Point<1> hess(const OptLib::Point<1>& p) const override
			{
				return OptLib::Point<1>{-sin(p[0])};
			}
		};

		class Sin2 :public FuncInterface::IFuncWithHess<2>
		{
		public:
			double operator()(const OptLib::Point<2>& p) const override
			{
				return { sin(p[0] + p[1]) };
			}
			OptLib::Point<2> grad(const OptLib::Point<2>& p) const override
			{
				return OptLib::Point<2>{cos(p[0] + p[1])};
			}
			OptLib::Point<2> hess(const OptLib::Point<2>& p) const override
			{
				return OptLib::Point<2>{-sin(p[0] + p[1])};
			}
		};
		/*class SinK :public FuncInterface::IFuncWithHess<1>
		{
		public:

			double operator()(const OptLib::Point<1>& p)const override
			{

				return { sin(p[0] ) };
			}
			OptLib::Point<1> grad(const OptLib::Point<1>& p) const override
			{
				return OptLib::Point<1>{cos(p[0])};
			}
			OptLib::Point<1> hess(const OptLib::Point<1>& p) const override
			{
				return OptLib::Point<1>{-sin(p[0])};
			}
		};*/
		template<size_t dim>
		class Paraboloid :public FuncInterface::IFuncWhithGrad<dim>
		{
		public:
			double operator ()(const Point<dim>& p)const override
			{
				Point<dim> res = p * p;
				return pointToDouble(res);
			}
			double pointToDouble(const Point<dim>& p)
			{
				double res = 0;
				for (auto& el : p)
					res += el;
				return res;
			}

			double operator()(const Point<dim>& x, SetOfPoints<dim, Point<dim>> mat_A)
			{
				SetOfPoints<dim, Point<1>>x_tr{ Tr(x) };
				SetOfPoints<dim, Point<1>> mult = x_tr * mat_A;
				double res = mult * x;
				return res;
			}

			Point <dim> grad(const Point<dim>& p) const override
			{
				return 2 * p;
			}

			SetOfPoints<dim, Point<1>> Tr(const Point<dim>& p)
			{
				SetOfPoints<dim, Point<1>> tr_mat;
				for (size_t i = 0;i < dim;i++)
				{
					Point<1>  q{ p[i] };
					tr_mat[i] = q;
				}
				return tr_mat;
			}
		};
	}
}
