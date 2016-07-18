TString outputDir;

TObjArray *arr;
TLatex *gammaL;
TLatex *nlo;
TLatex *cocktail;
TLatex *tpi;
TLatex *teta;
TLatex *tomega;
TLatex *tetaprime;
TLatex *tphi;
TLatex *trho;
TLatex *tsigma;

//declaration for printing logo 
Float_t purityDrawingCoordinates[5] = {0.25, 0.76, 0.2, 0.05, 0.0};
Float_t convProbDrawingCoordinates[5] = {0.25, 0.76, 0.2, 0.05, 0.0};
Float_t recoEffDrawingCoordinates[5] =  {0.25, 0.76, 0.2, 0.05, 0.0};
Float_t incRatioDrawingCoordinates[5] =  {0.65, 0.75, 0.2, 0.05, 0.0};
Float_t incRatioAllDrawingCoordinates[5] =  {0.45, 0.75, 0.2, 0.05, 0.0};
Float_t decayRatioDrawingCoordinates[5] =  {0.2, 0.75, 0.2, 0.05, 0.0};


Double_t binningRAA[12] = {0.4,0.8,1.0,1.4,1.8,2.2,2.6,3.0,4.0,5.0,6.0,8.0};
Double_t multiplicity[10] = {1502.7,923.26,558.68,321.20,171.67,85.13,38.51,15.78,6.32,2.63}; 
//                           0-1,   1-2,   2-3,   3-4,   4-5,  5-6,  6-7,  7-8,  8-9, 9-10
Double_t multiplicityCent[6] = {1686.87,1319.89, 1031.9,807.90,627.99,483.95};
//                               0-05,   05-1  

TH1D *histoBinningDoubleRatioRaa;

Bool_t pictDrawingOptions[4] = {kFALSE, kFALSE, kFALSE, kTRUE};

TString textFinder;
TString textPi0New;

TString textPrefix2;
TString Meson_text;

TFile *fileGamma;
TFile *filePi0;
TFile *fileEta;
TFile *fileQuarkMatter;
TFile *fileSystErrorPbPb;

TString fcocktailFuncA = "";
TString fcocktailFuncB = "";
TString fcocktailFuncC = "";
TString fcocktailFuncPions = "";
TString fcocktailFuncPHOS = "";
TString fcocktailFuncNarrow = "";
TString fcocktailFuncWide = "";
TString fcocktailFuncSyst = "";
Double_t fcmult;
Bool_t ffive = kFALSE;

TGraphErrors *graphNLOCalcMuHalfcopyA;
TGraphErrors *graphNLOCalcMuHalfcopyB;
TGraphErrors *graphNLOCalcMuHalfcopyC;

TGraphErrors *half;
TGraphErrors *one;
TGraphErrors *two;

TGraphAsymmErrors *PbPb276CTEQ61EPS09BFG2_sum_pdferr;
TGraphAsymmErrors *PbPb276CTEQ61EPS09BFG2_sum_pdferr_InvYield;
TGraphAsymmErrors *pp276CT10BFG2_sum_pdferr;
TGraphAsymmErrors *pp276CT10BFG2_sum_pdferr_InvYield;

TGraphAsymmErrors *PbPb276EPS09BFG2_sum_scale;
TGraphAsymmErrors *PbPb276EPS09BFG2_sum_scale_InvYield;
TGraphAsymmErrors *pp276CT10BFG2_sum_scale;
TGraphAsymmErrors *pp276CT10BFG2_sum_scale_InvYield;

Double_t *xHalf;
Double_t *yHalf;
Double_t *eyHalf;

Double_t *xOne;
Double_t *yOne;
Double_t *eyOne;

Double_t *xTwo;
Double_t *yTwo;
Double_t *eyTwo;


TFile *combinedFile;
TFile *combinedFileOld;
TFile *cocktailFileA;
TFile *cocktailFileB;
TFile *cocktailFileC;
TFile *cocktailFilepp;
TFile *cocktailFileHadrons;
TFile *cocktailFilePions;
TFile *cocktailFilePHOS;
TFile *cocktailFileWide;
TFile *cocktailFileNarrow;
TFile *cocktailFileSyst;
TFile *finalppFile;
TDirectoryFile *cocktailA;
TDirectoryFile *cocktailB;
TDirectoryFile *cocktailDirA;
TDirectoryFile *cocktailDirB;
TDirectoryFile *cocktailDirC;
TDirectoryFile *cocktailDirpp;
TDirectoryFile *cocktailDirHadrons;
TDirectoryFile *cocktailDirPions;
TDirectoryFile *cocktailDirPHOS;
TDirectoryFile *cocktailDirWide;
TDirectoryFile *cocktailDirNarrow;
TDirectoryFile *cocktailDirSyst;

TH1D *histoCorrectedEtaNormalEff;
TH1D *histoCorrectedEtaTrueEff;


const char* fileNameNLOPhotonTwo;
const char* fileNameNLOPhotonOne;
const char* fileNameNLOPhotonHalf;

ifstream inDRDimitri;
ifstream inHalf;
ifstream inOne;
ifstream inTwo;
Double_t xSection;
Double_t recalcBarn = 1e12; //NLO in pbarn!!!!

Double_t		xSection7TeV =			62.22*1e-3;
Double_t		xSection7TeVV0AND =			54.31*1e-3;
Double_t		xSection7TeVErrUp =		2.18;
Double_t		xSection7TeVErrDown =	2.18;
Double_t		xSection900GeV =		47.78*1e-3;
Double_t		xSection900GeVV0AND =		40.06*1e-3;
Double_t		xSection900GeVErrUp =		 2.39;
Double_t		xSection900GeVErrDown =		 1.86;
Double_t		xSection2760GeV = 		55.416*1e-3;
Double_t		xSection2760GeVV0AND = 		47.73*1e-3;
Double_t		xSection2760GeVErr = 	3.9;

Double_t xSection2760GeVpp = 		55.416*1e-3;
Double_t xSection2760GeVErrpp = 	3.9;
Double_t xSection2760GeVppINEL = 62.8*1e9;
Double_t xSection5023GeVppINEL = 		70*1e-3;
Double_t xSection900GeVppINEL = 52.5*1e9;
Double_t xSection7TeVppINEL = 73.2*1e9;	




Int_t nlinesNLOTwo = 0;
Int_t nlinesNLOOne = 0;
Int_t nlinesNLOHalf = 0;
Double_t muXU[100];
Double_t muXD[100];
Double_t ptNLOPhotonTwo[100];
Double_t ptNLOPhotonOne[100];
Double_t ptNLOPhotonHalf[100];
Double_t muHalfDF[100];
Double_t muHalfD[100];
Double_t muHalfF[100];
Double_t muOneDF[100];
Double_t muOneD[100];
Double_t muOneF[100];
Double_t muTwoDF[100];
Double_t muTwoD[100];
Double_t muTwoF[100];

TGraphErrors *graphNLOCalcMuTwo;
TGraphErrors *graphNLOCalcMuOne;
TGraphErrors *graphNLOCalcMuHalf;
TGraphErrors *graphNLOCalcMuTwoRebin;
TGraphErrors *graphNLOCalcMuOneRebin;
TGraphErrors *graphNLOCalcMuHalfRebin;
TH1D *histNLOCalcMuTwoRebin;
TH1D *histNLOCalcMuOneRebin;
TH1D *histNLOCalcMuHalfRebin;

