#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TPaveLabel.h>
#include <TSystem.h>
#include <TFrame.h>
#include <TStyle.h>
#include <TString.h>
#include "TGaxis.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TF1.h"
#include "TVirtualFitter.h"
#include "TObject.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TTree.h"
#include "TMinuit.h"
#include "TLatex.h"
#include "TMath.h"
#include "TPostScript.h"
#include "TGraphErrors.h"
#include "TArrow.h"
#include "TGraphAsymmErrors.h"
#include "TGaxis.h"
#include "TMarker.h"
#include "TVectorT.h"
#include "TDatabasePDG.h"
#include "TASImage.h"

#include "PlottingGammaConversionHistos.h"
#include "PlottingGammaConversionAdditional.h"
#include "PlottingCorrelation.h"
#include "CorrelationBinning.h"

TH1D** 	fHistoDataCorrelationGammadPhiCh=				NULL;
TF1** 	fFitDataCorrelationGammadPhiChAwaySide=		NULL;
TH1D** 	fHistoDataCorrelationGammadEtaCh=				NULL;
TH1D** 	fHistoDataCorrelationGammadPhiCh_minPtAss1=	NULL;
TF1** 	fFitDataCorrelationGammadPhiChAwaySide_minPtAss1=		NULL;
TH1D** 	fHistoDataCorrelationGammadEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoDataCorrelationGammadPhiCh_minPtAss05=NULL;
TF1** 	fFitDataCorrelationGammadPhiChAwaySide_minPtAss05=		NULL;
TH1D** 	fHistoDataCorrelationGammadEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoDataCorrelationGammaIsoMin=				NULL;
TH1D** 	fHistoDataCorrelationGammaIsodPhiCh=				NULL;
TH1D** 	fHistoDataCorrelationGammaIsodEtaCh=				NULL;
TH1D** 	fHistoDataCorrelationGammaIsodPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoDataCorrelationGammaIsodEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoDataCorrelationGammaIsodPhiCh_minPtAss05=NULL;
TH1D** 	fHistoDataCorrelationGammaIsodEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCRecCorrelationGammadPhiCh=				NULL;
TH1D** 	fHistoMCRecCorrelationGammadEtaCh=				NULL;
TH1D** 	fHistoMCRecCorrelationGammadPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCRecCorrelationGammadEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCRecCorrelationGammadPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCRecCorrelationGammadEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCRecCorrelationGammaIsoMin=				NULL;
TH1D** 	fHistoMCRecCorrelationGammaIsodPhiCh=				NULL;
TH1D** 	fHistoMCRecCorrelationGammaIsodEtaCh=				NULL;
TH1D** 	fHistoMCRecCorrelationGammaIsodPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCRecCorrelationGammaIsodEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCRecCorrelationGammaIsodPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCRecCorrelationGammaIsodEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCTrueCorrelationGammadPhiCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationGammadEtaCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationGammadPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCTrueCorrelationGammadEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCTrueCorrelationGammadPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCTrueCorrelationGammadEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCTrueCorrelationGammaIsoMin=				NULL;
TH1D** 	fHistoMCTrueCorrelationGammaIsodPhiCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationGammaIsodEtaCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationGammaIsodPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCTrueCorrelationGammaIsodEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCTrueCorrelationGammaIsodPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCTrueCorrelationGammaIsodEtaCh_minPtAss05=NULL;   

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

//fit with tsallis at the near side and the PHENIX formula for away side
Double_t fitPureTsallisAwaySide(Double_t *x, Double_t *par){
	Double_t fitTsallisAway;
	fitTsallisAway = par[0]+  par[1]*pow(1 - par[2]*(1-par[3])*x[0]*x[0],1/(1-par[3])) 
	+par[4]*(-par[5]*TMath::Cos(x[0])/(TMath::Sqrt(2*TMath::Pi()*par[6])*TMath::Erf(TMath::Sqrt(2)*par[5]/TMath::Sqrt(par[6])))
				*TMath::Exp(-par[5]*par[5]*TMath::Sin(x[0])*TMath::Sin(x[0])/(2*par[6])));
	return fitTsallisAway ;
}

//fit only on the away side to get <pout2>
Double_t fitPureAwaySide(Double_t *x, Double_t *par){
	Double_t fitAway;
	fitAway = par[0]+par[1]*(-par[2]*TMath::Cos(x[0])/(TMath::Sqrt(2*TMath::Pi()*par[3])*TMath::Erf(TMath::Sqrt(2)*par[2]/TMath::Sqrt(par[3])))
										*TMath::Exp(-par[2]*par[2]*TMath::Sin(x[0])*TMath::Sin(x[0])/(2*par[3])));
	return fitAway ;
}


