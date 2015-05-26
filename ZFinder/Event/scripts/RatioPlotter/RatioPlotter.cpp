// Standard Library
#include <stdexcept>
#include <iostream>
#include <sstream>

// ROOT
#include <TFile.h>
#include <TBranch.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLeaf.h>

#include <TTree.h>
#include "TSystem.h"


#include <set>
#include <TDirectory.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH2.h>
#include "TLine.h"
#include <TStyle.h>

using namespace std; // yeah I am evil, get over it
bool scaleFactor=false;

TTree* GetTTree(const std::string TFILE, const std::string TTREE) {
    // Open the TFiles
    TFile* mc_tfile = new TFile(TFILE.c_str(), "READ");
    if (!mc_tfile || mc_tfile->IsZombie()) {
        const std::string ERR = "Could not open the file " + TFILE;
        throw std::runtime_error(ERR);
    }

    // Load the tree
    TTree* tree = new TTree();
    mc_tfile->GetObject(TTREE.c_str(), tree);
    if (!tree || tree->IsZombie()) {
        const std::string ERR = "Could not open the TTree " + TTREE;
        throw std::runtime_error(ERR);
    }

    return tree;
}

TH1* FillHisto(const TH1* Denominator, const string TreeNumerator, TH2* ScaleFactorDouble8, TH2* ScaleFactorDouble17, TH2* ScaleFactorGSF) {
    const string file_name = "/data/whybee0a/user/lesko_2/fermi/Output/ZfinderMC30-20pt-15-5-20/Madgraph15-5-20.root";
    //TFile* theFile = new TFile(file_name.c_str());
    TH1* Numerator = (TH1F*) Denominator->Clone("NEW");
    for (int i = 1; i <= Denominator->GetNbinsX(); i++) {
        Numerator->SetBinContent(i, 0);
    }
    const string BranchLoc = "reco";

    TTree* NumTree = GetTTree(file_name, TreeNumerator); //denominator tree

    TBranch* RecoEvent = NumTree->GetBranch("reco"); //now Getting denominator stuff
    TLeaf* phistar = RecoEvent->GetLeaf("z_phistar_dressed");
    TLeaf* t0Tight = RecoEvent->GetLeaf("t0tight");
    TLeaf* e0Eta = RecoEvent->GetLeaf("e_eta0");
    TLeaf* e0Pt = RecoEvent->GetLeaf("e_pt0");
    TLeaf* t1Tight = RecoEvent->GetLeaf("t1tight");
    TLeaf* e1Eta = RecoEvent->GetLeaf("e_eta1");
    TLeaf* e1Pt = RecoEvent->GetLeaf("e_pt1");

    for (int i = 0; i < NumTree->GetEntries(); i++) {//grabbing numinator stuff
        if (!(i % 50000))cout << " still going :" << i << endl;
        NumTree->GetEntry(i);
        Int_t Bin = -1;
        double Weight1 = -1;
        double Weight2 = -1;
        double TotalWeight=-1;
        if(t0Tight->GetValue())
        {
          Bin=ScaleFactorDouble8->FindBin(e0Pt->GetValue(),fabs(e0Eta->GetValue()));
          Weight1=ScaleFactorDouble8->GetBinContent(Bin);
          Bin=ScaleFactorDouble17->FindBin(e1Pt->GetValue(),fabs(e1Eta->GetValue()));
          Weight2=ScaleFactorDouble17->GetBinContent(Bin);
          TotalWeight=Weight1*Weight2;
        }
        else if(t1Tight->GetValue())
        {
          Bin=ScaleFactorDouble17->FindBin(e1Pt->GetValue(),fabs(e1Eta->GetValue()));
          Weight1=ScaleFactorDouble17->GetBinContent(Bin);
          Bin=ScaleFactorDouble8->FindBin(e0Pt->GetValue(), fabs(e0Eta->GetValue()));
          Weight2=ScaleFactorDouble8->GetBinContent(Bin);
          TotalWeight=Weight1*Weight2;
        }
        else
        {
          cout<<"neither are tight?"<<endl;
          continue;
        }
        
        Bin = -1;
        Bin = ScaleFactorGSF->FindBin(e0Pt->GetValue(), fabs(e0Eta->GetValue()));
        TotalWeight *= ScaleFactorGSF->GetBinContent(Bin);
        Bin = -1;
        Bin = ScaleFactorGSF->FindBin(e1Pt->GetValue(), fabs(e1Eta->GetValue()));
        TotalWeight *= ScaleFactorGSF->GetBinContent(Bin);
        if(!scaleFactor)TotalWeight=1;
        Numerator->Fill(phistar->GetValue(),TotalWeight);
    }

    return Numerator;

}

