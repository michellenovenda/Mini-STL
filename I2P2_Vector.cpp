#include "../header/I2P2_Vector.h"
#include<iostream>

namespace I2P2 {
  Vector::~Vector()
  {
    std::cout << "Vector::~Vector()" << std::endl;
    if(begin_ != nullptr)
      delete[] begin_;

    begin_ = nullptr;
  }

  Vector::Vector()
  {
    std::cout << "Vector::Vector()" << std::endl;
    begin_ = nullptr;
    end_ = nullptr;
    last_ = nullptr;
  }

  Vector::Vector(const Vector &rhs) //???
  {
    std::cout << "Vector::Vector(const Vector &rhs)" << std::endl;
    begin_ = nullptr;
    end_ = nullptr;
    last_ = nullptr;

    reserve(rhs.size());

    for(size_type i=0; i<rhs.size(); i++)
      begin_[i] = rhs[i];
  }

  Vector &Vector::operator=(const Vector &rhs) //???
  {
    std::cout << "Vector &Vector::operator=(const Vector &rhs)" << std::endl;
    if(this == &rhs)
      return *this;

    last_ = begin_;
    reserve(rhs.size());
    
    for(size_type i=0; i<rhs.size(); i++)
      begin_[i] = rhs[i];

    return *this;
  }

  iterator Vector::begin()
  {
    std::cout << "iterator Vector::begin()" << std::endl;
    vector_iterator begin_ptr = vector_iterator(begin_);
    iterator begin_(&begin_ptr);
    return begin_;
  }

  const_iterator Vector::begin() const
  {
    std::cout << "const_iterator Vector::begin() const" << std::endl;
    vector_iterator begin_ptr = vector_iterator(begin_);
    iterator begin_(&begin_ptr);
    return begin_;
  }

  iterator Vector::end()
  {
    std::cout << "iterator Vector::end()" << std::endl;
    vector_iterator last_ptr = vector_iterator(last_);
    iterator last_(&last_ptr);
    return last_;
  }

  const_iterator Vector::end() const
  {
    std::cout << "const_iterator Vector::end() const" << std::endl;
    vector_iterator last_ptr = vector_iterator(last_);
    iterator last_(&last_ptr);
    return last_;
  }

  reference Vector::front()
  {
    std::cout << "reference Vector::front()" << std::endl;
    reference begin_val = *begin_;
    return begin_val;
  }

  const_reference Vector::front() const
  {
    std::cout << "const_reference Vector::front() const" << std::endl;
    reference begin_val = *begin_;
    return begin_val;
  }

  reference Vector::back()
  {
    std::cout << "reference Vector::back()" << std::endl;
    reference last_val = *last_;
    return last_val;
  }

  const_reference Vector::back() const
  {
    std::cout << "const_reference Vector::back() const" << std::endl;
    reference last_data = *last_;
    return last_data;
  }
  
  reference Vector::operator[](size_type pos) //the type harus di declare ga???
  {
    std::cout << "reference Vector::operator[](size_type pos)" << std::endl;
    return begin_[pos];
  }

  const_reference Vector::operator[](size_type pos) const //the type harus di declare ga???
  {
    std::cout << "const_reference Vector::operator[](size_type pos) const" << std::endl;
    return begin_[pos];
  }

  size_type Vector::capacity() const
  {
    std::cout << "size_type Vector::capacity() const" << std::endl;
    return end_-begin_;
  }

  size_type Vector::size() const
  {
    std::cout << "size_type Vector::size() const" << std::endl;
    return last_-begin_;
  }

  void Vector::clear()
  {
    std::cout << "void Vector::clear()" << std::endl;
    size_type old_size = size();

    for(size_type i=0; i<old_size; i++)
    {
      begin_[i].~value_type();
      last_--;
    }
  }

  bool Vector::empty() const
  {
    std::cout << "bool Vector::empty() const" << std::endl;
    return begin_ == nullptr;
  }

  void Vector::erase(const_iterator pos)
  {
    std::cout << "Vector::erase(const_iterator pos)" << std::endl;
    size_type pst = pos - this->begin();

    if(pst >= 0 && pst < size())
    {
      for(size_type i=pst; i<size()-1; i++)
        begin_[i] = begin_[i+1];

      last_--;
    }
  }

