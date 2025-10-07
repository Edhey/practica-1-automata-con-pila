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
 * @file AutomataFactory.h
 * @brief Header file for the abstract class AutomataFactory
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef AUTOMATAFACTORY_AUTOMATAFACTORY_H_
#define AUTOMATAFACTORY_AUTOMATAFACTORY_H_

#include <memory>
#include "../Automata/automata.h"

/**
 * @brief Base abstract class for automata factories
 */
template <typename TransitionKey, typename TransitionValue>
class AutomataFactory {
public:
  AutomataFactory() = default;
  virtual ~AutomataFactory() = default;
  virtual std::unique_ptr<Automata<TransitionKey, TransitionValue>> CreateAutomaton() = 0;
};

#endif  // AUTOMATAFACTORY_AUTOMATAFACTORY_H_