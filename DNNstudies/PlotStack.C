#include "TFile.h"
#include "TH1.h"
#include "THStack.h"


void PlotStack(TString scheme = "1", int rebin = 20){

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
  
  hthc->Rebin(rebin);
  hthb->Rebin(rebin);
  htho->Rebin(rebin);
  httb->Rebin(rebin);
  hott->Rebin(rebin);
  hewk->Rebin(rebin);
  hdat->Rebin(rebin);
 
  //Scale MC by 2 since only using "test" samples
  hthc->Scale(2);
  hthb->Scale(2);
  htho->Scale(2);
  httb->Scale(2);
  hott->Scale(2);
  hewk->Scale(2);

  hthc->SetFillColor(kPink+9);
  hthb->SetFillColor(kRed+2);
  htho->SetFillColor(kRed-3);
  httb->SetFillColor(kViolet+6);
  hott->SetFillColor(kCyan+1);
  hewk->SetFillColor(kGreen+2);
  
  
  THStack* hs = new THStack("hs","");
  hs->Add(hewk);
  hs->Add(hott);
  hs->Add(httb);
  hs->Add(htho);
  hs->Add(hthb);
  hs->Add(hthc);

  //Blind
  for(int i = 0; i <= hdat->GetNbinsX(); i++){
    float ntot = httb->GetBinContent(i) + hott->GetBinContent(i) + hewk->GetBinContent(i) + hthb->GetBinContent(i) + htho->GetBinContent(i);
    if(hdat->GetBinCenter(i) > 0.9){
      hdat->SetBinContent(i,-0.1); hdat->SetBinError(i,0);
      //cout<<"bin with S/B = "<<hthc->GetBinContent(i)<<"/"<<ntot<<" = "<<hthc->GetBinContent(i)/ntot<<" blind"<<endl;
    }
    //else cout<<"bin with S/B = "<<hthc->GetBinContent(i)<<"/"<<ntot<<" = "<<hthc->GetBinContent(i)/ntot<<" unblind"<<endl;
  }

  TCanvas* c1 = new TCanvas("c1","c1",50,50,600,700);
  TPad* pad1 = new TPad("pad1","pad1",0.0,0.35,1.0,1.0);
  TPad* pad2 = new TPad("pad2","pad2",0.0,0.0,1.0,0.35);
  
  pad1->SetBottomMargin(0);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.33);
  
  pad1->Draw();
  pad2->Draw();
  pad1->cd();

  
  hdat->SetMinimum(0.001);
  hdat->GetYaxis()->SetTitle("Events / bin ");
  
  hdat->Draw();
  hs->Draw("histsame");
  hdat->Draw("axissame");

  
  TLegend* leg = new TLegend(0.65,0.58,0.91,0.92);
  leg->AddEntry(hdat,"Data","PLE");
  leg->AddEntry(hthc,"ttH(cc)","F");
  leg->AddEntry(hthb,"ttH(bb)","F");
  leg->AddEntry(htho,"ttH other","F");
  leg->AddEntry(httb,"t#bar{t}","F");
  leg->AddEntry(hott,"other top","F");
  leg->AddEntry(hewk,"electroweak","F");

  leg->Draw("same");

  TLatex specs;
  specs.SetNDC(); specs.SetTextColor(1);
  specs.SetTextFont(72);
  specs.DrawLatex(0.30,0.89,"ATLAS ");
  specs.SetTextFont(42);
  specs.DrawLatex(0.43,0.89,"Internal ");
  specs.DrawLatex(0.30,0.84,"139 fb^{-1}, 13 TeV");
  
  TString schemestring = "";
  if(scheme == "1") schemestring = "Default binning";
  if(scheme == "2") schemestring = "Tight b bins";
  if(scheme == "3") schemestring = "Medium b bins";
  if(scheme == "4") schemestring = "Tight c bins";
  if(scheme == "5") schemestring = "Medium c bins";
  if(scheme == "6") schemestring = "Loose c bins";
  if(scheme == "7") schemestring = "All extra bins";
  if(scheme == "8") schemestring = "Discriminants";
  if(scheme == "9") schemestring = "Probabilities";
  specs.DrawLatex(0.65,0.53,schemestring);

  
  pad2->cd();

  TH1F* rdat = (TH1F*)hdat->Clone();

  TH1F* deno = (TH1F*)httb->Clone();
  deno->Add(hott);
  deno->Add(hewk);
  deno->Add(hthb);
  deno->Add(htho);
  deno->Add(hthc);
  
  for(int i = 0; i < rdat->GetNbinsX(); i++){
    
    if(deno->GetBinContent(i+1) > 0){
      rdat->SetBinContent(i+1, hdat->GetBinContent(i+1)/deno->GetBinContent(i+1));
      rdat->SetBinError(i+1, hdat->GetBinError(i+1)/deno->GetBinContent(i+1));
    }
    else{
      rdat->SetBinContent(i+1,0);
    }    
  }


  rdat->SetMaximum(3.3);
  rdat->SetMinimum(0.801);

  rdat->GetYaxis()->SetTitleOffset(.5);
  rdat->GetYaxis()->SetTitleSize(0.09);
  rdat->GetYaxis()->SetLabelSize(0.09);  
  rdat->GetXaxis()->SetLabelSize(0.10);  
  rdat->GetXaxis()->SetTitleSize(0.11);  
  rdat->GetXaxis()->SetTitleOffset(1.1);  

  rdat->GetYaxis()->SetTitle("data / pred    ");
  rdat->GetXaxis()->SetTitle("DNN score");

  TF1* line = new TF1("","1",rdat->GetXaxis()->GetXmin(),rdat->GetXaxis()->GetXmax());
  line->SetLineStyle(7);

  rdat->Draw("");
  line->Draw("same");
  rdat->Draw("same");

  
  return;
  
}
