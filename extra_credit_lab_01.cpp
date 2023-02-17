#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

int main(){
// getting file name from user and opening
char fileName[256];
std::cout << "Enter a file name: ";
std::cin >> fileName;
std::ifstream myfile; 
myfile.open(fileName);

//Check that the file works
if(myfile.fail()){
  std::cout << "Error, there is no file with that name. \n";
  return 1;
}


//making the 2d array
int pref[10][5];
int x, y, row = 10, col = 5;
for (x = 0; x < row; x++) {
    for (y = 0; y < col; y++) {
        myfile >> pref[x][y];
    }
}
myfile.close();


int sol[5] = {0,0,0,0,0};

// First for-loop iterates 1-5, to look for each programmer in department preferences
for(int prog = 1; prog<=5; prog++){
      bool flag = false;

    
    // Second for-loop looks through departmental preferences levels
    for(int dep_level = 0; dep_level < 5; dep_level++){
        
        // level count keeps track of how many departments have a preference, exists_pref array keeps track of which, bool flag  helps break the loop when a case is found
        int level_count = 0;
        int exists_pref[5] = {0,0,0,0,0};
        if (flag) continue;
        
        // Third for-loop specifies which department it is currently looking at
          for(int dep_pref = 0; dep_pref < 5; dep_pref++){
            
            
            // These conditionals check for matching preferences by adding to level count
            if (pref[dep_level][dep_pref] < prog && dep_level < 4 && sol[dep_pref] == 0){
              if (pref[dep_level+1][dep_pref] == prog){
                level_count++;
                exists_pref[dep_pref] = 1;
              }
            } 

            if(pref[dep_level][dep_pref] == prog && sol[dep_pref] == 0){
                level_count++;
                exists_pref[dep_pref] = 1;
              } 
          }

        // The easiest case, if only one dep has the current strongest pref, they win the programmer outright.
        if(level_count == 1){
          for(int winning_dep = 0; winning_dep < 4; winning_dep++){
            if(exists_pref[winning_dep] == 1){
              sol[winning_dep] = prog;
              flag = true;
              break;
            }
          }
        }

        // If more than one current strongest pref exists, check the Programmer's preferences for matching ones
        if(level_count > 1){
          for(int prog_pref = 5; prog_pref < 9; prog_pref++){
            int prog_strongest_choice = pref[prog_pref][prog-1];
            if(exists_pref[prog_strongest_choice -1] == 1){
              sol[prog_strongest_choice - 1] = prog;
              flag = true;
              break;
            }
          }
        }
    }
}

//Printing final results
for (int printer = 0; printer < 5; printer++){
  std::cout << "Department #" << printer+1 << " will get Programmer #" << sol[printer]<< "\n";
}

return 0;
}