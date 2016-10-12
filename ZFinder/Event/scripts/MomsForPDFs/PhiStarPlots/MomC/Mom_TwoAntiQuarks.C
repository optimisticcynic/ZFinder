{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:11 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,0.1031723,1.424743,4.59793);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis9[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *TwoAntiQuarks = new TH1D("TwoAntiQuarks","TwoAntiQuarks",35, xAxis9);
   TwoAntiQuarks->SetBinContent(1,7000);
   TwoAntiQuarks->SetBinContent(2,3500);
   TwoAntiQuarks->SetBinContent(3,4000);
   TwoAntiQuarks->SetBinContent(4,5750);
   TwoAntiQuarks->SetBinContent(5,5750);
   TwoAntiQuarks->SetBinContent(6,6000);
   TwoAntiQuarks->SetBinContent(7,7400);
   TwoAntiQuarks->SetBinContent(8,4800);
   TwoAntiQuarks->SetBinContent(9,6200);
   TwoAntiQuarks->SetBinContent(10,4833.333);
   TwoAntiQuarks->SetBinContent(11,6714.286);
   TwoAntiQuarks->SetBinContent(12,6600);
   TwoAntiQuarks->SetBinContent(13,7428.571);
   TwoAntiQuarks->SetBinContent(14,6625);
   TwoAntiQuarks->SetBinContent(15,5555.556);
   TwoAntiQuarks->SetBinContent(16,6200);
   TwoAntiQuarks->SetBinContent(17,6818.182);
   TwoAntiQuarks->SetBinContent(18,4166.667);
   TwoAntiQuarks->SetBinContent(19,5642.857);
   TwoAntiQuarks->SetBinContent(20,5294.118);
   TwoAntiQuarks->SetBinContent(21,6200);
   TwoAntiQuarks->SetBinContent(22,5083.333);
   TwoAntiQuarks->SetBinContent(23,4666.667);
   TwoAntiQuarks->SetBinContent(24,4769.231);
   TwoAntiQuarks->SetBinContent(25,3685.185);
   TwoAntiQuarks->SetBinContent(26,3392.405);
   TwoAntiQuarks->SetBinContent(27,2413.534);
   TwoAntiQuarks->SetBinContent(28,1690.058);
   TwoAntiQuarks->SetBinContent(29,928.2511);
   TwoAntiQuarks->SetBinContent(30,540.4255);
   TwoAntiQuarks->SetBinContent(31,320.6997);
   TwoAntiQuarks->SetBinContent(32,139.6896);
   TwoAntiQuarks->SetBinContent(33,60.86957);
   TwoAntiQuarks->SetBinContent(34,35.76159);
   TwoAntiQuarks->SetBinContent(35,7.13967);
   TwoAntiQuarks->SetBinContent(36,28);
   TwoAntiQuarks->SetEntries(3169);
   TwoAntiQuarks->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   TwoAntiQuarks->SetLineColor(ci);
   TwoAntiQuarks->SetLineWidth(2);
   TwoAntiQuarks->GetXaxis()->SetRange(2,35);
   TwoAntiQuarks->GetXaxis()->SetLabelFont(42);
   TwoAntiQuarks->GetXaxis()->SetLabelSize(0.035);
   TwoAntiQuarks->GetXaxis()->SetTitleSize(0.035);
   TwoAntiQuarks->GetXaxis()->SetTitleFont(42);
   TwoAntiQuarks->GetYaxis()->SetLabelFont(42);
   TwoAntiQuarks->GetYaxis()->SetLabelSize(0.035);
   TwoAntiQuarks->GetYaxis()->SetTitleSize(0.035);
   TwoAntiQuarks->GetYaxis()->SetTitleFont(42);
   TwoAntiQuarks->GetZaxis()->SetLabelFont(42);
   TwoAntiQuarks->GetZaxis()->SetLabelSize(0.035);
   TwoAntiQuarks->GetZaxis()->SetTitleSize(0.035);
   TwoAntiQuarks->GetZaxis()->SetTitleFont(42);
   TwoAntiQuarks->Draw("");
   
   TPaveText *pt = new TPaveText(0.3072691,0.94,0.6927309,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("TwoAntiQuarks");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
