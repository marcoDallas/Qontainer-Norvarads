#ifndef DEEPPTR_H
#define DEEPPTR_H

template <class T>
class DeepPtr
{
private:
  T *p;
public:
  DeepPtr(const T* t = nullptr) : p((t != nullptr) ? t->clone() : nullptr) { }

  DeepPtr(const DeepPtr& sp)
  {
    p = (sp.p)->clone();
  }

  DeepPtr& operator = (const DeepPtr& sp)
  {
    if ( this != &sp )
    {
      if (p)
        delete p;

      if ( sp.p )
        p = (sp.p)->clone();
      else
        p = nullptr;
    }
    return *this;
  }

  ~DeepPtr()
  {
    if (p)
      delete p;
  }

  T& operator *() const
  {
    return *p; // caller error if p is nullptr
  }

  T* operator ->() const
  {
    return p;
  }

  bool operator == (const DeepPtr& sp) const
  {
    return p == sp.p;
  }

  bool operator != (const DeepPtr& sp) const
  {
    return p != sp.p;
  }
};

#endif // DEEPPTR_H
