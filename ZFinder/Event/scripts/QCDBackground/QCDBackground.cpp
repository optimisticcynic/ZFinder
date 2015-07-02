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


#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooGenericPdf.h"
#include "RooHistPdf.h"
#include "RooPlot.h"
#include "RooRealVar.h"



#include <set>
#include <TH1.h>

using namespace std; // yeah I am evil, get over it

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

void FillHisto(const string FileName, double CrossSection, TH1* ZMassHist) {
    const string Tree_LowCut = "ZFinder/Combined Single Lowered Threshold Reco/Combined Single Lowered Threshold Reco";
    TTree* OurTree = GetTTree(FileName, Tree_LowCut);
    TFile* theFile = new TFile(FileName.c_str());
    TH1 *UnweightedSize = (TH1F*) theFile->Get("ZFinder/unweighted_counter");
    double totalUnweighted = UnweightedSize->Integral();
    TBranch* RecoEvent = OurTree->GetBranch("reco");
    TLeaf* ZMass = RecoEvent->GetLeaf("z_m");

    cout << "Number of events? :" << OurTree->GetEntries() << endl;
    for (int i = 0; i < OurTree->GetEntries(); i++) {
        if (!(i % 50000))cout << " still going :" << i << endl;
        OurTree->GetEntry(i);
        ZMassHist->Fill(ZMass->GetValue(), CrossSection / totalUnweighted);
    }
}

