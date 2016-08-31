{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:10 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,2.004965,1.424743,6.612203);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis6[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *SingleQuark = new TH1D("SingleQuark","SingleQuark",35, xAxis6);
   SingleQuark->SetBinContent(1,685000);
   SingleQuark->SetBinContent(2,665500);
   SingleQuark->SetBinContent(3,669500);
   SingleQuark->SetBinContent(4,666750);
   SingleQuark->SetBinContent(5,688750);
   SingleQuark->SetBinContent(6,675250);
   SingleQuark->SetBinContent(7,688200);
   SingleQuark->SetBinContent(8,685800);
   SingleQuark->SetBinContent(9,670400);
   SingleQuark->SetBinContent(10,664333.3);
   SingleQuark->SetBinContent(11,705428.6);
   SingleQuark->SetBinContent(12,645400);
   SingleQuark->SetBinContent(13,694571.4);
   SingleQuark->SetBinContent(14,680875);
   SingleQuark->SetBinContent(15,688000);
   SingleQuark->SetBinContent(16,696500);
   SingleQuark->SetBinContent(17,693181.8);
   SingleQuark->SetBinContent(18,714916.7);
   SingleQuark->SetBinContent(19,713928.6);
   SingleQuark->SetBinContent(20,731882.4);
   SingleQuark->SetBinContent(21,748050);
   SingleQuark->SetBinContent(22,733208.3);
   SingleQuark->SetBinContent(23,723800);
   SingleQuark->SetBinContent(24,692282.1);
   SingleQuark->SetBinContent(25,607574.1);
   SingleQuark->SetBinContent(26,477987.3);
   SingleQuark->SetBinContent(27,308511.3);
   SingleQuark->SetBinContent(28,170263.2);
   SingleQuark->SetBinContent(29,88004.48);
   SingleQuark->SetBinContent(30,46063.83);
   SingleQuark->SetBinContent(31,23830.9);
   SingleQuark->SetBinContent(32,11975.61);
   SingleQuark->SetBinContent(33,5667.826);
   SingleQuark->SetBinContent(34,2776.159);
   SingleQuark->SetBinContent(35,584.4117);
   SingleQuark->SetBinContent(36,1597);
   SingleQuark->SetEntries(377612);
   SingleQuark->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   SingleQuark->SetLineColor(ci);
   SingleQuark->SetLineWidth(2);
   SingleQuark->GetXaxis()->SetRange(2,35);
   SingleQuark->GetXaxis()->SetLabelFont(42);
   SingleQuark->GetXaxis()->SetLabelSize(0.035);
   SingleQuark->GetXaxis()->SetTitleSize(0.035);
   SingleQuark->GetXaxis()->SetTitleFont(42);
   SingleQuark->GetYaxis()->SetLabelFont(42);
   SingleQuark->GetYaxis()->SetLabelSize(0.035);
   SingleQuark->GetYaxis()->SetTitleSize(0.035);
   SingleQuark->GetYaxis()->SetTitleFont(42);
   SingleQuark->GetZaxis()->SetLabelFont(42);
   SingleQuark->GetZaxis()->SetLabelSize(0.035);
   SingleQuark->GetZaxis()->SetTitleSize(0.035);
   SingleQuark->GetZaxis()->SetTitleFont(42);
   SingleQuark->Draw("");
   
   TPaveText *pt = new TPaveText(0.3419076,0.9357407,0.6580924,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("SingleQuark");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
