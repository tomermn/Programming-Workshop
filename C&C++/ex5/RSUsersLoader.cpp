#include <sstream>
#include "RSUsersLoader.h"

vector<string> creates_movies_vec (const std::string& line, vector<string> movies_vec)
{
  std::string movie;
  std::istringstream iss(line);
  while (iss >> movie)
    {
      movies_vec.push_back(movie);
    }
  return movies_vec;
}

vector<sp_movie> creates_sp_movies_vec (const vector<string>& movies_vec, vector<sp_movie> sp_movies_vec, const
std::shared_ptr<RecommenderSystem>& recommender_system)
{
  for (auto movie : movies_vec)
    {
      std::string name;
      int year;
      movie = std::regex_replace(movie, std::regex("\\-"), " ");
      std::istringstream iss(movie);
      iss>>movie;
      name = movie;
      iss>>movie;
      year = stoi (movie);
      sp_movies_vec.push_back (recommender_system->get_movie (name, year));
    }
  return sp_movies_vec;
}

bool is_rate_valid (double rate)
{
  return ((rate >= MIN_RATE) && (rate < MAX_RATE));
}

RSUser create_user (const string& line, vector<double> rates_vec, vector<sp_movie> sp_movies_vec,
                    shared_ptr<RecommenderSystem> recommender_system){
  rank_map user_rank_map(0, sp_movie_hash, sp_movie_equal);
  string word;
  string name;
  int counter = 0;
  std::istringstream iss(line);

  while (iss >> word){
      if (counter == NAME){
          name = word;
          counter++;
        }
      else{
          if (word == NA){
              rates_vec.push_back (NA_VALUE);
            }
          else{
              rates_vec.push_back (std::stod (word));
            }
        }
    }

    for (int i = 0; i < (int) rates_vec.size(); i++){
        if (is_rate_valid (rates_vec[i])){
              user_rank_map[sp_movies_vec[i]] = rates_vec[i];
          }
      }

    RSUser new_user (name, user_rank_map, recommender_system);
    return new_user;
}

vector<RSUser>RSUsersLoader::create_users_from_file(const std::string& users_file_path,
                                                    std::unique_ptr<RecommenderSystem> rs) noexcept(false){

  std::ifstream input_stream(users_file_path);
  if (!input_stream){
      throw std::runtime_error(FILE_ERROR);
    }

  vector<RSUser> users_vec;
  int flag = 0;
  std::string line;
  vector<string> movies_vec;
  vector<sp_movie> sp_movies_vec;
  std::shared_ptr<RecommenderSystem> shared_rs = std::move (rs);

  while (getline(input_stream, line))
    {
      if (flag == NAME)
        {
          movies_vec = creates_movies_vec (line, movies_vec);
          sp_movies_vec = creates_sp_movies_vec \
          (movies_vec, sp_movies_vec, shared_rs);
           flag++;
        }
      else
        {
          std::vector<double> rates_vec;
          users_vec.push_back (create_user\
          (line, rates_vec, sp_movies_vec, shared_rs));
        }
    }
  return users_vec;
}


