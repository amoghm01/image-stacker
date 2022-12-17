//Amogh Manjunath
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

//constant max values
const int MAX_HEIGHT = 1000;
const int MAX_WIDTH = 1000;

int main(){

  ifstream fin;   //input file
	ofstream fout;  //output file

  //variable declarations
  string fileContents, fileName;
  string newFile;
  int h, w;
  int max;
  string folderName;
  int choice;
  int redValue, greenValue, blueValue;
  int avgRed, avgGreen, avgBlue;

  //menu 
  cout << "Welcome to the Image Stacker!\nChoose which set of images you would like to analyze:\n";
  cout << "1. cone_nebula\n";
  cout << "2. n44f\n";
  cout << "3. orion\n";
  cout << "4. wfc3_uvis\n";
  cout << "Enter the number of your choice: ";
  cin >> choice;

  //prompts user to enter valid choice if out of bounds
  while(choice < 1 || choice  > 4){
    cout << "\nThat is not a valid choice.\nEnter the number of your choice: ";
    cin >> choice;
  }

  //assigns folder name based on choice
  if(choice == 1){
    folderName = "cone_nebula";
  } else if(choice == 2){
    folderName = "n44f";
  } else if(choice == 3){
    folderName = "orion";
  } else if(choice == 4){
    folderName = "wfc3_uvis";
  } else {
    cout << "Invalid.";
    exit(2);
  }
  
  //counter variables
  int widthCounter = 0;
  int heightCounter = 0;

  //sum array initializations
  int sumRed[MAX_HEIGHT][MAX_WIDTH] = {{0}};
  int sumGreen[MAX_HEIGHT][MAX_WIDTH] = {{0}};
  int sumBlue[MAX_HEIGHT][MAX_WIDTH] = {{0}};

  for(int i = 1; i <= 10; i++){
    //concatenates new file name
    fileName = folderName + "_" + to_string(i) + ".ppm";
    fin.open(fileName); //open file
    cout << "Processing " << fileName << endl;  

    //read in header info from ppm files 
    fin >> fileContents;
    fin >> h;
    fin >> w;
    fin >> max;

    //declare arrays for r g b values
    int r[h][w];
    int g[h][w];
    int b[h][w];

    //nested for loops to iterate through each index of the 2 dimensional arrays
    for (heightCounter = 0; heightCounter < h; heightCounter++){  //iterating height

      for (widthCounter = 0; widthCounter < w; widthCounter++){ //iterating width

        //read in each r g b value from file
        fin >> redValue >> greenValue >> blueValue;
        
        //assign each value to respective array indices
        r[heightCounter][widthCounter] = redValue;
        g[heightCounter][widthCounter] = greenValue;
        b[heightCounter][widthCounter] = blueValue;

        //add each to sum arrays
        sumRed[heightCounter][widthCounter] += r[heightCounter][widthCounter];
        sumGreen[heightCounter][widthCounter] += g[heightCounter][widthCounter];
        sumBlue[heightCounter][widthCounter] += b[heightCounter][widthCounter];
        
      }
    }
    //close each file
    fin.close();
  }

  //user enters new file name
  cout << "Enter filename to save fixed image: ";
  cin >> newFile;

  //open new image file
  fout.open(newFile);

  //print header contents to file
  fout << fileContents << endl;
  fout << h << " ";
  fout << w << endl;
  fout << max << endl;

  //nested for loop to calculate average and print out each rgb value to file
  for (heightCounter = 0; heightCounter < h; heightCounter++){
    for (widthCounter = 0; widthCounter < w; widthCounter++){
      
      //calculates average of each value for 10 images
      avgRed = sumRed[heightCounter][widthCounter]/10;
      avgGreen = sumGreen[heightCounter][widthCounter]/10;
      avgBlue = sumBlue[heightCounter][widthCounter]/10;

      //prints to file
      fout << avgRed << " " << avgGreen << " " << avgBlue << endl;

    }
  }

  //close new image file
  fout.close();
}

