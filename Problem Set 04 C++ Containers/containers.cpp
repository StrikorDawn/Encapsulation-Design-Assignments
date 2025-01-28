/*************************************************************
 * 1. Name:
 *      Mark Van Horn & Taden Marston
 * 2. Assignment Name:
 *      Practice 04: Contaiers
 * 3. Assignment Description:
 *      Work with a list and a vector
 * 4. What was the hardest part? Be as specific as possible.
 *      Using an iterator on the listToVectorBackwards method.
 *      Tripped us up a bit.
 * 5. How long did it take for you to complete the assignment?
 *      20 minutes
 **************************************************************/


#include "testContainers.h"
#include <string>
#include <list>
using namespace std;

list<string> arrayToList(string a[], int num)
{
   list<string> listOfStrings;
   for(int i = 0; i < num; ++i) {
      listOfStrings.push_back(a[i]);
   }
   return listOfStrings;
}

/*****************************
 * ARRAY TO LIST BACKWARDS
 *****************************/
list<string> arrayToListBackwards(string a[], int num)
{
   list<string> listOfStrings;
   for(int i = num - 1; i >= 0; --i) {
      listOfStrings.push_back(a[i]);
   }
   return listOfStrings;
}

/*****************************
 * LIST TO VECTOR
 *****************************/
vector<string> listToVector(const list<string> & l)
{
   vector<string> vectorOfStrings;
   for(const auto& num : l) {
      vectorOfStrings.push_back(num);
   }
   return vectorOfStrings;
}

/*****************************
 * LIST TO VECTOR BACKWARDS
 *****************************/
vector<string> listToVectorBackwards(const list<string>& l)
{
   vector<string> vectorOfStrings;
   for(auto it = l.rbegin(); it != l.rend(); ++it) {
      vectorOfStrings.push_back(*it);
   }
   return vectorOfStrings;
}

/*****************************
 * FIND ELEMENT IN VECTOR
 *****************************/
bool findElementInVector(const vector<string> & v, const string& element)
{
   for(const auto& item : v) {
      if(item == element) {
         return true;
      }
   }
   return false;
}

/*****************************
 * MAIN
 *****************************/
int main()
{
   TestCollection().run();
   return 0;
}
