#include <iostream>
#include <string>

using namespace std;


void flipString(string &s);

int main() {
   string line;
   cout << "Enter a sentence:" << endl;
   getline(cin, line);
   cout << endl;
   cout << line << endl;
   flipString(line);
   cout << line << endl;

   return 0;
}

//Implement the flipString function here
void flipString(string &s){
   if (s.size() <= 1){
      return;
   }else{
      string first = s.substr(0, 1);
      string last = s.substr(s.size()-1, 1);
      s = s.substr(1, s.size()-2);
      flipString(s);

      s = last + s + first;
      //s = s + first;
   }
}

