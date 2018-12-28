#include "arguments.h"

namespace app {
	std::string Arguments::errorMessage = "";

	stypox::ArgParser Arguments::m_parser{
		"Into Space! remake by Stypox",
		{
			{"help", "shows this screen and exit", {"-?", "-h", "--help"}},
			{"wasd", "use WASD instead of arrow keys", {"--wasd"}},
			{"fullscreen", "start in fullscreen mode", {"--fullscreen"}},
		}, {
			{"verbosity", "verbosity (0-3; default=0)", {"-v=", "--verbosity="}, 0, [](int value){ return value >= 0 && value <= 3; }},
			{"width", "window starting width in pixel (default=480)", {"-w=", "--width="}, 480, [](int value){ return value > 0; }},
			{"height", "window starting height in pixel (default=480)", {"-h=", "--height="}, 480, [](int value){ return value > 0; }},
			{"entitiesPerChunk", "entities per chunk (default=1)", {"-e=", "--entities="}, 1, [](int value){ return value >= 0; }},
			{"percItems", "item generation probability (0-255), default=50)", {"--%items="}, 50, [](int value){ return value >= 0 && value <= 255; }},
			{"percClouds", "cloud generation probability (0-255), default=20)", {"--%clouds="}, 20, [](int value){ return value >= 0 && value <= 255; }}
		}, {
			{"zoom", "game starting zoom (0.5-2.0; default=1.0)", {"-z=", "--zoom="}, 1.0f, [](float value){ return value >= 0.5f && value <= 2.0f; }},
			{"doubleClickDelay", "double click/press delay in seconds (default=0.5)", {"--dc-delay="}, 0.5f, [](int value){ return value >= 0.0f; }},
		}, {
			{"itemsVertexShader", "items vertex shader (default=into-space-remake/src/rend/shader/items.vert)", {"--items-vert="}, "into-space-remake/src/rend/shader/items.vert"},
			{"itemsFragmentShader", "items fragment shader (default=into-space-remake/src/rend/shader/items.frag)", {"--items-frag="}, "into-space-remake/src/rend/shader/items.frag"},
			{"rectanglesVertexShader", "rectangles vertex shader (default=into-space-remake/src/rend/shader/rectangles.vert)", {"--rectagles-vert="}, "into-space-remake/src/rend/shader/rectangles.vert"},
			{"rectanglesFragmentShader", "rectangles fragment shader (default=into-space-remake/src/rend/shader/rectangles.frag)", {"--rectagles-frag="}, "into-space-remake/src/rend/shader/rectangles.frag"}
		}
	};

	bool Arguments::help{};
	bool Arguments::wasd{};
	bool Arguments::fullscreen{};

	Gravity Arguments::verbosity{};
	uint16_t Arguments::width{};
	uint16_t Arguments::height{};
	uint16_t Arguments::entitiesPerChunk{};
	uint8_t Arguments::percItems{};
	uint8_t Arguments::percClouds{};

	float Arguments::zoom{};
	float Arguments::doubleClickDelay{};

	std::filesystem::path Arguments::itemsVertexShader{};
	std::filesystem::path Arguments::itemsFragmentShader{};
	std::filesystem::path Arguments::rectanglesVertexShader{};
	std::filesystem::path Arguments::rectanglesFragmentShader{};

	void Arguments::parse(int argc, char const* argv[]) {
		try {
			m_parser.parse(argc, argv);
			m_parser.validate();
		}
		catch (std::runtime_error& error) {
			errorMessage = error.what();
			debug(Gravity::error, "Arguments", errorMessage);
			return;
		}

		help = m_parser.getBool("help");
		wasd = m_parser.getBool("wasd");
		fullscreen = m_parser.getBool("fullscreen");

		verbosity = static_cast<Gravity>(3 - m_parser.getInt("verbosity"));
		width = m_parser.getInt("width");
		height = m_parser.getInt("height");
		entitiesPerChunk = m_parser.getInt("entitiesPerChunk");
		percItems = m_parser.getInt("percItems");
		percClouds = m_parser.getInt("percClouds");

		zoom = m_parser.getFloat("zoom");
		doubleClickDelay = m_parser.getFloat("doubleClickDelay");

		itemsVertexShader = m_parser.getText("itemsVertexShader");
		itemsFragmentShader = m_parser.getText("itemsFragmentShader");
		rectanglesVertexShader = m_parser.getText("rectanglesVertexShader");
		rectanglesFragmentShader = m_parser.getText("rectanglesFragmentShader");

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
}