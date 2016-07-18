Double_t w(Double_t * x, Double_t *par){

  return TMath::Sqrt(par[0]*par[0]+par[1]*par[1]/x[0]/x[0]+par[2]*par[2]*x[0]*x[0]) ;

}

void CompMass(){

  PPRstyle() ;
  gStyle->SetOptFit(1);

  TFile *f= new TFile("/home/fredi/Photon/Software/photonconv/AnalysisSoftware/PHOS_Pi0MassPosData.root");
  TH1D * m1 = (TH1D*)f->Get("Mix_CB_mr1") ;
  TH1D * s1 = (TH1D*)f->Get("Mix_CB_sr1") ;
  TH1D * mG1 = (TH1D*)f->Get("Mix_mr1") ;
  TH1D * sG1 = (TH1D*)f->Get("Mix_sr1") ;

  m1->SetXTitle("p_{t} (GeV/c)") ;
  m1->SetYTitle("m_{#gamma#gamma} (GeV/c)") ;
  

  TFile * fmc= new TFile("/home/fredi/Photon/Software/photonconv/AnalysisSoftware/PHOS_Pi0MassPosMC.root") ;
  TH1D * massMC = (TH1D*)fmc->Get("mass1_GS") ;
  TH1D * massCB = (TH1D*)fmc->Get("mass1_CB") ;
  TH1D * widthMC = (TH1D*)fmc->Get("width1_GS") ;
  TH1D * widthCB = (TH1D*)fmc->Get("width1_CB") ;
  
  massMC->SetMarkerStyle(28) ;
  massMC->SetMarkerColor(6) ;
  massMC->SetLineColor(6) ;
  
  massCB->SetMarkerStyle(29) ;
  massCB->SetMarkerColor(2) ;
  massCB->SetLineColor(2) ;

  widthMC->SetMarkerStyle(28) ;
  widthMC->SetMarkerColor(6) ;
  widthMC->SetLineColor(6) ;
  
  widthCB->SetMarkerStyle(29) ;
  widthCB->SetMarkerColor(2) ;
  widthCB->SetLineColor(2) ;

  
  //  massMC->Divide(mG1);   massMC->Draw() ; return ;

  TCanvas * cm = new TCanvas("mass_7TeV","mass_7TeV",10,10,410,410) ;

  //Mass
  mG1->SetMarkerStyle(20) ;
  mG1->SetMarkerColor(12) ;
  mG1->SetMarkerSize(0.7) ;
  m1->SetMarkerStyle(21) ;
  m1->SetMarkerSize(0.7) ;
  m1->SetMarkerColor(4) ;
  mG1->SetXTitle("p_{t} (GeV/c)") ;
  mG1->SetYTitle("m (GeV/c^{2})") ;
  mG1->SetMinimum(0.125) ;
  mG1->SetMaximum(0.150) ;
  mG1->Draw() ;
  //  m1->Draw("same") ;
  massMC->Draw("same") ;
  //  massCB->Draw("same") ;
  TLegend * l = new TLegend(0.7,0.75,0.9,0.9) ;
  //  l->AddEntry(m1,"Data, Crystal Ball","p") ;
  //  l->AddEntry(mG1,"Data, Gaus","p") ;
  l->AddEntry(mG1,"Data","p") ;
 
  //  l->AddEntry(massCB,"MC, Crystal Ball","p") ;
  //  l->AddEntry(massMC,"MC, CB","p") ;
  l->AddEntry(massMC,"Monte-Carlo","p") ;
  l->Draw() ;

  //  return ;
  TCanvas * cm = new TCanvas("width_7TeV","width_7TeV",10,10,410,410) ;
  //Width
  sG1->SetMarkerStyle(20) ;
  sG1->SetMarkerColor(12) ;
  sG1->SetMarkerSize(0.7) ;
  s1->SetMarkerStyle(21) ;
  s1->SetMarkerSize(0.7) ;
  s1->SetMarkerColor(4) ;
  sG1->SetXTitle("p_{t} (GeV/c)") ;
  sG1->SetYTitle("#sigma (GeV/c^{2})") ;
  sG1->SetMinimum(0.00) ;
  sG1->SetMaximum(0.02) ;
  sG1->Draw() ;
  //  s1->Draw("same") ;
  widthMC->Draw("same") ;
  //  widthCB->Draw("same") ;
  TLegend * ll = new TLegend(0.7,0.7,0.9,0.9) ;
  ll->AddEntry(s1,"Data","p") ;
  ll->AddEntry(widthMC,"Monte-Carlo","p") ;
  /*
  ll->AddEntry(s1,"Data, Crystal Ball","p") ;
  ll->AddEntry(sG1,"Data, Gaus","p") ;
  ll->AddEntry(widthCB,"MC, Crystal Ball","p") ;
  ll->AddEntry(widthMC,"MC, Gaus","p") ;
  */
  ll->Draw() ;



}
//-----------------------------------------------------------------------------
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
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistLineColor(1);

  gStyle->SetPadColor(10);
  gStyle->SetPadBorderSize(1);
  gStyle->SetPadBorderMode(-1);

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

  gStyle->SetFillColor(kWhite);
  gStyle->SetTitleFillColor(kWhite);

  gStyle->SetOptDate(0);
  gStyle->SetOptTitle(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

}

