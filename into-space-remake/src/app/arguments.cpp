#include "arguments.h"

#include <algorithm>
#include <iostream>
#include <range.h>

namespace app {
	using namespace sp;

	
	const std::map<BoolArg, std::vector<Tstr>> boolArgs {
		{BoolArg::help, {"-h", "--help"}},
	};
	const std::map<ValueArg, std::vector<Tstr>> valueArgs {
		{ValueArg::verbosity, {"-v=", "--verbosity="}},
		{ValueArg::width, {"-w=", "--width="}},
		{ValueArg::height, {"-h=", "--height="}},
		{ValueArg::zoom, {"-z=", "--zoom="}},
		{ValueArg::doubleClickDelay, {"--dc-delay="}},
		{ValueArg::entitiesPerChunk, {"-e=", "--entities="}},
		{ValueArg::percItems, {"--%items="}},
	};


	Tstr Arguments::errorMessage = "";

	bool Arguments::help = false;

	Gravity Arguments::verbosity = Gravity::critical;
	uint16_t Arguments::width = 480;
	uint16_t Arguments::height = 480;
	float Arguments::zoom = 1.0f;
	float Arguments::doubleClickDelay = 0.5f;
	uint16_t Arguments::entitiesPerChunk = 1;
	uint8_t Arguments::percItems = 50;




	size_t findArg(BoolArg argType, std::vector<Tstr>& arguments) {
		int nrFoundIndices = 0;
		
		for (auto&& argString : boolArgs.at(argType)) {
			while (1) {
				auto index = std::find(arguments.begin(), arguments.end(), argString);
				if (index == arguments.end())
					break;
				else {
					arguments.erase(index);
					++nrFoundIndices;
				}
			}
		}			

		return nrFoundIndices;
	}
	std::pair<int, Tstr> findArg(ValueArg argType, std::vector<Tstr>& arguments) {
		int nrFoundIndices = 0;
		Tstr value;
		
		for (auto&& argString : valueArgs.at(argType)) {
			while (1) {
				auto index = std::find_if(arguments.begin(), arguments.end(), [&argString](const Tstr& arg) { return !arg.compare(0, argString.size(), argString); });
				if (index == arguments.end())
					break;
				else {
					value = index->substr(argString.size());
					arguments.erase(index);
					++nrFoundIndices;
				}
			}
		}

		return {nrFoundIndices, value};
	}
	

