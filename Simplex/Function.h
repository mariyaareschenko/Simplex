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
namespace ConcretFunc
{
	class Sin1 : public FuncInterface ::IFuncWithHess<1>
	{
	public:
		double operator()(const OptLib::Point<1>& p)const override
		{
			return {sin(p[0])};
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
}
