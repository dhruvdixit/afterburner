#include <Riostream.h>
#include <iostream>
#include "TMath.h"
#include <stdio.h>
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
#include "../CommonHeaders/PlottingGammaConversionHistos.h"
#include "../CommonHeaders/PlottingGammaConversionAdditional.h"
#include "../CommonHeaders/FittingGammaConversion.h"
#include "../CommonHeaders/ConversionFunctions.h"


using namespace std;


void AnalysisQA(TString mode = "allrun", TString fileName = "PhotonQA_501000102209297002322000000_Data.root", TString cutNumber = "501000102209297002322000000", TString fileDirectory = "/home/admin1/leardini/photonconv/AnalysisSoftware/f010", TString outputDirectory = "/home/admin1/leardini/OutputAnalysisQA", TString suffix = "eps", TString runFile = "RunNumbers.txt")

//"/home/admin1/leardini/GridOutput/PbPb/Legotrain-v5-05-40-AN-20131125/GA_PbPb_AOD-18_20131125-1758"

{ 
   if(mode.EqualTo("allrun"))
      {

	TFile *File = new TFile(Form("%s/%s", fileDirectory.Data(), fileName.Data()));
	if (File->IsZombie()) return;

	TDirectoryFile *folderInFile = (TDirectoryFile*) File->Get(Form("GammaConv_0004_%s",cutNumber.Data()));

	TH3F *ElectrondEdxEtaP = (TH3F*) folderInFile->Get("histoElectrondEdxEtaP")->Clone("ElectrondEdxEtaP");        
	TH3F *ElectronNSigmadEdxEtaP = (TH3F*) folderInFile->Get("histoElectronNSigmadEdxEtaP")->Clone("ElectronNSigmadEdxEtaP");        
	TH3F *PositrondEdxEtaP = (TH3F*) folderInFile->Get("histoPositrondEdxEtaP")->Clone("PositrondEdxEtaP");        
	TH3F *PositronNSigmadEdxEtaP = (TH3F*) folderInFile->Get("histoPositronNSigmadEdxEtaP")->Clone("PositronNSigmadEdxEtaP");        
		
	//dE/dx versus Pt
	TH2D *ElectrondEdxPt = (TH2D*) ElectrondEdxEtaP->Project3D("dEdxPt_xz");
	TH2D *PositrondEdxPt = (TH2D*) PositrondEdxEtaP->Project3D("dEdxPt_xz");
	//dE/dx versus Eta
	TH2D *ElectrondEdxEta = (TH2D*) ElectrondEdxEtaP->Project3D("dEdxEta_xy");
	TH2D *PositrondEdxEta = (TH2D*) PositrondEdxEtaP->Project3D("dEdxEta_xy");
	
	//NSigma dE/dx versus Pt 
	TH2D *ElectronNSigmadEdxPt = (TH2D*) ElectronNSigmadEdxEtaP->Project3D("NSigmadEdxPt_xz");
	TH2D *PositronNSigmadEdxPt = (TH2D*) PositronNSigmadEdxEtaP->Project3D("NSigmadEdxPt_xz");
	//NSigma dE/dx versus Eta
	TH2D *ElectronNSigmadEdxEta = (TH2D*) ElectronNSigmadEdxEtaP->Project3D("NSigmadEdxEta_xy");
	TH2D *PositronNSigmadEdxEta = (TH2D*) PositronNSigmadEdxEtaP->Project3D("NSigmadEdxEta_xy");

	//dE/dx distribution
	TH1D *ElectrondEdx = (TH1D*) ElectrondEdxEtaP->Project3D("dEdx_x");
	TH1D *PositrondEdx = (TH1D*) PositrondEdxEtaP->Project3D("dEdx_x");	

	//NSigma dE/dx distribution
	TH1D *ElectronNSigmadEdx = (TH1D*) ElectronNSigmadEdxEtaP->Project3D("NSigmadEdx_x");
	TH1D *PositronNSigmadEdx = (TH1D*) PositronNSigmadEdxEtaP->Project3D("NSigmadEdx_x");
	Double_t meanElectronNSigmadEdx = ElectronNSigmadEdx->GetMean(1);
	Double_t meanErrElectronNSigmadEdx = ElectronNSigmadEdx->GetMeanError(1);
	cout << "Mean value of electron nsigma dE/dx: " << meanElectronNSigmadEdx << " +/- " << meanErrElectronNSigmadEdx << endl;
	Double_t meanPositronNSigmadEdx = PositronNSigmadEdx->GetMean(1);
	Double_t meanErrPositronNSigmadEdx = PositronNSigmadEdx->GetMeanError(1);
	cout << "Mean value of positron nsigma dE/dx: " << meanPositronNSigmadEdx << " +/- " << meanErrPositronNSigmadEdx << endl;

	//Eta distribution (from dE/dx)
//	TH1D *ElectronEta = (TH1D*) ElectrondEdxEtaP->Project3D("y");
//	TH1D *PositronEta = (TH1D*) PositrondEdxEtaP->Project3D("y");	

	//Eta distribution (from NSigma dE/dx)
	TH1D *ElectronEta_NSigma = (TH1D*) ElectronNSigmadEdxEtaP->Project3D("EtafromNSigma_y");
	TH1D *PositronEta_NSigma = (TH1D*) PositronNSigmadEdxEtaP->Project3D("EtafromNSigma_y");
	Double_t meanEtaElectron_NSigma = ElectronEta_NSigma->GetMean(1);
	Double_t meanErrEtaElectron_NSigma = ElectronEta_NSigma->GetMeanError(1);
	cout << "Mean value of electron Eta distribution: " << meanEtaElectron_NSigma << " +/- " << meanErrEtaElectron_NSigma << endl;
	Double_t meanEtaPositron_NSigma = PositronEta_NSigma->GetMean(1);
	Double_t meanErrEtaPositron_NSigma = PositronEta_NSigma->GetMeanError(1);
	cout << "Mean value of positron Eta distribution: " << meanEtaPositron_NSigma << " +/- " << meanErrEtaPositron_NSigma << endl;

	//Pt distribution (from dE/dx)
//	TH1D *ElectronPt = (TH1D*) ElectrondEdxEtaP->Project3D("z");
//	TH1D *PositronPt = (TH1D*) PositrondEdxEtaP->Project3D("z");	

	//Eta distribution (from NSigma dE/dx)
	TH1D *ElectronPt_NSigma = (TH1D*) ElectronNSigmadEdxEtaP->Project3D("PtfromNSigma_z");
	TH1D *PositronPt_NSigma = (TH1D*) PositronNSigmadEdxEtaP->Project3D("PtfromNSigma_z");
	Double_t meanPtElectron_NSigma = ElectronPt_NSigma->GetMean(1);
	Double_t meanErrPtElectron_NSigma = ElectronPt_NSigma->GetMeanError(1);
	cout << "Mean value of electron Pt distribution: " << meanPtElectron_NSigma << " +/- " << meanErrPtElectron_NSigma << endl;
	Double_t meanPtPositron_NSigma = PositronPt_NSigma->GetMean(1);
	Double_t meanErrPtPositron_NSigma = PositronPt_NSigma->GetMeanError(1);
	cout << "Mean value of positron Pt distribution: " << meanPtPositron_NSigma << " +/- " << meanErrPtPositron_NSigma << endl;
	cout << "====================================================================================================" << endl;

	TH2F *ElectronEtaPt = (TH2F*) folderInFile->Get("histoElectronEtaPt")->Clone("ElectronEtaPt");
	TH2F *PositronEtaPt = (TH2F*) folderInFile->Get("histoPositronEtaPt")->Clone("PositronEtaPt");
	TH2F *GammaEtaPt = (TH2F*) folderInFile->Get("histoGammaEtaPt")->Clone("GammaEtaPt");

	//Eta distribution (from 2D histo)
	TH1D *ElectronEta_bis = (TH1D*) ElectronEtaPt->ProjectionX("ElectronEta");
	Double_t meanElectronEta_bis = ElectronEta_bis->GetMean(1);
	Double_t meanErrElectronEta_bis = ElectronEta_bis->GetMeanError(1);
	cout << "Mean value of electron Eta distribution: " << meanElectronEta_bis << " +/- " << meanErrElectronEta_bis << endl;

	TH1D *PositronEta_bis = (TH1D*) PositronEtaPt->ProjectionX("PositronEta");
	Double_t meanPositronEta_bis = PositronEta_bis->GetMean(1);
	Double_t meanErrPositronEta_bis = PositronEta_bis->GetMeanError(1);
	cout << "Mean value of positron Eta distribution: " << meanPositronEta_bis << " +/- " << meanErrPositronEta_bis << endl;

	TH1D *GammaEta = (TH1D*) GammaEtaPt->ProjectionX("GammaEta");
	Double_t meanGammaEta = GammaEta->GetMean(1);
	Double_t meanErrGammaEta = GammaEta->GetMeanError(1);
	cout << "Mean value of photon Eta distribution: " << meanGammaEta << " +/- " << meanErrGammaEta << endl;

	//Pt distribution
	TH1D *ElectronPt_bis = (TH1D*) ElectronEtaPt->ProjectionY("ElectronPt");
	Double_t meanElectronPt_bis = ElectronPt_bis->GetMean(1);
	Double_t meanErrElectronPt_bis = ElectronPt_bis->GetMeanError(1);
	cout << "Mean value of electron Pt distribution: " << meanElectronPt_bis << " +/- " << meanErrElectronPt_bis << endl;

	TH1D *PositronPt_bis = (TH1D*) PositronEtaPt->ProjectionY("PositronPt");
	Double_t meanPositronPt_bis = PositronPt_bis->GetMean(1);
	Double_t meanErrPositronPt_bis = PositronPt_bis->GetMeanError(1);
	cout << "Mean value of positron Pt distribution: " << meanPositronPt_bis << " +/- " << meanErrPositronPt_bis << endl;

	TH1D *GammaPt = (TH1D*) GammaEtaPt->ProjectionY("GammaPt");
	Double_t meanGammaPt = GammaPt->GetMean(1);
	Double_t meanErrGammaPt = GammaPt->GetMeanError(1);
	cout << "Mean value of photon Pt distribution: " << meanGammaPt << " +/- " << meanErrGammaPt << endl;

	//Gamma Alpha        
	TH2F *GammaAlphaQt = (TH2F*) folderInFile->Get("histoGammaAlphaQt")->Clone("GammaAlphaQt");
	TH1D *GammaAlpha = (TH1D*) GammaAlphaQt->ProjectionX("GammaAlpha");
	Double_t meanGammaAlpha = GammaAlpha->GetMean(1);
	Double_t meanErrGammaAlpha = GammaAlpha->GetMeanError(1);
	cout << "Mean value of photon alpha distribution: " << meanGammaAlpha << " +/- " << meanErrGammaAlpha << endl;
	cout << "====================================================================================================" << endl;

	//Gamma Phi
	TH1F *GammaPhi = (TH1F*) folderInFile->Get("histoGammaPhi")->Clone("GammaPhi");
	Double_t pi = TMath::Pi();
	Double_t rangePhi = pi/9.0;
	Double_t gammas[18], sector[18];
	
	/*TFile *EventFile = new TFile(Form("%s/GammaConvV1_QA_%s.root", fileDirectory.Data(),cutNumber.Data()));
	if(EventFile->IsZombie()) return;
      	TList *EvFolder = (TList*) EventFile->Get(Form("GammaConv_V1QA_%s",cutNumber.Data()));
	TList *ESDFolder = (TList*) EvFolder->FindObject("ESD QA");
	TH1F *VertexZ = (TH1F*) ESDFolder->FindObject("Vertex_Z");
	Double_t Events = VertexZ->GetEntries();
	cout << "Number of events: " << Events << endl;
	*/
	
	for(Int_t t=1; t<19; t++)
	  {
	     Double_t NumGammaPerSector = GammaPhi->GetBinContent(GammaPhi->GetXaxis()->FindBin(rangePhi*t));
	     //Double_t meanErrGammaAlpha = GammaAlpha->GetMeanError(1);
	     cout << "====================================================================================================" << endl;
	     cout << "Number of gamma for TPC sector  " << t << ": " << NumGammaPerSector << endl;
	     cout << "====================================================================================================" << endl;
	     sector[t-1] = t;
	     gammas[t-1] = NumGammaPerSector; ///Events;
	  }
	
	TCanvas *c1 = new TCanvas("c1","Gammas for TPC sectors",200,10,700,500);
	TGraph* NGammaPerSector = new TGraph(17,sector,gammas);
	NGammaPerSector->SetMarkerStyle(21);	
	NGammaPerSector->Draw("ACP");


	//ITS cluster plots

	TH1D *ElectronRcls1;
	TH1D *ElectronRcls2;
	TH1D *ElectronRcls3;
	TH1D *ElectronRcls4;
	TH1D *ElectronRcls5;
	TH1D *ElectronRcls6;		  
	TH1D *PositronRcls1;
	TH1D *PositronRcls2;
	TH1D *PositronRcls3;
	TH1D *PositronRcls4;
	TH1D *PositronRcls5;
	TH1D *PositronRcls6;

	//electron
	TH2F *ElectronITSclsR = (TH2F*) folderInFile->Get("histoElectronITSClR")->Clone("ElectronITSclsR");
	ElectronRcls1 = (TH1D*) ElectronITSclsR->ProjectionY("ElectronRcls1",1,1);
	ElectronRcls2 = (TH1D*) ElectronITSclsR->ProjectionY("ElectronRcls2",2,2);
	ElectronRcls3 = (TH1D*) ElectronITSclsR->ProjectionY("ElectronRcls3",3,3);
	ElectronRcls4 = (TH1D*) ElectronITSclsR->ProjectionY("ElectronRcls4",4,4);
	ElectronRcls5 = (TH1D*) ElectronITSclsR->ProjectionY("ElectronRcls5",5,5);
	ElectronRcls6 = (TH1D*) ElectronITSclsR->ProjectionY("ElectronRcls6",6,6);
	ElectronRcls1->SetLineColor(kBlack);
	ElectronRcls1->SetLineWidth(2);	
	ElectronRcls2->SetLineColor(kBlue);
	ElectronRcls2->SetLineWidth(2);
	ElectronRcls3->SetLineColor(kRed);
	ElectronRcls3->SetLineWidth(2);	
	ElectronRcls4->SetLineColor(kAzure-4);
	ElectronRcls4->SetLineWidth(2);	
	ElectronRcls5->SetLineColor(kOrange+1);
	ElectronRcls5->SetLineWidth(2);	
	ElectronRcls6->SetLineColor(kGreen+2);
	ElectronRcls6->SetLineWidth(2);
	//positron
	TH2F *PositronITSclsR = (TH2F*) folderInFile->Get("histoPositronITSClR")->Clone("PositronITSclsR");
	PositronRcls1 = (TH1D*) PositronITSclsR->ProjectionY("PositronRcls1",1,1);
	PositronRcls2 = (TH1D*) PositronITSclsR->ProjectionY("PositronRcls2",2,2);
	PositronRcls3 = (TH1D*) PositronITSclsR->ProjectionY("PositronRcls3",3,3);
	PositronRcls4 = (TH1D*) PositronITSclsR->ProjectionY("PositronRcls4",4,4);
	PositronRcls5 = (TH1D*) PositronITSclsR->ProjectionY("PositronRcls5",5,5);
	PositronRcls6 = (TH1D*) PositronITSclsR->ProjectionY("PositronRcls6",6,6);	

	PositronRcls1->SetLineColor(kBlack);
	PositronRcls1->SetLineWidth(2);
	PositronRcls2->SetLineColor(kBlue);
	PositronRcls2->SetLineWidth(2);	
	PositronRcls3->SetLineColor(kRed);
	PositronRcls3->SetLineWidth(2);	
	PositronRcls4->SetLineColor(kAzure-4);
	PositronRcls4->SetLineWidth(2);
	PositronRcls5->SetLineColor(kOrange+1);
	PositronRcls5->SetLineWidth(2);
	PositronRcls6->SetLineColor(kGreen+2);
	PositronRcls6->SetLineWidth(2);



	//Gamma candidates
	TFile *GammaCandidateFromData = TFile::Open("/home/admin1/leardini/OutputFilesXmas/GammaConvV1_GA_PbPb_Data_33.root");
	TList *folder = (TList*) GammaCandidateFromData->Get("GammaConvV1");
	TList *folderinfolder = (TList*) folder->FindObject("Cut Number 5010001002092970023220000000_01525045009000");
	TList *folderin2folder = (TList*) folderinfolder->FindObject("5010001002092970023220000000_01525045009000 ESD histograms");
	TH1I *GammaCandidates = (TH1I*) folderin2folder->FindObject("GammaCandidates")->Clone("GammaCandidates");
	GammaCandidates->SetLineColor(kBlack);


	TFile *fileoutput = new TFile(Form("%s/OutputFile_AnalysisQA_%s.root",outputDirectory.Data(), mode.Data()), "RECREATE");
	fileoutput->cd();

	ElectrondEdxPt->Write();
	ElectrondEdxEta->Write();
	ElectrondEdx->Write();
	ElectronNSigmadEdxPt->Write();
	ElectronNSigmadEdxEta->Write();
	ElectronNSigmadEdx->Write();
	ElectronEta_NSigma->Write();
	ElectronPt_NSigma->Write();
	ElectronEta_bis->Write();
	ElectronPt_bis->Write();

	PositrondEdxPt->Write();
	PositrondEdxEta->Write();
	PositrondEdx->Write();
	PositronNSigmadEdxPt->Write();
	PositronNSigmadEdxEta->Write();
	PositronNSigmadEdx->Write();
	PositronEta_NSigma->Write();
	PositronPt_NSigma->Write();
	PositronEta_bis->Write();
	PositronPt_bis->Write();
	
	GammaEta->Write();
	GammaPt->Write();
	GammaAlpha->Write();
	NGammaPerSector->Write("Gammas per TPC sector");

	ElectronRcls1->Write();
	ElectronRcls2->Write();
	ElectronRcls3->Write();
	ElectronRcls4->Write();
	ElectronRcls5->Write();
	ElectronRcls6->Write();
	PositronRcls1->Write();
	PositronRcls2->Write();
	PositronRcls3->Write();
	PositronRcls4->Write();
	PositronRcls5->Write();
	PositronRcls6->Write();
	GammaCandidates->Write();
	
	fileoutput->Write();
	fileoutput->Close();	
	
	File->Close();	
	GammaCandidateFromData->Close();


      }//end allrun QA analysis

   else
     if(mode.EqualTo("runwise"))
	{
	   TString RunNumbers[200];
	   Double_t nRun[200];
	   TFile *File[200];
	   TDirectoryFile *folderInFile[200];
	   
	   TFile *EventFile[200];
	   TList *EvFolder[200];
	   TList *ESDFolder[200];
	   TH1F *VertexZ[200];
	   Double_t Events[200];   
	   
	   TH3F *NSigmadEdxElectron[200];
	   TH3F *NSigmadEdxPositron[200];
	   
	   TH1D *projxNSigmadEdxElectron[200];
	   TH1D *projxNSigmadEdxPositron[200];
	   Double_t meanNSigmadEdxElectron[200];
	   Double_t meanErrNSigmadEdxElectron[200];
	   Double_t meanNSigmadEdxPositron[200];
	   Double_t meanErrNSigmadEdxPositron[200];
	   
	   TH1D *projyNSigmadEdxElectron[200];
	   TH1D *projyNSigmadEdxPositron[200];
	   Double_t meanEtaElectron[200];
	   Double_t meanErrEtaElectron[200];
	   Double_t meanEtaPositron[200];
	   Double_t meanErrEtaPositron[200];
	   
	   TH1D *projzNSigmadEdxElectron[200];
	   TH1D *projzNSigmadEdxPositron[200];
	   Double_t meanPtElectron[200];
	   Double_t meanErrPtElectron[200];
	   Double_t meanPtPositron[200];
	   Double_t meanErrPtPositron[200];
	   
	   TH2F *GammaEtaPt[200];
	   TH1D *GammaEta[200];
	   TH1D *GammaPt[200];
	   Double_t meanGammaEta[200];
	   Double_t meanErrGammaEta[200];
	   Double_t meanGammaPt[200];
	   Double_t meanErrGammaPt[200];
	   TH2F *GammaAlphaQt[200];
	   TH1D *GammaAlpha[200];
	   Double_t meanGammaAlpha[200];
	   Double_t meanErrGammaAlpha[200];   
	   Double_t ex[200];

	   StyleSettingsThesis();
	   SetPlotStyle();
	   Color_t color[20] = {kBlack, kAzure, kGreen+2,kOrange+2,kRed, kViolet,  kBlue-9, kSpring+10, kCyan+3, kCyan-10, kCyan, kGreen+4, kGreen-9, 
		       		kGreen,  kYellow+4, kYellow+3, kMagenta+4, kMagenta-8, kGray, kGray+3};
	   
	   ifstream in(runFile.Data());
	   string RunNum;
	   Int_t counter = 0;
	   while(getline(in, RunNum) && !in.eof())
	      {	  
		RunNumbers[counter] = RunNum;
	    	cout << "Run numbers: " << RunNumbers[counter] <<endl;
	   	nRun[counter] = RunNumbers[counter].Atoi();
	   	//cout << nRun[counter]<< endl; 		
	      	counter++;
	      }
	   in.close();
	   counter--;
	   cout << "========================== How many runs? " << counter << endl;
	   	
	   
	   for(Int_t i=0; i<counter+1; i++)
	      { ex[i] = 0; 

		File[i] = new TFile(Form("%s/%s/%s", fileDirectory.Data(), RunNumbers[i].Data(), fileName.Data()));
		if (File[i]->IsZombie()) return;
	   	
		folderInFile[i] = (TDirectoryFile*) File[i]->Get(Form("GammaConv_0004_%s",cutNumber.Data()));
	
		//EventFileName[i] = Form("%s/%s/GammaConvV1_QA_%s.root", fileDirectory.Data(),RunNumbers[i].Data(),cutNumber.Data());
		//cout << EventFileName[i].Data() << endl;


	      	EventFile[i] = new TFile(Form("%s/%s/GammaConvV1_QA_%s.root", fileDirectory.Data(),RunNumbers[i].Data(),cutNumber.Data()));
		//if(!EventFile[i]) {cout << "File not found for run " << nRun[i] << endl; continue;}
		//else{
		if(EventFile[i]->IsZombie()) return;

		//get the number of events	
	      	EvFolder[i] = (TList*) EventFile[i]->Get(Form("GammaConv_V1QA_%s",cutNumber.Data()));
	      	ESDFolder[i] = (TList*) EvFolder[i]->FindObject("ESD QA");
		VertexZ[i] = (TH1F*) ESDFolder[i]->FindObject("Vertex_Z");
		Events[i] = VertexZ[i]->GetEntries();
		cout << "Number of events for run number " << nRun[i] << ": " << Events[i] << endl;

	
		NSigmadEdxElectron[i] = (TH3F*) folderInFile[i]->Get("histoElectronNSigmadEdxEtaP")->Clone("ElectronNSigmadEdxEtaP");        
		//projection of NSigmadEdx electron and positron ---> get mean value
		projxNSigmadEdxElectron[i] = (TH1D*) NSigmadEdxElectron[i]->Project3D("x");
		projxNSigmadEdxElectron[i]->Scale(1./Events[i]);
		meanNSigmadEdxElectron[i] = projxNSigmadEdxElectron[i]->GetMean(1);
		meanErrNSigmadEdxElectron[i] = projxNSigmadEdxElectron[i]->GetMeanError(1);
	
		NSigmadEdxPositron[i] = (TH3F*) folderInFile[i]->Get("histoPositronNSigmadEdxEtaP")->Clone("PositronNSigmadEdxEtaP");        
		projxNSigmadEdxPositron[i] = (TH1D*) NSigmadEdxPositron[i]->Project3D("x");
		projxNSigmadEdxPositron[i]->Scale(1./Events[i]);
		meanNSigmadEdxPositron[i] = projxNSigmadEdxPositron[i]->GetMean(1);
		meanErrNSigmadEdxPositron[i] = projxNSigmadEdxPositron[i]->GetMeanError(1);

	
		GammaEtaPt[i] = (TH2F*) folderInFile[i]->Get("histoGammaEtaPt")->Clone("GammaEtaPt");
	
		//Gamma, electron and positron Eta ---> get mean value        
		projyNSigmadEdxElectron[i] = (TH1D*) NSigmadEdxElectron[i]->Project3D("y");
		projyNSigmadEdxElectron[i]->Scale(1./Events[i]);
		meanEtaElectron[i] = projyNSigmadEdxElectron[i]->GetMean(1);
		meanErrEtaElectron[i] = projyNSigmadEdxElectron[i]->GetMeanError(1);
	
		projyNSigmadEdxPositron[i] = (TH1D*) NSigmadEdxPositron[i]->Project3D("y");
		projyNSigmadEdxPositron[i]->Scale(1./Events[i]);
		meanEtaPositron[i] = projyNSigmadEdxPositron[i]->GetMean(1);
		meanErrEtaPositron[i] = projyNSigmadEdxPositron[i]->GetMeanError(1);
	
		GammaEta[i] = (TH1D*) GammaEtaPt[i]->ProjectionX("GammaEta");
		GammaEta[i]->Scale(1./Events[i]);
		meanGammaEta[i] = GammaEta[i]->GetMean(1);
		meanErrGammaEta[i] = GammaEta[i]->GetMeanError(1);
	
		//Gamma, electron and positron Pt ---> get mean value
		projzNSigmadEdxElectron[i] = (TH1D*) NSigmadEdxElectron[i]->Project3D("z");
		projzNSigmadEdxElectron[i]->Scale(1./Events[i]);
		meanPtElectron[i] = projzNSigmadEdxElectron[i]->GetMean(1);
		meanErrPtElectron[i] = projzNSigmadEdxElectron[i]->GetMeanError(1);
	
		projzNSigmadEdxPositron[i] = (TH1D*) NSigmadEdxPositron[i]->Project3D("z");
		projzNSigmadEdxPositron[i]->Scale(1./Events[i]);
		meanPtPositron[i] = projzNSigmadEdxPositron[i]->GetMean(1);
		meanErrPtPositron[i] = projzNSigmadEdxPositron[i]->GetMeanError(1);
	
		GammaPt[i] = (TH1D*) GammaEtaPt[i]->ProjectionY("GammaPt");
		GammaPt[i]->Scale(1./Events[i]);
		meanGammaPt[i] = GammaPt[i]->GetMean(1);
		meanErrGammaPt[i] = GammaPt[i]->GetMeanError(1);
	
	
		//Gamma Alpha ---> get mean value        
		GammaAlphaQt[i] = (TH2F*) folderInFile[i]->Get("histoGammaAlphaQt")->Clone("GammaAlphaQt");
		GammaAlpha[i] = (TH1D*) GammaAlphaQt[i]->ProjectionX("GammaAlpha");
		GammaAlpha[i]->Scale(1./Events[i]);
		meanGammaAlpha[i] = GammaAlpha[i]->GetMean(1);
		meanErrGammaAlpha[i] = GammaAlpha[i]->GetMeanError(1);
		//}

		File[i]->Close();
		EventFile[i]->Close();
		cout << "End of loop" << endl;


	      }
	

	//Draw variables run wise
	TGraphErrors* NSdEdxElectron = new TGraphErrors(counter,nRun,meanNSigmadEdxElectron,ex,meanErrNSigmadEdxElectron);
	NSdEdxElectron->SetMarkerStyle(20);
	NSdEdxElectron->SetMarkerColor(kBlue+2);
	TGraphErrors* NSdEdxPositron = new TGraphErrors(counter,nRun,meanNSigmadEdxPositron,ex,meanErrNSigmadEdxPositron);
	NSdEdxPositron->SetMarkerStyle(20);
	NSdEdxPositron->SetMarkerColor(kBlue+2);
	TGraphErrors* ElectronEta = new TGraphErrors(counter,nRun,meanEtaElectron,ex,meanErrEtaElectron);
	ElectronEta->SetMarkerStyle(22);
	ElectronEta->SetMarkerColor(kRed+2);
	TGraphErrors* PositronEta = new TGraphErrors(counter,nRun,meanEtaPositron,ex,meanErrEtaPositron);
	PositronEta->SetMarkerStyle(22);
	PositronEta->SetMarkerColor(kRed+2);
	TGraphErrors* PhotonEta = new TGraphErrors(counter,nRun,meanGammaEta,ex,meanErrGammaEta);
	PhotonEta->SetMarkerStyle(22);
	PhotonEta->SetMarkerColor(kRed+2);
	TGraphErrors* ElectronPt = new TGraphErrors(counter,nRun,meanPtElectron,ex,meanErrPtElectron);
	ElectronPt->SetMarkerStyle(24);
	ElectronPt->SetMarkerColor(kGreen+2);
	TGraphErrors* PositronPt = new TGraphErrors(counter,nRun,meanPtPositron,ex,meanErrPtPositron);
	PositronPt->SetMarkerStyle(24);
	PositronPt->SetMarkerColor(kGreen+2);
	TGraphErrors* PhotonPt = new TGraphErrors(counter,nRun,meanGammaPt,ex,meanErrGammaPt);
	PhotonPt->SetMarkerStyle(24);
	PhotonPt->SetMarkerColor(kGreen+2);
	TGraphErrors* PhotonAlpha = new TGraphErrors(counter,nRun,meanGammaAlpha,ex,meanErrGammaAlpha);
	PhotonAlpha->SetMarkerStyle(26);
	PhotonAlpha->SetMarkerColor(kMagenta+2);

	TCanvas* cNSElectron= new TCanvas("NSElectron","NSElectron",1350,1500);  // gives the page size
	cNSElectron->SetTickx();
	cNSElectron->SetTicky();
	//cNSElectron->SetGridx(0);
	cNSElectron->SetGridy(1);
	cNSElectron->SetFillColor(0);
	DrawGammaSetMarkerTGraph(NSdEdxElectron, 20, 1., color[0], color[0], 1, 1, kFALSE, 0); 
	//histoGammaPhiPerRunIntegral->SetMarkerColor(kBlue);
	//histoGammaPhiPerRunIntegral->SetMarkerStyle(25);
	//h->Draw();
	NSdEdxElectron->Draw("peaxis");
	TGaxis::SetMaxDigits(6);
	cNSElectron->SaveAs(Form("%s/NSigmadEdxElectron.%s",outputDirectory.Data(),suffix.Data()));
	delete cNSElectron;


	TCanvas* cNSPositron= new TCanvas("NSPositron","NSPositron",1350,1500);  // gives the page size
	cNSPositron->SetTickx();
	cNSPositron->SetTicky();
	//cNSPositron->SetGridx(0);
	cNSPositron->SetGridy(1);
	cNSPositron->SetFillColor(0);
	DrawGammaSetMarkerTGraph(NSdEdxPositron, 20, 1., color[0], color[0], 1, 1, kFALSE, 0); 
	NSdEdxPositron->Draw("peaxis");
	TGaxis::SetMaxDigits(6);
	cNSPositron->SaveAs(Form("%s/NSigmadEdxPositron.%s",outputDirectory.Data(),suffix.Data()));
	delete cNSPositron;


	TCanvas* cElectronEta= new TCanvas("ElectronEta","ElectronEta",1350,1500);  // gives the page size
	cElectronEta->SetTickx();
	cElectronEta->SetTicky();
	//cElectronEta->SetGridx(0);
	cElectronEta->SetGridy(1);
	cElectronEta->SetFillColor(0);
	DrawGammaSetMarkerTGraph(ElectronEta, 20, 1., color[0], color[0], 1, 1, kFALSE, 0); 
	ElectronEta->Draw("peaxis");
	TGaxis::SetMaxDigits(6);
	cElectronEta->SaveAs(Form("%s/ElectronEta.%s",outputDirectory.Data(),suffix.Data()));
	delete cElectronEta;


	TCanvas* cPositronEta= new TCanvas("PositronEta","PositronEta",1350,1500);  // gives the page size
	cPositronEta->SetTickx();
	cPositronEta->SetTicky();
	//cPositronEta->SetGridx(0);
	cPositronEta->SetGridy(1);
	cPositronEta->SetFillColor(0);
	DrawGammaSetMarkerTGraph(PositronEta, 20, 1., color[0], color[0], 1, 1, kFALSE, 0); 
	PositronEta->Draw("peaxis");
	TGaxis::SetMaxDigits(6);
	cPositronEta->SaveAs(Form("%s/PositronEta.%s",outputDirectory.Data(),suffix.Data()));
	delete cPositronEta;


	TCanvas* cPhotonEta= new TCanvas("PhotonEta","PhotonEta",1350,1500);  // gives the page size
	cPhotonEta->SetTickx();
	cPhotonEta->SetTicky();
	//cPhotonEta->SetGridx(0);
	cPhotonEta->SetGridy(1);
	cPhotonEta->SetFillColor(0);
	DrawGammaSetMarkerTGraph(PhotonEta, 20, 1., color[0], color[0], 1, 1, kFALSE, 0); 
	PhotonEta->Draw("peaxis");
	TGaxis::SetMaxDigits(6);
	cPhotonEta->SaveAs(Form("%s/PhotonEta.%s",outputDirectory.Data(),suffix.Data()));
	delete cPhotonEta;


	TCanvas* cElectronPt= new TCanvas("ElectronPt","ElectronPt",1350,1500);  // gives the page size
	cElectronPt->SetTickx();
	cElectronPt->SetTicky();
	//cElectronPt->SetGridx(0);
	cElectronPt->SetGridy(1);
	cElectronPt->SetFillColor(0);
	DrawGammaSetMarkerTGraph(ElectronPt, 20, 1., color[0], color[0], 1, 1, kFALSE, 0); 
	ElectronPt->Draw("peaxis");
	TGaxis::SetMaxDigits(6);
	cElectronPt->SaveAs(Form("%s/ElectronPt.%s",outputDirectory.Data(),suffix.Data()));
	delete cElectronPt;


	TCanvas* cPositronPt= new TCanvas("PositronPt","PositronPt",1350,1500);  // gives the page size
	cPositronPt->SetTickx();
	cPositronPt->SetTicky();
	//cPositronPt->SetGridx(0);
	cPositronPt->SetGridy(1);
	cPositronPt->SetFillColor(0);
	DrawGammaSetMarkerTGraph(PositronPt, 20, 1., color[0], color[0], 1, 1, kFALSE, 0); 
	PositronPt->Draw("peaxis");
	TGaxis::SetMaxDigits(6);
	cPositronPt->SaveAs(Form("%s/PositronPt.%s",outputDirectory.Data(),suffix.Data()));
	delete cPositronPt;


	TCanvas* cPhotonPt= new TCanvas("PhotonPt","PhotonPt",1350,1500);  // gives the page size
	cPhotonPt->SetTickx();
	cPhotonPt->SetTicky();
	//cPhotonPt->SetGridx(0);
	cPhotonPt->SetGridy(1);
	cPhotonPt->SetFillColor(0);
	DrawGammaSetMarkerTGraph(PhotonPt, 20, 1., color[0], color[0], 1, 1, kFALSE, 0); 
	PhotonPt->Draw("peaxis");
	TGaxis::SetMaxDigits(6);
	cPhotonPt->SaveAs(Form("%s/PhotonPt.%s",outputDirectory.Data(),suffix.Data()));
	delete cPhotonPt;	

	TCanvas* cPhotonAlpha= new TCanvas("PhotonAlpha","PhotonAlpha",1350,1500);  // gives the page size
	cPhotonAlpha->SetTickx();
	cPhotonAlpha->SetTicky();
	//cPhotonAlpha->SetGridx(0);
	cPhotonAlpha->SetGridy(1);
	cPhotonAlpha->SetFillColor(0);
	DrawGammaSetMarkerTGraph(PhotonAlpha, 20, 1., color[0], color[0], 1, 1, kFALSE, 0); 
	PhotonAlpha->Draw("peaxis");
	TGaxis::SetMaxDigits(6);
	cPhotonAlpha->SaveAs(Form("%s/PhotonAlpha.%s",outputDirectory.Data(),suffix.Data()));
	delete cPhotonAlpha;
	

	TFile *fileoutput_runwise = new TFile(Form("%s/OutputFile_AnalysisQA_%s.root",outputDirectory.Data(), mode.Data()), "RECREATE");
	fileoutput_runwise->cd();
	NSdEdxElectron->Write("NSdEdxElectron");
	NSdEdxPositron->Write("NSdEdxPositron");
	ElectronEta->Write("ElectronEta");
	PositronEta->Write("PositronEta");
	ElectronPt->Write("ElectronPt");
	PositronPt->Write("PositronPt");
	PhotonEta->Write("PhotonEta");
	PhotonEta->Write("PhotonPt");
	PhotonEta->Write("PhotonAlpha");
	fileoutput_runwise->Close();	
	}

}//end

