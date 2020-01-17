//
// <<Arvinbayar Jamsranjav>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"

using namespace std;

// declaring my struct to store Movie Data
// ...
struct MovieData
{
    string name;
    int Data;
    int PubYear;
    int Ratings;
    int Num5Stars;
    int Num4Stars;
    int Num3Stars;
    int Num2Stars;
    int Num1Stars;
};

//
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}

// getting ratings for reviews file
// populating the struct
// ...
void InputReviews(string reviewsFilename, binarysearchtree<string, MovieData> &byName, binarysearchtree<int, MovieData> &byID)
{
    ifstream reviewsFile(reviewsFilename);
    int rid, reviews, movieID;
    int RatingsTotal = 0;  // counting reviews in the file
    string name;
    
    if(!reviewsFile.good()) {
        cout << "**Error:unable to open reviews file '" << reviewsFilename << "',exiting" << endl;
        return;
    }
    // reading first data from file which is ID
    reviewsFile >> rid;
    
    while (!reviewsFile.eof())
    {
        // reading next data which is Movie ID
        reviewsFile >> movieID;
        // reading next data which is reviews
        reviewsFile >> reviews;
        // find particular Movie then add all the ratings from the .txt file
        MovieData *data = byID.search(movieID);
        RatingsTotal++;  // count them
        
        if(reviews == 5) {
            ++(data->Num5Stars);
        }
        else if(reviews == 4) {
            ++(data->Num4Stars);
        }
        else if(reviews == 3) {
            ++(data->Num3Stars);
        }
        else if(reviews == 2) {
            ++(data->Num2Stars);
        }
        else if(reviews == 1) {
            ++(data->Num1Stars);
        }
        
        reviewsFile >> rid;  // go to the next line
    }
    cout << "Num reviews: " << RatingsTotal << endl;
}

//
// InputMovies
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
//
void InputMovies(string moviesFilename, binarysearchtree<string , MovieData> &byName, binarysearchtree<int, MovieData> &byID)
{
  ifstream moviesFile(moviesFilename);
  int      id, pubYear;
  string   name;
    
  int numOfMovies = 0;  // counting # of movies

  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

  while (!moviesFile.eof())
  {
    
    // we have more data, so input publication year and movie name:
    moviesFile >> pubYear;
    getline(moviesFile, name);  // movie name fills rest of input line:
      numOfMovies++;
    // trim potential whitespace from both ends of movie name:
    name = trim(name);
    
    // assign name,id and publicatin year to particular movie
    MovieData temp;
    temp.PubYear = pubYear;
    temp.name = name;
    temp.Data = id;
    //initialize # of ratings
    temp.Num5Stars = 0;
    temp.Num4Stars = 0;
    temp.Num3Stars = 0;
    temp.Num2Stars = 0;
    temp.Num1Stars = 0;
      
    // create 2 trees: 1. for searching with name
    //                 2. for searching with ID
    byName.insert(name, temp);
    byID.insert(id, temp);
      
    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
  }
    cout << "Num movies: " << numOfMovies << endl;
}

// function that chooses search by name or ID
// if its ID then covert string to int
// ...
int checkIDorName (string input, int &x) {
    unsigned int counter =0;
    unsigned int i;
    for (i=0; i < input.length(); i++) {
         if (isdigit(input[i])) {
             counter++;
             if(counter == input.length()) {
                 x = stoi(input);
                 return 1;
             }
         }
    }
    return 0;
}

//
// main
//
int main()
{
    string moviesFilename; // = "movies1.txt";
    string reviewsFilename; // = "reviews1.txt";
    // declaring 2 trees
    binarysearchtree<int, MovieData> bstMoviesByID;
    binarysearchtree<string, MovieData> bstMoviesByName;

    string movieString;
    string reviewString;

    cout << "movies file?> ";
    cin >> moviesFilename;

    cout << "reviews file?> ";
    cin >> reviewsFilename;

    string junk;
    getline(cin, junk);  // discard EOL following last input:

    InputMovies(moviesFilename, bstMoviesByName, bstMoviesByID);
    InputReviews(reviewsFilename, bstMoviesByName, bstMoviesByID);
    
    // printing size and heights of 2 trees
    // ...
    cout << "\nTree by movie id: size=" << bstMoviesByID.size() << ", "
    << "height=" << bstMoviesByID.height() << endl;
    cout << "Tree by movie name: size=" << bstMoviesByName.size() << ", "
    << "height=" << bstMoviesByName.height() << endl;
    
    
    string input;
    while (1) {
        int x;  // declared new int to save a value of converted value from string
        cout << "\nEnter a movie id or name (or # to quit)> ";
        getline(cin,input);
        // condition to stop while loop
        if(input == "#"){
            break;
        }
        // searching the movie with ID
        if (checkIDorName(input, x) == 1) {
            MovieData *a = bstMoviesByID.search(x);
            // printing that movie is not found
            if(bstMoviesByID.search(x) == nullptr) {
                cout << "not found...\n";
                continue;
            }
            // finding average rating
            double sum = 5*a->Num5Stars + 4*a->Num4Stars + 3*a->Num3Stars + 2*a->Num2Stars + 1*a->Num1Stars;
            double div = a->Num5Stars + a->Num4Stars + a->Num3Stars + a->Num2Stars + a->Num1Stars;
            double avg = (sum / div);
            // if there is no data equal avg to 0
            if (sum == 0) {
                avg = 0.0;
            }
            // print final info of the movie
            cout << "Movie ID: " << a->Data << endl;
            cout << "Movie Name: " << a->name << endl;
            cout << "Avg rating: " << avg <<endl;
            cout << "5 stars: " << a->Num5Stars << endl;
            cout << "4 stars: " << a->Num4Stars << endl;
            cout << "3 stars: " << a->Num3Stars << endl;
            cout << "2 stars: " << a->Num2Stars << endl;
            cout << "1 star: " << a->Num1Stars << endl;

        }
        // searching the movie with Name
        else {
            if(bstMoviesByName.search(input) == nullptr) {
                cout << "not found...\n";
                continue;
            }
            // look for movie with name
            // use that movie's ID to get all the info
            // about ratings
            MovieData *b = bstMoviesByName.search(input);
            int IDtemp = b->Data;
            MovieData *a = bstMoviesByID.search(IDtemp);
           
            // finding average rating
            double sum = 5*a->Num5Stars + 4*a->Num4Stars + 3*a->Num3Stars + 2*a->Num2Stars + 1*a->Num1Stars;
            double div = a->Num5Stars + a->Num4Stars + a->Num3Stars + a->Num2Stars + a->Num1Stars;
            double avg = (sum / div);
            
            if (sum == 0) {
                avg = 0.0;
            }
            // print final info of the movie
            cout << "Movie ID: " << a->Data << endl;
            cout << "Movie Name: " << a->name << endl;
            cout << "Avg rating: " << avg <<endl;
            cout << "5 stars: " << a->Num5Stars << endl;
            cout << "4 stars: " << a->Num4Stars << endl;
            cout << "3 stars: " << a->Num3Stars << endl;
            cout << "2 stars: " << a->Num2Stars << endl;
            cout << "1 star: " << a->Num1Stars << endl;
        }
    }
    
  // done:
  return 0;
}

