{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:11 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,1.19742,1.424743,8.206704);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis10[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *QuarkAntiQuarkPair = new TH1D("QuarkAntiQuarkPair","QuarkAntiQuarkPair",35, xAxis10);
   QuarkAntiQuarkPair->SetBinContent(1,1.723625e+07);
   QuarkAntiQuarkPair->SetBinContent(2,1.691325e+07);
   QuarkAntiQuarkPair->SetBinContent(3,1.673075e+07);
   QuarkAntiQuarkPair->SetBinContent(4,1.63145e+07);
   QuarkAntiQuarkPair->SetBinContent(5,1.6017e+07);
   QuarkAntiQuarkPair->SetBinContent(6,1.5378e+07);
   QuarkAntiQuarkPair->SetBinContent(7,1.4684e+07);
   QuarkAntiQuarkPair->SetBinContent(8,1.38406e+07);
   QuarkAntiQuarkPair->SetBinContent(9,1.29872e+07);
   QuarkAntiQuarkPair->SetBinContent(10,1.211767e+07);
   QuarkAntiQuarkPair->SetBinContent(11,1.099229e+07);
   QuarkAntiQuarkPair->SetBinContent(12,1.0023e+07);
   QuarkAntiQuarkPair->SetBinContent(13,9173286);
   QuarkAntiQuarkPair->SetBinContent(14,8258500);
   QuarkAntiQuarkPair->SetBinContent(15,7240111);
   QuarkAntiQuarkPair->SetBinContent(16,6315700);
   QuarkAntiQuarkPair->SetBinContent(17,5470545);
   QuarkAntiQuarkPair->SetBinContent(18,4657333);
   QuarkAntiQuarkPair->SetBinContent(19,3917714);
   QuarkAntiQuarkPair->SetBinContent(20,3223647);
   QuarkAntiQuarkPair->SetBinContent(21,2535950);
   QuarkAntiQuarkPair->SetBinContent(22,1927792);
   QuarkAntiQuarkPair->SetBinContent(23,1393900);
   QuarkAntiQuarkPair->SetBinContent(24,916717.9);
   QuarkAntiQuarkPair->SetBinContent(25,548463);
   QuarkAntiQuarkPair->SetBinContent(26,296379.7);
   QuarkAntiQuarkPair->SetBinContent(27,131308.3);
   QuarkAntiQuarkPair->SetBinContent(28,55444.44);
   QuarkAntiQuarkPair->SetBinContent(29,23497.76);
   QuarkAntiQuarkPair->SetBinContent(30,11617.02);
   QuarkAntiQuarkPair->SetBinContent(31,5749.271);
   QuarkAntiQuarkPair->SetBinContent(32,3113.082);
   QuarkAntiQuarkPair->SetBinContent(33,1453.913);
   QuarkAntiQuarkPair->SetBinContent(34,772.1854);
   QuarkAntiQuarkPair->SetBinContent(35,158.2627);
   QuarkAntiQuarkPair->SetBinContent(36,462);
   QuarkAntiQuarkPair->SetEntries(1554855);
   QuarkAntiQuarkPair->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   QuarkAntiQuarkPair->SetLineColor(ci);
   QuarkAntiQuarkPair->SetLineWidth(2);
   QuarkAntiQuarkPair->GetXaxis()->SetRange(2,35);
   QuarkAntiQuarkPair->GetXaxis()->SetLabelFont(42);
   QuarkAntiQuarkPair->GetXaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkPair->GetXaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkPair->GetXaxis()->SetTitleFont(42);
   QuarkAntiQuarkPair->GetYaxis()->SetLabelFont(42);
   QuarkAntiQuarkPair->GetYaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkPair->GetYaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkPair->GetYaxis()->SetTitleFont(42);
   QuarkAntiQuarkPair->GetZaxis()->SetLabelFont(42);
   QuarkAntiQuarkPair->GetZaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkPair->GetZaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkPair->GetZaxis()->SetTitleFont(42);
   QuarkAntiQuarkPair->Draw("");
   
   TPaveText *pt = new TPaveText(0.2480321,0.94,0.7519679,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("QuarkAntiQuarkPair");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
