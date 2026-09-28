#pragma once

class MovieRating
{
private:
	int movie_id;
	double averageRating;
	int amountGrades;

public:
	MovieRating(int _movie_id, double _rating);
	MovieRating(int _movie_id, double _rating, int _amount);
	int getMovieId()const;
	void setAverageGrade(double avGrage);
	double getRating()const;
	int getAmountGrades()const;
	void setAmountGrades(int am);
};

