#ifndef CONTAINER_H
#define CONTAINER_H

/**
* Template Container implemented as a doubly linked list
*/

template <class T>
class Container
{
  friend class Iterator;      // per accedere al costruttore privato
  friend class Const_iterator; // per accedere al costruttore privato

private:
  class Node
  {
  public:
    T info;
    Node* prev;
    Node* next;
    Node(const T& = T(), Node* = nullptr, Node* = nullptr);
    ~Node();
    Node(const Node&) = default;
    Node& operator = (const Node&) = default;
  };

  Node* first;
  Node* last;
  unsigned int size;

  static Node* copy(const Node*, Node*&);
  static bool isListEqual(const Node* n1, const Node *n2);

public:
  class Iterator;
  class Const_iterator;

  Container();
  ~Container();
  Container(const Container&);
  Container& operator = (const Container&);
  /**
   * @brief operator < : every element of the implicit Container must be strictly
   *                      lower than every element of the explicit Container
   */
  bool operator < (const Container&) const;
  bool operator == (const Container&) const;
  bool operator != (const Container&) const;

  /**
   * @brief Test whether Container is empty
   * Returns a bool value indicating whether the Container is
   * empty, i.e. whether its size is 0.
   * This function does not modify the content of the Container in any way.
   * To clear the content of an Container object, see Container::clear.
   *
   * @return true if the Container size is 0, false otherwise.
   */
  bool empty() const;
  /**
   * @brief Clear content
   * Removes all elements from the Container (which are destroyed),
   * and leaving the Container with a size of 0.
   */
  void clear();
  /**
   * @brief Insert element at beginning
   * Inserts a new element at the beginning of the Container, right before
   * its current first element. The content of val is copied to the
   * inserted element.
   */
  void push_front(const T&);
  /**
   * @brief Insert element at ending
   * Inserts a new element at the ending of the Container, right after its
   * current last element. The content of the parameter is copied to the
   * inserted element.
   */
  void push_back(const T&);
  /**
   * @brief Delete first element
   * Removes the first element in the Container, effectively
   * reducing its size by one.
   * This destroys the removed element.
   */
  void pop_front();
  /**
   * @brief The container is extended by inserting a new element after the
   * element at the given position.
   */
  Iterator insert_after(Iterator, const T&);
  /**
   * @brief Removes from the Container a single element (the one at the
   * given position)
   */
  Iterator erase(Iterator);
  /**
   * @brief Remove elements with specific value
   * Removes from the Container all the elements that compare equal to val.
   * This calls the destructor of these objects and reduces the Container size
   * by the number of elements removed.
   */
  void remove (const T&);

  /**
   * @brief searches for a match of the given parameter in the container,
   * if a match is found the Iterator to the first element found is returned.
   * @return The Iterator pointing to the first match.
   */
  Iterator search_for(const T&) const;

  int getSize() const;


  /////////////////////////////////////////////////////////////////////////////
  ///// ITERATORS
  /////////////////////////////////////////////////////////////////////////////

  class Iterator
  {
    friend class Container<T>;

  private:
    Node* pt;
    bool pte; // true if past-the-end

    Iterator(Node*, bool = false);
  public:
    Iterator();
    ~Iterator() = default;
    Iterator& operator + (unsigned int i);
    Iterator& operator - (unsigned int i);
    Iterator& operator ++ ();
    Iterator operator ++ (int);
    Iterator& operator -- ();
    Iterator operator -- (int);
    T& operator * () const;
    T* operator -> () const;
    bool operator == (const Iterator&) const;
    bool operator != (const Iterator&) const;
    operator Const_iterator() const;
  };
  // without const they cannot be called on const objects:
  Iterator begin();
  Iterator end();

  class Const_iterator
  {
    friend class Container<T>;

  private:
    const Node* pt;
    bool pte; // true if past-the-end

