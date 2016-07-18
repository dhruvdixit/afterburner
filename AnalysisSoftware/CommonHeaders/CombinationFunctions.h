//**************************************************************************************************************************
//************************************************* Combination functions header *******************************************
//**************************************************************************************************************************
//***************** this header contains the functions needed to compare and combine different analysis ********************
//**************************************************************************************************************************
#include "TMatrixD.h"
#include "TArrayD.h"

struct AliConvDataObject {
    Double_t valueX;
    Double_t errorXLow;
    Double_t errorXHigh;
    Double_t valueY;
    Double_t errorYStatLow;
    Double_t errorYStatHigh;
    Double_t errorYSystLow;
    Double_t errorYSystHigh;
    Double_t errorYTotLow;
    Double_t errorYTotHigh;
};



TGraphAsymmErrors* CombinePtPointsSpectra(  TH1D* histoPCM,        TGraphAsymmErrors* graphSystPCM,
                                            TH1D* histoPHOS,        TGraphAsymmErrors* graphSystPHOS,
                                            TGraphAsymmErrors* &graphStatComb,     TGraphAsymmErrors* &graphSystComb,  
                                            Double_t* xPtLimits,    Int_t nPtLimits,
                                            Int_t offset,   Int_t bin0PCM,     Int_t bin0PHOS, Bool_t kRemoveLastPCMPoint=kFALSE, Int_t nBinsPCMRem = 1, Bool_t kRemoveFirstPHOSPoint =kFALSE){
   
    TGraphErrors* graphStatErrPHOS              = new TGraphErrors(histoPHOS);  
    TGraphErrors* graphStatErrPCM               = new TGraphErrors(histoPCM);
    TGraphAsymmErrors* graphSystPCMClone        = (TGraphAsymmErrors*)graphSystPCM->Clone("DummyPCM");  
    TGraphAsymmErrors* graphSystPHOSClone       = (TGraphAsymmErrors*)graphSystPHOS->Clone("DummyPHOS");  
    
    Double_t xComb[50];
    Double_t xEComb[50];
    Double_t xSectionComb[50];
    Double_t xSectionCombErr[50];
    Double_t xSectionCombErrL[50];
    Double_t xSectionCombErrH[50];
    Double_t xSectionCombStatErr[50];
    Double_t xSectionCombSysErr[50];

    if (kRemoveFirstPHOSPoint){
      graphStatErrPHOS->RemovePoint(0);
      graphSystPHOSClone->RemovePoint(0);
    }

    
    cout << "********************************************************************************" << endl;
    cout << "************************** PHOS ************************************************" << endl;
    cout << "********************************************************************************" << endl;
    graphStatErrPHOS->Print();
    cout<<endl;
    graphSystPHOSClone->Print();


    cout << "********************************************************************************" << endl;
    cout << "************************** PCM ************************************************" << endl;
    cout << "********************************************************************************" << endl;
    graphStatErrPCM->Print();
        cout<<endl;
    graphSystPCMClone->Print();
   
    Int_t nPHOS                                 = graphSystPHOSClone->GetN();
    Double_t* xPHOS                             = graphStatErrPHOS->GetX();
    Double_t* yPHOS                             = graphStatErrPHOS->GetY();
    Double_t* eySysPHOS                         = graphSystPHOSClone->GetEYlow();
    Double_t* exSysPHOS                         = graphSystPHOSClone->GetEXlow();
    Double_t* eyStaPHOS                         = graphStatErrPHOS->GetEY();
    Double_t* eTot2PHOS;
    eTot2PHOS                                   = new Double_t[nPHOS];
    Double_t* eTotPHOS;
    eTotPHOS                                    = new Double_t [nPHOS];
    
    for(Int_t i=0;i<nPHOS;i++){
        eTot2PHOS[i]                            = (eyStaPHOS[i]*eyStaPHOS[i]+eySysPHOS[i]*eySysPHOS[i]);
        eTotPHOS[i]                             = TMath::Sqrt( eTot2PHOS[i]);
         cout<< "PHOS::"<< xPHOS[i]<< " "<<yPHOS[i]<< " " <<  eTotPHOS[i]<< endl;
    }
    
    Int_t nPCM;
    Double_t* xPCM;
    Double_t* yPCM;
    Double_t* exSysPCM;
    Double_t* eySysLPCM;
    Double_t* eySysHPCM;
    
    nPCM                                        = graphSystPCMClone->GetN();
    if (kRemoveLastPCMPoint) {
        nPCM                                    = nPCM-nBinsPCMRem;
    }
    xPCM                                        = graphSystPCMClone->GetX();
    yPCM                                        = graphSystPCMClone->GetY();
    exSysPCM                                    = graphSystPCMClone->GetEXlow();
    eySysLPCM                                   = graphSystPCMClone->GetEYlow();
    eySysHPCM                                   = graphSystPCMClone->GetEYhigh();

    Double_t* eyStaPCM                          = graphStatErrPCM->GetEY();
    Double_t eTotL2PCM[nPCM];
    Double_t eTotH2PCM[nPCM];
    Double_t eTotLPCM[nPCM];
    cout<< "Offset::"<< offset<<endl;
    for(Int_t i=0;i<nPCM;i++){
        eTotH2PCM[i]                            = (eyStaPCM[i+offset]*eyStaPCM[i+offset]+eySysHPCM[i]*eySysHPCM[i]);
        eTotL2PCM[i]                            = (eyStaPCM[i+offset]*eyStaPCM[i+offset]+eySysLPCM[i]*eySysLPCM[i]);
        eTotLPCM[i]                             = TMath::Sqrt( eTotL2PCM[i]);
         cout<< "PCM::"<< xPCM[i]<< " "<<yPCM[i]<< " " <<  eTotLPCM[i]<< " "<< eyStaPCM[i+offset]<<" "<< eySysHPCM[i]<< endl;
    }
    //    cout<<endl;  
    //    cout<< "bin0PHOS::"<<bin0PHOS<<endl;
    Bool_t okPHOS,okPCM; 
    for (Int_t i=0;i<nPtLimits-1;i++){
        Double_t xCenter                        = 0.5*(xPtLimits[i+1]+xPtLimits[i]);
        okPHOS                                  = kFALSE;
        okPCM                                   = kFALSE;
        xComb[i]                                = xCenter;
        xSectionComb[i]                         = 0;
        xSectionCombErrL[i]                     = 0;
        xSectionCombErrH[i]                     = 0;

        if( (i-bin0PHOS) >= 0){
          //        cout << "PHOS x=" << xPHOS[i-bin0PHOS] << "\t and y" << yPHOS[i-bin0PHOS] << endl;
            if ( xPHOS[i-bin0PHOS] == xCenter && yPHOS[i-bin0PHOS]!= 0.){
                okPHOS                          = kTRUE;
            }
        }

        if( (i-bin0PCM) >= 0){
//             cout << "PCM x"<< xPCM[i-bin0PCM] <<"\t and y" <<   yPCM[i-bin0PCM]  << endl;
            if (i-bin0PCM < nPCM){
                if ( xPCM[i-bin0PCM] == xCenter && yPCM[i-bin0PCM] !=0){
                    okPCM                       = kTRUE;
                }
            }
        }
    
        if ( okPHOS && okPCM ){
            xEComb[i]=exSysPCM[i-bin0PCM];
            if( eTotL2PCM[i-bin0PCM]!=0. &&  eTotH2PCM[i-bin0PCM]!=0. && eTot2PHOS[i-bin0PHOS] !=0.){
                if(yPCM[i-bin0PCM]> yPHOS[i-bin0PHOS]){
                    Double_t wPHOS              = 1./eTot2PHOS[i-bin0PHOS];
                    Double_t wPCM               = 1./eTotL2PCM[i-bin0PCM];
                    Double_t wSum               = wPCM+wPHOS;
                    xSectionComb[i]             = (wPCM*yPCM[i-bin0PCM] +  wPHOS*yPHOS[i-bin0PHOS])/ wSum;
                    xSectionCombErr[i]          = pow((wPCM +  wPHOS),-0.5);
                    xSectionCombStatErr[i]      = pow( wPCM*wPCM/(wSum*wSum)* eyStaPCM[i-bin0PCM+offset]*eyStaPCM[i-bin0PCM+offset] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eyStaPHOS[i-bin0PHOS]*eyStaPHOS[i-bin0PHOS],0.5);
                    xSectionCombSysErr[i]       = pow( wPCM*wPCM/(wSum*wSum)* eySysHPCM[i-bin0PCM]*eySysHPCM[i-bin0PCM] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eySysPHOS[i-bin0PHOS]*eySysPHOS[i-bin0PHOS],0.5);
                    cout<< " PHOS,PCM_L::"<< xSectionComb[i]<< " " << xSectionCombErr[i] << " " << xSectionCombStatErr[i] << " " << xSectionCombSysErr[i] << endl;
                }else{
                    Double_t wPHOS              = 1./eTot2PHOS[i-bin0PHOS];
                    Double_t wPCM               = 1./eTotH2PCM[i-bin0PCM];
                    Double_t wSum               = wPCM+wPHOS;
                    xSectionComb[i]             = (wPCM*yPCM[i-bin0PCM] +  wPHOS*yPHOS[i-bin0PHOS])/ wSum;
                    xSectionCombErr[i]          = pow((wPCM +  wPHOS),-0.5);
                    xSectionCombStatErr[i]      = pow( wPCM*wPCM/(wSum*wSum)* eyStaPCM[i-bin0PCM+offset]*eyStaPCM[i-bin0PCM+offset] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eyStaPHOS[i-bin0PHOS]*eyStaPHOS[i-bin0PHOS],0.5);
                    xSectionCombSysErr[i]       = pow( wPCM*wPCM/(wSum*wSum)* eySysHPCM[i-bin0PCM]*eySysHPCM[i-bin0PCM] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eySysPHOS[i-bin0PHOS]*eySysPHOS[i-bin0PHOS],0.5);
                    cout<< " PHOS,PCM_H::"<< xSectionComb[i]<< " " << xSectionCombErr[i] << " " << xSectionCombStatErr[i] << " " << xSectionCombSysErr[i] << endl;
                }
            }
            xSectionCombErrL[i]                 = xSectionCombErr[i];
            xSectionCombErrH[i]                 = xSectionCombErr[i];
        }
    
        if ( okPHOS && !okPCM ){
            xEComb[i]=exSysPHOS[i-bin0PHOS];
            if( eTot2PHOS[i-bin0PHOS] !=0.){
                xSectionComb[i]                 = yPHOS[i-bin0PHOS];
                xSectionCombErr[i]              = pow((eTot2PHOS[i-bin0PHOS]),0.5);
                xSectionCombStatErr[i]          = eyStaPHOS[i-bin0PHOS];
                xSectionCombSysErr[i]           = eySysPHOS[i-bin0PHOS];
                cout<< " PHOS_OK::"<< xSectionComb[i]<< " " << xSectionCombErr[i] << " "  << xSectionCombStatErr[i] << " " << xSectionCombSysErr[i] << endl;
            }
            xSectionCombErrL[i]                 = xSectionCombErr[i];
            xSectionCombErrH[i]                 = xSectionCombErr[i];
        }
    
        if ( !okPHOS && okPCM ){
            xEComb[i]=exSysPCM[i-bin0PCM];
            if( eTotL2PCM[i-bin0PCM] !=0. && eTotH2PCM[i-bin0PCM]){
                xSectionComb[i]                 = yPCM[i-bin0PCM];
                xSectionCombErr[i]              = pow((eTotL2PCM[i-bin0PCM]),0.5);  // Asymmetric errors needed
                xSectionCombStatErr[i]          = eyStaPCM[i-bin0PCM+offset];
                xSectionCombSysErr[i]           = eySysHPCM[i-bin0PCM];
                cout<< " PCM_OK::"<< xSectionComb[i]<< " " << xSectionCombErr[i] << " "  << xSectionCombStatErr[i] << " " << xSectionCombSysErr[i] << endl;
            }
            xSectionCombErrL[i]                 = xSectionCombErr[i];
            xSectionCombErrH[i]                 = xSectionCombErr[i];
        }
    }
    graphStatComb                               = new TGraphAsymmErrors(nPtLimits-1,xComb,xSectionComb,xEComb,xEComb,xSectionCombStatErr,xSectionCombStatErr);
    graphSystComb                               = new TGraphAsymmErrors(nPtLimits-1,xComb,xSectionComb,xEComb,xEComb,xSectionCombSysErr,xSectionCombSysErr);   
    TGraphAsymmErrors* returnGraph              = new TGraphAsymmErrors(nPtLimits-1,xComb,xSectionComb,xEComb,xEComb,xSectionCombErrL,xSectionCombErrH);
    Int_t b                                     = 0;
    while (xSectionComb[b] == 0){
        graphStatComb->RemovePoint(0);
        graphSystComb->RemovePoint(0);
        returnGraph->RemovePoint(0);
        b++;
    }
    return returnGraph;
}

TGraphAsymmErrors* CombinePtPointsRAA(  TGraphAsymmErrors* graphStatErrPCM,        TGraphAsymmErrors* graphSystPCM,
                                        TGraphAsymmErrors* graphStatErrPHOS,        TGraphAsymmErrors* graphSystPHOS,
                                        TGraphAsymmErrors* &graphStatComb,     TGraphAsymmErrors* &graphSystComb,  
                                        Double_t* xPtLimits,    Int_t nPtLimits,
                                        Int_t offset,            Int_t bin0PCM,     Int_t bin0PHOS, Bool_t kRemoveLastPCMPoint=kFALSE, Int_t nBinsPCMRem = 1){
   
    TString detName = "";
    TString histoName = graphStatErrPHOS->GetName();
    if(histoName.Contains("EMC")) detName = "EMCal";
    else  detName = "PHOS";
    graphStatErrPHOS->Print();
     cout << "PCM histogram" << endl;
    graphStatErrPCM->Print();
    Double_t xComb[50];
    Double_t xEComb[50];
    Double_t xSectionComb[50];
    Double_t xSectionCombErr[50];
    Double_t xSectionCombErrL[50];
    Double_t xSectionCombErrH[50];
    Double_t xSectionCombStatErr[50];
    Double_t xSectionCombSysErr[50];
    
    Int_t nPHOS                                 = graphSystPHOS->GetN();
    Double_t* xPHOS                             = graphSystPHOS->GetX();
    Double_t* yPHOS                             = graphSystPHOS->GetY();
    Double_t eySysPHOS[nPHOS];
    Double_t exSysPHOS[nPHOS];
    Double_t eyStaPHOS[nPHOS];
//     Double_t * eySysPHOS                     = graphSystPHOS->GetEYlow();
//     Double_t * exSysPHOS                     = graphSystPHOS->GetEXlow();
//     Double_t * eyStaPHOS                     = graphStatErrPHOS->GetEYlow();
    Double_t* eTot2PHOS;
    eTot2PHOS                                   = new Double_t[nPHOS];
    Double_t* eTotPHOS;
    eTotPHOS                                    = new Double_t [nPHOS];
    
    for(Int_t i=0;i<nPHOS;i++){

        eyStaPHOS[i]                            = graphStatErrPHOS->GetErrorY(i);
        exSysPHOS[i]                            = graphSystPHOS->GetErrorX(i);
        eySysPHOS[i]                            = graphSystPHOS->GetErrorY(i);
        eTot2PHOS[i]                            = (eyStaPHOS[i]*eyStaPHOS[i]+eySysPHOS[i]*eySysPHOS[i]);
        eTotPHOS[i]                             = TMath::Sqrt( eTot2PHOS[i]);
//      cout<< "PHOS::"<< xPHOS[i]<< " "<<yPHOS[i]<< " " <<  eTotPHOS[i]<< endl;
         cout << detName.Data() <<  ":: " << xPHOS[i]<< " "<<yPHOS[i]<< " " <<  eTotPHOS[i]<< endl;
    }
    
    Int_t nPCM;
    Double_t* xPCM;
    Double_t* yPCM;
    Double_t* exSysPCM;
    Double_t* eySysLPCM;
    Double_t* eySysHPCM;
    
    nPCM= graphSystPCM->GetN();
    if (kRemoveLastPCMPoint) {
        nPCM                                    = nPCM-nBinsPCMRem;
    }
    xPCM                                        = graphSystPCM->GetX();
    yPCM                                        = graphSystPCM->GetY();
    exSysPCM                                    = graphSystPCM->GetEXlow();
    eySysLPCM                                   = graphSystPCM->GetEYlow();
    eySysHPCM                                   = graphSystPCM->GetEYhigh();
    Double_t * eyStaPCM                         = graphStatErrPCM->GetEYlow();

    cout << detName.Data() << " sys" << endl;
    graphSystPHOS->Print();
    cout << "PCM sys" << endl;
    graphSystPCM->Print();

    
    Double_t eTotL2PCM[nPCM];
    Double_t eTotH2PCM[nPCM];
    Double_t eTotLPCM[nPCM];
    Double_t eTotHPCM[nPCM];
    for(Int_t i=0;i<nPCM;i++){
        eTotH2PCM[i]                            = (eyStaPCM[i+offset]*eyStaPCM[i+offset]+eySysHPCM[i]*eySysHPCM[i]);
        eTotHPCM[i]                             = TMath::Sqrt( eTotH2PCM[i]);
        eTotL2PCM[i]                            = (eyStaPCM[i+offset]*eyStaPCM[i+offset]+eySysLPCM[i]*eySysLPCM[i]);
        eTotLPCM[i]                             = TMath::Sqrt( eTotL2PCM[i]);
         cout<< "PCM::"<< xPCM[i]<< " "<<yPCM[i]<< " " <<  eTotLPCM[i]<< " "<< eyStaPCM[i+offset]<<" "<< eySysHPCM[i]<< endl;
    }
    cout<<endl;  
    
    Bool_t okPHOS,okPCM; 
    for (Int_t i=0;i<nPtLimits-1;i++){
        Double_t xCenter                        = 0.5*(xPtLimits[i+1]+xPtLimits[i]);
        okPHOS                                  = kFALSE;
        okPCM                                   = kFALSE;
        xComb[i]                                = xCenter;
        xSectionComb[i]                         = 0;
        xSectionCombErrL[i]                     = 0;
        xSectionCombErrH[i]                     = 0;

        Double_t decisionBoundary               = 0.0000001;
        if((i-bin0PHOS)>=0){
             cout << xPHOS[i-bin0PHOS] << "\t" << xPCM[i-bin0PCM] << "  xCenter:: "<< i<< " " <<xCenter<< endl;
            if ( TMath::Abs(xPHOS[i-bin0PHOS] - xCenter) < decisionBoundary && yPHOS[i-bin0PHOS]!= 0.){
                okPHOS                          = kTRUE;
            }
        }

        if( (i-bin0PCM) >= 0){
            if (i-bin0PCM < nPCM){
                if ( TMath::Abs(xPCM[i-bin0PCM] - xCenter) < decisionBoundary && yPCM[i-bin0PCM]!= 0.){
                    okPCM                       = kTRUE;
                }
            }
        }
    
        if ( okPHOS && okPCM ){
            cout << detName.Data() << " ok, PCM ok" << endl;
            xEComb[i]=exSysPCM[i-bin0PCM];
            if( eTotL2PCM[i-bin0PCM]!=0. &&  eTotH2PCM[i-bin0PCM]!=0. && eTot2PHOS[i-bin0PHOS] !=0.){
                if(yPCM[i-bin0PCM]> yPHOS[i-bin0PHOS]){
                    Double_t wPHOS              = 1./eTot2PHOS[i-bin0PHOS];
                    Double_t wPCM               = 1./eTotL2PCM[i-bin0PCM];
                    Double_t wSum               = wPCM+wPHOS;
                    xSectionComb[i]             = (wPCM*yPCM[i-bin0PCM] +  wPHOS*yPHOS[i-bin0PHOS])/ wSum;
                    xSectionCombErr[i]          = pow((wPCM +  wPHOS),-0.5);
                    xSectionCombStatErr[i]      = pow( wPCM*wPCM/(wSum*wSum)* eyStaPCM[i-bin0PCM+offset]*eyStaPCM[i-bin0PCM+offset] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eyStaPHOS[i-bin0PHOS]*eyStaPHOS[i-bin0PHOS],0.5);
                    xSectionCombSysErr[i]       = pow( wPCM*wPCM/(wSum*wSum)* eySysHPCM[i-bin0PCM]*eySysHPCM[i-bin0PCM] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eySysPHOS[i-bin0PHOS]*eySysPHOS[i-bin0PHOS],0.5);
                    cout<< " " << detName.Data() << ",PCM_L::"<< xSectionComb[i]<< " " << xSectionCombErr[i] << " " << yPCM[i-bin0PCM]<< " "<< eTotLPCM[i-bin0PCM] << " "
                    << yPHOS[i-bin0PHOS]<<" "<< eTotPHOS[i-bin0PHOS]<< endl;
                    cout << "stat & sys separated ::" << xSectionCombStatErr[i] << " " << xSectionCombSysErr[i] << endl;
                }else{
                    Double_t wPHOS              = 1./eTot2PHOS[i-bin0PHOS];
                    Double_t wPCM               = 1./eTotH2PCM[i-bin0PCM];
                    Double_t wSum               = wPCM+wPHOS;
                    xSectionComb[i]             = (wPCM*yPCM[i-bin0PCM] +  wPHOS*yPHOS[i-bin0PHOS])/ wSum;
                    xSectionCombErr[i]          = pow((wPCM +  wPHOS),-0.5);
                    xSectionCombStatErr[i]      = pow( wPCM*wPCM/(wSum*wSum)* eyStaPCM[i-bin0PCM+offset]*eyStaPCM[i-bin0PCM+offset] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eyStaPHOS[i-bin0PHOS]*eyStaPHOS[i-bin0PHOS],0.5);
                    xSectionCombSysErr[i]       = pow( wPCM*wPCM/(wSum*wSum)* eySysHPCM[i-bin0PCM]*eySysHPCM[i-bin0PCM] 
                                                  + wPHOS*wPHOS/(wSum*wSum)* eySysPHOS[i-bin0PHOS]*eySysPHOS[i-bin0PHOS],0.5);
                    cout<< " " << detName.Data() << ",PCM_H::"<< xSectionComb[i]<< " " << xSectionCombErr[i] << " " << yPCM[i-bin0PCM]<< " "<< eTotHPCM[i-bin0PCM] << " "
                    << yPHOS[i-bin0PHOS]<<" "<< eTotPHOS[i-bin0PHOS] <<endl;
                    cout << "stat & sys separated ::" << xSectionCombStatErr[i] << " " << xSectionCombSysErr[i] << endl;
                }
            }
            xSectionCombErrL[i]                 = xSectionCombErr[i];
            xSectionCombErrH[i]                 = xSectionCombErr[i];
        }
    
        if ( okPHOS && !okPCM ){
            cout << "\n" << detName.Data() << " ok, PCM NOT ok" << endl;
            xEComb[i]=exSysPHOS[i-bin0PHOS];
            if( eTot2PHOS[i-bin0PHOS] !=0.){
                xSectionComb[i]                 = yPHOS[i-bin0PHOS];
                xSectionCombErr[i]              = pow((eTot2PHOS[i-bin0PHOS]),0.5);
                xSectionCombStatErr[i]          = eyStaPHOS[i-bin0PHOS];
                xSectionCombSysErr[i]           = eySysPHOS[i-bin0PHOS];
                cout<< detName.Data() << "_OK::"<< xSectionComb[i]<< " " << xSectionCombErr[i] << " "  << yPHOS[i-bin0PHOS]<<" "<< eTotPHOS[i-bin0PHOS] <<endl;
                cout << "stat & sys separated ::" << xSectionCombStatErr[i] << " " << xSectionCombSysErr[i] << endl;
            }
            xSectionCombErrL[i]                 = xSectionCombErr[i];
            xSectionCombErrH[i]                 = xSectionCombErr[i];
        }
    
        if ( !okPHOS && okPCM ){
            cout << "\n" <<detName.Data() << " NOT ok, PCM ok" << endl;
            xEComb[i]=exSysPCM[i-bin0PCM];
            if( eTotL2PCM[i-bin0PCM] !=0. && eTotH2PCM[i-bin0PCM]){
                xSectionComb[i]                 = yPCM[i-bin0PCM];
                xSectionCombErr[i]              = pow((eTotL2PCM[i-bin0PCM]),0.5);  // Asymmetric errors needed
                xSectionCombStatErr[i]          = eyStaPCM[i-bin0PCM+offset];
                xSectionCombSysErr[i]           = eySysHPCM[i-bin0PCM];
                cout<< " PCM_OK::"<< xSectionComb[i]<< " " << xSectionCombErr[i] << " "  << yPCM[i-bin0PCM]<< " "<< eTotLPCM[i-bin0PCM] << " "<< endl;
                cout << "stat & sys separated ::" << xSectionCombStatErr[i] << " " << xSectionCombSysErr[i] << endl;
            }
            xSectionCombErrL[i]                 = xSectionCombErr[i];
            xSectionCombErrH[i]                 = xSectionCombErr[i];
        }
        
        if ( !okPHOS && !okPCM ){
            cout << "\n" << detName.Data() << " NOT ok, PCM NOT ok" << endl;
        }
    }
    
    graphStatComb                               = new TGraphAsymmErrors(nPtLimits-1, xComb, xSectionComb, xEComb, xEComb, xSectionCombStatErr, xSectionCombStatErr);
    graphSystComb                               = new TGraphAsymmErrors(nPtLimits-1, xComb, xSectionComb, xEComb, xEComb, xSectionCombSysErr, xSectionCombSysErr);   
    TGraphAsymmErrors* returnGraph              = new TGraphAsymmErrors(nPtLimits-1, xComb, xSectionComb, xEComb, xEComb, xSectionCombErrL, xSectionCombErrH);

    Int_t b                                     = 0;
    while (xSectionComb[b] == 0){
        graphStatComb->RemovePoint(0);
        graphSystComb->RemovePoint(0);
        returnGraph->RemovePoint(0);
        b++;
    }
    cout << "statistical errors only" << endl;
    graphStatComb->Print();
    cout << "systematic errors only" << endl;
    graphSystComb->Print();
    cout << "stat+sys errors" << endl;
    returnGraph->Print();
    
    return returnGraph;
}

