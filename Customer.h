#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer;

class CustomerFactory {
public:
  Customer *makeCustomer(std::string data) const;
};

class Customer {
public:
  Customer(int id, std::string firstName, std::string lastName)
      : id(id), firstName(firstName), lastName(lastName) {};

  static CustomerFactory factory;
  int getID() const;

private:
  int id;
  std::string firstName;
  std::string lastName;
};

#endif