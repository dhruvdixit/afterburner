enum Data_t { kReal, kMix} ; 
const Double_t kw = 600;
const Double_t kh = 600;
static const Int_t kN = 9 ; 
const Int_t kmax = 8 ; 
const Double_t ptTr[] ={5., 6., 7., 9.,11.,13.,15.,18.,20., 30., 50.} ;
const Double_t ptAs[] ={1., 3., 4., 5.,8., 10., 15., 20.,25.,30.} ;
Double_t binTr[kN] ;
Double_t binAs[kN] ;
TFile * OpenFile() ; 

void FitPout(TString det = "EMCAL")
{
	TCanvas * canvas1 = new TCanvas("assocaited", "associated particle pt", kw, kh) ;  
	TCanvas * canvas2 = new TCanvas("IcDphi", "IcDphi", kw, kh) ;
	TCanvas * canvas3 = new TCanvas("Dphi", "Dphi", kw, kh) ;  
	
	OpenFile(kReal)->cd("PartCorr") ; 
	//photons
	TList * list = dynamic_cast<TList *>(gDirectory->Get(det.Data())) ; 
	TH2F  * TriggerAssoc = dynamic_cast<TH2F *>(list->FindObject("AnaHadronCorrTrig_PtTrigCharged")) ; 
	TriggerAssoc->Sumw2();
	TH3D  * PoutTrigAssoc = dynamic_cast<TH3D *>(list->FindObject("AnaHadronCorrTrig_PoutPtTrigPtAssoc")) ;
	PoutTrigAssoc->Sumw2();
	TH1F  * TrigPt = dynamic_cast<TH1F *>(list->FindObject("AnaHadronCorrTrig_hPtLeading")) ;
	TrigPt->Sumw2();
	TH2F  * DphiTrig = dynamic_cast<TH2F *>(list->FindObject("AnaHadronCorrTrig_DeltaPhiCharged")) ;  
	DphiTrig->Sumw2();
	//isolated triggers
	TH2F  * IcTriggerAssoc = dynamic_cast<TH2F *>(list->FindObject("AnaHadronCorrIsoTrig_PtTrigCharged")) ; 
	IcTriggerAssoc->Sumw2();
	TH3D  * IcPoutTrigAssoc = dynamic_cast<TH3D *>(list->FindObject("AnaHadronCorrIsoTrig_PoutPtTrigPtAssoc")) ;
	IcPoutTrigAssoc->Sumw2();
	TH1F  * IcTrigPt = dynamic_cast<TH1F *>(list->FindObject("AnaHadronCorrIsoTrig_hPtLeading")) ; 
	IcTrigPt->Sumw2();
	TH2F  * IcDphiTrig = dynamic_cast<TH2F *>(list->FindObject("AnaHadronCorrIsoTrig_DeltaPhiCharged")) ;  
	IcDphiTrig->Sumw2();
	if(det =="EMCAL" || det=="PHOS"){
		TH2F * deltaPhiPi0 = (TH2F*)list->FindObject("AnaHadronCorrPi0_DeltaPhiCharged");
		deltaPhiPi0->Sumw2();
		TH1F * Pi0 =(TH1F*)list->FindObject("AnaHadronCorrPi0_hPtLeading");
		Pi0->Sumw2();
		
		TH2F * deltaPhiIcPi0 = (TH2F*)list->FindObject("AnaHadronCorrIsoPi0_DeltaPhiCharged");
		deltaPhiIcPi0->Sumw2();
		TH1F * IcPi0 =(TH1F*)list->FindObject("AnaHadronCorrIsoPi0_hPtLeading");
		IcPi0->Sumw2();
		TH2F  * Pi0TrigAssoc = dynamic_cast<TH2F *>(list->FindObject("AnaHadronCorrPi0_PtTrigCharged")) ; 
		Pi0TrigAssoc->Sumw2();
		TH2F  * IcPi0TrigAssoc = dynamic_cast<TH2F *>(list->FindObject("AnaHadronCorrIsoPi0_PtTrigCharged")) ; 
		IcPi0TrigAssoc->Sumw2();
	}  
	//triggers for mix event
	OpenFile(kMix)->cd("PartCorr") ; 
	TList * listM = dynamic_cast<TList *>(gDirectory->Get(det.Data())) ; 
	TH2F  * TriggerAssocM = dynamic_cast<TH2F *>(listM->FindObject("AnaHadronCorrTrig_PtTrigCharged")) ; 
	TriggerAssocM->Sumw2();
	TH3D  * PoutTrigAssocM = dynamic_cast<TH3D *>(listM->FindObject("AnaHadronCorrTrig_PoutPtTrigPtAssoc")) ;
	PoutTrigAssocM->Sumw2();
	TH1F  * TrigPtM = dynamic_cast<TH1F *>(listM->FindObject("AnaHadronCorrTrig_hPtLeading")) ; 
	TrigPtM->Sumw2();
	TH2F  * DphiTrigM = dynamic_cast<TH2F *>(listM->FindObject("AnaHadronCorrTrig_DeltaPhiCharged")) ;
	DphiTrigM->Sumw2();
	//isolated trigger
	TH2F  * IcTriggerAssocM = dynamic_cast<TH2F *>(listM->FindObject("AnaHadronCorrIsoTrig_PtTrigCharged")) ; 
	IcTriggerAssocM->Sumw2();
	TH3D  * IcPoutTrigAssocM = dynamic_cast<TH3D *>(listM->FindObject("AnaHadronCorrIsoTrig_PoutPtTrigPtAssoc")) ;
	IcPoutTrigAssocM->Sumw2();
	TH1F  * IcTrigPtM = dynamic_cast<TH1F *>(listM->FindObject("AnaHadronCorrIsoTrig_hPtLeading")) ; 
	IcTrigPtM->Sumw2();
	TH2F  * IcDphiTrigM = dynamic_cast<TH2F *>(listM->FindObject("AnaHadronCorrIsoTrig_DeltaPhiCharged")) ; 
	IcDphiTrigM->Sumw2();
	if(det =="EMCAL" || det=="PHOS"){
		TH2F * deltaPhiPi0M = (TH2F*)listM->FindObject("AnaHadronCorrPi0_DeltaPhiCharged");
		deltaPhiPi0M->Sumw2();
		TH1F * Pi0M =(TH1F*)listM->FindObject("AnaHadronCorrPi0_hPtLeading");
		Pi0M->Sumw2();
		
		TH2F * deltaPhiIcPi0M = (TH2F*)listM->FindObject("AnaHadronCorrIsoPi0_DeltaPhiCharged");
		deltaPhiIcPi0M->Sumw2();
		TH1F * IcPi0M =(TH1F*)listM->FindObject("AnaHadronCorrIsoPi0_hPtLeading");
		IcPi0M->Sumw2();
		
		
	}
	
	for (Int_t index = 0; index <kN; index++) {   
		binTr[index] = TriggerAssoc->GetXaxis()->FindBin(ptTr[index]);
		binAs[index] = TriggerAssoc->GetYaxis()->FindBin(ptAs[index]);
		cout << "Bin = " <<binTr[index] <<" pt = " <<ptTr[index] <<endl;
	}
	Double_t MeanAssoc[kmax] ;
	Double_t MeanTrig[kmax] ;
	Double_t MeanPout[kmax] ;
	Double_t MeanPoutErr[kmax] ;
	Double_t MeanTrigErr[kmax] ;
	Double_t IcMeanPout[kmax] ;
	Double_t IcMeanPoutErr[kmax] ;
	Double_t MeanAsIcTr[kmax] ;
	Double_t MeanIcTr[kmax] ;
	Double_t MeanIcTrErr[kmax] ;
	TF1 *fitAway = new TF1("fitAway",fitAway,-1.5,4.5,4);
	TF1 *fitTsallisAway = new TF1("fitTsallisAway",fitTsallisAway,-1.5,4.5,7);
	if(kmax>1)canvas2->Divide(2, kmax/2);
	if(kmax>1)canvas3->Divide(2, kmax/2);
	TH1F * TrigProj = TrigPt->Clone("TrigProj");
	TH1F * IcTrigProj = IcTrigPt->Clone("IcTrigProj");
	Double_t nearA =0.0 ;
	Double_t awayA =0.0;
	Double_t nearW =0.0 ;
	Double_t awayW =0.0 ;  
	Double_t ped, icped ;
	if(det =="EMCAL" || det=="PHOS"){
	//    TCanvas * canvas22 = new TCanvas("IcPi0Dphi", "IcPi0Dphi", kw, kh) ;
	//    TCanvas * canvas33 = new TCanvas("pi0Dphi", "pi0Dphi", kw, kh) ; 
	//    canvas22->Divide(2, kmax/2);
	//    canvas33->Divide(2, kmax/2);
		TH1F * Pi0TrigProj = Pi0->Clone("TrigProj");
		TH1F * IcPi0TrigProj = IcPi0->Clone("IcTrigProj");
		Double_t MeanAsPi0Tr[kmax] ;
		Double_t MeanPi0Tr[kmax] ;
		Double_t MeanPoutPi0Tr[kmax] ;
		Double_t MeanPoutPi0TrErr[kmax] ;
		Double_t MeanPi0TrErr[kmax] ;
		Double_t MeanAsIcPi0Tr[kmax] ;
		Double_t MeanIcPi0Tr[kmax] ;
		Double_t MeanPoutIcPi0Tr[kmax] ;
		Double_t MeanPoutIcPi0TrErr[kmax] ;
		Double_t MeanIcPi0TrErr[kmax] ;
		
	}
	for (Int_t index = 0; index <kmax; index++) {  
		Double_t nTrig = TrigPt->Integral(binTr[index], -1); 
		Double_t nTrigM = TrigPtM->Integral(binTr[index], -1); 
		Double_t nIcTrig = IcTrigPt->Integral(binTr[index], -1); 
		Double_t nIcTrigM = IcTrigPtM->Integral(binTr[index], -1);  
		canvas1->cd();
		canvas1->SetLogy();
		canvas1->SetFillColor(0);
		canvas1->SetBorderSize(0);
		canvas1->SetFrameBorderMode(0);     
		TLegend  * l1 = new TLegend(0.4, 0.6, 0.75, 0.85);
		l1->SetFillColor(0);
		l1->SetBorderSize(0);
		l1->SetTextSize(0.04);         
		TH1F* AssocPt = (TH1F*)TriggerAssoc->ProjectionY(Form("TrigPt%1.0f", ptTr[index]), binTr[index], -1, "") ; 
		AssocPt->Scale(1./nTrig) ;
		AssocPt->Scale(1./AssocPt->GetBinWidth(ptTr[index]));    
		TH1F* IcTrAsPt = (TH1F*)IcTriggerAssoc->ProjectionY(Form("IcTrigPt%1.f", ptTr[index]), IcTriggerAssoc->GetXaxis()->FindBin(ptTr[index]), -1, "") ; 
		IcTrAsPt->Scale(1./nIcTrig);
		IcTrAsPt->Scale(1./IcTrAsPt->GetBinWidth(1));
		
		//mean trigger calculation
		TrigProj->SetAxisRange(ptTr[index],50., "X");
		MeanTrig[index]=TrigProj->GetMean();
		MeanTrigErr[index]=TrigProj->GetMeanError();
		IcTrigProj->SetAxisRange(ptTr[index],50., "X");
		MeanIcTr[index]=IcTrigProj->GetMean();
		MeanIcTrErr[index]=IcTrigProj->GetMeanError();
		MeanAssoc[index]=AssocPt->GetMean();
		MeanAsIcTr[index]=IcTrAsPt->GetMean();
		
		AssocPt->SetAxisRange(0, 20.,"X");
		AssocPt->SetAxisRange(1.e-3, 10.,"Y");
		AssocPt->SetLineColor(index+1);
		AssocPt->SetMarkerStyle(20+index);
		AssocPt->SetMarkerColor(index+1);      
		if(index==0) AssocPt->Draw();
		else AssocPt->Draw("same") ;
		l1->AddEntry(AssocPt, Form("p_{T}^{trig} > %1.0f GeV/c", ptTr[index]), "l");
		l1->Draw("same");
		canvas1->Update();
		
		TH1F* corr = (TH1F*)DphiTrig->ProjectionY(Form("DphiPt%1.0f", ptTr[index]), binTr[index], -1, "") ;
		corr->Scale(1./TrigPt->Integral(TrigPt->FindBin(ptTr[index]), -1)) ;
		corr->Rebin(4);
		corr->Scale(1./corr->GetBinWidth(1));
		TH1F* corrM = (TH1F*)DphiTrigM->ProjectionY(Form("DphiMPt%1.f", ptTr[index]), binTr[index], -1, "") ;
		corrM->Scale(1./TrigPtM->Integral(TrigPtM->FindBin(ptTr[index]), -1)) ;
		corrM->Rebin(4);
		corrM->Scale(1./corrM->GetBinWidth(1));
		Double_t ZYAM = corrM->GetBinContent(corrM->FindBin(TMath::PiOver2()))/corr->GetBinContent(corr->FindBin(TMath::PiOver2()));
		corrM->Scale(1./ZYAM);
		
		TH1F* IcCorr = (TH1F*)IcDphiTrig->ProjectionY(Form("IcDphiPt%1.f", ptTr[index]), binTr[index], -1, "") ;
		IcCorr->Scale(1./IcTrigPt->Integral(IcTrigPt->FindBin(ptTr[index]), -1)) ;
		IcCorr->Rebin(4);
		IcCorr->Scale(1./IcCorr->GetBinWidth(1));
		TH1F* IcCorrM = (TH1F*)IcDphiTrigM->ProjectionY(Form("IcDphiMPt%1.f", ptTr[index]), binTr[index], -1, "") ;
		IcCorrM->Scale(1./IcTrigPtM->Integral(TrigPtM->FindBin(ptTr[index]), -1));
		IcCorrM->Rebin(4);
		IcCorrM->Scale(1./IcCorrM->GetBinWidth(1));
		Double_t IcZYAM = IcCorrM->GetBinContent(IcCorrM->FindBin(TMath::PiOver2()))/IcCorr->GetBinContent(IcCorr->FindBin(TMath::PiOver2()));
		if(IcCorr->GetBinContent(IcCorr->FindBin(TMath::PiOver2()))) {     
			Double_t IcZYAM = IcCorrM->GetBinContent(IcCorrM->FindBin(TMath::PiOver2()))/IcCorr->GetBinContent(IcCorr->FindBin(TMath::PiOver2()));
			IcCorrM->Scale(1./IcZYAM); 
		//  IcCorr->Add(IcCorrM, -1);
		}
		else{     
			Double_t IcZYAM = corrM->GetBinContent(corrM->FindBin(TMath::PiOver2()))/IcCorr->GetBinContent(IcCorr->FindBin(TMath::PiOver2()));
		// corrM->Scale(1./IcZYAM);
		//  IcCorr->Add(corrM, -1);
		} 
		if(ped || icped) ped=icped=0.0 ;  
		IcCorrM->Fit("pol0", "", "NO", -1.5, 4.5);
		icped = IcCorrM->GetFunction("pol0")->GetParameter(0);
		corrM->Fit("pol0", "", "", -1.5, 4.5);
		Double_t ped = corrM->GetFunction("pol0")->GetParameter(0);
		
		canvas2->cd();    
		canvas2->cd(index+1)->SetFillColor(0);
		canvas2->cd(index+1)->SetBorderSize(0);
		canvas2->cd(index+1)->SetFrameBorderMode(0); 
		if(IcCorr->GetEntries()){
			fitAway->ReleaseParameter(0);
			fitAway->ReleaseParameter(2);
			if(awayA || awayW) awayA=awayW=0.0 ;
			fitAway->SetParameter(0, 10.);//set constant
			if(icped <=0.)fitAway->SetParameter(0, IcCorr->GetBinContent(IcCorr->FindBin(TMath::PiOver2())));//set constant
			awayA = IcCorr->GetBinContent(IcCorr->FindBin(TMath::Pi())) ;
			awayW = IcCorr->GetBinCenter(IcCorr->FindLastBinAbove(awayA/2.))-IcCorr->GetBinCenter(IcCorr->FindBin(TMath::Pi()));
			fitAway->SetParameter(1, awayA); //set amplitude of away side peak
			fitAway->FixParameter(2,MeanAssoc[index]);// associated pt 
			fitAway->SetParameter(3,2.*awayW*awayW);//set pout2
			IcCorr->Fit("fitAway", "","",1.5, 4.5);
			IcCorr->GetFunction("fitAway")->SetLineColor(2);
			IcMeanPout[index] = TMath::Sqrt(IcCorr->GetFunction("fitAway")->GetParameter(3));
			IcMeanPoutErr[index] = 0.5*IcCorr->GetFunction("fitAway")->GetParError(3)/IcCorr->GetFunction("fitAway")->GetParameter(3);
			IcMeanPoutErr[index]*=IcMeanPout[index];
		}
		IcCorr->SetAxisRange(-1.5, 4.5,"X");
		IcCorr->SetLineColor(1);
		IcCorr->SetMarkerStyle(20);
		IcCorr->SetMarkerColor(1);   
		IcCorr->Draw("same") ;
		//IcCorrM->Draw("same");
		TLegend  * l2 = new TLegend(0.3, 0.6, 0.45, 0.75);
		l2->SetFillColor(0);
		l2->SetBorderSize(0);
		l2->SetTextSize(0.1);  
		l2->AddEntry(IcCorr, Form("p_{T}^{trig} > %1.0f GeV/c", ptTr[index]), "");
		l2->Draw("same");    
		canvas2->Update() ;
		
		canvas3->cd();
		canvas3->cd(index+1)->SetFillColor(0);
		canvas3->cd(index+1)->SetBorderSize(0);
		canvas3->cd(index+1)->SetFrameBorderMode(0); 
		corr->SetAxisRange(-1.5, 4.5,"X");   
		corr->SetMinimum(0.);
		corr->SetXTitle("#Delta #phi ");
		corr->SetYTitle("1/N_{trig} dN/d#Delta #phi ");
		corr->SetTitle("");    
		corr->SetLineColor(1);
		corr->SetMarkerStyle(20);
		corr->SetMarkerColor(1);   
		
		if(corr->GetEntries()){
			fitTsallisAway->ReleaseParameter(0);
			fitTsallisAway->ReleaseParameter(5);
			if(nearA || awayA || nearW || awayW) nearA=awayA=nearW=awayW=0.0 ;
			//fitting parameters setting
			fitTsallisAway->SetParameter(0, ped);//set constant
		// if(ped <=0.)fitTsallisAway->SetParameter(0, corr->GetBinContent(corr->FindBin(TMath::PiOver2())));//set constant
			nearA = corr->GetBinContent(corr->FindBin(0.));
			awayA = corr->GetBinContent(corr->FindBin(TMath::Pi())) ;
			nearW = corr->GetBinCenter(corr->FindLastBinAbove(nearA/2.))-corr->GetBinCenter(corr->FindFirstBinAbove(nearA/2.));
			awayW = corr->GetBinCenter(corr->FindLastBinAbove(awayA/2.))-corr->GetBinCenter(corr->FindBin(TMath::Pi()));
			fitTsallisAway->SetParameter(1, nearA); //set amplitude of near side peak
			fitTsallisAway->SetParameter(2,12);//set beta Near
			fitTsallisAway->SetParameter(3,1.5);//set parameter q Near
			fitTsallisAway->SetParameter(4, awayA);//set amplitude of away side peak 
			fitTsallisAway->FixParameter(5, MeanAssoc[index]); // associated pt 
			fitTsallisAway->SetParameter(6,2.*awayW*awayW);//set pout2 
			corr->Fit("fitTsallisAway", "","",-1.5, 4.5);
			corr->GetFunction("fitTsallisAway")->SetLineColor(2);
			MeanPout[index] = TMath::Sqrt(corr->GetFunction("fitTsallisAway")->GetParameter(6));
			MeanPoutErr[index] = 0.5*corr->GetFunction("fitTsallisAway")->GetParError(6)/corr->GetFunction("fitTsallisAway")->GetParameter(6);
			MeanPoutErr[index]*=MeanPout[index];
		}
	
		corr->Draw("same PE");
		TLegend  * l3 = new TLegend(0.4, 0.6, 0.75, 0.85);
		l3->SetFillColor(0);
		l3->SetBorderSize(0);
		l3->SetTextSize(0.04);
		l3->AddEntry(corr, Form("p+p->Triger(%s)+X", det.Data()), "");
		l3->AddEntry(corr, Form("p_{T}^{trig} > %1.0f GeV/c", ptTr[index]), "");
		l3->Draw("same");
		
		canvas3->Update() ;
	}
	TCanvas * canvas4 = new TCanvas("Mean", Form("Mean associated vs Mean Trigger") , kw, kh) ;  
	TGraph * assoc    = new TGraph(kmax, MeanTrig, MeanAssoc) ;
	TGraph * icassoc    = new TGraph(kmax, MeanIcTr, MeanAsIcTr) ;
	
	canvas4->cd();
	canvas4->SetFillColor(0);
	canvas4->SetBorderSize(0);
	canvas4->SetFrameBorderMode(0); 
	gStyle->SetOptStat(0);  
	TH1F * dummy = new TH1F("dummy", "dummy", 100, 0., 50.); 
	dummy->SetTitle("") ; 
	dummy->SetStats(kFALSE) ; 
	dummy->SetAxisRange(0., 10., "Y") ; 
	dummy->SetAxisRange(5., 30., "X") ; 
	dummy->GetXaxis()->SetTitle("<p_{T}^{trig}> (GeV/c)");
	dummy->GetYaxis()->SetTitle("<p_{T}^{assoc}> (GeV/c)");
	dummy->Draw(); 
	assoc->SetLineColor(1);
	assoc->SetLineWidth(2);
	assoc->SetMarkerStyle(20);
	assoc->SetMarkerColor(1);
	assoc->SetMarkerSize(1.5);
	assoc->Draw("same PE") ;   
	icassoc->SetLineColor(2);
	icassoc->SetLineWidth(2);
	icassoc->SetMarkerStyle(22);
	icassoc->SetMarkerColor(2);
	icassoc->SetMarkerSize(1.5);
	icassoc->Draw("same PE") ;   
	TLegend  * l4 = new TLegend(0.15, 0.65, 0.55, 0.88);
	l4->SetFillColor(0);
	l4->SetBorderSize(0);
	l4->SetTextSize(0.05);
	l4->AddEntry(assoc,Form("pp@7TeV:Trigger->%s", det.Data()),"");
	l4->AddEntry(assoc, "IC: R =0.4, #varepsilon = 0.1", "");
	if(det =="EMCAL" || det =="PHOS"){  
		l4->AddEntry(assoc,"cluster trigger: w/o IC","P");
		l4->AddEntry(icassoc,"cluster trigger: w/ IC","P");
	}
	else {
		l4->AddEntry(assoc,"charged trigger: w/o IC","P");
		l4->AddEntry(icassoc,"chraged trigger: w/ IC","P");
	}
	l4->Draw("same");
	canvas4->Update() ;
	
	
	TCanvas * canvas5 = new TCanvas("MeanPout", Form("Mean Pout vs Mean Trigger") , kw, kh) ;        
	// TGraph * pout    = new TGraph(kmax, MeanTrig, MeanPout) ;
	TGraphErrors * pout = new TGraphErrors(kmax, MeanTrig, MeanPout, MeanTrigErr, MeanPoutErr) ;
	TGraphErrors * icpout = new TGraphErrors(kmax, MeanIcTr, IcMeanPout, MeanIcTrErr, IcMeanPoutErr) ;
	canvas5->cd();
	canvas5->SetFillColor(0);
	canvas5->SetBorderSize(0);
	canvas5->SetFrameBorderMode(0); 
	gStyle->SetOptStat(0);  
	TH1F * base = new TH1F("base", "base", 100, 0., 50.); 
	base->SetTitle("") ; 
	base->SetStats(kFALSE) ; 
	base->SetAxisRange(0., 5., "Y") ; 
	base->SetAxisRange(5., 30., "X") ;   
	base->GetXaxis()->SetTitle("<p_{T}^{trig}> (GeV/c)");
	base->GetYaxis()->SetTitle("#surd(<p_{out}^{2}>) (GeV/c)");
	base->Draw(); 
	pout->SetLineColor(1);
	pout->SetLineWidth(1.5);
	pout->SetMarkerStyle(20);
	pout->SetMarkerColor(1);
	pout->SetMarkerSize(1.5);
	pout->Draw("same P") ;   
	icpout->SetLineColor(1);
	icpout->SetLineWidth(2);
	icpout->SetMarkerStyle(21);
	icpout->SetMarkerColor(1);
	icpout->SetMarkerSize(1.5);
	icpout->Draw("same P") ;   
	TLegend  * l5 = new TLegend(0.4, 0.6, 0.75, 0.85);
	l5->SetFillColor(0);
	l5->SetBorderSize(0);
	l5->SetTextSize(0.04);   
	l5->AddEntry(pout,Form("pp@7TeV:Trigger->%s", det.Data()),"");
	l5->AddEntry(pout, "IC: R =0.4, #varepsilon = 0.1", "");
	if(det =="EMCAL" || det =="PHOS"){
		l5->AddEntry(pout,"cluster trigger: w/o IC","P");
		l5->AddEntry(icpout,"cluster trigger: w/ IC","P");
	}
	else {
		l5->AddEntry(pout,"charged trigger: w/o IC","P");
		l5->AddEntry(icpout,"chraged trigger: w/ IC","P");
	}
	l5->Draw("same");
	canvas5->Update() ;            	
}

