#include<iostream>
#include<list>
#include<set>
#include<vector>
#include"MovieRating.h"
#include<fstream>
#include<algorithm>
#include<numeric>

using namespace std;

struct UserMovieGrade
{
	int user_id;
	int movie_id;
	double rating;

	friend istream& operator>>(istream& is, UserMovieGrade& n)
	{
		is >> n.user_id >> n.movie_id >> n.rating;
		return is;
	}

	friend ostream& operator<<(ostream& os, UserMovieGrade& n)
	{
		os<< "Movie Id - " << n.movie_id << ";    Rating - " << n.rating << ";    User Id - " << n.user_id << endl;
		return os;
	}
};




int main()
{
	ifstream fileMovieName("movies.txt");
	set<int> setMoviesId;

	try 
	{
		if (fileMovieName.is_open())
		{
			copy(istream_iterator<int>(fileMovieName), istream_iterator<int>(), inserter(setMoviesId, setMoviesId.begin()));
		}
		else
		{
			throw runtime_error("File is not open!");
		}
	}
	catch (exception& e) 
	{
		cout << "Error: " << e.what();
	}

	fileMovieName.close();

	//for (int n : setMoviesId)
	//{
	//	cout << n << " ";
	//}
	//cout << endl;
	//copy(setMoviesId.begin(), setMoviesId.end(), ostream_iterator<int>(cout, " "));


	cout << endl;
	ifstream fileUsMovGrade("grades.txt");
	vector<UserMovieGrade> vectorUMG;

	try 
	{
		if (fileUsMovGrade.is_open())
		{
			copy(istream_iterator<UserMovieGrade>(fileUsMovGrade), istream_iterator<UserMovieGrade>(), back_inserter(vectorUMG));
		}
		else
		{
			throw runtime_error("File is not open!");
		}
	}
	catch (exception& e)
	{
		cout << "Error: " << e.what();
	}
	
	//for (UserMovieGrade el : vectorUMG)
	//{
	//	cout << el;
	//}
	fileUsMovGrade.close();




	list<MovieRating> listMovie;

	transform(setMoviesId.begin(), setMoviesId.end(), back_inserter(listMovie), [=](int id)
		{
			return MovieRating(id, 0.0);
		});


	for_each(listMovie.begin(), listMovie.end(), [&](MovieRating& movie)
		{
			int currentId = movie.getMovieId();
			int amount = count_if(vectorUMG.begin(), vectorUMG.end(), [=](UserMovieGrade& g)
				{
					return g.movie_id == currentId;
				});
			double sum = accumulate(vectorUMG.begin(), vectorUMG.end(), 0.0, [=](double result, UserMovieGrade& g)
				{
					if (g.movie_id == currentId)
					{
						return result + g.rating;
					}
					else
					{
						return result;
					}
				});

			if (amount > 0)
			{
				movie.setAverageGrade(sum / amount);
				movie.setAmountGrades(amount);
			}
		});

	cout << "-------------------------------------------------------" << endl;
	cout << "     FILM ID     |      GRADE      | NUMBER OF REVIEWS" << endl;
	cout << "-------------------------------------------------------" << endl;
	for (auto& n : listMovie)
	{
		cout << "        " << n.getMovieId() << "      |     " << n.getRating() << "\t   |\t    " << n.getAmountGrades() << endl;
		cout << "-------------------------------------------------------" << endl;
	}

	listMovie.sort([](const MovieRating& a, const MovieRating& b)
		{
			return a.getRating() > b.getRating();
		});

	cout << "\nSORTED BY RATING LIST:" << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "     FILM ID     |      GRADE      | NUMBER OF REVIEWS" << endl;
	cout << "-------------------------------------------------------" << endl;
	for (auto& n : listMovie)
	{
		cout << "        " << n.getMovieId() << "      |     " << n.getRating() << "\t   |\t    " << n.getAmountGrades() << endl;
		cout << "-------------------------------------------------------" << endl;
	}

	cout << "\nTOP 3 BEST FILMS BY RATING:\n";
	cout << "-------------------------------------------------------" << endl;
	cout << "     FILM ID     |      GRADE      | NUMBER OF REVIEWS" << endl;
	cout << "-------------------------------------------------------" << endl;
	list<MovieRating>::iterator topEnd = listMovie.begin();
	advance(topEnd, min((int)listMovie.size(), 3));

	for_each(listMovie.begin(), topEnd, [](const MovieRating& movie)
		{
			cout << "        " << movie.getMovieId() << "      |     " << movie.getRating() << "\t   |\t    " << movie.getAmountGrades() << endl;
			cout << "-------------------------------------------------------" << endl;
		});

	cout << "\nMOVIE WITH HIGH GRADE AND LOW AMOUNT OF REVIEWS:" << endl;
	list<MovieRating>::iterator filmGrade = find_if(listMovie.begin(), listMovie.end(), [](MovieRating& movie)
		{
			return movie.getRating() > 4.0 && movie.getAmountGrades() < 10;
		});

	if (filmGrade != listMovie.end())
	{
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "Movie Id - " << filmGrade->getMovieId() << "    |    Grade - " << filmGrade->getRating() << "     |    Amount of review - " << filmGrade->getAmountGrades() << endl;
		cout << "--------------------------------------------------------------------------" << endl;
	}

	return 0;
}