// provided by Gamma Conversion Group, PWGGA, Friederike Bock fbock@physi.uni-heidelberg.de
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
#include "TString.h"
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
#include "TFitResultPtr.h"
#include "TFitResult.h"

using namespace std;

Double_t fFWHMFunc;
Double_t fFWHMFuncError;

void CalculateFWHM(TF1 * fFunc, Double_t startMass, Double_t endMass)
{
   // Default function
   TF1* fFunc_def;
   fFunc_def = new TF1("fFunc_def","(x<[1])*([0]*(exp(-0.5*((x-[1])/[2])^2)+exp((x-[1])/[3])*(1.-exp(-0.5*((x-[1])/[2])^2))))+(x>=[1])*([0]*exp(-0.5*((x-[1])/[2])^2))",startMass,endMass);
   fFunc_def->SetParameter(0,fFunc->GetParameter(0));
   fFunc_def->SetParameter(1,fFunc->GetParameter(1));
   fFunc_def->SetParameter(2,fFunc->GetParameter(2));
   fFunc_def->SetParameter(3,fFunc->GetParameter(3));



   //FWHM
   fFWHMFunc = fFunc->GetX(fFunc_def->GetParameter(0)*0.5,fFunc_def->GetParameter(1), endMass) - fFunc_def->GetX(fFunc_def->GetParameter(0)*0.5,startMass,fFunc_def->GetParameter(1));

   //FWHM error +
   TF1* fFunc_plus;
   // fFunc_plus = fFunc;
   fFunc_plus = new TF1("fFunc_plus","(x<[1])*([0]*(exp(-0.5*((x-[1])/[2])^2)+exp((x-[1])/[3])*(1.-exp(-0.5*((x-[1])/[2])^2))))+(x>=[1])*([0]*exp(-0.5*((x-[1])/[2])^2))",startMass,endMass);

   fFunc_plus->SetParameter(0,fFunc->GetParameter(0) + fFunc->GetParError(0));
   fFunc_plus->SetParameter(1,fFunc->GetParameter(1) + fFunc->GetParError(1));
   fFunc_plus->SetParameter(2,fFunc->GetParameter(2) + fFunc->GetParError(2));
   fFunc_plus->SetParameter(3,fFunc->GetParameter(3) + fFunc->GetParError(3));
   Double_t FWHM_plus = fFunc_plus->GetX(fFunc_plus->GetParameter(0)*0.5,fFunc_plus->GetParameter(1), endMass) - fFunc_plus->GetX(fFunc_plus->GetParameter(0)*0.5,startMass,fFunc_plus->GetParameter(1));

   //FWHM error -
   TF1* fFunc_minus;
   // fFunc_minus = fFunc;
   fFunc_minus = new TF1("fFunc_minus","(x<[1])*([0]*(exp(-0.5*((x-[1])/[2])^2)+exp((x-[1])/[3])*(1.-exp(-0.5*((x-[1])/[2])^2))))+(x>=[1])*([0]*exp(-0.5*((x-[1])/[2])^2))",startMass,endMass);
   fFunc_minus->SetParameter(0,fFunc->GetParameter(0) - fFunc->GetParError(0));
   fFunc_minus->SetParameter(1,fFunc->GetParameter(1) - fFunc->GetParError(1));
   fFunc_minus->SetParameter(2,fFunc->GetParameter(2) - fFunc->GetParError(2));
   fFunc_minus->SetParameter(3,fFunc->GetParameter(3) - fFunc->GetParError(3));
   Double_t FWHM_minus =  fFunc_minus->GetX(fFunc_minus->GetParameter(0)*0.5,fFunc_minus->GetParameter(1), endMass) -fFunc_minus->GetX(fFunc_minus->GetParameter(0)*0.5,startMass,fFunc_minus->GetParameter(1));

   Double_t Error1 = TMath::Abs(fFWHMFunc-FWHM_plus);
   Double_t Error2 = TMath::Abs(fFWHMFunc-FWHM_minus);

   if(Error1>=Error2) fFWHMFuncError = Error1;
   if(Error1<Error2) fFWHMFuncError = Error2;
}


