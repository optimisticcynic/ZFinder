{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:11 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,-0.4158593,1.424743,7.85473);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis12[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *QuarkAntiQuarkNotPair = new TH1D("QuarkAntiQuarkNotPair","QuarkAntiQuarkNotPair",35, xAxis12);
   QuarkAntiQuarkNotPair->SetBinContent(1,4500000);
   QuarkAntiQuarkNotPair->SetBinContent(2,4125000);
   QuarkAntiQuarkNotPair->SetBinContent(3,5625000);
   QuarkAntiQuarkNotPair->SetBinContent(4,4625000);
   QuarkAntiQuarkNotPair->SetBinContent(5,5250000);
   QuarkAntiQuarkNotPair->SetBinContent(6,3937500);
   QuarkAntiQuarkNotPair->SetBinContent(7,4040000);
   QuarkAntiQuarkNotPair->SetBinContent(8,4280000);
   QuarkAntiQuarkNotPair->SetBinContent(9,5120000);
   QuarkAntiQuarkNotPair->SetBinContent(10,3472222);
   QuarkAntiQuarkNotPair->SetBinContent(11,2591837);
   QuarkAntiQuarkNotPair->SetBinContent(12,3400000);
   QuarkAntiQuarkNotPair->SetBinContent(13,2448980);
   QuarkAntiQuarkNotPair->SetBinContent(14,2703125);
   QuarkAntiQuarkNotPair->SetBinContent(15,2197531);
   QuarkAntiQuarkNotPair->SetBinContent(16,1760000);
   QuarkAntiQuarkNotPair->SetBinContent(17,1479339);
   QuarkAntiQuarkNotPair->SetBinContent(18,1513889);
   QuarkAntiQuarkNotPair->SetBinContent(19,1321429);
   QuarkAntiQuarkNotPair->SetBinContent(20,1044983);
   QuarkAntiQuarkNotPair->SetBinContent(21,857500);
   QuarkAntiQuarkNotPair->SetBinContent(22,666666.7);
   QuarkAntiQuarkNotPair->SetBinContent(23,541111.1);
   QuarkAntiQuarkNotPair->SetBinContent(24,407626.6);
   QuarkAntiQuarkNotPair->SetBinContent(25,248971.2);
   QuarkAntiQuarkNotPair->SetBinContent(26,145649.7);
   QuarkAntiQuarkNotPair->SetBinContent(27,66990.79);
   QuarkAntiQuarkNotPair->SetBinContent(28,37550.02);
   QuarkAntiQuarkNotPair->SetBinContent(29,17173.08);
   QuarkAntiQuarkNotPair->SetBinContent(30,9651.426);
   QuarkAntiQuarkNotPair->SetBinContent(31,3841.937);
   QuarkAntiQuarkNotPair->SetBinContent(32,1676.491);
   QuarkAntiQuarkNotPair->SetBinContent(33,583.7429);
   QuarkAntiQuarkNotPair->SetBinContent(34,235.0774);
   QuarkAntiQuarkNotPair->SetBinContent(35,5.155012);
   QuarkAntiQuarkNotPair->SetBinContent(36,108);
   QuarkAntiQuarkNotPair->SetEntries(11397);
   QuarkAntiQuarkNotPair->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   QuarkAntiQuarkNotPair->SetLineColor(ci);
   QuarkAntiQuarkNotPair->SetLineWidth(2);
   QuarkAntiQuarkNotPair->GetXaxis()->SetRange(2,35);
   QuarkAntiQuarkNotPair->GetXaxis()->SetLabelFont(42);
   QuarkAntiQuarkNotPair->GetXaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkNotPair->GetXaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkNotPair->GetXaxis()->SetTitleFont(42);
   QuarkAntiQuarkNotPair->GetYaxis()->SetLabelFont(42);
   QuarkAntiQuarkNotPair->GetYaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkNotPair->GetYaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkNotPair->GetYaxis()->SetTitleFont(42);
   QuarkAntiQuarkNotPair->GetZaxis()->SetLabelFont(42);
   QuarkAntiQuarkNotPair->GetZaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkNotPair->GetZaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkNotPair->GetZaxis()->SetTitleFont(42);
   QuarkAntiQuarkNotPair->Draw("");
   
   TPaveText *pt = new TPaveText(0.2063655,0.94,0.7936345,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("QuarkAntiQuarkNotPair");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
