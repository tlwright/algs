#include <iostream>
#include <string>
using namespace std;
class animal
{
protected:
  string type;
  string name;
  string pronoun;
  int    age;
  int    weight;
  int    id;
  string sound;
  string disposition;
  string training;
  string food;
public:
  animal( const string& name2, const string& pronoun2, 
	  int age2, int weight2, int id2 ) : 
    name (name2), pronoun (pronoun2), age (age2), weight (weight2), id (id2) {}
  virtual ~animal() {}
  
  virtual string getAnimal() = 0;
  virtual string getName() = 0;
  virtual string getPronoun() = 0;
  virtual int    getId() = 0;
  virtual int    getAge() = 0;
  virtual int    getWeight() = 0;
  virtual string getSound() = 0;
  virtual string getDisposition() = 0;
  virtual string getTraining() = 0;
  virtual string getFood() = 0;
};

class dog : public animal
{
public:
  dog( const string& name2, const string& pronoun2, 
       int age2, int weight2, int id2 ) : 
    animal( name2, pronoun2, age2, weight2, id2 )  
  { type = "dog";  sound = "bark";  disposition = "mellow"; 
  training = "easy";  food = "anything"; }
  virtual ~dog() {}

  string getAnimal()      { return type; }
  string getName()        { return name; }
  string getPronoun()     { return pronoun; }
  int    getId()          { return id; }
  int    getAge()         { return age; }
  int    getWeight()      { return weight; }
  string getSound()       { return sound; }
  string getDisposition() { return disposition; }
  string getTraining()    { return training; }
  string getFood()        { return food; }
};

class cat : public animal
{
  public:
  cat( const string& name2, const string& pronoun2, 
       int age2, int weight2, int id2 ) : 
    animal( name2, pronoun2, age2, weight2, id2 ) 
  { type = "cat"; sound = "meow"; disposition = "mysterious"; 
  training = "difficult"; food = "liver"; }
  virtual ~cat() {}

  string getAnimal()      { return type; }
  string getName()        { return name; }
  string getPronoun()     { return pronoun; }
  int    getId()          { return id; }
  int    getAge()         { return age; }
  int    getWeight()      { return weight; }
  string getSound()       { return sound; }
  string getDisposition() { return disposition; }
  string getTraining()    { return training; }
  string getFood()        { return food; }
};

int main( int argc, char *argv[] )
{
  animal *animalRef[] = { new dog("Spot", "Her", 5, 12, 12345), 
			  new cat("Tom", "His", 7, 21, 54321) };

  for (unsigned idx = 0; idx < (sizeof(animalRef) / sizeof(animal *)); idx++) {
    cout << animalRef[idx]->getName() << " is a " << 
      animalRef[idx]->getAnimal() << '\n';
    cout << animalRef[idx]->getPronoun() << " id is " << 
      animalRef[idx]->getId() << '\n';
    cout << animalRef[idx]->getPronoun() << " age is " << 
      animalRef[idx]->getAge() << '\n';
    cout << animalRef[idx]->getPronoun() << " weight is " << 
      animalRef[idx]->getWeight() << '\n';
    cout << animalRef[idx]->getPronoun() << " sound is " << 
      animalRef[idx]->getSound() << '\n';
    cout << animalRef[idx]->getPronoun() << " disposition is " << 
      animalRef[idx]->getDisposition() << '\n';
    cout << animalRef[idx]->getPronoun() << " food is " << 
      animalRef[idx]->getFood() << '\n';
    cout << animalRef[idx]->getPronoun() << " training is " << 
      animalRef[idx]->getTraining() << '\n';
    cout << '\n';
  }
  return 0;
}
