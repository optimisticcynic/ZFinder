#include "ZFinder/Event/interface/ZFinderEvent.h"

// Standard Library
#include <algorithm>  // std::sort, std::swap
#include <iostream>  // std::cout, std::endl

// CMSSW
#include "DataFormats/Common/interface/Handle.h"  // edm::Handle
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"  // reco::PhotonCollection
#include "DataFormats/EgammaReco/interface/HFEMClusterShape.h"  // reco::HFEMClusterShape
#include "DataFormats/EgammaReco/interface/HFEMClusterShapeAssociation.h"  // reco::HFEMClusterShapeAssociationCollection
#include "DataFormats/EgammaReco/interface/HFEMClusterShapeFwd.h"  // reco::HFEMClusterShapeRef,
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"  // reco::SuperClusterCollection, reco::SuperClusterRef
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidateFwd.h"  // reco::RecoEcalCandidateCollection
#include "EgammaAnalysis/ElectronTools/interface/EGammaCutBasedEleId.h"  // EgammaCutBasedEleId::PassWP, EgammaCutBasedEleId::*
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"  // PileupSummaryInfo

// ZFinder
#include "ZFinder/Event/interface/PDGID.h"  // PDGID enum (ELECTRON, POSITRON, etc.)


namespace zf {
    ZFinderEvent::ZFinderEvent(const edm::Event& iEvent, const edm::EventSetup& iSetup, const edm::ParameterSet& iConfig) {
        /* Given an event, parses them for the information needed to make the classe.
         *
         * It selects electrons based on a minimum level of hard-coded cuts.
         */
        // Clear Events
        InitVariables();

        // Get event info
        id.run_num = iEvent.run();
        id.lumi_num = iEvent.luminosityBlock();
        id.event_num = iEvent.id().event();

        // Set local is_real_data
        is_real_data = iEvent.isRealData();

        // Get InputTags
        // Reco
        inputtags_.ecal_electron = iConfig.getParameter<edm::InputTag>("ecalElectronsInputTag");
        inputtags_.nt_electron = iConfig.getParameter<edm::InputTag>("ntElectronsInputTag");
        inputtags_.hf_electron = iConfig.getParameter<edm::InputTag>("hfElectronsInputTag");
        inputtags_.hf_clusters = iConfig.getParameter<edm::InputTag>("hfClustersInputTag");
        inputtags_.conversion = iConfig.getParameter<edm::InputTag>("conversionsInputTag");
        inputtags_.beamspot = iConfig.getParameter<edm::InputTag>("beamSpotInputTag");
        inputtags_.rho_iso = iConfig.getParameter<edm::InputTag>("rhoIsoInputTag");
        inputtags_.vertex = iConfig.getParameter<edm::InputTag>("primaryVertexInputTag");
        inputtags_.iso_vals = iConfig.getParameter<std::vector<edm::InputTag> >("isoValInputTags");

        // Truth
        inputtags_.pileup = iConfig.getParameter<edm::InputTag>("pileupInputTag");
        inputtags_.generator = iConfig.getParameter<edm::InputTag>("generatorInputTag");

        // Finish initialization of electrons
        InitReco(iEvent, iSetup);  // Data
        if (!is_real_data) {
            InitTruth(iEvent, iSetup);  // MC
        }
    }

    void ZFinderEvent::InitReco(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

        /* Count Pile Up and store first vertex location*/
        edm::Handle<reco::VertexCollection> reco_vertices;
        iEvent.getByLabel(inputtags_.vertex, reco_vertices);
        reco_vert.num = 0;
        bool first_vertex = true;
        for(unsigned int vertex=0; vertex < reco_vertices->size(); ++vertex) {
            if (    // Criteria copied from twiki
                    !((*reco_vertices)[vertex].isFake())
                    && ((*reco_vertices)[vertex].ndof() > 4)
                    && (fabs((*reco_vertices)[vertex].z()) <= 24.0)
                    && ((*reco_vertices)[vertex].position().Rho() <= 2.0)
               ) {
                reco_vert.num++;
                // Store first good vertex as "primary"
                if (first_vertex) {
                    first_vertex = false;
                    reco_vert.x = (*reco_vertices)[vertex].x();
                    reco_vert.y = (*reco_vertices)[vertex].y();
                    reco_vert.z = (*reco_vertices)[vertex].z();
                }
            }
        }

        /* Beamspot */
        edm::Handle<reco::BeamSpot> beam_spot;
        iEvent.getByLabel(inputtags_.beamspot, beam_spot);
        reco_bs.x = beam_spot->position().X();
        reco_bs.y = beam_spot->position().Y();
        reco_bs.z = beam_spot->position().Z();

        /* Find electrons */
        InitGSFElectrons(iEvent, iSetup);
        InitHFElectrons(iEvent, iSetup);
        InitNTElectrons(iEvent, iSetup);

        // Sort our electrons and set e0, e1 as the two with the highest pt
        std::sort(reco_electrons_.begin(), reco_electrons_.end(), SortByPTHighLow);

        // For Zs
        n_reco_electrons = reco_electrons_.size();
        if (n_reco_electrons >= 2) {
            // Set our internal electrons
            set_both_e(reco_electrons_[0], reco_electrons_[1]);
            // Set up the Z
            InitZ();
        }
    }

