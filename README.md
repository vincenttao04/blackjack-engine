# Blackjack Strategy Engine

> **Project Status:** In Development

A C++ Blackjack strategy engine powered by Monte Carlo simulation. The program allows users to play Blackjack in the console and evaluate decisions by estimating the expected value (EV) of actions such as hit or stand.

Given a game state, the engine simulates millions of blackjack rounds and calculates the average outcome of each possible action to recommend the move with the highest EV.

Current number of simulations per decision: 1,000,000

```
g++ main.cpp src/\*.cpp -Iinclude -o blackjack  // compile
.\blackjack                                     // run
```

## TODO

- Multithreaded simulation to scale Monte Carlo runs into the millions _(in progress)_
- Use smiulation results for reinforcement learning model training
- Expand decision space (split, double, insurance, etc.)
- Implement running count and true count
- array vs vector - stack vs heap
