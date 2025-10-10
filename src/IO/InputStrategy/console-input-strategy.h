/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * Correo: alu0101552392@ull.edu.es
 * @date Oct 10 2025
 * @file console-input-strategy.h
 * @brief Console input strategy implementation
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 */

#ifndef IO_INPUTSTRATEGY_CONSOLE_INPUT_STRATEGY_H_
#define IO_INPUTSTRATEGY_CONSOLE_INPUT_STRATEGY_H_

#include <iostream>

#include "input-strategy.h"

class ConsoleInputStrategy : public InputStrategy {
public:
  std::optional<std::vector<std::string>> readInputs() override;
};

#endif  // IO_INPUTSTRATEGY_CONSOLE_INPUT_STRATEGY_H_