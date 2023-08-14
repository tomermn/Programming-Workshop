#ifndef GIT_USER_H
#define GIT_USER_H
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include "Movie.h"
#define NAME 0
#define YEAR 1
#define MAX_RATE 10
#define MIN_RATE 1
#define FILE_ERROR "Problem with file"
using std::unique_ptr;
class RecommenderSystem;
typedef std::unordered_map<sp_movie, double, hash_func,equal_func> rank_map;


class RSUser
{
 public:
  shared_ptr<RecommenderSystem> _rs_ptr;
  /**
   * Constructor for the class
   */
  RSUser(const string& user_name, const rank_map& rank_map,\
  std::shared_ptr<RecommenderSystem> rs_ptr);

  /**
   * a getter for the user's name
   * @return the username
   */
  const string& get_name () const {return _user_name;}

  /**
   * function for adding a movie to the DB
   * @param name name of movie
   * @param year year it was made
   * @param features a vector of the movie's features
   * @param rate the user rate for this movie
   */
  void add_movie_to_rs(const std::string &name, int year,
                       const std::vector<double> &features,
                       double rate);

  /**
   * a getter for the ranks map
   * @return
   */
  const rank_map& get_ranks() const {return _user_rank_map;}

  /**
   * returns a recommendation according to the movie's content
   * @return recommendation
   */
  sp_movie get_recommendation_by_content() const;

  /**
   * returns a recommendation according to the similarity recommendation method
   * @param k the number of the most similar movies to calculate by
   * @return recommendation
   */
  sp_movie get_recommendation_by_cf(int k) const;

  /**
   * predicts the score for a given movie
   * @param name the name of the movie
   * @param year the year the movie was created
   * @param k the parameter which represents the number
   * of the most similar movies to predict the score by
   * @return predicted score for the given movie
   */
  double get_prediction_score_for_movie\
  (const std::string& name, int year, int k) const;

  /**
   * output stream operator
   * @param os the output stream
   * @param user the user
   * @return output stream
   */
  friend std::ostream& operator << (std::ostream &os, const RSUser& user);

 private:
  string _user_name;
  rank_map _user_rank_map;

};

#endif //GIT_USER_H
