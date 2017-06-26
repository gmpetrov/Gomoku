#include <GraphSwitch.hpp>

GraphSwitch::GraphSwitch(void){
	_dl_handler = NULL;
}

GraphSwitch::~GraphSwitch(void){}

GraphSwitch::GraphSwitch(const GraphSwitch & src){
	*this = src;
}

GraphSwitch &	GraphSwitch::operator=(GraphSwitch const & rhs){
	(void)rhs;
	return *this;
}

void	GraphSwitch::setGraphic(std::string g){

	// if the already used return
	if (g.compare(_current) == 0){ return ; }

	if (_dl_handler){
		graph->close();
		dlclose(_dl_handler);
		_dl_handler = NULL;
	}

	// Open the graphic lib
	//if (!(_dl_handler = dlopen(("/Users/gpetrov/Workspace/Gomoku/lib/" + g + "/lib" + g + ".so").c_str(), RTLD_LOCAL))){
	if (!(_dl_handler = dlopen(("lib/" + g + "/lib" + g + ".so").c_str(), RTLD_LOCAL))){
		std::cerr << "Error : " << dlerror() << std::endl;
		// std::cerr << "[dlopen] : Failed to open library" << std::endl;
		// std::cerr << ("/Users/gpetrov/Workspace/Gomoku/lib/" + g + "/lib" + g + ".so").c_str() << std::endl;
		exit(EXIT_FAILURE);
	}

	// Searching for the create symbol
	if (!(_create = (IGraphicHandler *(*)(void))dlsym(_dl_handler, "create"))){
		std::cerr << "Error : " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}

	// Create a new instance of the grapic lib handler
	graph = _create();

	// setting g as current graphic lib
	_current = g;
}
