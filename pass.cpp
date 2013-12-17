#include "hashtable.h"

using namespace cop4530;
using namespace std;

int main(){
 
  ifstream myfile;
  ofstream ofile; 
  char infile[80];
  char outfile[80];
  string choice;
  int num;
  string userName;
  string unhashedPasswd;
  string newUnhashedPasswd;
  string garbage;    
  string filename;
  pair <string, string> add;
  cout << "Please enter desired table size: ";
  cin >> num;
  
  HashTable myHash(num);

do{
  cout << endl << endl;
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit Program" << endl;
  cout << "Enter Choice: ";
  cin >> choice;

  if(choice == "x"){

  }
 
  if(choice == "l"){

    cout << "Please enter the name of the input file." << endl;
    cout << "Filename: ";
    getline(cin, filename);    
    myfile.open(filename.c_str());
    while(!myfile.is_open()){
      cout << "Please enter the name of the input file." << endl;
      cout << "Filename: ";
      getline(cin, filename);
      myfile.open(filename.c_str());
    }
  while(myfile.good()){
    getline(myfile, userName, ':');
    getline(myfile, unhashedPasswd);
    unhashedPasswd =myHash.encrypt(unhashedPasswd);
    add = make_pair(userName, unhashedPasswd);
    myHash.insert(add);
  }

  }
  if(choice == "a"){
    cout << "\nUser Name: ";
    cin >> userName;
    cout << "\nPassword: ";
    cin >> unhashedPasswd;
    unhashedPasswd =myHash.encrypt(unhashedPasswd);
    add = make_pair(userName, unhashedPasswd);
    if(myHash.insert(add))
      cout << "\nuser " << userName << " added.";

  }
  if(choice == "r"){
    cout << "\nUser Name: ";
    cin >> userName;
    if(myHash.remove(userName))
      cout << "\nUser " << userName << " added";
    else
      cout << "\nUser " << userName << " not added";
  }
  if(choice == "c"){
    cout << "\nUser Name: ";
    cin >> userName;
    cout << "\nOld Password: ";
    cin >> unhashedPasswd;
    cout << "\nNew Password: ";
    cin >> newUnhashedPasswd;
    myHash.changePasswd(userName, unhashedPasswd, newUnhashedPasswd);
  }
  if(choice == "f"){
    cout << "\nUser Name: ";
    cin >> userName;
    if(myHash.contains(userName))
      cout << "\nHash Table Contains " << userName;
    else
      cout << "\nHash Table Does Not Contain " << userName;
  }
  if(choice == "d"){
     myHash.summary();
  }
  if(choice == "s"){
    cout << endl <<myHash.getSize();
  }
  if(choice == "w"){
    cout << "\nFile Name: ";
    cin >> filename;
    myHash.writeToFile(filename);
  }

}
while(choice != "x");



  return 0;
}