Int_t GetBinning(TObject *Obj_Dummy, Double_t* doubleBinningX){
    TString ClassName                           = Obj_Dummy->ClassName();
    if(ClassName.BeginsWith("TH1")){
        TH1D *histo                             = (TH1D*)Obj_Dummy;
        Int_t bin                               = 0;
        for (Int_t i = 1; i < histo->GetNbinsX()+1; i++){
            if (histo->GetBinContent(i) != 0){
                doubleBinningX[bin]             = histo->GetBinLowEdge(i);
                doubleBinningX[bin+1]           = histo->GetXaxis()->GetBinUpEdge(i);
                bin++;
            }
        }
        return bin+1;
    } else if(ClassName.CompareTo("TGraphErrors")==0){
        TGraphErrors *graph                     = (TGraphErrors*)Obj_Dummy;
        Double_t* binCenter                     = graph->GetX();
        Double_t* binContent                    = graph->GetY();
        Double_t* binError                      = graph->GetEX();
        Int_t nBins                             = graph->GetN();
        Int_t bin                               = 0;
        for (Int_t i = 0; i < nBins; i++){
            if (binContent[i] != 0){
                doubleBinningX[bin]             = binCenter[i]-binError[i];
                doubleBinningX[bin+1]           = binCenter[i]+binError[i];
                bin++;
            }
        }
        return bin+1;
    } else if(ClassName.CompareTo("TGraphAsymmErrors")==0){
        TGraphAsymmErrors *graph                = (TGraphAsymmErrors*)Obj_Dummy;
        Double_t* binCenter                     = graph->GetX();
        Double_t* binContent                    = graph->GetY();
        Double_t* binErrorDown                  = graph->GetEXlow();
        Double_t* binErrorUp                    = graph->GetEXhigh();
        Int_t nBins                             = graph->GetN();
        Int_t bin                               = 0;
        for (Int_t i = 0; i < nBins; i++){
            if (binContent[i] != 0){
                doubleBinningX[bin]             = binCenter[i]-binErrorDown[i];
                doubleBinningX[bin+1]           = binCenter[i]+binErrorUp[i];
                bin++;
            }
        }
        return bin+1;
    } else {
        cout << " class not defined" << endl;
        return 0;
    }
    
}

Int_t CompareBinning(Int_t nBinsA, Double_t* binningA, Int_t nBinsB, Double_t* binningB, Double_t* newBinning, Int_t* nBinsToBeCombinedA, Int_t* nBinsToBeCombinedB, TString returnStr = "", Double_t decisionBoundary = 0.0000001){
    Int_t startingBin = 0;
    //Finding startBin
    cout << "Binning A" << endl;
        for (Int_t i = 0; i < nBinsA ; i++){
            cout << binningA[i] << "\t" ;
        }
    cout << endl;
    cout << "Binning B" << endl;
        for (Int_t i = 0; i < nBinsB ; i++){
            cout << binningB[i] << "\t" ;
        }
    cout << endl;
    if (binningA[0] < binningB[0]){
        while ((binningB[0] - binningA[startingBin])>decisionBoundary && startingBin <nBinsA){
            startingBin++;
        }
        cout << "Binning A" << endl;
        for (Int_t i = startingBin; i < nBinsA ; i++){
            cout << binningA[i] << "\t" ;
        }
        cout << endl;
        cout << "Binning B" << endl;
        for (Int_t i = 0; i < nBinsB ; i++){
            cout << binningB[i] << "\t" ;
        }
        cout << endl;
    
        Int_t c                             = 1;
        Int_t startBinNewBins               = 1;
        Int_t binsToBeMergedB               = 1;
        Int_t binsToBeMergedA               = 1;
        cout << "Binning A starts earlier, combined binning will start at " << startingBin << " with " << binningA[startingBin] << endl;
        newBinning[0] = binningA[startingBin];
        for (Int_t i = startingBin+1; i < nBinsA; i++){
            if (c > nBinsB-1) return startBinNewBins;
            newBinning[startBinNewBins]     = binningA[i];
            binsToBeMergedB                 = 1;
            binsToBeMergedA                 = 1;
//              cout << "entering loop " << binningA[i] << "\t" << binningB[c] << endl;
            while( (binningA[i] - binningB[c])>decisionBoundary){
                cout << binningA[i] << "\t" << binningB[c] << endl;
                c++;
                binsToBeMergedB++; 
                if (!((binningA[i] - binningB[c])>decisionBoundary)){
//                      cout << "nächstes bin ist größer in B" << endl;
                    if (TMath::Abs(binningA[i]- binningB[c]) < decisionBoundary) {
//                          cout << " alles super" << endl;
                    } else {
//                          cout << " müssen einen hoch" << endl;
                        i++;
                        newBinning[startBinNewBins]     = binningA[i];
                        binsToBeMergedA++;
                    }
                }
                if (c > nBinsB-1) return startBinNewBins;
            }
            nBinsToBeCombinedB[startBinNewBins-1]       = binsToBeMergedB;
            nBinsToBeCombinedA[startBinNewBins-1]       = binsToBeMergedA;
            if (c > nBinsB-1) return startBinNewBins;
            cout << "exiting loop " << binningA[i] << "\t" << binningB[c] << "\t bins needed to merged A :"<<nBinsToBeCombinedA[startBinNewBins-1] <<" B :"<<nBinsToBeCombinedB[startBinNewBins-1] <<endl;
            startBinNewBins++;
            c++;
        }            
        return startBinNewBins;
    } else  if (binningB[0] < binningA[0]){
        while (!(TMath::Abs(binningA[0]- binningB[startingBin]) < decisionBoundary) && startingBin< nBinsB){
            cout << "deviation to first bin in A for startBin: "<< startingBin << "\t" <<TMath::Abs(binningA[0]- binningB[startingBin]) << endl;
            startingBin++;
        } 
        Int_t check2 = 0;
        while (startingBin == nBinsB){
            cout << "Failed to evalute starting point in attempt " << check2    << endl;
            check2++;
            startingBin=0;
            while (!(TMath::Abs(binningA[check2]- binningB[startingBin]) < decisionBoundary) && startingBin< nBinsB){
                cout << TMath::Abs(binningA[check2]- binningB[startingBin]) << endl;
                startingBin++;
            }
        }
        cout << "Binning A" << endl;
        for (Int_t i = 0; i < nBinsA ; i++){
            cout << binningA[i] << "\t" ;
        }
        cout << endl;
        cout << "Binning B" << endl;
        for (Int_t i = startingBin; i < nBinsB ; i++){
            cout << binningB[i] << "\t" ;
        }
        cout << endl;
        cout << "Binning B starts earlier, combined binning will start at " << startingBin << " with " << binningB[startingBin] << endl;
        
        Int_t c                             = startingBin+1;
        Int_t startBinNewBins               = 1;
        Int_t binsToBeMergedB               = 1;
        Int_t binsToBeMergedA               = 1;
        newBinning[0]                       = binningA[0];
        for (Int_t i = 1; i < nBinsA; i++){
            if (c > nBinsB-1) return startBinNewBins;
            newBinning[startBinNewBins]     = binningA[i];
            binsToBeMergedB                 = 1;
            binsToBeMergedA                 = 1;
//             cout << "entering loop " << binningA[i] << "\t" << binningB[c] << endl;
            while( (binningA[i] - binningB[c])>decisionBoundary){
//                 cout << binningA[i] << "\t" << binningB[c] << endl;
                if (!((binningA[i] - binningB[c+1])>decisionBoundary)){
//                     cout << "nächstes bin ist größer in B" << endl;
                    if (TMath::Abs(binningA[i]- binningB[c+1]) < decisionBoundary) {
//                         cout << " alles super" << endl;
                    } else {
//                         cout << " müssen einen hoch" << endl;
                        i++;
                        newBinning[startBinNewBins] = binningA[i];
                        binsToBeMergedA++;
                    }
                }
                c++;
                binsToBeMergedB++; 
                if (c > nBinsB-1) return startBinNewBins-1;
            }
            nBinsToBeCombinedB[startBinNewBins-1]   = binsToBeMergedB;
            nBinsToBeCombinedA[startBinNewBins-1]   = binsToBeMergedA;
             cout << "exiting loop " << binningA[i] << "\t" << binningB[c] << "\t bins needed to merged A :"<<nBinsToBeCombinedA[startBinNewBins-1] <<" B :"<<nBinsToBeCombinedB[startBinNewBins-1] <<endl;
            startBinNewBins++;
            c++;
        }            
        return startBinNewBins;

    } else {
        cout << "Binning A" << endl;
        for (Int_t i = 0; i < nBinsA ; i++){
            cout << binningA[i] << "\t" ;
        }
        cout << endl;
        cout << "Binning B" << endl;
        for (Int_t i = startingBin; i < nBinsB ; i++){
            cout << binningB[i] << "\t" ;
        }
        cout << endl;

        cout << "Both start at the same value " << binningA[0] << endl;
        
        Int_t c                             = 1;
        Int_t startBinNewBins               = 1;
        Int_t binsToBeMergedB               = 1;
        Int_t binsToBeMergedA               = 1;
        newBinning[0]                       = binningA[0];
        for (Int_t i = 1; i < nBinsA; i++){
            if (c > nBinsB-1) return startBinNewBins-1;
            newBinning[startBinNewBins]     = binningA[i];
            binsToBeMergedB                 = 1;
            binsToBeMergedA                 = 1;
//             cout << "entering loop " << binningA[i] << "\t" << binningB[c] << endl;
            while( (binningA[i] - binningB[c])>decisionBoundary){
//                 cout << binningA[i] << "\t" << binningB[c] << endl;
                if (!((binningA[i] - binningB[c+1])>decisionBoundary)){
//                     cout << "nächstes bin ist größer in B" << endl;
                    if (TMath::Abs(binningA[i]- binningB[c+1]) < decisionBoundary) {
//                         cout << " alles super" << endl;
                    } else {
//                         cout << " müssen einen hoch" << endl;
                        i++;
                        newBinning[startBinNewBins] = binningA[i];
                        binsToBeMergedA++;
                    }
                }
                c++;
                binsToBeMergedB++; 
                if (c > nBinsB-1) return startBinNewBins-1;
            }
            nBinsToBeCombinedB[startBinNewBins-1]   = binsToBeMergedB;
            nBinsToBeCombinedA[startBinNewBins-1]   = binsToBeMergedA;
//             cout << "exiting loop " << binningA[i] << "\t" << binningB[c] << "\t bins needed to merged A :"<<nBinsToBeCombinedA[startBinNewBins-1] <<" B :"<<nBinsToBeCombinedB[startBinNewBins-1] <<endl;
            startBinNewBins++;
            c++;
        }            
        return startBinNewBins;
    }
    return 0;
    if(returnStr){}
}

Int_t FindFirstCommonBin(Double_t* vectorNewBinning, Double_t* oldBinning, Double_t decisionBoundary = 0.0000001){
    Int_t startingBin   = 0;
    //Finding startBin
    
    while (!(TMath::Abs(vectorNewBinning[0] - oldBinning[startingBin])<decisionBoundary)){ 
        startingBin++;
        cout << startingBin << "\t" <<!(TMath::Abs(vectorNewBinning[0] - oldBinning[startingBin])<decisionBoundary) << endl;
    }
    return startingBin;
}

