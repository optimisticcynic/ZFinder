// Standard Library
#include <algorithm>  //std::equal_range, std::sort, std::unique
#include <cmath>  // std::abs
#include <iostream>
#include <string>

// ROOT
#include <TCanvas.h>
#include <TF1.h>
#include <TH1D.h>
#include <THStack.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLine.h>

// Plotting
#include "cross_check_plotter.h"

using namespace std;

void sample(TH1D* hdataold, TH1D* mc_histoold, std::vector<std::pair<std::string, TH1D* >> bg_histos, const PlotType PLOT_TYPE) {
    const double PhiStarBins[] = {0.001, 0.004, 0.008, 0.012, 0.016, 0.020, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277};
    //if (PLOT_TYPE != PHISTAR && PLOT_TYPE != Z_PT)return;
    //if (PLOT_TYPE != Z_PT) return;
    //if (PLOT_TYPE != E0_PT)return;

    bool POWHEGSamp = false;
    if (PLOT_TYPE == Z_MASS_COARSE)return;
    TH1D* hdata;
    TH1D* mc_histo;
    if (PLOT_TYPE != PHISTAR) {
        hdata = dynamic_cast<TH1D*> (hdataold->Clone());
        mc_histo = dynamic_cast<TH1D*> (mc_histoold->Clone());
    } else {
        hdata = new TH1D("Data", "Data", 34, PhiStarBins);
        mc_histo = new TH1D("MC", "MC", 34, PhiStarBins);
        for (int i = 1; i < 35; i++) {
            hdata->SetBinContent(i, hdataold->GetBinContent(i));
            mc_histo->SetBinContent(i, mc_histoold->GetBinContent(i));
        }
    }
    string yaxisname;
    string xaxisname;
    TH1D* totalMC;
    TH1D* hdytautau;
    TH1D* httbar;
    TH1D* hsinglet;
    TH1D* hsingletbar;
    TH1D* hWZ;
    TH1D* hWW;
    TH1D* hZZ;
    TH1D* QCDPlots;

    TH1D* mc_histoCloned;
    TH1D* htandtbar;
    TH1D* Allts;
    TCanvas *c1 = new TCanvas("c1", "", 81, 80, 500, 581);
    std::string FileName;
    double Maxhight = -1; //max hight for the tstack
    double Minhight = -1; //min hight of the tstack
    double AxisTSize = .18;
    double ErrorSize = -1;
    double offset = .55; // title offset, some titles needed slightly different offsets
    bool axis1 = false; //the eta and Y graphs axis needed to have different boundries
    THStack* hs = new THStack("hs", "");
    if (PLOT_TYPE == PHISTAR) {
        if (POWHEGSamp) {
            Maxhight = 2e9;
            Minhight = 3.7e3;
            ErrorSize = .2;
            FileName = "POWHEGphistar.pdf";
        } else {
            Maxhight = 2e9;
            Minhight = 3.7e3;
            ErrorSize = .3;
            FileName = "MADGRAPHphistar.pdf";
        }
        offset = .8;
        xaxisname = "#phi*";
        yaxisname = "Number of Events/Unit #phi*";

    } else if (PLOT_TYPE == Z_PT) {
        if (POWHEGSamp) {
            FileName = "POWHEGqt.pdf";
            Maxhight = 2e6;
            Minhight = 3.7;
            ErrorSize = .5;
        } else {
            FileName = "MADGRAPHqt.pdf";
            Maxhight = 2e6;
            Minhight = 10;
            ErrorSize = .5;
        }
        AxisTSize = .14;
        xaxisname = "q_{T} [GeV]";
        offset = .9;
        yaxisname = "Number of Events/ 5 GeV";
    } else if (PLOT_TYPE == E0_PT) {
        Maxhight = 1e7;
        Minhight = 3;
        xaxisname = "e_{0}p_{T} [GeV]";
        offset = .73;
        yaxisname = "Number of Events/ 5 GeV";
        if (POWHEGSamp)FileName = "POWHEG0pt.pdf";
        else FileName = "MADGRAPHE0pt.pdf";
    } else if (PLOT_TYPE == E1_PT) {
        Maxhight = 1e7;
        Minhight = 3;
        xaxisname = "e_{1}p_{T} [GeV]";
        offset = .73;
        yaxisname = "Number of Events/ 5 GeV";
        if (POWHEGSamp)FileName = "POWHEGE1pt.pdf";
        else FileName = "MADGRAPHE1pt.pdf";

    } else if (PLOT_TYPE == E0_ETA) {
        Maxhight = 1e8;
        Minhight = 1000;
        xaxisname = "#eta_{e_{0}}";
        yaxisname = "Events / Unit #eta";
        offset = .73;
        if (POWHEGSamp)FileName = "POWHEGE0Eta.pdf";
        else FileName = "MADGRAPHE0Eta.pdf";
        axis1 = true;
    } else if (PLOT_TYPE == E1_ETA) {
        Maxhight = 1e8;
        Minhight = 1000;
        xaxisname = "#eta_{e_{1}}";
        yaxisname = "Events / Unit #eta";
        offset = .73;
        if (POWHEGSamp)FileName = "POWHEGE1Eta.pdf";
        else FileName = "MADGRAPHE1Eta.pdf";
        axis1 = true;
    } else if (PLOT_TYPE == Z_RAPIDITY) {
        Maxhight = 1e8;
        Minhight = 1000;
        xaxisname = "Y_{Z}";
        yaxisname = "Events / Unit Y";
        if (POWHEGSamp)FileName = "POWHEGZrap.pdf";
        else FileName = "MADGRAPHEZrap.pdf";
        offset = .73;
        axis1 = true;
    } else if (PLOT_TYPE == Z_MASS_FINE) {
        Maxhight = 1e9;
        Minhight = 10;
        ErrorSize = .2;
        xaxisname = "m_{ee} [GeV]";
        offset = .73;
        yaxisname = "Events / .5 GeV";
        if (POWHEGSamp)FileName = "POWHEGEZmass.pdf";
        else FileName = "MADGRAPHEZmass.pdf";
    } else return;
    // setTDRStyle();
    //const int nphistar_bins = 35;
    //double phistar_var1[nphistar_bins] = { 0.004, 0.008, 0.012, 0.016, 0.020, 0.024, 0.029, 0.034, 0.039, 0.045, 0.051, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10.00};
    //Stack Plot



    c1->Range(0, 0, 1, 1);
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    c1->SetFrameBorderMode(0);


    //DATA
    hdata->SetStats(0);
    //okay so now where it gets different though I think only through naming.
    if (PLOT_TYPE != PHISTAR) {
        if (PLOT_TYPE == Z_PT) {
            mc_histoCloned = new TH1D("MCInfo", "", hdata->GetNbinsX(), 0, hdata->GetNbinsX() * mc_histo->GetBinWidth(1));
            for (int i = 1; i <= hdata->GetNbinsX(); i++) {
                mc_histoCloned->SetBinContent(i, mc_histo->GetBinContent(i));
            }
        } else mc_histoCloned = dynamic_cast<TH1D*> (mc_histo->Clone());

        for (auto& i_pair : bg_histos) {

            std::cout << "Okay here is the names " << i_pair.first << std::endl;

            if (i_pair.first == "2 Single Top") {
                hsinglet = dynamic_cast<TH1D*> (i_pair.second->Clone()); //Single Top
                //std::cout << "Got single t" << std::endl;
            }


            //std::cout << "and this the name " << i_pair.first << std::endl;
            if (i_pair.first == "3 Single TBar") {
                hsingletbar = dynamic_cast<TH1D*> (i_pair.second->Clone()); //single tbar
                // std::cout << "Got single tbar" << std::endl;
            }
            if (i_pair.first == "5 WW") {
                hWW = dynamic_cast<TH1D*> (i_pair.second->Clone());
                //std::cout << "got WW" << std::endl;
            }

            if (i_pair.first == "6 DY to #tau#tau") {
                hdytautau = dynamic_cast<TH1D*> (i_pair.second->Clone()); //Dy to tautau
                //std::cout << "Got to TauTau" << std::endl;
            }

            //std::cout << "and this the name " << i_pair.first << std::endl;


            if (i_pair.first == "7 WZ") {
                hWZ = dynamic_cast<TH1D*> (i_pair.second->Clone()); //WZ type
                //std::cout << "got WZ" << std::endl;
            }



            if (i_pair.first == "8 ZZ") {
                hZZ = dynamic_cast<TH1D*> (i_pair.second->Clone());
                // std::cout << "got ZZ" << std::endl;
            }

            if (i_pair.first == "9 TTBAR") {
                httbar = dynamic_cast<TH1D*> (i_pair.second->Clone()); //ttbar
                // std::cout << "Got ttbar" << std::endl;
            }

            if (i_pair.first == "4 QCD") {
                cout << "FFFFFFFFFFFFFFFFFFFFFFFFFFFFUUUUUUUUUUUCK" << endl;
                QCDPlots = dynamic_cast<TH1D*> (i_pair.second->Clone()); //ttbar
                std::cout << "Number of bins is " << QCDPlots->GetNbinsX() << std::endl << std::endl << std::endl;
                cout << "our intergral is " << QCDPlots->Integral() << endl;

            }

            //if(i_pair.first=="t#bar{t}")TH1F *hQCD = dynamic_cast<TH1D*> (i_pair.second->Clone());
        }
    } else {//so rebinning so that I can graph  logx, so resetting the starting point to .001, yes it is wrong, I was asked to do this
        mc_histoCloned = dynamic_cast<TH1D*> (mc_histo->Clone());
        hdytautau = new TH1D("DiTau", "DiTau", 34, PhiStarBins);
        httbar = new TH1D("ttbar", "ttbar", 34, PhiStarBins);
        hsinglet = new TH1D("singlet", "singlet", 34, PhiStarBins);
        hsingletbar = new TH1D("singletbar", "singletbar", 34, PhiStarBins);
        hWZ = new TH1D("WZ", "WZ", 34, PhiStarBins);
        hWW = new TH1D("WW", "WW", 34, PhiStarBins);
        hZZ = new TH1D("ZZ", "ZZ", 34, PhiStarBins);
        QCDPlots = new TH1D("QCD", "QCD", 34, PhiStarBins);
        for (auto& i_pair : bg_histos) {

            if (i_pair.first == "2 Single Top") {
                for (int i = 1; i < 35; i++)hsinglet->SetBinContent(i, i_pair.second->GetBinContent(i)); //Single Top
                //std::cout << "Got single t" << std::endl;
            }


            if (i_pair.first == "3 Single TBar") {
                //ttbar
                for (int i = 1; i < 35; i++)hsingletbar->SetBinContent(i, i_pair.second->GetBinContent(i));
                // std::cout << "Got ttbar" << std::endl;
            }


            if (i_pair.first == "5 WW") {
                for (int i = 1; i < 35; i++)hWW->SetBinContent(i, i_pair.second->GetBinContent(i));
                //std::cout << "got WW" << std::endl;
            }
            //std::cout << "Okay here is the names " << i_pair.first << std::endl;
            if (i_pair.first == "6 DY to #tau#tau") {
                for (int i = 1; i < 35; i++)hdytautau->SetBinContent(i, i_pair.second->GetBinContent(i)); //Dy to tautau
                //std::cout << "Got to TauTau" << std::endl;
            }

            if (i_pair.first == "7 WZ") {
                for (int i = 1; i < 35; i++)hWZ->SetBinContent(i, i_pair.second->GetBinContent(i)); //WZ type
                //std::cout << "got WZ" << std::endl;
            }

            if (i_pair.first == "8 ZZ") {
                for (int i = 1; i < 35; i++)hZZ->SetBinContent(i, i_pair.second->GetBinContent(i));
                // std::cout << "got ZZ" << std::endl;
            }

            //std::cout << "and this the name " << i_pair.first << std::endl;
            if (i_pair.first == "9 TTBAR") {
                for (int i = 1; i < 35; i++)httbar->SetBinContent(i, i_pair.second->GetBinContent(i)); //single tbar
                // std::cout << "Got single tbar" << std::endl;
            }


            if (i_pair.first == "4 QCD") {
                QCDPlots = dynamic_cast<TH1D*> (i_pair.second->Clone()); //
                // std::cout << "Got ttbar" << std::endl;
            }
            //if(i_pair.first=="t#bar{t}")TH1F *hQCD = dynamic_cast<TH1D*> (i_pair.second->Clone());
        }

    }
    //saving original files to a file so I can make a script that goes over everything more easily

    if (!hdytautau) {
        std::cout << "Missing double tau" << std::endl;
        return;
    }
    if (!httbar) {
        std::cout << "Missing double tt" << std::endl;
        return;
    }
    if (!hsinglet) {
        std::cout << "Missing single t" << std::endl;
        return;
    }

    if (!hWZ) {
        std::cout << "Missing wz" << std::endl;
        return;
    }
    if (!hWW) {
        std::cout << "Missing ww" << std::endl;
        return;
    }
    if (!hsingletbar) {
        std::cout << "Missing single tbar" << std::endl;
        return;
    }
    if (!QCDPlots) {
        std::cout << "Missing single QCD" << std::endl;
        return;
    }


    hZZ->SetFillColor(kGreen + 4);
    hZZ->SetFillStyle(1001);
    QCDPlots->SetFillColor(kGreen - 4); //QCD STUFF COULD GO TERRIBLE
    QCDPlots->SetFillStyle(1001);
    if (PLOT_TYPE == Z_MASS_FINE) {
        std::cout << " the Size of the bins are :" << httbar->GetBinWidth(5) << std::endl << std::endl;
    }
    htandtbar = dynamic_cast<TH1D*> (hsinglet->Clone());
    htandtbar->Add(hsingletbar); //wanted one graph with all the tops
    Allts = dynamic_cast<TH1D*> (htandtbar->Clone());
    Allts->Add(httbar);
    // delete htandtbar;//stopped using it, seemed like a good idea
    // delete hsinglet;
    // delete hsingletbar
    totalMC = dynamic_cast<TH1D*> (hdytautau->Clone());
    //totalMC->Add(hdytautau);
    totalMC->Add(Allts);

    totalMC->Add(hWZ);
    totalMC->Add(hZZ);
    totalMC->Add(hWW);
    totalMC->Add(mc_histoCloned);
    totalMC->Add(QCDPlots);
    Allts->SetFillColor(kYellow + 1);
    Allts->SetFillStyle(1001);

    if (PLOT_TYPE == PHISTAR) {
        cout << "Number of bins 1 :" << httbar->GetNbinsX() << endl;
        cout << "Number of bins 2 :" << hdata->GetNbinsX() << endl;
    }

    mc_histoCloned->SetFillColor(kRed - 7);
    mc_histoCloned->SetFillStyle(1001);

    hWW->SetFillColor(44);
    hWW->SetFillStyle(1001);

    hWZ->SetFillColor(kBlue - 3);
    hWZ->SetFillStyle(1001);

    hdytautau->SetFillColor(kViolet - 6);
    hdytautau->SetFillStyle(1001);

    hZZ->SetLineColor(1);
    QCDPlots->SetLineColor(1);
    hWW->SetLineColor(1);
    hWZ->SetLineColor(1);
    Allts->SetLineColor(1);
    hdytautau->SetLineColor(1);
    mc_histoCloned->SetLineColor(1);

    hs->Add(QCDPlots, "hist");
    hs->Add(hWW, "hist");
    hs->Add(hdytautau, "hist");
    hs->Add(hWZ, "hist");
    hs->Add(hZZ, "hist");
    hs->Add(Allts, "hist");

    for (int i = 1; i <= 34; i++) {
        cout << "our TauTau value is " << hdytautau->GetBinContent(i) << endl;
        //        cout<<"our TauTau value is "<<hdytautau->GetBinContent(i)<<endl;
        //        cout<<"our TauTau value is "<<hdytautau->GetBinContent(i)<<endl;
        //        cout<<"our MC cloned value is "<<mc_histoCloned->GetBinContent(i)<<endl;
    }
    cout << "TOTAL PERCENTAGE IS " << Allts->Integral() / totalMC->Integral()*100 << endl;

    hs->Add(mc_histoCloned, "hist");

    for (unsigned int i = 1; i <= (unsigned int) hdata->GetNbinsX(); i++) {
        double err_data1 = hdata->GetBinError(i);
        hdata->SetBinError(i, err_data1);

    }
    if (PLOT_TYPE == Z_PT || PLOT_TYPE == PHISTAR || PLOT_TYPE == Z_RAPIDITY) {
        string MCSample;
        if (POWHEGSamp)MCSample = "POWHEG";
        else MCSample = "MadGraph";
        string PlotType;
        if (PLOT_TYPE == Z_PT)PlotType = "QtFile.root";
        else if (PLOT_TYPE == PHISTAR)PlotType = "PhiStarFile.root";
        else if (PLOT_TYPE == Z_RAPIDITY)PlotType = "RapidityFile.root";
        string FileName = MCSample + PlotType;
        TFile f(FileName.c_str(), "RECREATE");
        hdata->Write("Data");
        mc_histoCloned->Write("MC");
        hdytautau->Write("DiTau");
        httbar->Write("ttbar");
        hsinglet->Write("singlet");
        hsingletbar->Write("singletbar");
        hWZ->Write("WZ");
        hWW->Write("WW");
        hZZ->Write("ZZ");
    }
    double leftMarg = 0.1807143;
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.1, 1, 1);
    pad1->Draw();
    pad1->cd();
    //    pad1->Range(-6.246851, -1575.816, 6.246851, 4673.11);
    pad1->SetFillColor(0);
    pad1->SetBorderMode(0);
    pad1->SetBorderSize(2);
    pad1->SetTopMargin(0.06304348);
    pad1->SetLeftMargin(leftMarg);
    pad1->SetBottomMargin(0.18);
    pad1->SetFrameBorderMode(0);
    pad1->SetFrameBorderMode(0);
    pad1->cd();
    //
    const std::string LUMI_STRING = "19.7 fb^{-1} (8 TeV)";
    TLatex* lumi_latex = new TLatex(.7, 0.95, LUMI_STRING.c_str());
    lumi_latex->SetNDC(kTRUE); // Use pad coordinates, not Axis
    lumi_latex->SetTextSize(0.035);

    // Add CMS text inside the plot on the top left
    const std::string CMS_STRING = "CMS Preliminary";
    TLatex* cms_latex = new TLatex(0.23, .88, CMS_STRING.c_str());
    cms_latex->SetNDC(kTRUE); // Use pad coordinates, not Axis
    cms_latex->SetTextSize(0.035);

    TLatex mark1;
    mark1.SetTextSize(0.05);
    mark1.SetTextFont(61);
    mark1.SetNDC(true);
    //mark1.DrawLatex(0.15, 0.955, "CMS");
    TLatex mark2;
    mark2.SetTextSize(0.038);
    mark2.SetTextFont(52);
    mark2.SetNDC(true);
    mark2.DrawLatex(0.23, 0.955, " Preliminary");


    hs->SetMaximum(Maxhight);
    hs->SetMinimum(Minhight);
    //hs->SetMinimum(3.6);
    //TH1D* DumbyTH1=new TH1D("Dumby","",1,httbar->GetBinLowEdge(1),httbar->GetBinLowEdge(httbar->GetNbinsX())+httbar->GetBinWidth(httbar->GetNbinsX()));
    //if(axis1)DumbyTH1= new TH1D("Dumby","Dumby",1,-3,3);
    //else if(PLOT_TYPE == Z_PT)DumbyTH1=new TH1D("Dumby","Dumby",1,0,300);
    //else DumbyTH1=new TH1D("Dumby","",1,httbar->GetBinLowEdge(1),httbar->GetBinLowEdge(httbar->GetNbinsX())+httbar->GetBinWidth(httbar->GetNbinsX()));

    hs->Draw();

    hdata->Draw("pe same");
    hdata->Draw("AXIS same");
    lumi_latex->Draw();
    //cms_latex->Draw();
    mark1.DrawLatex(0.15, 0.955, "CMS");
    mark2.DrawLatex(0.25, 0.955, " Preliminary");
    //if (axis1)hs->GetXaxis()->SetRangeUser(-3, 3);
    if (PLOT_TYPE == Z_PT)hs->GetXaxis()->SetRangeUser(0, 300);
    //
    hs->GetXaxis()->CenterTitle();
    hs->GetXaxis()->SetLabelOffset(10);

    hs->GetYaxis()->SetTitle(yaxisname.c_str());
    hs->GetYaxis()->CenterTitle();
    hs->GetYaxis()->SetTitleSize(AxisTSize * 0.24);
    hs->GetYaxis()->SetLabelSize(.7 * hs->GetYaxis()->GetLabelSize());
    hs->GetYaxis()->SetTitleSize(0.05);
    hs->GetYaxis()->SetTitleOffset(1.05);
    //cout<<" our title font for the y axis is "<<hs->GetYaxis()->GetTitleFont())<<endl;
    hdata->SetMarkerSize(0.7 * hdata->GetMarkerSize());
    hdata->SetMarkerStyle(20);

    //TLegend* tl = new TLegend(0.76, 0.7, 0.97, 0.942);
    TLegend* tl;
    if (PLOT_TYPE != PHISTAR && PLOT_TYPE != Z_PT && PLOT_TYPE != Z_MASS_FINE)tl = new TLegend(0.54, .67, .86, 0.95);
    else tl = new TLegend(0.49, .67, .86, 0.92);
    tl->AddEntry(hdata, "Data", "lp");
    if (POWHEGSamp)tl->AddEntry(mc_histoCloned, "#gamma*/Z#rightarrow ee(POWHEG)", "f");
    else tl->AddEntry(mc_histoCloned, "#gamma*/Z#rightarrow ee(MADGRAPH)", "f");
    //tl->AddEntry(hZZ, "ZZ", "f");
    //tl->AddEntry(hWZ, "WZ", "f");
    //tl->AddEntry(hWW, "WW", "f");
    tl->AddEntry(Allts, "t#bar{t}+tW+#bar{t}W", "f");
    tl->AddEntry(hdytautau, "#gamma*/Z#rightarrow#tau#tau", "f");

    //tl->AddEntry(hWZ, "WZ", "f");
    tl->SetFillColor(0);
    tl->SetLineColor(0);
    cout << "OUR TEXT FONT IS " << tl->GetTextFont() << endl;
    tl->Draw("same");

    //TLegend* tl2 = new TLegend(0.83, 0.7, 0.945, 0.81); //created second legend to make stuff fit
    TLegend* tl2;
    if (PLOT_TYPE != PHISTAR && PLOT_TYPE != Z_PT && PLOT_TYPE != Z_MASS_FINE) tl2 = new TLegend(0.75, .67, 0.993, .8);
    else tl2 = new TLegend(0.7, .67, 0.993, .8);
    //tl2->AddEntry(hdytautau, "#gamma*/Z#rightarrow#tau#tau", "f");
    //tl2->AddEntry(Allts, "t#bar{t}+tW+#bar{t}W", "f");
    tl2->AddEntry(hWZ, "WZ", "f");
    tl2->AddEntry(hZZ, "ZZ", "f");
    tl2->AddEntry(hWW, "WW", "f");
    //if (PLOT_TYPE == PHISTAR || PLOT_TYPE == Z_PT&&PLOT_TYPE !=Z_MASS_FINE)tl2->AddEntry(QCDPlots, "QCD, W+JET", "f");
    tl2->AddEntry(QCDPlots, "QCD, W+JET", "f");
    tl2->SetFillColor(0);
    tl2->SetLineColor(0);
    tl->SetTextSize(.03);
    tl2->SetTextSize(.03);
    tl2->SetFillColor(0);
    tl2->SetLineColor(0);
    tl->SetFillStyle(4002);
    tl2->SetFillStyle(4002);

    tl2->Draw("same");
    pad1->SetLogy();
    if (PLOT_TYPE == PHISTAR)pad1->SetLogx();

    c1->cd();
    if (hdata->GetNbinsX() != totalMC->GetNbinsX()) {
        std::cout << " Data and mc bins do not match " << std::endl;
        std::cout << " number of bins for Data " << hdata->GetNbinsX() << " and the number of bins for MC is" << totalMC->GetNbinsX() << std::endl;
    }

    // Ratio Plot
    double data = 0.0;
    double mc = 0.0;
    double err_data = 0.0;
    double err_mc = 0.0;
    double ratio = 0.0;
    double err_mc1 = 0.0;
    TH1D* hPull = dynamic_cast<TH1D*> (hdytautau->Clone());
    TLine* line;
    if (!axis1)line = new TLine(hdytautau->GetBinLowEdge(1), 1., hdytautau->GetBinLowEdge(hdytautau->GetNbinsX()), 1.);
    if (PLOT_TYPE == Z_PT)line = new TLine(hdytautau->GetBinLowEdge(1), 1., 300, 1.);



    if (axis1)line = new TLine(-3, 1., 3, 1.);

    line->SetLineStyle(2);


    for (unsigned int i = 1; i <= ((unsigned int) hdata->GetNbinsX()); i++) {
        data = hdata->GetBinContent(i);
        err_data = hdata->GetBinError(i);
        mc = totalMC->GetBinContent(i);
        err_mc = totalMC->GetBinError(i);

        if (mc != 0 && data != 0) {

            ratio = data / mc;
            err_mc1 = ratio * (sqrt(pow((err_data / data), 2) + pow((err_mc / mc), 2)));
            hPull->SetBinContent(i, ratio);
            hPull->SetBinError(i, err_mc1);
        }
    }
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.007, 1, 0.25);
    pad2->Draw();
    pad2->cd();
    if (PLOT_TYPE == PHISTAR)pad2->SetLogx();
    //    pad2->Range(-6.133501, -0.02305455, 6.246851, 1.268);
    pad2->SetFillColor(0);
    pad2->SetBorderMode(0);
    pad2->SetBorderSize(2);
    pad2->SetTickx(1);
    pad2->SetTicky(1);
    pad2->SetLeftMargin(leftMarg);
    pad2->SetBottomMargin(0.28);
    pad2->SetFrameBorderMode(0);
    pad2->SetFrameBorderMode(0);

    pad2->cd();
    hPull->SetStats(0);
    hPull->SetMarkerStyle(8);
    hPull->SetMarkerSize(0.6);
    hPull->SetTitle("");
    pad2->SetTicky();

    hPull->Draw("pe1");
    line->Draw("same");
    TAxis *xaxis = hPull->GetXaxis();
    TAxis *yaxis = hPull->GetYaxis();
    xaxis->SetTitle(xaxisname.c_str());
    xaxis->CenterTitle();
    xaxis->SetLabelSize(2.4 * xaxis->GetLabelSize());
    if (PLOT_TYPE == Z_PT)xaxis->SetLabelSize(.13);
    xaxis->SetTitleSize(AxisTSize);
    xaxis->SetTitleOffset(offset * xaxis->GetTitleOffset());
    double range = ErrorSize;
    yaxis->SetRangeUser(1 - range, 1 + range);
    if (axis1)xaxis->SetRangeUser(-3, 3);
    if (PLOT_TYPE == Z_PT)xaxis->SetRangeUser(0, 300);
    if (PLOT_TYPE == PHISTAR)yaxis->SetRangeUser(.96, 1.1);
    yaxis->SetTitle("Data/MC");
    yaxis->CenterTitle();
    yaxis->SetLabelSize(2.5 * yaxis->GetLabelSize());
    if (PLOT_TYPE == Z_PT)yaxis->SetLabelSize(.13);
    yaxis->SetLabelSize(.13);
    yaxis->SetTitleSize(.16);
    yaxis->SetTitleOffset(.32);
    yaxis->SetNdivisions(503);
    c1->SaveAs(FileName.c_str());
    delete c1;
}

