{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:17 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,0.6457605,1.424743,7.373804);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis27[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *UpQuarkPair = new TH1D("UpQuarkPair","UpQuarkPair",35, xAxis27);
   UpQuarkPair->SetBinContent(1,2757250);
   UpQuarkPair->SetBinContent(2,2651250);
   UpQuarkPair->SetBinContent(3,2635250);
   UpQuarkPair->SetBinContent(4,2467250);
   UpQuarkPair->SetBinContent(5,2389500);
   UpQuarkPair->SetBinContent(6,2311250);
   UpQuarkPair->SetBinContent(7,2165800);
   UpQuarkPair->SetBinContent(8,1994000);
   UpQuarkPair->SetBinContent(9,1814000);
   UpQuarkPair->SetBinContent(10,1649500);
   UpQuarkPair->SetBinContent(11,1436143);
   UpQuarkPair->SetBinContent(12,1243800);
   UpQuarkPair->SetBinContent(13,1098571);
   UpQuarkPair->SetBinContent(14,954500);
   UpQuarkPair->SetBinContent(15,807111.1);
   UpQuarkPair->SetBinContent(16,687300);
   UpQuarkPair->SetBinContent(17,570545.5);
   UpQuarkPair->SetBinContent(18,479083.3);
   UpQuarkPair->SetBinContent(19,389714.3);
   UpQuarkPair->SetBinContent(20,318352.9);
   UpQuarkPair->SetBinContent(21,254150);
   UpQuarkPair->SetBinContent(22,197750);
   UpQuarkPair->SetBinContent(23,149533.3);
   UpQuarkPair->SetBinContent(24,110769.2);
   UpQuarkPair->SetBinContent(25,72222.22);
   UpQuarkPair->SetBinContent(26,45455.7);
   UpQuarkPair->SetBinContent(27,24353.38);
   UpQuarkPair->SetBinContent(28,11947.37);
   UpQuarkPair->SetBinContent(29,5417.04);
   UpQuarkPair->SetBinContent(30,3089.362);
   UpQuarkPair->SetBinContent(31,1542.274);
   UpQuarkPair->SetBinContent(32,842.5721);
   UpQuarkPair->SetBinContent(33,363.4783);
   UpQuarkPair->SetBinContent(34,209.2715);
   UpQuarkPair->SetBinContent(35,41.64807);
   UpQuarkPair->SetBinContent(36,116);
   UpQuarkPair->SetEntries(204290);

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
