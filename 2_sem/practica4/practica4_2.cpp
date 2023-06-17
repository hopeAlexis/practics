#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Appliance
{
public:
	virtual void poll() {};
	virtual ~Appliance() {};
};

class ElectricityMonitor : public Appliance
{
private:
	std::string name;
public:
	ElectricityMonitor() = default;
	void setName(std::string& str)
	{
		name = str;
	}
	void poll() override
	{
		std::cout << name << "\n";
	}
};

class DiscreteSignalInputBlock: public Appliance
{
private:
	std::string name;
public:
	DiscreteSignalInputBlock() = default;
	void setName(std::string& str)
	{
		name = str;
	}
	void poll() override
	{
		std::cout << name << "\n";
	}
};

class HeatingControlBlock : public Appliance
{
private:
	std::string name;
public:
	HeatingControlBlock() = default;
	void setName(std::string& str)
	{
		name = str;
	}
	void poll() override
	{
		std::cout << name << "\n";
	}
};




int main()
{
	std::ifstream file; 
	file.open("appliances.txt");
	std::vector<Appliance*> appliances;
	std::string line;
	std::getline(file, line);

	if (line == "Electricity monitors") {
		ElectricityMonitor* electricity = new ElectricityMonitor();
		std::getline(file, line);
		electricity->setName(line);
		appliances.push_back(electricity);
	}
	else if (line == "Discrete signal input blocks") {
		DiscreteSignalInputBlock* signal = new DiscreteSignalInputBlock();
		std::getline(file, line);
		signal->setName(line);
		appliances.push_back(signal);
	}
	else if (line == "Heating control blocks") {
		HeatingControlBlock* heating = new HeatingControlBlock();
		std::getline(file, line);
		heating->setName(line);
		appliances.push_back(heating);
	}
	else {
		std::cout << "No corresponding appliances." << line << std::endl;
	}

	file.close();

	for (Appliance* appliance : appliances)		//for each item in the vector
	{
		std::cout << "1\n";
		appliance->poll();
	}

	//for (int i = 0; i < appliances.size(); i++)
	//{
	//	std::cout << "1\n";
	//	appliances[i]->poll();
	//}

	for (Appliance* device : appliances) 
	{
		delete device;
	}

	return 0;
}