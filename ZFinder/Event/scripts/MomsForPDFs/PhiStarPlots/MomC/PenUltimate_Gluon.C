{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:18 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,1.112416,1.424743,7.347432);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis33[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *Gluon = new TH1D("Gluon","Gluon",35, xAxis33);
   Gluon->SetBinContent(1,2808250);
   Gluon->SetBinContent(2,2795000);
   Gluon->SetBinContent(3,2783750);
   Gluon->SetBinContent(4,2731000);
   Gluon->SetBinContent(5,2743750);
   Gluon->SetBinContent(6,2631000);
   Gluon->SetBinContent(7,2557200);
   Gluon->SetBinContent(8,2458400);
   Gluon->SetBinContent(9,2375000);
   Gluon->SetBinContent(10,2236000);
   Gluon->SetBinContent(11,2136000);
   Gluon->SetBinContent(12,1976200);
   Gluon->SetBinContent(13,1882286);
   Gluon->SetBinContent(14,1725375);
   Gluon->SetBinContent(15,1566222);
   Gluon->SetBinContent(16,1426800);
   Gluon->SetBinContent(17,1267364);
   Gluon->SetBinContent(18,1128667);
   Gluon->SetBinContent(19,986857.1);
   Gluon->SetBinContent(20,845294.1);
   Gluon->SetBinContent(21,711900);
   Gluon->SetBinContent(22,579833.3);
   Gluon->SetBinContent(23,465000);
   Gluon->SetBinContent(24,353000);
   Gluon->SetBinContent(25,253555.6);
   Gluon->SetBinContent(26,171278.5);
   Gluon->SetBinContent(27,93616.54);
   Gluon->SetBinContent(28,47356.73);
   Gluon->SetBinContent(29,22282.51);
   Gluon->SetBinContent(30,10604.26);
   Gluon->SetBinContent(31,4877.551);
   Gluon->SetBinContent(32,2294.9);
   Gluon->SetBinContent(33,1055.652);
   Gluon->SetBinContent(34,516.5563);
   Gluon->SetBinContent(35,108.88);
   Gluon->SetBinContent(36,297);
   Gluon->SetEntries(368060);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   Gluon->SetLineColor(ci);
   Gluon->SetLineWidth(2);
   Gluon->GetXaxis()->SetRange(2,35);
   Gluon->GetXaxis()->SetLabelFont(42);
   Gluon->GetXaxis()->SetLabelSize(0.035);
   Gluon->GetXaxis()->SetTitleSize(0.035);
   Gluon->GetXaxis()->SetTitleFont(42);
   Gluon->GetYaxis()->SetLabelFont(42);
   Gluon->GetYaxis()->SetLabelSize(0.035);
   Gluon->GetYaxis()->SetTitleSize(0.035);
   Gluon->GetYaxis()->SetTitleFont(42);
   Gluon->GetZaxis()->SetLabelFont(42);
   Gluon->GetZaxis()->SetLabelSize(0.035);
   Gluon->GetZaxis()->SetTitleSize(0.035);
   Gluon->GetZaxis()->SetTitleFont(42);
   Gluon->Draw("");
   
   TPaveText *pt = new TPaveText(0.4187149,0.94,0.5812851,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("Gluon");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
