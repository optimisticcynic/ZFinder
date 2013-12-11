#ifndef ZFINDER_ZFINDEREVENT_H_
#define ZFINDER_ZFINDEREVENT_H_

// Standard Library
#include <map>  // std::map
#include <string>  // std::string
#include <utility>  // std::pair
#include <vector>  // std::vector

// CMSSW
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"  // reco::GsfElectron
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"  // reco::GenParticle
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"  // reco::RecoEcalCandidate
#include "FWCore/Framework/interface/Event.h"  // edm::Event, edm::EventSetup
#include "FWCore/ParameterSet/interface/ParameterSet.h"  // edm::ParameterSet
#include "FWCore/Utilities/interface/InputTag.h"  // edm::InputTag

// ZFinder
#include "ZFinder/ZFinder/interface/ZFinderElectron.h"  // ZFinderElectron, ZFinderElectron

namespace zf {

    typedef std::vector<std::pair<std::string, bool> > cutlevel_vector;

    class ZFinderEvent{
        public:
            // Constructor. Although iEvent, iSetup, and iConfig violate our naming
            // convention, they are almost ubiquitous in CMSSW code
            ZFinderEvent(
                    const edm::Event& iEvent,
                    const edm::EventSetup& iSetup,
                    const edm::ParameterSet& iConfig
                    );

            // Data or MC
            bool is_real_data;

            // Beam Spot
            struct Beamspot{
                double x;
                double y;
                double z;
            } reco_bs;

            // Primary vertexes
            struct Vertexes{
                unsigned int num;
                double x;
                double y;
                double z;
            } truth_vert, reco_vert;

            // Event ID
            struct EventID{
                unsigned int run_num;
                unsigned int lumi_num;
                unsigned int event_num;
            } id;

            // Z Data
            struct ZData{
                double m;
                double pt;
                double y;
                double phistar;
            } reco_z, truth_z;

            // These are the special, selected electrons used to make the Z
            ZFinderElectron* e0;
            ZFinderElectron* e1;
            void set_e0(ZFinderElectron* electron) { e0 = electron; }
            void set_e1(ZFinderElectron* electron) { e1 = electron; }
            void set_both_e(ZFinderElectron* electron0, ZFinderElectron* electron1) { e0 = electron0; e1 = electron1; }
            ZFinderElectron* e0_truth;
            ZFinderElectron* e1_truth;
            void set_e0_truth(ZFinderElectron* electron) { e0_truth = electron; }
            void set_e1_truth(ZFinderElectron* electron) { e1_truth = electron; }
            void set_both_e_truth(ZFinderElectron* electron0, ZFinderElectron* electron1) { e0_truth = electron0; e1_truth = electron1; }

            // Access pruned lists of the internal electrons
            std::vector<ZFinderElectron*>* FilteredElectrons();
            std::vector<ZFinderElectron*>* AllElectrons() { return FilteredElectrons(); };
            std::vector<ZFinderElectron*>* FilteredElectrons(const std::string& cut_name);

            // Number of Electrons
            int n_reco_electrons;

            // Output
            void PrintElectrons(const bool USE_MC = false, const bool PRINT_CUTS = false);
            void PrintTruthElectrons(const bool PRINT_CUTS = false) { PrintElectrons(true, PRINT_CUTS); };
            void PrintRecoElectrons(const bool PRINT_CUTS = false) { PrintElectrons(false, PRINT_CUTS); };

            // Access ZDefinition information
            void AddZDef(const std::string NAME, cutlevel_vector PASS_OBJ) { zdef_map_[NAME] = PASS_OBJ; };
            const cutlevel_vector* GetZDef(const std::string& NAME) const;
            bool ZDefPassed(const std::string& NAME) const;
            void PrintZDefs(const bool VERBOSE = false) const;

        protected:
            // Called by the constructor to handle MC and Data separately
            void InitReco(const edm::Event& iEvent, const edm::EventSetup& iSetup);
            void InitTruth(const edm::Event& iEvent, const edm::EventSetup& iSetup);

            void InitGSFElectrons(const edm::Event& iEvent, const edm::EventSetup& iSetup);
            void InitHFElectrons(const edm::Event& iEvent, const edm::EventSetup& iSetup);

            // Update the Z Info from e0, e1
            void InitZ();

            // Initialize all variables to safe values
            void InitVariables();

            // Input tags
            struct InputTags{
                edm::InputTag ecal_electron;
                edm::InputTag conversion;
                edm::InputTag beamspot;
                edm::InputTag rho_iso;
                edm::InputTag vertex;
                edm::InputTag pileup;
                edm::InputTag generator;
                std::vector<edm::InputTag> iso_vals;
                edm::InputTag hf_electron;
                edm::InputTag hf_clusters;
            } inputtags_;

            // A list of all electrons, split into reco and gen
            std::vector<ZFinderElectron*> reco_electrons_;
            ZFinderElectron* AddRecoElectron(reco::GsfElectron electron);
            ZFinderElectron* AddRecoElectron(reco::RecoEcalCandidate electron);

            std::vector<ZFinderElectron*> truth_electrons_;
            ZFinderElectron* AddTruthElectron(reco::GenParticle electron);

            // Calculate phistar
            static double ReturnPhistar(const double& eta0, const double& phi0, const double& eta1, const double& phi1);

            // Sorting functions
            static bool SortByPTHighLow(const ZFinderElectron* e0, const ZFinderElectron* e1) { return (e0->pt > e1->pt); }

            // Print cuts
            void PrintCuts(ZFinderElectron* zf_elec);

            // Store ZDefinition Information
            std::map<std::string, cutlevel_vector> zdef_map_;

    };
}  // namespace zf
#endif  // ZFINDER_ZFINDEREVENT_H_
