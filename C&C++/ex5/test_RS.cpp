#include "RecommenderSystem.h"
#include "RSUsersLoader.h"
#include <cassert>

using std::make_shared;
using std::pair;
using std::make_pair;
using std::cout;

#define NA  (-1)


int main()
{
    std::vector<double> Titanic = {7, 2, 9, 1};
    std::vector<double> Twilight = {3,4,6,5};
    std::vector<double> ForestGump = {1,7,7,6};
    std::vector<double> Batman =  {2,6,4,8};
    std::vector<double> StarWars = {3,3,4,9};
    rank_map rank(4, sp_movie_hash, sp_movie_equal);
    std::shared_ptr<RecommenderSystem> rs = make_shared<RecommenderSystem>();
    std::string name = "sofia";
    RSUser me(name, rank, rs);
    me.add_movie_to_rs("Titanic", 1997,Titanic, 4);
//    me.add_movie_to_rs("Twilight", 2008,Twilight, NA);
    me.add_movie_to_rs("ForestGump", 1994,ForestGump, 8);
//    me.add_movie_to_rs("Batman", 2022,Batman, NA);
//    me.add_movie_to_rs("StarWars", 1977,StarWars, NA);
    sp_movie res = (me.get_recommendation_by_content()) ;
    cout << (*res); // should print: "Batman (2022)\n"
//    assert(res->get_name() == "Batman" && res->get_year() ==  2022);
}