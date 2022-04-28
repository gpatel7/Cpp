#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <regex>

using namespace std;

typedef multimap<string, string> YearGenreIndexType;
class MovieCatalog
{
public:
    YearGenreIndexType Movies;

    int LoadMovieCatalog()
    {
        //Load Year Index where <year, <genre, title>>
        return 0;
    }

    vector<string> GetMovieTitles(const string &genre, const string &startYear, const string &endYear)
    {
        unordered_multimap<string, string> moviesByYear;
        vector<string> movieNames;
        
        string start = startYear + genre;
        string end = endYear + genre;

        
        

    }
};
