// Interface
#include "same_sign.h"  // branch_struct

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
#include <TDirectory.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TFitResult.h>
#include <TFitResultPtr.h>

// RooFit
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooDataHist.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooGenericPdf.h"
#include "RooHistPdf.h"
#include "RooPlot.h"
#include "RooRealVar.h"

// Style
#include "PlotStyle.h"

// ZFinder
#include "../../interface/WeightID.h"
#include "../../interface/ATLASBins.h"  // ATLAS_PHISTAR_BINNING

const double phistarBins[] = {0.000, 0.004, 0.008, 0.012, 0.016, 0.020, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10};
size_t nphistar = (sizeof (phistarBins) / sizeof (phistarBins[0])) - 1;


const bool SeperateYs = false;
const double YSeperations[] = {0, .4, .8, 1.2, 1.6, 2.0, 2.4};
const size_t nYSeper = (sizeof (YSeperations) / sizeof (YSeperations[0])) - 1;
const bool debug = false;
const bool AlexFiles = true;

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

double GetOverallNormalization(const std::string NAME) {
    const double DATA_LUMI = 19712;
    std::map<std::string, double> NORM = {
        //{"Signal", 3531.89 / 30459500.},
        //{"Signal", 1966.7 / (4.270546*1000*10000.)},
        {"BG_Ditau", 1966.7 / 47271600.},
        {"BG_TTBar", 23.64 / 4246440},
        {"BG_single_t", 11.1 / 497658},
        {"BG_single_tbar", 11.1 / 493460.},
        {"BG_ww", 54.84 / 10000430.},
        {"BG_wz", 33.21 / 10000280.},
        {"BG_zz", 17.0 / 9799908.},
    };
    if (AlexFiles) NORM["Signal"] = 3531.89 / 30459500.;
    else NORM["Signal"] = 1966.7 / (4.270546 * 1000 * 10000.);
    const double WEIGHT = DATA_LUMI * NORM.at(NAME);
    return WEIGHT;
}

double GetWeight(
        const int& WEIGHT_SIZE,
        const double WEIGHTS[],
        const int WEIGHTIDS[]
        ) {
    double weight = 1.;

    // Loop over the weights and use it if it is one of correct
    for (int i = 0; i < WEIGHT_SIZE; ++i) {
        switch (WEIGHTIDS[i]) {
            case zf::WeightID::GEN_MC:
            case zf::WeightID::PILEUP:
            case zf::WeightID::VETO:
            case zf::WeightID::LOOSE:
            case zf::WeightID::MEDIUM:
            case zf::WeightID::TIGHT:
            case zf::WeightID::SINGLE_TRIG:
            case zf::WeightID::DOUBLE_TRIG:
            case zf::WeightID::GSF_RECO:
                weight *= WEIGHTS[i];
                break;
            default:
                break;
        }
    }

    return weight;
}

