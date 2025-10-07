/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * Correo: alu0101552392@ull.edu.es
 * @date Sep 15 2025
 * @file pdaes.h
 * @brief Definition of the class PDAES, a Pushdown Automaton that accepts by
 * Empty Stack
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef PDAES_H
#define PDAES_H

#include <iostream>
#include <stack>

#include "../pda.h"

/**
 * @brief Class for a Pushdown Automaton that accepts by Empty Stack
 */
class PDAES : public PDA {
public:
  virtual ~PDAES() = default;
  bool isAccepted(const std::string& input) override;
  bool isAccepted(const State<PDATransitionKey, PDATransitionValue>* state,
                  std::stack<char> stack, std::string input);
};

#endif  // PDAES_H