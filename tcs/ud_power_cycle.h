#ifndef __UD_POWER_CYCLE_
#define __UD_POWER_CYCLE_

#include "interpolation_routines.h"
#include "csp_solver_util.h"

class C_ud_power_cycle
{

private:
	
	// Each Linear_Interp Table in C_user_defined_pc shares the following column structure:

	//    Independent |    Gross Power Output   |   HTF Thermal Power	|   Cooling Parasitics  |	 Water Use 
	// 0)  Variable   |  1) -   2) 0     3) +   |  4) -   5) 0    6) +  |  7) -    8) 0    9) + | 10) -  11) 0   12) + 

	enum E_output_order
	{
		i_W_dot_gross = 0,
		i_Q_dot_HTF,
		i_W_dot_cooling,
		i_m_dot_water
	};

	// Lookup table with dependent variables corresponding to parametric on independent variable T_htf_hot [C] (first column)
	Linear_Interp mc_T_htf_ind;		// At m_dot_htf levels

	// Lookup table with dependent variables corresponding to parametric on independent variable T_amb [C] (first column)
	Linear_Interp mc_T_amb_ind;		// At T_htf levels

	// Lookup table with dependent variables corresponding to parametric on independent variable m_dot_htf [ND] (first column)
	Linear_Interp mc_m_dot_htf_ind;	// At T_amb levels

	// Initialization will create three new interpolation tables for interaction effects
	
	//    Independent |   Gross Power Output   |   HTF Thermal Power  |   Cooling Parasitics   |	 Water Use        |
	// 0)  Variable   |  1) lower   2) upper   |  3) lower  4) upper  |  5) lower   6) upper   |  7) lower  8) upper  |

	
	Linear_Interp mc_T_htf_on_T_amb;		// rows = rows of T_amb
	Linear_Interp mc_T_amb_on_m_dot_htf;	// rows = rows of m_dot_htf
	Linear_Interp mc_m_dot_htf_on_T_htf;	// rows = rows of T_htf

	// member string for exception messages
	std::string m_error_msg;

	double get_interpolated_ND_output(int i_ME /*M.E. table index*/, double T_htf_hot /*C*/, double T_amb /*C*/, double m_dot_htf_ND /*-*/);

	double m_T_htf_ref;		//[C] Reference (design) HTF inlet temperature
	double m_T_htf_low;		//[C] Low level HTF inlet temperature (in T_amb parametric)
	double m_T_htf_high;	//[C] High level HTF inlet temperature (in T_amb parametric)

	double m_m_dot_htf_ref;		//[-] Reference (design) HTF mass flow rate
	double m_m_dot_htf_low;		//[-] Low level HTF mass flow rate (in T_HTF parametric)
	double m_m_dot_htf_high;	//[-] High level HTF mass flow rate (in T_HTF parametric)

	double m_T_amb_ref;		//[C] Reference (design) ambient temperature
	double m_T_amb_low;		//[C] Low level ambient temperature (in m_dot_htf parametric)
	double m_T_amb_high;	//[C] High level ambient temperature (in m_dot_htf parametric)

	// Can also save main effects of each independent variable at its upper and lower levels
	std::vector<double> m_ME_T_htf_low;		//[-]
	std::vector<double> m_ME_T_htf_high;	//[-]

	std::vector<double> m_ME_T_amb_low;		//[-]
	std::vector<double> m_ME_T_amb_high;	//[-]

	std::vector<double> m_ME_m_dot_htf_low;		//[-]
	std::vector<double> m_ME_m_dot_htf_high;	//[-]

public:

	C_ud_power_cycle(){};

	~C_ud_power_cycle(){};

	void init(const util::matrix_t<double> & T_htf_ind, double T_htf_ref /*C*/, double T_htf_low /*C*/, double T_htf_high /*C*/,
		const util::matrix_t<double> & T_amb_ind, double T_amb_ref /*C*/, double T_amb_low /*C*/, double T_amb_high /*C*/,
		const util::matrix_t<double> & m_dot_htf_ind, double m_dot_htf_ref /*-*/, double m_dot_htf_low /*-*/, double m_dot_htf_high /*-*/);

	double get_W_dot_gross_ND( double T_htf_hot /*C*/, double T_amb /*C*/, double m_dot_htf_ND /*-*/);

	double get_Q_dot_HTF_ND(double T_htf_hot /*C*/, double T_amb /*C*/, double m_dot_htf_ND /*-*/);

	double get_W_dot_cooling_ND(double T_htf_hot /*C*/, double T_amb /*C*/, double m_dot_htf_ND /*-*/);

	double get_m_dot_water_ND(double T_htf_hot /*C*/, double T_amb /*C*/, double m_dot_htf_ND /*-*/);

};





#endif