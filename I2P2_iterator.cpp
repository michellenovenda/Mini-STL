#include "../header/I2P2_iterator.h"
#include<iostream>

namespace I2P2 {

//===================================VECTOR========================================//

  //array 0 1 2 3 4 5
  //move one pointer to the next one (from 0, ++ = 1, ++ = 2...)
  
  vector_iterator::vector_iterator()
  {
    std::cout << "vector_iterator::vector_iterator()" << std::endl;
    vct = nullptr;
  }

  iterator_impl_base &vector_iterator::operator++() 
  {
    std::cout << "vector_iterator::operator++" << std::endl;
    vct = vct+1;
    return *this; 
  }

  iterator_impl_base &vector_iterator::operator--()
  {
    std::cout << "vector_iterator::operator--" << std::endl;
    vct = vct-1;
    return *this;
  }

  iterator_impl_base &vector_iterator::operator+=(difference_type offset)
  {
    std::cout << "vector_iterator::operator+=" << std::endl;
    vct += offset;
    return *this;
  }

  iterator_impl_base &vector_iterator::operator-=(difference_type offset)
  {
    std::cout << "vector_iterator::operator-=" << std::endl;
    vct -= offset;
    return *this;
  }

  bool vector_iterator::operator==(const iterator_impl_base &rhs) const
  {
    std::cout << "vector_iterator::operator==" << std::endl;
    if(*vct == *rhs)
      return true;

    else
      return false;
  }

  bool vector_iterator::operator!=(const iterator_impl_base &rhs) const
  {
    std::cout << "vector_iterator::operator!=" << std::endl;
    if(*vct != *rhs)
      return true;

    else
      return false;
  }

  bool vector_iterator::operator<(const iterator_impl_base &rhs) const
  {
    std::cout << "vector_iterator::operator<" << std::endl;
    if(*vct < *rhs)
      return true;

    else
      return false;
  }

  bool vector_iterator::operator>(const iterator_impl_base &rhs) const
  {
    std::cout << "vector_iterator::operator>" << std::endl;
    if(*vct > *rhs)
      return true;

    else
      return false;
  }

  bool vector_iterator::operator<=(const iterator_impl_base &rhs) const
  {
    std::cout << "vector_iterator::operator<=" << std::endl;
    if(*vct <= *rhs)
          return true;

    else
      return false;
  }

  bool vector_iterator::operator>=(const iterator_impl_base &rhs) const
  {
    std::cout << "vector_iterator::operator>=" << std::endl;
    if(*vct >= *rhs)
      return true;

    else
      return false;
  }

  difference_type vector_iterator::operator-(const iterator_impl_base &rhs) const
  {
    std::cout << "vector_iterator::operator-" << std::endl;
    difference_type diff = *vct - *rhs;
    return diff;
  }

  pointer vector_iterator::operator->() const //return address
  {
    std::cout << "vector_iterator::operator->" << std::endl;
    return &*vct;
  }

  reference vector_iterator::operator*() const //return data
  {
    std::cout << "vector_iterator::operator*" << std::endl;
    return *vct;
  }

  reference vector_iterator::operator[](difference_type offset) const
  {
    std::cout << "vector_iterator::operator[]" << std::endl;
    return vct[offset];
  }


//===================================LIST========================================//

  list_iterator::list_iterator()
  {
    std::cout << "list_iterator::list_iterator()" << std::endl;
    lst = nullptr;
  }

  iterator_impl_base &list_iterator::operator++()//ok
  {
    std::cout << "list_iterator::operator++" << std::endl;
    lst = lst->next;
    return *this;
  }

  iterator_impl_base &list_iterator::operator--()//ok
  {
    std::cout << "list_iterator::operator--" << std::endl;
    lst = lst->prev;
    return *this;
  }

  iterator_impl_base &list_iterator::operator+=(difference_type offset)//ok
  {
    std::cout << "list_iterator::operator+=" << std::endl;
    for(difference_type i=0; i<offset; i++)
      lst = lst->next;
    return *this;
  }

  iterator_impl_base &list_iterator::operator-=(difference_type offset)//ok
  {
    std::cout << "list_iterator::operator-=" << std::endl;
    for(difference_type i=0; i<offset; i++)
      lst = lst->prev;
    return *this;
  }

  bool list_iterator::operator==(const iterator_impl_base &rhs) const//ok
  {
    std::cout << "list_iterator::operator==" << std::endl;
    if(lst->data == *rhs)
      return true;

    else
      return false;
  }

  bool list_iterator::operator!=(const iterator_impl_base &rhs) const//ok
  {
    std::cout << "list_iterator::operator!=" << std::endl;
    if(lst->data != *rhs)
          return true;

    else
      return false;
  }

  bool list_iterator::operator<(const iterator_impl_base &rhs) const//ok
  {
    std::cout << "list_iterator::operator<" << std::endl;
    if(lst->data < *rhs)
              return true;

    else
      return false;
  }