TGraphAsymmErrors* combined7TeV;
TGraphAsymmErrors* combinedEta7TeV;
TGraphAsymmErrors* combined7TeVRebin;

TGraphAsymmErrors* combined7TeVOld;
TGraphAsymmErrors* combinedEta7TeVOld;
TGraphAsymmErrors* combined7TeVRebinOld;

TF1 *One;

TF1 *fitNLOMuHalf;
TF1 *fitNLOMuOne;
TF1 *fitNLOMuTwo;

TF1 *CombinedFitA;
TF1 *CombinedFitB;
TF1 *CombinedFitEtaA;
TF1 *CombinedFitEtaB;

TF1 *CombinedFitHighA;
TF1 *CombinedFitHighEtaA;
TF1 *CombinedFitLowA;
TF1 *CombinedFitLowEtaA;

TF1 *ConversionFitA;
TF1 *ConversionFitPionsStatLow;
TF1 *ConversionFitPionsStatHigh;
TF1 *ConversionFitPionsStatAverage;
TF1 *ConversionFitPionsCombinedStatLow;
TF1 *ConversionFitPionsCombinedStatHigh;
TF1 *ConversionFitPionsSystLow;
TF1 *ConversionFitPionsSystHigh;
TF1 *ConversionFitPionsSystAverage;
TF1 *ConversionFitPionsCombinedSystLow;
TF1 *ConversionFitPionsCombinedSystHigh;

TF1 *ConversionFitAWide;
TF1 *ConversionFitANarrow;
TF1 *ConversionFitB;
TF1 *ConversionFitEtaA;
TF1 *ConversionFitEtaB;
TF1 *ConversionFitC;
TF1 *ConversionFitPHOS;
TF1 *ConversionFitChargedKaons;
TF1 *ConversionFitNeutralKaons;
TF1 *ConversionFitNeutralKaonsUnscaled;

TF1 *ConversionGammaFitA;
TF1 *ConversionGammaFitB;

TH1D *histRatioNLOMuHalf;
TH1D *histRatioNLOMuOne;
TH1D *histRatioNLOMuTwo;

TH1D *histRatioConversionEtaA;
TH1D *histRatioConversionEtaB;
TH1D *histRatioConversionPi0A;
TH1D *histRatioConversionPi0AHighpt;
TH1D *histRatioConversionPi0B;
TH1D *histRatioConversionPi0C;
TH1D *histRatioConversionPi0Charged;
TH1D *histRatioConversionGammaA;
TH1D *histRatioConversionGammaB;

TGraphAsymmErrors* graphRatioCombinedEtaA;
TGraphAsymmErrors* graphRatioCombinedEtaB;
TGraphAsymmErrors* graphRatioCombinedPi0A;
TGraphAsymmErrors* graphRatioCombinedPi0B;
TGraphAsymmErrors* histoDirectPhotonNLORAA;

TH1D *histoTruePi0MCData;
TH1D *histoNormalPi0MCData;
TH1D *histoPurityGammaMCData;

TH1D *histoGammaSpecCorrPurity;
TH1D *histoGammaSpecLateCorr;
TH1D *histoGammaSpecMCAll;
TH1D *histoGammaSpecCorrESDMC;
TH1D *histoMCDecaySumGammaPt;
TH1D *histoMCDecayPi0GammaPt;
TH1D *histoMCDecayEtaGammaPt;
TH1D *histoMCDecayEtapGammaPt;
TH1D *histoMCDecayOmegaGammaPt;
TH1D *histoMCDecayRho0GammaPt;
TH1D *histoMCDecayK0sGammaPt;
TH1D *histoMCDecayPhiGammaPt;
TH1D *histoMCDecaySigmaGammaPt;
TH1D *histMCAllMinusDecay;
TH1D *histoCombinedPi0;
TH1D *histoConversionCombinedRatio;
TH1D *histoMCGammaConvProb;
TH1D *histoGammaPrimaryRecoEffMCPt;
TH1D *histoEventQuality;


TH1D *histoErrorGamma;
TH1D *histoErrorPi0;
TH1D *histoErrorIncRatio;
TH1D *histoErrorCocktailRatio;
TH1D *histoErrorDoubleRatio;

TH1D *histoCorrectedYieldNormalEff;
TH1D *histoCorrectedYieldTrueEff;
TH1D *histoCorrectedYieldTrueEffWide;
TH1D *histoCorrectedYieldTrueEffNarrow;
TH1D *histoMCYieldMeson;
TH1D *histoMCYieldMesonOldBin;
TH1D *histoCorrectedYieldTrueEffPi0Fit;
TH1D *histoCorrectedYieldTrueEffPi0FitWide;
TH1D *histoCorrectedYieldTrueEffPi0FitNarrow;

TH1D *histoIncRatioFitPurityA;
TH1D *histoIncRatioFitPurityB;
TH1D *histoIncRatioFitPurityC;
TH1D *histoIncRatioFitPurityPionsStatAverage;
TH1D *histoIncRatioFitPurityPHOS;
TH1D *histoIncRatioFitPurityWide;
TH1D *histoIncRatioFitPurityNarrow;
TH1D *histoIncRatioHighFitPurity;
TH1D *histoIncRatioLowFitPurity;
TH1D *histoIncRatioFitFit;
TH1D *histoIncRatioCombinedPurity;
TH1D *histoIncRatioPurity;
TH1D *histoIncRatioPurityTrueEff;
TH1D *histoIncRatioPurityTrueEffWide;
TH1D *histoIncRatioPurityTrueEffNarrow;

TH1D *histoChargedPionsSystAverage;
TH1D *histoChargedPionsStatAverage;

TH1D *histoMCIncRatio;
TH1D *histoMCesdIncRatio;
TH1D *histoIncRatioGammaMC;
TH1D *histoIncRatioPurityGammaData;

TH1D *histoDecayRatioSumGamma;
TH1D *histoDecayRatioPi0Gamma;
TH1D *histoDecayRatioEtaGamma;
TH1D *histoDecayRatioEtapGamma;
TH1D *histoDecayRatioOmegaGamma;
TH1D *histoDecayRatioRho0Gamma;
TH1D *histoDecayRatioK0sGamma;
TH1D *histoDecayRatioPhiGamma;
TH1D *histoDecayRatioSigmaGamma;

TFile *fileCorrectedOutput;

TH1D *cocktailAllGammaA;
TH1D *cocktailAllGammaB;
TH1D *cocktailAllGammaAB;
TH1D *cocktailAllGammaC;
TH1D *cocktailPi0Gamma;
TH1D *cocktailEtaGamma;
TH1D *cocktailEtapGamma;
TH1D *cocktailOmegaGamma;
TH1D *cocktailPhiGamma;
TH1D *cocktailRhoGamma;
TH1D *cocktailSigmaGamma;

TH1D *cocktailPi0A;
TH1D *cocktailPi0B;
TH1D *cocktailPi0C;
TH1D *cocktailEtaA;
TH1D *cocktailEtaB;
TH1D *cocktailEtaC;
TH1D *cocktailEtaLow;
TH1D *cocktailEtaHigh;
TH1D *cocktailEtaGammaLow;
TH1D *cocktailEtaGammaHigh;

TH1D *cocktailPi0;
TH1D *cocktailEta;
TH1D *cocktailOmega;
TH1D *cocktailEtap;
TH1D *cocktailPhi;
TH1D *cocktailSigma;
TH1D *cocktailEtaGammaPi0A;
TH1D *cocktailEtaGammaPi0B;
TH1D *cocktailEtaGammaPi0C;
TH1D *cocktailEtaGammaA;
TH1D *cocktailEtaGammaB;
TH1D *cocktailEtaGammaAB;
TH1D *cocktailEtaGammaC;
TH1D *cocktailPi0Pions;