void GetEventStats(const char *inputRootFile = "GammaConvV1.root", TString InputName="", Int_t runnumber = 1, TString fCutSelection ="", TString opt = "", TString nameFolder ="GammaConvV1", Int_t mode = 0){

   fstream outputFile(InputName.Data(),ios::out|ios::app);
   if(!outputFile.is_open()){
      cout<<"Problem opening file"<<endl;
      return;
   }

   cout << runnumber << endl;
   
   //  Char_t filename_input1[200] = (Form("%s%s",path,input1));  
   TString filename = inputRootFile;   
   TFile *file = new TFile(filename.Data()); 
   TList *list = (TList*) file->Get(nameFolder.Data());
   TList *HistosGammaConversion = (TList*)list->FindObject(Form("Cut Number %s",fCutSelection.Data()));
   TList *ESDContainer = (TList*) HistosGammaConversion->FindObject(Form("%s ESD histograms",fCutSelection.Data()));

   TH1D* fEventQuality = (TH1D*)ESDContainer->FindObject("NEvents");  
   TH1D* fESDConvGamma = (TH1D*)ESDContainer->FindObject("ESD_ConvGamma_Pt");  
   TH1D* fESDMult = (TH1D*)ESDContainer->FindObject("GoodESDTracks"); 
   Double_t meanMultTPC =  fESDMult->GetMean();
   Double_t rmsMultTPC =  fESDMult->GetRMS();
   TH1D* fESDMultV0 = (TH1D*)ESDContainer->FindObject("V0 Multiplicity");  
   Double_t meanMultV0 =  fESDMultV0->GetMean();
   Double_t rmsMultV0 =  fESDMultV0->GetRMS();


   TH2D* fInvMassMesonPt = (TH2D*)ESDContainer->FindObject("ESD_Mother_InvMass_Pt");
   TH1D *fGammaGamma = (TH1D*)fInvMassMesonPt->ProjectionX("ESD_Mother_InvMass");
   TH2D* fInvMassBGPt = (TH2D*)ESDContainer->FindObject("ESD_Background_InvMass_Pt");
   TH1D *fBck = (TH1D*)fInvMassBGPt->ProjectionX("ESD_BG_InvMass");

   for (Int_t binx= 0; binx < fGammaGamma->GetNbinsX()+1; binx++){
      if(fGammaGamma->GetBinContent(binx) == 0){
         fGammaGamma->SetBinError(binx,1.);
         fGammaGamma->SetBinContent(binx,0.);
      }
   }
   TH1D *  fBckNormPi = (TH1D*)fBck->Clone("fBckNormPi");
   TH1D *  fBckNormEta = (TH1D*)fBck->Clone("fBckNormEta");
   fGammaGamma->Sumw2();
   fBck->Sumw2();
   fBckNormPi->Sumw2();
   fBckNormEta->Sumw2();

   Double_t    rPi= fGammaGamma->Integral(fGammaGamma->GetXaxis()->FindBin(0.17),fGammaGamma->GetXaxis()->FindBin(0.3));
   Double_t    bPi= fBck->Integral(fBck->GetXaxis()->FindBin(0.17),fBck->GetXaxis()->FindBin(0.3));
   Double_t    normPi = 1;

   Double_t    rEta= fGammaGamma->Integral(fGammaGamma->GetXaxis()->FindBin(0.58),fGammaGamma->GetXaxis()->FindBin(0.8));
   Double_t    bEta= fBck->Integral(fBck->GetXaxis()->FindBin(0.58),fBck->GetXaxis()->FindBin(0.8));
   Double_t    normEta = 1;
   
   if(bPi != 0) normPi = rPi/bPi;
   fBckNormPi->Scale(normPi);
   if(bEta != 0) normEta = rEta/bEta;
   fBckNormEta->Scale(normEta);

//    cout<<"r="<<r<<" b="<<b<<" r/b="<<r/b<< " " << endl;
   
   Int_t numberOfZeros = 0;
   for (Int_t i = 1; i < fBckNormPi->GetNbinsX()+1; i++){
      if (fBckNormPi->GetBinContent(i) == 0){
         numberOfZeros++;
         if (normPi > 1.){
            fBckNormPi->SetBinError(i,1.);
            fBckNormPi->SetBinContent(i,0.);
         }
      }
   }
   numberOfZeros = 0;
   for (Int_t i = 1; i < fBckNormEta->GetNbinsX()+1; i++){
      if (fBckNormEta->GetBinContent(i) == 0){
         numberOfZeros++;
         if (normEta > 1.){
            fBckNormEta->SetBinError(i,1.);
            fBckNormEta->SetBinContent(i,0.);
         }
      }
   }

//    cout<<"counted " << numberOfZeros << " in the normalized BG" << endl;
   TCanvas* canvasMass = new TCanvas("canvasMass","",200,10,1350,900);  // gives the page size
   TH1D* fSignalPi = (TH1D*)fGammaGamma->Clone("fSignalPi");
   fSignalPi->Sumw2();
   fSignalPi->Add(fBckNormPi,-1.);

   if (mode == 0){
		fSignalPi->Rebin(2);
   } else {
		fSignalPi->Rebin(4);
   }   
   fSignalPi->GetXaxis()->SetRangeUser( 0.1,0.145);

   Double_t mesonAmplitude =fSignalPi->GetMaximum();
   Double_t mesonAmplitudeMinPi  = mesonAmplitude*80./100.;
   Double_t mesonAmplitudeMaxPi = mesonAmplitude*115./100.;
   TF1* fFitRecoPi = new TF1("GaussExpLinear","(x<[1])*([0]*(exp(-0.5*((x-[1])/[2])^2)+exp((x-[1])/[3])*(1.-exp(-0.5*((x-[1])/[2])^2)))+[4]+[5]*x)+(x>=[1])*([0]*exp(-0.5*((x-[1])/[2])^2)+[4]+[5]*x)",0.1,0.145);
   fFitRecoPi->SetParameter(0,mesonAmplitude);
   fFitRecoPi->SetParameter(1,0.135);
   fFitRecoPi->SetParameter(2,0.003);
   fFitRecoPi->SetParameter(3,0.012);
   fFitRecoPi->SetParLimits(0,mesonAmplitudeMinPi,mesonAmplitudeMaxPi);
   fFitRecoPi->SetParLimits(1,0.1,0.145);
   fFitRecoPi->SetParLimits(2,0.001,0.009);
   fFitRecoPi->SetParLimits(3,0.001,0.02);
   fSignalPi->Draw();
   fSignalPi->Fit(fFitRecoPi,"SINRMQE+","",0.1,0.145);
   TFitResultPtr result = fSignalPi->Fit(fFitRecoPi,"SINRMQE+","",0.1,0.145);
   fFitRecoPi->SetLineColor(3);
   fFitRecoPi->SetLineWidth(1);
   fFitRecoPi->SetLineStyle(1);
   fFitRecoPi->Draw("same");
   canvasMass->SaveAs("debugPi0.eps");
   
   Double_t widthPi = 0;
   Double_t widthPiErr = 0;
   Double_t massPi=0;
   Double_t massPiErr= 0;
   Double_t integral = 0;
   Double_t integralErr = 0;
   Double_t integralBG = 0;

   if(!(TString(gMinuit->fCstatu.Data()).CompareTo("CONVERGED") == 0 || TString(gMinuit->fCstatu.Data()).CompareTo("SUCCESSFUL") == 0) ){
      cout << "Pi0 Fitting failed in with status " << gMinuit->fCstatu.Data() <<endl << endl;
	  TString status = gMinuit->fCstatu.Data();
	  cout << status.Data() << endl;
	  if (status.Contains("PROBLEMS")){
		CalculateFWHM(fFitRecoPi,0.1,0.145);
		widthPi = fFWHMFunc;
		widthPiErr = fFWHMFuncError;
		massPi = fFitRecoPi->GetParameter(1);
		massPiErr = fFitRecoPi->GetParError(1);;
		integral = fFitRecoPi->Integral(0.1, 0.145, result->GetParams()) / fSignalPi->GetBinWidth(10);
		integralErr = fFitRecoPi->IntegralError(0.1, 0.145, result->GetParams(), result->GetCovarianceMatrix().GetMatrixArray() ) / fSignalPi->GetBinWidth(10);
		integralBG = fFitRecoPi->GetParameter(4)*0.145 + fFitRecoPi->GetParameter(5)/2 *0.145*0.145- (fFitRecoPi->GetParameter(4)*0.1 + fFitRecoPi->GetParameter(5)/2 *0.1*0.1);
		cout << "Pi0 width: "  << widthPi << "\t +-" << widthPiErr << "\t Mass: "<< massPi << "\t+-" << massPiErr  << endl;
		cout << "integral Pi: " << integral << "\t +-" << integralErr << "\t integral BG : "<< integralBG<< endl;		  
	  } else {
		cout << "here" << endl;  
	  } 
   } else {
      CalculateFWHM(fFitRecoPi,0.1,0.145);
      widthPi = fFWHMFunc;
      widthPiErr = fFWHMFuncError;
      massPi = fFitRecoPi->GetParameter(1);
      massPiErr = fFitRecoPi->GetParError(1);;
      integral = fFitRecoPi->Integral(0.1, 0.145, result->GetParams()) / fSignalPi->GetBinWidth(10);
      integralErr = fFitRecoPi->IntegralError(0.1, 0.145, result->GetParams(), result->GetCovarianceMatrix().GetMatrixArray() ) / fSignalPi->GetBinWidth(10);
      integralBG = fFitRecoPi->GetParameter(4)*0.145 + fFitRecoPi->GetParameter(5)/2 *0.145*0.145- (fFitRecoPi->GetParameter(4)*0.1 + fFitRecoPi->GetParameter(5)/2 *0.1*0.1);
      cout << "Pi0 width: "  << widthPi << "\t +-" << widthPiErr << "\t Mass: "<< massPi << "\t+-" << massPiErr  << endl;
      cout << "integral Pi: " << integral << "\t +-" << integralErr << "\t integral BG : "<< integralBG<< endl;

   }


   TH1D* fSignalEta = (TH1D*)fGammaGamma->Clone("fSignalEta");
   fSignalEta->Sumw2();
   fSignalEta->Add(fBckNormEta,-1.);

   fSignalEta->Rebin(4);
   fSignalEta->GetXaxis()->SetRangeUser( 0.5,0.57);


   TF1* fFitRecoEta = new TF1("GaussExpLinearEta","(x<[1])*([0]*(exp(-0.5*((x-[1])/[2])^2)+exp((x-[1])/[3])*(1.-exp(-0.5*((x-[1])/[2])^2)))+[4]+[5]*x)+(x>=[1])*([0]*exp(-0.5*((x-[1])/[2])^2)+[4]+[5]*x)",0.5,0.57);
   Double_t mesonAmplitudeEta =fSignalEta->GetMaximum();
   Double_t mesonAmplitudeMinEta  = mesonAmplitude*80./110.;
   Double_t mesonAmplitudeMaxEta = mesonAmplitude*115./100.;

   fFitRecoEta->SetParameter(0,mesonAmplitude);
   fFitRecoEta->SetParameter(1,0.548);
   fFitRecoEta->SetParameter(2,0.005);
   fFitRecoEta->SetParameter(3,0.007);
   fFitRecoEta->SetParLimits(0,mesonAmplitudeMinEta,mesonAmplitudeMaxEta);
   fFitRecoEta->SetParLimits(1,0.52,0.56);
   fFitRecoEta->SetParLimits(2,0.002,0.015);
   fFitRecoEta->SetParLimits(3,0.005,0.026);
   fSignalEta->Draw("");
   fSignalEta->Fit(fFitRecoEta,"SINRMQE+","",0.5,0.57);
   TFitResultPtr resultEta = fSignalEta->Fit(fFitRecoEta,"SINRQME+","",0.5,0.57);

   fFitRecoEta->SetLineColor(3);
   fFitRecoEta->SetLineWidth(1);
   fFitRecoEta->SetLineStyle(1);
   fFitRecoEta->Draw("same");
   canvasMass->SaveAs("debugEta.eps");
   Double_t widthEta = 0;
   Double_t widthEtaErr = 0;
   Double_t massEta =0;
   Double_t massEtaErr =0;
   Double_t integralEta = 0;
   Double_t integralEtaErr = 0;
   Double_t integralEtaBG = 0;

   if(!(TString(gMinuit->fCstatu.Data()).CompareTo("CONVERGED") == 0 || TString(gMinuit->fCstatu.Data()).CompareTo("SUCCESSFUL") == 0) ){
      cout << "Fitting failed in with status " << gMinuit->fCstatu.Data() <<endl << endl;    
   } else {
      CalculateFWHM(fFitRecoEta,0.1,0.145);
      widthEta = fFWHMFunc;
      widthEtaErr = fFWHMFuncError;
      massEta = fFitRecoEta->GetParameter(1);
      massEtaErr = fFitRecoEta->GetParError(1);;
      cout << "Eta width: "  << widthEta << "\t +-" << widthEtaErr << "\t Mass: "<< massEta << "\t+-" << massEtaErr  << endl;

      integralEta = fFitRecoEta->Integral(0.5,0.57, resultEta->GetParams()) / fSignalEta->GetBinWidth(10);
      integralEtaErr = fFitRecoEta->IntegralError(0.5,0.57, resultEta->GetParams(), resultEta->GetCovarianceMatrix().GetMatrixArray() ) / fSignalEta->GetBinWidth(10);
      integralEtaBG = fFitRecoEta->GetParameter(4)*0.57 + fFitRecoEta->GetParameter(5)/2 *0.57*0.57- (fFitRecoEta->GetParameter(4)*0.5 + fFitRecoEta->GetParameter(5)/2 *0.5*0.5);
      cout << "integral Eta: " << integralEta << "\t +-" << integralEtaErr << "\t integral BG : "<< integralEtaBG<< endl;
   }

   outputFile << runnumber << "\t" << fEventQuality->GetBinContent(1) <<"\t" << fEventQuality->GetBinContent(2) <<"\t" << fEventQuality->GetBinContent(3) <<"\t" << fEventQuality->GetBinContent(4) << "\t" << fEventQuality->GetBinContent(5) << "\t" << fEventQuality->GetBinContent(6) << "\t" << fEventQuality->GetBinContent(7) << "\t" << fESDConvGamma->GetEntries()<< "\t" << meanMultTPC << "\t" << rmsMultTPC << "\t" << meanMultV0<< "\t" << rmsMultV0<<"\t" << integral << "\t" << integralErr << "\t"<< integralBG <<"\t"<< massPi << "\t" << massPiErr << "\t" << widthPi << "\t" << widthPiErr << "\t"<< massEta << "\t" << massEtaErr << "\t" << widthEta << "\t" << widthEtaErr << "\t" << integralEta << "\t" << integralEtaErr << "\t"<< integralEtaBG<<endl;
   outputFile.close();
}

