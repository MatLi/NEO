/*
 * FILENAME:      Set.h
 * PROJECT:       NEO
 * PROGRAMMER:    David
 *
 * DATE:          2012-12-12
 *
 * DESCRIPTION:
 * A template for a set. Is used to store and work on sets of
 * edges and sets of nodes in the Network and the algorithms.
 */

#ifndef SET_HH
#define SET_HH

#include <vector>
#include <iostream>

template <class T>
class Set
{
 public:
  Set() = default;
  ~Set() = default;
  
  void add_member(T);
  void remove_member(T);
  virtual void clear();
  bool empty() const;
  unsigned int size() const;
  bool exists(T) const;
      
  typename std::vector<T>::iterator begin();
  typename std::vector<T>::iterator end();

 private:
  std::vector<T> members_;
};

/* Set<T>::exists(T)
 * Returnerar sant omm elementet T finns i m�ngden.
 */
template <class T>
bool
Set<T>::exists(T search_element) const
{
  bool exists = false;
  for (auto it : members_)
    {
      if (&(*it) == search_element)
	{
	  exists = true;
	}
    }
  return exists;
}

/*
 * Set<T>::add_member()
 * L�gg till medlemmen new_member i m�ngden.
 */
template <class T>
void
Set<T>::add_member(T new_member)
{
  for (auto it : members_)
    {
      if (&(*it) == new_member)
	{
	  return;
	}
    }
  members_.push_back(new_member);
  return;
}

/*
 * Set<T>::remove_member()
 *
 * Ta bort medlemmen old_member ur m�ngden.
 */
template <class T>
void
Set<T>::remove_member(T old_member)
{
  typename std::vector<T>::iterator temp = members_.begin();
  int i_it = 0;
  for (auto it : members_)
    {
      if (&(*it) == old_member)
	{
	  members_.erase(temp + i_it);
	  return;
	}
      i_it++;
    }
  return; 
}

/*
 * Set<T>::clear()
 *
 * Vi vill inte ta bort objekten som pekarna pekar p�
 * eftersom det kan vara medlem i andra m�ngder.
 */
template <class T>
void
Set<T>::clear()
{
  members_.clear();
  return;
}

template <class T>
bool
Set<T>::empty() const
{
  return members_.empty();
}

/*
 * Set<T>::size()
 *
 * M�ngdens kardinalitet.
 */
template <class T>
unsigned int
Set<T>::size() const
{
  return members_.size();
}

template <class T>
typename std::vector<T>::iterator
Set<T>::begin()
{
  return members_.begin();
}

template <class T>
typename std::vector<T>::iterator
Set<T>::end()
{
  return members_.end();
}

#endif