TF1* FitPout(TH1D* histoDPhi){
	
	Double_t MeanAssoc ;
	Double_t MeanPout ;
	Double_t MeanPoutErr ;
	Double_t IcMeanPout ;
	Double_t IcMeanPoutErr ;
	TF1 *fitAway = new TF1("fitAway",fitPureAwaySide,1.5,4.5,4);
	TF1 *fitTsallisAway = new TF1("fitTsallisAway",fitPureTsallisAwaySide,-1.5,4.5,7);
	Double_t nearA =0.0 ;
	Double_t awayA =0.0;
	Double_t nearW =0.0 ;
	Double_t awayW =0.0 ;  
	Double_t ped, icped ;
		
	/*if(histoDPhi->GetEntries()){
		fitAway->ReleaseParameter(0);
		fitAway->ReleaseParameter(2);
		if(awayA || awayW) awayA=awayW=0.0 ;
		fitAway->SetParameter(0, 10.);//set constant
		fitAway->SetParameter(2, 1.);//set constant
// 		fitAway->SetParameter(0, histoDPhi->GetBinContent(histoDPhi->FindBin(TMath::PiOver2())));//set constant
		awayA = histoDPhi->GetBinContent(histoDPhi->FindBin(TMath::Pi())) ;
		awayW = histoDPhi->GetBinCenter(histoDPhi->FindLastBinAbove(awayA/2.))-histoDPhi->GetBinCenter(histoDPhi->FindBin(TMath::Pi()));
		fitAway->SetParameter(1, awayA); //set amplitude of away side peak
		fitAway->SetParameter(3,2.*awayW*awayW);//set pout2
		cout << "Parameters set to: " << awayA << "\t" << 2.*awayW*awayW << "\t" << endl;
		cout << "start fitting" << endl;
		histoDPhi->Fit("fitAway", "V+","ep");

// 		histoDPhi->GetFunction("fitAway")->SetLineColor(2);
		IcMeanPout = TMath::Sqrt(histoDPhi->GetFunction("fitAway")->GetParameter(3));
		IcMeanPoutErr = 0.5*histoDPhi->GetFunction("fitAway")->GetParError(3)/histoDPhi->GetFunction("fitAway")->GetParameter(3);
		IcMeanPoutErr*=IcMeanPout;
		cout << IcMeanPout << endl;
	}
	*/
	/*histoDPhi->SetAxisRange(-1.5, 4.5,"X");
	histoDPhi->SetLineColor(1);
	histoDPhi->SetMarkerStyle(20);
	histoDPhi->SetMarkerColor(1);   
	*/	
	if(histoDPhi->GetEntries()){
		fitTsallisAway->ReleaseParameter(0);
		fitTsallisAway->ReleaseParameter(5);
		if(nearA || awayA || nearW || awayW) nearA=awayA=nearW=awayW=0.0 ;
		//fitting parameters setting
		Double_t averageBG = (histoDPhi->GetBinContent(histoDPhi->FindBin(TMath::Pi()/2))+ histoDPhi->GetBinContent(histoDPhi->FindBin(-TMath::Pi()/2)))/2;
		fitTsallisAway->SetParameter(0, averageBG);//set constant
	// if(ped <=0.)fitTsallisAway->SetParameter(0, histoDPhi->GetBinContent(histoDPhi->FindBin(TMath::PiOver2())));//set constant
		
		nearA = histoDPhi->GetBinContent(histoDPhi->FindBin(0.)) -averageBG;
		awayA = histoDPhi->GetBinContent(histoDPhi->FindBin(TMath::Pi()))- averageBG ;
		nearW = histoDPhi->GetBinCenter(histoDPhi->FindLastBinAbove(nearA/2.+averageBG))-histoDPhi->GetBinCenter(histoDPhi->FindFirstBinAbove(nearA/2.+averageBG));
		awayW = histoDPhi->GetBinCenter(histoDPhi->FindLastBinAbove(awayA/2.+averageBG))-histoDPhi->GetBinCenter(histoDPhi->FindFirstBinAbove(awayA/2.+averageBG));
		if (awayW > TMath::Pi()) awayW = TMath::Pi();
		if (nearW > TMath::Pi()) nearW = TMath::Pi();
		cout << "Parameters:\t" << nearA << "\t" << nearW << "\t" << awayA << "\t" << awayW << "\t" << averageBG<< endl;
		fitTsallisAway->SetParameter(1, nearA+averageBG); //set amplitude of near side peak
		fitTsallisAway->SetParameter(2,12);//set beta Near
		fitTsallisAway->SetParameter(3,1.5);//set parameter q Near
		fitTsallisAway->SetParameter(5, 0.5); // associated pt 
		fitTsallisAway->SetParLimits(5, 0.2,5.); // associated pt 
		fitTsallisAway->SetParameter(4, awayA+averageBG);//set amplitude of away side peak 
		fitTsallisAway->SetParameter(6,2.*awayW*awayW);//set pout2 
		histoDPhi->Fit("fitTsallisAway", "VQ0","ep");//QNRME
		histoDPhi->GetFunction("fitTsallisAway")->SetLineColor(2);
		MeanPout = TMath::Sqrt(histoDPhi->GetFunction("fitTsallisAway")->GetParameter(6));
		MeanPoutErr = 0.5*histoDPhi->GetFunction("fitTsallisAway")->GetParError(6)/histoDPhi->GetFunction("fitTsallisAway")->GetParameter(6);
		MeanPoutErr*=MeanPout;
	}

	if (fitTsallisAway) 	return  fitTsallisAway;	
		else return 0x0;
}

void FillHistoArray(TH2D* fHisto2DDummy, TH1D** &fHistoArrayPtBins, Int_t fStartBinPtRange, Int_t fNumberOfPtBins, Double_t* fBinsPtFilling, TString nameHistoArray = ""){
	TString kNameHistoArray;
	for(Int_t iPt=fStartBinPtRange;iPt<fNumberOfPtBins;iPt++){
		kNameHistoArray = Form("%s_Bin%02d", nameHistoArray.Data() ,iPt);
		Int_t startBin = fHisto2DDummy->GetYaxis()->FindBin(fBinsPtFilling[iPt]+0.001);
		Int_t endBin = fHisto2DDummy->GetYaxis()->FindBin(fBinsPtFilling[iPt+1]-0.001);
		fHisto2DDummy->ProjectionX(kNameHistoArray.Data(),startBin,endBin);
		fHistoArrayPtBins[iPt] = 0x0;
		fHistoArrayPtBins[iPt]=(TH1D*)gDirectory->Get(kNameHistoArray.Data());
	}
}

