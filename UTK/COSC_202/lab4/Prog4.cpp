//Nia Maheshwari
//COSC 202
//Professor Adam W. Disney

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

typedef unsigned long ulong;

struct credentials {
  void set_salt(string &);
  void set_hash(string &);

  void operator=(const credentials &);
  bool operator==(const credentials &);

  string salt;
  ulong password_hash;
};

void credentials::set_salt(string &username) {
  salt = "g0b1g0rAnge";

	//garbling the original salt based on the incoming username
	for (size_t i = 0; i < salt.size(); i++) {

		salt[i] += (username[i%username.size()] & 0x7);
		if (isalnum(salt[i]) == 0) {
			salt[i] = '*';
		} 
	}
}

void credentials::set_hash(string &password) {

	//salting the password (appending)
	password = password.append(salt);

    ulong hashed_password = 0;
    int len = password.length();

    //hashing the salted password using cyclic shift algorithm
    for(int i = 0; i < len; i++) {

		hashed_password = (hashed_password << 5) | (hashed_password >> 27);
		hashed_password += (password[i]);
    }

    password_hash = hashed_password;
}

void credentials::operator=(const credentials& cred) {
    
	//copying the inputted credentials object into member variables
    password_hash = cred.password_hash;
    salt = cred.salt;
}

bool credentials::operator==(const credentials& cred) {

    //returns true if the compared credential structs have identical password hash values
    if (password_hash == cred.password_hash) 
        return true;
    else
        return false;
}

istream &operator>>(istream &in, credentials &login) {

    //writes a salt and password hash to a file stream
    //by extracting the information from inputted credentials object
    in >> login.salt >> hex >> login.password_hash;

    return in;
}

ostream &operator<<(ostream &out, const credentials &login) {
  
    //reads in a credentials object 
    //outputs salt and password individually (hash is in hex form)
    out << setw(10) << login.salt << " " << hex << login.password_hash;

  return out;
}

typedef unordered_map<string,credentials> hashtable;

void printVerbose(hashtable &H) { //helper function to declutter the code for -verbose 
   
    //calculate certain table stats
    int tableCapacity = H.bucket_count();
    float tableLoad = H.load_factor();
    int tableSize = H.size();
    
    //print out table stats in correct format
    cout << "** S = " << right << setw(4) << setfill(' ') << tableSize << " N = " << setw(4) << tableCapacity << " : load = " << fixed << setprecision(2) << tableLoad << endl;
}


void write_hashtable(hashtable &H, bool verbose) { //used when we have a new username/credentials coming in

    credentials userCreds;
    ofstream passwordFile;
    string username;
    string password;

    //read username, password pairs from stdin
    while (cin >> username >> password) { //for each line of the file with usernames and passwords

		userCreds.set_salt(username); //creating salt
        userCreds.set_hash(password); //creating password_hash

        H.insert(make_pair(username, userCreds)); //inserting username creds into the hashtable
    
        if (verbose) { //toggles -verbose feature
			printVerbose(H);           
        }
    }

    //writing to the passwds file 
    passwordFile.open("passwd.txt");

    if (!passwordFile) { //only proceed if the file opened properly
        cerr << "write_hashtable: error opening passwd.txt." << endl;
        exit(1);
    }

    if (passwordFile) { 
        hashtable::iterator it;

        for (it = H.begin(); it != H.end(); it++) {
            passwordFile << left << setw(10) << it->first << " " << it->second << endl; //writing the contents of the hashtable to the file

        }
    }

    passwordFile.close(); 
}

