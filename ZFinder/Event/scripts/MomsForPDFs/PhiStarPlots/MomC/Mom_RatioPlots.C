{
//=========Macro generated from canvas: c4/c4
//=========  (Wed Aug 31 11:46:11 2016) by ROOT version5.32/00
   TCanvas *c4 = new TCanvas("c4", "c4",0,0,1000,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c4->SetHighLightColor(2);
   c4->Range(0,0,1,1);
   c4->SetFillColor(0);
   c4->SetBorderMode(0);
   c4->SetBorderSize(2);
   c4->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: c4_1
   TPad *c4_1 = new TPad("c4_1", "c4_1",0.01,0.81,0.99,0.99);
   c4_1->Draw();
   c4_1->cd();
   c4_1->Range(-2.822683,0.914117,1.424743,1.164679);
   c4_1->SetFillColor(0);
   c4_1->SetBorderMode(0);
   c4_1->SetBorderSize(2);
   c4_1->SetLogx();
   c4_1->SetFrameBorderMode(0);
   c4_1->SetFrameBorderMode(0);
   Double_t xAxis22[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *RatioUpQuarkPair = new TH1D("RatioUpQuarkPair","UpQuarkPair",35, xAxis22);
   RatioUpQuarkPair->SetBinContent(1,1.033765);
   RatioUpQuarkPair->SetBinContent(2,1.034406);
   RatioUpQuarkPair->SetBinContent(3,1.038034);
   RatioUpQuarkPair->SetBinContent(4,1.036748);
   RatioUpQuarkPair->SetBinContent(5,1.025468);
   RatioUpQuarkPair->SetBinContent(6,1.033637);
   RatioUpQuarkPair->SetBinContent(7,1.020263);
   RatioUpQuarkPair->SetBinContent(8,1.028423);
   RatioUpQuarkPair->SetBinContent(9,1.020839);
   RatioUpQuarkPair->SetBinContent(10,1.016722);
   RatioUpQuarkPair->SetBinContent(11,1.011984);
   RatioUpQuarkPair->SetBinContent(12,1.014747);
   RatioUpQuarkPair->SetBinContent(13,0.9849476);
   RatioUpQuarkPair->SetBinContent(14,0.9835155);
   RatioUpQuarkPair->SetBinContent(15,0.9823512);
   RatioUpQuarkPair->SetBinContent(16,0.9828706);
   RatioUpQuarkPair->SetBinContent(17,0.9649968);
   RatioUpQuarkPair->SetBinContent(18,0.9625293);
   RatioUpQuarkPair->SetBinContent(19,0.9504609);
   RatioUpQuarkPair->SetBinContent(20,0.9521512);
   RatioUpQuarkPair->SetBinContent(21,0.9486089);
   RatioUpQuarkPair->SetBinContent(22,0.9494194);
   RatioUpQuarkPair->SetBinContent(23,0.9482639);
   RatioUpQuarkPair->SetBinContent(24,0.9633229);
   RatioUpQuarkPair->SetBinContent(25,0.9730421);
   RatioUpQuarkPair->SetBinContent(26,0.994007);
   RatioUpQuarkPair->SetBinContent(27,1.024153);
   RatioUpQuarkPair->SetBinContent(28,1.084704);
   RatioUpQuarkPair->SetBinContent(29,1.068505);
   RatioUpQuarkPair->SetBinContent(30,1.115503);
   RatioUpQuarkPair->SetBinContent(31,1.041705);
   RatioUpQuarkPair->SetBinContent(32,1.041429);
   RatioUpQuarkPair->SetBinContent(33,1.130078);
   RatioUpQuarkPair->SetBinContent(34,1.064136);
   RatioUpQuarkPair->SetBinContent(35,1.016146);
   RatioUpQuarkPair->SetBinContent(36,1.058669);
   RatioUpQuarkPair->SetEntries(35.44188);
   RatioUpQuarkPair->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   RatioUpQuarkPair->SetLineColor(ci);
   RatioUpQuarkPair->GetXaxis()->SetTitle("#phi^{*}");
   RatioUpQuarkPair->GetXaxis()->SetRange(2,35);
   RatioUpQuarkPair->GetXaxis()->CenterTitle(true);
   RatioUpQuarkPair->GetXaxis()->SetLabelFont(42);
   RatioUpQuarkPair->GetXaxis()->SetLabelSize(0.035);
   RatioUpQuarkPair->GetXaxis()->SetTitleSize(0.035);
   RatioUpQuarkPair->GetXaxis()->SetTitleFont(42);
   RatioUpQuarkPair->GetYaxis()->SetLabelFont(42);
   RatioUpQuarkPair->GetYaxis()->SetLabelSize(0.035);
   RatioUpQuarkPair->GetYaxis()->SetTitleSize(0.035);
   RatioUpQuarkPair->GetYaxis()->SetTitleFont(42);
   RatioUpQuarkPair->GetZaxis()->SetLabelFont(42);
   RatioUpQuarkPair->GetZaxis()->SetLabelSize(0.035);
   RatioUpQuarkPair->GetZaxis()->SetTitleSize(0.035);
   RatioUpQuarkPair->GetZaxis()->SetTitleFont(42);
   RatioUpQuarkPair->Draw("");
   
   TPaveText *pt = new TPaveText(0.4613138,0.9332716,0.5386862,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText("UpQuarkPair");
   pt->Draw();
   c4_1->Modified();
   c4->cd();
  
// ------------>Primitives in pad: c4_2
   c4_2 = new TPad("c4_2", "c4_2",0.01,0.61,0.99,0.79);
   c4_2->Draw();
   c4_2->cd();
   c4_2->Range(-2.822683,0.8686551,1.424743,1.497808);
   c4_2->SetFillColor(0);
   c4_2->SetBorderMode(0);
   c4_2->SetBorderSize(2);
   c4_2->SetLogx();
   c4_2->SetFrameBorderMode(0);
   c4_2->SetFrameBorderMode(0);
   Double_t xAxis23[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *RatioDownQuarkPair = new TH1D("RatioDownQuarkPair","DownQuarkPair",35, xAxis23);
   RatioDownQuarkPair->SetBinContent(1,1.030633);
   RatioDownQuarkPair->SetBinContent(2,1.028946);
   RatioDownQuarkPair->SetBinContent(3,1.02856);
   RatioDownQuarkPair->SetBinContent(4,1.021168);
   RatioDownQuarkPair->SetBinContent(5,1.029264);
   RatioDownQuarkPair->SetBinContent(6,1.017087);
   RatioDownQuarkPair->SetBinContent(7,1.021787);
   RatioDownQuarkPair->SetBinContent(8,1.003414);
   RatioDownQuarkPair->SetBinContent(9,0.9999934);
   RatioDownQuarkPair->SetBinContent(10,0.9997615);
   RatioDownQuarkPair->SetBinContent(11,0.9896056);
   RatioDownQuarkPair->SetBinContent(12,0.9832187);
   RatioDownQuarkPair->SetBinContent(13,0.9895593);
   RatioDownQuarkPair->SetBinContent(14,0.9836577);
   RatioDownQuarkPair->SetBinContent(15,0.9741831);
   RatioDownQuarkPair->SetBinContent(16,0.9576428);
   RatioDownQuarkPair->SetBinContent(17,0.9601684);
   RatioDownQuarkPair->SetBinContent(18,0.9633325);
   RatioDownQuarkPair->SetBinContent(19,0.9723402);
   RatioDownQuarkPair->SetBinContent(20,0.9603963);
   RatioDownQuarkPair->SetBinContent(21,0.959528);
   RatioDownQuarkPair->SetBinContent(22,0.9543968);
   RatioDownQuarkPair->SetBinContent(23,0.9787852);
   RatioDownQuarkPair->SetBinContent(24,0.9865694);
   RatioDownQuarkPair->SetBinContent(25,1.0176);
   RatioDownQuarkPair->SetBinContent(26,1.061537);
   RatioDownQuarkPair->SetBinContent(27,1.119401);
   RatioDownQuarkPair->SetBinContent(28,1.148186);
   RatioDownQuarkPair->SetBinContent(29,1.206343);
   RatioDownQuarkPair->SetBinContent(30,1.256331);
   RatioDownQuarkPair->SetBinContent(31,1.355088);
   RatioDownQuarkPair->SetBinContent(32,1.314325);
   RatioDownQuarkPair->SetBinContent(33,1.350941);
   RatioDownQuarkPair->SetBinContent(34,1.342236);
   RatioDownQuarkPair->SetBinContent(35,1.410925);
   RatioDownQuarkPair->SetBinContent(36,1.345409);
   RatioDownQuarkPair->SetEntries(37.37691);
   RatioDownQuarkPair->SetStats(0);

   ci = TColor::GetColor("#000099");
   RatioDownQuarkPair->SetLineColor(ci);
   RatioDownQuarkPair->GetXaxis()->SetTitle("#phi^{*}");
   RatioDownQuarkPair->GetXaxis()->SetRange(2,35);
   RatioDownQuarkPair->GetXaxis()->CenterTitle(true);
   RatioDownQuarkPair->GetXaxis()->SetLabelFont(42);
   RatioDownQuarkPair->GetXaxis()->SetLabelSize(0.035);
   RatioDownQuarkPair->GetXaxis()->SetTitleSize(0.035);
   RatioDownQuarkPair->GetXaxis()->SetTitleFont(42);
   RatioDownQuarkPair->GetYaxis()->SetLabelFont(42);
   RatioDownQuarkPair->GetYaxis()->SetLabelSize(0.035);
   RatioDownQuarkPair->GetYaxis()->SetTitleSize(0.035);
   RatioDownQuarkPair->GetYaxis()->SetTitleFont(42);
   RatioDownQuarkPair->GetZaxis()->SetLabelFont(42);
   RatioDownQuarkPair->GetZaxis()->SetLabelSize(0.035);
   RatioDownQuarkPair->GetZaxis()->SetTitleSize(0.035);
   RatioDownQuarkPair->GetZaxis()->SetTitleFont(42);
   RatioDownQuarkPair->Draw("");
   
   pt = new TPaveText(0.4551668,0.94,0.5448332,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText("DownQuarkPair");
   pt->Draw();
   c4_2->Modified();
   c4->cd();
  
// ------------>Primitives in pad: c4_3
   c4_3 = new TPad("c4_3", "c4_3",0.01,0.41,0.99,0.59);
   c4_3->Draw();
   c4_3->cd();
   c4_3->Range(-2.822683,0.1664745,1.424743,1.220178);
   c4_3->SetFillColor(0);
   c4_3->SetBorderMode(0);
   c4_3->SetBorderSize(2);
   c4_3->SetLogx();
   c4_3->SetFrameBorderMode(0);
   c4_3->SetFrameBorderMode(0);
   Double_t xAxis24[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *RatioStrangeQuarkPair = new TH1D("RatioStrangeQuarkPair","StrangeQuarkPair",35, xAxis24);
   RatioStrangeQuarkPair->SetBinContent(1,0.9734031);
   RatioStrangeQuarkPair->SetBinContent(2,0.9499454);
   RatioStrangeQuarkPair->SetBinContent(3,0.9571475);
   RatioStrangeQuarkPair->SetBinContent(4,0.9633795);
   RatioStrangeQuarkPair->SetBinContent(5,0.9665797);
   RatioStrangeQuarkPair->SetBinContent(6,0.9817916);
   RatioStrangeQuarkPair->SetBinContent(7,0.991098);
   RatioStrangeQuarkPair->SetBinContent(8,1.005261);
   RatioStrangeQuarkPair->SetBinContent(9,0.99547);
   RatioStrangeQuarkPair->SetBinContent(10,1.004209);
   RatioStrangeQuarkPair->SetBinContent(11,1.008006);
   RatioStrangeQuarkPair->SetBinContent(12,1.019945);
   RatioStrangeQuarkPair->SetBinContent(13,1.040992);
   RatioStrangeQuarkPair->SetBinContent(14,1.036132);
   RatioStrangeQuarkPair->SetBinContent(15,1.051287);
   RatioStrangeQuarkPair->SetBinContent(16,1.047597);
   RatioStrangeQuarkPair->SetBinContent(17,1.074666);
   RatioStrangeQuarkPair->SetBinContent(18,1.058985);
   RatioStrangeQuarkPair->SetBinContent(19,1.042747);
   RatioStrangeQuarkPair->SetBinContent(20,1.042751);
   RatioStrangeQuarkPair->SetBinContent(21,1.048686);
   RatioStrangeQuarkPair->SetBinContent(22,1.054643);
   RatioStrangeQuarkPair->SetBinContent(23,1.02283);
   RatioStrangeQuarkPair->SetBinContent(24,0.9788265);
   RatioStrangeQuarkPair->SetBinContent(25,0.9226958);
   RatioStrangeQuarkPair->SetBinContent(26,0.8932751);
   RatioStrangeQuarkPair->SetBinContent(27,0.8167685);
   RatioStrangeQuarkPair->SetBinContent(28,0.7159087);
   RatioStrangeQuarkPair->SetBinContent(29,0.7029932);
   RatioStrangeQuarkPair->SetBinContent(30,0.5172451);
   RatioStrangeQuarkPair->SetBinContent(31,0.4842948);
   RatioStrangeQuarkPair->SetBinContent(32,0.549035);
   RatioStrangeQuarkPair->SetBinContent(33,0.3100745);
   RatioStrangeQuarkPair->SetBinContent(34,0.5148406);
   RatioStrangeQuarkPair->SetBinContent(35,0.4616146);
   RatioStrangeQuarkPair->SetBinContent(36,0.5167908);
   RatioStrangeQuarkPair->SetEntries(31.20512);
   RatioStrangeQuarkPair->SetStats(0);

   ci = TColor::GetColor("#000099");
   RatioStrangeQuarkPair->SetLineColor(ci);
   RatioStrangeQuarkPair->GetXaxis()->SetTitle("#phi^{*}");
   RatioStrangeQuarkPair->GetXaxis()->SetRange(2,35);
   RatioStrangeQuarkPair->GetXaxis()->CenterTitle(true);
   RatioStrangeQuarkPair->GetXaxis()->SetLabelFont(42);
   RatioStrangeQuarkPair->GetXaxis()->SetLabelSize(0.035);
   RatioStrangeQuarkPair->GetXaxis()->SetTitleSize(0.035);
   RatioStrangeQuarkPair->GetXaxis()->SetTitleFont(42);
   RatioStrangeQuarkPair->GetYaxis()->SetLabelFont(42);
   RatioStrangeQuarkPair->GetYaxis()->SetLabelSize(0.035);
   RatioStrangeQuarkPair->GetYaxis()->SetTitleSize(0.035);
   RatioStrangeQuarkPair->GetYaxis()->SetTitleFont(42);
   RatioStrangeQuarkPair->GetZaxis()->SetLabelFont(42);
   RatioStrangeQuarkPair->GetZaxis()->SetLabelSize(0.035);
   RatioStrangeQuarkPair->GetZaxis()->SetTitleSize(0.035);
   RatioStrangeQuarkPair->GetZaxis()->SetTitleFont(42);
   RatioStrangeQuarkPair->Draw("");
   
   pt = new TPaveText(0.4505565,0.9332716,0.5494435,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText("StrangeQuarkPair");
   pt->Draw();
   c4_3->Modified();
   c4->cd();
  
// ------------>Primitives in pad: c4_4
   c4_4 = new TPad("c4_4", "c4_4",0.01,0.21,0.99,0.39);
   c4_4->Draw();
   c4_4->cd();
   c4_4->Range(-2.822683,0.1384236,1.424743,1.343439);
   c4_4->SetFillColor(0);
   c4_4->SetBorderMode(0);
   c4_4->SetBorderSize(2);
   c4_4->SetLogx();
   c4_4->SetFrameBorderMode(0);
   c4_4->SetFrameBorderMode(0);
   Double_t xAxis25[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *RatioCharmQuarkPair = new TH1D("RatioCharmQuarkPair","CharmQuarkPair",35, xAxis25);
   RatioCharmQuarkPair->SetBinContent(1,0.8699343);
   RatioCharmQuarkPair->SetBinContent(2,0.9027538);
   RatioCharmQuarkPair->SetBinContent(3,0.8808859);
   RatioCharmQuarkPair->SetBinContent(4,0.9003454);
   RatioCharmQuarkPair->SetBinContent(5,0.9126805);
   RatioCharmQuarkPair->SetBinContent(6,0.9017037);
   RatioCharmQuarkPair->SetBinContent(7,0.91455);
   RatioCharmQuarkPair->SetBinContent(8,0.9247819);
   RatioCharmQuarkPair->SetBinContent(9,0.9571937);
   RatioCharmQuarkPair->SetBinContent(10,0.9672236);
   RatioCharmQuarkPair->SetBinContent(11,1.011292);
   RatioCharmQuarkPair->SetBinContent(12,0.9959776);
   RatioCharmQuarkPair->SetBinContent(13,1.052028);
   RatioCharmQuarkPair->SetBinContent(14,1.078657);
   RatioCharmQuarkPair->SetBinContent(15,1.082238);
   RatioCharmQuarkPair->SetBinContent(16,1.126148);
   RatioCharmQuarkPair->SetBinContent(17,1.127511);
   RatioCharmQuarkPair->SetBinContent(18,1.149382);
   RatioCharmQuarkPair->SetBinContent(19,1.134272);
   RatioCharmQuarkPair->SetBinContent(20,1.177032);
   RatioCharmQuarkPair->SetBinContent(21,1.157328);
   RatioCharmQuarkPair->SetBinContent(22,1.149903);
   RatioCharmQuarkPair->SetBinContent(23,1.096472);
   RatioCharmQuarkPair->SetBinContent(24,1.081182);
   RatioCharmQuarkPair->SetBinContent(25,1.025131);
   RatioCharmQuarkPair->SetBinContent(26,0.8908917);
   RatioCharmQuarkPair->SetBinContent(27,0.701842);
   RatioCharmQuarkPair->SetBinContent(28,0.5796812);
   RatioCharmQuarkPair->SetBinContent(29,0.4828451);
   RatioCharmQuarkPair->SetBinContent(30,0.3604143);
   RatioCharmQuarkPair->SetBinContent(31,0.3777771);
   RatioCharmQuarkPair->SetBinContent(32,0.4605294);
   RatioCharmQuarkPair->SetBinContent(33,0.3026445);
   RatioCharmQuarkPair->SetBinContent(34,0.3134306);
   RatioCharmQuarkPair->SetBinContent(35,0.3038455);
   RatioCharmQuarkPair->SetBinContent(36,0.1216983);
   RatioCharmQuarkPair->SetEntries(30.35051);
   RatioCharmQuarkPair->SetStats(0);

   ci = TColor::GetColor("#000099");
   RatioCharmQuarkPair->SetLineColor(ci);
   RatioCharmQuarkPair->GetXaxis()->SetTitle("#phi^{*}");
   RatioCharmQuarkPair->GetXaxis()->SetRange(2,35);
   RatioCharmQuarkPair->GetXaxis()->CenterTitle(true);
   RatioCharmQuarkPair->GetXaxis()->SetLabelFont(42);
   RatioCharmQuarkPair->GetXaxis()->SetLabelSize(0.035);
   RatioCharmQuarkPair->GetXaxis()->SetTitleSize(0.035);
   RatioCharmQuarkPair->GetXaxis()->SetTitleFont(42);
   RatioCharmQuarkPair->GetYaxis()->SetLabelFont(42);
   RatioCharmQuarkPair->GetYaxis()->SetLabelSize(0.035);
   RatioCharmQuarkPair->GetYaxis()->SetTitleSize(0.035);
   RatioCharmQuarkPair->GetYaxis()->SetTitleFont(42);
   RatioCharmQuarkPair->GetZaxis()->SetLabelFont(42);
   RatioCharmQuarkPair->GetZaxis()->SetLabelSize(0.035);
   RatioCharmQuarkPair->GetZaxis()->SetTitleSize(0.035);
   RatioCharmQuarkPair->GetZaxis()->SetTitleFont(42);
   RatioCharmQuarkPair->Draw("");
   
   pt = new TPaveText(0.4531178,0.94,0.5468822,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText("CharmQuarkPair");
   pt->Draw();
   c4_4->Modified();
   c4->cd();
  
// ------------>Primitives in pad: c4_5
   c4_5 = new TPad("c4_5", "c4_5",0.01,0.01,0.99,0.19);
   c4_5->Draw();
   c4_5->cd();
   c4_5->Range(-2.822683,-0.1034695,1.424743,1.785342);
   c4_5->SetFillColor(0);
   c4_5->SetBorderMode(0);
   c4_5->SetBorderSize(2);
   c4_5->SetLogx();
   c4_5->SetFrameBorderMode(0);
   c4_5->SetFrameBorderMode(0);
   Double_t xAxis26[36] = {0, 0.004, 0.008, 0.012, 0.016, 0.02, 0.024, 0.029, 0.034, 0.039, 0.045, 0.052, 0.057, 0.064, 0.072, 0.081, 0.091, 0.102, 0.114, 0.128, 0.145, 0.165, 0.189, 0.219, 0.258, 0.312, 0.391, 0.524, 0.695, 0.918, 1.153, 1.496, 1.947, 2.522, 3.277, 10}; 
   
   TH1D *RatioBottomQuarkPair = new TH1D("RatioBottomQuarkPair","BottomQuarkPair",35, xAxis26);
   RatioBottomQuarkPair->SetBinContent(1,0.670819);
   RatioBottomQuarkPair->SetBinContent(2,0.7145834);
   RatioBottomQuarkPair->SetBinContent(3,0.691534);
   RatioBottomQuarkPair->SetBinContent(4,0.7174295);
   RatioBottomQuarkPair->SetBinContent(5,0.7209494);
   RatioBottomQuarkPair->SetBinContent(6,0.7139451);
   RatioBottomQuarkPair->SetBinContent(7,0.7505401);
   RatioBottomQuarkPair->SetBinContent(8,0.7699059);
   RatioBottomQuarkPair->SetBinContent(9,0.86887);
   RatioBottomQuarkPair->SetBinContent(10,0.8595414);
   RatioBottomQuarkPair->SetBinContent(11,0.9136512);
   RatioBottomQuarkPair->SetBinContent(12,0.9306299);
   RatioBottomQuarkPair->SetBinContent(13,0.9969869);
   RatioBottomQuarkPair->SetBinContent(14,1.041895);
   RatioBottomQuarkPair->SetBinContent(15,1.083485);
   RatioBottomQuarkPair->SetBinContent(16,1.178494);
   RatioBottomQuarkPair->SetBinContent(17,1.237372);
   RatioBottomQuarkPair->SetBinContent(18,1.254158);
   RatioBottomQuarkPair->SetBinContent(19,1.40066);
   RatioBottomQuarkPair->SetBinContent(20,1.418759);
   RatioBottomQuarkPair->SetBinContent(21,1.485196);
   RatioBottomQuarkPair->SetBinContent(22,1.520774);
   RatioBottomQuarkPair->SetBinContent(23,1.524506);
   RatioBottomQuarkPair->SetBinContent(24,1.491097);
   RatioBottomQuarkPair->SetBinContent(25,1.409067);
   RatioBottomQuarkPair->SetBinContent(26,1.106473);
   RatioBottomQuarkPair->SetBinContent(27,0.8701991);
   RatioBottomQuarkPair->SetBinContent(28,0.558493);
   RatioBottomQuarkPair->SetBinContent(29,0.3825094);
   RatioBottomQuarkPair->SetBinContent(30,0.372576);
   RatioBottomQuarkPair->SetBinContent(31,0.2730639);
   RatioBottomQuarkPair->SetBinContent(32,0.2556894);
   RatioBottomQuarkPair->SetBinContent(33,0.2147057);
   RatioBottomQuarkPair->SetBinContent(34,0.1539399);
   RatioBottomQuarkPair->SetBinContent(35,0.2249298);
   RatioBottomQuarkPair->SetBinContent(36,0.5827726);
   RatioBottomQuarkPair->SetEntries(30.77743);
   RatioBottomQuarkPair->SetStats(0);

   ci = TColor::GetColor("#000099");
   RatioBottomQuarkPair->SetLineColor(ci);
   RatioBottomQuarkPair->GetXaxis()->SetTitle("#phi^{*}");
   RatioBottomQuarkPair->GetXaxis()->SetRange(2,35);
   RatioBottomQuarkPair->GetXaxis()->CenterTitle(true);
   RatioBottomQuarkPair->GetXaxis()->SetLabelFont(42);
   RatioBottomQuarkPair->GetXaxis()->SetLabelSize(0.035);
   RatioBottomQuarkPair->GetXaxis()->SetTitleSize(0.035);
   RatioBottomQuarkPair->GetXaxis()->SetTitleFont(42);
   RatioBottomQuarkPair->GetYaxis()->SetLabelFont(42);
   RatioBottomQuarkPair->GetYaxis()->SetLabelSize(0.035);
   RatioBottomQuarkPair->GetYaxis()->SetTitleSize(0.035);
   RatioBottomQuarkPair->GetYaxis()->SetTitleFont(42);
   RatioBottomQuarkPair->GetZaxis()->SetLabelFont(42);
   RatioBottomQuarkPair->GetZaxis()->SetLabelSize(0.035);
   RatioBottomQuarkPair->GetZaxis()->SetTitleSize(0.035);
   RatioBottomQuarkPair->GetZaxis()->SetTitleFont(42);
   RatioBottomQuarkPair->Draw("");
   
   pt = new TPaveText(0.451581,0.94,0.548419,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText("BottomQuarkPair");
   pt->Draw();
   c4_5->Modified();
   c4->cd();
   c4->Modified();
   c4->cd();
   c4->SetSelected(c4);
}
