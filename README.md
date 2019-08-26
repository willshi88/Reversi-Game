# Reversi-Game (Othello)
Self-developed AI strategy for Reversi
<p>Computer Reversi Game and also an AI Player for AI Competition.</p>
<p>this project consists of a GUI for Playing Othello and also an AI Player.</p>

<br/>
<p align="center">
  <img width="500" height="522" src="/../master/demo.gif?raw=true"/>
  
  <p align="center">AI Algorithm (Black) vs. Greedy Algorithm (White)</p>
</p>

![image](Images/Picture.png)


AI Strategy
-------
(Different strategies are measured and weighted according to chess number placed / fixed standard):

* Flipped decision, which measures the number of opponent's chess to be flipped. (Always moderatedly weighted)

* Mobility decision, which measures the available positions can be placed. (Weight dimished gradually)

* Last move decision, which measures the number you flipped at last 3 moves. (Weights increase at the end greatly)

* Corner decision (4 corners, always highly weighted)

* Numbers decision, which measures the absolute difference of chess numbers. (Weight increases gradually, and highly weighted in the end)

* Trying applying simulated annealing strategy
