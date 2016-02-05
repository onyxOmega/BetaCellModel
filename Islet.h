#ifndef ISLET_H
#define ISLET_H

#include <string>

class Islet
{
	private:
		std::string userVarMatrix[2][5];
		double ktt, kdd, ktd;
		
	public:
		void initialize(const char *);
		void setUserDefinedVars();
		double get_ktt() const;
		double get_kdd() const;
		double get_ktd() const;
};

#endif