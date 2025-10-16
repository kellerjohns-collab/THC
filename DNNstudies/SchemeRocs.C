#include "MakeRoc.C"

double getAUC(TGraph* groc){
  
  float auc = 0;
  for(int i  = 0; i < groc->GetN()-1; i++){
    auc += (groc->GetPointX(i) - groc->GetPointX(i+1))*(groc->GetPointY(i) + groc->GetPointY(i+1))/(2);
    //cout<<"bkg eff = "<<groc->GetPointX(i)<<"-"<<groc->GetPointX(i+1)<<", sig eff = "<<groc->GetPointY(i)<<"-"<<groc->GetPointY(i+1)<<", area "<<(groc->GetPointX(i+1) - groc->GetPointX(i))*(groc->GetPointY(i) + groc->GetPointY(i+1))/(2)<<endl;
  }
  return auc;

}

void SchemeRocs(){

  TGraph* g1 = MakeRoc("roc_scheme1.txt");
  TGraph* g2 = MakeRoc("roc_scheme2.txt");
  TGraph* g3 = MakeRoc("roc_scheme3.txt");
  TGraph* g4 = MakeRoc("roc_scheme4.txt");
  TGraph* g5 = MakeRoc("roc_scheme5.txt");
  TGraph* g6 = MakeRoc("roc_scheme6.txt"); 
  TGraph* g7 = MakeRoc("roc_scheme7.txt");
  TGraph* g8 = MakeRoc("roc_scheme8.txt");
  TGraph* g9 = MakeRoc("roc_scheme9.txt");
  
  g2->SetLineColor(kBlue-4);
  g3->SetLineColor(kBlue-6);
  g4->SetLineColor(kRed-4);
  g5->SetLineColor(kRed-6);
  g6->SetLineColor(kPink+10);
  g7->SetLineColor(kGreen-4);
  g8->SetLineColor(kGreen-6);
  g9->SetLineColor(kGreen+2);

  float lw = 2.;

  g1->SetLineWidth(lw);
  g2->SetLineWidth(lw);
  g3->SetLineWidth(lw);
  g4->SetLineWidth(lw);
  g5->SetLineWidth(lw);
  g6->SetLineWidth(lw);
  g7->SetLineWidth(lw);
  g8->SetLineWidth(lw);
  g9->SetLineWidth(lw);

  g1->GetXaxis()->SetRangeUser(0.,1.);
  g1->GetYaxis()->SetRangeUser(0.,1.);

  g1->GetXaxis()->SetTitle("Background efficiency");
  g1->GetYaxis()->SetTitle("Signal efficiency");

  TCanvas* c1 = new TCanvas();
  
  g1->Draw("AL");
  g2->Draw("Lsame");
  g3->Draw("Lsame");
  g4->Draw("Lsame");
  g5->Draw("Lsame");
  g6->Draw("Lsame");
  g7->Draw("Lsame");
  g8->Draw("Lsame");
  g9->Draw("Lsame");

  TLegend* leg = new TLegend(0.63,0.2,0.9,0.6);
  leg->AddEntry(g1,"Default binning","L");
  leg->AddEntry(g2,"Tight b bins","L");
  leg->AddEntry(g3,"Medium b bins","L");
  leg->AddEntry(g4,"Tight c bins","L");
  leg->AddEntry(g5,"Medium c bins","L");
  leg->AddEntry(g6,"Loose c bins","L");
  leg->AddEntry(g7,"All extra bins","L");
  leg->AddEntry(g8,"Discriminants","L");
  leg->AddEntry(g9,"GN2 probabilities","L");

  leg->Draw("same");

  float auc1 = getAUC(g1);
  float auc2 = getAUC(g2);
  float auc3 = getAUC(g3);
  float auc4 = getAUC(g4);
  float auc5 = getAUC(g5);
  float auc6 = getAUC(g6);
  float auc7 = getAUC(g7);
  float auc8 = getAUC(g8);
  float auc9 = getAUC(g9);

  cout<<"Baseline AUC = "<<auc1<<endl;
  cout<<"AUC scheme2  = "<<auc2<<"("<<100*(auc2-auc1)/auc1<<"%)"<<endl;
  cout<<"AUC scheme3  = "<<auc3<<"("<<100*(auc3-auc1)/auc1<<"%)"<<endl;
  cout<<"AUC scheme4  = "<<auc4<<"("<<100*(auc4-auc1)/auc1<<"%)"<<endl;
  cout<<"AUC scheme5  = "<<auc5<<"("<<100*(auc5-auc1)/auc1<<"%)"<<endl;
  cout<<"AUC scheme6  = "<<auc6<<"("<<100*(auc6-auc1)/auc1<<"%)"<<endl;
  cout<<"AUC scheme7  = "<<auc7<<"("<<100*(auc7-auc1)/auc1<<"%)"<<endl;
  cout<<"AUC scheme8  = "<<auc8<<"("<<100*(auc8-auc1)/auc1<<"%)"<<endl;
  cout<<"AUC scheme9  = "<<auc9<<"("<<100*(auc9-auc1)/auc1<<"%)"<<endl;

  
}
