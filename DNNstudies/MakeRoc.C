#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>


TGraph* MakeRoc(string input){

  TGraph* groc = new TGraph();
  
  ifstream ifs0(input.c_str());
  string str;
    
  while (getline(ifs0,str)){
    size_t s1 = 0;
    size_t s2 = 0;

    s1 = str.find_first_of(" ",0);
    s2 = str.find_first_of(" ",s1+1);

    TString point = str.substr(0,s1);
    TString xx = str.substr(s1+1,s2-s1-1);
    TString yy = str.substr(s2+1,str.length()-s2);

    //cout<<point<<", "<<xx<<", "<<yy<<","<<endl;

    groc->SetPoint(point.Atoi(), xx.Atof(), yy.Atof());
    
  }

  groc->SetPoint(groc->GetN(), 0., 0.);

  
  //  groc->Draw("AL");

  return groc;
  
}
