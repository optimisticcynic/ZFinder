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
#include "TH2.h"
#include "TF2.h"
#include "TGraphAsymmErrors.h"
#include <TTree.h>
#include "TSystem.h"
#include <TAxis.h>
#include <TLine.h>

#include <algorithm>
#include <set>
#include <vector>
#include <TH2.h>
#include <TColor.h>
#include <TFitResult.h>
#include <TGraph.h>
using namespace std; // yeah I am evil, get over it

const double phistarBins[] = {0.000, 0.004, 0.008, 0.012, 0.016, 0.020, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 5, 10};
size_t nphistar = (sizeof (phistarBins) / sizeof (phistarBins[0])) - 1;

const double yBins[] = {0.0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4};
size_t nY = (sizeof (yBins) / sizeof (yBins[0])) - 1;
size_t nbins = nphistar*nY;
bool Absolute = false;


const string NamesOfPlots[] = {
    "UpQuarkPair", //0
    "DownQuarkPair", //1
    "StrangeQuarkPair", //2
    "CharmQuarkPair", //3
    "BottomQuarkPair", //4
    "SingleQuark", //5
    "Gluon", //6
    "QuarkAntiQuarkNotPair", //7
    "TwoQuarks", //8
    "TwoAntiQuarks", //9
    "QuarkAntiQuarkPair", //10
    "QuarkQuarkAndAntiQuarkAntiQuark" //11
};
size_t numberofPlots = (sizeof (NamesOfPlots) / sizeof (NamesOfPlots[0]));

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

class HistosAndFits {
public:

    HistosAndFits(TH2D* DataPlot, map<string, TH2D*> AllPlots) : CorrilationMatrix(8) {
        DataPlotClass = (TH2D*) DataPlot->Clone("forClass");
        AllPlotsClass = AllPlots;

    };
    //~HistosAndFits(TH2D* DataPlot, map<string, TH2D*> AllPlots) {
    //  delete DataPlotClass ;
    //  delete AllPlotsClass ;
    //};

