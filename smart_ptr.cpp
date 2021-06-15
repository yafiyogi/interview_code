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
#include <atomic>

using namespace std;

template<typename T>
class SmartPtr
{
public:
  using type = T;
  using ptr_type = T *;
  SmartPtr():
    ptr_(nullptr)
  {
  }

  SmartPtr(ptr_type ptr):
    ptr_(new ptr_data{1, ptr})
  {
  }

  SmartPtr(const SmartPtr & other):
    ptr_(nullptr)
  {
    assign(other.ptr_);
  }

  SmartPtr(SmartPtr && other):
    ptr_(nullptr)
  {
    std::swap(ptr_, other.ptr_);
  }

  virtual ~SmartPtr()
  {
    destroy();
  }

  SmartPtr & operator=(const SmartPtr & other)
  {
    if( this != &other)
    {
      destroy();
      assign(other.ptr_);
    }

    *this;
  }

  SmartPtr & operator=(SmartPtr && other)
  {
    if( this != &other)
    {
      destroy();
      std::swap(ptr_, other.ptr_);
    }

    return *this;
  }

  type & operator*()
  {
    return *(ptr_->ptr);
  }

  ptr_type operator->()
  {
    return ptr_->ptr;
  }

  std::size_t count() const
  {
    if(nullptr == ptr_)
    {
      return 0;
    }

    return ptr_->count;
  }

private:
  struct ptr_data
  {
    ptr_data(int c, ptr_type p):
      count(c),
      ptr(p)
    {
    }

    std::atomic<std::size_t> count;
    ptr_type ptr;
  };

  void assign(ptr_data * other)
  {
    ptr_ = other;
    if(nullptr != ptr_)
    {
      ++ptr_->count;
    }
  }

  void destroy()
  {
    if(nullptr == ptr_)
    {
      return;
    }

    if(0 == --ptr_->count)
    {
      delete ptr_->ptr;
      delete ptr_;
    }
    ptr_ = nullptr;
  }

  ptr_data * ptr_;
};

class Thing
{
public:
  Thing():
    id(++count)
  {
    cout << "Create Thing id=" << id << endl;
  }

  Thing( const Thing & other):
    id( other.id + 100)
  {
    cout << "Copy Create of Thing id=" << other.id << " (id=" << id << ")" << endl;
    ++count;
  }

  Thing( Thing && other):
    id( other.id + 1000)
  {
    cout << "Move Create of Thing id=" << other.id << " (id=" << id << ")" << endl;
    ++count;
  }

  Thing & operator=(const Thing & other)
  {
    cout << "Copy Thing id=" << other.id << " to thing id=" << id << endl;

    return *this;
  }

  Thing & operator=(const Thing && other)
  {
    cout << "Move Thing id=" << other.id << " to thing id=" << id << endl;

    return *this;
  }

  ~Thing()
  {
    cout << "Destroy Thing id=" << id << endl;
  }

  int id;
  static int count;
};

int Thing::count = 0;

int main()
{
  cout << 1 << endl;
  SmartPtr<Thing> a( new Thing{});
  cout << 2 << " a count=" << a.count() << endl;

  cout << "2a" << " a= " << (*a).id << endl;
  cout << "2b" <<  " a= " << a->id << endl;

  cout << 3 << " a count=" << a.count() << endl;
    SmartPtr<Thing> b = a;
    cout << "3a" << " b= " << (*b).id << endl;
    cout << "3b" <<  " b= " << b->id << endl;
  cout << 4 << " a count=" << a.count() << endl;

  cout << 5 << " a count=" << a.count() << endl;

  cout << 6 << " a count=" << a.count() << endl;
  SmartPtr<Thing> c( std::move(b));
  cout << 7 << " a count=" << a.count() << endl;

    cout << 8 << " a count=" << a.count() << endl;
    SmartPtr<Thing> d;
    d = std::move(c);
    cout << 9 << " a count=" << a.count() << endl;

    d = SmartPtr<Thing>{};

  a = SmartPtr<Thing>{new Thing{}};
    cout << 10 << " a count=" << a.count() << endl;
  return 0;
}
