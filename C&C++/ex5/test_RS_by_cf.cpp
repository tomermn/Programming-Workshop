//
// Created by yonatan on 05/09/2022.
//

#include "RecommenderSystem.h"
#include <cassert>
using std::make_shared;
using std::pair;
using std::make_pair;
using std::cout;
typedef std::vector<double> d_vec;
using std::string;
#define NA -1

int main()
{
    d_vec Titanic = {7, 2, 9, 1};
    d_vec Twilight = {3,4,6,5};
    d_vec ForestGump = {1,7,7,6};
    d_vec Batman =  {2,6,4,8};
    d_vec StarWars = {3,3,4,9};
    rank_map rank(4, sp_movie_hash, sp_movie_equal);
    std::shared_ptr<RecommenderSystem> rs = make_shared<RecommenderSystem>();
    string name = "yoav";
    RSUser me(name, rank, rs);
    me.add_movie_to_rs("Titanic", 1997,Titanic, NA);
    me.add_movie_to_rs("Twilight", 2008,Twilight, NA);
    me.add_movie_to_rs("ForestGump", 1994,ForestGump, 5);
    me.add_movie_to_rs("Batman", 2022,Batman, NA);
    me.add_movie_to_rs("StarWars", 1977,StarWars, 6);
    double predict_titanic = me.get_prediction_score_for_movie("Titanic", 1997, 2);
    assert(predict_titanic == 5.4643177047208704);
    cout << "prediction works! :)\n";
}