#include "RecommenderSystemLoader.h"

unique_ptr<RecommenderSystem> RecommenderSystemLoader::create_rs_from_movies_file(const string &movies_file_path) noexcept (false)
{
  std::ifstream input_stream(movies_file_path);
  if (!input_stream)
    {
      throw std::runtime_error(FILE_ERROR);
    }
  unique_ptr<RecommenderSystem> rec_system = std::make_unique<RecommenderSystem>();
  string line;
  while (getline(input_stream, line))
    {
      std::vector<double> features;
      std::string name;
      int year;
      line = std::regex_replace (line, std::regex("\\-"), " ");
      std::istringstream ss(line);
      int flag = 0;
      string word;
      while (ss >> word)
        {
          if (flag == NAME)
            {
              name = word;
              flag ++;
            }
          else if (flag == YEAR)
            {
              year = std::stoi (word);
              flag++;
            }
          else
            {
              features.push_back (std::stod(word));
            }
        }
      rec_system->add_movie (name, year, features);
    }
  return rec_system;
}



