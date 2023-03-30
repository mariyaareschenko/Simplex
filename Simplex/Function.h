#pragma once
#include<array>
#include<cmath>
#include"Simplex.h"

namespace OptLib
{
	namespace FuncInterface
	{

		template<size_t dim>
		class IFunc
		{
		public:
			virtual double operator()(const Point<dim>& p) const = 0;
			template<size_t count>
			OptLib::Point<count> operator()(const SetOfPoints<count, Point<dim>>& arr) const
			{
				Point<count> out;
				for (int i = 0;i < count;i++)
					out = this->operator()(arr[i]);
				return out;
			}
		};
		template<size_t dim>
		class IGrad
		{
		public:
			virtual Point<dim> grad(const Point<dim>& p) const = 0;
			template<size_t count>
			SetOfPoints<count, Point<dim>> grad(const SetOfPoints<count, Point<dim>>& arr) const
			{
				SetOfPoints<count, Point<dim>> out;
				for (int i = 0; i < count;i++)
					out = this->grad(arr[i]);
				return out;
			}
		};
		template<size_t dim>
		class IHess
		{
		public:
			virtual Point<dim> hess(const Point<dim>& p) const = 0;
		};
		template<size_t dim>
		class IFuncWhithGrad : public IFunc<dim>, public IGrad<dim>
		{};
		template <size_t dim>
		class IFuncWithHess : public IFuncWhithGrad<dim>, public IHess<dim>
		{};

		template<size_t dimX, size_t dimP>
		class IFuncParam
		{
		public:
			virtual double operator()(const Point<dimX>& x, const Point<dimP>& p) const = 0;
			template<size_t count>
			Point<count> operator()(const SetOfPoints<count, Point<dimX>>& x, const Point<dimP>& p) const
			{
				Point<count> out;
				for (int i = 0;i < count;i++)
					out[i] = this->operator()(x[i], p);
				return out;
			}
		};

		template<size_t dimX, size_t dimP>
		class IFunParamGrag :public IFuncParam<dimX, dimP>
		{
		public:
			virtual Point<dimX> GradP(const Point<dimX>& x, const Point<dimP>& p) const = 0;
		};
	}
}
namespace OptLib {

	namespace ConcretFunc
	{
		class Sin1 : public FuncInterface::IFuncWithHess<1>
		{
		public:
			double operator()(const Point<1>& p)const override
			{
				return { sin(p[0]) };
			}
			Point<1> grad(const Point<1>& p) const override
			{
				return OptLib::Point<1>{cos(p[0])};
			}
			Point<1> hess(const Point<1>& p) const override
			{
				return Point<1>{-sin(p[0])};
			}
		};

		class Sin2 :public FuncInterface::IFuncWithHess<2>
		{
		public:
			double operator()(const Point<2>& p) const override
			{
				return { sin(p[0] + p[1]) };
			}
			Point<2> grad(const Point<2>& p) const override
			{
				return Point<2>{cos(p[0] + p[1])};
			}
			Point<2> hess(const Point<2>& p) const override
			{
				return Point<2>{-sin(p[0] + p[1])};
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
		class LinFunc :public FuncInterface::IFuncParam<1, 1>
		{
		public:
			double operator()(const Point<1>& x, const Point<1>&p) const override
			{
				return x[0] * p[0];
			}
		};
		class LinFuncGrad :public FuncInterface::IFunParamGrag<1, 1>
		{
		public:
			double operator()(const Point<1>& x, const Point<1>& p) const override
			{
				return x[0] * p[0];
			}
			Point<1> GradP(const Point<1>& x, const Point<1>& p) const override
			{
				return p;
			}
		};
	}
}
