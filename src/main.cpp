/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:43:20 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/09 10:43:22 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVM.hpp"

int main(int argc, char** argv)
{
	AbstractVM::Instance().procesing(argc,argv);
	return (0);
}
