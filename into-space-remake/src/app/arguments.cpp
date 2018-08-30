#include "arguments.h"

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
	};


	size_t findArg(BoolArg argType, std::vector<Tstr>& arguments) {
		int nrFoundIndices = 0;
		
		for (auto&& argString : boolArgs.at(argType)) {
			while (1) {
				auto index = std::find(arguments.begin(), arguments.end(), argString);
				if (index == arguments.end())
					break;
				else {
					arguments.erase(index, index + 1);
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
					arguments.erase(index, index + 1);
					++nrFoundIndices;
				}
			}
		}

		return {nrFoundIndices, value};
	}
	

	Arguments::Arguments(std::vector<Tstr> arguments) {
		help = findArg(BoolArg::help, arguments);


		using ValueFound = std::pair<int, Tstr>;

		//verbosity
		switch (ValueFound fVerbosity = findArg(ValueArg::verbosity, arguments); std::get<int>(fVerbosity)) {
			case 0:
				break;
			case 1: {
				try {
					int tempVerbosity = std::stoi(std::get<Tstr>(fVerbosity));
					if (tempVerbosity < 0 || tempVerbosity > 3)
						throw std::invalid_argument{""};
					verbosity = static_cast<Tint8>(tempVerbosity);
				}
				catch (const std::invalid_argument&) {
					errorMessage += "Invalid value of argument verbosity\n";
				}
				break;
			}
			default:
				errorMessage += "Argument verbosity used multiple times\n";
		}

		//screen widthdoubleClickDelay
		switch (ValueFound fWidth = findArg(ValueArg::width, arguments); std::get<int>(fWidth)) {
			case 0:
				break;
			case 1: {
				try {
					int tempWidth = std::stoi(std::get<Tstr>(fWidth));
					if (tempWidth < 0)
						throw std::invalid_argument{""};
					width = static_cast<Tint16>(tempWidth);
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
					height = static_cast<Tint16>(tempHeight);
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

		if (verbosity == 3) {
			std::cout << "Help: " << help << "\n"
				<< "Verbosity: " << static_cast<int>(verbosity) << "\n"
				<< "Screen width: " << width << "\n"
				<< "Screen height: " << height << "\n"
				<< "Zoom: " << zoom << "\n"
				<< "DoubleClickDelay: " << doubleClickDelay << "\n"
				<< "Errors:" << "\n" << errorMessage;
		}
	}
}