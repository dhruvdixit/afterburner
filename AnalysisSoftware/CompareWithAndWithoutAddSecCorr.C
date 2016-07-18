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
#include "TRandom2.h"
#include "TLatex.h"
#include "TASImage.h"
#include "TPostScript.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TArrow.h"
#include "TMarker.h"
#include "TGraphAsymmErrors.h"
#include "CommonHeaders/PlottingGammaConversionHistos.h"
#include "CommonHeaders/PlottingGammaConversionAdditional.h"

void CompareWithAndWithoutAddSecCorr(TString fileName1, TString fileName2, TString fEnergy,TString fSuffix, TString xAxisTitle = "(w)/(w/o) additional secondary contribution (RAW Yield)"){
	
	TFile* fileWithoutAddSec = 			new TFile(fileName1,"READ");
	TH1D *histoWithoutAddSecCorr =					(TH1D*)fileWithoutAddSec->Get("CorrectedYieldTrueEff");
	TH1D *histoWithoutAddSecCorrEffi =					(TH1D*)fileWithoutAddSec->Get("TrueMesonEffiPt");
		
	TFile* fileWithAddSec = 			new TFile(fileName2,"READ");
	TH1D *histoWithAddSecCorr =					(TH1D*)fileWithAddSec->Get("CorrectedYieldTrueEff"); 
	TH1D *histoWithAddSecCorrEffi =					(TH1D*)fileWithAddSec->Get("TrueMesonEffiPt");
	
	TH1D* histoRatioWithOverWithout = (TH1D*)histoWithAddSecCorr->Clone("histoRatioWithOverWithout");
	histoRatioWithOverWithout->Divide(histoRatioWithOverWithout,histoWithoutAddSecCorr,1.,1.,"B");
	TH1D* histoRatioEffiWithOverWithout = (TH1D*)histoWithAddSecCorrEffi->Clone("histoRatioEffiWithOverWithout");
	histoRatioEffiWithOverWithout->Divide(histoRatioEffiWithOverWithout,histoWithoutAddSecCorrEffi,1.,1.,"B");

	
	TCanvas* canvasComparison = new TCanvas("canvasComparison","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasComparison, 0.1, 0.02, 0.02, 0.09);
	canvasComparison->SetLogx(0);	
	
	DrawGammaSetMarker(histoRatioWithOverWithout, 20, 1.5, kBlack, kBlack);										 					
	DrawAutoGammaMesonHistos( histoRatioWithOverWithout, 
			"", "p_{t} (GeV/c)", xAxisTitle.Data(), 
			kFALSE, 2., 3e-6, kFALSE,
			kTRUE, 0.8, 1.2, 
			kFALSE, 0.2, 16.);
			
	canvasComparison->Update();
	canvasComparison->SaveAs(Form("ComparisonWithOverWithout_%s.%s",fEnergy.Data(),fSuffix.Data()));
	delete canvasComparison;

	TCanvas* canvasComparisonEffi = new TCanvas("canvasComparisonEffi","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasComparisonEffi, 0.1, 0.02, 0.02, 0.09);
	canvasComparisonEffi->SetLogx(0);	
	
	DrawGammaSetMarker(histoRatioEffiWithOverWithout, 20, 1.5, kBlack, kBlack);
	DrawAutoGammaMesonHistos( histoRatioEffiWithOverWithout, 
			"", "p_{t} (GeV/c)", xAxisTitle.Data(), 
			kFALSE, 2., 3e-6, kFALSE,
			kTRUE, 0.8, 1.2, 
			kFALSE, 0.2, 16.);
			
	canvasComparisonEffi->Update();
	canvasComparisonEffi->SaveAs(Form("ComparisonWithOverWithoutEffi_%s.%s",fEnergy.Data(),fSuffix.Data()));
	delete canvasComparisonEffi;

}