int main() {
    bool debug = true;
    //const string file_nameTree_020_030Cut_30_20 = "/data/whybee0a/user/lesko_2/fermi/qcdback/ZfinderQCDMC30-20pt-15-5-03/QCDMC020_030_Cuts_30-20pt-15-5-03.root";
    //const string file_nameTree_030_080Cut_30_20 = "/data/whybee0a/user/lesko_2/fermi/qcdback/ZfinderQCDMC30-20pt-15-5-03/QCDMC030_080_Cuts_30-20pt-15-5-03.root";
    const string file_nameTree_080_170Cut_30_20 = "/data/whybee0a/user/lesko_2/fermi/qcdback/ZfinderQCDMC30-20pt-15-5-03/QCDMC080_170_Cuts_30-20pt-15-5-03.root";
    const string file_nameTree_170_250Cut_30_20 = "/data/whybee0a/user/lesko_2/fermi/qcdback/ZfinderQCDMC30-20pt-15-5-03/QCDMC170_250_Cuts_30-20pt-15-5-03.root";
    const string file_nameTree_250_350Cut_30_20 = "/data/whybee0a/user/lesko_2/fermi/qcdback/ZfinderQCDMC30-20pt-15-5-03/QCDMC250_350_Cuts_30-20pt-15-5-03.root";


    /*TTree* Tree_020_030Cut_30_20 = GetTTree(file_nameTree_020_030Cut_30_20, Tree_LowCut);
    TTree* Tree_030_080Cut_30_20 = GetTTree(file_nameTree_030_080Cut_30_20, Tree_LowCut);
    TTree* Tree_080_170Cut_30_20 = GetTTree(file_nameTree_080_170Cut_30_20, Tree_LowCut);
    TTree* Tree_170_250Cut_30_20 = GetTTree(file_nameTree_170_250Cut_30_20, Tree_LowCut);
    TTree* Tree_250_350Cut_30_20 = GetTTree(file_nameTree_250_350Cut_30_20, Tree_LowCut);*/
    TH1* ZMassHist_3020 = new TH1F("QCDMass30_20", "QCD Invariant Mass;GeV;Events/GeV", 60, 60, 120);
    TH1* ZMassHist_2010 = new TH1F("QCDMass_20_10", "QCD Invariant Mass;GeV;Events/GeV", 60, 60, 120);
    //TFile* theFile = new TFile(file_nameTree_020_030Cut_30_20.c_str());

    //FillHisto(file_nameTree_020_030Cut_30_20, 2.886e8, ZMassHist_3020);
    //FillHisto(file_nameTree_030_080Cut_30_20, 7.433e7, ZMassHist_3020);
    FillHisto(file_nameTree_080_170Cut_30_20, 1191000.0, ZMassHist_3020);
    FillHisto(file_nameTree_170_250Cut_30_20, 30990, ZMassHist_3020);
    FillHisto(file_nameTree_250_350Cut_30_20, 4250.0, ZMassHist_3020);



    //const string file_nameTree_020_030Cut_20_10 = "/data/whybee0a/user/lesko_2/fermi/qcdback/ZfinderQCDMC20-10pt-15-5-03/QCDMC020_030_Cuts_20-10pt-15-5-03.root";
    //const string file_nameTree_030_080Cut_20_10 = "/data/whybee0a/user/lesko_2/fermi/qcdback/ZfinderQCDMC20-10pt-15-5-03/QCDMC030_080_Cuts_20-10pt-15-5-03.root";
    const string file_nameTree_080_170Cut_20_10 = "/data/whybee0a/user/lesko_2/fermi/qcdback/ZfinderQCDMC20-10pt-15-5-03/QCDMC080_170_Cuts_20-10pt-15-5-03.root";
    const string file_nameTree_170_250Cut_20_10 = "/data/whybee0a/user/lesko_2/fermi/qcdback/ZfinderQCDMC20-10pt-15-5-03/QCDMC170_250_Cuts_20-10pt-15-5-03.root";
    const string file_nameTree_250_350Cut_20_10 = "/data/whybee0a/user/lesko_2/fermi/qcdback/ZfinderQCDMC20-10pt-15-5-03/QCDMC250_350_Cuts_20-10pt-15-5-03.root";


    //FillHisto(file_nameTree_020_030Cut_20_10, 2.886e8, ZMassHist_2010);
    //FillHisto(file_nameTree_030_080Cut_20_10, 7.433e7, ZMassHist_2010);
    FillHisto(file_nameTree_080_170Cut_20_10, 1191000.0, ZMassHist_2010);
    FillHisto(file_nameTree_170_250Cut_20_10, 30990, ZMassHist_2010);
    FillHisto(file_nameTree_250_350Cut_20_10, 4250.0, ZMassHist_2010);

    TFile *theFile = new TFile("Masses.root", "RECREATE");
    theFile->cd();
    ZMassHist_3020->Write();
    ZMassHist_3020->Delete();
    ZMassHist_2010->Write();
    ZMassHist_2010->Delete();
    if (debug)cout << "test 1" << endl;
    using namespace RooFit;
    TFile *theFile20_10Pt250_350 = new TFile(file_nameTree_250_350Cut_20_10.c_str());
    TH1* ZMassHisto250_350Old = (TH1F*) theFile20_10Pt250_350->Get("ZFinder/Combined Single Lowered Threshold Reco/5 pt>20.0 AND pt>10.0/z_mass_all");
    TH1* ZMassHisto250_350= new TH1F("Masses","Mass",285,15,300);
    //double Newsize[285];
    for(int i=15;i<301;i++)
    {
       ZMassHisto250_350->SetBinContent(i-15,ZMassHisto250_350Old->GetBinContent(i));
    }
    ZMassHisto250_350->Rebin(5);
    //ZMassHisto250_350->GetXaxis()->SetRangeUser(100,300);
    if (!ZMassHisto250_350) {
        cout << "Histo not found" << endl;
        return EXIT_FAILURE;
    }

    if (debug)cout << "test 2" << ZMassHisto250_350->Integral() << endl;
    if (debug)cout << "test 2.1" << endl;
    RooRealVar z_mass("z_mass", "M_{ee}", 0, 300, "GeV");
    RooDataHist FittingQCD("QCDFit", "QCD_Fit", RooArgSet(z_mass), ZMassHisto250_350);
    if (debug)cout << "test 3" << endl;
    RooRealVar alpha("alpha", "alpha", 50., 10., 90.);
    // gamma controls the slope of the exponential
    if (debug)cout << "test 4" << endl;
    RooRealVar gamma("gamma", "gamma", 0.01, 0.0001, 0.03);
    // Delta controls the ratio of the slope of the two sides, as well as the
    // smoothness of the peak
    if (debug)cout << "test 5" << endl;
    RooRealVar delta("delta", "delta", 40., 10, 80.);

    RooFormulaVar var1("var1", "(alpha-z_mass)/delta", RooArgSet(alpha, z_mass, delta));
    RooFormulaVar var2("var2", "-1.0*gamma*z_mass", RooArgSet(gamma, z_mass));
    if (debug)cout << "test 6" << endl;
    RooGenericPdf QCDGraph("QCDGraph", "ROOT::Math::erfc(var1)*exp(var2)", RooArgSet(var1, var2));
    if (debug)cout << "test 7" << endl;
    RooFitResult* fit_result = QCDGraph.fitTo(FittingQCD, Verbose(false), PrintLevel(-1), Save(true));
    if (debug)cout << "test 8" << endl;
    TCanvas canvas("canvas", "canvas", 600, 600);
    canvas.cd();

    const std::string TITLE = "QCD Fit: ";
    RooPlot* fitFrame = z_mass.frame(Title(TITLE.c_str()));
    fitFrame->SetTitleOffset(1.25, "Y");
    fitFrame->SetAxisRange(10.0, 350.0, "Y");

    FittingQCD.plotOn(fitFrame);
    QCDGraph.plotOn(fitFrame);
    //canvas.SetLogy();
    fitFrame->Draw();
    fit_result->Draw("same");
    cout<<"our alpha is :"<<alpha.getVal()<<"  and our delta is :"<<delta.getVal()<<" and our gamma is :"<<gamma.getVal()<<endl;
    canvas.Print("QCD250_350.png");

    return EXIT_SUCCESS;
}
