#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef deque<string> Prefix;
map<Prefix, vector<string> > statetab; // prefix -> suffixes

enum {
    NPREF  = 2,    /* number of prefix words */
    NHASH  = 4093, /* size of state hash table array */
    MAXGEN = 10000 /* maximum words generated */
};

const string NONWORD = "\n"; /* cannot appear as a real word */

/* add: add word to suffix list, updates prefix*/
void add(Prefix& prefix, const string& s)
{
    if(prefix.size() == NPREF){
        statetab[prefix].push_back(s);
        prefix.pop_front();
    }
    prefix.push_back(s);
}

/* build: read input, build prefix table */
void build(Prefix& prefix, istream& in)
{
    string buf;

    while(in >> buf)
        add(prefix, buf);
}

/* generate: produce output, one word per line */
void generate(int nwords)
{
    Prefix prefix;

    for(int i=0; i< NPREF; i++) /* reset initial prefix */
        add(prefix, NONWORD);

    for(int i=0; i< nwords; i++) {
         vector<string>& suf = statetab[prefix];
         const string& w = suf[rand() % suf.size()];

         if(w == NONWORD)
            break;
        cout << w << "\n";
        prefix.pop_front(); // advance
        prefix.push_back(w);
    }
}

int main(int argc, char *argv[])
{
    int nwords = MAXGEN;
    Prefix prefix; /* current input prefix */

    for(int i=0; i< NPREF; i++) /* set up initial prefix */
        add(prefix, NONWORD);

    build(prefix, cin);
    add(prefix, NONWORD);

    generate(nwords);
    return 0;
}
