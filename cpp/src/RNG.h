#pragma once

#include <random>

class RNG {
public:
	virtual double get_random();
	virtual ~RNG() {}
};

// used for tests
class DefaultRNG : public RNG {
public:
	DefaultRNG() {};
	double get_random() override;
};

class MT_RNG : public RNG {
public:
	MT_RNG();
	double get_random() override;
private:
	std::mt19937 _mt;
};
