{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:18 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,-0.7694032,1.424743,6.43051);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis29[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *StrangeQuarkPair = new TH1D("StrangeQuarkPair","StrangeQuarkPair",35, xAxis29);
   StrangeQuarkPair->SetBinContent(1,290750);
   StrangeQuarkPair->SetBinContent(2,269750);
   StrangeQuarkPair->SetBinContent(3,271000);
   StrangeQuarkPair->SetBinContent(4,254000);
   StrangeQuarkPair->SetBinContent(5,252000);
   StrangeQuarkPair->SetBinContent(6,247500);
   StrangeQuarkPair->SetBinContent(7,237400);
   StrangeQuarkPair->SetBinContent(8,205400);
   StrangeQuarkPair->SetBinContent(9,174800);
   StrangeQuarkPair->SetBinContent(10,172500);
   StrangeQuarkPair->SetBinContent(11,143857.1);
   StrangeQuarkPair->SetBinContent(12,129800);
   StrangeQuarkPair->SetBinContent(13,105000);
   StrangeQuarkPair->SetBinContent(14,93750);
   StrangeQuarkPair->SetBinContent(15,80222.22);
   StrangeQuarkPair->SetBinContent(16,68900);
   StrangeQuarkPair->SetBinContent(17,57636.36);
   StrangeQuarkPair->SetBinContent(18,47333.33);
   StrangeQuarkPair->SetBinContent(19,38285.71);
   StrangeQuarkPair->SetBinContent(20,32294.12);
   StrangeQuarkPair->SetBinContent(21,24450);
   StrangeQuarkPair->SetBinContent(22,18166.67);
   StrangeQuarkPair->SetBinContent(23,13233.33);
   StrangeQuarkPair->SetBinContent(24,9153.846);
   StrangeQuarkPair->SetBinContent(25,5888.889);
   StrangeQuarkPair->SetBinContent(26,3822.785);
   StrangeQuarkPair->SetBinContent(27,1789.474);
   StrangeQuarkPair->SetBinContent(28,736.8421);
   StrangeQuarkPair->SetBinContent(29,345.2915);
   StrangeQuarkPair->SetBinContent(30,182.9787);
   StrangeQuarkPair->SetBinContent(31,52.47813);
   StrangeQuarkPair->SetBinContent(32,57.64967);
   StrangeQuarkPair->SetBinContent(33,12.17391);
   StrangeQuarkPair->SetBinContent(34,11.92053);
   StrangeQuarkPair->SetBinContent(35,1.784917);
   StrangeQuarkPair->SetBinContent(36,9);
   StrangeQuarkPair->SetEntries(20201);

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
