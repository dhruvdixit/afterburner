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

TH1D** 	fHistoDataCorrelationEtaInvMass=				NULL;
TH1D** 	fHistoDataCorrelationEtadPhiCh=				NULL;
TH1D** 	fHistoDataCorrelationEtadEtaCh=				NULL;
TH1D** 	fHistoDataCorrelationEtadPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoDataCorrelationEtadEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoDataCorrelationEtadPhiCh_minPtAss05=NULL;
TH1D** 	fHistoDataCorrelationEtadEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoDataCorrelationEtaSideBandInvMass=				NULL;
TH1D** 	fHistoDataCorrelationEtaSideBanddPhiCh=				NULL;
TH1D** 	fHistoDataCorrelationEtaSideBanddEtaCh=				NULL;
TH1D** 	fHistoDataCorrelationEtaSideBanddPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoDataCorrelationEtaSideBanddEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoDataCorrelationEtaSideBanddPhiCh_minPtAss05=	NULL;
TH1D** 	fHistoDataCorrelationEtaSideBanddEtaCh_minPtAss05=	NULL;   

TH1D** 	fHistoDataCorrelationEtaIsoMin=				NULL;
TH1D** 	fHistoDataCorrelationEtaIsodPhiCh=				NULL;
TH1D** 	fHistoDataCorrelationEtaIsodEtaCh=				NULL;
TH1D** 	fHistoDataCorrelationEtaIsodPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoDataCorrelationEtaIsodEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoDataCorrelationEtaIsodPhiCh_minPtAss05=NULL;
TH1D** 	fHistoDataCorrelationEtaIsodEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCRecCorrelationEtaInvMass=				NULL;
TH1D** 	fHistoMCRecCorrelationEtadPhiCh=				NULL;
TH1D** 	fHistoMCRecCorrelationEtadEtaCh=				NULL;
TH1D** 	fHistoMCRecCorrelationEtadPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCRecCorrelationEtadEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCRecCorrelationEtadPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCRecCorrelationEtadEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCRecCorrelationEtaSideBandInvMass=				NULL;
TH1D** 	fHistoMCRecCorrelationEtaSideBanddPhiCh=				NULL;
TH1D** 	fHistoMCRecCorrelationEtaSideBanddEtaCh=				NULL;
TH1D** 	fHistoMCRecCorrelationEtaSideBanddPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCRecCorrelationEtaSideBanddEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCRecCorrelationEtaSideBanddPhiCh_minPtAss05=	NULL;
TH1D** 	fHistoMCRecCorrelationEtaSideBanddEtaCh_minPtAss05=	NULL;   

TH1D** 	fHistoMCRecCorrelationEtaIsoMin=				NULL;
TH1D** 	fHistoMCRecCorrelationEtaIsodPhiCh=				NULL;
TH1D** 	fHistoMCRecCorrelationEtaIsodEtaCh=				NULL;
TH1D** 	fHistoMCRecCorrelationEtaIsodPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCRecCorrelationEtaIsodEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCRecCorrelationEtaIsodPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCRecCorrelationEtaIsodEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCTrueCorrelationEtaInvMass=				NULL;
TH1D** 	fHistoMCTrueCorrelationEtadPhiCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationEtadEtaCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationEtadPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCTrueCorrelationEtadEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCTrueCorrelationEtadPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCTrueCorrelationEtadEtaCh_minPtAss05=NULL;   

TH1D** 	fHistoMCTrueCorrelationEtaSideBandInvMass=				NULL;
TH1D** 	fHistoMCTrueCorrelationEtaSideBanddPhiCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationEtaSideBanddEtaCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationEtaSideBanddPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCTrueCorrelationEtaSideBanddEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCTrueCorrelationEtaSideBanddPhiCh_minPtAss05=	NULL;
TH1D** 	fHistoMCTrueCorrelationEtaSideBanddEtaCh_minPtAss05=	NULL;   