void RebinObjects(  TObject* Obj_DummyStat, 
                    TObject* Obj_DummySyst, 
                    Double_t* vectorNewBinning, 
                    Int_t* vectorRebinFactors, 
                    Int_t nCommonBins, 
                    AliConvDataObject* outputObject, 
                    TString ClassNameStat, 
                    TString ClassNameSyst, 
                    Bool_t scaleByBinCenter=kFALSE ) { //
    Double_t binningOldStat[200] ;
    Double_t binningOldSyst[200] ;
    Int_t validBinsOldStat          = GetBinning(Obj_DummyStat, binningOldStat);
    Int_t validBinsOldSys           = GetBinning(Obj_DummySyst, binningOldSyst);  
   
    Int_t firstBinStat              = FindFirstCommonBin(vectorNewBinning, binningOldStat);
    Int_t firstBinSyst              = FindFirstCommonBin(vectorNewBinning, binningOldSyst);
    
    cout << "FirstBin stat " << firstBinStat<< "\t" << binningOldStat[firstBinStat]    << endl;
    cout << "FirstBin sys " << firstBinSyst    << "\t" << binningOldSyst[firstBinSyst] << endl;
// 
    cout << "statistical Errors" <<endl;
    if(ClassNameStat.BeginsWith("TH1")){
        TH1D *histo                 = (TH1D*)Obj_DummyStat;
        Int_t indBin                = 0;
        
        while (vectorNewBinning[0] > histo->GetBinLowEdge(indBin))    { indBin++;}
        for (Int_t commonBin                        = 0; commonBin < nCommonBins-1; commonBin++){
            outputObject[commonBin].valueY          = 0;
            outputObject[commonBin].errorYStatLow   = 0;
            outputObject[commonBin].valueX          = (vectorNewBinning[commonBin] + vectorNewBinning[commonBin+1])/2;
            outputObject[commonBin].errorXLow       = (vectorNewBinning[commonBin] + vectorNewBinning[commonBin+1])/2 -vectorNewBinning[commonBin];
            outputObject[commonBin].errorXHigh      = (vectorNewBinning[commonBin] + vectorNewBinning[commonBin+1])/2 -vectorNewBinning[commonBin];
            for (Int_t add = 1; add < vectorRebinFactors[commonBin]+1;add++){
                if (scaleByBinCenter){
                    cout << indBin << "\t" << histo->GetBinCenter(indBin) << "\t"<< (histo->GetBinContent(indBin)*histo->GetBinCenter(indBin)*histo->GetBinWidth(indBin)*2*TMath::Pi()) << endl;
                    outputObject[commonBin].valueY          = outputObject[commonBin].valueY+(histo->GetBinContent(indBin)*histo->GetBinCenter(indBin)*histo->GetBinWidth(indBin)*2*TMath::Pi());
                    outputObject[commonBin].errorYStatLow   = outputObject[commonBin].errorYStatLow+TMath::Power((histo->GetBinError(indBin)*histo->GetBinCenter(indBin)*histo->GetBinWidth(indBin)*2*TMath::Pi()),2);
                }    else {
                    cout << indBin << "\t" << histo->GetBinCenter(indBin) << "\t"<<(histo->GetBinContent(indBin)*histo->GetBinWidth(indBin)) << endl;
                    outputObject[commonBin].valueY          = outputObject[commonBin].valueY+(histo->GetBinContent(indBin)*histo->GetBinWidth(indBin));
                    outputObject[commonBin].errorYStatLow   = outputObject[commonBin].errorYStatLow+TMath::Power((histo->GetBinContent(indBin)*histo->GetBinWidth(indBin)),2);
                }
                indBin++;
            }
            outputObject[commonBin].errorYStatLow   = TMath::Sqrt(outputObject[commonBin].errorYStatLow);
            outputObject[commonBin].errorYStatHigh  = outputObject[commonBin].errorYStatLow;
            cout << commonBin<< "\t"  <<outputObject[commonBin].valueX << "\t +- " << outputObject[commonBin].errorXLow << " \t " << outputObject[commonBin].valueY<< "\t+" << outputObject[commonBin].errorYStatHigh<<"\t-"<< outputObject[commonBin].errorYStatLow<<endl;
        }
    } else if(ClassNameStat.CompareTo("TGraphErrors")==0){
        TGraphErrors *graph         = (TGraphErrors*)Obj_DummyStat;
        TGraphErrors *graphCopy     = (TGraphErrors*)graph->Clone("GraphCopy");
        Double_t* valueX            = graphCopy->GetX();
        Double_t* valueY            = graphCopy->GetY();
        Double_t* errorX            = graphCopy->GetEX();
        Double_t* errorY            = graphCopy->GetEY();
        for (Int_t i = 0; i < graphCopy->GetN();i++){
            if (scaleByBinCenter){
                valueY[i]           = valueY[i]*valueX[i]*(errorX[i]+errorX[i])*2*TMath::Pi();
                errorY[i]           = errorY[i]*valueX[i]*(errorX[i]+errorX[i])*2*TMath::Pi();
            }    else {
                errorY[i]           = errorY[i]*(errorX[i]+errorX[i]);
            }
        }
        Int_t indBin                                = firstBinStat;
        for (Int_t commonBin = 0; commonBin < nCommonBins-1; commonBin++){
            outputObject[commonBin].valueY          = 0;
            outputObject[commonBin].errorYStatLow   = 0;
            outputObject[commonBin].valueX          = (vectorNewBinning[commonBin] + vectorNewBinning[commonBin+1])/2;
            outputObject[commonBin].errorXLow       = (vectorNewBinning[commonBin] + vectorNewBinning[commonBin+1])/2 -vectorNewBinning[commonBin];
            outputObject[commonBin].errorXHigh      = (vectorNewBinning[commonBin] + vectorNewBinning[commonBin+1])/2 -vectorNewBinning[commonBin];
            for (Int_t add = 1; add < vectorRebinFactors[commonBin]+1;add++){
                cout << indBin << "\t" << valueY[indBin] << endl;
                outputObject[commonBin].valueY          = outputObject[commonBin].valueY+valueY[indBin];
                outputObject[commonBin].errorYStatLow   = outputObject[commonBin].errorYStatLow+TMath::Power(errorY[indBin],2);
                indBin++;
            }
            outputObject[commonBin].errorYStatLow   = TMath::Sqrt(outputObject[commonBin].errorYStatLow);
            outputObject[commonBin].errorYStatHigh  = outputObject[commonBin].errorYStatLow;
            cout << commonBin<< "\t"  <<outputObject[commonBin].valueX << "\t +- " << outputObject[commonBin].errorXLow << " \t " << outputObject[commonBin].valueY<< "\t+" << outputObject[commonBin].errorYStatHigh<<"\t-"<< outputObject[commonBin].errorYStatLow<<endl;
        }
    } else if(ClassNameStat.CompareTo("TGraphAsymmErrors")==0){
        TGraphAsymmErrors *graph        = (TGraphAsymmErrors*)Obj_DummyStat;
        TGraphAsymmErrors *graphCopy    = (TGraphAsymmErrors*)graph->Clone("GraphCopy");
        Double_t* valueX                = graphCopy->GetX();
        Double_t* valueY                = graphCopy->GetY();
        Double_t* errorXlow             = graphCopy->GetEXlow();
        Double_t* errorXhigh            = graphCopy->GetEXhigh();
        Double_t* errorYlow             = graphCopy->GetEYlow();
        Double_t* errorYhigh            = graphCopy->GetEYhigh();
        for (Int_t i = 0; i < graphCopy->GetN();i++){
            if (scaleByBinCenter){
                valueY[i]               = valueY[i]*valueX[i]*(errorXlow[i]+errorXhigh[i])*2*TMath::Pi();
                errorYlow[i]            = errorYlow[i]*valueX[i]*(errorXlow[i]+errorXhigh[i])*2*TMath::Pi();
                errorYhigh[i]           = errorYhigh[i]*valueX[i]*(errorXlow[i]+errorXhigh[i])*2*TMath::Pi();
            }    else {
                valueY[i]               = valueY[i]*(errorXlow[i]+errorXhigh[i]);
                errorYlow[i]            = errorYlow[i]*(errorXlow[i]+errorXhigh[i]);
                errorYhigh[i]           = errorYhigh[i]*(errorXlow[i]+errorXhigh[i]);
            }
        }
        cout<< "after modification" << endl;
         graphCopy->Print();
        Int_t indBin                                = firstBinStat;
        for (Int_t commonBin = 0; commonBin < nCommonBins-1; commonBin++){
            outputObject[commonBin].valueY          = 0;
            outputObject[commonBin].errorYStatLow   = 0;
            outputObject[commonBin].errorYStatHigh  = 0;
            outputObject[commonBin].valueX          = (vectorNewBinning[commonBin] + vectorNewBinning[commonBin+1])/2;
            outputObject[commonBin].errorXLow       = (vectorNewBinning[commonBin] + vectorNewBinning[commonBin+1])/2 -vectorNewBinning[commonBin];
            outputObject[commonBin].errorXHigh      = (vectorNewBinning[commonBin] + vectorNewBinning[commonBin+1])/2 -vectorNewBinning[commonBin];

            for (Int_t add = 1; add < vectorRebinFactors[commonBin]+1;add++){
                cout << indBin << "\t" << valueY[indBin] << endl;
                outputObject[commonBin].valueY          = outputObject[commonBin].valueY+valueY[indBin];
                outputObject[commonBin].errorYStatHigh  = outputObject[commonBin].errorYStatHigh + TMath::Power(errorYhigh[indBin],2);
                outputObject[commonBin].errorYStatLow   = outputObject[commonBin].errorYStatLow + TMath::Power(errorYlow[indBin],2);
                indBin++;
            }
            outputObject[commonBin].errorYStatLow   = TMath::Sqrt(outputObject[commonBin].errorYStatLow);
            outputObject[commonBin].errorYStatHigh  = TMath::Sqrt(outputObject[commonBin].errorYStatHigh);
            cout << commonBin<< "\t"  <<outputObject[commonBin].valueX << "\t +- " << outputObject[commonBin].errorXLow << " \t " << outputObject[commonBin].valueY<< "\t+" << outputObject[commonBin].errorYStatHigh<<"\t-"<< outputObject[commonBin].errorYStatLow<<endl;
        }
    } else {
        cout << " class for Stat not defined" << endl;
        return;
    }
    cout << "systematic errors" << endl;
    if(ClassNameSyst.BeginsWith("TH1")){
        cout << "\n \n TH1" << endl << endl;
        TH1D *histo                                 = (TH1D*)Obj_DummySyst;
        Int_t indBin                                = 0;
        while (vectorNewBinning[0] > histo->GetBinLowEdge(indBin))    { indBin++;}
        for (Int_t commonBin = 0; commonBin < nCommonBins-1; commonBin++){
            outputObject[commonBin].errorYSystLow   = 0;
            for (Int_t add = 1; add < vectorRebinFactors[commonBin]+1;add++){
//                 if (scaleByBinCenter){
//                     cout << indBin << "\t" << histo->GetBinCenter(indBin) << "\t"<< histo->GetBinWidth(indBin) <<"\t" <<histo->GetBinError(indBin)/histo->GetBinContent(indBin)*100 <<"\t"<< histo->GetBinError(indBin)/histo->GetBinContent(indBin)*histo->GetBinWidth(indBin)<<endl; //
                outputObject[commonBin].errorYSystLow   = outputObject[commonBin].errorYSystLow + histo->GetBinError(indBin)/histo->GetBinContent(indBin)*histo->GetBinWidth(indBin);
//                     cout << indBin << "\t" << outputObject[commonBin].errorYSystLow<<endl; //
//                 }    else {
//                     cout << indBin << "\t" << histo->GetBinCenter(indBin) << "\t"<<(histo->GetBinContent(indBin)*histo->GetBinWidth(indBin)) << endl;
//                     outputObject[commonBin].errorYSystLow = outputObject[commonBin].errorYSystLow+(histo->GetBinContent(indBin)*histo->GetBinWidth(indBin))*histo->GetBinContent(indBin);
    
//                 }
                indBin++;
            }
            outputObject[commonBin].errorYSystLow   = outputObject[commonBin].errorYSystLow/(outputObject[commonBin].errorXLow*2)*outputObject[commonBin].valueY;
            outputObject[commonBin].errorYSystHigh  = outputObject[commonBin].errorYSystLow;
            outputObject[commonBin].errorYTotHigh   = TMath::Sqrt(TMath::Power(outputObject[commonBin].errorYSystHigh,2) + TMath::Power(outputObject[commonBin].errorYStatHigh,2));
            outputObject[commonBin].errorYTotLow    = TMath::Sqrt(TMath::Power(outputObject[commonBin].errorYSystLow,2) + TMath::Power(outputObject[commonBin].errorYStatLow,2));
            
             cout << commonBin<< "\t"  <<outputObject[commonBin].valueX << "\t +- " << outputObject[commonBin].errorXLow << " \t " << outputObject[commonBin].valueY<< "\t+" << outputObject[commonBin].errorYSystHigh<<"\t-"<< outputObject[commonBin].errorYSystLow<< "\t+" << outputObject[commonBin].errorYTotHigh<<"\t-"<< outputObject[commonBin].errorYTotLow<<"\t syst \t"<< outputObject[commonBin].errorYSystLow/outputObject[commonBin].valueY*100 <<"%"<<endl;
        }
    } else if(ClassNameSyst.CompareTo("TGraphErrors")==0){
        cout << "\n \n TGraphErrors" << endl << endl;
        TGraphErrors *graph                         = (TGraphErrors*)Obj_DummySyst;
        TGraphErrors *graphCopy                     = (TGraphErrors*)graph->Clone("GraphCopy");
        Double_t* valueX                            = graphCopy->GetX();
        Double_t* valueY                            = graphCopy->GetY();
        Double_t* errorX                            = graphCopy->GetEX();
        Double_t* errorY                            = graphCopy->GetEY();
        for (Int_t i = 0; i < graphCopy->GetN();i++){
            if (scaleByBinCenter){
                cout << i <<"\t"<<"before: " <<valueY[i] << "\t" << errorY[i] << "\t" << errorY[i]/valueY[i]*100<<"\t" << (errorX[i]+errorX[i])<< endl;
                errorY[i]                           = errorY[i]*(errorX[i]+errorX[i])/valueY[i];
                valueY[i]                           = valueY[i]*valueX[i]*(errorX[i]+errorX[i])*2*TMath::Pi();
            }    else {
                errorY[i]                           = errorY[i]*(errorX[i]+errorX[i])/valueY[i];
                errorY[i]                           = errorY[i]*(errorX[i]+errorX[i])*valueY[i] ;
            }
        }
        Int_t indBin                                = firstBinSyst;
        for (Int_t commonBin = 0; commonBin < nCommonBins-1; commonBin++){
            outputObject[commonBin].errorYSystLow   = 0;
            for (Int_t add = 1; add < vectorRebinFactors[commonBin]+1;add++){
//                 cout << indBin << "\t" << valueY[indBin] << endl;
                outputObject[commonBin].errorYSystLow   = outputObject[commonBin].errorYSystLow+errorY[indBin];
                cout << indBin << "\t" << valueY[indBin] << "\t"<< outputObject[commonBin].errorYSystLow<<endl;
                indBin++;
            }
            outputObject[commonBin].errorYSystLow   = outputObject[commonBin].errorYSystLow*outputObject[commonBin].valueY/ (outputObject[commonBin].errorXLow+outputObject[commonBin].errorXHigh);
            outputObject[commonBin].errorYSystHigh  = outputObject[commonBin].errorYSystLow;
            outputObject[commonBin].errorYTotHigh   = TMath::Sqrt(TMath::Power(outputObject[commonBin].errorYSystHigh,2) + TMath::Power(outputObject[commonBin].errorYStatHigh,2));
            outputObject[commonBin].errorYTotLow    = TMath::Sqrt(TMath::Power(outputObject[commonBin].errorYSystLow,2) + TMath::Power(outputObject[commonBin].errorYStatLow,2));
            
            cout << commonBin<< "\t"  <<outputObject[commonBin].valueX << "\t +- " << outputObject[commonBin].errorXLow << " \t " << outputObject[commonBin].valueY<< "\t+" << outputObject[commonBin].errorYSystHigh<<"\t-"<< outputObject[commonBin].errorYSystLow<< "\t+" << outputObject[commonBin].errorYTotHigh<<"\t-"<< outputObject[commonBin].errorYTotLow<<endl;
        }
    } else if(ClassNameSyst.CompareTo("TGraphAsymmErrors")==0){
        cout << "\n \n TGraphAsymmErrors" << endl << endl;
        TGraphAsymmErrors *graph                    = (TGraphAsymmErrors*)Obj_DummySyst;
        TGraphAsymmErrors *graphCopy                = (TGraphAsymmErrors*)graph->Clone("GraphCopy");
        graphCopy->Print();
        Double_t* valueX                            = graphCopy->GetX();
        Double_t* valueY                            = graphCopy->GetY();
        Double_t* errorXlow                         = graphCopy->GetEXlow();
        Double_t* errorXhigh                        = graphCopy->GetEXhigh();
        Double_t* errorYlow                         = graphCopy->GetEYlow();
        Double_t* errorYhigh                        = graphCopy->GetEYhigh();
        for (Int_t i = 0; i < graphCopy->GetN();i++){
            if (scaleByBinCenter){
                   cout << i <<"\t"<<"before: " <<valueY[i] << "\t" << errorYlow[i] << "\t" << errorYlow[i]/valueY[i]*100<<"\t" << (errorXlow[i]+errorXhigh[i])<< endl;
                errorYlow[i]                        = errorYlow[i]*(errorXlow[i]+errorXhigh[i])/valueY[i];
                errorYhigh[i]                       = errorYhigh[i]*(errorXlow[i]+errorXhigh[i])/valueY[i];
                valueY[i]                           = valueY[i]*valueX[i]*(errorXlow[i]+errorXhigh[i])*2*TMath::Pi();
            }    else {
                errorYlow[i]                        = errorYlow[i]*(errorXlow[i]+errorXhigh[i])*valueY[i];
                errorYhigh[i]                       = errorYhigh[i]*(errorXlow[i]+errorXhigh[i])*valueY[i];
                valueY[i]                           = valueY[i]*(errorXlow[i]+errorXhigh[i]);
                
            }
        }
//         graphCopy->Print();
        Int_t indBin                                = firstBinSyst;
        cout << firstBinSyst << endl;
        for (Int_t commonBin = 0; commonBin < nCommonBins-1; commonBin++){
            outputObject[commonBin].errorYSystLow   = 0;
            outputObject[commonBin].errorYSystHigh  = 0;
            for (Int_t add = 1; add < vectorRebinFactors[commonBin]+1;add++){
                 
                outputObject[commonBin].errorYSystHigh  = outputObject[commonBin].errorYSystHigh + errorYhigh[indBin];
                outputObject[commonBin].errorYSystLow   = outputObject[commonBin].errorYSystLow + errorYlow[indBin];
                cout << indBin << "\t" << valueY[indBin] << "\t"<< outputObject[commonBin].errorYSystHigh<<endl;
                indBin++;
            }
            outputObject[commonBin].errorYSystLow   = outputObject[commonBin].errorYSystLow*outputObject[commonBin].valueY/ (outputObject[commonBin].errorXLow+outputObject[commonBin].errorXHigh);
            outputObject[commonBin].errorYSystHigh  = outputObject[commonBin].errorYSystHigh*outputObject[commonBin].valueY/ (outputObject[commonBin].errorXLow+outputObject[commonBin].errorXHigh);
            outputObject[commonBin].errorYTotHigh   = TMath::Sqrt(TMath::Power(outputObject[commonBin].errorYSystHigh,2) + TMath::Power(outputObject[commonBin].errorYStatHigh,2));
            outputObject[commonBin].errorYTotLow    = TMath::Sqrt(TMath::Power(outputObject[commonBin].errorYSystLow,2) + TMath::Power(outputObject[commonBin].errorYStatLow,2));
            
             cout << commonBin<< "\t"  <<outputObject[commonBin].valueX << "\t +- " << outputObject[commonBin].errorXLow << " \t " << outputObject[commonBin].valueY<< "\t+" << outputObject[commonBin].errorYSystHigh<<"\t-"<< outputObject[commonBin].errorYSystLow<< "\t+" << outputObject[commonBin].errorYTotHigh<<"\t-"<< outputObject[commonBin].errorYTotLow<<"\t syst \t"<< outputObject[commonBin].errorYSystLow/outputObject[commonBin].valueY*100 <<"%"<<endl;
        }
    } else {
        cout << " class for Syst not defined" << endl;
        return;
    }
    return;
   if (validBinsOldStat || validBinsOldSys){}
}

//*******************************************************************************************
//** Function which compares 2 Spectra with each other and returns the ratio               **
//**  statistical and systematic errors have to be handed over                             **
//**   - Graphs should be handed over as Clones of the original object, otherwise          **
//**     they will be modified                                                             **
//*******************************************************************************************
TGraphErrors* CalculateRatioBetweenSpectraWithDifferentBinning(TObject* Obj_DummyAStat, TObject* Obj_DummyASyst, 
                                                               TObject* Obj_DummyBStat, TObject* Obj_DummyBSyst,  
                                                               Bool_t scaleByBinCenterA=kTRUE,  Bool_t scaleByBinCenterB=kTRUE, 
                                                               TGraphErrors** graphRebinnedAStat = NULL, TGraphErrors** graphRebinnedASyst = NULL, 
                                                               TGraphErrors** graphRebinnedBStat = NULL, TGraphErrors** graphRebinnedBSyst = NULL ){
    
    cout << "Reading from Object A " << endl;
    TString ClassNameA      = Obj_DummyAStat->ClassName();
    Int_t nBinsXA           = 0;
    if(ClassNameA.BeginsWith("TH1")){
        TH1D *histo         = (TH1D*)Obj_DummyAStat;
        nBinsXA             = histo->GetNbinsX()+1;
    } else if(ClassNameA.BeginsWith("TGraph")){
        TGraphErrors *graph = (TGraphErrors*)Obj_DummyAStat;
        nBinsXA             = graph->GetN()+1;
    }
    Double_t binningXA[nBinsXA];
    Int_t validBinsA        = GetBinning(Obj_DummyAStat, binningXA);
    
    cout << "Reading from Object B " << endl;
    TString ClassNameB      = Obj_DummyBStat->ClassName();
    Int_t nBinsXB           = 0 ;
    if(ClassNameB.BeginsWith("TH1")){
        TH1D *histo         = (TH1D*)Obj_DummyBStat;
        nBinsXB             = histo->GetNbinsX()+1;
    } else if(ClassNameB.BeginsWith("TGraph")){
        TGraphErrors *graph = (TGraphErrors*)Obj_DummyBStat;
        nBinsXB             = graph->GetN()+1;
    }
    Double_t binningXB[nBinsXB];
    Int_t validBinsB        = GetBinning(Obj_DummyBStat, binningXB);
    
    Int_t nBinsComb;
    if (nBinsXB < nBinsXA){
        nBinsComb           = nBinsXA;
    } else {
        nBinsComb           = nBinsXB;
    }
//     for (Int_t i = 0; i < nBinsXB; i++){
//         cout << binningXB[i] << "\t," ;
//     }
    Double_t binningCombined[nBinsComb];
    Int_t binningCombinedBinsToBeMergedA[nBinsComb];
    Int_t binningCombinedBinsToBeMergedB[nBinsComb];
    Int_t nBinsNew          = CompareBinning( validBinsA, binningXA,validBinsB, binningXB, binningCombined, binningCombinedBinsToBeMergedA,binningCombinedBinsToBeMergedB, "A");
    
    cout << "Object A"  << endl;
    AliConvDataObject rebinnedA[nBinsComb];
    RebinObjects(Obj_DummyAStat,Obj_DummyASyst, binningCombined, binningCombinedBinsToBeMergedA, nBinsNew,rebinnedA, Obj_DummyAStat->ClassName(), Obj_DummyASyst->ClassName(),scaleByBinCenterA);

    cout << "Object B"  << endl;
    AliConvDataObject rebinnedB[nBinsComb];
    RebinObjects(Obj_DummyBStat,Obj_DummyBSyst, binningCombined, binningCombinedBinsToBeMergedB, nBinsNew,rebinnedB, Obj_DummyBStat->ClassName(), Obj_DummyBSyst->ClassName(), scaleByBinCenterB);
    
    Double_t ratioX[nBinsComb];
    Double_t errorX[nBinsComb];
    Double_t ratioY[nBinsComb];
    Double_t errorY[nBinsComb];
    cout << nBinsNew-1 << "\t" <<nBinsComb << endl;
    for (Int_t commonBin = 0; commonBin < nBinsNew-1; commonBin++){
//         cout << "A "<<commonBin<< "\t"  <<rebinnedA[commonBin].valueX << "\t +- " << rebinnedA[commonBin].errorXLow << " \t " << rebinnedA[commonBin].valueY<< "\t+" << rebinnedA[commonBin].errorYStatHigh<<"\t-"<< rebinnedA[commonBin].errorYStatLow<< "\t+" << rebinnedA[commonBin].errorYSystHigh<<"\t-"<< rebinnedA[commonBin].errorYSystLow<< "\t+" << rebinnedA[commonBin].errorYTotHigh<<"\t-"<< rebinnedA[commonBin].errorYTotLow<< "\t" << rebinnedA[commonBin].errorYTotHigh/rebinnedA[commonBin].valueY*100 << "%"<<endl;
//         cout << "B " <<commonBin<< "\t"  <<rebinnedB[commonBin].valueX << "\t +- " << rebinnedB[commonBin].errorXLow << " \t " << rebinnedB[commonBin].valueY<< "\t+" << rebinnedB[commonBin].errorYStatHigh<<"\t-"<< rebinnedB[commonBin].errorYStatLow<< "\t+" << rebinnedB[commonBin].errorYSystHigh<<"\t-"<< rebinnedB[commonBin].errorYSystLow<< "\t+" << rebinnedB[commonBin].errorYTotHigh<<"\t-"<< rebinnedB[commonBin].errorYTotLow<< "\t" << rebinnedB[commonBin].errorYTotHigh/rebinnedB[commonBin].valueY*100 << "%"<<endl;
        ratioX[commonBin]   = rebinnedA[commonBin].valueX;
        errorX[commonBin]   = rebinnedA[commonBin].errorXHigh;
        ratioY[commonBin]   = rebinnedA[commonBin].valueY/rebinnedB[commonBin].valueY;
        errorY[commonBin]   = TMath::Sqrt(TMath::Power(rebinnedA[commonBin].errorYTotHigh/rebinnedA[commonBin].valueY,2) +TMath::Power(rebinnedB[commonBin].errorYTotHigh/rebinnedB[commonBin].valueY,2))*ratioY[commonBin];
//         cout << "Ratio: " << ratioX[commonBin] << "\t" <<  errorX[commonBin] << "\t" << ratioY[commonBin] << "\t" << errorY[commonBin] << "\t" << errorY[commonBin]/ratioY[commonBin]*100 << "%"<<endl;
    }
    
    
    Double_t rebinnedSpectrumAY[nBinsNew-1];
    Double_t rebinnedSpectrumAYStatErr[nBinsNew-1];
    Double_t rebinnedSpectrumAYSysErr[nBinsNew-1];
    Double_t rebinnedSpectrumBY[nBinsNew-1];
    Double_t rebinnedSpectrumBYStatErr[nBinsNew-1];
    Double_t rebinnedSpectrumBYSysErr[nBinsNew-1];
    for (Int_t commonBin = 0; commonBin < nBinsNew-1; commonBin++){
        rebinnedSpectrumAY[commonBin]           = rebinnedA[commonBin].valueY;
        rebinnedSpectrumBY[commonBin]           = rebinnedB[commonBin].valueY;
        rebinnedSpectrumAYStatErr[commonBin]    = rebinnedA[commonBin].errorYStatHigh;
        rebinnedSpectrumBYStatErr[commonBin]    = rebinnedB[commonBin].errorYStatHigh;
        rebinnedSpectrumAYSysErr[commonBin]     = TMath::Sqrt(rebinnedA[commonBin].errorYSystHigh*rebinnedA[commonBin].errorYSystHigh - 0.045*rebinnedA[commonBin].valueY*0.045*rebinnedA[commonBin].valueY) ;
        rebinnedSpectrumBYSysErr[commonBin]     = rebinnedB[commonBin].errorYSystHigh;
    }   
        
    (*graphRebinnedAStat)   = new TGraphErrors(nBinsNew-1,ratioX,rebinnedSpectrumAY,errorX,rebinnedSpectrumAYStatErr); 
    (*graphRebinnedASyst)   = new TGraphErrors(nBinsNew-1,ratioX,rebinnedSpectrumAY,errorX,rebinnedSpectrumAYSysErr); 
    (*graphRebinnedBStat)   = new TGraphErrors(nBinsNew-1,ratioX,rebinnedSpectrumBY,errorX,rebinnedSpectrumBYStatErr); 
    (*graphRebinnedBSyst)   = new TGraphErrors(nBinsNew-1,ratioX,rebinnedSpectrumBY,errorX,rebinnedSpectrumBYSysErr); 
        
    TGraphErrors* returnGraph                   =  new TGraphErrors(nBinsNew-1,ratioX,ratioY,errorX,errorY); 
    return returnGraph;
    
}

