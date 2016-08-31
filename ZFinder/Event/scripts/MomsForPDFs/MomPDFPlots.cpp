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

const double phistarBins[] = {0.000, 0.004, 0.008, 0.012, 0.016, 0.020, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10};
size_t nphistar = (sizeof (phistarBins) / sizeof (phistarBins[0])) - 1;

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

void ExploreTree(TTree* tree, TLeaf* mom1, TLeaf* PenUltimateMom1, TLeaf* mom2, TLeaf* PenUltimateMom2) {

    TH2F ParentageChange("MomCompPenUltimateMom", "MomCompPenUltimateMom", 91, -39, 52, 91, -39, 52);

    for (int i = 0; i < tree->GetEntries(); i++) {
        tree->GetEntry(i);

        double mom1Value = mom1->GetValue() == 21 ? 6 : mom1->GetValue();
        double mom2Value = mom2->GetValue() == 21 ? 6 : mom2->GetValue();

        double PenUltimate1Offsetter = PenUltimateMom1->GetValue() > 0 ? 13 * PenUltimateMom1->GetValue() - 7 : PenUltimateMom1->GetValue()*13 + 5;
        if (PenUltimate1Offsetter > 45)PenUltimate1Offsetter = 45; //deals with the fact that gluons are 21, rather then following directly after

        double PenUltimate2Offsetter = PenUltimateMom2->GetValue() > 0 ? 13 * PenUltimateMom2->GetValue() - 7 : PenUltimateMom2->GetValue()*13 + 5;
        if (PenUltimate2Offsetter > 45)PenUltimate2Offsetter = 45; //deals with the fact that gluons are 21, rather then following directly after 


        ParentageChange.Fill(mom1Value + PenUltimate1Offsetter, mom2Value + PenUltimate2Offsetter);
    }

    TCanvas canvas("c2", "c2", 1100, 1000);
    canvas.cd();
    canvas.SetLogz();
    gStyle->SetCanvasColor(0);
    gStyle->SetStatBorderSize(1);
    gStyle->SetOptStat("");
    ParentageChange.Draw("colz");

    TLine line1(-26.5, -39, -26.5, 52);
    TLine line2(-13.5, -39, -13.5, 52);
    TLine line3(0, -39, 0, 52);
    TLine line4(13.5, -39, 13.5, 52);
    TLine line5(26.5, -39, 26.5, 52);
    TLine line6(39.5, -39, 39.5, 52);

    TLine line7(-39, -26.5, 52, -26.5);
    TLine line8(-39, -13.5, 52, -13.5);
    TLine line9(-39, 0, 52, 0);
    TLine line10(-39, 13.5, 52, 13.5);
    TLine line11(-39, 26.5, 52, 26.5);
    TLine line12(-39, 39.5, 52, 39.5);
    TLine line13(-39, 52.5, 52, 52.5);

    line1.SetLineColor(kBlack);
    line2.SetLineColor(kBlack);
    line3.SetLineColor(kBlack);
    line4.SetLineColor(kBlack);
    line5.SetLineColor(kBlack);
    line6.SetLineColor(kBlack);
    line7.SetLineColor(kBlack);
    line8.SetLineColor(kBlack);
    line9.SetLineColor(kBlack);
    line10.SetLineColor(kBlack);
    line11.SetLineColor(kBlack);
    line12.SetLineColor(kBlack);
    line13.SetLineColor(kBlack);

    line1.Draw();
    line2.Draw();
    line3.Draw();
    line4.Draw();
    line5.Draw();
    line6.Draw();
    line7.Draw();
    line8.Draw();
    line9.Draw();
    line10.Draw();
    line11.Draw();
    line12.Draw();
    line13.Draw();
    canvas.Print("PhiStarPlots/Mompng/EVERYTHing.png");
    canvas.Print("PhiStarPlots/MomPDF/EVERYTHing.pdf");
    canvas.Print("PhiStarPlots/MomC/EVERYTHing.C");

}