CrossCheckPlotter::CrossCheckPlotter(
        DataConfig data_config,
        DataConfig mc_config
        ) {
    // Save DataConfigs
    data_config_ = data_config;
    mc_config_ = mc_config;
    bg_configs_ = {};

    // General Setup
    setup();
}

CrossCheckPlotter::CrossCheckPlotter(
        DataConfig data_config,
        DataConfig mc_config,
        data_config_map bg_configs
        ) {
    // Save DataConfigs
    data_config_ = data_config;
    mc_config_ = mc_config;
    bg_configs_ = bg_configs;

    // General Setup
    setup();
}

CrossCheckPlotter::~CrossCheckPlotter() {
    /* Clean up our heap variables */
    delete style_;
}

void CrossCheckPlotter::setup() {
    // Set up the config map
    init_config_map();

    // Set up the style
    set_plot_style();

    // Set up colors and hatching
    init_color_styles();

    // Rescaling
    set_mc_scale_factors();
    if (data_config_.luminosity <= 0) {
        area_rescale_factor_ = set_area_rescale_factor();
        data_config_.luminosity = 1;
    } else {
        area_rescale_factor_ = -1;
    }
}

void CrossCheckPlotter::set_mc_scale_factors() {
    /*
     * Set the "scale_factor" in the DataConfig for each MC sample. The
     * scale_factor is used to rescale the MC as compared to the signal MC
     * (which has a scale factor of 1).
     *
     * For a BG MC sample, it is:
     *     scale_factor = bg_lumi / signal_lumi
     */
    const double SIG_LUMI = mc_config_.luminosity;
    cout<<"our MC_config luminosity is set to "<<SIG_LUMI<<endl;
    mc_config_.scale_factor = 1.;
   
    for (auto& i_pair : bg_configs_) {
        double new_scale = SIG_LUMI / i_pair.second.luminosity;
        cout<<"FOR "<<i_pair.first<<" OUR APPARENT LUMINOSITY IS "<<i_pair.second.luminosity<< "   AND OUR SCALE FACTOR IS "<<new_scale<<endl;
        i_pair.second.scale_factor = new_scale;
    }
}

