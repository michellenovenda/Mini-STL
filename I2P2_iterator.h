#ifndef I2P2_ITERATOR_H
#define I2P2_ITERATOR_H
#include <iterator>
#include "I2P2_def.h"
#include<iostream>

namespace I2P2 {
  struct Node
  {
    Node* prev, *next;
    value_type data;
    Node(value_type d = 0) : prev(nullptr), next(nullptr), data(d) {}
  };

struct iterator_impl_base
{
  virtual reference operator*() const = 0;
  virtual reference operator[](difference_type offset) const = 0;
  virtual pointer operator->() const = 0;
  virtual difference_type operator-(const iterator_impl_base &rhs) const = 0;
  virtual iterator_impl_base &operator++() = 0; 
  virtual iterator_impl_base &operator--() = 0;
  virtual iterator_impl_base &operator+=(difference_type offset) = 0;
  virtual iterator_impl_base &operator-=(difference_type offset) = 0;
  virtual bool operator==(const iterator_impl_base &rhs) const = 0;
  virtual bool operator!=(const iterator_impl_base &rhs) const = 0;
  virtual bool operator<(const iterator_impl_base &rhs) const = 0;
  virtual bool operator>(const iterator_impl_base &rhs) const = 0;
  virtual bool operator<=(const iterator_impl_base &rhs) const = 0;
  virtual bool operator>=(const iterator_impl_base &rhs) const = 0;
  virtual iterator_impl_base* clone() const = 0;
  virtual Node* node_ref() const = 0;
};

class vector_iterator : public iterator_impl_base {
 protected:
  pointer vct;

 public:
  vector_iterator();
  vector_iterator(pointer ptr) : vct(ptr) {}
  iterator_impl_base &operator++();
  iterator_impl_base &operator--();
  iterator_impl_base &operator+=(difference_type offset);
  iterator_impl_base &operator-=(difference_type offset);
  bool operator==(const iterator_impl_base &rhs) const;
  bool operator!=(const iterator_impl_base &rhs) const;
  bool operator<(const iterator_impl_base &rhs) const;
  bool operator>(const iterator_impl_base &rhs) const;
  bool operator<=(const iterator_impl_base &rhs) const;
  bool operator>=(const iterator_impl_base &rhs) const;
  difference_type operator-(const iterator_impl_base &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
  iterator_impl_base* clone() const
  {
    return new vector_iterator(vct);
  }
  Node* node_ref() const 
  {
    return nullptr;
  };
};

class list_iterator : public iterator_impl_base {
 protected:
  Node* lst;

 public:
  list_iterator();
  list_iterator(Node* head) : lst(head) {}
  iterator_impl_base &operator++();
  iterator_impl_base &operator--();
  iterator_impl_base &operator+=(difference_type offset);
  iterator_impl_base &operator-=(difference_type offset);
  bool operator==(const iterator_impl_base &rhs) const;
  bool operator!=(const iterator_impl_base &rhs) const;
  bool operator<(const iterator_impl_base &rhs) const;
  bool operator>(const iterator_impl_base &rhs) const;
  bool operator<=(const iterator_impl_base &rhs) const;
  bool operator>=(const iterator_impl_base &rhs) const;
  difference_type operator-(const iterator_impl_base &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
  iterator_impl_base* clone() const
  {
    return new list_iterator(lst);
  }
  Node* node_ref() const
  {
    return lst;
  }
};

class const_iterator {
 public:
  using difference_type = I2P2::difference_type;
  using value_type = I2P2::value_type;
  using pointer = I2P2::const_pointer;
  using reference = I2P2::const_reference;
  using iterator_category = std::random_access_iterator_tag;

 protected:
  iterator_impl_base *p_;

 public:
  ~const_iterator(); 
  const_iterator(); 
  const_iterator(const const_iterator &rhs); 
  const_iterator(iterator_impl_base *p); 
  const_iterator &operator=(const const_iterator &rhs); 
  const_iterator &operator++(); 
  const_iterator operator++(int);
  const_iterator &operator--(); 
  const_iterator operator--(int);
  const_iterator &operator+=(difference_type offset); 
  const_iterator operator+(difference_type offset) const;
  const_iterator &operator-=(difference_type offset); 
  const_iterator operator-(difference_type offset) const;
  difference_type operator-(const const_iterator &rhs) const; 
  pointer operator->() const; 
  reference operator*() const; 
  reference operator[](difference_type offset) const; 
  bool operator==(const const_iterator &rhs) const; 
  bool operator!=(const const_iterator &rhs) const; 
  bool operator<(const const_iterator &rhs) const; 
  bool operator>(const const_iterator &rhs) const; 
  bool operator<=(const const_iterator &rhs) const; 
  bool operator>=(const const_iterator &rhs) const; 
  /* This class holds an iterator_impl_base
   * and you may want to have some ways to 
   * invoke a container-specialized method from here
   * for insert/erase methods (look at their parameters if you are not sure) */
  Node* node_ref() const 
  { 
    return p_->node_ref(); 
  }
};

class iterator : public const_iterator {
 public:
  using difference_type = I2P2::difference_type;
  using value_type = I2P2::value_type;
  using pointer = I2P2::pointer;
  using reference = I2P2::reference;
  using iterator_category = std::random_access_iterator_tag;

 public:
  iterator();
  iterator(iterator_impl_base *p);
  iterator(const iterator &rhs);
  iterator &operator++();
  iterator operator++(int);
  iterator &operator--();
  iterator operator--(int);
  iterator &operator+=(difference_type offset);
  iterator operator+(difference_type offset) const;
  iterator &operator-=(difference_type offset);
  iterator operator-(difference_type offset) const;
  difference_type operator-(const iterator &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
  Node* node_ref() const 
  { 
    return p_->node_ref(); 
  }
};
}  // namespace I2P2

#endif

