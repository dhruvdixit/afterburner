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
#include "TBenchmark.h"
#include "TRandom.h"
#include "TLatex.h"
#include "TASImage.h"
#include "TPostScript.h"
#include "TGraphErrors.h"
#include "TArrow.h"
#include "TGraphAsymmErrors.h" 
#include "TGaxis.h"
#include "TMarker.h"
#include "CommonHeaders/PlottingGammaConversionHistos.h"
#include "CommonHeaders/PlottingGammaConversionAdditional.h"
#include "CommonHeaders/FittingGammaConversion.h"
#include "CommonHeaders/ConversionFunctionsBasicsAndLabeling.h"
#include "CommonHeaders/ConversionFunctions.h"

void FinalyseSystematicErrorsGammaPbPb_LHC11h(const char* nameDataFileErrors ="", 
											  TString energy="", 
											  TString meson = "", 
											  Int_t numberOfPtBins =1 ,
											  Int_t numberCutStudies=1, 
											  Int_t offSetBeginning = 0, 
											  TString additionalName = "0-5%",
											  TString additionalNameOutput = "0005",
											  TString suffix = "pdf", 
											  Bool_t smooth = kTRUE, 
											  Int_t mode = 0){
	
	StyleSettingsThesis();	
	SetPlotStyle();
	
	TString date = ReturnDateString();
	TString dateForOutput = ReturnDateStringForOutput();
	TString collisionSystem= ReturnFullCollisionsSystem(energy);
	TString centralityRead = additionalNameOutput;
	
	Color_t color[20] = {860,894,807,880,418,403,802,923,634,432,404,435,420,407,416,830,404,608,kCyan-2,1};
	
	Int_t 	numberOfEntriesPos = 0;
	Int_t 	numberOfEntriesNeg = 0;
	
	TFile* fileErrorInput= new TFile(nameDataFileErrors);
	const Int_t nPtBins = numberOfPtBins;
	const Int_t nCuts = numberCutStudies;
	Double_t* ptBins;
	Double_t* ptBinsErr;
	Double_t* newPoint = NULL;
	
	TString nameCutVariation[9] = {"Yield extraction",
									"dE/dx e-line", 
									"dE/dx #pi-line", 
									"TPC cluster", 
									"Single e^{#pm} #it{p}_{T}", 
									"2D #chi^{2} #gamma, #psi_{pair} #gamma",
									"2D q_{T}",
									"#alpha meson", 
									"#varphi_{conv}", 
// 									"#eta",
// 									"Max #pi momentum", 
// 									"TOF",
// 									"cosine point. angle"
		
	};  
											
	TString nameCutVariationSC[9] = {"YieldExtraction", 
										"dEdxE", 
										"dEdxPi", 
										"TPCCluster", 
										"SinglePt", 
										"Chi2", 
										"Qt", 
										"Alpha", 
										"ConvPhi", 
// 										"Eta",
// 										"pdEdxPi", 
// 										"TOF",
// 										"CosPoint"
		
	};

		

	TString outputdir = Form("SystematicErrorsCalculatedGammaPbPb_LHC11h_%s/%s",dateForOutput.Data(),meson.Data());
	gSystem->Exec("mkdir -p "+outputdir);
	
	Double_t* errorsNeg[nCuts];
	Double_t errorsNegCorr[nCuts][nPtBins];
	Double_t errorsNegSummed[nPtBins];
	Double_t errorsNegCorrSummed[nPtBins];
	Double_t errorsNegCorrMatSummed[nPtBins];
	
	Double_t* errorsNegErr[nCuts];
	Double_t errorsNegErrCorr[nCuts][nPtBins];
	Double_t errorsNegErrSummed[nPtBins];
	Double_t errorsNegErrCorrSummed[nPtBins];
	
	Double_t* errorsPos[nCuts];
	Double_t errorsPosCorr[nCuts][nPtBins];
	Double_t errorsPosSummed[nPtBins];
	Double_t errorsPosCorrSummed[nPtBins];
	Double_t errorsPosCorrMatSummed[nPtBins];
	
	Double_t* errorsPosErr[nCuts];
	Double_t errorsPosErrSummed[nPtBins];
	Double_t errorsPosErrCorr[nCuts][nPtBins];
	Double_t errorsPosErrCorrSummed[nPtBins];
	
	Double_t errorsMean[nCuts][nPtBins];
	Double_t errorsMeanCorr[nCuts][nPtBins];
	Double_t errorsMeanSummed[nPtBins];
	Double_t errorsMeanCorrSummed[nPtBins];
	Double_t errorsMeanCorrMatSummed[nPtBins];

	Double_t* errorsMeanCorrSmoothed[nCuts];
	Double_t errorsMeanCorrSummedSmoothed[nPtBins];
	Double_t errorsMeanCorrMatSummedSmoothed[nPtBins];
	Double_t errorsMeanErrCorrSummedSmoothed[nPtBins];
	Double_t errorsMeanErrCorrMatSummedSmoothed[nPtBins];
	
	Double_t errorsMeanErr[nCuts][nPtBins];
	Double_t errorsMeanErrCorr[nCuts][nPtBins];
	Double_t errorsMeanErrSummed[nPtBins];
	Double_t errorsMeanErrCorrSummed[nPtBins];
	Double_t errorsMeanErrCorrMatSummed[nPtBins];
	
	TGraphErrors* negativeErrors[nCuts];
	TGraphErrors* negativeErrorsSummed;
	TGraphErrors* positiveErrors[nCuts];
	TGraphErrors* positiveErrorsSummed;
	TGraphErrors* negativeErrorsCorr[nCuts];
	TGraphErrors* negativeErrorsCorrSummed;
	TGraphErrors* positiveErrorsCorr[nCuts];
	TGraphErrors* positiveErrorsCorrSummed;
	TGraphErrors* meanErrors[nCuts];
	TGraphErrors* meanErrorsSummed;
	TGraphErrors* meanErrorsCorr[nCuts];
	TGraphErrors* meanErrorsCorrSummed;
	TGraphErrors* meanErrorsCorrSummedIncMat;
	TGraphErrors* meanErrorsCorrSummedSmoothed;
	TGraphErrors* meanErrorsCorrSummedIncMatSmoothed;

	TGraphErrors* meanErrorsCorrInterpol[nCuts];
	TGraphErrors* meanErrorsCorrSmoothed[nCuts];
	
	for (Int_t l = 0; l < nPtBins; l++){
			errorsPosSummed[l] = 0.;
			errorsNegSummed[l] = 0.;
			errorsMeanSummed[l] = 0.;
			errorsPosCorrSummed[l] = 0.;
			errorsNegCorrSummed[l] = 0.;
			errorsMeanCorrSummed[l] = 0.;
			errorsMeanCorrSummedSmoothed[l] = 0.;
		} 
	
	for (Int_t i = 0; i < nCuts; i++){
		TGraphAsymmErrors* graphPosErrors;
		TGraphAsymmErrors* graphNegErrors;
		if (i == 0){
			TString nameGraphPos = Form("%s_SystErrorRelPos_%s_%s",meson.Data(),nameCutVariationSC[i].Data(),additionalName.Data()	);
			TString nameGraphNeg = Form("%s_SystErrorRelNeg_%s_%s",meson.Data(),nameCutVariationSC[i].Data(),additionalName.Data()	);
			cout << "Cutstudies " << i<< "\t" <<nameGraphPos.Data() << "\t" << nameGraphNeg.Data()<<  endl;
			graphPosErrors = (TGraphAsymmErrors*)fileErrorInput->Get(nameGraphPos.Data());
			graphNegErrors = (TGraphAsymmErrors*)fileErrorInput->Get(nameGraphNeg.Data());
		} else {
			TString nameGraphPos = Form("%s_SystErrorRelPos_%s%s",meson.Data(),nameCutVariationSC[i].Data(),additionalNameOutput.Data()  );
			TString nameGraphNeg = Form("%s_SystErrorRelNeg_%s%s",meson.Data(),nameCutVariationSC[i].Data(),additionalNameOutput.Data()  );
			cout << "Cutstudies " << i<< "\t" <<nameGraphPos.Data() << "\t" << nameGraphNeg.Data()<<  endl;
			graphPosErrors = (TGraphAsymmErrors*)fileErrorInput->Get(nameGraphPos.Data());
			graphNegErrors = (TGraphAsymmErrors*)fileErrorInput->Get(nameGraphNeg.Data());
		}
		
		for (Int_t j = 0; j < offSetBeginning; j++){
			graphPosErrors->RemovePoint(0);
			graphNegErrors->RemovePoint(0);
		}
		if (i == 0) {
			ptBins = graphNegErrors->GetX();
			ptBinsErr = graphNegErrors->GetEXhigh();
		}
		errorsNeg[i] = graphNegErrors->GetY();
		errorsNegErr[i] = graphNegErrors->GetEYhigh();
		errorsPos[i] = graphPosErrors->GetY();
		errorsPosErr[i] = graphPosErrors->GetEYhigh();
			
		cout << nameCutVariationSC[i].Data() << endl;
		CalculateMeanSysErr(errorsMean[i], errorsMeanErr[i], errorsPos[i], errorsNeg[i], nPtBins);	
		CorrectSystematicErrorsWithMean(errorsPos[i],errorsPosErr[i], errorsPosCorr[i], errorsPosErrCorr[i], nPtBins);
		CorrectSystematicErrorsWithMean(errorsNeg[i],errorsNegErr[i], errorsNegCorr[i], errorsNegErrCorr[i], nPtBins);
		CorrectSystematicErrorsWithMean(errorsMean[i], errorsMeanErr[i], errorsMeanCorr[i], errorsMeanErrCorr[i], nPtBins);

		//for a good fitting:
		for (Int_t k = 0; k < nPtBins; k++){
			errorsMeanErr[i][k] = 0.03;
			errorsMeanErrCorr[i][k] = 0.03;
		}	

		
		cout << "errors added quadratically" << endl;
		for (Int_t l = 0; l < nPtBins; l++){
			errorsPosSummed[l] = errorsPosSummed[l]+pow(errorsPos[i][l],2);
			errorsNegSummed[l] = errorsNegSummed[l]+ pow(errorsNeg[i][l],2);
			errorsMeanSummed[l] = errorsMeanSummed[l]+ pow(errorsMean[i][l],2);
			errorsPosCorrSummed[l] = errorsPosCorrSummed[l]+pow(errorsPosCorr[i][l],2);
			errorsNegCorrSummed[l] = errorsNegCorrSummed[l] +pow(errorsNegCorr[i][l],2);
			errorsMeanCorrSummed[l] =errorsMeanCorrSummed[l]+ pow(errorsMeanCorr[i][l],2);
			
		}

		negativeErrors[i] = new TGraphErrors(nPtBins,ptBins ,errorsNeg[i] ,ptBinsErr ,errorsNegErr[i] );
		meanErrors[i] = new TGraphErrors(nPtBins,ptBins ,errorsMean[i] ,ptBinsErr ,errorsMeanErr[i] );
		positiveErrors[i] = new TGraphErrors(nPtBins,ptBins ,errorsPos[i] ,ptBinsErr ,errorsPosErr[i] );
		negativeErrorsCorr[i] = new TGraphErrors(nPtBins,ptBins ,errorsNegCorr[i] ,ptBinsErr ,errorsNegErrCorr[i] );
		meanErrorsCorr[i] = new TGraphErrors(nPtBins,ptBins ,errorsMeanCorr[i] ,ptBinsErr ,errorsMeanErrCorr[i] );
		positiveErrorsCorr[i] = new TGraphErrors(nPtBins,ptBins ,errorsPosCorr[i] ,ptBinsErr ,errorsPosErrCorr[i] );
		 
	}
	
		//smoothing with the fit function:
	if(smooth){
		for(Int_t cut = 0; cut< numberCutStudies; cut++){
		
			Double_t minPt;
			Double_t maxPt;
			if(meson.Contains("Pi0")){
				if(nameCutVariationSC[cut].Contains("dEdxPi")) minPt = 1.;
				else if(nameCutVariationSC[cut].Contains("Qt")) minPt = 0.51;
				else if(nameCutVariationSC[cut].Contains("TPCCluster")) minPt = 0.4;
				else minPt = 0.8;
			} else if(meson.Contains("Eta")){
				if(nameCutVariationSC[cut].Contains("dEdxPi")) minPt = 1.5;
				else minPt = 1.;
			}
			if(meson.Contains("Pi0")){	
				if(nameCutVariationSC[cut].Contains("dEdxPi") || nameCutVariationSC[cut].Contains("Qt")) maxPt = 12.9;
				else if(nameCutVariationSC[cut].Contains("ConvPhi") && (additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")) ) maxPt = 12.9;
				else maxPt = ptBins[nPtBins-2]+1;
			} else if(meson.Contains("Eta")){
				maxPt = ptBins[nPtBins-2]+1;
			}

			TF1* pol4 = new TF1("pol4","[0]+[1]*x+[2]*x*x+[3]*x*x*x*x",minPt,maxPt); 
			TF1* pol3 = new TF1("pol3","[0]+[1]*x*x+[2]*x*x*x",minPt,maxPt); 

			pol4->SetParLimits(3,0,10);
			meanErrorsCorr[cut]->Fit(pol4,"NRMEX0+","",minPt,maxPt);
			meanErrorsCorr[cut]->Fit(pol3,"NRMEX0+","",minPt,maxPt);

	

			Double_t newPoint;
			meanErrorsCorrSmoothed[cut] = (TGraphErrors*)meanErrorsCorr[cut]->Clone();
			if(nameCutVariationSC[cut].Contains("Alpha")){
				for (Int_t l=0; l< nPtBins; l++){
					if(meson.Contains("Pi0")){
						if(ptBins[l] >= 0.8 && ptBins[l] < 12. ){
							newPoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
						} else {
							cout << "taking graph point" << endl;					
						}
					} else if(meson.Contains("Eta")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] >= 0.8 && ptBins[l] < 8. ){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] >= 8.){
								newPoint = pol4->Eval(8.);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);							
							} else {
								cout << "taking graph point" << endl;					
							}
						} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] == 1.75){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] == 5. || ptBins[l] == 9.){
								newPoint = pol4->Eval(8.);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);							
							} else {
								cout << "taking graph point" << endl;					
							}						
						}
					}
				}					
			} else if(nameCutVariationSC[cut].Contains("Chi2")){
				for (Int_t l=0; l< nPtBins; l++){
					if(meson.Contains("Pi0")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] >= 1.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}
						} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] == 0.7){
								newPoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] >= 0.8){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}
						}
					} else if(meson.Contains("Eta")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] <= 2.){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);													
							} else if(ptBins[l] == 2.5){
								newPoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] > 2.5 && ptBins[l] < 6.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}	
						} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] > 3. && ptBins[l] < 6.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] < 2.){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);							
							} else {
								cout << "taking graph point" << endl;					
							}	
						}
					}
				}
			} else if( nameCutVariationSC[cut].Contains("ConvPhi")){
					for (Int_t l=0; l< nPtBins; l++){
						if(meson.Contains("Pi0")){
							if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
								if(ptBins[l] >= 0.8 && ptBins[l] < 8. ){
									newPoint = pol4->Eval(ptBins[l]);
									meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
								} else if(ptBins[l] >= 8.){
									newPoint = pol3->Eval(ptBins[l]);
									meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
								} else {
									cout << "taking graph point" << endl;					
								}
							} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
								if(ptBins[l] >= 0.8 && ptBins[l] < 12. ){
									newPoint = pol4->Eval(ptBins[l]);
									meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
								} else if(ptBins[l] >= 12.){
									newPoint = pol4->Eval(12.9);
									meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);	
								} else {
									cout << "taking graph point" << endl;					
								}
							}
						} else if(meson.Contains("Eta")){
							if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
								if(ptBins[l] < 2. || ptBins[l] == 5.){
									newPoint = pol3->Eval(ptBins[l]);
									meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
								} else {
									cout << "taking graph point" << endl;					
								}		
							} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
								if(ptBins[l] <= 5){
									newPoint = pol4->Eval(ptBins[l]);
									meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
								} else if(ptBins[l] >=8){
									newPoint = pol4->Eval(8.5);
									meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);	
								} else {
									cout << "taking graph point" << endl;					
								}						
							}
						}
					}
			} else if(nameCutVariationSC[cut].Contains("dEdxE")){
				for (Int_t l=0; l< nPtBins; l++){
					if(meson.Contains("Pi0")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] > 0.5 && ptBins[l] < 0.8){
								newPoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] >= 0.8 && ptBins[l] < 12. ){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}
						}  else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
	/*						if(ptBins[l] > 0.5 && ptBins[l] < 0.8){
								newPoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else*/ if(ptBins[l] >= 0.8 && ptBins[l] < 12. ){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}
						}	
					} else if(meson.Contains("Eta")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] <= 1.5){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] > 6.){
								newPoint = pol4->Eval(6.);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}					
						}  else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] == 1.75 || ptBins[l] == 2.5 || ptBins[l] == 5.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] > 6.){
								newPoint = pol4->Eval(6.);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}					
						}		
					}
				}	
			} else if(nameCutVariationSC[cut].Contains("dEdxPi")){
				for (Int_t l=0; l< nPtBins; l++){
					if(meson.Contains("Pi0")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] > 2.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] > 12.){
								newPoint = pol4->Eval(12.9);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);					
							} else {
								cout << "taking graph point" << endl;					
							}
						}  else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] > 1. && ptBins[l] <= 8.){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] == 11.){
								newPoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}
						}
					} else if(meson.Contains("Eta")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] <= 3.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] > 8.){
								newPoint = pol4->Eval(8.5);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);					
							} else {
								cout << "taking graph point" << endl;					
							}						
						}  else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] <= 3.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] == 7.){
								newPoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}
						}
					}
				}
			} else if(nameCutVariationSC[cut].Contains("Qt")){
				for (Int_t l=0; l< nPtBins; l++){
					if(meson.Contains("Pi0")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] < 0.8){
								newPoint = pol4->Eval(0.51);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] == 0.9){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);					
							} else if(ptBins[l] > 2.2 && ptBins[l] < 10.){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);					
							} else if(ptBins[l] >= 10. && ptBins[l] < 12.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);					
							} else if(ptBins[l] >= 12.){
								newPoint = pol4->Eval(11.);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);					
							} else {
								cout << "taking graph point" << endl;					
							}
						} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							newPoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);											
						}
					} else if(meson.Contains("Eta")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l]<= 1.5){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);					
							} else if(ptBins[l] == 7.){
								newPoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2; //newPoint = pol3->Eval(9.);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}					
						} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] == 7.){
								newPoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2; //newPoint = pol3->Eval(9.);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}					
						}
					}
				}
			} else if(nameCutVariationSC[cut].Contains("SinglePt")){
				for (Int_t l=0; l< nPtBins; l++){
					if(meson.Contains("Pi0")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] > 0.5 && ptBins[l] < 0.8){
								newPoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] >= 5.){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}
						} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] > 0.5 && ptBins[l] < 0.8){
								newPoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] >= 10.){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}						
						}
					} else if(meson.Contains("Eta")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] <= 3.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] == 7.){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}					
						} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] <= 3.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else {
								cout << "taking graph point" << endl;					
							}											
						}
					}
				}
			} else if(nameCutVariationSC[cut].Contains("TPCCluster")){
				for (Int_t l=0; l< nPtBins; l++){
					if(meson.Contains("Pi0")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
	// 						if(ptBins[l] < 0.8){
	// 							newPoint = pol4->Eval(ptBins[l]);
	// 							meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
	// 						} else if(ptBins[l] >= 4.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
	// 						} else if(ptBins[l] >= 4.){
	// 							newPoint = pol3->Eval(ptBins[l]);
	// 							meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);					
	// 						} else {
	// 							cout << "taking graph point" << endl;					
	// 						}
						} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] < 0.8){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] == 11.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
		// 					} else if(ptBins[l] >= 4.){
		// 						newPoint = pol3->Eval(ptBins[l]);
		// 						meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);					
							} else {
								cout << "taking graph point" << endl;					
							}
						}
					} else if(meson.Contains("Eta")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] < 2.){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] == 5.){
								newPoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] > 6.){
								newPoint = pol4->Eval(6.);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);								
							} else {
								cout << "taking graph point" << endl;					
							}					
						} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] < 2.){
								newPoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);
							} else if(ptBins[l] > 6.){
								newPoint = pol4->Eval(6.);
								meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);	
	// 						} else if(ptBins[l] == 1.75){
	// 							newPoint = pol3->Eval(ptBins[l]);
	// 							meanErrorsCorrSmoothed[cut]->SetPoint(l,ptBins[l],newPoint);							
							} else {
								cout << "taking graph point" << endl;					
							}					
						}
					}
				}
			} else cout <<"bla"<<endl;			
		} //cuts loop
	}//end smoothing if

	
	Double_t errorMaterial = 4.50;

	if(smooth){	
		for(Int_t cut = 0; cut< numberCutStudies; cut++){
			errorsMeanCorrSmoothed[cut] = meanErrorsCorrSmoothed[cut]->GetY();
			for (Int_t l = 0; l < nPtBins; l++){
				errorsMeanCorrSummedSmoothed[l] = errorsMeanCorrSummedSmoothed[l]+ pow(errorsMeanCorrSmoothed[cut][l],2);
	// 			cout << l << " errorsMeanCorrSummedSmoothed[l] " << errorsMeanCorrSummedSmoothed[l] << endl;
			}
		}
	}
	
	for (Int_t l = 0; l < nPtBins; l++){
		errorsPosSummed[l] = pow(errorsPosSummed[l],0.5);
		errorsMeanSummed[l] = pow(errorsMeanSummed[l],0.5);
		errorsPosErrSummed[l] = errorsPosSummed[l]*0.001;
		errorsMeanErrSummed[l] = errorsMeanSummed[l]*0.001;
		errorsNegSummed[l] = -pow(errorsNegSummed[l],0.5);
		errorsNegErrSummed[l] = errorsNegSummed[l]*0.001;

		errorsPosCorrMatSummed[l] = pow(errorsPosCorrSummed[l]+ pow(2*errorMaterial ,2.),0.5);
		errorsMeanCorrMatSummed[l] = pow(errorsMeanCorrSummed[l]+ pow(2*errorMaterial ,2.),0.5);
		errorsNegCorrMatSummed[l] = -pow(errorsNegCorrSummed[l]+ pow(2*errorMaterial ,2.),0.5);

		if(smooth){
			errorsMeanCorrMatSummedSmoothed[l] = pow(errorsMeanCorrSummedSmoothed[l]+ pow(2*errorMaterial ,2.),0.5);
// 			cout << " errorsMeanCorrMatSummedSmoothed: " << errorsMeanCorrMatSummedSmoothed[l] << endl;
			errorsMeanCorrSummedSmoothed[l] = pow(errorsMeanCorrSummedSmoothed[l],0.5);
			errorsMeanErrCorrSummedSmoothed[l] = errorsMeanCorrSummedSmoothed[l]*0.001;
		}
		
// 		cout << " errorsMeanCorrSummed: " << errorsMeanCorrSummed[l] << endl;
		errorsPosCorrSummed[l] = pow(errorsPosCorrSummed[l],0.5);
		errorsMeanCorrSummed[l] = pow(errorsMeanCorrSummed[l],0.5);
		errorsPosErrCorrSummed[l] = errorsPosCorrSummed[l]*0.001;
		errorsMeanErrCorrSummed[l] = errorsMeanCorrSummed[l]*0.001;
		errorsMeanErrCorrMatSummed[l] = errorsMeanCorrMatSummed[l]*0.001;
		errorsMeanErrCorrMatSummedSmoothed[l] = errorsMeanCorrMatSummedSmoothed[l]*0.001;
		errorsNegCorrSummed[l] = -pow(errorsNegCorrSummed[l],0.5);
		errorsNegErrCorrSummed[l] = errorsNegCorrSummed[l]*0.001;

// 		cout << errorsMeanSummed[l] << "\t" << errorsMeanCorrMatSummed[l]<< endl;
	}
	
	Double_t errorsMat[nPtBins];
	for (Int_t l = 0; l < nPtBins; l++){
		errorsMat[l] = 2*errorMaterial;
		
	}
	TGraphErrors* graphMaterialError = new TGraphErrors(nPtBins,ptBins ,errorsMat ,ptBinsErr ,errorsMeanErrSummed );

	cout << "here" << endl;
	negativeErrorsSummed 		= new TGraphErrors(nPtBins,ptBins ,errorsNegSummed ,ptBinsErr ,errorsNegErrSummed );
	negativeErrorsCorrSummed 	= new TGraphErrors(nPtBins,ptBins ,errorsNegCorrSummed ,ptBinsErr ,errorsNegErrCorrSummed );
	positiveErrorsSummed 		= new TGraphErrors(nPtBins,ptBins ,errorsPosSummed ,ptBinsErr ,errorsPosErrSummed );
	positiveErrorsCorrSummed 	= new TGraphErrors(nPtBins,ptBins ,errorsPosCorrSummed ,ptBinsErr ,errorsPosErrCorrSummed );
	meanErrorsSummed 			= new TGraphErrors(nPtBins,ptBins ,errorsMeanSummed ,ptBinsErr ,errorsMeanErrSummed );
	meanErrorsCorrSummed		= new TGraphErrors(nPtBins,ptBins ,errorsMeanCorrSummed ,ptBinsErr ,errorsMeanErrCorrSummed );
	meanErrorsCorrSummedIncMat 	= new TGraphErrors(nPtBins,ptBins ,errorsMeanCorrMatSummed ,ptBinsErr ,errorsMeanErrCorrMatSummed );
	if(smooth){
		meanErrorsCorrSummedSmoothed 		= new TGraphErrors(nPtBins,ptBins ,errorsMeanCorrSummedSmoothed ,ptBinsErr ,errorsMeanErrCorrSummed );
		meanErrorsCorrSummedIncMatSmoothed 	= new TGraphErrors(nPtBins,ptBins ,errorsMeanCorrMatSummedSmoothed,ptBinsErr ,errorsMeanErrCorrMatSummed );
	}
	
	cout << "Plotting the systematic: " << endl;
	
	TCanvas* canvasSysErrMean = new TCanvas("canvasSysErrMean","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasSysErrMean, 0.08, 0.01, 0.015, 0.09);
	TH2D *histo2DSysErrMean ;
	if (meson.Contains("Pi0") ){
		histo2DSysErrMean = new TH2D("histo2DSysErrMean", "histo2DSysErrMean", 20,0.,ptBins[nPtBins-1]+1,1000.,0.,30.);
	} else {
		histo2DSysErrMean = new TH2D("histo2DSysErrMean", "histo2DSysErrMean", 20,0.,ptBins[nPtBins-1]+1,1000.,0.,65.);
	}	
	histo2DSysErrMean->SetYTitle("mean systematic Err %");
	histo2DSysErrMean->SetXTitle("#it{p}_{T} (GeV/#it{c})");
	histo2DSysErrMean->GetYaxis()->SetNdivisions(510,kTRUE);
	histo2DSysErrMean->GetYaxis()->SetLabelSize(0.03);
	histo2DSysErrMean->GetYaxis()->SetTitleSize(0.04);
	histo2DSysErrMean->GetYaxis()->SetDecimals();
	histo2DSysErrMean->GetYaxis()->SetTitleOffset(0.9);
	histo2DSysErrMean->GetXaxis()->SetTitleOffset(1.);
	histo2DSysErrMean->GetXaxis()->SetLabelSize(0.03);
	histo2DSysErrMean->GetXaxis()->SetTitleSize(0.04);
	histo2DSysErrMean->SetTitle("");
	histo2DSysErrMean->Draw();
	
	TLegend* legendMean; 
	if (meson.Contains("Pi0")){
		legendMean= new TLegend(0.15,0.6,0.57,0.95);
	} else {
		legendMean= new TLegend(0.20,0.6,0.62,0.95);
	}
	legendMean->SetTextSize(0.035);
	legendMean->SetFillColor(0);
	legendMean->SetBorderSize(0);
	if (numberCutStudies> 9) legendMean->SetNColumns(2);
	for(Int_t i = 0; i< numberCutStudies ; i++){
		DrawGammaSetMarkerTGraphErr(meanErrors[i], 20+i, 1.,color[i],color[i]);
		meanErrors[i]->Draw("pE0,csame");
		legendMean->AddEntry(meanErrors[i],nameCutVariation[i].Data(),"p");
	}
	DrawGammaSetMarkerTGraphErr(graphMaterialError, 24, 1.,color[10],color[10]);
	graphMaterialError->Draw("pX0,csame");
	legendMean->AddEntry(graphMaterialError,"Material","p");

	
// 	DrawGammaSetMarkerTGraphErr(meanErrorsSummed, 20, 1.,1,1);
// 	meanErrorsSummed->Draw("pE0,csame");
// 	legendMean->AddEntry(meanErrorsSummed,"quad. sum.","p");
	legendMean->Draw();
	canvasSysErrMean->Update();
	canvasSysErrMean->SaveAs(Form("%s/SysMean_%s_%s%s_%s.%s",outputdir.Data(),meson.Data(), energy.Data(),additionalNameOutput.Data(),dateForOutput.Data(),suffix.Data()));
	
	delete canvasSysErrMean;
	
	TCanvas* canvasNewSysErrMean = new TCanvas("canvasNewSysErrMean","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasNewSysErrMean, 0.08, 0.01, 0.015, 0.09);
	
	TH2D *histo2DNewSysErrMean ;
	if (meson.Contains("Pi0")){
		histo2DNewSysErrMean = new TH2D("histo2DNewSysErrMean", "histo2DNewSysErrMean", 20,0.,ptBins[nPtBins-1]+1,1000.,-0.5,30.);
	} else { 
		histo2DNewSysErrMean = new TH2D("histo2DNewSysErrMean", "histo2DNewSysErrMean", 20,0.,ptBins[nPtBins-1]+1,1000.,-0.5,65.);
	}
	histo2DNewSysErrMean->SetYTitle("mean smoothed systematic Err %");
	histo2DNewSysErrMean->SetXTitle("#it{p}_{T} (GeV/#it{c})");
	histo2DNewSysErrMean->GetYaxis()->SetNdivisions(510,kTRUE);
	histo2DNewSysErrMean->GetYaxis()->SetLabelSize(0.03);
	histo2DNewSysErrMean->GetYaxis()->SetTitleSize(0.04);
	histo2DNewSysErrMean->GetYaxis()->SetDecimals();
	histo2DNewSysErrMean->GetYaxis()->SetTitleOffset(0.9);
	histo2DNewSysErrMean->GetXaxis()->SetTitleOffset(1.);
	histo2DNewSysErrMean->GetXaxis()->SetLabelSize(0.03);
	histo2DNewSysErrMean->GetXaxis()->SetTitleSize(0.04);
	histo2DNewSysErrMean->SetTitle("");
	histo2DNewSysErrMean->Draw();
	
	TLegend* legendMeanNew;
	if (meson.Contains("Pi0")){
		legendMeanNew= new TLegend(0.12,0.6,0.67,0.95);
	} else {
		legendMeanNew= new TLegend(0.23,0.65,0.72,0.95);
	}	
	legendMeanNew->SetTextSize(0.035);
	legendMeanNew->SetMargin(0.1);
	legendMeanNew->SetFillColor(0);
	legendMeanNew->SetFillStyle(0);
	legendMeanNew->SetBorderSize(0);
	if (numberCutStudies> 9) legendMeanNew->SetNColumns(2);
	for(Int_t i = 0; i< numberCutStudies ; i++){
		DrawGammaSetMarkerTGraphErr(meanErrorsCorr[i], 20+i, 1.,color[i],color[i]);
		meanErrorsCorr[i]->Draw("pX0,csame");
		legendMeanNew->AddEntry(meanErrorsCorr[i],nameCutVariation[i].Data(),"p");	
	}

	DrawGammaSetMarkerTGraphErr(graphMaterialError, 24, 1.,color[10],color[10]);
	graphMaterialError->Draw("pX0,csame");
	legendMeanNew->AddEntry(graphMaterialError,"Material","p");
	
	DrawGammaSetMarkerTGraphErr(meanErrorsCorrSummedIncMat, 20, 1.,kBlack,kBlack);
	meanErrorsCorrSummedIncMat->Draw("p,csame");
	legendMeanNew->AddEntry(meanErrorsCorrSummedIncMat,"quad. sum.","p");
	legendMeanNew->Draw();
	
	TLatex *labelMeson;
	if (meson.Contains("Pi0")){
		labelMeson= new TLatex(0.75,0.89,Form("#pi^{0} #rightarrow #gamma_{conv}#gamma_{conv}"));
	} else {
		labelMeson= new TLatex(0.75,0.89,Form("#eta #rightarrow #gamma_{conv}#gamma_{conv}"));
	}
	SetStyleTLatex( labelMeson, 0.038,4);
	labelMeson->Draw();

	TLatex *labelCentrality = new TLatex(0.75,0.93,Form("%s",collisionSystem.Data()	));
	SetStyleTLatex( labelCentrality, 0.038,4);
	labelCentrality->Draw();

	canvasNewSysErrMean->Update();
	canvasNewSysErrMean->SaveAs(Form("%s/SysMeanNewWithMean_%s_%s%s_%s.%s",outputdir.Data(),meson.Data(), energy.Data(),additionalNameOutput.Data(),dateForOutput.Data(),suffix.Data()));
	
	
	if(smooth){
		canvasNewSysErrMean->cd();
		histo2DNewSysErrMean->Draw();
			
		for(Int_t i = 0; i< numberCutStudies ; i++){
			DrawGammaSetMarkerTGraphErr(meanErrorsCorrSmoothed[i], 20+i, 1.,color[i],color[i]);
			meanErrorsCorrSmoothed[i]->Draw("pX0,csame");
	// 		legendMeanNew->AddEntry(meanErrorsCorr[i],nameCutVariation[i].Data(),"p");	
		}

		DrawGammaSetMarkerTGraphErr(graphMaterialError, 24, 1.,color[10],color[10]);
		graphMaterialError->Draw("pX0,csame");
		meanErrorsCorrSummedIncMat->Print();
		cout << " \n " << endl;
		meanErrorsCorrSummedIncMatSmoothed->Print();
		DrawGammaSetMarkerTGraphErr(meanErrorsCorrSummedIncMatSmoothed, 20, 1.,kBlack,kBlack);
		meanErrorsCorrSummedIncMatSmoothed->Draw("p,csame");

		labelMeson->Draw();
		labelCentrality->Draw();
		legendMeanNew->Draw();

		canvasNewSysErrMean->Update();
		canvasNewSysErrMean->SaveAs(Form("%s/SysMeanNewWithMeanSmoothed_%s_%s%s_%s.%s",outputdir.Data(),meson.Data(), energy.Data(),additionalNameOutput.Data(),dateForOutput.Data(),suffix.Data()));
	}
	

	
	for(Int_t cut = 0; cut< numberCutStudies ; cut++){
		canvasNewSysErrMean->cd();
		histo2DNewSysErrMean->Draw();
		
		Double_t minPt;
		Double_t maxPt;
		if(meson.Contains("Pi0")){
			if(nameCutVariationSC[cut].Contains("dEdxPi")) minPt = 1.;
			else if(nameCutVariationSC[cut].Contains("Qt")) minPt = 0.51;
			else if(nameCutVariationSC[cut].Contains("TPCCluster")) minPt = 0.4;
			else minPt = 0.8;
		} else if(meson.Contains("Eta")){
			if(nameCutVariationSC[cut].Contains("dEdxPi")) minPt = 1.5;
			else minPt = 1.;
		}
		if(meson.Contains("Pi0")){	
			if(nameCutVariationSC[cut].Contains("dEdxPi") || nameCutVariationSC[cut].Contains("Qt")) maxPt = 12.9;
			else if(nameCutVariationSC[cut].Contains("ConvPhi") && (additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")) ) maxPt = 12.9;
			else maxPt = ptBins[nPtBins-2]+1;
		} else if(meson.Contains("Eta")){
			maxPt = ptBins[nPtBins-2]+1;
		}
		
		TF1* pol2 = new TF1("pol2","[0]+[1]*x",minPt,maxPt); //+[2]*x*x
		TF1* pol3 = new TF1("pol3","[0]+[1]*x*x+[2]*x*x*x",minPt,maxPt); //
		TF1* pol4 = new TF1("pol4","[0]+[1]*x+[2]*x*x+[3]*x*x*x*x",minPt,maxPt); //
// 		pol4->SetParLimits(3,0,10);
// 		pol3->SetParLimits(3,0,10);
// 		pol4->FixParameter(2,0);
// 		pol4->SetParLimits(1,0,1);
// 		pol4->FixParameter(0,0.8);
		
		cout << "\n\n Here the fit for the cut variation: " << nameCutVariationSC[cut].Data() << endl;
		meanErrorsCorr[cut]->Fit(pol2,"NRMEX0+","",minPt,maxPt);
		meanErrorsCorr[cut]->Fit(pol3,"NRMEX0+","",minPt,maxPt);
		meanErrorsCorr[cut]->Fit(pol4,"NRMEX0+","",minPt,maxPt);
// 		pol4->SetParameter(0,0.598);
// 		pol4->SetParameter(1,0.285);
// 		pol4->SetParameter(2,0.112);
// 		pol4->SetParameter(3,-0.0004);
		pol4->SetLineColor(kRed+2);
		pol3->SetLineColor(kBlue+1);
		pol2->SetLineColor(kGreen+2);

		TLegend* legendSingleSyst;
		if (meson.Contains("Pi0")){
			legendSingleSyst= new TLegend(0.13,0.7,0.65,0.95);
		} else {
			legendSingleSyst= new TLegend(0.20,0.7,0.7,0.95);
		}
		legendSingleSyst->SetTextSize(0.035);
		legendSingleSyst->SetFillColor(0);
		legendSingleSyst->SetFillStyle(0);	
		legendSingleSyst->SetBorderSize(0);
// 		legendSingleSyst->SetNColumns(2);
		legendSingleSyst->SetMargin(0.1);
		legendSingleSyst->AddEntry(meanErrorsCorr[cut], Form("%s",nameCutVariationSC[cut].Data()),"p");
// 		legendSingleSyst->AddEntry(pol2,"pol1, [0]+[1]*x","l"); //+[2]*x^{2}
		legendSingleSyst->AddEntry(pol3,"pol3, [0]+[1]*x^{2}+[2]*x^{3}","l");
		legendSingleSyst->AddEntry(pol4,"pol4, [0]+[1]*x+[2]*x^{2}+[3]*x^{4}","l");
		
		
		DrawGammaSetMarkerTGraphErr(meanErrorsCorr[cut], 20+cut, 1.,color[cut],color[cut]);
		meanErrorsCorr[cut]->Draw("p,csame");
// 		pol2->Draw("same");
		pol3->Draw("same");
		pol4->Draw("same");

		Double_t newSinglePoint;
		meanErrorsCorrInterpol[cut] = (TGraphErrors*)meanErrorsCorr[cut]->Clone();
		if(nameCutVariationSC[cut].Contains("Alpha")){
			for (Int_t l=0; l< nPtBins; l++){
				if(meson.Contains("Pi0")){
					if(ptBins[l] >= 0.8 && ptBins[l] < 12. ){
						newSinglePoint = pol3->Eval(ptBins[l]);
						meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
					} else {
						cout << "taking graph point" << endl;					
					}
				} else if(meson.Contains("Eta")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l] >= 0.8 && ptBins[l] < 8. ){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] >= 8.){
							newSinglePoint = pol4->Eval(8.);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);							
						} else {
							cout << "taking graph point" << endl;					
						}
					} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						if(ptBins[l] == 1.75){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] == 5. || ptBins[l] == 9.){
							newSinglePoint = pol4->Eval(8.);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);							
						} else {
							cout << "taking graph point" << endl;					
						}						
					}
				}
			}					
		} else if(nameCutVariationSC[cut].Contains("Chi2")){
			for (Int_t l=0; l< nPtBins; l++){
				if(meson.Contains("Pi0")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l] >= 1.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}
					} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						if(ptBins[l] == 0.7){
							newSinglePoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] >= 0.8){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}
					}
				} else if(meson.Contains("Eta")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l] <= 2.){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);													
						} else if(ptBins[l] == 2.5){
							newSinglePoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] > 2.5 && ptBins[l] < 6.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}	
					} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						if(ptBins[l] > 3. && ptBins[l] < 6.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] < 2.){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);							
						} else {
							cout << "taking graph point" << endl;					
						}	
					}
				}
			}
		} else if( nameCutVariationSC[cut].Contains("ConvPhi")){
				for (Int_t l=0; l< nPtBins; l++){
					if(meson.Contains("Pi0")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] >= 0.8 && ptBins[l] < 8. ){
								newSinglePoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
							} else if(ptBins[l] >= 8.){
								newSinglePoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
							} else {
								cout << "taking graph point" << endl;					
							}
						} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] >= 0.8 && ptBins[l] < 12. ){
								newSinglePoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
							} else if(ptBins[l] >= 12.){
								newSinglePoint = pol4->Eval(12.9);
								meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);	
							} else {
								cout << "taking graph point" << endl;					
							}
						}
					} else if(meson.Contains("Eta")){
						if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
							if(ptBins[l] < 2. || ptBins[l] == 5.){
								newSinglePoint = pol3->Eval(ptBins[l]);
								meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
							} else {
								cout << "taking graph point" << endl;					
							}		
						} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
							if(ptBins[l] <= 5){
								newSinglePoint = pol4->Eval(ptBins[l]);
								meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
							} else if(ptBins[l] >=8){
								newSinglePoint = pol4->Eval(8.5);
								meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);	
							} else {
								cout << "taking graph point" << endl;					
							}						
						}
					}
				}
		} else if(nameCutVariationSC[cut].Contains("dEdxE")){
			for (Int_t l=0; l< nPtBins; l++){
				if(meson.Contains("Pi0")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l] > 0.5 && ptBins[l] < 0.8){
							newSinglePoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] >= 0.8 && ptBins[l] < 12. ){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}
					}  else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
