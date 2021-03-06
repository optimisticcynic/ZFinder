#include "ZFinder/Event/interface/ZDefinitionTree.h"

// Standard Library
#include <algorithm>
#include <vector>  // std::min

// ZFinder Code
#include "ZFinder/Event/interface/CutLevel.h"  // cutlevel_vector
#include "ZFinder/Event/interface/WeightID.h"  // WeightID, STR_TO_WEIGHTID

#include "iostream"

namespace zf {
    // Constructor

    ZDefinitionTree::ZDefinitionTree(const ZDefinition& zdef, TFileDirectory& tdir, const bool IS_MC) : IS_MC_(IS_MC) {
        // Get the name of the cut we want
        zdef_name_ = zdef.NAME;

        // Make the directory to save files to
        tdir.cd();

        // Make the Tree to write to
        tree_ = new TTree(zdef.NAME.c_str(), zdef.NAME.c_str());
        const std::string CODE = "z_m/D:z_y:z_yNaked:z_yBorn:z_phistar_born:z_phistar_dressed:z_phistar_naked:z_phistar_sc:z_pt:z_eta:e_pt0:e_pt1:e_eta0:e_eta1:e_phi0:e_phi1:e_rnine0:e_rnine1:e_TrackIso0:e_TrackIso1:e_EcalIso0:e_EcalIso1:e_HcalIso0:e_HcalIso1:n_true_pileup:z_mom1PDG/I:z_mom2PDG/I:z_penultimate1PDG/I:z_penultimate2PDG/I:e_charge0/I:e_charge1:n_verts:njets/I:JetHT/D:JetPt[njets]/D:JetEta[njets]:t0tight/O:t1tight";
        tree_->Branch("reco", &reco_, CODE.c_str());
        if (IS_MC_) {
            tree_->Branch("truth", &truth_, CODE.c_str());
        }
        const std::string EVENT_CODE = "event_number/i:run_number:is_mc/O";
        tree_->Branch("event_info", &event_, EVENT_CODE.c_str());
        if (IS_MC_) {
            tree_->Branch("weight_size", &weight_size_, "weight_size/I");
            tree_->Branch("weights", weights_, "weights[weight_size]/D");
            tree_->Branch("weight_ids", weight_ids_, "weight_ids[weight_size]/I");
            tree_->Branch("weight_cteq_size", &weight_cteq_size_, "weight_cteq_size/I");
            tree_->Branch("weights_cteq", weights_cteq_, "weights_cteq[weight_cteq_size]/D");
            tree_->Branch("weight_mstw_size", &weight_mstw_size_, "weight_mstw_size/I");
            tree_->Branch("weights_mstw", weights_mstw_, "weights_mstw[weight_mstw_size]/D");
            tree_->Branch("weight_nnpdf_size", &weight_nnpdf_size_, "weight_nnpdf_size/I");
            tree_->Branch("weights_nnpdf", weights_nnpdf_, "weights_nnpdf[weight_nnpdf_size]/D");
            tree_->Branch("weight_fsr", &weight_fsr_, "weight_fsr/D");
        }
    }

    ZDefinitionTree::~ZDefinitionTree() {
        // Clean up our pointer
        delete tree_;
    }

