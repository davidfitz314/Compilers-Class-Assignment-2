#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <fstream>
#include <string>

#include "Token.h"

using namespace std;

class ScannerClass 
{
	public:
		ScannerClass(std::string fileIn);
		~ScannerClass();
		TokenClass GetNextToken();
		TokenClass PeekNextToken();
		int GetLine();	

	private:
		std::ifstream mFin;
		int line;
};


#endif
