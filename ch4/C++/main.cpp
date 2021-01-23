#include "csv.h"
#include <iostream>

int main() {

    string line;
    Csv csv;
    while (csv.getline(line) != 0) {
        cout << "line = '" << line << endl;
        for (int i = 0; i < csv.getnfield(); i++)
            cout << "fiel[" << i << "] = '"
                 << csv.getfield(i) << "'" << endl;
    }
    return 0;
}
