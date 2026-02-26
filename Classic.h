#ifndef CLASSIC_H
#define CLASSIC_H

#include "movie.h"

class Classic : public Movie {
    private:
    std::string actorFirst;
    std::string actorLast;
    int month;

    public:
    Classic(int stock, const std::string name, std::string director, int year, int month, std::string actorFirst, std::string actorLast);

    void print() const override;
    bool isEqual(const Movie& other) const override;

    int getMonth() const;

};