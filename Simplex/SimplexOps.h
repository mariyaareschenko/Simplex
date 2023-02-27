#pragma once
#include <functional>
namespace OptLib
{
	namespace SimplexOps
	{
		namespace UnaryOps
		{
			template<class Scalar>
			struct plus
			{
				plus(Scalar value) : scalar{ value } {};
				template<class T = void>
				T operator()(const T& lhs)
				{
					return lhs + scalar;
				}
			protected:
				Scalar scalar;
			};
			template<class Scalar>
			struct minus
			{
				minus(Scalar value) : scalar{ value } {};
				template<class T = void>
				T operator()(const T& lhs)
				{
					return lhs - scalar;
				}
			protected:
				Scalar scalar;
			};
			template<class Scalar>
			struct multiplies
			{
				multiplies(Scalar value) : scalar{ value } {};
				template<class T = void>
				T operator()(const T& ihs)
				{
					return ihs * scalar;
				}
			protected:
				Scalar scalar;
			};
			template<class Scalar>
			struct division
			{
				division(Scalar value) : scalar{ value } {};
				template<class T = void>
				T operator()(const T& ihs)
				{
					return ihs / scalar;
				}
			protected:
				Scalar scalar;
			};
			template<class Scalar>
			struct div2
			{
				div2(Scalar value) : scalar{ value } {};
				template<class T = void>
				T operator()(const T& ihs)
				{
					return scalar/ihs;
				}
			protected:
				Scalar scalar;
			};

			template<class T = void>
			struct Abs
			{
				template<class T = void>
				T operator()(const T& ihs)
				{
					return abs(ihs);
				}
			};

			template<class T = void>
			struct Sqrt
			{
				template<class T = void>
				T operator()(const T& ihs)
				{
					return sqrt(ihs);
				}
			};
		}
		namespace BinaryOps
		{
			template<class T = void>
			using plus = std::plus<T>;
			template<class T = void>
			using minus = std::minus<T>;
			template<class T = void>
			using multiplies = std::multiplies<T>;
		}
	}
}
