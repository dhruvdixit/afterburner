/****************************************************************************************************************************
 ****** 		provided by Gamma Conversion Group, PWG4, 																						*****
 ******		Kathrin Koch, kkoch@physi.uni-heidelberg.de 																						*****
 ******		Friederike Bock, friederike.bock@cern.ch																							*****
 *****************************************************************************************************************************
 *** This macro can be used to display the Photon Characteristics of the conversion method in ALICE, it can be operated  *****
 *** on the output of the GammaConversionTask. It can take 2 input files, the second one should be MC, if this is not 	 *****
 *** the case all histograms including MC need to be commented out otherwise the running will crash.							 *****
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

void PlotStandard2D( TH2* histo2D, TString nameOutput, TString title, TString xTitle, TString yTitle, Bool_t kRangeY, Double_t startY, Double_t endY, Bool_t kRangeX, Double_t startX, Double_t endX, Int_t logX, Int_t logZ, Float_t* floatLogo, Int_t canvasSizeX = 500, Int_t canvasSizeY = 500, TString generator ="" , TString textPeriod ="", TString drawingAdditional = ""){
	TCanvas * canvasStandard = new TCanvas("canvasStandard","",10,10,canvasSizeX,canvasSizeY);  // gives the page size		
	canvasStandard->SetLogx(logX);
	canvasStandard->SetLogz(logZ);
	canvasStandard->SetRightMargin(0.12); 		
	canvasStandard->SetLeftMargin(0.12); 		
	canvasStandard->SetBottomMargin(0.1); 		
	canvasStandard->SetTopMargin(0.04); 		
	canvasStandard->cd();
	histo2D->SetTitle("");
	DrawAutoGammaHisto2D(	histo2D,
							title.Data(), xTitle.Data(), yTitle.Data(),"",kRangeY, startY, endY, kRangeX, startX, endX,
							1.03, 1.4,
							floatLogo[2], 1.15*floatLogo[2],
							floatLogo[2], 1.15*floatLogo[2]
						);
	if (drawingAdditional.CompareTo("dEdx")==0) {
		DrawdEdxLabel();
		cout << "ploted dEdx Labels" << endl;
	}
	if (drawingAdditional.CompareTo("Armenteros")==0) DrawArmenteros();
	if (drawingAdditional.CompareTo("TOF")==0) DrawTOFLabels();
	cout << generator.Data() << endl;
	cout << textPeriod.Data() << endl;
	DrawLabelsEvents(floatLogo[0],floatLogo[1],floatLogo[2], 0.00, collisionSystem, generator, textPeriod);
		
	canvasStandard->Update();
	canvasStandard->SaveAs(nameOutput.Data());
	delete canvasStandard;
}

					
void  V0QA(TString data = "myOutput", TString optMC = "", TString cutSel = "", const char *suffix = "gif", TString optEnergy="", TString optMCGenerator="", TString optPeriod="", Int_t mode = 9){	
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
	
	if(optEnergy.CompareTo("7TeV") == 0){
		collisionSystem = "pp @ #sqrt{#it{s}} = 7 TeV";		
	} else if( optEnergy.CompareTo("8TeV") == 0) {
		collisionSystem = "pp @ #sqrt{#it{s}} = 8 TeV";
	} else if( optEnergy.CompareTo("2.76TeV") == 0) {
		collisionSystem = "pp @ #sqrt{#it{s}} = 2.76 TeV";
	} else if( optEnergy.CompareTo("900GeV") == 0) {
		collisionSystem = "pp @ #sqrt{#it{s}} = 900 GeV";
	} else if( optEnergy.CompareTo("HI") == 0) {
		collisionSystem ="PbPb @ #sqrt{#it{s}_{_{NN}}} =2.76 TeV";
	} else {
		cout << "No correct collision system specification, has been given" << endl;
		return;		
	}
	
	
	TString outputDirectory;
	TString outputDirectory1;
	if(optPeriod.CompareTo("") ==0 || optPeriod.CompareTo("All") ==0){
		if (optMCGenerator.CompareTo("")!=0){
			outputDirectory =	 		Form("%s/%s/%s/%s/PhotonQA",optMCGenerator.Data(),cutSel.Data(),optEnergy.Data(),suffix);
			outputDirectory1 = Form("%s/%s",optMCGenerator.Data(),cutSel.Data());
		} else {
			outputDirectory =	 		Form("%s/%s/%s/PhotonQA",cutSel.Data(),optEnergy.Data(),suffix);
			outputDirectory1 = Form("%s",cutSel.Data());
		}
		gSystem->Exec("mkdir -p "+outputDirectory);
	} else if (optMCGenerator.CompareTo("")!=0){
		outputDirectory =	 		Form("%s/%s/%s/%s/%s/PhotonQA",optMCGenerator.Data(),cutSel.Data(),optEnergy.Data(),suffix,optPeriod.Data());
		outputDirectory1 = Form("%s/%s",optMCGenerator.Data(),cutSel.Data());
		gSystem->Exec("mkdir -p "+outputDirectory);
	} else {
		outputDirectory =	 		Form("%s/%s/%s/%s/PhotonQA",cutSel.Data(),optEnergy.Data(),suffix,optPeriod.Data());
		outputDirectory1 = Form("%s/%s",optMCGenerator.Data(),cutSel.Data());
		gSystem->Exec("mkdir -p "+outputDirectory);
	}

	Float_t floatLocationRightUp2D[4] = {0.6,0.95,0.035, 0.02};
	if( optEnergy.CompareTo("HI") == 0) {
		floatLocationRightUp2D[0]=		0.53;
	}
	
	TString textStandardYAxis = "#frac{d#it{N}_{#gamma}}{#it{N}_{ch}}";
	TString textYAxisEtaElec = "#frac{d#it{N}_{e^{-}}}{#it{N}_{e^{-}} d#eta}";
	TString textYAxisEtaPos = "#frac{d#it{N}_{e^{+}}}{#it{N}_{e^{+}} d#eta}";
	TString textYAxisEtaGamma = "#frac{d#it{N}_{#gamma}}{#it{N}_{#gamma} d#eta}";
	TString textYAxisPtDist = "#frac{d#it{N}_{#gamma}}{#it{N}_{#gamma} d#it{p}_{T}} (GeV/#it{c})^{-1}";
	TString textYAxisPtDistE = "#frac{d#it{N}_{e^{-}}}{#it{N}_{e^{-}} d#it{p}_{T}} (GeV/#it{c})^{-1}";
	TString textYAxisPtDistP = "#frac{d#it{N}_{e^{+}}}{#it{N}_{e^{+}} d#it{p}_{T}} (GeV/#it{c})^{-1}";
	TString textYAxisChi2 = "#frac{d#it{N}_{#gamma}}{#it{N}_{#gamma} d#chi^{2}}";
	TString textYAxisPsiPair = "#frac{d#it{N}_{#gamma}}{#it{N}_{#gamma} d#psi_{pair}}";
	TString textYAxisPhi = "#frac{d#it{N}_{#gamma}}{#it{N}_{#gamma} d#phi}";
	TString textYAxisMEP = "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d#it{M}_{e^{+}e^{-}}} (GeV/#it{c}^{2})^{-1}";
	TString textYAxisMGG = "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d#it{M}_{#gamma#gamma} } (GeV/#it{c}^{2})^{-1}";
	TString textYAxisAlpha = "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d#alpha}";
	TString textYAxisPoint = "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d cos(#theta_{pointing})}";
	TString textYAxisDCA = "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d DCA} (cm^{-1})";
	TString textYAxisNDCA = "#frac{1}{#it{N}_{ch}} #frac{d#it{N}_{#gamma}}{d DCA/#sigma}";
	TString textYAxisLike = "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d Likelyhood}";

	textDate = ReturnDateString();

	TLatex *latexScaling = new TLatex(0.6,0.5,"MC scaled to mean of Data"); // Bo: this was modified
	latexScaling->SetNDC();
	latexScaling->SetTextColor(2);
	latexScaling->SetTextFont(42);
	latexScaling->SetTextSize(0.03);
	latexScaling->SetLineWidth(2);	
	
	TString nameGammaDirectory = Form("ConvCuts_%s",  cutSel.Data());
	cout << nameGammaDirectory.Data() << endl;

// 	Float_t floatLineWidth = 1;
	
	// ---------------------------- LOAD ALL FILES ---------------------------------------------------
	TFile 	fileData(data.Data());  
	TString nameTopDir = "GammaConvV1";
	if (mode == 2 || mode == 3) nameTopDir = "GammaConvCalo";
	TList *TopDirData =(TList*)fileData.Get(nameTopDir.Data());
   if(TopDirData == NULL){
      cout<<"ERROR: TopDirData not Found"<<endl;
      return;
   }
	//for new versions
	TList *directoryPhotonQAData = (TList*)TopDirData->FindObject(nameGammaDirectory.Data());
	if(directoryPhotonQAData == NULL){
      cout<<"ERROR: ConversionCuts not Found"<<endl;
      return;
   }
	TH2F* 	hist2DDaughterCanddEdx = 		(TH2F*)directoryPhotonQAData->FindObject(Form("Gamma_dEdx_before %s",cutSel.Data()));	
	hist2DDaughterCanddEdx->Scale(1./hist2DDaughterCanddEdx->GetEntries());
	TH2F* 	hist2DDaughterCanddEdxSig = 	(TH2F*)directoryPhotonQAData->FindObject(Form("Gamma_dEdxSig_before %s",cutSel.Data()));	
	hist2DDaughterCanddEdxSig->Scale(1./hist2DDaughterCanddEdxSig->GetEntries());
	TH2F* 	hist2DDaughterCandTOF = 	(TH2F*)directoryPhotonQAData->FindObject(Form("Gamma_TOF_before %s",cutSel.Data()));	
	hist2DDaughterCandTOF->Scale(1./hist2DDaughterCandTOF->GetEntries());
	TH2F* 	hist2DDaughterCandTOFSig = 	(TH2F*)directoryPhotonQAData->FindObject(Form("Gamma_TOFSig_before %s",cutSel.Data()));	
	hist2DDaughterCandTOFSig->Scale(1./hist2DDaughterCandTOFSig->GetEntries());
	TH2F* 	hist2DArmenteros = 	(TH2F*)directoryPhotonQAData->FindObject(Form("Armenteros_before %s",cutSel.Data()));	
	hist2DArmenteros->Scale(1./hist2DArmenteros->GetEntries());
	

	
	// ---------------------------- LOAD ALL FILES ---------------------------------------------------
	TFile 	fileMonteCarlo(optMC.Data());  
	TList *TopDirMonteCarlo =(TList*)fileMonteCarlo.Get(nameTopDir.Data());
	if(TopDirMonteCarlo == NULL){
		cout<<"ERROR: TopDirMonteCarlo not Found"<<endl;
		return;
	}
	//for new versions
	TList *directoryPhotonQAMonteCarlo = (TList*)TopDirMonteCarlo->FindObject(Form("ConvCuts_%s",cutSel.Data()));
	
	TH2F* 	hist2DDaughterCanddEdxMC = 		(TH2F*)directoryPhotonQAMonteCarlo->FindObject(Form("Gamma_dEdx_before %s",cutSel.Data()));	
	hist2DDaughterCanddEdxMC->Scale(1./hist2DDaughterCanddEdxMC->GetEntries());
	TH2F* 	hist2DDaughterCanddEdxSigMC = 	(TH2F*)directoryPhotonQAMonteCarlo->FindObject(Form("Gamma_dEdxSig_before %s",cutSel.Data()));	
	hist2DDaughterCanddEdxSigMC->Scale(1./hist2DDaughterCanddEdxSigMC->GetEntries());
	TH2F* 	hist2DDaughterCandTOFMC = 	(TH2F*)directoryPhotonQAMonteCarlo->FindObject(Form("Gamma_TOF_before %s",cutSel.Data()));	
	hist2DDaughterCandTOFMC->Scale(1./hist2DDaughterCandTOFMC->GetEntries());
	TH2F* 	hist2DDaughterCandTOFSigMC = 	(TH2F*)directoryPhotonQAMonteCarlo->FindObject(Form("Gamma_TOFSig_before %s",cutSel.Data()));	
	hist2DDaughterCandTOFSigMC->Scale(1./hist2DDaughterCandTOFSigMC->GetEntries());
	TH2F* 	hist2DArmenterosMC = 	(TH2F*)directoryPhotonQAMonteCarlo->FindObject(Form("Armenteros_before %s",cutSel.Data()));	
	hist2DArmenterosMC->Scale(1./hist2DArmenterosMC->GetEntries());

	hist2DDaughterCanddEdx->GetZaxis()->SetRangeUser(1e-8,5e-4);
	if (hist2DDaughterCanddEdx->GetEntries() > 0){
		PlotStandard2D( hist2DDaughterCanddEdx , Form("%s/dEdx_Candidates_Data.%s",outputDirectory.Data(),suffix), "", "#it{p} (GeV/#it{c})", "d#it{E}/d#it{x}",   
						kTRUE, 30., 180., kTRUE, 0.05, 20., 1, 1, floatLocationRightUp2D,500,500,"Data", optPeriod, "dEdx");
	}
	hist2DDaughterCanddEdxMC->GetZaxis()->SetRangeUser(1e-8,5e-4);
	if (hist2DDaughterCanddEdxMC->GetEntries() > 0){
		PlotStandard2D( hist2DDaughterCanddEdxMC , Form("%s/dEdx_Candidates_MonteCarlo.%s",outputDirectory.Data(),suffix), "", "#it{p} (GeV/#it{c})", "d#it{E}/d#it{x}",   
						kTRUE, 30., 180., kTRUE, 0.05, 20., 1, 1, floatLocationRightUp2D,500,500,optMCGenerator, optPeriod, "dEdx");
	}
	hist2DDaughterCanddEdxSig->GetZaxis()->SetRangeUser(1e-8,5e-4);
	if (hist2DDaughterCanddEdxSig->GetEntries() > 0){
		PlotStandard2D( hist2DDaughterCanddEdxSig , Form("%s/nSigma_dEdx_Candidates_Data.%s",outputDirectory.Data(),suffix), "", "#it{p} (GeV/#it{c})", "#it{n} #sigma_{e^{#pm}} d#it{E}/d#it{x}", 
						kTRUE, -5., 7., kTRUE, 0.05, 20., 1, 1, floatLocationRightUp2D,500,500);	
	}

	hist2DDaughterCanddEdxSigMC->GetZaxis()->SetRangeUser(1e-8,5e-4);
	if (hist2DDaughterCanddEdxSigMC->GetEntries() > 0){
		PlotStandard2D( hist2DDaughterCanddEdxSigMC , Form("%s/nSigma_dEdx_Candidates_MonteCarlo.%s",outputDirectory.Data(),suffix), "", "#it{p} (GeV/#it{c})", "#it{n} #sigma_{e^{#pm}} d#it{E}/d#it{x}",
						kTRUE, -5., 7., kTRUE, 0.05, 20., 1, 1, floatLocationRightUp2D,500,500);	
	}
	
	hist2DDaughterCandTOF->GetZaxis()->SetRangeUser(1e-8,1e-4);
	if (hist2DDaughterCandTOF->GetEntries() > 0){
		PlotStandard2D( hist2DDaughterCandTOF , Form("%s/TOF_Candidates_Data.%s",outputDirectory.Data(),suffix),"", "#it{p} (GeV/#it{c})", "#it{t}_{measured}-#it{t}_{expected}", 
						kTRUE, -2000., 10000, kTRUE, 0.2, 15., 1, 1, floatLocationRightUp2D,500,500,"Data", optPeriod, "TOF");
	}
	hist2DDaughterCandTOFMC->GetZaxis()->SetRangeUser(1e-8,1e-4);
	if (hist2DDaughterCandTOFMC->GetEntries() > 0){
		PlotStandard2D( hist2DDaughterCandTOFMC , Form("%s/TOF_Candidates_MonteCarlo.%s",outputDirectory.Data(),suffix),"", "#it{p} (GeV/#it{c})", "#it{t}_{measured}-#it{t}_{expected}", 
						kTRUE, -2000., 10000, kTRUE, 0.2, 15., 1, 1, floatLocationRightUp2D,500,500,optMCGenerator, optPeriod,"TOF");
	}
	
	hist2DDaughterCandTOFSig->GetZaxis()->SetRangeUser(1e-8,1e-4);
	if (hist2DDaughterCandTOFSig->GetEntries() > 0){
		PlotStandard2D( hist2DDaughterCandTOFSig , Form("%s/nSigma_TOF_Candidates_Data.%s",outputDirectory.Data(),suffix), "", "#it{p} (GeV/#it{c})", "#it{n} #sigma_{e^{#pm}} TOF", 
						kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 1, floatLocationRightUp2D,500,500);	
	}
	hist2DDaughterCandTOFSigMC->GetZaxis()->SetRangeUser(1e-8,1e-4);
	if (hist2DDaughterCandTOFSigMC->GetEntries() > 0){
		PlotStandard2D( hist2DDaughterCandTOFSigMC , Form("%s/nSigma_TOF_Candidates_MonteCarlo.%s",outputDirectory.Data(),suffix), "", "#it{p} (GeV/#it{c})", "#it{n} #sigma_{e^{#pm}} TOF", 
						kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 1, floatLocationRightUp2D,500,500);	
	}
	
	hist2DArmenteros->GetZaxis()->SetRangeUser(1e-7,3e-4);
	PlotStandard2D( hist2DArmenteros , Form("%s/Armenteros_Candidates_Data.%s",outputDirectory.Data(),suffix), "", 
					"#alpha = (#it{p}^{+}_{L}-#it{p}^{-}_{L})/(#it{p}^{+}_{L}+#it{p}^{-}_{L})", "#it{q}_{T} (GeV/#it{c})",  
					kTRUE, 0., 0.25,kTRUE, -1., 1., 0, 1, floatLocationRightUp2D,500,500,"Data", optPeriod, "Armenteros");
	
	hist2DArmenterosMC->GetZaxis()->SetRangeUser(1e-7,3e-4);
	PlotStandard2D( hist2DArmenterosMC , Form("%s/Armenteros_Candidates_MonteCarlo.%s",outputDirectory.Data(),suffix), "", 
					"#alpha = (#it{p}^{+}_{L}-#it{p}^{-}_{L})/(#it{p}^{+}_{L}+#it{p}^{-}_{L})", "#it{q}_{T} (GeV/#it{c})", 
					kTRUE, 0., 0.25,kTRUE, -1., 1., 0, 1, floatLocationRightUp2D,500,500,optMCGenerator, optPeriod ,"Armenteros");
	
}