  bool list_iterator::operator>(const iterator_impl_base &rhs) const//ok
  {
    std::cout << "list_iterator::operator>" << std::endl;
    if(lst->data > *rhs)
              return true;

    else
      return false;
  }

  bool list_iterator::operator<=(const iterator_impl_base &rhs) const//ok
  {
    std::cout << "list_iterator::operator<=" << std::endl;
    if(lst->data <= *rhs)
      return true;

    else
      return false;
  }

  bool list_iterator::operator>=(const iterator_impl_base &rhs) const//ok
  {
    std::cout << "list_iterator::operator>=" << std::endl;
    if(lst->data >= *rhs)
              return true;

    else
      return false;
  }

  difference_type list_iterator::operator-(const iterator_impl_base &rhs) const//ok
  {
    std::cout << "list_iterator::operator-" << std::endl;
    difference_type diff = lst - rhs.node_ref();
    return diff;
  }

  pointer list_iterator::operator->() const//ok
  {
    std::cout << "list_iterator::operator->" << std::endl;
    return &lst->data;
  }

  reference list_iterator::operator*() const//ok
  {
    std::cout << "list_iterator::operator*" << std::endl;
    return lst->data;
  }

  reference list_iterator::operator[](difference_type offset) const//ok
  {
    std::cout << "list_iterator::operator[]" << std::endl;
    Node* ptr;

    while(offset--)
      ptr = ptr->next;

    return ptr->data;
  }

//=====================================CONST ITERATOR============================================//
//iterator constant bisa ngechange value, constant gabisa ngechange
  const_iterator::~const_iterator()
  {
    std::cout << "const_iterator::~const_iterator()" << std::endl;
    delete p_;
    p_ = nullptr;
  }

  const_iterator::const_iterator()
  {
    std::cout << "const_iterator::const_iterator()" << std::endl;
      p_ = nullptr;
  }

  const_iterator::const_iterator(const const_iterator &rhs)
  {
    std::cout << "const_iterator::const_iterator(const const_iterator &rhs)" << std::endl;
    p_ = rhs.p_->clone();
  }

  const_iterator::const_iterator(iterator_impl_base *p)
  {
    std::cout << "const_iterator::const_iterator(iterator_impl_base *p)" << std::endl;
      p_ = p->clone();
  }

  const_iterator &const_iterator::operator=(const const_iterator &rhs)
  {
    std::cout << "const_iterator &const_iterator::operator=(const const_iterator &rhs)" << std::endl;
     p_ = rhs.p_;
     return *this;
  }

  const_iterator &const_iterator::operator++() //pindahin pointer to next
  {
    std::cout << "const_iterator &const_iterator::operator++()" << std::endl;
    ++*p_;
    return *this;
  }

  const_iterator const_iterator::operator++(int)
  {
    std::cout << "const_iterator const_iterator::operator++(int)" << std::endl;
    const_iterator copy = p_;
    ++*p_;
    return copy;
  }

  const_iterator &const_iterator::operator--()
  {
    std::cout << "const_iterator &const_iterator::operator--()" << std::endl;
    --*p_;
    return *this;
  }

  const_iterator const_iterator::operator--(int)
  {
    std::cout << "const_iterator const_iterator::operator--(int)" << std::endl;
    const_iterator copy = p_;
    --*p_;
    return copy;
  }

  const_iterator &const_iterator::operator+=(difference_type offset)
  {
    std::cout << "const_iterator &const_iterator::operator+=(difference_type offset)" << std::endl;
    for(difference_type i=0; i<offset; i++)
      ++*p_;
    
    return *this;
  }

  const_iterator const_iterator::operator+(difference_type offset) const
  {
    std::cout << "const_iterator const_iterator::operator+(difference_type offset) const" << std::endl;
    iterator it(p_);
    
    while (offset--)
      ++it;
    
    return it;
  }

  const_iterator &const_iterator::operator-=(difference_type offset)
  {
    std::cout << "const_iterator &const_iterator::operator-=(difference_type offset)" << std::endl;
    for(difference_type i=0; i<offset; i++)
      --*p_;
    
    return *this;
  }

  const_iterator const_iterator::operator-(difference_type offset) const
  {
    std::cout << "const_iterator const_iterator::operator-(difference_type offset) const" << std::endl;
    iterator it(p_);
    
    while (offset--)
      --it;
    
    return it;
  }

  difference_type const_iterator::operator-(const const_iterator &rhs) const
  {
    std::cout << "difference_type const_iterator::operator-(const const_iterator &rhs) const" << std::endl;
    difference_type diff = *p_ - *rhs.p_;
    return diff;
  }

  const_iterator::pointer const_iterator::operator->() const
  {
    std::cout << "const_iterator::pointer const_iterator::operator->() const" << std::endl;
    return &**p_;
  }

