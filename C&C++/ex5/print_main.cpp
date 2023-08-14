//
// Created by 24565 on 6/1/2022.
//
//
#include "RecommenderSystemLoader.h"
#include "RSUsersLoader.h"

#include "Movie.h"
int main(){

auto rs = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_input.txt");
auto rs2 = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_2_input.txt");

std::cout << *rs << std::endl;
std::cout << *rs2 << std::endl;
  auto users = RSUsersLoader::create_users_from_file("RSUsersLoader_iput.txt",std::move(rs));
  auto users2 = RSUsersLoader::create_users_from_file("RSUsersLoader_2_input.txt",std::move(rs2));
std::vector<double> features;
features.push_back (2);
  features.push_back (5);
  features.push_back (2);
  features.push_back (6);
  std::vector<double> features2;
  features2.push_back (2);
  features2.push_back (5);
  features2.push_back (2);
  features2.push_back (6);
users[0].add_movie_to_rs ("Spiderman", 2001, features, 8);
std::cout<<*(users[0]._rs_ptr)<<std::endl;
  std::cout<<*(users2[0]._rs_ptr)<<std::endl;
//    auto rs = RecommenderSystemLoader::create_rs_from_movies_file("RecommenderSystemLoader_input.txt");
//    std::cout << *rs << std::endl;
//    auto users = RSUsersLoader::create_users_from_file("RSUsersLoader_input.txt",std::move(rs));
//    std::cout << users[0] << std::endl;

}