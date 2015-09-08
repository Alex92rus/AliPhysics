#ifndef AliAnalysisTaskEMCALPi0V2ShSh_h
#define AliAnalysisTaskEMCALPi0V2ShSh_h

// $Id: AliAnalysisTaskEMCALPi0V2ShSh.h$

class TH1I;
class TH1F;
class TH1D;
class TH2F;
class THnSparse;
class TList;
class TObjArray;
class TProfile;
class AliOADBContainer;
class AliEMCALGeometry;
class AliESDEvent;
class AliESDtrack;
class AliESDCaloCells;
class AliAODEvent;
class AliAODCaloCells;
class AliVCluster;
class AliCentrality;
class AliEPFlattener;

#include "AliAnalysisTaskSE.h"


class AliAnalysisTaskEMCALPi0V2ShSh : public AliAnalysisTaskSE {
 public:
  AliAnalysisTaskEMCALPi0V2ShSh();
  AliAnalysisTaskEMCALPi0V2ShSh(const char *name);
  virtual ~AliAnalysisTaskEMCALPi0V2ShSh() {}

  void                   UserCreateOutputObjects();
  void                   UserExec(Option_t *option);
  void                   Terminate(Option_t *);

  void                   SetEMCALClusterListName(TString &name) {fEMCALClustersListName = name;}

 protected:
  AliEventplane         *fEventPlane;
  Double_t               fCentrality;
  TString                fEMCALClustersListName; //
  TObjArray             *fESDClusters;           //!pointer to EMCal clusters
  TObjArray             *fAODClusters;           //!pointer to EMCal clusters
  AliESDCaloCells       *fESDCells;              //!pointer to EMCal cells, esd
  AliAODCaloCells       *fAODCells;              //!pointer to EMCal cells, aod  
  AliEMCALGeometry      *fGeom;                  // geometry utils
  TString                fGeoName;               // geometry name (def = EMCAL_FIRSTYEARV1)
  AliOADBContainer      *fOADBContainer;         //!OADB container used to load misalignment matrices
  AliOADBContainer      *fFlatContainer;
  
 private:
  void                   FillHistsCluster();
  void                   FillHistsTrack();

  Int_t        GetInternalRunNum(Int_t runnumber);
  Bool_t       IsCentralityDistrCorrected();
  void         VZEROEventPlane(Bool_t isFlatten);
  Double_t     ApplyFlatteningTPC(Double_t phi, Double_t c) ; //Apply centrality-dependent flattening
  Double_t     ApplyFlatteningV0A(Double_t phi, Double_t c) ; //Apply centrality-dependent flattening
  Double_t     ApplyFlatteningV0C(Double_t phi, Double_t c) ; //Apply centrality-dependent flattening

  Bool_t       IsGoodClusterV1(const AliVCluster *c) const;
  Double_t     GetMaxCellEnergy(const AliVCluster *cluster, Short_t &id) const;
  Bool_t       IsWithinFiducialVolume(Short_t id) const;
  Double_t     GetCrossEnergy(const AliVCluster *cluster, Short_t &idmax) const;
  Bool_t       IsGoodPi0(const AliVCluster *c);

  AliESDEvent *fESD;                 //! ESD object
  AliAODEvent *fAOD;                 //! AOD object
  TList       *fOutputList;          //! General Output list
  TGeoHMatrix *fGeomMatrix[12];      //! Geometry misalignment matrices for EMCal

  AliEPFlattener  *fTPCFlat;    //! Object for flattening of TPC
  AliEPFlattener  *fV0AFlat;    //! Object for flattening of V0A
  AliEPFlattener  *fV0CFlat;    //! Object for flattening of V0C

  Int_t       fRunNumber;
  Int_t       fInternalRunNum;
  Double_t    fEPTPC;
  Double_t    fEPTPCResolution;
  Double_t    fEPV0;
  Double_t    fEPV0A;
  Double_t    fEPV0C;
  Double_t    fEPV0AR;
  Double_t    fEPV0CR;
  Double_t    fEPV0R;
  Double_t    fEPV0AR4;
  Double_t    fEPV0AR5;
  Double_t    fEPV0AR6;
  Double_t    fEPV0AR7;
  Double_t    fEPV0CR0;
  Double_t    fEPV0CR1;
  Double_t    fEPV0CR2;
  Double_t    fEPV0CR3;

  // histograms
  TH1I        *fHistEvtStat;
  TH1I        *fHistClusterStat;
  TH1I        *fHistRunNumStat;
  TH1D        *fHistCentrality;
  TH1D        *fHistCentralityCorrected;

  TH1F        *fHistEPV0MB;
  TH1F        *fHistEPV0RMB;
  TH1F        *fHistEPV0AMB;
  TH1F        *fHistEPV0CMB;
  TH1F        *fHistEPTPCMB;

  TH2F        *fHistEPTPC;
  TH2F        *fHistEPTPCResolution;
  TH2F        *fHistEPV0;
  TH2F        *fHistEPV0A;
  TH2F        *fHistEPV0C;
  TH2F        *fHistEPV0AR;
  TH2F        *fHistEPV0CR;
  TH2F        *fHistEPV0R;
  TH2F        *fHistEPV0AR4;
  TH2F        *fHistEPV0AR7;
  TH2F        *fHistEPV0CR0;
  TH2F        *fHistEPV0CR3;

  TH2F        *fHistEPTPCFlatten;
  TH2F        *fHistEPV0AFlatten;
  TH2F        *fHistEPV0CFlatten;

  TH2F        *fHistDiffV0A_V0CR0;
  TH2F        *fHistDiffV0A_V0CR3;
  TH2F        *fHistDiffV0CR0_V0CR3;
  TH2F        *fHistDiffV0C_V0AR4;
  TH2F        *fHistDiffV0C_V0AR7;
  TH2F        *fHistDiffV0AR4_V0AR7;
  TH2F        *fHistDiffV0AR_V0CR;

  TProfile    *fHistRBRCosV0A;
  TProfile    *fHistRBRSinV0A;
  TProfile    *fHistRBRCosV0C;
  TProfile    *fHistRBRSinV0C;
  TProfile    *fHistRBRCosTPC;
  TProfile    *fHistRBRSinTPC;

  TH1F        *fHistClusterEta;
  TH1F        *fHistClusterPhi;
  TH1F        *fHistClusterE;
  TH1F        *fHistClusterEt;
  TH1F        *fHistClusterN;
  TH1F        *fHistClusterM02;
  TH2F        *fHistClusterEN;
  TH2F        *fHistClusterEM02;
  TH2F        *fHistClusterPhiEta;
  TH2F	      *fHistClusterEtN;
  TH2F        *fHistClusterEtM02;
  TH1D        *fHistClusterdphiV0;

  TH1F        *fHistTrackPt;
  TH1F        *fHistTrackEta;
  TH1F        *fHistTrackPhi;
  TH2F        *fHistTrackPhiEta;

  THnSparse   *fClusterV0;
  THnSparse   *fClusterV0A;
  THnSparse   *fClusterV0C;
  THnSparse   *fClusterTPC;

  AliAnalysisTaskEMCALPi0V2ShSh(const AliAnalysisTaskEMCALPi0V2ShSh&); // not implemented
  AliAnalysisTaskEMCALPi0V2ShSh& operator=(const AliAnalysisTaskEMCALPi0V2ShSh&); // not implemented
  
  ClassDef(AliAnalysisTaskEMCALPi0V2ShSh, 1);
};
#endif
