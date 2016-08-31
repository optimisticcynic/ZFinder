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
   Double_t xAxis30[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *CharmQuarkPair = new TH1D("CharmQuarkPair","CharmQuarkPair",35, xAxis30);
   CharmQuarkPair->SetEntries(35);

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