    Const_iterator(Node*, bool = false);
  public:
    Const_iterator();
    ~Const_iterator() = default;
    Const_iterator& operator + (unsigned int i);
    Const_iterator& operator - (unsigned int i);
    Const_iterator& operator ++ ();
    Const_iterator operator ++ (int);
    Const_iterator& operator -- ();
    Const_iterator operator -- (int);
    const T& operator * () const;
    const T* operator -> () const;
    bool operator == (const Const_iterator&) const;
    bool operator != (const Const_iterator&) const;
  };
  Const_iterator begin() const;
  Const_iterator end() const;

};

/////////////////////////////////////////////////////////////////////////////
///// NODE METHODS
/////////////////////////////////////////////////////////////////////////////
template <class T>
Container<T>::Node::Node(const T& i, Node* p, Node* n) : info(i), prev(p), next(n) {}

template <class T>
Container<T>::Node::~Node()
{
  if ( next )
    delete next;
}

/////////////////////////////////////////////////////////////////////////////
///// ITERATOR METHODS
/////////////////////////////////////////////////////////////////////////////
template <class T>
Container<T>::Iterator::Iterator() : pt(nullptr), pte(false) {}

template <class T>
Container<T>::Iterator::Iterator(Node* p, bool b) : pt(p), pte(b) {}

template <class T>
typename Container<T>::Iterator& Container<T>::Iterator::operator + (unsigned int i)
{
  while ( i )
 {
    operator++(1);
    --i;
  }
  return *this;
}

template <class T>
typename Container<T>::Iterator& Container<T>::Iterator::operator - (unsigned int i)
{
  while ( i )
  {
    operator--(1);
    --i;
  }
  return *this;
}

template<class T>
typename Container<T>::Iterator& Container<T>::Iterator::operator ++()
{
  if ( !pte && pt )
  {
    // not past-the-end
    if ( pt->next == nullptr )
    {
      // currently at last element
      pt = pt + 1;
      pte = true; // now past-the-end
    }
    else
    {
      pt = pt->next;
    }
  }
  return *this;
}

template <class T>
typename Container<T>::Iterator Container<T>::Iterator::operator ++ (int)
{
  Iterator aux = *this; // make a copy of current iterator

  if ( !pte && pt )
  {
    // not past-the-end
    if ( pt->next == nullptr )
    {
      // currently at last element
      pt = pt + 1;
      pte = true; // now past-the-end
    }
    else
    {
      pt = pt->next;
    }
  }
  return aux; // return previous state
}

template <class T>
typename Container<T>::Iterator& Container<T>::Iterator::operator -- ()
{
  if (pte)
  {
    pt = pt - 1;
    pte = false;
  }
  else if ( pt )
  {
    pt = pt->prev;
  }

  return *this;
}

template <class T>
typename Container<T>::Iterator Container<T>::Iterator::operator -- (int)
{
  Iterator aux = *this;

  if (pte)
  {
    pt = pt - 1;
    pte = false;
  }
  else if ( pt )
  {
    pt = pt->prev;
  }

  return aux;
}

template <class T>
T& Container<T>::Iterator::operator * () const
{
  return pt->info;
}

template <class T>
T* Container<T>::Iterator::operator -> () const
{
  return &(pt->info);
}

template <class T>
bool Container<T>::Iterator::operator == (const Iterator& x) const
{
  return pt == x.pt;
}

template <class T>
bool Container<T>::Iterator::operator != (const Iterator& x) const
{
  return pt != x.pt;
}

template <class T>
Container<T>::Iterator::operator Const_iterator() const
{
  return Const_iterator(pt, pte);
}

/////////////////////////////////////////////////////////////////////////////
///// CONSTITERATOR METHODS
/////////////////////////////////////////////////////////////////////////////
template <class T>
Container<T>::Const_iterator::Const_iterator() : pt(nullptr), pte(false) {}

template <class T>
Container<T>::Const_iterator::Const_iterator(Node* p, bool b) : pt(p), pte(b) {}

template <class T>
typename Container<T>::Const_iterator& Container<T>::Const_iterator::operator + (unsigned int i)
{
  while ( i )
  {
    operator++(1);
    --i;
  }
  return *this;
}

