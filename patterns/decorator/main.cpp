#include <iostream>

using namespace std;


class Beverage {
private:
  String description = "Unknown beverage";
public:
  String getDescription() {
  return description;
  }
  virtual double cost() = 0;
};

class CondimentDecorator:public Beverage{
public:
  virtual String getDescription();
};

class Espresso: public Beverage {
public:
  Espresso(){
    description = "Espresso";
  }
  bouble cost() {
    return 1.99;
  }
};

class HouseBlend :public Beverage{
public:
  HouseBlend(){
    description = "Hause Blend Caffee";
  }
  double cost() {
    return 0.89;
  }
};

class Mocha :public CondimentDecorator{
  Beverage beverage;
public:
  Mocha(Beverage beverage) {
    this->beverage = beverage;
  }
  String getDescription() {
    return beverage.getDescription() + ", Mocha";
  }
  double cost(){
    return 0.20 + beverage.cost();
  }
};

int main()
{
  Beverage beverage = new Espresso();

  cout<<beverage.getDescription()<<beverage.cost();

  Beverage beverage2 = new DarkRoast();

  beverage2 = new Mocha(beverage2);
  beverage2 = new Mocha(beverage2);
  beverage2 = new Mocha(beverage2);

  cout<<beverage2.getDescription()<<beverage2.cost();
  return 0;
}