    void GetFitParameters(double *Fitparm) {
        TH2D* AllOnes = new TH2D("all Ones", "all Ones", nphistar, 1, nphistar + 1, nY, 1, nY + 1); //should be filled with all ones.
        for (size_t YBin = 1; YBin <= nY; YBin++) {
            for (size_t PhistarBin = 1; PhistarBin <= nphistar; PhistarBin++) {
                AllOnes->SetBinContent(PhistarBin, YBin, 1);
                double ErrorsSquared = 0;
                double TotalTop = 0;
                for (size_t paramIndex = 0; paramIndex < 11; paramIndex++) {
                    double ErrorOfOne = AllPlotsClass[NamesOfPlots[paramIndex]]->GetBinError(PhistarBin, YBin);
                    //if(PhistarBin==1)cout<<AllPlotsClass[NamesOfPlots[paramIndex]]->GetBinContent(PhistarBin, YBin)<<"  For phi* "<<PhistarBin<<" YBin "<<YBin<<" our Error is "<<ErrorOfOne<<endl;
                    ErrorsSquared += ErrorOfOne*ErrorOfOne;
                    TotalTop += AllPlotsClass[NamesOfPlots[paramIndex]]->GetBinContent(PhistarBin, YBin);
                }
                double TotalTopSquared = TotalTop*TotalTop;
                ErrorsSquared /= DataPlotClass->GetBinContent(PhistarBin, YBin);
                ErrorsSquared /= DataPlotClass->GetBinContent(PhistarBin, YBin);
                double BottomForth = pow(DataPlotClass->GetBinContent(PhistarBin, YBin), 4);

                ErrorsSquared += DataPlotClass->GetBinError(PhistarBin, YBin) * DataPlotClass->GetBinError(PhistarBin, YBin) * TotalTopSquared / BottomForth;
                //cout<<"For phi* "<<PhistarBin<<" YBin "<<YBin<<" our Error is "<<sqrt(ErrorsSquared)<<endl;
                AllOnes->SetBinError(PhistarBin, YBin, sqrt(ErrorsSquared));

            }
        }

        //Calculates total error of each thing hackishly since can't have error on the function
        for (size_t YBin = 1; YBin <= nY; YBin++) {
            for (size_t PhistarBin = 1; PhistarBin <= nphistar; PhistarBin++) {
                AllOnes->SetBinContent(PhistarBin, YBin, 1);
            }
        }

        //TF2(const char *name, Double_t (*fcn)(Double_t *, Double_t *), Double_t xmin=0, Double_t xmax=1, Double_t ymin=0, Double_t ymax=1, Int_t npar=0);
        //TF2* FitFuction = new TF2("fit", (&HistosAndFits::DiffFunction) , 1.0, 35.0, 1.0, 6.0, 12);
        using namespace std::placeholders;
        TF2* FitFuction = new TF2("fit", this, &HistosAndFits::DiffFunction, 1.0, 36.0, 1.0, 7.0, 8, "", "");



        double MaxOffset;
        FitFuction->SetParameter(0, 1);
        FitFuction->SetParName(0, "UUBar+ddBar");
        MaxOffset = .1 * DataPlotClass->Integral() / (AllPlotsClass[NamesOfPlots[0]]->Integral() + AllPlotsClass[NamesOfPlots[1]]->Integral());
        //if (MaxOffset > .5)MaxOffset = .5;
        //FitFuction->SetParLimits(0, 1 - MaxOffset, 1 + MaxOffset);
        if (MaxOffset > 1)FitFuction->SetParLimits(0, 0, 2);
        else FitFuction->SetParLimits(0, 1 - MaxOffset, 1 + MaxOffset);

        FitFuction->SetParameter(7, 1);
        FitFuction->SetParName(7, "qq+AntiqAntiq");
        MaxOffset = .1 * DataPlotClass->Integral() / (AllPlotsClass[NamesOfPlots[8]]->Integral() + AllPlotsClass[NamesOfPlots[9]]->Integral());
        if (MaxOffset > 1)FitFuction->SetParLimits(7, 0, 2);
        else FitFuction->SetParLimits(7, 1 - MaxOffset, 1 + MaxOffset);


        for (size_t paramIndex = 2; paramIndex < 8; paramIndex++) {
            MaxOffset = .1 * DataPlotClass->Integral() / (AllPlotsClass[NamesOfPlots[paramIndex]]->Integral());
            //if (MaxOffset > .5)MaxOffset = .5;
            if (MaxOffset > 1)MaxOffset = 1;
            FitFuction->SetParameter(paramIndex - 1, 1);
            FitFuction->SetParLimits(paramIndex - 1, 1 - MaxOffset, 1 + MaxOffset);
            FitFuction->SetParName(paramIndex - 1, NamesOfPlots[paramIndex].c_str());
            //string NewName = NamesOfPlots[paramIndex] + "NormPlot";
            //AllPlotsClassNormalized[NamesOfPlots[paramIndex]] = (TH2D*) AllPlotsClass[NamesOfPlots[paramIndex]]->Clone(NewName.c_str());
            //if (AllPlotsClassNormalized[NamesOfPlots[paramIndex]]->Integral() != 0) {
            //    AllPlotsClassNormalized[NamesOfPlots[paramIndex]]->Scale(1 / AllPlotsClassNormalized[NamesOfPlots[paramIndex]]->Integral());
            //    double Total = AllPlotsClass[NamesOfPlots[paramIndex]]->Integral();
            //    double NumbeOfEventsChanged = .1 * DataPlotClass->Integral();
            //    if (Total - NumbeOfEventsChanged < 0)NumbeOfEventsChanged = .5 * Total;
            //    FitFuction->SetParameter(paramIndex, Total);
            //    FitFuction->SetParLimits(paramIndex, Total - NumbeOfEventsChanged, Total + NumbeOfEventsChanged);
            //
            //} else {
            //    FitFuction->SetParameter(paramIndex, 0);
            //    cout << "No Events in " << NamesOfPlots[paramIndex] << endl;
            //}
            //double TotalShouldBe = AllPlotsClass[NamesOfPlots[paramIndex]]->Integral();
        }




        TCanvas * c = new TCanvas("c", "c", 600, 600);
        c->SetRightMargin(.15);

        //Test Color
        Double_t Red[3] = {1.00, 1.00, 0.00};
        Double_t Green[3] = {0.00, 1.00, 0.00};
        Double_t Blue[3] = {0.00, .700, 1.00};
        Double_t Length[3] = {0.00, 0.50, 1.00};
        Int_t nb = 50;
        TColor::CreateGradientColorTable(3, Length, Red, Green, Blue, nb);


        //End Test
        //c->SetLogx();
        FitFuction->SetMaximum(1.2);
        FitFuction->SetMinimum(.8);
        FitFuction->Draw("colz");
        c->SaveAs("FitFunction.png");
        TFitResultPtr Test = AllOnes->Fit(FitFuction, "s");
        CorrilationMatrix = Test->GetCorrelationMatrix();
        FitFuction->Draw("colz");
        if (AllPlotsClass["BottomQuarkPair"]->Integral())
            c->SaveAs("FitFunctionAfterMomFit.png");
        else
            c->SaveAs("FitFunctionAfterPentFit.png");
        cout << " OKAY FOR Graph uu and dd WE CHANGED BY A FACTOR OF " << FitFuction->GetParameter(0) << endl;
        for (size_t paramIndex = 0; paramIndex < 8; paramIndex++) {
            Fitparm[paramIndex] = FitFuction->GetParameter(paramIndex);
            if (paramIndex > 1 && AllPlotsClass[NamesOfPlots[paramIndex]]->Integral() != 0)cout << " OKAY FOR Graph " << NamesOfPlots[paramIndex] << " WE CHANGED BY A FACTOR OF " << Fitparm[paramIndex - 1] << endl;

        }
    };

