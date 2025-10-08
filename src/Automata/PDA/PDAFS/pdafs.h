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
 * @file pdafs.h
 * @brief Definition of the class PDAFS, a Pushdown Automaton that accepts by
 * Final State
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef PDAFS_H
#define PDAFS_H

#include <iostream>
#include <queue>
#include <set>

#include "../../State/state.h"
#include "../pda.h"

/**
 * @brief Class for a Pushdown Automaton that accepts by Final State
 */
class PDAFS : public PDA {
public:
  PDAFS() : PDA(), final_states{} {}
  virtual ~PDAFS() = default;
  bool isAccepted(const std::string& input) override;

  const std::set<std::string>& getFinalStates() const { return final_states; }
  void setFinalStates(const std::set<std::string>& states) {
    final_states = states;
  }

private:
  std::set<std::string> final_states;

  struct Configuration {
    const State<PDATransitionKey, PDATransitionValue>* state;
    std::stack<char> stack;
    size_t input_position;
    Configuration(const State<PDATransitionKey, PDATransitionValue>* state,
                  std::stack<char> stack, size_t pos)
        : state(state), stack(std::move(stack)), input_position(pos) {}

    Configuration(const Configuration&) = default;
    Configuration& operator=(const Configuration&) = default;
    ~Configuration() = default;
  };

  bool pushStringOntoStack(std::stack<char>& stack, const std::string& push);
  bool isAcceptingConfiguration(const Configuration& cfg,
                                const std::string& input) const;
  void processInputTransitions(std::queue<Configuration>& q,
                               const Configuration& current,
                               const std::string& input);
  void processEpsilonTransitions(std::queue<Configuration>& q,
                                 const Configuration& current);
};

#endif  // PDAFS_H