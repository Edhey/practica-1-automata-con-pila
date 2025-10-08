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
 * @file state.h
 * @brief Definition of the class State
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <map>
#include <vector>

template <typename KeyType, typename ValueType>
class State {
public:
  State(const std::string& id = "q-1", bool is_final = false,
        bool is_initial = false)
      : id_(id), is_final_(is_final), is_initial_(is_initial) {}
  ~State() = default;

  bool operator<(const State& other) const { return id_ < other.id_; }
  bool operator<(const std::string& other_id) const { return id_ < other_id; }
  bool operator==(const State& other) const { return id_ == other.id_; }
  bool operator==(const std::string& other_id) const { return id_ == other_id; }
  const std::string& getId() const { return id_; }
  void addTransition(const KeyType& key, const ValueType& value) {
    this->transitions_.insert({key, value});
  }
  const std::multimap<KeyType, ValueType>& getTransitions() const {
    return transitions_;
  }

private:
  std::string id_;
  std::multimap<KeyType, ValueType> transitions_;
  bool is_final_ = false;
  bool is_initial_ = false;
};

#endif  // STATE_H