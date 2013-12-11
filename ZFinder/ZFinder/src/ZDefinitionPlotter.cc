#include "ZFinder/ZFinder/interface/ZDefinitionPlotter.h"

// Standard Library
#include <utility>      // std::make_pair
#include <sstream>  // std::ostringstream  


namespace zf {
    // Constructor
    ZDefinitionPlotter::ZDefinitionPlotter(const ZDefinition& zdef, TFileDirectory& tdir, const bool USE_MC) : USE_MC_(USE_MC) {
        // Get the name of the cut we want
        zdef_name = zdef.NAME;
        // Fill zf_ploters
        cutlevel_vector::const_iterator i_cutlevel;
        int counter = 0;
        for (i_cutlevel = zdef.clv.begin(); i_cutlevel != zdef.clv.end(); ++i_cutlevel) {
            const std::string CUT_NAME = i_cutlevel->first;

            // Make a name for our cuts
            std::ostringstream oss;
            oss << counter;
            std::string level_name = oss.str() + " " + CUT_NAME;

            // Make our TFileDirectory for the plotter
            TFileDirectory t_subdir = tdir.mkdir(level_name.c_str(), level_name.c_str());
            ZFinderPlotter zf_plotter(t_subdir, USE_MC_); 
            std::pair<std::string, ZFinderPlotter> new_pair(CUT_NAME, zf_plotter);
            zf_plotters.insert(new_pair);
            ++counter;
        }
    }

    void ZDefinitionPlotter::Fill(const ZFinderEvent& zf_event, const int electron_0, const int electron_1) {
        /*
         * We loop over the cutlevel_vector specified by the name given to use
         * by the zdef in the constructor. We then plot the event until it
         * fails a cut, then we stop.
         */
        const cutlevel_vector* clv = zf_event.GetZDef(zdef_name);
        if (clv != NULL) {
            bool cont = true;
            cutlevel_vector::const_iterator i_cutlevel;
            // Loop over cuts until one fails
            for (i_cutlevel = clv->begin(); i_cutlevel != clv->end(); ++i_cutlevel) {
                const std::string CUT_NAME = i_cutlevel->first;
                cont = i_cutlevel->second && cont;
                // Check if cut fails, if it does break, otherwise fill the
                // histogram associated with the cut
                if (cont) {
                    std::map<std::string, ZFinderPlotter>::iterator i_map = zf_plotters.find(CUT_NAME);
                    if (i_map != zf_plotters.end()) {
                       i_map->second.Fill(zf_event, electron_0, electron_1); 
                    }
                } else {  // We stop at the first failed cut
                    break;
                }
            }
        }
    }

}  // namespace zf