TH1D *cocktailAllGammaPi0A;
TH1D *cocktailAllGammaPi0B;
TH1D *cocktailAllGammaPi0C;
TH1D *cocktailAllGammaPi0AB;
TH1D *cocktailAllGammaPi0Low;
TH1D *cocktailAllGammaPi0High;
TH1D *cocktailAllGammaPi0EtaLow;
TH1D *cocktailAllGammaPi0EtaHigh;
TH1D *cocktailAllGammaPi0ParamLow;
TH1D *cocktailAllGammaPi0ParamHigh;
TH1D *cocktailAllGammaPi0Hadrons;
TH1D *cocktailAllGammaPi0Pions;
TH1D *cocktailAllGammaPi0PHOS;
TH1D *cocktailAllGammaPi0Wide;
TH1D *cocktailAllGammaPi0Narrow;
TH1D *cocktailAllGammaPi0Syst;
TH1D *cocktailPi0GammaPi0;
TH1D *cocktailEtaGammaPi0;
TH1D *cocktailEtapGammaPi0;
TH1D *cocktailOmegaGammaPi0;
TH1D *cocktailPhiGammaPi0;
TH1D *cocktailRhoGammaPi0;
TH1D *cocktailSigmaGammaPi0;
TH1D *cocktailEta1;
TH1D *cocktailEta2;

TH1D *cocktailPi0Rebin;
TH1D *cocktailGammaPi0Rebin;

TH1D *histoDoubleRatioConversionNormalPurity;
TH1D *histoDoubleRatioConversionTrueEffPurityA;
TH1D *histoDoubleRatioConversionTrueEffPurityB;
TH1D *histoDoubleRatioConversionTrueEffPurityC;
TH1D *histoDoubleRatioConversionTrueEffPurityAB;
TH1D *histoDoubleRatioConversionTrueEffPurityLow;
TH1D *histoDoubleRatioConversionTrueEffPurityHigh;
TH1D *histoDoubleRatioConversionTrueEffPurityEtaLow;
TH1D *histoDoubleRatioConversionTrueEffPurityEtaHigh;
TH1D *histoDoubleRatioConversionTrueEffPurityPi0ParamLow;
TH1D *histoDoubleRatioConversionTrueEffPurityPi0ParamHigh;
TH1D *histoDoubleRatioConversionOnlyGamma;
TH1D *histoDoubleRatioConversionTrueEffPurityHadrons;
TH1D *histoDoubleRatioConversionTrueEffPurityPions;
TH1D *histoDoubleRatioConversionTrueEffPurityPHOS;
TH1D *histoDoubleRatioConversionTrueEffPurityWide;
TH1D *histoDoubleRatioConversionTrueEffPurityNarrow;
TH1D *histoDoubleRatioConversionTrueEffPuritySyst;

TH1D *histoDoubleRatioConversionFitPurityA;
TH1D *histoDoubleRatioConversionFitPurityB;
TH1D *histoDoubleRatioConversionFitPurityC;
TH1D *histoDoubleRatioConversionFitPurityAB;
TH1D *histoDoubleRatioConversionFitPurityLow;
TH1D *histoDoubleRatioConversionFitPurityHigh;
TH1D *histoDoubleRatioConversionFitPurityEtaLow;
TH1D *histoDoubleRatioConversionFitPurityEtaHigh;
TH1D *histoDoubleRatioConversionFitPurityPi0ParamLow;
TH1D *histoDoubleRatioConversionFitPurityPi0ParamHigh;
TH1D *histoDoubleRatioConversionFitPurityPionsLow;
TH1D *histoDoubleRatioConversionFitPurityPionsHigh;
TH1D *histoDoubleRatioConversionFitPurityPionsAverage;
TH1D *histoDoubleRatioConversionFitPurityPHOS;
TH1D *histoDoubleRatioConversionLowFitPurity;
TH1D *histoDoubleRatioConversionHighFitPurity;
TH1D *histoDoubleRatioConversionFitPurityWide;
TH1D *histoDoubleRatioConversionFitPurityNarrow;
TH1D *histoDoubleRatioConversionFitPuritySyst;
TH1D *histoDoubleRatioConversionFitFit;

TH1D *histoDoubleRatioCombinedPurity;
TH1D *histoMCDoubleRatioSum;
TH1D *histoMCesdDoubleRatioSum;

// Systematic Error Graphs
ifstream fileSysErrPi0;

TGraphAsymmErrors *graphCorrectedYieldPi0SysErr;
TGraphAsymmErrors *graphCorrectedYieldPi0SysErrA;

TDirectoryFile *cocktailHighError;
TDirectoryFile *cocktailLowError;

TF1 *FitRandomHigh;
TF1 *FitRandomLow;
TGraphErrors* combined7TeVRandomHighError;
TGraphErrors* combined7TeVRandomLowError;

TF1 *CombinedFitEtaRandomHighA;
TF1 *CombinedFitEtaRandomLowA;
TGraphErrors* combinedEta7TeVRandomHighError;
TGraphErrors* combinedEta7TeVRandomLowError;

TGraphErrors* combined7TeVHighError;
TGraphErrors* combined7TeVLowError;
TGraphErrors* combinedEta7TeVHighError;
TGraphErrors* combinedEta7TeVLowError;

TGraphAsymmErrors *AsymmCombined7TeVHighError;
TGraphAsymmErrors *AsymmCombined7TeVLowError;

TH1D *histcombined7TeVHighError;
TH1D *histcombined7TeVLowError;
TH1D *histcombined7TeVIncRatioHighError;
TH1D *histcombined7TeVIncRatioLowError;


TGraphAsymmErrors* graphAllGammaPi0SysError;
TH1D *HighErrorAllGammaPi0;
TH1D *LowErrorAllGammaPi0;


TH1D* histoChargedPionSpecHighPtStatPP;
TH1D* histoChargedPionSpecHighPtSystPP;
TH1D* histoChargedPionSpecHighPtStat0005;
TH1D* histoChargedPionSpecHighPtSyst0005;
TH1D* histoChargedPionSpecHighPtStat0510;
TH1D* histoChargedPionSpecHighPtSyst0510;
TH1D* histoChargedPionSpecHighPtStat1020;
TH1D* histoChargedPionSpecHighPtSyst1020;
TH1D* histoChargedPionSpecHighPtSyst2040;
TH1D* histoChargedPionSpecHighPtStat2040;
TH1D* histoChargedPionSpecHighPtSyst4060;
TH1D* histoChargedPionSpecHighPtStat4060;
TH1D* histoChargedPionSpecHighPtSyst6080;
TH1D* histoChargedPionSpecHighPtStat6080;
TH1D *PionSummedStatHigh;
TH1D *PionSummedSystHigh;


TH1D *KaonsLowPt;
TH1D *KaonsHighPt;
TH1D *CombinedKaons;
TH1D *Kaon0s;


TH1D *CombinedKaonsRatioToFit;
TH1D *NeutralKaonsRatioToFit;
TH1D *NeutralKaonsRatioToFitAfterScaling;
TH1D *NeutralKaonsCocktailRatioToFitAfterScaling;
TH1D *CombinedKaonsCocktailRatioToFit;
TH1D *NeutralKaonsCocktailRatioToFit;

