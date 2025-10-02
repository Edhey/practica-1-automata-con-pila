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

class State {
public:
  State(const std::string& name, bool is_final = false, bool is_initial = false)
      : name_(name), is_final_(is_final), is_initial_(is_initial) {}
  ~State() = default;

  const std::string& getName() const { return name_; }

  bool operator<(const State& other) const { return name_ < other.name_; }

  bool operator==(const State& other) const { return name_ == other.name_; }

private:
  std::string name_;
  bool is_final_ = false;
  bool is_initial_ = false;
};

#endif // STATE_H