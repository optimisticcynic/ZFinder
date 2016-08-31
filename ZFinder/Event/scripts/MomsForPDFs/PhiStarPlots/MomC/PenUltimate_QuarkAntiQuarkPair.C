{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:18 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,1.028939,1.424743,7.681837);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis36[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *QuarkAntiQuarkPair = new TH1D("QuarkAntiQuarkPair","QuarkAntiQuarkPair",35, xAxis36);
   QuarkAntiQuarkPair->SetBinContent(1,5641500);
   QuarkAntiQuarkPair->SetBinContent(2,5482750);
   QuarkAntiQuarkPair->SetBinContent(3,5380500);
   QuarkAntiQuarkPair->SetBinContent(4,5142500);
   QuarkAntiQuarkPair->SetBinContent(5,4992500);
   QuarkAntiQuarkPair->SetBinContent(6,4789500);
   QuarkAntiQuarkPair->SetBinContent(7,4468400);
   QuarkAntiQuarkPair->SetBinContent(8,4088200);
   QuarkAntiQuarkPair->SetBinContent(9,3733200);
   QuarkAntiQuarkPair->SetBinContent(10,3408167);
   QuarkAntiQuarkPair->SetBinContent(11,2941571);
   QuarkAntiQuarkPair->SetBinContent(12,2544600);
   QuarkAntiQuarkPair->SetBinContent(13,2271429);
   QuarkAntiQuarkPair->SetBinContent(14,1993125);
   QuarkAntiQuarkPair->SetBinContent(15,1692000);
   QuarkAntiQuarkPair->SetBinContent(16,1410200);
   QuarkAntiQuarkPair->SetBinContent(17,1192818);
   QuarkAntiQuarkPair->SetBinContent(18,1004833);
   QuarkAntiQuarkPair->SetBinContent(19,826071.4);
   QuarkAntiQuarkPair->SetBinContent(20,672411.8);
   QuarkAntiQuarkPair->SetBinContent(21,534950);
   QuarkAntiQuarkPair->SetBinContent(22,415708.3);
   QuarkAntiQuarkPair->SetBinContent(23,318733.3);
   QuarkAntiQuarkPair->SetBinContent(24,229153.8);
   QuarkAntiQuarkPair->SetBinContent(25,154722.2);
   QuarkAntiQuarkPair->SetBinContent(26,96974.68);
   QuarkAntiQuarkPair->SetBinContent(27,51954.89);
   QuarkAntiQuarkPair->SetBinContent(28,24730.99);
   QuarkAntiQuarkPair->SetBinContent(29,11820.63);
   QuarkAntiQuarkPair->SetBinContent(30,6395.745);
   QuarkAntiQuarkPair->SetBinContent(31,3309.038);
   QuarkAntiQuarkPair->SetBinContent(32,1791.574);
   QuarkAntiQuarkPair->SetBinContent(33,857.3913);
   QuarkAntiQuarkPair->SetBinContent(34,449.0066);
   QuarkAntiQuarkPair->SetBinContent(35,98.91418);
   QuarkAntiQuarkPair->SetBinContent(36,247);
   QuarkAntiQuarkPair->SetEntries(424470);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   QuarkAntiQuarkPair->SetLineColor(ci);
   QuarkAntiQuarkPair->SetLineWidth(2);
   QuarkAntiQuarkPair->GetXaxis()->SetRange(2,35);
   QuarkAntiQuarkPair->GetXaxis()->SetLabelFont(42);
   QuarkAntiQuarkPair->GetXaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkPair->GetXaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkPair->GetXaxis()->SetTitleFont(42);
   QuarkAntiQuarkPair->GetYaxis()->SetLabelFont(42);
   QuarkAntiQuarkPair->GetYaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkPair->GetYaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkPair->GetYaxis()->SetTitleFont(42);
   QuarkAntiQuarkPair->GetZaxis()->SetLabelFont(42);
   QuarkAntiQuarkPair->GetZaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkPair->GetZaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkPair->GetZaxis()->SetTitleFont(42);
   QuarkAntiQuarkPair->Draw("");
   
   TPaveText *pt = new TPaveText(0.2480321,0.94,0.7519679,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("QuarkAntiQuarkPair");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
