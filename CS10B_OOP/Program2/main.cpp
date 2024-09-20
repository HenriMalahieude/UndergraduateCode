#include <iostream>
#include <string>

using namespace std;

const string monthLowerValues[12] = {
   "january",
   "february",
   "march",
   "april",
   "may",
   "june",
   "july",
   "august",
   "september",
   "october",
   "november",
   "december"
};

const string monthUpperValues[12] = {
   "January",
   "February",
   "March",
   "April",
   "May",
   "June",
   "July",
   "August",
   "September",
   "October",
   "November",
   "December"
};

class Date {
 private:
   unsigned day;
   unsigned month;
   string monthName;
   unsigned year;

 public:
   // creates the date January 1st, 2000.
   Date();


   /* parameterized constructor: month number, day, year 
       - e.g. (3, 1, 2010) will construct the date March 1st, 2010

       If any of the arguments are invalid (e.g. 15 for month or 32 for day)
       then the constructor will construct instead a valid Date as close
       as possible to the arguments provided - e.g. in above example,
       Date(15, 32, 2010), the Date would be corrected to Dec 31st, 2010.
       In case of such invalid input, the constructor will issue a console error message: 

       Invalid date values: Date corrected to 12/31/2010.
       (with a newline at the end).
   */
   Date(unsigned m, unsigned d, unsigned y);


   /* parameterized constructor: month name, day, year
      - e.g. (December, 15, 2012) will construct the date December 15th, 2012

       If the constructor is unable to recognize the string argument as a valid month name,
       then it will issue a console error message: 

       Invalid month name: the Date was set to 1/1/2000.
       (with a newline at the end).
 
       If the day argument is invalid for the given month (but the month name was valid),
       then the constructor will handle this error in the same manner as the other
       parameterized constructor. 

       This constructor will recognize both "december" and "December"
       as month name.
   */
   Date(const string &mn, unsigned d, unsigned y);


   /* Outputs to the console (cout) a Date exactly in the format "3/15/2012". 
      Does not output a newline at the end.
   */
   void printNumeric() const;


   /* Outputs to the console (cout) a Date exactly in the format "March 15, 2012".
      The first letter of the month name is upper case, and the month name is
      printed in full - January, not Jan, jan, or january. 
      Does not output a newline at the end.
   */
   void printAlpha() const;

 private:

   /* Returns true if the year passed in is a leap year, otherwise returns false.
   */
   bool isLeap(unsigned y) const;


   /* Returns number of days allowed in a given month
      -  e.g. daysPerMonth(9, 2000) returns 30.
      Calculates February's days for leap and non-leap years,
      thus, the reason year is also a parameter.
   */
   unsigned daysPerMonth(unsigned m, unsigned y) const;

   /* Returns the name of a given month
      - e.g. name(12) returns the string "December"
   */
   string name(unsigned m) const;

   /* Returns the number of a given named month
      - e.g. number("March") returns 3
   */
   unsigned number(const string &mn) const;
};


// Implement the Date member functions here
Date::Date(){
   this->day = 1;
   this->month = 1;
   this->year = 2000;
   this->monthName = Date::name(1);
}

Date::Date(unsigned m, unsigned d, unsigned y){
   bool corrected = false;

   unsigned month = m;
   if (month > 12){
      month = 12; 
      corrected = true;
   }
   if (month < 1){
      month = 1; 
      corrected = true;
   }

   unsigned max = Date::daysPerMonth(month, y);
   unsigned day = d;
   
   if (day > max){
      day = max;
      corrected = true;
   }
   if (day < 1){
      day = 1;
      corrected = true;
   }

   if(corrected){
      cout << "Invalid date values: Date corrected to " << month << "/" << day << "/" << y << "." << endl;
   }

   this->month = month;
   this->day = day;
   this->year = y;
   this->monthName = Date::name(month);
}

Date::Date(const string &mn, unsigned d, unsigned y){
   unsigned month = Date::number(mn);;

   if (month > 12 || month < 1){
      this->month = 1;
      this->day = 1;
      this->year = 2000;
      this->monthName = Date::name(1);
      cout << "Invalid month name: the Date was set to " << this->month << "/" << this->day << "/" << 2000 << "." << endl;
      return;
   }

   unsigned max = Date::daysPerMonth(month, y);
   unsigned day = d;
   
   if (day > max){
      day = max;
      cout << "Invalid date values: Date corrected to " << month << "/" << day << "/" << y << "." << endl;
   }
   if (day < 1){
      day = 1;
      cout << "Invalid date values: Date corrected to " << month << "/" << day << "/" << y << "." << endl;
   }

   this->month = month;
   this->monthName = Date::name(month);
   this->day = day;
   this->year = y;
}

void Date::printNumeric() const{
    cout << this->month << "/" << this->day << "/" << this->year;// << endl;
}

void Date::printAlpha() const{
   cout << Date::name(this->month) << " " << this->day << ", " << this->year;
}

unsigned Date::number(const string &mn) const{
   int month = 13;
   for (unsigned i = 0; i < 12; i++){
      if (monthUpperValues[i] == mn || monthLowerValues[i] == mn){
         month = i+1;
         break;
      }
   }

   return month;
}

string Date::name(unsigned m) const{
   return monthUpperValues[m-1];
}

bool Date::isLeap(unsigned y) const{
   bool standard = y % 4  == 0;
   bool against = y % 100 == 0;
   bool contra = y % 400 == 0;

   return contra || (standard && !against);
}

unsigned Date::daysPerMonth(unsigned m, unsigned y) const{
   unsigned max = 30;
   if ((m <= 7 && (m+1) % 2 == 0) || (m > 7 && m % 2 == 0)){
      max = 31;
   }

   if (m == 2){
      max = 28;
      if (Date::isLeap(y)){
         max = 29;
      }
   }

   return max;
}


// Don't change the code below this line.
// You may comment them out if you want to build your own test harness
// while in develope mode, but you will need these to pass tets in submit mode.

Date getDate();

int main() {
   //cout << "Bruh" << endl;
   
   Date testDate;
   testDate = getDate();
   cout << endl;
   cout << "Numeric: ";
   testDate.printNumeric();
   cout << endl;
   cout << "Alpha:   ";
   testDate.printAlpha();
   cout << endl;
   
   return 0;
}

Date getDate() {
   int choice;
   unsigned monthNumber, day, year;
   string monthName;

   cout << "Which Date constructor? (Enter 1, 2, or 3)" << endl
      << "1 - Month Number" << endl
      << "2 - Month Name" << endl
      << "3 - default" << endl;
   cin >> choice;
   cout << endl;

   if (choice == 1) {
      cout << "month number? ";
      cin >> monthNumber;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthNumber, day, year);
   } else if (choice == 2) {
      cout << "month name? ";
      cin >> monthName;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthName, day, year);
   } else {
      return Date();
   }
}