    void PrintCorrilations() {
        cout << "Corrilation matrix" << endl;
        cout << "UUbar+ddbar\tSSBar\tCCBar\tBBbar\tqg+qbarg\tgg\tqqbar!pair\tqq&qbarqbar" << endl;
        for (size_t i = 0; i < 8; i++) {
            for (size_t j = 0; j < 8; j++) {
                //cout << CorrilationMatrix(i, j) << "\t";
                printf("%.2f\t", CorrilationMatrix(i, j));
                if (j == 0 || j == 4 || j == 7)cout << "\t";
            }
            cout << endl;
        }

    }
private:

    Double_t DiffFunction(Double_t * x, Double_t * par) {
        double PhistarBin = x[0];
        double Rapidity = x[1];
        size_t PhistarbinDiscrete = (size_t) PhistarBin;
        size_t RapidityDiscrete = (size_t) Rapidity;
        double ReturnValue = 0;
        ReturnValue += par[0] * AllPlotsClass["UpQuarkPair"]->GetBinContent(PhistarbinDiscrete, RapidityDiscrete);
        ReturnValue += par[0] * AllPlotsClass["DownQuarkPair"]->GetBinContent(PhistarbinDiscrete, RapidityDiscrete);
        ReturnValue += par[1] * AllPlotsClass["StrangeQuarkPair"]->GetBinContent(PhistarbinDiscrete, RapidityDiscrete);
        ReturnValue += par[2] * AllPlotsClass["CharmQuarkPair"]->GetBinContent(PhistarbinDiscrete, RapidityDiscrete);
        ReturnValue += par[3] * AllPlotsClass["BottomQuarkPair"]->GetBinContent(PhistarbinDiscrete, RapidityDiscrete);
        ReturnValue += par[4] * AllPlotsClass["SingleQuark"]->GetBinContent(PhistarbinDiscrete, RapidityDiscrete);
        ReturnValue += par[5] * AllPlotsClass["Gluon"]->GetBinContent(PhistarbinDiscrete, RapidityDiscrete);
        ReturnValue += par[6] * AllPlotsClass["QuarkAntiQuarkNotPair"]->GetBinContent(PhistarbinDiscrete, RapidityDiscrete);
        ReturnValue += par[7] * AllPlotsClass["TwoQuarks"]->GetBinContent(PhistarbinDiscrete, RapidityDiscrete);
        ReturnValue += par[7] * AllPlotsClass["TwoAntiQuarks"]->GetBinContent(PhistarbinDiscrete, RapidityDiscrete);
        ReturnValue /= DataPlotClass->GetBinContent(PhistarbinDiscrete, RapidityDiscrete);
        // Double_t* ReturnPointer;
        //*ReturnPointer = ReturnValue;
        if ((PhistarbinDiscrete == 35 || PhistarbinDiscrete == 33 || PhistarbinDiscrete == 34) && RapidityDiscrete == 6)ReturnValue = 1;
        return ReturnValue;
    }
    TH2D* DataPlotClass;
    map<string, TH2D*> AllPlotsClass;
    //map<string, TH2D*> AllPlotsClassNormalized;
    TMatrixDSym CorrilationMatrix;

};

