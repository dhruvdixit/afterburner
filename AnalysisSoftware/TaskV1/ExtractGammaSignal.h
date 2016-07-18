// provided by Gamma Conversion Group, $ALICE_ROOT/PWG4/GammaConv ;https://twiki.cern.ch/twiki/bin/view/ALICE/PWG4GammaConversion

// Int_t
Int_t fIsMC = 0;
Double_t fnEvt;
// TString

TString fPrefix = "";
TString fPrefix2 = "";
TString fdate = "";
TString fdirectphoton = "";
TString fCutSelection = "";
TString fEnergyFlag = "";
TString fPeriodFlag = "";
TString fOutputDir = "";
TString fSuffix = "";
TString fmeson = "";
// Histograms
TString gammaCutSelectionRead ="";

//Bool_t fPileUpCorrection;

TH1D *fDeltaPt								= NULL;

TH1D *fNumberOfGoodESDTracks						= NULL;
TH1D *fEventQuality							= NULL;
TH1D *fHistoGammaESDConvPt						= NULL;
TH1D *fHistoGammaESDConvPtOriginalBinning				= NULL;
TH1D *fHistoGammaMCESDConvPt						= NULL;
TH1D *fHistoGammaMCConvPt						= NULL;
TH1D *fHistoGammaMCConvRSPt						= NULL;
TH1D *fHistoGammaMCAllPt						= NULL;
TH1D *fHistoGammaMCAllPtOriginalBinning					= NULL;
TH1D *fHistoGammaESDTrueConvPt						= NULL;
TH1D *fHistoGammaESDTruePrimaryConvPt					= NULL;
TH1D *fHistoGammaESDTruePrimaryConvPtOriginalBinning			= NULL;
TH1D *fHistoGammaESDTrueSecondaryConvPt					= NULL;
TH1D *fHistoGammaESDTrueSecondaryConvPtOriginalBinning			= NULL;
TH1D *fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPt	       	= NULL;
TH1D *fHistoGammaESDTrueSecondaryConvGammaFromXFromK0sPtOriginalBinning	= NULL;
TH1D *fHistoGammaMCDecayPi0Pt						= NULL;
TH1D *fHistoGammaMCDecayEtaPt						= NULL;
TH1D *fHistoGammaMCDecayEtapPt						= NULL;
TH1D *fHistoGammaMCDecayOmegaPt						= NULL;
TH1D *fHistoGammaMCDecayRho0Pt						= NULL;
TH1D *fHistoGammaMCDecayPhiPt						= NULL;
TH1D *fHistoGammaMCDecaySigmaPt						= NULL;
TH1D *fHistoGammaESDTruePrimaryGammaMCPt				= NULL;
TH1D *fHistoGammaESDTruePrimaryGammaRSMCPt				= NULL;

TH1D *fHistoFracAllGammaToSecOriginalBinning				= NULL;
TH1D *fHistoFracAllGammaToSec						= NULL;
TH1D *fHistoFracAllGammaToSecFromXFromK0s				= NULL;
TH1D *fHistoFracAllGammaToSecFromXFromK0sOriginalBinning	       	= NULL;
TH1D *fHistoGammaMCConvProb						= NULL;
TH1D *fHistoGammaMCPurity						= NULL;
TH1D *fHistoGammaMCTruePurityOriginalBinning				= NULL;
TH1D *fHistoGammaMCESDPrimaryConvPt					= NULL;
TH1D *fHistoGammaMCTruePurity						= NULL;
TH1D *fHistoGammaMCESDPrimaryConvPtOriginalBinning			= NULL;
TH1D *fHistoGammaMCRecoEff						= NULL;
TH1D *fHistoGammaMCPrimaryRecoEff					= NULL;
TH1D *fHistoGammaMCPrimaryRecoEffMCPt					= NULL;
TH1D *fHistoGammaMCPrimaryRecoEffRSMCPt					= NULL;
TH1D *fHistoGammaMCBackground						= NULL;