	void Arguments::parse(std::vector<Tstr> arguments) {
		help = findArg(BoolArg::help, arguments);


		using ValueFound = std::pair<int, Tstr>;

		//verbosity
		switch (ValueFound fVerbosity = findArg(ValueArg::verbosity, arguments); std::get<int>(fVerbosity)) {
			case 0:
				break;
			case 1: {
				try {
					int tempVerbosity = std::stoi(std::get<Tstr>(fVerbosity));
					if (tempVerbosity < 0 || tempVerbosity > static_cast<int>(Gravity::max))
						throw std::invalid_argument{""};
					verbosity = static_cast<Gravity>(-tempVerbosity + 3);
				}
				catch (const std::invalid_argument&) {
					errorMessage += "Invalid value of argument verbosity\n";
				}
				break;
			}
			default:
				errorMessage += "Argument verbosity used multiple times\n";
		}

		//screen width
		switch (ValueFound fWidth = findArg(ValueArg::width, arguments); std::get<int>(fWidth)) {
			case 0:
				break;
			case 1: {
				try {
					int tempWidth = std::stoi(std::get<Tstr>(fWidth));
					if (tempWidth < 0)
						throw std::invalid_argument{""};
					width = static_cast<uint16_t>(tempWidth);
				}
				catch (const std::invalid_argument&) {
					errorMessage += "Invalid value of argument width\n";
				}
				break;
			}
			default:
				errorMessage += "Argument width used multiple times\n";
		}

		//screen height
		switch (ValueFound fHeight = findArg(ValueArg::height, arguments); std::get<int>(fHeight)) {
			case 0:
				break;
			case 1: {
				try {
					int tempHeight = std::stoi(std::get<Tstr>(fHeight));
					if (tempHeight < 0)
						throw std::invalid_argument{""};
					height = static_cast<uint16_t>(tempHeight);
				}
				catch (const std::invalid_argument&) {
					errorMessage += "Invalid value of argument height\n";
				}
				break;
			}
			default:
				errorMessage += "Argument height used multiple times\n";
		}

		//zoom
		switch (ValueFound fZoom = findArg(ValueArg::zoom, arguments); std::get<int>(fZoom)) {
			case 0:
				break;
			case 1: {
				try {
					float tempZoom = std::stof(std::get<Tstr>(fZoom));
					if (tempZoom < 0.5f || tempZoom > 2.0f)
						throw std::invalid_argument{""};
					zoom = tempZoom;
				}
				catch (const std::invalid_argument&) {
					errorMessage += "Invalid value of argument zoom\n";
				}
				break;
			}
			default:
				errorMessage += "Argument zoom used multiple times\n";
		}

		//doubleClickDelay
		switch (ValueFound fDoubleClickDelay = findArg(ValueArg::doubleClickDelay, arguments); std::get<int>(fDoubleClickDelay)) {
			case 0:
				break;
			case 1: {
				try {
					float tempDoubleClickDelay = std::stof(std::get<Tstr>(fDoubleClickDelay));
					if (tempDoubleClickDelay < 0.0f)
						throw std::invalid_argument{""};
					doubleClickDelay = tempDoubleClickDelay;
				}
				catch (const std::invalid_argument&) {
					errorMessage += "Invalid value of argument doubleClickDelay\n";
				}
				break;
			}
			default:
				errorMessage += "Argument doubleClickDelay used multiple times\n";
		}

		//entitiesPerChunk
		switch (ValueFound fEntitiesPerChunk = findArg(ValueArg::entitiesPerChunk, arguments); std::get<int>(fEntitiesPerChunk)) {
			case 0:
				break;
			case 1: {
				try {
					int tempEntitiesPerChunk = std::stoi(std::get<Tstr>(fEntitiesPerChunk));
					if (tempEntitiesPerChunk < 0)
						throw std::invalid_argument{""};
					entitiesPerChunk = static_cast<uint16_t>(tempEntitiesPerChunk);
				}
				catch (const std::invalid_argument&) {
					errorMessage += "Invalid value of argument entitiesPerChunk\n";
				}
				break;
			}
			default:
				errorMessage += "Argument entitiesPerChunk used multiple times\n";
		}

		//percItems
		switch (ValueFound fPercItems = findArg(ValueArg::percItems, arguments); std::get<int>(fPercItems)) {
			case 0:
				break;
			case 1: {
				try {
					int tempPercItems = std::stoi(std::get<Tstr>(fPercItems));
					if (tempPercItems < 0 || tempPercItems > 255)
						throw std::invalid_argument{""};
					percItems = static_cast<uint8_t>(tempPercItems);
				}
				catch (const std::invalid_argument&) {
					errorMessage += "Invalid value of argument percItems\n";
				}
				break;
			}
			default:
				errorMessage += "Argument percItems used multiple times\n";
		}

		debug(Gravity::info, "Arguments", "Value of help: " + std::to_string(help));
		debug(Gravity::info, "Arguments", "Value of verbosity: " + std::to_string(static_cast<int>(verbosity)));
		debug(Gravity::info, "Arguments", "Value of width: " + std::to_string(width));
		debug(Gravity::info, "Arguments", "Value of height: " + std::to_string(height));
		debug(Gravity::info, "Arguments", "Value of zoom: " + std::to_string(zoom));
		debug(Gravity::info, "Arguments", "Value of doubleClickDelay: " + std::to_string(doubleClickDelay));
		debug(Gravity::info, "Arguments", "Value of entitiesPerChunk: " + std::to_string(entitiesPerChunk));
		debug(Gravity::info, "Arguments", "Value of percItems: " + std::to_string(static_cast<int>(percItems)));
		if (!errorMessage.empty())
			debug(Gravity::error, "Arguments", errorMessage);
	}
}