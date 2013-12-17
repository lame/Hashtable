#ifndef HASHTABLE_CPP
#define HASHTABLE_CPP

#include "hashtable.h"

static const unsigned int default_capacity = 11;

namespace cop4530{

  string HashTable::encrypt(string passwd){
    char salt[] = "$1$........";
    string key = passwd;

    char * password = new char [100];
    //char password[100];
    strcpy ( password, crypt(key.c_str(), salt));
    string encrypted = password;
    encrypted = encrypted.substr(12,88);

    return encrypted;
  }

  bool HashTable::changePasswd(string user, string passwd ,string newPass){    
    pair<string, string> x;
    passwd = encrypt(passwd);
    newPass = encrypt(newPass);
    x = make_pair(user, passwd);
    int index = Index(user);
    const list<pair<string, string> > & whichList = bucketVector[Index(user)];
    if(find(whichList.begin(), whichList.end(), x) != whichList.end()){
      x.second = encrypt(newPass);
      return true;
    }
    else
      return false;
  }

  void HashTable::summary(){
    for(int i = 0; i < bucketVector.size(); ++i){
      list < pair < string, string> > & theList = bucketVector[i];
      list < pair < string, string> >::iterator itr = theList.begin();
      for(itr; itr != theList.end(); ++itr){
        cout << "\nV[" << i << "]" << "\t";
        cout << itr->first << ":" << itr->second;
      }
    }
  }

  void HashTable::writeToFile(string fileName){
    ofstream myFile (fileName.c_str());
    if(myFile.is_open()){
      for(int i = 0; i < bucketVector.size(); ++i){
        list < pair < string, string> > & theList = bucketVector[i];
        list < pair < string, string> >::iterator itr = theList.begin();
        for(itr; itr != theList.end(); ++itr){
          myFile << itr->first << ":" << itr->second;
        }
      }
      myFile.close();
    }
  }

  HashTable::~HashTable(){
    for(int i = 0; i < bucketVector.size(); ++i)  //might have to replace bucket vector
      bucketVector[i].clear();
  }

  bool HashTable::contains(string userName) {
    const list<pair<string, string> > & whichList = bucketVector[Index(userName)];       //  
    list<pair<string, string > >::iterator itr = bucketVector[Index(userName)].begin();
    list<pair<string, string > >::iterator endItr = bucketVector[Index(userName)].end();

    for(itr; itr!=endItr; ++itr){
      if(itr->first == userName)
        return true;
    } 
    return false;
  }

  bool HashTable::remove(string userName){
    list<pair<string, string> > & whichList = bucketVector[Index(userName)];       //  
    list<pair<string, string > >::iterator itr = bucketVector[Index(userName)].begin();
    list<pair<string, string > >::iterator endItr = bucketVector[Index(userName)].end();

    for(itr; itr!=endItr; ++itr){
      if(itr->first == userName){
        whichList.erase(itr);
        --currentSize;
        --count;
        return true;
      }
    }
    
    return false;
  }

  bool HashTable::insert(pair<string, string> & x){
    //list.push_back x
    list<pair<string, string> > & whichList = bucketVector[Index(x.first)];
    if(find(whichList.begin(), whichList.end(), x) != whichList.end())
      return false;
    whichList.push_back(x);
    ++count;
    return true;
  }

  //Returns the bucket index where the pair<string, string> should be inserted
  unsigned int HashTable::Index (const string & key){
    return hash_function(key) % bucketVector.capacity();
  }
  
  //Returns the hashed index
  unsigned int HashTable::hash_function (const string & s){
    unsigned int i;
    unsigned long bigval = s[0];
    for (i = 1; i < s.size(); ++i)
      bigval = ((bigval & 65535) * 18000) + (bigval >> 16) + s[i];
    bigval = ((bigval & 65535) * 18000) + (bigval >> 16);
    return bigval & 65535;
    
  }
  
  // returns largest prime number <= n or zero if input is too large
  // This is likely to be more efficient than prime_above(), because
  // it only needs a vector of size n
  unsigned int HashTable::prime_below (unsigned int n)
  {
    if (n > max_prime){
	   std::cerr << "** input too large for prime_below()\n";
	   return 0;
    }
    if (n == max_prime){
	   return max_prime;
    }
    if (n <= 1){
	   return 0;
    }
      
    // now: 2 <= n < max_prime
    vector <unsigned int> v (n + 1);
    setPrimes(v);
    while (n > 2){
	   if (v[n] == 1)
	     return n;
	   --n;
    }
    return 2;
  }
  
  //Sets all prime number indexes to 1. Called by method prime_below(n) 
  void HashTable::setPrimes(vector<unsigned int>& vprimes){
    int root;
    int i = 0;
    int j = 0;
    
    vprimes[0] = 0;
    vprimes[1] = 0;
    int n = vprimes.capacity();
    
    for (i = 2; i < n; ++i)
      vprimes[i] = 1;
    
    for( i = 2; i*i < n; ++i){
	   if (vprimes[i] == 1)
	   for(j = i + i ; j < n; j += i)
	    vprimes[j] = 0;
    }
  }
  
}
#endif

