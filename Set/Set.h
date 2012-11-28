/*
 * Fil: Set.h
 * Programmerare: David Larsson <davla210@student.liu.se>
 * Datum: 2012-11-19
 *
 * En mall f�r en m�ngd. Skall anv�ndas f�r att representera och
 * arbeta p� de huvudsakliga m�ngderna som anv�nds dels f�r att
 * representera n�tverket och i n�gra av algoritmerna f�r att
 * l�sa optimeringsproblem.
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
      
  typename std::vector<T>::iterator begin();
  typename std::vector<T>::iterator end();
 private:
  std::vector<T> members_;
};

/*
 * Set<T>::add_member()
 * L�gg till medlemmen new_member i m�ngden.
 */
template <class T>
void Set<T>::add_member(T new_member)
{
  members_.push_back(new_member);
  return;
}

/*
 * Set<T>::remove_member()
 *
 * Ta bort medlemmen old_member ur m�ngden.
 */
template <class T>
void Set<T>::remove_member(T old_member)
{
  for (unsigned int i = 0; i < members_.size(); i++)
    {
      if (members_[i] == old_member)
	{
	  members_.erase(members_.begin() + i);
	  break;
	}
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
void Set<T>::clear()
{
  members_.clear();
  return;
}

template <class T>
bool Set<T>::empty() const
{
  return members_.empty();
}

/*
 * Set<T>::size()
 *
 * M�ngdens kardinalitet.
 */
template <class T>
unsigned int Set<T>::size() const
{
  return members_.size();
}

template <class T>
typename std::vector<T>::iterator Set<T>::begin()
{
  return members_.begin();
}

template <class T>
typename std::vector<T>::iterator Set<T>::end()
{
  return members_.end();
}

#endif