double CrossCheckPlotter::get_rescaling(
        const DataConfig& DATA,
        const DataConfig & MC
        ) {
    /*
     * Given two luminosities in inverse picobarns, calculates the correct
     * scaling so that the two distributions have the same amount of data.
     */
    return DATA.luminosity / MC.luminosity;
}

double CrossCheckPlotter::set_area_rescale_factor() {
    /*
     * If the data config has a lumi of 0, then we scale the sum of the MC such
     * that the area from 60 to 120 GeV (the area under the Z peak) is the same
     * as in data. We store the information in the luminosity key of the
     * config. We scale the MC to their relative luminosity before calculating
     * this number.
     */
    const double LOWER = 60.;
    const double UPPER = 120.;
    // Open the histograms
    const bool DO_RESCALING = true;
    HistoStore histo_store = open_histos("z_mass_all", DO_RESCALING);
    TH1D* data_histo = histo_store.data_histo;
    TH1D* mc_histo = histo_store.mc_histo;
    std::vector < std::pair < std::string, TH1D* >> bg_histos = histo_store.bg_histos;
    // Check that open_histos exited successfully, otherwise end
    if (data_histo == nullptr || mc_histo == nullptr) {
        return -1;
    }

    // Copy the MC histogram and add all the bg histos
    TH1D* tmp_histo = dynamic_cast<TH1D*> (mc_histo->Clone());
    for (auto& i_pair : bg_histos) {
        if (i_pair.first == "4 QCD")continue;
        tmp_histo->Add(i_pair.second);
    }

    // Calculate the area
    const int DATA_LOW = data_histo->FindBin(LOWER);
    const int DATA_HIGH = data_histo->FindBin(UPPER);
    const double DATA_AREA = data_histo->Integral(DATA_LOW, DATA_HIGH);

    const int MC_LOW = tmp_histo->FindBin(LOWER);
    const int MC_HIGH = tmp_histo->FindBin(UPPER);
    const double MC_AREA = tmp_histo->Integral(MC_LOW, MC_HIGH);

    return DATA_AREA / MC_AREA;
}