    void ZFinderEvent::InitGSFElectrons(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
        // We split this part into a new function because it is very long
        // Most of this code is stolen from the example here:
        // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/EGamma/EGammaAnalysisTools/src/EGammaCutBasedEleIdAnalyzer.cc?view=markup

        // electrons
        edm::Handle<reco::GsfElectronCollection> els_h;
        iEvent.getByLabel(inputtags_.ecal_electron, els_h);

        // conversions
        edm::Handle<reco::ConversionCollection> conversions_h;
        iEvent.getByLabel(inputtags_.conversion, conversions_h);

        // iso deposits
        typedef std::vector< edm::Handle< edm::ValueMap<double> > > IsoDepositVals;
        IsoDepositVals isoVals(inputtags_.iso_vals.size());
        for (size_t j = 0; j < inputtags_.iso_vals.size(); ++j) {
            iEvent.getByLabel(inputtags_.iso_vals[j], isoVals[j]);
        }

        // beam spot
        edm::Handle<reco::BeamSpot> beamspot_h;
        iEvent.getByLabel(inputtags_.beamspot, beamspot_h);
        const reco::BeamSpot &beamSpot = *(beamspot_h.product());

        // vertices
        edm::Handle<reco::VertexCollection> vtx_h;
        iEvent.getByLabel(inputtags_.vertex, vtx_h);

        // rho for isolation
        // The python uses:
        // cms.InputTag("kt6PFJetsForIsolation", "rho")
        edm::Handle<double> rho_iso_h;
        iEvent.getByLabel(inputtags_.rho_iso, rho_iso_h);
        double RHO_ISO = *(rho_iso_h.product());

        // loop on electrons
        for(unsigned int i = 0; i < els_h->size(); ++i) {
            // Get the electron and set put it into the electrons vector
            reco::GsfElectron electron = els_h->at(i);
            ZFinderElectron* zf_electron = AddRecoElectron(electron);

            // get reference to electron and the electron
            reco::GsfElectronRef ele_ref(els_h, i);

            // get particle flow isolation
            const double ISO_CH = (*(isoVals)[0])[ele_ref];
            const double ISO_EM = (*(isoVals)[1])[ele_ref];
            const double ISO_NH = (*(isoVals)[2])[ele_ref];

            // test ID
            // working points
            const bool VETO = EgammaCutBasedEleId::PassWP(EgammaCutBasedEleId::VETO, ele_ref, conversions_h, beamSpot, vtx_h, ISO_CH, ISO_EM, ISO_NH, RHO_ISO);
            const bool LOOSE = EgammaCutBasedEleId::PassWP(EgammaCutBasedEleId::LOOSE, ele_ref, conversions_h, beamSpot, vtx_h, ISO_CH, ISO_EM, ISO_NH, RHO_ISO);
            const bool MEDIUM = EgammaCutBasedEleId::PassWP(EgammaCutBasedEleId::MEDIUM, ele_ref, conversions_h, beamSpot, vtx_h, ISO_CH, ISO_EM, ISO_NH, RHO_ISO);
            const bool TIGHT = EgammaCutBasedEleId::PassWP(EgammaCutBasedEleId::TIGHT, ele_ref, conversions_h, beamSpot, vtx_h, ISO_CH, ISO_EM, ISO_NH, RHO_ISO);

            // eop/fbrem cuts for extra tight ID
            const bool FBREMEOPIN = EgammaCutBasedEleId::PassEoverPCuts(ele_ref);

            // cuts to match tight trigger requirements
            const bool TRIGTIGHT = EgammaCutBasedEleId::PassTriggerCuts(EgammaCutBasedEleId::TRIGGERTIGHT, ele_ref);

            // for 2011 WP70 trigger
            const bool TRIGWP70 = EgammaCutBasedEleId::PassTriggerCuts(EgammaCutBasedEleId::TRIGGERWP70, ele_ref);

            // Add the cuts to our electron
            const double WEIGHT = 1.;
            zf_electron->AddCutResult("eg_veto", VETO, WEIGHT);
            zf_electron->AddCutResult("eg_loose", LOOSE, WEIGHT);
            zf_electron->AddCutResult("eg_medium", MEDIUM, WEIGHT);
            zf_electron->AddCutResult("eg_tight", TIGHT, WEIGHT);
            zf_electron->AddCutResult("eg_eop_cut", FBREMEOPIN, WEIGHT);
            zf_electron->AddCutResult("eg_trigtight", TRIGTIGHT, WEIGHT);
            zf_electron->AddCutResult("eg_trigwp70", TRIGWP70, WEIGHT);
        }
    }