TH1D* histoChargedPionSpecLowPtStatPP2760GeV;
TH1D* histoChargedPionSpecLowPtSysPP2760GeV;
TH1D* histoChargedPionSpecLowPtStat0005;
TH1D* histoChargedPionSpecLowPtSyst0005;
TH1D* histoChargedPionSpecLowPtStat0510;
TH1D* histoChargedPionSpecLowPtSyst0510;
TH1D* histoChargedPionSpecLowPtStat1020;
TH1D* histoChargedPionSpecLowPtSyst1020;
TH1D* histoChargedPionSpecLowPtStat2040;
TH1D* histoChargedPionSpecLowPtSyst2040;
TH1D* histoChargedPionSpecLowPtStat4060;
TH1D* histoChargedPionSpecLowPtSyst4060;
TH1D* histoChargedPionSpecLowPtStat6080;
TH1D* histoChargedPionSpecLowPtSyst6080;
TH1D *PionSummedStatLow;
TH1D *PionSummedSystLow;

TH1D *CombinedChargedPionsStatHigh;
TH1D *CombinedChargedPionsStatLow;
TH1D *CombinedChargedPionsSystHigh;
TH1D *CombinedChargedPionsSystLow;
TH1D *CombinedChargedPionsStatAverage;
TH1D *CombinedChargedPionsSystAverage;
TH1D *CombinedChargedPionsAverageScaled;


