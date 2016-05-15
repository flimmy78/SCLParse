#ifndef _TYPE_PRIVATEINFO_H_
#define _TYPE_PRIVATEINFO_H_

#include <list>
#include <memory.h> 
#include <string.h>
#include <stdio.h>

class  Nari_IED
{
public:
	Nari_IED()
	{
		lineNo = -1;
		name = NULL;
		desc = NULL;
	};
	virtual ~Nari_IED(){
	
	}
	char * name;
	char * desc;
	unsigned int lineNo;	

};

typedef std::list<Nari_IED*> ListOfNari_IED;

class  Nari_Bay
{
public:
	Nari_Bay()
	{
		name= NULL;
		lineNo = -1;
	};
	~Nari_Bay()
	{
		ListOfNari_IED::iterator iter = listOfNari_IED.begin();
		for(;iter != listOfNari_IED.end();iter++)
			delete *iter;
	}
	char * name;
	std::list<Nari_IED*> listOfNari_IED;
	unsigned int lineNo;
};
typedef std::list<Nari_Bay*> ListOfNari_Bay; 

class Nari_Voltage
{
public:
	Nari_Voltage()
	{
		lineNo = -1;
		name = NULL;
	}
	virtual ~Nari_Voltage()
	{
		delete []name;
		ListOfNari_Bay::iterator iter = listOfNari_Bay.begin();
		for(;iter != listOfNari_Bay.end();iter++)
			delete *iter;
	}
	char * name;
	std::list<Nari_Bay*>  listOfNari_Bay;
	unsigned int lineNo;
};

typedef std::list<Nari_Voltage*> ListOfVOL; 

class CNariPrivate
{
public:
	CNariPrivate(){
		lineNo = -1;
		type = NULL;
	};
	virtual ~CNariPrivate(){
		delete []type;
	ListOfVOL::iterator iter = listVol.begin();
	for(;iter != listVol.end();iter++)
	delete *iter;
	}
	char * type;
	std::list<Nari_Voltage*> listVol;
	unsigned int lineNo;
};


#endif
