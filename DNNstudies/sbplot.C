void sbplot(){

  TFile* fthc = new TFile("THC_hists/hist-ttH_cc.root");
  TFile* fthb = new TFile("THC_hists/hist-ttH_bb.root");
  TFile* ftho = new TFile("THC_hists/hist-ttH_other.root");  
  TFile* fttb = new TFile("THC_hists/hist-ttbar.root");
  TFile* fott = new TFile("THC_hists/hist-othertop.root");
  TFile* fewk = new TFile("THC_hists/hist-EWK.root");

  vector<TGraph*> vg;
  
  for(int  i = 1; i <=9; i++){
    stringstream ss;
    ss<<i;
    TString istr = ss.str();

    TH1F* hthc = (TH1F*)fthc->Get("nntest_scheme"+istr);
    TH1F* hthb = (TH1F*)fthb->Get("nntest_scheme"+istr);
    TH1F* htho = (TH1F*)ftho->Get("nntest_scheme"+istr);
    TH1F* httb = (TH1F*)fttb->Get("nntest_scheme"+istr);
    TH1F* hott = (TH1F*)fott->Get("nntest_scheme"+istr);
    TH1F* hewk = (TH1F*)fewk->Get("nntest_scheme"+istr);

    httb->Scale(2.);
    httb->Add(hott);
    httb->Add(hewk);
    httb->Add(hthb);
    httb->Add(htho);

    TGraph* gg = new TGraph();
    int nbins = hthc->GetNbinsX();
    
    for(int i = 0; i <= nbins; i++){
      gg->SetPoint(i, hthc->GetBinLowEdge(i+1), hthc->Integral(i,nbins)/httb->Integral(i, nbins));
      //gg->SetPoint(i, hthc->GetBinLowEdge(i+1), hthc->Integral(i,nbins));
      //gg->SetPoint(i, hthc->GetBinLowEdge(i+1), httb->Integral(i,nbins));
    }

    gg->SetLineWidth(2.);
    
    vg.push_back(gg);

  }

  vg.at(1)->SetLineColor(kBlue-4);
  vg.at(2)->SetLineColor(kBlue-6);
  vg.at(3)->SetLineColor(kRed-4);
  vg.at(4)->SetLineColor(kRed-6);
  vg.at(5)->SetLineColor(kPink+10);
  vg.at(6)->SetLineColor(kGreen-4);
  vg.at(7)->SetLineColor(kGreen-6);
  vg.at(8)->SetLineColor(kGreen+2);

  vg.at(0)->GetXaxis()->SetTitle("NN cut");
  vg.at(0)->GetYaxis()->SetTitle("S/B");
  
  vg.at(0)->Draw("AL");
  for(int i = 1; i < 9; i++) vg.at(i)->Draw("same");

  TLegend* leg = new TLegend(0.63,0.2,0.9,0.6);
  leg->AddEntry(vg.at(0),"Default binning","L");
  leg->AddEntry(vg.at(1),"Tight b bins","L");
  leg->AddEntry(vg.at(2),"Medium b bins","L");
  leg->AddEntry(vg.at(3),"Tight c bins","L");
  leg->AddEntry(vg.at(4),"Medium c bins","L");
  leg->AddEntry(vg.at(5),"Loose c bins","L");
  leg->AddEntry(vg.at(6),"All extra bins","L");
  leg->AddEntry(vg.at(7),"Discriminants","L");
  leg->AddEntry(vg.at(8),"GN2 probabilities","L");

  leg->Draw("same");


  
}