TH1D** 	fHistoMCTrueCorrelationEtaIsoMin=				NULL;
TH1D** 	fHistoMCTrueCorrelationEtaIsodPhiCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationEtaIsodEtaCh=				NULL;
TH1D** 	fHistoMCTrueCorrelationEtaIsodPhiCh_minPtAss1=	NULL;
TH1D** 	fHistoMCTrueCorrelationEtaIsodEtaCh_minPtAss1=	NULL;   
TH1D** 	fHistoMCTrueCorrelationEtaIsodPhiCh_minPtAss05=NULL;
TH1D** 	fHistoMCTrueCorrelationEtaIsodEtaCh_minPtAss05=NULL;   


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

	fHistoDataCorrelationEtaInvMass = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtadPhiCh = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtadEtaCh = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtadPhiCh_minPtAss1 = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtadEtaCh_minPtAss1 = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtadPhiCh_minPtAss05 = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtadEtaCh_minPtAss05 = 	new TH1D*[numberOfBins];    

	fHistoDataCorrelationEtaSideBandInvMass = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtaSideBanddPhiCh = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtaSideBanddEtaCh = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtaSideBanddPhiCh_minPtAss1 = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtaSideBanddEtaCh_minPtAss1 = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtaSideBanddPhiCh_minPtAss05 = 	new TH1D*[numberOfBins];    
	fHistoDataCorrelationEtaSideBanddEtaCh_minPtAss05 = 	new TH1D*[numberOfBins];    

	fHistoDataCorrelationEtaIsoMin=				new TH1D*[numberOfBins];    
 	fHistoDataCorrelationEtaIsodPhiCh=				new TH1D*[numberOfBins];    
 	fHistoDataCorrelationEtaIsodEtaCh=				new TH1D*[numberOfBins];    
 	fHistoDataCorrelationEtaIsodPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
 	fHistoDataCorrelationEtaIsodEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
 	fHistoDataCorrelationEtaIsodPhiCh_minPtAss05=new TH1D*[numberOfBins];    
 	fHistoDataCorrelationEtaIsodEtaCh_minPtAss05=new TH1D*[numberOfBins];       

	fHistoMCRecCorrelationEtaInvMass=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationEtadPhiCh=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationEtadEtaCh=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationEtadPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationEtadEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
	fHistoMCRecCorrelationEtadPhiCh_minPtAss05=new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationEtadEtaCh_minPtAss05=new TH1D*[numberOfBins];       

	fHistoMCRecCorrelationEtaSideBandInvMass=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationEtaSideBanddPhiCh=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationEtaSideBanddEtaCh=				new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationEtaSideBanddPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationEtaSideBanddEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
	fHistoMCRecCorrelationEtaSideBanddPhiCh_minPtAss05=	new TH1D*[numberOfBins];    
	fHistoMCRecCorrelationEtaSideBanddEtaCh_minPtAss05=	new TH1D*[numberOfBins];       

	fHistoMCRecCorrelationEtaIsoMin=				new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationEtaIsodPhiCh=				new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationEtaIsodEtaCh=				new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationEtaIsodPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationEtaIsodEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
 	fHistoMCRecCorrelationEtaIsodPhiCh_minPtAss05=new TH1D*[numberOfBins];    
 	fHistoMCRecCorrelationEtaIsodEtaCh_minPtAss05=new TH1D*[numberOfBins];       

	fHistoMCTrueCorrelationEtaInvMass=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationEtadPhiCh=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationEtadEtaCh=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationEtadPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationEtadEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
	fHistoMCTrueCorrelationEtadPhiCh_minPtAss05=new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationEtadEtaCh_minPtAss05=new TH1D*[numberOfBins];       

	fHistoMCTrueCorrelationEtaSideBandInvMass=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationEtaSideBanddPhiCh=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationEtaSideBanddEtaCh=				new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationEtaSideBanddPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationEtaSideBanddEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
	fHistoMCTrueCorrelationEtaSideBanddPhiCh_minPtAss05=	new TH1D*[numberOfBins];    
	fHistoMCTrueCorrelationEtaSideBanddEtaCh_minPtAss05=	new TH1D*[numberOfBins];       
	
	fHistoMCTrueCorrelationEtaIsoMin=				new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationEtaIsodPhiCh=				new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationEtaIsodEtaCh=				new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationEtaIsodPhiCh_minPtAss1=	new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationEtaIsodEtaCh_minPtAss1=	new TH1D*[numberOfBins];       
 	fHistoMCTrueCorrelationEtaIsodPhiCh_minPtAss05=new TH1D*[numberOfBins];    
 	fHistoMCTrueCorrelationEtaIsodEtaCh_minPtAss05=new TH1D*[numberOfBins];       
}

TF1* FitInvMassGaussPol2(TH1D* fHistoInvMassSinglePt)
{

	cout<<"Start Fitting spectra"<<endl;
	fHistoInvMassSinglePt->GetXaxis()->SetRangeUser(0.5,0.6);
	Double_t mesonAmplitude =fHistoInvMassSinglePt->GetMaximum();
	
	TF1* fFitReco = new TF1("GaussExpLinear","(x<[1])*([0]*(exp(-0.5*((x-[1])/[2])^2)+exp((x-[1])/[3])*(1.-exp(-0.5*((x-[1])/[2])^2)))+[4]+[5]*x)+(x>=[1])*([0]*exp(-0.5*((x-[1])/[2])^2)+[4]+[5]*x)",0.5,0.6);
	TF1* fFitGausExp = new TF1("fGaussExp","(x<[1])*([0]*(exp(-0.5*((x-[1])/[2])^2)+exp((x-[1])/[3])*(1.-exp(-0.5*((x-[1])/[2])^2))))+(x>=[1])*([0]*exp(-0.5*((x-[1])/[2])^2))",0.5,0.6);
	TF1* fFitLinearBck = new TF1("Linear","[0]+[1]*x",0.5,0.6);

	Double_t fMesonWidthExpect = 0.0025;
	Double_t fMesonLambdaTail = 	0.009;
	Double_t fMesonMassExpect = TDatabasePDG::Instance()->GetParticle(221)->Mass();
	Double_t* fMesonWidthRange = 	new Double_t[2]; 	 fMesonWidthRange[0]=0.002;     fMesonWidthRange[1]=0.10;
	Double_t* fMesonLambdaTailRange = new Double_t[2]; fMesonLambdaTailRange[0]=0.0005; fMesonLambdaTailRange[1]=0.026;
	Double_t* fMesonMassRange = 	new Double_t[2]; 	fMesonMassRange[0]=	0.5; 	fMesonMassRange[1]=	0.6;;
	fFitReco->SetParameter(0,mesonAmplitude);
	fFitReco->FixParameter(1,fMesonMassExpect);
	fFitReco->SetParameter(2,fMesonWidthExpect);
	fFitReco->SetParameter(3,fMesonLambdaTail);
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

	fFitLinearBck->SetParError(0,fFitReco->GetParError(4));
	fFitLinearBck->SetParError(1,fFitReco->GetParError(5));

	if(TString(gMinuit->fCstatu.Data()).CompareTo("CONVERGED") == 0 || TString(gMinuit->fCstatu.Data()).CompareTo("SUCCESSFUL") == 0 ){
		cout << "Gausexp: \t" << fFitReco->GetParameter(0) <<"+-" << fFitReco->GetParError(0) << "\t " << fFitReco->GetParameter(1)<<"+-" << fFitReco->GetParError(1) << "\t "<< fFitReco->GetParameter(2) <<"+-" << fFitReco->GetParError(2)<< "\t "<< fFitReco->GetParameter(3) <<"+-" << fFitReco->GetParError(3)<<endl;
		cout << "Quadratic: \t"<<fFitReco->GetParameter(4)<<"+-" << fFitReco->GetParError(4) << "\t "<<fFitReco->GetParameter(5) <<"+-" << fFitReco->GetParError(5) << endl;
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
									kFALSE, 0.,180.);

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
									kFALSE, 0.,180.);

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
									kFALSE, 0.,180.);
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
									kFALSE, 0.,180.);
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
									kFALSE, 0.,180.);
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
									kFALSE, 0.,180.);
			
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
									kFALSE, 0.,180.);
	
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
									kFALSE, 0.,180.);
	
	canvasDataSpectra->Print(namePlot.Data());
	delete padDataSpectra;
	delete canvasDataSpectra;
	delete fitInvMassData;
	delete fitInvMassMCRec;
	delete fitInvMassMCTrue;
}


