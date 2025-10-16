TGraph* OneRoc(TString mva = "salt"){

  TString path = "THC_hists";
  if(mva=="nn") path = "../NNstudies/THC_hists";
  if(mva=="v1") path = "THC_hists/v1";
  if(mva=="score" || mva=="disc") path = "THC_hists/v3_split4";

  TFile* fthc = new TFile(path+"/hist-ttH_cc.root");
  TFile* fthb = new TFile(path+"/hist-ttH_bb.root");
  TFile* ftho = new TFile(path+"/hist-ttH_other.root");  
  TFile* fttb = new TFile(path+"/hist-ttbar.root");
  TFile* fott = new TFile(path+"/hist-othertop.root");
  TFile* fewk = new TFile(path+"/hist-EWK.root");
  TFile* ft1b = new TFile(path+"/hist-tt1b.root");
  TFile* ft1B = new TFile(path+"/hist-tt1B.root");
  TFile* ft2b = new TFile(path+"/hist-tt2b.root");
  TFile* ft1c = new TFile(path+"/hist-tt1c.root");
  TFile* ft1C = new TFile(path+"/hist-tt1C.root");
  TFile* ft2c = new TFile(path+"/hist-tt2c.root");
  TFile* fttl = new TFile(path+"/hist-ttlight.root");
  TFile* fttz = new TFile(path+"/hist-ttZ.root");
  TFile* fttw = new TFile(path+"/hist-ttW.root");
  TFile* fvhx = new TFile(path+"/hist-VH.root");


  TString name = "score_test";
  if(mva=="nn") name = "nntest_scheme1";
  if(mva=="score") name = "score_test";
  if(mva=="disc") name = "disc_test";

  TH1F* hthc = (TH1F*)fthc->Get(name);
  TH1F* hbkg = (TH1F*)fthb->Get(name);
  TH1F* htho = (TH1F*)ftho->Get(name);
  TH1F* hott = (TH1F*)fott->Get(name);
  TH1F* hewk = (TH1F*)fewk->Get(name);
  hbkg->Add(htho);
  hbkg->Add(hott);
  hbkg->Add(hewk);
  
  if(mva=="score" || mva=="disc"){
    TH1F* ht1b = (TH1F*)ft1b->Get(name);
    TH1F* ht1B = (TH1F*)ft1B->Get(name);
    TH1F* ht2b = (TH1F*)ft2b->Get(name);
    TH1F* ht1c = (TH1F*)ft1c->Get(name);
    TH1F* ht1C = (TH1F*)ft1C->Get(name);
    TH1F* ht2c = (TH1F*)ft2c->Get(name);
    TH1F* httl = (TH1F*)fttl->Get(name);
    TH1F* httz = (TH1F*)fttz->Get(name);
    TH1F* httw = (TH1F*)fttw->Get(name);
    hbkg->Add(ht1b);
    hbkg->Add(ht1B);
    hbkg->Add(ht2b);
    hbkg->Add(ht1c);
    hbkg->Add(ht1C);
    hbkg->Add(ht2c);
    hbkg->Add(httl);
    hbkg->Add(httz);
    hbkg->Add(httw);
  }
  else {
    TH1F* httb = (TH1F*)fttb->Get(name);
    hbkg->Add(httb);
  }
  

  int nbins = 500;
  
  hbkg->Rebin(2000/nbins);
  hthc->Rebin(2000/nbins);

  float ibkg = hbkg->Integral();
  float ithc = hthc->Integral();
  
  TGraph* gg = new TGraph();

  for(int i = 1; i < nbins+1; i++){

    gg->SetPoint(i-1, hbkg->Integral(i,nbins+1)/ibkg, hthc->Integral(i, nbins+1)/ithc);
    //cout<<i<<" "<< hbkg->Integral(i,nbins+1)/ibkg<<" "<< hthc->Integral(i, nbins+1)/ithc<<endl;
  }

  float auc = 0;
  for(int i  = 0; i < gg->GetN()-1; i++){
    auc += (gg->GetPointX(i) - gg->GetPointX(i+1))*(gg->GetPointY(i) + gg->GetPointY(i+1))/(2);
  }
  cout<<"AUC = "<<auc<<endl;

  return gg;
  
}

void GetRoc(){

  TGraph* g1 = OneRoc("salt");
  TGraph* g2 = OneRoc("score");
  TGraph* g3 = OneRoc("disc");

  g1->SetLineColor(kBlue-1);
  g2->SetLineColor(kRed+1);
  g3->SetLineColor(kViolet-1);

  g1->SetMarkerColor(g1->GetLineColor());
  g2->SetMarkerColor(g2->GetLineColor());
  g3->SetMarkerColor(g3->GetLineColor());

  g1->SetLineWidth(2);
  g2->SetLineWidth(2);
  g3->SetLineWidth(2);

  g1->GetXaxis()->SetRangeUser(0.,1.);

  g1->GetXaxis()->SetTitle("Background efficiency");
  g1->GetYaxis()->SetTitle("Signal efficiency");
  
  g1->Draw("AL");
  g2->Draw("Lsame");
  g3->Draw("Lsame");

  TLegend* leg = new TLegend(0.6,0.26,0.85,0.4);
  leg->AddEntry(g1,"S vs B","L");
  leg->AddEntry(g2,"Multiclass, p_{ttHcc}","L");
  leg->AddEntry(g3,"Multiclass, d_{ttHcc}","L");

  leg->SetBorderSize(0);
  leg->Draw("same");

  
}
