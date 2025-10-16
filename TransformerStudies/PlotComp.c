void PlotComp(){

  TFile* fthc = new TFile("THC_hists/hist-ttH_cc.root");
  TFile* fthb = new TFile("THC_hists/hist-ttH_bb.root");
  TFile* ftho = new TFile("THC_hists/hist-ttH_other.root");  
  TFile* fttb = new TFile("THC_hists/hist-ttbar.root");
  TFile* fott = new TFile("THC_hists/hist-othertop.root");
  TFile* fewk = new TFile("THC_hists/hist-EWK.root");
  
  TH1F* hthc = (TH1F*)fthc->Get("nn_test");
  TH1F* hbkg = (TH1F*)fthb->Get("nn_test");
  TH1F* htho = (TH1F*)ftho->Get("nn_test");
  TH1F* httb = (TH1F*)fttb->Get("nn_test");
  TH1F* hott = (TH1F*)fott->Get("nn_test");
  TH1F* hewk = (TH1F*)fewk->Get("nn_test");

  TFile* fthc2 = new TFile("../NNstudies/THC_hists/hist-ttH_cc.root");
  TFile* fthb2 = new TFile("../NNstudies/THC_hists/hist-ttH_bb.root");
  TFile* ftho2 = new TFile("../NNstudies/THC_hists/hist-ttH_other.root");  
  TFile* fttb2 = new TFile("../NNstudies/THC_hists/hist-ttbar.root");
  TFile* fott2 = new TFile("../NNstudies/THC_hists/hist-othertop.root");
  TFile* fewk2 = new TFile("../NNstudies/THC_hists/hist-EWK.root");

  TH1F* hthc2 = (TH1F*)fthc2->Get("nntest_scheme1");
  TH1F* hbkg2 = (TH1F*)fthb2->Get("nntest_scheme1");
  TH1F* htho2 = (TH1F*)ftho2->Get("nntest_scheme1");
  TH1F* httb2 = (TH1F*)fttb2->Get("nntest_scheme1");
  TH1F* hott2 = (TH1F*)fott2->Get("nntest_scheme1");
  TH1F* hewk2 = (TH1F*)fewk2->Get("nntest_scheme1");

  hbkg->Add(htho);
  hbkg->Add(httb);
  hbkg->Add(hott);
  hbkg->Add(hewk);
  
  hbkg2->Add(htho2);
  hbkg2->Add(httb2);
  hbkg2->Add(hott2);
  hbkg2->Add(hewk2);

  hthc->Rebin(20);
  hbkg->Rebin(20);
  hthc2->Rebin(20);
  hbkg2->Rebin(20);  

  hthc->Scale(1./hthc->Integral());
  hbkg->Scale(1./hbkg->Integral());
  hthc2->Scale(1./hthc2->Integral());
  hbkg2->Scale(1./hbkg2->Integral());
  
  hthc->SetLineColor(kOrange+1);
  hbkg->SetLineColor(kViolet-1); 
  hthc2->SetLineColor(kRed+1);
  hbkg2->SetLineColor(kBlue-1); 

  hthc->GetXaxis()->SetTitle("NN score");
  hthc->GetYaxis()->SetTitle("Fraction of events");
  
  hthc->Draw("hist");
  hbkg->Draw("histsame");
  hthc2->Draw("histsame");
  hbkg2->Draw("histsame");

  TLegend* leg = new TLegend(0.2,0.66,0.55,0.9);
  leg->AddEntry(hthc2,"DNN, signal","L");
  leg->AddEntry(hbkg2,"DNN, bkgd","L");
  leg->AddEntry(hthc,"Transformer, signal","L");
  leg->AddEntry(hbkg,"Transformer, bkgd","L");

  leg->Draw("same");
  
}