void ComposeEtaCorrelation(TString nameFile = "CorrelationOutput1stStep.root", TString cutSelection = "001023", TString suffix ="eps"){
	
	StyleSettingsThesis();
	SetPlotStyleNConts(99);

	TString outputDirectory;
	TString outputDirectory1;
	TString outputDirectory2;
	outputDirectory1 =	 Form("%s",cutSelection.Data());
	outputDirectory2 =	 Form("%s/%s/",cutSelection.Data(),suffix.Data());
	outputDirectory =	 	Form("%s/%s/EtaCorrelation",cutSelection.Data(),suffix.Data());
	gSystem->Exec("mkdir "+outputDirectory1);
	gSystem->Exec("mkdir "+outputDirectory2);
	gSystem->Exec("mkdir "+outputDirectory);


	TFile* fileCorrRead = new TFile(nameFile.Data(),"UPDATE");
	TDirectory*  directoryEtaCorr = 		(TDirectory*)fileCorrRead->Get(Form("CorrEta_%s",  cutSelection.Data())); 	
	
	
	TH2D* histoDataCorrEta_Phi_Eta = (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_Phi_Eta");
	cout << "Data: "<<histoDataCorrEta_Phi_Eta->GetEntries()<< endl;
	Double_t entriesData = histoDataCorrEta_Phi_Eta->GetEntries();
	TH2D* histoDataCorrEta_InvMass_Pt= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_InvMass_Pt");
	ConvGammaRebinWithBinCorrection2D(histoDataCorrEta_InvMass_Pt, 1, 1, 3);
	TH2D* histoData2DEta_dEta_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dEtaCh_PtTrig");
	histoData2DEta_dEta_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEta_dEta_PtTrig, 4, 1, 3);
	TH2D* histoData2DEta_dEta_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dEtaCh_PtTrig_minPtAssA");
	histoData2DEta_dEta_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEta_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DEta_dEta_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dEtaCh_PtTrig_minPtAssB");
	histoData2DEta_dEta_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEta_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoData2DEta_dPhi_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dPhiCh_PtTrig");
	histoData2DEta_dPhi_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEta_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoData2DEta_dPhi_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dPhiCh_PtTrig_minPtAssA");
	histoData2DEta_dPhi_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEta_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DEta_dPhi_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dPhiCh_PtTrig_minPtAssB");
	histoData2DEta_dPhi_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEta_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoDataCorrEtaSideBand_Phi_Eta= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_Phi_Eta");
	TH2D* histoDataCorrEtaSideBand_InvMass_Pt= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_InvMass_Pt");
	TH2D* histoData2DEtaSideBand_dEta_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dEtaCh_PtTrig");
	histoData2DEtaSideBand_dEta_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaSideBand_dEta_PtTrig, 4, 1, 3);
	TH2D* histoData2DEtaSideBand_dEta_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dEtaCh_PtTrig_minPtAssA");
	histoData2DEtaSideBand_dEta_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaSideBand_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DEtaSideBand_dEta_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dEtaCh_PtTrig_minPtAssB");
	histoData2DEtaSideBand_dEta_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaSideBand_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoData2DEtaSideBand_dPhi_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dPhiCh_PtTrig");
	histoData2DEtaSideBand_dPhi_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaSideBand_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoData2DEtaSideBand_dPhi_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dPhiCh_PtTrig_minPtAssA");
	histoData2DEtaSideBand_dPhi_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaSideBand_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DEtaSideBand_dPhi_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dPhiCh_PtTrig_minPtAssB");
	histoData2DEtaSideBand_dPhi_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaSideBand_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoDataCorrEta_IsoMin_Pt= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_IsoMin_Pt");		
	TH2D* histoData2DEtaIso_dEta_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaIso_dEtaCh_PtTrig");
	histoData2DEtaIso_dEta_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaIso_dEta_PtTrig, 4, 1, 3);
	TH2D* histoData2DEtaIso_dEta_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaIso_dEtaCh_PtTrig_minPtAssA");
	histoData2DEtaIso_dEta_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaIso_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DEtaIso_dEta_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaIso_dEtaCh_PtTrig_minPtAssB");
	histoData2DEtaIso_dEta_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaIso_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoData2DEtaIso_dPhi_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaIso_dPhiCh_PtTrig");
	histoData2DEtaIso_dPhi_PtTrig->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaIso_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoData2DEtaIso_dPhi_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaIso_dPhiCh_PtTrig_minPtAssA");
	histoData2DEtaIso_dPhi_PtTrig_minPtAss05->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaIso_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoData2DEtaIso_dPhi_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaIso_dPhiCh_PtTrig_minPtAssB");
	histoData2DEtaIso_dPhi_PtTrig_minPtAss1->Scale(1./entriesData);
	ConvGammaRebinWithBinCorrection2D(histoData2DEtaIso_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	
	TH2D* histoMCRecCorrEta_Phi_Eta = (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_Phi_Eta");
	cout << "MC reconstructed: "<< histoMCRecCorrEta_Phi_Eta->GetEntries()<< endl;
	Double_t entriesMCRec = histoMCRecCorrEta_Phi_Eta->GetEntries();
	TH2D* histoMCRecCorrEta_InvMass_Pt= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_InvMass_Pt");
	ConvGammaRebinWithBinCorrection2D(histoMCRecCorrEta_InvMass_Pt, 1, 1, 3);
	TH2D* histoMCRec2DEta_dEta_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dEtaCh_PtTrig");
	histoMCRec2DEta_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEta_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DEta_dEta_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dEtaCh_PtTrig_minPtAssA");
	histoMCRec2DEta_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEta_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DEta_dEta_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dEtaCh_PtTrig_minPtAssB");
	histoMCRec2DEta_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEta_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCRec2DEta_dPhi_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dPhiCh_PtTrig");
	histoMCRec2DEta_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEta_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DEta_dPhi_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dPhiCh_PtTrig_minPtAssA");
	histoMCRec2DEta_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEta_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DEta_dPhi_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dPhiCh_PtTrig_minPtAssB");
	histoMCRec2DEta_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEta_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCRecCorrEtaSideBand_Phi_Eta= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_Phi_Eta");
	TH2D* histoMCRecCorrEtaSideBand_InvMass_Pt= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_InvMass_Pt");
	TH2D* histoMCRec2DEtaSideBand_dEta_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dEtaCh_PtTrig");
	histoMCRec2DEtaSideBand_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaSideBand_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DEtaSideBand_dEta_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dEtaCh_PtTrig_minPtAssA");
	histoMCRec2DEtaSideBand_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaSideBand_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DEtaSideBand_dEta_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dEtaCh_PtTrig_minPtAssB");
	histoMCRec2DEtaSideBand_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaSideBand_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCRec2DEtaSideBand_dPhi_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dPhiCh_PtTrig");
	histoMCRec2DEtaSideBand_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaSideBand_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DEtaSideBand_dPhi_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dPhiCh_PtTrig_minPtAssA");
	histoMCRec2DEtaSideBand_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaSideBand_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DEtaSideBand_dPhi_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dPhiCh_PtTrig_minPtAssB");
	histoMCRec2DEtaSideBand_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaSideBand_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCRecCorrEta_IsoMin_Pt= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_IsoMin_Pt");		
	TH2D* histoMCRec2DEtaIso_dEta_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaIso_dEtaCh_PtTrig");
	histoMCRec2DEtaIso_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaIso_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DEtaIso_dEta_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaIso_dEtaCh_PtTrig_minPtAssA");
	histoMCRec2DEtaIso_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaIso_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DEtaIso_dEta_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaIso_dEtaCh_PtTrig_minPtAssB");
	histoMCRec2DEtaIso_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaIso_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCRec2DEtaIso_dPhi_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaIso_dPhiCh_PtTrig");
	histoMCRec2DEtaIso_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaIso_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCRec2DEtaIso_dPhi_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaIso_dPhiCh_PtTrig_minPtAssA");
	histoMCRec2DEtaIso_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaIso_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCRec2DEtaIso_dPhi_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaIso_dPhiCh_PtTrig_minPtAssB");
	histoMCRec2DEtaIso_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCRec2DEtaIso_dPhi_PtTrig_minPtAss1, 4, 1, 3);

	TH2D* histoMCTrueCorrEta_Phi_Eta = (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_Phi_Eta");
	cout << "MC true: "<< histoMCTrueCorrEta_Phi_Eta->GetEntries()<< endl;
	Double_t entriesMCTrue = histoMCTrueCorrEta_Phi_Eta->GetEntries();
	TH2D* histoMCTrueCorrEta_InvMass_Pt= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_InvMass_Pt");
	ConvGammaRebinWithBinCorrection2D(histoMCTrueCorrEta_InvMass_Pt, 1, 1, 3);
	TH2D* histoMCTrue2DEta_dEta_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dEtaCh_PtTrig");
	histoMCTrue2DEta_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEta_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DEta_dEta_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dEtaCh_PtTrig_minPtAssA");
	histoMCTrue2DEta_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEta_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DEta_dEta_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dEtaCh_PtTrig_minPtAssB");
	histoMCTrue2DEta_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEta_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCTrue2DEta_dPhi_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dPhiCh_PtTrig");
	histoMCTrue2DEta_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEta_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DEta_dPhi_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dPhiCh_PtTrig_minPtAssA");
	histoMCTrue2DEta_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEta_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DEta_dPhi_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dPhiCh_PtTrig_minPtAssB");
	histoMCTrue2DEta_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEta_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCTrueCorrEtaSideBand_Phi_Eta= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_Phi_Eta");
	TH2D* histoMCTrueCorrEtaSideBand_InvMass_Pt= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_InvMass_Pt");
	TH2D* histoMCTrue2DEtaSideBand_dEta_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dEtaCh_PtTrig");
	histoMCTrue2DEtaSideBand_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaSideBand_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DEtaSideBand_dEta_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dEtaCh_PtTrig_minPtAssA");
	histoMCTrue2DEtaSideBand_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaSideBand_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DEtaSideBand_dEta_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dEtaCh_PtTrig_minPtAssB");
	histoMCTrue2DEtaSideBand_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaSideBand_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCTrue2DEtaSideBand_dPhi_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dPhiCh_PtTrig");
	histoMCTrue2DEtaSideBand_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaSideBand_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DEtaSideBand_dPhi_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dPhiCh_PtTrig_minPtAssA");
	histoMCTrue2DEtaSideBand_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaSideBand_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DEtaSideBand_dPhi_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dPhiCh_PtTrig_minPtAssB");
	histoMCTrue2DEtaSideBand_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaSideBand_dPhi_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCTrueCorrEta_IsoMin_Pt= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_IsoMin_Pt");		
	TH2D* histoMCTrue2DEtaIso_dEta_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaIso_dEtaCh_PtTrig");
	histoMCTrue2DEtaIso_dEta_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaIso_dEta_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DEtaIso_dEta_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaIso_dEtaCh_PtTrig_minPtAssA");
	histoMCTrue2DEtaIso_dEta_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaIso_dEta_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DEtaIso_dEta_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaIso_dEtaCh_PtTrig_minPtAssB");
	histoMCTrue2DEtaIso_dEta_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaIso_dEta_PtTrig_minPtAss1, 4, 1, 3);
	TH2D* histoMCTrue2DEtaIso_dPhi_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaIso_dPhiCh_PtTrig");
	histoMCTrue2DEtaIso_dPhi_PtTrig->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaIso_dPhi_PtTrig, 4, 1, 3);
	TH2D* histoMCTrue2DEtaIso_dPhi_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaIso_dPhiCh_PtTrig_minPtAssA");
	histoMCTrue2DEtaIso_dPhi_PtTrig_minPtAss05->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaIso_dPhi_PtTrig_minPtAss05, 4, 1, 3);
	TH2D* histoMCTrue2DEtaIso_dPhi_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaIso_dPhiCh_PtTrig_minPtAssB");
	histoMCTrue2DEtaIso_dPhi_PtTrig_minPtAss1->Scale(1./entriesMCRec);
	ConvGammaRebinWithBinCorrection2D(histoMCTrue2DEtaIso_dPhi_PtTrig_minPtAss1, 4, 1, 3);