std::vector<double> CrossCheckPlotter::get_rebinning(
        std::vector<double> desired_bins,
        const TH1 * const HISTO
        ) {
    /* Given a desired set of bin edges, and a histogram, finds the bin edges
     * in the histogram that most closely approximate the desired edges. This
     * is done by, for each desired edge, choosing the bin edge from the
     * histogram gram that is closest in terms of linear distance.
     */
    std::vector<double> out_vec;
    // Fill the old bins
    std::vector<double> old_bins;
    const int N_BINS = HISTO->GetXaxis()->GetNbins();
    for (int i_bin = 1; i_bin <= N_BINS; ++i_bin) {
        double bin_edge = HISTO->GetXaxis()->GetBinLowEdge(i_bin);
        old_bins.push_back(bin_edge);
    }
    // Add the high edge, which isn't included but is needed
    old_bins.push_back(HISTO->GetXaxis()->GetBinUpEdge(N_BINS));
    std::sort(old_bins.begin(), old_bins.end());

    // Loop through the desired bins.
    //
    // We use a binary search to find the actual
    // bins on either side of the desired bin, we then compare the distance and
    // pick the closest. At the end we remove duplicate entries. equal_range
    // will return a pointer to the first entry that is not less than our
    // desired bin, and one that is strictly greater than our test bin. This
    // means we might need to move one of the pointers back, and of course we
    // need to check that they don't run off the edge of the vector.
    std::sort(desired_bins.begin(), desired_bins.end());
    for (auto& i : desired_bins) {
        const double DESIRED_BIN = i;
        auto bounds = std::equal_range(old_bins.begin(), old_bins.end(), DESIRED_BIN);
        // Move the first pointer back if needed
        if (bounds.first == bounds.second
                && bounds.first != old_bins.begin()
                && *bounds.first != DESIRED_BIN
                ) {
            --bounds.first;
        }
        // Check distance, pick the closest (or the first for a tie)
        const double FIRST_BIN = *bounds.first;
        const double SECOND_BIN = *bounds.second;
        const double FIRST_DIST = std::abs(FIRST_BIN - DESIRED_BIN);
        const double SECOND_DIST = std::abs(SECOND_BIN - DESIRED_BIN);
        if (SECOND_DIST >= FIRST_DIST) {
            out_vec.push_back(FIRST_BIN);
        } else {
            out_vec.push_back(SECOND_BIN);
        }
    }

    // Remove the non-unique entries. Unique moves the non-uniques to the end
    // and returns a pointer to the first non-unique item, erase then removes
    // them.
    std::sort(out_vec.begin(), out_vec.end());
    out_vec.erase(std::unique(out_vec.begin(), out_vec.end()), out_vec.end());

    // Return our vector
    return out_vec;
}

