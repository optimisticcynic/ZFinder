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
#include <TStyle.h>
#include <TLegend.h>

#include "TH1.h"
#include <TTree.h>
#include "TSystem.h"
#include <TAxis.h>
#include <TLine.h>

#include <algorithm>
#include <set>
#include <vector>
#include <TH2.h>
#include <TColor.h>
using namespace std; // yeah I am evil, get over it


const double yBins[] = {0.0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4};
size_t nY = (sizeof (yBins) / sizeof (yBins[0])) - 1;

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
    // Get7 a map of the histograms of the Z Masses
    const std::string file_name = "/data/whybee0a/user/lesko_2/fermi/MadWithInitial/Mad2016_8_25/results/AllMHWithMothers.root";
    // Open the file and load the tree
    const std::string TreeName = "ZFinder/Combined Single Reco/Combined Single Reco";
    TTree* tree = GetTTree(file_name, TreeName);

    TBranch* reco = tree->GetBranch("reco");
    //TLeaf* Z_YBorn = reco->GetLeaf("z_phistar_born");
    TLeaf* Mom1 = reco->GetLeaf("z_mom1PDG");
    TLeaf* Mom2 = reco->GetLeaf("z_mom2PDG");
    TLeaf* PenUltimateMom1 = reco->GetLeaf("z_penultimate1PDG");
    TLeaf* PenUltimateMom2 = reco->GetLeaf("z_penultimate2PDG");
    TLeaf* Z_YBorn = reco->GetLeaf("z_yBorn");


    TBranch* event_info = tree->GetBranch("event_info");
    //TLeaf* EVNumb = event_info->GetLeaf("event_number");
    // Pack into a hitogram

    for (int w = 0; w < 2; w++) {
        string PlotName;
        TLeaf* MomOrPenUltimateMom1 = w == 0 ? Mom1 : PenUltimateMom1;
        TLeaf* MomOrPenUltimateMom2 = w == 0 ? Mom2 : PenUltimateMom2;

        vector<string> NamesOfPlots;
        NamesOfPlots.push_back("UpQuarkPair"); //0
        NamesOfPlots.push_back("DownQuarkPair"); //1
        NamesOfPlots.push_back("StrangeQuarkPair"); //2
        NamesOfPlots.push_back("CharmQuarkPair"); //3
        NamesOfPlots.push_back("BottomQuarkPair"); //4
        NamesOfPlots.push_back("SingleQuark"); //5
        NamesOfPlots.push_back("Gluon"); //6
        NamesOfPlots.push_back("TwoQuarks"); //7
        NamesOfPlots.push_back("TwoAntiQuarks"); //8
        NamesOfPlots.push_back("QuarkAntiQuarkPair"); //9
        NamesOfPlots.push_back("QuarkAntiQuarkNotPair"); //10
        NamesOfPlots.push_back("Quark Quark And AntiQuark AntiQuark"); //11

        map<string, TH1*> AllPlots;
        AllPlots[NamesOfPlots[0]] = new TH1D(NamesOfPlots[0].c_str(), NamesOfPlots[0].c_str(), nY, yBins);
        AllPlots[NamesOfPlots[1]] = new TH1D(NamesOfPlots[1].c_str(), NamesOfPlots[1].c_str(), nY, yBins);
        AllPlots[NamesOfPlots[2]] = new TH1D(NamesOfPlots[2].c_str(), NamesOfPlots[2].c_str(), nY, yBins);
        AllPlots[NamesOfPlots[3]] = new TH1D(NamesOfPlots[3].c_str(), NamesOfPlots[3].c_str(), nY, yBins);
        AllPlots[NamesOfPlots[4]] = new TH1D(NamesOfPlots[4].c_str(), NamesOfPlots[4].c_str(), nY, yBins);
        AllPlots[NamesOfPlots[5]] = new TH1D(NamesOfPlots[5].c_str(), NamesOfPlots[5].c_str(), nY, yBins);
        AllPlots[NamesOfPlots[6]] = new TH1D(NamesOfPlots[6].c_str(), NamesOfPlots[6].c_str(), nY, yBins);
        AllPlots[NamesOfPlots[7]] = new TH1D(NamesOfPlots[7].c_str(), NamesOfPlots[7].c_str(), nY, yBins); //Two quarks
        AllPlots[NamesOfPlots[8]] = new TH1D(NamesOfPlots[8].c_str(), NamesOfPlots[8].c_str(), nY, yBins); //Two Anti quarks
        AllPlots[NamesOfPlots[9]] = new TH1D(NamesOfPlots[9].c_str(), NamesOfPlots[9].c_str(), nY, yBins); //
        AllPlots[NamesOfPlots[10]] = new TH1D(NamesOfPlots[10].c_str(), NamesOfPlots[10].c_str(), nY, yBins);
        AllPlots[NamesOfPlots[11]] = new TH1D(NamesOfPlots[11].c_str(), NamesOfPlots[11].c_str(), nY, yBins);

        map<string, TH1*> RatioPlots; //using normalized versions of the pairs to see shape changes

        cout << "test 1" << endl;
        //Vector<TH1*> YplotsFromParents;
        //YplotsFromParents.push_back(new TH1D("YSeperatedUpQuarkPair", "UpQuarkPair", nY, yBins));
        //YplotsFromParents.push_back(new TH1D("YSeperatedDownQuarkPair", "DownQuarkPair", nY, yBins));
        //YplotsFromParents.push_back(new TH1D("YSeperatedStrangeQuarkPair", "StrangeQuarkPair", nY, yBins));
        //YplotsFromParents.push_back(new TH1D("YSeperatedCharmQuarkPair", "CharmQuarkPair", nY, yBins));
        //YplotsFromParents.push_back(new TH1D("YSeperatedBottomQuarkPair", "BottomQuarkPair", nY, yBins));
        //YplotsFromParents.push_back(new TH1D("YSeperatedGluonQuarkPair", "GluonQuarkPair", nY, yBins));
        //YplotsFromParents.push_back(new TH1D("YSeperatedGluon", "Gluon", nY, yBins));
        //YplotsFromParents.push_back(new TH1D("YSeperatedUnmatchingQuarks", "UnmatchingQuarks", nY, yBins));

        //TH2D* Parents = new TH2D("ParentsPDGId", "Parents PDGID", 28, -6.5, 21.5, 28, -6.5, 21.5);
        TH2D* ProductionVsY = new TH2D("ProductionVsY", "ProductionVsY", 7, 0, 7, 6, yBins);

        for (int i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            if (fabs(MomOrPenUltimateMom1->GetValue()) == 1 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                AllPlots["QuarkAntiQuarkPair"]->Fill(Z_YBorn->GetValue());
                AllPlots["UpQuarkPair"]->Fill(Z_YBorn->GetValue());
                ProductionVsY->Fill(0.1, Z_YBorn->GetValue()
                        );
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 2 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                AllPlots["QuarkAntiQuarkPair"]->Fill(Z_YBorn->GetValue());
                AllPlots["DownQuarkPair"]->Fill(Z_YBorn->GetValue());
                ProductionVsY->Fill(1.1, Z_YBorn->GetValue());

            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 3 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                AllPlots["QuarkAntiQuarkPair"]->Fill(Z_YBorn->GetValue());
                AllPlots["StrangeQuarkPair"]->Fill(Z_YBorn->GetValue());
                ProductionVsY->Fill(2.1, Z_YBorn->GetValue());
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 4 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                AllPlots["QuarkAntiQuarkPair"]->Fill(Z_YBorn->GetValue());
                AllPlots["CharmQuarkPair"]->Fill(Z_YBorn->GetValue());
                ProductionVsY->Fill(3.1, Z_YBorn->GetValue());
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 5 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                AllPlots["QuarkAntiQuarkPair"]->Fill(Z_YBorn->GetValue());
                AllPlots["BottomQuarkPair"]->Fill(Z_YBorn->GetValue());
                ProductionVsY->Fill(4.1, Z_YBorn->GetValue());
            } else if ((MomOrPenUltimateMom1->GetValue() == 21 && fabs(MomOrPenUltimateMom2->GetValue()) < 7) || (MomOrPenUltimateMom2->GetValue() == 21 && fabs(MomOrPenUltimateMom1->GetValue()) < 7)) {
                AllPlots["SingleQuark"]->Fill(Z_YBorn->GetValue());
                ProductionVsY->Fill(6.1, Z_YBorn->GetValue());
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 21 && MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                AllPlots["Gluon"]->Fill(Z_YBorn->GetValue());
                ProductionVsY->Fill(6.1, Z_YBorn->GetValue());
            } else if ((MomOrPenUltimateMom1->GetValue()) < 7 && (MomOrPenUltimateMom1->GetValue()) > 0 && (MomOrPenUltimateMom2->GetValue()) < 7 && (MomOrPenUltimateMom2->GetValue()) > 0) {
                AllPlots["TwoQuarks"]->Fill(Z_YBorn->GetValue());
                ProductionVsY->Fill(7.1, Z_YBorn->GetValue());
            } else if ((MomOrPenUltimateMom1->GetValue()) > -7 && (MomOrPenUltimateMom1->GetValue()) < 0 && (MomOrPenUltimateMom2->GetValue()) > -7 && (MomOrPenUltimateMom2->GetValue()) < 0) {
                AllPlots["TwoAntiQuarks"]->Fill(Z_YBorn->GetValue());
                ProductionVsY->Fill(7.1, Z_YBorn->GetValue());
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) < 7 && fabs(MomOrPenUltimateMom1->GetValue()) < 7) {
                AllPlots["QuarkAntiQuarkNotPair"]->Fill(Z_YBorn->GetValue());
                ProductionVsY->Fill(7.1, Z_YBorn->GetValue());
            }
        }
        cout << "test 2" << endl;

        AllPlots["Quark Quark And AntiQuark AntiQuark"]->Add(AllPlots["TwoAntiQuarks"]);
        cout << "test 2.1" << endl;
        AllPlots["Quark Quark And AntiQuark AntiQuark"] ->Add(AllPlots["TwoQuarks"]);
        TH1D* AllQuarksNorm = (TH1D*) AllPlots["QuarkAntiQuarkPair"]->Clone("Devisor");
        AllQuarksNorm->Scale(1 / AllQuarksNorm->Integral());
        for (int i = 0; i < 5; i++) {
            string NewName = "Ratio" + NamesOfPlots[i];
            RatioPlots[NewName] = (TH1D*) AllPlots[NamesOfPlots[i]]->Clone(NewName.c_str());
            RatioPlots[NewName]->Scale(1 / RatioPlots[NewName]->Integral());
            RatioPlots[NewName]->Divide(AllQuarksNorm);
        }
        cout << "test 3" << endl;

        for (size_t i = 0; i < AllPlots.size(); i++) {
            for (size_t j = 1; j <= nY; j++) {
                AllPlots[NamesOfPlots[i]]->SetBinContent(j, AllPlots[NamesOfPlots[i]]->GetBinContent(j) / (yBins[j] - yBins[j - 1]));
            }
        }
        cout << "test 4" << endl;
        for (size_t i = 0; i < NamesOfPlots.size(); i++) {

            TCanvas canvas("canvas", "canvas", 1000, 1000);
            canvas.cd();
            gStyle->SetCanvasColor(0);
            gStyle->SetStatBorderSize(1);
            gStyle->SetOptStat("");
            gStyle->SetOptFit();
            AllPlots[NamesOfPlots[i]]->Draw();
            AllPlots[NamesOfPlots[i]]->SetLineWidth(2);

            string SaveName = NamesOfPlots[i];
            SaveName = 0 == w ? "Mom_" + SaveName : "PenUltimate_" + SaveName;
            string WithType = "RapidityPlots/Mompng/" + SaveName + ".png";
            canvas.Print(WithType.c_str());
            WithType = "RapidityPlots/MomPDF/" + SaveName + ".pdf";
            canvas.Print(WithType.c_str());
            WithType = "RapidityPlots/MomC/" + SaveName + ".C";
            canvas.Print(WithType.c_str());



            //if (i == 8)canvas.Print("Broken.png");
        }
        cout << "test 5" << endl;

        TCanvas canvas("c2", "c2", 1000, 1000);
        canvas.cd();
        canvas.SetLogy();
        gStyle->SetCanvasColor(0);
        gStyle->SetStatBorderSize(1);
        gStyle->SetOptStat("");

        AllPlots[NamesOfPlots[0]]->SetLineColor(kBlack);
        AllPlots[NamesOfPlots[1]]->SetLineColor(kBlue);
        AllPlots[NamesOfPlots[2]]->SetLineColor(kRed);
        AllPlots[NamesOfPlots[3]]->SetLineColor(kGreen + 1);
        AllPlots[NamesOfPlots[4]]->SetLineColor(kMagenta + 1);
        AllPlots[NamesOfPlots[5]]->SetLineColor(kOrange + 1);
        AllPlots[NamesOfPlots[6]]->SetLineColor(TColor::GetColor("#a65628"));
        AllPlots["Quark Quark And AntiQuark AntiQuark"]->SetLineColor(TColor::GetColor("#999999"));

        if (w == 0) {
            AllPlots[NamesOfPlots[0]]->SetTitle("");
            AllPlots[NamesOfPlots[0]]->SetXTitle("Rapidity");
            AllPlots[NamesOfPlots[0]]->GetYaxis()->SetRangeUser(90, 920e3);
            AllPlots[NamesOfPlots[0]]->GetXaxis()->CenterTitle();
            AllPlots[NamesOfPlots[0]]->Draw();
            AllPlots[NamesOfPlots[5]]->Draw("same");
        } else {
            AllPlots[NamesOfPlots[5]]->SetTitle("");
            AllPlots[NamesOfPlots[5]]->GetYaxis()->SetRangeUser(100, 930e3);
            AllPlots[NamesOfPlots[5]]->SetXTitle("Rapidity");
            AllPlots[NamesOfPlots[5]]->GetXaxis()->CenterTitle();
            AllPlots[NamesOfPlots[5]]->Draw();
            AllPlots[NamesOfPlots[0]]->Draw("same");
        }
        AllPlots[NamesOfPlots[1]]->Draw("same");
        AllPlots[NamesOfPlots[2]]->Draw("same");
        if (w == 0) {
            AllPlots[NamesOfPlots[3]]->Draw("same");
            AllPlots[NamesOfPlots[4]]->Draw("same");
        }
        AllPlots[NamesOfPlots[6]]->Draw("same");
        AllPlots["Quark Quark And AntiQuark AntiQuark"]->Draw("same");
        cout << "test 6" << endl;



        TLegend* leg = new TLegend(0.7, 0.70, 0.87, 0.89);
        leg->AddEntry(AllPlots[NamesOfPlots[0]], "u#bar{u}");
        leg->AddEntry(AllPlots[NamesOfPlots[1]], "d#bar{d}");
        leg->AddEntry(AllPlots[NamesOfPlots[2]], "s#bar{s}");
        if (w == 0) {
            leg->AddEntry(AllPlots[NamesOfPlots[3]], "c#bar{c}");
            leg->AddEntry(AllPlots[NamesOfPlots[4]], "b#bar{b}");
        }
        leg->AddEntry(AllPlots[NamesOfPlots[5]], "q or #bar{q}");
        leg->AddEntry(AllPlots[NamesOfPlots[6]], "gg");
        //leg->AddEntry(AllPlots[8], "Broken");NamesOfPlots[0]], "Up");
        leg->AddEntry(AllPlots[NamesOfPlots[11]], "qq or #bar{q}#bar{q}");
        leg->SetFillColor(0);
        leg->SetLineColor(0);
        leg->Draw("same");
        cout << "test 7" << endl;
        PlotName = w == 0 ? "Mom_AllLines" : "PenUltimate_AllLines";
        string WithType = "RapidityPlots/Mompng/" + PlotName + ".png";
        canvas.Print(WithType.c_str());
        WithType = "RapidityPlots/MomPDF/" + PlotName + ".pdf";
        canvas.Print(WithType.c_str());
        WithType = "RapidityPlots/MomC/" + PlotName + ".C";
        canvas.Print(WithType.c_str());
        TCanvas canvas3("c3", "c3", 1000, 1000);
        canvas3.cd();
        canvas3.SetLogz();
        gStyle->SetCanvasColor(0);
        gStyle->SetStatBorderSize(1);
        gStyle->SetOptStat("");
        ProductionVsY->Draw("colz");
        PlotName = w == 0 ? "Mom_TwoDCompProductionToY" : "PenUltimate_TwoDCompProductionToY";
        WithType = "RapidityPlots/Mompng/" + PlotName + ".png";
        canvas3.Print(WithType.c_str());
        WithType = "RapidityPlots/MomPDF/" + PlotName + ".pdf";
        canvas3.Print(WithType.c_str());
        WithType = "RapidityPlots/MomC/" + PlotName + ".C";
        canvas3.Print(WithType.c_str());
        cout << "test 8" << endl;

        TCanvas canvas4("c4", "c4", 1000, 1000); //Ratio Plots
        canvas4.Divide(1, 3 + 2 * (1 - w));
        for (int i = 0; i < 3 + 2 * (1 - w); i++) {
            string NewName = "Ratio" + NamesOfPlots[i];
            TPad * p = (TPad *) canvas4.cd(i + 1);
            RatioPlots[NewName]->GetXaxis()->SetTitle("Rapidity");
            RatioPlots[NewName]->GetXaxis()->CenterTitle();
            cout << "OUR FIRST BIN IS: " << RatioPlots[NewName]->GetBinContent(1) << endl;
            RatioPlots[NewName]->Draw();
        }
        //canvas4.cd(0);

        PlotName = w == 0 ? "Mom_RatioPlots" : "PenUltimate_RatioPlots";
        WithType = "RapidityPlots/Mompng/" + PlotName + ".png";
        canvas4.Print(WithType.c_str());
        WithType = "RapidityPlots/MomPDF/" + PlotName + ".pdf";
        canvas4.Print(WithType.c_str());
        WithType = "RapidityPlots/MomC/" + PlotName + ".C";
        canvas4.Print(WithType.c_str());
cout<<"Test End"<<endl;
        string FileName = w == 0 ? "Mom_RapiditySeperated.root" : "PenUltimate_RapiditySeperated.root";
        TFile SavedHistos(FileName.c_str(), "recreate");
        for (size_t i = 0; i < NamesOfPlots.size(); i++) {
            AllPlots[NamesOfPlots[i]]->Write();
        }
        SavedHistos.Write();
    }
    return EXIT_SUCCESS;
}
