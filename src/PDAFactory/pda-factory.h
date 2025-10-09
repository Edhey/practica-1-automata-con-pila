/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown PDAcreateAutomata Simulator
 * @author Himar Edhey Hernández Alonso
 * Correo: alu0101552392@ull.edu.es
 * @date Sep 15 2025
 * @file pda-factory.h
 * @brief Factory for creating different types of pushdown automata
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

#ifndef PDAFACTORY_PDAFACTORY_H_
#define PDAFACTORY_PDAFACTORY_H_

#include <memory>
#include <string>

#include "../Automata/PDA/PDAES/pdaes.h"
#include "../Automata/PDA/PDAFS/pdafs.h"
#include "../Automata/PDA/pda.h"
#include "../Parser/PDAParser/pda-parser.h"
#include "../Parser/PDAParser/PDAESParser/pdaes-parser.h"
#include "../Parser/PDAParser/PDAFSParser/pdafs-parser.h"
#include "pda-type.h"

/**
 * @brief Factory class for creating Pushdown Automata (PDA) of different types.
 */
class PDAFactory {
public:
  /**
   * @brief Creates a PDA (Pushdown Automaton) of the specified type.
   * @param type The type of PDA to create (PDAES or PDAFS).
   * @param filename The path to the PDA definition file.
   * @return A unique pointer to the created PDA, or nullptr on error.
   */
  static std::unique_ptr<PDA> createAutomata(PDAType type,
                                             const std::string& filename) {
    switch (type) {
    case PDAType::PDAES: {
      return createPDAES(filename);     
    }
    case PDAType::PDAFS: {
      return createPDAFS(filename);
    }
    default:
      return nullptr;
    }
  }

private:
  static std::unique_ptr<PDA> createPDAES(const std::string& filename);
  static std::unique_ptr<PDA> createPDAFS(const std::string& filename);
};

#endif  // PDAFACTORY_PDAFACTORY_H_