HistoStore CrossCheckPlotter::open_histos(
        const std::string HISTO_NAME,
        const bool DO_RESCALE
        ) {
    /*
     * Open the histograms for a given PlotType and return them in a HistoStore
     * object. If DO_RESCALE is true, then use the DataConfig.scale_factor to
     * rescale the histogram. The Data is NEVER rescaled, only the signal MC
     * and BG MC are
     */
    TH1D* tmp_histo;
    cout << "Histo name is " << HISTO_NAME << endl;
    const std::string DATA_HISTO_NAME = data_config_.tdir_name + "/" + HISTO_NAME;
    data_config_.tfile->GetObject(DATA_HISTO_NAME.c_str(), tmp_histo);
    if (!tmp_histo) {
        std::cout << "Can not open the Data Histogram!" << std::endl;
        std::cout << DATA_HISTO_NAME << std::endl;
        return HistoStore(nullptr, nullptr,{});
    }
    TH1D* data_histo = dynamic_cast<TH1D*> (tmp_histo->Clone());
    // We always divide the bins by their width
    data_histo->Scale(1, "width");

    const std::string MC_HISTO_NAME = mc_config_.tdir_name + "/" + HISTO_NAME;
    mc_config_.tfile->GetObject(MC_HISTO_NAME.c_str(), tmp_histo);
    if (!tmp_histo) {
        std::cout << "Can not open the MC Histogram!" << std::endl;
        std::cout << MC_HISTO_NAME << std::endl;
        return HistoStore(nullptr, nullptr,{});
    }
    TH1D* mc_histo = dynamic_cast<TH1D*> (tmp_histo->Clone());
    mc_histo->Scale(1, "width");
    if (DO_RESCALE) {
        mc_histo->Scale(mc_config_.scale_factor);
    }

    std::vector < std::pair < std::string, TH1D* >> bg_histos = {};
    if (bg_configs_.size() != 0) {
        // Open each BG and save to a vector with its name
        for (auto& i_pair : bg_configs_) {
            std::string BG_HISTO_NAME = i_pair.second.tdir_name + "/" + HISTO_NAME;
            TH1D* bg_histo;
           
            i_pair.second.tfile->GetObject(BG_HISTO_NAME.c_str(), bg_histo);
            if (bg_histo && (i_pair.first.compare("4 QCD") == 0)) {
                cout << "OUR HISTO NAME IS " << BG_HISTO_NAME << endl << endl << endl;
                cout << "QCD bin Number of bins is " << bg_histo->GetNbinsX() << endl << endl << endl;
                cout << "OUR CENTER BIN VALUE IS " << bg_histo->GetBinContent(60);
            }
            if (!bg_histo && (i_pair.first.compare("4 QCD") != 0)) {
                std::cout << "Can not open the BG Histogram for ";
                std::cout << i_pair.first;
                std::cout << "!" << std::endl;
                return HistoStore(nullptr, nullptr,{});
            } else if (!bg_histo && (i_pair.first.compare("4 QCD") == 0)) {
                bg_histo = dynamic_cast<TH1D*> (data_histo->Clone());
                bg_histo->Scale(0);
            }

            // Clone incase, for some unknown reason (perhaps testing) we want
            // to use the same histogram twice
            TH1D* bg_clone = dynamic_cast<TH1D*> (bg_histo->Clone());

             cout << "ABOUT TO SCALE BIN 1 is " << bg_clone->GetBinContent(1) << "   /and scale factor is " << i_pair.second.scale_factor << endl;
            if (i_pair.first.compare("4 QCD") != 0)bg_clone->Scale(1, "width"); //QCD should already have bin width involved in it
            if (DO_RESCALE&&data_config_.luminosity>0) {
                if (i_pair.first.compare("4 QCD") == 0 && HISTO_NAME.compare("z_pt") == 0) {
                   

                }
//                cout << "FOr " << i_pair.first << " our scale factor is " << i_pair.second.scale_factor << endl;
                if (i_pair.first.compare("4 QCD") != 0)
                    if(data_config_.luminosity<0)bg_clone->Scale(i_pair.second.scale_factor);
                if (i_pair.first.compare("4 QCD") == 0 && HISTO_NAME.compare("z_pt") == 0) {
                    cout << "NEW VALUE FOR BIN 1 IS :" << bg_clone->GetBinContent(1) << endl;
                }
            }

            bg_histos.push_back(std::make_pair(i_pair.first, bg_clone));
        }
    }

    // Set up and return HistoStore
    return HistoStore(data_histo, mc_histo, bg_histos);
}

