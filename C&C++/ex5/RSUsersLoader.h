//
// Created on 2/21/2022.
//
#ifndef SCHOOL_SOLUTION_USERFACTORY_H
#define SCHOOL_SOLUTION_USERFACTORY_H

#include "RSUser.h"
#include "RecommenderSystem.h"
#include "Movie.h"
#include <fstream>
#include <regex>

#define NA "NA"
#define NA_VALUE -1


class RSUsersLoader
{
public:
    RSUsersLoader() = delete;
    /**
     *
     * loads users by the given format with their movie's ranks
     * @param users_file_path a path to the file of the users and
     * their movie ranks
     * @param rs RecommendingSystem for the Users
     * @return vector of the users created according to the file
     */
    static std::vector<RSUser> create_users_from_file\
    (const string& users_file_path,\
    std::unique_ptr<RecommenderSystem> rs) noexcept(false);

 private:
};

std::vector<string> creates_movies_vec\
(const string& line, std::vector<string> movies_vec);

std::vector<sp_movie> creates_sp_movies_vec\
(const vector<string>& movies_bec, vector<sp_movie> sp_movies_vec,const \
std::shared_ptr<RecommenderSystem>& recommender_system);

#endif //SCHOOL_SOLUTION_USERFACTORY_H
