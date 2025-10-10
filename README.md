# PushDown Automaton - Practice 1
- **Author:** Himar Edhey Hernández Alonso
- **Subject:** Complejidad Computacional
- **Repository:** [GitHub Link](https://github.com/Edhey/practica-1-automata-con-pila.git)
---

## Introduction
In this project, we will implement a Pushdown Automaton (PDA) that can process strings based on a given set of states, input symbols, stack symbols, and transition functions. The PDA will be able to read input strings from either the keyboard or a file and determine whether the strings are accepted or rejected based on the defined transitions and stack operations.

---

## 🔧 Compilation

### Requirements
- C++20 or higher
- CMake 3.10+
- GCC/Clang with C++20 support

### Build Instructions

```bash
# Create build directory
mkdir build && cd build

# Configure CMake
cmake ..

# Compile
cmake -DCMAKE_BUILD_TYPE=Debug .. 
# or for release
cmake -DCMAKE_BUILD_TYPE=Release ..

# The executable will be: build/stack-automaton
Usage: stack-automaton <mode> <automaton_file.txt> [options]

Modes:
  <es|PDAES|emptystack> - Empty Stack PDA
  <fs|PDAFS|finalstate> - Final State PDA

Options:
  -i, --input <file>     Read input strings from file
  -o, --output <file>    Write results to file
  -t, --trace            Enable execution trace
  -h, --help             Show this help message

Examples:
  stack-automaton es automaton.txt
  stack-automaton fs automaton.txt -i strings.txt -o results.txt
  stack-automaton PDAES automaton.txt --trace
  stack-automaton PDAFS automaton.txt -i strings.txt -t -o trace.txt
```

---

## 📄 File Format
The input file defines the PDA structure and transitions. There are two formats supported: PDAES (Empty Stack) and PDAFS (Final State). The PDAFS format must include a line for final statesa after the initial stack symbol.

### PDAES (Empty Stack) Format

```
# States (one or more characters each)
q0 q1 q2
# Input alphabet (single characters)
a b
# Stack alphabet (single characters)
S A B
# Initial state
q0
# Initial stack symbol
S
# Transitions: state input_symbol stack_top next_state push_string
# Use . for epsilon
q0 a . q1 aS
q1 b A q1 .
q1 . S q2 .
```

### PDAFS (Final State) Format

```
# States
q0 q1 qf
# Input alphabet
a b
# Stack alphabet
S A
# Initial state
q0
# Initial stack symbol
S
# Final states (NEW LINE)
qf
# Transitions
q0 a . q1 aS
q1 b A qf .
```
## Implementation Details
### Key Components:
The PDA is implemented in C++ using Object-Oriented Programming principles. The main components include:
- **`Automata<KeyType, ValueType>`**: Base template class for all automata
- **`PDA`**: Pushdown automaton base class with stack management
- **`PDAES`**: Acceptance by empty stack (recursive implementation)
- **`PDAFS`**: Acceptance by final state (iterative BFS implementation)
- **`State<KeyType, ValueType>`**: Represents states with transitions
- **`Alphabet<T>`**: Manages symbol sets
- **`PdaParser`**: Base parser with template method pattern
- **`Transition`**: Struct defining the concrete transition rules.

### Workflow:
The workflow that I followed to implement the PDA is as follows:
I defined a base class `Automata` that contains the common attributes and methods for all types of automata. this class contains the states, input alphabet, initial state and epsilon character that every automaton will have.

For the State representation, I created a `State` that holds the transitions as a multimap, allowing multiple transitions for the same input symbol and stack top symbol. For this I used two Typenames `KeyType` and `ValueType` for defining the key and value of the transitions to make the class more generic and reusable.

Following this, I implemented in the pda-transitions file two structs, `PDATransitionKey` and `PDATransitionValue`, to define the structure of the transition rules specific to PDAs. The key consists of the input symbol and the stack top symbol, while the value includes the next state and the string to push onto the stack.

Then the class `Alphabet` was created to manage the input and stack alphabets, ensuring that only valid symbols are used in transitions.

I created also a derived class `PDA` that extends `Automata` and adds stack management functionality. This class includes methods for pushing and popping symbols from the stack, as well as checking the stack's top symbol. It works as a interface for the specific PDA implementations.

Finally, I implemented two specific PDA types: `PDAES` for acceptance by empty stack and `PDAFS` for acceptance by final state. The `PDAES` class uses a recursive approach to explore all possible transitions, while the `PDAFS` class employs an iterative breadth-first search (BFS) strategy to find an accepting path using a queue.

I also created a `PdaParser` class to handle the parsing of the input file and the instantiation of the appropriate PDA type based on the file's content. This is a base class that uses the template method pattern to define the steps for parsing, while allowing subclasses to implement specific parsing logic for different PDA types (in this case PDAES and PDAFS). It checks for the correct format and populates the automaton's states, transitions, and other attributes. This modular design allowed me to use the Factory Method pattern to create instances of the specific PDA types based on the input file, using polymorphism to handle different Automatons through a common interface.


For the trace functionality, I added an optional output stream parameter to the `isAccepted` method in both PDA types. If trace mode is enabled, the current configuration (state, remaining input, stack content and posible transitions) is printed at each step of the computation. The trace was implemented **only** in the `PDAES` recursive isAccepted method, as it is more straightforward to show the recursive calls and stack changes. The PDAFS method could be extended similarly but it was not implemented cause time constraints.

Finally, I implemented input and output strategies using the Strategy pattern. The `InputStrategy` interface defines a method for reading input strings, with concrete implementations for reading from the console (`ConsoleInputStrategy`) and from a file (`FileInputStrategy`). Similarly, the `OutputStrategy` interface defines a method for writing results, with implementations for writing to the console (`ConsoleOutputStrategy`) and to a file (`FileOutputStrategy`). This allows flexibility in how inputs are provided and results are displayed or stored. All inputs string must be read before processing them, and all results must be written after processing them.

## IA Use
This project is self-made, but I used AI tools, in this case Copilot, to help me in the development of some parts of the code. Mainly for writing boilerplate code and for suggesting improvements in certain functions.