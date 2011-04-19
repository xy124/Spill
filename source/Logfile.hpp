#ifndef __CLOGFILE
#define __CLOGFILE


#include <stdio.h>
#include "Singleton.hpp"
#include <string>


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
		void CreateLogfile	(const char *LogName);
		void WriteTopic		(const std::string Topic, int HeadingSize);
		void Textout		(const std::string Text); //der ursprung allen übels :P gibt Text ohne Umbruchaus!!!! evtl. privaten....
		void Textout		(int Color, const std::string Text);
		void Textout		(int Color, bool List, const std::string Text);
		void fTextout		(const std::string Text, ...);// zum ausgeben von Variablen
		void fTextout		(int Color, const std::string Text, ...);
		void fTextout		(int Color, bool List, const std::string Text, ...);
		void FunctionResult	(const std::string Name, bool Result);
		void FunctionResult	(const std::string Name, bool Result, const std::string DescribtionText);

	private:
		FILE *m_Logfile;
		
};

#endif