void FindCocktailFile(TString cutSelection, TString centrality, TString option){
   
   fcmult = 1;
   
   ffive = kFALSE;
   
   TString centralityCutNumberLow = cutSelection(GetEventCentralityMinCutPosition(),1);
   TString centralityCutNumberHigh = cutSelection(GetEventCentralityMaxCutPosition(),1);
   Int_t centCutNumberI  = centralityCutNumberLow.Atoi();
   Int_t centCutNumberBI = centralityCutNumberHigh.Atoi();

   if(!option.CompareTo("PbPb_2.76TeV")){    
      if(!centrality.CompareTo("0-5%")){
         fcocktailFuncA = "cocktail_PbPb_0005_rad";
         fcocktailFuncB = "cocktail_PbPb_0005_rad";
         fcocktailFuncC = "cocktail_PbPb_0005_rad";
         fcocktailFuncSyst = "cocktail_PbPb_0005_rad";
         fcocktailFuncNarrow = "cocktail_PbPb_0005_rad";
         fcocktailFuncWide = "cocktail_PbPb_0005_rad";
         fcocktailFuncPions =  "cocktail_PbPb_0005_rad";
         fcocktailFuncPHOS = "cocktail_PbPb_0005_rad";
         ffive = kTRUE;
      }
      if(!centrality.CompareTo("5-10%")){
         fcocktailFuncA = "cocktail_PbPb_0510_rad";
         fcocktailFuncB = "cocktail_PbPb_0510_rad_KaonsPosXiango";
         fcocktailFuncC = "cocktail_PbPb_0510_rad";
         fcocktailFuncSyst = "cocktail_PbPb_0510_rad";
         fcocktailFuncNarrow = "cocktail_PbPb_0510_rad";
         fcocktailFuncWide = "cocktail_PbPb_0510_rad";
         fcocktailFuncPions =  "cocktail_PbPb_0510_chargedPions_xqcd";
         fcocktailFuncPHOS = "cocktail_PbPb_0510_rad";
         ffive = kTRUE;
      }
      if(!centrality.CompareTo("0-10%")){
         fcocktailFuncA = "cocktail_PbPb_0010c_dmtsallis_ratioEta";
         fcocktailFuncB = "cocktail_PbPb_0010_dmtsallis_mTEta";
         fcocktailFuncC = "cocktail_PbPb_0010_dmtsallis_mTEta";
         fcocktailFuncSyst = "cocktail_PbPb_0010_dmtsallis_mTEta";
         fcocktailFuncNarrow = "cocktail_PbPb_0010_dmtsallis_mTEta";
         fcocktailFuncWide = "cocktail_PbPb_0010_charged_qcd_tmK0s";
         fcocktailFuncPions =  "cocktail_PbPb_0010_charged_dmtsallis_mTEta";
         fcocktailFuncPHOS = "cocktail_PbPb_0010_dmtsallis_mTEta";
      }
      if(!centrality.CompareTo("10-20%")){
         fcocktailFuncA = "cocktail_PbPb_1020c_dmtsallis_ratioEta";
         fcocktailFuncB = "cocktail_PbPb_1020c_dmtsallis_mTEta";
         fcocktailFuncC = "cocktail_PbPb_1020c_dmtsallis_mTEta";
         fcocktailFuncSyst = "cocktail_PbPb_1020c_dmtsallis_mTEta";
         fcocktailFuncNarrow = "cocktail_PbPb_1020c_dmtsallis_mTEta";
         fcocktailFuncWide = "cocktail_PbPb_1020c_dmtsallis_mTEta";
         fcocktailFuncPions =  "cocktail_PbPb_1020_charged_dmtsallis_mTEta";
         fcocktailFuncPHOS = "cocktail_PbPb_1020c_dmtsallis_mTEta";
      }
      if(!centrality.CompareTo("0-40%")){
         fcocktailFuncA = "cocktail_PbPb_0040c_dmtsallis_RatioEta";
         fcocktailFuncB = "cocktail_PbPb_0040c_dmtsallis_MTEta";
         //fcocktailFuncB = "cocktail_PbPb_0040c_dmtsallis_mTEta";
         fcocktailFuncC = "cocktail_PbPb_0040c_dmtsallis_mTEta";
         fcocktailFuncSyst = "cocktail_PbPb_0040c_dmtsallis_mTEta";
         fcocktailFuncNarrow = "cocktail_PbPb_0040c_dmtsallis_mTEta";
         fcocktailFuncWide = "cocktail_PbPb_0040c_dmtsallis_mTEta";
         fcocktailFuncPions =  "cocktail_PbPb_0040_charged_dmtsallis_mTEta";
         fcocktailFuncPHOS = "cocktail_PbPb_0040c_dmtsallis_mTEta";
      }
      if(!centrality.CompareTo("0-20%")){
         fcocktailFuncA = "cocktail_PbPb_0020c_dmtsallis_RatioEta";//cocktail_PbPb_0020c_dmtsallis_RatioEta";
         //fcocktailFuncB = "cocktail_PbPb_0020c_dmtsallis_RatioEta";
         fcocktailFuncB = "cocktail_PbPb_0020c_dmtsallis_mtEta";//cocktail_PbPb_0020c_dmtsallis_MTEta";
         fcocktailFuncC = "cocktail_PbPb_0020c_dmtsallis_RatioEta";
         fcocktailFuncSyst = "cocktail_PbPb_0020c_dmtsallis_mTEta";
         fcocktailFuncNarrow = "cocktail_PbPb_0020c_dmtsallis_mTEta";
         fcocktailFuncWide = "cocktail_PbPb_0020c_dmtsallis_mTEta";
         fcocktailFuncPions =  "cocktail_PbPb_0020_charged_dmtsallis_mTEta";
         fcocktailFuncPHOS = "cocktail_PbPb_0020c_dmtsallis_mTEta";
      }
      if(!centrality.CompareTo("20-40%")){
         fcocktailFuncA = "cocktail_PbPb_2040c_dmtsallis_RatioEta";
         fcocktailFuncB = "cocktail_PbPb_2040c_dmtsallis_MTEta";
         fcocktailFuncC = "cocktail_PbPb_2040c_dmtsallis_MTEta";
         fcocktailFuncNarrow = "cocktail_PbPb_2040c_dmtsallis_mTEta";
         fcocktailFuncWide =   "cocktail_PbPb_2040c_dmtsallis_mTEta";
         fcocktailFuncSyst = "cocktail_PbPb_2040c_dmtsallis_mTEta";
         fcocktailFuncPions =  "cocktail_PbPb_2040_charged_dmtsallis_mTEta";
         fcocktailFuncPHOS = "cocktail_PbPb_2040c_dmtsallis_mTEta";
      }
      if(!centrality.CompareTo("40-80%")){
         fcocktailFuncA = "cocktail_PbPb_4080c_dmtsallis_RatioEta";
         fcocktailFuncB = "cocktail_PbPb_4080c_dmtsallis_MTEta";
         fcocktailFuncC = "cocktail_PbPb_4080c_dmtsallis_MTEta";
         fcocktailFuncNarrow = "cocktail_PbPb_4080c_dmtsallis_mTEta";
         fcocktailFuncWide =   "cocktail_PbPb_4080c_dmtsallis_mTEta";
         fcocktailFuncSyst = "cocktail_PbPb_4080c_dmtsallis_mTEta";
         fcocktailFuncPions =  "cocktail_PbPb_4080_charged_dmtsallis_mTEta";
         fcocktailFuncPHOS = "cocktail_PbPb_4080c_dmtsallis_mTEta";
      }
      if(!centrality.CompareTo("60-80%")){
         fcocktailFuncA = "cocktail_Pb-Pb_4080_qcd";
         fcocktailFuncB = "cocktail_Pb-Pb_4080_qcd";
         fcocktailFuncC = "cocktail_Pb-Pb_4080_qcd";
         fcocktailFuncNarrow = "cocktail_Pb-Pb_4080_qcd";
         fcocktailFuncWide =   "cocktail_Pb-Pb_4080_qcd";
         fcocktailFuncSyst = "cocktail_Pb-Pb_4080_qcd";
         fcocktailFuncPions =  "cocktail_PbPb_4080_chargedPions_qcd";
         fcocktailFuncPHOS = "cocktail_PbPb_00-10_PHOS_qcd";
      }
      if(!centrality.CompareTo("40-60%")){
         fcocktailFuncNarrow = "cocktail_HI_40-80_oHag";
         fcocktailFuncWide =   "cocktail_HI_40-80_oHag";
         fcocktailFuncSyst = "cocktail_HI_40-80_oHag";
         fcocktailFuncPions =  "cocktail_HI_40-80_oHag";
      }
      if(!centrality.CompareTo("0-80%")){
         fcocktailFuncA = "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncB = "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncC = "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncNarrow = "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncWide =   "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncSyst = "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncPions =  "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
      }
      if(!centrality.CompareTo("0-90%")){
         fcocktailFuncA = "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncB = "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncC = "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncNarrow = "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncWide =   "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncSyst = "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
         fcocktailFuncPions =  "cocktail_HI_0080_qcd";//cocktail_40-80_QCD_Neu_pp";
      }
   
      fcmult = 0;
      for(Int_t i = centCutNumberI; i<centCutNumberBI;i++){
         if(ffive){
            fcmult += multiplicityCent[i];
            cout<<multiplicityCent[i]<<endl;
         }
         else{
            fcmult += multiplicity[i];
            cout<<multiplicity[i]<<endl;
         }
         cout<<" Sum:"<<fcmult<<endl;
      }
      cout<<" / "<<centCutNumberBI-centCutNumberI<<"  =  "<<endl;
      fcmult = fcmult/(centCutNumberBI-centCutNumberI);
      cout<<fcmult<<endl;
   }
   else if(!option.CompareTo("7TeV")){    
      fcocktailFuncNarrow = "cocktail_7TeV_pi0LevyetaLevy";
      fcocktailFuncWide =   "cocktail_7TeV_pi0LevyetaLevy";
      fcocktailFuncSyst = "cocktail_7TeV_pi0LevyetaLevy";
      //fcocktailFunc = "cocktail_7TeV_pi0LevyetaLevy";
      //fcocktailFunc = "cocktail_pp7TeV_HagLevy";
      //fcocktailFunc = "cocktail_pp7TeV_HagHag";;
      //fcocktailFunc = "cocktail_pp7TeV_oHagHag";
      fcocktailFuncA = "cocktail_pp7TeV_TsallisTsallis";
      fcocktailFuncB = "cocktail_pp7TeV_TsallisTsallis";
      fcocktailFuncC = "cocktail_pp7TeV_TsallisTsallis";
      //fcocktailFunc = "cocktail_pp7TeV_QCDTsallis";
      //fcocktailFunc = "cocktail_7TeV_pi0LevyetaLevy";
      //fcocktailFunc = "cocktail_pp7TeV_qcdqcd";
      fcocktailFuncPions = "cocktail_276TeV";
   }
   else if(!option.CompareTo("2.76TeV")){
      fcocktailFuncA = "cocktail_pp_2760GeVc_ratioEta";//cocktail_pp_2760GeVc_mTEta";
      fcocktailFuncB = "cocktail_pp_2760GeVc_ratioEta";//cocktail_pp_2760GeVc_mTEta";
      fcocktailFuncC = "cocktail_pp_2760GeVc_mTEta";
      fcocktailFuncSyst = "cocktail_pp_2760GeVc_mTEta";
      fcocktailFuncNarrow = "cocktail_pp_2760GeVc_mTEta";
      fcocktailFuncWide = "cocktail_pp_2760GeVc_mTEta";
      fcocktailFuncPions =  "cocktail_pp_2760GeVc_ratioEta";//cocktail_pp_2760GeVc_mTEta";
      fcocktailFuncPHOS = "cocktail_pp_2760GeVc_mTEta";


      /* fcocktailFuncNarrow = "cocktail_pp_2760_Levy"; */
      /* fcocktailFuncWide =   "cocktail_pp_2760_Levy"; */
      /* fcocktailFuncSyst = "cocktail_pp_2760_Levy"; */
      /* fcocktailFuncA = "cocktail_pp_2760_Levy"; */
      /* fcocktailFuncB = "cocktail_pp_2760_Levy"; */
      /* fcocktailFuncC = "cocktail_pp_2760_Levy"; */
      /* fcocktailFuncPions = "cocktail_pp_2760_Levy"; */
      /* fcocktailFuncPHOS = "cocktail_pp_2760_Levy"; */
   }
   else if(!option.CompareTo("900GeV")){
      fcocktailFuncNarrow = "cocktail_pp2760GeV_oHagmt";
      fcocktailFuncWide =   "cocktail_pp2760GeV_oHagmt";
      fcocktailFuncSyst = "cocktail_pp2760GeV_oHagmt";
      fcocktailFuncA = "cocktail_pp900GeV_oHag";//cocktail_pp900GeV_Iqcd";
      fcocktailFuncB = "cocktail_pp900GeV_oHag";//cocktail_pp900GeV_Iqcd";
      fcocktailFuncC = "cocktail_pp900GeV_oHag";//cocktail_pp900GeV_Iqcd";
      fcocktailFuncPions = "cocktail_pp2760GeV_oHagmt";
   }
   else {
      fcocktailFuncNarrow = "cocktail_Test";
      fcocktailFuncWide =   "cocktail_Test";
      fcocktailFuncSyst = "cocktail_Test";
      fcocktailFuncA = "cocktail_Test";
      fcocktailFuncB = "cocktail_Test";
      fcocktailFuncC = "cocktail_Test";
      fcocktailFuncPions =  "cocktail_Test";
   }

   //return 0;

}


