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

TH1D** 	fHistoDataCorrelationPi0InvMass=				NULL;
TH1D** 	fHistoDataCorrelationPi0dPhiCh=				NULL;
TF1** 	fFitDataCorrelationPi0dPhiChAwaySide=		NULL;
TH1D** 	fHistoDataCorrelationPi0dEtaCh=				NULL;
TH1D** 	fHistoDataCorrelationPi0dPhiCh_minPtAss1=	NULL;
TF1** 	fFitDataCorrelationPi0dPhiChAwaySide_minPtAss1=		NULL;
TH1D** 	fHistoDataCorrelationPi0dEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoDataCorrelationPi0dPhiCh_minPtAss05=NULL;
TF1** 	fFitDataCorrelationPi0dPhiChAwaySide_minPtAss05=		NULL;
TH1D** 	fHistoDataCorrelationPi0dEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoDataCorrelationPi0SideBandInvMass=				NULL;
TH1D** 	fHistoDataCorrelationPi0SideBanddPhiCh=				NULL;
TH1D** 	fHistoDataCorrelationPi0SideBanddEtaCh=				NULL;
TH1D** 	fHistoDataCorrelationPi0SideBanddPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoDataCorrelationPi0SideBanddEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoDataCorrelationPi0SideBanddPhiCh_minPtAss05=	NULL;
TH1D** 	fHistoDataCorrelationPi0SideBanddEtaCh_minPtAss05=	NULL;   

TH1D** 	fHistoDataCorrelationPi0IsoMin=				NULL;
TH1D** 	fHistoDataCorrelationPi0IsodPhiCh=				NULL;
TH1D** 	fHistoDataCorrelationPi0IsodEtaCh=				NULL;
TH1D** 	fHistoDataCorrelationPi0IsodPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoDataCorrelationPi0IsodEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoDataCorrelationPi0IsodPhiCh_minPtAss05=NULL;
TH1D** 	fHistoDataCorrelationPi0IsodEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCRecCorrelationPi0InvMass=				NULL;
TH1D** 	fHistoMCRecCorrelationPi0dPhiCh=				NULL;
TH1D** 	fHistoMCRecCorrelationPi0dEtaCh=				NULL;
TH1D** 	fHistoMCRecCorrelationPi0dPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCRecCorrelationPi0dEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCRecCorrelationPi0dPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCRecCorrelationPi0dEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCRecCorrelationPi0SideBandInvMass=				NULL;
TH1D** 	fHistoMCRecCorrelationPi0SideBanddPhiCh=				NULL;
TH1D** 	fHistoMCRecCorrelationPi0SideBanddEtaCh=				NULL;
TH1D** 	fHistoMCRecCorrelationPi0SideBanddPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCRecCorrelationPi0SideBanddEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCRecCorrelationPi0SideBanddPhiCh_minPtAss05=	NULL;
TH1D** 	fHistoMCRecCorrelationPi0SideBanddEtaCh_minPtAss05=	NULL;   

TH1D** 	fHistoMCRecCorrelationPi0IsoMin=				NULL;
TH1D** 	fHistoMCRecCorrelationPi0IsodPhiCh=				NULL;
TH1D** 	fHistoMCRecCorrelationPi0IsodEtaCh=				NULL;
TH1D** 	fHistoMCRecCorrelationPi0IsodPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCRecCorrelationPi0IsodEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCRecCorrelationPi0IsodPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCRecCorrelationPi0IsodEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCTrueCorrelationPi0InvMass=				NULL;
TH1D** 	fHistoMCTrueCorrelationPi0dPhiCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationPi0dEtaCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationPi0dPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCTrueCorrelationPi0dEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCTrueCorrelationPi0dPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCTrueCorrelationPi0dEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCTrueCorrelationPi0SideBandInvMass=				NULL;
TH1D** 	fHistoMCTrueCorrelationPi0SideBanddPhiCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationPi0SideBanddEtaCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationPi0SideBanddPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCTrueCorrelationPi0SideBanddEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCTrueCorrelationPi0SideBanddPhiCh_minPtAss05=	NULL;
TH1D** 	fHistoMCTrueCorrelationPi0SideBanddEtaCh_minPtAss05=	NULL;   

TH1D** 	fHistoMCTrueCorrelationPi0IsoMin=				NULL;
TH1D** 	fHistoMCTrueCorrelationPi0IsodPhiCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationPi0IsodEtaCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationPi0IsodPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCTrueCorrelationPi0IsodEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCTrueCorrelationPi0IsodPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCTrueCorrelationPi0IsodEtaCh_minPtAss05=NULL;   

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

	fHistoDataCorrelationPi0InvMass = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationPi0dPhiCh = 	new TH1D*[numberOfBins];    
	fFitDataCorrelationPi0dPhiChAwaySide = new TF1* [numberOfBins];    
	fHistoDataCorrelationPi0dEtaCh = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationPi0dPhiCh_minPtAss1 = 	new TH1D*[numberOfBins];    
	fFitDataCorrelationPi0dPhiChAwaySide_minPtAss1 = new TF1* [numberOfBins];    
	fHistoDataCorrelationPi0dEtaCh_minPtAss1 = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationPi0dPhiCh_minPtAss05 = 	new TH1D*[numberOfBins];    
	fFitDataCorrelationPi0dPhiChAwaySide_minPtAss05 = new TF1* [numberOfBins];    
	fHistoDataCorrelationPi0dEtaCh_minPtAss05 = 	new TH1D*[numberOfBins];    

	fHistoDataCorrelationPi0SideBandInvMass = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationPi0SideBanddPhiCh = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationPi0SideBanddEtaCh = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationPi0SideBanddPhiCh_minPtAss1 = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationPi0SideBanddEtaCh_minPtAss1 = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationPi0SideBanddPhiCh_minPtAss05 = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationPi0SideBanddEtaCh_minPtAss05 = 	new TH1D*[numberOfBins];    

	fHistoDataCorrelationPi0IsoMin=				new TH1D*[numberOfBins];    
 	fHistoDataCorrelationPi0IsodPhiCh=				new TH1D*[numberOfBins];    
 	fHistoDataCorrelationPi0IsodEtaCh=				new TH1D*[numberOfBins];    
 	fHistoDataCorrelationPi0IsodPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
 	fHistoDataCorrelationPi0IsodEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
 	fHistoDataCorrelationPi0IsodPhiCh_minPtAss05=new TH1D*[numberOfBins];    
 	fHistoDataCorrelationPi0IsodEtaCh_minPtAss05=new TH1D*[numberOfBins];       

	fHistoMCRecCorrelationPi0InvMass=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationPi0dPhiCh=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationPi0dEtaCh=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationPi0dPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationPi0dEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
	fHistoMCRecCorrelationPi0dPhiCh_minPtAss05=new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationPi0dEtaCh_minPtAss05=new TH1D*[numberOfBins];       

	fHistoMCRecCorrelationPi0SideBandInvMass=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationPi0SideBanddPhiCh=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationPi0SideBanddEtaCh=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationPi0SideBanddPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationPi0SideBanddEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
	fHistoMCRecCorrelationPi0SideBanddPhiCh_minPtAss05=	new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationPi0SideBanddEtaCh_minPtAss05=	new TH1D*[numberOfBins];       

	fHistoMCRecCorrelationPi0IsoMin=				new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationPi0IsodPhiCh=				new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationPi0IsodEtaCh=				new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationPi0IsodPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationPi0IsodEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
 	fHistoMCRecCorrelationPi0IsodPhiCh_minPtAss05=new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationPi0IsodEtaCh_minPtAss05=new TH1D*[numberOfBins];       

	fHistoMCTrueCorrelationPi0InvMass=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationPi0dPhiCh=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationPi0dEtaCh=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationPi0dPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationPi0dEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
	fHistoMCTrueCorrelationPi0dPhiCh_minPtAss05=new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationPi0dEtaCh_minPtAss05=new TH1D*[numberOfBins];       

	fHistoMCTrueCorrelationPi0SideBandInvMass=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationPi0SideBanddPhiCh=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationPi0SideBanddEtaCh=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationPi0SideBanddPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationPi0SideBanddEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
	fHistoMCTrueCorrelationPi0SideBanddPhiCh_minPtAss05=	new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationPi0SideBanddEtaCh_minPtAss05=	new TH1D*[numberOfBins];       
	
	fHistoMCTrueCorrelationPi0IsoMin=				new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationPi0IsodPhiCh=				new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationPi0IsodEtaCh=				new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationPi0IsodPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationPi0IsodEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
 	fHistoMCTrueCorrelationPi0IsodPhiCh_minPtAss05=new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationPi0IsodEtaCh_minPtAss05=new TH1D*[numberOfBins];       
}

