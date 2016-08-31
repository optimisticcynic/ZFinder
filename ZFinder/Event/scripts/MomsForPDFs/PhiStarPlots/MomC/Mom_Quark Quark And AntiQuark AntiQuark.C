{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:11 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,1.567255,1.424743,3.853504);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis13[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *Quark Quark And AntiQuark AntiQuark = new TH1D("Quark Quark And AntiQuark AntiQuark","Quark Quark And AntiQuark AntiQuark",35, xAxis13);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(1,171);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(2,136);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(3,140);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(4,125);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(5,143);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(6,149);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(7,199);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(8,169);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(9,179);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(10,196);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(11,262);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(12,186);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(13,257);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(14,312);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(15,301);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(16,327);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(17,399);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(18,387);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(19,431);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(20,491);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(21,638);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(22,755);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(23,846);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(24,1001);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(25,1321);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(26,1729);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(27,2225);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(28,2079);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(29,1654);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(30,1114);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(31,997);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(32,761);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(33,468);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(34,328);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(35,605);
   Quark Quark And AntiQuark AntiQuark->SetBinContent(36,281);
   Quark Quark And AntiQuark AntiQuark->SetEntries(21762);
   Quark Quark And AntiQuark AntiQuark->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   Quark Quark And AntiQuark AntiQuark->SetLineColor(ci);
   Quark Quark And AntiQuark AntiQuark->SetLineWidth(2);
   Quark Quark And AntiQuark AntiQuark->GetXaxis()->SetRange(2,35);
   Quark Quark And AntiQuark AntiQuark->GetXaxis()->SetLabelFont(42);
   Quark Quark And AntiQuark AntiQuark->GetXaxis()->SetLabelSize(0.035);
   Quark Quark And AntiQuark AntiQuark->GetXaxis()->SetTitleSize(0.035);
   Quark Quark And AntiQuark AntiQuark->GetXaxis()->SetTitleFont(42);
   Quark Quark And AntiQuark AntiQuark->GetYaxis()->SetLabelFont(42);
   Quark Quark And AntiQuark AntiQuark->GetYaxis()->SetLabelSize(0.035);
   Quark Quark And AntiQuark AntiQuark->GetYaxis()->SetTitleSize(0.035);
   Quark Quark And AntiQuark AntiQuark->GetYaxis()->SetTitleFont(42);
   Quark Quark And AntiQuark AntiQuark->GetZaxis()->SetLabelFont(42);
   Quark Quark And AntiQuark AntiQuark->GetZaxis()->SetLabelSize(0.035);
   Quark Quark And AntiQuark AntiQuark->GetZaxis()->SetTitleSize(0.035);
   Quark Quark And AntiQuark AntiQuark->GetZaxis()->SetTitleFont(42);
   Quark Quark And AntiQuark AntiQuark->Draw("");
   
   TPaveText *pt = new TPaveText(0.15,0.94,0.85,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("Quark Quark And AntiQuark AntiQuark");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