TH1* MakeSingle(const string TreeLoc, TH2* ScaleFactorGSF) {//Single
    double PtBins[7] = {30, 40, 50, 70, 250};
    double EtaBins[6] = {0, .8, 1.442, 1.56, 2, 2.5};
    cout<<"test 1"<<endl;
    TH2* ScaleFactorSingle27 = new TH2F("scaleFactor27", "scaleFactor8", 4, PtBins, 5, EtaBins);
    cout<<"test 2"<<endl;
    ScaleFactorSingle27->SetBinContent(1, 1, 0.9740); //10-20 GeV Pt
    ScaleFactorSingle27->SetBinContent(1, 2, 0.9595);
    ScaleFactorSingle27->SetBinContent(1, 3, 0.0);
    ScaleFactorSingle27->SetBinContent(1, 4, 1.0144);
    ScaleFactorSingle27->SetBinContent(1, 5, 1.0022);

    ScaleFactorSingle27->SetBinContent(2, 1, 0.9827); //20-30 GeV Pt
    ScaleFactorSingle27->SetBinContent(2, 2, 0.9818);
    ScaleFactorSingle27->SetBinContent(2, 3, 0.0);
    ScaleFactorSingle27->SetBinContent(2, 4, 1.0136);
    ScaleFactorSingle27->SetBinContent(2, 5, 1.0084);

    ScaleFactorSingle27->SetBinContent(3, 1, 0.9825); //30-40 GeV Pt
    ScaleFactorSingle27->SetBinContent(3, 2, 0.9871);
    ScaleFactorSingle27->SetBinContent(3, 3, 0.0);
    ScaleFactorSingle27->SetBinContent(3, 4, 1.0009);
    ScaleFactorSingle27->SetBinContent(3, 5, 1.0120);

    ScaleFactorSingle27->SetBinContent(4, 1, 0.9834); //40-50 GeV Pt
    ScaleFactorSingle27->SetBinContent(4, 2, 0.9897);
    ScaleFactorSingle27->SetBinContent(4, 3, 0.0);
    ScaleFactorSingle27->SetBinContent(4, 4, 0.9711);
    ScaleFactorSingle27->SetBinContent(4, 5, 1.0374);
   // cout<<"Get Bin numbers "<<ScaleFactorSingle27->GetBin(1,2);
    //cout<<" Should be the same "<<ScaleFactorSingle27->FindBin(33,.9)<<endl;
    const string file_name = "/data/whybee0a/user/lesko_2/fermi/Output/ZfinderMC30-20pt-15-5-20/Madgraph15-5-20.root";
    TFile* theFile = new TFile(file_name.c_str());
    string hold = "ZFinder/Combined Single 3020 Reco/7 60 < M_{ee} < 120/phistar";

    TH1* Denominator = (TH1F*) theFile->Get(hold.c_str());
    for (int i = 1; i <= Denominator->GetNbinsX(); i++) {
        Denominator->SetBinContent(i, 0);
    }

    TTree* DenTree = GetTTree(file_name, TreeLoc); //denominator tree

    TBranch* RecoEvent = DenTree->GetBranch("reco"); //now Getting denominator stuff
    TLeaf* phistar = RecoEvent->GetLeaf("z_phistar_dressed");
    TLeaf* t0Tight = RecoEvent->GetLeaf("t0tight");
    TLeaf* e0Eta = RecoEvent->GetLeaf("e_eta0");
    TLeaf* e0Pt = RecoEvent->GetLeaf("e_pt0");
    TLeaf* t1Tight = RecoEvent->GetLeaf("t1tight");
    TLeaf* e1Eta = RecoEvent->GetLeaf("e_eta1");
    TLeaf* e1Pt = RecoEvent->GetLeaf("e_pt1");
    Int_t Bin = -1;
    for (int i = 0; i < DenTree->GetEntries(); i++) {//grabbing numinator stuff
        //if (!(i % 50000))cout << " still going :" << i << endl;
        DenTree->GetEntry(i);
         Bin = -1;
        double Weight = -1;
        //double GSFWeight1 = -1;
        if (t0Tight->GetValue()) {
            Bin = ScaleFactorSingle27->FindBin(e0Pt->GetValue(), fabs(e0Eta->GetValue()));
            //cout<<"Bin number "<<Bin<<" Pt is "<<e0Pt->GetValue()<<" and eta is "<<fabs(e0Eta->GetValue())<<endl;
            Weight = ScaleFactorSingle27->GetBinContent(Bin);
            //cout<<"And the weight is "<<Weight<<endl;
            //cout<<"okay we shoud get .9897 "<< ScaleFactorSingle27->GetBinContent(20)<<endl;
        } else if (t1Tight->GetValue()) {
            Bin = ScaleFactorSingle27->FindBin(e1Pt->GetValue(), fabs(e1Eta->GetValue()));
            Weight = ScaleFactorSingle27->GetBinContent(Bin);
           
        } else {
            cout << "Neither electron is tight " << endl;
            continue;

        }
        Bin = -1;
        Bin = ScaleFactorGSF->FindBin(e0Pt->GetValue(), fabs(e0Eta->GetValue()));
        Weight *= ScaleFactorGSF->GetBinContent(Bin);
        Bin = -1;
        Bin = ScaleFactorGSF->FindBin(e1Pt->GetValue(), fabs(e1Eta->GetValue()));
        Weight *= ScaleFactorGSF->GetBinContent(Bin);
        if(!scaleFactor)Weight=1;
        Denominator->Fill(phistar->GetValue() , Weight);
    }

    return Denominator;
}

