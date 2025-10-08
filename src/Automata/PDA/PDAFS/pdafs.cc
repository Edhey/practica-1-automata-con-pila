/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * Correo: alu0101552392@ull.edu.es
 * @date Oct 06 2025
 * @file pdafs.cc
 * @brief Implementation of the class PDAFS
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#include "pdafs.h"

#include <queue>

/**
 * @brief Configuration of an automaton state during execution
 */
struct Configuration {
  const State<PDATransitionKey, PDATransitionValue>* state;
  std::stack<char> stack;
  size_t input_position;

  Configuration(const State<PDATransitionKey, PDATransitionValue>* s,
                std::stack<char> st, size_t pos)
      : state(s), stack(st), input_position(pos) {}
};

/**
 * @brief Checks if the input string is accepted by the PDA
 * Accepts if it reaches a final state after consuming all input
 * @param input Input string to check
 * @return true if accepted, false otherwise
 */
bool PDAFS::isAccepted(const std::string& input) {
  if (!this->checkInputAlphabet(input)) {
    std::cerr
        << "Error: Input string contains symbols not in the input alphabet"
        << std::endl;
    return false;
  }
  this->resetStack();

  State<PDATransitionKey, PDATransitionValue>* initial_state =
      this->getStateById(this->initial_state);

  if (initial_state == nullptr) {
    std::cerr << "Error: Initial state not found" << std::endl;
    return false;
  }

  // Queue for BFS (breadth-first search) - explores all possible branches
  std::queue<Configuration> queue;
  queue.push(Configuration(initial_state, this->stack, 0));

  while (!queue.empty()) {
    Configuration current = queue.front();
    queue.pop();

    if (current.input_position == input.size()) {
      for (const auto& final_state : final_states) {
        if (final_state == *(current.state)) {
          return true;
        }
      }
    }

    if (current.stack.empty())
      continue;

    char stack_top = current.stack.top();

    if (current.input_position < input.size()) {
      char current_symbol = input[current.input_position];
      PDATransitionKey key{current_symbol, stack_top};

      const auto& transitions = current.state->getTransitions();
      auto range = transitions.equal_range(key);

      for (auto it = range.first; it != range.second; ++it) {
        const PDATransitionValue& transition = it->second;

        std::stack<char> new_stack = current.stack;
        new_stack.pop();

        for (int i = transition.push_string.size() - 1; i >= 0; --i) {
          char symbol = transition.push_string[i];
          if (symbol != PDA::EPSILON) {
            if (!checkStackAlphabet(symbol)) {
              std::cerr << "Error: Stack symbol '" << symbol
                        << "' not in stack alphabet" << std::endl;
              return false;
            }
            new_stack.push(symbol);
          }
        }

        State<PDATransitionKey, PDATransitionValue>* next_state =
            this->getStateById(transition.next_state_id);

        if (next_state != nullptr) {
          queue.push(
              Configuration(next_state, new_stack, current.input_position + 1));
        }
      }
    }

    PDATransitionKey epsilon_key{PDA::EPSILON, stack_top};
    const auto& transitions = current.state->getTransitions();
    auto epsilon_range = transitions.equal_range(epsilon_key);

    for (auto it = epsilon_range.first; it != epsilon_range.second; ++it) {
      const PDATransitionValue& transition = it->second;
      std::stack<char> new_stack = current.stack;
      new_stack.pop();
      for (int i = transition.push_string.size() - 1; i >= 0; --i) {
        char symbol = transition.push_string[i];
        if (symbol != PDA::EPSILON) {
          if (!checkStackAlphabet(symbol)) {
            std::cerr << "Error: Stack symbol '" << symbol
                      << "' not in stack alphabet" << std::endl;
            return false;
          }
          new_stack.push(symbol);
        }
      }
      State<PDATransitionKey, PDATransitionValue>* next_state =
          this->getStateById(transition.next_state_id);
      if (next_state != nullptr) {
        queue.push(
            Configuration(next_state, new_stack, current.input_position));
      }
    }
  }

  return false;
}