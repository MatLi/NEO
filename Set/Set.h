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
      
  const T* operator[](std::size_t n) const;
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
  using namespace std;
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
  using namespace std;
  for (auto it : members_)
    {
      if ((*it) == old_member)
	members_.erase(it);
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
  using namespace std;
  members_.clear();
  return;
}

template <class T>
bool Set<T>::empty() const
{
  using namespace std;
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
  using namespace std;
  return members_.size();
}

/*
 * Set<T>::operator[]
 *
 * Åtkomst till element n i mängden. Används för iteration.
 */
template <class T>
const T* Set<T>::operator[](std::size_t n) const
{
  using namespace std;
  return members_[n];
}

#endif
