void PlotSamples(TString mva = "salt"){

  TString path = "";
  if(mva=="nn") path = "../NNstudies/";
  
  TFile* fthc = new TFile(path+"THC_hists/hist-ttH_cc.root");
  TFile* fthb = new TFile(path+"THC_hists/hist-ttH_bb.root");
  TFile* ftho = new TFile(path+"THC_hists/hist-ttH_other.root");  
  TFile* fttb = new TFile(path+"THC_hists/hist-ttbar.root");
  TFile* fott = new TFile(path+"THC_hists/hist-othertop.root");
  TFile* fewk = new TFile(path+"THC_hists/hist-EWK.root");

  TString name = "nn_test";
  if(mva=="nn") name = "nntest_scheme1";

  TH1F* hthc = (TH1F*)fthc->Get(name);
  TH1F* hthb = (TH1F*)fthb->Get(name);
  TH1F* htho = (TH1F*)ftho->Get(name);
  TH1F* httb = (TH1F*)fttb->Get(name);
  TH1F* hott = (TH1F*)fott->Get(name);
  TH1F* hewk = (TH1F*)fewk->Get(name);
  
  int rebin = 20;
  hthc->Rebin(rebin);
  hthb->Rebin(rebin);  
  htho->Rebin(rebin);
  httb->Rebin(rebin);  
  hott->Rebin(rebin);  
  hewk->Rebin(rebin);


  hthc->Scale(1./hthc->Integral());
  hthb->Scale(1./hthb->Integral());
  htho->Scale(1./htho->Integral());
  httb->Scale(1./httb->Integral());
  hott->Scale(1./hott->Integral());
  hewk->Scale(1./hewk->Integral());

  hthc->SetLineColor(kPink+9);
  hthb->SetLineColor(kRed+2);
  htho->SetLineColor(kRed-3);
  httb->SetLineColor(kViolet+6);
  hott->SetLineColor(kCyan+1);
  hewk->SetLineColor(kGreen+2);

  if(mva == "salt") hthc->GetXaxis()->SetTitle("Transformer score");
  else hthc->GetXaxis()->SetTitle("DNN score");
  hthc->GetYaxis()->SetTitle("Fraction of events");
  
  hthc->Draw("hist");
  hthb->Draw("histsame");
  htho->Draw("histsame");
  httb->Draw("histsame");
  hott->Draw("histsame");
  hewk->Draw("histsame");

  TLegend* leg = new TLegend(0.25,0.64,0.45,0.9);
  leg->AddEntry(hthc,"ttH cc","L");
  leg->AddEntry(hthb,"ttH bb","L");
  leg->AddEntry(htho,"ttH other","L");
  leg->AddEntry(httb,"t#bar{t}","L");
  leg->AddEntry(hott,"other top","L");
  leg->AddEntry(hewk,"electroweak","L");
  leg->Draw("same");
  
}
