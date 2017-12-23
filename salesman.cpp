#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int n = 50;

struct Point{
  double xval;
  double yval;
  int num;
  Point(double x, double y, int n) {xval = x; yval = y; num = n;}
  Point() {xval = 0; yval = 0; num = 0;}
};

double findDist(Point *p1, Point *p2) {
  double dx = p1->xval - p2->xval;
  double dy = p1->yval - p2->yval;
  return sqrt(dx*dx + dy*dy);}

double tourDistance(Point array[n]){
  double total = 0;
  for (int i = 0; i < n; i++){
    if (i == n-1){total = total + findDist(&array[i], &array[0]);}
    else {total = total + findDist(&array[i], &array[i+1]);}
  }
  return total;
}

void reverseSection(Point *array, int edge1, int edge2){

  while (edge1 < edge2){
    swap(array[edge1], array[edge2]);
    edge1 = edge1 + 1;
    edge2 = edge2 - 1;
  }
  return;
}

int *saveArray(Point *copyArray){
  int *finalTour = new int [50];
  for (int i = 0; i < n; i++){
    finalTour[i] = copyArray[i].num;
  }
  return finalTour;
}

void printTour(Point *array){
  for (int i = 0; i < n; i++){
    cout << array[i].num << " ";
  }
  return;
}

void printInts(int *tour){
  for (int i = 0; i < n; i++){
    cout << tour[i] << " ";
  }
  return;
}

int main() {
  Point array[n];
  double x, y;
  ifstream tourPoints("tsp_points.txt");

  for (int i = 0; i < n; i++){
    tourPoints >> x >> y;
    array[i] = Point(x, y, i);
  }
//  cout << endl;
  double shortest;
  double possibleShortest;
  double absoluteShortest = tourDistance(array);

  int *finalTour;
//  printTour(array);
  cout << endl;
  for (int i = 0; i < 100; i++){

    for (int j = 1; j < n; j++){
      int rando = rand() % j;
      swap(array[j], array[rando]);
    }

    shortest = tourDistance(array);


    bool improvement = true;
    while (improvement){
      improvement = false;
      for (int j = 0; j < n-1; j++){
        for (int k = j + 1; k < n; k++){

          reverseSection(array, j, k);
          possibleShortest = tourDistance(array);

           if (possibleShortest < shortest){
             shortest = possibleShortest;
             improvement = true;
           }
           else {reverseSection(array, j, k);}
        }
      }
    }
    if (absoluteShortest > shortest) {
      absoluteShortest = shortest;
      finalTour = saveArray(array);
    }
  }
  cout << absoluteShortest << endl;
  printInts(finalTour);
  cout << endl;
  cout << endl;
  return 0;
}
