/*****************************************************************************************************
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
#include "TEllipse.h"

TString textGenerator;
TString collisionSystem;
TString textPeriod;
TString textDate;

void PlotStandard2D( TH2* histo2D, TString nameOutput, TString title, TString xTitle, TString yTitle, Bool_t kRangeY, Double_t startY, Double_t endY, Bool_t kRangeX, Double_t startX, Double_t endX, Int_t logX, Int_t logY, Int_t logZ, Float_t* floatLogo, Int_t canvasSizeX = 500, Int_t canvasSizeY = 500, TString generator ="" , TString period ="", TString drawingAdditional = ""){
   TCanvas * canvasStandard = new TCanvas("canvasStandard","",10,10,canvasSizeX,canvasSizeY);  // gives the page size      
   canvasStandard->SetLogx(logX);
   canvasStandard->SetLogy(logY);
   canvasStandard->SetLogz(logZ);
   canvasStandard->SetRightMargin(0.12);     
   canvasStandard->SetLeftMargin(0.12);      
   canvasStandard->SetBottomMargin(0.1);     
   canvasStandard->SetTopMargin(0.04);       
   canvasStandard->cd();
   histo2D->SetTitle("");
   DrawAutoGammaHisto2D(   histo2D,
                           title.Data(), xTitle.Data(), yTitle.Data(),"",
						   kRangeY, startY, endY, kRangeX, startX, endX);
   histo2D->GetXaxis()->SetTitleOffset(1.05);
   histo2D->GetYaxis()->SetTitleOffset(1.35);
   if (logX==1){
      histo2D->GetXaxis()->SetLabelOffset(0.);
   }   
      
   histo2D->Draw("colz");
   if (drawingAdditional.CompareTo("dEdx")==0) {
      DrawdEdxLabel();
      cout << "ploted dEdx Labels" << endl;
   }
   if (drawingAdditional.CompareTo("Armenteros")==0){
      DrawArmenteros();
      TF1 *felipseGamma = new TF1 ("felipseGamma", "TMath::Sqrt(1-(x*x)/([0]*[0]))*[1]", -0.95, 0.95);
      felipseGamma->SetParameter(0,0.95);
      felipseGamma->SetParameter(1,0.03);
      felipseGamma->Draw("same");
      TF1 *felipseK0s = new TF1 ("felipseK0s", "TMath::Sqrt(1-(x*x)/([0]*[0]))*[1]", -0.828, 0.828);
      felipseK0s->SetParameter(0,0.828);
      felipseK0s->SetParameter(1,0.206);
      felipseK0s->SetLineColor(kViolet+2);
      felipseK0s->Draw("same");
      TF1 *felipseLambda = new TF1 ("felipseLambda", "TMath::Sqrt(1-((x-[2])*(x-[2]))/([0]*[0]))*[1]", 0.511, 0.871);
      felipseLambda->SetParameter(0,0.18);
      felipseLambda->SetParameter(1,0.101);
      felipseLambda->SetParameter(2,0.691);
      felipseLambda->SetLineColor(kGreen+2);
      felipseLambda->Draw("same");
      TF1 *felipseLambdaBar = new TF1 ("felipseLambdaBar", "TMath::Sqrt(1-((x-[2])*(x-[2]))/([0]*[0]))*[1]", -0.871, -0.511);
      felipseLambdaBar->SetParameter(0,0.18);
      felipseLambdaBar->SetParameter(1,0.101);
      felipseLambdaBar->SetParameter(2,-0.691);
      felipseLambdaBar->SetLineColor(kGreen+2);
      felipseLambdaBar->Draw("same");
      
   }   
//    if (drawingAdditional.CompareTo("Asym")==0){
//       TF1 *fAsym = new TF1 ("fAsym", "0.175*TMath::Tan(TMath::Pi()/0.94*(x-0.5))",0.04, 0.96);
//       fAsym->Draw("same");
//       TF1 *fAsym1 = new TF1 ("fAsym1", "0.175*1/TMath::Tan(TMath::Pi()/0.94*(x-0.03))",0.04, 0.96);
//       fAsym1->SetLineColor(kGreen+2);
//       fAsym1->Draw("same");
//    }
   if (drawingAdditional.CompareTo("TOF")==0) DrawTOFLabels();
   DrawLabelsEvents(floatLogo[0],floatLogo[1],floatLogo[2], 0.00, collisionSystem, generator, period);
   
   canvasStandard->Update();
   canvasStandard->SaveAs(nameOutput.Data());
   delete canvasStandard;
}

//*******************************************************************************************************************************************               
//*********************************************************** Main routine ******************************************************************
//*******************************************************************************************************************************************
void  PhotonQAAdvV2(TString data 			= "myOutput", 
					TString optMC 			= "", 
					TString QAcutSelection 	= "0004314141", 
					TString cutSelection 	= "5120001022092970003190000000", 
					TString cutSelectionMC 	= "5120001022092970003190000000", 
					TString suffix 			= "gif", 
					TString optEnergy		= "",
					TString optMCGenerator	= "", 
					TString optPeriod		= ""){   
   
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
   
   collisionSystem 						= ReturnFullCollisionsSystem(optEnergy);
   if (collisionSystem.CompareTo("") == 0){
      cout << "No correct collision system specification, has been given" << endl;
      return;
   }
   TString centralityCutNumber 			= cutSelection(GetEventSystemCutPosition(),3);
   TString centralityString 			= GetCentralityString(centralityCutNumber);
   cout<< centralityCutNumber.Data() << "\t" << centralityString.Data() << endl;
   if (centralityString.CompareTo("pp") !=0){
      collisionSystem 					= Form("%s %s", centralityString.Data(), collisionSystem.Data());
   }

   if(optMCGenerator.CompareTo("") ==0){
      textGenerator 					= "";
   } else {
      textGenerator 					= optMCGenerator;
   }
   
   TString outputDirectory;
   if(optPeriod.CompareTo("") ==0 || optPeriod.CompareTo("All") ==0){
      if (textGenerator.CompareTo("")!=0){
         outputDirectory 				= Form("%s/%s_%s/%s/%s/PhotonQA",textGenerator.Data(),QAcutSelection.Data(),cutSelection.Data(),optEnergy.Data(),suffix.Data());
      } else {
         textPeriod 					= "";
         outputDirectory 				= Form("%s_%s/%s/%s/PhotonQA",QAcutSelection.Data(),cutSelection.Data(),optEnergy.Data(),suffix.Data());
      }
      gSystem->Exec("mkdir -p "+outputDirectory);
   } else if (textGenerator.CompareTo("")!=0){
      textPeriod 						= optPeriod;
      if (optPeriod.CompareTo("LHC12abcd") == 0) 
		textPeriod 						= "LHC12[a-d]";
	  outputDirectory 					= Form("%s/%s/%s/%s/%s/PhotonQA",textGenerator.Data(),cutSelection.Data(),optEnergy.Data(),suffix.Data(),optPeriod.Data());
      gSystem->Exec("mkdir -p "+outputDirectory);
   } else {
      textPeriod 						= optPeriod;
	  if (optPeriod.CompareTo("LHC12abcd") == 0) 
		textPeriod 						= "LHC12[a-d]";
      outputDirectory 					= Form("%s/%s/%s/%s/PhotonQA",cutSelection.Data(),optEnergy.Data(),suffix.Data(),optPeriod.Data());
      gSystem->Exec("mkdir -p "+outputDirectory);
   }
   
   //Array defintion for printing Logo in right upper corner
   
   Float_t floatLocationRightUp2D[4] 	= {0.6,0.95,0.035, 0.02};
   Float_t floatLocationLeft[4] 		= {0.2,0.95,0.035, 0.02};
   if( optEnergy.Contains("PbPb")) {
      floatLocationRightUp2D[0]			= 0.43;
      cout << floatLocationRightUp2D[0] << endl;
   }
   if( optEnergy.Contains("pPb") ) {
      floatLocationRightUp2D[0]			= 0.43;
   }
   
   TString textStandardYAxis 			= "#frac{d#it{N}_{#gamma}}{#it{N}_{ch}}";
   TString textYAxisEtaElec 			= "#frac{d#it{N}_{e^{-}}}{#it{N}_{e^{-}} d#eta}";
   TString textYAxisEtaPos 				= "#frac{d#it{N}_{e^{+}}}{#it{N}_{e^{+}} d#eta}";
   TString textYAxisITSClvsR 			= "#frac{d#it{N}_{e^{-}}}{#it{N}_{e^{-}} d#it{R}}";
   TString textYAxisEtaGamma 			= "#frac{d#it{N}_{#gamma}}{#it{N}_{#gamma} d#eta}";
   TString textYAxisPtDist 				= "#frac{d#it{N}_{#gamma}}{#it{N}_{#gamma} d#it{p}_{T}} (GeV/#it{c})^{-1}";
   TString textYAxisPtDistE 			= "#frac{d#it{N}_{e^{-}}}{#it{N}_{e^{-}} d#it{p}_{T}} (GeV/#it{c})^{-1}";
   TString textYAxisPtDistP 			= "#frac{d#it{N}_{e^{+}}}{#it{N}_{e^{+}} d#it{p}_{T}} (GeV/#it{c})^{-1}";
   TString textYAxisChi2 				= "#frac{d#it{N}_{#gamma}}{#it{N}_{#gamma} d#chi^{2}}";
   TString textYAxisPsiPair 			= "#frac{d#it{N}_{#gamma}}{#it{N}_{#gamma} d#psi_{pair}}";
   TString textYAxisPhi 				= "#frac{d#it{N}_{#gamma}}{#it{N}_{#gamma} d#phi}";
   TString textYAxisCosPoint 			= "#frac{d#it{N}_{#gamma}}{#it{N}_{#gamma} dcos(#theta_{point})}";
   TString textYAxisMEP 				= "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d#it{M}_{e^{+}e^{-}}} (GeV/#it{c}^{2})^{-1}";
   TString textYAxisMGG 				= "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d#it{M}_{#gamma#gamma} } (GeV/#it{c}^{2})^{-1}";
   TString textYAxisAlpha 				= "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d#alpha}";
   TString textYAxisPoint 				= "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d cos(#theta_{pointing})}";
   TString textYAxisDCA 				= "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d DCA} (cm^{-1})";
   TString textYAxisNDCA 				= "#frac{1}{#it{N}_{ch}} #frac{d#it{N}_{#gamma}}{d DCA/#sigma}";
   TString textYAxisLike 				= "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d Likelyhood}";
   TString textYAxisInvMass 			= "#frac{d#it{N}_{#gamma}}{#it{N}_{ch} d#it{M}_{e^{+}e^{-}}} (GeV/#it{c}^{2})^{-1}";
   textDate 							= ReturnDateString();

   TLatex *latexScaling 				= new TLatex(0.6,0.5,"MC scaled to mean of Data"); // Bo: this was modified
   latexScaling->SetNDC();
   latexScaling->SetTextColor(2);
   latexScaling->SetTextFont(42);
   latexScaling->SetTextSize(0.03);
   latexScaling->SetLineWidth(2);   
   
   TString nameGammaDirectory 			= Form("GammaConv_%s_%s",  QAcutSelection.Data(), cutSelection.Data());
   cout << "data: " << nameGammaDirectory.Data() << endl;

   TString nameGammaDirectoryMC 		= Form("GammaConv_%s_%s",  QAcutSelection.Data(), cutSelectionMC.Data());
   cout << "MC: " << nameGammaDirectoryMC.Data() << endl;


//    Float_t floatLineWidth = 1;
   
   // ---------------------------- LOAD ALL FILES ---------------------------------------------------
   TFile    fileData(data.Data());  
   //for new versions
   TDirectory* directoryPhotonQAData 			= new TDirectory(); // definition of first folder / list   
   directoryPhotonQAData 						= (TDirectory*)fileData.Get(nameGammaDirectory.Data()) ;

   TH3F* hist3DElectronDEdxEtaPData 			= (TH3F*)directoryPhotonQAData->Get("histoElectrondEdxEtaP"); 
   Double_t nElectronsData 						= hist3DElectronDEdxEtaPData->GetEntries();  
   TH2D*  histoDataElectrondEdxP 				= (TH2D*)hist3DElectronDEdxEtaPData->Project3D("xz");
   histoDataElectrondEdxP->SetName("histoDataElectrondEdxP");
   histoDataElectrondEdxP->Scale(1./nElectronsData);
   if (histoDataElectrondEdxP->GetEntries() > 0){
      PlotStandard2D( histoDataElectrondEdxP , Form("%s/dEdxTPC_Electron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "d#it{E}_{e^{-}-cand} /d#it{x} TPC",
					  kTRUE, 30., 180., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);
   }
   delete histoDataElectrondEdxP;
   delete hist3DElectronDEdxEtaPData;
   
   TH3F* hist3DElectronSigmaDEdxEtaPData 	= (TH3F*)directoryPhotonQAData->Get("histoElectronNSigmadEdxEtaP"); 
   TH2D*  histoDataElectronSigmadEdxP 		= (TH2D*)hist3DElectronSigmaDEdxEtaPData->Project3D("xz");
   histoDataElectronSigmadEdxP->SetName("histoDataElectronSigmadEdxP");
   histoDataElectronSigmadEdxP->Scale(1./nElectronsData);
   if (histoDataElectronSigmadEdxP->GetEntries() > 0){
      PlotStandard2D( histoDataElectronSigmadEdxP , Form("%s/nSigma_dEdxTPC_Electron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{n} #sigma_{e^{-}} d#it{E}/d#it{x} TPC", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod,"dEdx");   
   }
   delete histoDataElectronSigmadEdxP;
   delete hist3DElectronSigmaDEdxEtaPData;

   TH3F* hist3DElectronDEdxITSEtaPData 		= (TH3F*)directoryPhotonQAData->Get("histoElectronITSdEdxEtaP"); 
   TH2D*  histoDataElectrondEdxITSP 			= (TH2D*)hist3DElectronDEdxITSEtaPData->Project3D("xz");
   histoDataElectrondEdxITSP->SetName("histoDataElectrondEdxITSP");
   histoDataElectrondEdxITSP->Scale(1./nElectronsData);
   if (histoDataElectrondEdxITSP->GetEntries() > 0){
      PlotStandard2D( histoDataElectrondEdxITSP , Form("%s/dEdxITS_Electron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "d#it{E}_{e^{-}-cand} /d#it{x} ITS", 
					  kTRUE, 30., 180., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);
   }
   delete histoDataElectrondEdxITSP;
   delete hist3DElectronDEdxITSEtaPData;
   
   TH3F* hist3DElectronSigmaDEdxITSEtaPData 	= (TH3F*)directoryPhotonQAData->Get("histoElectronNSigmaITSEtaP"); 
   TH2D*  histoDataElectronSigmadEdxITSP 		= (TH2D*)hist3DElectronSigmaDEdxITSEtaPData->Project3D("xz");
   histoDataElectronSigmadEdxITSP->SetName("histoDataElectronSigmadEdxITSP");
   histoDataElectronSigmadEdxITSP->Scale(1./nElectronsData);
   if (histoDataElectronSigmadEdxITSP->GetEntries() > 0){
      PlotStandard2D( histoDataElectronSigmadEdxITSP , Form("%s/nSigma_dEdxITS_Electron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{n} #sigma_{e^{-}} d#it{E}/d#it{x} ITS", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);   
   }
   delete histoDataElectronSigmadEdxITSP;
   delete hist3DElectronSigmaDEdxITSEtaPData;

   
   TH3F* hist3DElectronTOFEtaPData 			= (TH3F*)directoryPhotonQAData->Get("histoElectronTOFEtaP");     
   TH2D*  histoDataElectronTOFP 				= (TH2D*)hist3DElectronTOFEtaPData->Project3D("xz");
   histoDataElectronTOFP->SetName("histoDataElectronTOFP");
   histoDataElectronTOFP->Scale(1./nElectronsData);
   if (histoDataElectronTOFP->GetEntries() > 0){
      PlotStandard2D( histoDataElectronTOFP , Form("%s/TOF_Electron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{t}_{measured}-#it{t}_{expected} e^{-}", 
					  kTRUE, -1000., 2500, kTRUE, 0.2, 15., 1, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);
   }
   delete histoDataElectronTOFP;
   delete hist3DElectronTOFEtaPData;

   TH3F* hist3DElectronSigmaTOFEtaPData 		= (TH3F*)directoryPhotonQAData->Get("histoElectronNSigmaTOFEtaP");  
   TH2D*  histoDataElectronSigmaTOFP 			= (TH2D*)hist3DElectronSigmaTOFEtaPData->Project3D("xz");
   histoDataElectronSigmaTOFP->SetName("histoDataElectronSigmaTOFP");
   histoDataElectronSigmaTOFP->Scale(1./nElectronsData);
   if (histoDataElectronSigmaTOFP->GetEntries() > 0){
      PlotStandard2D( histoDataElectronSigmaTOFP , Form("%s/nSigma_TOF_Electron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{n} #sigma_{e^{-}} TOF", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);   
   }
   delete histoDataElectronSigmaTOFP;
   delete hist3DElectronSigmaTOFEtaPData;

   TH3F* hist3DPositronDEdxEtaPData 			= (TH3F*)directoryPhotonQAData->Get("histoPositrondEdxEtaP"); 
   Double_t nPositronsData	 					= hist3DPositronDEdxEtaPData->GetEntries();
   TH2D*  histoDataPositrondEdxP 				= (TH2D*)hist3DPositronDEdxEtaPData->Project3D("xz");
   histoDataPositrondEdxP->SetName("histoDataPositrondEdxP");
   histoDataPositrondEdxP->Scale(1./nPositronsData);
   if (histoDataPositrondEdxP->GetEntries() > 0){
      PlotStandard2D( histoDataPositrondEdxP , Form("%s/dEdxTPC_Positron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{+}} (GeV/#it{c})", "d#it{E}_{e^{+}-cand} /d#it{x} TPC",
					  kTRUE, 30., 180., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);
   }
   delete histoDataPositrondEdxP;
   delete hist3DPositronDEdxEtaPData;

   
   TH3F* hist3DPositronSigmaDEdxEtaPData 	= (TH3F*)directoryPhotonQAData->Get("histoPositronNSigmadEdxEtaP"); 
   TH2D*  histoDataPositronSigmadEdxP 		= (TH2D*)hist3DPositronSigmaDEdxEtaPData->Project3D("xz");
   histoDataPositronSigmadEdxP->SetName("histoDataPositronSigmadEdxP");
   histoDataPositronSigmadEdxP->Scale(1./nPositronsData);
   hist3DPositronSigmaDEdxEtaPData->GetYaxis()->SetRange(hist3DPositronSigmaDEdxEtaPData->GetYaxis()->FindBin(-0.2),hist3DPositronSigmaDEdxEtaPData->GetYaxis()->FindBin(0.2));
   if (histoDataPositronSigmadEdxP->GetEntries() > 0){
      PlotStandard2D( histoDataPositronSigmadEdxP , Form("%s/nSigma_dEdxTPC_Positron_Data.%s", outputDirectory.Data(), suffix.Data()),
					  "", "#it{p}_{e^{+}} (GeV/#it{c})", "#it{n} #sigma_{e^{+}} d#it{E}/d#it{x} TPC", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod,"dEdx");   
   }
   delete histoDataPositronSigmadEdxP;
   delete hist3DPositronSigmaDEdxEtaPData;

   
   TH3F* hist3DPositronDEdxITSEtaPData 		= (TH3F*)directoryPhotonQAData->Get("histoPositronITSdEdxEtaP"); 
   TH2D*  histoDataPositrondEdxITSP 			= (TH2D*)hist3DPositronDEdxITSEtaPData->Project3D("xz");
   histoDataPositrondEdxITSP->SetName("histoDataPositrondEdxITSP");
   histoDataPositrondEdxITSP->Scale(1./nPositronsData);
   if (histoDataPositrondEdxITSP->GetEntries() > 0){
      PlotStandard2D( histoDataPositrondEdxITSP , Form("%s/dEdxITS_Positron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "d#it{E}_{e^{-}-cand} /d#it{x} ITS", 
					  kTRUE, 30., 180., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);
   }
   delete histoDataPositrondEdxITSP;
   delete hist3DPositronDEdxITSEtaPData;
   
   TH3F* hist3DPositronSigmaDEdxITSEtaPData 	= (TH3F*)directoryPhotonQAData->Get("histoPositronNSigmaITSEtaP"); 
   TH2D*  histoDataPositronSigmadEdxITSP 		= (TH2D*)hist3DPositronSigmaDEdxITSEtaPData->Project3D("xz");
   histoDataPositronSigmadEdxITSP->SetName("histoDataPositronSigmadEdxITSP");
   histoDataPositronSigmadEdxITSP->Scale(1./nPositronsData);
   if (histoDataPositronSigmadEdxITSP->GetEntries() > 0){
      PlotStandard2D( histoDataPositronSigmadEdxITSP , Form("%s/nSigma_dEdxITS_Positron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{n} #sigma_{e^{-}} d#it{E}/d#it{x} ITS", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);   
   }
   delete histoDataPositronSigmadEdxITSP;
   delete hist3DPositronSigmaDEdxITSEtaPData;

   
   TH3F* hist3DPositronTOFEtaPData 			= (TH3F*)directoryPhotonQAData->Get("histoPositronTOFEtaP");  
   TH2D*  histoDataPositronTOFP 				= (TH2D*)hist3DPositronTOFEtaPData->Project3D("xz");
   histoDataPositronTOFP->SetName("histoDataPositronTOFP");
   histoDataPositronTOFP->Scale(1./nPositronsData);
   if (histoDataPositronTOFP->GetEntries() > 0){ 
      PlotStandard2D( histoDataPositronTOFP , Form("%s/TOF_Positron_Data.%s", outputDirectory.Data(), suffix.Data()),
					  "", "#it{p}_{e^{+}} (GeV/#it{c})", "#it{t}_{measured}-#it{t}_{expected} e^{+}", 
					  kTRUE,  -1000., 2500, kTRUE, 0.2, 15., 1,0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);
   }
   delete histoDataPositronTOFP;
   delete hist3DPositronTOFEtaPData;

   TH3F* hist3DPositronSigmaTOFEtaPData 		= (TH3F*)directoryPhotonQAData->Get("histoPositronNSigmaTOFEtaP");  
   TH2D*  histoDataPositronSigmaTOFP 			= (TH2D*)hist3DPositronSigmaTOFEtaPData->Project3D("xz");
   histoDataPositronSigmaTOFP->SetName("histoDataPositronSigmaTOFP");
   histoDataPositronSigmaTOFP->Scale(1./nPositronsData);
   if (histoDataPositronSigmaTOFP->GetEntries() > 0){  
      PlotStandard2D( histoDataPositronSigmaTOFP , Form("%s/nSigma_TOF_Positron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{+}} (GeV/#it{c})", "#it{n} #sigma_{e^{+}} TOF", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod); 
   }
   delete histoDataPositronSigmaTOFP;
   delete hist3DPositronSigmaTOFEtaPData;
   
   TH2F* histoDataGammaAlphaQtData 			= (TH2F*)directoryPhotonQAData->Get("histoGammaAlphaQt");  
   cout << "number of gammas data " <<  histoDataGammaAlphaQtData->GetEntries()<< endl;
   Double_t nGammasData 						= histoDataGammaAlphaQtData->GetEntries();
   histoDataGammaAlphaQtData->Scale(1./nGammasData);
   histoDataGammaAlphaQtData->SetMaximum(2e-3);
   histoDataGammaAlphaQtData->SetMinimum(1e-8);
   PlotStandard2D( histoDataGammaAlphaQtData , Form("%s/Armenteros_Data.%s", outputDirectory.Data(), suffix.Data()), 
				   "", "#alpha = (#it{p}^{+}_{L}-#it{p}^{-}_{L})/(#it{p}^{+}_{L}+#it{p}^{-}_{L})", "#it{q}_{T} (GeV/#it{c})",  
				   kFALSE, 30., 100.,kTRUE, -1., 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod,"Armenteros");   
   delete histoDataGammaAlphaQtData;
   
   //------------------------------- SECOND FILE ------------------------------
   TDirectory* directoryPhotonQAMonteCarlo 		= new TDirectory(); // definition of first folder / list   
   TFile*   fileMonteCarlo 						= new TFile(Form("%s", optMC.Data()));

      // ---------------------------- LOAD ALL FILES ---------------------------------------------------
   directoryPhotonQAMonteCarlo 					= (TDirectory*)fileMonteCarlo->Get(nameGammaDirectoryMC.Data()) ;
         cout << "here" << endl;
   TH3F* hist3DElectronDEdxEtaPMonteCarlo 		= (TH3F*)directoryPhotonQAMonteCarlo->Get("histoElectrondEdxEtaP"); 
   Double_t nElectronsMonteCarlo 				= hist3DElectronDEdxEtaPMonteCarlo->GetEntries();  
   TH2D*  histoMonteCarloElectrondEdxP 			= (TH2D*)hist3DElectronDEdxEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloElectrondEdxP->SetName("histoMonteCarloElectrondEdxP");
   histoMonteCarloElectrondEdxP->Scale(1./nElectronsMonteCarlo);
   if (histoMonteCarloElectrondEdxP->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloElectrondEdxP , Form("%s/dEdxTPC_Electron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "d#it{E}_{e^{-}-cand} /d#it{x} TPC", 
					  kTRUE, 30., 180., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);
   }
   delete histoMonteCarloElectrondEdxP;
   delete hist3DElectronDEdxEtaPMonteCarlo;
   
   TH3F* hist3DElectronSigmaDEdxEtaPMonteCarlo 	= (TH3F*)directoryPhotonQAMonteCarlo->Get("histoElectronNSigmadEdxEtaP"); 
   TH2D*  histoMonteCarloElectronSigmadEdxP 	= (TH2D*)hist3DElectronSigmaDEdxEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloElectronSigmadEdxP->SetName("histoMonteCarloElectronSigmadEdxP");
   histoMonteCarloElectronSigmadEdxP->Scale(1./nElectronsMonteCarlo);
   if (histoMonteCarloElectronSigmadEdxP->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloElectronSigmadEdxP , Form("%s/nSigma_dEdxTPC_Electron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{n} #sigma_{e^{-}} d#it{E}/d#it{x} TPC", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "dEdx");   
   }
   delete histoMonteCarloElectronSigmadEdxP;
   delete hist3DElectronSigmaDEdxEtaPMonteCarlo;

   TH3F* hist3DElectronDEdxITSEtaPMonteCarlo	= (TH3F*)directoryPhotonQAMonteCarlo->Get("histoElectronITSdEdxEtaP"); 
   TH2D*  histoMonteCarloElectrondEdxITSP 		= (TH2D*)hist3DElectronDEdxITSEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloElectrondEdxITSP->SetName("histoMonteCarloElectrondEdxITSP");
   histoMonteCarloElectrondEdxITSP->Scale(1./nElectronsMonteCarlo);
   if (histoMonteCarloElectrondEdxITSP->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloElectrondEdxITSP , Form("%s/dEdxITS_Electron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "d#it{E}_{e^{-}-cand} /d#it{x} ITS", 
					  kTRUE, 30., 180., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);
   }
   delete histoMonteCarloElectrondEdxITSP;
   delete hist3DElectronDEdxITSEtaPMonteCarlo;
   
   TH3F* hist3DElectronSigmaDEdxITSEtaPMonteCarlo =  (TH3F*)directoryPhotonQAMonteCarlo->Get("histoElectronNSigmaITSEtaP"); 
         cout << "here" << endl;
   TH2D*  histoMonteCarloElectronSigmadEdxITSP 	= (TH2D*)hist3DElectronSigmaDEdxITSEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloElectronSigmadEdxITSP->SetName("histoMonteCarloElectronSigmadEdxITSP");
   histoMonteCarloElectronSigmadEdxITSP->Scale(1./nElectronsMonteCarlo);
   if (histoMonteCarloElectronSigmadEdxITSP->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloElectronSigmadEdxITSP , Form("%s/nSigma_dEdxITS_Electron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{n} #sigma_{e^{-}} d#it{E}/d#it{x} ITS", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);   
   }
   delete histoMonteCarloElectronSigmadEdxITSP;
   delete hist3DElectronSigmaDEdxITSEtaPMonteCarlo;

   
   TH3F* hist3DElectronTOFEtaPMonteCarlo 		= (TH3F*)directoryPhotonQAMonteCarlo->Get("histoElectronTOFEtaP");     
   TH2D*  histoMonteCarloElectronTOFP 			= (TH2D*)hist3DElectronTOFEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloElectronTOFP->SetName("histoMonteCarloElectronTOFP");
   histoMonteCarloElectronTOFP->Scale(1./nElectronsMonteCarlo);
   if (histoMonteCarloElectronTOFP->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloElectronTOFP , Form("%s/TOF_Electron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()),
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{t}_{measured}-#it{t}_{expected} e^{-}", 
					  kTRUE, -1000., 2500, kTRUE, 0.2, 15., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);
   }
   delete histoMonteCarloElectronTOFP;
   delete hist3DElectronTOFEtaPMonteCarlo;
      cout << "here" << endl;
   TH3F* hist3DElectronSigmaTOFEtaPMonteCarlo 	= (TH3F*)directoryPhotonQAMonteCarlo->Get("histoElectronNSigmaTOFEtaP");  
   TH2D*  histoMonteCarloElectronSigmaTOFP 		= (TH2D*)hist3DElectronSigmaTOFEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloElectronSigmaTOFP->SetName("histoMonteCarloElectronSigmaTOFP");
   histoMonteCarloElectronSigmaTOFP->Scale(1./nElectronsMonteCarlo);
   if (histoMonteCarloElectronSigmaTOFP->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloElectronSigmaTOFP , Form("%s/nSigma_TOF_Electron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{n} #sigma_{e^{-}} TOF", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);   
   }
   delete histoMonteCarloElectronSigmaTOFP;
   delete hist3DElectronSigmaTOFEtaPMonteCarlo;

   TH3F* hist3DPositronDEdxEtaPMonteCarlo 		= (TH3F*)directoryPhotonQAMonteCarlo->Get("histoPositrondEdxEtaP"); 
   Double_t nPositronsMonteCarlo 				= hist3DPositronDEdxEtaPMonteCarlo->GetEntries();
   TH2D*  histoMonteCarloPositrondEdxP 			= (TH2D*)hist3DPositronDEdxEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloPositrondEdxP->SetName("histoMonteCarloPositrondEdxP");
   histoMonteCarloPositrondEdxP->Scale(1./nPositronsMonteCarlo);
   if (histoMonteCarloPositrondEdxP->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloPositrondEdxP , Form("%s/dEdxTPC_Positron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{+}} (GeV/#it{c})", "d#it{E}_{e^{+}-cand} /d#it{x} TPC", 
					  kTRUE, 30., 180., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);
   }
   delete histoMonteCarloPositrondEdxP;
   delete hist3DPositronDEdxEtaPMonteCarlo;
      cout << "here" << endl;
   
   TH3F* hist3DPositronSigmaDEdxEtaPMonteCarlo 	= (TH3F*)directoryPhotonQAMonteCarlo->Get("histoPositronNSigmadEdxEtaP"); 
   TH2D*  histoMonteCarloPositronSigmadEdxP 	= (TH2D*)hist3DPositronSigmaDEdxEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloPositronSigmadEdxP->SetName("histoMonteCarloPositronSigmadEdxP");
   histoMonteCarloPositronSigmadEdxP->Scale(1./nPositronsMonteCarlo);
   hist3DPositronSigmaDEdxEtaPMonteCarlo->GetYaxis()->SetRange(hist3DPositronSigmaDEdxEtaPMonteCarlo->GetYaxis()->FindBin(-0.2),hist3DPositronSigmaDEdxEtaPMonteCarlo->GetYaxis()->FindBin(0.2));
   if (histoMonteCarloPositronSigmadEdxP->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloPositronSigmadEdxP , Form("%s/nSigma_dEdxTPC_Positron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()),
					  "", "#it{p}_{e^{+}} (GeV/#it{c})", "#it{n} #sigma_{e^{+}} d#it{E}/d#it{x} TPC", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod,"dEdx");   
   }
   delete histoMonteCarloPositronSigmadEdxP;
   delete hist3DPositronSigmaDEdxEtaPMonteCarlo;

   
   TH3F* hist3DPositronDEdxITSEtaPMonteCarlo 	= (TH3F*)directoryPhotonQAMonteCarlo->Get("histoPositronITSdEdxEtaP"); 
   TH2D*  histoMonteCarloPositrondEdxITSP 		= (TH2D*)hist3DPositronDEdxITSEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloPositrondEdxITSP->SetName("histoMonteCarloPositrondEdxITSP");
   histoMonteCarloPositrondEdxITSP->Scale(1./nPositronsMonteCarlo);
   if (histoMonteCarloPositrondEdxITSP->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloPositrondEdxITSP , Form("%s/dEdxITS_Positron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "d#it{E}_{e^{-}-cand} /d#it{x} ITS",   
					  kTRUE, 30., 180., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);
   }
   delete histoMonteCarloPositrondEdxITSP;
   delete hist3DPositronDEdxITSEtaPMonteCarlo;
   
   TH3F* hist3DPositronSigmaDEdxITSEtaPMonteCarlo =  (TH3F*)directoryPhotonQAMonteCarlo->Get("histoPositronNSigmaITSEtaP"); 
   TH2D*  histoMonteCarloPositronSigmadEdxITSP 	= (TH2D*)hist3DPositronSigmaDEdxITSEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloPositronSigmadEdxITSP->SetName("histoMonteCarloPositronSigmadEdxITSP");
   histoMonteCarloPositronSigmadEdxITSP->Scale(1./nPositronsMonteCarlo);
   if (histoMonteCarloPositronSigmadEdxITSP->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloPositronSigmadEdxITSP , Form("%s/nSigma_dEdxITS_Positron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{n} #sigma_{e^{-}} d#it{E}/d#it{x} ITS", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);   
   }
   delete histoMonteCarloPositronSigmadEdxITSP;
   delete hist3DPositronSigmaDEdxITSEtaPMonteCarlo;

   
   TH3F* hist3DPositronTOFEtaPMonteCarlo 		= (TH3F*)directoryPhotonQAMonteCarlo->Get("histoPositronTOFEtaP");  
   TH2D*  histoMonteCarloPositronTOFP 			= (TH2D*)hist3DPositronTOFEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloPositronTOFP->SetName("histoMonteCarloPositronTOFP");
   histoMonteCarloPositronTOFP->Scale(1./nPositronsMonteCarlo);
   if (histoMonteCarloPositronTOFP->GetEntries() > 0){ 
      PlotStandard2D( histoMonteCarloPositronTOFP , Form("%s/TOF_Positron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{+}} (GeV/#it{c})", "#it{t}_{measured}-#it{t}_{expected} e^{+}", 
					  kTRUE, -1000., 2500, kTRUE, 0.2, 15., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);
   }
   delete histoMonteCarloPositronTOFP;
   delete hist3DPositronTOFEtaPMonteCarlo;
      cout << "here" << endl;
   TH3F* hist3DPositronSigmaTOFEtaPMonteCarlo 	= (TH3F*)directoryPhotonQAMonteCarlo->Get("histoPositronNSigmaTOFEtaP");  
   TH2D*  histoMonteCarloPositronSigmaTOFP 		= (TH2D*)hist3DPositronSigmaTOFEtaPMonteCarlo->Project3D("xz");
   histoMonteCarloPositronSigmaTOFP->SetName("histoMonteCarloPositronSigmaTOFP");
   histoMonteCarloPositronSigmaTOFP->Scale(1./nPositronsMonteCarlo);
   if (histoMonteCarloPositronSigmaTOFP->GetEntries() > 0){  
      PlotStandard2D( histoMonteCarloPositronSigmaTOFP , Form("%s/nSigma_TOF_Positron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{+}} (GeV/#it{c})", "#it{n} #sigma_{e^{+}} TOF", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoMonteCarloPositronSigmaTOFP;
   delete hist3DPositronSigmaTOFEtaPMonteCarlo;
      cout << "here" << endl;
   TH2F* histoMonteCarloGammaAlphaQtMonteCarlo 				= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaAlphaQt");  
   TH2F* histoMonteCarloTruePrimGammaAlphaQtMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTruePrimGammaAlphaQt");  
   TH2F* histoMonteCarloTrueSecGammaAlphaQtMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueSecGammaAlphaQt");  
   TH2F* histoMonteCarloTrueDalitzGammaAlphaQtMonteCarlo 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueDalitzGammaAlphaQt");  
   TH2F* histoMonteCarloBGAlphaQtMonteCarlo 				= (TH2F*)histoMonteCarloGammaAlphaQtMonteCarlo->Clone("histoMonteCarloBGAlphaQtMonteCarlo");  
   histoMonteCarloBGAlphaQtMonteCarlo->Sumw2();
   histoMonteCarloBGAlphaQtMonteCarlo->Add(histoMonteCarloTruePrimGammaAlphaQtMonteCarlo,-1);
   histoMonteCarloBGAlphaQtMonteCarlo->Add(histoMonteCarloTrueSecGammaAlphaQtMonteCarlo,-1);
   histoMonteCarloBGAlphaQtMonteCarlo->Add(histoMonteCarloTrueDalitzGammaAlphaQtMonteCarlo,-1);
   cout << "here" << endl;
   cout << "number of gammas MC " <<  histoMonteCarloGammaAlphaQtMonteCarlo->GetEntries()<< endl;
   Double_t nGammasMonteCarlo 								= histoMonteCarloGammaAlphaQtMonteCarlo->GetEntries();
   histoMonteCarloGammaAlphaQtMonteCarlo->Scale(1/nGammasMonteCarlo);
   histoMonteCarloGammaAlphaQtMonteCarlo->SetMaximum(2e-3);
   histoMonteCarloGammaAlphaQtMonteCarlo->SetMinimum(1e-8);
   PlotStandard2D( histoMonteCarloGammaAlphaQtMonteCarlo , Form("%s/Armenteros_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
				   "", "#alpha = (#it{p}^{+}_{L}-#it{p}^{-}_{L})/(#it{p}^{+}_{L}+#it{p}^{-}_{L})", "#it{q}_{T} (GeV/#it{c})", 
				   kFALSE, 30., 100.,kTRUE, -1., 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Armenteros");  
   delete histoMonteCarloGammaAlphaQtMonteCarlo;
   
   histoMonteCarloTruePrimGammaAlphaQtMonteCarlo->Scale(1/nGammasMonteCarlo);
   histoMonteCarloTruePrimGammaAlphaQtMonteCarlo->SetMaximum(2e-3);
   histoMonteCarloTruePrimGammaAlphaQtMonteCarlo->SetMinimum(1e-8);
   PlotStandard2D( histoMonteCarloTruePrimGammaAlphaQtMonteCarlo , Form("%s/Armenteros_TruePrimGamma_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
				   "", "#alpha = (#it{p}^{+}_{L}-#it{p}^{-}_{L})/(#it{p}^{+}_{L}+#it{p}^{-}_{L})", "#it{q}_{T} (GeV/#it{c})",  
				   kFALSE, 30., 100., kTRUE, -1., 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Armenteros");  
   delete histoMonteCarloTruePrimGammaAlphaQtMonteCarlo;

   
   histoMonteCarloTrueSecGammaAlphaQtMonteCarlo->Scale(1/nGammasMonteCarlo);
   histoMonteCarloTrueSecGammaAlphaQtMonteCarlo->SetMaximum(2e-3);
   histoMonteCarloTrueSecGammaAlphaQtMonteCarlo->SetMinimum(1e-8);
   PlotStandard2D( histoMonteCarloTrueSecGammaAlphaQtMonteCarlo , Form("%s/Armenteros_TrueSecGamma_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()),
				   "", "#alpha = (#it{p}^{+}_{L}-#it{p}^{-}_{L})/(#it{p}^{+}_{L}+#it{p}^{-}_{L})", "#it{q}_{T} (GeV/#it{c})", 
				   kFALSE, 30., 100., kTRUE, -1., 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Armenteros");  
   delete histoMonteCarloTrueSecGammaAlphaQtMonteCarlo;

   
   histoMonteCarloTrueDalitzGammaAlphaQtMonteCarlo->Scale(1/nGammasMonteCarlo);
   histoMonteCarloTrueDalitzGammaAlphaQtMonteCarlo->SetMaximum(2e-3);
   histoMonteCarloTrueDalitzGammaAlphaQtMonteCarlo->SetMinimum(1e-8);
   PlotStandard2D( histoMonteCarloTrueDalitzGammaAlphaQtMonteCarlo , Form("%s/Armenteros_TrueDalitzGamma_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
				   "", "#alpha = (#it{p}^{+}_{L}-#it{p}^{-}_{L})/(#it{p}^{+}_{L}+#it{p}^{-}_{L})", "#it{q}_{T} (GeV/#it{c})",  
				   kFALSE, 30., 100.,kTRUE, -1., 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod,"Armenteros");  
   delete histoMonteCarloTrueDalitzGammaAlphaQtMonteCarlo;
   
   histoMonteCarloBGAlphaQtMonteCarlo->Scale(1/nGammasMonteCarlo);
   histoMonteCarloBGAlphaQtMonteCarlo->SetMaximum(2e-3);
   histoMonteCarloBGAlphaQtMonteCarlo->SetMinimum(1e-8);
   PlotStandard2D( histoMonteCarloBGAlphaQtMonteCarlo , Form("%s/Armenteros_BG_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
				   "", "#alpha = (#it{p}^{+}_{L}-#it{p}^{-}_{L})/(#it{p}^{+}_{L}+#it{p}^{-}_{L})", "#it{q}_{T} (GeV/#it{c})", 
				   kFALSE, 30., 100., kTRUE, -1., 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Armenteros");  
   delete histoMonteCarloBGAlphaQtMonteCarlo;
   
   
   TH2F* histoDataElectronFClPt 							= (TH2F*)directoryPhotonQAData->Get("histoElectronFClPt");
   TH1D* histoDataElectronFCL 								= (TH1D*)histoDataElectronFClPt->ProjectionX("histoDataElectronFCL");
   GammaScalingHistogramm(histoDataElectronFCL,1./nElectronsData);
   GammaScalingHistogramm(histoDataElectronFClPt,1./nElectronsData);
   
   TH2F* histoMonteCarloElectronFClPt 						= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoElectronFClPt");
   TH1D* histoMonteCarloElectronFCL 						= (TH1D*)histoMonteCarloElectronFClPt->ProjectionX("histoMonteCarloElectronFCL");
   GammaScalingHistogramm(histoMonteCarloElectronFCL,1./nElectronsMonteCarlo);
   GammaScalingHistogramm(histoMonteCarloElectronFClPt,1./nElectronsMonteCarlo);

   TH2F* histoDataPositronFClPt 							= (TH2F*)directoryPhotonQAData->Get("histoPositronFClPt");
   TH1D* histoDataPositronFCL 								= (TH1D*)histoDataPositronFClPt->ProjectionX("histoDataPositronFCL");
   GammaScalingHistogramm(histoDataPositronFCL,1./nPositronsData);
   GammaScalingHistogramm(histoDataPositronFClPt,1./nPositronsData);
   
   TH2F* histoMonteCarloPositronFClPt 						= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoPositronFClPt");
   TH1D* histoMonteCarloPositronFCL 						= (TH1D*)histoMonteCarloPositronFClPt->ProjectionX("histoMonteCarloPositronFCL");
   GammaScalingHistogramm(histoMonteCarloPositronFCL,1./nPositronsMonteCarlo);
   GammaScalingHistogramm(histoMonteCarloPositronFClPt,1./nPositronsMonteCarlo);


   TCanvas * canvasClustersFindProj = new TCanvas("canvasClustersFindProj","",10,10,2000,700);  // gives the page size
   TPad* padClustersFindProj = new TPad("padClustersFindProj","",0.0,0.0,1,1,0);   // gives the size of the histo areas 
   padClustersFindProj->SetFillColor(0);
   padClustersFindProj->GetFrame()->SetFillColor(0);
   padClustersFindProj->SetBorderMode(0);
   
   padClustersFindProj->Divide(2,1);
   padClustersFindProj->Draw();
   
   padClustersFindProj->cd(1);
   padClustersFindProj->cd(1)->SetLogy(1);
   DrawAutoGammaHistos( histoDataElectronFCL,
                  histoMonteCarloElectronFCL , 
                  "","TPC Clusters/Findable Clusters e^{-}","Counts 1/n_{e^{-}}", 
                  kTRUE, 4.,1e-6,
                  kFALSE,0. ,0., 
                  kFALSE, 0.,0.);
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   padClustersFindProj->cd(2);
   padClustersFindProj->cd(2)->SetLogy(1);
   DrawAutoGammaHistos( histoDataPositronFCL, 
                  histoMonteCarloPositronFCL ,
                  "","TPC Clusters/Findable Clusters e^{+}","Counts 1/n_{e^{+}}",
                  kTRUE, 4.,1e-6,
                  kFALSE,0. ,0.,
                  kFALSE, 0.,0.);
   canvasClustersFindProj->Update();
   canvasClustersFindProj->SaveAs(Form("%s/FindTPCClusters.%s", outputDirectory.Data(), suffix.Data()));
   delete padClustersFindProj;
   delete canvasClustersFindProj;      
   delete histoDataPositronFCL;
   delete histoDataElectronFCL;
   delete histoMonteCarloElectronFCL;
   delete histoMonteCarloPositronFCL;
   
   if (histoDataElectronFClPt->GetEntries() > 0){  
      PlotStandard2D( histoDataElectronFClPt , Form("%s/FindClusterTPC_Pt_Electron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "TPC Clusters/Findable Clusters e^{-}", "#it{p}_{T,e^{-}}", 
					  kTRUE, 0.003, 20, kFALSE, 0.0, 2.,0 , 1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);  
   }
   if (histoMonteCarloElectronFClPt->GetEntries() > 0){  
      PlotStandard2D( histoMonteCarloElectronFClPt , Form("%s/FindClusterTPC_Pt_Electron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "TPC Clusters/Findable Clusters e^{-}", "#it{p}_{T,e^{-}}", 
					  kTRUE, 0.003, 20, kFALSE, 0.0, 2.,0 , 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);   
   }
   if (histoDataPositronFClPt->GetEntries() > 0){  
      PlotStandard2D( histoDataPositronFClPt , Form("%s/FindClusterTPC_Pt_Positron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "TPC Clusters/Findable Clusters e^{+}", "#it{p}_{T,e^{+}}", 
					  kTRUE, 0.003, 20, kFALSE, 0.0, 2.,0, 1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);   
   }
   if (histoMonteCarloPositronFClPt->GetEntries() > 0){  
      PlotStandard2D( histoMonteCarloPositronFClPt , Form("%s/FindClusterTPC_Pt_Positron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "TPC Clusters/Findable Clusters e^{+}", "#it{p}_{T,e^{+}}", 
					  kTRUE,0.003, 20, kFALSE, 0.0, 2., 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoDataElectronFClPt;
   delete histoMonteCarloElectronFClPt;
   delete histoDataPositronFClPt;
   delete histoMonteCarloPositronFClPt;
   
   TH2F* histoDataElectronClPt 							= (TH2F*)directoryPhotonQAData->Get("histoElectronClPt"); 
   TH2F* histoMonteCarloElectronClPt 					= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoElectronClPt"); 
   TH2F* histoDataPositronClPt 							= (TH2F*)directoryPhotonQAData->Get("histoPositronClPt"); 
   TH2F* histoMonteCarloPositronClPt 					= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoPositronClPt"); 

   TH1D* histoDataElectronCl	 						= (TH1D*)histoDataElectronClPt->ProjectionX("histoDataElectronCl");
   TH1D* histoMonteCarloElectronCl 						= (TH1D*)histoMonteCarloElectronClPt->ProjectionX("histoMonteCarloElectronCl");
   TH1D* histoDataPositronCl 							= (TH1D*)histoDataPositronClPt->ProjectionX("histoDataPositronCl");
   TH1D* histoMonteCarloPositronCl 						= (TH1D*)histoMonteCarloPositronClPt->ProjectionX("histoMonteCarloPositronCl");
   
   GammaScalingHistogramm(histoDataElectronCl,1./nElectronsData);
   GammaScalingHistogramm(histoDataElectronClPt,1./nElectronsData);
   GammaScalingHistogramm(histoMonteCarloElectronCl,1./nElectronsMonteCarlo);
   GammaScalingHistogramm(histoMonteCarloElectronClPt,1./nElectronsMonteCarlo);

   GammaScalingHistogramm(histoDataPositronCl,1./nPositronsData);
   GammaScalingHistogramm(histoDataPositronClPt,1./nPositronsData);

   GammaScalingHistogramm(histoMonteCarloPositronCl,1./nPositronsMonteCarlo);
   GammaScalingHistogramm(histoMonteCarloPositronClPt,1./nPositronsMonteCarlo);
 
   TCanvas * canvasClustersProj = new TCanvas("canvasClustersProj","",10,10,2000,700);  // gives the page size
   TPad* padClustersProj = new TPad("padClustersProj","",0.0,0.0,1,1,0);   // gives the size of the histo areas 
   padClustersProj->SetFillColor(0);
   padClustersProj->GetFrame()->SetFillColor(0);
   padClustersProj->SetBorderMode(0);
   
   padClustersProj->Divide(2,1);
   padClustersProj->Draw();
   
   padClustersProj->cd(1);
   padClustersProj->cd(1)->SetLogy(1);
   DrawAutoGammaHistos( histoDataElectronCl,
                  histoMonteCarloElectronCl , 
                  "","TPC Clusters e^{-}","Counts 1/n_{e^{-}}", 
                  kTRUE, 4.,1e-6,
                  kFALSE,0. ,0., 
                  kFALSE, 0.,0.);
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   padClustersProj->cd(2);
   padClustersProj->cd(2)->SetLogy(1);
   DrawAutoGammaHistos( histoDataPositronCl, 
                  histoMonteCarloPositronCl ,
                  "","TPC Clusters e^{+}","Counts 1/n_{e^{+}}",
                  kTRUE, 4.,1e-6,
                  kFALSE,0. ,0.,
                  kFALSE, 0.,0.);
   canvasClustersProj->Update();
   canvasClustersProj->SaveAs(Form("%s/TPCClusters.%s", outputDirectory.Data(), suffix.Data()));
   delete padClustersProj;
   delete canvasClustersProj;      
   delete histoDataPositronCl;
   delete histoDataElectronCl;
   delete histoMonteCarloElectronCl;
   delete histoMonteCarloPositronCl;

   if (histoDataElectronClPt->GetEntries() > 0){ 
      PlotStandard2D( histoDataElectronClPt , Form("%s/Pt_ClusterTPC_Electron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "TPC Clusters e^{-}","#it{p}_{T} e^{-}", 
					  kFALSE, -0.9, 0.9, kFALSE, 0.0, 1.5, 0 ,1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);  
   }
   if (histoMonteCarloElectronClPt->GetEntries() > 0){ 
      PlotStandard2D( histoMonteCarloElectronClPt , Form("%s/Pt_ClusterTPC_Electron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "TPC Clusters e^{-}", "#it{p}_{T} e^{-}", 
					  kFALSE, -0.9, 0.9, kFALSE, 0.0, 1.5, 0 ,1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);  
   }
   if (histoDataPositronClPt->GetEntries() > 0){ 
      PlotStandard2D( histoDataPositronClPt , Form("%s/Pt_ClusterTPC_Positron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "TPC Clusters e^{+}","#it{p}_{T} e^{+}", 
					  kFALSE, -0.9, 0.9, kFALSE, 0.0, 1.5, 0 ,1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);  
   }
   if (histoMonteCarloPositronClPt->GetEntries() > 0){ 
      PlotStandard2D( histoMonteCarloPositronClPt , Form("%s/Pt_ClusterTPC_Positron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "TPC Clusters e^{+}","#it{p}_{T} e^{+}", 
					  kFALSE, -0.9, 0.9, kFALSE, 0.0, 1.5, 0 ,1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);  
   }

   delete histoDataElectronClPt;
   delete histoMonteCarloElectronClPt;
   delete histoDataPositronClPt;
   delete histoMonteCarloPositronClPt;

//    
   TH2F* histoDataGammaChi2NDFPt 							= (TH2F*)directoryPhotonQAData->Get("histoGammaChi2NDFPt");   
   TH2F* histoMonteCarloGammaChi2NDFPt 						= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaChi2NDFPt");   
   TH2F* histoMonteCarloTruePrimGammaChi2NDFPt 				= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTruePrimGammaChi2NDFPt");   
   TH2F* histoMonteCarloTrueSecGammaChi2NDFPt 				= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueSecGammaChi2NDFPt");   
   TH2F* histoMonteCarloTrueDalitzGammaChi2NDFPt 			= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueDalitzGammaChi2NDFPt");   
   TH2F* histoMonteCarloBGChi2NDFPt 						= (TH2F*)histoMonteCarloGammaChi2NDFPt->Clone("histoMonteCarloBGChi2NDFPt");
   histoMonteCarloBGChi2NDFPt->Sumw2();
   histoMonteCarloBGChi2NDFPt->Add(histoMonteCarloTruePrimGammaChi2NDFPt, -1.);
   histoMonteCarloBGChi2NDFPt->Add(histoMonteCarloTrueSecGammaChi2NDFPt, -1.);
   histoMonteCarloBGChi2NDFPt->Add(histoMonteCarloTrueDalitzGammaChi2NDFPt, -1.);
   TH1D* histoMonteCarloBGChi2 = (TH1D*)histoMonteCarloBGChi2NDFPt->ProjectionX("histoMonteCarloBGChi2");
   ConvGammaRebinWithBinCorrection(histoMonteCarloBGChi2,1);
   GammaScalingHistogramm(histoMonteCarloBGChi2,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoMonteCarloBGChi2NDFPt,1./nGammasMonteCarlo);
   
   TH1D* histoDataGammaChi2 = (TH1D*)histoDataGammaChi2NDFPt->ProjectionX("histoDataGammaChi2");
   TH1D* histoDataGammaChi2LowPt = (TH1D*)histoDataGammaChi2NDFPt->ProjectionX("histoDataGammaChi2LowPt",0,109);
   TH1D* histoDataGammaChi2HighPt = (TH1D*)histoDataGammaChi2NDFPt->ProjectionX("histoDataGammaChi2HighPt",110,203);
   TH1D* histoMonteCarloGammaChi2 = (TH1D*)histoMonteCarloGammaChi2NDFPt->ProjectionX("histoMonteCarloGammaChi2");
   TH1D* histoMonteCarloGammaChi2LowPt = (TH1D*)histoMonteCarloGammaChi2NDFPt->ProjectionX("histoMonteCarloGammaChi2LowPt",0,109);
   TH1D* histoMonteCarloGammaChi2HighPt = (TH1D*)histoMonteCarloGammaChi2NDFPt->ProjectionX("histoMonteCarloGammaChi2HighPt",110,203);
   ConvGammaRebinWithBinCorrection(histoDataGammaChi2,1);
   ConvGammaRebinWithBinCorrection(histoDataGammaChi2LowPt,1);
   ConvGammaRebinWithBinCorrection(histoDataGammaChi2HighPt,1);
   GammaScalingHistogramm(histoDataGammaChi2,1./nGammasData);
   GammaScalingHistogramm(histoDataGammaChi2LowPt,1./histoDataGammaChi2LowPt->GetEntries());
   GammaScalingHistogramm(histoDataGammaChi2HighPt,1./histoDataGammaChi2HighPt->GetEntries());
   GammaScalingHistogramm(histoDataGammaChi2NDFPt,1./nGammasData);
   ConvGammaRebinWithBinCorrection(histoMonteCarloGammaChi2,1);
   ConvGammaRebinWithBinCorrection(histoMonteCarloGammaChi2LowPt,1);
   ConvGammaRebinWithBinCorrection(histoMonteCarloGammaChi2HighPt,1);
   GammaScalingHistogramm(histoMonteCarloGammaChi2,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoMonteCarloGammaChi2LowPt,1./histoMonteCarloGammaChi2LowPt->GetEntries());
   GammaScalingHistogramm(histoMonteCarloGammaChi2HighPt,1./histoMonteCarloGammaChi2HighPt->GetEntries());
   GammaScalingHistogramm(histoMonteCarloGammaChi2NDFPt,1./nGammasMonteCarlo);   
   
   TH1D* histoMonteCarloTruePrimGammaChi2 = (TH1D*)histoMonteCarloTruePrimGammaChi2NDFPt->ProjectionX("histoMonteCarloTruePrimGammaChi2");
   ConvGammaRebinWithBinCorrection(histoMonteCarloTruePrimGammaChi2,1);
   GammaScalingHistogramm(histoMonteCarloTruePrimGammaChi2,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoMonteCarloTruePrimGammaChi2NDFPt,1./nGammasMonteCarlo);
   
   TH1D* histoMonteCarloTrueSecGammaChi2 = (TH1D*)histoMonteCarloTrueSecGammaChi2NDFPt->ProjectionX("histoMonteCarloTrueSecGammaChi2");
   ConvGammaRebinWithBinCorrection(histoMonteCarloTrueSecGammaChi2,1);
   GammaScalingHistogramm(histoMonteCarloTrueSecGammaChi2,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoMonteCarloTrueSecGammaChi2NDFPt,1./nGammasMonteCarlo);
   
   TH1D* histoMonteCarloTrueDalitzGammaChi2 = (TH1D*)histoMonteCarloTrueDalitzGammaChi2NDFPt->ProjectionX("histoMonteCarloTrueDalitzGammaChi2");
   ConvGammaRebinWithBinCorrection(histoMonteCarloTrueDalitzGammaChi2,1);
   GammaScalingHistogramm(histoMonteCarloTrueDalitzGammaChi2,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoMonteCarloTrueDalitzGammaChi2NDFPt,1./nGammasMonteCarlo);
   
   //-------------------------------------- Photon Chi2 ----------------------------------------------
   
   TCanvas * canvasChi2NDF = new TCanvas("canvasChi2NDF","",10,10,500,500);  // gives the page size
   canvasChi2NDF->SetLogy(1);
   canvasChi2NDF->SetLeftMargin(0.16);
   canvasChi2NDF->cd();
   DrawAutoGammaHistos( histoDataGammaChi2,
                  histoMonteCarloGammaChi2, 
                  "", "#chi^{2}_{#gamma}/ndf ",textYAxisChi2,
                  kTRUE, 2.5,1e-4,
                  kFALSE,0. ,0., 
                  kTRUE, 0.,40.);
   DrawGammaSetMarker(histoMonteCarloTruePrimGammaChi2,20,0.8, kBlue+2 , kBlue+2);
   histoMonteCarloTruePrimGammaChi2->Draw("histsame");
   DrawGammaSetMarker(histoMonteCarloTrueSecGammaChi2,20,0.8, kGreen+2 , kGreen+2);
   histoMonteCarloTrueSecGammaChi2->Draw("histsame");
   DrawGammaSetMarker(histoMonteCarloTrueDalitzGammaChi2,20,0.8, kOrange+2 , kOrange+2);
   histoMonteCarloTrueDalitzGammaChi2->Draw("histsame");
   DrawGammaSetMarker(histoMonteCarloBGChi2,20,0.8, kViolet , kViolet);
   histoMonteCarloBGChi2->Draw("histsame");
   
   
   
   TLegend* legAdditionalInfoChi2 = new TLegend( 0.65,0.78,0.97,0.97);
   legAdditionalInfoChi2->SetTextSize(0.03);         
   legAdditionalInfoChi2->SetFillColor(0);
   legAdditionalInfoChi2->AddEntry(histoDataGammaChi2,("Data"));
   legAdditionalInfoChi2->AddEntry(histoMonteCarloGammaChi2,("MC"));
   legAdditionalInfoChi2->AddEntry(histoMonteCarloTruePrimGammaChi2,("true prim #gamma"),"l");
   legAdditionalInfoChi2->AddEntry(histoMonteCarloTrueSecGammaChi2,("true sec #gamma"),"l");
   legAdditionalInfoChi2->AddEntry(histoMonteCarloTrueDalitzGammaChi2,("true dalitz"),"l");
   legAdditionalInfoChi2->AddEntry(histoMonteCarloBGChi2,("BG"),"l");
   legAdditionalInfoChi2->Draw();
   
   
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   
   canvasChi2NDF->Update();
   canvasChi2NDF->SaveAs(Form("%s/Photon_Chi2.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasChi2NDF;      
   delete histoDataGammaChi2;
   delete histoMonteCarloGammaChi2;

   //-------------------------------------- Photon Chi2 Low vs High Pt ----------------------------------------------
   
   TCanvas * canvasChi2NDFLowHighPt = new TCanvas("canvasChi2NDFLowHighPt","",10,10,500,500);  // gives the page size
   canvasChi2NDFLowHighPt->SetLogy(1);
   canvasChi2NDFLowHighPt->SetLeftMargin(0.16);
   canvasChi2NDFLowHighPt->cd();
   DrawAutoGammaHistos( histoDataGammaChi2LowPt,
                  histoMonteCarloGammaChi2LowPt, 
                  "", "#chi^{2}_{#gamma}/ndf ",textYAxisChi2,
                  kTRUE, 2.5,1e-4,
                  kFALSE,0. ,0., 
                  kTRUE, 0.,40.);
   DrawGammaSetMarker(histoDataGammaChi2LowPt,20,0.8, kBlack, kBlack);
   histoDataGammaChi2LowPt->Draw("same");
   DrawGammaSetMarker(histoMonteCarloGammaChi2LowPt,20,0.8, kRed , kRed);
   histoMonteCarloGammaChi2LowPt->Draw("same");
   DrawGammaSetMarker(histoDataGammaChi2HighPt,24,0.8, kBlack, kBlack);
   histoDataGammaChi2HighPt->Draw("same");
   DrawGammaSetMarker(histoMonteCarloGammaChi2HighPt,24,0.8, kRed , kRed);
   histoMonteCarloGammaChi2HighPt->Draw("same");
   
   TLegend* legLowHighPtChi2 = new TLegend( 0.65,0.78,0.97,0.97);
   legLowHighPtChi2->SetTextSize(0.03);         
   legLowHighPtChi2->SetFillColor(0);
   legLowHighPtChi2->AddEntry(histoDataGammaChi2LowPt,("Data p_{T} < 0.4 GeV/c"));
   legLowHighPtChi2->AddEntry(histoMonteCarloGammaChi2LowPt,("MC p_{T} < 0.4 GeV/c"));
   legLowHighPtChi2->AddEntry(histoDataGammaChi2HighPt,("Data p_{T} > 0.4 GeV/c"));
   legLowHighPtChi2->AddEntry(histoMonteCarloGammaChi2HighPt,("MC p_{T} > 0.4 GeV/c"));
   legLowHighPtChi2->Draw();
      
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   
   canvasChi2NDFLowHighPt->Update();
   canvasChi2NDFLowHighPt->SaveAs(Form("%s/Photon_Chi2_ProjInPt.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasChi2NDFLowHighPt;      
   delete histoDataGammaChi2LowPt;
   delete histoMonteCarloGammaChi2LowPt;
   delete histoDataGammaChi2HighPt;
   delete histoMonteCarloGammaChi2HighPt;
   
   
//    
   histoDataGammaChi2NDFPt->SetMaximum(2e-2);
   histoDataGammaChi2NDFPt->SetMinimum(2e-8);
   if (histoDataGammaChi2NDFPt->GetEntries() > 0){ 
      PlotStandard2D( histoDataGammaChi2NDFPt , Form("%s/Chi2NDF_Pt_Photon_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#chi^{2}_{#gamma}/ndf", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, 0.0, 30., 0 ,1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod,"Chi2"); 
   }
   histoMonteCarloGammaChi2NDFPt->SetMaximum(2e-2);
   histoMonteCarloGammaChi2NDFPt->SetMinimum(2e-8);
   if (histoMonteCarloGammaChi2NDFPt->GetEntries() > 0){ 
      PlotStandard2D( histoMonteCarloGammaChi2NDFPt , Form("%s/Chi2NDF_Pt_Photon_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#chi^{2}_{#gamma}/ndf", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, 0.0, 30., 0 ,1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Chi2"); 
   }
   histoMonteCarloTrueDalitzGammaChi2NDFPt->SetMaximum(2e-2);
   histoMonteCarloTrueDalitzGammaChi2NDFPt->SetMinimum(2e-8);
   if (histoMonteCarloTrueDalitzGammaChi2NDFPt->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloTrueDalitzGammaChi2NDFPt , Form("%s/Chi2NDF_Pt_TrueDalitz_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()),
					  "", "#chi^{2}_{#gamma}/ndf", "#it{p}_{T,#gamma}", 
					  kTRUE, 0.1, 20, kTRUE, 0.0, 30., 0 ,1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Chi2"); 
   }
   histoMonteCarloTruePrimGammaChi2NDFPt->SetMaximum(2e-2);
   histoMonteCarloTruePrimGammaChi2NDFPt->SetMinimum(2e-8);
   if (histoMonteCarloTruePrimGammaChi2NDFPt->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloTruePrimGammaChi2NDFPt , Form("%s/Chi2NDF_Pt_TruePrimGamma_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#chi^{2}_{#gamma}/ndf", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, 0.0, 30., 0 ,1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Chi2"); 
   }
   histoMonteCarloTrueSecGammaChi2NDFPt->SetMaximum(2e-2);
   histoMonteCarloTrueSecGammaChi2NDFPt->SetMinimum(2e-8);
   if (histoMonteCarloTrueSecGammaChi2NDFPt->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloTrueSecGammaChi2NDFPt , Form("%s/Chi2NDF_Pt_TrueSecGamma_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#chi^{2}_{#gamma}/ndf", "#it{p}_{T,#gamma}",
					  kTRUE, 0.1, 20, kTRUE, 0.0, 30., 0 ,1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Chi2"); 
   }
   histoMonteCarloBGChi2NDFPt->SetMaximum(2e-2);
   histoMonteCarloBGChi2NDFPt->SetMinimum(2e-8);
   if (histoMonteCarloBGChi2NDFPt->GetEntries() > 0){
      PlotStandard2D( histoMonteCarloBGChi2NDFPt , Form("%s/Chi2NDF_Pt_BG_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#chi^{2}_{#gamma}/ndf", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, 0.0, 30., 0 ,1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Chi2"); 
   }
   delete histoDataGammaChi2NDFPt;
   delete histoMonteCarloGammaChi2NDFPt;
   delete histoMonteCarloTrueDalitzGammaChi2NDFPt;
   delete histoMonteCarloTruePrimGammaChi2NDFPt;
   delete histoMonteCarloTrueSecGammaChi2NDFPt;
   delete histoMonteCarloBGChi2NDFPt;
   
   TH2F* histoGammaPsiPairPtData 							= (TH2F*)directoryPhotonQAData->Get("histoGammaPsiPairPt");  
   TH2F* histoGammaPsiPairPtMonteCarlo 						= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaPsiPairPt");  
   TH2F* histoTruePrimGammaPsiPairPtMonteCarlo 				= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTruePrimGammaPsiPairPt");  
   TH2F* histoTrueSecGammaPsiPairPtMonteCarlo 				= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueSecGammaPsiPairPt");  
   TH2F* histoTrueDalitzGammaPsiPairPtMonteCarlo 			= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueDalitzGammaPsiPairPt");  
   TH2F* histoBGPsiPairPtMonteCarlo 						= (TH2F*)histoGammaPsiPairPtMonteCarlo->Clone("histoBGPsiPairMonteCarloPt");  
   histoBGPsiPairPtMonteCarlo->Sumw2();
   histoBGPsiPairPtMonteCarlo->Add(histoTruePrimGammaPsiPairPtMonteCarlo,-1.);
   histoBGPsiPairPtMonteCarlo->Add(histoTrueSecGammaPsiPairPtMonteCarlo,-1.);
   histoBGPsiPairPtMonteCarlo->Add(histoTrueDalitzGammaPsiPairPtMonteCarlo,-1.);
   
   TH1D* histoGammaPsiPairData 								= (TH1D*)histoGammaPsiPairPtData->ProjectionX("histoGammaPsiPairData");
   TH1D* histoGammaPsiPairDataLowPt                              = (TH1D*)histoGammaPsiPairPtData->ProjectionX("histoGammaPsiPairDataLowPt",0,109);   
   TH1D* histoGammaPsiPairDataHighPt                              = (TH1D*)histoGammaPsiPairPtData->ProjectionX("histoGammaPsiPairDataHighPt",110,203);   
   GammaScalingHistogramm(histoGammaPsiPairPtData,1./nGammasData);
   ConvGammaRebinWithBinCorrection(histoGammaPsiPairData,1);
   ConvGammaRebinWithBinCorrection(histoGammaPsiPairDataLowPt,1);
   ConvGammaRebinWithBinCorrection(histoGammaPsiPairDataHighPt,1);
   GammaScalingHistogramm(histoGammaPsiPairData,1./nGammasData);
   GammaScalingHistogramm(histoGammaPsiPairDataLowPt,1./histoGammaPsiPairDataLowPt->GetEntries());
   GammaScalingHistogramm(histoGammaPsiPairDataHighPt,1./histoGammaPsiPairDataHighPt->GetEntries());
   
   TH1D* histoGammaPsiPairMonteCarlo 						= (TH1D*)histoGammaPsiPairPtMonteCarlo->ProjectionX("histoGammaPsiPairMonteCarlo");
   TH1D* histoGammaPsiPairMonteCarloLowPt                        = (TH1D*)histoGammaPsiPairPtMonteCarlo->ProjectionX("histoGammaPsiPairMonteCarloLowPt",0,109);
   TH1D* histoGammaPsiPairMonteCarloHighPt                        = (TH1D*)histoGammaPsiPairPtMonteCarlo->ProjectionX("histoGammaPsiPairMonteCarloHighPt",110,203);
   GammaScalingHistogramm(histoGammaPsiPairPtMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoGammaPsiPairMonteCarlo,1);
   ConvGammaRebinWithBinCorrection(histoGammaPsiPairMonteCarloLowPt,1);
   ConvGammaRebinWithBinCorrection(histoGammaPsiPairMonteCarloHighPt,1);   
   GammaScalingHistogramm(histoGammaPsiPairMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoGammaPsiPairMonteCarloLowPt,1./histoGammaPsiPairMonteCarloLowPt->GetEntries());
   GammaScalingHistogramm(histoGammaPsiPairMonteCarloHighPt,1./histoGammaPsiPairMonteCarloHighPt->GetEntries());
   
   TH1D* histoTruePrimGammaPsiPairMonteCarlo 				= (TH1D*)histoTruePrimGammaPsiPairPtMonteCarlo->ProjectionX("histoTruePrimGammaPsiPairMonteCarlo");
   GammaScalingHistogramm(histoTruePrimGammaPsiPairPtMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoTruePrimGammaPsiPairMonteCarlo,1);
   GammaScalingHistogramm(histoTruePrimGammaPsiPairMonteCarlo,1./nGammasMonteCarlo);
   
   TH1D* histoTrueSecGammaPsiPairMonteCarlo 				= (TH1D*)histoTrueSecGammaPsiPairPtMonteCarlo->ProjectionX("histoTrueSecGammaPsiPairMonteCarlo");
   GammaScalingHistogramm(histoTrueSecGammaPsiPairPtMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoTrueSecGammaPsiPairMonteCarlo,1);
   GammaScalingHistogramm(histoTrueSecGammaPsiPairMonteCarlo,1./nGammasMonteCarlo);
   
   TH1D* histoTrueDalitzGammaPsiPairMonteCarlo 				= (TH1D*)histoTrueDalitzGammaPsiPairPtMonteCarlo->ProjectionX("histoTrueDalitzGammaPsiPairMonteCarlo");
   GammaScalingHistogramm(histoTrueDalitzGammaPsiPairPtMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoTrueDalitzGammaPsiPairMonteCarlo,1);
   GammaScalingHistogramm(histoTrueDalitzGammaPsiPairMonteCarlo,1./nGammasMonteCarlo);
   
   TH1D* histoBGPsiPairMonteCarlo 							= (TH1D*)histoBGPsiPairPtMonteCarlo->ProjectionX("histoBGPsiPairMonteCarlo");
   GammaScalingHistogramm(histoBGPsiPairPtMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoBGPsiPairMonteCarlo,1);
   GammaScalingHistogramm(histoBGPsiPairMonteCarlo,1./nGammasMonteCarlo);
   
   //-------------------------------------- Photon PsiPair ----------------------------------------------
   
   TCanvas * canvasPsiPair = new TCanvas("canvasPsiPair","",10,10,500,500);  // gives the page size
   canvasPsiPair->SetLogy(1);
   canvasPsiPair->SetLeftMargin(0.16);
   canvasPsiPair->cd();
   DrawAutoGammaHistos( histoGammaPsiPairData,
                  histoGammaPsiPairMonteCarlo, 
                  "", "#psi_{pair} ",textYAxisPsiPair,
                  kTRUE, 3,1e-3,
                  kFALSE,0. ,0., 
                  kTRUE, -0.15,0.15);   
   DrawGammaSetMarker(histoTruePrimGammaPsiPairMonteCarlo,20,0.8, kBlue+2 , kBlue+2);
   histoTruePrimGammaPsiPairMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueSecGammaPsiPairMonteCarlo,20,0.8, kGreen+2 , kGreen+2);
   histoTrueSecGammaPsiPairMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueDalitzGammaPsiPairMonteCarlo,20,0.8, kOrange+2 , kOrange+2);
   histoTrueDalitzGammaPsiPairMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoBGPsiPairMonteCarlo,20,0.8, kViolet , kViolet);
   histoBGPsiPairMonteCarlo->Draw("histsame");
   
   TLegend* legAdditionalInfoPsiPair = new TLegend( 0.65,0.78,0.97,0.97);
   legAdditionalInfoPsiPair->SetTextSize(0.03);         
   legAdditionalInfoPsiPair->SetFillColor(0);
   legAdditionalInfoPsiPair->AddEntry(histoGammaPsiPairData,("Data"));
   legAdditionalInfoPsiPair->AddEntry(histoGammaPsiPairMonteCarlo,("MC"));
   legAdditionalInfoPsiPair->AddEntry(histoTruePrimGammaPsiPairMonteCarlo,("true prim #gamma"),"l");
   legAdditionalInfoPsiPair->AddEntry(histoTrueSecGammaPsiPairMonteCarlo,("true sec #gamma"),"l");
   legAdditionalInfoPsiPair->AddEntry(histoTrueDalitzGammaPsiPairMonteCarlo,("true dalitz"),"l");
   legAdditionalInfoPsiPair->AddEntry(histoBGPsiPairMonteCarlo,("BG"),"l");
   legAdditionalInfoPsiPair->Draw();
   
   
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasPsiPair->Update();
   canvasPsiPair->SaveAs(Form("%s/Photon_PsiPair.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasPsiPair;      
   delete histoGammaPsiPairData;
   delete histoGammaPsiPairMonteCarlo;

   
   //-------------------------------------- Photon PsiPair Low vs High Pt ----------------------------------------------
   
   TCanvas * canvasPsiPairLowHighPt = new TCanvas("canvasPsiPairLowHighPt","",10,10,500,500);  // gives the page size
   canvasPsiPairLowHighPt->SetLogy(1);
   canvasPsiPairLowHighPt->SetLeftMargin(0.16);
   canvasPsiPairLowHighPt->cd();
   DrawAutoGammaHistos( histoGammaPsiPairDataLowPt,
                  histoGammaPsiPairMonteCarloLowPt, 
                  "", "#psi_{pair} ",textYAxisPsiPair,
                  kTRUE, 6,1e-2,
                  kFALSE,0. ,0., 
                  kTRUE, -0.1,0.3);   
   DrawGammaSetMarker(histoGammaPsiPairDataLowPt,20,0.8, kBlack, kBlack);
   histoGammaPsiPairDataLowPt->Draw("same");
   DrawGammaSetMarker(histoGammaPsiPairMonteCarloLowPt,20,0.8, kRed , kRed);
   histoGammaPsiPairMonteCarloLowPt->Draw("same");
   DrawGammaSetMarker(histoGammaPsiPairDataHighPt,24,0.8, kBlack, kBlack);
   histoGammaPsiPairDataHighPt->Draw("same");
   DrawGammaSetMarker(histoGammaPsiPairMonteCarloHighPt,24,0.8, kRed , kRed);
   histoGammaPsiPairMonteCarloHighPt->Draw("same");
   
   TLegend* legLowHighPtPsi = new TLegend( 0.65,0.78,0.97,0.97);
   legLowHighPtPsi->SetTextSize(0.03);         
   legLowHighPtPsi->SetFillColor(0);
   legLowHighPtPsi->AddEntry(histoGammaPsiPairDataLowPt,("Data p_{T} < 0.4 GeV/c"));
   legLowHighPtPsi->AddEntry(histoGammaPsiPairMonteCarloLowPt,("MC p_{T} < 0.4 GeV/c"));
   legLowHighPtPsi->AddEntry(histoGammaPsiPairDataHighPt,("Data p_{T} > 0.4 GeV/c"));
   legLowHighPtPsi->AddEntry(histoGammaPsiPairMonteCarloHighPt,("MC p_{T} > 0.4 GeV/c"));
   legLowHighPtPsi->Draw();   
   
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasPsiPairLowHighPt->Update();
   canvasPsiPairLowHighPt->SaveAs(Form("%s/Photon_PsiPair_ProjInPt.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasPsiPairLowHighPt;      
   delete histoGammaPsiPairDataLowPt;
   delete histoGammaPsiPairMonteCarloLowPt;
   delete histoGammaPsiPairDataHighPt;
   delete histoGammaPsiPairMonteCarloHighPt;

   
   histoGammaPsiPairPtData->SetMaximum(2e-3);
   histoGammaPsiPairPtData->SetMinimum(1e-8);
   if (histoGammaPsiPairPtData->GetEntries() > 0){ 
      PlotStandard2D( histoGammaPsiPairPtData , Form("%s/PsiPair_Pt_Photon_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#psi_{pair}", "#it{p}_{T,#gamma}", 
					  kTRUE, 0.1, 20, kTRUE, -0.5, 0.5, 0, 1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod); 
   }
   delete histoGammaPsiPairPtData;
   
   histoGammaPsiPairPtMonteCarlo->SetMaximum(2e-3);
   histoGammaPsiPairPtMonteCarlo->SetMinimum(1e-8);   
   if (histoGammaPsiPairPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoGammaPsiPairPtMonteCarlo , Form("%s/PsiPair_Pt_Photon_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#psi_{pair}", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, -0.5, 0.5, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoGammaPsiPairPtMonteCarlo;

   histoTruePrimGammaPsiPairPtMonteCarlo->SetMaximum(2e-3);
   histoTruePrimGammaPsiPairPtMonteCarlo->SetMinimum(1e-8);
   if (histoTruePrimGammaPsiPairPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTruePrimGammaPsiPairPtMonteCarlo , Form("%s/PsiPair_Pt_TruePrimPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#psi_{pair}", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, -0.5, 0.5, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTruePrimGammaPsiPairPtMonteCarlo;
   
   histoTrueSecGammaPsiPairPtMonteCarlo->SetMaximum(2e-3);
   histoTrueSecGammaPsiPairPtMonteCarlo->SetMinimum(1e-8);
   if (histoTrueSecGammaPsiPairPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueSecGammaPsiPairPtMonteCarlo , Form("%s/PsiPair_Pt_TrueSecPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()),
					  "", "#psi_{pair}", "#it{p}_{T,#gamma}", 
					  kTRUE, 0.1, 20, kTRUE, -0.5, 0.5, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueSecGammaPsiPairPtMonteCarlo;
   
   histoTrueDalitzGammaPsiPairPtMonteCarlo->SetMaximum(2e-3);
   histoTrueDalitzGammaPsiPairPtMonteCarlo->SetMinimum(1e-8);
   if (histoTrueDalitzGammaPsiPairPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueDalitzGammaPsiPairPtMonteCarlo , Form("%s/PsiPair_Pt_TrueDalitzPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#psi_{pair}", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, -0.5, 0.5, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueDalitzGammaPsiPairPtMonteCarlo;
   
   histoBGPsiPairPtMonteCarlo->SetMaximum(2e-3);
   histoBGPsiPairPtMonteCarlo->SetMinimum(1e-8);
   if (histoBGPsiPairPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoBGPsiPairPtMonteCarlo , Form("%s/PsiPair_Pt_BG_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#psi_{pair}", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, -0.5, 0.5, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoBGPsiPairPtMonteCarlo;

   //-------------------------------------- Photon Phi ----------------------------------------------
   TH1F* histoGammaPhiData 							= (TH1F*)directoryPhotonQAData->Get("histoGammaPhi");   
   ConvGammaRebinWithBinCorrection(histoGammaPhiData,1);
   GammaScalingHistogramm(histoGammaPhiData,1./nGammasData);
   TH1F* histoGammaPhiMonteCarlo 					= (TH1F*)directoryPhotonQAMonteCarlo->Get("histoGammaPhi");   
   ConvGammaRebinWithBinCorrection(histoGammaPhiMonteCarlo,1);
   GammaScalingHistogramm(histoGammaPhiMonteCarlo,1./nGammasMonteCarlo);
   
   TCanvas * canvasPhi = new TCanvas("canvasPhi","",10,10,500,500);  // gives the page size
   canvasPhi->SetLeftMargin(0.16);
   canvasPhi->cd();
   DrawAutoGammaHistos( histoGammaPhiData,
                  histoGammaPhiMonteCarlo, 
                  "", "#phi ",textYAxisPhi,
                  kTRUE, 1.2,1e-6,
                  kFALSE,0. ,0., 
                  kFALSE, 0.,60.);  
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasPhi->Update();
   canvasPhi->SaveAs(Form("%s/Photon_Phi.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasPhi;    
   delete histoGammaPhiData;
   delete histoGammaPhiMonteCarlo;

   
   //-------------------------------------- Photon CosPoint ----------------------------------------------
   TH2F* histoGammaZRData                   = (TH2F*)directoryPhotonQAData->Get("histoGammaAsymR");     
   TH2F* histoGammaZRMonteCarlo             = (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaAsymR");  
   
   TH1D* histoGammaRData                     = (TH1D*)histoGammaZRData->ProjectionY("histoGammaRData");
   ConvGammaRebinWithBinCorrection(histoGammaRData,1);
   GammaScalingHistogramm(histoGammaRData,1./nGammasData);
   TH1D* histoGammaRMonteCarlo               = (TH1D*)histoGammaZRMonteCarlo->ProjectionY("histoGammaRMonteCarlo");
   ConvGammaRebinWithBinCorrection(histoGammaRMonteCarlo,1);
   GammaScalingHistogramm(histoGammaRMonteCarlo,1./nGammasMonteCarlo);

   TCanvas * canvasGammaR = new TCanvas("canvasGammaR","",10,10,500,500);  // gives the page size
   canvasGammaR->SetLeftMargin(0.16);
   canvasGammaR->SetLogy(1);
   canvasGammaR->cd();
   DrawAutoGammaHistos( histoGammaRData,
                  histoGammaRMonteCarlo, 
                  "", "R (cm)",textYAxisITSClvsR,
                  kTRUE, 10.,1e-4,
                  kFALSE,0. ,0., 
                  kTRUE, 0.,200);  
   DrawGammaSetMarker(histoGammaRData,20,0.8, kBlack, kBlack);
   histoGammaRData->Draw("histsame");
   DrawGammaSetMarker(histoGammaRMonteCarlo,20,0.8, kRed , kRed);
   histoGammaRMonteCarlo->Draw("histsame");
   
   TLegend* legAdditionalInfoR = new TLegend( 0.65,0.82,0.97,0.97);
   legAdditionalInfoR->SetTextSize(0.03);         
   legAdditionalInfoR->SetFillColor(0);
   legAdditionalInfoR->AddEntry(histoGammaRData,("Data"));
   legAdditionalInfoR->AddEntry(histoGammaRMonteCarlo,("MC"));
   legAdditionalInfoR->Draw();

   
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasGammaR->SaveAs(Form("%s/Photon_R.%s", outputDirectory.Data(), suffix.Data()));
   canvasGammaR->SaveAs(Form("%s/Photon_R.root", outputDirectory.Data(), suffix.Data()));
   
   
   TH1D *histoGammaRratio = (TH1D*) histoGammaRData->Clone("histoGammaRratio");
   histoGammaRratio->Divide(histoGammaRData,histoGammaRMonteCarlo,1.,1.,"B");
   canvasGammaR->cd();
   canvasGammaR->SetLogy(0);
   DrawAutoGammaHistos( histoGammaRratio,
                  histoGammaRratio, 
                  "", "R (cm)",textYAxisITSClvsR,
                  kTRUE, 2,0.,
                  kFALSE,0. ,0., 
                  kTRUE, 0.,200);  
   DrawGammaSetMarker(histoGammaRratio,20,0.8, kBlack, kBlack);
   histoGammaRratio->Draw("histsame");
      
   legAdditionalInfoR->Draw();
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasGammaR->SaveAs(Form("%s/Photon_Rratio.%s", outputDirectory.Data(), suffix.Data()));

   delete canvasGammaR;    
   delete histoGammaRData;
   delete histoGammaRMonteCarlo;
   
   
   //-------------------------------------- Photon CosPoint ----------------------------------------------
   TH2F* histoGammaCosPointPtData 					= (TH2F*)directoryPhotonQAData->Get("histoGammaCosPointPt");  
   
   TH2F* histoGammaCosPointPtMonteCarlo 			= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaCosPointPt");  
   TH2F* histoTruePrimGammaCosPointPtMonteCarlo 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTruePrimGammaCosPointPt");  
   TH2F* histoTrueSecGammaCosPointPtMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueSecGammaCosPointPt");  
   TH2F* histoTrueDalitzGammaCosPointPtMonteCarlo 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueDalitzGammaCosPointPt");  
   TH2F* histoBGCosPointPtMonteCarlo 				= (TH2F*)histoGammaCosPointPtMonteCarlo->Clone("histoBGCosPointMonteCarloPt");  
   histoBGCosPointPtMonteCarlo->Sumw2();
   histoBGCosPointPtMonteCarlo->Add(histoTruePrimGammaCosPointPtMonteCarlo,-1.);
   histoBGCosPointPtMonteCarlo->Add(histoTrueSecGammaCosPointPtMonteCarlo,-1.);
   histoBGCosPointPtMonteCarlo->Add(histoTrueDalitzGammaCosPointPtMonteCarlo,-1.);
   
   TH1D* histoGammaCosPointData 					= (TH1D*)histoGammaCosPointPtData->ProjectionX("histoGammaCosPointData");
   TH1D* histoGammaCosPointDataLowPt                     = (TH1D*)histoGammaCosPointPtData->ProjectionX("histoGammaCosPointDataLowPt",0,109);
   TH1D* histoGammaCosPointDataHighPt                     = (TH1D*)histoGammaCosPointPtData->ProjectionX("histoGammaCosPointDataHighPt",110,203);
   TH1D* histoGammaPtData 							= (TH1D*)histoGammaCosPointPtData->ProjectionY("histoGammaPtData");
   GammaScalingHistogramm(histoGammaCosPointPtData,1./nGammasData);
   ConvGammaRebinWithBinCorrection(histoGammaCosPointData,1);
   ConvGammaRebinWithBinCorrection(histoGammaCosPointDataLowPt,1);
   ConvGammaRebinWithBinCorrection(histoGammaCosPointDataHighPt,1);
   GammaScalingHistogramm(histoGammaCosPointData,1./nGammasData);
   GammaScalingHistogramm(histoGammaCosPointDataLowPt,1./histoGammaCosPointDataLowPt->GetEntries());
   GammaScalingHistogramm(histoGammaCosPointDataHighPt,1./histoGammaCosPointDataHighPt->GetEntries());
   ConvGammaRebinWithBinCorrection(histoGammaPtData,1);
   GammaScalingHistogramm(histoGammaPtData,1./nGammasData);
   
   TH1D* histoGammaCosPointMonteCarlo 				= (TH1D*)histoGammaCosPointPtMonteCarlo->ProjectionX("histoGammaCosPointMonteCarlo");
   TH1D* histoGammaCosPointMonteCarloLowPt               = (TH1D*)histoGammaCosPointPtMonteCarlo->ProjectionX("histoGammaCosPointMonteCarloLowPt",0,109);
   TH1D* histoGammaCosPointMonteCarloHighPt               = (TH1D*)histoGammaCosPointPtMonteCarlo->ProjectionX("histoGammaCosPointMonteCarloHighPt",110,203);
   TH1D* histoGammaPtMonteCarlo 					= (TH1D*)histoGammaCosPointPtMonteCarlo->ProjectionY("histoGammaPtMonteCarlo");
   GammaScalingHistogramm(histoGammaCosPointPtMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoGammaCosPointMonteCarlo,1);
   ConvGammaRebinWithBinCorrection(histoGammaCosPointMonteCarloLowPt,1);
   ConvGammaRebinWithBinCorrection(histoGammaCosPointMonteCarloHighPt,1);
   GammaScalingHistogramm(histoGammaCosPointMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoGammaCosPointMonteCarloLowPt,1./histoGammaCosPointMonteCarloLowPt->GetEntries());
   GammaScalingHistogramm(histoGammaCosPointMonteCarloHighPt,1./histoGammaCosPointMonteCarloHighPt->GetEntries());
   ConvGammaRebinWithBinCorrection(histoGammaPtMonteCarlo,1);
   GammaScalingHistogramm(histoGammaPtMonteCarlo,1./nGammasMonteCarlo);
   
   
   TH1D* histoTruePrimGammaCosPointMonteCarlo 		= (TH1D*)histoTruePrimGammaCosPointPtMonteCarlo->ProjectionX("histoTruePrimGammaCosPointMonteCarlo");
   TH1D* histoTruePrimGammaPtMonteCarlo 			= (TH1D*)histoTruePrimGammaCosPointPtMonteCarlo->ProjectionY("histoTruePrimGammaPtMonteCarlo");
   GammaScalingHistogramm(histoTruePrimGammaCosPointPtMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoTruePrimGammaCosPointMonteCarlo,1);
   GammaScalingHistogramm(histoTruePrimGammaCosPointMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoTruePrimGammaPtMonteCarlo,1);
   GammaScalingHistogramm(histoTruePrimGammaPtMonteCarlo,1./nGammasMonteCarlo);
   
   
   TH1D* histoTrueSecGammaCosPointMonteCarlo 		= (TH1D*)histoTrueSecGammaCosPointPtMonteCarlo->ProjectionX("histoTrueSecGammaCosPointMonteCarlo");
   TH1D* histoTrueSecGammaPtMonteCarlo 				= (TH1D*)histoTrueSecGammaCosPointPtMonteCarlo->ProjectionY("histoTrueSecGammaPtMonteCarlo");
   GammaScalingHistogramm(histoTrueSecGammaCosPointPtMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoTrueSecGammaCosPointMonteCarlo,1);
   GammaScalingHistogramm(histoTrueSecGammaCosPointMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoTrueSecGammaPtMonteCarlo,1);
   GammaScalingHistogramm(histoTrueSecGammaPtMonteCarlo,1./nGammasMonteCarlo);
   
   
   TH1D* histoTrueDalitzGammaCosPointMonteCarlo 	= (TH1D*)histoTrueDalitzGammaCosPointPtMonteCarlo->ProjectionX("histoTrueDalitzGammaCosPointMonteCarlo");
   TH1D* histoTrueDalitzGammaPtMonteCarlo 			= (TH1D*)histoTrueDalitzGammaCosPointPtMonteCarlo->ProjectionY("histoTrueDalitzGammaPtMonteCarlo");
   GammaScalingHistogramm(histoTrueDalitzGammaCosPointPtMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoTrueDalitzGammaCosPointMonteCarlo,1);
   GammaScalingHistogramm(histoTrueDalitzGammaCosPointMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoTrueDalitzGammaPtMonteCarlo,1);
   GammaScalingHistogramm(histoTrueDalitzGammaPtMonteCarlo,1./nGammasMonteCarlo);
   
   
   TH1D* histoBGCosPointMonteCarlo 					= (TH1D*)histoBGCosPointPtMonteCarlo->ProjectionX("histoBGCosPointMonteCarlo");
   TH1D* histoBGPtMonteCarlo 						= (TH1D*)histoBGCosPointPtMonteCarlo->ProjectionY("histoBGPtMonteCarlo");
   GammaScalingHistogramm(histoBGCosPointPtMonteCarlo,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoBGCosPointMonteCarlo,1);
   GammaScalingHistogramm(histoBGCosPointMonteCarlo,1./nGammasMonteCarlo); 
   ConvGammaRebinWithBinCorrection(histoBGPtMonteCarlo,1);
   GammaScalingHistogramm(histoBGPtMonteCarlo,1./nGammasMonteCarlo); 
   
   TH1D* histoTruePhotonPt 							= (TH1D*) histoTruePrimGammaPtMonteCarlo->Clone("histoTruePhotonPt");
   histoTruePhotonPt->Add(histoTrueSecGammaPtMonteCarlo);
   
   TH1D* histoPurity 								= (TH1D*) histoTruePhotonPt->Clone("histoPurity");
   histoPurity->Divide(histoPurity,histoGammaPtMonteCarlo,1,1,"B");
   
   TCanvas * canvasGammaPt = new TCanvas("canvasGammaPt","",10,10,500,500);  // gives the page size
   canvasGammaPt->SetLeftMargin(0.16);
   canvasGammaPt->SetLogy(1);
   canvasGammaPt->SetLogx(1);
   canvasGammaPt->cd();
   DrawAutoGammaHistos( histoGammaPtData,
                  histoGammaPtMonteCarlo, 
                  "", "#it{p}_{T} (GeV/#it{c}) ",textYAxisPtDist,
                  kTRUE, 10.,1e-4,
                  kFALSE,0. ,0., 
                  kTRUE, 0.05,60.); 
   DrawGammaSetMarker(histoTruePrimGammaPtMonteCarlo,20,0.8, kBlue+2 , kBlue+2);
   histoTruePrimGammaPtMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueSecGammaPtMonteCarlo,20,0.8, kGreen+2 , kGreen+2);
   histoTrueSecGammaPtMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueDalitzGammaPtMonteCarlo,20,0.8, kOrange+2 , kOrange+2);
   histoTrueDalitzGammaPtMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoBGPtMonteCarlo,20,0.8, kViolet , kViolet);
   histoBGPtMonteCarlo->Draw("histsame");
   
   TLegend* legAdditionalInfoPt = new TLegend( 0.65,0.78,0.97,0.97);
   legAdditionalInfoPt->SetTextSize(0.03);         
   legAdditionalInfoPt->SetFillColor(0);
   legAdditionalInfoPt->AddEntry(histoGammaPtData,("Data"));
   legAdditionalInfoPt->AddEntry(histoGammaPtMonteCarlo,("MC"));
   legAdditionalInfoPt->AddEntry(histoTruePrimGammaPtMonteCarlo,("true prim #gamma"),"l");
   legAdditionalInfoPt->AddEntry(histoTrueSecGammaPtMonteCarlo,("true sec #gamma"),"l");
   legAdditionalInfoPt->AddEntry(histoTrueDalitzGammaPtMonteCarlo,("true dalitz"),"l");
   legAdditionalInfoPt->AddEntry(histoBGPtMonteCarlo,("BG"),"l");
   legAdditionalInfoPt->Draw();
   
   
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasGammaPt->Update();
   canvasGammaPt->SaveAs(Form("%s/Photon_Pt_AddMCInfo.%s", outputDirectory.Data(), suffix.Data()));

   TCanvas * canvasPurity = new TCanvas("canvasPurity","",10,10,500,500);  // gives the page size
   canvasPurity->SetLeftMargin(0.16);
//    canvasPurity->SetLogy(1);
   canvasPurity->SetLogx(1);
   canvasPurity->cd();
   histoPurity->GetYaxis()->SetTitle("#epsilon_{pur}");
   histoPurity->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
   histoPurity->GetYaxis()->SetRangeUser(0.9,1.05);
   histoPurity->GetXaxis()->SetRangeUser(0.05,60.);
   DrawGammaSetMarker(histoPurity,20,0.8, kBlue+2 , kBlue+2);
   histoPurity->Draw("pe1");
   
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasPurity->Update();
   canvasPurity->SaveAs(Form("%s/Photon_Purity.%s", outputDirectory.Data(), suffix.Data()));

   
   
   TCanvas * canvasCosPoint = new TCanvas("canvasCosPoint","",10,10,500,500);  // gives the page size
   canvasCosPoint->SetLeftMargin(0.16);
   canvasCosPoint->SetLogy(1);
   canvasCosPoint->cd();
   DrawAutoGammaHistos( histoGammaCosPointData,
                  histoGammaCosPointMonteCarlo, 
                  "", "cos(#theta_{point}) ",textYAxisCosPoint,
                  kTRUE, 10.,1e-5,
                  kFALSE,0. ,0., 
                  kFALSE, 0.,60.);  
   DrawGammaSetMarker(histoTruePrimGammaCosPointMonteCarlo,20,0.8, kBlue+2 , kBlue+2);
   histoTruePrimGammaCosPointMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueSecGammaCosPointMonteCarlo,20,0.8, kGreen+2 , kGreen+2);
   histoTrueSecGammaCosPointMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueDalitzGammaCosPointMonteCarlo,20,0.8, kOrange+2 , kOrange+2);
   histoTrueDalitzGammaCosPointMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoBGCosPointMonteCarlo,20,0.8, kViolet , kViolet);
   histoBGCosPointMonteCarlo->Draw("histsame");
   
   TLegend* legAdditionalInfoCosPoint = new TLegend( 0.65,0.82,0.97,0.97);
   legAdditionalInfoCosPoint->SetTextSize(0.03);         
   legAdditionalInfoCosPoint->SetFillColor(0);
   legAdditionalInfoCosPoint->AddEntry(histoGammaCosPointData,("Data"));
   legAdditionalInfoCosPoint->AddEntry(histoGammaCosPointMonteCarlo,("MC"));
   legAdditionalInfoCosPoint->AddEntry(histoTruePrimGammaCosPointMonteCarlo,("true prim #gamma"),"l");
   legAdditionalInfoCosPoint->AddEntry(histoTrueSecGammaCosPointMonteCarlo,("true sec #gamma"),"l");
   legAdditionalInfoCosPoint->AddEntry(histoTrueDalitzGammaCosPointMonteCarlo,("true dalitz"),"l");
   legAdditionalInfoCosPoint->AddEntry(histoBGCosPointMonteCarlo,("BG"),"l");
   legAdditionalInfoCosPoint->Draw();
   
   
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasCosPoint->Update();
   canvasCosPoint->SaveAs(Form("%s/Photon_CosPoint.%s", outputDirectory.Data(), suffix.Data()));
   
   canvasCosPoint->cd();
   DrawAutoGammaHistos( histoGammaCosPointData,
                  histoGammaCosPointMonteCarlo, 
                  "", "cos(#theta_{point}) ",textYAxisCosPoint,
                  kTRUE, 100.,1e-5,
                  kFALSE,0. ,0., 
                  kTRUE, 0.8,1.);  
   DrawGammaSetMarker(histoTruePrimGammaCosPointMonteCarlo,20,0.8, kBlue+2 , kBlue+2);
   histoTruePrimGammaCosPointMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueSecGammaCosPointMonteCarlo,20,0.8, kGreen+2 , kGreen+2);
   histoTrueSecGammaCosPointMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueDalitzGammaCosPointMonteCarlo,20,0.8, kOrange+2 , kOrange+2);
   histoTrueDalitzGammaCosPointMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoBGCosPointMonteCarlo,20,0.8, kViolet , kViolet);
   histoBGCosPointMonteCarlo->Draw("histsame");
   
   legAdditionalInfoCosPoint->Draw();
   
   
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasCosPoint->Update();
   canvasCosPoint->SaveAs(Form("%s/Photon_CosPoint_Enlarged.%s", outputDirectory.Data(), suffix.Data()));

   
   delete canvasCosPoint;    
   delete histoGammaCosPointData;
   delete histoGammaCosPointMonteCarlo;
   
   
   TCanvas * canvasCosPointLowHighPt = new TCanvas("canvasCosPointLowHighPt","",10,10,500,500);  // gives the page size
   canvasCosPointLowHighPt->SetLeftMargin(0.16);
   canvasCosPointLowHighPt->SetLogy(1);
   canvasCosPointLowHighPt->cd();
   DrawAutoGammaHistos( histoGammaCosPointDataLowPt,
                  histoGammaCosPointMonteCarloLowPt, 
                  "", "cos(#theta_{point}) ",textYAxisCosPoint,
                  kTRUE, 1.e4,1e-5,
                  kFALSE,0. ,0., 
                  kTRUE, 0.8,1.);  
   DrawGammaSetMarker(histoGammaCosPointDataLowPt,20,0.8, kBlack, kBlack);
   histoGammaCosPointDataLowPt->Draw("e0,same");
   DrawGammaSetMarker(histoGammaCosPointMonteCarloLowPt,20,0.8, kRed , kRed);
   histoGammaCosPointMonteCarloLowPt->Draw("e0,same");
   DrawGammaSetMarker(histoGammaCosPointDataHighPt,24,0.8, kBlack, kBlack);
   histoGammaCosPointDataHighPt->Draw("e0,same");
   DrawGammaSetMarker(histoGammaCosPointMonteCarloHighPt,24,0.8, kRed , kRed);
   histoGammaCosPointMonteCarloHighPt->Draw("e0,same");
   
   TLegend* legLowHighPtCosPA = new TLegend( 0.65,0.78,0.97,0.97);
   legLowHighPtCosPA->SetTextSize(0.03);         
   legLowHighPtCosPA->SetFillColor(0);
   legLowHighPtCosPA->AddEntry(histoGammaCosPointDataLowPt,("Data p_{T} < 0.4 GeV/c"));
   legLowHighPtCosPA->AddEntry(histoGammaCosPointMonteCarloLowPt,("MC p_{T} < 0.4 GeV/c"));
   legLowHighPtCosPA->AddEntry(histoGammaCosPointDataHighPt,("Data p_{T} > 0.4 GeV/c"));
   legLowHighPtCosPA->AddEntry(histoGammaCosPointMonteCarloHighPt,("MC p_{T} > 0.4 GeV/c"));
   legLowHighPtCosPA->Draw(); 
   
   
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasCosPointLowHighPt->Update();
   canvasCosPointLowHighPt->SaveAs(Form("%s/Photon_CosPoint_ProjInPt.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasCosPointLowHighPt;    
   delete histoGammaCosPointDataLowPt;
   delete histoGammaCosPointMonteCarloLowPt;
   delete histoGammaCosPointDataHighPt;
   delete histoGammaCosPointMonteCarloHighPt;
   
   
   histoGammaCosPointPtData->SetMaximum(2e-2);
   histoGammaCosPointPtData->SetMinimum(2e-8);
   if (histoGammaCosPointPtData->GetEntries() > 0){ 
      PlotStandard2D( histoGammaCosPointPtData , Form("%s/CosPoint_Pt_Photon_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.05, 20, kTRUE, -1.0, 1., 0, 1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod); 
   }
   delete histoGammaCosPointPtData;
   histoGammaCosPointPtMonteCarlo->SetMaximum(2e-2);
   histoGammaCosPointPtMonteCarlo->SetMinimum(2e-8);
   if (histoGammaCosPointPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoGammaCosPointPtMonteCarlo , Form("%s/CosPoint_Pt_Photon_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()),
					  "", "cos(#theta_{point})", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.05, 20, kTRUE, -1.0, 1., 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoGammaCosPointPtMonteCarlo;
   histoTruePrimGammaCosPointPtMonteCarlo->SetMaximum(2e-2);
   histoTruePrimGammaCosPointPtMonteCarlo->SetMinimum(2e-8);
   if (histoTruePrimGammaCosPointPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTruePrimGammaCosPointPtMonteCarlo , Form("%s/CosPoint_Pt_TruePrimPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#it{p}_{T,#gamma}", 
					  kTRUE, 0.05, 20, kTRUE, -1.0, 1., 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTruePrimGammaCosPointPtMonteCarlo;
   histoTrueSecGammaCosPointPtMonteCarlo->SetMaximum(2e-2);
   histoTrueSecGammaCosPointPtMonteCarlo->SetMinimum(2e-8);
   if (histoTrueSecGammaCosPointPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueSecGammaCosPointPtMonteCarlo , Form("%s/CosPoint_Pt_TrueSecPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.05, 20, kTRUE, -1.0, 1., 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueSecGammaCosPointPtMonteCarlo;
   histoTrueDalitzGammaCosPointPtMonteCarlo->SetMaximum(2e-2);
   histoTrueDalitzGammaCosPointPtMonteCarlo->SetMinimum(2e-8);
   if (histoTrueDalitzGammaCosPointPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueDalitzGammaCosPointPtMonteCarlo , Form("%s/CosPoint_Pt_TrueDalitzPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.05, 20, kTRUE,-1.0, 1., 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueDalitzGammaCosPointPtMonteCarlo;
   histoBGCosPointPtMonteCarlo->SetMaximum(2e-2);
   histoBGCosPointPtMonteCarlo->SetMinimum(2e-8);
   if (histoBGCosPointPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoBGCosPointPtMonteCarlo , Form("%s/CosPoint_Pt_BG_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.05, 20, kTRUE, -1.0, 1., 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoBGCosPointPtMonteCarlo;

   

   TH2F* hist2DElectronEtaPtData 					= (TH2F*)directoryPhotonQAData->Get("histoElectronEtaPt"); 
   TH1D* histoDataElectronEta 						= (TH1D*)hist2DElectronEtaPtData->ProjectionX("histoDataElectronEta");
   TH1D* histoDataElectronPt 						= (TH1D*)hist2DElectronEtaPtData->ProjectionY("histoDataElectronPt");
   ConvGammaRebinWithBinCorrection(histoDataElectronEta,1);
   GammaScalingHistogramm(histoDataElectronEta,1./nElectronsData);
   ConvGammaRebinWithBinCorrection(histoDataElectronPt,1);
   GammaScalingHistogramm(histoDataElectronPt,1./nElectronsData);
   
   TH2F* hist2DElectronEtaPtMonteCarlo 				= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoElectronEtaPt"); 
   TH1D* histoMonteCarloElectronEta 				= (TH1D*)hist2DElectronEtaPtMonteCarlo->ProjectionX("histoMonteCarloElectronEta");
   TH1D* histoMonteCarloElectronPt 					= (TH1D*)hist2DElectronEtaPtMonteCarlo->ProjectionY("histoMonteCarloElectronPt");
   ConvGammaRebinWithBinCorrection(histoMonteCarloElectronEta,1);
   GammaScalingHistogramm(histoMonteCarloElectronEta,1./nElectronsMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoMonteCarloElectronPt,1);
   GammaScalingHistogramm(histoMonteCarloElectronPt,1./nElectronsMonteCarlo);
   
   //-------------------------------------- Electron Eta ----------------------------------------------
   
   TCanvas * canvasElectronEta = new TCanvas("canvasElectronEta","",10,10,500,500);  // gives the page size
   canvasElectronEta->SetLeftMargin(0.16);
   canvasElectronEta->cd();
   //if (optEnergy.CompareTo("PbPb_2.76TeV") == 0 ) histoMonteCarloElectronEta->Scale(1/1.28);
   DrawAutoGammaHistos( histoDataElectronEta,
                  histoMonteCarloElectronEta, 
                  "", "#eta ",textYAxisEtaElec,
                  kTRUE, 1.3,1e-1,
                  kFALSE,0. ,0., 
                  kTRUE,-1.6,1.6);
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasElectronEta->Update();
   canvasElectronEta->SaveAs(Form("%s/Electron_Eta.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasElectronEta;     
   delete histoDataElectronEta;
   delete histoMonteCarloElectronEta;
   
   //-------------------------------------- Electron Pt ----------------------------------------------
   
   TCanvas * canvasElectronPt = new TCanvas("canvasElectronPt","",10,10,500,500);  // gives the page size
   canvasElectronPt->SetLogy(1);
   canvasElectronPt->SetLogx(1);
   canvasElectronPt->SetLeftMargin(0.16);
   canvasElectronPt->cd();
   DrawAutoGammaHistos( histoDataElectronPt,
                  histoMonteCarloElectronPt, 
                  "", "#it{p}_{T} e^{-} (GeV/#it{c}) ",textYAxisPtDistE,
                  kTRUE, 5.,1e-3,
                  kFALSE,0. ,0., 
                  kTRUE, 0.05,60.); 
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasElectronPt->Update();
   canvasElectronPt->SaveAs(Form("%s/Electron_Pt.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasElectronPt;      
   delete histoDataElectronPt;
   delete histoMonteCarloElectronPt;
   
   delete hist2DElectronEtaPtData;
   delete hist2DElectronEtaPtMonteCarlo;

   
   TH2F* hist2DPositronEtaPtData 					= (TH2F*)directoryPhotonQAData->Get("histoPositronEtaPt"); 
   TH1D* histoDataPositronEta 						= (TH1D*)hist2DPositronEtaPtData->ProjectionX("histoDataPositronEta");
   TH1D* histoDataPositronPt 						= (TH1D*)hist2DPositronEtaPtData->ProjectionY("histoDataPositronPt");
   ConvGammaRebinWithBinCorrection(histoDataPositronEta,1);
   GammaScalingHistogramm(histoDataPositronEta,1./nPositronsData);
   ConvGammaRebinWithBinCorrection(histoDataPositronPt,1);
   GammaScalingHistogramm(histoDataPositronPt,1./nPositronsData);
   
   TH2F* hist2DPositronEtaPtMonteCarlo 				= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoPositronEtaPt"); 
   TH1D* histoMonteCarloPositronEta 				= (TH1D*)hist2DPositronEtaPtMonteCarlo->ProjectionX("histoMonteCarloPositronEta");
   TH1D* histoMonteCarloPositronPt 					= (TH1D*)hist2DPositronEtaPtMonteCarlo->ProjectionY("histoMonteCarloPositronPt");
   ConvGammaRebinWithBinCorrection(histoMonteCarloPositronEta,1);
   GammaScalingHistogramm(histoMonteCarloPositronEta,1./nPositronsMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoMonteCarloPositronPt,1);
   GammaScalingHistogramm(histoMonteCarloPositronPt,1./nPositronsMonteCarlo);
   
   //-------------------------------------- Positron Eta ----------------------------------------------
   
   TCanvas * canvasPositronEta = new TCanvas("canvasPositronEta","",10,10,500,500);  // gives the page size
   canvasPositronEta->SetLeftMargin(0.16);
   canvasPositronEta->cd();
   //if (optEnergy.CompareTo("PbPb_2.76TeV") == 0 ) histoMonteCarloPositronEta->Scale(1/1.28);
   DrawAutoGammaHistos( histoDataPositronEta,
                  histoMonteCarloPositronEta, 
                  "", "#eta ",textYAxisEtaPos,
                  kTRUE, 1.3,1e-1,
                  kFALSE,0. ,0., 
                  kTRUE,-1.6,1.6);
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasPositronEta->Update();
   canvasPositronEta->SaveAs(Form("%s/Positron_Eta.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasPositronEta;     
   delete histoDataPositronEta;
   delete histoMonteCarloPositronEta;
   
   //-------------------------------------- Positron Pt ----------------------------------------------
   
   TCanvas * canvasPositronPt = new TCanvas("canvasPositronPt","",10,10,500,500);  // gives the page size
   canvasPositronPt->SetLogy(1);
   canvasPositronPt->SetLogx(1);
   canvasPositronPt->SetLeftMargin(0.16);
   canvasPositronPt->cd();
   DrawAutoGammaHistos( histoDataPositronPt,
                  histoMonteCarloPositronPt, 
                  "", "#it{p}_{T} e^{+} (GeV/#it{c}) ",textYAxisPtDistP,
                  kTRUE, 5.,1e-3,
                  kFALSE,0. ,0., 
                  kTRUE, 0.05,60.); 
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasPositronPt->Update();
   canvasPositronPt->SaveAs(Form("%s/Positron_Pt.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasPositronPt;      
   delete histoDataPositronPt;
   delete histoMonteCarloPositronPt;
   
   delete hist2DPositronEtaPtData;
   delete hist2DPositronEtaPtMonteCarlo;

   TH2F* hist2DPhotonEtaPtData 							= (TH2F*)directoryPhotonQAData->Get("histoGammaEtaPt"); 
   TH1D* histoDataPhotonEta 							= (TH1D*)hist2DPhotonEtaPtData->ProjectionX("histoDataPhotonEta");
   TH1D* histoDataPhotonPt 								= (TH1D*)hist2DPhotonEtaPtData->ProjectionY("histoDataPhotonPt");
   ConvGammaRebinWithBinCorrection(histoDataPhotonEta,1);
   GammaScalingHistogramm(histoDataPhotonEta,1./nGammasData);
   ConvGammaRebinWithBinCorrection(histoDataPhotonPt,1);
   GammaScalingHistogramm(histoDataPhotonPt,1./nGammasData);
   
   TH2F* hist2DPhotonEtaPtMonteCarlo 					= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaEtaPt"); 
   TH1D* histoMonteCarloPhotonEta 						= (TH1D*)hist2DPhotonEtaPtMonteCarlo->ProjectionX("histoMonteCarloPhotonEta");
   TH1D* histoMonteCarloPhotonPt 						= (TH1D*)hist2DPhotonEtaPtMonteCarlo->ProjectionY("histoMonteCarloPhotonPt");
   ConvGammaRebinWithBinCorrection(histoMonteCarloPhotonEta,1);
   GammaScalingHistogramm(histoMonteCarloPhotonEta,1./nGammasMonteCarlo);
   ConvGammaRebinWithBinCorrection(histoMonteCarloPhotonPt,1);
   GammaScalingHistogramm(histoMonteCarloPhotonPt,1./nGammasMonteCarlo);

   TH1D* histoRatioGammaEta 							= (TH1D*) histoMonteCarloPhotonEta->Clone("histoRatioGammaEta");
   histoRatioGammaEta->Divide(histoRatioGammaEta,histoDataPhotonEta,1.,1.,"B");
   
   //-------------------------------------- Photon Eta ----------------------------------------------
   
   TCanvas * canvasPhotonEta = new TCanvas("canvasPhotonEta","",10,10,500,500);  // gives the page size
   canvasPhotonEta->SetLeftMargin(0.16);
   canvasPhotonEta->cd();
   if (optEnergy.CompareTo("PbPb_2.76TeV") == 0 ) histoMonteCarloPhotonEta->Scale(1/1.28);
   DrawAutoGammaHistos( histoDataPhotonEta,
                  histoMonteCarloPhotonEta, 
                  "", "#eta ",textYAxisEtaGamma,
                  kTRUE, 1.3,1e-1,
                  kFALSE,0. ,0., 
                  kTRUE,-1.6,1.6);
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasPhotonEta->Update();
   canvasPhotonEta->SaveAs(Form("%s/Photon_Eta.%s", outputDirectory.Data(), suffix.Data()));
   
   TCanvas * canvasPhotonEtaRatio = new TCanvas("canvasPhotonEtaRatio","",10,10,500,500);  // gives the page size
   canvasPhotonEtaRatio->SetLeftMargin(0.16);
   canvasPhotonEtaRatio->cd();
   if (optEnergy.CompareTo("PbPb_2.76TeV") == 0 ) histoRatioGammaEta->Scale(1/1.28);
   histoRatioGammaEta->GetYaxis()->SetRangeUser(0,2.);
   histoRatioGammaEta->GetXaxis()->SetRangeUser(-0.9,0.9);
   histoRatioGammaEta->SetMarkerStyle(20);
   histoRatioGammaEta->GetYaxis()->SetTitle("Ratio MC/Data");
   histoRatioGammaEta->GetXaxis()->SetTitle("#eta_{#gamma}");
   histoRatioGammaEta->Draw("pe");
//    DrawAutoGammaHistos( histoDataPhotonEta,
//                   histoMonteCarloPhotonEta, 
//                   "", "#eta ","MC/Data,
//                   kTRUE, 1.3,1e-1,
//                   kFALSE,0. ,0., 
//                   kTRUE,-1.6,1.6);
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasPhotonEtaRatio->Update();
   canvasPhotonEtaRatio->SaveAs(Form("%s/Photon_Ratio_Eta.%s", outputDirectory.Data(), suffix.Data()));

   
   delete canvasPhotonEta;    
   delete histoDataPhotonEta;
   delete histoMonteCarloPhotonEta;
   
   //-------------------------------------- Photon Pt ----------------------------------------------
   
   TCanvas * canvasPhotonPt = new TCanvas("canvasPhotonPt","",10,10,500,500);  // gives the page size
   canvasPhotonPt->SetLogy(1);
   canvasPhotonPt->SetLogx(1);
   canvasPhotonPt->SetLeftMargin(0.16);
   canvasPhotonPt->cd();
   DrawAutoGammaHistos( histoDataPhotonPt,
                  histoMonteCarloPhotonPt, 
                  "", "#it{p}_{T} #gamma (GeV/#it{c}) ",textYAxisPtDist,
                  kTRUE, 5.,1e-3,
                  kFALSE,0. ,0., 
                  kTRUE, 0.05,60.); 
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasPhotonPt->Update();
   canvasPhotonPt->SaveAs(Form("%s/Photon_Pt.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasPhotonPt;     
   delete histoDataPhotonPt;
   delete histoMonteCarloPhotonPt;
   
   delete hist2DPhotonEtaPtData;
   delete hist2DPhotonEtaPtMonteCarlo;


   //-------------------------------------- Photon CosPoint vs Chi2 ----------------------------------------------
   TH2F* histoGammaCosPointChi2Data 					= (TH2F*)directoryPhotonQAData->Get("histoGammaCosPointChi2");  
   TH2F* histoGammaCosPointChi2MonteCarlo 				= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaCosPointChi2");  
   TH2F* histoTrueGammaCosPointChi2MonteCarlo 			= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueGammaCosPointChi2");  
   TH2F* histoTrueDalitzGammaCosPointChi2MonteCarlo 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueDalitzGammaCosPointChi2");  
   TH2F* histoBGCosPointChi2MonteCarlo 					= (TH2F*)histoGammaCosPointChi2MonteCarlo->Clone("histoBGCosPointMonteCarloPt");  
   histoBGCosPointChi2MonteCarlo->Sumw2();
   histoBGCosPointChi2MonteCarlo->Add(histoTrueGammaCosPointChi2MonteCarlo,-1.);
   histoBGCosPointChi2MonteCarlo->Add(histoTrueDalitzGammaCosPointChi2MonteCarlo,-1.);
   
   GammaScalingHistogramm(histoGammaCosPointChi2Data,1./nGammasData);   
   GammaScalingHistogramm(histoGammaCosPointChi2MonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueGammaCosPointChi2MonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueDalitzGammaCosPointChi2MonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoBGCosPointChi2MonteCarlo,1./nGammasMonteCarlo);
   
   histoGammaCosPointChi2Data->SetMaximum(2e-2);
   histoGammaCosPointChi2Data->SetMinimum(2e-8);
   if (histoGammaCosPointChi2Data->GetEntries() > 0){ 
      PlotStandard2D( histoGammaCosPointChi2Data , Form("%s/CosPoint_Chi2_Photon_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#chi^{2}_{#gamma}/ndf",  
					  kTRUE, 0.0, 30, kTRUE, -1.0, 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod); 
   }
   delete histoGammaCosPointChi2Data;
   histoGammaCosPointChi2MonteCarlo->SetMaximum(2e-2);
   histoGammaCosPointChi2MonteCarlo->SetMinimum(2e-8);
   if (histoGammaCosPointChi2MonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoGammaCosPointChi2MonteCarlo , Form("%s/CosPoint_Chi2_Photon_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()),
					  "", "cos(#theta_{point})", "#chi^{2}_{#gamma}/ndf",  
					  kTRUE, 0.0, 30, kTRUE, -1.0, 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoGammaCosPointChi2MonteCarlo;
   histoTrueGammaCosPointChi2MonteCarlo->SetMaximum(2e-2);
   histoTrueGammaCosPointChi2MonteCarlo->SetMinimum(2e-8);
   if (histoTrueGammaCosPointChi2MonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueGammaCosPointChi2MonteCarlo , Form("%s/CosPoint_Chi2_TruePhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#chi^{2}_{#gamma}/ndf",  
					  kTRUE, 0.0, 30, kTRUE, -1.0, 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueGammaCosPointChi2MonteCarlo;
   histoTrueDalitzGammaCosPointChi2MonteCarlo->SetMaximum(2e-2);
   histoTrueDalitzGammaCosPointChi2MonteCarlo->SetMinimum(2e-8);
   if (histoTrueDalitzGammaCosPointChi2MonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueDalitzGammaCosPointChi2MonteCarlo , Form("%s/CosPoint_Chi2_TrueDalitzPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#chi^{2}_{#gamma}/ndf",  
					  kTRUE, 0.0, 30, kTRUE,-1.0, 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueDalitzGammaCosPointChi2MonteCarlo;
   histoBGCosPointChi2MonteCarlo->SetMaximum(2e-2);
   histoBGCosPointChi2MonteCarlo->SetMinimum(2e-8);
   if (histoBGCosPointChi2MonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoBGCosPointChi2MonteCarlo , Form("%s/CosPoint_Chi2_BG_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#chi^{2}_{#gamma}/ndf", 
					  kTRUE, 0.0, 30, kTRUE, -1.0, 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoBGCosPointChi2MonteCarlo;

   //-------------------------------------- Photon Chi2 vs PsiPair ----------------------------------------------
   TH2F* histoGammaChi2PsiPairData 					= (TH2F*)directoryPhotonQAData->Get("histoGammaChi2PsiPair");  
   TH2F* histoGammaChi2PsiPairMonteCarlo 			= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaChi2PsiPair");  
   TH2F* histoTrueGammaChi2PsiPairMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueGammaChi2PsiPair");  
   TH2F* histoTrueDalitzGammaChi2PsiPairMonteCarlo 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueDalitzGammaChi2PsiPair");  
   TH2F* histoBGChi2PsiPairMonteCarlo 				= (TH2F*)histoGammaChi2PsiPairMonteCarlo->Clone("histoBGCosPointMonteCarloPt");  
   histoBGChi2PsiPairMonteCarlo->Sumw2();
   histoBGChi2PsiPairMonteCarlo->Add(histoTrueGammaChi2PsiPairMonteCarlo,-1.);
   histoBGChi2PsiPairMonteCarlo->Add(histoTrueDalitzGammaChi2PsiPairMonteCarlo,-1.);
   
   GammaScalingHistogramm(histoGammaChi2PsiPairData,1./nGammasData);   
   GammaScalingHistogramm(histoGammaChi2PsiPairMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueGammaChi2PsiPairMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueDalitzGammaChi2PsiPairMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoBGChi2PsiPairMonteCarlo,1./nGammasMonteCarlo);
   
   histoGammaChi2PsiPairData->SetMaximum(2e-2);
   histoGammaChi2PsiPairData->SetMinimum(2e-8);
   if (histoGammaChi2PsiPairData->GetEntries() > 0){ 
      PlotStandard2D( histoGammaChi2PsiPairData , Form("%s/Chi2_PsiPair_Photon_Data.%s", outputDirectory.Data(), suffix.Data()),
					  "", "#chi^{2}_{#gamma}/ndf", "#psi_{pair}", 
					  kTRUE, -0.5, 0.5, kTRUE, 0, 30., 0, 0, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod); 
   }
   delete histoGammaChi2PsiPairData;
   histoGammaChi2PsiPairMonteCarlo->SetMaximum(2e-2);
   histoGammaChi2PsiPairMonteCarlo->SetMinimum(2e-8);
   if (histoGammaChi2PsiPairMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoGammaChi2PsiPairMonteCarlo , Form("%s/Chi2_PsiPair_Photon_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#chi^{2}_{#gamma}/ndf", "#psi_{pair}",  
					  kTRUE, -0.5, 0.5, kTRUE, 0, 30.,0 ,0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoGammaChi2PsiPairMonteCarlo;
   histoTrueGammaChi2PsiPairMonteCarlo->SetMaximum(2e-2);
   histoTrueGammaChi2PsiPairMonteCarlo->SetMinimum(2e-8);
   if (histoTrueGammaChi2PsiPairMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueGammaChi2PsiPairMonteCarlo , Form("%s/Chi2_PsiPair_TruePhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#chi^{2}_{#gamma}/ndf", "#psi_{pair}",  
					  kTRUE, -0.5, 0.5, kTRUE, 0, 30., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueGammaChi2PsiPairMonteCarlo;
   histoTrueDalitzGammaChi2PsiPairMonteCarlo->SetMaximum(2e-2);
   histoTrueDalitzGammaChi2PsiPairMonteCarlo->SetMinimum(2e-8);
   if (histoTrueDalitzGammaChi2PsiPairMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueDalitzGammaChi2PsiPairMonteCarlo , Form("%s/Chi2_PsiPair_TrueDalitzPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()),
					  "", "#chi^{2}_{#gamma}/ndf", "#psi_{pair}",  
					  kTRUE, -0.5, 0.5, kTRUE, 0, 30., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueDalitzGammaChi2PsiPairMonteCarlo;
   histoBGChi2PsiPairMonteCarlo->SetMaximum(2e-2);
   histoBGChi2PsiPairMonteCarlo->SetMinimum(2e-8);
   if (histoBGChi2PsiPairMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoBGChi2PsiPairMonteCarlo , Form("%s/Chi2_PsiPair_BG_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#chi^{2}_{#gamma}/ndf", "#psi_{pair}", 
					  kTRUE, -0.5, 0.5, kTRUE, 0, 30., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoBGChi2PsiPairMonteCarlo;
   

   //-------------------------------------- Photon CosPoint vs PsiPair ----------------------------------------------
   TH2F* histoGammaCosPointPsiPairData 					= (TH2F*)directoryPhotonQAData->Get("histoGammaCosPointPsiPair");  
   TH2F* histoGammaCosPointPsiPairMonteCarlo 			= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaCosPointPsiPair");  
   TH2F* histoTrueGammaCosPointPsiPairMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueGammaCosPointPsiPair");  
   TH2F* histoTrueDalitzGammaCosPointPsiPairMonteCarlo 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueDalitzGammaCosPointPsiPair");  
   TH2F* histoBGCosPointPsiPairMonteCarlo 				= (TH2F*)histoGammaCosPointPsiPairMonteCarlo->Clone("histoBGCosPointMonteCarloPt");  
   histoBGCosPointPsiPairMonteCarlo->Sumw2();
   histoBGCosPointPsiPairMonteCarlo->Add(histoTrueGammaCosPointPsiPairMonteCarlo,-1.);
   histoBGCosPointPsiPairMonteCarlo->Add(histoTrueDalitzGammaCosPointPsiPairMonteCarlo,-1.);
   
   GammaScalingHistogramm(histoGammaCosPointPsiPairData,1./nGammasData);   
   GammaScalingHistogramm(histoGammaCosPointPsiPairMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueGammaCosPointPsiPairMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueDalitzGammaCosPointPsiPairMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoBGCosPointPsiPairMonteCarlo,1./nGammasMonteCarlo);
   
   histoGammaCosPointPsiPairData->SetMaximum(2e-2);
   histoGammaCosPointPsiPairData->SetMinimum(2e-8);
   if (histoGammaCosPointPsiPairData->GetEntries() > 0){ 
      PlotStandard2D( histoGammaCosPointPsiPairData , Form("%s/CosPoint_PsiPair_Photon_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#psi_{pair}", 
					  kTRUE, -0.5, 0.5, kTRUE, -1.0, 1., 0, 0 , 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod); 
   }
   delete histoGammaCosPointPsiPairData;
   histoGammaCosPointPsiPairMonteCarlo->SetMaximum(2e-2);
   histoGammaCosPointPsiPairMonteCarlo->SetMinimum(2e-8);
   if (histoGammaCosPointPsiPairMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoGammaCosPointPsiPairMonteCarlo , Form("%s/CosPoint_PsiPair_Photon_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#psi_{pair}", 
					  kTRUE, -0.5, 0.5, kTRUE, -1.0, 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoGammaCosPointPsiPairMonteCarlo;
   histoTrueGammaCosPointPsiPairMonteCarlo->SetMaximum(2e-2);
   histoTrueGammaCosPointPsiPairMonteCarlo->SetMinimum(2e-8);
   if (histoTrueGammaCosPointPsiPairMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueGammaCosPointPsiPairMonteCarlo , Form("%s/CosPoint_PsiPair_TruePhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#psi_{pair}", 
					  kTRUE, -0.5, 0.5, kTRUE, -1.0, 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueGammaCosPointPsiPairMonteCarlo;
   histoTrueDalitzGammaCosPointPsiPairMonteCarlo->SetMaximum(2e-2);
   histoTrueDalitzGammaCosPointPsiPairMonteCarlo->SetMinimum(2e-8);
   if (histoTrueDalitzGammaCosPointPsiPairMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueDalitzGammaCosPointPsiPairMonteCarlo , Form("%s/CosPoint_PsiPair_TrueDalitzPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#psi_{pair}",  
					  kTRUE, -0.5, 0.5, kTRUE,-1.0, 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueDalitzGammaCosPointPsiPairMonteCarlo;
   histoBGCosPointPsiPairMonteCarlo->SetMaximum(2e-2);
   histoBGCosPointPsiPairMonteCarlo->SetMinimum(2e-8);
   if (histoBGCosPointPsiPairMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoBGCosPointPsiPairMonteCarlo , Form("%s/CosPoint_PsiPair_BG_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "cos(#theta_{point})", "#psi_{pair}",  
					  kTRUE, -0.5, 0.5, kTRUE, -1.0, 1., 0, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoBGCosPointPsiPairMonteCarlo;
   

   TH2F* histoGammaAsymPData 					= (TH2F*)directoryPhotonQAData->Get("histoGammaAsymP");  
   TH2F* histoGammaAsymPMonteCarlo 				= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaAsymP");  
   TH2F* histoTruePrimGammaAsymPMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTruePrimGammaAsymP");  
   TH2F* histoTrueSecGammaAsymPMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueSecGammaAsymP");  
   TH2F* histoTrueDalitzGammaAsymPMonteCarlo 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueDalitzGammaAsymP");  
   TH2F* histoBGAsymPMonteCarlo 				= (TH2F*)histoGammaAsymPMonteCarlo->Clone("histoBGAsymPMonteCarlo");  
   histoBGAsymPMonteCarlo->Sumw2();
   histoBGAsymPMonteCarlo->Add(histoTruePrimGammaAsymPMonteCarlo,-1.);
   histoBGAsymPMonteCarlo->Add(histoTrueSecGammaAsymPMonteCarlo,-1.);
   histoBGAsymPMonteCarlo->Add(histoTrueDalitzGammaAsymPMonteCarlo,-1.);
   
   GammaScalingHistogramm(histoGammaAsymPData,1./nGammasData);
   GammaScalingHistogramm(histoGammaAsymPMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTruePrimGammaAsymPMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueSecGammaAsymPMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueDalitzGammaAsymPMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoBGAsymPMonteCarlo,1./nGammasMonteCarlo);   

   histoGammaAsymPData->SetMaximum(2e-3);
   histoGammaAsymPData->SetMinimum(1e-8);
   if (histoGammaAsymPData->GetEntries() > 0){ 
      PlotStandard2D( histoGammaAsymPData , Form("%s/Asymmetry_P_Photon_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#alpha", "#it{p}_{#gamma}", 
					  kTRUE, 0.1, 20, kTRUE, 0.0, 1, 0, 1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod,"Asym"); 
   }
   delete histoGammaAsymPData;
   
   histoGammaAsymPMonteCarlo->SetMaximum(2e-3);
   histoGammaAsymPMonteCarlo->SetMinimum(1e-8);   
   if (histoGammaAsymPMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoGammaAsymPMonteCarlo , Form("%s/Asymmetry_P_Photon_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#alpha", "#it{p}_{#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, 0.0, 1, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Asym"); 
   }
   delete histoGammaAsymPMonteCarlo;

   histoTruePrimGammaAsymPMonteCarlo->SetMaximum(2e-3);
   histoTruePrimGammaAsymPMonteCarlo->SetMinimum(1e-8);
   if (histoTruePrimGammaAsymPMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTruePrimGammaAsymPMonteCarlo , Form("%s/Asymmetry_P_TruePrimPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#alpha", "#it{p}_{#gamma}",
					  kTRUE, 0.1, 20, kTRUE, 0.0, 1, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Asym"); 
   }
   delete histoTruePrimGammaAsymPMonteCarlo;
   
   histoTrueSecGammaAsymPMonteCarlo->SetMaximum(2e-3);
   histoTrueSecGammaAsymPMonteCarlo->SetMinimum(1e-8);
   if (histoTrueSecGammaAsymPMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueSecGammaAsymPMonteCarlo , Form("%s/Asymmetry_P_TrueSecPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#alpha", "#it{p}_{#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, 0.0, 1, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Asym"); 
   }
   delete histoTrueSecGammaAsymPMonteCarlo;
   
   histoTrueDalitzGammaAsymPMonteCarlo->SetMaximum(2e-3);
   histoTrueDalitzGammaAsymPMonteCarlo->SetMinimum(1e-8);
   if (histoTrueDalitzGammaAsymPMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueDalitzGammaAsymPMonteCarlo , Form("%s/Asymmetry_P_TrueDalitzPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#alpha", "#it{p}_{#gamma}", 
					  kTRUE, 0.1, 20, kTRUE, 0.0, 1, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Asym"); 
   }
   delete histoTrueDalitzGammaAsymPMonteCarlo;
   
   histoBGAsymPMonteCarlo->SetMaximum(2e-3);
   histoBGAsymPMonteCarlo->SetMinimum(1e-8);
   if (histoBGAsymPMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoBGAsymPMonteCarlo , Form("%s/Asymmetry_P_BG_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#alpha", "#it{p}_{#gamma}", 
					  kTRUE, 0.1, 20, kTRUE, 0.0, 1, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "Asym"); 
   }
   delete histoBGAsymPMonteCarlo;

      //-------------------------------------- Photon CosPoint vs PsiPair ----------------------------------------------
   TH2F* histoGammaInvMassPtData 					= (TH2F*)directoryPhotonQAData->Get("histoGammaInvMassPt");  
   TH2F* histoGammaInvMassPtMonteCarlo 				= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaInvMassPt");  
   TH2F* histoTrueGammaInvMassPtMonteCarlo 			= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueGammaInvMassPt");  
   TH2F* histoTrueDalitzGammaInvMassPtMonteCarlo	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueDalitzGammaInvMassPt");  
   TH2F* histoBGInvMassPtMonteCarlo 				= (TH2F*)histoGammaInvMassPtMonteCarlo->Clone("histoBGCosPointMonteCarloPt");  
   histoBGInvMassPtMonteCarlo->Sumw2();
   histoBGInvMassPtMonteCarlo->Add(histoTrueGammaInvMassPtMonteCarlo,-1.);
   histoBGInvMassPtMonteCarlo->Add(histoTrueDalitzGammaInvMassPtMonteCarlo,-1.);
   
   TH1D* histoGammaInvMassData 						= (TH1D*)histoGammaInvMassPtData->ProjectionX("histoGammaInvMassData");
   ConvGammaRebinWithBinCorrection(histoGammaInvMassData,1);
   GammaScalingHistogramm(histoGammaInvMassData,1./nGammasData);
   TH1D* histoGammaInvMassMonteCarlo 				= (TH1D*)histoGammaInvMassPtMonteCarlo->ProjectionX("histoGammaInvMassMonteCarlo");
   ConvGammaRebinWithBinCorrection(histoGammaInvMassMonteCarlo,1);
   GammaScalingHistogramm(histoGammaInvMassMonteCarlo,1./nGammasMonteCarlo);
   TH1D* histoTrueGammaInvMassMonteCarlo 			= (TH1D*)histoTrueGammaInvMassPtMonteCarlo->ProjectionX("histoTrueGammaInvMassMonteCarlo");
   ConvGammaRebinWithBinCorrection(histoTrueGammaInvMassMonteCarlo,1);
   GammaScalingHistogramm(histoTrueGammaInvMassMonteCarlo,1./nGammasMonteCarlo);
   TH1D* histoTrueDalitzGammaInvMassMonteCarlo 		= (TH1D*)histoTrueDalitzGammaInvMassPtMonteCarlo->ProjectionX("histoTrueDalitzGammaInvMassMonteCarlo");
   ConvGammaRebinWithBinCorrection(histoTrueDalitzGammaInvMassMonteCarlo,1);
   GammaScalingHistogramm(histoTrueDalitzGammaInvMassMonteCarlo,1./nGammasMonteCarlo);
   TH1D* histoBGInvMassMonteCarlo 					= (TH1D*)histoBGInvMassPtMonteCarlo->ProjectionX("histoBGInvMassMonteCarlo");
   ConvGammaRebinWithBinCorrection(histoBGInvMassMonteCarlo,1);
   GammaScalingHistogramm(histoBGInvMassMonteCarlo,1./nGammasMonteCarlo);
   
   GammaScalingHistogramm(histoGammaInvMassPtData,1./nGammasData);   
   GammaScalingHistogramm(histoGammaInvMassPtMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueGammaInvMassPtMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueDalitzGammaInvMassPtMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoBGInvMassPtMonteCarlo,1./nGammasMonteCarlo);
   
   
   
   TCanvas * canvasInvMass = new TCanvas("canvasInvMass","",10,10,500,500);  // gives the page size
   canvasInvMass->SetLeftMargin(0.16);
   canvasInvMass->SetLogy(1);
   canvasInvMass->cd();
   DrawAutoGammaHistos( histoGammaInvMassData,
                  histoGammaInvMassMonteCarlo, 
                  "", "M_{e^{+}e^{-}} GeV/#it{c}^{2}",textYAxisInvMass,
                  kTRUE, 10.,1e-5,
                  kFALSE,0. ,0., 
                  kTRUE, 0.,0.2);  
   DrawGammaSetMarker(histoTrueGammaInvMassMonteCarlo,20,0.8, kBlue+2 , kBlue+2);
   histoTrueGammaInvMassMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueDalitzGammaInvMassMonteCarlo,20,0.8, kOrange+2 , kOrange+2);
   histoTrueDalitzGammaInvMassMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoBGInvMassMonteCarlo,20,0.8, kViolet , kViolet);
   histoBGInvMassMonteCarlo->Draw("histsame");
   
   TLegend* legAdditionalInfoInvMass = new TLegend( 0.65,0.78,0.97,0.97);
   legAdditionalInfoInvMass->SetTextSize(0.03);         
   legAdditionalInfoInvMass->SetFillColor(0);
   legAdditionalInfoInvMass->AddEntry(histoGammaInvMassData,("Data"));
   legAdditionalInfoInvMass->AddEntry(histoGammaInvMassMonteCarlo,("MC"));
   legAdditionalInfoInvMass->AddEntry(histoTrueGammaInvMassMonteCarlo,("true #gamma"),"l");
   legAdditionalInfoInvMass->AddEntry(histoTrueDalitzGammaInvMassMonteCarlo,("true dalitz"),"l");
   legAdditionalInfoInvMass->AddEntry(histoBGInvMassMonteCarlo,("BG"),"l");
   legAdditionalInfoInvMass->Draw();
   
   
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasInvMass->Update();
   canvasInvMass->SaveAs(Form("%s/Photon_InvMass.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasInvMass;    
   delete histoGammaInvMassData;
   delete histoGammaInvMassMonteCarlo;
   
   histoGammaInvMassPtData->SetMaximum(2e-2);
   histoGammaInvMassPtData->SetMinimum(2e-8);
   if (histoGammaInvMassPtData->GetEntries() > 0){ 
      PlotStandard2D( histoGammaInvMassPtData , Form("%s/InvMass_Pt_Photon_Data.%s", outputDirectory.Data(), suffix.Data()),
					  "", "M_{e^{+}e^{-}} GeV/#it{c}^{2}", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.04, 30, kTRUE, 0, 0.2, 0, 1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod); 
   }
   delete histoGammaInvMassPtData;
   histoGammaInvMassPtMonteCarlo->SetMaximum(2e-2);
   histoGammaInvMassPtMonteCarlo->SetMinimum(2e-8);
   if (histoGammaInvMassPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoGammaInvMassPtMonteCarlo , Form("%s/InvMass_Pt_Photon_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "M_{e^{+}e^{-}} GeV/#it{c}^{2}", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.04, 30, kTRUE, 0, 0.2, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoGammaInvMassPtMonteCarlo;
   histoTrueGammaInvMassPtMonteCarlo->SetMaximum(2e-2);
   histoTrueGammaInvMassPtMonteCarlo->SetMinimum(2e-8);
   if (histoTrueGammaInvMassPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueGammaInvMassPtMonteCarlo , Form("%s/InvMass_Pt_TruePhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()),
					  "", "M_{e^{+}e^{-}} GeV/#it{c}^{2}", "#it{p}_{T,#gamma}", 
					  kTRUE, 0.04, 30, kTRUE, 0, 0.2, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueGammaInvMassPtMonteCarlo;
   histoTrueDalitzGammaInvMassPtMonteCarlo->SetMaximum(2e-2);
   histoTrueDalitzGammaInvMassPtMonteCarlo->SetMinimum(2e-8);
   if (histoTrueDalitzGammaInvMassPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueDalitzGammaInvMassPtMonteCarlo , Form("%s/InvMass_Pt_TrueDalitzPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "M_{e^{+}e^{-}} GeV/#it{c}^{2}", "#it{p}_{T,#gamma}", 
					  kTRUE, 0.04, 30, kTRUE,0, 0.2, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueDalitzGammaInvMassPtMonteCarlo;
   histoBGInvMassPtMonteCarlo->SetMaximum(2e-2);
   histoBGInvMassPtMonteCarlo->SetMinimum(2e-8);
   if (histoBGInvMassPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoBGInvMassPtMonteCarlo , Form("%s/InvMass_Pt_BG_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "M_{e^{+}e^{-}} GeV/#it{c}^{2}", "#it{p}_{T,#gamma}", 
					  kTRUE, 0.04, 30, kTRUE, 0, 0.2, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoBGInvMassPtMonteCarlo;

   
   
   TH2F* histoGammaQtPtData 					= (TH2F*)directoryPhotonQAData->Get("histoGammaQtPt");  
   TH2F* histoGammaQtPtMonteCarlo 				= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoGammaQtPt");  
   TH2F* histoTruePrimGammaQtPtMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTruePrimGammaQtPt");  
   TH2F* histoTrueSecGammaQtPtMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueSecGammaQtPt");  
   TH2F* histoTrueDalitzGammaQtPtMonteCarlo 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueDalitzGammaQtPt");  
   TH2F* histoBGQtPtMonteCarlo 					= (TH2F*)histoGammaQtPtMonteCarlo->Clone("histoBGQtPtMonteCarlo");  
   histoBGQtPtMonteCarlo->Sumw2();
   histoBGQtPtMonteCarlo->Add(histoTruePrimGammaQtPtMonteCarlo,-1.);
   histoBGQtPtMonteCarlo->Add(histoTrueSecGammaQtPtMonteCarlo,-1.);
   histoBGQtPtMonteCarlo->Add(histoTrueDalitzGammaQtPtMonteCarlo,-1.);
   
   GammaScalingHistogramm(histoGammaQtPtData,1./nGammasData);
   GammaScalingHistogramm(histoGammaQtPtMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTruePrimGammaQtPtMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueSecGammaQtPtMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoTrueDalitzGammaQtPtMonteCarlo,1./nGammasMonteCarlo);
   GammaScalingHistogramm(histoBGQtPtMonteCarlo,1./nGammasMonteCarlo);   

   histoGammaQtPtData->SetMaximum(2e-3);
   histoGammaQtPtData->SetMinimum(1e-8);
   if (histoGammaQtPtData->GetEntries() > 0){ 
      PlotStandard2D( histoGammaQtPtData , Form("%s/Qt_Pt_Photon_Data.%s", outputDirectory.Data(), suffix.Data()),
					  "", "#it{q}_{T,#gamma}", "#it{p}_{T,#gamma}", 
					  kTRUE, 0.1, 20, kTRUE, 0.0, 0.1, 0, 1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod); 
   }
   delete histoGammaQtPtData;
   
   histoGammaQtPtMonteCarlo->SetMaximum(2e-3);
   histoGammaQtPtMonteCarlo->SetMinimum(1e-8);   
   if (histoGammaQtPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoGammaQtPtMonteCarlo , Form("%s/Qt_Pt_Photon_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{q}_{T,#gamma}", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, 0.0, 0.1, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoGammaQtPtMonteCarlo;

   histoTruePrimGammaQtPtMonteCarlo->SetMaximum(2e-3);
   histoTruePrimGammaQtPtMonteCarlo->SetMinimum(1e-8);
   if (histoTruePrimGammaQtPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTruePrimGammaQtPtMonteCarlo , Form("%s/Qt_Pt_TruePrimPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{q}_{T,#gamma}", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, 0.0, 0.1, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTruePrimGammaQtPtMonteCarlo;
   
   histoTrueSecGammaQtPtMonteCarlo->SetMaximum(2e-3);
   histoTrueSecGammaQtPtMonteCarlo->SetMinimum(1e-8);
   if (histoTrueSecGammaQtPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueSecGammaQtPtMonteCarlo , Form("%s/Qt_Pt_TrueSecPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{q}_{T,#gamma}", "#it{p}_{T,#gamma}",
					  kTRUE, 0.1, 20, kTRUE, 0.0, 0.1, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueSecGammaQtPtMonteCarlo;
   
   histoTrueDalitzGammaQtPtMonteCarlo->SetMaximum(2e-3);
   histoTrueDalitzGammaQtPtMonteCarlo->SetMinimum(1e-8);
   if (histoTrueDalitzGammaQtPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoTrueDalitzGammaQtPtMonteCarlo , Form("%s/Qt_Pt_TrueDalitzPhoton_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{q}_{T,#gamma}", "#it{p}_{T,#gamma}",  
					  kTRUE, 0.1, 20, kTRUE, 0.0, 0.1, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoTrueDalitzGammaQtPtMonteCarlo;
   
   histoBGQtPtMonteCarlo->SetMaximum(2e-3);
   histoBGQtPtMonteCarlo->SetMinimum(1e-8);
   if (histoBGQtPtMonteCarlo->GetEntries() > 0){ 
      PlotStandard2D( histoBGQtPtMonteCarlo , Form("%s/Qt_Pt_BG_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{q}_{T,#gamma}", "#it{p}_{T,#gamma}", 
					  kTRUE, 0.1, 20, kTRUE, 0.0, 0.1, 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod); 
   }
   delete histoBGQtPtMonteCarlo;
   
   TH2F* histoDataTrueElectronSigmadEdxTPCP 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueElectronNSigmadEdxTPCP");
   histoDataTrueElectronSigmadEdxTPCP->Scale(1./nElectronsMonteCarlo);
   if (histoDataTrueElectronSigmadEdxTPCP->GetEntries() > 0){
      PlotStandard2D( histoDataTrueElectronSigmadEdxTPCP , Form("%s/nSigma_dEdxTPC_TrueElectron.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{n} #sigma_{e^{-}} d#it{E}/d#it{x} TPC", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "dEdx");   
   }
   delete histoDataTrueElectronSigmadEdxTPCP;

   
   TH2F* histoDataTruePositronSigmadEdxTPCP 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTruePositronNSigmadEdxTPCP");
   histoDataTruePositronSigmadEdxTPCP->Scale(1./nPositronsMonteCarlo);
   if (histoDataTruePositronSigmadEdxTPCP->GetEntries() > 0){
      PlotStandard2D( histoDataTruePositronSigmadEdxTPCP , Form("%s/nSigma_dEdxTPC_TruePositron.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{+}} (GeV/#it{c})", "#it{n} #sigma_{e^{+}} d#it{E}/d#it{x} TPC", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod, "dEdx");   
   }
   delete histoDataTruePositronSigmadEdxTPCP;

   TH2F* histoDataTrueElectronSigmadEdxITSP 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueElectronNSigmadEdxITSP");
   histoDataTrueElectronSigmadEdxITSP->Scale(1./nElectronsMonteCarlo);
   if (histoDataTrueElectronSigmadEdxITSP->GetEntries() > 0){
      PlotStandard2D( histoDataTrueElectronSigmadEdxITSP , Form("%s/nSigma_dEdxITS_TrueElectron.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{n} #sigma_{e^{-}} d#it{E}/d#it{x} ITS", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);   
   }
   delete histoDataTrueElectronSigmadEdxITSP;

   
   TH2F* histoDataTruePositronSigmadEdxITSP 	= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTruePositronNSigmadEdxITSP");
   histoDataTruePositronSigmadEdxITSP->Scale(1./nPositronsMonteCarlo);
   if (histoDataTruePositronSigmadEdxITSP->GetEntries() > 0){
      PlotStandard2D( histoDataTruePositronSigmadEdxITSP , Form("%s/nSigma_dEdxITS_TruePositron.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{+}} (GeV/#it{c})", "#it{n} #sigma_{e^{+}} d#it{E}/d#it{x} ITS", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);   
   }
   delete histoDataTruePositronSigmadEdxITSP;


   TH2F* histoDataTrueElectronSigmaTOFP 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTruePositronNSigmaTOFP");
   histoDataTrueElectronSigmaTOFP->Scale(1./nElectronsMonteCarlo);
   if (histoDataTrueElectronSigmaTOFP->GetEntries() > 0){
      PlotStandard2D( histoDataTrueElectronSigmaTOFP , Form("%s/nSigma_TOF_TrueElectron.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "#it{p}_{e^{-}} (GeV/#it{c})", "#it{n} #sigma_{e^{-}} TOF", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);   
   }
   delete histoDataTrueElectronSigmaTOFP;

   TH2F* histoDataTruePositronSigmaTOFP 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTruePositronNSigmaTOFP");
   histoDataTruePositronSigmaTOFP->Scale(1./nPositronsMonteCarlo);
   if (histoDataTruePositronSigmaTOFP->GetEntries() > 0){
      PlotStandard2D( histoDataTruePositronSigmaTOFP , Form("%s/nSigma_TOF_TruePositron.%s", outputDirectory.Data(), suffix.Data()),
					  "", "#it{p}_{e^{+}} (GeV/#it{c})", "#it{n} #sigma_{e^{+}} TOF", 
					  kTRUE, -5., 7., kTRUE, 0.01, 20., 1, 0, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);   
   }
   delete histoDataTruePositronSigmaTOFP;
 
   
   TH2F* histoElectronITSClPtData 				= (TH2F*)directoryPhotonQAData->Get("histoElectronITSClPt");  
   TH2F* histoElectronITSClPtMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoElectronITSClPt");  
   histoElectronITSClPtData->Scale(1./nElectronsData);
   if (histoElectronITSClPtData->GetEntries() > 0){
      PlotStandard2D( histoElectronITSClPtData , Form("%s/nITSCl_Electron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "n ITS cl", "#it{p}_{T,e^{-}} (GeV/#it{c})", 
					  kFALSE, -5., 7., kFALSE, 0.01, 20., 0, 1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);   
   }
   delete histoElectronITSClPtData;
   histoElectronITSClPtMonteCarlo->Scale(1./nElectronsMonteCarlo);
   if (histoElectronITSClPtMonteCarlo->GetEntries() > 0){
      PlotStandard2D( histoElectronITSClPtMonteCarlo , Form("%s/nITSCl_Electron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()),
					  "", "n ITS cl", "#it{p}_{T,e^{-}} (GeV/#it{c})", 
					  kFALSE, -5., 7., kFALSE, 0.01, 20., 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);   
   }
   delete histoElectronITSClPtMonteCarlo;
 
   TH2F* histoPositronITSClPtData 				= (TH2F*)directoryPhotonQAData->Get("histoPositronITSClPt");  
   TH2F* histoPositronITSClPtMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoPositronITSClPt");  
   histoPositronITSClPtData->Scale(1./nPositronsData);
   if (histoPositronITSClPtData->GetEntries() > 0){
      PlotStandard2D( histoPositronITSClPtData , Form("%s/nITSCl_Positron_Data.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "n ITS cl", "#it{p}_{T,e^{+}} (GeV/#it{c})", 
					  kFALSE, -5., 7., kFALSE, 0.01, 20., 0, 1, 1, floatLocationRightUp2D, 500, 500, "Data", textPeriod);   
   }
   delete histoPositronITSClPtData;
   histoPositronITSClPtMonteCarlo->Scale(1./nPositronsMonteCarlo);
   if (histoPositronITSClPtMonteCarlo->GetEntries() > 0){
      PlotStandard2D( histoPositronITSClPtMonteCarlo , Form("%s/nITSCl_Positron_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()), 
					  "", "n ITS cl", "#it{p}_{T,e^{+}} (GeV/#it{c})", 
					  kFALSE, -5., 7., kFALSE, 0.01, 20., 0, 1, 1, floatLocationRightUp2D, 500, 500, optMCGenerator, textPeriod);   
   }
   delete histoPositronITSClPtMonteCarlo;
 
   TH2F* histoElectronITSClRData 				= (TH2F*)directoryPhotonQAData->Get("histoElectronITSClR");  
   TH1D* histoElectronITSClData 				= (TH1D*)histoElectronITSClRData->ProjectionX("histoElectronITSClData");
   ConvGammaRebinWithBinCorrection(histoElectronITSClData,1);
   GammaScalingHistogramm(histoElectronITSClData,1./nElectronsData);
   
   TH1D* histoElectronITSCl0RData 				= (TH1D*)histoElectronITSClRData->ProjectionY("histoElectronITSCl0RData",1,1);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl0RData,1);
   GammaScalingHistogramm(histoElectronITSCl0RData,1./nElectronsData);
   
   TH1D* histoElectronITSCl1RData 				= (TH1D*)histoElectronITSClRData->ProjectionY("histoElectronITSCl1RData",2,2);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl1RData,1);
   GammaScalingHistogramm(histoElectronITSCl1RData,1./nElectronsData);
   
   TH1D* histoElectronITSCl2RData 				= (TH1D*)histoElectronITSClRData->ProjectionY("histoElectronITSCl2RData",3,3);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl2RData,1);
   GammaScalingHistogramm(histoElectronITSCl2RData,1./nElectronsData);
   
   TH1D* histoElectronITSCl3RData 				= (TH1D*)histoElectronITSClRData->ProjectionY("histoElectronITSCl3RData",4,4);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl3RData,1);
   GammaScalingHistogramm(histoElectronITSCl3RData,1./nElectronsData);
   
   TH1D* histoElectronITSCl4RData 				= (TH1D*)histoElectronITSClRData->ProjectionY("histoElectronITSCl4RData",5,5);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl4RData,1);
   GammaScalingHistogramm(histoElectronITSCl4RData,1./nElectronsData);
   
   TH1D* histoElectronITSCl5RData 				= (TH1D*)histoElectronITSClRData->ProjectionY("histoElectronITSCl5RData",6,6);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl5RData,1);
   GammaScalingHistogramm(histoElectronITSCl5RData,1./nElectronsData);
   
   TH1D* histoElectronITSCl6RData 				= (TH1D*)histoElectronITSClRData->ProjectionY("histoElectronITSCl6RData",7,7);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl6RData,1);
   GammaScalingHistogramm(histoElectronITSCl6RData,1./nElectronsData);
   
   TH2F* histoElectronITSClRMonteCarlo 			= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoElectronITSClR");  
   TH1D* histoElectronITSClMonteCarlo 			= (TH1D*)histoElectronITSClRMonteCarlo->ProjectionX("histoElectronITSClMonteCarlo");
   ConvGammaRebinWithBinCorrection(histoElectronITSClMonteCarlo,1);
   GammaScalingHistogramm(histoElectronITSClMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoElectronITSCl0RMonteCarlo 		= (TH1D*)histoElectronITSClRMonteCarlo->ProjectionY("histoElectronITSCl0RMonteCarlo",1,1);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl0RMonteCarlo,1);
   GammaScalingHistogramm(histoElectronITSCl0RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoElectronITSCl1RMonteCarlo 		= (TH1D*)histoElectronITSClRMonteCarlo->ProjectionY("histoElectronITSCl1RMonteCarlo",2,2);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl1RMonteCarlo,1);
   GammaScalingHistogramm(histoElectronITSCl1RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoElectronITSCl2RMonteCarlo 		= (TH1D*)histoElectronITSClRMonteCarlo->ProjectionY("histoElectronITSCl2RMonteCarlo",3,3);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl2RMonteCarlo,1);
   GammaScalingHistogramm(histoElectronITSCl2RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoElectronITSCl3RMonteCarlo 		= (TH1D*)histoElectronITSClRMonteCarlo->ProjectionY("histoElectronITSCl3RMonteCarlo",4,4);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl3RMonteCarlo,1);
   GammaScalingHistogramm(histoElectronITSCl3RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoElectronITSCl4RMonteCarlo 		= (TH1D*)histoElectronITSClRMonteCarlo->ProjectionY("histoElectronITSCl4RMonteCarlo",5,5);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl4RMonteCarlo,1);
   GammaScalingHistogramm(histoElectronITSCl4RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoElectronITSCl5RMonteCarlo 		= (TH1D*)histoElectronITSClRMonteCarlo->ProjectionY("histoElectronITSCl5RMonteCarlo",6,6);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl5RMonteCarlo,1);
   GammaScalingHistogramm(histoElectronITSCl5RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoElectronITSCl6RMonteCarlo 		= (TH1D*)histoElectronITSClRMonteCarlo->ProjectionY("histoElectronITSCl6RMonteCarlo",7,7);
   ConvGammaRebinWithBinCorrection(histoElectronITSCl6RMonteCarlo,1);
   GammaScalingHistogramm(histoElectronITSCl6RMonteCarlo,1./nElectronsMonteCarlo);
   
   TH2F* histoTrueElectronITSClRMonteCarlo 		= (TH2F*)directoryPhotonQAMonteCarlo->Get("histoTrueElectronITSClR");  
   TH1D* histoTrueElectronITSCl0RMonteCarlo 	= (TH1D*)histoTrueElectronITSClRMonteCarlo->ProjectionY("histoTrueElectronITSCl0RMonteCarlo",1,1);
   ConvGammaRebinWithBinCorrection(histoTrueElectronITSCl0RMonteCarlo,1);
   GammaScalingHistogramm(histoTrueElectronITSCl0RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoTrueElectronITSCl1RMonteCarlo 	= (TH1D*)histoTrueElectronITSClRMonteCarlo->ProjectionY("histoTrueElectronITSCl1RMonteCarlo",2,2);
   ConvGammaRebinWithBinCorrection(histoTrueElectronITSCl1RMonteCarlo,1);
   GammaScalingHistogramm(histoTrueElectronITSCl1RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoTrueElectronITSCl2RMonteCarlo 	= (TH1D*)histoTrueElectronITSClRMonteCarlo->ProjectionY("histoTrueElectronITSCl2RMonteCarlo",3,3);
   ConvGammaRebinWithBinCorrection(histoTrueElectronITSCl2RMonteCarlo,1);
   GammaScalingHistogramm(histoTrueElectronITSCl2RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoTrueElectronITSCl3RMonteCarlo 	= (TH1D*)histoTrueElectronITSClRMonteCarlo->ProjectionY("histoTrueElectronITSCl3RMonteCarlo",4,4);
   ConvGammaRebinWithBinCorrection(histoTrueElectronITSCl3RMonteCarlo,1);
   GammaScalingHistogramm(histoTrueElectronITSCl3RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoTrueElectronITSCl4RMonteCarlo 	= (TH1D*)histoTrueElectronITSClRMonteCarlo->ProjectionY("histoTrueElectronITSCl4RMonteCarlo",5,5);
   ConvGammaRebinWithBinCorrection(histoTrueElectronITSCl4RMonteCarlo,1);
   GammaScalingHistogramm(histoTrueElectronITSCl4RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoTrueElectronITSCl5RMonteCarlo 	= (TH1D*)histoTrueElectronITSClRMonteCarlo->ProjectionY("histoTrueElectronITSCl5RMonteCarlo",6,6);
   ConvGammaRebinWithBinCorrection(histoTrueElectronITSCl5RMonteCarlo,1);
   GammaScalingHistogramm(histoTrueElectronITSCl5RMonteCarlo,1./nElectronsMonteCarlo);
   TH1D* histoTrueElectronITSCl6RMonteCarlo 	= (TH1D*)histoTrueElectronITSClRMonteCarlo->ProjectionY("histoTrueElectronITSCl6RMonteCarlo",7,7);
   ConvGammaRebinWithBinCorrection(histoTrueElectronITSCl6RMonteCarlo,1);
   GammaScalingHistogramm(histoTrueElectronITSCl6RMonteCarlo,1./nElectronsMonteCarlo);
   
   
   TCanvas * canvasITSClvsR = new TCanvas("canvasITSClvsR","",10,10,500,500);  // gives the page size
   canvasITSClvsR->SetLeftMargin(0.16);
   canvasITSClvsR->SetLogy(1);
   canvasITSClvsR->cd();
   DrawAutoGammaHistos( histoElectronITSCl0RData,
                  histoElectronITSCl0RMonteCarlo, 
                  "", "R (cm)",textYAxisITSClvsR,
                  kTRUE, 10.,1e-5,
                  kFALSE,0. ,0., 
                  kTRUE, 0.,120);  
   histoElectronITSCl0RData->Draw("hist");
   DrawGammaSetMarker(histoElectronITSCl1RData,20,0.8, kBlue+2 , kBlue+2);
   histoElectronITSCl1RData->Draw("histsame");
   DrawGammaSetMarker(histoElectronITSCl2RData,20,0.8, kOrange+2 , kOrange+2);
   histoElectronITSCl2RData->Draw("histsame");
   DrawGammaSetMarker(histoElectronITSCl3RData,20,0.8, kViolet+2 , kViolet+2);
   histoElectronITSCl3RData->Draw("histsame");
   DrawGammaSetMarker(histoElectronITSCl4RData,20,0.8, kRed+2 , kRed+2);
   histoElectronITSCl4RData->Draw("histsame");
   DrawGammaSetMarker(histoElectronITSCl5RData,20,0.8, kGreen+2 , kGreen+2);
   histoElectronITSCl5RData->Draw("histsame");
   DrawGammaSetMarker(histoElectronITSCl6RData,20,0.8, kPink+2 , kPink+2);
   histoElectronITSCl6RData->Draw("histsame");
   
   
   TLegend* legAdditionalInfoITSClvsR = new TLegend( 0.65,0.82,0.97,0.97);
   legAdditionalInfoITSClvsR->SetTextSize(0.03);         
   legAdditionalInfoITSClvsR->SetFillColor(0);
   legAdditionalInfoITSClvsR->SetNColumns(2);
   legAdditionalInfoITSClvsR->AddEntry(histoElectronITSCl0RData,("0 ITS cl"),"l");
   legAdditionalInfoITSClvsR->AddEntry(histoElectronITSCl1RData,("1 ITS cl"),"l");
   legAdditionalInfoITSClvsR->AddEntry(histoElectronITSCl2RData,("2 ITS cl"),"l");
   legAdditionalInfoITSClvsR->AddEntry(histoElectronITSCl3RData,("3 ITS cl"),"l");
   legAdditionalInfoITSClvsR->AddEntry(histoElectronITSCl4RData,("4 ITS cl"),"l");
   legAdditionalInfoITSClvsR->AddEntry(histoElectronITSCl5RData,("5 ITS cl"),"l");
   legAdditionalInfoITSClvsR->AddEntry(histoElectronITSCl6RData,("6 ITS cl"),"l");
   legAdditionalInfoITSClvsR->Draw();
   
   
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, "Data", textPeriod);
   canvasITSClvsR->Update();
   canvasITSClvsR->SaveAs(Form("%s/Electron_ITSClvsR_Data.%s", outputDirectory.Data(), suffix.Data()));
   
   canvasITSClvsR->cd();
   DrawAutoGammaHistos( histoElectronITSCl0RMonteCarlo,
                  histoElectronITSCl0RMonteCarlo, 
                  "", "R (cm)",textYAxisITSClvsR,
                  kTRUE, 10.,1e-5,
                  kFALSE,0. ,0., 
                  kTRUE, 0.,120);  
   DrawGammaSetMarker(histoElectronITSCl0RMonteCarlo,20,0.8, kBlack , kBlack);
   histoElectronITSCl0RMonteCarlo->Draw("hist");
   DrawGammaSetMarker(histoElectronITSCl1RMonteCarlo,20,0.8, kBlue+2 , kBlue+2);
   histoElectronITSCl1RMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoElectronITSCl2RMonteCarlo,20,0.8, kOrange+2 , kOrange+2);
   histoElectronITSCl2RMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoElectronITSCl3RMonteCarlo,20,0.8, kViolet+2 , kViolet+2);
   histoElectronITSCl3RMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoElectronITSCl4RMonteCarlo,20,0.8, kRed+2 , kRed+2);
   histoElectronITSCl4RMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoElectronITSCl5RMonteCarlo,20,0.8, kGreen+2 , kGreen+2);
   histoElectronITSCl5RMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoElectronITSCl6RMonteCarlo,20,0.8, kPink+2 , kPink+2);
   histoElectronITSCl6RMonteCarlo->Draw("histsame");
   
   
   legAdditionalInfoITSClvsR->Draw();
   
   
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasITSClvsR->Update();
   canvasITSClvsR->SaveAs(Form("%s/Electron_ITSClvsR_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()));
   
   canvasITSClvsR->cd();
   histoTrueElectronITSCl0RMonteCarlo->SetMaximum(histoElectronITSCl0RMonteCarlo->GetMaximum());
   histoTrueElectronITSCl0RMonteCarlo->SetMinimum(histoElectronITSCl0RMonteCarlo->GetMinimum());
   histoTrueElectronITSCl0RMonteCarlo->GetYaxis()->SetTitle(textYAxisITSClvsR);
   histoTrueElectronITSCl0RMonteCarlo->GetXaxis()->SetTitle("R (cm)");
   DrawGammaSetMarker(histoTrueElectronITSCl0RMonteCarlo,20,0.8, kBlack , kBlack);
   histoTrueElectronITSCl0RMonteCarlo->Draw("hist");
   DrawGammaSetMarker(histoTrueElectronITSCl1RMonteCarlo,20,0.8, kBlue+2 , kBlue+2);
   histoTrueElectronITSCl1RMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueElectronITSCl2RMonteCarlo,20,0.8, kOrange+2 , kOrange+2);
   histoTrueElectronITSCl2RMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueElectronITSCl3RMonteCarlo,20,0.8, kViolet+2 , kViolet+2);
   histoTrueElectronITSCl3RMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueElectronITSCl4RMonteCarlo,20,0.8, kRed+2 , kRed+2);
   histoTrueElectronITSCl4RMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueElectronITSCl5RMonteCarlo,20,0.8, kGreen+2 , kGreen+2);
   histoTrueElectronITSCl5RMonteCarlo->Draw("histsame");
   DrawGammaSetMarker(histoTrueElectronITSCl6RMonteCarlo,20,0.8, kPink+2 , kPink+2);
   histoTrueElectronITSCl6RMonteCarlo->Draw("histsame");
   
   
   legAdditionalInfoITSClvsR->Draw();
   
   
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasITSClvsR->Update();
   canvasITSClvsR->SaveAs(Form("%s/TrueElectron_ITSClvsR_MonteCarlo.%s", outputDirectory.Data(), suffix.Data()));
   delete canvasITSClvsR;    
   
   TCanvas * canvasElectronITScl = new TCanvas("canvasElectronITScl","",10,10,500,500);  // gives the page size
   canvasElectronITScl->SetLeftMargin(0.16);
   canvasElectronITScl->SetLogy();
   canvasElectronITScl->cd();
   
   DrawAutoGammaHistos( histoElectronITSClData,
                  histoElectronITSClMonteCarlo, 
                  "", "# ITS cl ","",
                  kTRUE, 5,8e-3,
                  kFALSE,0. ,0., 
                  kFALSE,-1.6,1.6);
//    DrawAliceLogoPerformance(floatLocationRightUp [0],floatLocationRightUp[1],floatLocationRightUp[2],floatLocationRightUp[3],0.01,textDate,collisionSystem, textGenerator, textPeriod,500,500); 
   DrawLabelsEvents(floatLocationLeft[0],floatLocationLeft[1],floatLocationLeft[2], 0.00, collisionSystem, optMCGenerator, textPeriod);
   canvasElectronITScl->Update();
   canvasElectronITScl->SaveAs(Form("%s/Electron_ITScl.%s", outputDirectory.Data(), suffix.Data()));
   
   
//    TCanvas * canvasTestChi2 = new TCanvas("canvasTestChi2","",10,10,500,500);  // gives the page size
//       TF1 *fAsym = new TF1 ("fAsym", "TMath::Tan(TMath::Pi()*(x+0.5))+1",0, 1);
//       fAsym->Draw("");
//       TF1 *fAsym1 = new TF1 ("fAsym1", "1/TMath::Tan(TMath::Pi()*(x))+1",0,1);
//       fAsym1->SetLineColor(kGreen+2);
//       fAsym1->Draw("same");
//    canvasTestChi2->SaveAs(Form("%s/TestChi2Func.%s", outputDirectory.Data(), suffix.Data())); 
   
}

