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
  *  Subclass 1. Factory 2
  */
class SubclassFactory2Product1: public ProductName{
public:
  SubclassFactory2Product1(){}
  ~SubclassFactory2Product1(){}
//protected:
   void factoryOperation1(){
    cout<<"factory2 subclass1 op1 "<<endl;
  }
   void factoryOperation2(){
    cout<<"factory2 subclass1 op2 "<<endl;
  }
   void factoryOperation3(){
    cout<<"factory2 subclass1 op3 "<<endl;
  }
   void factoryOperation4(){
    cout<<"factory2 subclass1 op4 "<<endl;
  }
};


/**
  *  Subclass 2. Factory 2
  */
class SubclassFactory2Product2: public ProductName {
public:
  SubclassFactory2Product2(){}
  ~SubclassFactory2Product2(){}
//protected:
  void factoryOperation1(){
    cout<<"factory2 subclass2 op1 "<<endl;
  }
  void factoryOperation2(){
    cout<<"factory2 subclass2 op2 "<<endl;
  }
  void factoryOperation3(){
    cout<<"factory2 subclass2 op3 "<<endl;
  }
  void factoryOperation4(){
    cout<<"factory2 subclass2 op4 "<<endl;
  }
};

/**
  *  Subclass 1. Factory 1
  */
class SubclassFactory1Product1: public ProductName{
public:
  SubclassFactory1Product1(){}
  ~SubclassFactory1Product1(){}
//protected:
   void factoryOperation1(){
    cout<<"factory1 subclass1 op1 "<<endl;
  }
   void factoryOperation2(){
    cout<<"factory1 subclass1 op2 "<<endl;
  }
   void factoryOperation3(){
    cout<<"factory1 subclass1 op3 "<<endl;
  }
   void factoryOperation4(){
    cout<<"factory1 subclass1 op4 "<<endl;
  }
};


/**
  *  Subclass 2. Factory 1
  */
class SubclassFactory1Product2: public ProductName {
public:
  SubclassFactory1Product2(){}
  ~SubclassFactory1Product2(){}
//protected:
  void factoryOperation1(){
    cout<<"factory1 subclass2 op1 "<<endl;
  }
  void factoryOperation2(){
    cout<<"factory1 subclass2 op2 "<<endl;
  }
  void factoryOperation3(){
    cout<<"factory1 subclass2 op3 "<<endl;
  }
  void factoryOperation4(){
    cout<<"factory1 subclass2 op4 "<<endl;
  }
};

class ProductNameStrore {
public:
  ProductName *orderProduct(string type) {
    ProductName *product;
    product = createProductName(type);
    product->factoryOperation1();
    product->factoryOperation2();
    product->factoryOperation3();
    product->factoryOperation4();
    return product;
  }
  virtual ProductName *createProductName(string type)=0;
};

class SimpleProductNameFactory1 : public ProductNameStrore{
public:
  ProductName *createProductName(string type) {
    ProductName *product = NULL;
      if (type == "sub1") {
        product = new SubclassFactory1Product1();
      }
      else if (type == "sub2") {
        product = new SubclassFactory1Product2();
      }
      else {
        product = new ProductName();
      }
    return product;
  }
};

class SimpleProductNameFactory2 : public ProductNameStrore{
public:
  ProductName *createProductName(string type) {
    ProductName *product = NULL;
      if (type == "sub1") {
        product = new SubclassFactory2Product1();
      }
      else if (type == "sub2") {
        product = new SubclassFactory2Product2();
      }
      else {
        product = new ProductName();
      }
    return product;
  }
};


/**
  * Testing pattern code...
  */
int main()
{
  SimpleProductNameFactory1 *simp1 = new SimpleProductNameFactory1();
//  ProductNameStrore *pr1 = new ProductNameStrore();
  simp1->orderProduct("");
  cout<<endl;
  simp1->orderProduct("sub1");
  cout<<endl;
  simp1->orderProduct("sub2");


  SimpleProductNameFactory2 *simp2 = new SimpleProductNameFactory2();
//  ProductNameStrore *pr2 = new ProductNameStrore();
  simp2->orderProduct("");
  cout<<endl;
  simp2->orderProduct("sub1");
  cout<<endl;
  simp2->orderProduct("sub2");
  return 0;
}

