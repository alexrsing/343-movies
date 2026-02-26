#include "Classic.h"

Classic::Classic(int stock,
                 const std::string& director,
                 const std::string& title,
                 const std::string& actorFirst,
                 const std::string& actorLast,
                 int month,
                 int year)
    : Movie(stock, director, title, year),
      actorFirst(actorFirst),
      actorLast(actorLast),
      month(month) {}

void Classic::print() const {
    std::cout << "Classic: "
              << stock << ", "
              << director << ", "
              << title << ", "
              << actorFirst << " "
              << actorLast << " "
              << month << " "
              << year << std::endl;
}

bool Classic::isEqual(const Movie* other) const {
    const Classic* otherClassic = dynamic_cast<const Classic*>(other);
    if (otherClassic == nullptr) return false;

    return (month == otherClassic->month &&
            year == otherClassic->year &&
            actorFirst == otherClassic->actorFirst &&
            actorLast == otherClassic->actorLast);
}

int Classic::getMonth() const {
    return month;
}