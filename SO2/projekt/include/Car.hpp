#pragma once

struct Car
{
	public:
	Car(bool isFree, int carType, int price, int owner = -1) 
		: m_isFree(isFree)
		, m_carType(carType)
		, m_price(price)
		, m_owner(owner)
	{
	}
	
	bool m_isFree;
	int m_carType;	// from 3 to 9
	int m_price;
	int m_owner;
};