int main() {
    // Get7 a map of the histograms of the Z Masses
    const std::string file_name = "/data/whybee0a/user/lesko_2/fermi/MadWithInitial/Mad2016_8_25/results/AllMHWithMothers.root";
    // Open the file and load the tree
    const std::string TreeName = "ZFinder/Combined Single Reco/Combined Single Reco";
    TTree* tree = GetTTree(file_name, TreeName);

    TBranch* reco = tree->GetBranch("reco");
    TLeaf* PhiStar = reco->GetLeaf("z_phistar_born");
    TLeaf* Mom1 = reco->GetLeaf("z_mom1PDG");
    TLeaf* Mom2 = reco->GetLeaf("z_mom2PDG");
    TLeaf* PenUltimateMom1 = reco->GetLeaf("z_penultimate1PDG");
    TLeaf* PenUltimateMom2 = reco->GetLeaf("z_penultimate2PDG");
    TLeaf* Z_YBorn = reco->GetLeaf("z_yBorn");

    ExploreTree(tree, Mom1, PenUltimateMom1, Mom2, PenUltimateMom2);

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
        NamesOfPlots.push_back("QuarkAntiQuarkNotPair"); //11
        NamesOfPlots.push_back("Quark Quark And AntiQuark AntiQuark"); //12

        map<string, TH1*> AllPlots;
        AllPlots[NamesOfPlots[0]] = new TH1D(NamesOfPlots[0].c_str(), NamesOfPlots[0].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[1]] = new TH1D(NamesOfPlots[1].c_str(), NamesOfPlots[1].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[2]] = new TH1D(NamesOfPlots[2].c_str(), NamesOfPlots[2].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[3]] = new TH1D(NamesOfPlots[3].c_str(), NamesOfPlots[3].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[4]] = new TH1D(NamesOfPlots[4].c_str(), NamesOfPlots[4].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[5]] = new TH1D(NamesOfPlots[5].c_str(), NamesOfPlots[5].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[6]] = new TH1D(NamesOfPlots[6].c_str(), NamesOfPlots[6].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[7]] = new TH1D(NamesOfPlots[7].c_str(), NamesOfPlots[7].c_str(), nphistar, phistarBins); //Two quarks
        AllPlots[NamesOfPlots[8]] = new TH1D(NamesOfPlots[8].c_str(), NamesOfPlots[8].c_str(), nphistar, phistarBins); //Two Anti quarks
        AllPlots[NamesOfPlots[9]] = new TH1D(NamesOfPlots[9].c_str(), NamesOfPlots[9].c_str(), nphistar, phistarBins); //
        AllPlots[NamesOfPlots[10]] = new TH1D(NamesOfPlots[10].c_str(), NamesOfPlots[10].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[11]] = new TH1D(NamesOfPlots[11].c_str(), NamesOfPlots[11].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[12]] = new TH1D(NamesOfPlots[12].c_str(), NamesOfPlots[12].c_str(), nphistar, phistarBins);

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
                AllPlots["QuarkAntiQuarkPair"]->Fill(PhiStar->GetValue());
                AllPlots["UpQuarkPair"]->Fill(PhiStar->GetValue());
                ProductionVsY->Fill(0.1, Z_YBorn->GetValue()
                        );
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 2 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                AllPlots["QuarkAntiQuarkPair"]->Fill(PhiStar->GetValue());
                AllPlots["DownQuarkPair"]->Fill(PhiStar->GetValue());
                ProductionVsY->Fill(1.1, Z_YBorn->GetValue());

            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 3 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                AllPlots["QuarkAntiQuarkPair"]->Fill(PhiStar->GetValue());
                AllPlots["StrangeQuarkPair"]->Fill(PhiStar->GetValue());
                ProductionVsY->Fill(2.1, Z_YBorn->GetValue());
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 4 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                AllPlots["QuarkAntiQuarkPair"]->Fill(PhiStar->GetValue());
                AllPlots["CharmQuarkPair"]->Fill(PhiStar->GetValue());
                ProductionVsY->Fill(3.1, Z_YBorn->GetValue());
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 5 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                AllPlots["QuarkAntiQuarkPair"]->Fill(PhiStar->GetValue());
                AllPlots["BottomQuarkPair"]->Fill(PhiStar->GetValue());
                ProductionVsY->Fill(4.1, Z_YBorn->GetValue());
            } else if ((MomOrPenUltimateMom1->GetValue() == 21 && fabs(MomOrPenUltimateMom2->GetValue()) < 7) || (MomOrPenUltimateMom2->GetValue() == 21 && fabs(MomOrPenUltimateMom1->GetValue()) < 7)) {
                AllPlots["SingleQuark"]->Fill(PhiStar->GetValue());
                ProductionVsY->Fill(6.1, Z_YBorn->GetValue());
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 21 && MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                AllPlots["Gluon"]->Fill(PhiStar->GetValue());
                ProductionVsY->Fill(6.1, Z_YBorn->GetValue());
            } else if ((MomOrPenUltimateMom1->GetValue()) < 7 && (MomOrPenUltimateMom1->GetValue()) > 0 && (MomOrPenUltimateMom2->GetValue()) < 7 && (MomOrPenUltimateMom2->GetValue()) > 0) {
                AllPlots["TwoQuarks"]->Fill(PhiStar->GetValue());
                ProductionVsY->Fill(7.1, Z_YBorn->GetValue());
            } else if ((MomOrPenUltimateMom1->GetValue()) > -7 && (MomOrPenUltimateMom1->GetValue()) < 0 && (MomOrPenUltimateMom2->GetValue()) > -7 && (MomOrPenUltimateMom2->GetValue()) < 0) {
                AllPlots["TwoAntiQuarks"]->Fill(PhiStar->GetValue());
                ProductionVsY->Fill(7.1, Z_YBorn->GetValue());
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) < 7 && fabs(MomOrPenUltimateMom1->GetValue()) < 7) {
                AllPlots["QuarkAntiQuarkNotPair"]->Fill(PhiStar->GetValue());
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
            for (size_t j = 1; j <= nphistar; j++) {
                AllPlots[NamesOfPlots[i]]->SetBinContent(j, AllPlots[NamesOfPlots[i]]->GetBinContent(j) / (phistarBins[j] - phistarBins[j - 1]));
            }
        }
        cout << "test 4" << endl;
        for (size_t i = 0; i < NamesOfPlots.size(); i++) {

            TCanvas canvas("canvas", "canvas", 1000, 1000);
            canvas.cd();
            canvas.SetLogx();
            canvas.SetLogy();
            gStyle->SetCanvasColor(0);
            gStyle->SetStatBorderSize(1);
            gStyle->SetOptStat("");
            gStyle->SetOptFit();
            AllPlots[NamesOfPlots[i]]->GetXaxis()->SetRangeUser(.004, 10);
            AllPlots[NamesOfPlots[i]]->Draw();
            AllPlots[NamesOfPlots[i]]->SetLineWidth(2);

            string SaveName = NamesOfPlots[i];
            SaveName = 0 == w ? "Mom_" + SaveName : "PenUltimate_" + SaveName;
            string WithType = "PhiStarPlots/Mompng/" + SaveName + ".png";
            canvas.Print(WithType.c_str());
            WithType = "PhiStarPlots/MomPDF/" + SaveName + ".pdf";
            canvas.Print(WithType.c_str());
            WithType = "PhiStarPlots/MomC/" + SaveName + ".C";
            canvas.Print(WithType.c_str());



            //if (i == 8)canvas.Print("Broken.png");
        }
        cout << "test 5" << endl;

        TCanvas canvas("c2", "c2", 1000, 1000);
        canvas.cd();
        canvas.SetLogx();
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
            AllPlots[NamesOfPlots[0]]->SetXTitle("#phi^{*}");
            AllPlots[NamesOfPlots[0]]->GetXaxis()->CenterTitle();
            AllPlots[NamesOfPlots[0]]->Draw();
            AllPlots[NamesOfPlots[5]]->Draw("same");
        } else {
            AllPlots[NamesOfPlots[5]]->SetTitle("");
            AllPlots[NamesOfPlots[5]]->SetXTitle("#phi^{*}");
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
        leg->AddEntry(AllPlots[NamesOfPlots[12]], "qq or #bar{q}#bar{q}");
        leg->SetFillColor(0);
        leg->SetLineColor(0);
        leg->Draw("same");

        PlotName = w == 0 ? "Mom_AllLines.pn" : "PenUltimate_AllLines";
        string WithType = "PhiStarPlots/Mompng/" + PlotName + ".png";
        canvas.Print(WithType.c_str());
        WithType = "PhiStarPlots/MomPDF/" + PlotName + ".pdf";
        canvas.Print(WithType.c_str());
        WithType = "PhiStarPlots/MomC/" + PlotName + ".C";
        canvas.Print(WithType.c_str());
        TCanvas canvas3("c3", "c3", 1000, 1000);
        canvas3.cd();
        canvas3.SetLogz();
        gStyle->SetCanvasColor(0);
        gStyle->SetStatBorderSize(1);
        gStyle->SetOptStat("");
        cout << "test last" << endl;
        ProductionVsY->Draw("colz");
        PlotName = w == 0 ? "Mom_TwoDCompProductionToY" : "PenUltimate_TwoDCompProductionToY";
         WithType = "PhiStarPlots/Mompng/" + PlotName + ".png";
        canvas3.Print(WithType.c_str());
        WithType = "PhiStarPlots/MomPDF/" + PlotName + ".pdf";
        canvas3.Print(WithType.c_str());
        WithType = "PhiStarPlots/MomC/" + PlotName + ".C";
        canvas3.Print(WithType.c_str());
        cout << "test 7" << endl;

        TCanvas canvas4("c4", "c4", 1000, 1000); //Ratio Plots
        canvas4.Divide(1, 3 + 2 * (1 - w));
        //canvas4.SetLogx();
        //canvas4.SetLogy();
        for (int i = 0; i < 3 + 2 * (1 - w); i++) {
            string NewName = "Ratio" + NamesOfPlots[i];
            TPad * p = (TPad *) canvas4.cd(i + 1);
            p->SetLogx();
            RatioPlots[NewName]->GetXaxis()->SetRangeUser(.004, 10);
            RatioPlots[NewName]->GetXaxis()->SetTitle("#phi^{*}");
            RatioPlots[NewName]->GetXaxis()->CenterTitle();
            cout << "OUR FIRST BIN IS: " << RatioPlots[NewName]->GetBinContent(1) << endl;
            RatioPlots[NewName]->Draw();
        }
        //canvas4.cd(0);

        PlotName = w == 0 ? "Mom_RatioPlots" : "PenUltimate_RatioPlots";
        WithType = "PhiStarPlots/Mompng/" + PlotName + ".png";
        canvas4.Print(WithType.c_str());
        WithType = "PhiStarPlots/MomPDF/" + PlotName + ".pdf";
        canvas4.Print(WithType.c_str());
        WithType = "PhiStarPlots/MomC/" + PlotName + ".C";
        canvas4.Print(WithType.c_str());
    }
    return EXIT_SUCCESS;
}
