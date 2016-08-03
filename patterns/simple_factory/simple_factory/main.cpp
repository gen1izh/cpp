#include <iostream>
#include <string>

using namespace std;

/**
  *  Product realization
  *  Base class
  */
class ProductName {
public:
  ProductName(){}
  ~ProductName(){}
//protected:
  virtual void factoryOperation1(){
    cout<<"ProductName :: factoryOperation1 "<<endl;
  }
  virtual void factoryOperation2(){
    cout<<"ProductName :: factoryOperation2 "<<endl;
  }
  virtual void factoryOperation3(){
    cout<<"ProductName :: factoryOperation3 "<<endl;
  }
  virtual void factoryOperation4(){
    cout<<"ProductName :: factoryOperation4 "<<endl;
  }
};

/**
  *  Subclass 1
  */
class SubclassProduct1: public ProductName{
public:
  SubclassProduct1(){}
  ~SubclassProduct1(){}
//protected:
   void factoryOperation1(){
    cout<<"SubclassProduct1 :: factoryOperation1 "<<endl;
  }
   void factoryOperation2(){
    cout<<"SubclassProduct1 :: factoryOperation2 "<<endl;
  }
   void factoryOperation3(){
    cout<<"SubclassProduct1 :: factoryOperation3 "<<endl;
  }
   void factoryOperation4(){
    cout<<"SubclassProduct1 :: factoryOperation4 "<<endl;
  }
};


/**
  *  Subclass 2
  */
class SubclassProduct2: public ProductName {
public:
  SubclassProduct2(){}
  ~SubclassProduct2(){}
//protected:
  void factoryOperation1(){
    cout<<"SubclassProduct2 :: factoryOperation1 "<<endl;
  }
  void factoryOperation2(){
    cout<<"SubclassProduct2 :: factoryOperation2 "<<endl;
  }
  void factoryOperation3(){
    cout<<"SubclassProduct2 :: factoryOperation3 "<<endl;
  }
  void factoryOperation4(){
    cout<<"SubclassProduct2 :: factoryOperation4 "<<endl;
  }
};

class SimpleProductNameFactory{
public:
  ProductName *createProduct(string type) {
    ProductName *product = NULL;
      if (type == "sub1") {
        product = new SubclassProduct1();
      }
      else if (type == "sub2") {
        product = new SubclassProduct2();
      }
      else {
        product = new ProductName();
      }
    return product;
  }
};

class ProductNameStrore {
  SimpleProductNameFactory *factory;
public:
  ProductNameStrore(SimpleProductNameFactory *factory) {
    this->factory = factory;
  }
  ProductName *orderProduct(string type) {
    ProductName *product;
    product = factory->createProduct(type);
    product->factoryOperation1();
    product->factoryOperation2();
    product->factoryOperation3();
    product->factoryOperation4();
    return product;
  }
};



/**
  * Testing pattern code...
  */
int main()
{
  SimpleProductNameFactory *simp = new SimpleProductNameFactory();
  ProductNameStrore *pr = new ProductNameStrore(simp);
  pr->orderProduct("");
  cout<<endl;
  pr->orderProduct("sub1");
  cout<<endl;
  pr->orderProduct("sub2");

  return 0;
}

