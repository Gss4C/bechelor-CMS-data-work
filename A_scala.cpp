#include <iostream>
#include <cmath>
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1.h"
#include <TLegend.h>
#include <TLatex.h>

using namespace std;

int main (int argc, char**argv){

    TCanvas c;

    string nomehisto = argv[1];
    TFile *_file0=TFile::Open("outputfilename.root");
    TTree *t=NULL;

    TH1F *h_700=(TH1F*)(_file0->Get(("Tprime_tHq_700_"+nomehisto).c_str()));
    TH1F *h_1000=(TH1F*)(_file0->Get(("Tprime_tHq_1000_"+nomehisto).c_str()));
    TH1F *h_1200=(TH1F*)(_file0->Get(("Tprime_tHq_1200_"+nomehisto).c_str()));

    //TH1F *h_sm=(TH1F*)(_file0->Get(("SM_tHq_aa_"+nomehisto).c_str()));
    TH1F *h_sm_all=(TH1F*)(_file0->Get(("SM_tHq_all_"+nomehisto).c_str()));
    TH1F *h_bsm=(TH1F*)(_file0->Get(("BSM_tHq_all_"+nomehisto).c_str()));

    TH1F *h_tg=(TH1F*)(_file0->Get(("tGamma_"+nomehisto).c_str()));
    TH1F *h_ttg=(TH1F*)(_file0->Get(("ttGamma_"+nomehisto).c_str()));
    TH1F *h_ttgg=(TH1F*)(_file0->Get(("ttGG_"+nomehisto).c_str()));
    

    TH1F *cf_700=(TH1F*)(_file0->Get("Tprime_tHq_700_cutflow"));
    TH1F *cf_1000=(TH1F*)(_file0->Get("Tprime_tHq_1000_cutflow"));
    TH1F *cf_1200=(TH1F*)(_file0->Get("Tprime_tHq_1200_cutflow"));
    
    //TH1F *cf_sm=(TH1F*)(_file0->Get("SM_tHq_aa_cutflow"));
    TH1F *cf_sm_all=(TH1F*)(_file0->Get("SM_tHq_all_cutflow"));
    TH1F *cf_bsm=(TH1F*)(_file0->Get("BSM_tHq_all_cutflow"));

    TH1F *cf_tg=(TH1F*)(_file0->Get("tGamma_cutflow"));
    TH1F *cf_ttg=(TH1F*)(_file0->Get("ttGamma_cutflow"));
    TH1F *cf_ttgg=(TH1F*)(_file0->Get("ttGG_cutflow"));
    
    double n_700,n_1000,n_1200,n_sm,n_tg,n_ttg,n_ttgg,n_bsm,n_sm_all,s_700,s_1000,s_1200,s_sm,s_tg,s_ttg,s_ttgg,s_bsm,s_sm_all;
    double L=137000;
    
    //s_700=0.078;
    //s_1000=0.0136;
    //s_1200=0.0051;
    s_700=1.49;
    s_1000=0.726;
    s_1200=0.277;

    s_tg=2.9;
    s_ttg=3.8;
    s_ttgg=0.013;
    
    s_bsm=0.79;
    s_sm_all=0.09;
    //s_sm=0.09*0.0023;
    
        n_700=cf_700->GetBinContent(0);
        n_1000=cf_1000->GetBinContent(0);
        n_1200=cf_1200->GetBinContent(0);

        //n_sm=cf_sm->GetBinContent(0);
        n_bsm=cf_bsm->GetBinContent(0);
        n_sm_all=cf_sm_all->GetBinContent(0);

        n_tg=cf_tg->GetBinContent(0);
        n_ttg=cf_ttg->GetBinContent(0);
        n_ttgg=cf_ttgg->GetBinContent(0);

    //Scalo a sez d'urto su eventi
    h_700->Scale((s_700*L)/(n_700));
    h_1000->Scale((s_1000*L)/(n_1000));
    h_1200->Scale((s_1200*L)/(n_1200));

    h_bsm->Scale((s_bsm*L)/(n_bsm));
    h_sm_all->Scale((s_sm_all*L)/(n_sm_all));
    //h_sm->Scale((s_sm*L)/(n_sm));
    
    h_tg->Scale((s_tg*L)/(n_tg));
    h_ttg->Scale((s_ttg*L)/(n_ttg));
    h_ttgg->Scale((s_ttgg*L)/(n_ttgg));

        /*h_bsm->Rebin(5);
        h_sm_all->Rebin(5);
        //h_sm->Rebin(4);

        h_tg->Rebin(5);
        h_ttg->Rebin(5);
        h_ttgg->Rebin(5);
        
        h_700->Rebin(5);
        h_1000->Rebin(5);
        h_1200->Rebin(5); */

    //h_tg->GetXaxis()->SetRangeUser(0.1,650);
    //h_700->GetYaxis()->SetRangeUser(0.1,1);
    //h_tg->GetXaxis()->SetTitle("Tagli");

    /*h_ttgg->GetXaxis()->SetBinLabel(1,"Higgs");
    h_ttgg->GetXaxis()->SetBinLabel(2,"Leptoni");
    h_ttgg->GetXaxis()->SetBinLabel(3,"Jets");*/

        /*h_tg->SetLineColor(7);
        h_ttg->SetLineColor(8);
        h_ttgg->SetLineColor(15);
        h_ttgg->DrawNormalized("hist same");
        h_tg->DrawNormalized("hist same");
        
        h_ttg->DrawNormalized("hist same");

            //h_sm->SetLineColor(6);
            //h_sm->Draw("hist same");
        h_sm_all->SetLineColor(6);
        h_bsm->SetLineColor(9);
        //h_bsm->Draw("hist same");
        //h_sm_all->Draw("hist same");
        
        h_700->SetLineColor(kRed);
        h_1000->SetLineColor(kBlack);
        h_1200->SetLineColor(kOrange);
        //h_700->Draw("hist same");
        //h_1000->Draw("hist same");
        //h_1200->Draw("hist same"); */
        

    //Legenda centrale 0.4,0.7,0.6,0.9
    //Legenda a sx 0.1,0.7,0.48,0.9
    //sx ristretta 0.1,0.7,0.4,0.9
    /*auto leg = new TLegend(0.4,0.7,0.6,0.9);
    leg->SetHeader("Legenda","C");

    leg->AddEntry(h_tg, "t+photon","l");
    leg->AddEntry(h_ttg, "tt+photon","l");
    leg->AddEntry(h_ttgg, "tt+2photon","l");*/

    //leg->AddEntry(h_bsm, "BSM","l");
    //leg->AddEntry(h_sm_all, "SM","l");
    //leg->AddEntry(h_sm, "SM_aa","l"); 

    //leg->AddEntry(h_700, "tHq_700","l");
    //leg->AddEntry(h_1000, "tHq_1000","l");
    //leg->AddEntry(h_1200, "tHq_1200","l");

    /*leg->Draw();
    //c.SetLogy();
    c.SaveAs((nomehisto+"_Scalato.pdf").c_str());*/

    //Da qui integro
    
        double ni_sm_all,ni_sm,ni_bsm,ni_700,ni_1000,ni_1200,ni_bg;
        double cut_sm_all,cut_sm,cut_bsm,cut_700,cut_1000,cut_1200;
        cut_sm_all=h_sm_all->FindBin(250);
        //cut_sm=h_sm->FindBin(140);
        cut_bsm=h_bsm->FindBin(160);
        cut_700=h_700->FindBin(180);
        cut_1000=h_1000->FindBin(250);
        cut_1200=h_1200->FindBin(260);

        ni_sm_all=h_sm_all->Integral(cut_sm_all,9999);
        //ni_sm=h_sm->Integral(cut_sm,9999);
        ni_bsm=h_bsm->Integral(cut_bsm,9999);
        ni_700=h_700->Integral(cut_700,9999);
        ni_1000=h_1000->Integral(cut_1000,9999);
        ni_1200=h_1200->Integral(cut_1200,9999);
        ni_bg=h_tg->Integral()+h_ttg->Integral()+h_ttgg->Integral();
           cout<<endl;
            /*cout<<"Mando in Output la funzione nome_histo->Integral(); dei vari fondi e segnali"<<endl;
            cout<<"integrale fatto su SM_all: "<<ni_sm_all<<endl;
            //cout<<"integrale fatto su SM_aa: "<<ni_sm<<endl;
            cout<<"integrale fatto su BSM: "<<ni_bsm<<endl;

            cout<<"integrale fatto su tHq_700: "<<ni_700<<endl;
            cout<<"integrale fatto su tHq_1000: "<<ni_1000<<endl;
            cout<<"integrale fatto su tHq_1200: "<<ni_1200<<endl;

            cout<<"integrale tG+ttG+ttGG: "<<ni_bg<<endl<<endl;*/

    //Ora calcolo la significance
    double sig_sm_all,sig_sm,sig_bsm,sig_700,sig_1000,sig_1200;
        sig_sm_all=ni_sm_all/(sqrt(ni_sm_all+ni_bg));
        //sig_sm=ni_sm/(sqrt(ni_sm+ni_bg));
        sig_bsm=ni_bsm/(sqrt(ni_bsm+ni_bg));

        sig_700=ni_700/(sqrt(ni_700+ni_bg));
        sig_1000=ni_1000/(sqrt(ni_1000+ni_bg));
        sig_1200=ni_1200/(sqrt(ni_1200+ni_bg));

            cout<<"Mando in Output le varie significance per ogni segnale calcolate con sig=ni_s/(sqrt(ni_s+ni_bg))"<<endl;
            //cout<<"Significance sm_all= "<<sig_sm_all<<endl;
                //cout<<"Significance sm_aa= "<<sig_sm<<endl;
            //cout<<"Significance bsm= "<<sig_bsm<<endl;

            cout<<"Significance 700= "<<sig_700<<endl;
            cout<<"Significance 1000= "<<sig_1000<<endl;
            cout<<"Significance 1200= "<<sig_1200<<endl;
}