histogram_map Get2DHistoMap(double Ymin = 0, double YMax = 2.4) {
    // The list of files
    std::map<std::string, std::string> files_to_open = {
        {"Data", "/data/whybee0a/user/gude_2/Data/20150306_SingleElectron_2012ALL_same_sign/20150306_SingleElectron_2012ALL_same_sign.root"},
        //{"Signal", "/data/whybee0a/user/gude_2/MC/20150219_MC_CTEQ6LL_same_sign_no_mass_cut/MadGraph_hadded.root"}, 
        {"BG_Ditau", "/data/whybee0a/user/gude_2/MC/20150219_MC_CTEQ6LL_same_sign_no_mass_cut/BG_Ditau_hadded.root"},
        {"BG_TTBar", "/data/whybee0a/user/gude_2/MC/20150219_MC_CTEQ6LL_same_sign_no_mass_cut/BG_TTBar_hadded.root"},
        {"BG_single_t", "/data/whybee0a/user/gude_2/MC/20150219_MC_CTEQ6LL_same_sign_no_mass_cut/BG_singlet_tw_hadded.root"},
        {"BG_single_tbar", "/data/whybee0a/user/gude_2/MC/20150219_MC_CTEQ6LL_same_sign_no_mass_cut/BG_singlet_tbarw_hadded.root"},
        {"BG_ww", "/data/whybee0a/user/gude_2/MC/20150219_MC_CTEQ6LL_same_sign_no_mass_cut/BG_ww_hadded.root"},
        {"BG_wz", "/data/whybee0a/user/gude_2/MC/20150219_MC_CTEQ6LL_same_sign_no_mass_cut/BG_wz_hadded.root"},
        {"BG_zz", "/data/whybee0a/user/gude_2/MC/20150219_MC_CTEQ6LL_same_sign_no_mass_cut/BG_zz_hadded.root"},


        //{"Data", "/data/whybee0a/user/lesko_2/fermi/Output/ZfinderoutputData15-9-8/2012ABCD15-9-8.root"},
        ////{"Signal", "/data/whybee0a/user/lesko_2/fermi/Output/Zfinder2MCPDFweightBorn15-7-2/Powheg15-7-04.root"},
        //{"BG_Ditau", "/data/whybee0a/user/lesko_2/fermi/Output/ZfinderBGFiles15-7-15/BG_Ditau15-7-15.root"},
        //{"BG_TTBar", "/data/whybee0a/user/lesko_2/fermi/Output/ZfinderBGFiles15-7-15/BG_TTBar15-7-15.root"},
        //{"BG_single_t", "/data/whybee0a/user/lesko_2/fermi/Output/ZfinderBGFiles15-7-15/BG_singlet_tw15-7-15.root"},
        //{"BG_single_tbar", "/data/whybee0a/user/lesko_2/fermi/Output/ZfinderBGFiles15-7-15/BG_singlet_tbarw15-7-15.root"},
        //{"BG_ww", "/data/whybee0a/user/lesko_2/fermi/Output/ZfinderBGFiles15-7-15/BG_ww15-7-15.root"},
        //{"BG_wz", "/data/whybee0a/user/lesko_2/fermi/Output/ZfinderBGFiles15-7-15/BG_wz15-7-15.root"},
        //{"BG_zz", "/data/whybee0a/user/lesko_2/fermi/Output/ZfinderBGFiles15-7-15/BG_zz15-7-15.root"},

    };

    if (AlexFiles)files_to_open["Signal"] = "/data/whybee0a/user/gude_2/MC/20150219_MC_CTEQ6LL_same_sign_no_mass_cut/MadGraph_hadded.root";
        //else files_to_open["Signal"] = "/data/whybee0a/user/lesko_2/fermi/Output/Zfinder2MCPDFweightBorn15-7-2/Powheg15-7-04.root";
    else files_to_open["Signal"] = "/data/whybee0a/user/lesko_2/fermi/NewMC/ZfinderPOWHEGBornNoMassCuts2016-01-14/POWwithAllYBornNoMass.root";
    // The Tree to access
    const std::string TREE_NAME = "ZFinder/Combined Single Reco/Combined Single Reco";

    // Open the files and fill the file map
    histogram_map output_map;
    for (auto iter : files_to_open) {
        std::string data_type = iter.first;
        std::string file_name = iter.second;
        bool is_real_data = false;
        if (data_type == "Data") {
            is_real_data = true;
        }

        // Open the file and load the tree
        TTree* tree = GetTTree(file_name, TREE_NAME);

        TBranch* reco_branch = tree->GetBranch("reco");
        TLeaf* e0_charge = reco_branch->GetLeaf("e_charge0");
        TLeaf* e1_charge = reco_branch->GetLeaf("e_charge1");
        TLeaf* mee = reco_branch->GetLeaf("z_m");
        TLeaf* phistar = reco_branch->GetLeaf("z_phistar_dressed");
        TLeaf* Zrapidity = reco_branch->GetLeaf("z_y");


        // We have to grab the first entry to learn how many weights there are
        int nweights = 0;
        if (!is_real_data) {
            tree->SetBranchAddress("weight_size", &nweights);
            tree->GetEntry(0);
        }
        double weights[nweights];
        int weightid[nweights];
        if (!is_real_data) {
            tree->SetBranchAddress("weights", &weights);
            tree->SetBranchAddress("weight_ids", &weightid);
        }

        // Pack into a hitogram
        TH2D* histo;
        if (SeperateYs)histo = new TH2D("phistar_and_mass", "Phistar Vs. Mass;#phi*;m_{ee}", zf::ATLAS_PHISTAR_BINNING.size() - 1, &zf::ATLAS_PHISTAR_BINNING[0], 42, 0, 252);
        else histo = new TH2D("phistar_and_mass", "Phistar Vs. Mass;#phi*;m_{ee}", zf::ATLAS_PHISTAR_BINNING.size() - 1, &zf::ATLAS_PHISTAR_BINNING[0], 50, 0, 300);
        for (int i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            if (Ymin > fabs(Zrapidity->GetValue()) || YMax < fabs(Zrapidity->GetValue()))continue;
            // Reject opposite sign
            if (e0_charge->GetValue() * e1_charge->GetValue() < 0) {
                continue;
            }

            // We have a bug in our tuples where the charge is often set wrong.
            // Instead we selected the events from the beinging to be be same
            // sign, so we run on all of them.
            double weight = 1;
            if (!is_real_data) {
                weight = GetOverallNormalization(data_type);
                weight *= GetWeight(nweights, weights, weightid);
            }

            const double MEE = mee->GetValue();
            const double PHISTAR = phistar->GetValue();
            histo->Fill(PHISTAR, MEE, weight);
        }
        if (data_type == "Signal")cout << "This is The value after signal weight: " << histo->Integral() << endl << endl << endl;
        histo->Sumw2();

        delete tree;

        output_map[data_type] = histo;
    }

    return output_map;
}

