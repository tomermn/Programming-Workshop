//
// Created on 2/20/2022.
//

#ifndef SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
#define SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H

#include "RSUser.h"
#include <regex>
#include <map>
#include <cmath>
#include <bits/stdc++.h>
#include <set>


using std::vector;
typedef std::map<sp_movie , std::vector<double>, equal_func> movies_map;


class RecommenderSystem
{
 public:
  explicit RecommenderSystem():_movies_map(sp_movie_compare)
  {}
  /**
   * adds a new movie to the system
   * @param name name of movie
   * @param year year it was made
   * @param features features for movie
   * @return shared pointer for movie in system
   */
  sp_movie add_movie(const std::string& name,int year, \
  const vector<double>& features);

  /**
   * a function that calculates the movie with highest score
   * based on movie features
   * @param ranks user ranking to use for algorithm
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_content(const RSUser& user);

  /**
   * a function that calculates the movie with highest
   * predicted score based on ranking of other movies
   * @param ranks user ranking to use for algorithm
   * @param k
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_cf(const RSUser& user, int k);


  /**
   * Predict a user rating for a movie given argument using
   * item cf procedure with k most similar movies.
   * @param user_rankings: ranking to use
   * @param movie: movie to predict
   * @param k:
   * @return score based on algorithm as described in pdf
   */
  double predict_movie_score(const RSUser &user, const sp_movie &movie,
                             int k);

  /**
   * gets a shared pointer to movie in system
   * @param name name of movie
   * @param year year movie was made
   * @return shared pointer to movie in system
   */
  sp_movie get_movie(const std::string &name, int year) const;


  friend std::ostream & operator << (std::ostream& ,RecommenderSystem& system);


 private:
  movies_map _movies_map;

  /**
 * creates preference vector from the normal rank map of the user.
 */
  vector<double> create_preference_vec (const rank_map& normal_vec);

  /**
  * checks similarity between preference vector to unwatched movies.
  */
  sp_movie check_similarity (const vector<double>& preference_vec,
                             const RSUser& user);
  /**
   * creates vector of unwatched movies with a pair:
   * <similarity, sp_movie>
   */
  vector<std::pair<double, sp_movie>> create_similarity_vec(const sp_movie& movie, const RSUser& user);
  double calculate_prediction (const RSUser& user, vector<std::pair<double, sp_movie>> similarity_vec, int k);
};


#endif //SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H