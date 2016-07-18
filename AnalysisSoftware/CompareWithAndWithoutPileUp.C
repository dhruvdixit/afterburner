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

void CompareWithAndWithoutPileUp(TString fileName1, TString fileName2, TString fEnergy,TString fSuffix, TString meson, Double_t startRatio=0.8, Double_t endRatio=1.2, TString xAxisTitle = "(w)/(w/o) PileUp Rejection"){
	
	TFile* fileWithoutPileUp = 			new TFile(fileName1,"READ");
	TDirectory* directoryPi07TeVWOPileUp = 			(TDirectory*)fileWithoutPileUp->Get(Form("%s2.76TeV",meson.Data())); 	
	TH1D *histoWithoutPileUp =					(TH1D*)directoryPi07TeVWOPileUp->Get(Form("CorrectedYield%sBinShifted",meson.Data()));
		
	TFile* fileWithPileUp = 			new TFile(fileName2,"READ");
	TDirectory* directoryPi07TeVWPileUp = 			(TDirectory*)fileWithPileUp->Get(Form("%s2.76TeV",meson.Data())); 	
	TH1D *histoWithPileUp =					(TH1D*)directoryPi07TeVWPileUp->Get(Form("CorrectedYield%sBinShifted",meson.Data()));
	
	TH1D* histoRatioWithOverWithout = (TH1D*)histoWithPileUp->Clone("histoRatioWithOverWithout");
	for (Int_t i = 1; i < histoRatioWithOverWithout->GetNbinsX()+1;i++){
		cout << histoRatioWithOverWithout->GetBinCenter(i) << "\t" << histoWithoutPileUp->GetBinCenter(i) << endl;
		if (histoRatioWithOverWithout->GetBinCenter(i) == histoWithoutPileUp->GetBinCenter(i) && histoWithoutPileUp->GetBinContent(i)!= 0){
			cout << histoRatioWithOverWithout->GetBinContent(i)/histoWithoutPileUp->GetBinContent(i) << endl;
			histoRatioWithOverWithout->SetBinContent(i,histoRatioWithOverWithout->GetBinContent(i)/histoWithoutPileUp->GetBinContent(i));
		} else {
			histoRatioWithOverWithout->SetBinContent(i,0);
		}
	}
	
// 	histoRatioWithOverWithout->Divide(histoRatioWithOverWithout,histoWithoutPileUp,1.,1.,"B");
	
	
	
	TCanvas* canvasComparison = new TCanvas("canvasComparison","",200,10,1350,900);  // gives the page size
	DrawGammaCanvasSettings( canvasComparison, 0.1, 0.02, 0.02, 0.09);
	canvasComparison->SetLogx(0);	
	
	DrawGammaSetMarker(histoRatioWithOverWithout, 20, 1.5, kBlack, kBlack);										 					
	DrawAutoGammaMesonHistos( histoRatioWithOverWithout, 
			"", "p_{t} (GeV/c)", xAxisTitle.Data(), 
			kFALSE, 2., 3e-6, kFALSE,
			kTRUE, startRatio,endRatio, 
			kFALSE, 0.2, 16.);

	TF1 *fRatioConst  = new TF1("line","[0]",0.2,16.); 
	histoRatioWithOverWithout->Fit(fRatioConst,"RME0");
	Double_t parameterProb[1];
	fRatioConst->GetParameters(parameterProb);
	TLine *line = new TLine(0.,parameterProb[0],16.,parameterProb[0]);
	line->SetLineWidth(1);
	line->SetLineColor(kRed+2);
	line->Draw();

	canvasComparison->Update();
	canvasComparison->SaveAs(Form("%s_Comparison_%s.%s",meson.Data(),fEnergy.Data(),fSuffix.Data()));
	delete canvasComparison;

	
}
