#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void outputData(const vector<double> &v);

void readData(const string &fileName, vector<double> &angle, vector<double> &coefficient);

double interpolation(double angleChosen, vector<double> &angle, vector<double> &coefficient);

bool isOrdered(const vector<double> &v);

void reorder(vector<double> &angle, vector<double> &coefficient);

int main(int argc, char *argv[]){
    if (argc < 2){
        cout << "USAGE: " << argv[0] << " [file name]" << endl;
        return 1;
    }

    vector<double> angles;
    vector<double> coefficients;

    readData(argv[1], angles, coefficients);

    while (true){
        double angleChosen = 0;
        cout << "Please insert an angle: " << endl;
        cin >> angleChosen;
        cout << endl;

        double calced = interpolation(angleChosen, angles, coefficients);

        cout << calced << endl; //<< "Coefficient: " 

        string line;
        cout << "Continue? Yes or No" << endl;
        cin >> line;
        cout << endl;

        if (line == "No"){
            break;
        }
    }

    return 0;
}

void outputData(const vector<double> &v){
    for (unsigned i = 0; i < v.size(); i++){
        cout << v.at(i) << " ";
    }
    cout << endl;
}

void readData(const string &fileName, vector<double> &angle, vector<double> &coefficient){
    ifstream inputFile(fileName);

    if (!inputFile.is_open()){
        cout << "Error opening " << fileName << endl;
        exit(1);
    }

    double angleS, coefficientS; //variableS = variable single
    while(inputFile >> angleS >> coefficientS ){
        angle.push_back(angleS);
        coefficient.push_back(coefficientS);
    }
    
    inputFile.close();
}

double interpolation(double angleChosen, vector<double> &angle, vector<double> &coefficient){
    //cout << "Angle Vec Size: " << angle.size() << endl;
    //cout << "Coeff Vec Size: " << coefficient.size() << endl; 
    if (angle.size() <= 0 || coefficient.size() <= 0){ return 0.0;}
    //if (angleChosen < 0){ return 0.0; }

    if (!isOrdered(angle)){
        reorder(angle, coefficient);
    }

    int indexA = -1;
    int indexB = 0;
    for (unsigned i = 0; i < angle.size(); i++){
        if (angle.at(i) > angleChosen){
            indexA = i - 1;
            break;
        }
    }
    //cout << index << endl << endl;

    //cout << angle.at(index) << ' < ' << angleChosen << ' < ' << angle.at(index+1) << endl;
    /*double alpha, slope;
    double t1;

    if (indexA == -1){
        //return 0.0;
        indexA = 0;

        t1 = (angle.at(0) - angle.at(angle.size()-1));

        if (t1 == 0){ return 0.0;} //bing chilling

        alpha = ((angle.at(0) - angleChosen) / t1);
        slope = (coefficient.at(0) - coefficient.at(angle.size()-1)) / (t1);
    }else{

        t1 = angle.at(indexA) - angle.at(indexA+1);

        if (t1 == 0){ return 0.0;} //bing chilling

        alpha = (angle.at(indexA) - angleChosen) / (t1);
        slope = (coefficient.at(indexA) - coefficient.at(indexA + 1)) / (t1);
    }

    double calc = coefficient.at(indexA) + (slope * alpha);

    return calc;*/
    if (indexA == -1){
        indexA = 0;
        indexB = angle.size()-1;
    }else{
        indexB = indexA + 1;
    }

    return coefficient.at(indexA) + (((angleChosen - angle.at(indexA)) / (angle.at(indexB) - angle.at(indexA))) * (coefficient.at(indexB) - coefficient.at(indexA)));
    
}

bool isOrdered(const vector<double> &v){
    if (v.size() <= 0){ return true; }

    double last = v.at(0);
    for (unsigned i = 1; i < v.size(); i++){
        if (last > v.at(i)){
            return false;
        }
        last = v.at(i);
    }

    return true;
}

void reorder(vector<double> &angle, vector<double> &coefficient){
    if (angle.size() <= 0 || coefficient.size() <= 0){ return; }

    while(true){ //pretty sure this is bubble sort or something
        bool end = true;

        double last = angle.at(0);
        for (unsigned i = 1; i < angle.size(); i++){
            if(last > angle.at(i)){
                end = false;

                double tempVar = angle.at(i);
                double otheVar = coefficient.at(i);

                angle[i] = last;
                coefficient[i] = coefficient.at(i-1);

                angle[i-1] = tempVar;
                coefficient[i-1] = otheVar;
            }
            last = angle.at(i);
        }

        if (end){break;}
    }
}