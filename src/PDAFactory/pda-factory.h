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
#include "pda-type.h"

/**
 * @brief Factory estática para crear autómatas
 */
class PDAFactory {
public:
  /**
   * @brief Crea un autómata del tipo especificado
   * @param type Tipo de autómata (PDAES o PDAFS)
   * @param filename Archivo de definición del autómata
   * @return Puntero único al autómata creado, o nullptr si hay error
   */
  static std::unique_ptr<PDA> createAutomata(PDAType type,
                                             const std::string& filename) {
    switch (type) {
    case PDAType::PDAES: {
      PdaESParser parser(filename);
      auto data = parser.parse();
      if (!data) {
        std::cerr << "Error parsing PDA file: " << data.error().message
                  << " at line " << data.error().line_number << std::endl;
        return nullptr;
      }

      auto pda = std::make_unique<PDAES>();
      pda->setStates(data->states);
      pda->setInputAlphabet(data->input_alphabet);
      pda->setStackAlphabet(data->stack_alphabet);
      pda->setInitialState(data->initial_state);
      pda->setInitialStackSymbol(data->initial_stack_symbol);
      pda->resetStack();

      return pda;      
    }
    case PDAType::PDAFS: {
      return std::make_unique<PDAFS>();
    }
    default:
      return nullptr;
    }
  }
};

#endif  // PDAFACTORY_PDAFACTORY_H_