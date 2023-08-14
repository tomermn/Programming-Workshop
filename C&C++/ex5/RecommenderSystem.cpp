#include "RecommenderSystem.h"


// -- aux functions -- //
double calculate_rates_average (const RSUser& user)
{
  double  sum = 0;
  double watched = 0;
  for (auto& m : user.get_ranks())
    {
      if (m.second >= MIN_RATE && m.second <= MAX_RATE)
        {
          sum += m.second;
          watched ++;
        }
    }
  double average = (sum / watched);//we are assuming that each RSUser watched at least one movie.
  return average;
}

/**
* normalizes user's rank_map.
*/
rank_map create_normal_vec(const RSUser& user)
{
  double average = calculate_rates_average(user);
  rank_map normal_rank_vector(0, sp_movie_hash, sp_movie_equal);
  for (auto& m : user.get_ranks())
    {
        normal_rank_vector[m.first] = m.second;
        normal_rank_vector[m.first] -= average;
    }
  return normal_rank_vector;
}

vector<double> vector_multiplication_by_scalar (double scalar, const vector<double>& vector)
{
  std::vector<double> new_vec;
  for (auto &cord : vector)
    {
      new_vec.push_back (cord * scalar);
    }
  return new_vec;
}

/**
* add to th i'th coordinate of target the i'th coordinate of other.
*/
void vector_addition (vector<double>& target, const vector<double>& other)
{
  for (int i = 0; i < (int) target.size (); i++)
    {
      target[i] += other[i];
    }
}

/**
* returns the dot product of twe vectors.
*/
double vector_multiplication(const vector<double>& target,\
const vector<double>& other)
{
  double result = 0;
  for (int i = 0; i < (int) target.size (); i++)
    {
      result += target[i] * other[i];
    }
  return result;
}

/**
* calculate and returns the norm of a given vector.
*/
double calculate_norm (const vector<double>& vector)
{
  double sum = 0;
  for (auto& cord : vector)
    {
      sum += (cord * cord);
    }
  double norm = sqrt(sum);
  return norm;
}


// -- private methods for recommendation algorithms -- //
vector<double> RecommenderSystem::create_preference_vec (const rank_map& normal_vec)
{
  vector<double> preference_vec(_movies_map.begin()->second.size(), 0);

  for (auto& movie : normal_vec)
    {
      double scalar = movie.second;
      vector<double> features = _movies_map[movie.first];
      vector<double> temp = vector_multiplication_by_scalar (scalar, features);
      vector_addition (preference_vec, temp);
    }
  return preference_vec;
}


double calculate_similarity(const vector<double>& preference_vec, const vector<double>& features_vec)
{
  double pref_norm = calculate_norm (preference_vec);
  double features_norm = calculate_norm (features_vec);
  if (pref_norm == 0 || features_norm == 0)
    {
      throw std::logic_error("Divided by 0");
    }
  vector<double> vec_a = vector_multiplication_by_scalar \
  ((1/pref_norm), preference_vec);
  vector<double> vec_b = vector_multiplication_by_scalar \
  ((1/features_norm), features_vec);
  return vector_multiplication (vec_a, vec_b);
}


sp_movie RecommenderSystem::check_similarity (const vector<double>& preference_vec, const RSUser& user)
{
  double max_similarity = -(std::numeric_limits<double>::infinity());
  sp_movie recommendation;
  for (auto &movie : _movies_map)
    {
      if (user.get_ranks().find (movie.first)  == user.get_ranks().end())
        {
          vector<double> features = movie.second;
          double similarity = calculate_similarity(preference_vec, features);
          if (similarity > max_similarity)
            {
              max_similarity = similarity;
              recommendation = movie.first;
            }
        }
    }
  return recommendation;
}


vector<std::pair<double, sp_movie>> RecommenderSystem::create_similarity_vec(const sp_movie& movie, const RSUser& user)
{
  vector<std::pair<double, sp_movie>> similarity_vec;
  for (auto &watched_movie : user.get_ranks())
    {
      double similarity = calculate_similarity\
      (_movies_map[movie], _movies_map[watched_movie.first]);
      std::pair <double, sp_movie > pair;
      pair.first = similarity;
      pair.second = watched_movie.first;
      similarity_vec.push_back(pair);
    }
    return similarity_vec;
}

bool compare_pairs_reverse (const std::pair<double, sp_movie >& a, const std::pair<double, sp_movie >&  b)
{
  return a.first > b.first;
}

double RecommenderSystem::calculate_prediction (const RSUser& user, vector<std::pair<double, sp_movie>> similarity_vec, int k)
{
  std::sort(similarity_vec.begin(), similarity_vec.end(), compare_pairs_reverse);
  double numerator = 0, denominator = 0;
  for (int i = 0; i < k; i++)
    {
      sp_movie movie = similarity_vec[i].second;
      numerator += (similarity_vec[i].first * user.get_ranks().find(movie)->second);
      denominator += similarity_vec[i].first;
    }
  if (denominator == 0)
    {
      throw std::logic_error("Divided by 0");
    }
  double result = (numerator / denominator);
  return result;
}

// -- recommendation algorithms -- //

sp_movie RecommenderSystem::recommend_by_content(const RSUser& user)
{
  rank_map normal_rank_vector = create_normal_vec(user);
  vector<double> preference_vec = create_preference_vec (normal_rank_vector);
  sp_movie recommendation = check_similarity (preference_vec, user);
  return recommendation;
}

double RecommenderSystem::predict_movie_score(const RSUser &user, const sp_movie &movie, int k)
{
  vector<std::pair < double, sp_movie >> similarity_vec = create_similarity_vec (movie, user);
  double prediction = calculate_prediction (user, similarity_vec, k);
  return prediction;
}


sp_movie RecommenderSystem::recommend_by_cf(const RSUser& user, int k)
{
  double max_prediction = 0;
  sp_movie recommendation;
  for (auto &movie : _movies_map)
    {
      if (user.get_ranks().find(movie.first) == user.get_ranks().end())
        {
          double prediction = predict_movie_score (user, movie.first, k);
          if (prediction > max_prediction)
            {
              max_prediction = prediction;
              recommendation = movie.first;
            }
        }
    }
    return recommendation;
}

// -- general methods -- //

sp_movie RecommenderSystem::add_movie(const std::string& name, int year,const std::vector<double>& features)
{
  std::shared_ptr<Movie> sp_movie = std::make_shared<Movie>(name, year);
  _movies_map[sp_movie] = features;
  return sp_movie;
}


sp_movie RecommenderSystem::get_movie(const std::string &name, int year) const
{
  sp_movie temp = std::make_shared<Movie>(name, year);
  auto it = _movies_map.find(temp);
  if (it == _movies_map.end())
    {
      return nullptr;
    }
  return it->first;
}

std::ostream & operator << (std::ostream& os, RecommenderSystem& system)
{
  for (auto& sp_movie : system._movies_map)
    {
      os << *(sp_movie.first);
    }
  return os;
}