TF1* FitInvMassGaussPol2(TH1D* fHistoInvMassSinglePt)
{

	cout<<"Start Fitting spectra"<<endl;
	fHistoInvMassSinglePt->GetXaxis()->SetRangeUser(0.09,0.17);
	Double_t mesonAmplitude =fHistoInvMassSinglePt->GetMaximum();
	Double_t mesonAmplitudeMin;
	Double_t mesonAmplitudeMax;
	mesonAmplitudeMin = mesonAmplitude*80./100.;
	mesonAmplitudeMax = mesonAmplitude*115./100.;

	TF1* fFitReco = new TF1("GaussExpLinear","(x<[1])*([0]*(exp(-0.5*((x-[1])/[2])^2)+exp((x-[1])/[3])*(1.-exp(-0.5*((x-[1])/[2])^2)))+[4]+[5]*x+[6]*x*x)+(x>=[1])*([0]*exp(-0.5*((x-[1])/[2])^2)+[4]+[5]*x+[6]*x*x)",0.09,0.17);
	TF1* fFitGausExp = new TF1("fGaussExp","(x<[1])*([0]*(exp(-0.5*((x-[1])/[2])^2)+exp((x-[1])/[3])*(1.-exp(-0.5*((x-[1])/[2])^2))))+(x>=[1])*([0]*exp(-0.5*((x-[1])/[2])^2))",0.09,0.17);
	TF1* fFitLinearBck = new TF1("Linear","[0]+[1]*x+[2]*x*x",0.09,0.17);

	Double_t fMesonWidthExpect = 0.003;
	Double_t fMesonLambdaTail = 	0.012;
	Double_t fMesonMassExpect = TDatabasePDG::Instance()->GetParticle(111)->Mass();
	Double_t* fMesonWidthRange = 	new Double_t[2]; 	fMesonWidthRange[0]=0.001; 	fMesonWidthRange[1]=0.009;
	Double_t* fMesonLambdaTailRange = new Double_t[2]; fMesonLambdaTailRange[0]=0.001; fMesonLambdaTailRange[1]=0.02;
	Double_t* fMesonMassRange = 	new Double_t[2]; 	fMesonMassRange[0]=	0.09; 		fMesonMassRange[1]=	0.17;
	fFitReco->SetParameter(0,mesonAmplitude);
	fFitReco->SetParameter(1,fMesonMassExpect);
	fFitReco->SetParameter(2,fMesonWidthExpect);
	fFitReco->FixParameter(3,fMesonLambdaTail);
	fFitReco->SetParLimits(0,mesonAmplitudeMin,mesonAmplitudeMax);
	fFitReco->SetParLimits(1,fMesonMassRange[0],fMesonMassRange[1]);
	fFitReco->SetParLimits(2,fMesonWidthRange[0],fMesonWidthRange[1]);
	fFitReco->SetParLimits(3,fMesonLambdaTailRange[0],fMesonLambdaTailRange[1]);

	fHistoInvMassSinglePt->Fit(fFitReco,"QRME0");
	fHistoInvMassSinglePt->Fit(fFitReco,"QRME0");

	fFitReco->SetLineColor(3);
	fFitReco->SetLineWidth(1);
	fFitReco->SetLineStyle(1);

	fFitGausExp->SetParameter(0,fFitReco->GetParameter(0));
	fFitGausExp->SetParameter(1,fFitReco->GetParameter(1));
	fFitGausExp->SetParameter(2,fFitReco->GetParameter(2));
	fFitGausExp->SetParameter(3,fFitReco->GetParameter(3));

	fFitGausExp->SetParError(0,fFitReco->GetParError(0));
	fFitGausExp->SetParError(1,fFitReco->GetParError(1));
	fFitGausExp->SetParError(2,fFitReco->GetParError(2));
	fFitGausExp->SetParError(3,fFitReco->GetParError(3));

	fFitLinearBck->SetParameter(0,fFitReco->GetParameter(4));
	fFitLinearBck->SetParameter(1,fFitReco->GetParameter(5));
	fFitLinearBck->SetParameter(1,fFitReco->GetParameter(6));

	fFitLinearBck->SetParError(0,fFitReco->GetParError(4));
	fFitLinearBck->SetParError(1,fFitReco->GetParError(5));
	fFitLinearBck->SetParError(1,fFitReco->GetParError(6));

	if(TString(gMinuit->fCstatu.Data()).CompareTo("CONVERGED") == 0 || TString(gMinuit->fCstatu.Data()).CompareTo("SUCCESSFUL") == 0 ){
		cout << "Gausexp: \t" << fFitReco->GetParameter(0) <<"+-" << fFitReco->GetParError(0) << "\t " << fFitReco->GetParameter(1)<<"+-" << fFitReco->GetParError(1) << "\t "<< fFitReco->GetParameter(2) <<"+-" << fFitReco->GetParError(2)<< "\t "<< fFitReco->GetParameter(3) <<"+-" << fFitReco->GetParError(3)<<endl;
		cout << "Quadratic: \t"<<fFitReco->GetParameter(4)<<"+-" << fFitReco->GetParError(4) << "\t "<<fFitReco->GetParameter(5) <<"+-" << fFitReco->GetParError(5) << "\t "<<fFitReco->GetParameter(6) <<"+-" << fFitReco->GetParError(6)<< endl;
		return fFitReco;
	} else {
		cout << "Fitting failed with status " << gMinuit->fCstatu.Data() <<endl << endl;
		return 0x00;
	}
}


