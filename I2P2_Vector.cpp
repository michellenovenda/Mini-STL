#include "../header/I2P2_Vector.h"
#include<iostream>

namespace I2P2 {
  Vector::~Vector()
  {
    for (size_type i = 0; i < size();i++)
        begin_[i].~value_type();

    if(begin_ != nullptr)
      operator delete[](begin_);
  }

  Vector::Vector()
  {
    begin_ = nullptr;
    end_ = nullptr;
    last_ = nullptr;
  }

  Vector::Vector(const Vector &rhs)
  {
    begin_ = nullptr;
    end_ = nullptr;
    last_ = nullptr;

    reserve(rhs.size());

    for(size_type i=0; i<rhs.size(); i++)
      insert(this->begin()+i, 1, rhs[i]);
  }

  Vector &Vector::operator=(const Vector &rhs)
  {
    if(this == &rhs)
      return *this;

    for(size_type i=0; i<size(); i++)
      begin_[i].~value_type();

    last_ = begin_;
    reserve(rhs.size());
    
    for(size_type i=0; i<rhs.size(); i++)
      insert(this->begin()+i, 1, rhs[i]);

    return *this;
  }

  iterator Vector::begin()
  {
    vector_iterator begin_ptr = vector_iterator(begin_);
    iterator begin_(&begin_ptr);
    return begin_;
  }

  const_iterator Vector::begin() const
  {
    vector_iterator begin_ptr = vector_iterator(begin_);
    const_iterator begin_(&begin_ptr);
    return begin_;
  }

  iterator Vector::end()
  {
    vector_iterator last_ptr = vector_iterator(last_);
    iterator last_(&last_ptr);
    return last_;
  }

  const_iterator Vector::end() const
  {
    vector_iterator last_ptr = vector_iterator(last_);
    const_iterator last_(&last_ptr);
    return last_;
  }

  reference Vector::front()
  {
    return *begin_;
  }

  const_reference Vector::front() const
  {
    return *begin_;
  }

  reference Vector::back()
  {
    size_type last_element = size()-1;
    return begin_[last_element];
  }

  const_reference Vector::back() const
  {
    size_type last_element = size()-1;
    return begin_[last_element];
  }
  
  reference Vector::operator[](size_type pos)
  {
    return begin_[pos];
  }

  const_reference Vector::operator[](size_type pos) const
  {
    return begin_[pos];
  }

  size_type Vector::capacity() const
  {
    return end_-begin_;
  }

  size_type Vector::size() const
  {
    return last_-begin_;
  }

  void Vector::clear()
  {
    size_type old_size = size();

    for(size_type i=0; i<old_size; i++)
    {
      begin_[i].~value_type();
      last_--;
    }
  }

  bool Vector::empty() const
  {
    return last_ == begin_;
  }

  void Vector::erase(const_iterator pos)
  {
    if(pos != end())
    {
      size_type pst = pos - this->begin();

      if(pst >= 0 && pst < size())
      {
        for(size_type i=pst; i<size()-1; i++)
        {
          begin_[i] = begin_[i+1];
        }
        
        begin_[size()-1].~value_type();
        last_--;
      }
    }
  }

  void Vector::erase(const_iterator begin, const_iterator end)
  {
    if(begin != end)
    {
      size_type beg_pos = begin - this->begin();
      size_type end_pos = end - this->begin();
      size_type diff_pos = end_pos - beg_pos;
      size_type vec_size = size();
      size_type i;

      if(begin == this->begin() && end == this->end())
        clear();

      else if(beg_pos >= 0)
      {
        for (i = beg_pos; i < vec_size-diff_pos; i++)
        {
            begin_[i] = begin_[i+diff_pos];
        }

        for(i = vec_size-1; i>=vec_size-diff_pos; i--)
        {
          begin_[i].~value_type();
          last_--;
        }
      }
    }
	}

  void Vector::insert(const_iterator pos, size_type count, const_reference val)
  {
    if(count <= 0)
      return;

    size_type old_capacity = capacity();
		size_type old_size = size();
    size_type pst = pos - this->begin();

    if(pst > old_size)
      return;

		if (old_size + count > old_capacity)
    {
			if (old_capacity + old_capacity / 2 > old_capacity + count)
				reserve(old_capacity + old_capacity / 2);

			else
        reserve(old_capacity + count);
		}

    last_ += count;

      for (size_type i = 0; i < count; i++)
        new(begin_ + size()-1) value_type(0);

      for(size_type i=(size()-1); i>=pst+count; i--)
        begin_[i] = begin_[i-count];

      for (size_type i = 0; i < count; i++)
        begin_[pst+i] = val;
  }

  void Vector::insert(const_iterator pos, const_iterator begin, const_iterator end)
  {
    if(begin != end)
    {
      size_type old_capacity = capacity();
      size_type old_size = size();
      size_type diff_pos = end - begin;
      size_type pst = pos - this->begin();
      pointer store = new value_type[diff_pos+1];

      if (old_size + diff_pos > old_capacity)
      {
        if (old_capacity + old_capacity / 2 > old_capacity + diff_pos)
          reserve(old_capacity + old_capacity / 2);

        else
          reserve(old_capacity + diff_pos);
      }

      last_ += diff_pos;

      size_type idx = 0;
      while(begin != end)
      {
        store[idx++] = *begin;
        begin++;
      }

      for(size_type i=0; i<diff_pos; i++)
        new(begin_ + i + old_size) value_type(0);

      for(size_type i=size()-1; i>=pst + diff_pos ; i--)
        begin_[i] = begin_[i-diff_pos];

      for(size_type i=0; i<diff_pos; i++)
        begin_[pst+i] = store[i];

      delete[] store;
    }
  }

  void Vector::pop_back()
  {
    erase(begin() + size() - 1);
  }

  void Vector::pop_front()
  {
    erase(begin());
  }

  void Vector::push_back(const_reference val)
  {
    insert(end(), 1, val);
  }

  void Vector::push_front(const_reference val)
  {
    insert(begin(), 1, val);
  }

  void Vector::reserve(size_type new_capacity)
  {
    size_type old_capacity = capacity();
    size_type old_size = size();

    if(old_capacity < new_capacity)
    {
      pointer new_begin_(static_cast<pointer>(operator new[](new_capacity * sizeof(value_type))));

      for(size_type i=0; i<old_size; i++)
      {
        new(new_begin_ + i) value_type(begin_[i]);
        begin_[i].~value_type();
      }

      if(begin_ != nullptr)
        operator delete[](begin_);

      begin_ = new_begin_;
      last_ = begin_ + old_size;
      end_ = begin_ + new_capacity;
    }
  }

  void Vector::shrink_to_fit()
  {
    size_type old_size = size();
    size_type old_capacity = capacity();

    if(old_capacity > old_size)
    {
      pointer new_begin_(static_cast<pointer>(operator new[](old_size * sizeof(value_type))));

      for(size_type i=0; i<old_size; i++)
      {
        new(new_begin_ + i) value_type(begin_[i]);
        begin_[i].~value_type();
      }

      if(begin_ != nullptr)
        operator delete[](begin_);

      begin_ = new_begin_;
      last_ = begin_ + old_size;
      end_ = begin_ + old_size;
    }
  }
}  // namespace I2P2