    void ZFinderEvent::InitHFElectrons(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
        // HF Electrons
        edm::Handle<reco::RecoEcalCandidateCollection> els_h;
        iEvent.getByLabel(inputtags_.hf_electron, els_h);
        // HF Superclusters
        edm::Handle<reco::SuperClusterCollection> scs_h;
        iEvent.getByLabel(inputtags_.hf_clusters, scs_h);
        edm::Handle<reco::HFEMClusterShapeAssociationCollection> scas_h;
        iEvent.getByLabel(inputtags_.hf_clusters, scas_h);

        // Loop over electrons
        for(unsigned int i = 0; i < els_h->size(); ++i) {
            // Get the electron and set put it into the electrons vector
            reco::RecoEcalCandidate electron = els_h->at(i);
            ZFinderElectron* zf_electron = AddRecoElectron(electron);

            reco::SuperClusterRef cluster_ref = electron.superCluster();
            const reco::HFEMClusterShapeRef CLUSTER_SHAPE_REF = scas_h->find(cluster_ref)->val;
            const reco::HFEMClusterShape& CLUSTER_SHAPE = *CLUSTER_SHAPE_REF;

            const double ECE9 = CLUSTER_SHAPE.eCOREe9();
            const double ESEL = CLUSTER_SHAPE.eSeL();
            const double E9E25 = (CLUSTER_SHAPE.eLong3x3() * 1.0 / CLUSTER_SHAPE.eLong5x5());

            // e9e25 cut
            const bool PASS_E9E25 = (E9E25 > 0.94);

            // HF Tight (as defined in hfRecoEcalCandidate_cfi.py in ZShape)
            const double TIGHT2D = (ECE9 - (ESEL * 0.20));
            const bool HFTIGHT = (TIGHT2D > 0.92);

            // HF Medium
            const double MEDIUM2D = (ECE9 - (ESEL * 0.275));
            const bool HFMEDIUM = (MEDIUM2D > 0.875);

            // HF Loose
            const double LOOSE2D = (ECE9 - (ESEL * 0.475));
            const bool HFLOOSE = (LOOSE2D > 0.815);

            // Add the cuts to our electron
            const double WEIGHT = 1.;
            zf_electron->AddCutResult("hf_e9e25", PASS_E9E25, WEIGHT);
            zf_electron->AddCutResult("hf_2dtight", HFTIGHT, WEIGHT);
            zf_electron->AddCutResult("hf_2dmedium", HFMEDIUM, WEIGHT);
            zf_electron->AddCutResult("hf_2dloose", HFLOOSE, WEIGHT);
        }
    }

