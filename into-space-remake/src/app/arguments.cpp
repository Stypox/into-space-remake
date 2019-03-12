#include "arguments.hpp"

#include <stypox/argparser.hpp>

namespace app {
	using stypox::ArgParser;
	using stypox::Option;
	using stypox::SwitchOption;
	using stypox::ManualOption;
	using stypox::HelpSection;
	using stypox::args;

	std::string Arguments::errorMessage = "";

	bool Arguments::help = false;
	bool Arguments::wasd = false;
	bool Arguments::fullscreen = false;

	Gravity Arguments::verbosity = Gravity::critical;
	uint16_t Arguments::width = 480;
	uint16_t Arguments::height = 480;
	uint16_t Arguments::entitiesPerChunk = 1;
	uint8_t Arguments::percItems = 50;
	uint8_t Arguments::percClouds = 20;

	float Arguments::zoom = 1.0f;
	float Arguments::doubleClickDelay = 0.5f;

	std::filesystem::path Arguments::itemsVertexShader = "into-space-remake/src/rend/shader/items.vert";
	std::filesystem::path Arguments::itemsFragmentShader = "into-space-remake/src/rend/shader/items.frag";
	std::filesystem::path Arguments::rectanglesVertexShader = "into-space-remake/src/rend/shader/rectangles.vert";
	std::filesystem::path Arguments::rectanglesFragmentShader = "into-space-remake/src/rend/shader/rectangles.frag";

	stypox::ArgParser parser{
		std::make_tuple(
			HelpSection{"Fly with your customized rocket until you reach the moon!\n\nWindow options:"},
			Option{"width", Arguments::width, args("-w=", "--width="), "window starting width in pixel (default=480)", false, [](auto value){ return value > 0; }},
			Option{"height", Arguments::height, args("-h=", "--height="), "window starting height in pixel (default=480)", false, [](auto value){ return value > 0; }},
			SwitchOption{"fullscreen", Arguments::fullscreen, args("--fullscreen"), "start in fullscreen mode"},
			Option{"zoom", Arguments::zoom, args("-z=", "--zoom="), "game starting zoom (0.5-2.0; default=1.0)", false, [](float value){ return value >= 0.5f && value <= 2.0f; }},
			SwitchOption{"wasd", Arguments::wasd, args("--wasd"), "use WASD instead of arrow keys"},

			HelpSection{"\nGame options:"},
			Option{"entitiesPerChunk", Arguments::entitiesPerChunk, args("-e=", "--entities="), "entities per chunk (default=1)", false, [](auto value){ return value >= 0; }},
			Option{"percItems", Arguments::percItems, args("--%items="), "item generation probability (0-255; default=50)"},
			Option{"percClouds", Arguments::percClouds, args("--%clouds="), "cloud generation probability (0-255; default=20)"},
			Option{"doubleClickDelay", Arguments::doubleClickDelay, args("--dc-delay="), "double click/press delay in seconds (default=0.5)", false, [](int value){ return value >= 0.0f; }},

			HelpSection{"\nTechnical options:"},
			SwitchOption{"help", Arguments::help, args("-?", "-h", "--help"), "shows this screen and exit"},
			ManualOption{"verbosity", Arguments::verbosity, args("-v=", "--verbosity="), "verbosity (0-3; default=0)", [](auto str){
				int value;
				try {
					value = std::stoi(str.data());
				}
				catch (...) {
					throw std::runtime_error{"Option verbosity: \"" + std::string{str} + "\" is not an integer."};
				}
				if (value < 0 || value > 3)
					throw std::runtime_error{"Option verbosity: " + std::to_string(value) + " is not in range 0-3."};
				return static_cast<Gravity>(3 - value);
			}},
			Option{"itemsVertexShader", Arguments::itemsVertexShader, args("--items-vert="), "items vertex shader (default=into-space-remake/src/rend/shader/items.vert)"},
			Option{"itemsFragmentShader", Arguments::itemsFragmentShader, args("--items-frag="), "items fragment shader (default=into-space-remake/src/rend/shader/items.frag)"},
			Option{"rectanglesVertexShader", Arguments::rectanglesVertexShader, args("--rectagles-vert="), "rectangles vertex shader (default=into-space-remake/src/rend/shader/rectangles.vert)"},
			Option{"rectanglesFragmentShader", Arguments::rectanglesFragmentShader, args("--rectagles-frag="), "rectangles fragment shader (default=into-space-remake/src/rend/shader/rectangles.frag)"}
		),
		"Into Space! remake by Stypox",
		21
	};

	void Arguments::parse(int argc, char const* argv[]) {
		try {
			parser.parse(argc, argv);
			parser.validate();
		}
		catch (std::runtime_error& error) {
			errorMessage = error.what();
			debug(Gravity::error, "Arguments", errorMessage);
			return;
		}

		debug(Gravity::info, "Arguments", "Value of help: " + std::to_string(help));
		debug(Gravity::info, "Arguments", "Value of wasd: " + std::to_string(help));
		debug(Gravity::info, "Arguments", "Value of verbosity: " + std::to_string(static_cast<int>(verbosity)));
		debug(Gravity::info, "Arguments", "Value of width: " + std::to_string(width));
		debug(Gravity::info, "Arguments", "Value of height: " + std::to_string(height));
		debug(Gravity::info, "Arguments", "Value of zoom: " + std::to_string(zoom));
		debug(Gravity::info, "Arguments", "Value of doubleClickDelay: " + std::to_string(doubleClickDelay));
		debug(Gravity::info, "Arguments", "Value of entitiesPerChunk: " + std::to_string(entitiesPerChunk));
		debug(Gravity::info, "Arguments", "Value of percItems: " + std::to_string(static_cast<int>(percItems)));
		debug(Gravity::info, "Arguments", "Value of percClouds: " + std::to_string(static_cast<int>(percClouds)));
		debug(Gravity::info, "Arguments", "Value of itemsVertexShader: " + itemsVertexShader.string());
		debug(Gravity::info, "Arguments", "Value of itemsFragmentShader: " + itemsFragmentShader.string());
		debug(Gravity::info, "Arguments", "Value of rectanglesVertexShader: " + rectanglesVertexShader.string());
		debug(Gravity::info, "Arguments", "Value of rectanglesFragmentShader: " + rectanglesFragmentShader.string());
	}
	std::string Arguments::helpScreen() {
		return parser.help();
	}
}