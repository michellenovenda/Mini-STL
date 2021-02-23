#include "../header/I2P2_List.h"
#include<iostream>

namespace I2P2 {
	List::~List()
	{
    clear();
    delete _head;
    delete _tail;
    _head = nullptr; 
    _tail = nullptr; 
	}

	List::List()
	{
		_head = new Node(0);
    _tail = new Node(0);
    _head->next = _tail;
    _tail->next = nullptr;
    _head->prev = nullptr;
    _tail->prev = _head;
    _size = 0;
	}

	List::List(const List &rhs)
  {
    _head = new Node(0);
    _tail = new Node(0);
    _head->next = _tail;
    _tail->next = nullptr;
    _head->prev = nullptr;
    _tail->prev = _head;
    _size = 0;

    Node* now = rhs._head->next;

    while(now != rhs._tail)
    {
      push_back(now->data);
      now = now->next;
    }
  }

	List &List::operator=(const List &rhs)
  {
    _head = new Node(0);
    _tail = new Node(0);
    _head->next = _tail;
    _tail->next = nullptr;
    _head->prev = nullptr;
    _tail->prev = _head;
    _size = 0;

    Node* now = rhs._head->next;

    while(now != rhs._tail)
    {
      push_back(now->data);
      now = now->next;
    }

    return *this;
  }

	iterator List::begin()
  {
    list_iterator head_ptr;

    if(_head->next == _tail)
      head_ptr = list_iterator(_tail);

    else if(_head->next != _tail)
      head_ptr = list_iterator(_head->next);

    iterator ret_head(&head_ptr);
    return ret_head;
  }

	const_iterator List::begin() const
  {
    list_iterator head_ptr;

    if(_head->next == _tail)
      head_ptr = list_iterator(_tail);

    else if(_head->next != _tail)
      head_ptr = list_iterator(_head->next);

    const_iterator ret_head(&head_ptr);
    return ret_head;
  }

	iterator List::end()
  {
    list_iterator tail_ptr = list_iterator(_tail);
    iterator ret_tail(&tail_ptr);
    return ret_tail;
  }

	const_iterator List::end() const
  {
    list_iterator tail_ptr = list_iterator(_tail);
    const_iterator ret_tail(&tail_ptr);
    return ret_tail;
  }

	reference List::front()
  {
    if(!empty())
      return _head->next->data;

    else
      return _head->data;
  }

	const_reference List::front() const
  {
    if(!empty())
      return _head->next->data;

    else
      return _head->data;
  }

	reference List::back()
  {
    if(!empty())
      return _tail->prev->data;

    else
      return _tail->data;
  }

	const_reference List::back() const
  {
    if(!empty())
      return _tail->prev->data;

    else
      return _tail->data;
  }

	size_type List::size() const
  {
    return _size;
  }
  
	void List::clear() 
  {
    if(!empty())
    {
      Node* curNode = _head->next;

      while (curNode != _tail)
      {
        Node* temp = curNode;
        curNode = curNode->next;
        delete temp;
      }
      
      _head->next = _tail;
      _tail->prev = _head;
      _size = 0;
    }
  }

	bool List::empty() const
  {
    return _size == 0;
  }

	void List::erase(const_iterator pos) 
  {
    if(!empty())
    {
      Node* curNode = pos.node_ref();

      curNode->next->prev = curNode->prev;
      curNode->prev->next = curNode->next;
      delete curNode;
      _size--;
    }
  }

	void List::erase(const_iterator begin, const_iterator end) 
  {
      Node* begin_ = begin.node_ref();
      Node* end_ = end.node_ref();
      Node* temp = begin_->prev;
      
      while (begin_ != end_)
      {
        Node* newnode = begin_;
        begin_ = begin_->next;
        delete newnode;
        _size--;
      }

      temp->next = end_;
      end_->prev = temp;
  }

	void List::insert(const_iterator pos, size_type count, const_reference val) 
  {
    if(count > 0)
    {
      Node* targetNode = pos.node_ref();

      Node* new_head = new Node(val);
      Node* new_tail = new_head;
      count -= 1;
      _size++;

      for(size_type i = 0; i < count; i++)
      {
        new_tail->next = new Node(val);
        new_tail->next->prev = new_tail;
        new_tail = new_tail->next;
        _size++;
      }
        
      targetNode->prev->next = new_head;
      new_head->prev = targetNode->prev;
      new_tail->next = targetNode;
      targetNode->prev = new_tail;
    }
  }

	void List::insert(const_iterator pos, const_iterator begin, const_iterator end)
  {
    if(begin != end)
    {
      Node* targetNode = pos.node_ref();
      Node* beginNode = begin.node_ref();
      Node* endNode = end.node_ref();

      Node* new_head = new Node(*begin);
      Node* new_tail = new_head;
      begin++;
      _size++;

      while(begin != end)
      {
        new_tail->next = new Node(*begin);
        new_tail->next->prev = new_tail;
        new_tail = new_tail->next;
        begin++;
        _size++;
      }

      targetNode->prev->next = new_head;
      new_head->prev = targetNode->prev;
      new_tail->next = targetNode;
      targetNode->prev = new_tail;
    }
  }

	void List::pop_back()
	{
		if (!empty())
		{
      Node* tail_ptr = _tail->prev;
			tail_ptr->prev->next = _tail;
			_tail->prev = tail_ptr->prev;
      delete tail_ptr;
      _size--;
		}
	}

	void List::pop_front()
	{
		if (!empty())
		{
      Node* head_ptr = _head->next;
			head_ptr->next->prev = _head;
			_head->next = head_ptr->next;
      delete head_ptr;
      _size--;
		}
	}

	void List::push_back(const_reference val)
	{
    Node* newnode = new Node(0);
    newnode->data = val;
    _tail->prev->next = newnode;
    newnode->prev = _tail->prev;
    newnode->next = _tail;
    _tail->prev = newnode;
    _size++;
	}

	void List::push_front(const_reference val)
	{
    Node* newnode = new Node(0);
    newnode->data = val;
    _head->next->prev = newnode;
    newnode->next = _head->next;
    newnode->prev = _head;
    _head->next = newnode;
    _size++;
	}
}  // namespace I2P2

