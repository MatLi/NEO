/*
 * Fil: Set.h
 * Programmerare: David Larsson <davla210@student.liu.se>
 * Datum: 2012-11-19
 *
 * En mall för en mängd. Skall användas för att representera och
 * arbeta på de huvudsakliga mängderna som används dels för att
 * representera nätverket och i några av algoritmerna för att
 * lösa optimeringsproblem.
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
  
  void add_member(T*);
  void remove_member(T*);
  virtual void clear();
  bool empty() const;
  unsigned int size() const;
      
  T* operator[](std::size_t n) const;
 private:
  std::vector<T*> members_;
};

/*
 * Set<T>::add_member()
 * Lägg till medlemmen new_member i mängden.
 */
template <class T>
void Set<T>::add_member(T* new_member)
{
  members_.push_back(new_member);
  return;
}

/*
 * Set<T>::remove_member()
 *
 * Ta bort medlemmen old_member ur mängden.
 */
template <class T>
void Set<T>::remove_member(T* old_member)
{
  unsigned int i = 0;
  bool removed = false;
  while (i < members_.size() && !removed)
    {
      if (members_[i] == old_member)
	{
	  members_.erase(members_.begin() + i);
	  removed = true;
	}
      i++;
    }
  return; 
}

/*
 * Set<T>::clear()
 *
 * Vi vill inte ta bort objekten som pekarna pekar på
 * eftersom det kan vara medlem i andra mängder.
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
 * Mängdens kardinalitet.
 */
template <class T>
unsigned int Set<T>::size() const
{
  return members_.size();
}

/*
 * Set<T>::operator[]
 *
 * Åtkomst till element n i mängden. Används för iteration.
 */
template <class T>
T* Set<T>::operator[](std::size_t n) const
{
  return members_[n];
}

#endif