// 	TH2D* histoData2DEta_dEtaGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dEtaGa_PtTrig");
// 	TH2D* histoData2DEta_dEtaGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dEtaGa_PtTrig_minPtAssA");
// 	TH2D* histoData2DEta_dEtaGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dEtaGa_PtTrig_minPtAssB");
// 	TH2D* histoData2DEta_dPhiGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dPhiGa_PtTrig");
// 	TH2D* histoData2DEta_dPhiGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dPhiGa_PtTrig_minPtAssA");
// 	TH2D* histoData2DEta_dPhiGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEta_dPhiGa_PtTrig_minPtAssB");
// 	TH2D* histoData2DEtaSideBand_dEtaGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dEtaGa_PtTrig");
// 	TH2D* histoData2DEtaSideBand_dEtaGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dEtaGa_PtTrig_minPtAssA");
// 	TH2D* histoData2DEtaSideBand_dEtaGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dEtaGa_PtTrig_minPtAssB");
// 	TH2D* histoData2DEtaSideBand_dPhiGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dPhiGa_PtTrig");
// 	TH2D* histoData2DEtaSideBand_dPhiGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dPhiGa_PtTrig_minPtAssA");
// 	TH2D* histoData2DEtaSideBand_dPhiGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_Data_CorrEtaSideBand_dPhiGa_PtTrig_minPtAssB");
// 	TH2D* histoMCRec2DEta_dEtaGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dEtaGa_PtTrig");
// 	TH2D* histoMCRec2DEta_dEtaGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dEtaGa_PtTrig_minPtAssA");
// 	TH2D* histoMCRec2DEta_dEtaGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dEtaGa_PtTrig_minPtAssB");
// 	TH2D* histoMCRec2DEta_dPhiGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dPhiGa_PtTrig");
// 	TH2D* histoMCRec2DEta_dPhiGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dPhiGa_PtTrig_minPtAssA");
// 	TH2D* histoMCRec2DEta_dPhiGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEta_dPhiGa_PtTrig_minPtAssB");
// 	TH2D* histoMCRec2DEtaSideBand_dEtaGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dEtaGa_PtTrig");
// 	TH2D* histoMCRec2DEtaSideBand_dEtaGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dEtaGa_PtTrig_minPtAssA");
// 	TH2D* histoMCRec2DEtaSideBand_dEtaGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dEtaGa_PtTrig_minPtAssB");
// 	TH2D* histoMCRec2DEtaSideBand_dPhiGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dPhiGa_PtTrig");
// 	TH2D* histoMCRec2DEtaSideBand_dPhiGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dPhiGa_PtTrig_minPtAssA");
// 	TH2D* histoMCRec2DEtaSideBand_dPhiGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCRec_CorrEtaSideBand_dPhiGa_PtTrig_minPtAssB");
// 	TH2D* histoMCTrue2DEta_dEtaGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dEtaGa_PtTrig");
// 	TH2D* histoMCTrue2DEta_dEtaGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dEtaGa_PtTrig_minPtAssA");
// 	TH2D* histoMCTrue2DEta_dEtaGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dEtaGa_PtTrig_minPtAssB");
// 	TH2D* histoMCTrue2DEta_dPhiGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dPhiGa_PtTrig");
// 	TH2D* histoMCTrue2DEta_dPhiGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dPhiGa_PtTrig_minPtAssA");
// 	TH2D* histoMCTrue2DEta_dPhiGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEta_dPhiGa_PtTrig_minPtAssB");
// 	TH2D* histoMCTrue2DEtaSideBand_dEtaGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dEtaGa_PtTrig");
// 	TH2D* histoMCTrue2DEtaSideBand_dEtaGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dEtaGa_PtTrig_minPtAssA");
// 	TH2D* histoMCTrue2DEtaSideBand_dEtaGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dEtaGa_PtTrig_minPtAssB");
// 	TH2D* histoMCTrue2DEtaSideBand_dPhiGa_PtTrig= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dPhiGa_PtTrig");
// 	TH2D* histoMCTrue2DEtaSideBand_dPhiGa_PtTrig_minPtAss05= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dPhiGa_PtTrig_minPtAssA");
// 	TH2D* histoMCTrue2DEtaSideBand_dPhiGa_PtTrig_minPtAss1= (TH2D*)directoryEtaCorr->Get("ESD_MCTrue_CorrEtaSideBand_dPhiGa_PtTrig_minPtAssB");

	Initialize(12);
	FillHistoArray(histoDataCorrEta_InvMass_Pt, fHistoDataCorrelationEtaInvMass, 1, 12, fPtBinnningEta, "Eta_Data_InvMass_Pt" );
	FillHistoArray(histoData2DEta_dEta_PtTrig, fHistoDataCorrelationEtadEtaCh, 1, 12, fPtBinnningEta, "Eta_Data_dEta_Pt" );
	FillHistoArray(histoData2DEta_dEta_PtTrig_minPtAss1, fHistoDataCorrelationEtadEtaCh_minPtAss1, 1, 12, fPtBinnningEta, "Eta_Data_dEta_Pt_minPtAss1" );
	FillHistoArray(histoData2DEta_dEta_PtTrig_minPtAss05, fHistoDataCorrelationEtadEtaCh_minPtAss05, 1, 12, fPtBinnningEta, "Eta_Data_dEta_Pt_minPtAss05" );
	FillHistoArray(histoData2DEta_dPhi_PtTrig, fHistoDataCorrelationEtadPhiCh, 1, 12, fPtBinnningEta, "Eta_Data_dPhi_Pt" );
	FillHistoArray(histoData2DEta_dPhi_PtTrig_minPtAss1, fHistoDataCorrelationEtadPhiCh_minPtAss1, 1, 12, fPtBinnningEta, "Eta_Data_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoData2DEta_dPhi_PtTrig_minPtAss05, fHistoDataCorrelationEtadPhiCh_minPtAss05, 1, 12, fPtBinnningEta, "Eta_Data_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoDataCorrEta_IsoMin_Pt, fHistoDataCorrelationEtaIsoMin, 1, 12, fPtBinnningEta, "Eta_Data_IsoMin_Pt" );
	FillHistoArray(histoData2DEtaIso_dEta_PtTrig, fHistoDataCorrelationEtaIsodEtaCh, 1, 12, fPtBinnningEta, "EtaIso_Data_dEta_Pt" );
	FillHistoArray(histoData2DEtaIso_dEta_PtTrig_minPtAss05, fHistoDataCorrelationEtaIsodEtaCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaIso_Data_dEta_Pt_minPtAss05");
	FillHistoArray(histoData2DEtaIso_dEta_PtTrig_minPtAss1, fHistoDataCorrelationEtaIsodEtaCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaIso_Data_dEta_Pt_minPtAss1");
	FillHistoArray(histoData2DEtaIso_dPhi_PtTrig, fHistoDataCorrelationEtaIsodPhiCh, 1, 12, fPtBinnningEta, "EtaIso_Data_dPhi_Pt" );
	FillHistoArray(histoData2DEtaIso_dPhi_PtTrig_minPtAss05, fHistoDataCorrelationEtaIsodPhiCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaIso_Data_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoData2DEtaIso_dPhi_PtTrig_minPtAss1, fHistoDataCorrelationEtaIsodPhiCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaIso_Data_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoData2DEtaSideBand_dEta_PtTrig, fHistoDataCorrelationEtaSideBanddEtaCh, 1, 12, fPtBinnningEta, "EtaSideBand_Data_dEta_Pt" );
	FillHistoArray(histoData2DEtaSideBand_dEta_PtTrig_minPtAss1, fHistoDataCorrelationEtaSideBanddEtaCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaSideBand_Data_dEta_Pt_minPtAss1" );
	FillHistoArray(histoData2DEtaSideBand_dEta_PtTrig_minPtAss05, fHistoDataCorrelationEtaSideBanddEtaCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaSideBand_Data_dEta_Pt_minPtAss05" );
	FillHistoArray(histoData2DEtaSideBand_dPhi_PtTrig, fHistoDataCorrelationEtaSideBanddPhiCh, 1, 12, fPtBinnningEta, "EtaSideBand_Data_dPhi_Pt" );
	FillHistoArray(histoData2DEtaSideBand_dPhi_PtTrig_minPtAss1, fHistoDataCorrelationEtaSideBanddPhiCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaSideBand_Data_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoData2DEtaSideBand_dPhi_PtTrig_minPtAss05, fHistoDataCorrelationEtaSideBanddPhiCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaSideBand_Data_dPhi_Pt_minPtAss05" );

	FillHistoArray(histoMCRecCorrEta_InvMass_Pt, fHistoMCRecCorrelationEtaInvMass, 1, 12, fPtBinnningEta, "Eta_MCRec_InvMass_Pt" );
	FillHistoArray(histoMCRec2DEta_dEta_PtTrig, fHistoMCRecCorrelationEtadEtaCh, 1, 12, fPtBinnningEta, "Eta_MCRec_dEta_Pt" );
	FillHistoArray(histoMCRec2DEta_dEta_PtTrig_minPtAss1, fHistoMCRecCorrelationEtadEtaCh_minPtAss1, 1, 12, fPtBinnningEta, "Eta_MCRec_dEta_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DEta_dEta_PtTrig_minPtAss05, fHistoMCRecCorrelationEtadEtaCh_minPtAss05, 1, 12, fPtBinnningEta, "Eta_MCRec_dEta_Pt_minPtAss05" );
	FillHistoArray(histoMCRec2DEta_dPhi_PtTrig, fHistoMCRecCorrelationEtadPhiCh, 1, 12, fPtBinnningEta, "Eta_MCRec_dPhi_Pt" );
	FillHistoArray(histoMCRec2DEta_dPhi_PtTrig_minPtAss1, fHistoMCRecCorrelationEtadPhiCh_minPtAss1, 1, 12, fPtBinnningEta, "Eta_MCRec_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DEta_dPhi_PtTrig_minPtAss05, fHistoMCRecCorrelationEtadPhiCh_minPtAss05, 1, 12, fPtBinnningEta, "Eta_MCRec_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoMCRecCorrEta_IsoMin_Pt, fHistoMCRecCorrelationEtaIsoMin, 1, 12, fPtBinnningEta, "Eta_MCRec_IsoMin_Pt" );
	FillHistoArray(histoMCRec2DEtaIso_dEta_PtTrig, fHistoMCRecCorrelationEtaIsodEtaCh, 1, 12, fPtBinnningEta, "EtaIso_MCRec_dEta_Pt" );
	FillHistoArray(histoMCRec2DEtaIso_dEta_PtTrig_minPtAss05, fHistoMCRecCorrelationEtaIsodEtaCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaIso_MCRec_dEta_Pt_minPtAss05");
	FillHistoArray(histoMCRec2DEtaIso_dEta_PtTrig_minPtAss1, fHistoMCRecCorrelationEtaIsodEtaCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaIso_MCRec_dEta_Pt_minPtAss1");
	FillHistoArray(histoMCRec2DEtaIso_dPhi_PtTrig, fHistoMCRecCorrelationEtaIsodPhiCh, 1, 12, fPtBinnningEta, "EtaIso_MCRec_dPhi_Pt" );
	FillHistoArray(histoMCRec2DEtaIso_dPhi_PtTrig_minPtAss05, fHistoMCRecCorrelationEtaIsodPhiCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaIso_MCRec_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoMCRec2DEtaIso_dPhi_PtTrig_minPtAss1, fHistoMCRecCorrelationEtaIsodPhiCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaIso_MCRec_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DEtaSideBand_dEta_PtTrig, fHistoMCRecCorrelationEtaSideBanddEtaCh, 1, 12, fPtBinnningEta, "EtaSideBand_MCRec_dEta_Pt" );
	FillHistoArray(histoMCRec2DEtaSideBand_dEta_PtTrig_minPtAss1, fHistoMCRecCorrelationEtaSideBanddEtaCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaSideBand_MCRec_dEta_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DEtaSideBand_dEta_PtTrig_minPtAss05, fHistoMCRecCorrelationEtaSideBanddEtaCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaSideBand_MCRec_dEta_Pt_minPtAss05" );
	FillHistoArray(histoMCRec2DEtaSideBand_dPhi_PtTrig, fHistoMCRecCorrelationEtaSideBanddPhiCh, 1, 12, fPtBinnningEta, "EtaSideBand_MCRec_dPhi_Pt" );
	FillHistoArray(histoMCRec2DEtaSideBand_dPhi_PtTrig_minPtAss1, fHistoMCRecCorrelationEtaSideBanddPhiCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaSideBand_MCRec_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCRec2DEtaSideBand_dPhi_PtTrig_minPtAss05, fHistoMCRecCorrelationEtaSideBanddPhiCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaSideBand_MCRec_dPhi_Pt_minPtAss05" );

	FillHistoArray(histoMCTrueCorrEta_InvMass_Pt, fHistoMCTrueCorrelationEtaInvMass, 1, 12, fPtBinnningEta, "Eta_MCTrue_InvMass_Pt" );
	FillHistoArray(histoMCTrue2DEta_dEta_PtTrig, fHistoMCTrueCorrelationEtadEtaCh, 1, 12, fPtBinnningEta, "Eta_MCTrue_dEta_Pt" );
	FillHistoArray(histoMCTrue2DEta_dEta_PtTrig_minPtAss1, fHistoMCTrueCorrelationEtadEtaCh_minPtAss1, 1, 12, fPtBinnningEta, "Eta_MCTrue_dEta_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DEta_dEta_PtTrig_minPtAss05, fHistoMCTrueCorrelationEtadEtaCh_minPtAss05, 1, 12, fPtBinnningEta, "Eta_MCTrue_dEta_Pt_minPtAss05" );
	FillHistoArray(histoMCTrue2DEta_dPhi_PtTrig, fHistoMCTrueCorrelationEtadPhiCh, 1, 12, fPtBinnningEta, "Eta_MCTrue_dPhi_Pt" );
	FillHistoArray(histoMCTrue2DEta_dPhi_PtTrig_minPtAss1, fHistoMCTrueCorrelationEtadPhiCh_minPtAss1, 1, 12, fPtBinnningEta, "Eta_MCTrue_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DEta_dPhi_PtTrig_minPtAss05, fHistoMCTrueCorrelationEtadPhiCh_minPtAss05, 1, 12, fPtBinnningEta, "Eta_MCTrue_dPhi_Pt_minPtAss05" );	
	FillHistoArray(histoMCTrueCorrEta_IsoMin_Pt, fHistoMCTrueCorrelationEtaIsoMin, 1, 12, fPtBinnningEta, "Eta_MCTrue_IsoMin_Pt" );
	FillHistoArray(histoMCTrue2DEtaIso_dEta_PtTrig, fHistoMCTrueCorrelationEtaIsodEtaCh, 1, 12, fPtBinnningEta, "EtaIso_MCTrue_dEta_Pt" );
	FillHistoArray(histoMCTrue2DEtaIso_dEta_PtTrig_minPtAss05, fHistoMCTrueCorrelationEtaIsodEtaCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaIso_MCTrue_dEta_Pt_minPtAss05");
	FillHistoArray(histoMCTrue2DEtaIso_dEta_PtTrig_minPtAss1, fHistoMCTrueCorrelationEtaIsodEtaCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaIso_MCTrue_dEta_Pt_minPtAss1");
	FillHistoArray(histoMCTrue2DEtaIso_dPhi_PtTrig, fHistoMCTrueCorrelationEtaIsodPhiCh, 1, 12, fPtBinnningEta, "EtaIso_MCTrue_dPhi_Pt" );
	FillHistoArray(histoMCTrue2DEtaIso_dPhi_PtTrig_minPtAss05, fHistoMCTrueCorrelationEtaIsodPhiCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaIso_MCTrue_dPhi_Pt_minPtAss05" );
	FillHistoArray(histoMCTrue2DEtaIso_dPhi_PtTrig_minPtAss1, fHistoMCTrueCorrelationEtaIsodPhiCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaIso_MCTrue_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DEtaSideBand_dEta_PtTrig, fHistoMCTrueCorrelationEtaSideBanddEtaCh, 1, 12, fPtBinnningEta, "EtaSideBand_MCTrue_dEta_Pt" );
	FillHistoArray(histoMCTrue2DEtaSideBand_dEta_PtTrig_minPtAss1, fHistoMCTrueCorrelationEtaSideBanddEtaCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaSideBand_MCTrue_dEta_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DEtaSideBand_dEta_PtTrig_minPtAss05, fHistoMCTrueCorrelationEtaSideBanddEtaCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaSideBand_MCTrue_dEta_Pt_minPtAss05" );
	FillHistoArray(histoMCTrue2DEtaSideBand_dPhi_PtTrig, fHistoMCTrueCorrelationEtaSideBanddPhiCh, 1, 12, fPtBinnningEta, "EtaSideBand_MCTrue_dPhi_Pt" );
	FillHistoArray(histoMCTrue2DEtaSideBand_dPhi_PtTrig_minPtAss1, fHistoMCTrueCorrelationEtaSideBanddPhiCh_minPtAss1, 1, 12, fPtBinnningEta, "EtaSideBand_MCTrue_dPhi_Pt_minPtAss1" );
	FillHistoArray(histoMCTrue2DEtaSideBand_dPhi_PtTrig_minPtAss05, fHistoMCTrueCorrelationEtaSideBanddPhiCh_minPtAss05, 1, 12, fPtBinnningEta, "EtaSideBand_MCTrue_dPhi_Pt_minPtAss05" );

	for (Int_t i = 1; i < 12; i++){
		PlotCorrelationBinsPt(  fHistoDataCorrelationEtaInvMass[i],fHistoMCRecCorrelationEtaInvMass[i], fHistoMCTrueCorrelationEtaInvMass[i],
								   fHistoDataCorrelationEtaIsoMin[i], fHistoMCRecCorrelationEtaIsoMin[i],fHistoMCTrueCorrelationEtaIsoMin[i],
									fHistoDataCorrelationEtadPhiCh[i], fHistoMCRecCorrelationEtadPhiCh[i], fHistoMCTrueCorrelationEtadPhiCh[i],
									fHistoDataCorrelationEtadEtaCh[i], fHistoMCRecCorrelationEtadEtaCh[i], fHistoMCTrueCorrelationEtadEtaCh[i],
									fHistoDataCorrelationEtaIsodPhiCh[i], fHistoMCRecCorrelationEtaIsodPhiCh[i], fHistoMCTrueCorrelationEtaIsodPhiCh[i],
									fHistoDataCorrelationEtaIsodEtaCh[i], fHistoMCRecCorrelationEtaIsodEtaCh[i], fHistoMCTrueCorrelationEtaIsodEtaCh[i],
									fHistoDataCorrelationEtaSideBanddPhiCh[i], fHistoMCRecCorrelationEtaSideBanddPhiCh[i], fHistoMCTrueCorrelationEtaSideBanddPhiCh[i],
									fHistoDataCorrelationEtaSideBanddEtaCh[i], fHistoMCRecCorrelationEtaSideBanddEtaCh[i], fHistoMCTrueCorrelationEtaSideBanddEtaCh[i],
									Form("%s/CompilationCorrelation_PtBin_%i.%s",outputDirectory.Data(),i,suffix.Data()),fPtBinnningEta[i],fPtBinnningEta[i+1],fPtRebinEta[i],i);
	}
	for (Int_t i = 1; i < 12; i++){
		PlotCorrelationBinsPt(  fHistoDataCorrelationEtaInvMass[i],fHistoMCRecCorrelationEtaInvMass[i], fHistoMCTrueCorrelationEtaInvMass[i],
								   fHistoDataCorrelationEtaIsoMin[i], fHistoMCRecCorrelationEtaIsoMin[i],fHistoMCTrueCorrelationEtaIsoMin[i],
									fHistoDataCorrelationEtadPhiCh_minPtAss05[i], fHistoMCRecCorrelationEtadPhiCh_minPtAss05[i], fHistoMCTrueCorrelationEtadPhiCh_minPtAss05[i],
									fHistoDataCorrelationEtadEtaCh_minPtAss05[i], fHistoMCRecCorrelationEtadEtaCh_minPtAss05[i], fHistoMCTrueCorrelationEtadEtaCh_minPtAss05[i],
									fHistoDataCorrelationEtaIsodPhiCh_minPtAss05[i], fHistoMCRecCorrelationEtaIsodPhiCh_minPtAss05[i], fHistoMCTrueCorrelationEtaIsodPhiCh_minPtAss05[i],
									fHistoDataCorrelationEtaIsodEtaCh_minPtAss05[i], fHistoMCRecCorrelationEtaIsodEtaCh_minPtAss05[i], fHistoMCTrueCorrelationEtaIsodEtaCh_minPtAss05[i],
									fHistoDataCorrelationEtaSideBanddPhiCh_minPtAss05[i], fHistoMCRecCorrelationEtaSideBanddPhiCh_minPtAss05[i], fHistoMCTrueCorrelationEtaSideBanddPhiCh_minPtAss05[i],
									fHistoDataCorrelationEtaSideBanddEtaCh_minPtAss05[i], fHistoMCRecCorrelationEtaSideBanddEtaCh_minPtAss05[i], fHistoMCTrueCorrelationEtaSideBanddEtaCh_minPtAss05[i],
									Form("%s/CompilationCorrelation_minPtAss05_PtBin_%i.%s",outputDirectory.Data(),i,suffix.Data()),fPtBinnningEta[i],fPtBinnningEta[i+1],1,i);
	}
	for (Int_t i = 1; i < 12; i++){
		PlotCorrelationBinsPt(  fHistoDataCorrelationEtaInvMass[i],fHistoMCRecCorrelationEtaInvMass[i], fHistoMCTrueCorrelationEtaInvMass[i],
								   fHistoDataCorrelationEtaIsoMin[i], fHistoMCRecCorrelationEtaIsoMin[i],fHistoMCTrueCorrelationEtaIsoMin[i],
									fHistoDataCorrelationEtadPhiCh_minPtAss1[i], fHistoMCRecCorrelationEtadPhiCh_minPtAss1[i], fHistoMCTrueCorrelationEtadPhiCh_minPtAss1[i],
									fHistoDataCorrelationEtadEtaCh_minPtAss1[i], fHistoMCRecCorrelationEtadEtaCh_minPtAss1[i], fHistoMCTrueCorrelationEtadEtaCh_minPtAss1[i],
									fHistoDataCorrelationEtaIsodPhiCh_minPtAss1[i], fHistoMCRecCorrelationEtaIsodPhiCh_minPtAss1[i], fHistoMCTrueCorrelationEtaIsodPhiCh_minPtAss1[i],
									fHistoDataCorrelationEtaIsodEtaCh_minPtAss1[i], fHistoMCRecCorrelationEtaIsodEtaCh_minPtAss1[i], fHistoMCTrueCorrelationEtaIsodEtaCh_minPtAss1[i],
									fHistoDataCorrelationEtaSideBanddPhiCh_minPtAss1[i], fHistoMCRecCorrelationEtaSideBanddPhiCh_minPtAss1[i], fHistoMCTrueCorrelationEtaSideBanddPhiCh_minPtAss1[i],
									fHistoDataCorrelationEtaSideBanddEtaCh_minPtAss1[i], fHistoMCRecCorrelationEtaSideBanddEtaCh_minPtAss1[i], fHistoMCTrueCorrelationEtaSideBanddEtaCh_minPtAss1[i],
									Form("%s/CompilationCorrelation_minPtAss1_PtBin_%i.%s",outputDirectory.Data(),i,suffix.Data()),fPtBinnningEta[i],fPtBinnningEta[i+1],1,i);
	}
	
}