TH2D* GetTemplate(histogram_map histo_map) {
    // Clone the histograms to make new ones to fill.
    TH2D* data_mass_histo = histo_map["Data"];
    TH2D* template_2d = new TH2D();
    template_2d = dynamic_cast<TH2D*> (data_mass_histo->Clone("2d_template"));

    // Empty the histogram
    template_2d->Reset();

    // Add the backgrounds and signal
    for (auto iter : histo_map) {
        if (iter.first != "Data") {
            template_2d->Add(iter.second, 1.);
        }
    }

    return template_2d;
}

TH1D* Get1DFromBin(TH2D* histo, const int BIN, const std::string PREFIX) {
    // Project the histogram
    TH1D* out_histo = new TH1D();
    const std::string NAME = PREFIX + std::to_string(BIN);
    out_histo = histo->ProjectionY(NAME.c_str(), BIN, BIN, "e");

    return out_histo;
}

std::pair<double, double> FitForQCD(TH1D* data_histo, TH1D* template_histo, const std::string BIN, const std::string PHISTAR_RANGE, TH1D* fake_zmass, TH1D* RatioPlot, unsigned int PhiBin, double MaxY = 2.4, double MinY = 0) {
    using namespace RooFit;
    // The X value of the histogram
    double ZMax = 0;
    if (SeperateYs)ZMax = 252;
    else ZMax = 300;
    RooRealVar z_mass("z_mass", "m_{ee}", 0, ZMax, "GeV");
    z_mass.setRange("signal", 60., 120.);

    // Data and MC histogram
    RooDataHist h_data("h_data", "h_data", RooArgSet(z_mass), data_histo);
    RooDataHist h_mc("h_mc", "h_mc", RooArgSet(z_mass), template_histo);
    RooHistPdf signalpdf("signalpdf", "signalpdf", z_mass, h_mc);
    // Background pdf
    // alpha controls the peak position
    RooRealVar alpha("alpha", "alpha", 50., 10., 90.);
    // gamma controls the slope of the exponential
    RooRealVar gamma("gamma", "gamma", 0.01, 0.0001, 0.03);
    // Delta controls the ratio of the slope of the two sides, as well as the
    // smoothness of the peak
    RooRealVar delta("delta", "delta", 40., 10, 80.);
    RooFormulaVar var1("var1", "(alpha-z_mass)/delta", RooArgSet(alpha, z_mass, delta));
    RooFormulaVar var2("var2", "-1.0*gamma*z_mass", RooArgSet(gamma, z_mass));
    RooGenericPdf MyBackgroundPdf("MyBackgroundPdf", "ROOT::Math::erfc(var1)*exp(var2)", RooArgSet(var1, var2));
    // Make the sum of the histogram and the Haupt function
    //RooRealVar sigratio("sigratio", "sigratio", 0.9, 0.6, 1.0); //Zach Allow to go lower at high phi*
    RooRealVar nsig("nsig", "nsig", 1000, 0.0, 1000000);
    RooRealVar nbkg("nbkg", "nbkg", 1000, 0.0, 1000000);


    RooAddPdf combined_pdf("combined_pdf", "combined_pdf", RooArgList(signalpdf, MyBackgroundPdf), RooArgList(nsig, nbkg));
    //RooAddPdf combined_pdf("combined_pdf", "combined_pdf", RooArgList(signalpdf, MyBackgroundPdf), RooArgList(sigratio));
    // Fit, but without yelling please
    std::cout << std::endl;
    std::cout << "Running on Bin: " << BIN << std::endl;
    std::cout << std::endl;
    RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);
    gErrorIgnoreLevel = kWarning;
    RooFitResult* fit_result = combined_pdf.fitTo(h_data, Verbose(false), PrintLevel(-1), Save(true));

    // Set up the legend using the plot edges to set its location
    const double RIGHT_EDGE = 0.90;
    const double TOP_EDGE = 0.92;
    const double LEG_HEIGHT = 0.20;
    const double LEG_LENGTH = 0.40;
    TLegend legend(
            RIGHT_EDGE - LEG_LENGTH,
            (TOP_EDGE - 0.025) - LEG_HEIGHT, // 0.025 offset to avoid ticks
            RIGHT_EDGE,
            TOP_EDGE - 0.025 // 0.025 offset to avoid the ticks
            );
    legend.SetFillColor(kWhite);
    legend.SetBorderSize(0); // Remove drop shadow and border
    legend.SetFillStyle(0); // Transparent

    // Plot
    TCanvas canvas("canvas", "canvas", 600, 600);
    canvas.cd();
    gPad->SetLogy();
    const std::string TITLE = "QCD Fit: " + PHISTAR_RANGE;
    RooPlot* fitFrame = z_mass.frame(Title(TITLE.c_str()));
    fitFrame->SetTitleOffset(1.25, "Y");

    // Plot components and add them to the legend
    h_data.plotOn(fitFrame, Name("data"));
    legend.AddEntry(fitFrame->findObject("data"), "Data", "p");

    combined_pdf.plotOn(fitFrame, Components(signalpdf), LineColor(kBlack), LineStyle(kDashed), Name("template"));
    legend.AddEntry(fitFrame->findObject("template"), "MC Template", "l");

    combined_pdf.plotOn(fitFrame, Components(MyBackgroundPdf), LineColor(kRed), LineStyle(kDashed), Name("qcd"));
    legend.AddEntry(fitFrame->findObject("qcd"), "Analytic Background", "l");

    combined_pdf.plotOn(fitFrame, LineColor(kBlue), Name("fit"));
    legend.AddEntry(fitFrame->findObject("fit"), "Sum of Fit Components", "l");

    h_data.plotOn(fitFrame);
    fitFrame->Draw();
    legend.Draw();
    const std::string FILE_TYPE = "pdf";

    std::string OutputFileName;
    if (SeperateYs) {
        char buffer [50];
        sprintf(buffer, "qcd_fit_plot_for_Bin_%s_forY%f-%f", BIN.c_str(), MinY, MaxY);
        OutputFileName = buffer;
    } else {
        if (AlexFiles)OutputFileName = "qcd_fitNick_plot_for_Bin" + BIN;
        else OutputFileName = "qcd_fitNotAlex_plot_for_Bin" + BIN;
    }

    const std::string OUT_NAME = OutputFileName + "Test." + FILE_TYPE;
    canvas.Print(OUT_NAME.c_str(), FILE_TYPE.c_str());
    RooAbsReal* SignalPDFInt = signalpdf.createIntegral(z_mass, Range("signal"));
    RooAbsReal* fracInt = MyBackgroundPdf.createIntegral(z_mass, Range("signal"));

    delete fitFrame;

    for (size_t MassBin = 1; MassBin <= 120; MassBin++) {
        z_mass.setRange("Int", 60 + .5 * (MassBin - 1), 60 + .5 * (MassBin)); //Set range for an integral
        RooAbsReal* MassIntHelp = MyBackgroundPdf.createIntegral(z_mass, Range("Int"));
        fake_zmass->Fill(60 + .5 * (MassBin - 1), MassIntHelp->getVal());
    }

    double ScaledValue, ScaledError;
    z_mass.setRange("ALL", 0., 300.);
    RooAbsReal* fracIntTotal = MyBackgroundPdf.createIntegral(z_mass, Range("ALL")); //Should be PDF backgroundpdf.integral(0,300)

    ////Nicoles changes
    RooAbsReal* fracIntNic = MyBackgroundPdf.createIntegral(z_mass);
    RooAbsReal* fracIntSNic = MyBackgroundPdf.createIntegral(z_mass, NormSet(z_mass), Range("signal"));
    double NicolesResult = nbkg.getVal() * fracIntSNic->getVal();
    double NicoleErrorSquared = fracIntSNic->getVal() * fracIntSNic->getVal() * nbkg.getPropagatedError(*fit_result) * nbkg.getPropagatedError(*fit_result);
    NicoleErrorSquared += fracIntSNic->getPropagatedError(*fit_result) * fracIntSNic->getPropagatedError(*fit_result) * nbkg.getVal() * nbkg.getVal();
    double NicoleError = sqrt(NicoleErrorSquared);
    cout << "Alpha: " << alpha.getVal() << " Delta: " << delta.getVal() << " And Gamma: " << gamma.getVal() << "  nsig: " << nsig.getVal() << " nbkg: " << nbkg.getVal() << " fracIntTotal is: " << fracIntTotal->getVal() << "  Total Data is " << data_histo->Integral() << endl;
    //RooRealVar StupidTest("Stupid", "Stupid", 0, 10, 300);
    //StupidTest.setVal(87.9932);
    //cout << "Stupid TEst is " << MyBackgroundPdf.getVal(StupidTest) << endl;
    //cout << "Zachary Bin: " << BIN << " Sig ratio: " << sigratio.getVal() << " Fraction intigral " << fracInt->getVal() << " Data Intigral: " << data_histo->Integral() << "Signal PDF int: " << endl;
    //cout<<"NICOLES RESULT IS "<<NicolesResult<<" AND THE OTHER THING IS "<<fracInt->getVal()<<endl;
    RatioPlot->SetBinContent(PhiBin, nsig.getVal() / (nbkg.getVal() + nsig.getVal()));
    double UncertaintyRatio = sqrt((pow(nsig.getVal() * nbkg.getError(), 2) + pow(nbkg.getVal() * nsig.getError(), 2)) / pow(nsig.getVal() + nbkg.getVal(), 4));
    RatioPlot->SetBinError(PhiBin, UncertaintyRatio);
    if(NicoleError>100*NicolesResult)NicoleError=10;
    return
    {
        //fracInt->getVal(), fracInt->getPropagatedError(*fit_result)
        NicolesResult, NicoleError
    };
}