    void ZDefinitionTree::Fill(const ZFinderEvent& zf_event) {
        // If the ZDefinition doesn't pass, escape
        if (!zf_event.ZDefPassed(zdef_name_)) {
            return;
        }

        // Clear our branches
        reco_.clear_values();
        truth_.clear_values();
        event_.clear_values();
        weight_id_vector_.clear();

        // Set the weightsg
        if (IS_MC_) {
            // The weight from the generator
            const double GEN_WEIGHT = zf_event.weight_natural_mc;
            weight_id_vector_.push_back(std::make_pair(WeightID::GEN_MC, GEN_WEIGHT));

            // The pileup weight
            const double VERT_WEIGHT = zf_event.weight_vertex;
            weight_id_vector_.push_back(std::make_pair(WeightID::PILEUP, VERT_WEIGHT));
            const double VERT_WEIGHT_PLUS = zf_event.weight_vertex_plus;
            weight_id_vector_.push_back(std::make_pair(WeightID::PILEUP_PLUS, VERT_WEIGHT_PLUS));
            const double VERT_WEIGHT_MINUS = zf_event.weight_vertex_minus;
            weight_id_vector_.push_back(std::make_pair(WeightID::PILEUP_MINUS, VERT_WEIGHT_MINUS));

            // Get the scale factors weight and fill up weight_id_vector_ with them
            const cutlevel_vector* clv = zf_event.GetZDef(zdef_name_);
            FillCutWeights(clv);

            // Loop over out vector of weights and save them to the arrays so that
            // the tree can grab the values. If the vector is longer than
            // MAX_SIZE_, we stop there so as not to overflow our array!
            weight_size_ = weight_id_vector_.size();
            for (int i = 0; i < std::min(weight_size_, MAX_SIZE_); ++i) {
                const int WEIGHT_ID = weight_id_vector_.at(i).first;
                const double WEIGHT = weight_id_vector_.at(i).second;
                weights_[i] = WEIGHT;
                weight_ids_[i] = WEIGHT_ID;
            }
            weight_cteq_size_ = zf_event.weights_cteq.size();
            for (int i = 0; i < std::min(weight_cteq_size_, MAX_SIZE_PDF_); ++i) {
                weights_cteq_[i] = zf_event.weights_cteq[i];
            }
            weight_mstw_size_ = zf_event.weights_mstw.size();
            for (int i = 0; i < std::min(weight_mstw_size_, MAX_SIZE_PDF_); ++i) {
                weights_mstw_[i] = zf_event.weights_mstw[i];
            }
            weight_nnpdf_size_ = zf_event.weights_nnpdf.size();
            for (int i = 0; i < std::min(weight_nnpdf_size_, MAX_SIZE_PDF_); ++i) {
                weights_nnpdf_[i] = zf_event.weights_nnpdf[i];
            }

            weight_fsr_ = zf_event.weight_fsr;
        }

        // Reco
        reco_.z_m = zf_event.reco_z.m;
        reco_.z_y = zf_event.reco_z.y;
        //std::cout<<"TREE Mom 1: "<<zf_event.reco_z.z_mom1PDG<<"  Mom 2: "<<zf_event.reco_z.z_mom2PDG<<" Penultimate1PDG: "<<zf_event.reco_z.z_penultimate1PDG<<" and the second is: "<<zf_event.reco_z.z_penultimate2PDG<<std::endl;
        reco_.z_mom1PDG = zf_event.reco_z.z_mom1PDG;
        reco_.z_mom2PDG = zf_event.reco_z.z_mom2PDG;
        reco_.z_penultimate1PDG = zf_event.reco_z.z_penultimate1PDG;
        reco_.z_penultimate2PDG = zf_event.reco_z.z_penultimate2PDG;

        reco_.z_yNaked = zf_event.reco_z.yNaked;
        reco_.z_yBorn = zf_event.reco_z.yBorn;

        reco_.z_phistar_dressed = zf_event.reco_z.phistar;
        reco_.z_phistar_born = zf_event.reco_z.bornPhistar;
        reco_.z_phistar_naked = zf_event.reco_z.nakedPhistar;
        reco_.z_phistar_sc = zf_event.reco_z.scPhistar;
        reco_.z_pt = zf_event.reco_z.pt;
        reco_.z_eta = zf_event.reco_z.eta;
        reco_.n_verts = zf_event.reco_vert.num;
        reco_.njets = zf_event.reco_z.njets;

        memcpy(reco_.JetEta, zf_event.reco_z.JetEta, sizeof (zf_event.reco_z.JetEta));
        memcpy(reco_.JetPt, zf_event.reco_z.JetPt, sizeof (zf_event.reco_z.JetPt));

        reco_.JetHT = zf_event.reco_z.JetHT;
        if (zf_event.e0 != nullptr) {
            reco_.e_pt[0] = zf_event.e0->pt();
            reco_.e_eta[0] = zf_event.e0->eta();
            reco_.e_phi[0] = zf_event.e0->phi();
            reco_.e_rnine[0] = zf_event.e0->r9();
            reco_.e_charge[0] = zf_event.e0->charge();
            reco_.e_TrackIso[0] = zf_event.e0->track_iso();
            reco_.e_EcalIso[0] = zf_event.e0->ecal_iso();
            reco_.e_HcalIso[0] = zf_event.e0->hcal_iso();
        }
        if (zf_event.e1 != nullptr) {
            reco_.e_pt[1] = zf_event.e1->pt();
            reco_.e_eta[1] = zf_event.e1->eta();
            reco_.e_phi[1] = zf_event.e1->phi();
            reco_.e_rnine[1] = zf_event.e1->r9();
            reco_.e_charge[1] = zf_event.e1->charge();
            reco_.e_TrackIso[1] = zf_event.e1->track_iso();
            reco_.e_EcalIso[1] = zf_event.e1->ecal_iso();
            reco_.e_HcalIso[1] = zf_event.e1->hcal_iso();
            if (zf_event.GetZDef(zdef_name_) != nullptr) {
                const cutlevel_vector* clv = zf_event.GetZDef(zdef_name_);
                reco_.t0tight = clv->back().second.t0p1_pass;
                reco_.t1tight = clv->back().second.t1p0_pass;
            }
        }
        // Truth
        if (IS_MC_ && !zf_event.is_real_data) {
            truth_.z_m = zf_event.truth_z.m;
            truth_.z_y = zf_event.truth_z.y;
            truth_.z_phistar_dressed = zf_event.truth_z.phistar;
            truth_.z_phistar_born = zf_event.truth_z.bornPhistar;
            truth_.z_phistar_naked = zf_event.truth_z.nakedPhistar;
            truth_.z_phistar_sc = zf_event.truth_z.scPhistar;
            truth_.z_pt = zf_event.truth_z.pt;
            truth_.z_eta = zf_event.truth_z.eta;
            truth_.n_verts = zf_event.truth_vert.num;

            truth_.njets = zf_event.truth_z.njets;
            memcpy(truth_.JetEta, zf_event.truth_z.JetEta, sizeof (zf_event.truth_z.JetEta));
            memcpy(truth_.JetPt, zf_event.truth_z.JetPt, sizeof (zf_event.truth_z.JetPt));
            truth_.JetHT = zf_event.truth_z.JetHT;

            truth_.n_true_pileup = zf_event.truth_vert.true_num;


            truth_.z_mom1PDG = zf_event.truth_z.z_mom1PDG;
            truth_.z_mom2PDG = zf_event.truth_z.z_mom2PDG;
            truth_.z_penultimate1PDG = zf_event.truth_z.z_penultimate1PDG;
            truth_.z_penultimate2PDG = zf_event.truth_z.z_penultimate2PDG;
            if (zf_event.e0_truth != nullptr) {
                truth_.e_pt[0] = zf_event.e0_truth->pt();
                truth_.e_eta[0] = zf_event.e0_truth->eta();
                truth_.e_phi[0] = zf_event.e0_truth->phi();
                truth_.e_rnine[0] = zf_event.e0_truth->r9();
                truth_.e_charge[0] = zf_event.e0_truth->charge();
            }
            if (zf_event.e1_truth != nullptr) {
                truth_.e_pt[1] = zf_event.e1_truth->pt();
                truth_.e_eta[1] = zf_event.e1_truth->eta();
                truth_.e_phi[1] = zf_event.e1_truth->phi();
                truth_.e_rnine[1] = zf_event.e1_truth->r9();
                truth_.e_charge[1] = zf_event.e1_truth->charge();
                if (zf_event.GetZDef(zdef_name_) != nullptr) {
                    const cutlevel_vector* clv = zf_event.GetZDef(zdef_name_);
                    truth_.t0tight = clv->back().second.t0p1_pass;
                    truth_.t1tight = clv->back().second.t1p0_pass;
                }
            }
        }
        // General Event info
        event_.is_mc = !zf_event.is_real_data;
        event_.event_number = zf_event.id.event_num;
        event_.run_number = zf_event.id.run_num;

        // Fill if there is a good Z in either truth or reco
        if (zf_event.truth_z.m > -1 || zf_event.reco_z.m > -1) {
            tree_->Fill();
        }
    }

