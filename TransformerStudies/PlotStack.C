#include "TFile.h"
#include "TH1.h"
#include "THStack.h"


void PlotStack(TString var = "score", int rebin = 20){

  TString folder = "v3_split4/";
  //TString folder = "";
  
  TFile* fthc = new TFile("THC_hists/"+folder+"hist-ttH_cc.root");
  TFile* fthb = new TFile("THC_hists/"+folder+"hist-ttH_bb.root");
  TFile* ftho = new TFile("THC_hists/"+folder+"hist-ttH_other.root");  
  TFile* ft1b = new TFile("THC_hists/"+folder+"hist-tt1b.root");
  TFile* ft1B = new TFile("THC_hists/"+folder+"hist-tt1B.root");
  TFile* ft2b = new TFile("THC_hists/"+folder+"hist-tt2b.root");
  TFile* ft1c = new TFile("THC_hists/"+folder+"hist-tt1c.root");
  TFile* ft1C = new TFile("THC_hists/"+folder+"hist-tt1C.root");
  TFile* ft2c = new TFile("THC_hists/"+folder+"hist-tt2c.root");
  TFile* fttl = new TFile("THC_hists/"+folder+"hist-ttlight.root");
  TFile* fott = new TFile("THC_hists/"+folder+"hist-othertop.root");
  TFile* fewk = new TFile("THC_hists/"+folder+"hist-EWK.root");
  TFile* fttz = new TFile("THC_hists/"+folder+"hist-ttZ.root");
  TFile* fttw = new TFile("THC_hists/"+folder+"hist-ttW.root");
  TFile* fvhx = new TFile("THC_hists/"+folder+"hist-VH.root");
  TFile* fdat = new TFile("THC_hists/"+folder+"hist-data.root");

  TString test = "_test";
  if(var.Contains("HT")) test = "";
  TH1F* hthc = (TH1F*)fthc->Get(var+test);
  TH1F* hthb = (TH1F*)fthb->Get(var+test);
  TH1F* htho = (TH1F*)ftho->Get(var+test);
  TH1F* ht1b = (TH1F*)ft1b->Get(var+test);
  TH1F* ht1B = (TH1F*)ft1B->Get(var+test);
  TH1F* ht2b = (TH1F*)ft2b->Get(var+test);
  TH1F* ht1c = (TH1F*)ft1c->Get(var+test);
  TH1F* ht1C = (TH1F*)ft1C->Get(var+test);
  TH1F* ht2c = (TH1F*)ft2c->Get(var+test);
  TH1F* httl = (TH1F*)fttl->Get(var+test);
  TH1F* hott = (TH1F*)fott->Get(var+test);
  TH1F* hewk = (TH1F*)fewk->Get(var+test);
  TH1F* httz = (TH1F*)fttz->Get(var+test);
  TH1F* httw = (TH1F*)fttw->Get(var+test);
  TH1F* hvhx = (TH1F*)fvhx->Get(var+test);
  TH1F* hdat = (TH1F*)fdat->Get(var);

  TH1F* cthc = (TH1F*)hthc->Clone();
  
  vector<TH1F*> hvec;
  hvec.push_back(hvhx);
  hvec.push_back(hewk);
  hvec.push_back(hott);
  hvec.push_back(htho);
  hvec.push_back(hthb);
  hvec.push_back(httw);
  hvec.push_back(httz);
  hvec.push_back(httl);
  hvec.push_back(ht1b);
  hvec.push_back(ht1B);
  hvec.push_back(ht2b);
  hvec.push_back(ht1c);
  hvec.push_back(ht1C);
  hvec.push_back(ht2c);
  hvec.push_back(hthc);

  THStack* hs = new THStack("hs","");
  
  
  for(int i = 0; i < hvec.size(); i++){
    hvec.at(i)->Rebin(rebin);
    if(test != "") hvec.at(i)->Scale(2.); //Scale MC by 2 since only using "test" samples
    hs->Add(hvec.at(i));
  }
  hdat->Rebin(rebin);
  cthc->Rebin(rebin);
  
  hthc->SetFillColor(kPink+9);
  hthb->SetFillColor(kRed+2);
  htho->SetFillColor(kRed-3);
  ht1b->SetFillColor(kBlue-9);
  ht1B->SetFillColor(kBlue-6);
  ht2b->SetFillColor(kBlue-2);
  ht1c->SetFillColor(kGreen-9);
  ht1C->SetFillColor(kGreen-6);
  ht2c->SetFillColor(kGreen-2);
  httl->SetFillColor(kYellow-7);
  hott->SetFillColor(kViolet-4);
  hewk->SetFillColor(kOrange-7);
  httz->SetFillColor(kOrange+8);
  httw->SetFillColor(kOrange+10);
  hvhx->SetFillColor(kOrange-9);
  
  //Blind
  for(int i = 0; i <= hdat->GetNbinsX(); i++){

    float ntot = 0.;
    for(int j = 0; j < hvec.size(); j++){
      ntot += hvec.at(j)->GetBinContent(i);
    }
    if( hthc->GetBinContent(i)/ntot >  0.0005 ){
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

  TH1F* deno = (TH1F*)hvhx->Clone();
  for(int j = 1; j < hvec.size(); j++){
    deno->Add(hvec.at(j));
  }
  
  hdat->SetMinimum(0.001);
  hdat->SetMaximum(1.15*TMath::Max(hdat->GetMaximum(), deno->GetMaximum()));
  hdat->GetYaxis()->SetTitle("Events / bin ");

  if(var.Contains("disc_")) hdat->GetXaxis()->SetRangeUser(0,6.5);
  
  hdat->Draw("PE");
  hs->Draw("histsame");
  hdat->Draw("PEsame");
  hdat->Draw("axissame");

  
  TLegend* leg = new TLegend(0.53,0.56,0.94,0.92);
  leg->SetNColumns(2);
  leg->AddEntry(hdat,"Data","PLE");
  leg->AddEntry(hthc,"ttH(cc)","F");
  leg->AddEntry(ht2c,"t#bar{t}+2c","F");
  leg->AddEntry(ht1C,"t#bar{t}+1C","F");
  leg->AddEntry(ht1c,"t#bar{t}+1c","F");
  leg->AddEntry(ht2b,"t#bar{t}+2b","F");
  leg->AddEntry(ht1B,"t#bar{t}+1B","F");
  leg->AddEntry(ht1b,"t#bar{t}+1b","F");
  leg->AddEntry(httl,"t#bar{t}+light","F");
  leg->AddEntry(httz,"t#bar{t}Z","F");
  leg->AddEntry(httw,"t#bar{t}W","F");
  leg->AddEntry(hthb,"ttH(bb)","F");
  leg->AddEntry(htho,"other ttH","F");
  leg->AddEntry(hott,"other top","F");
  leg->AddEntry(hewk,"electroweak","F");
  leg->AddEntry(hvhx,"VH","F");

  leg->SetBorderSize(0);  
  leg->Draw("same");
  
  TLatex specs;
  specs.SetNDC(); specs.SetTextColor(1);
  specs.SetTextFont(72);
  specs.DrawLatex(0.26,0.89,"ATLAS ");
  specs.SetTextFont(42);
  specs.DrawLatex(0.39,0.89,"Internal ");
  specs.DrawLatex(0.26,0.84,"140 fb^{-1}, 13 TeV");
  
  TH1F* rdat = (TH1F*)hdat->Clone();
  
  // float dint1 = deno->Integral();
  // float dint2 = deno->Integral( deno->GetXaxis()->FindBin(0.9), deno->GetNbinsX() );
  // float dint3 = deno->Integral( deno->GetXaxis()->FindBin(0.98), deno->GetNbinsX() );
  // for(int i = 0; i < hvec.size(); i++){
  //   cout<<100*hvec.at(i)->Integral()/dint1<<" "<<100*hvec.at(i)->Integral(deno->GetXaxis()->FindBin(0.9), deno->GetNbinsX() )/dint2<<" "<<100*hvec.at(i)->Integral(deno->GetXaxis()->FindBin(0.98), deno->GetNbinsX() )/dint3<<endl;
  // }
  
  cthc->SetLineColor(hthc->GetFillColor() );
  cthc->Scale(0.5*deno->Integral()/cthc->Integral());
  cthc->Draw("HISTsame");
  
  for(int i = 0; i < rdat->GetNbinsX(); i++){
    
    if(deno->GetBinContent(i+1) > 0){
      rdat->SetBinContent(i+1, hdat->GetBinContent(i+1)/deno->GetBinContent(i+1));
      rdat->SetBinError(i+1, hdat->GetBinError(i+1)/deno->GetBinContent(i+1));
    }
    else{
      rdat->SetBinContent(i+1,0);
    }    
  }


  rdat->SetMaximum(1.39);
  rdat->SetMinimum(0.801);

  rdat->GetYaxis()->SetTitleOffset(.5);
  rdat->GetYaxis()->SetTitleSize(0.09);
  rdat->GetYaxis()->SetLabelSize(0.09);  
  rdat->GetXaxis()->SetLabelSize(0.10);  
  rdat->GetXaxis()->SetTitleSize(0.11);  
  rdat->GetXaxis()->SetTitleOffset(1.1);  

  rdat->GetYaxis()->SetTitle("data / pred    ");
  if(var.Contains("score")) rdat->GetXaxis()->SetTitle("Transformer ttH(cc) score");
  else if(var.Contains("HT")) rdat->GetXaxis()->SetTitle("H_{T} [GeV]");
  else rdat->GetXaxis()->SetTitle("Transformer ttH(cc) discriminant");

  TF1* line = new TF1("","1",rdat->GetXaxis()->GetXmin(),rdat->GetXaxis()->GetXmax());
  line->SetLineStyle(7);

  pad2->cd();
  
  rdat->Draw("");
  line->Draw("same");
  rdat->Draw("same");

  
  return;
  
}
