{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:18 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,-2.748352,1.424743,1.724871);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis31[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *BottomQuarkPair = new TH1D("BottomQuarkPair","BottomQuarkPair",35, xAxis31);
   BottomQuarkPair->SetEntries(35);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   BottomQuarkPair->SetLineColor(ci);
   BottomQuarkPair->SetLineWidth(2);
   BottomQuarkPair->GetXaxis()->SetRange(2,35);
   BottomQuarkPair->GetXaxis()->SetLabelFont(42);
   BottomQuarkPair->GetXaxis()->SetLabelSize(0.035);
   BottomQuarkPair->GetXaxis()->SetTitleSize(0.035);
   BottomQuarkPair->GetXaxis()->SetTitleFont(42);
   BottomQuarkPair->GetYaxis()->SetLabelFont(42);
   BottomQuarkPair->GetYaxis()->SetLabelSize(0.035);
   BottomQuarkPair->GetYaxis()->SetTitleSize(0.035);
   BottomQuarkPair->GetYaxis()->SetTitleFont(42);
   BottomQuarkPair->GetZaxis()->SetLabelFont(42);
   BottomQuarkPair->GetZaxis()->SetLabelSize(0.035);
   BottomQuarkPair->GetZaxis()->SetTitleSize(0.035);
   BottomQuarkPair->GetZaxis()->SetTitleFont(42);
   BottomQuarkPair->Draw("");
   
   TPaveText *pt = new TPaveText(0.2816667,0.94,0.7183333,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("BottomQuarkPair");
   pt->Draw();
   canvas->Modified();
   canvas->cd();
   canvas->SetSelected(canvas);
}