TH2D* SplitGraph(TGraphAsymmErrors* graph) {
    TH2D* Data2DHisto = new TH2D("TwoDHisto", "TwoDHisto", nphistar, phistarBins, nY, yBins);
    for (uint i = 0; i < nY; i++) {
        for (uint j = 0; j < nphistar; j++) {
            int bin = i * nphistar + j;
            double x, y;
            graph->GetPoint(bin, x, y);
            Data2DHisto->SetBinContent(j + 1, i + 1, y);
            Data2DHisto->SetBinError(j + 1, i + 1, graph->GetErrorYlow(bin));
        }

    }
    return Data2DHisto;
}

int main() {
    // Get7 a map of the histograms of the Z Masses
    const std::string Data_file_name = "TwoDFiles/Data_Graph_Norm_PH_BornTT.root";

    const std::string file_name = "/data/whybee0a/user/lesko_2/fermi/MadWithInitial/Mad2016_8_25/results/AllMHWithMothers.root";
    // Open the file and load the tree
    const std::string TreeName = "ZFinder/Combined Gen Cuts Reco/Combined Gen Cuts Reco";
    TTree* tree = GetTTree(file_name, TreeName);

    TBranch* reco = tree->GetBranch("reco");
    TLeaf* PhiStar = reco->GetLeaf("z_phistar_born");
    TLeaf* Mom1 = reco->GetLeaf("z_mom1PDG");
    TLeaf* Mom2 = reco->GetLeaf("z_mom2PDG");
    TLeaf* PenUltimateMom1 = reco->GetLeaf("z_penultimate1PDG");
    TLeaf* PenUltimateMom2 = reco->GetLeaf("z_penultimate2PDG");
    TLeaf* Z_YBorn = reco->GetLeaf("z_yBorn");



    TFile Data_file(Data_file_name.c_str(), "read");
    TGraphAsymmErrors* DataWhole = (TGraphAsymmErrors*) Data_file.Get("Graph");

    for (int w = 0; w < 2; w++) {
        TH2D* AllData = SplitGraph(DataWhole);
        TH2D* AllMC = new TH2D("ALLMC", "ALLMC", nphistar, phistarBins, nY, yBins);
        AllData->Sumw2();

        string PlotName;
        TLeaf* MomOrPenUltimateMom1 = w == 0 ? Mom1 : PenUltimateMom1;
        TLeaf* MomOrPenUltimateMom2 = w == 0 ? Mom2 : PenUltimateMom2;
        map<string, TH2D*> MCPlots;
        for (size_t i = 0; i < numberofPlots; i++) {
            MCPlots[NamesOfPlots[i]] = new TH2D(NamesOfPlots[i].c_str(), NamesOfPlots[i].c_str(), nphistar, phistarBins, nY, yBins);
            MCPlots[NamesOfPlots[i]]->Sumw2();
        }
        double Normalizer = 0;

        for (int i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            if (PhiStar->GetValue() == -1)continue;
            Normalizer++;
            double ZYABS = fabs(Z_YBorn->GetValue());
            AllMC->Fill(PhiStar->GetValue(), ZYABS);

            if (fabs(MomOrPenUltimateMom1->GetValue()) == 1 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                MCPlots["QuarkAntiQuarkPair"]->Fill(PhiStar->GetValue(), ZYABS);
                MCPlots["UpQuarkPair"]->Fill(PhiStar->GetValue(), ZYABS);
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 2 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                MCPlots["QuarkAntiQuarkPair"]->Fill(PhiStar->GetValue(), ZYABS);
                MCPlots["DownQuarkPair"]->Fill(PhiStar->GetValue(), ZYABS);
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 3 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                MCPlots["QuarkAntiQuarkPair"]->Fill(PhiStar->GetValue(), ZYABS);
                MCPlots["StrangeQuarkPair"]->Fill(PhiStar->GetValue(), ZYABS);
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 4 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                MCPlots["QuarkAntiQuarkPair"]->Fill(PhiStar->GetValue(), ZYABS);
                MCPlots["CharmQuarkPair"]->Fill(PhiStar->GetValue(), ZYABS);
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 5 && -MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                MCPlots["QuarkAntiQuarkPair"]->Fill(PhiStar->GetValue(), ZYABS);
                MCPlots["BottomQuarkPair"]->Fill(PhiStar->GetValue(), ZYABS);
            } else if ((MomOrPenUltimateMom1->GetValue() == 21 && fabs(MomOrPenUltimateMom2->GetValue()) < 7) || (MomOrPenUltimateMom2->GetValue() == 21 && fabs(MomOrPenUltimateMom1->GetValue()) < 7)) {
                MCPlots["SingleQuark"]->Fill(PhiStar->GetValue(), ZYABS);
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) == 21 && MomOrPenUltimateMom1->GetValue() == MomOrPenUltimateMom2->GetValue()) {
                MCPlots["Gluon"]->Fill(PhiStar->GetValue(), ZYABS);
            } else if ((MomOrPenUltimateMom1->GetValue()) < 7 && (MomOrPenUltimateMom1->GetValue()) > 0 && (MomOrPenUltimateMom2->GetValue()) < 7 && (MomOrPenUltimateMom2->GetValue()) > 0) {
                MCPlots["TwoQuarks"]->Fill(PhiStar->GetValue(), ZYABS);
            } else if ((MomOrPenUltimateMom1->GetValue()) > -7 && (MomOrPenUltimateMom1->GetValue()) < 0 && (MomOrPenUltimateMom2->GetValue()) > -7 && (MomOrPenUltimateMom2->GetValue()) < 0) {
                MCPlots["TwoAntiQuarks"]->Fill(PhiStar->GetValue(), ZYABS);
                MCPlots["QuarkQuarkAndAntiQuarkAntiQuark"]->Fill(PhiStar->GetValue(), ZYABS);
            } else if (fabs(MomOrPenUltimateMom1->GetValue()) < 7 && fabs(MomOrPenUltimateMom1->GetValue()) < 7) {
                MCPlots["QuarkAntiQuarkNotPair"]->Fill(PhiStar->GetValue(), ZYABS);
                MCPlots["QuarkQuarkAndAntiQuarkAntiQuark"]->Fill(PhiStar->GetValue(), ZYABS);
            } else {
                cout << "our mom1 is " << MomOrPenUltimateMom1->GetValue() << " and mom 2 is: " << MomOrPenUltimateMom2->GetValue() << endl;
                cout << "SOmething broke" << endl;
            }
        }





        //double Weight = 19.7*1177.3 * 3/tree->GetEntries()/tree->GetEntries();
        TH2F* AddTogether = 0;
        for (auto const &iterator : MCPlots) {
            if (iterator.first == "QuarkAntiQuarkPair")continue;
            if (AddTogether == 0)AddTogether = (TH2F*) iterator.second->Clone("TestAddition");
            else AddTogether->Add((TH2F*) iterator.second);
        }

        for (auto const &iterator : MCPlots) {//Normalizing all the plots
            for (uint i = 1; i <= nY; i++) {
                for (uint j = 1; j <= nphistar; j++) {
                    double NormConstant = 1.0 / AllMC->Integral() / .4 / (phistarBins[j] - phistarBins[j - 1]);
                    // cout << "our bin was " << iterator.second->GetBinError(j, i) << endl;
                    iterator.second->SetBinContent(j, i, iterator.second->GetBinContent(j, i) * NormConstant);
                    iterator.second->SetBinError(j, i, iterator.second->GetBinError(j, i) * NormConstant);
                }
            }
        }

        double FullInt = AllMC->Integral();
        FullInt *= .4;
        AllMC->Scale(1 / AllMC->Integral());
        cout << "Sanity check 1 " << AllMC->Integral() << endl;
        for (uint i = 1; i <= nY; i++) {
            for (uint j = 1; j <= nphistar; j++) {
                double NormConstant = 1.0 / .4 / (phistarBins[j] - phistarBins[j - 1]);
                AllMC->SetBinContent(j, i, AllMC->GetBinContent(j, i) * NormConstant);
                //cout << " Our MC is " << AllMC->GetBinContent(j, i) << "  and our Data is " << AllData->GetBinContent(j, i) << endl;
            }
        }

        HistosAndFits MakeFits(AllData, MCPlots);
        double FitParam[8];
        MakeFits.GetFitParameters(FitParam);

        vector<TH1D> AllRatioPlots;
        AllRatioPlots.push_back(TH1D("YBin0", "", nphistar, phistarBins));
        AllRatioPlots.push_back(TH1D("YBin1", "", nphistar, phistarBins));
        AllRatioPlots.push_back(TH1D("YBin2", "", nphistar, phistarBins));
        AllRatioPlots.push_back(TH1D("YBin3", "", nphistar, phistarBins));
        AllRatioPlots.push_back(TH1D("YBin4", "", nphistar, phistarBins));
        AllRatioPlots.push_back(TH1D("YBin5", "", nphistar, phistarBins));
        
        TGraphAsymmErrors* Combined = new TGraphAsymmErrors(nbins);
        for (size_t YBin = 1; YBin <= 6; YBin++) {
            for (size_t PhistarBin = 1; PhistarBin <= nphistar; PhistarBin++) {
                double BinContent = 0;



                BinContent += FitParam[0] * MCPlots["UpQuarkPair"]->GetBinContent(PhistarBin, YBin);
                BinContent += FitParam[0] * MCPlots["DownQuarkPair"]->GetBinContent(PhistarBin, YBin);
                BinContent += FitParam[1] * MCPlots["StrangeQuarkPair"]->GetBinContent(PhistarBin, YBin);
                BinContent += FitParam[2] * MCPlots["CharmQuarkPair"]->GetBinContent(PhistarBin, YBin);
                BinContent += FitParam[3] * MCPlots["BottomQuarkPair"]->GetBinContent(PhistarBin, YBin);
                BinContent += FitParam[4] * MCPlots["SingleQuark"]->GetBinContent(PhistarBin, YBin);
                BinContent += FitParam[5] * MCPlots["Gluon"]->GetBinContent(PhistarBin, YBin);
                BinContent += FitParam[7] * MCPlots["TwoQuarks"]->GetBinContent(PhistarBin, YBin);
                BinContent += FitParam[7] * MCPlots["TwoAntiQuarks"]->GetBinContent(PhistarBin, YBin);
                BinContent += FitParam[6] * MCPlots["QuarkAntiQuarkNotPair"]->GetBinContent(PhistarBin, YBin);

                size_t CombinedBin = PhistarBin+YBin*nphistar-1-nphistar;
                double XPosition=(phistarBins[PhistarBin]+phistarBins[PhistarBin-1])/2+10*(YBin-1);
                Combined->SetPoint(CombinedBin,XPosition,BinContent);
                if (AllData->GetBinContent(PhistarBin, YBin) != 0)BinContent = BinContent / AllData->GetBinContent(PhistarBin, YBin);
                else BinContent = 1;
                if (YBin == 6 && PhistarBin == 35)BinContent = 1;
                // if(YBin==6&&PhistarBin==35)cout<<" our bin mc has  for phistar "<<PhistarBin<<" is "<<BinContent<<" aNd all data is "<<AllData->GetBinContent(PhistarBin, YBin)<<endl;

                AllRatioPlots[YBin - 1].SetBinContent(PhistarBin, BinContent);

            }
        }

        
        
        
        string FileName;
        if (Absolute) FileName = w == 0 ? "Mom_PhiStarFitted_abs.root" : "PenUltimate_PhiStarFitted_abs.root";
        else FileName = w == 0 ? "Mom_PhiStarFitted_norm.root" : "PenUltimate_PhiStarFitted_norm.root";
        FileName = "Output/"+FileName;
        TFile SavedHistos(FileName.c_str(), "recreate");
        Combined->Write("combined");

        MakeFits.PrintCorrilations();
        TCanvas c1("c1", "c1", 600, 600); //New Phi* Ratio Distribution
        //c1.SetLogy();
        c1.Divide(1, 6, 0, 0);
        c1.SetLogx(1);
        for (size_t i = 0; i < 6; i++) {
            c1.cd(i + 1);
            TPad * p = (TPad *) c1.cd(i + 1);
            p->SetLogx();
            AllRatioPlots[i].GetYaxis()->SetRangeUser(.8, 1.1);
            AllRatioPlots[i].GetXaxis()->SetRangeUser(4e-3, 10);
            AllRatioPlots[i].Draw();
        }

        c1.cd(0);
        if (w == 0) c1.Print("TestMoms.pdf");
        else c1.Print("TestPenultimate.pdf");




        map<string, TH1*> AllPlots;
        AllPlots[NamesOfPlots[0]] = new TH1D(NamesOfPlots[0].c_str(), NamesOfPlots[0].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[1]] = new TH1D(NamesOfPlots[1].c_str(), NamesOfPlots[1].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[2]] = new TH1D(NamesOfPlots[2].c_str(), NamesOfPlots[2].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[3]] = new TH1D(NamesOfPlots[3].c_str(), NamesOfPlots[3].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[4]] = new TH1D(NamesOfPlots[4].c_str(), NamesOfPlots[4].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[5]] = new TH1D(NamesOfPlots[5].c_str(), NamesOfPlots[5].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[6]] = new TH1D(NamesOfPlots[6].c_str(), NamesOfPlots[6].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[6]] = new TH1D(NamesOfPlots[6].c_str(), NamesOfPlots[6].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[7]] = new TH1D(NamesOfPlots[7].c_str(), NamesOfPlots[7].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[8]] = new TH1D(NamesOfPlots[8].c_str(), NamesOfPlots[8].c_str(), nphistar, phistarBins);
        AllPlots[NamesOfPlots[9]] = new TH1D(NamesOfPlots[9].c_str(), NamesOfPlots[9].c_str(), nphistar, phistarBins);
        AllPlots["Quark Quark And AntiQuark AntiQuark"] = new TH1D("Quark Quark And AntiQuark AntiQuark", "Quark Quark And AntiQuark AntiQuark", nphistar, phistarBins); //

        for (size_t YBin = 1; YBin <= 6; YBin++) {
            for (size_t PhistarBin = 1; PhistarBin <= nphistar; PhistarBin++) {
                AllPlots[NamesOfPlots[0]]->Fill(phistarBins[PhistarBin - 1] + .0001, FullInt * FitParam[0] * MCPlots[NamesOfPlots[0]]->GetBinContent(PhistarBin, YBin));
                AllPlots[NamesOfPlots[1]]->Fill(phistarBins[PhistarBin - 1] + .0001, FullInt * FitParam[0] * MCPlots[NamesOfPlots[1]]->GetBinContent(PhistarBin, YBin));
                AllPlots[NamesOfPlots[2]]->Fill(phistarBins[PhistarBin - 1] + .0001, FullInt * FitParam[1] * MCPlots[NamesOfPlots[2]]->GetBinContent(PhistarBin, YBin));
                AllPlots[NamesOfPlots[3]]->Fill(phistarBins[PhistarBin - 1] + .0001, FullInt * FitParam[2] * MCPlots[NamesOfPlots[3]]->GetBinContent(PhistarBin, YBin));
                AllPlots[NamesOfPlots[4]]->Fill(phistarBins[PhistarBin - 1] + .0001, FullInt * FitParam[3] * MCPlots[NamesOfPlots[4]]->GetBinContent(PhistarBin, YBin));
                AllPlots[NamesOfPlots[5]]->Fill(phistarBins[PhistarBin - 1] + .0001, FullInt * FitParam[4] * MCPlots[NamesOfPlots[5]]->GetBinContent(PhistarBin, YBin));
                AllPlots[NamesOfPlots[6]]->Fill(phistarBins[PhistarBin - 1] + .0001, FullInt * FitParam[5] * MCPlots[NamesOfPlots[6]]->GetBinContent(PhistarBin, YBin));
                AllPlots[NamesOfPlots[8]]->Fill(phistarBins[PhistarBin - 1] + .0001, MCPlots[NamesOfPlots[8]]->GetBinContent(PhistarBin, YBin));
                AllPlots[NamesOfPlots[9]]->Fill(phistarBins[PhistarBin - 1] + .0001, MCPlots[NamesOfPlots[9]]->GetBinContent(PhistarBin, YBin));
                AllPlots["Quark Quark And AntiQuark AntiQuark"] ->Fill(phistarBins[PhistarBin - 1] + .0001, FullInt * FitParam[7] * MCPlots["TwoQuarks"]->GetBinContent(PhistarBin, YBin));
                AllPlots["Quark Quark And AntiQuark AntiQuark"] ->Fill(phistarBins[PhistarBin - 1] + .0001, FullInt * FitParam[7] * MCPlots["TwoAntiQuarks"]->GetBinContent(PhistarBin, YBin));
            }
        }


        TCanvas c3("canvas", "canvas", 1000, 1000);
        c3.cd();
        c3.SetLogx();
        c3.SetLogy();
        gStyle->SetCanvasColor(0);
        gStyle->SetStatBorderSize(1);
        gStyle->SetOptStat("");
        gStyle->SetOptFit();
        AllPlots["TwoQuarks"]->SetLineColor(kBlue);
        AllPlots["TwoAntiQuarks"]->SetLineColor(kRed);
        AllPlots["TwoQuarks"]->Draw();
        AllPlots["TwoAntiQuarks"]->Draw("same");
        TLegend* leg2 = new TLegend(0.7, 0.70, 0.87, 0.89);
        leg2->AddEntry(AllPlots["TwoQuarks"], "qq");
        leg2->AddEntry(AllPlots["TwoAntiQuarks"], "#bar{q}#bar{q}");
        leg2->SetFillColor(0);
        leg2->SetLineColor(0);
        leg2->Draw();


        c3.Print("qqVsqbarqbar.pdf");

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
            AllPlots[NamesOfPlots[0]]->GetXaxis()->SetRangeUser(.004, 10);
            AllPlots[NamesOfPlots[0]]->Draw();
            AllPlots[NamesOfPlots[5]]->Draw("same");
        } else {
            AllPlots[NamesOfPlots[5]]->SetTitle("");
            AllPlots[NamesOfPlots[5]]->SetXTitle("#phi^{*}");
            AllPlots[NamesOfPlots[5]]->GetXaxis()->CenterTitle();
            AllPlots[NamesOfPlots[5]]->Draw();
            AllPlots[NamesOfPlots[5]]->GetXaxis()->SetRangeUser(.004, 10);
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
        leg->AddEntry(AllPlots[NamesOfPlots[5]], "qg or #bar{q}g");
        leg->AddEntry(AllPlots[NamesOfPlots[6]], "gg");
        //leg->AddEntry(AllPlots[8], "Broken");NamesOfPlots[0]], "Up");
        leg->AddEntry(AllPlots["Quark Quark And AntiQuark AntiQuark"], "qq or #bar{q}#bar{q}");
        leg->SetFillColor(0);
        leg->SetLineColor(0);
        leg->Draw("same");

        if (w == 0)canvas.Print("FullGraphsFITMom.pdf");
        else canvas.Print("FullGraphsFITPen.pdf");
        for (auto const &iterator : MCPlots) {
            //cout << iterator.first << ' ' << iterator.second->GetName() << endl;
            delete iterator.second;
        }
        delete AllData;
        delete AllMC;
    }


    return EXIT_SUCCESS;
}