void Initialize(Int_t numberOfBins){

	fHistoDataCorrelationGammadPhiCh = 	new TH1D*[numberOfBins];    
	fFitDataCorrelationGammadPhiChAwaySide = new TF1* [numberOfBins];    
	fHistoDataCorrelationGammadEtaCh = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationGammadPhiCh_minPtAss1 = 	new TH1D*[numberOfBins];    
	fFitDataCorrelationGammadPhiChAwaySide_minPtAss1 = new TF1* [numberOfBins];    
	fHistoDataCorrelationGammadEtaCh_minPtAss1 = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationGammadPhiCh_minPtAss05 = 	new TH1D*[numberOfBins];    
	fFitDataCorrelationGammadPhiChAwaySide_minPtAss05 = new TF1* [numberOfBins];    
	fHistoDataCorrelationGammadEtaCh_minPtAss05 = 	new TH1D*[numberOfBins];    

	fHistoDataCorrelationGammaIsoMin=				new TH1D*[numberOfBins];    
 	fHistoDataCorrelationGammaIsodPhiCh=				new TH1D*[numberOfBins];    
 	fHistoDataCorrelationGammaIsodEtaCh=				new TH1D*[numberOfBins];    
 	fHistoDataCorrelationGammaIsodPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
 	fHistoDataCorrelationGammaIsodEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
 	fHistoDataCorrelationGammaIsodPhiCh_minPtAss05=new TH1D*[numberOfBins];    
 	fHistoDataCorrelationGammaIsodEtaCh_minPtAss05=new TH1D*[numberOfBins];       

	fHistoMCRecCorrelationGammadPhiCh=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationGammadEtaCh=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationGammadPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationGammadEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
	fHistoMCRecCorrelationGammadPhiCh_minPtAss05=new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationGammadEtaCh_minPtAss05=new TH1D*[numberOfBins];       

	fHistoMCRecCorrelationGammaIsoMin=				new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationGammaIsodPhiCh=				new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationGammaIsodEtaCh=				new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationGammaIsodPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationGammaIsodEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
 	fHistoMCRecCorrelationGammaIsodPhiCh_minPtAss05=new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationGammaIsodEtaCh_minPtAss05=new TH1D*[numberOfBins];       

	fHistoMCTrueCorrelationGammadPhiCh=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationGammadEtaCh=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationGammadPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationGammadEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
	fHistoMCTrueCorrelationGammadPhiCh_minPtAss05=new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationGammadEtaCh_minPtAss05=new TH1D*[numberOfBins];       
	
	fHistoMCTrueCorrelationGammaIsoMin=				new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationGammaIsodPhiCh=				new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationGammaIsodEtaCh=				new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationGammaIsodPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationGammaIsodEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
 	fHistoMCTrueCorrelationGammaIsodPhiCh_minPtAss05=new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationGammaIsodEtaCh_minPtAss05=new TH1D*[numberOfBins];       
}


//__________________________________________ Plotting all Invariant Mass bins _______________________________________________
void PlotCorrelationBinsPt(TH1D* fHistoIsoMinData,  TH1D* fHistoIsoMinMCRec, TH1D* fHistoIsoMinMCTrue,
									TH1D* fHistodPhiData,  TH1D* fHistodPhiMCRec, TH1D* fHistodPhiMCTrue,
									TH1D* fHistodEtaData,  TH1D* fHistodEtaMCRec, TH1D* fHistodEtaMCTrue,
									TH1D* fHistoIsodPhiData,  TH1D* fHistoIsodPhiMCRec, TH1D* fHistoIsodPhiMCTrue,
									TH1D* fHistoIsodEtaData,  TH1D* fHistoIsodEtaMCRec, TH1D* fHistoIsodEtaMCTrue,
									TString namePlot, Double_t ptStart, Double_t ptEnd, Int_t rebin = 2){

	TGaxis::SetMaxDigits(3);

	TCanvas * canvasDataSpectra = new TCanvas("Bla","",2800,1800);  // gives the page size
	canvasDataSpectra->SetTopMargin(0.0);
	canvasDataSpectra->SetBottomMargin(0.0);
	canvasDataSpectra->SetRightMargin(0.0);
	canvasDataSpectra->SetLeftMargin(0.0);

	TPad * padDataSpectra = new TPad("Blub","",0.0,0.0,1.,1.,0);   // gives the size of the histo areas
	padDataSpectra->SetFillColor(0);
	padDataSpectra->GetFrame()->SetFillColor(0);
	padDataSpectra->SetBorderMode(0);
	padDataSpectra->SetLogy(0);
	padDataSpectra->Divide(3,2);
	padDataSpectra->Draw();

	Double_t topMargin = 0.035;
	Double_t bottomMargin = 0.1;
	Double_t rightMargin = 0.01;
	Double_t leftMargin = 0.15;
	
	padDataSpectra->cd(1);
	padDataSpectra->cd(1)->SetTopMargin(topMargin);
	padDataSpectra->cd(1)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(1)->SetRightMargin(rightMargin);
	padDataSpectra->cd(1)->SetLeftMargin(leftMargin);

	
	fHistoIsoMinData->Rebin(rebin);
	fHistoIsoMinMCRec->Rebin(rebin);
	fHistoIsoMinMCTrue->Rebin(rebin);
	
	DrawCorrelation3Histos( fHistoIsoMinData, 
									fHistoIsoMinMCRec,
									fHistoIsoMinMCTrue,
									"","R_{Iso}","N_{trig}",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,180.);

	padDataSpectra->cd(4);
	TLatex *alice = new TLatex(0.,0.8,Form("%3.2f GeV/c < p_{T} < %3.2f GeV/c",ptStart,ptEnd));
	alice->SetNDC();
	alice->SetTextColor(1);
	alice->SetTextSize(0.07);
	alice->Draw();

	
	padDataSpectra->cd(2);
	padDataSpectra->cd(2)->SetTopMargin(topMargin);
	padDataSpectra->cd(2)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(2)->SetRightMargin(rightMargin);
	padDataSpectra->cd(2)->SetLeftMargin(leftMargin);

	DrawCorrelation3Histos( fHistodEtaData, 
									fHistodEtaMCRec,
									fHistodEtaMCTrue,
									"","#Delta#eta","#frac{dN_{ch,Ass}}{dN_{#gamma,trig}} #frac{1}{d#Delta#eta}",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,180.);
			
	padDataSpectra->cd(3);
	padDataSpectra->cd(3)->SetTopMargin(topMargin);
	padDataSpectra->cd(3)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(3)->SetRightMargin(rightMargin);
	padDataSpectra->cd(3)->SetLeftMargin(leftMargin);

	DrawCorrelation3Histos( 	fHistoIsodEtaData, 
									fHistoIsodEtaMCRec,
									fHistoIsodEtaMCTrue,
									"","#Delta#eta","#frac{dN_{ch,Ass}}{dN_{#gamma,trig}} #frac{1}{d#Delta#eta}",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,180.);
			
			
	padDataSpectra->cd(5);
	padDataSpectra->cd(5)->SetTopMargin(topMargin);
	padDataSpectra->cd(5)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(5)->SetRightMargin(rightMargin);
	padDataSpectra->cd(5)->SetLeftMargin(leftMargin);

	DrawCorrelation3Histos( 	fHistodPhiData, 
									fHistodPhiMCRec,
									fHistodPhiMCTrue,
									"","#Delta#phi","#frac{dN_{ch,Ass}}{dN_{#gamma,trig}} #frac{1}{d#Delta#phi}",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,180.);
			
	padDataSpectra->cd(6);
	padDataSpectra->cd(6)->SetTopMargin(topMargin);
	padDataSpectra->cd(6)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(6)->SetRightMargin(rightMargin);
	padDataSpectra->cd(6)->SetLeftMargin(leftMargin);

	DrawCorrelation3Histos( 	fHistoIsodPhiData, 
									fHistoIsodPhiMCRec,
									fHistoIsodPhiMCTrue,
									"","#Delta#phi","#frac{dN_{ch,Ass}}{dN_{#gamma,trig}} #frac{1}{d#Delta#phi}",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,180.);
	
	
	canvasDataSpectra->Print(namePlot.Data());
	delete padDataSpectra;
	delete canvasDataSpectra;
}


