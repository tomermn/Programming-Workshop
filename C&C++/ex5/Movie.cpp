#include "Movie.h"
#define HASH_START 17
#define RES_MULT 31

Movie::Movie (const std::string &name, int year)
{
  _name = name;
  _year = year;
}

std::ostream& operator<< (std::ostream& os, const Movie& movie)
{
  os << movie.get_name() << " (" <<movie.get_year() << ")" << "\n";
  return os;
}

bool Movie::operator < (const Movie& other) const
{
  if (get_year() == other.get_year())
    {
      return std::lexicographical_compare (get_name().begin(),\
      get_name().end(), other.get_name().begin(), other.get_name().end());
    }
  return get_year() < other.get_year();
}


/**
 * hash function used for a unordered_map (implemented for you)
 * @param movie shared pointer to movie
 * @return an integer for the hash map
 */
std::size_t sp_movie_hash(const sp_movie& movie)
{
  std::size_t res = HASH_START;
  res = res * RES_MULT + std::hash<std::string> () (movie->get_name ());
  res = res * RES_MULT + std::hash<int> () (movie->get_year ());
  return res;
}

/**
 * equal function used for an unordered_map (implemented for you)
 * @param m1
 * @param m2
 * @return true if the year and name are equal else false
 */
bool sp_movie_equal(const sp_movie& m1,const sp_movie& m2){
  return !(*m1 < *m2) && !(*m2 < *m1);
}


/**
 * comparator used for a map
 * @param m1
 * @param m2
 * @return true if *m1 < *m2 (the movies) by the "<" operator of Movie class.
 */
bool sp_movie_compare (const sp_movie& m1,const sp_movie& m2)
{
  return (*m1 < *m2);
}