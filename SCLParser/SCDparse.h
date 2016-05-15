#ifndef SCDPARSE_H
#define SCDPARSE_H

#define SHORT_NAME_LENTH     20
#define NAME_LENTH           64
#define LONG_NAME_LENTH      128
#define IP_ADDR_LENTH		4
#define MAC_ADDR_LENTH		6


struct SubNetwork_inf
{
	char SubNetwork_Name[NAME_LENTH];       //子网名称
	char SubNetwork_Type[SHORT_NAME_LENTH]; //子网类型
};

struct IED_inf
{
	char name[NAME_LENTH];     	            //1)	IED名字
	char desc[NAME_LENTH];                  //2)	IED描述
	char type[SHORT_NAME_LENTH];            //3)	IED装置类型
	char manufacturer[NAME_LENTH];          //4)	IED制造厂家
	char configVersion[NAME_LENTH];         //5)	IED配置配置版本
};

struct MMS_Comm_inf
{
	char SubNetwork_Name[NAME_LENTH];        //子网名称
	char MMS_ConnectedAP_IEDName[NAME_LENTH];//1)	IED名字
	char ConnectedAP_apName[SHORT_NAME_LENTH];     //2)	访问点名
	char Address_IP[IP_ADDR_LENTH];          //3)	IP 地址
	char Address_IP_SUBNET[IP_ADDR_LENTH];   //4)	IP子网掩码
	char Address_IP_GATEWAY[IP_ADDR_LENTH];  //5)	IP网关
	char IP_SNTPSERVER[IP_ADDR_LENTH];       //6)	SNTP对时服务器IP
};

struct IED_connect
{
	char ied_name[NAME_LENTH];               //IED名字
	char ref[LONG_NAME_LENTH];               //接收的Reference标识
};

struct DataSet_Fcda_Element
{
	char id[LONG_NAME_LENTH];                //信号标识
	char desc[NAME_LENTH];                   //信号含义	
};

struct SMV_Comm_inf
{
public :
	char SubNetwork_Name[NAME_LENTH];            //子网名称
	char SMV_ConnectedAP_IEDName[NAME_LENTH];    //1)	IED名字
	char ConnectedAP_apName[SHORT_NAME_LENTH];   //2)	访问点名
	char SMV_cbName[NAME_LENTH];                 //1)	SMV关联的控制块名字
	char SMV_ldInst[NAME_LENTH];                 //2)	SMV关联的逻辑设备名字
	char Address_MAC_Address[MAC_ADDR_LENTH];    //3)	SMV关联的MAC组播地址
	unsigned short Address_MAC_VLAN_ID;          //4)	SMV虚拟网ID
	unsigned char  Address_VLAN_PRIORITY;        //5)	SMV虚拟网优先级
	unsigned short Address_APPID;                //6)	SMV应用ID
	unsigned int svc_confRev;                    //7)	SMV控制块配置版本
	char svc_desc[NAME_LENTH];                   //8)	SMV控制块描述
	char svc_ID[NAME_LENTH];                     //9)	SMV控制块ID
	char svc_datSet[NAME_LENTH]; //10)	SMV数据集名称
	unsigned char svc_multicast;           //11)	是否多播
	unsigned char svc_nofASDU;             //12)	SMV控制块ASDU个数
	unsigned int svc_smpRate;             //13)	SMV控制块采样率
	unsigned short ds_element_count;
	struct DataSet_Fcda_Element *m_pDataSet;	    //数据集起始指针，数据个数= ds_element_count 
	unsigned short connect_count;	
	struct IED_connect* m_pIedConnected;        //接收IED的起始指针，数据个数= connect_count

