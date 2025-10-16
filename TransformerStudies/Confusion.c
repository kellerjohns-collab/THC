void Confusion(TString split = "2", TString var = "score", bool reconorm = false){

  TFile* fthc = new TFile("THC_hists/v3_split"+split+"/hist-ttH_cc.root");
  TFile* fthb = new TFile("THC_hists/v3_split"+split+"/hist-ttH_bb.root");
  TFile* ftho = new TFile("THC_hists/v3_split"+split+"/hist-ttH_other.root");  
  TFile* ft1b = new TFile("THC_hists/v3_split"+split+"/hist-tt1b.root");
  TFile* ft1B = new TFile("THC_hists/v3_split"+split+"/hist-tt1B.root");
  TFile* ft2b = new TFile("THC_hists/v3_split"+split+"/hist-tt2b.root");
  TFile* ft1c = new TFile("THC_hists/v3_split"+split+"/hist-tt1c.root");
  TFile* ft1C = new TFile("THC_hists/v3_split"+split+"/hist-tt1C.root");
  TFile* ft2c = new TFile("THC_hists/v3_split"+split+"/hist-tt2c.root");
  TFile* fttl = new TFile("THC_hists/v3_split"+split+"/hist-ttlight.root");
  TFile* fott = new TFile("THC_hists/v3_split"+split+"/hist-othertop.root");
  TFile* fewk = new TFile("THC_hists/v3_split"+split+"/hist-EWK.root");
  TFile* fttz = new TFile("THC_hists/v3_split"+split+"/hist-ttZ.root");
  TFile* fttw = new TFile("THC_hists/v3_split"+split+"/hist-ttW.root");
  TFile* fvhx = new TFile("THC_hists/v3_split"+split+"/hist-VH.root");

  vector<TString> labels;
  if(split == "2") labels = {"ttH_cc","ttH_bkg", "ttV", "otherbkg", "ttlight", "tt1c1C", "tt2c", "tt1b1B", "tt2b"};
  else if(split == "3") labels = {"ttH_cc","ttH_bkg", "ttV", "otherbkg", "ttlight", "tt1c", "tt1C2c", "tt1b", "tt1B2b"};
  else if(split == "4") labels = {"ttH_cc","ttH_bkg", "ttV", "otherbkg", "ttlight", "tt1c", "tt1C", "tt2c", "tt1b", "tt1B", "tt2b"};

  int ncat = labels.size();
  
  TH1F* hthc = (TH1F*)fthc->Get("region_"+var);
  TH1F* hthb = (TH1F*)fthb->Get("region_"+var);
  TH1F* htho = (TH1F*)ftho->Get("region_"+var);
  TH1F* ht1b = (TH1F*)ft1b->Get("region_"+var);
  TH1F* ht1B = (TH1F*)ft1B->Get("region_"+var);
  TH1F* ht2b = (TH1F*)ft2b->Get("region_"+var);
  TH1F* ht1c = (TH1F*)ft1c->Get("region_"+var);
  TH1F* ht1C = (TH1F*)ft1C->Get("region_"+var);
  TH1F* ht2c = (TH1F*)ft2c->Get("region_"+var);
  TH1F* httl = (TH1F*)fttl->Get("region_"+var);
  TH1F* hott = (TH1F*)fott->Get("region_"+var);
  TH1F* hewk = (TH1F*)fewk->Get("region_"+var);
  TH1F* httz = (TH1F*)fttz->Get("region_"+var);
  TH1F* httw = (TH1F*)fttw->Get("region_"+var);
  TH1F* hvhx = (TH1F*)fvhx->Get("region_"+var);

  hthb->Add(htho);
  httz->Add(httw);
  hewk->Add(hott);
  hewk->Add(hvhx);

  if(split == "2"){
    ht1c->Add(ht1C);
    ht1b->Add(ht1B);
  }

  if(split == "3"){
    ht2c->Add(ht1C);
    ht2b->Add(ht1B);
  }

  vector<TH1F*> hvec;
  hvec.push_back(hthc);
  hvec.push_back(hthb);
  hvec.push_back(httz);
  hvec.push_back(hewk);
  hvec.push_back(httl);
  hvec.push_back(ht1c);
  if(split == "4") hvec.push_back(ht1C);
  hvec.push_back(ht2c);
  hvec.push_back(ht1b);
  if(split == "4") hvec.push_back(ht1B);
  hvec.push_back(ht2b);

  if(hvec.size() != ncat) return;
  
  //here figure out normalization
  if(!reconorm){
    for(int i = 0; i < ncat;  i++){
      hvec.at(i)->Scale(1./hvec.at(i)->Integral());
    }
  }
		

  TH2F* cmat = new TH2F("cmat","",ncat,0.,ncat,ncat,0,ncat);
  for(int i = 0; i < ncat; i++){
    for(int b = 1; b <= ncat; b++){
      cmat->SetBinContent(b+(i+1)*(ncat+2), round(1000.*hvec.at(i)->GetBinContent(b))/1000.);
    }
    cmat->GetXaxis()->SetBinLabel(i+1, labels.at(i));
    cmat->GetYaxis()->SetBinLabel(i+1, labels.at(i));
  }

  if(reconorm){

    for(int b = 1; b <= ncat; b++){
      float sumcat = 0.;
      for(int i = 1; i <= ncat; i++){
	sumcat += cmat->GetBinContent( b+i*(ncat+2) );
      }
      for(int i = 1; i <= ncat; i++){
	cmat->SetBinContent( b+i*(ncat+2), round(10000.*cmat->GetBinContent( b+i*(ncat+2))/sumcat)/10000. );
      }
    }
    
  }
  
  cmat->GetXaxis()->SetTitle("Reco category");
  cmat->GetYaxis()->SetTitle("True category");

  TCanvas* c1 = new TCanvas("c1","c1",10,10,900,900);
  cmat->Draw("COLTEXT");

}
