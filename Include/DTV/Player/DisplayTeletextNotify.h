#ifndef DISPLAYTELETEXTNOTIFY_H_
#define DISPLAYTELETEXTNOTIFY_H_

#define TELE_START_DISPLAY	0 ////界面开始显示
#define TELE_CAPTION_PAGE	1 ////显示Close Caption页
#define TELE_PAGE_UPDATE	2 ////页面更新
#define TELE_PAGE_FLASH		3 ////一般页数据闪烁
#define TELE_LINK_FLASH		4 ////Link页闪烁
#define TELE_CLEAR_DISPLAY  5 ////Clear Caption Display while Stop decoding.

class DisplayTeletextNotify
{

public:

	DisplayTeletextNotify();
	virtual ~DisplayTeletextNotify();

public:

	virtual void DisplayTeletextNotity ( unsigned int unMsg, void* pvMsgParams ) = 0;

};

#endif /* DISPLAYSUBTITLENOTIFY_H_ */