void CrossCheckPlotter::plot(
        const PlotType PLOT_TYPE,
        const std::string FILE_NAME
        ) {
    // Get our config_pair and some of the values from it
    config_map::iterator i_config_pair = conf_map_.find(PLOT_TYPE);
    if (i_config_pair == conf_map_.end()) {
        std::cout << "Missing PLOT_TYPE in conf_map_!" << std::endl;
        return;
    }
    PlotConfig plot_config = i_config_pair->second;
    const std::string HISTO_NAME = plot_config.histo_name;

    // Open the histograms
    const bool DO_RESCALING = true;
    HistoStore histo_store = open_histos(HISTO_NAME, DO_RESCALING);
    TH1D* data_histo = histo_store.data_histo;
    TH1D* mc_histo = histo_store.mc_histo;
    std::vector < std::pair < std::string, TH1D* >> bg_histos = histo_store.bg_histos;
    // Check that open_histos exited successfully, otherwise end
    if (data_histo == nullptr || mc_histo == nullptr) {
        return;
    }

    
    // Rebin if the binning is greater than 0 in size. If it is size one assume
    // we want a simple rebinning (where N bins are combined to 1), otherwise
    // the vector is the edges of the bins.
    if (plot_config.binning.size() == 1) {
        mc_histo->Rebin(static_cast<int> (plot_config.binning[0]));
        data_histo->Rebin(static_cast<int> (plot_config.binning[0]));
        for (auto& i_pair : bg_histos) {
           
            if ((PLOT_TYPE == PHISTAR || PLOT_TYPE == Z_PT)&&(i_pair.first == "4 QCD")) {
                cout << "TEST Before" << i_pair.second->GetNbinsX() << endl << endl << endl;
            }
            if (i_pair.first != "4 QCD" || PLOT_TYPE != Z_PT)i_pair.second->Rebin(static_cast<int> (plot_config.binning[0]));
            if ((PLOT_TYPE == PHISTAR || PLOT_TYPE == Z_PT || PLOT_TYPE == Z_MASS_FINE)&&(i_pair.first == "4 QCD")) {
                cout << "TEST After" << i_pair.second->GetNbinsX() << endl << endl << endl;
            }
        }
    } else if (plot_config.binning.size() > 1) {
        std::vector<double> new_binning = get_rebinning(
                plot_config.binning,
                data_histo
                );
        mc_histo = dynamic_cast<TH1D*> (
                mc_histo->Rebin(
                new_binning.size() - 1,
                "mc_rebinned_histo",
                &new_binning[0] // double*
                )
                );
        data_histo = dynamic_cast<TH1D*> (
                data_histo->Rebin(
                new_binning.size() - 1,
                "data_rebinned_histo",
                &new_binning[0] // double*
                )
                );
        for (auto& i_pair : bg_histos) {
            std::string new_name = i_pair.first + "_rebinned_histo";
            i_pair.second = dynamic_cast<TH1D*> (
                    i_pair.second->Rebin(
                    new_binning.size() - 1,
                    new_name.c_str(),
                    &new_binning[0] // double*
                    )
                    );
        }
    }

    // Normalize the plots
    // Signal MC
    if (area_rescale_factor_ > 0) {
        // Normalize by area
        std::cout << " so mc_hist scale factor is :" << area_rescale_factor_ << std::endl << std::endl;
        mc_histo->Scale(area_rescale_factor_);
    } else {
        // Normalize by luminosity
        //std::cout << "else statment mc Scale factor " << get_rescaling(data_config_, mc_config_) << std::endl << std::endl;
        mc_histo->Scale(get_rescaling(data_config_, mc_config_));
    }
    // BG MC
    for (auto& i_pair : bg_histos) {
        // Locate the DataConfig by name
        auto it = bg_configs_.find(i_pair.first);
        if (it != bg_configs_.end()) {
            if (area_rescale_factor_ > 0) {//Sanity checks
                // Normalize by area
                cout<<"OKay my head hurts now................................................."<<area_rescale_factor_<<endl;
                i_pair.second->Scale(area_rescale_factor_);
            } else {
                // Normalize by luminosity
                const double RESCALING = get_rescaling(data_config_, it->second);
                
                
                i_pair.second->Scale(RESCALING);
            }
        } else {
            std::cout << "Failed to normalize " << i_pair.first;
            std::cout << ". Scaling to 0!!" << std::endl;
            i_pair.second->Scale(0);
        }
    }

    // Update uncertainties after rescaling
    data_histo->Sumw2();
    mc_histo->Sumw2();
    for (auto& i_pair : bg_histos) {
        i_pair.second->Sumw2();
    }


    // Make a stack to store the MC and a ratio histogram for the ratio plot
    THStack* histo_stack = new THStack("hs", "Monte Carlo histrogram stack");
    TH1D* ratio_histo = dynamic_cast<TH1D*> (data_histo->Clone());

    sample(data_histo, mc_histo, bg_histos, PLOT_TYPE);
    // Title
    data_histo->SetTitle(0); // Remove the title, we'll place it by hand
    // Axis labels
    ratio_histo->GetXaxis()->SetTitle(plot_config.x_label.c_str());
    ratio_histo->GetXaxis()->SetLabelSize(0.1);
    ratio_histo->GetXaxis()->SetTitleSize(0.15);
    ratio_histo->GetXaxis()->SetTitleOffset(0.8);
    ratio_histo->GetYaxis()->SetTitle("Data/MC");
    ratio_histo->GetYaxis()->SetLabelSize(0.1);
    ratio_histo->GetYaxis()->SetTitleSize(0.1);
    ratio_histo->GetYaxis()->SetNdivisions(7, 0, 0); // Set 10 major ticks, 0 minor
    ratio_histo->GetYaxis()->SetTickLength(0.01); // Make the ticks smaller
    data_histo->GetXaxis()->SetTitle(0); // We use the ratio_histo to draw these
    data_histo->GetXaxis()->SetLabelSize(0); // Remove numbers
    data_histo->GetYaxis()->SetTitle(plot_config.y_label.c_str());

    // Set up the legend using the plot edges to set its location
    const double LEG_HEIGHT = 0.30;
    const double LEG_LENGTH = 0.20;
    TLegend legend(
            RIGHT_EDGE_ - LEG_LENGTH,
            (TOP_EDGE_ - 0.025) - LEG_HEIGHT, // 0.025 offset to avoid ticks
            RIGHT_EDGE_,
            TOP_EDGE_ - 0.025 // 0.025 offset to avoid the ticks
            );
    legend.SetFillColor(kWhite);
    legend.AddEntry(data_histo, data_config_.name.c_str(), "p");
    legend.AddEntry(mc_histo, mc_config_.name.c_str(), "f");
    legend.SetBorderSize(0); // Remove drop shadow and border
    legend.SetFillStyle(0); // Transparent

    // Set up the styles of the histograms
    style_->cd();
    // Position of axis labels
    mc_histo->GetYaxis()->SetTitleOffset(1.25);
    mc_histo->GetXaxis()->SetTitleOffset(1.1);
    // Marker, line, and fill style
    ratio_histo->SetMarkerStyle(kFullCircle);
    ratio_histo->SetMarkerColor(kBlack);
    ratio_histo->SetLineColor(kBlack);
    data_histo->SetMarkerStyle(kFullCircle);
    data_histo->SetMarkerColor(kBlack);
    data_histo->SetLineColor(kBlack);
    mc_histo->SetLineColor(kBlue);
    mc_histo->SetFillColor(kBlue);
    mc_histo->SetFillStyle(SPARSEDOT_FILL);

    // Set up the background histograms' style, coloring, and legend entry. We
    // have to do this almost at the end because we need the legend to exist.
    unsigned int i_style = 0;
    for (auto& i_pair : bg_histos) {
        // Reset if we run beyond the array
        if (i_style >= color_styles_.size()) {
            i_style = 0;
        }
        std::pair<RootFill, int> style_pair = color_styles_[i_style];
        ++i_style;
        // Set the color and fill
        i_pair.second->SetFillStyle(style_pair.first);
        i_pair.second->SetLineColor(style_pair.second);
        i_pair.second->SetFillColor(style_pair.second);
        // Add to the stack
        histo_stack->Add(i_pair.second);
        const std::string BG_NAME = bg_configs_[i_pair.first].name;
    }
    // Now add the legends. The stack fills from bottom up, and the legend from
    // top down, so we have to do a reverse loop for them to match.
    for (auto rit = bg_histos.rbegin(); rit != bg_histos.rend(); ++rit) {
        const std::string BG_NAME = bg_configs_[rit->first].name;
        legend.AddEntry(rit->second, BG_NAME.c_str(), "f");
    }
    // Added last because we added the legend entry first
    histo_stack->Add(mc_histo);

    // Set the plot range maximum and minimum based on the highest peak in
    // either histo
    // Set the maximum
    const double DATA_MAX = data_histo->GetMaximum();
    const double STACK_MAX = histo_stack->GetMaximum();

    const double MAX_CONST = 5;
    if (DATA_MAX > STACK_MAX) {
        data_histo->SetMaximum(DATA_MAX * MAX_CONST);
    } else {
        data_histo->SetMaximum(STACK_MAX * MAX_CONST);
    }
    // Set the minimum
    double bg_min_max = -1; // The smallest maximum
    for (auto& i_pair : bg_histos) {
        const double BG_MAX = i_pair.second->GetMaximum();
        if (BG_MAX < bg_min_max || bg_min_max < 0) {
            bg_min_max = BG_MAX;
        }
    };
    // Set the minimum if sane, otherwise trust root to do it
    if (bg_min_max > 0) {
        data_histo->SetMinimum(bg_min_max * 0.1);
    }

    // Add title
    TLatex *plot_title = nullptr;
    if (plot_config.title != "") {
        const std::string TITLE = plot_config.title;
        plot_title = new TLatex(0.18, 0.93, TITLE.c_str());
        plot_title->SetNDC();
        plot_title->SetTextFont(42);
        plot_title->SetTextColor(1);
        plot_title->SetTextSize(0.06);
        plot_title->SetTextAlign(22);
        plot_title->SetTextAngle(0);
    }

    // Make a canvas to hold the plot
    TCanvas canvas("canvas", "canvas", X_VAL_, Y_VAL_);
    canvas.Divide(1, 2); // Make two stacked plots
    canvas.cd(1);
    gPad->SetPad(0, RATIO_HEIGHT, 1., 1.);
    gPad->SetLogy(plot_config.logy);
    gPad->SetLogx(plot_config.logx);
    gPad->SetBottomMargin(0.01); // Remove the margin, we'll put it under the ratio

    // Add luminosity text outside the plot on the top right
    //double RIGHT_EDGE_ = 0.96;
    //double LEFT_EDGE_ = 0.10;
    //double TOP_EDGE_ = 0.95;


    const std::string LUMI_STRING = "19.7 fb^{-1} (8 TeV)";
    TLatex* lumi_latex = new TLatex(0.96 - 0.175, TOP_EDGE_ + 0.007, LUMI_STRING.c_str());
    lumi_latex->SetNDC(kTRUE); // Use pad coordinates, not Axis
    lumi_latex->SetTextSize(0.035);

    // Add CMS text inside the plot on the top left
    const std::string CMS_STRING = "CMS Preliminary";
    TLatex* cms_latex = new TLatex(LEFT_EDGE_ + 0.035, TOP_EDGE_ + 0.007, CMS_STRING.c_str());
    cms_latex->SetNDC(kTRUE); // Use pad coordinates, not Axis
    cms_latex->SetTextSize(0.035);
    TLatex mark1;
    mark1.SetTextSize(0.05);
    mark1.SetTextFont(61);
    mark1.SetNDC(true);
    //mark1.DrawLatex(0.15, 0.955, "CMS");
    TLatex mark2;
    mark2.SetTextSize(0.038);
    mark2.SetTextFont(52);
    mark2.SetNDC(true);
    //mark2.DrawLatex(0.23, 0.955, " Preliminary");
    // Draw the histograms
    data_histo->Draw("E"); // Set axis titles
    histo_stack->Draw("HIST SAME");
    data_histo->Draw("E SAME"); // Make point cover histogram
    legend.Draw();
    if (plot_title != nullptr) {
        plot_title->Draw();
    }
    lumi_latex->Draw();
    cms_latex->Draw();
    mark1.DrawLatex(0.15, 0.7, "CMS");
    mark2.DrawLatex(0.23, 0.955, " Preliminary");
    // Make the ratio plot
    canvas.cd(2);
    gPad->SetPad(0, 0.05, 1., RATIO_HEIGHT);
    gPad->SetTopMargin(0); // Move pad flush with plot above it
    gPad->SetLogx(plot_config.logx);
    // Sum all the MC histos
    TH1D* histo_sum = dynamic_cast<TH1D*> (mc_histo->Clone());
    for (auto& i_pair : bg_histos) {
        histo_sum->Add(i_pair.second);
    }
    // Make a red line at 1
    TF1 ratio_line("line", "pol0", ratio_histo->GetBinLowEdge(1), ratio_histo->GetBinLowEdge(ratio_histo->GetNbinsX()) + ratio_histo->GetBinWidth(ratio_histo->GetNbinsX()));
    ratio_line.SetParameter(0, 1);
    ratio_line.SetLineColor(kRed);
    // Make the ratio
    ratio_histo->Divide(data_histo, histo_sum);
    const double RATIO_OFFSET_FROM_1 = 0.2 + 0.02; // 0.02 is to avoid label clipping
    ratio_histo->SetMaximum(1. + RATIO_OFFSET_FROM_1);
    ratio_histo->SetMinimum(1. - RATIO_OFFSET_FROM_1);

    ratio_histo->Draw("E"); // Draw first for Axis labels
    ratio_line.Draw("SAME");
    ratio_histo->Draw("E SAME");

    // Redraw axises so tick marks show over the histograms
    canvas.cd(1);
    redraw_border();
    canvas.cd(2);
    redraw_border();

    // Save the plot to a file
    canvas.Print(FILE_NAME.c_str(), "pdf");
    const std::string C_FILE_NAME = FILE_NAME + ".C";
    canvas.Print(C_FILE_NAME.c_str(), "cxx");

    // Clean up
    delete ratio_histo;
    delete plot_title;
    delete histo_stack;
    delete lumi_latex;
    delete cms_latex;
}

