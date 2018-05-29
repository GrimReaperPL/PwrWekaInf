#include "CarSquare.hpp"

CarSquare::CarSquare()
	: m_availableCars(0)
	, m_quit(false)
	, m_start(false)
	, m_holdASec(100)
	, m_ching(nullptr)
{
	m_places.reserve(m_squareSize);
}

CarSquare::~CarSquare()
{
}

void CarSquare::init(unsigned int customers, Mix_Chunk *chunk)
{
	m_ching = chunk;
	m_customers = customers;
	//need random
	std::srand(time(NULL));
	//car initializations
	for(unsigned int i = 0; i < m_squareSize; i++)
	{
		m_places.push_back(Car(false, (rand() % 7 + 3), (rand() % 15000 + 500)));	//make it rand
		m_availableCars++;
	}
	
	std::cout << "Cars available: " << m_availableCars << "\n";
	
	//threads initializations (customers)
	for(unsigned int i = 0; i < m_customers; i++)
	{
		m_threads.push_back(std::thread(&CarSquare::customerService, this, (rand() % 50000 + 10000), i));
		std::cout << "Created new Thread nr " << i << "\n";
	}
	
	m_customerWithCash = m_customers;
	
	//dealer thread
	m_threads.push_back(std::thread(&CarSquare::dealerService, this));
	std::cout << "Dealer Thread started with nr: " << m_threads.size() - 1 << "\n";
	
	//unlock customers - lets go shopping
	m_start = true;
}

void CarSquare::customerService(int cash, int id)
{	
	int myCash = cash;
	std::cout << "New Customer started working\n";
	while(myCash > 0 && !m_quit)
	{
		int chooseCar = rand() % m_squareSize;
		{
			std::unique_lock<std::mutex> locker(m_customerLock);
			if(m_quit)
				break;
			std::this_thread::sleep_for(std::chrono::milliseconds(m_waitTime));
			while(m_availableCars == 0)
			{
				m_carsAvailableHere.wait(locker, [&](){ return m_availableCars > 0; });
				//std::this_thread::sleep_for(std::chrono::milliseconds(m_waitTime));
			}
			if(m_places[chooseCar].m_isFree || !m_start)	// there is no car
			{
				m_customerLock.unlock();
				continue;	//check another one
			}
			m_places[chooseCar].m_isFree = true;
			m_places[chooseCar].m_owner = id;
			std::cout << "---Customer nr: " << id << "--- I'm buying car nr: " << chooseCar << "\n";
			myCash -= m_places[chooseCar].m_price;
			m_dealerBalance += m_places[chooseCar].m_price;
			Mix_PlayChannel(-1, m_ching, 0);
			m_availableCars--;
			m_customerLock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(m_waitTime*2));
			m_customerLock.lock();
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(m_sleepTime));
	}
	
	std::cout << "---Customer nr: " << id << " out of cash\n";
	m_customerWithCash--;
}

void CarSquare::dealerService()
{
	std::cout << "Getting new cars...\n";
	while(!m_quit)
	{
		if(m_availableCars < (m_squareSize/2))	//keep the cars cool
		{
			std::unique_lock<std::mutex> locker(m_customerLock);
			for(unsigned int i = 0; i < m_squareSize; i++)	//import some cars!
			{
				int choice = rand() % 2;
				if(choice == 1)
				{
					m_places[i].m_isFree = false;
					m_places[i].m_price = (rand() % 15000 + 500);
					m_places[i].m_owner = -1;
					m_dealerBalance -= m_places[i].m_price;
					m_availableCars++;
					std::cout << "Dealer adding new car at: " << i << "\n";
				}
				else
					continue;
			}
			locker.unlock();
			m_carsAvailableHere.notify_all();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(m_sleepTime));
	}
}

unsigned int CarSquare::getCustomersWithCash() const
{
	return m_customerWithCash;
}

unsigned int CarSquare::getCash() const
{
	return m_dealerBalance;
}

void CarSquare::endThem()
{
	unsigned int i = 0;
	m_quit = true;	//stop the dealer
	for (std::vector<std::thread>::iterator it = m_threads.begin() ; it != m_threads.end(); ++it)
	{
		(*it).join();
		std::cout << "Thread nr " << i << " ended\n";
		++i;
	}
}

std::vector<Car> CarSquare::getPlaces() const
{
	return m_places;
}
