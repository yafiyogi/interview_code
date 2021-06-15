/*

MIT License

Copyright (c) 2021 Yafiyogi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <iostream>

using namespace std;

int fib_iter(int n)
{
  if( 0 == n)
  {
    return 0;
  }

  if(1 == n)
  {
    return 1;
  }

  int fib_m1 = 0;
  int fib_m2 = 1;
  int fib = 0;

  for(auto ii = 0; ii < n; ++ii)
  {
    fib = fib_m1 + fib_m2;
    fib_m2 = fib_m1;
    fib_m1 = fib;
  }

  return fib;
}


int fib_recu(int n)
{
  if(0 == n)
  {
    return 0;
  }

  if(1 == n)
  {
    return 1;
  }

  return fib_recu(n - 1) + fib_recu(n - 2);
}

int fib_tail_recu(int n, int fib_m2 = 0, int fib_m1 = 1)
{
  if(0 == n)
  {
    return fib_m2;
  }

  if(1 == n)
  {
    return fib_m1;
  }

  return fib_tail_recu(n - 1, fib_m1, fib_m2 + fib_m1);
}

int main()
{
  cout << "fib 0=" << fib_iter(0) << endl;
  cout << "fib 1=" << fib_iter(1) << endl;
  cout << "fib 2=" << fib_iter(2) << endl;
  cout << "fib 3=" << fib_iter(3) << endl;
  cout << "fib 4=" << fib_iter(4) << endl;
  cout << "fib 5=" << fib_iter(5) << endl;
  cout << "fib 6=" << fib_iter(6) << endl;
  cout << "fib 7=" << fib_iter(7) << endl;
  cout << "fib 8=" << fib_iter(8) << endl;
  cout << "fib 9=" << fib_iter(9) << endl;

  cout << endl;

  cout << "fib 0=" << fib_recu(0) << endl;
  cout << "fib 1=" << fib_recu(1) << endl;
  cout << "fib 2=" << fib_recu(2) << endl;
  cout << "fib 3=" << fib_recu(3) << endl;
  cout << "fib 4=" << fib_recu(4) << endl;
  cout << "fib 5=" << fib_recu(5) << endl;
  cout << "fib 6=" << fib_recu(6) << endl;
  cout << "fib 7=" << fib_recu(7) << endl;
  cout << "fib 8=" << fib_recu(8) << endl;
  cout << "fib 9=" << fib_recu(9) << endl;

  cout << endl;

  cout << "fib 0=" << fib_tail_recu(0) << endl;
  cout << "fib 1=" << fib_tail_recu(1) << endl;
  cout << "fib 2=" << fib_tail_recu(2) << endl;
  cout << "fib 3=" << fib_tail_recu(3) << endl;
  cout << "fib 4=" << fib_tail_recu(4) << endl;
  cout << "fib 5=" << fib_tail_recu(5) << endl;
  cout << "fib 6=" << fib_tail_recu(6) << endl;
  cout << "fib 7=" << fib_tail_recu(7) << endl;
  cout << "fib 8=" << fib_tail_recu(8) << endl;
  cout << "fib 9=" << fib_tail_recu(9) << endl;

  return 0;
}
