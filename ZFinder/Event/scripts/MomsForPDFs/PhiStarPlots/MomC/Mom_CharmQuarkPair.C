{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:10 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,-0.5269083,1.424743,7.073522);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis4[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *CharmQuarkPair = new TH1D("CharmQuarkPair","CharmQuarkPair",35, xAxis4);
   CharmQuarkPair->SetBinContent(1,1066750);
   CharmQuarkPair->SetBinContent(2,1086250);
   CharmQuarkPair->SetBinContent(3,1048500);
   CharmQuarkPair->SetBinContent(4,1045000);
   CharmQuarkPair->SetBinContent(5,1040000);
   CharmQuarkPair->SetBinContent(6,986500);
   CharmQuarkPair->SetBinContent(7,955400);
   CharmQuarkPair->SetBinContent(8,910600);
   CharmQuarkPair->SetBinContent(9,884400);
   CharmQuarkPair->SetBinContent(10,833833.3);
   CharmQuarkPair->SetBinContent(11,790857.1);
   CharmQuarkPair->SetBinContent(12,710200);
   CharmQuarkPair->SetBinContent(13,686571.4);
   CharmQuarkPair->SetBinContent(14,633750);
   CharmQuarkPair->SetBinContent(15,557444.4);
   CharmQuarkPair->SetBinContent(16,506000);
   CharmQuarkPair->SetBinContent(17,438818.2);
   CharmQuarkPair->SetBinContent(18,380833.3);
   CharmQuarkPair->SetBinContent(19,316142.9);
   CharmQuarkPair->SetBinContent(20,269941.2);
   CharmQuarkPair->SetBinContent(21,208800);
   CharmQuarkPair->SetBinContent(22,157708.3);
   CharmQuarkPair->SetBinContent(23,108733.3);
   CharmQuarkPair->SetBinContent(24,70512.82);
   CharmQuarkPair->SetBinContent(25,40000);
   CharmQuarkPair->SetBinContent(26,18784.81);
   CharmQuarkPair->SetBinContent(27,6556.391);
   CharmQuarkPair->SetBinContent(28,2286.55);
   CharmQuarkPair->SetBinContent(29,807.1749);
   CharmQuarkPair->SetBinContent(30,297.8723);
   CharmQuarkPair->SetBinContent(31,154.519);
   CharmQuarkPair->SetBinContent(32,101.9956);
   CharmQuarkPair->SetBinContent(33,31.30435);
   CharmQuarkPair->SetBinContent(34,17.21854);
   CharmQuarkPair->SetBinContent(35,3.421092);
   CharmQuarkPair->SetBinContent(36,4);
   CharmQuarkPair->SetEntries(110621);
   CharmQuarkPair->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   CharmQuarkPair->SetLineColor(ci);
   CharmQuarkPair->SetLineWidth(2);
   CharmQuarkPair->GetXaxis()->SetRange(2,35);
   CharmQuarkPair->GetXaxis()->SetLabelFont(42);
   CharmQuarkPair->GetXaxis()->SetLabelSize(0.035);
   CharmQuarkPair->GetXaxis()->SetTitleSize(0.035);
   CharmQuarkPair->GetXaxis()->SetTitleFont(42);
   CharmQuarkPair->GetYaxis()->SetLabelFont(42);
   CharmQuarkPair->GetYaxis()->SetLabelSize(0.035);
   CharmQuarkPair->GetYaxis()->SetTitleSize(0.035);
   CharmQuarkPair->GetYaxis()->SetTitleFont(42);
   CharmQuarkPair->GetZaxis()->SetLabelFont(42);
   CharmQuarkPair->GetZaxis()->SetLabelSize(0.035);
   CharmQuarkPair->GetZaxis()->SetTitleSize(0.035);
   CharmQuarkPair->GetZaxis()->SetTitleFont(42);
   CharmQuarkPair->Draw("");
   
   TPaveText *pt = new TPaveText(0.2896988,0.94,0.7103012,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("CharmQuarkPair");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