    void ZDefinitionTree::FillCutWeights(cutlevel_vector const * const CUT_LEVEL_VECTOR) {
        if (CUT_LEVEL_VECTOR != nullptr) {
            // Check if we pass via Tag 0 Probe 1, or Tag 1 Probe 1
            CutLevel last_cutlevel = CUT_LEVEL_VECTOR->back().second;
            bool t0p1 = last_cutlevel.t0p1_pass; // Takes Priority
            bool t1p0 = last_cutlevel.t1p0_pass;

            // Loop over our vector and at each level pull out the right
            for (auto& i_cutlevel : *CUT_LEVEL_VECTOR) {
                // Get the cut names and try to find the matching WeightIDs
                const std::string TAG_CUT = i_cutlevel.second.tag_cut;
                const std::string PROBE_CUT = i_cutlevel.second.probe_cut;
                std::map<std::string, int>::const_iterator tag_it = STR_TO_WEIGHTID.find(TAG_CUT);
                std::map<std::string, int>::const_iterator probe_it = STR_TO_WEIGHTID.find(PROBE_CUT);
                // Get the weights for the tag and probe
                double tag_weight = 1.;
                double probe_weight = 1.;
                if (t0p1) {
                    tag_weight = i_cutlevel.second.t0p1_tag_weight;
                    probe_weight = i_cutlevel.second.t0p1_probe_weight;
                } else if (t1p0) {
                    tag_weight = i_cutlevel.second.t1p0_tag_weight;
                    probe_weight = i_cutlevel.second.t1p0_probe_weight;
                }
                // The Tag has a WeightID
                if (tag_it != STR_TO_WEIGHTID.end()) {
                    const int WEIGHTID = tag_it->second;
                    weight_id_vector_.push_back(std::make_pair(WEIGHTID, tag_weight));
                }
                if (probe_it != STR_TO_WEIGHTID.end()) {
                    const int WEIGHTID = probe_it->second;
                    weight_id_vector_.push_back(std::make_pair(WEIGHTID, probe_weight));
                }
            }
        }
    }

    TFile* ZDefinitionTree::GetCurrentFile() {
        return tree_->GetCurrentFile();
    }
} // namespace zf
