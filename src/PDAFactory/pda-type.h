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
 * @file pda-type.h
 * @brief Enum for different pushdown automata types
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef PDA_TYPE_H_
#define PDA_TYPE_H_

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>

/**
 * @brief Enum for different pushdown automata types
 */
enum class AutomataType { PDAES, PDAFS };

/**
 * @brief Helper class for AutomataType
 */
class AutomataTypeHelper {
public:
  static std::optional<AutomataType> fromString(const std::string& text) {
    std::string lower_text = text;
    std::transform(lower_text.begin(), lower_text.end(), lower_text.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (lower_text == "es" || lower_text == "pdaes" ||
        lower_text == "emptystack") {
      return AutomataType::PDAES;
    } else if (lower_text == "fs" || lower_text == "pdafs" ||
               lower_text == "finalstate") {
      return AutomataType::PDAFS;
    } else {
      return std::nullopt;
    }
  }

  /**
   * @brief Transforms a AutomataType enum to its string representation
   */
  static std::string toString(AutomataType type) {
    switch (type) {
    case AutomataType::PDAES:
      return "PDAES (Empty Stack)";
    case AutomataType::PDAFS:
      return "PDAFS (Final State)";
    default:
      return "Unknown";
    }
  }
};

#endif  // PDA_TYPE_H_