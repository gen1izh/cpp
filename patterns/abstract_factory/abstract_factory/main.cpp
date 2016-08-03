#include <iostream>
#include <string>

using namespace std;

class PizzaIngredientFactory {
public:
  Dough       createDough();
  Sance       createSance();
  Cheese      createCheese();
  Veggies     createVeggies();
  Pepperoni   createPepperoni();
  Clams       createClam();
};

class NYPizzaIngredientFactory : public PizzaIngredientFactory {
public:
  Dough createDough(){
    return new ThinGrustDough();
  }
  Sance createSance(){
    return new MarinaraSauce();
  }
  Cheese createCheese(){
    return new ReggianoCheese();
  }
  Veggies createVeggies(){
    return new Veggies();
  }
  Pepperoni createPepperoni(){
    return new SlicedPepperoni();
  }
  Clams createClam(){
    return new FreshClams();
  }
};

class CheesePizza : public Pizza {
private:
  PizzaIngredientFactory ingredientFactory;
  void prepare(){
    cout << "preparing"<<name;
    dough = ingredientFactory.createDough();
    sance = ingredientFactory.createSance();
    cheese = ingredientFactory.createCheese();
  }
public:
  CheesePizza(PizzaIngredientFactory ingredientFactory){
    this->ingredientFactory = ingredientFactory;
  }
};

class ClamPizza : public Pizza {
private:
  PizzaIngredientFactory ingredientFactory;
  void prepare(){
    cout << "preparing"<<name;
    dough = ingredientFactory.createDough();
    sance = ingredientFactory.createSance();
    cheese = ingredientFactory.createCheese();
    clam = ingredientFactory.createClam();
  }
public:
  ClamPizza(PizzaIngredientFactory ingredientFactory){
    this->ingredientFactory = ingredientFactory;
  }
};

class NYPizzaStore : public PizzaStore {
protected:
  Pizza createPizza(String item){
    Pizza pizza = NULL;
    PizzaIngredientFactory ingredientFactory =
        new NYPizzaIngredientFactory();
    if (item == "cheese"){
        pizza = new  CheesePizza(ingredientFactory);
        pizza.setName("New York Style Cheese Pizza");
      }
    else if (item == "Veggie"){
        pizza = new VeggiePizza(ingredientFactory);
        pizza.setName("New York Style Veggie Pizza");
      }
    else if(item == "clam"){
        pizza = new ClamPizza(ingredientFactory);
        pizza.setName("New York Style Clam Pizza");
      }
    else if (item == "pepperoni"){
        pizza = new PepperoniPizza(ingredientFactory);
        pizza.setName("New York Style Pepperoni Pizza");
      }
    return pizza;
  }
};

int main()
{

  //Pizza pizzaStrore.createPizza("cheese");

  return 0;
}

