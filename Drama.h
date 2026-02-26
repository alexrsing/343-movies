#ifndef DRAMA_H
#define DRAMA_H

#include "movie.h"

class Drama : public Movie {
    public:
    Drama(int stock, const std::string name, std::string director, int year);

    void print() const override;
    bool isEqual(const Movie& other) const override;

};

#endif