//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
TGraphAsymmErrors* CombinePtPointsSpectraAdv(       TH1D* histoPCM,        TGraphAsymmErrors* graphSystPCM,     
                                                    TGraphAsymmErrors* graphSystAPCM,     TGraphAsymmErrors* graphSystBPCM, TGraphAsymmErrors* graphSystCPCM, 
                                                    TH1D* histoPHOS,        TGraphAsymmErrors* graphSystPHOS,
                                                    TGraphAsymmErrors* graphSystAPHOS,     TGraphAsymmErrors* graphSystBPHOS, TGraphAsymmErrors* graphSystCPHOS, 
                                                    TGraphAsymmErrors* &graphStatComb,     TGraphAsymmErrors* &graphSystComb,  
                                                    TGraphAsymmErrors* &graphSystAComb, TGraphAsymmErrors* &graphSystBComb, TGraphAsymmErrors* &graphSystCComb, 
                                                    Double_t* xPtLimits,    Int_t nPtLimits,
                                                    Int_t offset,            Int_t bin0PCM,     Int_t bin0PHOS, Bool_t kRemoveLastPCMPoint=kFALSE, Int_t nBinsPCMRem = 1){
   
    TGraphErrors* graphStatErrPHOS              = new TGraphErrors(histoPHOS);  
    TGraphErrors* graphStatErrPCM               = new TGraphErrors(histoPCM);
    TGraphAsymmErrors* graphSystPCMClone        = (TGraphAsymmErrors*)graphSystPCM->Clone("DummyPCM");  
    TGraphAsymmErrors* graphSystAPCMClone       = (TGraphAsymmErrors*)graphSystAPCM->Clone("DummyPCMSystA");  
    TGraphAsymmErrors* graphSystBPCMClone       = (TGraphAsymmErrors*)graphSystBPCM->Clone("DummyPCMSystB");  
    TGraphAsymmErrors* graphSystCPCMClone       = (TGraphAsymmErrors*)graphSystCPCM->Clone("DummyPCMSystC");  
    
    TGraphAsymmErrors* graphSystPHOSClone       = (TGraphAsymmErrors*)graphSystPHOS->Clone("DummyPHOS");  
    TGraphAsymmErrors* graphSystAPHOSClone      = (TGraphAsymmErrors*)graphSystAPHOS->Clone("DummyPHOSSystA");  
    TGraphAsymmErrors* graphSystBPHOSClone      = (TGraphAsymmErrors*)graphSystBPHOS->Clone("DummyPHOSSystB");  
    TGraphAsymmErrors* graphSystCPHOSClone      = (TGraphAsymmErrors*)graphSystCPHOS->Clone("DummyPHOSSystC");  
    
    Double_t xComb[50];
    Double_t xEComb[50];
    Double_t xSectionComb[50];
    Double_t xSectionCombErr[50];
    Double_t xSectionCombErrL[50];
    Double_t xSectionCombErrH[50];
    Double_t xSectionCombStatErr[50];
    Double_t xSectionCombSysErr[50];
    Double_t xSectionCombSysAErr[50];
    Double_t xSectionCombSysBErr[50];
    Double_t xSectionCombSysCErr[50];
    
    cout << "********************************************************************************" << endl;
    cout << "************************** PHOS ************************************************" << endl;
    cout << "********************************************************************************" << endl;
    graphStatErrPHOS->Print();
    
    cout << "********************************************************************************" << endl;
    cout << "************************** PCM ************************************************" << endl;
    cout << "********************************************************************************" << endl;
    graphStatErrPCM->Print();
   
    Int_t nPHOS                                 = graphSystPHOSClone->GetN();
    Double_t* xPHOS                             = graphStatErrPHOS->GetX();
    Double_t* yPHOS                             = graphStatErrPHOS->GetY();
    Double_t* eySysPHOS                         = graphSystPHOSClone->GetEYlow();
    Double_t* eySysAPHOS                        = graphSystAPHOSClone->GetEYlow();
    Double_t* eySysBPHOS                        = graphSystBPHOSClone->GetEYlow();
    Double_t* eySysCPHOS                        = graphSystCPHOSClone->GetEYlow();
    Double_t* exSysPHOS                         = graphSystPHOSClone->GetEXlow();
    Double_t* eyStaPHOS                         = graphStatErrPHOS->GetEY();
    Double_t* eTot2PHOS;
    eTot2PHOS                                   = new Double_t[nPHOS];
    Double_t* eTotPHOS;
    eTotPHOS                                    = new Double_t [nPHOS];
    
    for(Int_t i=0;i<nPHOS;i++){
        eTot2PHOS[i]                            = (eyStaPHOS[i]*eyStaPHOS[i]+eySysPHOS[i]*eySysPHOS[i]);
        eTotPHOS[i]                             = TMath::Sqrt( eTot2PHOS[i]);
         cout<< "PHOS::"<< xPHOS[i]<< " "<<yPHOS[i]<< " " <<  eTotPHOS[i]<< endl;
    }
    
    Int_t nPCM;
    Double_t* xPCM;
    Double_t* yPCM;
    Double_t* exSysPCM;
    Double_t* eySysPCM;
    Double_t* eySysAPCM;
    Double_t* eySysBPCM;
    Double_t* eySysCPCM;
    nPCM                                        = graphSystPCMClone->GetN();
    if (kRemoveLastPCMPoint) {
        nPCM                                    = nPCM-nBinsPCMRem;
    }
    xPCM                                        = graphSystPCMClone->GetX();
    yPCM                                        = graphSystPCMClone->GetY();
    exSysPCM                                    = graphSystPCMClone->GetEXlow();
    eySysPCM                                    = graphSystPCMClone->GetEYlow();
    eySysAPCM                                   = graphSystAPCMClone->GetEYlow();
    eySysBPCM                                   = graphSystBPCMClone->GetEYlow();
    eySysCPCM                                   = graphSystCPCMClone->GetEYlow();
    Double_t* eyStaPCM                          = graphStatErrPCM->GetEY();
    Double_t eTot2PCM[nPCM];
    Double_t eTotPCM[nPCM];
    for(Int_t i=0;i<nPCM;i++){
        eTot2PCM[i]                             = (eyStaPCM[i+offset]*eyStaPCM[i+offset]+eySysPCM[i]*eySysPCM[i]);
        eTotPCM[i]                              = TMath::Sqrt( eTot2PCM[i]);
         cout<< "PCM::"<< xPCM[i]<< " "<<yPCM[i]<< " " <<  eTotPCM[i]<< " "<< eyStaPCM[i+offset]<<" "<< endl;
    }
    cout<<endl;  
    
    Bool_t okPHOS,okPCM; 
    for (Int_t i=0;i<nPtLimits-1;i++){
        Double_t xCenter                        = 0.5*(xPtLimits[i+1]+xPtLimits[i]);
        okPHOS                                  = kFALSE;
        okPCM                                   = kFALSE;
        xComb[i]                                = xCenter;
        xSectionComb[i]                         = 0;
        xSectionCombErrL[i]                     = 0;
        xSectionCombErrH[i]                     = 0;
        xSectionCombSysAErr[i]                  = 0;
        xSectionCombSysBErr[i]                  = 0;
        xSectionCombSysCErr[i]                  = 0;
        if((i-bin0PHOS)>=0){
             cout << "PHOS " << xPHOS[i-bin0PHOS] << "\t" << yPHOS[i-bin0PHOS] << endl;
            if ( xPHOS[i-bin0PHOS] == xCenter && yPHOS[i-bin0PHOS]!= 0.){
                okPHOS                          = kTRUE;
            }
        }
    
        if( (i-bin0PCM) >= 0){
            cout << "PCM "<< xPCM[i-bin0PCM] <<"\t" <<   yPCM[i-bin0PCM]  << endl;
            if (i-bin0PCM < nPCM){
                if ( xPCM[i-bin0PCM] == xCenter && yPCM[i-bin0PCM] !=0){
                    okPCM                       = kTRUE;
                }
            }
        }
    
        if ( okPHOS && okPCM ){
            xEComb[i]=exSysPCM[i-bin0PCM];
            if( eTot2PCM[i-bin0PCM]!=0. &&  eTot2PHOS[i-bin0PHOS] !=0.){
                Double_t wPHOS                  = 1./eTot2PHOS[i-bin0PHOS];
                Double_t wPCM                   = 1./eTot2PCM[i-bin0PCM];
                Double_t wSum                   = wPCM+wPHOS;
                xSectionComb[i]                 = (wPCM*yPCM[i-bin0PCM] +  wPHOS*yPHOS[i-bin0PHOS])/ wSum;
                xSectionCombErr[i]              = pow((wPCM +  wPHOS),-0.5);
                xSectionCombStatErr[i]          = pow( wPCM*wPCM/(wSum*wSum)* eyStaPCM[i-bin0PCM+offset]*eyStaPCM[i-bin0PCM+offset] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eyStaPHOS[i-bin0PHOS]*eyStaPHOS[i-bin0PHOS],0.5);
                xSectionCombSysErr[i]           = pow( wPCM*wPCM/(wSum*wSum)* eySysPCM[i-bin0PCM]*eySysPCM[i-bin0PCM] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eySysPHOS[i-bin0PHOS]*eySysPHOS[i-bin0PHOS],0.5);
                xSectionCombSysAErr[i]          = pow( wPCM*wPCM/(wSum*wSum)* eySysAPCM[i-bin0PCM]*eySysAPCM[i-bin0PCM] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eySysAPHOS[i-bin0PHOS]*eySysAPHOS[i-bin0PHOS],0.5);
                xSectionCombSysBErr[i]          = pow( wPCM*wPCM/(wSum*wSum)* eySysBPCM[i-bin0PCM]*eySysBPCM[i-bin0PCM] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eySysBPHOS[i-bin0PHOS]*eySysBPHOS[i-bin0PHOS],0.5);
                xSectionCombSysCErr[i]          = pow( wPCM*wPCM/(wSum*wSum)* eySysCPCM[i-bin0PCM]*eySysCPCM[i-bin0PCM] 
                                                       + wPHOS*wPHOS/(wSum*wSum)* eySysCPHOS[i-bin0PHOS]*eySysCPHOS[i-bin0PHOS],0.5);

                cout<< " PHOS,PCM OK::"<< xSectionComb[i]<< " " << xSectionCombErr[i] << " " << xSectionCombStatErr[i] << " " << xSectionCombSysErr[i] << endl;
            }
            xSectionCombErrL[i]                 = xSectionCombErr[i];
            xSectionCombErrH[i]                 = xSectionCombErr[i];
        }
    
        if ( okPHOS && !okPCM ){
            xEComb[i]=exSysPHOS[i-bin0PHOS];
            if( eTot2PHOS[i-bin0PHOS] !=0.){
                xSectionComb[i]                 = yPHOS[i-bin0PHOS];
                xSectionCombErr[i]              = pow((eTot2PHOS[i-bin0PHOS]),0.5);
                xSectionCombStatErr[i]          = eyStaPHOS[i-bin0PHOS];
                xSectionCombSysErr[i]           = eySysPHOS[i-bin0PHOS];
                xSectionCombSysAErr[i]          = eySysAPHOS[i-bin0PHOS];
                xSectionCombSysBErr[i]          = eySysBPHOS[i-bin0PHOS];
                xSectionCombSysCErr[i]          = eySysCPHOS[i-bin0PHOS];
                cout<< " PHOS_OK::"<< xSectionComb[i]<< " " << xSectionCombErr[i] << " "  << xSectionCombStatErr[i] << " " << xSectionCombSysErr[i] << endl;
            }
            xSectionCombErrL[i]                 = xSectionCombErr[i];
            xSectionCombErrH[i]                 = xSectionCombErr[i];
        }
    
        if ( !okPHOS && okPCM ){
            xEComb[i]=exSysPCM[i-bin0PCM];
            if( eTot2PCM[i-bin0PCM] !=0. ){
                xSectionComb[i]                 = yPCM[i-bin0PCM];
                xSectionCombErr[i]              = pow((eTot2PCM[i-bin0PCM]),0.5);  // Asymmetric errors needed
                xSectionCombStatErr[i]          = eyStaPCM[i-bin0PCM+offset];
                xSectionCombSysErr[i]           = eySysPCM[i-bin0PCM];
                xSectionCombSysAErr[i]          = eySysAPCM[i-bin0PCM];
                xSectionCombSysBErr[i]          = eySysBPCM[i-bin0PCM];
                xSectionCombSysCErr[i]          = eySysCPCM[i-bin0PCM];
                cout<< " PCM_OK::"<< xSectionComb[i]<< " " << xSectionCombErr[i] << " "  << xSectionCombStatErr[i] << " " << xSectionCombSysErr[i] << endl;
            }
            xSectionCombErrL[i]                 = xSectionCombErr[i];
            xSectionCombErrH[i]                 = xSectionCombErr[i];
        }
    }
    graphStatComb                               = new TGraphAsymmErrors(nPtLimits-1,xComb,xSectionComb,xEComb,xEComb,xSectionCombStatErr,xSectionCombStatErr);
    graphSystComb                               = new TGraphAsymmErrors(nPtLimits-1,xComb,xSectionComb,xEComb,xEComb,xSectionCombSysErr,xSectionCombSysErr);   
    graphSystAComb                              = new TGraphAsymmErrors(nPtLimits-1,xComb,xSectionComb,xEComb,xEComb,xSectionCombSysAErr,xSectionCombSysAErr);   
    graphSystBComb                              = new TGraphAsymmErrors(nPtLimits-1,xComb,xSectionComb,xEComb,xEComb,xSectionCombSysBErr,xSectionCombSysBErr);   
    graphSystCComb                              = new TGraphAsymmErrors(nPtLimits-1,xComb,xSectionComb,xEComb,xEComb,xSectionCombSysCErr,xSectionCombSysCErr);   
    TGraphAsymmErrors* returnGraph              = new TGraphAsymmErrors(nPtLimits-1,xComb,xSectionComb,xEComb,xEComb,xSectionCombErrL,xSectionCombErrH);
    Int_t b                                     = 0;
    while (xSectionComb[b] == 0){
        graphStatComb->RemovePoint(0);
        graphSystComb->RemovePoint(0);
        graphSystAComb->RemovePoint(0);
        graphSystBComb->RemovePoint(0);
        graphSystCComb->RemovePoint(0);
        returnGraph->RemovePoint(0);
        b++;
    }
    return returnGraph;
}

//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
TGraphAsymmErrors* CombinePtPointsSpectraFullCorrMat( TH1D** histoStat,    TGraphAsymmErrors** graphSyst,     
                                                      Double_t* xPtLimits,  Int_t nPtLimits,
                                                      Int_t* startOffsets, Int_t* sysOffsets,
                                                      TGraphAsymmErrors* &graphStatComb, TGraphAsymmErrors* &graphSystComb,
                                                      TString nameWeightsOutputFile = "output.dat",
                                                      Int_t method = 1
                                                    ){
    
    Int_t maxNMeasurements                      = 11;
    TString nameMeas[11]                        = {"PCM", "PHOS", "EMCal", "PCM-PHOS", "PCM-EMCal", "PCM-Dalitz", "PHOS-Dalitz", "EMCal-Dalitz", "spare", "EMCAL merged","PCMOtherDataset"};
    Bool_t isPresentGeneral[11]                 = {kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE};
    Bool_t isPresentForPt[11]                   = {kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE};
    Double_t yValueFinal[50]                    = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t yErrStatFinal[50]                  = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t yErrTotFinal[50]                   = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t yErrSysFinal[50]                   = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t xValue[50]                         = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t xErr[50]                           = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t finalWeights[11][50]               = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };

    Int_t binCounters[11]                       = { -1,-1,-1,-1,-1,
                                                    -1,-1,-1,-1,-1,
                                                    -1};
                                                
    for (Int_t i = 0; i< maxNMeasurements; i++){
        if (histoStat[i] && graphSyst[i] ) 
            isPresentGeneral[i]                 = kTRUE;
        if (isPresentGeneral[i]){
            cout << "both statistical & systematic errors have been supplied for: " << nameMeas[i].Data() << endl;
            graphSyst[i]->Print();
        } else {
            cout << "no input for: " << nameMeas[i].Data() << endl; 
        }
    }
    
    
    
    for (Int_t ptBin = 0; ptBin < nPtLimits; ptBin++){
        Double_t yValue[11]                     = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        Double_t yStatErr[11]                   = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        Double_t ySysErr[11]                    = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        Double_t yTotErr[11]                    = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        Int_t identCurr[2][11]                  = { {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10 },
                                                    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};  
        TString nameMeasPtBin[11]               = {"", "", "", "", "", "", "", "", "", "", ""};
        Int_t numberOfMeasInPtBin               = 0;
        for (Int_t meas = 0; meas < maxNMeasurements; meas++){
            binCounters[meas]                   = binCounters[meas]+1;
            cout << "Current pt boarders: " << xPtLimits[ptBin] <<" - "<< xPtLimits[ptBin+1] <<endl; 
            xValue[ptBin]                       = xPtLimits[ptBin] + (xPtLimits[ptBin+1]-xPtLimits[ptBin])/2;
            xErr[ptBin]                         = (xPtLimits[ptBin+1]-xPtLimits[ptBin])/2;
            cout << xValue[ptBin] << "\t" << xErr[ptBin] << endl;
            if (isPresentGeneral[meas]){
                cout << "current pt bin: " << binCounters[meas] << "\t offset: " << startOffsets[meas]  << "\t offset sys: " << sysOffsets[meas]  <<endl;
                if ((binCounters[meas] - startOffsets[meas]) >= 0 && histoStat[meas]->GetBinContent(binCounters[meas]+1-startOffsets[meas]) > 0. ){
                    cout << nameMeas[meas].Data() << ": pt " <<  histoStat[meas]->GetBinCenter(binCounters[meas]+1-startOffsets[meas]) 
                         << "\t value "<<histoStat[meas]->GetBinContent(binCounters[meas]+1-startOffsets[meas]) 
                         << "\t stat err: "<< histoStat[meas]->GetBinError(binCounters[meas]+1-startOffsets[meas]) <<endl;
                    if (abs(xPtLimits[ptBin]-histoStat[meas]->GetXaxis()->GetBinLowEdge(binCounters[meas]+1-startOffsets[meas])) < 0.0001 
                        &&  abs(xPtLimits[ptBin+1]-histoStat[meas]->GetXaxis()->GetBinUpEdge(binCounters[meas]+1-startOffsets[meas])) < 0.0001 ){
//                         cout << "matches bin edges" << endl;
                        isPresentForPt[meas]                    = kTRUE;
                        identCurr[1][numberOfMeasInPtBin]       = meas;
                        nameMeasPtBin[numberOfMeasInPtBin]      = nameMeas[meas];
                        yValue[meas]                            = histoStat[meas]->GetBinContent(binCounters[meas]+1-startOffsets[meas]);
                        yStatErr[meas]                          = histoStat[meas]->GetBinError(binCounters[meas]+1-startOffsets[meas]);
                        cout << binCounters[meas]-sysOffsets[meas] << "\t"<< graphSyst[meas]->GetX()[binCounters[meas]-sysOffsets[meas]] 
                             << "\t"<< graphSyst[meas]->GetErrorYhigh(binCounters[meas]-sysOffsets[meas]) 
                             << "\t"<< graphSyst[meas]->GetErrorYlow(binCounters[meas]-sysOffsets[meas]) << endl;
                        ySysErr[meas]                           = graphSyst[meas]->GetErrorYhigh(binCounters[meas]-sysOffsets[meas]);
                        yTotErr[meas]                           = TMath::Sqrt(yStatErr[meas]*yStatErr[meas]+ySysErr[meas]*ySysErr[meas]);
                        numberOfMeasInPtBin++;
                    } else {
                        isPresentForPt[meas] = kFALSE;
                        cout << "measurement: "  <<  nameMeas[meas].Data() << " not taken in this pT slice, due to mismatch in binwidth, bin: " << binCounters[meas]<< "\t" << ptBin<< " boarders: " << histoStat[meas]->GetXaxis()->GetBinLowEdge(binCounters[meas]+1-startOffsets[meas]) <<" - "<< histoStat[meas]->GetXaxis()->GetBinUpEdge(binCounters[meas]+1-startOffsets[meas]) << endl;
                        if (xPtLimits[ptBin+1] < histoStat[meas]->GetXaxis()->GetBinUpEdge(binCounters[meas]+1-startOffsets[meas]) &&
                            abs(xPtLimits[ptBin]-histoStat[meas]->GetXaxis()->GetBinLowEdge(binCounters[meas]+1-startOffsets[meas])) < 0.0001){
                            cout << "binning is smaller" << endl;
                            binCounters[meas] = binCounters[meas]-1;
                            cout << "testing bin again" << endl;
                        }
                    }    
                } else {
                    if (binCounters[meas] - startOffsets[meas] >= 0){
                        cout << "measurement: " <<  nameMeas[meas].Data() << " not taken in this pT slice, due to value = 0" << endl;
                    } else {
// //                         cout << "measurement: " <<  nameMeas[meas].Data() << " not taken in this pT slice" << endl;
                    }    
                    isPresentForPt[meas] = kFALSE;
                }    
            } else {
                cout << "measurement: " <<  nameMeas[meas].Data() << " not provided in general" << endl;
                isPresentForPt[meas] = kFALSE;
            }    
            cout << "done" << endl;
        }
        cout << "************************************************************************** number of measurements for this pT slice: " << numberOfMeasInPtBin << endl;
        Double_t corrFracPCM_PCMEMC_PCM         = 0;
        Double_t corrFracPCM_PCMEMC_PCMEMC      = 0;
        Double_t corrFracEMC_PCMEMC_EMC         = 0;
        Double_t corrFracEMC_PCMEMC_PCMEMC      = 0;

        // values are quite outdate
        if (method == 1){ // method A - more conservative correlation approach
            corrFracPCM_PCMEMC_PCM              = 0.99;
            corrFracPCM_PCMEMC_PCMEMC           = 0.55;
            corrFracEMC_PCMEMC_EMC              = 0.90;
            corrFracEMC_PCMEMC_PCMEMC           = 0.69;
        } else if (method == 2){
            corrFracPCM_PCMEMC_PCM              = 0.50;
            corrFracPCM_PCMEMC_PCMEMC           = 0.55;
            corrFracEMC_PCMEMC_EMC              = 0.69;
            corrFracEMC_PCMEMC_PCMEMC           = 0.69;
        }
        
        Double_t cvPCM_PCMPHO                   = 0;
        Double_t cvPCM_PCMEMC                   = 0.; //0.508;
        if (yValue[0]>0 && yValue[4]>0 ){
            cvPCM_PCMEMC = (corrFracPCM_PCMEMC_PCM*ySysErr[0]*corrFracPCM_PCMEMC_PCMEMC*ySysErr[4])/(yTotErr[0]*yTotErr[4]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[4] <<  ":\t sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
        }    
        Double_t cvPCM_PCMDal                   = 0.225; //Add correlation 
        Double_t cvPHO_PCMPHO                   = 0.;
        Double_t cvPHO_PHODal                   = 0.;
        Double_t cvEMC_PCMEMC                   = 0.; // 0.775
        if (yValue[2]>0 && yValue[4]>0 ){
            cvEMC_PCMEMC = (corrFracEMC_PCMEMC_EMC*ySysErr[2]*corrFracEMC_PCMEMC_PCMEMC*ySysErr[4])/(yTotErr[2]*yTotErr[4]);
            cout << nameMeas[2] <<  " sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
            cout << nameMeas[4] <<  " sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
    
        }    
        Double_t cvEMC_EMCDal                   = 0.;
        Double_t cvPCMPHO_PCMEMC                = 0.;
        Double_t cvPCMPHO_PCMDal                = 0.;
        Double_t cvPCMPHO_PHODal                = 0.;
        Double_t cvPCMEMC_PCMDal                = 0.;
        Double_t cvPCMEMC_EMCDal                = 0.;
        Double_t cvPCMDal_PHODal                = 0.;
        Double_t cvPCMDal_EMCDal                = 0.;
        Double_t cvPHODal_EMCDal                = 0.;
        Double_t cvEMCDal_EMCm                  = 0.;

        Double_t corrFracEMC_EMCm_EMC           = 0;
        Double_t corrFracEMC_EMCm_EMCm          = 0;
        Double_t corrFracPCMEMC_EMCm_PCMEMC     = 0;
        Double_t corrFracPCMEMC_EMCm_EMCm       = 0;
        
        // currently arbitrary numbers
        corrFracEMC_EMCm_EMC                    = 1;
        corrFracEMC_EMCm_EMCm                   = 0.9;
        corrFracPCMEMC_EMCm_PCMEMC              = 0.6;
        corrFracPCMEMC_EMCm_EMCm                = 0.7;
        
        Double_t cvEMC_EMCm                     = 0.;
        if (yValue[2]>0 && yValue[9]>0 ){
            cvEMC_EMCm = (corrFracEMC_EMCm_EMC*ySysErr[2]*corrFracEMC_EMCm_EMCm*ySysErr[9])/(yTotErr[2]*yTotErr[9]);
            cout << nameMeas[2] <<  ":\t sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
            cout << nameMeas[9] <<  ":\t sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
        }    
        Double_t cvPCMEMC_EMCm                  = 0.;
        if (yValue[4]>0 && yValue[9]>0 ){
            cvPCMEMC_EMCm = (corrFracPCMEMC_EMCm_PCMEMC*ySysErr[4]*corrFracPCMEMC_EMCm_EMCm*ySysErr[9])/(yTotErr[4]*yTotErr[9]);
            cout << nameMeas[4] <<  " sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
            cout << nameMeas[9] <<  " sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
        }    
      
        
        
                                        //PCM           PHOS            EMCal           PCM-PHOS            PCM-EMCal           PCM-Dalitz          PHOS-Dalitz         EMCal-Dalitz        spare   EMCAL merged    PCMOtherDataset
        Double_t cvMatrix[11][11] = {   { 1,            0,              0,              cvPCM_PCMPHO,       cvPCM_PCMEMC,       cvPCM_PCMDal,       0,                  0,                  0,      0,              1,              },
                                        { 0,            1,              0,              cvPHO_PCMPHO,       0,                  0,                  cvPHO_PHODal,       0,                  0,      0,              0,              },
                                        { 0,            0,              1,              0,                  cvEMC_PCMEMC,       0,                  0,                  cvEMC_EMCDal,       0,      cvEMC_EMCm,     0,              },
                                        { cvPCM_PCMPHO, cvPHO_PCMPHO,   0,              1,                  cvPCMPHO_PCMEMC,    cvPCMPHO_PCMDal,    cvPCMPHO_PHODal,    0,                  0,      0,              0,              },
                                        { cvPCM_PCMEMC, 0,              cvEMC_PCMEMC,   cvPCMPHO_PCMEMC,    1,                  cvPCMEMC_PCMDal,    0,                  cvPCMEMC_EMCDal,    0,      cvPCMEMC_EMCm,  0,              },
                                        { cvPCM_PCMDal, 0,              0,              cvPCMPHO_PCMDal,    cvPCMEMC_PCMDal,    1,                  cvPCMDal_PHODal,    cvPCMDal_EMCDal,    0,      0,              cvPCM_PCMDal,   },
                                        { 0,            cvPHO_PHODal,   0,              cvPCMPHO_PHODal,    0,                  cvPCMDal_PHODal,    1,                  cvPHODal_EMCDal,    0,      0,              cvPCM_PCMEMC,   },
                                        { 0,            0,              cvEMC_EMCDal,   0,                  cvPCMEMC_EMCDal,    cvPCMDal_EMCDal,    cvPHODal_EMCDal,    1,                  0,      cvEMCDal_EMCm,  cvPCM_PCMPHO,   },
                                        { 0,            0,              0.,             0,                  0,                  0,                  0,                  0,                  1,      0,              0,              },
                                        { 0,            0,              cvEMC_EMCm,     0,                  cvPCMEMC_EMCm,      0,                  0,                  cvEMCDal_EMCm,      0,      1,              0,              },
                                        { 1,            0,              0,              0,                  0,                  cvPCM_PCMDal,       cvPCM_PCMEMC,       cvPCM_PCMPHO,       0,      0,              1,              } };
        
        Double_t cvMatrixCurrPtBin[11][11]      = { {     1,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1},
                                                    {     0,    1,    0,    0,    0,    0,    0,    0,    0,    0,    0},
                                                    {     0,    0,    1,    0,    0,    0,    0,    0,    0,    0,    0},
                                                    {     0,    0,    0,    1,    0,    0,    0,    0,    0,    0,    0},
                                                    {     0,    0,    0,    0,    1,    0,    0,    0,    0,    0,    0},
                                                    {     0,    0,    0,    0,    0,    1,    0,    0,    0,    0,    0},
                                                    {     0,    0,    0,    0,    0,    0,    1,    0,    0,    0,    0},
                                                    {     0,    0,    0,    0,    0,    0,    0,    1,    0,    0,    0},
                                                    {     0,    0,    0,    0,    0,    0,    0,    0,    1,    0,    0},
                                                    {     0,    0,    0,    0,    0,    0,    0,    0,    0,    1,    0},
                                                    {     1,    0,    0,    0,    0,    0,    0,    0,    0,    0,    1} };
        
        Double_t weightArray[11]                = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
        Double_t fullSumOfWeights               = 0;
        for (Int_t meas = 0; meas < maxNMeasurements; meas++){
            cout << "identity: " << identCurr[0][meas] << " <- " << identCurr[1][meas] << endl;
        }    
        cout << "**************************************************************************" << endl;
        if (numberOfMeasInPtBin>1){
            cout << "need to do more complicated stuff"<< endl;
            TMatrixD weightingMatrix(numberOfMeasInPtBin, numberOfMeasInPtBin);
            weightingMatrix.SetTol(1.E-23);
            TArrayD arrayToFillMatrix(numberOfMeasInPtBin*numberOfMeasInPtBin);
            for (Int_t nCurrMeas = 0; nCurrMeas < numberOfMeasInPtBin; nCurrMeas++){
                for (Int_t nCurrMeas2 = 0; nCurrMeas2 < numberOfMeasInPtBin; nCurrMeas2++){
                    cout << cvMatrix[identCurr[1][nCurrMeas]][identCurr[1][nCurrMeas2]] << "*" << yTotErr[identCurr[1][nCurrMeas]] << "*"<<yTotErr[identCurr[1][nCurrMeas2]] << "\t" ;
                }
                cout << endl;
            }
            for (Int_t nCurrMeas = 0; nCurrMeas < numberOfMeasInPtBin; nCurrMeas++){
                for (Int_t nCurrMeas2 = 0; nCurrMeas2 < numberOfMeasInPtBin; nCurrMeas2++){
                    cvMatrixCurrPtBin[nCurrMeas][nCurrMeas2] = cvMatrix[identCurr[1][nCurrMeas]][identCurr[1][nCurrMeas2]];
                    cout << cvMatrixCurrPtBin[nCurrMeas][nCurrMeas2] << "\t\t" ;
                    arrayToFillMatrix[nCurrMeas*numberOfMeasInPtBin+nCurrMeas2] = cvMatrixCurrPtBin[nCurrMeas][nCurrMeas2] * yTotErr[identCurr[1][nCurrMeas]] * yTotErr[identCurr[1][nCurrMeas2]];
                }    
                cout << endl;
            }    
            weightingMatrix.SetMatrixArray(arrayToFillMatrix.GetArray());
            weightingMatrix.Print();
            weightingMatrix.Invert();
            cout << "inverted matrix" << endl;
            weightingMatrix.Print();
            cout << "trying to acces inverted matrix" << endl;
            for (Int_t nCurrMeas = 0; nCurrMeas < numberOfMeasInPtBin; nCurrMeas++){
                for (Int_t nCurrMeas2 = 0; nCurrMeas2 < numberOfMeasInPtBin; nCurrMeas2++){
                    fullSumOfWeights            = fullSumOfWeights+weightingMatrix[nCurrMeas][nCurrMeas2];
                    cout << weightingMatrix[nCurrMeas][nCurrMeas2] << "\t" ;
                }
                cout << endl;
            }
            cout << fullSumOfWeights << "\t"<< TMath::Sqrt(fullSumOfWeights)<< endl;
            cout << "weights for individual measurements" << endl;
            for (Int_t nCurrMeas = 0; nCurrMeas < numberOfMeasInPtBin; nCurrMeas++){
                Double_t partSumOfWeights       = 0;
                for (Int_t nCurrMeas2 = 0; nCurrMeas2 < numberOfMeasInPtBin; nCurrMeas2++){
                    partSumOfWeights            = partSumOfWeights+ weightingMatrix[nCurrMeas][nCurrMeas2];
                }    
                weightArray[nCurrMeas]          = partSumOfWeights/fullSumOfWeights;
                cout << weightArray[nCurrMeas] << endl;
            }
            for (Int_t nCurrMeas = 0; nCurrMeas < numberOfMeasInPtBin; nCurrMeas++){
                yValueFinal[ptBin]              = yValueFinal[ptBin]+ weightArray[nCurrMeas]* yValue[identCurr[1][nCurrMeas]];
                yErrStatFinal[ptBin]            = yErrStatFinal[ptBin] + TMath::Power(weightArray[nCurrMeas]* yStatErr[identCurr[1][nCurrMeas]],2);
                finalWeights[identCurr[1][nCurrMeas]][ptBin] = weightArray[nCurrMeas];
            }    
            yErrStatFinal[ptBin]                = TMath::Sqrt(yErrStatFinal[ptBin]);
            yErrTotFinal[ptBin]                 = 1./TMath::Sqrt(fullSumOfWeights);
            cout << "tot sys: " << yErrTotFinal[ptBin] << "\t"<< sqrt(fullSumOfWeights)<< endl; 
            yErrSysFinal[ptBin]                 = TMath::Sqrt(yErrTotFinal[ptBin]*yErrTotFinal[ptBin] - yErrStatFinal[ptBin]*yErrStatFinal[ptBin]);
            
            cout << "final weighted average: " <<  yValueFinal[ptBin] << " +- " << yErrTotFinal[ptBin] << "( stat: " << yErrStatFinal[ptBin] << " , syst: " << yErrSysFinal[ptBin] << " )"<< endl;
        } else {
            cout << "do simple copy of measurement: " << nameMeasPtBin[0].Data() << endl; 
            yValueFinal[ptBin]                  = yValue[identCurr[1][0]];
            yErrStatFinal[ptBin]                = yStatErr[identCurr[1][0]];
            yErrSysFinal[ptBin]                 = ySysErr[identCurr[1][0]];
            yErrTotFinal[ptBin]                 = yTotErr[identCurr[1][0]];
            finalWeights[identCurr[1][0]][ptBin]= 1.;
            cout << "final weighted average: " <<  yValueFinal[ptBin] << " +- " << yErrTotFinal[ptBin] << "( stat: " << yErrStatFinal[ptBin] << " , syst: " << yErrSysFinal[ptBin] << " )"<< endl;
        }    
        cout << "__________________________________________________________________________" << endl;
    }
    graphStatComb                               = new TGraphAsymmErrors(nPtLimits,xValue,yValueFinal,xErr,xErr,yErrStatFinal,yErrStatFinal);
    graphSystComb                               = new TGraphAsymmErrors(nPtLimits,xValue,yValueFinal,xErr,xErr,yErrSysFinal,yErrSysFinal);
    TGraphAsymmErrors* returnGraph              = new TGraphAsymmErrors(nPtLimits,xValue,yValueFinal,xErr,xErr,yErrTotFinal,yErrTotFinal);
    Int_t b                                     = 0;
    while (yValueFinal[b] == 0){
        graphStatComb->RemovePoint(0);
        graphSystComb->RemovePoint(0);
        returnGraph->RemovePoint(0);
        b++;
    }

    fstream  fileWeightsOutput;
    fileWeightsOutput.open(nameWeightsOutputFile.Data(), ios::out);  

    fileWeightsOutput << "pT \t" ;
    for (Int_t i = 0; i < maxNMeasurements; i++){
        if (isPresentGeneral[i]) fileWeightsOutput << i << "\t" ;
    }
    fileWeightsOutput << endl;
    
    for (Int_t ptBin = 0; ptBin < nPtLimits; ptBin++){
        if (yValueFinal[ptBin] > 0){
            fileWeightsOutput << xValue[ptBin] << "\t" ;
            for (Int_t i = 0; i < maxNMeasurements; i++){
                if (isPresentGeneral[i]) fileWeightsOutput << finalWeights[i][ptBin] << "\t" ;
            }
            fileWeightsOutput << endl;
        }    
    }    
    fileWeightsOutput.close();
    
    return returnGraph;
    
}