    void ZFinderEvent::InitNTElectrons(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
        // NT Electrons
        edm::Handle<reco::PhotonCollection> els_h;
        iEvent.getByLabel(inputtags_.nt_electron, els_h);

        // Loop over all electrons
        for(unsigned int i = 0; i < els_h->size(); ++i) {
            reco::Photon electron = els_h->at(i);
            // Because the photon collect is NOT filtered for electrons, we
            // reject all electrons outside of the NT region of ECAL.
            if (2.5 < abs(electron.eta()) && abs(electron.eta()) < 2.850) {
                ZFinderElectron* zf_electron = AddRecoElectron(electron);

                // Apply Alexey's Cuts
                //const double PHOTON_ET = electron.superCluster()->rawEnergy() * sin(electron.superCluster()->theta());
                if (       0.89 < electron.r9() && electron.r9() < 1.02
                        && electron.hadronicOverEm() < 0.05
                        && abs(electron.superCluster()->eta()) > 2.5
                        //&& PHOTON_ET > 20.
                        && electron.sigmaIetaIeta() < 0.029
                        && (electron.ecalRecHitSumEtConeDR03() / electron.pt()) < 0.035
                        && (electron.hcalTowerSumEtConeDR03() / electron.pt()) < 0.11
                   ) {
                    const bool PASSED = true;
                    const double WEIGHT = 1.;
                    zf_electron->AddCutResult("nt_loose", PASSED, WEIGHT);
                }
            }
        }
    }

    void ZFinderEvent::InitZ() {
        if (e0 != NULL && e1 != NULL) {
            // Set Z properties
            const double ELECTRON_MASS = 5.109989e-4;
            math::PtEtaPhiMLorentzVector e0lv(e0->pt, e0->eta, e0->phi, ELECTRON_MASS);
            math::PtEtaPhiMLorentzVector e1lv(e1->pt, e1->eta, e1->phi, ELECTRON_MASS);
            math::PtEtaPhiMLorentzVector zlv;
            zlv = e0lv + e1lv;

            reco_z.m = zlv.mass();
            reco_z.y = zlv.Rapidity();
            reco_z.pt = zlv.pt();
            reco_z.phistar = ReturnPhistar(e0->eta, e0->phi, e1->eta, e1->phi);
            reco_z.eta = zlv.eta();
        }
    }

    void ZFinderEvent::InitVariables() {
        // Beamspot
        reco_bs.x = -1000;
        reco_bs.y = -1000;
        reco_bs.z = -1000;

        // Vertexes
        reco_vert.num = -1;
        reco_vert.x = -1000;
        reco_vert.y = -1000;
        reco_vert.z = -1000;
        truth_vert.num = -1;
        truth_vert.x = -1000;
        truth_vert.y = -1000;
        truth_vert.z = -1000;

        // Event ID
        id.run_num = 0;
        id.lumi_num = 0;
        id.event_num = 0;

        // Z Data
        reco_z.m = -1;
        reco_z.y = -1000;
        reco_z.pt = -1;
        reco_z.phistar = -1;
        reco_z.eta = -1000;
        truth_z.m = -1;
        truth_z.y = -1000;
        truth_z.pt = -1;
        truth_z.phistar = -1;
        truth_z.eta = -1000;

        // Electrons
        e0 = NULL;
        e1 = NULL;
        n_reco_electrons = -1;
        e0_truth = NULL;
        e1_truth = NULL;

        // Is Data
        is_real_data = false;
    }

