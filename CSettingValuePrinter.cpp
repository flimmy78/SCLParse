#include "CSettingValuePrinter.h"

const int minStep = 5;
CSettingValuePrinter::CSettingValuePrinter(CComTradeFile*pObj):CPrinterObject(pObj)
{
	
}

void CSettingValuePrinter::DoPrinter(QPainter*p)
{



	PrintTitle(p);

	PrintHeader(p);

	PrintTable(p);
}

void CSettingValuePrinter::PrintTitle(QPainter*p)
{
	p->setPen(Qt::black);
	QFont font(QFont("Arial",12));
	p->setFont(font);
	QString strDeviceName = m_pComTrade->GetUnitName();
	strDeviceName+=QString("━设备参数定值");
	int textWidth = p->window().width();
	int maxHeight = p->window().height();
	QFontMetrics metics(font);
	
	int nTitleWidth = metics.width(strDeviceName);
	QRectF rect = p->boundingRect(0,0,textWidth,maxHeight,Qt::AlignCenter,strDeviceName);


	QRectF rect((textWidth-nTitleWidth)/2,0,(textWidth+nTitleWidth)/2,0);
	p->drawText(strDeviceName,rect);
	m_TitleRect = rect;
}

void CSettingValuePrinter::PrintHeader(QPainter*p)
{
	int textWidth = p->window().width();
	int height = m_TitleRect.y()+minStep;
	p->drawLine(0,height,textWidth,height);
	int nStartY = m_TitleRect.bottom+minStep*2;
	int nMaxLength = textWidth/3;
	QString strStation = QString("厂站名:")+m_pComTrade->GetSiteName();
	QRectF rect(0,nStartY,nMaxLength,nStartY);
	p->drawText(strStation,rect);
	
}

void CSettingValuePrinter::PrintTable(QPainter*p)
{

}