/*						if(ptBins[l] > 0.5 && ptBins[l] < 0.8){
							newSinglePoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else*/ if(ptBins[l] >= 0.8 && ptBins[l] < 12. ){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}
					}	
				} else if(meson.Contains("Eta")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l] <= 1.5){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] > 6.){
							newSinglePoint = pol4->Eval(6.);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}					
					}  else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						if(ptBins[l] == 1.75 || ptBins[l] == 2.5 || ptBins[l] == 5.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] > 6.){
							newSinglePoint = pol4->Eval(6.);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}					
					}		
				}
			}	
		} else if(nameCutVariationSC[cut].Contains("dEdxPi")){
			for (Int_t l=0; l< nPtBins; l++){
				if(meson.Contains("Pi0")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l] > 2.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] > 12.){
							newSinglePoint = pol4->Eval(12.9);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);					
						} else {
							cout << "taking graph point" << endl;					
						}
					}  else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						if(ptBins[l] > 1. && ptBins[l] <= 8.){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] == 11.){
							newSinglePoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}
					}
				} else if(meson.Contains("Eta")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l] <= 3.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] > 8.){
							newSinglePoint = pol4->Eval(8.5);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);					
						} else {
							cout << "taking graph point" << endl;					
						}						
					}  else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						if(ptBins[l] <= 3.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] == 7.){
							newSinglePoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}
					}
				}
			}
		} else if(nameCutVariationSC[cut].Contains("Qt")){
			for (Int_t l=0; l< nPtBins; l++){
				if(meson.Contains("Pi0")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l] < 0.8){
							newSinglePoint = pol4->Eval(0.51);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] == 0.9){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);					
						} else if(ptBins[l] > 2.2 && ptBins[l] < 10.){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);					
						} else if(ptBins[l] >= 10. && ptBins[l] < 12.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);					
						} else if(ptBins[l] >= 12.){
							newSinglePoint = pol4->Eval(11.);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);					
						} else {
							cout << "taking graph point" << endl;					
						}
					} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						newSinglePoint = pol3->Eval(ptBins[l]);
						meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);											
					}
				} else if(meson.Contains("Eta")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l]<= 1.5){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);					
						} else if(ptBins[l] == 7.){
							newSinglePoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2; //newSinglePoint = pol3->Eval(9.);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}					
					} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						if(ptBins[l] == 7.){
							newSinglePoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2; //newSinglePoint = pol3->Eval(9.);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}					
					}
				}
			}
		} else if(nameCutVariationSC[cut].Contains("SinglePt")){
			for (Int_t l=0; l< nPtBins; l++){
				if(meson.Contains("Pi0")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l] > 0.5 && ptBins[l] < 0.8){
							newSinglePoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] >= 5.){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}
					} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						if(ptBins[l] > 0.5 && ptBins[l] < 0.8){
							newSinglePoint = (errorsMeanCorr[cut][l-1] + errorsMeanCorr[cut][l+1])/2;
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] >= 10.){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}						
					}
				} else if(meson.Contains("Eta")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l] <= 3.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] == 7.){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}					
					} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						if(ptBins[l] <= 3.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else {
							cout << "taking graph point" << endl;					
						}											
					}
				}
			}
		} else if(nameCutVariationSC[cut].Contains("TPCCluster")){
			for (Int_t l=0; l< nPtBins; l++){
				if(meson.Contains("Pi0")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
// 						if(ptBins[l] < 0.8){
// 							newSinglePoint = pol4->Eval(ptBins[l]);
// 							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
// 						} else if(ptBins[l] >= 4.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
// 						} else if(ptBins[l] >= 4.){
// 							newSinglePoint = pol3->Eval(ptBins[l]);
// 							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);					
// 						} else {
// 							cout << "taking graph point" << endl;					
// 						}
 					} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						if(ptBins[l] < 0.8){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] == 11.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
	// 					} else if(ptBins[l] >= 4.){
	// 						newSinglePoint = pol3->Eval(ptBins[l]);
	// 						meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);					
						} else {
							cout << "taking graph point" << endl;					
						}
					}
				} else if(meson.Contains("Eta")){
					if(additionalNameOutput.Contains("0010") || additionalNameOutput.Contains("0005") || additionalNameOutput.Contains("0510") ){
						if(ptBins[l] < 2.){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] == 5.){
							newSinglePoint = pol4->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] > 6.){
							newSinglePoint = pol4->Eval(6.);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);								
						} else {
							cout << "taking graph point" << endl;					
						}					
					} else if(additionalNameOutput.Contains("2050") || additionalNameOutput.Contains("2040")){
						if(ptBins[l] < 2.){
							newSinglePoint = pol3->Eval(ptBins[l]);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
						} else if(ptBins[l] > 6.){
							newSinglePoint = pol4->Eval(6.);
							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);	
// 						} else if(ptBins[l] == 1.75){
// 							newSinglePoint = pol3->Eval(ptBins[l]);
// 							meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);							
						} else {
							cout << "taking graph point" << endl;					
						}					
					}
				}
			}
		} else cout <<"bla"<<endl;
				  
		DrawGammaSetMarkerTGraphErr(meanErrorsCorrInterpol[cut], 20, 1.5,kGray+2,kGray+2);
		meanErrorsCorrInterpol[cut]->Draw("p,csame");
		legendSingleSyst->AddEntry(meanErrorsCorrInterpol[cut], Form("%s smoothed",nameCutVariationSC[cut].Data()),"p");
		
		
		/* else if(nameCutVariationSC[cut].Contains("Eta")){
			meanErrorsCorrInterpol[cut] = (TGraphErrors*)meanErrorsCorr[cut]->Clone();
			for (Int_t l=0; l< nPtBins; l++){
				newSinglePoint = pol4->Eval(12.);
				if(ptBins[l] == 11.){
					meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
				}
			}
			DrawGammaSetMarkerTGraphErr(meanErrorsCorrInterpol[cut], 20+cut, 1.,kPink-9,kPink-9);
			meanErrorsCorrInterpol[cut]->Draw("p,csame");			
		} else if(nameCutVariationSC[cut].Contains("dEdxPi")){
			meanErrorsCorrInterpol[cut] = (TGraphErrors*)meanErrorsCorr[cut]->Clone();
			for (Int_t l=0; l< nPtBins; l++){
				newSinglePoint = pol4->Eval(13.);
				if(ptBins[l] == 13.){
					meanErrorsCorrInterpol[cut]->SetPoint(l,ptBins[l],newSinglePoint);
				}
			}
			DrawGammaSetMarkerTGraphErr(meanErrorsCorrInterpol[cut], 20+cut, 1.,kPink-9,kPink-9);
			meanErrorsCorrInterpol[cut]->Draw("p,csame");			
		}*/
		
		legendSingleSyst->Draw("same");
		
		canvasNewSysErrMean->SaveAs(Form("%s/SysMeanNewWithMeanSingle%s_%s_%s%s_%s.%s",outputdir.Data(),nameCutVariationSC[cut].Data(),meson.Data(), energy.Data(),additionalNameOutput.Data(),dateForOutput.Data(),suffix.Data()));

	}
	
