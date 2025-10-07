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
 * @file pdaes-factory.h
 * @brief Header file for the Pushdown Automaton by Empty Stack Factory class
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 * Revision history:
 */

// #ifndef AUTOMATAFACTORY_PDAESFACTORY_PDAES_FACTORY_H_
// #define AUTOMATAFACTORY_PDAESFACTORY_PDAES_FACTORY_H_

// #include <memory>

// #include "../../Automata/PDA/PDAES/pdaes.h"
// #include "../../Parser/PDAESParser/pdaes-parser.h"
// #include "../AutomataFactory.h"

// /**
//  * @brief Factory concreta para crear autómatas de pila con estados finales
//  */
// class PDAESFactory
//     : public AutomataFactory<PDATransitionKey, PDATransitionValue> {
// public:
//   explicit PDAESFactory(const std::string& filename);
//   ~PDAESFactory() override = default;
//   std::unique_ptr<Automata<PDATransitionKey, PDATransitionValue>>
//   CreateAutomaton() override;

// private:
//   std::string filename_;
// };

// #endif  // AUTOMATAFACTORY_PDAESFACTORY_PDAES_FACTORY_H_