  const_iterator::reference const_iterator::operator*() const
  {
    std::cout << "const_iterator::reference const_iterator::operator*() const" << std::endl;
    return *(*p_);
  }

  const_iterator::reference const_iterator::operator[](difference_type offset) const
  {
    std::cout << "const_iterator::reference const_iterator::operator[](difference_type offset) const" << std::endl;
    return *p_[offset];
  }

  bool const_iterator::operator==(const const_iterator &rhs) const
  {
    std::cout << "bool const_iterator::operator==(const const_iterator &rhs) const" << std::endl;
    return *(p_) == *rhs.p_;
  }

  bool const_iterator::operator!=(const const_iterator &rhs) const
  {
    std::cout << "bool const_iterator::operator!=(const const_iterator &rhs) const" << std::endl;
    if(*p_ != *rhs.p_)
      return true;

    else
      return false;
  }

  bool const_iterator::operator<(const const_iterator &rhs) const
  {
    std::cout << "bool const_iterator::operator<(const const_iterator &rhs) const" << std::endl;
    if(*p_ < *rhs.p_)
      return true;

    else
      return false;
  }

  bool const_iterator::operator>(const const_iterator &rhs) const
  {
    std::cout << "bool const_iterator::operator>(const const_iterator &rhs) const" << std::endl;
    if(*p_ > *rhs.p_)
      return true;

    else
      return false;
  }

  bool const_iterator::operator<=(const const_iterator &rhs) const
  {
    std::cout << "bool const_iterator::operator<=(const const_iterator &rhs) const" << std::endl;
    if(*p_ <= *rhs.p_)
      return true;

    else
      return false;
  }

  bool const_iterator::operator>=(const const_iterator &rhs) const
  {
    std::cout << "bool const_iterator::operator>=(const const_iterator &rhs) const" << std::endl;
    if(*p_ >= *rhs.p_)
      return true;

    else
      return false;
  }

  /* This class holds an iterator_impl_base
   * and you may want to have some ways to 
   * invoke a container-specialized method from here
   * for insert/erase methods (look at their parameters if you are not sure) */


//=====================================ITERATOR============================================//

  iterator::iterator()
  {
    std::cout << "iterator::iterator()" << std::endl;
      p_ = nullptr;
  }

  iterator::iterator(iterator_impl_base *p)
  {
    std::cout << "iterator::iterator(iterator_impl_base *p)" << std::endl;
      p_ = p->clone();
  }

  iterator::iterator(const iterator &rhs)
  {
    std::cout << "iterator::iterator(const iterator &rhs)" << std::endl;
      p_ = rhs.p_->clone();
  }

  iterator &iterator::operator++()
  {
    std::cout << "iterator &iterator::operator++()" << std::endl;
    ++*p_;
    return *this;
  }

  iterator iterator::operator++(int)
  {
    std::cout << "iterator iterator::operator++(int)" << std::endl;
    iterator copy = p_;
    ++*p_;
    return copy;
  }

  iterator &iterator::operator--()
  {
    std::cout << "iterator &iterator::operator--()" << std::endl;
    --*p_;
    return *this;
  }

  iterator iterator::operator--(int)
  {
    std::cout << "iterator iterator::operator--(int)" << std::endl;
    iterator copy = p_;
    --*p_;
    return copy;
  }

  iterator &iterator::operator+=(difference_type offset)
  {
    std::cout << "iterator &iterator::operator+=(difference_type offset)" << std::endl;
    for(difference_type i=0; i<offset; i++)
      ++*p_;
    
    return *this;
  }

  iterator iterator::operator+(difference_type offset) const
  {
    std::cout << "iterator iterator::operator+(difference_type offset) const" << std::endl;
    iterator it(p_);
    
    while (offset--)
      ++it;
    
    return it;
  }

  iterator &iterator::operator-=(difference_type offset)
  {
    std::cout << "iterator &iterator::operator-=(difference_type offset)" << std::endl;
    for(difference_type i=0; i<offset; i++)
      --*p_;
    
    return *this;
  }

  iterator iterator::operator-(difference_type offset) const
  {
    std::cout << "iterator iterator::operator-(difference_type offset) const" << std::endl;
    iterator it(p_);
    
    while (offset--)
      --it;
    
    return it;
  }

  difference_type iterator::operator-(const iterator &rhs) const
  {
    std::cout << "difference_type iterator::operator-(const iterator &rhs) const" << std::endl;
    difference_type diff = *p_ - *rhs.p_;
    return diff;
  }

  pointer iterator::operator->() const
  {
    std::cout << "pointer iterator::operator->() const" << std::endl;
    return &**p_;
  }

  reference iterator::operator*() const
  {
    std::cout << "reference iterator::operator*() const" << std::endl;
    return *(*p_);
  }

  reference iterator::operator[](difference_type offset) const
  {
    std::cout << "reference iterator::operator[](difference_type offset) const" << std::endl;
    return *p_[offset];
  }
}  // namespace I2P2


