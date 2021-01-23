#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Csv { // read and parse comma-separated values
    /* sample input "LU",86.25,"11/4/1998","2:19PM",+4.0625 */
public:
    Csv(istream &fin = cin, string sep = ",") : fin(cin), fieldsep(sep) {}

    int getline(string &);

    string getfield(int n);

    int getnfield() const { return nfield; }

private:
    istream &fin; // input file pointer
    string line;  // input line
    vector<string> field; // field strings
    int nfield;   // number of fields
    string fieldsep; // separator characters

    int split();

    int endofline(char);

    int advplain(const string &s, string &fld, int);

    int advquoted(const string &s, string &fld, int);

};