template <class T>
typename Container<T>::Const_iterator& Container<T>::Const_iterator::operator - (unsigned int i)
{
  while ( i )
  {
    operator--(1);
    --i;
  }
  return *this;
}

template<class T>
typename Container<T>::Const_iterator& Container<T>::Const_iterator::operator ++()
{
  if ( !pte && pt )
  {
    // not past-the-end
    if ( pt->next == nullptr )
    {
      // currently at last element
      pt = pt + 1;
      pte = true; // now past-the-end
    }
    else
    {
      pt = pt->next;
    }
  }
  return *this;
}

template <class T>
typename Container<T>::Const_iterator Container<T>::Const_iterator::operator ++ (int)
{
  Const_iterator aux = *this; // make a copy of current iterator

  if ( !pte && pt )
  {
    // not past-the-end
    if ( pt->next == nullptr )
    {
      // currently at last element
      pt = pt + 1;
      pte = true; // now past-the-end
    }
    else
    {
      pt = pt->next;
    }
  }
  return aux; // return previous state
}

template <class T>
typename Container<T>::Const_iterator& Container<T>::Const_iterator::operator -- ()
{
  if (pte)
  {
    pt = pt - 1;
    pte = false;
  }
  else if ( pt )
  {
    pt = pt->prev;
  }

  return *this;
}

template <class T>
typename Container<T>::Const_iterator Container<T>::Const_iterator::operator -- (int)
{
  Const_iterator aux = *this;

  if (pte)
  {
    pt = pt - 1;
    pte = false;
  }
  else if ( pt )
  {
    pt = pt->prev;
  }

  return aux;
}

template <class T>
const T& Container<T>::Const_iterator::operator * () const
{
  return pt->info;
}

template <class T>
const T* Container<T>::Const_iterator::operator -> () const
{
  return &(pt->info);
}

template <class T>
bool Container<T>::Const_iterator::operator == (const Const_iterator& x) const
{
  return pt == x.pt;
}

template <class T>
bool Container<T>::Const_iterator::operator != (const Const_iterator& x) const
{
  return pt != x.pt;
}

/////////////////////////////////////////////////////////////////////////////
///// CONTAINER METHODS
/////////////////////////////////////////////////////////////////////////////
/**
* default constructor that creates an empty list
*/
template <class T>
Container<T>::Container() : first(nullptr), last(nullptr), size(0) { }

template <class T>
Container<T>::~Container()
{
  if ( first )
    delete first;
}

template <class T>
Container<T>::Container(const Container& c)
{
  first = copy(c.first, last);
  size = c.size;
}

template <class T>
Container<T>& Container<T>::operator = (const Container& c)
{
  if ( this != &c )
  {
    if ( first )
      delete first;

    first = copy(c.first, last);
    size = c.size;
  }
  return *this;
}

template <class T>
bool Container<T>::operator < (const Container& c) const
{
  for ( Const_iterator i = begin(); i != end(); i++ )
  {
    for ( Const_iterator j = c.begin(); j != c.end(); j++ )
    {
      if ( *i >= *j )
        return false;
    }
  }
  return true;
}

template <class T>
bool Container<T>::operator == (const Container& c) const
{
  return isListEqual(first, c.first);
}

template <class T>
bool Container<T>::operator != (const Container& c) const
{
  return !(isListEqual(first, c.first));
}

template <class T>
typename Container<T>::Iterator Container<T>::begin()
{
  return Iterator(first);
}

template <class T>
typename Container<T>::Iterator Container<T>::end()
{
  if ( first == nullptr )
    return Iterator();

  // else create past-the-end iterator
  return Iterator(last +1, true);
}

template <class T>
typename Container<T>::Const_iterator Container<T>::begin() const
{
  return Const_iterator(first);
}

template <class T>
typename Container<T>::Const_iterator Container<T>::end() const
{
  if ( first == nullptr )
    return Const_iterator();

  // else create past-the-end iterator
  return Const_iterator(last +1, true);
}

template <class T>
bool Container<T>::empty() const
{
  return ( first == nullptr );
}

template <class T>
void Container<T>::clear()
{
  if ( first )
    delete first;

  first = last = nullptr;
  size = 0;
}