	bool WriteToFile(FILE * pFile)
	{

		if(!pFile)
			return false;

		if(fwrite(SubNetwork_Name,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(SMV_ConnectedAP_IEDName,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(ConnectedAP_apName,SHORT_NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(SMV_cbName,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(SMV_ldInst,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(Address_MAC_Address,MAC_ADDR_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&Address_MAC_VLAN_ID,sizeof(unsigned short),1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&Address_VLAN_PRIORITY,sizeof(char),1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&Address_APPID,sizeof(unsigned short),1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&svc_confRev,sizeof(unsigned int),1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(svc_desc,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(svc_ID,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(svc_datSet,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&svc_multicast,sizeof(char),1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&svc_nofASDU,sizeof(char),1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&svc_smpRate,sizeof(unsigned int),1,pFile) != 1)
		{
			return false;
		}

		//dataset fcda element
		if(fwrite(&ds_element_count,sizeof(unsigned short),1,pFile) != 1)
		{
			return false;
		}
		
		if(ds_element_count >0)
		{
			if(fwrite(m_pDataSet,ds_element_count*sizeof(struct DataSet_Fcda_Element),1,pFile) != 1)
			{
					return false;
			}
		}
		
		//connected ied info
		if(fwrite(&connect_count,sizeof(unsigned short),1,pFile) != 1)
		{
			return false;
		}
		
		if(connect_count >0)
		{
			if(fwrite(m_pIedConnected,connect_count*sizeof(struct IED_connect),1,pFile) != 1)
			{
					return false;
			}
		}

		return true;

	};
};

struct GOOSE_Comm_inf
{
	char SubNetwork_Name[NAME_LENTH];            //子网名称
	char GOOSE_ConnectedAP_IEDName[NAME_LENTH];  //IED名字
	char ConnectedAP_apName[SHORT_NAME_LENTH];    //访问点名
	char GSE_cbName[NAME_LENTH];                 //GSE 关联的控制块名字
	char GSE_ldInst[NAME_LENTH];                 //GSE 关联的逻辑设备名字
	char Address_MAC_Address[MAC_ADDR_LENTH];     //GSE 关联的MAC组播地址
	unsigned short Address_MAC_VLAN_ID;//4)	GSE 虚拟网ID
	unsigned char  Address_VLAN_PRIORITY; //GSE 虚拟网优先级
	unsigned short Address_APPID;//6)	GSE应用ID
	int GSE_MinTime;                             //GSE 最小发送时间
	int GSE_MaxTime;                             //GSE 最大发送时间
	unsigned int gsc_confRev;         //GOOSE控制块配置版本
	char gsc_desc[NAME_LENTH];            //GOOSE控制块描述
	char gsc_appID[NAME_LENTH];           //GOOSE控制块ID
	char gsc_datSet[NAME_LENTH];          //GOOSE数据集名称
	unsigned short ds_element_count;
	struct DataSet_Fcda_Element *m_pDataSet;			//数据集起始指针，数据个数= ds_element_count  
	unsigned short connect_count;
	struct IED_connect* m_pIedConnected;          //接收IED的起始指针，数据个数= connect_count 

	bool WriteToFile(FILE * pFile)
	{

		if(!pFile)
			return false;

		if(fwrite(SubNetwork_Name,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(GOOSE_ConnectedAP_IEDName,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(ConnectedAP_apName,SHORT_NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(GSE_cbName,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(GSE_ldInst,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(Address_MAC_Address,MAC_ADDR_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&Address_MAC_VLAN_ID,sizeof(unsigned short),1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&Address_VLAN_PRIORITY,sizeof(char),1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&Address_APPID,sizeof(unsigned short),1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&GSE_MinTime,sizeof(int),1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(&GSE_MaxTime,sizeof(int),1,pFile) != 1)
		{
			return false;
		}
		
		if(fwrite(&gsc_confRev,sizeof(unsigned int),1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(gsc_desc,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(gsc_appID,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}
		if(fwrite(gsc_datSet,NAME_LENTH,1,pFile) != 1)
		{
			return false;
		}

		//dataset fcda element
		if(fwrite(&ds_element_count,sizeof(unsigned short),1,pFile) != 1)
		{
			return false;
		}
		
		if(ds_element_count >0)
		{
			if(fwrite(m_pDataSet,ds_element_count*sizeof(struct DataSet_Fcda_Element),1,pFile) != 1)
			{
					return false;
			}
		}

		//connected ied info
		if(fwrite(&connect_count,sizeof(unsigned short),1,pFile) != 1)
		{
			return false;
		}
		
		if(connect_count >0)
		{
			if(fwrite(m_pIedConnected,connect_count*sizeof(struct IED_connect),1,pFile) != 1)
			{
					return false;
			}
		}

		return true;

	};
};

struct FILE_VERSION_STRUCT
{
    unsigned short    minor;
    unsigned short    major;
};

struct SCD_inf
{
	struct FILE_VERSION_STRUCT  m_FileVersion;
	unsigned int  magicNumber;          //83097788
	char    stationName[NAME_LENTH];
	
	unsigned short total_SubNetwork_num;
	unsigned short total_IED_num;
	unsigned short total_MMS_num;
	unsigned short total_SMV_Comm_num;
	unsigned short total_GOOSE_Comm_num;
	
	struct SubNetwork_inf*  	m_pSubNetwork_inf;	//起始指针，数据个数= total_SubNetwork_num 
	struct IED_inf*         	m_pIED_inf;					//起始指针，数据个数= total_IED_num 
	struct MMS_Comm_inf*     	m_pMMS_Comm_inf;		//起始指针，数据个数= total_MMS_num 
	struct SMV_Comm_inf*     	m_pSMV_Comm_inf;		//起始指针，数据个数= total_SMV_Comm_num 
	struct GOOSE_Comm_inf*   	m_pGOOSE_Comm_inf;	//起始指针，数据个数= total_GOOSE_Comm_num 
	
	unsigned short checksum;
	unsigned short anti_checksum;
};

#endif
