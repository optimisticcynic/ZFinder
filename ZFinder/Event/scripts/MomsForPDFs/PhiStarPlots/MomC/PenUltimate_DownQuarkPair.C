{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:18 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,0.7877444,1.424743,7.341457);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis28[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *DownQuarkPair = new TH1D("DownQuarkPair","DownQuarkPair",35, xAxis28);
   DownQuarkPair->SetBinContent(1,2593500);
   DownQuarkPair->SetBinContent(2,2561750);
   DownQuarkPair->SetBinContent(3,2474250);
   DownQuarkPair->SetBinContent(4,2421250);
   DownQuarkPair->SetBinContent(5,2351000);
   DownQuarkPair->SetBinContent(6,2230750);
   DownQuarkPair->SetBinContent(7,2065200);
   DownQuarkPair->SetBinContent(8,1888800);
   DownQuarkPair->SetBinContent(9,1744400);
   DownQuarkPair->SetBinContent(10,1586167);
   DownQuarkPair->SetBinContent(11,1361571);
   DownQuarkPair->SetBinContent(12,1171000);
   DownQuarkPair->SetBinContent(13,1067857);
   DownQuarkPair->SetBinContent(14,944875);
   DownQuarkPair->SetBinContent(15,804666.7);
   DownQuarkPair->SetBinContent(16,654000);
   DownQuarkPair->SetBinContent(17,564636.4);
   DownQuarkPair->SetBinContent(18,478416.7);
   DownQuarkPair->SetBinContent(19,398071.4);
   DownQuarkPair->SetBinContent(20,321764.7);
   DownQuarkPair->SetBinContent(21,256350);
   DownQuarkPair->SetBinContent(22,199791.7);
   DownQuarkPair->SetBinContent(23,155966.7);
   DownQuarkPair->SetBinContent(24,109230.8);
   DownQuarkPair->SetBinContent(25,76611.11);
   DownQuarkPair->SetBinContent(26,47696.2);
   DownQuarkPair->SetBinContent(27,25812.03);
   DownQuarkPair->SetBinContent(28,12046.78);
   DownQuarkPair->SetBinContent(29,6058.296);
   DownQuarkPair->SetBinContent(30,3123.404);
   DownQuarkPair->SetBinContent(31,1714.286);
   DownQuarkPair->SetBinContent(32,891.3525);
   DownQuarkPair->SetBinContent(33,481.7391);
   DownQuarkPair->SetBinContent(34,227.8146);
   DownQuarkPair->SetBinContent(35,55.48118);
   DownQuarkPair->SetBinContent(36,122);
   DownQuarkPair->SetEntries(200049);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   DownQuarkPair->SetLineColor(ci);
   DownQuarkPair->SetLineWidth(2);
   DownQuarkPair->GetXaxis()->SetRange(2,35);
   DownQuarkPair->GetXaxis()->SetLabelFont(42);
   DownQuarkPair->GetXaxis()->SetLabelSize(0.035);
   DownQuarkPair->GetXaxis()->SetTitleSize(0.035);
   DownQuarkPair->GetXaxis()->SetTitleFont(42);
   DownQuarkPair->GetYaxis()->SetLabelFont(42);
   DownQuarkPair->GetYaxis()->SetLabelSize(0.035);
   DownQuarkPair->GetYaxis()->SetTitleSize(0.035);
   DownQuarkPair->GetYaxis()->SetTitleFont(42);
   DownQuarkPair->GetZaxis()->SetLabelFont(42);
   DownQuarkPair->GetZaxis()->SetLabelSize(0.035);
   DownQuarkPair->GetZaxis()->SetTitleSize(0.035);
   DownQuarkPair->GetZaxis()->SetTitleFont(42);
   DownQuarkPair->Draw("");
   
   TPaveText *pt = new TPaveText(0.301245,0.94,0.698755,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("DownQuarkPair");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
