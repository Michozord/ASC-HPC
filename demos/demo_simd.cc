#include <iostream>
#include <sstream>


#include <simd.h>

using namespace ASC_HPC;
using std::cout, std::endl;

auto Func1 (SIMD<double> a, SIMD<double> b)
{
  return a+b;
}

auto Func2 (SIMD<double,4> a, SIMD<double,4> b)
{
  return a+3*b;
}

auto Func3 (SIMD<double,4> a, SIMD<double,4> b, SIMD<double,4> c)
{
  return FMA(a,b,c);
}


auto Load (double * p)
{
  return SIMD<double,2>(p);
}

auto LoadMask (double * p, SIMD<mask64,2> m)
{
  return SIMD<double,2>(p, m);
}

auto TestSelect (SIMD<mask64,2> m, SIMD<double,2> a, SIMD<double,2> b)
{
  return Select (m, a, b);
}

SIMD<double,2> TestHSum (SIMD<double,4> a, SIMD<double,4> b)
{
  return HSum(a,b);
}



int main()
{
  SIMD<double,4> a(1.,2.,3.,4.);
  SIMD<double,4> b(1.0);

  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "a+b = " << a+b << endl;
  cout << "a-b = " << a-b << endl;

  cout << "HSum(a) = " << HSum(a) << endl;
  cout << "HSum(a,b) = " << HSum(a,b) << endl;

  
  auto sequ = IndexSequence<int64_t, 4>();
  cout << "sequ = " << sequ << endl;
  auto mask = (2 >= sequ);
  cout << "2 >= " << sequ << " = " << mask << endl;

  {
    double a[] = { 10, 10, 10, 10 };
    SIMD<double,4> sa(&a[0], mask);
    cout << "sa = " << sa << endl;
  }

  cout << "Select(mask, a, b) = " << Select(mask, a,b) << endl;

  //test division
  std::cout << "b/a = "<< b/a <<std::endl;
  std::cout << "b/2 = "<< b/2. <<std::endl;
  // test <=
  std::cout <<"a<b = "<<(a<b) << " a>b = "<<(a>b) <<std::endl;
  std::cout <<"a==b = "<<(a==b) << " a==a ="<<(a==a) <<std::endl;


  //test transposition
  SIMD<double,4> a0(1.,2.,3.,4.);
  SIMD<double,4> a1(5.,6.,7.,8.);
  SIMD<double,4> a2(9.,10.,11.,12.);
  SIMD<double,4> a3(13.,14.,15.,16.);
  SIMD<double,4> b0(1.,2.,3.,4.);
  SIMD<double,4> b1(5.,6.,7.,8.);
  SIMD<double,4> b2(9.,10.,11.,12.);
  SIMD<double,4> b3(13.,14.,15.,16.);
  Transpose(a0, a1, a2, a3, b0, b1, b2, b3);
  cout<<b0<<endl<<b1<<endl<<b2<<endl<<b3<<endl;

}
