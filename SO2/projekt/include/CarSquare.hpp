#pragma once

#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <ctime>
#include <SDL2/SDL_mixer.h>

#include "Car.hpp"

class CarSquare
{
	public:
	CarSquare();
	~CarSquare();
	
	void init(unsigned int customers, Mix_Chunk *chung);
	void endThem();
	
	void customerService(int cash, int id);
	void dealerService();
	
	std::vector<Car> getPlaces() const;
	
	unsigned int getCustomersWithCash() const;
	unsigned int getCash() const;
	
	private:
	std::vector<Car> m_places;
	std::vector<std::thread> m_threads;
	const unsigned int m_squareSize = 64;
	unsigned int m_customers;
	const unsigned int m_sleepTime = 100;
	const unsigned int m_creationSleep = 200;
	const unsigned int m_waitTime = 300;
	std::mutex m_customerLock;
	std::mutex m_holdLock;
	unsigned int m_availableCars;
	std::condition_variable m_carsAvailableHere;
	bool m_quit;
	unsigned int m_customerWithCash;
	bool m_start;
	unsigned int m_holdASec;
	int m_dealerBalance = 100000;
	Mix_Chunk *m_ching;
};
