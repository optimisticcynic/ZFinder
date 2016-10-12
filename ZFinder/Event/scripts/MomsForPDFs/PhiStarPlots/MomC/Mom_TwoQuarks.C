{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:11 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,1.220908,1.424743,5.184448);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis8[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *TwoQuarks = new TH1D("TwoQuarks","TwoQuarks",35, xAxis8);
   TwoQuarks->SetBinContent(1,35750);
   TwoQuarks->SetBinContent(2,30500);
   TwoQuarks->SetBinContent(3,31000);
   TwoQuarks->SetBinContent(4,25500);
   TwoQuarks->SetBinContent(5,30000);
   TwoQuarks->SetBinContent(6,31250);
   TwoQuarks->SetBinContent(7,32400);
   TwoQuarks->SetBinContent(8,29000);
   TwoQuarks->SetBinContent(9,29600);
   TwoQuarks->SetBinContent(10,27833.33);
   TwoQuarks->SetBinContent(11,30714.29);
   TwoQuarks->SetBinContent(12,30600);
   TwoQuarks->SetBinContent(13,29285.71);
   TwoQuarks->SetBinContent(14,32375);
   TwoQuarks->SetBinContent(15,27888.89);
   TwoQuarks->SetBinContent(16,26500);
   TwoQuarks->SetBinContent(17,29454.55);
   TwoQuarks->SetBinContent(18,28083.33);
   TwoQuarks->SetBinContent(19,25142.86);
   TwoQuarks->SetBinContent(20,23588.24);
   TwoQuarks->SetBinContent(21,25700);
   TwoQuarks->SetBinContent(22,26375);
   TwoQuarks->SetBinContent(23,23533.33);
   TwoQuarks->SetBinContent(24,20897.44);
   TwoQuarks->SetBinContent(25,20777.78);
   TwoQuarks->SetBinContent(26,18493.67);
   TwoQuarks->SetBinContent(27,14315.79);
   TwoQuarks->SetBinContent(28,10467.84);
   TwoQuarks->SetBinContent(29,6488.789);
   TwoQuarks->SetBinContent(30,4200);
   TwoQuarks->SetBinContent(31,2586.006);
   TwoQuarks->SetBinContent(32,1547.672);
   TwoQuarks->SetBinContent(33,753.0435);
   TwoQuarks->SetBinContent(34,398.6755);
   TwoQuarks->SetBinContent(35,82.84992);
   TwoQuarks->SetBinContent(36,253);
   TwoQuarks->SetEntries(18663);
   TwoQuarks->SetStats(0);

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
