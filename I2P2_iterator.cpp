#include "../header/I2P2_iterator.h"
#include<iostream>

namespace I2P2 {

//===================================VECTOR========================================//
  vector_iterator::vector_iterator()
  {
    vct = nullptr;
  }

  iterator_impl_base &vector_iterator::operator++() 
  {
    vct = vct+1;
    return *this; 
  }

  iterator_impl_base &vector_iterator::operator--()
  {
    vct = vct-1;
    return *this;
  }

  iterator_impl_base &vector_iterator::operator+=(difference_type offset)
  {
    vct += offset;
    return *this;
  }

  iterator_impl_base &vector_iterator::operator-=(difference_type offset)
  {
    vct -= offset;
    return *this;
  }

  bool vector_iterator::operator==(const iterator_impl_base &rhs) const
  {
    return vct == rhs.operator->();
  }

  bool vector_iterator::operator!=(const iterator_impl_base &rhs) const
  {
    return vct != rhs.operator->();
  }

  bool vector_iterator::operator<(const iterator_impl_base &rhs) const
  {
    return vct < rhs.operator->();
  }

  bool vector_iterator::operator>(const iterator_impl_base &rhs) const
  {
    return vct > rhs.operator->();
  }

  bool vector_iterator::operator<=(const iterator_impl_base &rhs) const
  {
    return vct <= rhs.operator->();
  }

  bool vector_iterator::operator>=(const iterator_impl_base &rhs) const
  {
    return vct >= rhs.operator->();
  }

  difference_type vector_iterator::operator-(const iterator_impl_base &rhs) const
  {
    difference_type diff = this->vct - rhs.operator->();
    return diff;
  }

  pointer vector_iterator::operator->() const
  {
    return vct;
  }

  reference vector_iterator::operator*() const
  {
    return *vct;
  }

  reference vector_iterator::operator[](difference_type offset) const
  {
    return vct[offset];
  }


//===================================LIST========================================//

  list_iterator::list_iterator()
  {
    lst = nullptr;
  }

  iterator_impl_base &list_iterator::operator++()
  {
    lst = lst->next;
    return *this;
  }

  iterator_impl_base &list_iterator::operator--()
  {
    lst = lst->prev;
    return *this;
  }

  iterator_impl_base &list_iterator::operator+=(difference_type offset)
  {
    for(difference_type i=0; i<offset; i++)
      lst = lst->next;
    return *this;
  }

  iterator_impl_base &list_iterator::operator-=(difference_type offset)
  {
    for(difference_type i=0; i<offset; i++)
      lst = lst->prev;
    return *this;
  }

  bool list_iterator::operator==(const iterator_impl_base &rhs) const
  {
    return lst == rhs.node_ref();
  }

  bool list_iterator::operator!=(const iterator_impl_base &rhs) const
  {
    return lst != rhs.node_ref();
  }

  bool list_iterator::operator<(const iterator_impl_base &rhs) const
  {
    Node* it = lst;
    Node* ndp = rhs.node_ref();

    if(it == ndp)
      return false;

    while(it != nullptr)
    {
      if(it == ndp)
        return true;

      it = it->next;
    }

    return false;
  }

  bool list_iterator::operator>(const iterator_impl_base &rhs) const
  {
    Node* it = lst;
    Node* ndp = rhs.node_ref();

    if(it == ndp)
      return false;

    while(it != nullptr)
    {
      if(it == ndp)
        return true;

      it = it->prev;
    }

    return false;
  }

  bool list_iterator::operator<=(const iterator_impl_base &rhs) const
  {
    Node* it = lst;
    Node* ndp = rhs.node_ref();

    while(it != nullptr)
    {
      if(it == ndp)
        return true;

      it = it->next;
    }

    return false;
  }

  bool list_iterator::operator>=(const iterator_impl_base &rhs) const
  {
    Node* it = lst;
    Node* ndp = rhs.node_ref();

    while(it != nullptr)
    {
      if(it == ndp)
        return true;

      it = it->prev;
    }

    return false;
  }

  difference_type list_iterator::operator-(const iterator_impl_base &rhs) const
  {
    difference_type flag = 1;
    difference_type front = 0;
    difference_type back = 0;
    Node* mov_front = rhs.node_ref();
    Node* mov_back = rhs.node_ref();
    Node* targetNode = this->lst;

    if(flag != 0)
    {
      while(mov_front != nullptr)
      {
        if(mov_front == targetNode)
        {
          break;
        }

        mov_front = mov_front->next;
        front++;
      }
      return front;
    }
    
    while(mov_back != nullptr)
    {
      if(mov_back == targetNode)
      {
        flag = 0;
        break;
      }

      mov_back = mov_back->prev;
      back++;
    }

    return back;
  }

  pointer list_iterator::operator->() const
  {
    return &(lst->data);
  }

  reference list_iterator::operator*() const
  {
    return lst->data;
  }

