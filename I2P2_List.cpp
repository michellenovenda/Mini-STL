#include "../header/I2P2_List.h"
#include<iostream>

namespace I2P2 {
	List::~List()
	{
    std::cout << "List::~List()" << std::endl;
    clear();
    delete _head;
    _head = nullptr;
	}

	List::List()
	{
    std::cout << "List::List()" << std::endl;
		_head = new Node(0);
    _head->next = _head;
    _head->prev = _head;
    _size = 0;
	}

	List::List(const List &rhs)
  {
    std::cout << "List::List(const List &rhs)" << std::endl;
    if(_head != nullptr)
      clear();

    Node* head_ptr = _head;
    Node* now = rhs._head->next;

    while(now != rhs._head)
    {
      Node* newnode = new Node(now->data);

      if(now->next != rhs._head)
      {
        head_ptr->next = newnode;
        newnode->prev = head_ptr;
      }

      else
      {
        _head->prev = newnode;
        newnode->next = _head;
      }
      
      _size++;
      now = now->next;
    }
  }

	List &List::operator=(const List &rhs)
  {
    std::cout << "List &List::operator=(const List &rhs)" << std::endl;
    if(this == &rhs)
      return *this;

    if(_head != nullptr)
      clear();

    Node* head_ptr = _head;
    Node* now = rhs._head->next;

    while(now != rhs._head)
    {
      Node* newnode = new Node(now->data);

      if(now->next != rhs._head)
      {
        head_ptr->next = newnode;
        newnode->prev = head_ptr;
      }

      else
      {
        _head->prev = newnode;
        newnode->next = _head;
      }

      _size++;
      now = now->next;
    }

    return *this;
  }

	iterator List::begin()
  {
    std::cout << "iterator List::begin()" << std::endl;
    list_iterator head_ptr = list_iterator(_head->next);
    iterator head(&head_ptr);
    return head;
  }

	const_iterator List::begin() const
  {
    std::cout << "const_iterator List::begin() const" << std::endl;
    list_iterator head_ptr = list_iterator(_head->next);
    iterator head(&head_ptr);
    return head;
  }

	iterator List::end()
  {
    std::cout << "iterator List::end()" << std::endl;
    list_iterator tail_ptr = list_iterator(_head);
    iterator tail(&tail_ptr);
    return tail;
  }

	const_iterator List::end() const
  {
    std::cout << "const_iterator List::end() const" << std::endl;
    list_iterator tail_ptr = list_iterator(_head);
    iterator tail(&tail_ptr);
    return tail;
  }

	reference List::front()
  {
    std::cout << "reference List::front()" << std::endl;
    return _head->next->data;
  }

	const_reference List::front() const
  {
    std::cout << "const_reference List::front() const" << std::endl;
    return _head->next->data;
  }

	reference List::back()
  {
    std::cout << "reference List::back()" << std::endl;
    return _head->prev->data;
  }

	const_reference List::back() const
  {
    std::cout << "const_reference List::back() const" << std::endl;
    return _head->prev->data;
  }

	size_type List::size() const
  {
    std::cout << "size_type List::size() const" << std::endl;
    return _size;
  }
  
	void List::clear()
  {
    std::cout << "List::clear()" << std::endl;

    if(_size > 0)
    {
      Node* curNode = _head->next;

      while (curNode != _head)
      {
        Node* temp = curNode;
        curNode = curNode->next;
        delete temp;
      }
      
      _head->next = _head;
      _head->prev = _head;
      _size = 0;
    }
  }

	bool List::empty() const
  {
    std::cout << "List::empty() const" << std::endl;
    return _size == 0;
  }

	void List::erase(const_iterator pos)
  {
    std::cout << "List::erase(const_iterator pos)" << std::endl;
    Node* curNode = pos.node_ref();
    curNode->next->prev = curNode->prev;
    curNode->prev->next = curNode->next;
    delete curNode;
    curNode = nullptr;
    _size--;
  }

	void List::erase(const_iterator begin, const_iterator end)
  {
    std::cout << "List::erase(const_iterator begin, const_iterator end)" << std::endl;
    Node* curNode = begin.node_ref();
    Node* end_ = end.node_ref();
    
    while (curNode != end_)
    {
      curNode->next->prev = curNode->prev;
      curNode->prev->next = curNode->next;
      Node* temp = curNode;
      curNode = curNode->next;
      delete temp;
      temp = nullptr;
      _size--;
    }
  }

	void List::insert(const_iterator pos, size_type count, const_reference val)
  {
    std::cout << "List::insert(const_iterator pos, size_type count, const_reference val)" << std::endl;
    Node* targetNode = pos.node_ref();
    
    for (int i = 0; i < count; i++)
    {
      Node* newNode = new Node(val);
      newNode->prev = targetNode->prev;
      targetNode->prev->next = newNode;
      newNode->next = targetNode;
      targetNode->prev = newNode;
    }
    _size += count;
  }

	void List::insert(const_iterator pos, const_iterator begin, const_iterator end) //???
  {
    std::cout << "List::insert(const_iterator pos, const_iterator begin, const_iterator end)" << std::endl;
    Node* targetNode = pos.node_ref();
    Node* beginNode = begin.node_ref();
    Node* endNode = end.node_ref();
    
    for (Node* i = beginNode; i < endNode; i++)
    {
      Node* newNode = new Node(_head->data);
      newNode->prev = targetNode->prev;
      targetNode->prev->next = newNode;
      newNode->next = targetNode;
      targetNode->prev = newNode;
    }
    _size += (endNode - beginNode);
  }

	void List::pop_back()
	{
    std::cout << "List::pop_back()" << std::endl;
		if (_head == nullptr)
			return;

		else if (_head->next == _head)
		{
			delete _head;
			_head = nullptr;
		}

		else
		{
			Node* tail = _head->prev;
			tail->prev->next = tail->next;
			tail->next->prev = tail->prev;
      clear();
		}
	}

	void List::pop_front()
	{
    std::cout << "List::pop_front()" << std::endl;
		if (_head == nullptr)
			return;

		else if (_head->next == _head)
		{
			delete _head;
			_head = nullptr;
		}

		else
		{
			Node* head = _head->next;
			head->prev->next = head->next;
			head->next->prev = head->prev;
			clear();
		}
	}

	void List::push_back(const_reference val)
	{
    std::cout << "List::push_back(const_reference val)" << std::endl;
		Node* newnode = new Node(val);

		Node*tail = _head->prev;
		newnode->next = tail->next;
		tail->next->prev = newnode;
		tail->next = newnode;
		newnode->prev = tail;
    _size++;
	}

	void List::push_front(const_reference val)
	{
    std::cout << "List::push_front(const_reference val)" << std::endl;
		Node* newnode = new Node(val);

		Node*tail = _head->next;
    tail->prev->next = newnode;
		newnode->prev = tail->prev;
		newnode->next = tail;
		tail->prev = newnode;
    _size++;
	}
}  // namespace I2P2