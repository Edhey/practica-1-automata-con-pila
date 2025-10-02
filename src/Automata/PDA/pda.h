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
 * @file automata.h
 * @brief Definition of the class PDA
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef PDA_H
#define PDA_H

#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#include "../Automata/Automata.h"
#include "../../State/state.h"

struct PDATransition {
  State next_state;
  std::string stack_push;

  PDATransition(const State& state, const std::string& push)
      : next_state(state), stack_push(push) {}
};

using TransitionKey = std::tuple<State, char, char>;

class PDA : public Automata {
public:
  virtual ~PDA() = default;
  virtual bool isAccepted(const std::string& input) override;
  void setStates(const std::vector<State>& states) {
    this->states = std::set<State>(states.begin(), states.end());
  }
  void setInputAlphabet(const std::set<char>& alphabet) { this->input_alphabet = alphabet; }
  void setStackAlphabet(const std::set<char>& alphabet) { this->stack_alphabet = alphabet; }
  void setInitialState(const State& state) { this->initial_state = state; }
  void setInitialStackSymbol(char symbol) { this->initial_stack_symbol = symbol; }
  void addTransition(const State& current_state, char input_symbol, char stack_top,
                     const State& next_state, const std::string& push_string) {
    TransitionKey key = std::make_tuple(current_state, input_symbol, stack_top);
    PDATransition transition(next_state, push_string);
    transitions.insert({key, transition});
  }

protected:
  std::stack<char> stack;
  std::set<char> stack_alphabet;
  char initial_stack_symbol;
  std::multimap<TransitionKey, PDATransition> transitions;
};

#endif