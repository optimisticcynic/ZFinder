{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:10 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,0.9208146,1.424743,7.75871);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis2[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *DownQuarkPair = new TH1D("DownQuarkPair","DownQuarkPair",35, xAxis2);
   DownQuarkPair->SetBinContent(1,6401750);
   DownQuarkPair->SetBinContent(2,6271500);
   DownQuarkPair->SetBinContent(3,6201500);
   DownQuarkPair->SetBinContent(4,6003750);
   DownQuarkPair->SetBinContent(5,5941000);
   DownQuarkPair->SetBinContent(6,5636500);
   DownQuarkPair->SetBinContent(7,5407000);
   DownQuarkPair->SetBinContent(8,5004800);
   DownQuarkPair->SetBinContent(9,4680200);
   DownQuarkPair->SetBinContent(10,4365833);
   DownQuarkPair->SetBinContent(11,3920143);
   DownQuarkPair->SetBinContent(12,3551400);
   DownQuarkPair->SetBinContent(13,3271286);
   DownQuarkPair->SetBinContent(14,2927500);
   DownQuarkPair->SetBinContent(15,2541778);
   DownQuarkPair->SetBinContent(16,2179600);
   DownQuarkPair->SetBinContent(17,1892909);
   DownQuarkPair->SetBinContent(18,1616833);
   DownQuarkPair->SetBinContent(19,1372786);
   DownQuarkPair->SetBinContent(20,1115706);
   DownQuarkPair->SetBinContent(21,876900);
   DownQuarkPair->SetBinContent(22,663041.7);
   DownQuarkPair->SetBinContent(23,491666.7);
   DownQuarkPair->SetBinContent(24,325923.1);
   DownQuarkPair->SetBinContent(25,201129.6);
   DownQuarkPair->SetBinContent(26,113379.7);
   DownQuarkPair->SetBinContent(27,52969.92);
   DownQuarkPair->SetBinContent(28,22941.52);
   DownQuarkPair->SetBinContent(29,10215.25);
   DownQuarkPair->SetBinContent(30,5259.574);
   DownQuarkPair->SetBinContent(31,2807.58);
   DownQuarkPair->SetBinContent(32,1474.501);
   DownQuarkPair->SetBinContent(33,707.8261);
   DownQuarkPair->SetBinContent(34,373.5099);
   DownQuarkPair->SetBinContent(35,80.47003);
   DownQuarkPair->SetBinContent(36,224);
   DownQuarkPair->SetEntries(560407);
   DownQuarkPair->SetStats(0);

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
