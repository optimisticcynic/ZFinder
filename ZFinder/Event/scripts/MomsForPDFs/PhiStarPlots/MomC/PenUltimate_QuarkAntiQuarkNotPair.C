{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:18 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,-0.5009081,1.424743,9.292299);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis38[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *QuarkAntiQuarkNotPair = new TH1D("QuarkAntiQuarkNotPair","QuarkAntiQuarkNotPair",35, xAxis38);
   QuarkAntiQuarkNotPair->SetBinContent(1,1.095625e+08);
   QuarkAntiQuarkNotPair->SetBinContent(2,1.03375e+08);
   QuarkAntiQuarkNotPair->SetBinContent(3,1.085e+08);
   QuarkAntiQuarkNotPair->SetBinContent(4,1.03875e+08);
   QuarkAntiQuarkNotPair->SetBinContent(5,1.021875e+08);
   QuarkAntiQuarkNotPair->SetBinContent(6,1.025625e+08);
   QuarkAntiQuarkNotPair->SetBinContent(7,8.2e+07);
   QuarkAntiQuarkNotPair->SetBinContent(8,7.756e+07);
   QuarkAntiQuarkNotPair->SetBinContent(9,7.776e+07);
   QuarkAntiQuarkNotPair->SetBinContent(10,6.038889e+07);
   QuarkAntiQuarkNotPair->SetBinContent(11,4.702041e+07);
   QuarkAntiQuarkNotPair->SetBinContent(12,6.42e+07);
   QuarkAntiQuarkNotPair->SetBinContent(13,4.142857e+07);
   QuarkAntiQuarkNotPair->SetBinContent(14,3.48125e+07);
   QuarkAntiQuarkNotPair->SetBinContent(15,2.781481e+07);
   QuarkAntiQuarkNotPair->SetBinContent(16,2.262e+07);
   QuarkAntiQuarkNotPair->SetBinContent(17,1.82314e+07);
   QuarkAntiQuarkNotPair->SetBinContent(18,1.428472e+07);
   QuarkAntiQuarkNotPair->SetBinContent(19,1.127551e+07);
   QuarkAntiQuarkNotPair->SetBinContent(20,8183391);
   QuarkAntiQuarkNotPair->SetBinContent(21,5837500);
   QuarkAntiQuarkNotPair->SetBinContent(22,4166667);
   QuarkAntiQuarkNotPair->SetBinContent(23,2710000);
   QuarkAntiQuarkNotPair->SetBinContent(24,1669297);
   QuarkAntiQuarkNotPair->SetBinContent(25,862825.8);
   QuarkAntiQuarkNotPair->SetBinContent(26,434545.7);
   QuarkAntiQuarkNotPair->SetBinContent(27,154389.7);
   QuarkAntiQuarkNotPair->SetBinContent(28,66242.6);
   QuarkAntiQuarkNotPair->SetBinContent(29,26523.76);
   QuarkAntiQuarkNotPair->SetBinContent(30,13490.27);
   QuarkAntiQuarkNotPair->SetBinContent(31,5023.417);
   QuarkAntiQuarkNotPair->SetBinContent(32,2069.803);
   QuarkAntiQuarkNotPair->SetBinContent(33,725.8979);
   QuarkAntiQuarkNotPair->SetBinContent(34,243.849);
   QuarkAntiQuarkNotPair->SetBinContent(35,6.017868);
   QuarkAntiQuarkNotPair->SetBinContent(36,132);
   QuarkAntiQuarkNotPair->SetEntries(63246);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   QuarkAntiQuarkNotPair->SetLineColor(ci);
   QuarkAntiQuarkNotPair->SetLineWidth(2);
   QuarkAntiQuarkNotPair->GetXaxis()->SetRange(2,35);
   QuarkAntiQuarkNotPair->GetXaxis()->SetLabelFont(42);
   QuarkAntiQuarkNotPair->GetXaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkNotPair->GetXaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkNotPair->GetXaxis()->SetTitleFont(42);
   QuarkAntiQuarkNotPair->GetYaxis()->SetLabelFont(42);
   QuarkAntiQuarkNotPair->GetYaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkNotPair->GetYaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkNotPair->GetYaxis()->SetTitleFont(42);
   QuarkAntiQuarkNotPair->GetZaxis()->SetLabelFont(42);
   QuarkAntiQuarkNotPair->GetZaxis()->SetLabelSize(0.035);
   QuarkAntiQuarkNotPair->GetZaxis()->SetTitleSize(0.035);
   QuarkAntiQuarkNotPair->GetZaxis()->SetTitleFont(42);
   QuarkAntiQuarkNotPair->Draw("");
   
   TPaveText *pt = new TPaveText(0.2063655,0.94,0.7936345,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("QuarkAntiQuarkNotPair");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
