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
 * @see
 * Historial de revisiones:
 */

#ifndef STATE_H
#define STATE_H

#include <iostream>

class State {
 public:
  State() = default;
  explicit State(const std::string& name) : name_(name) {}
  ~State() = default;

  std::string getName() const { return name_; }
  void setName(const std::string& name) { name_ = name; }

 private:
  std::string name_;
};

#endif