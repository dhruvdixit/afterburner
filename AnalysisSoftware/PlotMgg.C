const Double_t kMean=0.136 ; //Approximate peak position to facilitate error estimate
void PlotMgg(const Int_t centrality=0)
{

  const Double_t ptMin=2.;
  const Double_t ptMax=2.5;

  PPRstyle() ;
  
  gStyle->SetOptTitle(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  TGaxis::SetMaxDigits(3);
  
  
  //Fit Real/Mixed ratio, normalize Mixed and subtract it from Real

  TFile * f = new TFile("PHOS_PbPb_mgg.root") ;

  TH2F *h , *hAdd;
  TH2F *hm, *hmAdd;  
  if (centrality == 0 ) {// centrality 0-20%, 
    h = (TH2F*)f->Get("hPi0Both2core_cen0") ;
    hm= (TH2F*)f->Get("hMiPi0Both2core_cen0") ;
    h->Add((TH2F*)f->Get("hPi0Both2core_cen1")) ;
    hm->Add((TH2F*)f->Get("hMiPi0Both2core_cen1")) ;
    h->Add((TH2F*)f->Get("hPi0Both2core_cen2")) ;
    hm->Add((TH2F*)f->Get("hMiPi0Both2core_cen2")) ;
  }    
  if (centrality == 1 ) {// centrality 60-80%,   
    h = (TH2F*)f->Get("hPi0Both2core_cen5") ;
    hm= (TH2F*)f->Get("hMiPi0Both2core_cen5") ;
  }


  TAxis * pta = h->GetYaxis() ;
  Int_t imin=pta->FindBin(ptMin+0.0001);
  Int_t imax=pta->FindBin(ptMax-0.0001) ;
  TH1D * hp = h->ProjectionX("re",imin,imax) ;
  hp->Sumw2() ;
  TH1D * hpm= hm->ProjectionX("mi",imin,imax) ;
  
  TF1 * fit1 = new TF1("fit",CB,0.,1.,6) ;
  TF1 * fbg1 = new TF1("bg1",BG1,0.,1.,3) ;
  
  TH1D * remi = re->Clone("remi") ;
  remi->Divide(hpm) ;
  remi->SetXTitle("m_{#gamma#gamma} (GeV/c^{2})") ;
  remi->SetYTitle("Real/Mixed") ;
  remi->GetXaxis()->SetRangeUser(0.,0.3) ;
  
  Double_t rangeMin=0.1 ;
  Double_t rangeMax=0.2 ;
    fit1->SetParameters(0.001,0.136,0.0055,0.0002,-0.002,0.0) ;
    fit1->SetParLimits(0,0.000,1.000) ;
    fit1->SetParLimits(1,0.120,0.145) ;
    fit1->SetParLimits(2,0.005,0.012) ;
  remi->Fit(fit1,"Q" ,"",rangeMin,rangeMax) ;
  remi->Fit(fit1,"MQ","",rangeMin,rangeMax) ;  
  
//  return ;
  
  fbg1->SetParameters(fit1->GetParameter(3),fit1->GetParameter(4),fit1->GetParameter(5)); 
  hpm ->Multiply(fbg1) ;
  
  TH1D * hS = hp->Clone("Signal") ;
  hS->Add(hpm,-1.) ;
  Double_t nScale=(centrality==0)?7.:1. ;
  hS->Scale(nScale) ;

  TF1 * gs  = new TF1("gaus","gaus",0.,1.) ;
  gs->SetLineColor(kBlue);
  gs->SetLineWidth(2);
   hS->Fit(gs,"","",0.05,0.3) ;
  
  
  TH1D * hBox = new TH1D("box",Form("Centrality 0-20%%, %3.1f<p_{t}<%3.1f GeV/c",ptMin,ptMax),100,0.1,0.2) ;
  hp->SetMinimum(-100.) ;
  hp->SetMaximum(799.) ;
if(centrality==0){
  hp->SetMinimum(-10000.) ;
  hp->SetMaximum(130000.) ;
}
  //  hBox->SetMaximum(800.) ;
  hp->SetXTitle("M_{#gamma#gamma} (GeV/c^{2})") ;
  hp->SetNdivisions(505,"XY");

  Double_t mBinPi0 = hp->GetBinWidth(1);
  hp->SetYTitle(Form("Events/%.0f MeV/c^{2}",mBinPi0*1000));

  hp->SetTitleOffset(1.4,"Y");
  hp->SetLabelOffset(0.015,"Y");
  hp->SetTitleOffset(1.0,"X");
  

  hp->SetLineWidth(2);
  hS->SetLineWidth(2);
  hS->SetMarkerColor(kRed+1);
  hS->SetLineColor(kRed+1);
  hS->SetLineStyle(9);
  hS->SetMarkerStyle(20);
  hS->SetMarkerSize(1.);


  hp->SetLabelFont(42,"XY");
  hp->SetTitleFont(42,"XY");
  hp->SetLabelSize(0.04,"XY");
  hp->SetTitleSize(0.04,"XY");
  
  hp->SetMarkerStyle(20) ;
  hp->SetMarkerSize(0.001) ;
  hp->GetXaxis()->SetRangeUser(0.1,0.19999) ;

//  hpm->SetFillColor(kYellow) ;
  hpm->SetLineColor(kOrange-3) ;
  hpm->SetLineWidth(2) ;
  
  TCanvas * cM = new TCanvas("cen","") ;//,10,10,610,410) ;
  cM->SetFillColor(0) ;
  cM->SetFillStyle(0) ;
  cM->Range(0,0,1,1);
  cM->SetBorderSize(0);

   hp->Draw("h") ;
   hS->Draw("same") ;
   
   
  TPaveText *txtPi0 = new TPaveText(0.55,0.72,0.86,0.80,"NDC");
  txtPi0->SetFillColor(kWhite);
  txtPi0->SetBorderSize(0);
  txtPi0->SetTextAlign(14);
  txtPi0->AddText("PHOS");
  txtPi0->AddText(Form("#pi^{0}: %3.1f<p_{T}<%3.1f GeV/c",ptMin,ptMax));
  txtPi0->Draw();
  
  TLatex *labelCentrality = new TLatex(0.565,0.69,Form("PbPb @ #sqrt{#it{s}_{_{NN}}} 2.76 TeV"));
  SetStyleTLatex(labelCentrality, 0.03,4,kRed,kTRUE);
  labelCentrality->Draw();
  TLatex *labelCentrality2 = (centrality==0)? new TLatex(0.565,0.65,"0-20%") : new TLatex(0.565,0.65,"60-80%") ;
  SetStyleTLatex( labelCentrality2, 0.03,4,kRed,kTRUE);
  labelCentrality2->Draw();
   
  if(nScale!=1.){
    TLatex *labelS = new TLatex(0.48,0.40,Form("Signal #times %1.0f",nScale));
    SetStyleTLatex(labelS, 0.033,4,kRed,kTRUE);
    labelS->Draw();
  }   
   
  

}
//-----------------------------------------------------------------------------
Double_t CB(Double_t * x, Double_t * par){
  //Parameterization of Real/Mixed ratio
  Double_t m=par[1] ;
  Double_t s=par[2] ;
  Double_t dx=(x[0]-m)/s ;
  return par[0]*exp(-dx*dx/2.)+par[3]+par[4]*(x[0]-kMean) ;
}
//-----------------------------------------------------------------------------
Double_t BG1(Double_t * x, Double_t * par){
  //Normalizatino of Mixed
  return par[0]+par[1]*(x[0]-kMean) ;
}

//=============================================================================
PPRstyle()
{

  //////////////////////////////////////////////////////////////////////
  //
  // ROOT style macro for the TRD TDR
  //
  //////////////////////////////////////////////////////////////////////

  gStyle->SetPalette(1);
  gStyle->SetCanvasBorderMode(-1);
  gStyle->SetCanvasBorderSize(1);
  gStyle->SetCanvasColor(10);

  gStyle->SetFrameFillColor(10);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameBorderMode(-1);
  gStyle->SetFrameLineWidth(1.2);
  gStyle->SetFrameLineColor(1);

  gStyle->SetHistFillColor(0);
  gStyle->SetHistLineWidth(2);
  gStyle->SetHistLineColor(1);

  gStyle->SetPadColor(10);
  gStyle->SetPadBorderSize(1);
  // gStyle->SetPadBorderMode(-1);

  gStyle->SetStatColor(10);
  gStyle->SetTitleColor(kBlack,"X");
  gStyle->SetTitleColor(kBlack,"Y");

  gStyle->SetLabelSize(0.04,"X");
  gStyle->SetLabelSize(0.04,"Y");
  gStyle->SetLabelSize(0.04,"Z");
  gStyle->SetTitleSize(0.04,"X");
  gStyle->SetTitleSize(0.04,"Y");
  gStyle->SetTitleSize(0.04,"Z");
  gStyle->SetTitleFont(42,"X");
  gStyle->SetTitleFont(42,"Y");
  gStyle->SetTitleFont(42,"X");
  gStyle->SetLabelFont(42,"X");
  gStyle->SetLabelFont(42,"Y");
  gStyle->SetLabelFont(42,"Z");
  gStyle->SetStatFont(42);

  gStyle->SetTitleOffset(1.0,"X");
  gStyle->SetTitleOffset(1.4,"Y");

  gStyle->SetTitleFillColor(kWhite);

  gStyle->SetOptDate(0);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

}
void SetStyleTLatex( TLatex* text, Size_t textSize, Width_t lineWidth, Color_t textColor = 1, Bool_t kNDC = kTRUE){
	if (kNDC) {text->SetNDC();}
	text->SetTextColor(textColor);
	text->SetTextSize(textSize);
	text->SetLineWidth(lineWidth);
}

