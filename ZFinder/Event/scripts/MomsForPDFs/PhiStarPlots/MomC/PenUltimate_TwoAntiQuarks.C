{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:18 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,-0.07253187,1.424743,5.898981);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis35[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *TwoAntiQuarks = new TH1D("TwoAntiQuarks","TwoAntiQuarks",35, xAxis35);
   TwoAntiQuarks->SetBinContent(1,103750);
   TwoAntiQuarks->SetBinContent(2,99500);
   TwoAntiQuarks->SetBinContent(3,97250);
   TwoAntiQuarks->SetBinContent(4,100250);
   TwoAntiQuarks->SetBinContent(5,105750);
   TwoAntiQuarks->SetBinContent(6,104500);
   TwoAntiQuarks->SetBinContent(7,93000);
   TwoAntiQuarks->SetBinContent(8,87200);
   TwoAntiQuarks->SetBinContent(9,86600);
   TwoAntiQuarks->SetBinContent(10,82500);
   TwoAntiQuarks->SetBinContent(11,76285.71);
   TwoAntiQuarks->SetBinContent(12,70400);
   TwoAntiQuarks->SetBinContent(13,70142.86);
   TwoAntiQuarks->SetBinContent(14,68250);
   TwoAntiQuarks->SetBinContent(15,56111.11);
   TwoAntiQuarks->SetBinContent(16,50700);
   TwoAntiQuarks->SetBinContent(17,45818.18);
   TwoAntiQuarks->SetBinContent(18,39333.33);
   TwoAntiQuarks->SetBinContent(19,36357.14);
   TwoAntiQuarks->SetBinContent(20,29941.18);
   TwoAntiQuarks->SetBinContent(21,25450);
   TwoAntiQuarks->SetBinContent(22,20791.67);
   TwoAntiQuarks->SetBinContent(23,17166.67);
   TwoAntiQuarks->SetBinContent(24,13512.82);
   TwoAntiQuarks->SetBinContent(25,9814.815);
   TwoAntiQuarks->SetBinContent(26,6810.127);
   TwoAntiQuarks->SetBinContent(27,4075.188);
   TwoAntiQuarks->SetBinContent(28,1918.129);
   TwoAntiQuarks->SetBinContent(29,1098.655);
   TwoAntiQuarks->SetBinContent(30,570.2128);
   TwoAntiQuarks->SetBinContent(31,239.0671);
   TwoAntiQuarks->SetBinContent(32,128.6031);
   TwoAntiQuarks->SetBinContent(33,64.34783);
   TwoAntiQuarks->SetBinContent(34,25.16556);
   TwoAntiQuarks->SetBinContent(35,6.69344);
   TwoAntiQuarks->SetBinContent(36,14);
   TwoAntiQuarks->SetEntries(13859);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   TwoAntiQuarks->SetLineColor(ci);
   TwoAntiQuarks->SetLineWidth(2);
   TwoAntiQuarks->GetXaxis()->SetRange(2,35);
   TwoAntiQuarks->GetXaxis()->SetLabelFont(42);
   TwoAntiQuarks->GetXaxis()->SetLabelSize(0.035);
   TwoAntiQuarks->GetXaxis()->SetTitleSize(0.035);
   TwoAntiQuarks->GetXaxis()->SetTitleFont(42);
   TwoAntiQuarks->GetYaxis()->SetLabelFont(42);
   TwoAntiQuarks->GetYaxis()->SetLabelSize(0.035);
   TwoAntiQuarks->GetYaxis()->SetTitleSize(0.035);
   TwoAntiQuarks->GetYaxis()->SetTitleFont(42);
   TwoAntiQuarks->GetZaxis()->SetLabelFont(42);
   TwoAntiQuarks->GetZaxis()->SetLabelSize(0.035);
   TwoAntiQuarks->GetZaxis()->SetTitleSize(0.035);
   TwoAntiQuarks->GetZaxis()->SetTitleFont(42);
   TwoAntiQuarks->Draw("");
   
   TPaveText *pt = new TPaveText(0.3072691,0.94,0.6927309,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("TwoAntiQuarks");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
