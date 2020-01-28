
#include <iostream>
#include "bmplib.h"
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream> 
#define PATH_IN "./Pictures/"
#define PATH_OUT "./Outfiles/"
using namespace std;

void showMenu() {
   cout << "0: Exit" << endl;
   cout << "1. Flip 90 degrees clockwise" << endl;
   cout << "2. Flip upside down" << endl;
   cout << "3. Mirror" << endl;
   cout << "4. Greyscale" << endl;
   cout << "5. Copy" << endl;
   cout << "6. Color Inversion" << endl;
   cout << "7. Zoom" << endl;
}

vector<string> findBMP() {
   DIR *dir;
   struct dirent *ent;
   char targetFolderAddr[] = "./";
   vector <string> files;
       
   if ((dir = opendir(PATH_IN)) != NULL) {
      while ((ent = readdir(dir)) != NULL) {
         string str(ent->d_name);
         int idx = str.find('.');
         string ext = str.substr(idx+1);
         if (ext == "bmp") {
            cout << str << endl;
            files.push_back(str);
         }
         else {
            continue;
         }
      }
      closedir(dir);
   }
   else {
      perror ("No directory!");
   } 
   
   return files; 
}

int main() {
   
   int option;
   unsigned char src[SIZE][SIZE][RGB];
   unsigned char dest[SIZE][SIZE][RGB];
   vector<string> files = findBMP();
   
   while(1) {
      showMenu();
      cout << "Select an option: ";
      cin >> option;
      switch(option) {
         case 0:
            cout << "Exiting" << endl;
            return 0;
         case 1:
            cout << "Flip 90 degrees clockwise" << endl;
            for (int f=0; f<files.size(); f++) {
               string path = PATH_IN + files[f];
               string path2 = PATH_OUT + files[f];
               const char* pathIn = path.c_str();
               const char* pathOut = path2.c_str();
               ifstream inFile;
               inFile.open(pathIn); 
               readRGBBMP(pathIn, src);
               for (int i=0; i<SIZE; i++) {
                  for (int j=0; j<SIZE; j++) {
                     for (int c=0; c<3; c++) {
                        dest[i][j][c] = src[SIZE-j][i][c];
                     }
                  }
               }
               ofstream outFile;
               outFile.open(pathOut);
               writeRGBBMP(pathOut, dest);
               //showRGBBMP(dest);
               outFile.close();
               inFile.close();   
            }         
            break;
         case 2:
            cout << "Flip upside down" << endl;
            for (int f=0; f<files.size(); f++) {
               string path = PATH_IN + files[f];
               string path2 = PATH_OUT + files[f];
               const char* pathIn = path.c_str();
               const char* pathOut = path2.c_str();
               ifstream inFile;
               inFile.open(pathIn); 
               readRGBBMP(pathIn, src);
               for (int i=0; i<SIZE; i++) {
                  for (int j=0; j<SIZE; j++) {
                     for (int c=0; c<3; c++) {
                        dest[i][j][c] = src[255-i][j][c];
                     }
                  }
               }
               ofstream outFile;
               outFile.open(pathOut);
               writeRGBBMP(pathOut, dest);
               //showRGBBMP(dest);
               outFile.close();
               inFile.close();   
            }         
            break; 
         case 3:
            cout << "MIRROR" << endl;
            for (int f=0; f<files.size(); f++) {
               string path = PATH_IN + files[f];
               string path2 = PATH_OUT + files[f];
               const char* pathIn = path.c_str();
               const char* pathOut = path2.c_str();
               ifstream inFile;
               inFile.open(pathIn); 
               readRGBBMP(pathIn, src);
               for (int i=0; i<SIZE; i++) {
                  for (int j=0; j<SIZE; j++) {
                     for (int c=0; c<3; c++) {
                        dest[i][j][c] = src[i][255-j][c];
                     }
                  }
               }
               ofstream outFile;
               outFile.open(pathOut);
               writeRGBBMP(pathOut, dest);
               //showRGBBMP(dest);
               outFile.close();
               inFile.close();   
            }    
            break;
         case 4:
            cout << "Greyscale" << endl;
            unsigned char gsrc[SIZE][SIZE][RGB];
            unsigned char gdest[SIZE][SIZE];
            for (int f=0; f<files.size(); f++) {
               string path = PATH_IN + files[f];
               string path2 = PATH_OUT + files[f];
               const char* pathIn = path.c_str();
               const char* pathOut = path2.c_str();
               ifstream inFile;
               inFile.open(pathIn); 
               readRGBBMP(pathIn, gsrc);
               for (int i=0; i<SIZE; i++) {
                  for (int j=0; j<SIZE; j++) {
                     unsigned char r = gsrc[i][j][0];
                     unsigned char g = gsrc[i][j][1];
                     unsigned char b = gsrc[i][j][2];
                     gdest[i][j] = (unsigned char)(.299*r + .587*g + .114*b);
                  }
               }
               ofstream outFile;
               outFile.open(pathOut);
               writeGSBMP(pathOut, gdest);
               //showGSBMP(gdest);
               outFile.close();
               inFile.close();   
            }    
            break;
         case 5:
            cout << "COPY" << endl;
            break;
         case 6:
            cout << "Color Inversion" << endl;
            for (int f=0; f<files.size(); f++) {
               string path = PATH_IN + files[f];
               string path2 = PATH_OUT + files[f];
               const char* pathIn = path.c_str();
               const char* pathOut = path2.c_str();
               ifstream inFile;
               inFile.open(pathIn); 
               readRGBBMP(pathIn, src);
               for (int i=0; i<SIZE; i++) {
                  for (int j=0; j<SIZE; j++) {
                     for (int c=0; c<3; c++) {
                        dest[i][j][c] = 255-src[i][j][c];
                     }
                  }
               }
               ofstream outFile;
               outFile.open(pathOut);
               writeRGBBMP(pathOut, dest);
               //showRGBBMP(dest);
               outFile.close();
               inFile.close();   
            }    
            break;
         case 7: 
            cout << "Zoom" << endl;
            for (int f=0; f<files.size(); f++) {
               string path = PATH_IN + files[f];
               string path2 = PATH_OUT + files[f];
               const char* pathIn = path.c_str();
               const char* pathOut = path2.c_str();
               ifstream inFile;
               inFile.open(pathIn); 
               readRGBBMP(pathIn, src);
               for(int i=0; i < SIZE; i++){
                  for(int j=0; j < SIZE; j++){
                     for (int c=0; c<3; c++) {
                     dest[i][j][c] = src[SIZE/4 + i/2][SIZE/4 + j/2][c];
                     }
                  }
               }
               ofstream outFile;
               outFile.open(pathOut);
               writeRGBBMP(pathOut, dest);
               //showRGBBMP(dest);
               outFile.close();
               inFile.close();   
            }   
            break;
         default:
            cout << "Not an option" << endl;
            break;
      }
   }
   
 return 0;

}
            