void MakePhistarPlot(TH1D* histo, int Yindex = 0) {
    SetPlotStyle();
    TCanvas canvas("canvas", "canvas", 800, 800);
    canvas.cd();
    //gPad->SetLogy();
    gPad->SetLogx();

    histo->GetYaxis()->SetTitle("Estimated QCD and W+Jet Events");
    histo->SetTitleOffset(1.3, "Y");
    histo->SetMinimum(0);
    histo->SetMarkerStyle(kFullCircle);
    histo->SetMarkerColor(kBlack);
    histo->SetLineColor(kBlack);

    histo->Draw("E");

    // Add CMS text inside the plot on the top left
    const std::string CMS_STRING = "CMS Preliminary";
    const double LEFT_EDGE_ = 0.10;
    const double TOP_EDGE_ = 0.95;
    TLatex* cms_latex = new TLatex(LEFT_EDGE_ + 0.035, TOP_EDGE_ - 0.055, CMS_STRING.c_str());
    cms_latex->SetNDC(kTRUE); // Use pad coordinates, not Axis
    cms_latex->SetTextSize(0.035);

    std::string OutputFileName;
    if (SeperateYs) {
        char buffer [50];
        double Min = YSeperations[Yindex];
        double Max = YSeperations[Yindex + 1];
        sprintf(buffer, "qcd_phistar%f-%f", Min, Max);
        OutputFileName = buffer;
    } else OutputFileName = "qcd_phistar";

    std::string QCDName = OutputFileName + "Test.pdf";

    canvas.Print(QCDName.c_str(), "pdf");
    if (debug) {
        QCDName = OutputFileName + ".C";
        canvas.Print(QCDName.c_str(), "cxx");
    }

    // Print bins for the latex table
    for (int i = 1; i <= histo->GetNbinsX(); ++i) {
        const double LOW_EDGE = histo->GetBinLowEdge(i);
        const double HIGH_EDGE = LOW_EDGE + histo->GetBinWidth(i);
        const double VALUE = histo->GetBinContent(i);
        //const double UP_ERR = histo->GetBinErrorUp(i);
        //const double DOWN_ERR = histo->GetBinErrorLow(i);
        const double ERR = histo->GetBinError(i);
        std::cout << '$' << LOW_EDGE << "--" << HIGH_EDGE << "$ ";
        std::cout << '&' << " $" << VALUE;
        std::cout << " \\pm " << ERR << "$ \\\\" << std::endl;
    }
}

