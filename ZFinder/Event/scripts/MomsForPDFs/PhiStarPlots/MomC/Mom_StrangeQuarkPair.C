{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:10 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,-0.01136648,1.424743,7.389692);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis3[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *StrangeQuarkPair = new TH1D("StrangeQuarkPair","StrangeQuarkPair",35, xAxis3);
   StrangeQuarkPair->SetBinContent(1,2459500);
   StrangeQuarkPair->SetBinContent(2,2355250);
   StrangeQuarkPair->SetBinContent(3,2347500);
   StrangeQuarkPair->SetBinContent(4,2304000);
   StrangeQuarkPair->SetBinContent(5,2269500);
   StrangeQuarkPair->SetBinContent(6,2213250);
   StrangeQuarkPair->SetBinContent(7,2133400);
   StrangeQuarkPair->SetBinContent(8,2039600);
   StrangeQuarkPair->SetBinContent(9,1895200);
   StrangeQuarkPair->SetBinContent(10,1783833);
   StrangeQuarkPair->SetBinContent(11,1624286);
   StrangeQuarkPair->SetBinContent(12,1498600);
   StrangeQuarkPair->SetBinContent(13,1399857);
   StrangeQuarkPair->SetBinContent(14,1254375);
   StrangeQuarkPair->SetBinContent(15,1115778);
   StrangeQuarkPair->SetBinContent(16,969900);
   StrangeQuarkPair->SetBinContent(17,861818.2);
   StrangeQuarkPair->SetBinContent(18,723000);
   StrangeQuarkPair->SetBinContent(19,598857.1);
   StrangeQuarkPair->SetBinContent(20,492764.7);
   StrangeQuarkPair->SetBinContent(21,389850);
   StrangeQuarkPair->SetBinContent(22,298041.7);
   StrangeQuarkPair->SetBinContent(23,209000);
   StrangeQuarkPair->SetBinContent(24,131538.5);
   StrangeQuarkPair->SetBinContent(25,74185.19);
   StrangeQuarkPair->SetBinContent(26,38810.13);
   StrangeQuarkPair->SetBinContent(27,15721.8);
   StrangeQuarkPair->SetBinContent(28,5818.713);
   StrangeQuarkPair->SetBinContent(29,2421.525);
   StrangeQuarkPair->SetBinContent(30,880.8511);
   StrangeQuarkPair->SetBinContent(31,408.1633);
   StrangeQuarkPair->SetBinContent(32,250.5543);
   StrangeQuarkPair->SetBinContent(33,66.08696);
   StrangeQuarkPair->SetBinContent(34,58.27815);
   StrangeQuarkPair->SetBinContent(35,10.7095);
   StrangeQuarkPair->SetBinContent(36,35);
   StrangeQuarkPair->SetEntries(227927);
   StrangeQuarkPair->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   StrangeQuarkPair->SetLineColor(ci);
   StrangeQuarkPair->SetLineWidth(2);
   StrangeQuarkPair->GetXaxis()->SetRange(2,35);
   StrangeQuarkPair->GetXaxis()->SetLabelFont(42);
   StrangeQuarkPair->GetXaxis()->SetLabelSize(0.035);
   StrangeQuarkPair->GetXaxis()->SetTitleSize(0.035);
   StrangeQuarkPair->GetXaxis()->SetTitleFont(42);
   StrangeQuarkPair->GetYaxis()->SetLabelFont(42);
   StrangeQuarkPair->GetYaxis()->SetLabelSize(0.035);
   StrangeQuarkPair->GetYaxis()->SetTitleSize(0.035);
   StrangeQuarkPair->GetYaxis()->SetTitleFont(42);
   StrangeQuarkPair->GetZaxis()->SetLabelFont(42);
   StrangeQuarkPair->GetZaxis()->SetLabelSize(0.035);
   StrangeQuarkPair->GetZaxis()->SetTitleSize(0.035);
   StrangeQuarkPair->GetZaxis()->SetTitleFont(42);
   StrangeQuarkPair->Draw("");
   
   TPaveText *pt = new TPaveText(0.2761446,0.9357407,0.7238554,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("StrangeQuarkPair");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
