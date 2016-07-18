/*******************************************************************************
 ****** 	provided by Gamma Conversion Group, PWGGA,								*****
 ******		Ana Marin, marin@physi.uni-heidelberg.de								*****
 ******	  	Martin Wilde, m_wild03@uni-muenster.de 								*****
 ******		Friederike Bock, friederike.bock@cern.ch								*****
 *******************************************************************************/

#include <Riostream.h>
#include <fstream>
#include "TMath.h"
#include <stdlib.h>
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
#include "TF1.h"
#include "TVirtualFitter.h"
#include "TObject.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TDatabasePDG.h"
#include "TMinuit.h"
#include "TLatex.h"
#include "TASImage.h"
#include "TPostScript.h"
#include "TGraphErrors.h"
#include "TArrow.h"
#include "TMarker.h"
#include "TGraphAsymmErrors.h" 
#include "CommonHeaders/PlottingGammaConversionHistos.h"
#include "CommonHeaders/PlottingGammaConversionAdditional.h"
#include "CommonHeaders/FittingGammaConversion.h"
#include "CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "CommonHeaders/ConversionFunctions.h"

void PrepareEventStats(TString fileNameEvents = "outputFileLHC10h_3010001042092970023220000_01322045000.txt", TString centrality ="0005", TString period = "LHC10h", TString suffix = "eps"){
	gROOT->Reset();	
	gROOT->SetStyle("Plain");
	
	StyleSettingsThesis();	
	SetPlotStyle();
	
	TString date = ReturnDateString();

	cout << fileNameEvents.Data() << endl;
	
	TString outputDir = "EventStats";
	gSystem->Exec("mkdir "+outputDir);
		
	
	ifstream fileEventStat;
 	fileEventStat.open(fileNameEvents.Data(),ios_base::in);
	Float_t runnumber[1000];
	Float_t nEventsBin1[1000];
	Float_t nEventsBin1Err[1000];
	Float_t nEventsBin2Err[1000];
	Float_t nEventsBin3Err[1000];
	Float_t nEventsBin4Err[1000];
	Float_t nEventsBin5Err[1000];
	Float_t nEventsBin6Err[1000];
	Float_t nEventsBin7Err[1000];
	Float_t nEventsBin2[1000];
	Float_t nEventsBin3[1000];
	Float_t nEventsBin4[1000];
	Float_t nEventsBin5[1000];
	Float_t nEventsBin6[1000];
	Float_t nEventsBin7[1000];
	Float_t nGamma[1000];
	Float_t nGammaErr[1000];
	Float_t meanMultTPC[1000];
	Float_t rmsMultTPC[1000];
	Float_t meanMultV0[1000];
	Float_t rmsMultV0[1000];
	Float_t integralPi0[1000];
	Float_t integralPi0Err[1000];  
	Float_t integralPi0BG[1000] ;  
	Float_t massPi0[1000] ;  
	Float_t massPi0Err[1000] ;  
	Float_t widthPi0[1000] ;  
	Float_t widthPi0Err[1000] ;  
	Float_t massEta[1000] ;  
	Float_t massEtaErr[1000] ;  
	Float_t widthEta[1000] ;  
	Float_t widthEtaErr[1000] ;  
	Float_t integralEta[1000] ;  
	Float_t integralEtaErr[1000] ;  
	Float_t integralEtaBG[1000];
	Float_t ratioGamma[1000];
	Float_t ratioPi0[1000];
	Float_t ratioPi0Err[1000];
	Float_t ratioEta[1000];
	Float_t ratioEtaErr[1000];
	Float_t ratioGammaErr[1000];
	Float_t ratioWOVtxEvt[1000];
	Float_t ratioWOVtxEvtErr[1000];
	Float_t ratioPileUpEvt[1000];
	Float_t ratioPileUpEvtErr[1000];
	Float_t ratioGoodEventsEvt[1000];
	Float_t ratioGoodEventsEvtErr[1000];
	Float_t ratioNormAllEvt[1000];
	Float_t ratioNormAllEvtErr[1000];
	Float_t ratioNormMinBiasEvt[1000];
	Float_t ratioNormMinBiasEvtErr[1000];
	
	Float_t ratioWVtxOutside10cmEvt[1000];
	Float_t ratioWVtxOutside10cmEvtErr[1000]; 
	
	Int_t nRuns = 0;
	Float_t nEBin1 = 0;
	Float_t nEBin2 = 0;
	Float_t nEBin3 = 0;
	Float_t nEBin4 = 0;
	Float_t nEBin5 = 0;
	Float_t nEBin6 = 0;
	Float_t nEBin7 = 0;
	Float_t nGammaTot = 0;
	while(!fileEventStat.eof()){
		fileEventStat >> runnumber[nRuns] >> nEventsBin1[nRuns]>>	nEventsBin2[nRuns] >> nEventsBin3[nRuns] >> nEventsBin4[nRuns] >> nEventsBin5[nRuns] >>nEventsBin6[nRuns] >> nEventsBin7[nRuns]  >> nGamma[nRuns] >> meanMultTPC[nRuns] >> rmsMultTPC[nRuns] >> meanMultV0[nRuns] >> rmsMultV0[nRuns] >> integralPi0[nRuns] >> integralPi0Err[nRuns] >> integralPi0BG[nRuns] >> massPi0[nRuns] >> massPi0Err[nRuns] >> widthPi0[nRuns] >> widthPi0Err[nRuns] >> massEta[nRuns] >> massEtaErr[nRuns] >> widthEta[nRuns] >> widthEtaErr[nRuns] >> integralEta[nRuns] >> integralEtaErr[nRuns] >> integralEtaBG[nRuns];
		nEventsBin1Err[nRuns] = TMath::Sqrt(nEventsBin1[nRuns]);
      nEventsBin2Err[nRuns] = TMath::Sqrt(nEventsBin2[nRuns]);
      nEventsBin3Err[nRuns] = TMath::Sqrt(nEventsBin3[nRuns]);
      nEventsBin4Err[nRuns] = TMath::Sqrt(nEventsBin4[nRuns]);
      nEventsBin5Err[nRuns] = TMath::Sqrt(nEventsBin5[nRuns]);
      nEventsBin6Err[nRuns] = TMath::Sqrt(nEventsBin6[nRuns]);
      nEventsBin7Err[nRuns] = TMath::Sqrt(nEventsBin7[nRuns]);
		nGammaErr[nRuns] = TMath::Sqrt(nGamma[nRuns]);
		rmsMultTPC[nRuns] = 0;
		rmsMultV0[nRuns] = 0;
		nEBin1 = nEBin1+nEventsBin1[nRuns];
		nEBin2 = nEBin2+nEventsBin2[nRuns];
		nEBin3 = nEBin3+nEventsBin3[nRuns];
		nEBin4 = nEBin4+nEventsBin4[nRuns];
		nEBin5 = nEBin5+nEventsBin5[nRuns];
		nEBin6 = nEBin6+nEventsBin6[nRuns];
		nEBin7 = nEBin7+nEventsBin7[nRuns];
		nGammaTot = nGammaTot+nGamma[nRuns];
		
		if (nEventsBin1[nRuns] > 0){
			ratioGamma[nRuns] = (Float_t)nGamma[nRuns]/nEventsBin1[nRuns];
			ratioGammaErr[nRuns] = TMath::Sqrt( pow(nGammaErr[nRuns]/nEventsBin1[nRuns],2)  + pow( nEventsBin1Err[nRuns]*nGamma[nRuns]/pow(nEventsBin1[nRuns],2),2) );
			Float_t nEventsAllEvt = nEventsBin1[nRuns] + nEventsBin2[nRuns] +nEventsBin3[nRuns]+nEventsBin4[nRuns] +nEventsBin5[nRuns] + nEventsBin6[nRuns] + nEventsBin7[nRuns];
			Float_t nEventsAllEvtErr = TMath::Sqrt(nEventsAllEvt);
			Float_t nEventsMinBiasEvt = nEventsBin1[nRuns] + nEventsBin2[nRuns] + nEventsBin5[nRuns] + nEventsBin6[nRuns] + nEventsBin7[nRuns];
			Float_t nEventsMinBiasEvtErr = TMath::Sqrt(nEventsMinBiasEvt);
			Float_t nEventsNormEvt = nEventsBin1[nRuns] +(nEventsBin1[nRuns]/(nEventsBin1[nRuns]+nEventsBin5[nRuns]))*nEventsBin6[nRuns];
			Float_t nEventsNormEvtErr = TMath::Sqrt(nEventsNormEvt);
         if ( period.CompareTo("LHC10h") == 0 || period.CompareTo("LHC11a10a_bis") == 0 || period.CompareTo("LHC11a10a") == 0 || period.CompareTo("LHC11a10b_bis") == 0 || period.CompareTo("LHC11a10a_plus") == 0 ){
            ratioWOVtxEvt[nRuns] = nEventsBin6[nRuns]/nEventsBin1[nRuns];
            ratioWOVtxEvtErr[nRuns] = TMath::Sqrt( pow(TMath::Sqrt(nEventsBin6Err[nRuns])/nEventsBin1[nRuns],2)  + pow( nEventsBin1Err[nRuns]*nEventsBin6[nRuns]/pow(nEventsBin1[nRuns],2),2) );
            ratioWVtxOutside10cmEvt[nRuns] = nEventsBin5[nRuns]/nEventsBin1[nRuns];
            ratioWVtxOutside10cmEvtErr[nRuns] = TMath::Sqrt( pow(TMath::Sqrt(nEventsBin5[nRuns])/nEventsBin1[nRuns],2)  + pow( nEventsBin1Err[nRuns]*nEventsBin5[nRuns]/pow(nEventsBin1[nRuns],2),2) );
            ratioPileUpEvt[nRuns] = nEventsBin7[nRuns]/nEventsBin1[nRuns];
            ratioPileUpEvtErr[nRuns] = TMath::Sqrt( pow(TMath::Sqrt(nEventsBin7[nRuns])/nEventsBin1[nRuns],2)  + pow( nEventsBin1Err[nRuns]*nEventsBin7[nRuns]/pow(nEventsBin1[nRuns],2),2) );
         } else {   
            ratioWOVtxEvt[nRuns] = nEventsBin6[nRuns]/nEventsMinBiasEvt;
            ratioWOVtxEvtErr[nRuns] = TMath::Sqrt( pow(TMath::Sqrt(nEventsBin6[nRuns])/nEventsMinBiasEvt,2)  + pow( nEventsMinBiasEvtErr*nEventsBin6[nRuns]/pow(nEventsMinBiasEvt,2),2) );
            ratioWVtxOutside10cmEvt[nRuns] = nEventsBin5[nRuns]/nEventsMinBiasEvt;
            ratioWVtxOutside10cmEvtErr[nRuns] = TMath::Sqrt( pow(TMath::Sqrt(nEventsBin5[nRuns])/nEventsMinBiasEvt,2)  + pow( nEventsMinBiasEvtErr*nEventsBin5[nRuns]/pow(nEventsMinBiasEvt,2),2) );
            ratioPileUpEvt[nRuns] = nEventsBin7[nRuns]/nEventsMinBiasEvt;
            ratioPileUpEvtErr[nRuns] = TMath::Sqrt( pow(TMath::Sqrt(nEventsBin7[nRuns])/nEventsMinBiasEvt,2)  + pow( nEventsMinBiasEvtErr*nEventsBin7[nRuns]/pow(nEventsMinBiasEvt,2),2) );
         }
			ratioGoodEventsEvt[nRuns] = nEventsBin1[nRuns]/nEventsMinBiasEvt;
			ratioGoodEventsEvtErr[nRuns] = TMath::Sqrt( pow(TMath::Sqrt(nEventsBin1[nRuns])/nEventsMinBiasEvt,2)  + pow( nEventsMinBiasEvtErr*nEventsBin1[nRuns]/pow(nEventsMinBiasEvt,2),2) );
			ratioNormAllEvt[nRuns] = nEventsNormEvt/nEventsAllEvt;
			ratioNormAllEvtErr[nRuns] = TMath::Sqrt( pow(TMath::Sqrt(nEventsNormEvt)/nEventsAllEvt,2)  + pow( nEventsAllEvtErr*nEventsNormEvt/pow(nEventsAllEvt,2),2) );
			ratioNormMinBiasEvt[nRuns] = nEventsNormEvt/nEventsMinBiasEvt;
			ratioNormMinBiasEvtErr[nRuns] = TMath::Sqrt( pow(TMath::Sqrt(nEventsNormEvt)/nEventsMinBiasEvt,2)  + pow( nEventsMinBiasEvtErr*nEventsNormEvt/pow(nEventsMinBiasEvt,2),2) );
			ratioPi0[nRuns] = (Float_t)	(integralPi0[nRuns]-integralPi0BG[nRuns])/nEventsBin1[nRuns];
			ratioPi0Err[nRuns] = TMath::Sqrt( pow(integralPi0Err[nRuns]/nEventsBin1[nRuns],2)  + pow( nEventsBin1Err[nRuns]*(integralPi0[nRuns]-integralPi0BG[nRuns])/pow(nEventsBin1[nRuns],2),2) );
			ratioEta[nRuns] = (Float_t)	(integralEta[nRuns]-integralEtaBG[nRuns])/nEventsBin1[nRuns];
			ratioEtaErr[nRuns] = TMath::Sqrt( pow(integralEtaErr[nRuns]/nEventsBin1[nRuns],2)  + pow( nEventsBin1Err[nRuns]*(integralEta[nRuns]-integralEtaBG[nRuns])/pow(nEventsBin1[nRuns],2),2) );
		} else {
			ratioGamma[nRuns] = 0;
			ratioGammaErr[nRuns] =0;
			ratioWOVtxEvt[nRuns] = 0;
			ratioWOVtxEvtErr[nRuns] = 0;
			ratioWVtxOutside10cmEvt[nRuns] = 0;
			ratioWVtxOutside10cmEvtErr[nRuns] = 0;
			ratioPileUpEvt[nRuns] = 0;
			ratioPileUpEvtErr[nRuns] = 0;
			ratioGoodEventsEvt[nRuns] = 0;
			ratioGoodEventsEvtErr[nRuns] = 0;
			ratioNormAllEvt[nRuns] = 0;
			ratioNormAllEvtErr[nRuns] = 0;
			ratioNormMinBiasEvt[nRuns] = 0;
			ratioNormMinBiasEvtErr[nRuns] = 0;
			ratioPi0[nRuns] = 0;
			ratioPi0Err[nRuns] = 0;
			ratioEta[nRuns] = 0;
			ratioEtaErr[nRuns] = 0;
			
		}
// 		cout << runnumber[nRuns] << ", \t";
		nRuns++;
	}
	cout << endl;
	fileEventStat.close();
	nRuns = nRuns-1;
	cout << "All: " << nEBin1<< "\t" <<	nEBin2 <<  "\t" <<nEBin3 << "\t" << nEBin4 << "\t" << nEBin5 << "\t" <<nEBin6 << "\t" << nEBin7  << "\t" << nGammaTot << endl;;
	
		// BinContent 1 - good events
		// BinContent 2 - centrality not selected
		// BinContent 3 - MC corrupt
		// BinContent 4 - no Trigger Bit
		// BinContent 5 - Zvertex-position, 
		// BinContent 6 - no Contributors to vtx
		// BinContent 7 - PileUp

	
	Float_t nEventsNorm = nEBin1 +(nEBin1/(nEBin1+nEBin5))*nEBin6;
	Float_t nEventsMinBias = nEBin1 + nEBin2 + nEBin5 + nEBin6 + nEBin7;
	Float_t ratioWOVtx = nEBin6/nEventsMinBias;
	Float_t ratioWVtxOutside10cm = nEBin5/nEventsMinBias;
	Float_t ratioPileUp = nEBin7/nEventsMinBias;
	Float_t ratioGoodEvents = nEBin1/nEventsMinBias;
	cout << "EventsNorm \t EventsMinBias \t ratioGoodEvents \t ratioWVtxOutside10cm \t ratioWOVtx  \t ratioPileUp" << endl;
	cout << nEventsNorm <<"\t" << nEventsMinBias << "\t" << ratioGoodEvents << "\t" <<  ratioWVtxOutside10cm <<"\t" << ratioWOVtx  << "\t" << ratioPileUp << endl;
		
	TGraphErrors* numberOfEventsInCent = new TGraphErrors(nRuns, runnumber, nEventsBin1, 0,nEventsBin1Err );
	TGraphErrors* fractionNumberOfEventsInCentToTotal = ScaleGraph(numberOfEventsInCent,1/nEBin1*100);
	
	TGraphErrors* numberOfGammasInCent = new TGraphErrors(nRuns, runnumber, nGamma, 0, nGammaErr);
	TGraphErrors* fractionOfPi0InCent = new TGraphErrors(nRuns, runnumber, ratioPi0, 0, ratioPi0Err);
	TGraphErrors* fractionOfEtaInCent = new TGraphErrors(nRuns, runnumber, ratioEta, 0, ratioEtaErr);
	TGraphErrors* fractionOfGammasInCent = new TGraphErrors(nRuns, runnumber, ratioGamma, 0, ratioGammaErr);
	TGraphErrors* fractionOfGoodEvents = new TGraphErrors(nRuns, runnumber, ratioGoodEventsEvt, 0, ratioGoodEventsEvtErr);
	TGraphErrors* fractionOfWVtxOutside10cm = new TGraphErrors(nRuns, runnumber, ratioWVtxOutside10cmEvt, 0, ratioWVtxOutside10cmEvtErr);
	TGraphErrors* fractionOfWOVtx = new TGraphErrors(nRuns, runnumber, ratioWOVtxEvt, 0, ratioWOVtxEvtErr);
	TGraphErrors* fractionOfPileUp = new TGraphErrors(nRuns, runnumber, ratioPileUpEvt, 0, ratioPileUpEvtErr);
	TGraphErrors* fractionOfNormAll = new TGraphErrors(nRuns, runnumber, ratioNormAllEvt, 0, ratioNormAllEvtErr);
	TGraphErrors* fractionOfNormMinBias = new TGraphErrors(nRuns, runnumber, ratioNormMinBiasEvt, 0, ratioNormMinBiasEvtErr);
	TGraphErrors* meanTrackMultTPCInCent = new TGraphErrors(nRuns, runnumber, meanMultTPC, 0, rmsMultTPC);
	TGraphErrors* meanMultV0InCent = new TGraphErrors(nRuns, runnumber, meanMultV0, 0, rmsMultV0);
	TGraphErrors* widthPi0perRun = new TGraphErrors(nRuns, runnumber, widthPi0, 0, widthPi0Err);
	TGraphErrors* massPi0perRun = new TGraphErrors(nRuns, runnumber, massPi0, 0, massPi0Err);
	TGraphErrors* widthEtaperRun = new TGraphErrors(nRuns, runnumber, widthEta, 0, widthEtaErr);
	TGraphErrors* massEtaperRun = new TGraphErrors(nRuns, runnumber, massEta, 0, massEtaErr);
	
	const char* Outputname = Form("%s/EventStats.root",outputDir.Data());
	TFile* EventStatsFile = new TFile(Outputname,"UPDATE");
		numberOfEventsInCent->Write(Form("NEvents_%s_%s", period.Data(), centrality.Data()),TObject::kOverwrite);
		fractionNumberOfEventsInCentToTotal->Write(Form("fracNEventsToTotal_%s_%s", period.Data(), centrality.Data()),TObject::kOverwrite);
		numberOfGammasInCent->Write(Form("NGammas_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		fractionOfGammasInCent->Write(Form("fracGammas_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		fractionOfGoodEvents->Write(Form("fracGoodEvents_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		fractionOfWVtxOutside10cm->Write(Form("fracWVtxOutside10cm_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		fractionOfWOVtx->Write(Form("fracWOVtx_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		fractionOfPileUp->Write(Form("fracPileUp_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		fractionOfNormAll->Write(Form("fracNormAll_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		fractionOfNormMinBias->Write(Form("fracNormMinBias_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		meanTrackMultTPCInCent->Write(Form("meanTrackMultTPCInCent_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		fractionOfPi0InCent->Write(Form("fractionOfPi0InCent_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		fractionOfEtaInCent->Write(Form("fractionOfEtaInCent_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		widthPi0perRun->Write(Form("widthPi0perRun_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		massPi0perRun->Write(Form("massPi0perRun_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		widthEtaperRun->Write(Form("widthEtaperRun_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
		massEtaperRun->Write(Form("massEtaperRun_%s_%s", period.Data(),centrality.Data()),TObject::kOverwrite);
	EventStatsFile->Write();
	EventStatsFile->Close();
	
}