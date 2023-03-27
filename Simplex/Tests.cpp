#include <iostream>
#include<array>
#include "Tests.h"
#include "Simplex.h"
#include "SimplexOps.h"
#include "Stream.h"
#include"Function.h"
namespace OptLib
{
    void test_plus()
    {
        Point<2> p1{ 1, 2 }, p2{ 3, 4 };

        std::cout << "\nout = " << "{" << p1 + p2 << "}";
    }
    void test_plus_scalar()
    {
        Point<2> p1{ 1, 2 };
        std::cout << "\nout = " "{" << p1 + 4.7 << "}";
    }
    void test_minus_scalar()
    {
        Point<2> p1{ 1, 2 };
        std::cout << "\nout = " << "{" << p1 -4.7  << "}";
    }
    void test_minus()
    {
        Point<2> p1{ 2, 1 }, p2{ 4, 3 };
        std::cout << "\nout = "<< "{" << p1 - p2 << "}";
    }
    void test_mult()
    {
        Point<2> p1{ 2, 1 }, p2{ 4, 3 };
        std::cout << "\nout =  " << "{" << p1 * p2 << "}";
    }
    void test_mult_scalar()
    {
        Point<2> p1{ 1,2 };
        std::cout << "\nout = " << "{" << p1 *2.1 << "}";
    }
    void test_div_scalar()
    {
        Point<2> p{ 1,2 };
        std::cout << "\nout = " << "{"<<p / 2.3<<"}";
    }
    void test_abs()
    {
        Point <2> p{ -4,-6 };
        auto res = Abs(p);
        std::cout << "\nout" << "{" << res << "}";
    }
    void test_sqrt()
    {
        Point<2> p{ 4,9 };
        auto res = Sqrt(p);
        std::cout << "\nout" << "{" << res << "}";
    }
    void test_matrix()
    {
        Point<2> p1{ -1,4 }, p2{ 2, 1.5 }, p3{-0.5, 3}, pv{ 2,-2 };
        SetOfPoints <2, Point<2>> mat1 = { p1,p2 };
        SetOfPoints <2, Point<2>> mat2 = { p1,p3 };
        Point<2> res1 = mat1 * pv;
        SetOfPoints<2, Point<2>> res2 = mat1 * mat2;
        std::cout<< "\nout" << "{" << res1 << "}";
        std::cout<< "\nout" << "{" << res2 << "}";
    }
    void test_mean()
    {
        Point<2> p1{ 0,0 }, p2{ 0, 1 }, p3{ 1, 0 };
        SetOfPoints <3, Point<2>> points = { p1,p2,p3 };
        RawSetOfPoints<3, Point<2>> P = points;
        Point<2> res = P.Mean();
        std::cout<< "\nout" << "{" << res << "}";
    }
    void test_pointval()
    {
        constexpr size_t dim = 2;
        constexpr size_t count = 3;
        using point = Point<dim>;
        using pointval = PointVal<dim>;

        point p1{ 1,2 }, p2{ 2,1 }, p3{ 2,3 };
        SetOfPoints<count, point> M{ p1,p2, p3 };
        std::array<double, count>arr{ 2.0,3.0,3.5 };
        SetOfPointsVal<count, point, pointval> P{std::move(M),std::move(arr)};
        //std::cout<< "\nout" << "{" << P << "}";
    }
    void test_sin()
    {
        Point<1> p1{ 1.2 }; 
        Point<2> p2{ -1,2.3 };
        double res1, res2, resk;
        FuncInterface::IFunc<1>* f1 = new ConcretFunc::Sin1{};
        FuncInterface::IFunc<2>* f2 = new ConcretFunc::Sin2{};
        res1 = (*f1)(p1);
        res2 = (*f2)(p2);
        std::cout << "\nsin p1: " << res1<<"\n"<<"sin p2:"<< res2;
    }
    /*void test_paraboloid()
    {
        Point<2> p1{ 1,1 }, p2{ 2,2 }, t{ 4,5 }, grad_res;
        double res;
        SetOfPoints<2, Point<2>> MatrConst{ p1,p2 };
        ConcretFunc::Paraboloid<2> paraboloid;
        res = paraboloid(t);
        std::cout << "valFunc" << t << "=" << res;
    }*/
    void test_grad()
    {
        Point <1> p1{ 2.2 }, p2{ 1.5 };
        double res;
        FuncInterface::IFunc<1>* f1 = new ConcretFunc::LinFunc{};

    }
}
    