//*******************************************************************************************
//******** Combination of quantities with given statistical and sytematic errors for ********
//******** different triggers according to the correlation matrix given below and ***********
//******** order of triggers as indicated in nameMeas, no pt dependence of correlation ******
//******** factors forseen yet **************************************************************
//*******************************************************************************************
TGraphAsymmErrors* CombinePtPointsSpectraTriggerCorrMat(    TH1D** histoStat, TGraphAsymmErrors** graphSyst,  
                                                            Double_t* xPtLimits,  Int_t nPtLimits,
                                                            Int_t* startOffsets, Int_t* sysOffsets,
                                                            TGraphAsymmErrors* &graphStatComb, TGraphAsymmErrors* &graphSystComb,
                                                            TString nameWeightsOutputFile = "output.dat",
                                                            Int_t mode = 2, TString energy = "2.76TeV", TString meson = "Pi0"
                                                    ){
    cout << "***************************************************************************************************" << endl;
    cout << "*********************************Starting combination of triggers *********************************" << endl;
    cout << "***************************************************************************************************" << endl;
    
    Int_t maxNMeasurements                  = 12;
    TString nameMeas[12]                    = { "INT1", "INT7", "EMC1", "EMC7", "EG2", "EG1",
                                                "INT1_NLM1", "INT7_NLM1", "EMC1_NLM1", "EMC7_NLM1", "EG2_NLM1", "EG1_NLM1"};
    Bool_t isPresentGeneral[12]             = { kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE,
                                                kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE};
    Bool_t isPresentForPt[12]               = { kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE,
                                                kFALSE, kFALSE, kFALSE, kFALSE, kFALSE, kFALSE};
    Double_t yValueFinal[50]                = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t yErrStatFinal[50]              = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t yErrTotFinal[50]               = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t yErrSysFinal[50]               = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t xValue[50]                     = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t xErr[50]                       = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Double_t finalWeights[12][50]           = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
                                             };

    Int_t binCounters[12]                   = { -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1};
                                                
    for (Int_t i = 0; i< maxNMeasurements; i++){
        if (histoStat[i] && graphSyst[i] ) 
            isPresentGeneral[i]             = kTRUE;
        if (isPresentGeneral[i]){
            cout << "both statistical & systematic errors have been supplied for: " << nameMeas[i].Data() << endl;
            cout << "stat" << endl;
            for (Int_t l = 0; l< histoStat[i]->GetNbinsX(); l++ ){
              cout << "x["<< l << "]=" << histoStat[i]->GetBinCenter(l+1) <<", y["<< l << "]=" << histoStat[i]->GetBinContent(l+1) << ", ey["<< l << "]=" << histoStat[i]->GetBinError(l+1) << endl;
            }    
            cout << "sys" << endl;
            graphSyst[i]->Print();
        } else {
            cout << "no input for: " << nameMeas[i].Data() << endl; 
        }
    }
    
    for (Int_t ptBin = 0; ptBin < nPtLimits; ptBin++){
        Double_t yValue[12]                 = { -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1};
        Double_t yStatErr[12]               = { -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1};
        Double_t ySysErr[12]                = { -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1};
        Double_t yTotErr[12]                = { -1, -1, -1, -1, -1, -1,
                                                -1, -1, -1, -1, -1, -1};
        Int_t identCurr[2][12]              = { {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11},
                                                {  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}}; 
        TString nameMeasPtBin[12]           = {"", "", "", "", "", "", "", "", "", "", "", ""};
        Int_t numberOfMeasInPtBin           = 0;
        for (Int_t meas = 0; meas < maxNMeasurements; meas++){
            binCounters[meas]               = binCounters[meas]+1;
            cout << "Current pt boarders: " << xPtLimits[ptBin] <<" - "<< xPtLimits[ptBin+1] <<endl; 
            xValue[ptBin]                   = xPtLimits[ptBin] + (xPtLimits[ptBin+1]-xPtLimits[ptBin])/2;
            xErr[ptBin]                     = (xPtLimits[ptBin+1]-xPtLimits[ptBin])/2;
            cout << xValue[ptBin] << "\t" << xErr[ptBin] << endl;
            if (isPresentGeneral[meas]){
                cout << "current pt bin: " << binCounters[meas] << "\t offset: " << startOffsets[meas]  << "\t offset sys: " << sysOffsets[meas]  <<endl;
                if ((binCounters[meas] - startOffsets[meas]) >= 0 && histoStat[meas]->GetBinContent(binCounters[meas]+1-startOffsets[meas]) > 0. ){
                    cout << nameMeas[meas].Data() << ": pt " <<  histoStat[meas]->GetBinCenter(binCounters[meas]+1-startOffsets[meas]) 
                         << "\t value "<<histoStat[meas]->GetBinContent(binCounters[meas]+1-startOffsets[meas]) 
                         << "\t stat err: "<< histoStat[meas]->GetBinError(binCounters[meas]+1-startOffsets[meas]) << endl;
                    if (abs(xPtLimits[ptBin]-histoStat[meas]->GetXaxis()->GetBinLowEdge(binCounters[meas]+1-startOffsets[meas])) < 0.0001 
                        &&  abs(xPtLimits[ptBin+1]-histoStat[meas]->GetXaxis()->GetBinUpEdge(binCounters[meas]+1-startOffsets[meas])) < 0.0001 ){
//                      cout << "matches bin edges" << endl;
                        isPresentForPt[meas]                = kTRUE;
                        identCurr[1][numberOfMeasInPtBin]   = meas;
                        nameMeasPtBin[numberOfMeasInPtBin]  = nameMeas[meas];
                        yValue[meas]                        = histoStat[meas]->GetBinContent(binCounters[meas]+1-startOffsets[meas]);
                        yStatErr[meas]                      = histoStat[meas]->GetBinError(binCounters[meas]+1-startOffsets[meas]);
                        cout << "Full: "<< binCounters[meas]-sysOffsets[meas] << "\t"<< graphSyst[meas]->GetX()[binCounters[meas]-sysOffsets[meas]] 
                             << "\t"<< graphSyst[meas]->GetErrorYhigh(binCounters[meas]-sysOffsets[meas]) 
                             << "\t"<< graphSyst[meas]->GetErrorYlow(binCounters[meas]-sysOffsets[meas]) << endl;
                        ySysErr[meas]                       = graphSyst[meas]->GetErrorYhigh(binCounters[meas]-sysOffsets[meas]);
                        yTotErr[meas]                       = TMath::Sqrt(yStatErr[meas]*yStatErr[meas]+ySysErr[meas]*ySysErr[meas]);
                        numberOfMeasInPtBin++;
                    } else {
                        isPresentForPt[meas]                = kFALSE;
                      cout << "measurement: "  <<  nameMeas[meas].Data() << " not taken in this pT slice, due to mismatch in binwidth, bin: " << binCounters[meas]<< "\t" << ptBin<< " boarders: " << histoStat[meas]->GetXaxis()->GetBinLowEdge(binCounters[meas]+1-startOffsets[meas]) <<" - "<< histoStat[meas]->GetXaxis()->GetBinUpEdge(binCounters[meas]+1-startOffsets[meas]) << endl;
                      if (xPtLimits[ptBin+1] < histoStat[meas]->GetXaxis()->GetBinUpEdge(binCounters[meas]+1-startOffsets[meas]) &&
                            abs(xPtLimits[ptBin]-histoStat[meas]->GetXaxis()->GetBinLowEdge(binCounters[meas]+1-startOffsets[meas])) < 0.0001){
                            cout << "binning is smaller" << endl;
                            binCounters[meas] = binCounters[meas]-1;
                            cout << "testing bin again" << endl;
                        }
                    }   
                } else {
                    if (binCounters[meas] - startOffsets[meas] >= 0){
                        cout << "measurement: " <<  nameMeas[meas].Data() << " not taken in this pT slice, due to value = 0" << endl;
                    } else {
//                      cout << "measurement: " <<  nameMeas[meas].Data() << " not taken in this pT slice" << endl;
                    }   
                    isPresentForPt[meas]    = kFALSE;
                }   
            } else {
//              cout << "measurement: " <<  nameMeas[meas].Data() << " not provided in general" << endl;
                isPresentForPt[meas]        = kFALSE;
            }   
        }
        cout << "************************************************************************** number of measurements for this pT slice: " << numberOfMeasInPtBin << endl;
        Double_t corrFracINT1_INT1_INT7     = 0;
        Double_t corrFracINT1_INT1_EMC1     = 0;
        Double_t corrFracINT1_INT1_EMC7     = 0;
        Double_t corrFracINT1_INT1_EG2      = 0;
        Double_t corrFracINT1_INT1_EG1      = 0;
        Double_t corrFracINT1_INT1_INT11    = 0;
        Double_t corrFracINT1_INT1_INT71    = 0;
        Double_t corrFracINT1_INT1_EMC11    = 0;
        Double_t corrFracINT1_INT1_EMC71    = 0;
        Double_t corrFracINT1_INT1_EG21     = 0;
        Double_t corrFracINT1_INT1_EG11     = 0;
        Double_t corrFracINT7_INT1_INT7     = 0;
        Double_t corrFracEMC1_INT1_EMC1     = 0;
        Double_t corrFracEMC7_INT1_EMC7     = 0;
        Double_t corrFracEG2_INT1_EG2       = 0;
        Double_t corrFracEG1_INT1_EG1       = 0;
        Double_t corrFracINT11_INT1_INT11   = 0;
        Double_t corrFracINT71_INT1_INT71   = 0;
        Double_t corrFracEMC11_INT1_EMC11   = 0;
        Double_t corrFracEMC71_INT1_EMC71   = 0;
        Double_t corrFracEG21_INT1_EG21     = 0;
        Double_t corrFracEG11_INT1_EG11     = 0;

        Double_t corrFracINT7_INT7_EMC1     = 0;
        Double_t corrFracINT7_INT7_EMC7     = 0;
        Double_t corrFracINT7_INT7_EG2      = 0;
        Double_t corrFracINT7_INT7_EG1      = 0;
        Double_t corrFracINT7_INT7_INT11    = 0;
        Double_t corrFracINT7_INT7_INT71    = 0;
        Double_t corrFracINT7_INT7_EMC11    = 0;
        Double_t corrFracINT7_INT7_EMC71    = 0;
        Double_t corrFracINT7_INT7_EG21     = 0;
        Double_t corrFracINT7_INT7_EG11     = 0;
        Double_t corrFracEMC1_INT7_EMC1     = 0;
        Double_t corrFracEMC7_INT7_EMC7     = 0;
        Double_t corrFracEG2_INT7_EG2       = 0;
        Double_t corrFracEG1_INT7_EG1       = 0;
        Double_t corrFracINT11_INT7_INT11   = 0;
        Double_t corrFracINT71_INT7_INT71   = 0;
        Double_t corrFracEMC11_INT7_EMC11   = 0;
        Double_t corrFracEMC71_INT7_EMC71   = 0;
        Double_t corrFracEG21_INT7_EG21     = 0;
        Double_t corrFracEG11_INT7_EG11     = 0;

        Double_t corrFracEMC1_EMC1_EMC7     = 0;
        Double_t corrFracEMC1_EMC1_EG2      = 0;
        Double_t corrFracEMC1_EMC1_EG1      = 0;
        Double_t corrFracEMC1_EMC1_INT11    = 0;
        Double_t corrFracEMC1_EMC1_INT71    = 0;
        Double_t corrFracEMC1_EMC1_EMC11    = 0;
        Double_t corrFracEMC1_EMC1_EMC71    = 0;
        Double_t corrFracEMC1_EMC1_EG21     = 0;
        Double_t corrFracEMC1_EMC1_EG11     = 0;
        Double_t corrFracEMC7_EMC1_EMC7     = 0;
        Double_t corrFracEG2_EMC1_EG2       = 0;
        Double_t corrFracEG1_EMC1_EG1       = 0;
        Double_t corrFracINT11_EMC1_INT11   = 0;
        Double_t corrFracINT71_EMC1_INT71   = 0;
        Double_t corrFracEMC11_EMC1_EMC11   = 0;
        Double_t corrFracEMC71_EMC1_EMC71   = 0;
        Double_t corrFracEG21_EMC1_EG21     = 0;
        Double_t corrFracEG11_EMC1_EG11     = 0;

        Double_t corrFracEMC7_EMC7_EG2      = 0;
        Double_t corrFracEMC7_EMC7_EG1      = 0;
        Double_t corrFracEMC7_EMC7_INT11    = 0;
        Double_t corrFracEMC7_EMC7_INT71    = 0;
        Double_t corrFracEMC7_EMC7_EMC11    = 0;
        Double_t corrFracEMC7_EMC7_EMC71    = 0;
        Double_t corrFracEMC7_EMC7_EG21     = 0;
        Double_t corrFracEMC7_EMC7_EG11     = 0;
        Double_t corrFracEG2_EMC7_EG2       = 0;
        Double_t corrFracEG1_EMC7_EG1       = 0;
        Double_t corrFracINT11_EMC7_INT11   = 0;
        Double_t corrFracINT71_EMC7_INT71   = 0;
        Double_t corrFracEMC11_EMC7_EMC11   = 0;
        Double_t corrFracEMC71_EMC7_EMC71   = 0;
        Double_t corrFracEG21_EMC7_EG21     = 0;
        Double_t corrFracEG11_EMC7_EG11     = 0;

        Double_t corrFracEG2_EG2_EG1        = 0;
        Double_t corrFracEG2_EG2_INT11      = 0;
        Double_t corrFracEG2_EG2_INT71      = 0;
        Double_t corrFracEG2_EG2_EMC11      = 0;
        Double_t corrFracEG2_EG2_EMC71      = 0;
        Double_t corrFracEG2_EG2_EG21       = 0;
        Double_t corrFracEG2_EG2_EG11       = 0;
        Double_t corrFracEG1_EG2_EG1        = 0;
        Double_t corrFracINT11_EG2_INT11    = 0;
        Double_t corrFracINT71_EG2_INT71    = 0;
        Double_t corrFracEMC11_EG2_EMC11    = 0;
        Double_t corrFracEMC71_EG2_EMC71    = 0;
        Double_t corrFracEG21_EG2_EG21      = 0;
        Double_t corrFracEG11_EG2_EG11      = 0;

        Double_t corrFracEG1_EG1_INT11      = 0;
        Double_t corrFracEG1_EG1_INT71      = 0;
        Double_t corrFracEG1_EG1_EMC11      = 0;
        Double_t corrFracEG1_EG1_EMC71      = 0;
        Double_t corrFracEG1_EG1_EG21       = 0;
        Double_t corrFracEG1_EG1_EG11       = 0;
        Double_t corrFracINT11_EG1_INT11    = 0;
        Double_t corrFracINT71_EG1_INT71    = 0;
        Double_t corrFracEMC11_EG1_EMC11    = 0;
        Double_t corrFracEMC71_EG1_EMC71    = 0;
        Double_t corrFracEG21_EG1_EG21      = 0;
        Double_t corrFracEG11_EG1_EG11      = 0;
        
        Double_t corrFracINT11_INT11_INT71  = 0;
        Double_t corrFracINT11_INT11_EMC11  = 0;
        Double_t corrFracINT11_INT11_EMC71  = 0;
        Double_t corrFracINT11_INT11_EG21   = 0;
        Double_t corrFracINT11_INT11_EG11   = 0;
        Double_t corrFracINT71_INT11_INT71  = 0;
        Double_t corrFracEMC11_INT11_EMC11  = 0;
        Double_t corrFracEMC71_INT11_EMC71  = 0;
        Double_t corrFracEG21_INT11_EG21    = 0;
        Double_t corrFracEG11_INT11_EG11    = 0;

        Double_t corrFracINT71_INT71_EMC11  = 0;
        Double_t corrFracINT71_INT71_EMC71  = 0;
        Double_t corrFracINT71_INT71_EG21   = 0;
        Double_t corrFracINT71_INT71_EG11   = 0;
        Double_t corrFracEMC11_INT71_EMC11  = 0;
        Double_t corrFracEMC71_INT71_EMC71  = 0;
        Double_t corrFracEG21_INT71_EG21    = 0;
        Double_t corrFracEG11_INT71_EG11    = 0;

        Double_t corrFracEMC11_EMC11_EMC71  = 0;
        Double_t corrFracEMC11_EMC11_EG21   = 0;
        Double_t corrFracEMC11_EMC11_EG11   = 0;
        Double_t corrFracEMC71_EMC11_EMC71  = 0;
        Double_t corrFracEG21_EMC11_EG21    = 0;
        Double_t corrFracEG11_EMC11_EG11    = 0;

        Double_t corrFracEMC71_EMC71_EG21   = 0;
        Double_t corrFracEMC71_EMC71_EG11   = 0;
        Double_t corrFracEG21_EMC71_EG21    = 0;
        Double_t corrFracEG11_EMC71_EG11    = 0;

        Double_t corrFracEG21_EG21_EG11     = 0;
        Double_t corrFracEG11_EG21_EG11     = 0;

        
        // Definition of correlations coefficients between triggered spectra for pi0 in 2.76TeV PCM-EMC
        if ( mode == 2 && energy.CompareTo("2.76TeV") == 0 && meson.CompareTo("Pi0") == 0){ 
            corrFracINT1_INT1_INT7      = 0.9340;
            corrFracINT1_INT1_EMC1      = 0.9567;
            corrFracINT1_INT1_EMC7      = 0.9567;
            corrFracINT1_INT1_EG2       = 0.9567;
            corrFracINT1_INT1_EG1       = 0.9567;
            corrFracINT7_INT1_INT7      = 0.9415;
            corrFracEMC1_INT1_EMC1      = 0.8313;
            corrFracEMC7_INT1_EMC7      = 0.7361;
            corrFracEG2_INT1_EG2        = 0.7405;
            corrFracEG1_INT1_EG1        = 0.9340;

            corrFracINT7_INT7_EMC1      = 0.9438;
            corrFracINT7_INT7_EMC7      = 0.9438;
            corrFracINT7_INT7_EG2       = 0.9438;
            corrFracINT7_INT7_EG1       = 0.9438;
            corrFracEMC1_INT7_EMC1      = 0.8313;
            corrFracEMC7_INT7_EMC7      = 0.7361;
            corrFracEG2_INT7_EG2        = 0.7405;
            corrFracEG1_INT7_EG1        = 0.9340;

            corrFracEMC1_EMC1_EMC7      = 0.8799;
            corrFracEMC1_EMC1_EG2       = 0.8809;
            corrFracEMC1_EMC1_EG1       = 0.8809;
            corrFracEMC7_EMC1_EMC7      = 0.8102;
            corrFracEG2_EMC1_EG2        = 0.7321;
            corrFracEG1_EMC1_EG1        = 0.8365;

            corrFracEMC7_EMC7_EG2       = 0.9161;
            corrFracEMC7_EMC7_EG1       = 0.9161;
            corrFracEG2_EMC7_EG2        = 0.7950;
            corrFracEG1_EMC7_EG1        = 0.8584;

            corrFracEG2_EG2_EG1         = 0.9137;
            corrFracEG1_EG2_EG1         = 0.9071;
        // Definition of correlations coefficients between triggered spectra for pi0 in 2.76TeV PCM-EMC
        } else if (mode == 2 && energy.CompareTo("2.76TeV") == 0 && meson.CompareTo("Eta") == 0){ 
            corrFracINT1_INT1_INT7      = 0.7835;
            corrFracINT1_INT1_EMC1      = 0.7835;
            corrFracINT1_INT1_EMC7      = 0.7835;
            corrFracINT1_INT1_EG2       = 0.7835;
            corrFracINT1_INT1_EG1       = 0.7835;
            corrFracINT7_INT1_INT7      = 0.7820;
            corrFracEMC1_INT1_EMC1      = 0.5927;
            corrFracEMC7_INT1_EMC7      = 0.9103;
            corrFracEG2_INT1_EG2        = 0.8088;
            corrFracEG1_INT1_EG1        = 0.7059;

            corrFracINT7_INT7_EMC1      = 0.7820;
            corrFracINT7_INT7_EMC7      = 0.7820;
            corrFracINT7_INT7_EG2       = 0.7820;
            corrFracINT7_INT7_EG1       = 0.7820;
            corrFracEMC1_INT7_EMC1      = 0.5927;
            corrFracEMC7_INT7_EMC7      = 0.9103;
            corrFracEG2_INT7_EG2        = 0.8088;
            corrFracEG1_INT7_EG1        = 0.7059;

            corrFracEMC1_EMC1_EMC7      = 0.9261;
            corrFracEMC1_EMC1_EG2       = 0.9261;
            corrFracEMC1_EMC1_EG1       = 0.9261;
            corrFracEMC7_EMC1_EMC7      = 0.7808;
            corrFracEG2_EMC1_EG2        = 0.8365;
            corrFracEG1_EMC1_EG1        = 0.8683;

            corrFracEMC7_EMC7_EG2       = 0.8140;
            corrFracEMC7_EMC7_EG1       = 0.8140;
            corrFracEG2_EMC7_EG2        = 0.8593;
            corrFracEG1_EMC7_EG1        = 0.8945;

            corrFracEG2_EG2_EG1         = 0.9022;
            corrFracEG1_EG2_EG1         = 0.9221;
        // Definition of correlations coefficients between triggered spectra for eta/pi0 in 2.76TeV PCM-EMC
        } else if (mode == 2 && energy.CompareTo("2.76TeV") == 0 && meson.CompareTo("EtaToPi0") == 0){ 
            corrFracINT1_INT1_INT7      = 0.8020;
            corrFracINT1_INT1_EMC1      = 0.8036;
            corrFracINT1_INT1_EMC7      = 0.8036;
            corrFracINT1_INT1_EG2       = 0.8036;
            corrFracINT1_INT1_EG1       = 0.8036;
            corrFracINT7_INT1_INT7      = 0.8045;
            corrFracEMC1_INT1_EMC1      = 0.8170;
            corrFracEMC7_INT1_EMC7      = 0.9648;
            corrFracEG2_INT1_EG2        = 0.8898;
            corrFracEG1_INT1_EG1        = 0.9650;
            
            corrFracINT7_INT7_EMC1      = 0.7948;
            corrFracINT7_INT7_EMC7      = 0.7948;
            corrFracINT7_INT7_EG2       = 0.7948;
            corrFracINT7_INT7_EG1       = 0.7948;
            corrFracEMC1_INT7_EMC1      = 0.8089;
            corrFracEMC7_INT7_EMC7      = 0.9648;
            corrFracEG2_INT7_EG2        = 0.8898;
            corrFracEG1_INT7_EG1        = 0.9650;
            
            corrFracEMC1_EMC1_EMC7      = 0.9660;
            corrFracEMC1_EMC1_EG2       = 0.9662;
            corrFracEMC1_EMC1_EG1       = 0.9662;
            corrFracEMC7_EMC1_EMC7      = 0.8663;
            corrFracEG2_EMC1_EG2        = 0.8672;
            corrFracEG1_EMC1_EG1        = 0.9495;
            
            corrFracEMC7_EMC7_EG2       = 0.8663;
            corrFracEMC7_EMC7_EG1       = 0.8663;
            corrFracEG2_EMC7_EG2        = 0.8670;
            corrFracEG1_EMC7_EG1        = 0.9495;
            
            corrFracEG2_EG2_EG1         = 0.8672;
            corrFracEG1_EG2_EG1         = 0.9495;
        }
 
        // Definition of correlations coefficients between triggered spectra for pi0 in 2.76TeV EMC-EMC
        if (mode == 4 && energy.CompareTo("2.76TeV") == 0 && meson.CompareTo("Pi0") == 0){ 
            corrFracINT1_INT1_INT7      = 0.8953;
            corrFracINT1_INT1_EMC1      = 0.9165;
            corrFracINT1_INT1_EMC7      = 0.9165;
            corrFracINT1_INT1_EG2       = 0.9165;
            corrFracINT1_INT1_EG1       = 0.9165;
            corrFracINT7_INT1_INT7      = 0.9376;
            corrFracEMC1_INT1_EMC1      = 0.8798;
            corrFracEMC7_INT1_EMC7      = 0.8477;
            corrFracEG2_INT1_EG2        = 0.6737;
            corrFracEG1_INT1_EG1        = 0.8112;
            
            corrFracINT7_INT7_EMC1      = 0.9116;
            corrFracINT7_INT7_EMC7      = 0.9116;
            corrFracINT7_INT7_EG2       = 0.9116;
            corrFracINT7_INT7_EG1       = 0.9116;
            corrFracEMC1_INT7_EMC1      = 0.8798;
            corrFracEMC7_INT7_EMC7      = 0.8477;
            corrFracEG2_INT7_EG2        = 0.6737;
            corrFracEG1_INT7_EG1        = 0.8112;
            
            corrFracEMC1_EMC1_EMC7      = 0.8276;
            corrFracEMC1_EMC1_EG2       = 0.8276;
            corrFracEMC1_EMC1_EG1       = 0.8276;
            corrFracEMC7_EMC1_EMC7      = 0.7843;
            corrFracEG2_EMC1_EG2        = 0.7085;
            corrFracEG1_EMC1_EG1        = 0.7390;
            
            corrFracEMC7_EMC7_EG2       = 0.9412;
            corrFracEMC7_EMC7_EG1       = 0.9412;
            corrFracEG2_EMC7_EG2        = 0.8318;
            corrFracEG1_EMC7_EG1        = 0.8171;
            
            corrFracEG2_EG2_EG1         = 0.9354;
            corrFracEG1_EG2_EG1         = 0.8861;
        // Definition of correlations coefficients between triggered spectra for eta in 2.76TeV EMC-EMC    
        } else if (mode == 4 && energy.CompareTo("2.76TeV") == 0 && meson.CompareTo("Eta") == 0){ 
            corrFracINT1_INT1_INT7      = 0.6500;
            corrFracINT1_INT1_EMC1      = 0.6548;
            corrFracINT1_INT1_EMC7      = 0.6548;
            corrFracINT1_INT1_EG2       = 0.6548;
            corrFracINT1_INT1_EG1       = 0.6548;
            corrFracINT7_INT1_INT7      = 0.6501;
            corrFracEMC1_INT1_EMC1      = 0.8435;
            corrFracEMC7_INT1_EMC7      = 0.7372;
            corrFracEG2_INT1_EG2        = 0.7485;
            corrFracEG1_INT1_EG1        = 0.8618;
            
            corrFracINT7_INT7_EMC1      = 0.6501;
            corrFracINT7_INT7_EMC7      = 0.6501;
            corrFracINT7_INT7_EG2       = 0.6501;
            corrFracINT7_INT7_EG1       = 0.6501;
            corrFracEMC1_INT7_EMC1      = 0.8244;
            corrFracEMC7_INT7_EMC7      = 0.7372;
            corrFracEG2_INT7_EG2        = 0.7485;
            corrFracEG1_INT7_EG1        = 0.8618;
            
            corrFracEMC1_EMC1_EMC7      = 0.8803;
            corrFracEMC1_EMC1_EG2       = 0.8803;
            corrFracEMC1_EMC1_EG1       = 0.8803;
            corrFracEMC7_EMC1_EMC7      = 0.7180;
            corrFracEG2_EMC1_EG2        = 0.7894;
            corrFracEG1_EMC1_EG1        = 0.8022;
            
            corrFracEMC7_EMC7_EG2       = 0.7529;
            corrFracEMC7_EMC7_EG1       = 0.7529;
            corrFracEG2_EMC7_EG2        = 0.8234;
            corrFracEG1_EMC7_EG1        = 0.7139;
            
            corrFracEG2_EG2_EG1         = 0.8895;
            corrFracEG1_EG2_EG1         = 0.8689;
        // Definition of correlations coefficients between triggered spectra for eta/pi0 in 2.76TeV EMC-EMC    
        } else if (mode == 4 && energy.CompareTo("2.76TeV") == 0 && meson.CompareTo("EtaToPi0") == 0){ 
            corrFracINT1_INT1_INT7      = 0.6509;
            corrFracINT1_INT1_EMC1      = 0.6426;
            corrFracINT1_INT1_EMC7      = 0.6426;
            corrFracINT1_INT1_EG2       = 0.6426;
            corrFracINT1_INT1_EG1       = 0.6426;
            corrFracINT7_INT1_INT7      = 0.6504;
            corrFracEMC1_INT1_EMC1      = 0.9154;
            corrFracEMC7_INT1_EMC7      = 0.6941;
            corrFracEG2_INT1_EG2        = 0.8355;
            corrFracEG1_INT1_EG1        = 0.8839;
            
            corrFracINT7_INT7_EMC1      = 0.6293;
            corrFracINT7_INT7_EMC7      = 0.6293;
            corrFracINT7_INT7_EG2       = 0.6293;
            corrFracINT7_INT7_EG1       = 0.6293;
            corrFracEMC1_INT7_EMC1      = 0.8971;
            corrFracEMC7_INT7_EMC7      = 0.6941;
            corrFracEG2_INT7_EG2        = 0.8355;
            corrFracEG1_INT7_EG1        = 0.8839;
            
            corrFracEMC1_EMC1_EMC7      = 0.9116;
            corrFracEMC1_EMC1_EG2       = 0.9116;
            corrFracEMC1_EMC1_EG1       = 0.9116;
            corrFracEMC7_EMC1_EMC7      = 0.6579;
            corrFracEG2_EMC1_EG2        = 0.8355;
            corrFracEG1_EMC1_EG1        = 0.8733;
            
            corrFracEMC7_EMC7_EG2       = 0.6579;
            corrFracEMC7_EMC7_EG1       = 0.6579;
            corrFracEG2_EMC7_EG2        = 0.8355;
            corrFracEG1_EMC7_EG1        = 0.8733;
            
            corrFracEG2_EG2_EG1         = 0.8355;
            corrFracEG1_EG2_EG1         = 0.8733;
        }
  
        // correlation coefficients for merged cluster analysis cross NLM
        if ( mode == 10 && energy.CompareTo("2.76TeV") == 0 && meson.CompareTo("Pi0") == 0) {
            corrFracEMC1_EMC1_EG2      = 0.6984;
            corrFracEMC1_EMC1_EG1      = 0.6984;
            corrFracEMC1_EMC1_EMC11    = 0.9568;
            corrFracEMC1_EMC1_EG21     = 0.6746;
            corrFracEMC1_EMC1_EG11     = 0.6746;
            corrFracEG2_EMC1_EG2       = 0.8327;
            corrFracEG1_EMC1_EG1       = 0.5313;
            corrFracEMC11_EMC1_EMC11   = 0.8787;
            corrFracEG21_EMC1_EG21     = 0.9064;
            corrFracEG11_EMC1_EG11     = 0.5079;

            corrFracEG2_EG2_EG1        = 1;
            corrFracEG2_EG2_EMC11      = 0.8189;
            corrFracEG2_EG2_EG21       = 0.9558;
            corrFracEG2_EG2_EG11       = 0.9558;
            corrFracEG1_EG2_EG1        = 0.9462;
            corrFracEMC11_EG2_EMC11    = 0.5876;
            corrFracEG21_EG2_EG21      = 0.9519;
            corrFracEG11_EG2_EG11      = 0.8837;

            corrFracEG1_EG1_EMC11      = 0.7263;
            corrFracEG1_EG1_EG21       = 0.9515;
            corrFracEG1_EG1_EG11       = 0.9848;
            corrFracEMC11_EG1_EMC11    = 0.7049;
            corrFracEG21_EG1_EG21      = 0.9064;
            corrFracEG11_EG1_EG11      = 0.9604;
        
            corrFracEMC11_EMC11_EG21   = 0.8094;
            corrFracEMC11_EMC11_EG11   = 0.8094;
            corrFracEG21_EMC11_EG21    = 0.9161;
            corrFracEG11_EMC11_EG11    = 0.7965;

            corrFracEG21_EG21_EG11     = 1;
            corrFracEG11_EG21_EG11     = 0.9730;
        }    
  
        // correlation factors for INT1 triggers
        Double_t cvINT1_INT7              = 0.;
        if (yValue[0]>0 && yValue[1]>0 ){
            cvINT1_INT7 = (corrFracINT1_INT1_INT7*ySysErr[0]*corrFracINT7_INT1_INT7*ySysErr[1])/(yTotErr[0]*yTotErr[1]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[1] <<  ":\t sys error : "  << ySysErr[1] << "\t, total err: " <<  yTotErr[1] << endl;
        }   
        Double_t cvINT1_EMC1              = 0.;
        if (yValue[0]>0 && yValue[2]>0 ){
            cvINT1_EMC1 = (corrFracINT1_INT1_EMC1*ySysErr[0]*corrFracEMC1_INT1_EMC1*ySysErr[2])/(yTotErr[0]*yTotErr[2]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[2] <<  ":\t sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
        }   
        Double_t cvINT1_EMC7              = 0.;
        if (yValue[0]>0 && yValue[3]>0 ){
            cvINT1_EMC7 = (corrFracINT1_INT1_EMC7*ySysErr[0]*corrFracEMC7_INT1_EMC7*ySysErr[3])/(yTotErr[0]*yTotErr[3]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[3] <<  ":\t sys error : "  << ySysErr[3] << "\t, total err: " <<  yTotErr[3] << endl;
        }   
        Double_t cvINT1_EG2               = 0.;
        if (yValue[0]>0 && yValue[4]>0 ){
            cvINT1_EG2 = (corrFracINT1_INT1_EG2*ySysErr[0]*corrFracEG2_INT1_EG2*ySysErr[4])/(yTotErr[0]*yTotErr[4]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[4] <<  ":\t sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
        }   
        Double_t cvINT1_EG1               = 0.;
        if (yValue[0]>0 && yValue[5]>0 ){
            cvINT1_EG1 = (corrFracINT1_INT1_EG1*ySysErr[0]*corrFracEG1_INT1_EG1*ySysErr[5])/(yTotErr[0]*yTotErr[5]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[5] <<  ":\t sys error : "  << ySysErr[5] << "\t, total err: " <<  yTotErr[5] << endl;
        }   
        Double_t cvINT1_INT11            = 0.;
        if (yValue[0]>0 && yValue[6]>0 ){
            cvINT1_INT11 = (corrFracINT1_INT1_INT11*ySysErr[0]*corrFracINT11_INT1_INT11*ySysErr[6])/(yTotErr[0]*yTotErr[6]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[6] <<  ":\t sys error : "  << ySysErr[6] << "\t, total err: " <<  yTotErr[6] << endl;
        }   
        Double_t cvINT1_INT71            = 0.;
        if (yValue[0]>0 && yValue[7]>0 ){
            cvINT1_INT71 = (corrFracINT1_INT1_INT71*ySysErr[0]*corrFracINT71_INT1_INT71*ySysErr[7])/(yTotErr[0]*yTotErr[7]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[7] <<  ":\t sys error : "  << ySysErr[7] << "\t, total err: " <<  yTotErr[7] << endl;
        }   
        Double_t cvINT1_EMC11            = 0.;
        if (yValue[0]>0 && yValue[8]>0 ){
            cvINT1_EMC11 = (corrFracINT1_INT1_EMC11*ySysErr[0]*corrFracEMC11_INT1_EMC11*ySysErr[8])/(yTotErr[0]*yTotErr[8]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[8] <<  ":\t sys error : "  << ySysErr[8] << "\t, total err: " <<  yTotErr[8] << endl;
        }   
        Double_t cvINT1_EMC71            = 0.;
        if (yValue[0]>0 && yValue[9]>0 ){
            cvINT1_EMC71 = (corrFracINT1_INT1_EMC71*ySysErr[0]*corrFracEMC71_INT1_EMC71*ySysErr[9])/(yTotErr[0]*yTotErr[9]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[9] <<  ":\t sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
        }   
        Double_t cvINT1_EG21            = 0.;
        if (yValue[0]>0 && yValue[10]>0 ){
            cvINT1_EG21 = (corrFracINT1_INT1_EG21*ySysErr[0]*corrFracEG21_INT1_EG21*ySysErr[10])/(yTotErr[0]*yTotErr[10]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[10] <<  ":\t sys error : "  << ySysErr[10] << "\t, total err: " <<  yTotErr[10] << endl;
        }   
        Double_t cvINT1_EG11            = 0.;
        if (yValue[0]>0 && yValue[11]>0 ){
            cvINT1_EG11 = (corrFracINT1_INT1_EG11*ySysErr[0]*corrFracEG11_INT1_EG11*ySysErr[11])/(yTotErr[0]*yTotErr[11]);
            cout << nameMeas[0] <<  ":\t sys error : "  << ySysErr[0] << "\t, total err: " <<  yTotErr[0] << endl;
            cout << nameMeas[11] <<  ":\t sys error : "  << ySysErr[11] << "\t, total err: " <<  yTotErr[11] << endl;
        }   
        
        // correlation factors for INT7
        Double_t cvINT7_EMC1            = 0.;
        if (yValue[1]>0 && yValue[2]>0 ){
            cvINT7_EMC1 = (corrFracINT7_INT7_EMC1*ySysErr[1]*corrFracEMC1_INT7_EMC1*ySysErr[2])/(yTotErr[1]*yTotErr[2]);
            cout << nameMeas[1] <<  ":\t sys error : "  << ySysErr[1] << "\t, total err: " <<  yTotErr[1] << endl;
            cout << nameMeas[2] <<  ":\t sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
        }   
        Double_t cvINT7_EMC7            = 0.;
        if (yValue[1]>0 && yValue[3]>0 ){
            cvINT7_EMC7 = (corrFracINT7_INT7_EMC7*ySysErr[1]*corrFracEMC7_INT7_EMC7*ySysErr[3])/(yTotErr[1]*yTotErr[3]);
            cout << nameMeas[1] <<  ":\t sys error : "  << ySysErr[1] << "\t, total err: " <<  yTotErr[1] << endl;
            cout << nameMeas[3] <<  ":\t sys error : "  << ySysErr[3] << "\t, total err: " <<  yTotErr[3] << endl;
        }   
        Double_t cvINT7_EG2             = 0.;
        if (yValue[1]>0 && yValue[4]>0 ){
            cvINT7_EG2 = (corrFracINT7_INT7_EG2*ySysErr[1]*corrFracEG2_INT7_EG2*ySysErr[4])/(yTotErr[1]*yTotErr[4]);
            cout << nameMeas[1] <<  ":\t sys error : "  << ySysErr[1] << "\t, total err: " <<  yTotErr[1] << endl;
            cout << nameMeas[4] <<  ":\t sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
        }   
        Double_t cvINT7_EG1             = 0.;
        if (yValue[1]>0 && yValue[5]>0 ){
            cvINT7_EG1 = (corrFracINT7_INT7_EG1*ySysErr[1]*corrFracEG1_INT7_EG1*ySysErr[5])/(yTotErr[1]*yTotErr[5]);
            cout << nameMeas[1] <<  ":\t sys error : "  << ySysErr[1] << "\t, total err: " <<  yTotErr[1] << endl;
            cout << nameMeas[5] <<  ":\t sys error : "  << ySysErr[5] << "\t, total err: " <<  yTotErr[5] << endl;
        }   
        Double_t cvINT7_INT11           = 0.;
        if (yValue[1]>0 && yValue[6]>0 ){
            cvINT7_INT11 = (corrFracINT7_INT7_INT11*ySysErr[1]*corrFracINT11_INT7_INT11*ySysErr[6])/(yTotErr[1]*yTotErr[6]);
            cout << nameMeas[1] <<  ":\t sys error : "  << ySysErr[1] << "\t, total err: " <<  yTotErr[1] << endl;
            cout << nameMeas[6] <<  ":\t sys error : "  << ySysErr[6] << "\t, total err: " <<  yTotErr[6] << endl;
        }   
        Double_t cvINT7_INT71           = 0.;
        if (yValue[1]>0 && yValue[7]>0 ){
            cvINT7_INT71 = (corrFracINT7_INT7_INT71*ySysErr[1]*corrFracINT71_INT7_INT71*ySysErr[7])/(yTotErr[1]*yTotErr[7]);
            cout << nameMeas[1] <<  ":\t sys error : "  << ySysErr[1] << "\t, total err: " <<  yTotErr[1] << endl;
            cout << nameMeas[7] <<  ":\t sys error : "  << ySysErr[7] << "\t, total err: " <<  yTotErr[7] << endl;
        }   
        Double_t cvINT7_EMC11           = 0.;
        if (yValue[1]>0 && yValue[8]>0 ){
            cvINT7_EMC11 = (corrFracINT7_INT7_EMC11*ySysErr[1]*corrFracEMC11_INT7_EMC11*ySysErr[8])/(yTotErr[1]*yTotErr[8]);
            cout << nameMeas[1] <<  ":\t sys error : "  << ySysErr[1] << "\t, total err: " <<  yTotErr[1] << endl;
            cout << nameMeas[8] <<  ":\t sys error : "  << ySysErr[8] << "\t, total err: " <<  yTotErr[8] << endl;
        }   
        Double_t cvINT7_EMC71           = 0.;
        if (yValue[1]>0 && yValue[9]>0 ){
            cvINT7_EMC71 = (corrFracINT7_INT7_EMC71*ySysErr[1]*corrFracEMC71_INT7_EMC71*ySysErr[9])/(yTotErr[1]*yTotErr[9]);
            cout << nameMeas[1] <<  ":\t sys error : "  << ySysErr[1] << "\t, total err: " <<  yTotErr[1] << endl;
            cout << nameMeas[9] <<  ":\t sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
        }   
        Double_t cvINT7_EG21           = 0.;
        if (yValue[1]>0 && yValue[10]>0 ){
            cvINT7_EG21 = (corrFracINT7_INT7_EG21*ySysErr[1]*corrFracEG21_INT7_EG21*ySysErr[10])/(yTotErr[1]*yTotErr[10]);
            cout << nameMeas[1] <<  ":\t sys error : "  << ySysErr[1] << "\t, total err: " <<  yTotErr[1] << endl;
            cout << nameMeas[10] <<  ":\t sys error : "  << ySysErr[10] << "\t, total err: " <<  yTotErr[10] << endl;
        }   
        Double_t cvINT7_EG11           = 0.;
        if (yValue[1]>0 && yValue[11]>0 ){
            cvINT7_EG11 = (corrFracINT7_INT7_EG11*ySysErr[1]*corrFracEG11_INT7_EG11*ySysErr[11])/(yTotErr[1]*yTotErr[11]);
            cout << nameMeas[1] <<  ":\t sys error : "  << ySysErr[1] << "\t, total err: " <<  yTotErr[1] << endl;
            cout << nameMeas[11] <<  ":\t sys error : "  << ySysErr[11] << "\t, total err: " <<  yTotErr[11] << endl;
        }   
        
        // correlation factors for EMC1
        Double_t cvEMC1_EMC7            = 0.;
        if (yValue[2]>0 && yValue[3]>0 ){
            cvEMC1_EMC7 = (corrFracEMC1_EMC1_EMC7*ySysErr[2]*corrFracEMC7_EMC1_EMC7*ySysErr[3])/(yTotErr[2]*yTotErr[3]);
            cout << nameMeas[2] <<  " sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
            cout << nameMeas[3] <<  " sys error : "  << ySysErr[3] << "\t, total err: " <<  yTotErr[3] << endl;
        }   
        Double_t cvEMC1_EG2             = 0.;
        if (yValue[2]>0 && yValue[4]>0 ){
            cvEMC1_EG2 = (corrFracEMC1_EMC1_EG2*ySysErr[2]*corrFracEG2_EMC1_EG2*ySysErr[4])/(yTotErr[2]*yTotErr[4]);
            cout << nameMeas[2] <<  " sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
            cout << nameMeas[4] <<  " sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
        }   
        Double_t cvEMC1_EG1             = 0.;
        if (yValue[2]>0 && yValue[5]>0 ){
            cvEMC1_EG1 = (corrFracEMC1_EMC1_EG1*ySysErr[2]*corrFracEG1_EMC1_EG1*ySysErr[5])/(yTotErr[2]*yTotErr[5]);
            cout << nameMeas[2] <<  " sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
            cout << nameMeas[5] <<  " sys error : "  << ySysErr[5] << "\t, total err: " <<  yTotErr[5] << endl;
        }   
        Double_t cvEMC1_INT11           = 0.;
        if (yValue[2]>0 && yValue[6]>0 ){
            cvEMC1_INT11 = (corrFracEMC1_EMC1_INT11*ySysErr[2]*corrFracINT11_EMC1_INT11*ySysErr[6])/(yTotErr[2]*yTotErr[6]);
            cout << nameMeas[2] <<  " sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
            cout << nameMeas[6] <<  " sys error : "  << ySysErr[6] << "\t, total err: " <<  yTotErr[6] << endl;
        }   
        Double_t cvEMC1_INT71           = 0.;
        if (yValue[2]>0 && yValue[7]>0 ){
            cvEMC1_INT71 = (corrFracEMC1_EMC1_INT71*ySysErr[2]*corrFracINT71_EMC1_INT71*ySysErr[7])/(yTotErr[2]*yTotErr[7]);
            cout << nameMeas[2] <<  " sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
            cout << nameMeas[7] <<  " sys error : "  << ySysErr[7] << "\t, total err: " <<  yTotErr[7] << endl;
        }   
        Double_t cvEMC1_EMC11           = 0.;
        if (yValue[2]>0 && yValue[8]>0 ){
            cvEMC1_EMC11 = (corrFracEMC1_EMC1_EMC11*ySysErr[2]*corrFracEMC11_EMC1_EMC11*ySysErr[8])/(yTotErr[2]*yTotErr[8]);
            cout << nameMeas[2] <<  " sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
            cout << nameMeas[8] <<  " sys error : "  << ySysErr[8] << "\t, total err: " <<  yTotErr[8] << endl;
        }           
        Double_t cvEMC1_EMC71           = 0.;
        if (yValue[2]>0 && yValue[9]>0 ){
            cvEMC1_EMC71 = (corrFracEMC1_EMC1_EMC71*ySysErr[2]*corrFracEMC71_EMC1_EMC71*ySysErr[9])/(yTotErr[2]*yTotErr[9]);
            cout << nameMeas[2] <<  " sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
            cout << nameMeas[9] <<  " sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
        }   
        Double_t cvEMC1_EG21           = 0.;
        if (yValue[2]>0 && yValue[10]>0 ){
            cvEMC1_EG21 = (corrFracEMC1_EMC1_EG21*ySysErr[2]*corrFracEG21_EMC1_EG21*ySysErr[10])/(yTotErr[2]*yTotErr[10]);
            cout << nameMeas[2] <<  " sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
            cout << nameMeas[10] <<  " sys error : "  << ySysErr[10] << "\t, total err: " <<  yTotErr[10] << endl;
        }   
        Double_t cvEMC1_EG11           = 0.;
        if (yValue[2]>0 && yValue[11]>0 ){
            cvEMC1_EG11 = (corrFracEMC1_EMC1_EG11*ySysErr[2]*corrFracEG11_EMC1_EG11*ySysErr[11])/(yTotErr[2]*yTotErr[11]);
            cout << nameMeas[2] <<  " sys error : "  << ySysErr[2] << "\t, total err: " <<  yTotErr[2] << endl;
            cout << nameMeas[11] <<  " sys error : "  << ySysErr[11] << "\t, total err: " <<  yTotErr[11] << endl;
        }   
        
        // correlation factors for EMC7
        Double_t cvEMC7_EG2             = 0.;
        if (yValue[3]>0 && yValue[4]>0 ){
            cvEMC7_EG2 = (corrFracEMC7_EMC7_EG2*ySysErr[3]*corrFracEG2_EMC7_EG2*ySysErr[4])/(yTotErr[3]*yTotErr[4]);
            cout << nameMeas[3] <<  " sys error : "  << ySysErr[3] << "\t, total err: " <<  yTotErr[3] << endl;
            cout << nameMeas[4] <<  " sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
        }   
        Double_t cvEMC7_EG1             = 0.;
        if (yValue[3]>0 && yValue[5]>0 ){
            cvEMC7_EG1 = (corrFracEMC7_EMC7_EG1*ySysErr[3]*corrFracEG1_EMC7_EG1*ySysErr[5])/(yTotErr[3]*yTotErr[5]);
            cout << nameMeas[3] <<  " sys error : "  << ySysErr[3] << "\t, total err: " <<  yTotErr[3] << endl;
            cout << nameMeas[5] <<  " sys error : "  << ySysErr[5] << "\t, total err: " <<  yTotErr[5] << endl;
        }   
        Double_t cvEMC7_INT11             = 0.;
        if (yValue[3]>0 && yValue[6]>0 ){
            cvEMC7_INT11 = (corrFracEMC7_EMC7_INT11*ySysErr[3]*corrFracINT11_EMC7_INT11*ySysErr[6])/(yTotErr[3]*yTotErr[6]);
            cout << nameMeas[3] <<  " sys error : "  << ySysErr[3] << "\t, total err: " <<  yTotErr[3] << endl;
            cout << nameMeas[6] <<  " sys error : "  << ySysErr[6] << "\t, total err: " <<  yTotErr[6] << endl;
        }   
        Double_t cvEMC7_INT71             = 0.;
        if (yValue[3]>0 && yValue[7]>0 ){
            cvEMC7_INT71 = (corrFracEMC7_EMC7_INT71*ySysErr[3]*corrFracINT71_EMC7_INT71*ySysErr[7])/(yTotErr[3]*yTotErr[7]);
            cout << nameMeas[3] <<  " sys error : "  << ySysErr[3] << "\t, total err: " <<  yTotErr[3] << endl;
            cout << nameMeas[7] <<  " sys error : "  << ySysErr[7] << "\t, total err: " <<  yTotErr[7] << endl;
        }   
        Double_t cvEMC7_EMC11             = 0.;
        if (yValue[3]>0 && yValue[8]>0 ){
            cvEMC7_EMC11 = (corrFracEMC7_EMC7_EMC11*ySysErr[3]*corrFracEMC11_EMC7_EMC11*ySysErr[8])/(yTotErr[3]*yTotErr[8]);
            cout << nameMeas[3] <<  " sys error : "  << ySysErr[3] << "\t, total err: " <<  yTotErr[3] << endl;
            cout << nameMeas[8] <<  " sys error : "  << ySysErr[8] << "\t, total err: " <<  yTotErr[8] << endl;
        }   
        Double_t cvEMC7_EMC71             = 0.;
        if (yValue[3]>0 && yValue[9]>0 ){
            cvEMC7_EMC71 = (corrFracEMC7_EMC7_EMC71*ySysErr[3]*corrFracEMC71_EMC7_EMC71*ySysErr[9])/(yTotErr[3]*yTotErr[9]);
            cout << nameMeas[3] <<  " sys error : "  << ySysErr[3] << "\t, total err: " <<  yTotErr[3] << endl;
            cout << nameMeas[9] <<  " sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
        }   
        Double_t cvEMC7_EG21             = 0.;
        if (yValue[3]>0 && yValue[10]>0 ){
            cvEMC7_EG21 = (corrFracEMC7_EMC7_EG21*ySysErr[3]*corrFracEG21_EMC7_EG21*ySysErr[10])/(yTotErr[3]*yTotErr[10]);
            cout << nameMeas[3] <<  " sys error : "  << ySysErr[3] << "\t, total err: " <<  yTotErr[3] << endl;
            cout << nameMeas[10] <<  " sys error : "  << ySysErr[10] << "\t, total err: " <<  yTotErr[10] << endl;
        }   
        Double_t cvEMC7_EG11             = 0.;
        if (yValue[3]>0 && yValue[11]>0 ){
            cvEMC7_EG11 = (corrFracEMC7_EMC7_EG11*ySysErr[3]*corrFracEG11_EMC7_EG11*ySysErr[11])/(yTotErr[3]*yTotErr[11]);
            cout << nameMeas[3] <<  " sys error : "  << ySysErr[3] << "\t, total err: " <<  yTotErr[3] << endl;
            cout << nameMeas[11] <<  " sys error : "  << ySysErr[11] << "\t, total err: " <<  yTotErr[11] << endl;
        }   
        
        // correlation factors for EG2
        Double_t cvEG2_EG1              = 0.;
        if (yValue[4]>0 && yValue[5]>0 ){
            cvEG2_EG1 = (corrFracEG2_EG2_EG1*ySysErr[4]*corrFracEG1_EG2_EG1*ySysErr[5])/(yTotErr[4]*yTotErr[5]);
            cout << nameMeas[4] <<  " sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
            cout << nameMeas[5] <<  " sys error : "  << ySysErr[5] << "\t, total err: " <<  yTotErr[5] << endl;
        }   
        Double_t cvEG2_INT11              = 0.;
        if (yValue[4]>0 && yValue[6]>0 ){
            cvEG2_INT11 = (corrFracEG2_EG2_INT11*ySysErr[4]*corrFracINT11_EG2_INT11*ySysErr[6])/(yTotErr[4]*yTotErr[6]);
            cout << nameMeas[4] <<  " sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
            cout << nameMeas[6] <<  " sys error : "  << ySysErr[6] << "\t, total err: " <<  yTotErr[6] << endl;
        }   
        Double_t cvEG2_INT71              = 0.;
        if (yValue[4]>0 && yValue[7]>0 ){
            cvEG2_INT71 = (corrFracEG2_EG2_INT71*ySysErr[4]*corrFracINT71_EG2_INT71*ySysErr[7])/(yTotErr[4]*yTotErr[7]);
            cout << nameMeas[4] <<  " sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
            cout << nameMeas[7] <<  " sys error : "  << ySysErr[7] << "\t, total err: " <<  yTotErr[7] << endl;
        }   
        Double_t cvEG2_EMC11              = 0.;
        if (yValue[4]>0 && yValue[8]>0 ){
            cvEG2_EMC11 = (corrFracEG2_EG2_EMC11*ySysErr[4]*corrFracEMC11_EG2_EMC11*ySysErr[8])/(yTotErr[4]*yTotErr[8]);
            cout << nameMeas[4] <<  " sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
            cout << nameMeas[8] <<  " sys error : "  << ySysErr[8] << "\t, total err: " <<  yTotErr[8] << endl;
        }   
        Double_t cvEG2_EMC71              = 0.;
        if (yValue[4]>0 && yValue[9]>0 ){
            cvEG2_EMC71 = (corrFracEG2_EG2_EMC71*ySysErr[4]*corrFracEMC71_EG2_EMC71*ySysErr[9])/(yTotErr[4]*yTotErr[9]);
            cout << nameMeas[4] <<  " sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
            cout << nameMeas[9] <<  " sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
        }   
        Double_t cvEG2_EG21              = 0.;
        if (yValue[4]>0 && yValue[10]>0 ){
            cvEG2_EG21 = (corrFracEG2_EG2_EG21*ySysErr[4]*corrFracEG21_EG2_EG21*ySysErr[10])/(yTotErr[4]*yTotErr[10]);
            cout << nameMeas[4] <<  " sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
            cout << nameMeas[10] <<  " sys error : "  << ySysErr[10] << "\t, total err: " <<  yTotErr[10] << endl;
        }   
        Double_t cvEG2_EG11              = 0.;
        if (yValue[4]>0 && yValue[11]>0 ){
            cvEG2_EG11 = (corrFracEG2_EG2_EG11*ySysErr[4]*corrFracEG11_EG2_EG11*ySysErr[11])/(yTotErr[4]*yTotErr[11]);
            cout << nameMeas[4] <<  " sys error : "  << ySysErr[4] << "\t, total err: " <<  yTotErr[4] << endl;
            cout << nameMeas[11] <<  " sys error : "  << ySysErr[11] << "\t, total err: " <<  yTotErr[11] << endl;
        }   

        // correlation factors for EG1
        Double_t cvEG1_INT11              = 0.;
        if (yValue[5]>0 && yValue[6]>0 ){
            cvEG1_INT11 = (corrFracEG1_EG1_INT11*ySysErr[5]*corrFracINT11_EG1_INT11*ySysErr[6])/(yTotErr[5]*yTotErr[6]);
            cout << nameMeas[5] <<  " sys error : "  << ySysErr[5] << "\t, total err: " <<  yTotErr[5] << endl;
            cout << nameMeas[6] <<  " sys error : "  << ySysErr[6] << "\t, total err: " <<  yTotErr[6] << endl;
        }   
        Double_t cvEG1_INT71              = 0.;
        if (yValue[5]>0 && yValue[7]>0 ){
            cvEG1_INT71 = (corrFracEG1_EG1_INT71*ySysErr[5]*corrFracINT71_EG1_INT71*ySysErr[7])/(yTotErr[5]*yTotErr[7]);
            cout << nameMeas[5] <<  " sys error : "  << ySysErr[5] << "\t, total err: " <<  yTotErr[5] << endl;
            cout << nameMeas[7] <<  " sys error : "  << ySysErr[7] << "\t, total err: " <<  yTotErr[7] << endl;
        }   
        Double_t cvEG1_EMC11              = 0.;
        if (yValue[5]>0 && yValue[8]>0 ){
            cvEG1_EMC11 = (corrFracEG1_EG1_EMC11*ySysErr[5]*corrFracEMC11_EG1_EMC11*ySysErr[8])/(yTotErr[5]*yTotErr[8]);
            cout << nameMeas[5] <<  " sys error : "  << ySysErr[5] << "\t, total err: " <<  yTotErr[5] << endl;
            cout << nameMeas[8] <<  " sys error : "  << ySysErr[8] << "\t, total err: " <<  yTotErr[8] << endl;
        }   
        Double_t cvEG1_EMC71              = 0.;
        if (yValue[5]>0 && yValue[9]>0 ){
            cvEG1_EMC71 = (corrFracEG1_EG1_EMC71*ySysErr[5]*corrFracEMC71_EG1_EMC71*ySysErr[9])/(yTotErr[5]*yTotErr[9]);
            cout << nameMeas[5] <<  " sys error : "  << ySysErr[5] << "\t, total err: " <<  yTotErr[5] << endl;
            cout << nameMeas[9] <<  " sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
        }   
        Double_t cvEG1_EG21              = 0.;
        if (yValue[5]>0 && yValue[10]>0 ){
            cvEG1_EG21 = (corrFracEG1_EG1_EG21*ySysErr[5]*corrFracEG21_EG1_EG21*ySysErr[10])/(yTotErr[5]*yTotErr[10]);
            cout << nameMeas[5] <<  " sys error : "  << ySysErr[5] << "\t, total err: " <<  yTotErr[5] << endl;
            cout << nameMeas[10] <<  " sys error : "  << ySysErr[10] << "\t, total err: " <<  yTotErr[10] << endl;
        }   
        Double_t cvEG1_EG11              = 0.;
        if (yValue[5]>0 && yValue[11]>0 ){
            cvEG1_EG11 = (corrFracEG1_EG1_EG11*ySysErr[5]*corrFracEG11_EG1_EG11*ySysErr[11])/(yTotErr[5]*yTotErr[11]);
            cout << nameMeas[5] <<  " sys error : "  << ySysErr[5] << "\t, total err: " <<  yTotErr[5] << endl;
            cout << nameMeas[11] <<  " sys error : "  << ySysErr[11] << "\t, total err: " <<  yTotErr[11] << endl;
        }   

        // correlation factors for INT1_NLM1
        Double_t cvINT11_INT71              = 0.;
        if (yValue[6]>0 && yValue[7]>0 ){
            cvINT11_INT71 = (corrFracINT11_INT11_INT71*ySysErr[6]*corrFracINT71_INT11_INT71*ySysErr[7])/(yTotErr[6]*yTotErr[7]);
            cout << nameMeas[6] <<  " sys error : "  << ySysErr[6] << "\t, total err: " <<  yTotErr[6] << endl;
            cout << nameMeas[7] <<  " sys error : "  << ySysErr[7] << "\t, total err: " <<  yTotErr[7] << endl;
        }   
        Double_t cvINT11_EMC11              = 0.;
        if (yValue[6]>0 && yValue[8]>0 ){
            cvINT11_EMC11 = (corrFracINT11_INT11_EMC11*ySysErr[6]*corrFracEMC11_INT11_EMC11*ySysErr[8])/(yTotErr[6]*yTotErr[8]);
            cout << nameMeas[6] <<  " sys error : "  << ySysErr[6] << "\t, total err: " <<  yTotErr[6] << endl;
            cout << nameMeas[8] <<  " sys error : "  << ySysErr[8] << "\t, total err: " <<  yTotErr[8] << endl;
        }   
        Double_t cvINT11_EMC71              = 0.;
        if (yValue[6]>0 && yValue[9]>0 ){
            cvINT11_EMC71 = (corrFracINT11_INT11_EMC71*ySysErr[6]*corrFracEMC71_INT11_EMC71*ySysErr[9])/(yTotErr[6]*yTotErr[9]);
            cout << nameMeas[6] <<  " sys error : "  << ySysErr[6] << "\t, total err: " <<  yTotErr[6] << endl;
            cout << nameMeas[9] <<  " sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
        }   
        Double_t cvINT11_EG21              = 0.;
        if (yValue[6]>0 && yValue[10]>0 ){
            cvINT11_EG21 = (corrFracINT11_INT11_EG21*ySysErr[6]*corrFracEG21_INT11_EG21*ySysErr[10])/(yTotErr[6]*yTotErr[10]);
            cout << nameMeas[6] <<  " sys error : "  << ySysErr[6] << "\t, total err: " <<  yTotErr[6] << endl;
            cout << nameMeas[10] <<  " sys error : "  << ySysErr[10] << "\t, total err: " <<  yTotErr[10] << endl;
        }   
        Double_t cvINT11_EG11              = 0.;
        if (yValue[6]>0 && yValue[11]>0 ){
            cvINT11_EG11 = (corrFracINT11_INT11_EG11*ySysErr[6]*corrFracEG11_INT11_EG11*ySysErr[11])/(yTotErr[6]*yTotErr[11]);
            cout << nameMeas[6] <<  " sys error : "  << ySysErr[6] << "\t, total err: " <<  yTotErr[6] << endl;
            cout << nameMeas[11] <<  " sys error : "  << ySysErr[11] << "\t, total err: " <<  yTotErr[11] << endl;
        }   

        // correlation factors for INT7_NLM1
        Double_t cvINT71_EMC11              = 0.;
        if (yValue[7]>0 && yValue[8]>0 ){
            cvINT71_EMC11 = (corrFracINT71_INT71_EMC11*ySysErr[7]*corrFracEMC11_INT71_EMC11*ySysErr[8])/(yTotErr[7]*yTotErr[8]);
            cout << nameMeas[7] <<  " sys error : "  << ySysErr[7] << "\t, total err: " <<  yTotErr[7] << endl;
            cout << nameMeas[8] <<  " sys error : "  << ySysErr[8] << "\t, total err: " <<  yTotErr[8] << endl;
        }   
        Double_t cvINT71_EMC71              = 0.;
        if (yValue[7]>0 && yValue[9]>0 ){
            cvINT71_EMC71 = (corrFracINT71_INT71_EMC71*ySysErr[7]*corrFracEMC71_INT71_EMC71*ySysErr[9])/(yTotErr[7]*yTotErr[9]);
            cout << nameMeas[7] <<  " sys error : "  << ySysErr[7] << "\t, total err: " <<  yTotErr[7] << endl;
            cout << nameMeas[9] <<  " sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
        }   
        Double_t cvINT71_EG21              = 0.;
        if (yValue[7]>0 && yValue[10]>0 ){
            cvINT71_EG21 = (corrFracINT71_INT71_EG21*ySysErr[7]*corrFracEG21_INT71_EG21*ySysErr[10])/(yTotErr[7]*yTotErr[10]);
            cout << nameMeas[7] <<  " sys error : "  << ySysErr[7] << "\t, total err: " <<  yTotErr[7] << endl;
            cout << nameMeas[10] <<  " sys error : "  << ySysErr[10] << "\t, total err: " <<  yTotErr[10] << endl;
        }   
        Double_t cvINT71_EG11              = 0.;
        if (yValue[7]>0 && yValue[11]>0 ){
            cvINT71_EG11 = (corrFracINT71_INT71_EG11*ySysErr[7]*corrFracEG11_INT71_EG11*ySysErr[11])/(yTotErr[7]*yTotErr[11]);
            cout << nameMeas[7] <<  " sys error : "  << ySysErr[7] << "\t, total err: " <<  yTotErr[7] << endl;
            cout << nameMeas[11] <<  " sys error : "  << ySysErr[11] << "\t, total err: " <<  yTotErr[11] << endl;
        }   

        // correlation factors for EMC1_NLM1
        Double_t cvEMC11_EMC71              = 0.;
        if (yValue[8]>0 && yValue[9]>0 ){
            cvEMC11_EMC71 = (corrFracEMC11_EMC11_EMC71*ySysErr[8]*corrFracEMC71_EMC11_EMC71*ySysErr[9])/(yTotErr[8]*yTotErr[9]);
            cout << nameMeas[8] <<  " sys error : "  << ySysErr[8] << "\t, total err: " <<  yTotErr[8] << endl;
            cout << nameMeas[9] <<  " sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
        }   
        Double_t cvEMC11_EG21              = 0.;
        if (yValue[8]>0 && yValue[10]>0 ){
            cvEMC11_EG21 = (corrFracEMC11_EMC11_EG21*ySysErr[8]*corrFracEG21_EMC11_EG21*ySysErr[10])/(yTotErr[8]*yTotErr[10]);
            cout << nameMeas[8] <<  " sys error : "  << ySysErr[8] << "\t, total err: " <<  yTotErr[8] << endl;
            cout << nameMeas[10] <<  " sys error : "  << ySysErr[10] << "\t, total err: " <<  yTotErr[10] << endl;
        }   
        Double_t cvEMC11_EG11              = 0.;
        if (yValue[8]>0 && yValue[11]>0 ){
            cvEMC11_EG11 = (corrFracEMC11_EMC11_EG11*ySysErr[8]*corrFracEG11_EMC11_EG11*ySysErr[11])/(yTotErr[8]*yTotErr[11]);
            cout << nameMeas[8] <<  " sys error : "  << ySysErr[8] << "\t, total err: " <<  yTotErr[8] << endl;
            cout << nameMeas[11] <<  " sys error : "  << ySysErr[11] << "\t, total err: " <<  yTotErr[11] << endl;
        }   
    
        // correlation factors for EMC7_NLM1
        Double_t cvEMC71_EG21              = 0.;
        if (yValue[9]>0 && yValue[10]>0 ){
            cvEMC71_EG21 = (corrFracEMC71_EMC71_EG21*ySysErr[9]*corrFracEG21_EMC71_EG21*ySysErr[10])/(yTotErr[9]*yTotErr[10]);
            cout << nameMeas[9] <<  " sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
            cout << nameMeas[10] <<  " sys error : "  << ySysErr[10] << "\t, total err: " <<  yTotErr[10] << endl;
        }   
        Double_t cvEMC71_EG11              = 0.;
        if (yValue[9]>0 && yValue[11]>0 ){
            cvEMC71_EG11 = (corrFracEMC71_EMC71_EG11*ySysErr[9]*corrFracEG11_EMC71_EG11*ySysErr[11])/(yTotErr[9]*yTotErr[11]);
            cout << nameMeas[9] <<  " sys error : "  << ySysErr[9] << "\t, total err: " <<  yTotErr[9] << endl;
            cout << nameMeas[11] <<  " sys error : "  << ySysErr[11] << "\t, total err: " <<  yTotErr[11] << endl;
        }   

        // correlation factors for EG2_NLM1   
        Double_t cvEG21_EG11              = 0.;
        if (yValue[10]>0 && yValue[11]>0 ){
            cvEG21_EG11 = (corrFracEG21_EG21_EG11*ySysErr[10]*corrFracEG11_EG21_EG11*ySysErr[11])/(yTotErr[10]*yTotErr[11]);
            cout << nameMeas[10] <<  " sys error : "  << ySysErr[10] << "\t, total err: " <<  yTotErr[10] << endl;
            cout << nameMeas[11] <<  " sys error : "  << ySysErr[11] << "\t, total err: " <<  yTotErr[11] << endl;
        }   

                                        //INT1        INT7          EMC1          EMC7          EG2          EG1          INT1_NLM1      INT7_NLM1      EMC1_NLM1      EMC7_NLM1      EG2_NLM1      EG1_NLM1
        Double_t cvMatrix[12][12] = { { 1,            cvINT1_INT7,  cvINT1_EMC1,  cvINT1_EMC7,  cvINT1_EG2,  cvINT1_EG1,  cvINT1_INT11,  cvINT1_INT71,  cvINT1_EMC11,  cvINT1_EMC71,  cvINT1_EG21,  cvINT1_EG11  },
                                      { cvINT1_INT7,  1,            cvINT7_EMC1,  cvINT7_EMC7,  cvINT7_EG2,  cvINT7_EG1,  cvINT7_INT11,  cvINT7_INT71,  cvINT7_EMC11,  cvINT7_EMC71,  cvINT7_EG21,  cvINT7_EG11  },
                                      { cvINT1_EMC1,  cvINT7_EMC1,  1,            cvEMC1_EMC7,  cvEMC1_EG2,  cvEMC1_EG1,  cvEMC1_INT11,  cvEMC1_INT71,  cvEMC1_EMC11,  cvEMC1_EMC71,  cvEMC1_EG21,  cvEMC1_EG11  },
                                      { cvINT1_EMC7,  cvINT7_EMC7,  cvEMC1_EMC7,  1,            cvEMC7_EG2,  cvEMC7_EG1,  cvEMC7_INT11,  cvEMC7_INT71,  cvEMC7_EMC11,  cvEMC7_EMC71,  cvEMC7_EG21,  cvEMC7_EG11  },
                                      { cvINT1_EG2,   cvINT7_EG2,   cvEMC1_EG2,   cvEMC7_EG2,   1,           cvEG2_EG1,   cvEG2_INT11,   cvEG2_INT71,   cvEG2_EMC11,   cvEG2_EMC71,   cvEG2_EG21,   cvEG2_EG11   },
                                      { cvINT1_EG1,   cvINT7_EG1,   cvEMC1_EG1,   cvEMC7_EG1,   cvEG2_EG1,   1,           cvEG1_INT11,   cvEG1_INT71,   cvEG1_EMC11,   cvEG1_EMC71,   cvEG1_EG21,   cvEG1_EG11   },
                                      { cvINT1_INT11, cvINT7_INT11, cvEMC1_INT11, cvEMC7_INT11, cvEG2_INT11, cvEG1_INT11, 1,             cvINT11_INT71, cvINT11_EMC11, cvINT11_EMC71, cvINT11_EG21, cvINT11_EG11 },
                                      { cvINT1_INT71, cvINT7_INT71, cvEMC1_INT71, cvEMC7_INT71, cvEG2_INT71, cvEG1_INT71, cvINT11_INT71, 1,             cvINT71_EMC11, cvINT71_EMC71, cvINT71_EG21, cvINT71_EG11 },
                                      { cvINT1_EMC11, cvINT7_EMC11, cvEMC1_EMC11, cvEMC7_EMC11, cvEG2_EMC11, cvEG1_EMC11, cvINT11_EMC11, cvINT71_EMC11, 1,             cvEMC11_EMC71, cvEMC11_EG21, cvEMC11_EG11 },
                                      { cvINT1_EMC71, cvINT7_EMC71, cvEMC1_EMC71, cvEMC7_EMC71, cvEG2_EMC71, cvEG1_EMC71, cvINT11_EMC71, cvINT71_EMC71, cvEMC11_EMC71, 1,             cvEMC71_EG21, cvEMC71_EG11 }, 
                                      { cvINT1_EG21,  cvINT7_EG21,  cvEMC1_EG21,  cvEMC7_EG21,  cvEG2_EG21,  cvEG1_EG21,  cvINT11_EG21,  cvINT71_EG21,  cvEMC11_EG21,  cvEMC71_EG21,  1,            cvEG21_EG11  },
                                      { cvINT1_EG11,  cvINT7_EG11,  cvEMC1_EG11,  cvEMC7_EG11,  cvEG2_EG11,  cvEG1_EG11,  cvINT11_EG11,  cvINT71_EG11,  cvEMC11_EG11,  cvEMC71_EG11,  cvEG21_EG11,  1            }
                                    };
        
        Double_t cvMatrixCurrPtBin[12][12] = {  {   1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
                                                {   0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
                                                {   0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
                                                {   0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0 },
                                                {   0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0 },
                                                {   0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0 },
                                                {   0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0 },
                                                {   0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0 },
                                                {   0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0 },
                                                {   0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0 },
                                                {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0 },
                                                {   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1 } };
        
        Double_t weightArray[12]        = { 0, 0, 0, 0, 0, 0, 
                                            0, 0, 0, 0, 0, 0}; 
        Double_t fullSumOfWeights       = 0;
        for (Int_t meas = 0; meas < maxNMeasurements; meas++){
            cout << "identity: " << identCurr[0][meas] << " <- " << identCurr[1][meas] << endl;
        }   
        cout << "**************************************************************************" << endl;   
        if (numberOfMeasInPtBin>1){
            cout << "need to do more complicated stuff"<< endl;
            TMatrixD weightingMatrix(numberOfMeasInPtBin, numberOfMeasInPtBin);
            weightingMatrix.SetTol(1.E-23);
            TArrayD arrayToFillMatrix(numberOfMeasInPtBin*numberOfMeasInPtBin);
            for (Int_t nCurrMeas = 0; nCurrMeas < numberOfMeasInPtBin; nCurrMeas++){
                for (Int_t nCurrMeas2 = 0; nCurrMeas2 < numberOfMeasInPtBin; nCurrMeas2++){
                    cout << cvMatrix[identCurr[1][nCurrMeas]][identCurr[1][nCurrMeas2]] << "*" << yTotErr[identCurr[1][nCurrMeas]] << "*"<<yTotErr[identCurr[1][nCurrMeas2]] << "\t" ;
                }
                cout << endl;
            }
            for (Int_t nCurrMeas = 0; nCurrMeas < numberOfMeasInPtBin; nCurrMeas++){
                for (Int_t nCurrMeas2 = 0; nCurrMeas2 < numberOfMeasInPtBin; nCurrMeas2++){
                    cvMatrixCurrPtBin[nCurrMeas][nCurrMeas2] = cvMatrix[identCurr[1][nCurrMeas]][identCurr[1][nCurrMeas2]];
                    cout << cvMatrixCurrPtBin[nCurrMeas][nCurrMeas2] << "\t\t" ;
                    arrayToFillMatrix[nCurrMeas*numberOfMeasInPtBin+nCurrMeas2] = cvMatrixCurrPtBin[nCurrMeas][nCurrMeas2] * yTotErr[identCurr[1][nCurrMeas]] * yTotErr[identCurr[1][nCurrMeas2]];
                }   
                cout << endl;
            }   
            weightingMatrix.SetMatrixArray(arrayToFillMatrix.GetArray());
            weightingMatrix.Print();
            weightingMatrix.Invert();
            cout << "inverted matrix" << endl;
            weightingMatrix.Print();
            cout << "trying to acces inverted matrix" << endl;
            for (Int_t nCurrMeas = 0; nCurrMeas < numberOfMeasInPtBin; nCurrMeas++){
                for (Int_t nCurrMeas2 = 0; nCurrMeas2 < numberOfMeasInPtBin; nCurrMeas2++){
                    fullSumOfWeights    = fullSumOfWeights+weightingMatrix[nCurrMeas][nCurrMeas2];
                    cout << weightingMatrix[nCurrMeas][nCurrMeas2] << "\t" ;
                }
                cout << endl;
            }
            cout << "weights for individual measurements" << endl;
            for (Int_t nCurrMeas = 0; nCurrMeas < numberOfMeasInPtBin; nCurrMeas++){
                Double_t partSumOfWeights = 0;
                for (Int_t nCurrMeas2 = 0; nCurrMeas2 < numberOfMeasInPtBin; nCurrMeas2++){
                    partSumOfWeights    = partSumOfWeights+ weightingMatrix[nCurrMeas][nCurrMeas2];
                }   
                weightArray[nCurrMeas]  = partSumOfWeights/fullSumOfWeights;
                cout << weightArray[nCurrMeas] << endl;
            }
            for (Int_t nCurrMeas = 0; nCurrMeas < numberOfMeasInPtBin; nCurrMeas++){
                yValueFinal[ptBin]      = yValueFinal[ptBin]+ weightArray[nCurrMeas]* yValue[identCurr[1][nCurrMeas]];
                yErrStatFinal[ptBin]    = yErrStatFinal[ptBin] + TMath::Power(weightArray[nCurrMeas]* yStatErr[identCurr[1][nCurrMeas]],2);
                finalWeights[identCurr[1][nCurrMeas]][ptBin]    = weightArray[nCurrMeas];
            }   
            yErrStatFinal[ptBin]        = TMath::Sqrt(yErrStatFinal[ptBin]);
            yErrTotFinal[ptBin]         = 1./TMath::Sqrt(fullSumOfWeights);
            yErrSysFinal[ptBin]         = TMath::Sqrt(yErrTotFinal[ptBin]*yErrTotFinal[ptBin] - yErrStatFinal[ptBin]*yErrStatFinal[ptBin]);
            
            cout << "final weighted average: " <<  yValueFinal[ptBin] << " +- " << yErrTotFinal[ptBin] << "( stat: " << yErrStatFinal[ptBin] << " , syst: " << yErrSysFinal[ptBin] << " )"<< endl;
        } else {
            cout << "do simple copy of measurement: " << nameMeasPtBin[0].Data() << endl;   
            yValueFinal[ptBin]          = yValue[identCurr[1][0]];
            yErrStatFinal[ptBin]        = yStatErr[identCurr[1][0]];
            yErrSysFinal[ptBin]         = ySysErr[identCurr[1][0]];
            yErrTotFinal[ptBin]         = yTotErr[identCurr[1][0]];
            finalWeights[identCurr[1][0]][ptBin]                = 1.;
            cout << "final weighted average: " <<  yValueFinal[ptBin] << " +- " << yErrTotFinal[ptBin] << "( stat: " << yErrStatFinal[ptBin] << " , syst: " << yErrSysFinal[ptBin] << " )"<< endl;
        }   
        cout << "__________________________________________________________________________" << endl;   
    }
    graphStatComb                       = new TGraphAsymmErrors(nPtLimits,xValue,yValueFinal,xErr,xErr,yErrStatFinal,yErrStatFinal);
    graphSystComb                       = new TGraphAsymmErrors(nPtLimits,xValue,yValueFinal,xErr,xErr,yErrSysFinal,yErrSysFinal);
    TGraphAsymmErrors* returnGraph      = new TGraphAsymmErrors(nPtLimits,xValue,yValueFinal,xErr,xErr,yErrTotFinal,yErrTotFinal);
    Int_t b                             = 0;
    while (yValueFinal[b] == 0){
        graphStatComb->RemovePoint(0);
        graphSystComb->RemovePoint(0);
        returnGraph->RemovePoint(0);
        b++;
    }

    fstream  fileWeightsOutput;
    fileWeightsOutput.open(nameWeightsOutputFile.Data(), ios::out);  

    fileWeightsOutput << "pT \t" ;
    for (Int_t i = 0; i < maxNMeasurements; i++){
        if (isPresentGeneral[i]) fileWeightsOutput << i << "\t" ;
    }
    fileWeightsOutput << endl;
    
    for (Int_t ptBin = 0; ptBin < nPtLimits; ptBin++){
        if (yValueFinal[ptBin] > 0){
            fileWeightsOutput << xValue[ptBin] << "\t" ;
            for (Int_t i = 0; i < maxNMeasurements; i++){
                if (isPresentGeneral[i]) fileWeightsOutput << finalWeights[i][ptBin] << "\t" ;
            }
            fileWeightsOutput << endl;
        }   
    }   
    fileWeightsOutput.close();
    return returnGraph;    
}

//*******************************************************************************************
//******* Combination of quantities from i.e. different triggers with given weights *********
//******* Binning has to be the same for weights and graphs, attention they have to *********
//******* follow from some point on binning given in xPtLimits, no wider bins in the ********
//******* beginning, in the end binning doesn't matter any more *****************************
//*******************************************************************************************
//********** ATTENTION: this is no general implementation yet !!!! **************************
//*******************************************************************************************
TGraphAsymmErrors* CalculateWeightedQuantity(   TGraphAsymmErrors** graphs, 
                                                TGraph** weights,
                                                Double_t* xPtLimits,  Int_t nPtLimits,
                                                Int_t maxNMeasurements
                                             ){
    Double_t xValue[nPtLimits];
    Double_t xErr[nPtLimits];
    Double_t values     [nPtLimits];
    Double_t errors     [nPtLimits];
    Int_t offsets       [maxNMeasurements];
    Bool_t available    [maxNMeasurements];
    Bool_t correctBin   [maxNMeasurements];
    
    for (Int_t meas = 0; meas < maxNMeasurements; meas++){
        available[meas]         = kFALSE;
        cout << meas         << endl;
        cout << graphs[meas] << endl;
        cout << weights[meas] << endl;
        if (graphs[meas] && weights[meas]){
            available[meas]     = kTRUE;
            offsets[meas]       = 0;
            correctBin[meas]    = kFALSE;
        
            while (graphs[meas]->GetX()[0] > xPtLimits[offsets[meas]]){
                cout << offsets[meas] << "\t"<< graphs[meas]->GetX()[0] << "\t"<< xPtLimits[offsets[meas]] << endl;
                offsets[meas]++;
            } 
            offsets[meas]--;
            if (abs(graphs[meas]->GetX()[0] - graphs[meas]->GetErrorXlow(0) - xPtLimits[offsets[meas]] ) < 0.000001 &&
                abs(graphs[meas]->GetX()[0] + graphs[meas]->GetErrorXhigh(0) - xPtLimits[offsets[meas]+1] ) < 0.000001 
            )
                correctBin[meas] = kTRUE; 
            cout << "offset measurement  " << meas << " \t:" << offsets[meas] << "\t"<< graphs[meas]->GetX()[0] << "\t"<< correctBin[meas] << "\t"<< xPtLimits[offsets[meas]] 
                 << " - " << xPtLimits[offsets[meas]+1]<< endl;
            cout << "measurement :" << meas << endl;
            graphs[meas]->Print();
            cout << "weights :" << meas << endl;
            weights[meas]->Print();
        }    
    }    
    
    for (Int_t ptBin = 0; ptBin < nPtLimits; ptBin++){
        values[ptBin]   = 0;
        errors[ptBin]   = 0.;
        xValue[ptBin]   = (xPtLimits[ptBin]+xPtLimits[ptBin+1])/2;
        xErr[ptBin]     = xValue[ptBin]- xPtLimits[ptBin];
        Int_t nMeas     = 0;
        for (Int_t meas = 0; meas < maxNMeasurements; meas++){            
            if (graphs[meas] && weights[meas] && !(ptBin < offsets[meas]) ){
                if (   abs(graphs[meas]->GetX()[ptBin-offsets[meas]] - graphs[meas]->GetErrorXlow(ptBin-offsets[meas]) - xPtLimits[ptBin] ) < 0.000001 &&
                        abs(graphs[meas]->GetX()[ptBin-offsets[meas]] + graphs[meas]->GetErrorXhigh(ptBin-offsets[meas]) - xPtLimits[ptBin+1] ) < 0.000001 
                ){
                    cout << meas << "\t" << ptBin-offsets[meas] << endl;
                    cout << graphs[meas]->GetX()[ptBin-offsets[meas]] << "\t"<< graphs[meas]->GetY()[ptBin-offsets[meas]] << "\t" << weights[meas]->GetY()[ptBin-offsets[meas]] << endl;
                    if (TMath::Abs(weights[meas]->GetY()[ptBin-offsets[meas]]) > 1e-5){
                        values[ptBin] += graphs[meas]->GetY()[ptBin-offsets[meas]]*weights[meas]->GetY()[ptBin-offsets[meas]];
                        errors[ptBin] += graphs[meas]->GetErrorYhigh(ptBin-offsets[meas])*weights[meas]->GetY()[ptBin-offsets[meas]];
                        nMeas++;
                    } else {
                        cout << "weight put to 0" << endl;
                    }    
                }    
            }
        }
        if (nMeas == 0) 
            values[ptBin] = -10000;
        cout << values[ptBin] << "+-"<< errors[ptBin] << endl;
    }
    
    TGraphAsymmErrors* graphWeighted = new TGraphAsymmErrors(nPtLimits,xValue,values,xErr,xErr,errors,errors);
    graphWeighted->Print();
    return graphWeighted;
}