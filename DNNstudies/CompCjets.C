void CompCjets(TString reg){

  bool autoprint = true;
  
  TFile* fthc = new TFile("THC_hists/hist-ttH_cc.root");
  TFile* fthb = new TFile("THC_hists/hist-ttH_bb.root");
  TFile* ftho = new TFile("THC_hists/hist-ttH_other.root");  
  TFile* fttb = new TFile("THC_hists/hist-ttbar.root");
  TFile* fott = new TFile("THC_hists/hist-othertop.root");
  TFile* fewk = new TFile("THC_hists/hist-EWK.root");

  TH1F* hthc = (TH1F*)fthc->Get("ncjets_"+reg);
  TH1F* hthb = (TH1F*)fthb->Get("ncjets_"+reg);
  TH1F* htho = (TH1F*)ftho->Get("ncjets_"+reg);
  TH1F* httb = (TH1F*)fttb->Get("ncjets_"+reg);
  TH1F* hott = (TH1F*)fott->Get("ncjets_"+reg);
  TH1F* hewk = (TH1F*)fewk->Get("ncjets_"+reg);

  hthb->Add(htho);

  hthc->Scale(1./hthc->Integral());
  hthb->Scale(1./hthb->Integral());  
  httb->Scale(1./httb->Integral());  
  hott->Scale(1./hott->Integral());  
  hewk->Scale(1./hewk->Integral());

  hthc->SetLineColor(kPink+9);
  hthb->SetLineColor(kRed+2);
  httb->SetLineColor(kViolet+6);
  hott->SetLineColor(kCyan+1);
  hewk->SetLineColor(kGreen+2);

  hthc->SetMaximum(1.0);
  hthc->SetMinimum(0.0);

  hthc->GetYaxis()->SetTitle("Fraction of events");
  hthc->GetXaxis()->SetTitle("N truth c-jets");

  TCanvas* c1 = new TCanvas("c1","c1",50,50,600,600);
  
  hthc->Draw("hist");
  hthb->Draw("histsame");
  httb->Draw("histsame");
  hott->Draw("histsame");
  hewk->Draw("histsame");

  TLegend* leg = new TLegend(0.65,0.68,0.91,0.92);
  leg->AddEntry(hthc,"ttH(cc)","L");
  leg->AddEntry(hthb,"ttH bkg","L");
  leg->AddEntry(httb,"t#bar{t}","L");
  leg->AddEntry(hott,"other top","L");
  leg->AddEntry(hewk,"electroweak","L");

  leg->Draw("same");

  TLatex specs;
  specs.SetNDC(); specs.SetTextColor(1);
  specs.SetTextSize(0.04);
  specs.SetTextFont(72);
  specs.DrawLatex(0.3,0.89,"ATLAS ");
  specs.SetTextFont(42);
  specs.DrawLatex(0.43,0.89,"Internal ");

  TString schemestring = "";
  if(reg.Contains("e1")) schemestring = "Default binning";
  if(reg.Contains("e2")) schemestring = "Tight b bins";
  if(reg.Contains("e3")) schemestring = "Medium b bins";
  if(reg.Contains("e4")) schemestring = "Tight c bins";
  if(reg.Contains("e5")) schemestring = "Medium c bins";
  if(reg.Contains("e6")) schemestring = "Loose c bins";
  if(reg.Contains("e7")) schemestring = "All extra bins";
  if(reg.Contains("e8")) schemestring = "Discriminants";
  if(reg.Contains("e9")) schemestring = "Probabilities";
  specs.DrawLatex(0.3,0.84,schemestring);

  if(autoprint) c1->Print("nCjet_"+reg+".png");

}


