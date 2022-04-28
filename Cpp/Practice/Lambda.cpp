#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>
using namespace std;

class Movie
{
public:
	string toString()
	{
		return "[name:" + name + "] [year:" + to_string(year) + "] [genre:" + genre + "]";
	}
	shared_ptr<Movie> ToSharedPtr()
	{
			auto s=shared_ptr<Movie>(new Movie());
			s->year = year;
			s->genre = genre;
			s->name = name;
			return s;
	}
	string name;
	int year;
	string genre;

private:
};


typedef vector<shared_ptr<Movie>> CacheType;
typedef vector<shared_ptr<Movie>> Movies;

class Cache
{

public:
	static Cache &GetInstance()
	{
		if (_self == nullptr)
		{
			_self = new Cache();
		}
		return *_self;
	}
	~Cache()
	{
		delete _self;
	}
	void AddMovie(const string &name, const string &genre, const string &year)
	{
		auto m = shared_ptr<Movie>(new Movie());
		m->name = name;
		m->genre = genre;
		m->year = regex_match(year, regex("[0-9][0-9][0-9][0-9]")) ? stoi(year) : 0;

		_cache.push_back(m);
	}
	void GetMovieByYears(const int& beginYear, const int& endYear,Movies& movies)
	{
		copy_if(_cache.begin(),_cache.end(),back_inserter(movies),[beginYear,endYear](shared_ptr<Movie> const& m){ return m->year>=beginYear && m->year<=endYear;});
	}
	void GetMovieByGenre(const string& genre, Movies& movies)
	{
		copy_if(_cache.begin(),_cache.end(),back_inserter(movies),[genre](shared_ptr<Movie> const& m) { return m->genre == genre;});
	}
	void PrintMovies( Movies& movies)
	{
		for ( Movies::iterator iter = movies.begin(); iter != movies.end(); ++iter)
		{
			cout << iter->get()->toString() << endl;
		}
	}
private:
	Cache() {}
	static Cache *_self;
	CacheType _cache;
};

Cache *Cache::_self = nullptr;

int init()
{
	ifstream f("/Users/ndoshi200/CodePractice/Cpp/Practice/lambdaInput.txt");
	char delim(',');
	string line, cell = "";
	vector<string> row;
	if (!f.is_open())
	{
		cerr << "file not found" << endl;
		f.close();
		return 1;
	}
	while (getline(f, line, '\n'))
	{
		row.clear();
		stringstream str(line);
		while (getline(str, cell, ','))
		{
			row.push_back(cell);
		}
		Cache::GetInstance().AddMovie(row[0], row[1], row[7]);
	}
	f.close();
	return 0;
}
int main(void)
{
	if (init() == 0)
	{
		Movies movies;
		// Cache::GetInstance().GetMovieByYears(2010,2010,movies);
		// Cache::GetInstance().PrintMovies(movies);
		// movies.clear();
		Cache::GetInstance().GetMovieByGenre("Drama",movies);
		Cache::GetInstance().PrintMovies(movies);
		return 0;
	}
	return 1;
}