//__________________________________________ Plotting all Invariant Mass bins _______________________________________________
void PlotCorrelationBinsPt(TH1D* fHistoInvMassData, TH1D* fHistoInvMassMCRec, TH1D* fHistoInvMassMCTrue,
									TH1D* fHistoIsoMinData,  TH1D* fHistoIsoMinMCRec, TH1D* fHistoIsoMinMCTrue,
									TH1D* fHistodPhiData,  TH1D* fHistodPhiMCRec, TH1D* fHistodPhiMCTrue,
									TH1D* fHistodEtaData,  TH1D* fHistodEtaMCRec, TH1D* fHistodEtaMCTrue,
									TH1D* fHistoIsodPhiData,  TH1D* fHistoIsodPhiMCRec, TH1D* fHistoIsodPhiMCTrue,
									TH1D* fHistoIsodEtaData,  TH1D* fHistoIsodEtaMCRec, TH1D* fHistoIsodEtaMCTrue,
									TH1D* fHistoSBdPhiData,  TH1D* fHistoSBdPhiMCRec, TH1D* fHistoSBdPhiMCTrue,
									TH1D* fHistoSBdEtaData,  TH1D* fHistoSBdEtaMCRec, TH1D* fHistoSBdEtaMCTrue,
									TString namePlot, Double_t ptStart, Double_t ptEnd, Int_t rebin=2, Int_t bin=1){

	TGaxis::SetMaxDigits(3);

	TCanvas * canvasDataSpectra = new TCanvas("Bla","",2800,2800);  // gives the page size
	canvasDataSpectra->SetTopMargin(0.0);
	canvasDataSpectra->SetBottomMargin(0.0);
	canvasDataSpectra->SetRightMargin(0.0);
	canvasDataSpectra->SetLeftMargin(0.0);

	TPad * padDataSpectra = new TPad("Blub","",0.0,0.0,1.,1.,0);   // gives the size of the histo areas
	padDataSpectra->SetFillColor(0);
	padDataSpectra->GetFrame()->SetFillColor(0);
	padDataSpectra->SetBorderMode(0);
	padDataSpectra->SetLogy(0);
	padDataSpectra->Divide(3,3);
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

	fHistoInvMassData->Rebin(rebin);
	fHistoInvMassMCRec->Rebin(rebin);
	fHistoInvMassMCTrue->Rebin(rebin);
	
	cout << "PtBin: \t" << bin << "\t rebin factor: \t" << rebin<< endl;
	TF1* fitInvMassData = FitInvMassGaussPol2(fHistoInvMassData);
	TF1* fitInvMassMCRec = FitInvMassGaussPol2(fHistoInvMassMCRec);
	TF1* fitInvMassMCTrue = FitInvMassGaussPol2(fHistoInvMassMCTrue);
	
	DrawCorrelation3Histos( fHistoInvMassData, 
									fHistoInvMassMCRec,
									fHistoInvMassMCTrue,
									"","M_{#gamma#gamma}","Counts",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,200.);

	if (fitInvMassData!=0x0){
		DrawGammaSetMarkerTF1( fitInvMassData, 1, 1.,kGray); 
		fitInvMassData->Draw("same");
	}
	if (fitInvMassMCRec!=0x0){
		DrawGammaSetMarkerTF1( fitInvMassMCRec, 1, 1.,kRed-2); 
		fitInvMassMCRec->Draw("same");
	}
	if (fitInvMassMCTrue!=0x0){
		DrawGammaSetMarkerTF1( fitInvMassMCTrue, 1, 1.,kGreen-2); 
		fitInvMassMCTrue->Draw("same");
	}
	
	padDataSpectra->cd(2);
	padDataSpectra->cd(2)->SetTopMargin(topMargin);
	padDataSpectra->cd(2)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(2)->SetRightMargin(rightMargin);
	padDataSpectra->cd(2)->SetLeftMargin(leftMargin);
	
	fHistoIsoMinData->Rebin(rebin);
	fHistoIsoMinMCRec->Rebin(rebin);
	fHistoIsoMinMCTrue->Rebin(rebin);
	
	DrawCorrelation3Histos( fHistoIsoMinData, 
									fHistoIsoMinMCRec,
									fHistoIsoMinMCTrue,
									"","R_{Iso}","N_{trig}",
									kTRUE,1.2 ,1e-10,
									kTRUE,0. ,8.,
									kFALSE, 0.,200.);

	padDataSpectra->cd(3);
	TLatex *textPtBin = new TLatex(0.1,0.8,Form("%3.2f GeV/c < p_{T} < %3.2f GeV/c",ptStart,ptEnd));
	textPtBin->SetNDC();
	textPtBin->SetTextColor(1);
	textPtBin->SetTextSize(0.06);
	textPtBin->Draw();

	
	padDataSpectra->cd(4);
	padDataSpectra->cd(4)->SetTopMargin(topMargin);
	padDataSpectra->cd(4)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(4)->SetRightMargin(rightMargin);
	padDataSpectra->cd(4)->SetLeftMargin(leftMargin);

	TLatex *textInclusive = new TLatex(0.2,0.88,"Inclusive #pi^{0}");
	textInclusive->SetNDC();
	textInclusive->SetTextColor(1);
	textInclusive->SetTextSize(0.06);
	
	DrawCorrelation3Histos( fHistodEtaData, 
									fHistodEtaMCRec,
									fHistodEtaMCTrue,
									"","#Delta#eta","#frac{dN_{ch,Ass}}{N_{#pi^{0},trig}} #frac{1}{d#Delta#eta}",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,200.);
	textInclusive->Draw();	
	
	padDataSpectra->cd(5);
	padDataSpectra->cd(5)->SetTopMargin(topMargin);
	padDataSpectra->cd(5)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(5)->SetRightMargin(rightMargin);
	padDataSpectra->cd(5)->SetLeftMargin(leftMargin);

	TLatex *textIsolation = new TLatex(0.2,0.88,"Isolated #pi^{0}");
	textIsolation->SetNDC();
	textIsolation->SetTextColor(1);
	textIsolation->SetTextSize(0.06);
	

	DrawCorrelation3Histos( 	fHistoIsodEtaData, 
									fHistoIsodEtaMCRec,
									fHistoIsodEtaMCTrue,
									"","#Delta#eta","#frac{dN_{ch,Ass}}{N_{#pi^{0},trig}} #frac{1}{d#Delta#eta}",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,200.);
	textIsolation->Draw();
	
	padDataSpectra->cd(6);
	padDataSpectra->cd(6)->SetTopMargin(topMargin);
	padDataSpectra->cd(6)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(6)->SetRightMargin(rightMargin);
	padDataSpectra->cd(6)->SetLeftMargin(leftMargin);

	TLatex *textSideBand = new TLatex(0.2,0.88,"#pi^{0} Sideband");
	textSideBand->SetNDC();
	textSideBand->SetTextColor(1);
	textSideBand->SetTextSize(0.06);
	
	DrawCorrelation3Histos( 	fHistoSBdEtaData, 
									fHistoSBdEtaMCRec,
									fHistoSBdEtaMCTrue,
									"","#Delta#eta","#frac{dN_{ch,Ass}}{N_{#pi^{0},trig}} #frac{1}{d#Delta#eta}",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,200.);
	textSideBand->Draw();		
			
	padDataSpectra->cd(7);
	padDataSpectra->cd(7)->SetTopMargin(topMargin);
	padDataSpectra->cd(7)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(7)->SetRightMargin(rightMargin);
	padDataSpectra->cd(7)->SetLeftMargin(leftMargin);

	DrawCorrelation3Histos( 	fHistodPhiData, 
									fHistodPhiMCRec,
									fHistodPhiMCTrue,
									"","#Delta#phi","#frac{dN_{ch,Ass}}{N_{#pi^{0},trig}} #frac{1}{d#Delta#phi}",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,200.);
			
	padDataSpectra->cd(8);
	padDataSpectra->cd(8)->SetTopMargin(topMargin);
	padDataSpectra->cd(8)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(8)->SetRightMargin(rightMargin);
	padDataSpectra->cd(8)->SetLeftMargin(leftMargin);

	DrawCorrelation3Histos( 	fHistoIsodPhiData, 
									fHistoIsodPhiMCRec,
									fHistoIsodPhiMCTrue,
									"","#Delta#phi","#frac{dN_{ch,Ass}}{N_{#pi^{0},trig}} #frac{1}{d#Delta#phi}",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,200.);
	
	padDataSpectra->cd(9);
	padDataSpectra->cd(9)->SetTopMargin(topMargin);
	padDataSpectra->cd(9)->SetBottomMargin(bottomMargin);
	padDataSpectra->cd(9)->SetRightMargin(rightMargin);
	padDataSpectra->cd(9)->SetLeftMargin(leftMargin);

	DrawCorrelation3Histos( 	fHistoSBdPhiData, 
									fHistoSBdPhiMCRec,
									fHistoSBdPhiMCTrue,
									"","#Delta#phi","#frac{dN_{ch,Ass}}{N_{#pi^{0},trig}} #frac{1}{d#Delta#phi}",
									kTRUE,1.2 ,1e-10,
									kFALSE,0. ,0.,
									kFALSE, 0.,200.);
	
	canvasDataSpectra->Print(namePlot.Data());
	delete padDataSpectra;
	delete canvasDataSpectra;
	delete fitInvMassData;
	delete fitInvMassMCRec;
	delete fitInvMassMCTrue;
}

