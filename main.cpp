/* 
 * File:   main.cpp
 * Author: acarroll94
 *
 * Created on May 15, 2015, 2:51 PM
 */
#include <iostream>
#include <cstdlib>

#include <string>
#include <sstream>
#include <fstream>
#include <strings.h>
#include <math.h>
#include <vector>

#include <map>
#include <iterator>
#include <algorithm>
#include <utility>

#include <TFormula.h>
#include <TRandom1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TGraphAsymmErrors.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TApplication.h>

using namespace std;


/*
 * 
 */

struct dataPoint
{
    Double_t energy_MeV,counts;
};

int main(int argc, char** argv) {
    TApplication* rootapp = new TApplication("Counts v MeV", &argc, argv);
    std::vector<Double_t> double_t_Counts;
    std::vector<Double_t> double_t_Potential_MeV;
    double_t_Counts.reserve(500);
    double_t_Potential_MeV.reserve(500);
    
    //Open up our file
    ifstream fin("/r_19ne_states/peaks/ne19_peaks456.txt");
    string str;
    
    //Counter Variables 
    Double_t theta_current;
    Double_t minEnergyValue;
    Double_t minThetaValue; 
            
    int ctr = 0;
    //Loop through our file
    while(getline(fin,str)){ 
        /*
         * Creates an instance of dataPoint, a struct defined earlier in this
         * program.
         */
        dataPoint p;
        // Places the read values on the line into our temporary dataPoint p.
        // Format:
        // LongFloat LongFloat   LongFloat   NewLine
        sscanf( str.c_str(), "%lf\t%lf\t%lf\n", &theta_current, &p.energy_MeV, &p.counts);

        if(ctr == 0){//Is this the first line?
            minThetaValue = theta_current;
            minEnergyValue = p.energy_MeV;
        }
        if(theta_current == minThetaValue){
            // Adds p to our permanent dynamic array, dataPointArr
            double_t_Counts.push_back(p.energy_MeV);
            double_t_Potential_MeV.push_back(p.counts);
        }
        else{ 
            double_t_Counts[ctr] += p.counts;
        }
        // Output: Energy Potential
        //cout << p.energy_MeV << "\t " << p.counts <<"\n";
        ctr++;
    }
    
    for(int i = 0; i < double_t_Counts.size();i++){
        cout << double_t_Potential_MeV[i] << "\t " << double_t_Counts[i] << "\n";
    }
    //Create canvas for our graph
    TCanvas *c1 = new TCanvas("c1", "Graph", 200, 10, 700, 500);
    c1->SetFillColor(42);
    c1->SetGrid();

    TGraph *gr = new TGraph(double_t_Counts.size(), &double_t_Counts[0], &double_t_Potential_MeV[0]);
    gr->Draw("ACP");
    //Draws the graph
    c1->Update();
    //c1->GetFrame()->SetFillColor(21);
    //c1->GetFrame()->SetBorderSize(12);
    c1->Modified();
    rootapp->Run();
    return 0;
}

