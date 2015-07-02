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

#include "TH1.h"
#include <TTree.h>
#include "TSystem.h"

#include <algorithm>
#include <set>
#include <vector>
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

int main() {
    // Get a map of the histograms of the Z Masses
    const std::string Tree_MedCut = "ZFinder/Combined Single Reco/Combined Single Reco";
    const std::string Tree_LowCut = "ZFinder/Combined Single Lowered Threshold Reco/Combined Single Lowered Threshold Reco";
    const std::string med_file_name = "/data/whybee0a/user/lesko_2/fermi/Output/2012MidABCD.root";
    const std::string low_file_name = "/data/whybee0a/user/lesko_2/fermi/Output/2012LowABCD.root";

    // Open the file and load the tree
    TTree* TreeLow = GetTTree(low_file_name, Tree_LowCut);
    TBranch* event_infoL = TreeLow->GetBranch("event_info");
    TLeaf* EVNumbLow = event_infoL->GetLeaf("event_number");
    TLeaf* RunNumbLow = event_infoL->GetLeaf("run_number");
    // Pack into a hitogram
    typedef pair<int, int> pairs;
    std::set<pairs> event_and_Run_Number_Low;
    std::set<pairs> event_and_Run_Number_Med;
    for (int i = 0; i < TreeLow->GetEntries(); i++) {
        TreeLow->GetEntry(i);
        pairs Lower;
        Lower.first = EVNumbLow->GetValue();
        Lower.second =RunNumbLow->GetValue();
        if (!(i % 50000))cout << " still going :" << i << endl;
        event_and_Run_Number_Low.insert(Lower);

    }

    TH1 *EPt0Hist = new TH1F("E_Pt0", "PT of e0", 700, 0, 700);
    TH1 *EPt1Hist = new TH1F("E_Pt1", "PT of e1", 700, 0, 700);

    TH1 *EEta0Hist = new TH1F("E_Eta0", "Eta of e0", 200, -10, 10);
    TH1 *EEta1Hist = new TH1F("E_Eta1", "Eta of e1", 200, -10, 10);


    TTree* treeM = GetTTree(med_file_name, Tree_MedCut);
    TBranch* event_infoM = treeM->GetBranch("event_info");
    TLeaf* EVNumbM = event_infoM->GetLeaf("event_number");
    TLeaf *RunNMed = event_infoM->GetLeaf("run_number"); //////FIX
    TBranch* RecoMed = treeM->GetBranch("reco");
    TLeaf* EPt0 = RecoMed->GetLeaf("e_pt0");
    TLeaf* EPt1 = RecoMed->GetLeaf("e_pt1");
    TLeaf* EEta0 = RecoMed->GetLeaf("e_eta0");
    TLeaf* EEta1 = RecoMed->GetLeaf("e_eta1");
    int j = 0;

    for (int i = 0; i < treeM->GetEntries(); i++) {
        treeM->GetEntry(i);
        if (!(i % 50000))cout << " still going 2 :" << i << endl;
        pairs Medium;
        Medium.first = EVNumbM->GetValue();
        Medium.second =RunNMed->GetValue();
        
        event_and_Run_Number_Med.insert(Medium);

        if (event_and_Run_Number_Low.find(Medium) == event_and_Run_Number_Low.end()) {
            EPt0Hist->Fill(EPt0->GetValue());
            EPt1Hist->Fill(EPt1->GetValue());
            EEta0Hist->Fill(EEta0->GetValue());
            EEta1Hist->Fill(EEta1->GetValue());
            j++;
        }

    }
    TFile *theFile = new TFile("MuonIssues.root", "RECREATE");
    theFile->cd();
    EPt0Hist->Write();
    EPt1Hist->Write();
    EEta0Hist->Write();
    EEta1Hist->Write();

    EPt0Hist->Delete();
    EPt1Hist->Delete();
    EEta0Hist->Delete();
    EEta1Hist->Delete();
    //cout << " NUMBER IN THE HIGH :" << treeM->GetEntries() << endl;
    //cout << "Number of things in High :" << event_and_Run_Number_Med.size() << endl;
    //cout << "NUmber in Med :" << TreeMed->GetEntries() << endl;
    //cout << "NUMBER THAT is in low :" << event_and_Run_Number_Med.size() << endl;
    //cout << "NUMBER THAT WE SHOULD HAVE :" << TreeMed->GetEntries() - treeM->GetEntries() << endl;
    //cout << "HOW MANY DO WE HAVE :" << j << endl;
    return EXIT_SUCCESS;
}
