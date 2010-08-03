#include "ITEM.h"


class itemContainer {
public:
	static itemContainer *GetIF();	// 1
	
	int		m_itemN;
	ITEM	*m_item;

public:
	bool		SetUp();
	void		itemUse(int player,int cardIndex,int activeTarget=-1);	// activeTarget을 함부로 사용하면 100% error
};

