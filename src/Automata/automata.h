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
 * @brief Definition of the abstract class Automata
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <set>
#include <string>

#include "Alphabet/alphabet.h"
#include "State/state.h"

/**
 * @brief Abstract class for automata (automaton interface)
 */
template <typename KeyType, typename ValueType>
class Automata {
public:
  Automata() : initial_state{}, states{}, input_alphabet{} {}
  virtual ~Automata() = default;
  virtual bool isAccepted(const std::string& input) = 0;
  static constexpr char EPSILON = '.';
  void setInitialState(const std::string& state) { initial_state = state; }
  void setStates(
      const std::map<std::string, State<KeyType, ValueType>>& states_set) {
    states = states_set;
  }
  void setInputAlphabet(const Alphabet<char>& alphabet) {
    input_alphabet = alphabet;
  }
  State<KeyType, ValueType>* getStateById(const std::string& id);
  bool checkInputAlphabet(const std::string& input);

protected:
  // State current_state;
  std::string initial_state;
  // std::set<State<KeyType, ValueType>> states;
  std::map<std::string, State<KeyType, ValueType>> states;
  Alphabet<char> input_alphabet;
};

template <typename KeyType, typename ValueType>
inline State<KeyType, ValueType>* Automata<KeyType, ValueType>::getStateById(
    const std::string& id) {
  auto it = states.find(id);
  if (it != states.end()) {
    return &it->second;
  }
  return nullptr;
}

template <typename KeyType, typename ValueType>
inline bool Automata<KeyType, ValueType>::checkInputAlphabet(
    const std::string& input) {
  for (const char& symbol : input) {
    if (!input_alphabet.contains(symbol) && symbol != EPSILON) {
      return false;
    }
  }
  return true;
}

#endif  // AUTOMATA_H