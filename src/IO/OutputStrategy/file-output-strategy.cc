/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Complejidad Computacional
 * Curso: 4º
 * Práctica 1: Pushdown Automaton Simulator
 * @author Himar Edhey Hernández Alonso
 * Correo: alu0101552392@ull.edu.es
 * @date Oct 10 2025
 * @file file-output-strategy.cc
 * @brief File output strategy implementation
 * @bug There are no known bugs
 * @see https://github.com/Edhey/practica-1-automata-con-pila.git
 */

#include "file-output-strategy.h"

void FileOutputStrategy::writeResult(const std::string& input, bool accepted) {
  if (file_.is_open()) {
    file_ << "String '" << input
          << "': " << (accepted ? "ACCEPTED" : "REJECTED") << std::endl;

    // También mostrar en consola
    std::cout << "String '" << input
              << "': " << (accepted ? "ACCEPTED" : "REJECTED")
              << " (written to " << filename_ << ")" << std::endl;
  }
}

void FileOutputStrategy::finalize() {
  if (file_.is_open()) {
    file_.flush();
    file_.close();
    std::cout << "Results written to: " << filename_ << std::endl;
  }
}