void GetKaonsPbPb(TFile *file, TString cutSel){   

   
   KaonsLowPt = (TH1D*)(file->Get("histoChargedKaonSpecLowPtStat0005"))->Clone();
   KaonsHighPt = (TH1D*)(file->Get("histoChargedKaonSpecHighPtStat0005"))->Clone();
   Kaon0s = (TH1D*)(file->Get("histoNeutralKaonSpecStat0005"))->Clone();

   KaonsLowPt->Reset();
   KaonsHighPt->Reset();
   Kaon0s->Reset();

   TString centralityCutNumberLow = cutSel(GetEventCentralityMinCutPosition(),1);
   TString centralityCutNumberHigh = cutSel(GetEventCentralityMaxCutPosition(),1);
   Int_t centCutNumberI  = centralityCutNumberLow.Atoi();
   Int_t centCutNumberBI = centralityCutNumberHigh.Atoi();
   
   
   Double_t scale = 0;

   if(!ffive && centCutNumberI<1 && centCutNumberBI>0){ // 0-10%
      KaonsLowPt->Add((TH1D*)file->Get("histoChargedKaonSpecLowPtStat0010"),2);
      KaonsHighPt->Add((TH1D*)file->Get("histoChargedKaonSpecHighPtStat0010"),2);
      Kaon0s->Add((TH1D*)file->Get("histoNeutralKaonSpecStat0010"),2);
      scale=scale+2;
   }
   if(ffive && centCutNumberI<1 && centCutNumberBI>0){
      KaonsLowPt->Add((TH1D*)file->Get("histoChargedKaonSpecLowPtStat0005"));
      KaonsHighPt ->Add((TH1D*)file->Get("histoChargedKaonSpecHighPtStat0005"));
      Kaon0s->Add((TH1D*)file->Get("histoNeutralKaonSpecStat0005"));
      scale=scale+1;
   }
   if(ffive && centCutNumberI<2 && centCutNumberBI>1){
      KaonsLowPt->Add((TH1D*)file->Get("histoChargedKaonSpecLowPtStat0510"));
      KaonsHighPt ->Add((TH1D*)file->Get("histoChargedKaonSpecHighPtStat0510"));
      Kaon0s->Add((TH1D*)file->Get("histoNeutralKaonSpecStat0510"));
      scale=scale+1;
   }
   if(!ffive && centCutNumberI<2 && centCutNumberBI>1){
      KaonsLowPt->Add((TH1D*)file->Get("histoChargedKaonSpecLowPtStat1020"),2);
      KaonsHighPt->Add((TH1D*)file->Get("histoChargedKaonSpecHighPtStat1020"),2);
      Kaon0s->Add((TH1D*)file->Get("histoNeutralKaonSpecStat1020"),2);
      scale=scale+2;
   }
   if(!ffive && centCutNumberI<4 && centCutNumberBI>2){
      KaonsLowPt->Add((TH1D*)file->Get("histoChargedKaonSpecLowPtStat2040"),4);
      KaonsHighPt->Add((TH1D*)file->Get("histoChargedKaonSpecHighPtStat2040"),4);
      Kaon0s->Add((TH1D*)file->Get("histoNeutralKaonSpecStat2040"),4);
      scale=scale+4;
   }
   if(!ffive && centCutNumberI<6 && centCutNumberBI>4){
      KaonsLowPt->Add((TH1D*)file->Get("histoChargedKaonSpecLowPtStat4060"),4);
      KaonsHighPt->Add((TH1D*)file->Get("histoChargedKaonSpecHighPtStat4060"),4);
      Kaon0s->Add((TH1D*)file->Get("histoNeutralKaonSpecStat4060"),4);
      scale=scale+4;
   }
   if(!ffive && centCutNumberI<8 && centCutNumberBI>6){
      KaonsLowPt->Add((TH1D*)file->Get("histoChargedKaonSpecLowPtStat6080"),4);
      KaonsHighPt->Add((TH1D*)file->Get("histoChargedKaonSpecHighPtStat6080"),4);
      Kaon0s->Add((TH1D*)file->Get("histoNeutralKaonSpecStat6080"),4);
      scale=scale+4;
   }

   KaonsLowPt->Scale(1./scale);
   KaonsHighPt->Scale(1./scale);
   Kaon0s->Scale(1./scale);
   
   Double_t binningKaons[] = {0.05, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.2, 3.4, 3.6, 3.8, 4, 4.5, 5, 5.5, 6, 6.5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 40};
   
   CombinedKaons = new TH1D("CombinedKaons","",60,binningKaons);
   for(Int_t i = 0;i<CombinedKaons->GetNbinsX();i++){
      if(CombinedKaons->GetBinCenter(i)<3){
         CombinedKaons->SetBinContent(i,KaonsLowPt->GetBinContent(KaonsLowPt->FindBin(CombinedKaons->GetBinCenter(i))));
         CombinedKaons->SetBinError(i,KaonsLowPt->GetBinError(KaonsLowPt->FindBin(CombinedKaons->GetBinCenter(i))));
      }
      else{
         CombinedKaons->SetBinContent(i,KaonsHighPt->GetBinContent(KaonsHighPt->FindBin(CombinedKaons->GetBinCenter(i))));
         CombinedKaons->SetBinError(i,KaonsHighPt->GetBinError(KaonsHighPt->FindBin(CombinedKaons->GetBinCenter(i))));
      }
   }
   
}

