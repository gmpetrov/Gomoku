/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/10 12:44:42 by gpetrov           #+#    #+#             */
/*   Updated: 2015/10/10 13:09:45 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_HPP
# define BOARD_HPP

# include <iostream>
# include <string>
# include <Enums.hpp>
# include <vector>
# include <IGraphicHandler.hpp>
# include <stdlib.h>
# include <time.h>

# define BOARD_SIZE 19

class Board{
	public:
		Board(int width, int height);
		~Board(void);
		Board(const Board & src);
		Board &	operator=(Board const & rhs);

		void quit();
		std::vector<std::vector<eBlock>> getMap(void);
		void initMap(void);
		void drawMap(IGraphicHandler *graph);
		void updateMap(void);
		void move(void);
		void handleKey(eKeys);

		bool isAlive;
		int  getScore() const;
	private:
		Board(void);

		int	_width;
		int _height;

		std::vector<std::vector<eBlock>> _map;

		time_t _elapsedTime;
};

#endif