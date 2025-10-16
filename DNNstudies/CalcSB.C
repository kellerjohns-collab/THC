#include "MakeRoc.C"

void CalcSB(TString scheme = "1"){

  TString input = "roc_scheme"+scheme+".txt";
  TGraph* g1 = MakeRoc(input.Data());

  float S2 = 0.;
  
  double xx1, yy1;
  double xx2, yy2;
  
  for(int i = g1->GetN()-1; i > 79; i--){
    g1->GetPoint(i, xx1, yy1);
    g1->GetPoint(i-1, xx2, yy2);
    //cout<<"bkg eff = "<<xx1<<", sig eff = "<<yy1<<endl;

    float si = 117.12*(yy2-yy1);
    float bi = 4*650745.5*(xx2-xx1)/0.6; //4 is fraction of events i took, 0.6 is the fraction of succeeding jobs.

    float sig = 2*((si+bi)*TMath::Log(1+(si/bi))-si);
    cout<<"bin "<<i<<" has s="<<si<<", b="<<bi<<", sig = "<<sig<<endl;

    S2 += sig;
    
  }

  float S = TMath::Sqrt(S2);
  cout<<"S = "<<S<<endl;
  cout<<"Limit = "<<2/S<<" ("<<100*(2/S)/10.2708-100<<")"<<endl;
  
}
