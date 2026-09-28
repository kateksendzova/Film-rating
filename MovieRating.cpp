#include "MovieRating.h"

MovieRating::MovieRating(int _movie_id, double _rating) 
	: movie_id(_movie_id >= 0 ? _movie_id : 0), averageRating((_rating >= 0.0 && _rating <= 5.0) ? _rating : 0.0), amountGrades(0)
{ }

int MovieRating::getMovieId()const
{
	return movie_id;
}

void MovieRating::setAverageGrade(double avGrage)
{
	averageRating = avGrage;
}

double MovieRating::getRating()const
{
	return averageRating;
}

int MovieRating::getAmountGrades()const 
{
	return amountGrades;
}

void MovieRating::setAmountGrades(int am)
{
	amountGrades = am;
}