//__________________________________________ Plotting all Invariant Mass bins _______________________________________________
void PlotdPhiInPtBins(TH1D** fHistosdPhi,TH1D** fHistosdPhiIso, TF1** fFitsdPhi, TString namePlot, TString nameCanvas, TString namePad, 
							 Int_t fRowPlot, Int_t fColumnPlot, Int_t fStartBinPtRange, Int_t fNumberPtBins, Double_t* fRangeBinsPt){
	TGaxis::SetMaxDigits(3);

	TCanvas * canvasDataSpectra = new TCanvas(nameCanvas.Data(),"",2800,1800);  // gives the page size
	canvasDataSpectra->SetTopMargin(0.0);
	canvasDataSpectra->SetBottomMargin(0.0);
	canvasDataSpectra->SetRightMargin(0.0);
	canvasDataSpectra->SetLeftMargin(0.0);

	TPad * padDataSpectra = new TPad(namePad.Data(),"",0.0,0.0,1.,1.,0);   // gives the size of the histo areas
	padDataSpectra->SetFillColor(0);
	padDataSpectra->GetFrame()->SetFillColor(0);
	padDataSpectra->SetBorderMode(0);
	padDataSpectra->SetLogy(0);
	padDataSpectra->Divide(fColumnPlot,fRowPlot);
	padDataSpectra->Draw();

	
	Int_t place = 0;
	for(Int_t iPt=fStartBinPtRange;iPt<fNumberPtBins;iPt++){
		cout<<"Pt: "<<iPt<<" of "<<fNumberPtBins<<endl;
		Double_t startPt = fRangeBinsPt[iPt];
		Double_t endPt = fRangeBinsPt[iPt+1];

		place = place + 1;						//give the right place in the page
			padDataSpectra->cd(place);
			padDataSpectra->cd(place)->SetTopMargin(0.08);
			padDataSpectra->cd(place)->SetBottomMargin(0.08);
			padDataSpectra->cd(place)->SetRightMargin(0.0);
			padDataSpectra->cd(place)->SetLeftMargin(0.1);

			DrawCorrHisto( fHistosdPhi[iPt],
						Form("%3.2f GeV/c < p_{T,trig} < %3.2f GeV/c",startPt,endPt),
						"#Delta#phi","dN_{ch,Ass}/dN_{#gamma,trig} 1/d#Delta#phi");
			fHistosdPhiIso[iPt]->SetMarkerColor(kBlue);
			fHistosdPhiIso[iPt]->SetLineColor(kBlue);
			fHistosdPhiIso[iPt]->SetLineWidth(0.5);
			fHistosdPhiIso[iPt]->Draw("same,hist");
			if(fFitsdPhi[iPt]!=0x0){
				fFitsdPhi[iPt]->SetLineColor(kRed+2);
				fFitsdPhi[iPt]->SetLineWidth(0.7);
				fFitsdPhi[iPt]->Draw("same");
			}
	}
	canvasDataSpectra->Print(namePlot.Data());
	delete padDataSpectra;
	delete canvasDataSpectra;
}


