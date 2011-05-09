#ifndef __CLOGFILE
#define __CLOGFILE


#include <stdio.h>
#include "Singleton.hpp"
#include <string>
#include <stdarg.h>


#define MAX_BUFFER 1024
#define L_FAIL false
#define L_OK true
#define g_pLogfile CLogfile::get() //Makro zur einfachen verwendung

enum FONTCOLORS {
	BLACK,
	RED,
	GREEN,
	BLUE,
	PURPLE
};


class CLogfile : public TSingleton<CLogfile> {
	public:
		CLogfile();
		~CLogfile();
		void CreateLogfile	(const char *sLogName);
		void WriteTopic		(const std::string &sTopic, int HeadingSize);
		void Textout		(const std::string &sText); //der ursprung allen übels :P gibt Text ohne Umbruchaus!!!! evtl. privaten....
		void Textout		(int Color, const std::string &sText);
		void Textout		(int Color, bool List, const std::string &sText);
		void fTextout		(const std::string &sText, ...);// zum ausgeben von Variablen
		void fTextout		(int Color, const std::string &sText, ...);
		void fTextout		(int Color, bool List, const std::string &sText, ...);
		void FunctionResult	(const std::string &sName, bool Result);
		void FunctionResult	(const std::string &sName, bool Result, const std::string &sDescribtionText);

	private:
		FILE *m_Logfile;
		
};

#endif