TFile * OpenFile(Data_t index){
	const char * kHomeDir = "/Users/ymao/group/ana/7TeV/corr/anaAOD" ; 
	const char * fileName = "anaCorrLHC10bceAllGoodAodIcR04Frac01_Pt2_1.root" ; 
	const char * fileNameMix = "anaMixLHC10bceAllGoodAodIcR04Frac01_Pt2_1.root" ; 
	
	TString sfile(Form("%s/%s", kHomeDir, fileName));
	if(index == kMix) TString sfile(Form("%s/%s", kHomeDir, fileNameMix));
	return TFile::Open(sfile.Data()) ; 
}

Double_t tsallis(Double_t *x, Double_t *par){
	Double_t tsallis;
	// Fit of the azimuthal corr. function with Tsallis+Tsallis + const  
	tsallis = par[0] +  par[1]*pow(1 - par[2]*(1-par[3])*x[0]*x[0],1/(1-par[3])) 
	+ par[4]*pow(1 - par[5]*(1-par[6])*(x[0]-TMath::Pi())*(x[0]-TMath::Pi()),1/(1-par[6]));
	return tsallis ;
}

Double_t gaus(Double_t *x, Double_t *par){
	Double_t gaus;
	gaus = par[0] * TMath::Exp( -(x[0]-par[1])*(x[0]-par[1]) /
										(2*par[2]*par[2]) );
	return gaus ;
}

