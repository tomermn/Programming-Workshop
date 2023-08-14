//
// Created on 2/20/2022.
//

// don't change those includes
#include "RSUser.h"
#include "RecommenderSystem.h"



RSUser::RSUser(const string& user_name, const rank_map& rank_map, shared_ptr<RecommenderSystem> sptr_rs)
{
  _user_name = user_name;
  _user_rank_map = rank_map;
  _rs_ptr = std::move(sptr_rs);
}

std::ostream& operator << (std::ostream &os, const RSUser& user)
{
  os << "name: " << user.get_name() << std::endl;
  os << *(user._rs_ptr) << std::endl;
  return os;
}

sp_movie RSUser::get_recommendation_by_content() const
{
  sp_movie chosen = _rs_ptr->recommend_by_content (*this);
  return chosen;
}

double RSUser::get_prediction_score_for_movie(const std::string& name, int year, int k) const
{
  sp_movie movie = _rs_ptr->get_movie (name, year);
  double prediction = _rs_ptr->predict_movie_score (*this, movie, k);
  return prediction;
}

sp_movie RSUser::get_recommendation_by_cf(int k) const
{
  return _rs_ptr->recommend_by_cf (*this, k);
}

void RSUser::add_movie_to_rs(const std::string &name, int year,
                             const std::vector<double> &features, double rate)
{
  _rs_ptr->add_movie (name, year, features);
  sp_movie new_movie = std::make_shared<Movie>(name, year);
  _user_rank_map[new_movie] = rate;
}