int main() {
    // Get a map of the histograms of the Z Masses
    SetPlotStyle();
    for (unsigned int Yindex = 0; Yindex < nYSeper && (SeperateYs || Yindex == 0); Yindex++) {

        // Write and draw the histos
        histogram_map histo2d;
        if (SeperateYs) histo2d = Get2DHistoMap(YSeperations[Yindex], YSeperations[Yindex + 1]);
        else histo2d = Get2DHistoMap();
        TH2D* data_histo2d = histo2d["Data"];
        TH2D* template_histo2d = GetTemplate(histo2d);

        // Fit the mass peak from each phistar bin using an MC template and
        // analytic QCD function
        TH1D* qcd_phistar_histo = new TH1D("phistar", "QCD Phistar;#phi*;counts", zf::ATLAS_PHISTAR_BINNING.size() - 1, &zf::ATLAS_PHISTAR_BINNING[0]);
        TH1D* fake_zmass = new TH1D("z_mass_all", "z_mass_all", 120, 60., 120.);
        qcd_phistar_histo->Sumw2();
        TH1D* RatioPlot = new TH1D("nsigOverntot", "QCD nsig/(nsig+nbkg);#phi*;counts", zf::ATLAS_PHISTAR_BINNING.size() - 1, &zf::ATLAS_PHISTAR_BINNING[0]);
        RatioPlot->Sumw2();
        for (unsigned int i = 1; i < zf::ATLAS_PHISTAR_BINNING.size(); ++i) {
            if (debug && i != 1)continue;
            // Get histograms for each phistar bin
            TH1D* data_histo = Get1DFromBin(data_histo2d, i, "data_bin_");
            TH1D* template_histo = Get1DFromBin(template_histo2d, i, "template_bin_");
            Int_t reBiner = data_histo->Integral() > 100 ? 1 : 2;
            TH1D* data_histo_Test = (TH1D*) data_histo->Rebin(reBiner);
            TH1D* template_histo_Test = (TH1D*) template_histo->Rebin(reBiner);
            // Set up the title for the plot
            const double MIN_PHISTAR = zf::ATLAS_PHISTAR_BINNING.at(i - 1);
            const double MAX_PHISTAR = zf::ATLAS_PHISTAR_BINNING.at(i);
            std::ostringstream convert;
            convert << std::setprecision(3);
            convert << std::fixed;
            convert << MIN_PHISTAR;
            convert << " < #phi* < ";
            convert << MAX_PHISTAR;
            const std::string PHISTART_BINNING = convert.str();

            // Run the fit and make the plot
            std::ostringstream convert2;
            convert2 << std::setw(2) << std::setfill('0') << i;
            std::pair<double, double> fit_result;
            if (SeperateYs) fit_result = FitForQCD(data_histo_Test, template_histo_Test, convert2.str(), PHISTART_BINNING, fake_zmass, RatioPlot, i, YSeperations[Yindex + 1], YSeperations[Yindex]);
            else fit_result = FitForQCD(data_histo_Test, template_histo_Test, convert2.str(), PHISTART_BINNING, fake_zmass, RatioPlot, i);
            // Fill the background histogram
            qcd_phistar_histo->SetBinContent(i, fit_result.first);
            qcd_phistar_histo->SetBinError(i, fit_result.second);
            //fake_zmass->Fill(91, fit_result.first);

            // Clean up
            delete data_histo;
            delete template_histo;
        }

        // Divide by bin width and scale for the fact that we consider only same
        // sign here, but in the analysis have same sign and opposite.
        const int SAME_SIGN_CORRECTION = 2;
        qcd_phistar_histo->Scale(SAME_SIGN_CORRECTION);
        fake_zmass->Scale(SAME_SIGN_CORRECTION);

        // Get the background subtracted MZ
        const int FIRST_BIN = 1;
        const int LAST_BIN = -1; // -1 means "ALL"
        TH1D* data_mass = data_histo2d->ProjectionY("data_mass", FIRST_BIN, LAST_BIN, "e");
        TH1D* mc_mass = template_histo2d->ProjectionY("mc_mass", FIRST_BIN, LAST_BIN, "e");

        data_mass->Add(mc_mass, -1);

        // Open a tfile to save our histos
        std::string OutputFileName;
        if (SeperateYs) {
            char buffer [50];
            double Min = YSeperations[Yindex];
            double Max = YSeperations[Yindex + 1];
            if (AlexFiles)sprintf(buffer, "outputY%f-%fAlexTest.root", Min, Max);
            else sprintf(buffer, "outputY%f-%fNotAlexTest.root", Min, Max);
            OutputFileName = buffer;
        } else {
            if (AlexFiles)OutputFileName = "outputALexTest.root";
            else OutputFileName = "outputNOTAlexTest.root";
        }
        cout << "OUR FILE NAME SHOULD BE " << OutputFileName << endl;

        TFile output_file(OutputFileName.c_str(), "RECREATE");
        output_file.cd();

        data_histo2d->Write();
        template_histo2d->Write();
        data_mass->Write();

        // Make a folder
        output_file.mkdir("qcd");
        output_file.cd("qcd");
        qcd_phistar_histo->Write();
        fake_zmass->Write();
        RatioPlot->Write();
        //TH1D* Crazy=qcd_phistar_histo->Clone();

        output_file.cd();
        output_file.mkdir("QCDCorrected");
        output_file.cd("QCDCorrected");

        TH1D* qcd_phistar_histoCorrectA = new TH1D("phistarCorrectByRatio", "QCD Phistar Corrected;#phi*;counts", zf::ATLAS_PHISTAR_BINNING.size() - 1, &zf::ATLAS_PHISTAR_BINNING[0]); //This is corrected by taking the ratio of the corrected over normal and multipling by original
        double CorRatio = (2 * RatioPlot->GetBinContent(1) + RatioPlot->GetBinContent(2)) / 3;
        double CorQCD = CorRatio / RatioPlot->GetBinContent(1) * qcd_phistar_histo->GetBinContent(1);
        qcd_phistar_histoCorrectA->SetBinContent(1, CorQCD);

        double a = RatioPlot->GetBinContent(1);
        double b = RatioPlot->GetBinContent(1);
        double c = RatioPlot->GetBinContent(2);
        double d = qcd_phistar_histo->GetBinContent(1);
        double sa = RatioPlot->GetBinError(1);
        double sb = RatioPlot->GetBinError(1);
        double sc = RatioPlot->GetBinError(2);
        double sd = qcd_phistar_histo->GetBinError(1);

        double BinError = 0;
        BinError = sqrt((d * d*((a + c)*(a + c) * sb * sb + b * b*(sa * sa + sc * sc)) + b * b * (a + b + c)*(a + b + c) *sd * sd) / pow(b, 4));//propegating error. I am so so sorry
        qcd_phistar_histoCorrectA->SetBinError(1, BinError);



        CorRatio = (2 * RatioPlot->GetBinContent(nphistar) + RatioPlot->GetBinContent(nphistar - 1)) / 3;
        CorQCD = CorRatio / RatioPlot->GetBinContent(nphistar) * qcd_phistar_histo->GetBinContent(nphistar);
        qcd_phistar_histoCorrectA->SetBinContent(nphistar, CorQCD);

        a = RatioPlot->GetBinContent(nphistar - 1);
        b = RatioPlot->GetBinContent(nphistar);
        c = RatioPlot->GetBinContent(nphistar);
        d = qcd_phistar_histo->GetBinContent(nphistar);
        sa = RatioPlot->GetBinError(nphistar - 1);
        sb = RatioPlot->GetBinError(nphistar);
        sc = RatioPlot->GetBinError(nphistar);
        sd = qcd_phistar_histo->GetBinError(nphistar);
        BinError = sqrt((d * d*((a + c)*(a + c) * sb * sb + b * b*(sa * sa + sc * sc)) + b * b * (a + b + c)*(a + b + c)* sd * sd) / pow(b, 4));
        qcd_phistar_histoCorrectA->SetBinError(nphistar, BinError);

        for (size_t PhiBin = 2; PhiBin < nphistar; PhiBin++) {
            CorRatio = (RatioPlot->GetBinContent(PhiBin + 1) + RatioPlot->GetBinContent(PhiBin) + RatioPlot->GetBinContent(PhiBin - 1)) / 3;
            CorQCD = CorRatio / RatioPlot->GetBinContent(PhiBin) * qcd_phistar_histo->GetBinContent(PhiBin);
            qcd_phistar_histoCorrectA->SetBinContent(PhiBin, CorQCD);

            a = RatioPlot->GetBinContent(PhiBin - 1);
            b = RatioPlot->GetBinContent(PhiBin);
            c = RatioPlot->GetBinContent(PhiBin+1);
            d = qcd_phistar_histo->GetBinContent(PhiBin);
            sa = RatioPlot->GetBinError(PhiBin - 1);
            sb = RatioPlot->GetBinError(PhiBin);
            sc = RatioPlot->GetBinError(PhiBin+1);
            sd = qcd_phistar_histo->GetBinError(PhiBin);

            BinError = sqrt((d * d*((a + c)*(a + c) * sb * sb + b * b*(sa * sa + sc * sc)) + b * b * (a + b + c)*(a + b + c)* sd * sd) / pow(b, 4));
            if(BinError>100)BinError=20;
            qcd_phistar_histoCorrectA->SetBinError(PhiBin, BinError);
        }

        MakePhistarPlot(qcd_phistar_histo, Yindex);

        output_file.Write();
        output_file.Close();
    }
    return EXIT_SUCCESS;
}
