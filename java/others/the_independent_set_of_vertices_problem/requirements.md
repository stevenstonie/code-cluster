#### requirements

The student associations in the city of 'O' intend to organize a sports day on a weekend, so that students from different universities in the city can meet and spend time together. Several team sports events will be organized (football, volleyball, basketball, etc.) and each student can register for one or more of them. The games can be scheduled simultaneously as long as there are no students who have registered for two of them. The fields on which the sports events will take place belong to the University 'U' and there are enough of them, so the simultaneous running of the games is not a problem.

The students in the associations propose that on Saturday afternoon at 12:00, there should be as many games as possible in progress, so that they can organize a festive meal at 17:00. In addition, officials from the universities in the city will also be invited to this event which starts at 12:00, and the association members want to have as many fields occupied at that time.

The task involves planning as many sports events as possible during this time interval. The problem of scheduling the sports events is modeled as a problem of determining a maximum independent set of vertices in a graph. The graph has a node associated with each game, and two nodes are connected by an edge if there is at least one student who has registered for the corresponding games of the two nodes.

#### -----------------------------

Write a Greedy heuristic algorithm (with polynomial complexity) to determine a MAXIMAL independent vertex set. The greedy method should select one node at a time to add to the independent set, according to certain criteria that you consider best.

The final solution should be an independent vertex set, even if it is not maximal. What is the selection criterion used? Could it be improved? Briefly justify that the algorithm runs in polynomial time.
