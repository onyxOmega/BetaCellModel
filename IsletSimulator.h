#ifndef ISLETSIMULATOR_H
#define ISLETSIMULATOR_H

#include <string>

class IsletSimulator
{
	private:
		std::string userVarMatrix[2][10];
		double ktt, kdd, ktd;
		
	public:
		void initialize(const char *);
		void setUserDefinedVars();
		double get_ktt() const;
		double get_kdd() const;
		double get_ktd() const;
};
#endif