void read_hashtable(hashtable &H, bool verbose) { //used to compare incoming password/usernames with the set passwords/usernames

    ifstream passwordFile;
    passwordFile.open("passwd.txt"); //is this the correct file to open? Shouldn't we be taking in cin from a different file than the one that has the same content as the hashtable?
    string username;
    string password;
    credentials userCreds;
    hashtable::iterator it;

    if (!passwordFile) { //exit if the file did not open properly
        cerr << "write_hashtable: error opening passwd.txt." << endl;
        exit(1);
    }

    if (passwordFile) { //only proceed if the file opened properly

		while (passwordFile >> username >> userCreds) { //iterating through the lines of the file
			H.insert(make_pair(username, userCreds)); //inserting username creds into the hashtable from the passwd.txt
			
			if (verbose) { //toggles -verbose feature
				printVerbose(H);
			}
		}

        passwordFile.close();
	}
    
} 

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------ Main  --------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]) {
    
    enum {neither, create, check} checkerFlag = neither; //custom flag to determine program's mode
    bool verbose = false;
    bool exit = false;
	bool exit1 = false;
    float newLoad;
    string password;
    string username;
    hashtable H;
    credentials userCreds;
    H.max_load_factor(1.0);

    if (argc <= 1 || argc > 6) {
		exit = true;
    }

    if (!exit) {

		int c = 0;
		while (c < argc) {

			if ((strcmp(argv[c], "-create")) == 0 || (strcmp(argv[c], "-check")) == 0) { //ensuring that either -create or -check will be toggled
				exit1 = false;
				break;
			} 

			else {
				exit1 = true;
			 }

			 c++;
		}
	}
		
    if (exit || exit1) { //print error message and exit main
        cerr << "usage: " << argv[0] << " -create|check [-load Z] [-verbose] < logins.txt" << endl;
        return 1;
	}

    if (!exit && !exit1) { //commandline arg parsing

        for (int v = 0; v < argc; v++) { 

             if ((strcmp(argv[v], "-create")) == 0) { //checking for -create
                 checkerFlag = create;

				for (int v = 0; v < argc; v++) { 

					if ((strcmp(argv[v], "-verbose")) == 0) {
						verbose = true;
					}

					if ((strcmp(argv[v], "-load")) == 0) { //stuff for load here
						newLoad = (float)(strtod((argv[v+1]), NULL)); //converting the char* right after '-load' to a floating point
						H.max_load_factor(newLoad);
					}
				}
			 }


			 else if ((strcmp(argv[v], "-check")) == 0) { //checking for -check
                 checkerFlag = check;

				for (int v = 0; v < argc; v++) {

					if ((strcmp(argv[v], "-verbose")) == 0) {
						verbose = true;
					}

					if ((strcmp(argv[v], "-load")) == 0) { //stuff for load here
						newLoad = (float)(strtod((argv[v+1]), NULL)); //converting the char* right after '-load' to a floating point
						H.max_load_factor(newLoad);
					}
				}
			 }

         }
    }


    if (checkerFlag == create) { //-create mode

        if (verbose) {
           cout << "** S = " << right << setw(4) << setfill(' ') << "0" << " N = " << setw(4) << "1" << " : load = " << "0.00" << endl;
        }

        write_hashtable(H, verbose); //creating the hashtable
           
        if (verbose) {//toggles verbose
            cout << endl;

            for (size_t i = 0; i < H.bucket_count(); i++) {//parsing each bucket in the hashtable
               cout << right << setw(6) << setfill(' ') << i << setw(5) << setfill(' ') << H.bucket_size(i) << setw(1);

               for (auto bucketParser = H.begin(i); bucketParser != H.end(i); ++bucketParser) { //parsing each element in the bucket 
                    cout << " " << bucketParser->first << setw(1);
               }

               cout << endl;
		    } 

			cout << endl;
        }

    }
    

    if (checkerFlag == check) {//-check mode

		if (verbose) {
			cout << "** S = " << right << setw(4) << setfill(' ') << "0" << " N = " << setw(4) << "1" << " : load = " << "0.00" << endl;
		}

        read_hashtable(H, verbose);

		if (verbose) { //toggles verbose
           cout << endl;

            for (size_t i = 0; i < H.bucket_count(); i++) {
               cout << right << setw(6) << setfill(' ') << i << setw(5) << setfill(' ') << H.bucket_size(i) << setw(1);

               for (auto bucketParser = H.begin(i); bucketParser != H.end(i); ++bucketParser) {
                    cout << " " << bucketParser->first << setw(1);
               }

               cout << endl;
		   } 

			cout << endl;
		}

        while (cin >> username >> password) { //logic for checking credentials begins here

            hashtable::iterator searchUsername = H.find(username);

            if (searchUsername != H.end()) { //if the username is valid, create the credentials for the username to compare
                userCreds.set_salt(username);
                userCreds.set_hash(password);

                if (userCreds == searchUsername->second) {
                    cout << left << setw(10) << username << " access granted" << endl; //if username and pwd match, allow access 
                }

                else {
                    cout << left << setw(10) << username << " bad password" << endl; //print that the pwd is not a match 
                } 
            }

            else {
                cout << left << setw(10) << username << " bad username" << endl; //if usernname does not exist
            } 
        }

    }


    return 0;
}