  reference list_iterator::operator[](difference_type offset) const
  {
    Node* ptr = lst;

    if(offset < 0)
    {
      while(offset++)
        ptr = ptr->prev;
    }

    else
    {
      while(offset--)
        ptr = ptr->next;
    }

    return ptr->data;
  }

//=====================================CONST ITERATOR============================================//
  const_iterator::~const_iterator()
  {
    delete p_;
    p_ = nullptr;
  }

  const_iterator::const_iterator()
  {
      p_ = nullptr;
  }

  const_iterator::const_iterator(const const_iterator &rhs)
  {
    p_ = rhs.p_->clone();
  }

  const_iterator::const_iterator(iterator_impl_base *p)
  {
    p_ = p->clone();
  }

  const_iterator &const_iterator::operator=(const const_iterator &rhs)
  {
    p_ = rhs.p_->clone();

    return *this;
  }

  const_iterator &const_iterator::operator++()
  {
    p_->operator++();
    return *this;
  }

  const_iterator const_iterator::operator++(int)
  {
    const_iterator copy(*this);
    p_->operator++();
    return copy;
  }

  const_iterator &const_iterator::operator--()
  {
    p_->operator--();
    return *this;
  }

  const_iterator const_iterator::operator--(int)
  {
    const_iterator copy(*this);
    p_->operator--();
    return copy;
  }

  const_iterator &const_iterator::operator+=(difference_type offset)
  {
    p_->operator+=(offset);
  
    return *this;
  }

  const_iterator const_iterator::operator+(difference_type offset) const
  {
    const_iterator copy(*this);
    copy.p_->operator+=(offset);
    
    return copy;
  }

  const_iterator &const_iterator::operator-=(difference_type offset)
  {
    p_->operator-=(offset);
    
    return *this;
  }

  const_iterator const_iterator::operator-(difference_type offset) const
  {
    const_iterator copy(*this);
    copy.p_->operator-=(offset);
    
    return copy;
  }

  difference_type const_iterator::operator-(const const_iterator &rhs) const
  {
    return (p_->operator-(*rhs.p_));
  }

  const_iterator::pointer const_iterator::operator->() const
  {
    return p_->operator->();
  }

  const_iterator::reference const_iterator::operator*() const
  {
    return *(*p_);
  }

  const_iterator::reference const_iterator::operator[](difference_type offset) const
  {
    return p_->operator[](offset);
  }

  bool const_iterator::operator==(const const_iterator &rhs) const
  {
    return p_->operator==(*rhs.p_);
  }

  bool const_iterator::operator!=(const const_iterator &rhs) const
  {
    return p_->operator!=(*rhs.p_);
  }

  bool const_iterator::operator<(const const_iterator &rhs) const
  {
    return p_->operator<(*rhs.p_);
  }

  bool const_iterator::operator>(const const_iterator &rhs) const
  {
    return p_->operator>(*rhs.p_);
  }

  bool const_iterator::operator<=(const const_iterator &rhs) const
  {
    return p_->operator<=(*rhs.p_);
  }

  bool const_iterator::operator>=(const const_iterator &rhs) const
  {
    return p_->operator>=(*rhs.p_);
  }

//=====================================ITERATOR============================================//

  iterator::iterator()
  {
    p_ = nullptr;
  }

  iterator::iterator(iterator_impl_base *p)
  {
    p_ = p->clone();
  }

  iterator::iterator(const iterator &rhs)
  {
     p_ = rhs.p_->clone();
  }

  iterator &iterator::operator++()
  {
    p_->operator++();
    return *this;
  }

  iterator iterator::operator++(int)
  {
    iterator copy(*this);
    p_->operator++();
    return copy;
  }

  iterator &iterator::operator--()
  {
    p_->operator--();
    return *this;
  }

  iterator iterator::operator--(int)
  {
    iterator copy(*this);
    p_->operator--();
    return copy;
  }

  iterator &iterator::operator+=(difference_type offset)
  {
    p_->operator+=(offset);
  
    return *this;
  }

  iterator iterator::operator+(difference_type offset) const
  {
    iterator copy(*this);
    copy.p_->operator+=(offset);
    
    return copy;
  }

  iterator &iterator::operator-=(difference_type offset)
  {
    p_->operator-=(offset);
    
    return *this;
  }

  iterator iterator::operator-(difference_type offset) const
  {
    iterator copy(*this);
    copy.p_->operator-=(offset);
    
    return copy;
  }

  difference_type iterator::operator-(const iterator &rhs) const
  {
    return (p_->operator-(*rhs.p_));
  }

  pointer iterator::operator->() const
  {
    return p_->operator->();
  }

  reference iterator::operator*() const
  {
    return *(*p_);
  }

  reference iterator::operator[](difference_type offset) const
  {
    return p_->operator[](offset);
  }
}  // namespace I2P2

