/****************************************************************************************************************************
 ******     provided by Gamma Conversion Group, PWG4,                                                                   *****
 ******     Kathrin Koch, kkoch@physi.uni-heidelberg.de                                                                 *****
 ******     Friederike Bock, friederike.bock@cern.ch                                                                    *****
 *****************************************************************************************************************************
 *** This macro can be used to display the Photon Characteristics of the conversion method in ALICE, it can be operated  *****
 *** on the output of the GammaConversionTask. It can take 2 input files, the second one should be MC, if this is not    *****
 *** the case all histograms including MC need to be commented out otherwise the running will crash.                     *****
 ****************************************************************************************************************************/

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
#include "TH3F.h"
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
#include "../CommonHeaders/PlottingGammaConversionHistos.h"
#include "../CommonHeaders/PlottingGammaConversionAdditional.h"
#include "../CommonHeaders/FittingGammaConversion.h"
#include "../CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "../CommonHeaders/ConversionFunctions.h"

TString collisionSystem;
TString textDate;
               
void  BasicQA(TString data = "myOutput", TString optMC = "", TString cutSel = "", TString suffix = "gif", TString optEnergy="", TString optMCGenerator="", TString optPeriod="", Int_t mode = 9){  
   cout << data.Data() << "\t" << optMC.Data() << "\t" << cutSel.Data() << endl;
   gROOT->Reset();   
   gSystem->Load("libCore.so");
   gSystem->Load("libTree.so");
   gSystem->Load("libGeom.so");
   gSystem->Load("libVMC.so");
   gSystem->Load("libPhysics.so");
   gSystem->Load("libSTEERBase");
   gSystem->Load("libESD");
   gSystem->Load("libAOD");
   gSystem->Load("libANALYSIS");
   gSystem->Load("libANALYSISalice");
   gSystem->Load("libCORRFW.so");
   gROOT->SetStyle("Plain");
   
   StyleSettingsThesis();  
   //StyleSettings();
   
   SetPlotStyle();
   
   collisionSystem = ReturnFullCollisionsSystem(optEnergy.Data());
   
   TString outputDirectory;
   TString outputDirectory1;
   if(optPeriod.CompareTo("") ==0 || optPeriod.CompareTo("All") ==0){
      if (optMCGenerator.CompareTo("")!=0){
         outputDirectory =       Form("%s/%s/%s/%s/QA",optMCGenerator.Data(),cutSel.Data(),optEnergy.Data(),suffix.Data());
         outputDirectory1 = Form("%s/%s",optMCGenerator.Data(),cutSel.Data());
      } else {
         outputDirectory =       Form("%s/%s/%s/QA",cutSel.Data(),optEnergy.Data(),suffix.Data());
         outputDirectory1 = Form("%s",cutSel.Data());
      }
      gSystem->Exec("mkdir -p "+outputDirectory);
   } else if (optMCGenerator.CompareTo("")!=0){
      outputDirectory =       Form("%s/%s/%s/%s/%s/PhotonQA",optMCGenerator.Data(),cutSel.Data(),optEnergy.Data(),suffix.Data(),optPeriod.Data());
      outputDirectory1 = Form("%s/%s",optMCGenerator.Data(),cutSel.Data());
      gSystem->Exec("mkdir -p "+outputDirectory);
   } else {
      outputDirectory =       Form("%s/%s/%s/%s/PhotonQA",cutSel.Data(),optEnergy.Data(),suffix.Data(),optPeriod.Data());
      outputDirectory1 = Form("%s/%s",optMCGenerator.Data(),cutSel.Data());
      gSystem->Exec("mkdir -p "+outputDirectory);
   }
   gSystem->Exec("echo "+outputDirectory);

   Float_t floatLocationRightUp2D[4] = {0.6,0.95,0.035, 0.02};
   if( optEnergy.CompareTo("HI") == 0) {
      floatLocationRightUp2D[0]=    0.53;
   }
   
   textDate = ReturnDateString();

   	TString fEventCutSelection="";
	TString fGammaCutSelection="";
	TString fClusterCutSelection="";
	TString fElectronCutSelection="";
	TString fMesonCutSelection="";
	
	TString fCutSelectionData = cutSel;
	if (mode == 9){
		ReturnSeparatedCutNumber(fCutSelectionData, fGammaCutSelection, fElectronCutSelection,fMesonCutSelection);
		fEventCutSelection = fGammaCutSelection(0,7);
		fGammaCutSelection = fGammaCutSelection(7,fGammaCutSelection.Length()-7);
		cout << fEventCutSelection.Data() << "\t" << fGammaCutSelection.Data() << endl;
	} else {
		ReturnSeparatedCutNumberAdvanced(fCutSelectionData,fEventCutSelection, fGammaCutSelection, fClusterCutSelection, fElectronCutSelection, fMesonCutSelection, mode);
	}
  
	
	
	TString nameMainDirectory = "GammaConvV1_56";
	TString nameGammaDirectoryData = Form("Cut Number %s",  fCutSelectionData.Data());
	TString nameESDDirectoryData = Form("%s ESD histograms",  fCutSelectionData.Data());
	TString nameGammaDirectoryMonteCarlo = Form("Cut Number %s",  cutSel.Data());
	TString nameESDDirectoryMonteCarlo = Form("%s ESD histograms",  cutSel.Data());
	
	//    cout << nameGammaDirectoryData.Data() << endl;

	//    Float_t floatLineWidth = 1;
	
	// ---------------------------- LOAD ALL FILES ---------------------------------------------------
	TFile    fileData(data.Data());  
	TList *TopDirData =(TList*)fileData.Get(nameMainDirectory.Data());
	if(TopDirData == NULL){
		cout<<"ERROR: TopDirData not Found"<<endl;
		return;
	}
	//for new versions
	TList *directoryMainData = (TList*)TopDirData->FindObject(nameGammaDirectoryData.Data());
	if(directoryMainData == NULL){
		cout<<"ERROR: Cut Number Directory not Found"<<endl;
		return;
	}
	TList *directoryESDData = (TList*)directoryMainData->FindObject(nameESDDirectoryData.Data());
	if(directoryESDData == NULL){
		cout<<"ERROR: ESD Directory not Found"<<endl;
		return;
	}
	TH1F*    histNEventsData =      (TH1F*)directoryESDData->FindObject("NEvents");  
	Double_t fNEventsData =0;
	if (optEnergy.CompareTo("PbPb_2.76TeV") == 0 || optEnergy.CompareTo("pPb_5.023TeV") == 0){
		fNEventsData = histNEventsData->GetBinContent(1);
	} else {
		fNEventsData =  GetNEvents(histNEventsData);
	}
	TH1I*    histESDTracksData =      (TH1I*)directoryESDData->FindObject("GoodESDTracks");  
	TH1D* hNGoodESDTracksData = new TH1D("GoodESDTracksCorrectlyScale","GoodESDTracksCorrectlyScale",200,0,200);
	for (Int_t i = 1; i < hNGoodESDTracksData->GetNbinsX(); i++){
		hNGoodESDTracksData->SetBinContent(i, histESDTracksData->GetBinContent(i)/fNEventsData);
		hNGoodESDTracksData->SetBinError(i, histESDTracksData->GetBinError(i)/fNEventsData);
	}   
	TH1I*    histESDV0Data =      (TH1I*)directoryESDData->FindObject("V0 Multiplicity");  
	TH1D* hNV0TracksData = new TH1D("V0 Multiplicity","V0 Multiplicity",2000,0,2000);
	for (Int_t i = 1; i < hNV0TracksData->GetNbinsX(); i++){
		hNV0TracksData->SetBinContent(i, histESDV0Data->GetBinContent(i)/fNEventsData);
		hNV0TracksData->SetBinError(i, histESDV0Data->GetBinError(i)/fNEventsData);
	}   
	TH1F* histEtaData = (TH1F*)directoryESDData->FindObject("ESD_ConvGamma_Eta");  
	if (histEtaData){
		histEtaData->Sumw2();
		histEtaData->Scale(1./fNEventsData);
		
	}
	
	// ---------------------------- LOAD ALL FILES ---------------------------------------------------
	TFile    fileMonteCarlo(optMC.Data());  
	TList *TopDirMonteCarlo =(TList*)fileMonteCarlo.Get(nameMainDirectory.Data());
	if(TopDirMonteCarlo == NULL){
		cout<<"ERROR: TopDirMonteCarlo not Found"<<endl;
		return;
	}
	TList *directoryMainMonteCarlo = (TList*)TopDirMonteCarlo->FindObject(nameGammaDirectoryMonteCarlo.Data());
	if(directoryMainMonteCarlo == NULL){
		cout<<"ERROR: Cut Number Directory not Found"<<endl;
		return;
	}
	TList *directoryESDMonteCarlo = (TList*)directoryMainMonteCarlo->FindObject(nameESDDirectoryMonteCarlo.Data());
	if(directoryESDMonteCarlo == NULL){
		cout<<"ERROR: ESD Directory not Found"<<endl;
		return;
	}
	
	TH1F*    histNEventsMonteCarlo =      (TH1F*)directoryESDMonteCarlo->FindObject("NEvents");  
	Float_t fNEventsMonteCarlo =0;
	if (optEnergy.CompareTo("PbPb_2.76TeV") == 0 || optEnergy.CompareTo("pPb_5.023TeV") == 0){
		fNEventsMonteCarlo = histNEventsMonteCarlo->GetBinContent(1);
	} else {
		fNEventsMonteCarlo =  GetNEvents(histNEventsMonteCarlo);
	}
	TH1D*    histESDTracksMonteCarlo =      (TH1D*)directoryESDMonteCarlo->FindObject("GoodESDTracks");  
	cout << fNEventsMonteCarlo << endl;

	TH1D* hNGoodESDTracksMonteCarlo = new TH1D("GoodESDTracksCorrectlyScaleMC","GoodESDTracksCorrectlyScaleMC",200,0,200);
	for (Int_t i = 1; i < hNGoodESDTracksMonteCarlo->GetNbinsX(); i++){
		hNGoodESDTracksMonteCarlo->SetBinContent(i, histESDTracksMonteCarlo->GetBinContent(i)/fNEventsMonteCarlo);
		hNGoodESDTracksMonteCarlo->SetBinError(i, histESDTracksMonteCarlo->GetBinError(i)/fNEventsMonteCarlo);
	}   
	TH1I*    histESDV0MonteCarlo =      (TH1I*)directoryESDMonteCarlo->FindObject("V0 Multiplicity");  
	TH1D* hNV0TracksMonteCarlo = new TH1D("V0 Multiplicity","V0 Multiplicity",2000,0,2000);
	for (Int_t i = 1; i < hNV0TracksMonteCarlo->GetNbinsX(); i++){
		hNV0TracksMonteCarlo->SetBinContent(i, histESDV0MonteCarlo->GetBinContent(i)/fNEventsMonteCarlo);
		hNV0TracksMonteCarlo->SetBinError(i, histESDV0MonteCarlo->GetBinError(i)/fNEventsMonteCarlo);
	}   
	TH1F* histEtaMonteCarlo = (TH1F*)directoryESDMonteCarlo->FindObject("ESD_ConvGamma_Eta");  
	if (histEtaMonteCarlo){
		histEtaMonteCarlo->Sumw2();
		histEtaMonteCarlo->Scale(1./fNEventsMonteCarlo);
	}
	
	TCanvas * canvasMult = new TCanvas("canvasMult","",10,10,500,500);  // gives the page size
	canvasMult->SetLeftMargin(0.16);
	canvasMult->cd();
	canvasMult->SetLogy();
	//    histESDTracksMonteCarlo->Draw();
	//    cout << histESDTracksData->GetMaximum() << endl;
	DrawAutoGammaHistos( hNGoodESDTracksData,
					hNGoodESDTracksMonteCarlo, 
					"", "# Good TPC Tracks","Counts/Event",
					kFALSE, 1.2,1e-8,
					kFALSE,1e-10 ,1e-6, 
					kTRUE, 0.,190.);  
	//    DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, optPeriod);
	canvasMult->Update();
	canvasMult->SaveAs(Form("%s/NChargedTracks.%s",outputDirectory.Data(),suffix.Data()));
	cout << "TPC Mult \t Data: "<<hNGoodESDTracksData->GetMean() << "+-" << hNGoodESDTracksData->GetRMS()<< " \t MC: " << hNGoodESDTracksMonteCarlo->GetMean() << "+-" << hNGoodESDTracksMonteCarlo->GetRMS()<< endl;
	//    delete canvasMult;    

	DrawAutoGammaHistos( hNV0TracksData,
					hNV0TracksMonteCarlo, 
					"", "V0 Multiplicity","Counts/Event",
					kFALSE, 1.2,1e-8,
					kFALSE,1e-10 ,1e-6, 
					kTRUE, 0.,900.);  
	//    DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, optPeriod);
	canvasMult->Update();
	canvasMult->SaveAs(Form("%s/VZEROMultiplicity.%s",outputDirectory.Data(),suffix.Data()));
	cout << "V0 Mult \t Data: "<<hNV0TracksData->GetMean() << "+-" << hNV0TracksData->GetRMS() <<  " \t MC: " << hNV0TracksMonteCarlo->GetMean() << "+-" << hNV0TracksMonteCarlo->GetRMS()<< endl;
	
	if (histEtaData && histEtaMonteCarlo){
		DrawAutoGammaHistos( histEtaData,
						histEtaMonteCarlo, 
						"", "#eta","Counts/Event",
						kFALSE, 1.2,1e-8,
						kFALSE,1e-10 ,1e-6, 
						kTRUE, -1.2,1.2);  
	//    DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, optPeriod);
		canvasMult->Update();
		canvasMult->SaveAs(Form("%s/EtaDistribution.%s",outputDirectory.Data(),suffix.Data()));
	}
}