// 	delete canvasNewSysErrMean;
		
	Double_t errorsMeanCorrPID[nPtBins];	
	Double_t errorsMeanCorrSignalExtraction[nPtBins];	
	Double_t errorsMeanCorrTrackReco[nPtBins];	
	Double_t errorsMeanCorrPhotonReco[nPtBins];	
	Double_t errorsMeanCorrAcceptance[nPtBins];			
	Double_t errorsMeanCorrOther[nPtBins];	
	
	for (Int_t l=0; l< nPtBins; l++){
// 			"YieldExtraction"-0,"dEdxE"-1,"dEdxPi"-2, "TPCCluster"-3, "SinglePt"-4, "Chi2"-5, "Qt"-6, "Alpha"-7, "ConvPhi"-8, "eta"-9, "maxPiMon"-10, "TOF"-11, "cosPA" -12
		// grouping:
		if (numberCutStudies>8){
			// Signal extraction: Yield extraction 0, Alpha 7 
			errorsMeanCorrSignalExtraction[l] = TMath::Sqrt(errorsMeanCorr[0][l]*errorsMeanCorr[0][l]+errorsMeanCorr[7][l]*errorsMeanCorr[7][l]+2.5*2.5);	
		} 
// 			else {
// 				// Signal extraction: Yield extraction 0, Alpha 7 
// 				errorsMeanCorrSignalExtraction[l] = TMath::Sqrt(errorsMeanCorr[0][l]*errorsMeanCorr[0][l]+2.5*2.5);
// 			}
		// PID: dEdxE 1, dEdxPi 2, maxPiMon 10
		errorsMeanCorrPID[l] =TMath::Sqrt(errorsMeanCorr[1][l]*errorsMeanCorr[1][l]+ errorsMeanCorr[2][l]*errorsMeanCorr[2][l]+errorsMeanCorr[10][l]*errorsMeanCorr[10][l]);
		// photon reco: Chi2 5, Qt 6
		errorsMeanCorrPhotonReco[l] =TMath::Sqrt( errorsMeanCorr[5][l]* errorsMeanCorr[5][l]+errorsMeanCorr[6][l]*errorsMeanCorr[6][l]);
		// track reconstruction: TPCCluster 3, Single pt 4, ConvPhi 8
		errorsMeanCorrTrackReco[l] = TMath::Sqrt(errorsMeanCorr[3][l]*errorsMeanCorr[3][l]+errorsMeanCorr[4][l]*errorsMeanCorr[4][l]+errorsMeanCorr[8][l]*errorsMeanCorr[8][l]);			
		// eta only
		errorsMeanCorrAcceptance[l] = TMath::Sqrt(errorsMeanCorr[9][l]*errorsMeanCorr[9][l]);	
		// TOF, cosPA
		errorsMeanCorrOther[l] = TMath::Sqrt(errorsMeanCorr[11][l]*errorsMeanCorr[11][l]+errorsMeanCorr[12][l]*errorsMeanCorr[12][l]);	
	}
		
		
	TGraphErrors* meanErrorsPID = new TGraphErrors(nPtBins,ptBins ,errorsMeanCorrPID ,ptBinsErr ,errorsMeanErrCorrSummed );
	TGraphErrors* meanErrorsPhotonReco = new TGraphErrors(nPtBins,ptBins ,errorsMeanCorrPhotonReco ,ptBinsErr ,errorsMeanErrCorrSummed );
	TGraphErrors* meanErrorsSignalExtraction = new TGraphErrors(nPtBins,ptBins ,errorsMeanCorrSignalExtraction ,ptBinsErr ,errorsMeanErrCorrSummed );
	TGraphErrors* meanErrorsTrackReco = new TGraphErrors(nPtBins,ptBins ,errorsMeanCorrTrackReco ,ptBinsErr ,errorsMeanErrCorrSummed );
	TGraphErrors* meanErrorsAcceptance = new TGraphErrors(nPtBins,ptBins ,errorsMeanCorrAcceptance ,ptBinsErr ,errorsMeanErrCorrSummed );
	TGraphErrors* meanErrorsOther = new TGraphErrors(nPtBins,ptBins ,errorsMeanCorrOther ,ptBinsErr ,errorsMeanErrCorrSummed );

    cout << "here" << endl;
   
   
	TCanvas* canvasSummedErrMean = new TCanvas("canvasSummedErrMean","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasSummedErrMean, 0.08, 0.01, 0.015, 0.09);
	TH2D *histo2DSummedErrMean ;
	
	if (meson.Contains("Pi0") ){	
		histo2DSummedErrMean = new TH2D("histo2DSummedErrMean", "histo2DSummedErrMean", 20,0.,ptBins[nPtBins-1]+1,1000.,-0.5,30.);
	} else {
		histo2DSummedErrMean = new TH2D("histo2DSummedErrMean", "histo2DSummedErrMean", 20,0.,ptBins[nPtBins-1]+1,1000.,-0.5,65.);
	}
	histo2DSummedErrMean->SetYTitle("mean smoothed systematic Err %");
	histo2DSummedErrMean->SetXTitle("#it{p}_{T} (GeV/#it{c})");
	histo2DSummedErrMean->GetYaxis()->SetNdivisions(510,kTRUE);
	histo2DSummedErrMean->GetYaxis()->SetLabelSize(0.03);
	histo2DSummedErrMean->GetYaxis()->SetTitleSize(0.04);
	histo2DSummedErrMean->GetYaxis()->SetDecimals();
	histo2DSummedErrMean->GetYaxis()->SetTitleOffset(0.9);
	histo2DSummedErrMean->GetXaxis()->SetTitleOffset(1.);
	histo2DSummedErrMean->GetXaxis()->SetLabelSize(0.03);
	histo2DSummedErrMean->GetXaxis()->SetTitleSize(0.04);
	histo2DSummedErrMean->SetTitle("");
	histo2DSummedErrMean->Draw();
	
	TLegend* legendSummedMeanNew;
	if (meson.Contains("Pi0")){
		legendSummedMeanNew= new TLegend(0.13,0.7,0.65,0.95);
	} else {
		legendSummedMeanNew= new TLegend(0.20,0.7,0.7,0.95);
	}
	legendSummedMeanNew->SetTextSize(0.035);
	legendSummedMeanNew->SetFillColor(0);
	legendSummedMeanNew->SetFillStyle(0);	
	legendSummedMeanNew->SetBorderSize(0);
	legendSummedMeanNew->SetNColumns(2);
	legendSummedMeanNew->SetMargin(0.1);
	
	// Signal extraction error
	DrawGammaSetMarkerTGraphErr(meanErrorsSignalExtraction, 20, 1.,color[0],color[0]);
	meanErrorsSignalExtraction->Draw("pX0,csame");
	// electron PID error
	DrawGammaSetMarkerTGraphErr(meanErrorsPID, 21, 1.,color[1],color[1]);
	meanErrorsPID->Draw("pX0,csame");
	// track reconstruction error
	DrawGammaSetMarkerTGraphErr(meanErrorsTrackReco, 22, 1.,color[2],color[2]);
	meanErrorsTrackReco->Draw("pX0,csame");
	// Photon reco error
	DrawGammaSetMarkerTGraphErr(meanErrorsPhotonReco, 23, 1.,color[3],color[3]);
	meanErrorsPhotonReco->Draw("pX0,csame");
	// Eta error
	DrawGammaSetMarkerTGraphErr(meanErrorsAcceptance, 28, 1.,color[5],color[5]);
	meanErrorsAcceptance->Draw("pX0,csame");
	// Other error
	DrawGammaSetMarkerTGraphErr(meanErrorsOther, 26, 1.,color[6],color[6]);
	meanErrorsOther->Draw("pX0,csame");
	// PCM Material budget 
	DrawGammaSetMarkerTGraphErr(graphMaterialError, 24, 1.,color[4],color[4]);
	graphMaterialError->Draw("pX0,csame");

	
	legendSummedMeanNew->AddEntry(meanErrorsSignalExtraction,"Signal Extraction","p");
	legendSummedMeanNew->AddEntry(meanErrorsPID,"Electron PID","p");
	legendSummedMeanNew->AddEntry(meanErrorsTrackReco,"Track Reconstruction","p");
	legendSummedMeanNew->AddEntry(meanErrorsPhotonReco,"Photon Reconstruction","p");
	legendSummedMeanNew->AddEntry(meanErrorsAcceptance,"Acceptance (#eta)","p");
    legendSummedMeanNew->AddEntry(graphMaterialError,"Material","p");
	legendSummedMeanNew->AddEntry(meanErrorsOther,"TOF, cos(P.A.)","p");
	
	DrawGammaSetMarkerTGraphErr(meanErrorsCorrSummedIncMat, 20, 1.,kBlack,kBlack);
	meanErrorsCorrSummedIncMat->Draw("p,csame");
	legendSummedMeanNew->AddEntry(meanErrorsCorrSummedIncMat,"quad. sum.","p");
	legendSummedMeanNew->Draw();
	
	labelMeson->Draw();
	labelCentrality->Draw();
	
	canvasSummedErrMean->Update();
	canvasSummedErrMean->SaveAs(Form("%s/SysErrorSummedVisu_%s_%s%s_%s.%s",outputdir.Data(),meson.Data(), energy.Data(),additionalNameOutput.Data(),dateForOutput.Data(),suffix.Data()));
	
	delete canvasSummedErrMean;




	const char *SysErrDatname = Form("SystematicErrorsCalculatedGammaPbPb_LHC11h_%s/SystematicError_%s_%s%s_%s.dat",dateForOutput.Data(),meson.Data(),energy.Data(),additionalNameOutput.Data(),dateForOutput.Data());
	fstream SysErrDat;
	cout << SysErrDatname << endl;
	SysErrDat.open(SysErrDatname, ios::out);
	for (Int_t l=0; l< nPtBins; l++){
		SysErrDat <<errorsNegCorrMatSummed[l] << "\t" <<errorsPosCorrMatSummed[l] << "\t"  <<errorsNegCorrSummed[l] << "\t" <<errorsPosCorrSummed[l]  << endl;
	}

	SysErrDat.close();

	const char *SysErrDatnameMean = Form("SystematicErrorsCalculatedGammaPbPb_LHC11h_%s/SystematicErrorAveraged_%s_%s%s_%s.dat",dateForOutput.Data(),meson.Data(),energy.Data(),additionalNameOutput.Data(),dateForOutput.Data());
	fstream SysErrDatAver;
	cout << SysErrDatnameMean << endl;
	SysErrDatAver.open(SysErrDatnameMean, ios::out);
	for (Int_t l=0; l< nPtBins; l++){
		if(smooth){
			SysErrDatAver << "-"<< errorsMeanCorrMatSummedSmoothed[l] << "\t" <<errorsMeanCorrMatSummedSmoothed[l] << "\t"  << "-"<< errorsMeanCorrSummedSmoothed[l] << "\t" <<errorsMeanCorrSummedSmoothed[l]  << endl;
		} else {
			SysErrDatAver << "-"<< errorsMeanCorrMatSummed[l] << "\t" <<errorsMeanCorrMatSummed[l] << "\t"  << "-"<< errorsMeanCorrSummed[l] << "\t" <<errorsMeanCorrSummed[l]  << endl;
		}
	}

	SysErrDatAver.close();

		
		
// 	
// 	const char *SysErrDatnameMeanPaper = Form("SystematicErrorsCalculatedGammaPbPb_LHC11h_%s/SystematicErrorAveragedPaper_%s_%s%s_%s.dat",dateForOutput.Data(),meson.Data(),energy.Data(),additionalNameOutput.Data(),dateForOutput.Data());
// 	fstream SysErrDatAverPaper;
// 	cout << SysErrDatnameMeanPaper << endl;
// 	SysErrDatAverPaper.open(SysErrDatnameMeanPaper, ios::out);
// 	SysErrDatAverPaper  << "#it{p}_{T}" << "\t Material \t Yield Extraction \t PID \t photon reco \t track recon \t summed" <<  endl;
// 	for (Int_t l=0; l< nPtBins; l++){
// 		SysErrDatAverPaper << ptBins[l] <<"\t" << errorMaterial*2 << "\t" << errorsMeanCorrSignalExtraction[l] << "\t" << errorsMeanCorrPID[l]<< "\t" << errorsMeanCorrPhotonReco[l]<< "\t" <<errorsMeanCorrTrackReco[l] <<"\t" << errorsMeanCorrMatSummed[l]<< endl;
// 	}
// 
// 	SysErrDatAverPaper.close();
	
}