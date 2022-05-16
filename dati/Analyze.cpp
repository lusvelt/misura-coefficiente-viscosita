#include <TROOT.h>
#include <TGraph.h>
#include <TF1.h>
#include <fstream>
#include <iostream>
#include <string>
#include <TCanvas.h>

using namespace std;

void Analyze(string fileName) {
    ifstream input(fileName);
    vector<Double_t> T, Y;

    
    while (!input.eof()) {
        Double_t t, x, y;
        input >> t >> x >> y;
        T.push_back(t);
        Y.push_back(y);
    }

    Double_t y0 = Y[0];
    for (vector<Double_t>::iterator it = Y.begin(); it != Y.end(); it++)
        *it -= y0;
    TGraph *graph = new TGraph(T.size(), &T[0], &Y[0]);
    graph->SetMarkerSize(0.8);
    TF1 *f = (TF1*) gROOT->GetFunction("pol1");
    f->FixParameter(0, 0);
    graph->Fit(f, "B");
    

    cout << f->GetParameter(1) << "    " << f->GetParError(1) << endl;
}