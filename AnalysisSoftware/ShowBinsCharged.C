{
	TString fileNameChargedSpectra2760GeV = "charged_dNdPt_pp_276.root";
	TFile* fileCharged2760GeV = 		new TFile(fileNameChargedSpectra2760GeV);
	TH1D* histoCharged2760GeV = 		(TH1D*)fileCharged2760GeV->Get("dNdPt_276");	
	

	TFile* fileInput("RAABaseOutput.root");  
	TH1D* histoPtpp = 		(TH1D*)fileInput->Get("trackPt_pp");	
	
	for (Int_t i = 0; i < histoPtpp->GetNbinsX()+1; i++){
		histoPtpp->SetBinContent(histoPtpp->GetBinContent(i)/histoPtpp->GetBinCenter(i))
	}
	
	histoPtpp->Scale(1/1.6);
	histoPtpp->Scale(1/(2*TMath::Pi()));
									
									
}