template <class T>
void Container<T>::push_front(const T& i)
{
  ++size;
  if (!first)
  {
    // the list was empty
    first = last = new Node(i);
  }
  else
  {
    first->prev = new Node(i,nullptr,first);
    first = first->prev;
  }
}

template <class T>
void Container<T>::push_back(const T& i)
{
  ++size;
  if ( !last )
  {
    // the list was empty
    first = last = new Node(i);
  }
  else
  {
    last->next = new Node(i,last);
    last = last->next;
  }
}

template <class T>
void Container<T>::pop_front()
{
  --size;
  Node* aux = first;
  if ( first != last )
  {
    first = first->next;
    first->prev = nullptr;
  }
  else
  {
    first = last = nullptr; // empty list
  }
  aux->next = nullptr;
  delete aux;
}

template<class T>
typename Container<T>::Iterator Container<T>::insert_after(Iterator pos, const T & t)
{
  ++size;
  Node* aux = new Node(t, pos.pt, pos.pt->next);

  if ( pos.pt == last )
  {
    last = aux;
  }
  else
  {
    pos.pt->next->prev = aux;
  }

  pos.pt->next = aux;

  return Iterator(aux);
}

template<class T>
typename Container<T>::Iterator Container<T>::erase(Iterator pos)
{
  --size;
  Iterator aux;

  if (pos.pt == last && pos.pt == first)
  {
    // only one element left in list
    aux = end();
    first = last = nullptr;
  }
  else if ( pos.pt == last )
  {
    // deleting last element (but not the only one in list)
    aux = end();
    pos.pt->prev->next = nullptr;
    last = pos.pt->prev;
  }
  else if ( pos.pt == first )
  {
    // deleting first element (but not the only one in list)
    first = pos.pt->next;
    first->prev = nullptr;
    aux = Iterator(first);
  }
  else
  {
    // deleting in the middle of the list
    aux = Iterator(pos.pt->next);
    pos.pt->prev->next = pos.pt->next;
    pos.pt->next->prev = pos.pt->prev;
  }
  pos.pt->next = nullptr;
  delete pos.pt;

  return aux;
}

template <class T>
void Container<T>::remove (const T& i)
{
  Node* aux = first;
  Node* markForDel = 0;

  /*
   * last node is a special case because there's the need to
   * update the pointer to it, if it's deleted. First needs to be checked
   * every time because it's updated during the while cycle.
   */

  while ( aux != last )
  {
    if ( aux->info == i )
    {
      // remove  this element
      markForDel = aux;
      if ( aux == first )
      {
        first = aux->next;
        aux->next->prev = nullptr;
      }
      else
      {
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
      }
      aux = aux->next;
      markForDel->next = nullptr;
      delete markForDel;
      --size;
    }
    else
    {
      aux = aux->next;
    }
  }

  // aux now is last element, check if we need to delete it
  if ( aux->info == i )
  {
    aux->prev->next = nullptr;
    last = aux->prev;

    // remove last element
    delete aux;
    --size;
  }
}

template <class T>
typename Container<T>::Iterator Container<T>::search_for(const T& t) const
{
  for (Container<T>::Iterator it = begin(); it != end(); ++it)
  {
    if ( *it == t )
      return it;
  }
  return nullptr;
}

template <class T>
typename Container<T>::Node* Container<T>::copy(const Node* first, Node*& last)
{
  if ( !first )
    return last = nullptr;

  Node* start = new Node(first->info);
  Node* n = start;

  while ( first->next )
  {
    first = first->next;
    n->next = new Node(first->info, n);
    n = n->next;
  }
  last = n;
  return start;
}

template <class T>
bool Container<T>::isListEqual(const Node* n1, const Node *n2)
{
  if ( n1 == n2 )
    return true;

  if ( !n1 || !n2 )
    return false;

  return (( n1->info == n2->info ) && isListEqual(n1->next,n2->next));
}

template <class T>
int Container<T>::getSize() const
{
  return size;
}

#endif // CONTAINER_H
