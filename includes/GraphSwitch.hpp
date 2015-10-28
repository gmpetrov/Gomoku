#ifndef GRAPH_SWITCH_HPP
# define GRAPH_SWITCH_HPP

# include <IGraphicHandler.hpp>
# include <dlfcn.h>

class GraphSwitch{
	public:
		GraphSwitch(void);
		~GraphSwitch(void);
		GraphSwitch(const GraphSwitch & src);
		GraphSwitch &	operator=(GraphSwitch const & rhs);

		void	setGraphic(std::string g);
		IGraphicHandler *graph;
	private:
		std::string _current;
		void 		*_dl_handler;
		IGraphicHandler *(*_create)(void);
};

#endif