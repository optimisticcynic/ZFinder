{
//=========Macro generated from canvas: canvas/canvas
//=========  (Wed Aug 31 11:46:10 2016) by ROOT version5.32/00
   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   canvas->SetHighLightColor(2);
   canvas->Range(-2.822683,-0.9891823,1.424743,6.647609);
   canvas->SetFillColor(0);
   canvas->SetBorderMode(0);
   canvas->SetBorderSize(2);
   canvas->SetLogx();
   canvas->SetLogy();
   canvas->SetFrameBorderMode(0);
   canvas->SetFrameBorderMode(0);
   Double_t xAxis5[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *BottomQuarkPair = new TH1D("BottomQuarkPair","BottomQuarkPair",35, xAxis5);
   BottomQuarkPair->SetBinContent(1,386500);
   BottomQuarkPair->SetBinContent(2,404000);
   BottomQuarkPair->SetBinContent(3,386750);
   BottomQuarkPair->SetBinContent(4,391250);
   BottomQuarkPair->SetBinContent(5,386000);
   BottomQuarkPair->SetBinContent(6,367000);
   BottomQuarkPair->SetBinContent(7,368400);
   BottomQuarkPair->SetBinContent(8,356200);
   BottomQuarkPair->SetBinContent(9,377200);
   BottomQuarkPair->SetBinContent(10,348166.7);
   BottomQuarkPair->SetBinContent(11,335714.3);
   BottomQuarkPair->SetBinContent(12,311800);
   BottomQuarkPair->SetBinContent(13,305714.3);
   BottomQuarkPair->SetBinContent(14,287625);
   BottomQuarkPair->SetBinContent(15,262222.2);
   BottomQuarkPair->SetBinContent(16,248800);
   BottomQuarkPair->SetBinContent(17,226272.7);
   BottomQuarkPair->SetBinContent(18,195250);
   BottomQuarkPair->SetBinContent(19,183428.6);
   BottomQuarkPair->SetBinContent(20,152882.4);
   BottomQuarkPair->SetBinContent(21,125900);
   BottomQuarkPair->SetBinContent(22,98000);
   BottomQuarkPair->SetBinContent(23,71033.33);
   BottomQuarkPair->SetBinContent(24,45692.31);
   BottomQuarkPair->SetBinContent(25,25833.33);
   BottomQuarkPair->SetBinContent(26,10962.03);
   BottomQuarkPair->SetBinContent(27,3819.549);
   BottomQuarkPair->SetBinContent(28,1035.088);
   BottomQuarkPair->SetBinContent(29,300.4484);
   BottomQuarkPair->SetBinContent(30,144.6809);
   BottomQuarkPair->SetBinContent(31,52.47813);
   BottomQuarkPair->SetBinContent(32,26.60754);
   BottomQuarkPair->SetBinContent(33,10.43478);
   BottomQuarkPair->SetBinContent(34,3.97351);
   BottomQuarkPair->SetBinContent(35,1.189945);
   BottomQuarkPair->SetBinContent(36,9);
   BottomQuarkPair->SetEntries(52002);
   BottomQuarkPair->SetStats(0);

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
