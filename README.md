# OthelloSimpleMCTS
Simple multithread MCTS Othello bot. Aim for performance with simplicity in mind.

The size of the board can vary. Recompile after config change

Sacrifices randomness for extra speed. Mixed in some minmax.

Maintains decent balance between RAM usage and tree structure.

# How to use
Run
```
pip install -r requirements.txt
make
./a.out
```

# Arguments
TimeLimit: time given for the AI to think at every step, should be a positive integer
ThreadCount: The amount of thread allocated to this program, should be a positive integer