int main() {
    bool debug = false;

    const string file_name = "/data/whybee0a/user/lesko_2/fermi/Output/ZfinderMC30-20pt-15-5-20/Madgraph15-5-20.root";
    const string TreeOrginLoc = "ZFinder/Combined Single 3020 Reco/Combined Single 3020 Reco";
    const string TreeSingle3010Loc = "ZFinder/Combined Single 3010 Reco/Combined Single 3010 Reco";
    const string TreeDouble2020Loc = "ZFinder/Combined Double 2020 Reco/Combined Double 2020 Reco";
    const string TreeDouble3020Loc = "ZFinder/Combined Double 3020 Reco/Combined Double 3020 Reco";
    string hold = "z_m";

    double PtBins[7] = {10, 20, 30, 40, 50, 70, 250};
    double EtaBins[6] = {0, .8, 1.442, 1.56, 2, 2.5};
    TH2* ScaleFactorDouble8 = new TH2F("scaleFactor8", "scaleFactor8", 6, PtBins, 5, EtaBins);
    ScaleFactorDouble8->SetBinContent(1, 1, 0.9961); //10-20 GeV Pt
    ScaleFactorDouble8->SetBinContent(1, 2, 0.9934);
    ScaleFactorDouble8->SetBinContent(1, 3, 0.0);
    ScaleFactorDouble8->SetBinContent(1, 4, 0.9973);
    ScaleFactorDouble8->SetBinContent(1, 5, 0.9975);

    ScaleFactorDouble8->SetBinContent(2, 1, 0.9961); //20-30 GeV Pt
    ScaleFactorDouble8->SetBinContent(2, 2, 0.9934);
    ScaleFactorDouble8->SetBinContent(2, 3, 0.0);
    ScaleFactorDouble8->SetBinContent(2, 4, 0.9973);
    ScaleFactorDouble8->SetBinContent(2, 5, 0.9975);

    ScaleFactorDouble8->SetBinContent(3, 1, 0.9962); //30-40 GeV Pt
    ScaleFactorDouble8->SetBinContent(3, 2, 0.9943);
    ScaleFactorDouble8->SetBinContent(3, 3, 0.0);
    ScaleFactorDouble8->SetBinContent(3, 4, 0.9981);
    ScaleFactorDouble8->SetBinContent(3, 5, 0.9988);

    ScaleFactorDouble8->SetBinContent(4, 1, 0.9948); //40-50 GeV Pt
    ScaleFactorDouble8->SetBinContent(4, 2, 0.9952);
    ScaleFactorDouble8->SetBinContent(4, 3, 0.0);
    ScaleFactorDouble8->SetBinContent(4, 4, 0.9982);
    ScaleFactorDouble8->SetBinContent(4, 5, 0.9986);

    ScaleFactorDouble8->SetBinContent(5, 1, 0.9963); //50-70 GeV Pt
    ScaleFactorDouble8->SetBinContent(5, 2, 0.9959);
    ScaleFactorDouble8->SetBinContent(5, 3, 0.0);
    ScaleFactorDouble8->SetBinContent(5, 4, 0.9986);
    ScaleFactorDouble8->SetBinContent(5, 5, 1.0041);

    ScaleFactorDouble8->SetBinContent(6, 1, 0.9938); //70-120 GeV Pt
    ScaleFactorDouble8->SetBinContent(6, 2, 0.9976);
    ScaleFactorDouble8->SetBinContent(6, 3, 0.000);
    ScaleFactorDouble8->SetBinContent(6, 4, 1.0020);
    ScaleFactorDouble8->SetBinContent(6, 5, .9906);

    TH2* ScaleFactorDouble17 = new TH2F("scaleFactor17", "scaleFactor17", 6, PtBins, 5, EtaBins);

    ScaleFactorDouble17->SetBinContent(1, 1, 0.9935); //10-20 GeV Pt
    ScaleFactorDouble17->SetBinContent(1, 2, 0.9892);
    ScaleFactorDouble17->SetBinContent(1, 3, 0.0);
    ScaleFactorDouble17->SetBinContent(1, 4, 0.9973);
    ScaleFactorDouble17->SetBinContent(1, 5, 0.9955);

    ScaleFactorDouble17->SetBinContent(2, 1, 0.9935); //20-30 GeV Pt
    ScaleFactorDouble17->SetBinContent(2, 2, 0.9892);
    ScaleFactorDouble17->SetBinContent(2, 3, 0.0);
    ScaleFactorDouble17->SetBinContent(2, 4, 0.9973);
    ScaleFactorDouble17->SetBinContent(2, 5, 0.9955);

    ScaleFactorDouble17->SetBinContent(3, 1, 0.9953); //30-40 GeV Pt
    ScaleFactorDouble17->SetBinContent(3, 2, 0.9938);
    ScaleFactorDouble17->SetBinContent(3, 3, 0.0);
    ScaleFactorDouble17->SetBinContent(3, 4, 0.9978);
    ScaleFactorDouble17->SetBinContent(3, 5, 0.9985);

    ScaleFactorDouble17->SetBinContent(4, 1, 0.9947); //40-50 GeV Pt
    ScaleFactorDouble17->SetBinContent(4, 2, 0.9944);
    ScaleFactorDouble17->SetBinContent(4, 0, 0.0);
    ScaleFactorDouble17->SetBinContent(4, 4, 0.9977);
    ScaleFactorDouble17->SetBinContent(4, 5, 0.9985);

    ScaleFactorDouble17->SetBinContent(5, 1, 0.9943); //50-70 GeV Pt
    ScaleFactorDouble17->SetBinContent(5, 2, 0.9959);
    ScaleFactorDouble17->SetBinContent(5, 3, 0.0);
    ScaleFactorDouble17->SetBinContent(5, 4, 0.9968);
    ScaleFactorDouble17->SetBinContent(5, 5, 1.0015);

    ScaleFactorDouble17->SetBinContent(6, 1, 0.9933); //50-120 GeV Pt
    ScaleFactorDouble17->SetBinContent(6, 2, 0.9959);
    ScaleFactorDouble17->SetBinContent(6, 3, 0.0);
    ScaleFactorDouble17->SetBinContent(6, 4, 0.9971);
    ScaleFactorDouble17->SetBinContent(6, 5, 0.9906);

    double PTBins2[5]={20, 30, 40, 50, 200};
    
    TH2* ScaleFactorGSF = new TH2F("scaleFactorGSF", "scaleFactorGSF", 4, PTBins2, 5, EtaBins);
    
    ScaleFactorGSF->SetBinContent(1, 1, 0.960);
    ScaleFactorGSF->SetBinContent(1, 2, 0.936);
    ScaleFactorGSF->SetBinContent(1, 3, 0.933);
    ScaleFactorGSF->SetBinContent(1, 4, 0.879);
    ScaleFactorGSF->SetBinContent(1, 5, 0.974);
    
    ScaleFactorGSF->SetBinContent(2, 1, 0.978);
    ScaleFactorGSF->SetBinContent(2, 2, 0.958);
    ScaleFactorGSF->SetBinContent(2, 3, 0.907);
    ScaleFactorGSF->SetBinContent(2, 4, 0.909);
    ScaleFactorGSF->SetBinContent(2, 5, 0.987);
    
    ScaleFactorGSF->SetBinContent(3, 1, 0.981);
    ScaleFactorGSF->SetBinContent(3, 2, 0.969);
    ScaleFactorGSF->SetBinContent(3, 3, 0.904);
    ScaleFactorGSF->SetBinContent(3, 4, 0.942);
    ScaleFactorGSF->SetBinContent(3, 5, 0.991);
    
    ScaleFactorGSF->SetBinContent(4, 1, 0.982);
    ScaleFactorGSF->SetBinContent(4, 2, 0.969);
    ScaleFactorGSF->SetBinContent(4, 3, 0.926);
    ScaleFactorGSF->SetBinContent(4, 4, 0.957);
    ScaleFactorGSF->SetBinContent(4, 5, 0.999);
    if (debug)cout << "test 1" << endl;
    //TH1* ZMassRatio = new TH1F("ZMass", "Zmass Ratio", 200, 0, 200);
    //FillHisto(TreeOrginLoc, TreeSingle3010Loc, hold, ZMass3010);
    //TFile* TFileOrg = new TFile(file_name.c_str(), "READ");

    TH1* phistarOrg = MakeSingle(TreeOrginLoc, ScaleFactorGSF);
    
    TH1* phistarSingle3010=MakeSingle( TreeSingle3010Loc, ScaleFactorGSF);

    TH1* phistarDoub2020=  FillHisto(phistarOrg, TreeDouble2020Loc,  ScaleFactorDouble8, ScaleFactorDouble17, ScaleFactorGSF);
            
    TH1* phistarDoub3020=FillHisto(phistarOrg, TreeDouble3020Loc,  ScaleFactorDouble8,  ScaleFactorDouble17, ScaleFactorGSF);

    phistarOrg->Sumw2();

    TFile* theFile = new TFile("test.root", "RECREATE");
    theFile->cd();
    phistarDoub2020->Sumw2();
    phistarDoub2020->Divide(phistarOrg);
    phistarDoub2020->Write();



    phistarSingle3010->Sumw2();
    phistarSingle3010->Divide(phistarOrg);
    phistarSingle3010->Write();


    phistarDoub3020->Divide(phistarOrg);
    phistarDoub3020->Write();


    TLine *line = new TLine(0, 1, 3.25, 1);
    line->SetLineColor(kRed);
    TCanvas* c1 = new TCanvas("c1", "", 800, 700);
    c1->SetFillColor(10);
    c1->SetFillColor(10);
    c1->cd();
    gStyle->SetOptStat("");
    c1->SetLogx();
    phistarDoub2020->SetMarkerColor(kBlack);
    phistarDoub2020->SetLineColor(kBlack);
    phistarDoub2020->SetMarkerStyle(22);
    phistarDoub2020->SetTitle("Double electron trigger 20 GeV Pt Cut");
    if(scaleFactor)phistarDoub2020->SetTitle("Double electron trigger 20 GeV Pt Cut Scaled");
    phistarDoub2020->GetXaxis()->SetTitle(" #phi *");
    phistarDoub2020->GetYaxis()->SetTitle("Modified selection/Nominal selection");
    phistarDoub2020->GetYaxis()->SetRangeUser(.8, 1.2);
    phistarDoub2020->GetYaxis()->SetTitleOffset(1.3);
    phistarDoub2020->Draw("e1");


    line->Draw("same");
    string type = ".png";
    if(scaleFactor)type="Scaled"+type;
    string plotname = "Double2020" + type;
    c1->Print(plotname.c_str());


    phistarDoub2020->Delete();

    TCanvas* c2 = new TCanvas("c2", "", 800, 700);
    c2->SetFillColor(10);
    c2->SetFillColor(10);
    c2->cd();
    gStyle->SetOptStat("");
    c2->SetLogx();
    phistarSingle3010->SetMarkerColor(kBlack);
    phistarSingle3010->SetLineColor(kBlack);
    phistarSingle3010->SetMarkerStyle(22);
    phistarSingle3010->SetTitle("Single electron trigger 30 10 GeV Pt Cut");
    if(scaleFactor)phistarSingle3010->SetTitle("Single electron trigger 30 10 GeV Pt Cut Scaled");
    phistarSingle3010->GetXaxis()->SetTitle(" #phi *");
    phistarSingle3010->GetYaxis()->SetTitle("Modified selection/Nominal selection");
    phistarSingle3010->GetYaxis()->SetRangeUser(.8, 1.2);
    phistarSingle3010->GetYaxis()->SetTitleOffset(1.3);
    phistarSingle3010->Draw("e1");


    line->Draw("same");

    plotname = "Single3010" + type;
    c2->Print(plotname.c_str());
    phistarSingle3010->Delete();

    if (debug)cout << "test 3" << endl;
    TCanvas* c3 = new TCanvas("c3", "", 800, 700);
    c3->SetFillColor(10);
    c3->SetFillColor(10);
    c3->cd();
    if (debug)cout << "test 4" << endl;
    gStyle->SetOptStat("");
    c3->SetLogx();
    if (debug)cout << "test 4.1" << endl;
    phistarDoub3020->SetMarkerColor(kBlack);
    if (debug)cout << "test 4.2" << endl;
    phistarDoub3020->SetLineColor(kBlack);
    phistarDoub3020->SetMarkerStyle(22);
    if (debug)cout << "test 5" << endl;
    phistarDoub3020->SetTitle("double electron trigger 30 20 GeV Pt Cut");
    if(scaleFactor)phistarDoub3020->SetTitle("double electron trigger 30 20 GeV Pt Cut Scaled");
    phistarDoub3020->GetXaxis()->SetTitle(" #phi *");
    phistarDoub3020->GetYaxis()->SetTitle("Modified selection/Nominal selection");
    phistarDoub3020->GetYaxis()->SetRangeUser(.8, 1.2);
    phistarDoub3020->GetYaxis()->SetTitleOffset(1.3);
    phistarDoub3020->Draw("e1");
    if (debug)cout << "test " << endl;

    line->Draw("same");

    plotname = "phistarDouble3020" + type;
   
    c3->Print(plotname.c_str());



    return EXIT_SUCCESS;
}
