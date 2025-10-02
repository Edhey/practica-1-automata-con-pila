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
 * @file transition.h
 * @brief Definition of the abstract class Transition
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef TRANSITION_H
#define TRANSITION_H

#include <iostream>
#include <string>
#include <vector>
#include "../State/state.h"

class Transition {
 public:
  virtual ~Transition() = default;
  
};

#endif  // TRANSITION_H