//__________________________________________ Plotting all Invariant Mass bins _______________________________________________
void PlotdPhiInPtBins(TH1D** fHistosdPhi, TF1** fFitsdPhi, TString namePlot, TString nameCanvas, TString namePad, 
							 Int_t fRowPlot, Int_t fColumnPlot, Int_t fStartBinPtRange, Int_t fNumberPtBins, Double_t* fRangeBinsPt){
	TGaxis::SetMaxDigits(3);

	TCanvas * canvasDataSpectra = new TCanvas(nameCanvas.Data(),"",2800,2000);  // gives the page size
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
						"d#Delta#phi","dN_{ch,Ass}/dN_{#pi^{0},trig} 1/d#Delta#phi");
			if(fFitsdPhi[iPt]!=0x0){
				fFitsdPhi[iPt]->SetLineColor(kBlue);
				fFitsdPhi[iPt]->SetLineWidth(0.7);
				fFitsdPhi[iPt]->Draw("same");
			}
	}
	canvasDataSpectra->Print(namePlot.Data());
	delete padDataSpectra;
	delete canvasDataSpectra;
}


void ComposePi0Correlation(TString nameFile = "CorrelationOutput1stStep.root", TString cutSelection = "001023", TString suffix ="eps"){
	
	StyleSettingsThesis();
	SetPlotStyleNConts(99);

	TString outputDirectory;
	TString outputDirectory1;
	TString outputDirectory2;
	outputDirectory1 =	 Form("%s",cutSelection.Data());
	outputDirectory2 =	 Form("%s/%s/",cutSelection.Data(),suffix.Data());
	outputDirectory =	 	Form("%s/%s/Pi0Correlation",cutSelection.Data(),suffix.Data());
	gSystem->Exec("mkdir "+outputDirectory1);
	gSystem->Exec("mkdir "+outputDirectory2);
	gSystem->Exec("mkdir "+outputDirectory);


	TFile* fileCorrRead = new TFile(nameFile.Data(),"UPDATE");
	TDirectory*  directoryPi0Corr = 		(TDirectory*)fileCorrRead->Get(Form("CorrPi0_%s",  cutSelection.Data())); 	
	
	
	TH2D* histoDataCorrPi0_Phi_Eta = (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0_Phi_Eta");
	cout << "Data: "<<histoDataCorrPi0_Phi_Eta->GetEntries()<< endl;
	Double_t entriesData = histoDataCorrPi0_Phi_Eta->GetEntries();
	TH2D* histoDataCorrPi0_InvMass_Pt= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0_InvMass_Pt");
	ConvGammaRebinWithBinCorrection2D(histoDataCorrPi0_InvMass_Pt, 1, 1, 3);
	TH2D* histoData2DPi0_dEta_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0_dEtaCh_PtTrig");
	histoData2DPi0_dEta_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0_dEta_PtTrig, 4, 1, 3);
	TH2D* histoData2DPi0_dEta_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0_dEtaCh_PtTrig_minPtAssA");
	histoData2DPi0_dEta_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DPi0_dEta_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0_dEtaCh_PtTrig_minPtAssB");
	histoData2DPi0_dEta_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoData2DPi0_dPhi_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0_dPhiCh_PtTrig");
	histoData2DPi0_dPhi_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoData2DPi0_dPhi_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0_dPhiCh_PtTrig_minPtAssA");
	histoData2DPi0_dPhi_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DPi0_dPhi_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0_dPhiCh_PtTrig_minPtAssB");
	histoData2DPi0_dPhi_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoDataCorrPi0SideBand_Phi_Eta= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0SideBand_Phi_Eta");
	TH2D* histoDataCorrPi0SideBand_InvMass_Pt= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0SideBand_InvMass_Pt");
	TH2D* histoData2DPi0SideBand_dEta_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0SideBand_dEtaCh_PtTrig");
	histoData2DPi0SideBand_dEta_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0SideBand_dEta_PtTrig, 4, 1, 3);
	TH2D* histoData2DPi0SideBand_dEta_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0SideBand_dEtaCh_PtTrig_minPtAssA");
	histoData2DPi0SideBand_dEta_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0SideBand_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DPi0SideBand_dEta_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0SideBand_dEtaCh_PtTrig_minPtAssB");
	histoData2DPi0SideBand_dEta_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0SideBand_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoData2DPi0SideBand_dPhi_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0SideBand_dPhiCh_PtTrig");
	histoData2DPi0SideBand_dPhi_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0SideBand_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoData2DPi0SideBand_dPhi_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0SideBand_dPhiCh_PtTrig_minPtAssA");
	histoData2DPi0SideBand_dPhi_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0SideBand_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DPi0SideBand_dPhi_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0SideBand_dPhiCh_PtTrig_minPtAssB");
	histoData2DPi0SideBand_dPhi_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0SideBand_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoDataCorrPi0_IsoMin_Pt= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0_IsoMin_Pt");		
	TH2D* histoData2DPi0Iso_dEta_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0Iso_dEtaCh_PtTrig");
	histoData2DPi0Iso_dEta_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0Iso_dEta_PtTrig, 4, 1, 3);
	TH2D* histoData2DPi0Iso_dEta_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0Iso_dEtaCh_PtTrig_minPtAssA");
	histoData2DPi0Iso_dEta_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0Iso_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DPi0Iso_dEta_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0Iso_dEtaCh_PtTrig_minPtAssB");
	histoData2DPi0Iso_dEta_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0Iso_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoData2DPi0Iso_dPhi_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0Iso_dPhiCh_PtTrig");
	histoData2DPi0Iso_dPhi_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0Iso_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoData2DPi0Iso_dPhi_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0Iso_dPhiCh_PtTrig_minPtAssA");
	histoData2DPi0Iso_dPhi_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0Iso_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DPi0Iso_dPhi_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_Data_CorrPi0Iso_dPhiCh_PtTrig_minPtAssB");
	histoData2DPi0Iso_dPhi_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DPi0Iso_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	
	TH2D* histoMCRecCorrPi0_Phi_Eta = (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0_Phi_Eta");
	cout << "MC reconstructed: "<< histoMCRecCorrPi0_Phi_Eta->GetEntries()<< endl;
	Double_t entriesMCRec = histoMCRecCorrPi0_Phi_Eta->GetEntries();
	TH2D* histoMCRecCorrPi0_InvMass_Pt= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0_InvMass_Pt");
	ConvGammaRebinWithBinCorrection2D(histoMCRecCorrPi0_InvMass_Pt, 1, 1, 3);
	TH2D* histoMCRec2DPi0_dEta_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0_dEtaCh_PtTrig");
	histoMCRec2DPi0_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DPi0_dEta_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0_dEtaCh_PtTrig_minPtAssA");
	histoMCRec2DPi0_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DPi0_dEta_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0_dEtaCh_PtTrig_minPtAssB");
	histoMCRec2DPi0_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCRec2DPi0_dPhi_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0_dPhiCh_PtTrig");
	histoMCRec2DPi0_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DPi0_dPhi_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0_dPhiCh_PtTrig_minPtAssA");
	histoMCRec2DPi0_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DPi0_dPhi_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0_dPhiCh_PtTrig_minPtAssB");
	histoMCRec2DPi0_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCRecCorrPi0SideBand_Phi_Eta= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0SideBand_Phi_Eta");
	TH2D* histoMCRecCorrPi0SideBand_InvMass_Pt= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0SideBand_InvMass_Pt");
	TH2D* histoMCRec2DPi0SideBand_dEta_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0SideBand_dEtaCh_PtTrig");
	histoMCRec2DPi0SideBand_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0SideBand_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DPi0SideBand_dEta_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0SideBand_dEtaCh_PtTrig_minPtAssA");
	histoMCRec2DPi0SideBand_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0SideBand_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DPi0SideBand_dEta_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0SideBand_dEtaCh_PtTrig_minPtAssB");
	histoMCRec2DPi0SideBand_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0SideBand_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCRec2DPi0SideBand_dPhi_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0SideBand_dPhiCh_PtTrig");
	histoMCRec2DPi0SideBand_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0SideBand_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DPi0SideBand_dPhi_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0SideBand_dPhiCh_PtTrig_minPtAssA");
	histoMCRec2DPi0SideBand_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0SideBand_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DPi0SideBand_dPhi_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0SideBand_dPhiCh_PtTrig_minPtAssB");
	histoMCRec2DPi0SideBand_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0SideBand_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCRecCorrPi0_IsoMin_Pt= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0_IsoMin_Pt");		
	TH2D* histoMCRec2DPi0Iso_dEta_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0Iso_dEtaCh_PtTrig");
	histoMCRec2DPi0Iso_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0Iso_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DPi0Iso_dEta_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0Iso_dEtaCh_PtTrig_minPtAssA");
	histoMCRec2DPi0Iso_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0Iso_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DPi0Iso_dEta_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0Iso_dEtaCh_PtTrig_minPtAssB");
	histoMCRec2DPi0Iso_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0Iso_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCRec2DPi0Iso_dPhi_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0Iso_dPhiCh_PtTrig");
	histoMCRec2DPi0Iso_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0Iso_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DPi0Iso_dPhi_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0Iso_dPhiCh_PtTrig_minPtAssA");
	histoMCRec2DPi0Iso_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0Iso_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DPi0Iso_dPhi_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCRec_CorrPi0Iso_dPhiCh_PtTrig_minPtAssB");
	histoMCRec2DPi0Iso_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DPi0Iso_dPhi_PtTrig_minPtAss1, 4, 1, 3);

	TH2D* histoMCTrueCorrPi0_Phi_Eta = (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0_Phi_Eta");
	cout << "MC true: "<< histoMCTrueCorrPi0_Phi_Eta->GetEntries()<< endl;
	Double_t entriesMCTrue = histoMCTrueCorrPi0_Phi_Eta->GetEntries();
	TH2D* histoMCTrueCorrPi0_InvMass_Pt= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0_InvMass_Pt");
	ConvGammaRebinWithBinCorrection2D(histoMCTrueCorrPi0_InvMass_Pt, 1, 1, 3);
	TH2D* histoMCTrue2DPi0_dEta_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0_dEtaCh_PtTrig");
	histoMCTrue2DPi0_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DPi0_dEta_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0_dEtaCh_PtTrig_minPtAssA");
	histoMCTrue2DPi0_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DPi0_dEta_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0_dEtaCh_PtTrig_minPtAssB");
	histoMCTrue2DPi0_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCTrue2DPi0_dPhi_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0_dPhiCh_PtTrig");
	histoMCTrue2DPi0_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DPi0_dPhi_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0_dPhiCh_PtTrig_minPtAssA");
	histoMCTrue2DPi0_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DPi0_dPhi_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0_dPhiCh_PtTrig_minPtAssB");
	histoMCTrue2DPi0_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCTrueCorrPi0SideBand_Phi_Eta= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0SideBand_Phi_Eta");
	TH2D* histoMCTrueCorrPi0SideBand_InvMass_Pt= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0SideBand_InvMass_Pt");
	TH2D* histoMCTrue2DPi0SideBand_dEta_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0SideBand_dEtaCh_PtTrig");
	histoMCTrue2DPi0SideBand_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0SideBand_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DPi0SideBand_dEta_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0SideBand_dEtaCh_PtTrig_minPtAssA");
	histoMCTrue2DPi0SideBand_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0SideBand_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DPi0SideBand_dEta_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0SideBand_dEtaCh_PtTrig_minPtAssB");
	histoMCTrue2DPi0SideBand_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0SideBand_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCTrue2DPi0SideBand_dPhi_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0SideBand_dPhiCh_PtTrig");
	histoMCTrue2DPi0SideBand_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0SideBand_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DPi0SideBand_dPhi_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0SideBand_dPhiCh_PtTrig_minPtAssA");
	histoMCTrue2DPi0SideBand_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0SideBand_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DPi0SideBand_dPhi_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0SideBand_dPhiCh_PtTrig_minPtAssB");
	histoMCTrue2DPi0SideBand_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0SideBand_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCTrueCorrPi0_IsoMin_Pt= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0_IsoMin_Pt");		
	TH2D* histoMCTrue2DPi0Iso_dEta_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0Iso_dEtaCh_PtTrig");
	histoMCTrue2DPi0Iso_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0Iso_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DPi0Iso_dEta_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0Iso_dEtaCh_PtTrig_minPtAssA");
	histoMCTrue2DPi0Iso_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0Iso_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DPi0Iso_dEta_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0Iso_dEtaCh_PtTrig_minPtAssB");
	histoMCTrue2DPi0Iso_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0Iso_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCTrue2DPi0Iso_dPhi_PtTrig= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0Iso_dPhiCh_PtTrig");
	histoMCTrue2DPi0Iso_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0Iso_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DPi0Iso_dPhi_PtTrig_minPtAss05= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0Iso_dPhiCh_PtTrig_minPtAssA");
	histoMCTrue2DPi0Iso_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0Iso_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DPi0Iso_dPhi_PtTrig_minPtAss1= (TH2D*)directoryPi0Corr->Get("ESD_MCTrue_CorrPi0Iso_dPhiCh_PtTrig_minPtAssB");
	histoMCTrue2DPi0Iso_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DPi0Iso_dPhi_PtTrig_minPtAss1, 4, 1, 3);

	Initialize(20);
	FillHistoArray(histoDataCorrPi0_InvMass_Pt, fHistoDataCorrelationPi0InvMass, 1, 20, fPtBinnningPi0, "Pi0_Data_InvMass_Pt" );
	FillHistoArray(histoData2DPi0_dEta_PtTrig, fHistoDataCorrelationPi0dEtaCh, 1, 20, fPtBinnningPi0, "Pi0_Data_dEta_Pt" );
	FillHistoArray(histoData2DPi0_dEta_PtTrig_minPtAss1, fHistoDataCorrelationPi0dEtaCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0_Data_dEta_Pt_minPtAss1" );
	FillHistoArray(histoData2DPi0_dEta_PtTrig_minPtAss05, fHistoDataCorrelationPi0dEtaCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0_Data_dEta_Pt_minPtAss05" );
	FillHistoArray(histoData2DPi0_dPhi_PtTrig, fHistoDataCorrelationPi0dPhiCh, 1, 20, fPtBinnningPi0, "Pi0_Data_dPhi_Pt" );
	FillHistoArray(histoData2DPi0_dPhi_PtTrig_minPtAss1, fHistoDataCorrelationPi0dPhiCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0_Data_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoData2DPi0_dPhi_PtTrig_minPtAss05, fHistoDataCorrelationPi0dPhiCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0_Data_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoDataCorrPi0_IsoMin_Pt, fHistoDataCorrelationPi0IsoMin, 1, 20, fPtBinnningPi0, "Pi0_Data_IsoMin_Pt" );
	FillHistoArray(histoData2DPi0Iso_dEta_PtTrig, fHistoDataCorrelationPi0IsodEtaCh, 1, 20, fPtBinnningPi0, "Pi0Iso_Data_dEta_Pt" );
	FillHistoArray(histoData2DPi0Iso_dEta_PtTrig_minPtAss05, fHistoDataCorrelationPi0IsodEtaCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0Iso_Data_dEta_Pt_minPtAss05");
	FillHistoArray(histoData2DPi0Iso_dEta_PtTrig_minPtAss1, fHistoDataCorrelationPi0IsodEtaCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0Iso_Data_dEta_Pt_minPtAss1");
	FillHistoArray(histoData2DPi0Iso_dPhi_PtTrig, fHistoDataCorrelationPi0IsodPhiCh, 1, 20, fPtBinnningPi0, "Pi0Iso_Data_dPhi_Pt" );
	FillHistoArray(histoData2DPi0Iso_dPhi_PtTrig_minPtAss05, fHistoDataCorrelationPi0IsodPhiCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0Iso_Data_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoData2DPi0Iso_dPhi_PtTrig_minPtAss1, fHistoDataCorrelationPi0IsodPhiCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0Iso_Data_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoData2DPi0SideBand_dEta_PtTrig, fHistoDataCorrelationPi0SideBanddEtaCh, 1, 20, fPtBinnningPi0, "Pi0SideBand_Data_dEta_Pt" );
	FillHistoArray(histoData2DPi0SideBand_dEta_PtTrig_minPtAss1, fHistoDataCorrelationPi0SideBanddEtaCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0SideBand_Data_dEta_Pt_minPtAss1" );
	FillHistoArray(histoData2DPi0SideBand_dEta_PtTrig_minPtAss05, fHistoDataCorrelationPi0SideBanddEtaCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0SideBand_Data_dEta_Pt_minPtAss05" );
	FillHistoArray(histoData2DPi0SideBand_dPhi_PtTrig, fHistoDataCorrelationPi0SideBanddPhiCh, 1, 20, fPtBinnningPi0, "Pi0SideBand_Data_dPhi_Pt" );
	FillHistoArray(histoData2DPi0SideBand_dPhi_PtTrig_minPtAss1, fHistoDataCorrelationPi0SideBanddPhiCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0SideBand_Data_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoData2DPi0SideBand_dPhi_PtTrig_minPtAss05, fHistoDataCorrelationPi0SideBanddPhiCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0SideBand_Data_dPhi_Pt_minPtAss05" );

	FillHistoArray(histoMCRecCorrPi0_InvMass_Pt, fHistoMCRecCorrelationPi0InvMass, 1, 20, fPtBinnningPi0, "Pi0_MCRec_InvMass_Pt" );
	FillHistoArray(histoMCRec2DPi0_dEta_PtTrig, fHistoMCRecCorrelationPi0dEtaCh, 1, 20, fPtBinnningPi0, "Pi0_MCRec_dEta_Pt" );
	FillHistoArray(histoMCRec2DPi0_dEta_PtTrig_minPtAss1, fHistoMCRecCorrelationPi0dEtaCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0_MCRec_dEta_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DPi0_dEta_PtTrig_minPtAss05, fHistoMCRecCorrelationPi0dEtaCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0_MCRec_dEta_Pt_minPtAss05" );
	FillHistoArray(histoMCRec2DPi0_dPhi_PtTrig, fHistoMCRecCorrelationPi0dPhiCh, 1, 20, fPtBinnningPi0, "Pi0_MCRec_dPhi_Pt" );
	FillHistoArray(histoMCRec2DPi0_dPhi_PtTrig_minPtAss1, fHistoMCRecCorrelationPi0dPhiCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0_MCRec_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DPi0_dPhi_PtTrig_minPtAss05, fHistoMCRecCorrelationPi0dPhiCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0_MCRec_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoMCRecCorrPi0_IsoMin_Pt, fHistoMCRecCorrelationPi0IsoMin, 1, 20, fPtBinnningPi0, "Pi0_MCRec_IsoMin_Pt" );
	FillHistoArray(histoMCRec2DPi0Iso_dEta_PtTrig, fHistoMCRecCorrelationPi0IsodEtaCh, 1, 20, fPtBinnningPi0, "Pi0Iso_MCRec_dEta_Pt" );
	FillHistoArray(histoMCRec2DPi0Iso_dEta_PtTrig_minPtAss05, fHistoMCRecCorrelationPi0IsodEtaCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0Iso_MCRec_dEta_Pt_minPtAss05");
	FillHistoArray(histoMCRec2DPi0Iso_dEta_PtTrig_minPtAss1, fHistoMCRecCorrelationPi0IsodEtaCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0Iso_MCRec_dEta_Pt_minPtAss1");
	FillHistoArray(histoMCRec2DPi0Iso_dPhi_PtTrig, fHistoMCRecCorrelationPi0IsodPhiCh, 1, 20, fPtBinnningPi0, "Pi0Iso_MCRec_dPhi_Pt" );
	FillHistoArray(histoMCRec2DPi0Iso_dPhi_PtTrig_minPtAss05, fHistoMCRecCorrelationPi0IsodPhiCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0Iso_MCRec_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoMCRec2DPi0Iso_dPhi_PtTrig_minPtAss1, fHistoMCRecCorrelationPi0IsodPhiCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0Iso_MCRec_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DPi0SideBand_dEta_PtTrig, fHistoMCRecCorrelationPi0SideBanddEtaCh, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCRec_dEta_Pt" );
	FillHistoArray(histoMCRec2DPi0SideBand_dEta_PtTrig_minPtAss1, fHistoMCRecCorrelationPi0SideBanddEtaCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCRec_dEta_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DPi0SideBand_dEta_PtTrig_minPtAss05, fHistoMCRecCorrelationPi0SideBanddEtaCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCRec_dEta_Pt_minPtAss05" );
	FillHistoArray(histoMCRec2DPi0SideBand_dPhi_PtTrig, fHistoMCRecCorrelationPi0SideBanddPhiCh, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCRec_dPhi_Pt" );
	FillHistoArray(histoMCRec2DPi0SideBand_dPhi_PtTrig_minPtAss1, fHistoMCRecCorrelationPi0SideBanddPhiCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCRec_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DPi0SideBand_dPhi_PtTrig_minPtAss05, fHistoMCRecCorrelationPi0SideBanddPhiCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCRec_dPhi_Pt_minPtAss05" );

	FillHistoArray(histoMCTrueCorrPi0_InvMass_Pt, fHistoMCTrueCorrelationPi0InvMass, 1, 20, fPtBinnningPi0, "Pi0_MCTrue_InvMass_Pt" );
	FillHistoArray(histoMCTrue2DPi0_dEta_PtTrig, fHistoMCTrueCorrelationPi0dEtaCh, 1, 20, fPtBinnningPi0, "Pi0_MCTrue_dEta_Pt" );
	FillHistoArray(histoMCTrue2DPi0_dEta_PtTrig_minPtAss1, fHistoMCTrueCorrelationPi0dEtaCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0_MCTrue_dEta_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DPi0_dEta_PtTrig_minPtAss05, fHistoMCTrueCorrelationPi0dEtaCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0_MCTrue_dEta_Pt_minPtAss05" );
	FillHistoArray(histoMCTrue2DPi0_dPhi_PtTrig, fHistoMCTrueCorrelationPi0dPhiCh, 1, 20, fPtBinnningPi0, "Pi0_MCTrue_dPhi_Pt" );
	FillHistoArray(histoMCTrue2DPi0_dPhi_PtTrig_minPtAss1, fHistoMCTrueCorrelationPi0dPhiCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0_MCTrue_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DPi0_dPhi_PtTrig_minPtAss05, fHistoMCTrueCorrelationPi0dPhiCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0_MCTrue_dPhi_Pt_minPtAss05" );	
	FillHistoArray(histoMCTrueCorrPi0_IsoMin_Pt, fHistoMCTrueCorrelationPi0IsoMin, 1, 20, fPtBinnningPi0, "Pi0_MCTrue_IsoMin_Pt" );
	FillHistoArray(histoMCTrue2DPi0Iso_dEta_PtTrig, fHistoMCTrueCorrelationPi0IsodEtaCh, 1, 20, fPtBinnningPi0, "Pi0Iso_MCTrue_dEta_Pt" );
	FillHistoArray(histoMCTrue2DPi0Iso_dEta_PtTrig_minPtAss05, fHistoMCTrueCorrelationPi0IsodEtaCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0Iso_MCTrue_dEta_Pt_minPtAss05");
	FillHistoArray(histoMCTrue2DPi0Iso_dEta_PtTrig_minPtAss1, fHistoMCTrueCorrelationPi0IsodEtaCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0Iso_MCTrue_dEta_Pt_minPtAss1");
	FillHistoArray(histoMCTrue2DPi0Iso_dPhi_PtTrig, fHistoMCTrueCorrelationPi0IsodPhiCh, 1, 20, fPtBinnningPi0, "Pi0Iso_MCTrue_dPhi_Pt" );
	FillHistoArray(histoMCTrue2DPi0Iso_dPhi_PtTrig_minPtAss05, fHistoMCTrueCorrelationPi0IsodPhiCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0Iso_MCTrue_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoMCTrue2DPi0Iso_dPhi_PtTrig_minPtAss1, fHistoMCTrueCorrelationPi0IsodPhiCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0Iso_MCTrue_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DPi0SideBand_dEta_PtTrig, fHistoMCTrueCorrelationPi0SideBanddEtaCh, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCTrue_dEta_Pt" );
	FillHistoArray(histoMCTrue2DPi0SideBand_dEta_PtTrig_minPtAss1, fHistoMCTrueCorrelationPi0SideBanddEtaCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCTrue_dEta_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DPi0SideBand_dEta_PtTrig_minPtAss05, fHistoMCTrueCorrelationPi0SideBanddEtaCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCTrue_dEta_Pt_minPtAss05" );
	FillHistoArray(histoMCTrue2DPi0SideBand_dPhi_PtTrig, fHistoMCTrueCorrelationPi0SideBanddPhiCh, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCTrue_dPhi_Pt" );
	FillHistoArray(histoMCTrue2DPi0SideBand_dPhi_PtTrig_minPtAss1, fHistoMCTrueCorrelationPi0SideBanddPhiCh_minPtAss1, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCTrue_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DPi0SideBand_dPhi_PtTrig_minPtAss05, fHistoMCTrueCorrelationPi0SideBanddPhiCh_minPtAss05, 1, 20, fPtBinnningPi0, "Pi0SideBand_MCTrue_dPhi_Pt_minPtAss05" );

	for (Int_t i = 1; i < 19; i++){
		PlotCorrelationBinsPt(  fHistoDataCorrelationPi0InvMass[i],fHistoMCRecCorrelationPi0InvMass[i], fHistoMCTrueCorrelationPi0InvMass[i],
								   fHistoDataCorrelationPi0IsoMin[i], fHistoMCRecCorrelationPi0IsoMin[i],fHistoMCTrueCorrelationPi0IsoMin[i],
									fHistoDataCorrelationPi0dPhiCh[i], fHistoMCRecCorrelationPi0dPhiCh[i], fHistoMCTrueCorrelationPi0dPhiCh[i],
									fHistoDataCorrelationPi0dEtaCh[i], fHistoMCRecCorrelationPi0dEtaCh[i], fHistoMCTrueCorrelationPi0dEtaCh[i],
									fHistoDataCorrelationPi0IsodPhiCh[i], fHistoMCRecCorrelationPi0IsodPhiCh[i], fHistoMCTrueCorrelationPi0IsodPhiCh[i],
									fHistoDataCorrelationPi0IsodEtaCh[i], fHistoMCRecCorrelationPi0IsodEtaCh[i], fHistoMCTrueCorrelationPi0IsodEtaCh[i],
									fHistoDataCorrelationPi0SideBanddPhiCh[i], fHistoMCRecCorrelationPi0SideBanddPhiCh[i], fHistoMCTrueCorrelationPi0SideBanddPhiCh[i],
									fHistoDataCorrelationPi0SideBanddEtaCh[i], fHistoMCRecCorrelationPi0SideBanddEtaCh[i], fHistoMCTrueCorrelationPi0SideBanddEtaCh[i],
									Form("%s/CompilationCorrelation_PtBin_%i.%s",outputDirectory.Data(),i,suffix.Data()),fPtBinnningPi0[i],fPtBinnningPi0[i+1],fPtRebinPi0[i],i);
		fFitDataCorrelationPi0dPhiChAwaySide[i] = FitPout(fHistoDataCorrelationPi0dPhiCh[i]);
	}
	for (Int_t i = 5; i < 19; i++){
		PlotCorrelationBinsPt(  fHistoDataCorrelationPi0InvMass[i],fHistoMCRecCorrelationPi0InvMass[i], fHistoMCTrueCorrelationPi0InvMass[i],
								   fHistoDataCorrelationPi0IsoMin[i], fHistoMCRecCorrelationPi0IsoMin[i],fHistoMCTrueCorrelationPi0IsoMin[i],
									fHistoDataCorrelationPi0dPhiCh_minPtAss05[i], fHistoMCRecCorrelationPi0dPhiCh_minPtAss05[i], fHistoMCTrueCorrelationPi0dPhiCh_minPtAss05[i],
									fHistoDataCorrelationPi0dEtaCh_minPtAss05[i], fHistoMCRecCorrelationPi0dEtaCh_minPtAss05[i], fHistoMCTrueCorrelationPi0dEtaCh_minPtAss05[i],
									fHistoDataCorrelationPi0IsodPhiCh_minPtAss05[i], fHistoMCRecCorrelationPi0IsodPhiCh_minPtAss05[i], fHistoMCTrueCorrelationPi0IsodPhiCh_minPtAss05[i],
									fHistoDataCorrelationPi0IsodEtaCh_minPtAss05[i], fHistoMCRecCorrelationPi0IsodEtaCh_minPtAss05[i], fHistoMCTrueCorrelationPi0IsodEtaCh_minPtAss05[i],
									fHistoDataCorrelationPi0SideBanddPhiCh_minPtAss05[i], fHistoMCRecCorrelationPi0SideBanddPhiCh_minPtAss05[i], fHistoMCTrueCorrelationPi0SideBanddPhiCh_minPtAss05[i],
									fHistoDataCorrelationPi0SideBanddEtaCh_minPtAss05[i], fHistoMCRecCorrelationPi0SideBanddEtaCh_minPtAss05[i], fHistoMCTrueCorrelationPi0SideBanddEtaCh_minPtAss05[i],
									Form("%s/CompilationCorrelation_minPtAss05_PtBin_%i.%s",outputDirectory.Data(),i,suffix.Data()),fPtBinnningPi0[i],fPtBinnningPi0[i+1],1,i);
		fFitDataCorrelationPi0dPhiChAwaySide_minPtAss05[i] = FitPout(fHistoDataCorrelationPi0dPhiCh_minPtAss05[i]);
	}
	for (Int_t i = 7; i < 19; i++){
		PlotCorrelationBinsPt(  fHistoDataCorrelationPi0InvMass[i],fHistoMCRecCorrelationPi0InvMass[i], fHistoMCTrueCorrelationPi0InvMass[i],
								   fHistoDataCorrelationPi0IsoMin[i], fHistoMCRecCorrelationPi0IsoMin[i],fHistoMCTrueCorrelationPi0IsoMin[i],
									fHistoDataCorrelationPi0dPhiCh_minPtAss1[i], fHistoMCRecCorrelationPi0dPhiCh_minPtAss1[i], fHistoMCTrueCorrelationPi0dPhiCh_minPtAss1[i],
									fHistoDataCorrelationPi0dEtaCh_minPtAss1[i], fHistoMCRecCorrelationPi0dEtaCh_minPtAss1[i], fHistoMCTrueCorrelationPi0dEtaCh_minPtAss1[i],
									fHistoDataCorrelationPi0IsodPhiCh_minPtAss1[i], fHistoMCRecCorrelationPi0IsodPhiCh_minPtAss1[i], fHistoMCTrueCorrelationPi0IsodPhiCh_minPtAss1[i],
									fHistoDataCorrelationPi0IsodEtaCh_minPtAss1[i], fHistoMCRecCorrelationPi0IsodEtaCh_minPtAss1[i], fHistoMCTrueCorrelationPi0IsodEtaCh_minPtAss1[i],
									fHistoDataCorrelationPi0SideBanddPhiCh_minPtAss1[i], fHistoMCRecCorrelationPi0SideBanddPhiCh_minPtAss1[i], fHistoMCTrueCorrelationPi0SideBanddPhiCh_minPtAss1[i],
									fHistoDataCorrelationPi0SideBanddEtaCh_minPtAss1[i], fHistoMCRecCorrelationPi0SideBanddEtaCh_minPtAss1[i], fHistoMCTrueCorrelationPi0SideBanddEtaCh_minPtAss1[i],
									Form("%s/CompilationCorrelation_minPtAss1_PtBin_%i.%s",outputDirectory.Data(),i,suffix.Data()),fPtBinnningPi0[i],fPtBinnningPi0[i+1],1,i);
		fFitDataCorrelationPi0dPhiChAwaySide_minPtAss1[i] = FitPout(fHistoDataCorrelationPi0dPhiCh_minPtAss1[i]);
	}
	PlotdPhiInPtBins(fHistoDataCorrelationPi0dPhiCh, fFitDataCorrelationPi0dPhiChAwaySide, Form("%s/CompilationCorrelationIncFit.%s",outputDirectory.Data(),suffix.Data()), "blubber", "bla", 4,5,1,19, fPtBinnningPi0);
	PlotdPhiInPtBins(fHistoDataCorrelationPi0dPhiCh_minPtAss05, fFitDataCorrelationPi0dPhiChAwaySide_minPtAss05, Form("%s/CompilationCorrelationIncFit_minPtAss1GeV.%s",outputDirectory.Data(),suffix.Data()), "blubber", "bla", 3,5,5,19, fPtBinnningPi0);
	PlotdPhiInPtBins(fHistoDataCorrelationPi0dPhiCh_minPtAss1, fFitDataCorrelationPi0dPhiChAwaySide_minPtAss1, Form("%s/CompilationCorrelationIncFit_minPtAss2GeV.%s",outputDirectory.Data(),suffix.Data()), "blubber", "bla", 3,4,7,19, fPtBinnningPi0);
}