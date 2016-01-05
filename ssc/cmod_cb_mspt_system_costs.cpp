#include "core.h"

#include "csp_system_costs.h"

static var_info _cm_vtab_cb_mspt_system_costs[] = {

	
	
	{ SSC_INPUT,        SSC_NUMBER,      "A_sf",                        "Total reflective solar field area",              "m2",           "",            "heliostat",      "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "site_spec_cost",              "Site improvement cost",                          "$/m2",         "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "heliostat_spec_cost",         "Heliostat field cost",                           "$/m2",         "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.fixed_sf",        "Heliostat field cost fixed",                     "$",            "",            "system_costs",   "*",        "",  "" },
	
	{ SSC_INPUT,        SSC_NUMBER,      "h_tower",                     "Tower height",                                   "m",            "",            "receiver",       "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "H_rec",                       "The height of the receiver",                     "m",            "",            "receiver",       "*",        "",  "" },
    { SSC_INPUT,        SSC_NUMBER,      "helio_height",                "Heliostat height",                               "m",            "",            "receiver",       "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "tower_fixed_cost",            "Tower fixed cost",                               "$",            "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "tower_exp",                   "Tower cost scaling exponent",                    "",             "",            "system_costs",   "*",        "",  "" },
	
	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.receiver.area",   "Receiver area",                                  "m2",           "",            "receiver",       "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "rec_ref_cost",                "Receiver reference cost",                        "$",            "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "rec_ref_area",                "Receiver reference area for cost scale",         "",             "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "rec_cost_exp",                "Receiver cost scaling exponent",                 "",             "",            "system_costs",   "*",        "",  "" },

	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.storage_mwht",    "Storage capacity",                               "MWt-hr",       "",            "TES",            "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "tes_spec_cost",               "Thermal energy storage cost",                    "$/kWht",       "",            "system_costs",   "*",        "",  "" },
	
  	{ SSC_INPUT,        SSC_NUMBER,      "P_ref",                       "Reference output electric power at design condition",  "MWe",    "",            "system_design",  "*",        "",  "" },	
	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.power_block_per_kwe", "Power cycle specific cost",                  "$/kWe",        "",            "system_costs",   "*",        "",  "" },

	{ SSC_INPUT,        SSC_NUMBER,      "bop_spec_cost",               "BOP specific cost",                              "$/kWe",        "",            "system_costs",   "*",        "",  "" },
	
	{ SSC_INPUT,        SSC_NUMBER,      "fossil_spec_cost",            "Fossil system specific cost",                    "$/kWe",        "",            "system_costs",   "*",        "",  "" },

	{ SSC_INPUT,        SSC_NUMBER,      "contingency_rate",            "Contingency for cost overrun",                   "%",            "",            "system_costs",   "*",        "",  "" },

	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.sf.fixed_land_area",   "Fixed land area",                                "acre",         "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "system_capacity",             "Nameplate capacity",                             "kWe",          "",            "system_design",  "*",        "",  "" },    
	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.epc.per_acre",    "EPC cost per acre",                              "$/acre",       "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.epc.percent",     "EPC cost percent of direct",                     "%",            "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.epc.per_watt",    "EPC cost per watt",                              "$/W",          "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.epc.fixed",       "EPC fixed",                                      "$",            "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.plm.per_acre",    "PLM cost per acre",                              "$/acre",       "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.plm.percent",     "PLM cost percent of direct",                     "%",            "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.plm.per_watt",    "PLM cost per watt",                              "$/W",          "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "csp.pt.cost.plm.fixed",       "PLM fixed",                                      "$",            "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "sales_tax_frac",              "Percent of cost to which sales tax applies",     "%",            "",            "system_costs",   "*",        "",  "" },
	{ SSC_INPUT,        SSC_NUMBER,      "sales_tax_rate",              "Sales tax rate",                                 "%",            "",            "system_costs",   "*",        "",  "" },

	{ SSC_OUTPUT,       SSC_NUMBER,      "total_installed_cost",	    "Total installed cost",                           "$",            "",            "system_costs",   "*",        "",  "" },
	
	var_info_invalid };

class cm_cb_mspt_system_costs : public compute_module
{
public:

	cm_cb_mspt_system_costs()
	{
		add_var_info(_cm_vtab_cb_mspt_system_costs);
	}

	void exec() throw(general_error)
	{
		C_mspt_system_costs sys_costs;

		sys_costs.ms_par.A_sf_refl = as_double("A_sf");
		sys_costs.ms_par.site_improv_spec_cost = as_double("site_spec_cost");
		sys_costs.ms_par.heliostat_spec_cost = as_double("heliostat_spec_cost");
		sys_costs.ms_par.heliostat_fixed_cost = as_double("csp.pt.cost.fixed_sf");

		sys_costs.ms_par.h_tower = as_double("h_tower");
		sys_costs.ms_par.h_rec = as_double("H_rec");
		sys_costs.ms_par.h_helio = as_double("helio_height");
		sys_costs.ms_par.tower_fixed_cost = as_double("tower_fixed_cost");
		sys_costs.ms_par.tower_cost_scaling_exp = as_double("tower_exp");

		sys_costs.ms_par.A_rec = as_double("csp.pt.cost.receiver.area");
		sys_costs.ms_par.rec_ref_cost = as_double("rec_ref_cost");
		sys_costs.ms_par.A_rec_ref = as_double("rec_ref_area");
		sys_costs.ms_par.rec_cost_scaling_exp = as_double("rec_cost_exp");

		sys_costs.ms_par.Q_storage = as_double("csp.pt.cost.storage.mwht");
		sys_costs.ms_par.tes_spec_cost = as_double("tes_spec_cost");
		
		sys_costs.ms_par.W_dot_design = as_double("P_ref");
		sys_costs.ms_par.power_cycle_spec_cost = as_double("csp.pt.cost.power_block_per_kwe");

		sys_costs.ms_par.bop_spec_cost = as_double("bop_spec_cost");

		sys_costs.ms_par.fossil_backup_spec_cost = as_double("fossil_spec_cost");

		sys_costs.ms_par.contingency_rate = as_double("contingency_rate");

		sys_costs.ms_par.total_land_area = as_double("csp.pt.sf.fixed_land_area");
		sys_costs.ms_par.plant_net_capacity = as_double("system_capacity");
		sys_costs.ms_par.EPC_land_spec_cost = as_double("csp.pt.cost.epc.per_acre");
		sys_costs.ms_par.EPC_land_perc_direct_cost = as_double("csp.pt.cost.epc.percent");
		sys_costs.ms_par.EPC_land_per_power_cost = as_double("csp.pt.cost.epc.per_watt");
		sys_costs.ms_par.EPC_land_fixed_cost = as_double("csp.pt.cost.epc.fixed");
		sys_costs.ms_par.total_land_spec_cost = as_double("csp.pt.cost.plm.per_acre");
		sys_costs.ms_par.total_land_perc_direct_cost = as_double("csp.pt.cost.plm.percent");
		sys_costs.ms_par.total_land_per_power_cost = as_double("csp.pt.cost.plm.per_watt");
		sys_costs.ms_par.total_land_fixed_cost = as_double("csp.pt.cost.plm.fixed");
		sys_costs.ms_par.sales_tax_basis = as_double("sales_tax_frac");
		sys_costs.ms_par.sales_tax_rate = as_double("sales_tax_rate");

		

		return;
	}

};

DEFINE_MODULE_ENTRY(cb_mspt_system_costs, "CSP molten salt power tower system costs", 0)