void GetChargedPionsPbPb(TFile *file, TString cutSel){   

   
   PionSummedStatHigh = new TH1D();
   PionSummedStatLow = new TH1D();
   PionSummedStatHigh = (TH1D*)(file->Get("histoChargedPionSpecHighPtSyst0005"))->Clone();
   PionSummedStatLow = (TH1D*)(file->Get("histoChargedPionSpecLowPtSyst0005"))->Clone();
   PionSummedSystHigh = (TH1D*)(file->Get("histoChargedPionSpecHighPtSyst0005"))->Clone();
   PionSummedSystLow = (TH1D*)(file->Get("histoChargedPionSpecLowPtSyst0005"))->Clone();

   PionSummedStatHigh->Reset();
   PionSummedStatLow->Reset();
   PionSummedSystHigh->Reset();
   PionSummedSystLow->Reset();

   TString centralityCutNumberLow = cutSel(GetEventCentralityMinCutPosition(),1);
   TString centralityCutNumberHigh = cutSel(GetEventCentralityMaxCutPosition(),1);
   Int_t centCutNumberI  = centralityCutNumberLow.Atoi();
   Int_t centCutNumberBI = centralityCutNumberHigh.Atoi();
   
   TH1D *ChargedSystLow = NULL;
   TH1D *ChargedSystHigh = NULL;

   Double_t scale = 0;

   if(!ffive && centCutNumberI<1 && centCutNumberBI>0){
      if(!ChargedSystLow)ChargedSystLow = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst0005");
      if(!ChargedSystHigh)ChargedSystHigh = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst0005");
      
      histoChargedPionSpecHighPtStat0005 = (TH1D*)file->Get("histoChargedPionSpecHighPtStat0005");
      PionSummedStatHigh->Add(histoChargedPionSpecHighPtStat0005);
      histoChargedPionSpecHighPtSyst0005 = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst0005");
      PionSummedSystHigh->Add(histoChargedPionSpecHighPtSyst0005);
      
      histoChargedPionSpecLowPtStat0005 = (TH1D*)file->Get("histoChargedPionSpecLowPtStat0005");
      PionSummedStatLow->Add(histoChargedPionSpecLowPtStat0005);
      histoChargedPionSpecLowPtSyst0005 = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst0005");
      PionSummedSystLow->Add(histoChargedPionSpecLowPtSyst0005);
      
      scale=scale+1;
   }
   if(!ffive && centCutNumberI<1 && centCutNumberBI>0){
      if(!ChargedSystLow)ChargedSystLow = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst0510");
      if(!ChargedSystHigh)ChargedSystHigh = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst0510");

      histoChargedPionSpecHighPtStat0510 = (TH1D*)file->Get("histoChargedPionSpecHighPtStat0510");
      PionSummedStatHigh->Add(histoChargedPionSpecHighPtStat0510);
      histoChargedPionSpecHighPtSyst0510 = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst0510");
      PionSummedSystHigh->Add(histoChargedPionSpecHighPtSyst0510);

      histoChargedPionSpecLowPtStat0510 = (TH1D*)file->Get("histoChargedPionSpecLowPtStat0510");
      PionSummedStatLow->Add(histoChargedPionSpecLowPtStat0510);
      histoChargedPionSpecLowPtSyst0510 = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst0510");
      PionSummedSystLow->Add(histoChargedPionSpecLowPtSyst0510);

      scale=scale+1;
   }
   if(ffive && centCutNumberI<1 && centCutNumberBI>0){
      if(!ChargedSystLow)ChargedSystLow = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst0005");
      if(!ChargedSystHigh)ChargedSystHigh = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst0005");

      histoChargedPionSpecHighPtStat0005 = (TH1D*)file->Get("histoChargedPionSpecHighPtStat0005");
      PionSummedStatHigh->Add(histoChargedPionSpecHighPtStat0005);
      histoChargedPionSpecHighPtSyst0005 = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst0005");
      PionSummedSystHigh->Add(histoChargedPionSpecHighPtSyst0005);

      histoChargedPionSpecLowPtStat0005 = (TH1D*)file->Get("histoChargedPionSpecLowPtStat0005");
      PionSummedStatLow->Add(histoChargedPionSpecLowPtStat0005);
      histoChargedPionSpecLowPtSyst0005 = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst0005");
      PionSummedSystLow->Add(histoChargedPionSpecLowPtSyst0005);

      scale=scale+1;
   }
   if(ffive && centCutNumberI<2 && centCutNumberBI>1){
      if(!ChargedSystLow)ChargedSystLow = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst0510");
      if(!ChargedSystHigh)ChargedSystHigh = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst0510");

      histoChargedPionSpecHighPtStat0510 = (TH1D*)file->Get("histoChargedPionSpecHighPtStat0510");
      PionSummedStatHigh->Add(histoChargedPionSpecHighPtStat0510);
      histoChargedPionSpecHighPtSyst0510 = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst0510");
      PionSummedSystHigh->Add(histoChargedPionSpecHighPtSyst0510);

      histoChargedPionSpecLowPtStat0510 = (TH1D*)file->Get("histoChargedPionSpecLowPtStat0510");
      PionSummedStatLow->Add(histoChargedPionSpecLowPtStat0510);
      histoChargedPionSpecLowPtSyst0510 = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst0510");
      PionSummedSystLow->Add(histoChargedPionSpecLowPtSyst0510);

      scale=scale+1;
   }
   if(!ffive && centCutNumberI<2 && centCutNumberBI>1){
      if(!ChargedSystLow)ChargedSystLow = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst1020");
      if(!ChargedSystHigh)ChargedSystHigh = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst1020");

      histoChargedPionSpecHighPtStat1020 = (TH1D*)file->Get("histoChargedPionSpecHighPtStat1020");
      PionSummedStatHigh->Add(histoChargedPionSpecHighPtStat1020,2);
      histoChargedPionSpecHighPtSyst1020 = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst1020");
      PionSummedSystHigh->Add(histoChargedPionSpecHighPtSyst1020,2);

      histoChargedPionSpecLowPtStat1020 = (TH1D*)file->Get("histoChargedPionSpecLowPtStat1020");
      PionSummedStatLow->Add(histoChargedPionSpecLowPtStat1020,2);
      histoChargedPionSpecLowPtSyst1020 = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst1020");
      PionSummedSystLow->Add(histoChargedPionSpecLowPtSyst1020,2);

      scale=scale+2;
   }
   if(!ffive && centCutNumberI<4 && centCutNumberBI>2){
      if(!ChargedSystLow)ChargedSystLow = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst2040");
      if(!ChargedSystHigh)ChargedSystHigh = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst2040");

      histoChargedPionSpecHighPtStat2040 = (TH1D*)file->Get("histoChargedPionSpecHighPtStat2040");
      PionSummedStatHigh->Add(histoChargedPionSpecHighPtStat2040,4);
      histoChargedPionSpecHighPtSyst2040 = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst2040");
      PionSummedSystHigh->Add(histoChargedPionSpecHighPtSyst2040,4);

      histoChargedPionSpecLowPtStat2040 = (TH1D*)file->Get("histoChargedPionSpecLowPtStat2040");
      PionSummedStatLow->Add(histoChargedPionSpecLowPtStat2040,4);
      histoChargedPionSpecLowPtSyst2040 = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst2040");
      PionSummedSystLow->Add(histoChargedPionSpecLowPtSyst2040,4);

      scale=scale+4;
   }
   if(!ffive && centCutNumberI<6 && centCutNumberBI>4){
      if(!ChargedSystLow)ChargedSystLow = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst4060");
      if(!ChargedSystHigh)ChargedSystHigh = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst4060");

      histoChargedPionSpecHighPtStat4060 = (TH1D*)file->Get("histoChargedPionSpecHighPtStat4060");
      PionSummedStatHigh->Add(histoChargedPionSpecHighPtStat4060,4);
      histoChargedPionSpecHighPtSyst4060 = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst4060");
      PionSummedSystHigh->Add(histoChargedPionSpecHighPtSyst4060,4);
      
      histoChargedPionSpecLowPtStat4060 = (TH1D*)file->Get("histoChargedPionSpecLowPtStat4060");
      PionSummedStatLow->Add(histoChargedPionSpecLowPtStat4060,4);
      histoChargedPionSpecLowPtSyst4060 = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst4060");
      PionSummedSystLow->Add(histoChargedPionSpecLowPtSyst4060,4);
      
      scale=scale+4;
   }
   if(!ffive && centCutNumberI<8 && centCutNumberBI>6){
      if(!ChargedSystLow)ChargedSystLow = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst6080");
      if(!ChargedSystHigh)ChargedSystHigh = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst6080");

      histoChargedPionSpecHighPtStat6080 = (TH1D*)file->Get("histoChargedPionSpecHighPtStat6080");
      PionSummedStatHigh->Add(histoChargedPionSpecHighPtStat6080,4);
      histoChargedPionSpecHighPtSyst6080 = (TH1D*)file->Get("histoChargedPionSpecHighPtSyst6080");
      PionSummedSystHigh->Add(histoChargedPionSpecHighPtSyst6080,4);
      
      histoChargedPionSpecLowPtStat6080 = (TH1D*)file->Get("histoChargedPionSpecLowPtStat6080");
      PionSummedStatLow->Add(histoChargedPionSpecLowPtStat6080,4);
      histoChargedPionSpecLowPtSyst6080 = (TH1D*)file->Get("histoChargedPionSpecLowPtSyst6080");
      PionSummedSystLow->Add(histoChargedPionSpecLowPtSyst6080,4);
      
      scale=scale+4;
   }

      PionSummedStatHigh->Scale(1./scale);
      PionSummedSystHigh->Scale(1./scale);
      
      PionSummedStatLow->Scale(1./scale);
      PionSummedSystLow->Scale(1./scale);

      for(Int_t i=0;i<PionSummedSystHigh->GetNbinsX();i++){
         if(ChargedSystHigh->GetBinError(i+1)>0 && ChargedSystHigh->GetBinContent(i+1)>0){
            Double_t systErr = ChargedSystHigh->GetBinError(i+1)/ChargedSystHigh->GetBinContent(i+1);
            PionSummedSystHigh->SetBinError(i+1,PionSummedSystHigh->GetBinContent(i+1)*systErr);
         }
         else PionSummedSystHigh->SetBinError(i+1,0);
         
      }
      for(Int_t i=0;i<PionSummedSystLow->GetNbinsX();i++){
         if(ChargedSystLow->GetBinError(i+1)>0 && ChargedSystLow->GetBinContent(i+1)>0){
            Double_t systErr = ChargedSystLow->GetBinError(i+1)/ChargedSystLow->GetBinContent(i+1);
            PionSummedSystLow->SetBinError(i+1,PionSummedSystLow->GetBinContent(i+1)*systErr);
         }
         else PionSummedSystLow->SetBinError(i+1,0);
      }

      

}