void CrossCheckPlotter::redraw_border() {
    // https://root.cern.ch/drupal/content/how-redraw-axis-and-plot-borders
    // this little macro redraws the axis tick marks and the pad border lines.
    gPad->Update();
    gPad->RedrawAxis();
    //TLine l;
    //l.DrawLine(gPad->GetUxmin(), gPad->GetUymax(), gPad->GetUxmax(), gPad->GetUymax());
    //l.DrawLine(gPad->GetUxmax(), gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax());
}

void CrossCheckPlotter::set_plot_style() {
    style_ = new TStyle("style_", "Style for P-TDR");

    // For the canvas:
    style_->SetCanvasBorderMode(0);
    style_->SetCanvasColor(kWhite);
    style_->SetCanvasDefX(0); //Position on screen
    style_->SetCanvasDefY(0);

    // For the Pad:
    style_->SetPadBorderMode(0);
    style_->SetPadColor(kWhite);
    style_->SetPadGridX(false);
    style_->SetPadGridY(false);
    style_->SetGridColor(kBlack);
    style_->SetGridStyle(3);
    style_->SetGridWidth(1);

    // For the frame:
    style_->SetFrameBorderMode(0);
    style_->SetFrameBorderSize(1);
    style_->SetFrameFillColor(kWhite);
    style_->SetFrameFillStyle(0);
    style_->SetFrameLineColor(kBlack);
    style_->SetFrameLineStyle(1);
    style_->SetFrameLineWidth(1);

    // For the histo:
    // style_->SetHistFillColor(1);
    style_->SetHistFillStyle(0); //
    style_->SetHistLineColor(kBlack);
    style_->SetHistLineStyle(0);
    style_->SetHistLineWidth(1);

    style_->SetEndErrorSize(2);
    style_->SetErrorX(0.);

    style_->SetMarkerStyle(20);

    //For the fit/function:
    style_->SetOptFit(1);
    style_->SetFitFormat("5.4g");
    style_->SetFuncColor(kRed);
    style_->SetFuncStyle(1);
    style_->SetFuncWidth(1);

    //For the date:
    style_->SetOptDate(0);

    // For the statistics box:
    style_->SetOptFile(0);
    style_->SetOptStat(0); // To display the mean and RMS: SetOptStat("mr");
    style_->SetStatColor(kWhite);
    style_->SetStatFont(42);
    style_->SetStatFontSize(0.025);
    style_->SetStatTextColor(kBlack);
    style_->SetStatFormat("6.4g");
    style_->SetStatBorderSize(1);
    style_->SetStatH(0.1);
    style_->SetStatW(0.15);

    // Margins:
    style_->SetPadTopMargin(1 - TOP_EDGE_);
    style_->SetPadBottomMargin(BOTTOM_EDGE_);
    style_->SetPadLeftMargin(LEFT_EDGE_);
    style_->SetPadRightMargin(1 - RIGHT_EDGE_);

    // For the Global title:
    style_->SetOptTitle(0);
    style_->SetTitleFont(42);
    style_->SetTitleColor(kBlack);
    style_->SetTitleTextColor(kBlack);
    style_->SetTitleFillColor(kWhite); //10 is roughly kWhite, 10% grey?
    style_->SetTitleFontSize(0.05);

    // For the axis titles:
    style_->SetTitleColor(kBlack, "XYZ");
    style_->SetTitleFont(42, "XYZ");
    style_->SetTitleSize(0.06, "XYZ");
    style_->SetTitleXOffset(0.9);
    style_->SetTitleYOffset(1.25);

    // For the axis labels:
    style_->SetLabelColor(kBlack, "XYZ");
    style_->SetLabelFont(42, "XYZ");
    style_->SetLabelOffset(0.007, "XYZ");
    style_->SetLabelSize(0.05, "XYZ");

    // For the axis:
    style_->SetAxisColor(kBlack, "XYZ");
    style_->SetStripDecimals(true);
    style_->SetTickLength(0.03, "XYZ");
    style_->SetNdivisions(510, "XYZ");
    style_->SetPadTickX(true); // To get tick marks on the opposite side of the frame
    style_->SetPadTickY(true);

    // Change for log plots:
    style_->SetOptLogx(false);
    style_->SetOptLogy(false);
    style_->SetOptLogz(false);

    // Set the style
    style_->cd();
}

void CrossCheckPlotter::init_color_styles() {
    /*
     * Set up the color and hatching pairs used for backgrounds
     */
    color_styles_ = {
        {FORWARD_HATCH, kRed},
        {BACKWARD_HATCH, kGreen + 2},
        {VERT_HATCH, kMagenta + 2},
        {CROSS_HATCH, kOrange},
        {BACKWARD_HATCH, kOrange + 7},
        {VERT_HATCH, kRed},
        {CROSS_HATCH, kGreen + 2},
        {FORWARD_HATCH, kMagenta + 2},
    };
}

