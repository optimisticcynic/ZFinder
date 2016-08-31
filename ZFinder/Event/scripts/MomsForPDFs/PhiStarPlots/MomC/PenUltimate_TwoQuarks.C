{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:18 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,1.42964,1.424743,6.812937);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis34[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *TwoQuarks = new TH1D("TwoQuarks","TwoQuarks",35, xAxis34);
   TwoQuarks->SetBinContent(1,989000);
   TwoQuarks->SetBinContent(2,971500);
   TwoQuarks->SetBinContent(3,993250);
   TwoQuarks->SetBinContent(4,945000);
   TwoQuarks->SetBinContent(5,960000);
   TwoQuarks->SetBinContent(6,941250);
   TwoQuarks->SetBinContent(7,900000);
   TwoQuarks->SetBinContent(8,881800);
   TwoQuarks->SetBinContent(9,834600);
   TwoQuarks->SetBinContent(10,803833.3);
   TwoQuarks->SetBinContent(11,758285.7);
   TwoQuarks->SetBinContent(12,728200);
   TwoQuarks->SetBinContent(13,688285.7);
   TwoQuarks->SetBinContent(14,642250);
   TwoQuarks->SetBinContent(15,588777.8);
   TwoQuarks->SetBinContent(16,546700);
   TwoQuarks->SetBinContent(17,492909.1);
   TwoQuarks->SetBinContent(18,454833.3);
   TwoQuarks->SetBinContent(19,394785.7);
   TwoQuarks->SetBinContent(20,350058.8);
   TwoQuarks->SetBinContent(21,301150);
   TwoQuarks->SetBinContent(22,258416.7);
   TwoQuarks->SetBinContent(23,213233.3);
   TwoQuarks->SetBinContent(24,171384.6);
   TwoQuarks->SetBinContent(25,133611.1);
   TwoQuarks->SetBinContent(26,96139.24);
   TwoQuarks->SetBinContent(27,62721.8);
   TwoQuarks->SetBinContent(28,35871.35);
   TwoQuarks->SetBinContent(29,19475.34);
   TwoQuarks->SetBinContent(30,11936.17);
   TwoQuarks->SetBinContent(31,6562.682);
   TwoQuarks->SetBinContent(32,3676.275);
   TwoQuarks->SetBinContent(33,1758.261);
   TwoQuarks->SetBinContent(34,927.1523);
   TwoQuarks->SetBinContent(35,185.7802);
   TwoQuarks->SetBinContent(36,535);
   TwoQuarks->SetEntries(162313);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   TwoQuarks->SetLineColor(ci);
   TwoQuarks->SetLineWidth(2);
   TwoQuarks->GetXaxis()->SetRange(2,35);
   TwoQuarks->GetXaxis()->SetLabelFont(42);
   TwoQuarks->GetXaxis()->SetLabelSize(0.035);
   TwoQuarks->GetXaxis()->SetTitleSize(0.035);
   TwoQuarks->GetXaxis()->SetTitleFont(42);
   TwoQuarks->GetYaxis()->SetLabelFont(42);
   TwoQuarks->GetYaxis()->SetLabelSize(0.035);
   TwoQuarks->GetYaxis()->SetTitleSize(0.035);
   TwoQuarks->GetYaxis()->SetTitleFont(42);
   TwoQuarks->GetZaxis()->SetLabelFont(42);
   TwoQuarks->GetZaxis()->SetLabelSize(0.035);
   TwoQuarks->GetZaxis()->SetTitleSize(0.035);
   TwoQuarks->GetZaxis()->SetTitleFont(42);
   TwoQuarks->Draw("");
   
   TPaveText *pt = new TPaveText(0.3559639,0.94,0.6440361,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("TwoQuarks");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