void ComposeGammaCorrelation(TString nameFile = "CorrelationOutput1stStep.root", TString cutSelection = "001023", TString suffix ="eps"){
	
	StyleSettingsThesis();
	SetPlotStyleNConts(99);

	TString outputDirectory;
	TString outputDirectory1;
	TString outputDirectory2;
	outputDirectory1 =	 Form("%s",cutSelection.Data());
	outputDirectory2 =	 Form("%s/%s/",cutSelection.Data(),suffix.Data());
	outputDirectory =	 	Form("%s/%s/GammaCorrelation",cutSelection.Data(),suffix.Data());
	gSystem->Exec("mkdir "+outputDirectory1);
	gSystem->Exec("mkdir "+outputDirectory2);
	gSystem->Exec("mkdir "+outputDirectory);


	TFile* fileCorrRead = new TFile(nameFile.Data(),"UPDATE");
	TDirectory*  directoryGammaCorr = 		(TDirectory*)fileCorrRead->Get(Form("CorrGamma_%s",  cutSelection.Data())); 	
	
	
	TH1D* histoDataCorrAssGamma = (TH1D*)directoryGammaCorr->Get("ESD_Data_AssociatedGamma");
	cout << "Data: "<<histoDataCorrAssGamma->GetEntries()<< endl;
	Double_t entriesData = histoDataCorrAssGamma->GetEntries();
	TH2D* histoData2DGamma_dEta_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGamma_dEtaCh_PtTrig");
	histoData2DGamma_dEta_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGamma_dEta_PtTrig, 2,1,3);
	TH2D* histoData2DGamma_dEta_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGamma_dEtaCh_PtTrig_minPtAssA");
	histoData2DGamma_dEta_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGamma_dEta_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoData2DGamma_dEta_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGamma_dEtaCh_PtTrig_minPtAssB");
	histoData2DGamma_dEta_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGamma_dEta_PtTrig_minPtAss1, 2,1,3);
	TH2D* histoData2DGamma_dPhi_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGamma_dPhiCh_PtTrig");
	histoData2DGamma_dPhi_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGamma_dPhi_PtTrig, 2,1,3);
	TH2D* histoData2DGamma_dPhi_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGamma_dPhiCh_PtTrig_minPtAssA");
	histoData2DGamma_dPhi_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGamma_dPhi_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoData2DGamma_dPhi_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGamma_dPhiCh_PtTrig_minPtAssB");
	histoData2DGamma_dPhi_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGamma_dPhi_PtTrig_minPtAss1, 2,1,3);
	TH2D* histoDataCorrGamma_IsoMin_Pt= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGamma_IsoMin_Pt");		
	TH2D* histoData2DGammaIso_dEta_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGammaIso_dEtaCh_PtTrig");
	histoData2DGammaIso_dEta_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGammaIso_dEta_PtTrig, 2,1,3);
	TH2D* histoData2DGammaIso_dEta_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGammaIso_dEtaCh_PtTrig_minPtAssA");
	histoData2DGammaIso_dEta_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGammaIso_dEta_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoData2DGammaIso_dEta_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGammaIso_dEtaCh_PtTrig_minPtAssB");
	histoData2DGammaIso_dEta_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGammaIso_dEta_PtTrig_minPtAss1, 2,1,3);
	TH2D* histoData2DGammaIso_dPhi_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGammaIso_dPhiCh_PtTrig");
	histoData2DGammaIso_dPhi_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGammaIso_dPhi_PtTrig, 2,1,3);
	TH2D* histoData2DGammaIso_dPhi_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGammaIso_dPhiCh_PtTrig_minPtAssA");
	histoData2DGammaIso_dPhi_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGammaIso_dPhi_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoData2DGammaIso_dPhi_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_Data_CorrGammaIso_dPhiCh_PtTrig_minPtAssB");
	histoData2DGammaIso_dPhi_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2DSumw2(histoData2DGammaIso_dPhi_PtTrig_minPtAss1, 2,1,3);
	
	TH1D* histoMCRecCorrAssGamma = (TH1D*)directoryGammaCorr->Get("ESD_MCRec_AssociatedGamma");
	cout << "MCRec: "<<histoMCRecCorrAssGamma->GetEntries()<< endl;
	Double_t entriesMCRec = histoMCRecCorrAssGamma->GetEntries();
	TH2D* histoMCRec2DGamma_dEta_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGamma_dEtaCh_PtTrig");
	histoMCRec2DGamma_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGamma_dEta_PtTrig, 2,1,3);
	TH2D* histoMCRec2DGamma_dEta_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGamma_dEtaCh_PtTrig_minPtAssA");
	histoMCRec2DGamma_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGamma_dEta_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoMCRec2DGamma_dEta_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGamma_dEtaCh_PtTrig_minPtAssB");
	histoMCRec2DGamma_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGamma_dEta_PtTrig_minPtAss1, 2,1,3);
	TH2D* histoMCRec2DGamma_dPhi_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGamma_dPhiCh_PtTrig");
	histoMCRec2DGamma_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGamma_dPhi_PtTrig, 2,1,3);
	TH2D* histoMCRec2DGamma_dPhi_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGamma_dPhiCh_PtTrig_minPtAssA");
	histoMCRec2DGamma_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGamma_dPhi_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoMCRec2DGamma_dPhi_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGamma_dPhiCh_PtTrig_minPtAssB");
	histoMCRec2DGamma_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGamma_dPhi_PtTrig_minPtAss1, 2,1,3);
	TH2D* histoMCRecCorrGamma_IsoMin_Pt= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGamma_IsoMin_Pt");		
	TH2D* histoMCRec2DGammaIso_dEta_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGammaIso_dEtaCh_PtTrig");
	histoMCRec2DGammaIso_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGammaIso_dEta_PtTrig, 2,1,3);
	TH2D* histoMCRec2DGammaIso_dEta_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGammaIso_dEtaCh_PtTrig_minPtAssA");
	histoMCRec2DGammaIso_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGammaIso_dEta_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoMCRec2DGammaIso_dEta_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGammaIso_dEtaCh_PtTrig_minPtAssB");
	histoMCRec2DGammaIso_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGammaIso_dEta_PtTrig_minPtAss1, 2,1,3);
	TH2D* histoMCRec2DGammaIso_dPhi_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGammaIso_dPhiCh_PtTrig");
	histoMCRec2DGammaIso_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGammaIso_dPhi_PtTrig, 2,1,3);
	TH2D* histoMCRec2DGammaIso_dPhi_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGammaIso_dPhiCh_PtTrig_minPtAssA");
	histoMCRec2DGammaIso_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGammaIso_dPhi_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoMCRec2DGammaIso_dPhi_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_MCRec_CorrGammaIso_dPhiCh_PtTrig_minPtAssB");
	histoMCRec2DGammaIso_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCRec2DGammaIso_dPhi_PtTrig_minPtAss1, 2,1,3);

	TH2D* histoMCTrue2DGamma_dEta_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGamma_dEtaCh_PtTrig");
	histoMCTrue2DGamma_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGamma_dEta_PtTrig, 2,1,3);
	TH2D* histoMCTrue2DGamma_dEta_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGamma_dEtaCh_PtTrig_minPtAssA");
	histoMCTrue2DGamma_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGamma_dEta_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoMCTrue2DGamma_dEta_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGamma_dEtaCh_PtTrig_minPtAssB");
	histoMCTrue2DGamma_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGamma_dEta_PtTrig_minPtAss1, 2,1,3);
	TH2D* histoMCTrue2DGamma_dPhi_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGamma_dPhiCh_PtTrig");
	histoMCTrue2DGamma_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGamma_dPhi_PtTrig, 2,1,3);
	TH2D* histoMCTrue2DGamma_dPhi_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGamma_dPhiCh_PtTrig_minPtAssA");
	histoMCTrue2DGamma_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGamma_dPhi_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoMCTrue2DGamma_dPhi_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGamma_dPhiCh_PtTrig_minPtAssB");
	histoMCTrue2DGamma_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGamma_dPhi_PtTrig_minPtAss1, 2,1,3);
	TH2D* histoMCTrueCorrGamma_IsoMin_Pt= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGamma_IsoMin_Pt");		
	TH2D* histoMCTrue2DGammaIso_dEta_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGammaIso_dEtaCh_PtTrig");
	histoMCTrue2DGammaIso_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGammaIso_dEta_PtTrig, 2,1,3);
	TH2D* histoMCTrue2DGammaIso_dEta_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGammaIso_dEtaCh_PtTrig_minPtAssA");
	histoMCTrue2DGammaIso_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGammaIso_dEta_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoMCTrue2DGammaIso_dEta_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGammaIso_dEtaCh_PtTrig_minPtAssB");
	histoMCTrue2DGammaIso_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGammaIso_dEta_PtTrig_minPtAss1, 2,1,3);
	TH2D* histoMCTrue2DGammaIso_dPhi_PtTrig= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGammaIso_dPhiCh_PtTrig");
	histoMCTrue2DGammaIso_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGammaIso_dPhi_PtTrig, 2,1,3);
	TH2D* histoMCTrue2DGammaIso_dPhi_PtTrig_minPtAss05= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGammaIso_dPhiCh_PtTrig_minPtAssA");
	histoMCTrue2DGammaIso_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGammaIso_dPhi_PtTrig_minPtAss05, 2,1,3);
	TH2D* histoMCTrue2DGammaIso_dPhi_PtTrig_minPtAss1= (TH2D*)directoryGammaCorr->Get("ESD_MCTrue_CorrGammaIso_dPhiCh_PtTrig_minPtAssB");
	histoMCTrue2DGammaIso_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2DSumw2(histoMCTrue2DGammaIso_dPhi_PtTrig_minPtAss1, 2,1,3);

	Initialize(31);
	FillHistoArray(histoData2DGamma_dEta_PtTrig, fHistoDataCorrelationGammadEtaCh, 1, 31, fPtBinnningGamma, "Gamma_Data_dEta_Pt" );
	FillHistoArray(histoData2DGamma_dEta_PtTrig_minPtAss1, fHistoDataCorrelationGammadEtaCh_minPtAss1, 1, 31, fPtBinnningGamma, "Gamma_Data_dEta_Pt_minPtAss1" );
	FillHistoArray(histoData2DGamma_dEta_PtTrig_minPtAss05, fHistoDataCorrelationGammadEtaCh_minPtAss05, 1, 31, fPtBinnningGamma, "Gamma_Data_dEta_Pt_minPtAss05" );
	FillHistoArray(histoData2DGamma_dPhi_PtTrig, fHistoDataCorrelationGammadPhiCh, 1, 31, fPtBinnningGamma, "Gamma_Data_dPhi_Pt" );
	FillHistoArray(histoData2DGamma_dPhi_PtTrig_minPtAss1, fHistoDataCorrelationGammadPhiCh_minPtAss1, 1, 31, fPtBinnningGamma, "Gamma_Data_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoData2DGamma_dPhi_PtTrig_minPtAss05, fHistoDataCorrelationGammadPhiCh_minPtAss05, 1, 31, fPtBinnningGamma, "Gamma_Data_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoDataCorrGamma_IsoMin_Pt, fHistoDataCorrelationGammaIsoMin, 1, 31, fPtBinnningGamma, "Gamma_Data_IsoMin_Pt" );
	FillHistoArray(histoData2DGammaIso_dEta_PtTrig, fHistoDataCorrelationGammaIsodEtaCh, 1, 31, fPtBinnningGamma, "GammaIso_Data_dEta_Pt" );
	FillHistoArray(histoData2DGammaIso_dEta_PtTrig_minPtAss05, fHistoDataCorrelationGammaIsodEtaCh_minPtAss05, 1, 31, fPtBinnningGamma, "GammaIso_Data_dEta_Pt_minPtAss05");
	FillHistoArray(histoData2DGammaIso_dEta_PtTrig_minPtAss1, fHistoDataCorrelationGammaIsodEtaCh_minPtAss1, 1, 31, fPtBinnningGamma, "GammaIso_Data_dEta_Pt_minPtAss1");
	FillHistoArray(histoData2DGammaIso_dPhi_PtTrig, fHistoDataCorrelationGammaIsodPhiCh, 1, 31, fPtBinnningGamma, "GammaIso_Data_dPhi_Pt" );
	FillHistoArray(histoData2DGammaIso_dPhi_PtTrig_minPtAss05, fHistoDataCorrelationGammaIsodPhiCh_minPtAss05, 1, 31, fPtBinnningGamma, "GammaIso_Data_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoData2DGammaIso_dPhi_PtTrig_minPtAss1, fHistoDataCorrelationGammaIsodPhiCh_minPtAss1, 1, 31, fPtBinnningGamma, "GammaIso_Data_dPhi_Pt_minPtAss1" );
	
	FillHistoArray(histoMCRec2DGamma_dEta_PtTrig, fHistoMCRecCorrelationGammadEtaCh, 1, 31, fPtBinnningGamma, "Gamma_MCRec_dEta_Pt" );
	FillHistoArray(histoMCRec2DGamma_dEta_PtTrig_minPtAss1, fHistoMCRecCorrelationGammadEtaCh_minPtAss1, 1, 31, fPtBinnningGamma, "Gamma_MCRec_dEta_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DGamma_dEta_PtTrig_minPtAss05, fHistoMCRecCorrelationGammadEtaCh_minPtAss05, 1, 31, fPtBinnningGamma, "Gamma_MCRec_dEta_Pt_minPtAss05" );
	FillHistoArray(histoMCRec2DGamma_dPhi_PtTrig, fHistoMCRecCorrelationGammadPhiCh, 1, 31, fPtBinnningGamma, "Gamma_MCRec_dPhi_Pt" );
	FillHistoArray(histoMCRec2DGamma_dPhi_PtTrig_minPtAss1, fHistoMCRecCorrelationGammadPhiCh_minPtAss1, 1, 31, fPtBinnningGamma, "Gamma_MCRec_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DGamma_dPhi_PtTrig_minPtAss05, fHistoMCRecCorrelationGammadPhiCh_minPtAss05, 1, 31, fPtBinnningGamma, "Gamma_MCRec_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoMCRecCorrGamma_IsoMin_Pt, fHistoMCRecCorrelationGammaIsoMin, 1, 31, fPtBinnningGamma, "Gamma_MCRec_IsoMin_Pt" );
	FillHistoArray(histoMCRec2DGammaIso_dEta_PtTrig, fHistoMCRecCorrelationGammaIsodEtaCh, 1, 31, fPtBinnningGamma, "GammaIso_MCRec_dEta_Pt" );
	FillHistoArray(histoMCRec2DGammaIso_dEta_PtTrig_minPtAss05, fHistoMCRecCorrelationGammaIsodEtaCh_minPtAss05, 1, 31, fPtBinnningGamma, "GammaIso_MCRec_dEta_Pt_minPtAss05");
	FillHistoArray(histoMCRec2DGammaIso_dEta_PtTrig_minPtAss1, fHistoMCRecCorrelationGammaIsodEtaCh_minPtAss1, 1, 31, fPtBinnningGamma, "GammaIso_MCRec_dEta_Pt_minPtAss1");
	FillHistoArray(histoMCRec2DGammaIso_dPhi_PtTrig, fHistoMCRecCorrelationGammaIsodPhiCh, 1, 31, fPtBinnningGamma, "GammaIso_MCRec_dPhi_Pt" );
	FillHistoArray(histoMCRec2DGammaIso_dPhi_PtTrig_minPtAss05, fHistoMCRecCorrelationGammaIsodPhiCh_minPtAss05, 1, 31, fPtBinnningGamma, "GammaIso_MCRec_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoMCRec2DGammaIso_dPhi_PtTrig_minPtAss1, fHistoMCRecCorrelationGammaIsodPhiCh_minPtAss1, 1, 31, fPtBinnningGamma, "GammaIso_MCRec_dPhi_Pt_minPtAss1" );
	
	FillHistoArray(histoMCTrue2DGamma_dEta_PtTrig, fHistoMCTrueCorrelationGammadEtaCh, 1, 31, fPtBinnningGamma, "Gamma_MCTrue_dEta_Pt" );
	FillHistoArray(histoMCTrue2DGamma_dEta_PtTrig_minPtAss1, fHistoMCTrueCorrelationGammadEtaCh_minPtAss1, 1, 31, fPtBinnningGamma, "Gamma_MCTrue_dEta_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DGamma_dEta_PtTrig_minPtAss05, fHistoMCTrueCorrelationGammadEtaCh_minPtAss05, 1, 31, fPtBinnningGamma, "Gamma_MCTrue_dEta_Pt_minPtAss05" );
	FillHistoArray(histoMCTrue2DGamma_dPhi_PtTrig, fHistoMCTrueCorrelationGammadPhiCh, 1, 31, fPtBinnningGamma, "Gamma_MCTrue_dPhi_Pt" );
	FillHistoArray(histoMCTrue2DGamma_dPhi_PtTrig_minPtAss1, fHistoMCTrueCorrelationGammadPhiCh_minPtAss1, 1, 31, fPtBinnningGamma, "Gamma_MCTrue_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DGamma_dPhi_PtTrig_minPtAss05, fHistoMCTrueCorrelationGammadPhiCh_minPtAss05, 1, 31, fPtBinnningGamma, "Gamma_MCTrue_dPhi_Pt_minPtAss05" );	
	FillHistoArray(histoMCTrueCorrGamma_IsoMin_Pt, fHistoMCTrueCorrelationGammaIsoMin, 1, 31, fPtBinnningGamma, "Gamma_MCTrue_IsoMin_Pt" );
	FillHistoArray(histoMCTrue2DGammaIso_dEta_PtTrig, fHistoMCTrueCorrelationGammaIsodEtaCh, 1, 31, fPtBinnningGamma, "GammaIso_MCTrue_dEta_Pt" );
	FillHistoArray(histoMCTrue2DGammaIso_dEta_PtTrig_minPtAss05, fHistoMCTrueCorrelationGammaIsodEtaCh_minPtAss05, 1, 31, fPtBinnningGamma, "GammaIso_MCTrue_dEta_Pt_minPtAss05");
	FillHistoArray(histoMCTrue2DGammaIso_dEta_PtTrig_minPtAss1, fHistoMCTrueCorrelationGammaIsodEtaCh_minPtAss1, 1, 31, fPtBinnningGamma, "GammaIso_MCTrue_dEta_Pt_minPtAss1");
	FillHistoArray(histoMCTrue2DGammaIso_dPhi_PtTrig, fHistoMCTrueCorrelationGammaIsodPhiCh, 1, 31, fPtBinnningGamma, "GammaIso_MCTrue_dPhi_Pt" );
	FillHistoArray(histoMCTrue2DGammaIso_dPhi_PtTrig_minPtAss05, fHistoMCTrueCorrelationGammaIsodPhiCh_minPtAss05, 1, 31, fPtBinnningGamma, "GammaIso_MCTrue_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoMCTrue2DGammaIso_dPhi_PtTrig_minPtAss1, fHistoMCTrueCorrelationGammaIsodPhiCh_minPtAss1, 1, 31, fPtBinnningGamma, "GammaIso_MCTrue_dPhi_Pt_minPtAss1" );
	
	for (Int_t i = 1; i < 30; i++){
		PlotCorrelationBinsPt( fHistoDataCorrelationGammaIsoMin[i], fHistoMCRecCorrelationGammaIsoMin[i],fHistoMCTrueCorrelationGammaIsoMin[i],
									fHistoDataCorrelationGammadPhiCh[i], fHistoMCRecCorrelationGammadPhiCh[i], fHistoMCTrueCorrelationGammadPhiCh[i],
									fHistoDataCorrelationGammadEtaCh[i], fHistoMCRecCorrelationGammadEtaCh[i], fHistoMCTrueCorrelationGammadEtaCh[i],
									fHistoDataCorrelationGammaIsodPhiCh[i], fHistoMCRecCorrelationGammaIsodPhiCh[i], fHistoMCTrueCorrelationGammaIsodPhiCh[i],
									fHistoDataCorrelationGammaIsodEtaCh[i], fHistoMCRecCorrelationGammaIsodEtaCh[i], fHistoMCTrueCorrelationGammaIsodEtaCh[i],
									Form("%s/CompilationCorrelation_PtBin_%i.%s",outputDirectory.Data(),i,suffix.Data()),fPtBinnningGamma[i],fPtBinnningGamma[i+1],fPtRebinGamma[i]);
		fFitDataCorrelationGammadPhiChAwaySide[i] = FitPout(fHistoDataCorrelationGammadPhiCh[i]);
	}
	for (Int_t i = 4; i < 30; i++){
		PlotCorrelationBinsPt( fHistoDataCorrelationGammaIsoMin[i], fHistoMCRecCorrelationGammaIsoMin[i],fHistoMCTrueCorrelationGammaIsoMin[i],
									fHistoDataCorrelationGammadPhiCh_minPtAss05[i], fHistoMCRecCorrelationGammadPhiCh_minPtAss05[i], fHistoMCTrueCorrelationGammadPhiCh_minPtAss05[i],
									fHistoDataCorrelationGammadEtaCh_minPtAss05[i], fHistoMCRecCorrelationGammadEtaCh_minPtAss05[i], fHistoMCTrueCorrelationGammadEtaCh_minPtAss05[i],
									fHistoDataCorrelationGammaIsodPhiCh_minPtAss05[i], fHistoMCRecCorrelationGammaIsodPhiCh_minPtAss05[i], fHistoMCTrueCorrelationGammaIsodPhiCh_minPtAss05[i],
									fHistoDataCorrelationGammaIsodEtaCh_minPtAss05[i], fHistoMCRecCorrelationGammaIsodEtaCh_minPtAss05[i], fHistoMCTrueCorrelationGammaIsodEtaCh_minPtAss05[i],
									Form("%s/CompilationCorrelation_minPtAss05_PtBin_%i.%s",outputDirectory.Data(),i,suffix.Data()),fPtBinnningGamma[i],fPtBinnningGamma[i+1],1);
		fFitDataCorrelationGammadPhiChAwaySide_minPtAss05[i] = FitPout(fHistoDataCorrelationGammadPhiCh_minPtAss05[i]);
	}
	for (Int_t i = 10; i < 30; i++){
		PlotCorrelationBinsPt( fHistoDataCorrelationGammaIsoMin[i], fHistoMCRecCorrelationGammaIsoMin[i],fHistoMCTrueCorrelationGammaIsoMin[i],
									fHistoDataCorrelationGammadPhiCh_minPtAss1[i], fHistoMCRecCorrelationGammadPhiCh_minPtAss1[i], fHistoMCTrueCorrelationGammadPhiCh_minPtAss1[i],
									fHistoDataCorrelationGammadEtaCh_minPtAss1[i], fHistoMCRecCorrelationGammadEtaCh_minPtAss1[i], fHistoMCTrueCorrelationGammadEtaCh_minPtAss1[i],
									fHistoDataCorrelationGammaIsodPhiCh_minPtAss1[i], fHistoMCRecCorrelationGammaIsodPhiCh_minPtAss1[i], fHistoMCTrueCorrelationGammaIsodPhiCh_minPtAss1[i],
									fHistoDataCorrelationGammaIsodEtaCh_minPtAss1[i], fHistoMCRecCorrelationGammaIsodEtaCh_minPtAss1[i], fHistoMCTrueCorrelationGammaIsodEtaCh_minPtAss1[i],
									Form("%s/CompilationCorrelation_minPtAss1_PtBin_%i.%s",outputDirectory.Data(),i,suffix.Data()),fPtBinnningGamma[i],fPtBinnningGamma[i+1],1);
		fFitDataCorrelationGammadPhiChAwaySide_minPtAss1[i] = FitPout(fHistoDataCorrelationGammadPhiCh_minPtAss1[i]);
	}
	
	PlotdPhiInPtBins(fHistoDataCorrelationGammadPhiCh, fHistoDataCorrelationGammaIsodPhiCh,fFitDataCorrelationGammadPhiChAwaySide, Form("%s/CompilationCorrelationIncFit.%s",outputDirectory.Data(),suffix.Data()), "blubber", "bla", 5,6,1,29, fPtBinnningGamma);
	PlotdPhiInPtBins(fHistoDataCorrelationGammadPhiCh_minPtAss05,fHistoDataCorrelationGammaIsodPhiCh_minPtAss05, fFitDataCorrelationGammadPhiChAwaySide_minPtAss05, Form("%s/CompilationCorrelationIncFit_minPt1GeV.%s",outputDirectory.Data(),suffix.Data()), "blubber", "bla", 4,6,5,29, fPtBinnningGamma);
	PlotdPhiInPtBins(fHistoDataCorrelationGammadPhiCh_minPtAss1, fHistoDataCorrelationGammaIsodPhiCh_minPtAss1, fFitDataCorrelationGammadPhiChAwaySide_minPtAss1, Form("%s/CompilationCorrelationIncFit_minPt2GeV.%s",outputDirectory.Data(),suffix.Data()), "blubber", "bla", 4,5,10,29, fPtBinnningGamma);
}