TH2D *fHistoCombinatorialBackground					= NULL;
TH2D *fHistoGammaESDTruePrimary_ESDPt_MCPt_MC				= NULL;
TH2D *fHistoGammaESDTruePrimary_ESDPt_MCPt_MC_RS			= NULL;
TH2D *fHistoGammaESDTruePrimary_ESDPt_MCPt_MC_Rebin			= NULL;

TH2F *fESDMCGammaPtDCAz							= NULL;
TH2F **fESDGammaPtDCAz							= NULL;
TH1D **fESDGammaPtDCAzBins						= NULL;
TH1D **fESDGammaPtDCAzBinsBack						= NULL;
TH1D **fESDMCGammaPtDCAzBins						= NULL;
TH1D **fESDSubGammaPtDCAzBins						= NULL;
TH1D **fESDMCSubGammaPtDCAzBins						= NULL;
TH1D **fESDMCGammaPtDCAzBinsBack					= NULL;
TH2F **fTruePrimaryPhotonPtDCAz						= NULL;
TH1D **fTruePrimaryPhotonPtDCAzBins					= NULL;
TH2F **fTrueSecondaryPhotonPtDCAz					= NULL;
TH1D **fTrueSecondaryPhotonPtDCAzBins					= NULL;
TH2F **fTrueSecondaryPhotonFromXFromK0sPtDCAz				= NULL;
TH1D **fTrueSecondaryPhotonFromXFromK0sPtDCAzBins			= NULL;
TH1D **fTrueBackgroundPtDCAzBins					= NULL;
TH1D **fTrueGammaPtDCAzBins						= NULL;
TH1D **fTrueSubGammaPtDCAzBins						= NULL;
TH1D **fHistoCombinatorialSpecies					= NULL;

TH1D *fESDGammaPtPileUp							= NULL;
TH1D *fESDMCGammaPtPileUp						= NULL;
TH1D *fTruePrimaryConvGammaPtPileUp					= NULL;
TH1D *fTrueSecondaryConvGammaPtPileUp					= NULL;
TH1D *fTrueSecondaryFromXFromK0sConvGammaPtPileUp			= NULL;

TH1D *fHistoFracAllGammaToSecPileUp					= NULL;
TH1D *fHistoFracAllGammaToSecFromXFromK0sPileUp				= NULL;
TH1D *fHistoGammaMCPurityPileUp						= NULL;
TH1D *fHistoGammaMCESDPrimaryConvPtPileUp				= NULL;
TH1D *fHistoGammaMCTruePurityPileUp   					= NULL;
TH1D *fHistoGammaMCRecoEffPileUp					= NULL;
TH1D *fHistoGammaMCPrimaryRecoEffPileUp					= NULL;

TH1D *fRatioWithWithoutPileUp						= NULL;

TH1D *PhotonIsSelected							= NULL;

void RebinSpectrum(TH1D *Spectrum, TString NewName = "");
void CalculatePileUpBackground(Bool_t doMC);
void CalculateGammaCorrection();
void CalculatePileUpGammaCorrection();
void Initialize(TString Binning, TString Energy , Int_t Bins);
void SaveHistos(Int_t isMC, TString fCutID, TString fPrefix3,Bool_t PileUpCorrection);
void SaveCorrectionHistos(TString fCutID, TString fPrefix3,Bool_t PileUpCorrection);
void SaveDCAHistos(Int_t isMC, TString fCutID, TString fPrefix3);
void FillDCAHistogrmasFromTree(TTree *dcaTree, Bool_t isMC);
void PlotAdditionalDCAz(Int_t isMC, TString fCutID);
void PlotDCAzInPtBinsWitchack(TH1D** ESDGammaPtDCAzBins, TH1D** ESDGammaPtDCAzBinsBack,TH1D** ESDGammaPtDCAzBinsBackB, TString namePlot, TString nameCanvas, TString namePad, Double_t* dcazRange, TString dateDummy, TString fMesonType,  Int_t fRowPlot, Int_t fColumnPlot, Int_t fStartBinPtRange, Int_t fNumberPtBins, Double_t* fRangeBinsPt, TString fDecayChannel, Bool_t fMonteCarloInfo, TString decayChannel, TString textCent = "MinBias");
