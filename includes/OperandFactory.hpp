/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrassokh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:46:07 by mrassokh          #+#    #+#             */
/*   Updated: 2018/05/09 10:46:09 by mrassokh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include "Operand.hpp"
#include <vector>

class OperandFactory
{
public:
    static OperandFactory* getOperandFactory();

    IOperand const * createOperand(eOperandType type, std::string const & value ) const;

private:
    OperandFactory();
    OperandFactory(OperandFactory const & rhs) = delete;
    OperandFactory & operator = (OperandFactory const & rhs) = delete;
    virtual ~OperandFactory();

    static OperandFactory*       m_operandFactory;

    std::vector<IOperand const* (OperandFactory:: *)(std::string const & value) const>      m_createFunctions;

    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;
};

#endif // OPERANDFACTORY_HPP
