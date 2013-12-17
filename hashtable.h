#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <crypt.h>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <stdlib.h>
#include <algorithm>
#include <cstring>

using namespace std;

namespace cop4530
{

static const unsigned int max_prime = 64997;

class HashTable
  {
  private:
    int count;
    int currentSize;
    unsigned int Index (const string &);
    unsigned int hash_function   (const string& );
    unsigned int prime_below(unsigned int);
    void setPrimes(vector<unsigned int> &);
    vector < list < pair<string, string> > > bucketVector;
  
  public:
    HashTable () {bucketVector.resize(11); int currentSize = 0;}   //
    HashTable (size_t n) {bucketVector.resize(prime_below(n)); int currentSize = 0;}   //
  
    ~HashTable();   //
    
    int getSize() {return count;}

    bool contains(string userName);    //
    bool insert(pair<string, string> & x);            //
    bool remove(string userName);            //

    bool changePasswd(string user, string passwd, string newPass);
    void summary();
    void writeToFile(string fileName);

    string encrypt(string passwd);
  };
}

#endif