Double_t fitDphi(Double_t *x, Double_t *par){
	Double_t dphi;
	dphi = par[0] +par[1]*TMath::Exp(-x[0]*x[0]/(2*par[2]))
	+par[3]*(-par[4]*TMath::Cos(x[0])/(TMath::Sqrt(2*TMath::Pi()*par[5])*TMath::Erf(TMath::Sqrt(2)*par[4]/TMath::Sqrt(par[5])))
				*TMath::Exp(-par[4]*par[4]*TMath::Sin(x[0])*TMath::Sin(x[0])/(2*par[5])));
	return dphi ;
}

//fit only on the away side to get <pout2>
Double_t fitAway(Double_t *x, Double_t *par){
	Double_t fitAway;
	fitAway = par[0]+par[1]*(-par[2]*TMath::Cos(x[0])/(TMath::Sqrt(2*TMath::Pi()*par[3])*TMath::Erf(TMath::Sqrt(2)*par[2]/TMath::Sqrt(par[3])))
										*TMath::Exp(-par[2]*par[2]*TMath::Sin(x[0])*TMath::Sin(x[0])/(2*par[3])));
	return fitAway ;
}

//fit with tsallis at the near side and the PHENIX formula for away side
Double_t fitTsallisAway(Double_t *x, Double_t *par){
	Double_t fitTsallisAway;
	fitTsallisAway = par[0]+  par[1]*pow(1 - par[2]*(1-par[3])*x[0]*x[0],1/(1-par[3])) 
	+par[4]*(-par[5]*TMath::Cos(x[0])/(TMath::Sqrt(2*TMath::Pi()*par[6])*TMath::Erf(TMath::Sqrt(2)*par[5]/TMath::Sqrt(par[6])))
				*TMath::Exp(-par[5]*par[5]*TMath::Sin(x[0])*TMath::Sin(x[0])/(2*par[6])));
	return fitTsallisAway ;
}