  void Vector::erase(const_iterator begin, const_iterator end)
  {
    std::cout << "Vector::erase(const_iterator begin, const_iterator end)" << std::endl;
    size_type beg_pos = begin - this->begin();
    size_type end_pos = end - this->begin();

		for (size_type i = beg_pos; i <= end_pos; i++)
    {
			begin_[i].~value_type();
			new (begin_ + i) value_type(begin_[i + 1]);
		}
		begin_[size() - 1].~value_type();
		last_--;
	}

  void Vector::insert(const_iterator pos, size_type count, const_reference val)
  {
    std::cout << "Vector::insert(const_iterator pos, size_type count, const_reference val)" << std::endl;
    size_type old_capacity = capacity();
		size_type old_size = size();
    size_type pst = pos - this->begin();

		if (old_size + count > old_capacity)
    {
			if (old_capacity + old_capacity / 2 > old_capacity + count)
				reserve(old_capacity + old_capacity / 2);

			else
        reserve(old_capacity + count);
		}

		size_type new_size = count + old_size;

    for(size_type i=old_size; i<new_size; i++)
      push_back(0);

		for (size_type i = pst + count; i < size(); i++)
			begin_[i] = begin_[i - count];

		for (size_type i = pst; i < count + pst; i++)
			begin_[i] = val;
  }

  void Vector::insert(const_iterator pos, const_iterator begin, const_iterator end)
  {
    std::cout << "Vector::insert(const_iterator pos, const_iterator begin, const_iterator end)" << std::endl;
    size_type old_capacity = capacity();
		size_type old_size = size();
    size_type beg_pos = begin - this->begin();
    size_type end_pos = end - this->begin();
    size_type diff_pos = end_pos - beg_pos;

		if (old_size + diff_pos > old_capacity)
    {
			if (old_capacity + old_capacity / 2 > old_capacity + diff_pos)
				reserve(old_capacity + old_capacity / 2);

			else
        reserve(old_capacity + diff_pos);
		}

    int n=0;
    while(n < diff_pos)
      push_back(0);

    for (size_type i = beg_pos; i < size(); i++)
			begin_[i] = begin_[i + diff_pos];

		for (size_type i = beg_pos; i < end_pos; i++)
    {
      for(size_type j=size(); j>size()-diff_pos; j--)
        begin_[i] = begin_[j];
    }
  }

  void Vector::pop_back()
  {
    std::cout << "Vector::pop_back()" << std::endl;
    if(size() > 0)
      last_--;
  }

  void Vector::pop_front()
  {
    std::cout << "Vector::pop_front()" << std::endl;
    if(size() > 0)
      begin_++;
  }

  void Vector::push_back(const_reference val)
  {
    std::cout << "Vector::push_back(const_reference val)" << std::endl;
    size_type old_capacity = capacity();

		if (size() == old_capacity)
    {
			if (old_capacity + 1 > old_capacity * 3)
				reserve(old_capacity + 1);

			else
        reserve(old_capacity * 3);

			push_back(val);
		}

		else
    {
			(*last_) = val;
			last_++;
		}
  }

  void Vector::push_front(const_reference val)
  {
    std::cout << "Vector::push_front(const_reference val)" << std::endl;
    size_type old_capacity = capacity();
    size_type old_size = size();

		if (size() == old_capacity)
    {
			if (old_capacity + 1 > old_capacity * 3)
				reserve(old_capacity + 1);

			else
        reserve(old_capacity * 3);

			push_front(val);
		}

		else
    {
			for(size_type i=old_size; i>0; i--)
        begin_[i] = begin_[i-1];

      *begin_ = val;
		}
  }

  void Vector::reserve(size_type new_capacity)
  {
    std::cout << "Vector::reserve(size_type new_capacity)" << std::endl;
    size_type old_capacity = capacity();
    size_type old_size = size();

    if(old_capacity < new_capacity)
    {
      pointer new_begin_ = new value_type[new_capacity];

      for(size_type i=0; i<old_size; i++)
        new_begin_[i] = begin_[i];

      if(begin_ != nullptr)
        delete[] begin_;

      begin_ = new_begin_;
      last_ = begin_ + old_size;
      end_ = begin_ + new_capacity;
    }
  }

  void Vector::shrink_to_fit()
  {
    std::cout << "Vector::shrink_to_fit()" << std::endl;
    size_type old_size = size();
    size_type old_capacity = capacity();

    if(old_size < old_capacity)
    {
      for(size_type i=old_capacity; i>old_size; i++)
        end_[i].~value_type();

      size_type shrink = old_capacity-old_size;
      end_ -= shrink;
    }
  }
}  // namespace I2P2








