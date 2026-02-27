#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class CustomerFactory {
public:
  virtual Customer *makeCustomer(std::string data) const = 0;
};

class Customer {
public:
  int getID() const;

private:
  int id;
  std::string firstName;
  std::string lastName;
};

#endif