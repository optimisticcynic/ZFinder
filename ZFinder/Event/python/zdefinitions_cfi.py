import FWCore.ParameterSet.Config as cms

MIN_MZ = cms.untracked.double(60.)
MAX_MZ = cms.untracked.double(120.)

# Define common PSets

# All events with at least 2 electrons
all_electrons = cms.untracked.PSet(
        name = cms.untracked.string("All Electrons"),
        cuts0 = cms.untracked.vstring("acc(ALL)"),
        cuts1 = cms.untracked.vstring("acc(ALL)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

# Only the kinematic cuts for the combined muon result, using generator
# quantities
combined_gen_cuts = cms.untracked.PSet(
        name = cms.untracked.string("Combined Gen Cuts"),
        cuts0 = cms.untracked.vstring("gaeta<2.1", "gpt>30"),
        cuts1 = cms.untracked.vstring("gaeta<2.4", "gpt>20"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(True),
        )

# Only the kinematic cuts for the combined muon result, using reco quantities
combined_reco_cuts = cms.untracked.PSet(
        name = cms.untracked.string("Combined Reco Cuts"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "acc(MUON_TIGHT)", "pt>30"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "acc(MUON_LOOSE)", "pt>20"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

# Cuts for the combined muon result assuming a single electron trigger
combined_single = cms.untracked.PSet(
        name = cms.untracked.string("Combined Single"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(single_ele)", "pt>30", "eg_tight", "dr(0.3)"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "acc(ALL)",         "pt>20", "eg_medium", "dr(0.3)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )
        
combined_single_Kinematic_First_NoGsf_NoTrig_NoTight = cms.untracked.PSet(
        name = cms.untracked.string("combined single Kinematic First NoGsf NoTrig NoTight"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "pt>30", "acc(MUON_TIGHT)", "dr(0.3)"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "pt>20", "acc(MUON_LOOSE)", "dr(0.3)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )
        
combined_single_Kinematic_First_NoTrig_NoTight = cms.untracked.PSet(
        name = cms.untracked.string("combined single Kinematic First NoTrig NoTight"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "pt>30", "acc(MUON_TIGHT)", "dr(0.3)", "type_gsf"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "pt>20", "acc(MUON_LOOSE)", "dr(0.3)", "type_gsf"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )
        
combined_single_Kinematic_First_NoTight = cms.untracked.PSet(
        name = cms.untracked.string("combined single Kinematic First NoTight"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "pt>30", "acc(MUON_TIGHT)", "dr(0.3)", "type_gsf", "trig(single_ele)"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "pt>20", "acc(MUON_LOOSE)", "dr(0.3)", "type_gsf", "acc(ALL)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

combined_single_3020 = cms.untracked.PSet(
        name = cms.untracked.string("Combined Single 3020"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(single_ele)", "pt>30", "eg_tight"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "acc(ALL)",         "pt>20", "eg_medium"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )
combined_single_3010 = cms.untracked.PSet(
        name = cms.untracked.string("Combined Single 3010"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(single_ele)", "pt>30", "eg_tight"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "acc(ALL)",         "pt>10", "eg_medium"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

combined_single_3020dr3 = cms.untracked.PSet(
        name = cms.untracked.string("Combined Single 3020dr3"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(single_ele)", "pt>30", "eg_tight", "dr(0.3)"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "acc(ALL)",         "pt>20", "eg_medium", "dr(0.3)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )
combined_single_3010dr3 = cms.untracked.PSet(
        name = cms.untracked.string("Combined Single 3010dr3"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(single_ele)", "pt>30", "eg_tight", "dr(0.3)"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "acc(ALL)",         "pt>10", "eg_medium", "dr(0.3)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

combined_single_low = cms.untracked.PSet(
        name = cms.untracked.string("Combined Single Lowered Threshold"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(single_ele)", "pt>29.91.0", "acc(ALL)"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "acc(ALL)",         "pt>19.94", "acc(ALL)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )


combined_single_high = cms.untracked.PSet(
        name = cms.untracked.string("Combined Single Higher Threshold"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(single_ele)", "pt>30.09", "eg_tight"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "acc(ALL)",         "pt>20.06", "eg_medium"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

combined_single_no_trigger = combined_single.clone(
        name = cms.untracked.string("Combined Single No Trigger"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "pt>30", "eg_tight"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "pt>20", "eg_medium"),
        )

# Cuts for the combined muon result assuming a double electron trigger

combined_double_2010 = cms.untracked.PSet(
        name = cms.untracked.string("Combined Double 2010"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(et_et_tight)", "pt>20", "eg_medium"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "trig(et_et_loose)",  "pt>10", "eg_medium"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False), 
        )

combined_double_2010dr3 = cms.untracked.PSet(
        name = cms.untracked.string("Combined Double 2010dr3"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(et_et_tight)", "pt>20", "eg_medium", "dr(0.3)"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "trig(et_et_loose)",  "pt>10", "eg_medium", "dr(0.3)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )



combined_double_2020 = cms.untracked.PSet(
        name = cms.untracked.string("Combined Double 2020"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(et_et_tight)", "pt>20", "eg_medium"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "trig(et_et_loose)",  "pt>20", "eg_medium"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

combined_double_3020 = cms.untracked.PSet(
        name = cms.untracked.string("Combined Double 3020"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(et_et_tight)", "pt>30", "eg_medium"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "trig(et_et_loose)",  "pt>20", "eg_medium"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

combined_double_2020dr3 = cms.untracked.PSet(
        name = cms.untracked.string("Combined Double 2020dr3"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_TIGHT)", "trig(et_et_tight)", "pt>20", "eg_medium", "dr(0.3)"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "type_gsf", "acc(MUON_LOOSE)", "trig(et_et_loose)",  "pt>20", "eg_medium", "dr(0.3)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

# Cuts needed for "phi* by cut" plot
sequence_plots_0_gen_mass = cms.untracked.PSet(
        name = cms.untracked.string("0 Gen Mass Only"),
        cuts0 = cms.untracked.vstring("acc(ALL)"),
        cuts1 = cms.untracked.vstring("acc(ALL)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(True),
        )

sequence_plots_1_acceptance = cms.untracked.PSet(
        name = cms.untracked.string("1 Acceptance Cuts"),
        cuts0 = cms.untracked.vstring("acc(ALL)", "gpt>30", "gaeta<2.1"),
        cuts1 = cms.untracked.vstring("acc(ALL)", "gpt>20", "gaeta<2.4"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(True),
        )

sequence_plots_2_id = cms.untracked.PSet(
        name = cms.untracked.string("2 ID Cuts"),
        cuts0 = cms.untracked.vstring("type_gsf", "acc(ALL)", "ACC(MUON_TIGHT)", "pt>30", "eg_tight"),
        cuts1 = cms.untracked.vstring("type_gsf", "acc(ALL)", "ACC(MUON_LOOSE)", "pt>20", "eg_medium"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

sequence_plots_3_single_trigger = cms.untracked.PSet(
        name = cms.untracked.string("3 Single Trigger Cuts"),
        cuts0 = cms.untracked.vstring("type_gsf", "acc(ALL)", "ACC(MUON_TIGHT)", "pt>30", "eg_tight",  "trig(single_ele)"),
        cuts1 = cms.untracked.vstring("type_gsf", "acc(ALL)", "ACC(MUON_LOOSE)", "pt>20", "eg_medium", "acc(ALL)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

sequence_plots_3_double_trigger = cms.untracked.PSet(
        name = cms.untracked.string("3 Double Trigger Cuts"),
        cuts0 = cms.untracked.vstring("type_gsf", "acc(ALL)", "ACC(MUON_TIGHT)", "pt>30", "eg_tight",  "trig(et_et_tight)"),
        cuts1 = cms.untracked.vstring("type_gsf", "acc(ALL)", "ACC(MUON_LOOSE)", "pt>20", "eg_medium", "trig(et_et_loose)"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

# Regression Checks
regression_r9_lt_eta_10 = cms.untracked.PSet(
        name = cms.untracked.string("Regression Check R9<0.94 |eta|<1"),
        cuts0 = cms.untracked.vstring("aeta<1", "r9<0.94"),
        cuts1 = cms.untracked.vstring("aeta<1", "r9<0.94"),
        min_mz = MIN_MZ,
        max_mz = MAX_MZ,
        use_truth_mass = cms.untracked.bool(False),
        )

regression_r9_lt_eta_14 = regression_r9_lt_eta_10.clone(
        name = cms.untracked.string("Regression Check R9<0.94 |eta|<1.4"),
        cuts0 = cms.untracked.vstring("aeta>1", "aeta<1.4442", "r9<0.94"),
        cuts1 = cms.untracked.vstring("aeta>1", "aeta<1.4442", "r9<0.94"),
        )

regression_r9_lt_eta_20 = regression_r9_lt_eta_10.clone(
        name = cms.untracked.string("Regression Check R9<0.94 |eta|<2"),
        cuts0 = cms.untracked.vstring("aeta>1.566", "aeta<2", "r9<0.94"),
        cuts1 = cms.untracked.vstring("aeta>1.566", "aeta<2", "r9<0.94"),
        )

regression_r9_lt_eta_25 = regression_r9_lt_eta_10.clone(
        name = cms.untracked.string("Regression Check R9<0.94 |eta|<2.5"),
        cuts0 = cms.untracked.vstring("aeta>2", "aeta<2.5", "r9<0.94"),
        cuts1 = cms.untracked.vstring("aeta>2", "aeta<2.5", "r9<0.94"),
        )

regression_r9_gt_eta_10 = regression_r9_lt_eta_10.clone(
        name = cms.untracked.string("Regression Check R9>0.94 |eta|>1"),
        cuts0 = cms.untracked.vstring("aeta<1", "r9<0.94"),
        cuts1 = cms.untracked.vstring("aeta<1", "r9<0.94"),
        )

regression_r9_gt_eta_14 = regression_r9_lt_eta_10.clone(
        name = cms.untracked.string("Regression Check R9>0.94 |eta|<1.4"),
        cuts0 = cms.untracked.vstring("aeta>1", "aeta<1.4442", "r9<0.94"),
        cuts1 = cms.untracked.vstring("aeta>1", "aeta<1.4442", "r9<0.94"),
        )

regression_r9_gt_eta_20 = regression_r9_lt_eta_10.clone(
        name = cms.untracked.string("Regression Check R9>0.94 |eta|<2"),
        cuts0 = cms.untracked.vstring("aeta>1.566", "aeta<2", "r9<0.94"),
        cuts1 = cms.untracked.vstring("aeta>1.566", "aeta<2", "r9<0.94"),
        )

regression_r9_gt_eta_25 = regression_r9_lt_eta_10.clone(
        name = cms.untracked.string("Regression Check R9>0.94 |eta|<2.5"),
        cuts0 = cms.untracked.vstring("aeta>2", "aeta<2.5", "r9<0.94"),
        cuts1 = cms.untracked.vstring("aeta>2", "aeta<2.5", "r9<0.94"),
        )

# The ZDefinition for use on data for the combined result
zdefs_combined_data = cms.untracked.VPSet(
        all_electrons,
        combined_reco_cuts,
        combined_single,
        #combined_double,
        combined_single_low,
        combined_single_high,
        #regression_r9_lt_eta_10,
        #regression_r9_lt_eta_14,
        #regression_r9_lt_eta_20,
        #regression_r9_lt_eta_25,
        #regression_r9_gt_eta_10,
        #regression_r9_gt_eta_14,
        #regression_r9_gt_eta_20,
        #regression_r9_gt_eta_25,
        )

# The ZDefinition for use on MC for the combined result
zdefs_combined_mc = cms.untracked.VPSet(
        #all_electrons,
        combined_gen_cuts,
        #combined_reco_cuts,
        
	combined_single,
	combined_single_Kinematic_First_NoGsf_NoTrig_NoTight,
	combined_single_Kinematic_First_NoTrig_NoTight,
	combined_single_Kinematic_First_NoTight,
	#combined_single_3020dr3,
	#combined_single_3010dr3,
#        combined_single_low,
 #       combined_single_high,
        #combined_single_no_trigger,
	#combined_double_3020,
     #   combined_double_2020,
	#combined_double_2010,
     #   combined_double_2020dr3,
	#combined_double_2010dr3,
        #sequence_plots_0_gen_mass,
        #sequence_plots_1_acceptance,
        #sequence_plots_2_id,
        #sequence_plots_3_single_trigger,
        #sequence_plots_3_double_trigger,
        #regression_r9_lt_eta_10,
        #regression_r9_lt_eta_14,
        #regression_r9_lt_eta_20,
        #regression_r9_lt_eta_25,
        #regression_r9_gt_eta_10,
        #regression_r9_gt_eta_14,
        #regression_r9_gt_eta_20,
        #regression_r9_gt_eta_25,
        )
