#include <TROOT.h>
#include <TStyle.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>
#include <TAxis.h>

#include <iostream>
using namespace std;

// Builds a graph with errors, displays it and saves it as an image
void setStyle(){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(111);
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void viscosity(){
setStyle();    
    // The values and the errors on the X and Y axis
    const int n_points=4;

    /* CAMERA*/
    double x_vals[n_points]=
            {16.244, 24.708, 51.9, 19.169};
    double y_vals[n_points]=
            {9.072, 14.425, 32.298, 12.602};
    
   double x_errs[n_points]=
            {1.161, 1.711, 4.386, 1.353};
    double y_errs[n_points]=
        {0.292, 0.323, 0.437, 0.445};
        

    /* CRONOMETRO 
    double x_vals[n_points] =
        {17.306, 28.095, 61.846, 21.824};
    double y_vals[n_points] =
        {9.072, 14.425, 32.298, 12.602};

    double x_errs[n_points] =
        {0.262, 0.452, 2.146, 0.443};
    double y_errs[n_points] =
        {0.292, 0.323, 0.437, 0.445};*/

    // Instance of the graph
    TGraphErrors * graph =new TGraphErrors(n_points,x_vals,y_vals,x_errs,y_errs);
    // graph->SetTitle("Fit delle misure col cronometro");
    graph->SetTitle("Fit delle misure con IMAQ");
    graph->GetXaxis()->SetTitle("velocit#grave{a} corretta #times 10^{-3} (m/s)");
    graph->GetYaxis()->SetTitle("#beta #times 10^{-3} (Kg/s^{2})");
    //graph->SetTitle("Fit delle misure con IMAQ ; velocit#grave{a} corretta #times 10^{-3} (m/s); #beta #times 10^{-3} (Kg/s^{2})");

    // Cosmetics
    graph->SetMarkerStyle(kOpenCircle);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kBlue);

    // The canvas on which we'll draw the graph
    TCanvas *mycanvas = new TCanvas();


    // Define a linear function
    TF1 *f = new TF1("Linear law","[0]+x*[1]",0.2,1.2);
    // Let's make the function line nicer
    f->SetLineColor(kRed); f->SetLineStyle(2);
    f->FixParameter(0,0.);    
    // Fit it to the graph and draw it
    graph->Fit(f);

    // Draw the graph !
    graph->Draw("APE");

    cout << "x and y measurements correlation =" <<graph->GetCorrelationFactor()<<endl;
    cout << "The Chisquare of the fit = "<< graph->Chisquare(f)<<endl;
    cout << "From function  "<<f->GetChisquare()<<endl;
    cout << "From function  "<<f->GetNDF()<<endl;
 
   // Build and Draw a legend
    TLegend *leg=new TLegend(.1,.7,.3,.9);
    leg->SetFillColor(0);
    
    graph->SetFillColor(0);
    graph->SetMarkerStyle(8);
    graph->SetMarkerSize(0.8);
    leg->AddEntry(graph,"Punti Sperimentali");
    leg->AddEntry(f,"Fit Lineare");
    leg->Draw("Same");

    // mycanvas->SetTitle("Fit delle misure effettuate con IMAQ");
    mycanvas->SetGrid();
}
