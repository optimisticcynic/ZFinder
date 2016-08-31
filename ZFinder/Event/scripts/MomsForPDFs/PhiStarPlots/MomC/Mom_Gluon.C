{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:10 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,0.7278245,1.424743,5.173948);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis7[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *Gluon = new TH1D("Gluon","Gluon",35, xAxis7);
   Gluon->SetBinContent(1,25750);
   Gluon->SetBinContent(2,21750);
   Gluon->SetBinContent(3,24000);
   Gluon->SetBinContent(4,26750);
   Gluon->SetBinContent(5,28250);
   Gluon->SetBinContent(6,27750);
   Gluon->SetBinContent(7,26200);
   Gluon->SetBinContent(8,24800);
   Gluon->SetBinContent(9,20600);
   Gluon->SetBinContent(10,26000);
   Gluon->SetBinContent(11,26428.57);
   Gluon->SetBinContent(12,23600);
   Gluon->SetBinContent(13,25428.57);
   Gluon->SetBinContent(14,27625);
   Gluon->SetBinContent(15,23222.22);
   Gluon->SetBinContent(16,28300);
   Gluon->SetBinContent(17,25454.55);
   Gluon->SetBinContent(18,24500);
   Gluon->SetBinContent(19,24857.14);
   Gluon->SetBinContent(20,22235.29);
   Gluon->SetBinContent(21,23200);
   Gluon->SetBinContent(22,23541.67);
   Gluon->SetBinContent(23,22233.33);
   Gluon->SetBinContent(24,20230.77);
   Gluon->SetBinContent(25,20111.11);
   Gluon->SetBinContent(26,17759.49);
   Gluon->SetBinContent(27,13879.7);
   Gluon->SetBinContent(28,9625.731);
   Gluon->SetBinContent(29,5439.462);
   Gluon->SetBinContent(30,2940.426);
   Gluon->SetBinContent(31,1545.19);
   Gluon->SetBinContent(32,665.1885);
   Gluon->SetBinContent(33,365.2174);
   Gluon->SetBinContent(34,148.3444);
   Gluon->SetBinContent(35,29.74862);
   Gluon->SetBinContent(36,98);
   Gluon->SetEntries(15480);
   Gluon->SetStats(0);

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
