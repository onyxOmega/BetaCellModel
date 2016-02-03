#ifndef NEWBETACELL_H
#define NEWBETACELL_H

class BetaCell
{
	private:
		double dxdt[30];
		double x[30];
		
		double pKATP;
		double gKATPar;
		double IKATPvec;
		double gCoup;
		double gKtoar;
		double PCaERar;
		double gKCaBKar;
		double ATPar;
		double PNACAar;
		double Prelar;
		double Popar;
		double KRev;
		double gChR2;
		double RandomSeed;
		double Vm;
		double Nai;
		double Ki;
		double Cai;
		double Caer;
		double ATP;
		double MgADP;
		double Re;
		double q_KDr;
		double d_CaL;
		double U_CaL;
		double fus;
		double p_KDr;
		double m_Kto;
		double h_Kto;
		double E1_tota;
		double I1;
		double I2;
		double O1;
		double O2;
		double C1;
		double C2;
		
		// exocytosis variables
		double IRP;
		double PP;
		double DP;
		double RES;
		double FIP;
		double RIP;
		double Cap;
		
		// noise
		double Pns;
		
	public:
		void Initialize();
		void Calc_Intermediates();							// perform intermediate calculations
		void Calc_dxdt();										// calculate dxdt
		void linear_approximation();						// add dxdt to the current x value
};

#endif