    void ZFinderEvent::InitTruth(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
        /* Count Pile Up */
        edm::Handle<std::vector<PileupSummaryInfo> > pileup_info;
        iEvent.getByLabel(inputtags_.pileup, pileup_info);
        if (pileup_info.isValid()) {
            truth_vert.num = pileup_info->size();
        } else {
            truth_vert.num = -1;
        }

        /*
         * We don't need to select electrons with cuts, because in Monte Carlo we
         * can just ask for the Z.
         */
        edm::Handle<reco::GenParticleCollection> mc_particles;
        iEvent.getByLabel(inputtags_.generator, mc_particles);

        /* Finding the Z and daughter electrons
         *
         * We loop over all gen particles. If it is a Z, we check its daughters
         * until we find an electron, then we know that it is a Z->ee decay. If
         * this is the first Z we save it. If the particle is an electron, we
         * make sure it came from a Z. This might have problems in ZZ->eeee
         * decays, but we expect those to be impossibly rare.
         */
        const reco::GenParticle* electron_0 = NULL;
        const reco::GenParticle* electron_1 = NULL;
        const reco::GenParticle* z_boson = NULL;

        for(unsigned int i = 0; i < mc_particles->size(); ++i) {
            const reco::GenParticle* gen_particle = &mc_particles->at(i);
            // Is a Z
            if (gen_particle->pdgId() == ZBOSON && z_boson == NULL) {
                for (size_t j = 0; j < gen_particle->numberOfDaughters(); ++j) {
                    if (gen_particle->daughter(j)->pdgId() == ELECTRON) {
                        z_boson = gen_particle;
                        break;
                    }
                }
                // Is an electron
            } else if (   fabs(gen_particle->pdgId()) == ELECTRON  // In pdgId, fabs(POSITRON) == ELECTRON
                    && (electron_0 == NULL || electron_1 == NULL)
                    ) {
                for (size_t j = 0; j < gen_particle->numberOfMothers(); ++j) {
                    if (gen_particle->mother(j)->pdgId() == ZBOSON) {
                        if (electron_0 == NULL) {
                            electron_0 = gen_particle;
                        } else {
                            electron_1 = gen_particle;
                        }
                    }
                }
            }
        }

        // Continue only if all particles have been found
        if (z_boson != NULL && electron_0 != NULL && electron_1 != NULL) {
            // We set electron_0 to the higher pt electron
            if (electron_0->pt() < electron_1->pt()) {
                std::swap(electron_0, electron_1);
            }

            // Add electrons
            ZFinderElectron* zf_electron_0 = AddTruthElectron(*electron_0);
            set_e0_truth(zf_electron_0);
            ZFinderElectron* zf_electron_1 = AddTruthElectron(*electron_1);
            set_e1_truth(zf_electron_1);

            // Z Properties
            truth_z.m = z_boson->mass();
            truth_z.pt = z_boson->pt();
            const double ZEPP = z_boson->energy() + z_boson->pz();
            const double ZEMP = z_boson->energy() - z_boson->pz();
            truth_z.y = 0.5 * log(ZEPP / ZEMP);
            truth_z.phistar = ReturnPhistar(electron_0->eta(), electron_0->phi(), electron_1->eta(), electron_1->phi());
            truth_z.eta = z_boson->eta();
        }
    }

    ZFinderElectron* ZFinderEvent::AddRecoElectron(reco::GsfElectron electron) {
        ZFinderElectron* zf_electron = new ZFinderElectron(electron);
        reco_electrons_.push_back(zf_electron);
        return zf_electron;
    }

    ZFinderElectron* ZFinderEvent::AddRecoElectron(reco::RecoEcalCandidate electron) {
        ZFinderElectron* zf_electron = new ZFinderElectron(electron);
        reco_electrons_.push_back(zf_electron);
        return zf_electron;
    }

    ZFinderElectron* ZFinderEvent::AddRecoElectron(reco::Photon electron) {
        ZFinderElectron* zf_electron = new ZFinderElectron(electron);
        reco_electrons_.push_back(zf_electron);
        return zf_electron;
    }

    ZFinderElectron* ZFinderEvent::AddTruthElectron(reco::GenParticle electron) {
        ZFinderElectron* zf_electron = new ZFinderElectron(electron);
        truth_electrons_.push_back(zf_electron);
        return zf_electron;
    }

    double ZFinderEvent::ReturnPhistar(const double& eta0, const double& phi0, const double& eta1, const double& phi1) {
        /* Calculate phi star */
        const double PI = 3.14159265358979323846;
        double dphi = phi0 - phi1;

        // Properly account for the fact that 2pi == 0.
        if (dphi < 0){
            if (dphi > -PI){
                dphi = fabs(dphi);
            }
            if (dphi < -PI) {
                dphi += 2*PI;
            }
        }
        if (dphi > PI){
            dphi = 2*PI - dphi;
        }

        const double DETA = fabs(eta0 - eta1);

        /* PhiStar */
        return ( 1 / cosh( DETA / 2 ) ) * (1 / tan( dphi / 2 ) );
    }

    void ZFinderEvent::PrintCuts(ZFinderElectron* zf_elec) {
        using std::cout;
        using std::endl;
        // Print all the cuts of the given zf_elec
        std::vector<const CutResult*>* cuts = zf_elec->GetAllCuts();
        std::vector<const CutResult*>::const_iterator i_cut;
        for (i_cut = cuts->begin(); i_cut != cuts->end(); ++i_cut) {
            cout << "\t\t" << (*i_cut)->name << ": " << (*i_cut)->passed << endl;
        }
    }

