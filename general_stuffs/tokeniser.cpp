#include <bits/stdc++.h>
using namespace std;

/**Class to store each row of CSV data as its object*/
class CSV_Data{
    private:
        string data1;
        string data2;
    public:
        CSV_Data() : data1(NULL), data2(NULL) {}
        CSV_Data(string data1, string data2) : data1(data1), data2(data2) {}
};

/**Function to tokenise the string at the separator*/
vector<string> tokenise(string CSV_Line, char separator) {
    vector<string> tokens;
    string token;

    int start = -1, end = -1;

    start = CSV_Line.find_first_not_of(separator,0);

    do{
        end = CSV_Line.find_first_of(separator,start);
        if(start==CSV_Line.size() || start==end) break;

        if(end!=string::npos) token = CSV_Line.substr(start,end-start);
        else token = CSV_Line.substr(start, CSV_Line.size()-start);

        tokens.push_back(token);
        start = end+1;
    } while(end!=string::npos);

    return tokens;
}

/**Function to read the CSV File and store it in the vector of the objects of the CSV_Data class*/
void read_file(vector<CSV_Data> &input) {
    ifstream CSVFile ("input_data.csv");
    string line;

    if(CSVFile.is_open()) {
        // getline(CSVFile,line); //In order to avoid the first row of CSV file (uncomment if needed)

        while(getline(CSVFile,line)) {
            vector<string> temp = tokenise(line,',');

            //Can do exception-handling here if needed.
            input.push_back(CSV_Data(temp[0],temp[1]));
        }
        CSVFile.close();
    }
}

int main () {

    return 0;
}