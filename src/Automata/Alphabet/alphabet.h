/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * @mail: alu0101552392@ull.edu.es
 * @date Sep 15 2025
 * @file alphabet.h
 * @brief Definition of the class Alphabet
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef AUTOMATA_ALPHABET_ALPHABET_H_
#define AUTOMATA_ALPHABET_ALPHABET_H_

#include <iostream>
#include <set>
#include <string>

template <typename T>
class Alphabet {
public:
  Alphabet() : symbols_() {}
  ~Alphabet() = default;

  void addSymbol(T symbol) {
    auto result = symbols_.insert(symbol);
    if (!result.second) {
      std::cerr << "Warning: Duplicate symbol '" << symbol
                << "' not added to alphabet" << std::endl;
    }
  }
  void removeSymbol(T symbol) { symbols_.erase(symbol); }
  bool contains(T symbol) const { return symbols_.contains(symbol); }
  const std::set<T>& getSymbols() const { return symbols_; }

private:
  std::set<T> symbols_;
};

#endif  // AUTOMATA_ALPHABET_ALPHABET_H_