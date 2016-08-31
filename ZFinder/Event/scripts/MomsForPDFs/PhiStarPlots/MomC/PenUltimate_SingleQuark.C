{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:18 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,1.756225,1.424743,7.776594);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis32[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *SingleQuark = new TH1D("SingleQuark","SingleQuark",35, xAxis32);
   SingleQuark->SetBinContent(1,8027000);
   SingleQuark->SetBinContent(2,7888750);
   SingleQuark->SetBinContent(3,7793000);
   SingleQuark->SetBinContent(4,7723500);
   SingleQuark->SetBinContent(5,7580000);
   SingleQuark->SetBinContent(6,7257500);
   SingleQuark->SetBinContent(7,7029800);
   SingleQuark->SetBinContent(8,6703000);
   SingleQuark->SetBinContent(9,6321400);
   SingleQuark->SetBinContent(10,5968667);
   SingleQuark->SetBinContent(11,5538429);
   SingleQuark->SetBinContent(12,5105800);
   SingleQuark->SetBinContent(13,4745000);
   SingleQuark->SetBinContent(14,4320125);
   SingleQuark->SetBinContent(15,3851111);
   SingleQuark->SetBinContent(16,3430200);
   SingleQuark->SetBinContent(17,3042273);
   SingleQuark->SetBinContent(18,2648083);
   SingleQuark->SetBinContent(19,2303857);
   SingleQuark->SetBinContent(20,1987588);
   SingleQuark->SetBinContent(21,1666050);
   SingleQuark->SetBinContent(22,1357250);
   SingleQuark->SetBinContent(23,1088933);
   SingleQuark->SetBinContent(24,838641);
   SingleQuark->SetBinContent(25,615759.3);
   SingleQuark->SetBinContent(26,419987.3);
   SingleQuark->SetBinContent(27,246436.1);
   SingleQuark->SetBinContent(28,132707.6);
   SingleQuark->SetBinContent(29,67596.41);
   SingleQuark->SetBinContent(30,34953.19);
   SingleQuark->SetBinContent(31,18638.48);
   SingleQuark->SetBinContent(32,9372.506);
   SingleQuark->SetBinContent(33,4483.478);
   SingleQuark->SetBinContent(34,2206.623);
   SingleQuark->SetBinContent(35,456.3439);
   SingleQuark->SetBinContent(36,1321);
   SingleQuark->SetEntries(949228);

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
