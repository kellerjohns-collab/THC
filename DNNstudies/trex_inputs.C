void trex_inputs(TString scheme){

  
  TFile* fthc = new TFile("THC_hists/hist-ttH_cc.root");
  TFile* fthb = new TFile("THC_hists/hist-ttH_bb.root");
  TFile* ftho = new TFile("THC_hists/hist-ttH_other.root");  
  TFile* fttb = new TFile("THC_hists/hist-ttbar.root");
  TFile* fott = new TFile("THC_hists/hist-othertop.root");
  TFile* fewk = new TFile("THC_hists/hist-EWK.root");
  TFile* fdat = new TFile("THC_hists/hist-data.root");
  
  TH1F* hthc = (TH1F*)fthc->Get("nntest_scheme"+scheme);
  TH1F* hthb = (TH1F*)fthb->Get("nntest_scheme"+scheme);
  TH1F* htho = (TH1F*)ftho->Get("nntest_scheme"+scheme);
  TH1F* httb = (TH1F*)fttb->Get("nntest_scheme"+scheme);
  TH1F* hott = (TH1F*)fott->Get("nntest_scheme"+scheme);
  TH1F* hewk = (TH1F*)fewk->Get("nntest_scheme"+scheme);
  TH1F* hdat = (TH1F*)fdat->Get("nn_scheme"+scheme);


  //Scale MC by 2 since only using "test" samples
  hthc->Scale(2);
  hthb->Scale(2);
  htho->Scale(2);
  hott->Scale(2);
  hewk->Scale(2);
  httb->Scale(2);

  //find scale factor for ttbar
  TH1F* hnum = (TH1F*)hdat->Clone();
  hnum->Add(hthc,-1);
  hnum->Add(hthb,-1);
  hnum->Add(htho,-1);
  hnum->Add(hott,-1);
  hnum->Add(hewk,-1);

  float  edge08 = hnum->GetXaxis()->FindBin(0.8);
  float  edge09 = hnum->GetXaxis()->FindBin(0.9);
  float  edge95 = hnum->GetXaxis()->FindBin(0.95);

  //float sf = hnum->Integral(edge08,edge09-1)/httb->Integral(edge08,edge09-1);
  //cout<<"Scaling by "<<sf<<endl;
  float sf = 2.9;
  httb->Scale(sf);

  //new file
  TFile fnew("InputScheme"+scheme+".root","RECREATE");

  int nbins = hnum->GetNbinsX() - edge95 +1;

  TH1F* nthc = new TH1F("h_thc","h_thc",nbins,0.95,1.0);
  TH1F* nthb = new TH1F("h_thb","h_thb",nbins,0.95,1.0);
  TH1F* ntho = new TH1F("h_tho","h_tho",nbins,0.95,1.0);
  TH1F* nttb = new TH1F("h_ttb","h_ttb",nbins,0.95,1.0);
  TH1F* nott = new TH1F("h_ott","h_ott",nbins,0.95,1.0);
  TH1F* newk = new TH1F("h_ewk","h_ewk",nbins,0.95,1.0);
  TH1F* ndat = new TH1F("h_dat","h_dat",nbins,0.95,1.0);

  for(int i = 0; i < nbins; i++){

    nthc->SetBinContent(i+1, hthc->GetBinContent(edge95+i));
    nthb->SetBinContent(i+1, hthb->GetBinContent(edge95+i));
    ntho->SetBinContent(i+1, htho->GetBinContent(edge95+i));
    nttb->SetBinContent(i+1, httb->GetBinContent(edge95+i));
    nott->SetBinContent(i+1, hott->GetBinContent(edge95+i));
    newk->SetBinContent(i+1, hewk->GetBinContent(edge95+i));
    ndat->SetBinContent(i+1, hdat->GetBinContent(edge95+i));

    nthc->SetBinError(i+1, hthc->GetBinError(edge95+i));
    nthb->SetBinError(i+1, hthb->GetBinError(edge95+i));
    ntho->SetBinError(i+1, htho->GetBinError(edge95+i));
    nttb->SetBinError(i+1, httb->GetBinError(edge95+i));
    nott->SetBinError(i+1, hott->GetBinError(edge95+i));
    newk->SetBinError(i+1, hewk->GetBinError(edge95+i));
    ndat->SetBinError(i+1, hdat->GetBinError(edge95+i));
    
  }

  nthc->Write();
  nthb->Write();
  ntho->Write();
  nttb->Write();
  nott->Write();
  newk->Write();
  ndat->Write();
  
  fnew.Close();

}
