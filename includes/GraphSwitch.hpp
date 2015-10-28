#ifndef GRAPH_SWITCH_HPP
# define GRAPH_SWITCH_HPP

# include <IGraphicHandler.hpp>
# include <dlfcn.h>

class GraphSwitch{
	public:
		GraphSwitch(int w, int _h);
		~GraphSwitch(void);
		GraphSwitch(const GraphSwitch & src);
		GraphSwitch &	operator=(GraphSwitch const & rhs);

		void	setGraphic(std::string g);
		IGraphicHandler *graph;
	private:
		GraphSwitch(void);
		std::string _current;
		void 		*_dl_handler;
		IGraphicHandler *(*_create)(int, int);
		int			_w;
		int			_h;
};

#endif