    void ZFinderEvent::PrintElectrons(const bool USE_MC, const bool PRINT_CUTS) {
        using std::cout;
        using std::endl;
        /*
         * Loops over the electrons, and prints out the information about them.
         */
        cout << "Run " << id.run_num;
        cout << " event " << id.event_num;
        if (!USE_MC) {
            cout << " Reco Z Mass " << reco_z.m << std::endl;
            for (std::vector<ZFinderElectron*>::const_iterator i_elec = reco_electrons_.begin(); i_elec != reco_electrons_.end(); ++i_elec) {
                ZFinderElectron* elec = (*i_elec);
                cout << "\tpt: " << elec->pt;
                cout << " eta: " << elec->eta;
                cout << " phi: " << elec->phi << endl;
                if (PRINT_CUTS) { PrintCuts(elec); }
            }
        } else if (USE_MC && !is_real_data) {
            if (e0_truth != NULL && e1_truth != NULL) {
                cout << " Truth Z Mass " << truth_z.m << endl;
                cout << "\tpt: " << e0_truth->pt;
                cout << " eta: " << e0_truth->eta;
                cout << " phi: " << e0_truth->phi << endl;
                if (PRINT_CUTS) { PrintCuts(e0_truth); }
                cout << "\tpt: " << e1_truth->pt;
                cout << " eta: " << e1_truth->eta;
                cout << " phi: " << e1_truth->phi << endl;
                if (PRINT_CUTS) { PrintCuts(e1_truth); }
            }
        }
    }

    std::vector<ZFinderElectron*>* ZFinderEvent::FilteredElectrons() {
        /*
         * Return all electrons
         */
        std::vector<ZFinderElectron*>* tmp_vec = new std::vector<ZFinderElectron*>();
        for (std::vector<ZFinderElectron*>::iterator i_elec = reco_electrons_.begin(); i_elec != reco_electrons_.end(); ++i_elec) {
            tmp_vec->push_back(*i_elec);
        }

        return tmp_vec;
    }

    std::vector<ZFinderElectron*>* ZFinderEvent::FilteredElectrons(const std::string& cut_name) {
        /*
         * Return all electrons that pass a specified cut
         */
        std::vector< ZFinderElectron*>* tmp_vec = new std::vector< ZFinderElectron*>();
        for (std::vector<ZFinderElectron*>::iterator i_elec = reco_electrons_.begin(); i_elec != reco_electrons_.end(); ++i_elec) {
            ZFinderElectron* zfe = (*i_elec);
            if (zfe->CutPassed(cut_name)) {
                tmp_vec->push_back(zfe);
            }
        }

        return tmp_vec;
    }

    bool ZFinderEvent::ZDefPassed(const std::string& NAME) const {
        /*
         * Try to find the ZDef name in the map, if it exists return the pass
         * value, else return false.
         */
        std::map<std::string, cutlevel_vector>::const_iterator it = zdef_map_.find(NAME);
        if (it != zdef_map_.end()) {
            const cutlevel_vector* cuts_vec = &it->second;
            cutlevel_vector::const_iterator v_it;
            bool has_passed = true;
            for (v_it = cuts_vec->begin(); v_it != cuts_vec->end(); ++v_it) {
                has_passed = v_it->second && has_passed;
            }
            return has_passed;
        } else {
            return false;
        }
    }

    void ZFinderEvent::PrintZDefs(const bool VERBOSE) const {
        /*
         * Loop over all ZDefs and print the results.
         */
        using std::cout;
        using std::endl;
        cout << "ZDefinitions:" << endl;
        std::map<std::string, cutlevel_vector>::const_iterator i_map;
        for (i_map = zdef_map_.begin(); i_map != zdef_map_.end(); ++i_map) {
            cout << "\t" << i_map->first << ": ";
            cout << ZDefPassed(i_map->first) << endl;
            // If VERBOSE, print out each cutlevel as well
            if (VERBOSE) {
                const cutlevel_vector* clv = &i_map->second;
                cutlevel_vector::const_iterator i_cutlevel;

                for (i_cutlevel = clv->begin(); i_cutlevel != clv->end(); ++i_cutlevel) {
                    cout << "\t\t" << i_cutlevel->first << ": " << i_cutlevel->second << endl;
                }
            }
        }
    }

    const cutlevel_vector* ZFinderEvent::GetZDef(const std::string& NAME) const {
        std::map<std::string, cutlevel_vector>::const_iterator it = zdef_map_.find(NAME);
        if (it != zdef_map_.end()) {
            return &(it->second);
        } else {
            return NULL;
        }

    }
}  // namespace zf