void CrossCheckPlotter::init_config_map() {
    /*
     * Here we fill the PlotConfigs. Unfortunately these must be set by hand,
     * and there should be one for every value in the PlotType enum.
     */
    // Z_MASS
    /* conf_map_.insert(
             config_pair(
             Z_MASS_ALL,
             PlotConfig(
             "m_{ee} [GeV]", // x_label
             "Events / GeV", // y_label
             "", // title
             "z_mass_all", // histogram name (for reading in)
             true, // log Y axis
             false, // log X axis
     {} // Desired new binning
     // DY Group Binning
     //{15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76,
     //81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141,
     //150, 160, 171, 185, 200, 220, 243, 273, 320, 380, 440, 510,
     //600, 1000, 1500, 2000 }               // Desired new binning
     )
     )
     );*/
    conf_map_.insert(
            config_pair(
            Z_MASS_COARSE,
            PlotConfig(
            "m_{ee} [GeV]",
            "Events / GeV",
            "",
            "z_mass_coarse",
            true,
            false,{}
    // DY Group Binning
    //{15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76,
    //81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141,
    //150, 160, 171, 185, 200, 220, 243, 273, 320, 380, 440, 510,
    //600, 1000, 1500, 2000 }               // Desired new binning
    )
    )
    );
    conf_map_.insert(
            config_pair(
            Z_MASS_FINE,
            PlotConfig(
            "m_{ee} [GeV]",
            "Events / GeV",
            "",
            "z_mass_fine",
            true,
            false,{}
    // DY Group Binning
    //{15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 64, 68, 72, 76,
    //81, 86, 91, 96, 101, 106, 110, 115, 120, 126, 133, 141,
    //150, 160, 171, 185, 200, 220, 243, 273, 320, 380, 440, 510,
    //600, 1000, 1500, 2000 }               // Desired new binning
    )
    )
    );
    // Z Rapidity
    conf_map_.insert(
            config_pair(
            Z_RAPIDITY,
            PlotConfig(
            "Y_{Z}",
            "Events / Unit Y",
            "",
            "z_rapidity",
            true,
            false,{}
    )
    )
    );
    // PT
    conf_map_.insert(
            config_pair(
            Z_PT,
            PlotConfig(
            "Z p_{T} [GeV]",
            "Events / GeV",
            "",
            "z_pt",
            true,
            false,{5} // with one entry, just calls histo->Rebin(5);
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E0_PT,
            PlotConfig(
            "e_{0} p_{T} [GeV]",
            "Events / GeV",
            "",
            "e0_pt",
            true,
            false,{5}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_PT,
            PlotConfig(
            "e_{1} p_{T} [GeV]",
            "Events / GeV",
            "",
            "e1_pt",
            true,
            false,{5}
    )
    )
    );
    // Eta
    conf_map_.insert(
            config_pair(
            E0_ETA,
            PlotConfig(
            "#eta_{e_{0}}",
            "Events / Unit #eta",
            "",
            "e0_eta",
            true,
            false,{}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_ETA,
            PlotConfig(
            "#eta_{e_{1}}",
            "Events / Unit #eta",
            "",
            "e1_eta",
            true,
            false,{}
    )
    )
    );
    // Phi
    conf_map_.insert(
            config_pair(
            E0_PHI,
            PlotConfig(
            "#phi_{e_{0}}",
            "Events / Unit #phi",
            "",
            "e0_phi",
            false,
            false,{}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_PHI,
            PlotConfig(
            "#phi_{e_{1}}",
            "Events / Unit #phi",
            "",
            "e1_phi",
            false,
            false,{}
    )
    )
    );
    // Charge
    conf_map_.insert(
            config_pair(
            E0_CHARGE,
            PlotConfig(
            "q_{e_{0}}",
            "Events",
            "",
            "e0_charge",
            false,
            false,{}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_CHARGE,
            PlotConfig(
            "q_{e_{1}}",
            "Events",
            "",
            "e1_charge",
            false,
            false,{}
    )
    )
    );
    // Phi*
    conf_map_.insert(
            config_pair(
            PHISTAR,
            PlotConfig(
            "#phi*",
            "Events / Unit #phi*",
            "",
            //"phistar_split",
            "phistar",
            true,
            true,
            // multiple entries means these are new bin edges
            //{0.0, 0.05, 0.1, 0.2, 0.3, 0.4, 0.6, 1.0}
    {.001, 0.004, 0.008, 0.012, 0.016, 0.020, 0.024, 0.029,
        0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081,
        0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219,
        0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496,
        1.947, 2.522, 3.277}
    )
    )
    );
    // Vertexes
    conf_map_.insert(
            config_pair(
            N_VERTS,
            PlotConfig(
            "Number of Vertexes",
            "Events",
            "",
            "n_verts",
            true,
            false,{0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12.,
        13., 14., 15., 16., 17., 18., 19., 20., 21., 22., 23., 24.,
        25., 26., 27., 28., 29., 30., 31., 32., 33., 34., 35., 36.,
        37., 38., 39., 40., 41., 42., 43., 44., 45., 46., 47., 48.,
        49., 50.}
    )
    )
    );
    // Electrons
    conf_map_.insert(
            config_pair(
            N_E,
            PlotConfig(
            "Number of Electrons",
            "Events",
            "",
            "n_electrons",
            true,
            false,{}
    )
    )
    );
    // Supercluster R9
    conf_map_.insert(
            config_pair(
            E0_R9,
            PlotConfig(
            "R9",
            "Events",
            "",
            "e0_r9",
            true,
            false,{}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_R9,
            PlotConfig(
            "R9",
            "Events",
            "",
            "e1_r9",
            true,
            false,{}
    )
    )
    );
    // Supercluster sigma ieta sigma ieta
    conf_map_.insert(
            config_pair(
            E0_SIGMAIETA,
            PlotConfig(
            "#sigma_{i #eta i #eta}^{e_{0}}",
            "Events",
            "",
            "e0_siesie",
            true,
            false,{}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_SIGMAIETA,
            PlotConfig(
            "#sigma_{i #eta i #eta}^{e_{1}}",
            "Events",
            "",
            "e1_siesie",
            true,
            false,{}
    )
    )
    );
    // Supercluster H/E
    conf_map_.insert(
            config_pair(
            E0_HE,
            PlotConfig(
            "H/E",
            "Events",
            "",
            "e0_he",
            true,
            false,{10}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_HE,
            PlotConfig(
            "H/E",
            "Events",
            "",
            "e1_he",
            true,
            false,{10}
    )
    )
    );
    // Supercluster dEta
    conf_map_.insert(
            config_pair(
            E0_DETA,
            PlotConfig(
            "d#eta",
            "Events",
            "",
            "e0_deta",
            true,
            false,{5}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_DETA,
            PlotConfig(
            "d#eta",
            "Events",
            "",
            "e1_deta",
            true,
            false,{5}
    )
    )
    );
    // Supercluster dPhi
    conf_map_.insert(
            config_pair(
            E0_DPHI,
            PlotConfig(
            "d#phi",
            "Events",
            "",
            "e0_dphi",
            true,
            false,{10}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_DPHI,
            PlotConfig(
            "d#phi",
            "Events",
            "",
            "e1_dphi",
            true,
            false,{10}
    )
    )
    );
    // Supercluster Track ISO
    conf_map_.insert(
            config_pair(
            E0_TRACKISO,
            PlotConfig(
            "Track ISO",
            "Events",
            "",
            "e0_track_iso",
            true,
            false,{10}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_TRACKISO,
            PlotConfig(
            "Track ISO",
            "Events",
            "",
            "e1_track_iso",
            true,
            false,{10}
    )
    )
    );
    // Supercluster ECAL ISO
    conf_map_.insert(
            config_pair(
            E0_ECALISO,
            PlotConfig(
            "ECAL ISO",
            "Events",
            "",
            "e0_ecal_iso",
            true,
            false,{10}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_ECALISO,
            PlotConfig(
            "ECAL ISO",
            "Events",
            "",
            "e1_ecal_iso",
            true,
            false,{10}
    )
    )
    );
    // Supercluster HCAL ISO
    conf_map_.insert(
            config_pair(
            E0_HCALISO,
            PlotConfig(
            "HCAL ISO",
            "Events",
            "",
            "e0_hcal_iso",
            true,
            false,{10}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_HCALISO,
            PlotConfig(
            "HCAL ISO",
            "Events",
            "",
            "e1_hcal_iso",
            true,
            false,{10}
    )
    )
    );
    // Supercluster 1/E - 1/P
    conf_map_.insert(
            config_pair(
            E0_1OEM1OP,
            PlotConfig(
            "1/E - 1/P",
            "Events",
            "",
            "e0_1oe_1op",
            true,
            false,{10}
    )
    )
    );
    conf_map_.insert(
            config_pair(
            E1_1OEM1OP,
            PlotConfig(
            "1/E - 1/P",
            "Events",
            "",
            "e1_1oe_1op",
            true,
            false,{10}
    )
    )
    );
}
