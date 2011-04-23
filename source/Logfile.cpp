#include "Logfile.hpp"
#include "StringUtils.hpp"
#include <iostream>

using namespace std;


CLogfile::CLogfile() {} //juhu ein leerer constructor!

CLogfile::~CLogfile() {//logfileendeschreiben und schlie�en
	Textout("<br /><br />end of Logfile</body></html>");
	fclose(m_Logfile);
}

void CLogfile::CreateLogfile(const char *sLogName) {
	m_Logfile = fopen(sLogName, "w");
	if (m_Logfile == NULL) {//TODO werden FILES wirklich NULL wenn sie nciht erstellt wurden? ich hoffe schon!
		printf("could not open/create Logfile");
		return ;
	}
	Textout("<html><head><title>Logfile</title></head>");
	Textout("<body style='font-family: Courier;'>");
	WriteTopic("Logfile", 1);

	#ifdef _DEBUG //Debug ist eine vorgefertigte Definition
		Textout("BUILD: DEBUG<br />");
	#else
		Textout("BUILD: RELEASE<br />");
	#endif

	Textout("<a href='mailto:qcd@gmx.net?subject=Logfile'>");
	Textout("Send mail to me!</a><br />");

	//Logfile schlie�en und mit append wieder �ffnen
	fclose (m_Logfile);
	m_Logfile = fopen (sLogName, "a");
	if (m_Logfile == NULL) {
		printf("could not open Logfile");
		return ;
	}
}

static std::string htmlToSimpleOut(const std::string& s) {
	std::string ret;
	std::string tag;
	ret.reserve(s.size());
	int state = 0;
	for(size_t i = 0; i < s.size(); ++i) {
		char c = s[i];
		if(state == 0) {
			if(c == '<') state = 1;
			else ret += c;
		}
		else if(state == 1) {
			if(c == '>') {
			finishTag:
				if(tag == "br" || tag == "br/") ret += '\n';
				else if(tag == "title") ret += "Title: ";
				else if(tag == "/title") ret += "\n";
				else if(tag.size() == 2 && tag[0] == 'h' && '1' <= tag[1] && tag[1] <= '5') ret += std::string(size_t(6 - (tag[1] - '0')), '*') + " ";
				else if(tag.size() == 3 && tag.substr(0,2) == "/h" && '1' <= tag[2] && tag[2] <= '5') ret += " " + std::string(size_t(6 - (tag[2] - '0')), '*') + "\n";
				else if(tag == "a" || tag == "/a") {}
				else if(tag == "/td") ret += " | ";
				else if(tag == "/tr") ret += "\n";
				else if(tag == "li") ret += "* ";
				else if(tag == "/li") ret += "\n";
				else if(tag == "/table") {}
				else if(tag == "/body") ret += "\n";
				tag = "";
				state = 0;
			}
			else if(c == '/') {
				if(tag != "") {
					state = 2;
					goto tagContinued;
				}
				else tag += "/";
			}
			else if(c == ' ') {
				if(tag != "") state = 2;
			}
			else tag += c;
		}
		else if(state == 2) {
		tagContinued:
			if(c == '/') tag += "/";
			else if(c == '>') goto finishTag;
		}
	}
	return ret;
}

void CLogfile::WriteTopic (const std::string &sTopic, int HeadingSize) {//macht ne �berschrift
	fTextout("<h%i>",HeadingSize);
	Textout(sTopic);
	fTextout("</h%i>",HeadingSize);
}

void CLogfile::Textout(const std::string &sText) {
	fprintf(m_Logfile, "%s\n", sText.c_str()); //schreibt den Text in die logfile
	fflush(m_Logfile); //erzwingt das schreiben aller ncoh ausstehenden daten, wenns programm abst�rtzt wei� man wo...
	cout << htmlToSimpleOut(sText) << flush;
}

void CLogfile::Textout(int Color, const std::string &sText) {
	Textout(Color, false, sText); //Trick 17, man beachte das false
}

void CLogfile::Textout(int Color, bool List, const std::string &sText) {
	switch (Color) {
		case BLACK:
			Textout("<div style='color: black'>"); break;
		case RED:
			Textout("<div style='color: red'>"); break;
		case GREEN:
			Textout("<div style='color: green'>"); break;
		case BLUE:
			Textout("<div style='color: blue'>"); break;
		case PURPLE:
			Textout("<div style='color: purple'>"); break;
		default:
			Textout("<div>"); break;
	};
	if (List) Textout("<li>");
	Textout(sText);
	if (List) Textout("</li>");
	Textout("</div>");
	if (!List) Textout("<br />");
}

void CLogfile::fTextout(const std::string &sText, ...) {
	char buffer[MAX_BUFFER];
	va_list pArgList;	//hierrein hauts jetzt die �bergebenen parameter!

	if (sText.length()+1>MAX_BUFFER) {
		FunctionResult("fTextout", L_FAIL, "*Text > MAX_BUFFER!");
		return;
	}
	
	va_start (pArgList, sText); //std::string aus Argumenten erstellen!
	vsprintf(buffer, sText.c_str(), pArgList);
	va_end (pArgList);


	//erzeugten std::string schreiben:
	Textout(buffer);
}

void CLogfile::fTextout(int Color, const std::string &sText, ...) {
	char buffer[MAX_BUFFER];
	va_list pArgList;	//hierrein hauts jetzt die �bergebenen parameter!

	if (sText.length()+1>MAX_BUFFER) {
		FunctionResult("fTextout", L_FAIL, "*Text > MAX_BUFFER!");
		return;
	}
	
	va_start (pArgList, sText); //std::string aus Argumenten erstellen!
	vsprintf(buffer, sText.c_str(), pArgList);
	va_end (pArgList);


	//erzeugten std::string schreiben:
	Textout(Color, buffer);	
}

void CLogfile::fTextout(int Color, bool List, const std::string &sText, ...) {
	char buffer[MAX_BUFFER];
	va_list pArgList;	//hierrein hauts jetzt die �bergebenen parameter!
	fTextout("sizeof=%i",sizeof(sText));
	if (sizeof(sText)>MAX_BUFFER) {
		FunctionResult("fTextout", L_FAIL, "*Text > MAX_BUFFER!");
		return;
	}
	
	va_start (pArgList, sText); //std::string aus Argumenten erstellen!
	vsprintf(buffer, sText.c_str(), pArgList);
	va_end (pArgList);


	//erzeugten std::string schreiben:
	Textout(Color, List, buffer);
}

void CLogfile::FunctionResult(const std::string &sName, bool Result) {
	FunctionResult(sName, Result, "-/-");
}

void CLogfile::FunctionResult(const std::string &sName, bool Result, const std::string &sDescribtionText) {
	
	if (Result == L_OK)
		Textout("<table bgcolor=green>");
	else
		Textout("<table bgcolor=red>");
	Textout("<tr><td>");
	Textout(sName);
	Textout("</td><td>");
	Textout( (Result == L_OK ? "OK" : "ERROR") );
	Textout("</td><td>");
	Textout(sDescribtionText);
	Textout("</td></tr></table>");
}
