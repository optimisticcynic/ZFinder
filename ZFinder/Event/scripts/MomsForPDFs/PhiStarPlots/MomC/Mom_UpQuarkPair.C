{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:10 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,0.7927609,1.424743,7.811714);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis1[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *UpQuarkPair = new TH1D("UpQuarkPair","UpQuarkPair",35, xAxis1);
   UpQuarkPair->SetBinContent(1,6921750);
   UpQuarkPair->SetBinContent(2,6796250);
   UpQuarkPair->SetBinContent(3,6746500);
   UpQuarkPair->SetBinContent(4,6570500);
   UpQuarkPair->SetBinContent(5,6380500);
   UpQuarkPair->SetBinContent(6,6174750);
   UpQuarkPair->SetBinContent(7,5819800);
   UpQuarkPair->SetBinContent(8,5529400);
   UpQuarkPair->SetBinContent(9,5150200);
   UpQuarkPair->SetBinContent(10,4786000);
   UpQuarkPair->SetBinContent(11,4321286);
   UpQuarkPair->SetBinContent(12,3951000);
   UpQuarkPair->SetBinContent(13,3509857);
   UpQuarkPair->SetBinContent(14,3155250);
   UpQuarkPair->SetBinContent(15,2762889);
   UpQuarkPair->SetBinContent(16,2411400);
   UpQuarkPair->SetBinContent(17,2050727);
   UpQuarkPair->SetBinContent(18,1741417);
   UpQuarkPair->SetBinContent(19,1446500);
   UpQuarkPair->SetBinContent(20,1192353);
   UpQuarkPair->SetBinContent(21,934500);
   UpQuarkPair->SetBinContent(22,711000);
   UpQuarkPair->SetBinContent(23,513466.7);
   UpQuarkPair->SetBinContent(24,343051.3);
   UpQuarkPair->SetBinContent(25,207314.8);
   UpQuarkPair->SetBinContent(26,114443);
   UpQuarkPair->SetBinContent(27,52240.6);
   UpQuarkPair->SetBinContent(28,23362.57);
   UpQuarkPair->SetBinContent(29,9753.363);
   UpQuarkPair->SetBinContent(30,5034.043);
   UpQuarkPair->SetBinContent(31,2326.531);
   UpQuarkPair->SetBinContent(32,1259.424);
   UpQuarkPair->SetBinContent(33,638.2609);
   UpQuarkPair->SetBinContent(34,319.2053);
   UpQuarkPair->SetBinContent(35,62.47211);
   UpQuarkPair->SetBinContent(36,190);
   UpQuarkPair->SetEntries(604038);
   UpQuarkPair->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   UpQuarkPair->SetLineColor(ci);
   UpQuarkPair->SetLineWidth(2);
   UpQuarkPair->GetXaxis()->SetRange(2,35);
   UpQuarkPair->GetXaxis()->SetLabelFont(42);
   UpQuarkPair->GetXaxis()->SetLabelSize(0.035);
   UpQuarkPair->GetXaxis()->SetTitleSize(0.035);
   UpQuarkPair->GetXaxis()->SetTitleFont(42);
   UpQuarkPair->GetYaxis()->SetLabelFont(42);
   UpQuarkPair->GetYaxis()->SetLabelSize(0.035);
   UpQuarkPair->GetYaxis()->SetTitleSize(0.035);
   UpQuarkPair->GetYaxis()->SetTitleFont(42);
   UpQuarkPair->GetZaxis()->SetLabelFont(42);
   UpQuarkPair->GetZaxis()->SetLabelSize(0.035);
   UpQuarkPair->GetZaxis()->SetTitleSize(0.035);
   UpQuarkPair->GetZaxis()->SetTitleFont(42);
   UpQuarkPair->Draw("");
   
   TPaveText *pt = new TPaveText(0.3358835,0.9369753,0.6641165,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("UpQuarkPair");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
