#include <iostream>
#include <cmath>
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TLorentzVector.h"

using namespace std;

int main(int argc, char**argv ){

    TCanvas c1;

    string nomecanale = argv[1];
    string option = argv[2];
    TFile * outputfile = new TFile("outputfilename.root",(option).c_str()); 
    TFile *_file0=TFile::Open((nomecanale+".root").c_str());
    TTree *t=NULL;
    t=((TTree *)(_file0->Get("Events")));

    TH1F * h_mH = new TH1F("h_mH","Massa Higgs ricostruita",400, 0, 200 );
    TH1F * h_mHf = new TH1F("h_mHf","Massa Higgs ultimo taglio",400, 0, 200 );

    TH1F * h_nmu = new TH1F("h_nmu","Conteggio muoni good",10, 0, 10 );
    TH1F * h_ne = new TH1F("h_ne","Conteggio elettroni good",10, 0, 10 );

    TH1F * h_tpt = new TH1F("h_tpt","Pt top",300, 0, 1500 );
    TH1F * h_Tpt = new TH1F("h_Tpt","Pt Tprime",300, 0, 1500 );

    TH1F * h_Hpt_1 = new TH1F("h_Hpt","Pt higgs",300, 0, 1000 );
    TH1F * h_Hpt_2 = new TH1F("h_Hpt","Pt higgs",300, 0, 1000 );
    TH1F * h_Hpt_3 = new TH1F("h_Hpt","Pt higgs",300, 0, 1000 );

    TH1F * h_jett_pt = new TH1F("h_jett_pt","Pt jets",300, 0, 700 );
    TH1F * h_MET_pt = new TH1F("h_MET_pt","Pt met",300, 0, 700 );
    TH1F * h_mupt = new TH1F("h_mupt","pt muoni good",100, 0, 700 );
    TH1F * h_ept = new TH1F("h_ept","pt elettroni good",100, 0, 700 );

    TH1F * h_cutFlow = new TH1F("h_cutFlow","cutFlow",3, 0, 3 );
    TH1F * h_dr = new TH1F("h_dr","DeltaR",20, 0, 10 );


    int higgs_count=0;
    int lepton_count=0;
    int jet_count=0;

    unsigned int nph=-1;
    unsigned int nmu=-1;
    unsigned int ne=-1;
    unsigned int njet=-1;

    double massaH = 125.18;
    double MH = 1500,H_pt,T_pt;
    double s1,s2;

    bool mvaID[50];
    bool muID[50];
    bool eID[50];
    float jet_btag[50];

    float photon_pt[50];
    float mu_pt[50];
    float e_pt[50];
    float MET_pt;
    float jet_pt[50];

    float photon_eta[50];
    float photon_phi[50];
    float photon_mass[50];
    float e_phi[50];
    float e_eta[50];
    float mu_eta[50];
    float mu_phi[50];
    float jet_phi[50];
    float MET_phi;

    size_t photon_idx1=0,photon_idx2=0;

    t->SetBranchAddress("nPhoton" , &nph);
    t->SetBranchAddress("nElectron" , &ne);
    t->SetBranchAddress("nMuon" , &nmu);
    t->SetBranchAddress("nJet" , &njet);

    t->SetBranchAddress("Photon_pt" , &photon_pt);
    t->SetBranchAddress("Electron_pt" , &e_pt);
    t->SetBranchAddress("Muon_pt" , &mu_pt);
    t->SetBranchAddress("MET_pt" , &MET_pt);
    t->SetBranchAddress("Jet_pt" , &jet_pt);

    t->SetBranchAddress("Photon_eta" , &photon_eta);
    t->SetBranchAddress("Photon_phi" , &photon_phi);
    t->SetBranchAddress("Photon_mass",&photon_mass);
    t->SetBranchAddress("Electron_phi" , &e_phi);
    t->SetBranchAddress("Electron_eta" , &e_eta);
    t->SetBranchAddress("Muon_phi" , &mu_phi);
    t->SetBranchAddress("Muon_eta" , &mu_eta);
    t->SetBranchAddress("MET_phi" , &MET_phi);
    t->SetBranchAddress("Jet_phi" , &jet_phi);

    t->SetBranchAddress("Photon_mvaID_WP80" , &mvaID);
    t->SetBranchAddress("Muon_mediumId" , &muID);
    t->SetBranchAddress("Electron_mvaFall17V2Iso_WP80" , &eID);
    t->SetBranchAddress("Jet_btagDeepFlavB" , &jet_btag);

    //int nentries=t->GetEntries();
    for(int i=0 ; i<t->GetEntries() ; i++){
        t->GetEntry(i);
        if(i%50000==0){
            cout<<"evento #"<<i<<"; "<<((float)i/t->GetEntries())*100<<"%"<<endl;
        }
        TLorentzVector pp1,pp2;
        for(int j1=0 ; j1<nph ; j1++){
            if((photon_pt[j1])>25 && (mvaID[j1])==1){
                for(int j2=0 ; j2<j1 ; j2++){
                    if((photon_pt[j2])>25 && (mvaID[j2])==1){
                        pp1.SetPtEtaPhiM((photon_pt)[j1],(photon_eta)[j1],(photon_phi)[j1],(photon_mass)[j1]);
                        pp2.SetPtEtaPhiM((photon_pt)[j2],(photon_eta)[j2],(photon_phi)[j2],(photon_mass)[j2]);       
                        TLorentzVector pH= (pp1+pp2);
                        double mH= (pH.M());

                        s1=(mH-massaH)*(mH-massaH);
                        s2=(MH-massaH)*(MH-massaH);
                        if(s1<s2){
                            MH=mH;
                            H_pt=(pH.Pt());

                            photon_idx1=j1; //Mi servono per salvarmi gli indici di sti cosi
                            photon_idx2=j2;
                        }
                    }
                }
            }
        }
        if(MH>110 && MH<140){
            higgs_count++;
                h_mH->Fill(MH);
                h_Hpt_1->Fill(H_pt);

                int conteggio_mu=0;
                for(int l=0 ; l<nmu ; l++){
                    if((mu_pt[l])>20 && (muID[l])==1){
                        conteggio_mu=conteggio_mu+1;
                    }
                }
                h_nmu->Fill(conteggio_mu);

                int conteggio_e=0;
                for(int m=0 ; m<ne ; m++){
                    if((e_pt[m])>20 && (eID[m])==1){
                        conteggio_e=conteggio_e+1;
                    }
                }
                h_ne->Fill(conteggio_e);
                
                double Dr1,Dr2,Dr_min;
                double mu_px=0,mu_py=0,e_px=0,e_py=0,MET_px=0,MET_py=0;
                double jet_px,jet_py,t_px,t_py,t_pt;
                if((conteggio_mu==1 && conteggio_e==0) || (conteggio_mu==0 && conteggio_e==1)){
                    for(int l=0 ; l<nmu ; l++){
                        if ((mu_pt[l])>20 && (muID[l])==1){
                            lepton_count++;
                            h_mupt->Fill(mu_pt[l]);
                            mu_px=(mu_pt[l])*cos(mu_phi[l]);
                            mu_py=(mu_pt[l])*sin(mu_phi[l]);

                            Dr1=sqrt((mu_phi[l]-photon_phi[photon_idx1])*(mu_phi[l]-photon_phi[photon_idx1])+(mu_eta[l]-photon_eta[photon_idx1])*(mu_eta[l]-photon_eta[photon_idx1]));
                            Dr2=sqrt((mu_phi[l]-photon_phi[photon_idx2])*(mu_phi[l]-photon_phi[photon_idx2])+(mu_eta[l]-photon_eta[photon_idx2])*(mu_eta[l]-photon_eta[photon_idx2]));
                            if(Dr1>Dr2){
                                h_dr->Fill(Dr2);
                                Dr_min=Dr2;
                            }
                            else if(Dr1<Dr2){
                                h_dr->Fill(Dr1);
                                Dr_min=Dr1;
                            }
                        }
                    }
                    for(int l=0 ; l<ne ; l++){
                        if ((e_pt[l])>20 && (eID[l])==1){
                            lepton_count++;
                            h_ept->Fill(e_pt[l]);
                            e_px=(e_pt[l])*cos(e_phi[l]);
                            e_py=(e_pt[l])*sin(e_phi[l]);

                            Dr1=sqrt((e_phi[l]-photon_phi[photon_idx1])*(e_phi[l]-photon_phi[photon_idx1])+(e_eta[l]-photon_eta[photon_idx1])*(e_eta[l]-photon_eta[photon_idx1]));
                            Dr2=sqrt((e_phi[l]-photon_phi[photon_idx2])*(e_phi[l]-photon_phi[photon_idx2])+(e_eta[l]-photon_eta[photon_idx2])*(e_eta[l]-photon_eta[photon_idx2]));
                            if(Dr1>Dr2){
                                h_dr->Fill(Dr2);
                                Dr_min=Dr2;
                            }
                            else if(Dr1<Dr2){
                                h_dr->Fill(Dr1);
                                Dr_min=Dr1; 
                            }
                        }
                    }

                    //Il seguente if serve per selezionare i fondi
                    if(Dr_min>0.4){
                        MET_px=MET_pt*cos(MET_phi);
                        MET_py=MET_pt*sin(MET_phi);
                        h_MET_pt->Fill(MET_pt);
                        h_Hpt_2->Fill(H_pt);

                        double jet_pt_max=0;
                        for(int l=0 ; l<njet ; l++){
                            if(jet_pt[l]>jet_pt_max  && jet_btag[l] > 0.7264 ){
                                jet_pt_max=jet_pt[l];
                                if(jet_pt_max>30){
                                    jet_count++;
                                    jet_px=jet_pt_max*cos(jet_phi[l]);
                                    jet_py=jet_pt_max*sin(jet_phi[l]);

                                    h_jett_pt->Fill(jet_pt_max);

                                    t_px=mu_px+e_px+MET_px+jet_px;
                                    t_py=mu_py+e_py+MET_py+jet_py;
                                    t_pt=sqrt((t_px*t_px)+(t_py*t_py));

                                    T_pt=H_pt+t_pt;
                                }
                            }
                        }
                        h_tpt->Fill(t_pt);
                        h_Tpt->Fill(T_pt);
                        h_Hpt_3->Fill(H_pt);
                        h_mHf->Fill(MH);
                    }
                }
            }
        MH=1500;
    }


    h_cutFlow->SetBinContent(0,t->GetEntries());
    h_cutFlow->SetBinContent(1,higgs_count);
    h_cutFlow->SetBinContent(2,lepton_count);
    h_cutFlow->SetBinContent(3,jet_count);


    /*h_tpt->Draw();
    c1.SaveAs((nomecanale+"h_tpt_E.pdf").c_str());
    h_Tpt->Draw();
    c1.SaveAs((nomecanale+"h_Tpt_E.pdf").c_str());
    h_cutFlow->Draw();
    c1.SaveAs((nomecanale+"h_cutFlow_E.pdf").c_str());
    h_mH->Draw();
    c1.SaveAs((nomecanale+"h_mH_E.pdf").c_str());

    h_Hpt_1->Draw();
    c1.SaveAs((nomecanale+"h_Hpt_1_E.pdf").c_str());
    h_Hpt_2->Draw();
    c1.SaveAs((nomecanale+"h_Hpt_2_E.pdf").c_str());
    h_Hpt_3->Draw();
    c1.SaveAs((nomecanale+"h_Hpt_3_E.pdf").c_str());

    h_mupt->Draw();
    c1.SaveAs((nomecanale+"mu_pt_E.pdf").c_str());
    h_ept->Draw();
    c1.SaveAs((nomecanale+"e_pt_E.pdf").c_str());
    h_MET_pt->Draw();
    c1.SaveAs((nomecanale+"MET_pt_E.pdf").c_str());
    h_jett_pt->Draw();
    c1.SaveAs((nomecanale+"Jet_pt_max_E.pdf").c_str());
    h_nmu->Draw();
    c1.SaveAs((nomecanale+"n_mu_E.pdf").c_str());
    h_ne->Draw();
    c1.SaveAs((nomecanale+"n_e_E.pdf").c_str()); */


    outputfile->cd();
    h_tpt->Write((nomecanale+"_top_pt").c_str());
    h_Tpt->Write((nomecanale+"_Tprime_pt").c_str());
    h_mH->Write((nomecanale+"_mHiggs").c_str());
    h_cutFlow->Write((nomecanale+"_cutflow").c_str());

    h_Hpt_1->Write((nomecanale+"_Higgs_1_pt").c_str());
    h_Hpt_2->Write((nomecanale+"_Higgs_2_pt").c_str());
    h_Hpt_3->Write((nomecanale+"_Higgs_3_pt").c_str());

    h_mupt->Write((nomecanale+"_mu_pt").c_str());
    h_ept->Write((nomecanale+"_e_pt").c_str());
    h_jett_pt->Write((nomecanale+"_jetmax_pt").c_str());
    h_nmu->Write((nomecanale+"_n_mu").c_str());
    h_ne->Write((nomecanale+"_n_e").c_str());

    h_dr->Write((nomecanale+"_deltar").c_str());
    h_mHf->Write((nomecanale+"_massa_higgs_finale").c_str());

    outputfile->Close();
    return 0;
}