void CombineChargedPions(){   

   Double_t combinedbinningHigh[70] = {0.05,0.1,0.12,0.14,0.16,0.18,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.2,2.4,2.6,2.8,3,3.2,3.4,3.6,3.8,4,4.5,5,5.5,6,6.5,7,8,9,10,11,12,13,14,15,16,18,20,22,24,26,28,30,32,34,36,40,45};
   Double_t combinedbinningLow[75] = {0.05,0.1,0.12,0.14,0.16,0.18,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3,3.2,3.4,3.6,3.8,4,4.5,5,5.5,6,6.5,7,8,9,10,11,12,13,14,15,16,18,20,22,24,26,28,30,32,34,36,40,45};

   CombinedChargedPionsStatHigh = new TH1D("CombinedChargedPionsHigh_stat","",69,combinedbinningHigh);
   CombinedChargedPionsStatLow = new TH1D("CombinedChargedPionsLow_stat","",74,combinedbinningLow);
   CombinedChargedPionsSystHigh = new TH1D("CombinedChargedPionsHigh_syst","",69,combinedbinningHigh);
   CombinedChargedPionsSystLow = new TH1D("CombinedChargedPionsLow_syst","",74,combinedbinningLow);

   
   for(Int_t i = 0; i<70; i++){
      for(Int_t j = 0;j<PionSummedStatLow->GetNbinsX();j++){
         if((CombinedChargedPionsStatHigh->GetBinCenter(i+1) == PionSummedStatLow->GetBinCenter(j+1)) && 
            (CombinedChargedPionsStatHigh->GetBinWidth(i+1) == PionSummedStatLow->GetBinWidth(j+1)) && 
            PionSummedStatLow->GetBinCenter(j+1)<2){
            CombinedChargedPionsStatHigh->SetBinContent(i+1,PionSummedStatLow->GetBinContent(j+1));
            CombinedChargedPionsStatHigh->SetBinError(i+1,PionSummedStatLow->GetBinError(j+1));
            CombinedChargedPionsSystHigh->SetBinContent(i+1,PionSummedSystLow->GetBinContent(j+1));
            CombinedChargedPionsSystHigh->SetBinError(i+1,PionSummedSystLow->GetBinError(j+1));
            break;
         }
      }
      for(Int_t j = 0;j<PionSummedStatHigh->GetNbinsX();j++){
         if(CombinedChargedPionsStatHigh->GetBinCenter(i+1) == PionSummedStatHigh->GetBinCenter(j+1) && 
            CombinedChargedPionsStatHigh->GetBinWidth(i+1) == PionSummedStatHigh->GetBinWidth(j+1) && 
            PionSummedStatHigh->GetBinCenter(j+1)>2){
            CombinedChargedPionsStatHigh->SetBinContent(i+1,PionSummedStatHigh->GetBinContent(j+1));
            CombinedChargedPionsStatHigh->SetBinError(i+1,PionSummedStatHigh->GetBinError(j+1));
            CombinedChargedPionsSystHigh->SetBinContent(i+1,PionSummedSystHigh->GetBinContent(j+1));
            CombinedChargedPionsSystHigh->SetBinError(i+1,PionSummedSystHigh->GetBinError(j+1));
            break;
         }
      }
   }
   
   for(Int_t i = 0; i<75; i++){
      for(Int_t j = 0;j<PionSummedStatLow->GetNbinsX();j++){
         if((CombinedChargedPionsStatLow->GetBinCenter(i+1) == PionSummedStatLow->GetBinCenter(j+1)) && 
            (CombinedChargedPionsStatLow->GetBinWidth(i+1) == PionSummedStatLow->GetBinWidth(j+1)) &&
            PionSummedStatLow->GetBinCenter(j+1)<3){
            CombinedChargedPionsStatLow->SetBinContent(i+1,PionSummedStatLow->GetBinContent(j+1));
            CombinedChargedPionsStatLow->SetBinError(i+1,PionSummedStatLow->GetBinError(j+1));
            CombinedChargedPionsSystLow->SetBinContent(i+1,PionSummedSystLow->GetBinContent(j+1));
            CombinedChargedPionsSystLow->SetBinError(i+1,PionSummedSystLow->GetBinError(j+1));
            break;
         }
      }
      for(Int_t j = 0;j<PionSummedStatHigh->GetNbinsX();j++){
         if(CombinedChargedPionsStatLow->GetBinCenter(i+1) == PionSummedStatHigh->GetBinCenter(j+1) && 
            CombinedChargedPionsStatLow->GetBinWidth(i+1) == PionSummedStatHigh->GetBinWidth(j+1) && 
            PionSummedStatHigh->GetBinCenter(j+1)>3){
            CombinedChargedPionsStatLow->SetBinContent(i+1,PionSummedStatHigh->GetBinContent(j+1));
            CombinedChargedPionsStatLow->SetBinError(i+1,PionSummedStatHigh->GetBinError(j+1));
            CombinedChargedPionsSystLow->SetBinContent(i+1,PionSummedSystHigh->GetBinContent(j+1));
            CombinedChargedPionsSystLow->SetBinError(i+1,PionSummedSystHigh->GetBinError(j+1));
            break;
         }
      }
   }
   
}

void PrintParameter(TF1 *Fit,TString func, TString name, Int_t nParam, TString fitResult = "not known"){
  
   cout<<"-----------------------------------"<<endl;
   cout<<name<<"  "<<func<<" Status "<<fitResult<<endl;
   cout<<"Chi2/ndf: "<<Fit->GetChisquare()/Fit->GetNDF()<<endl;
   for(Int_t i = 0; i<nParam; i++)
      cout<<Fit->GetParameter(i)<<endl;
   cout<<"-----------------------------------"<<endl;
}
