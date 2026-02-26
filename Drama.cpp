#include "Drama.h"
Drama::Drama(int stock, const std::string name, std::string director, int year) {}

void Drama::print() const {
    std::cout << "Drama: "
              << stock << ", "
              << director << ", "
              << title << ", "
              << year << std::endl;
}

bool Drama::isEqual(const Movie& other) const {
    const Drama* otherDrama = dynamic_cast<const Drama*>(other);
    if (otherDrama == nullptr) return false;

    return (director == otherDrama->director &&
            title == otherDrama->title);
}