//
//  main.cpp
//  Sorting Chemicals
//
//  Created by Yanglin Tao on 9/17/21.
//
//  This program is to maintain one entry for each unique molecular
//  formula along with all the names for that formula.
//  After they have all been read in, the vector will be sorted by carbon and hydrogen,
//  and finally display all the entries in the sorted vector.

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


//build a struct of chemicals;
struct chemicals{
    vector<string> formula_name;
    int carbon_count;
    int hydrogen_count;
};

//creating function prototypes;
void open_file(ifstream& my_doc);
void fill_vector(ifstream& my_doc, vector<chemicals>& vector_chemicals);
void sort_vector(vector<chemicals> &vector_chemicals);
void display_vector(const vector<chemicals> &vector_chemicals);

//function to open file
void open_file(ifstream& my_doc){
    do{
        cout << "Please enter the name of the file you want to open: ";
        string file_name;
        cin >> file_name;
        my_doc.open(file_name);
        if(!my_doc){
            cout << "Could not open file." << endl;
            my_doc.clear();
            cout << "Please enter the name of the file you want to open: ";
            cin >> file_name;
            my_doc.open(file_name);
        }
    }
    while(!my_doc);
}

// function to check duplicate formulas in the file
size_t check_loc (vector<chemicals>& vector_chemicals,
                  chemicals check_chemical){
    for(size_t i = 0; i < vector_chemicals.size(); ++i){
        if(vector_chemicals[i].carbon_count ==
           check_chemical.carbon_count &&
           vector_chemicals[i].hydrogen_count ==
           check_chemical.hydrogen_count){
            return i;
        }
    }
    return vector_chemicals.size();
}

// function to fill the vector
void fill_vector(ifstream& my_doc, vector<chemicals>& vector_chemicals){
    char C = 'C';
    char H = 'H';
    int carbon_counts;
    int hydrogen_counts;
    string formula_names;
    while (my_doc >> formula_names >> C >> carbon_counts >> H >> hydrogen_counts){
        chemicals check_chemical;
        check_chemical.carbon_count = carbon_counts;
        check_chemical.hydrogen_count = hydrogen_counts;
        check_chemical.formula_name.push_back(formula_names);
        size_t locator;
        locator = check_loc(vector_chemicals, check_chemical);
        if(locator == vector_chemicals.size()){
            vector_chemicals.push_back(check_chemical);
        }
        else{
            vector_chemicals[locator].formula_name.push_back(formula_names);
        }
    }
}

// function to sort the vector by carbon counts
void sort_vector(vector<chemicals> &vector_chemicals){
    for(size_t i = 0; i + 1 < vector_chemicals.size(); i++){
        bool done = true;
        for(size_t j = 0; j + 1 < vector_chemicals.size(); j++){
            if(vector_chemicals[j].carbon_count >
               vector_chemicals[j + 1].carbon_count){
                chemicals temp = vector_chemicals[j];
                vector_chemicals[j] = vector_chemicals[j + 1];
                vector_chemicals[j + 1] = temp;
                done = false;
            }
            else if(vector_chemicals[j].carbon_count ==
                    vector_chemicals[j + 1].carbon_count){
                if(vector_chemicals[j].hydrogen_count >
                   vector_chemicals[j + 1].hydrogen_count){
                    chemicals temp = vector_chemicals[j];
                    vector_chemicals[j] = vector_chemicals[j + 1];
                    vector_chemicals[j + 1] = temp;
                    done = false;
                }
            }
        }
        if(done){
            break;
        }
    }
}

// function to display the sorted vector of chemicals
void display_vector(const vector<chemicals> &vector_chemicals){
    for(size_t i = 0; i < vector_chemicals.size(); ++i){
        cout << "C" << vector_chemicals[i].carbon_count <<
        "H" << vector_chemicals[i].hydrogen_count << " ";
        for(size_t j = 0; j <
            vector_chemicals[i].formula_name.size(); ++j){
            cout << vector_chemicals[i].formula_name[j] << " ";
        }
        cout << "\n";
    }
}

int main(int argc, const char * argv[]) {
    ifstream my_doc;
    vector<chemicals> vector_chemicals;
    open_file(my_doc);
    fill_vector(my_doc,vector_chemicals);
    sort_vector(vector_chemicals);
    my_doc.close();
    display_vector(vector_chemicals);
    return 0;
}




