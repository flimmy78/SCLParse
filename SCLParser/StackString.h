#ifndef _STACK_STRING_INCLUDE_
#define _STACK_STRING_INCLUDE_

#define STACT_MAX_SIZE 30
#define STRING_MAX_SIZE 50




class StackString
{
protected:
	char data[STACT_MAX_SIZE][STRING_MAX_SIZE];
	char typeData[STACT_MAX_SIZE][STRING_MAX_SIZE];
	int top;
	int typeTop;
	char m_ref[256];
	int m_nSeePos;
	int m_nTypePos;

public:
	StackString()
	{
		memset(data,0,STACT_MAX_SIZE*STRING_MAX_SIZE);
		memset(typeData,0,STACT_MAX_SIZE*STRING_MAX_SIZE);
		strcpy(m_ref,"");
		top= -1;
		typeTop = -1;
		m_nSeePos= 0;
		m_nTypePos = 0;
		
		
	};
	
	~StackString()
	{
		/*
		for(int i=0;i< STACT_MAX_SIZE-1;i++)
			delete data[i];*/
	};

	int  IsEmpty()
	{
		return (top == -1);
	};

	int  IsTypeEmpty()
	{
		return (typeTop == -1);
	};

	void push(const char* str)
	{
		top++;
		if(top < STACT_MAX_SIZE)
		{
			memset(data+top,0,STRING_MAX_SIZE);
			strncpy(data[top],str,STRING_MAX_SIZE);
		}
		else
		{
			top--;
		}
		
	};

	void pushType(const char* str)
	{
		typeTop++;
		if(typeTop < STACT_MAX_SIZE)
		{
			memset(typeData+typeTop,0,STRING_MAX_SIZE);
			strncpy(typeData[typeTop],str,STRING_MAX_SIZE);
		}
		else
		{
			typeTop--;
		}

	};

	char* pop()
	{
		if(top == -1)
			return NULL;
		top--;
		return data[top+1];
	};

	char* popType()
	{
		if(typeTop == -1)
			return NULL;
		typeTop--;
		return typeData[typeTop+1];
	};


	char* ref()
	{
		strcpy(m_ref,"");
		for(int i=0;i<=top;i++)
		{
			strcat(m_ref,data[i]);
			if(i != top)
				strcat(m_ref,".");
		}

		return m_ref;
	};

	bool stackIsContains(char* str)
	{
		bool flag = false;
		for(int i=0;i<=top;i++)
		{
			char* temp;
			strcpy(temp,data[i]);
			if(strcmp(str,temp)==0){
				flag = true;
				break;
			}			
		}
		return flag;
	};

	void ResetSee()
	{
		m_nSeePos = 0;
	}

	void ResetTypeSee()
	{
		m_nTypePos = 0;
	}

	char* see()
	{
		if(IsEmpty())
			return NULL;

		if(m_nSeePos <= top )
		{
			m_nSeePos++;
				return data[m_nSeePos-1];
			
		}
		else
		{
			return NULL;
		}
	}

	char* typeSee()
	{
		if(IsEmpty())
			return NULL;

		if(m_nTypePos <= typeTop )
		{
			m_nTypePos++;
			return typeData[m_nTypePos-1];

		}
		else
		{
			return NULL;
		}
	}

};



#endif